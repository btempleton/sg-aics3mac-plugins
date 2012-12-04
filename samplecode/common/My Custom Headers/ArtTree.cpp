/*
 *  ArtTree.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 11/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ArtTree.h"
#include "error.h"
#include "Node.h"

AIArtHandle GetArtObjectByName(ai::UnicodeString targetName, int CORNER /* =-1 */, Node* const startNode, Node* const currNode) {
	long count = 0;
	ai::UnicodeString currArtName;
	ASBoolean isDefault = TRUE;
	AIArtHandle currArtObj = NULL;
	
	AIArtSet allArt; sAIArtSet->NewArtSet(&allArt);
	
	AIArtSpec allSpecs[] = { { kPathArt , 0 , 0 },
							  { kCompoundPathArt , 0 , 0 },
							  { kPlacedArt , 0 , 0 },
							  { kRasterArt , 0 , 0 },
							  { kPluginArt , 0 , 0 },
							  { kMeshArt , 0 , 0 },
							  { kTextFrameArt , 0 , 0 },
							  { kSymbolArt , 0 , 0 },
							  { kGroupArt , 0 , 0 },
							};

	sAIArtSet->MatchingArtSet( allSpecs , 9, allArt );
	
	sAIArtSet->CountArtSet(allArt, &count);
	
	for(int i=0; i < count ; i++) {
		sAIArtSet->IndexArtSet(allArt, i, &currArtObj);
		if(currArtObj) {
			AIErr error = sAIArt->GetArtName(currArtObj, currArtName, &isDefault);
			if ( error == kNoErr ) {
				if (!isDefault) {
					if (currArtName == targetName) {
						//If the closest node is the one passed in, or CORNER is the default -1
						if ( FindClosestNode(currArtObj, CORNER) == currNode || CORNER == -1) {
							sAIArtSet->DisposeArtSet(&allArt); allArt = NULL;
							return currArtObj;
						}
					}
				}
			}
		}
	}
	
	sAIArtSet->DisposeArtSet(&allArt); allArt = NULL;
	return NULL;
}


long CreateArtSetFromLayer(ai::UnicodeString layerName,  AIArtSet const targetSet) {
	AILayerHandle hLayer = NULL;
	long count = 0;
	
	//Find the layer called layerName
	sAILayer->GetLayerByTitle(&hLayer, layerName);
	if(!hLayer) { errorMessage = "Could not find Layer " + layerName.as_Platform(); sADMBasic->MessageAlert( errorMessage.c_str() ); return 0; }
	
	if (hLayer) {
		//Store the User Attributes
		int eflag = 0; int vflag = 0;
		ASBoolean editable = FALSE;
		ASBoolean visible = FALSE;
		//Check if the layer is editable
		sAILayer->GetLayerEditable(hLayer, &editable);
		sAILayer->GetLayerVisible(hLayer, &visible);
		
		//Unlock and Unhide the layer
		if (!editable) { sAILayer->SetLayerEditable(hLayer, TRUE); eflag = 1; }
		if (!visible) { sAILayer->SetLayerVisible(hLayer, TRUE); vflag = 1; }
		
		//Create a new art set and fill it with the art in LAYER_WITH_PLATE_INFO
		//Get the first art of the layer, which is a group containing all the objects in the layer
		//Then, get the first child, which should be the topmost art object, we'll then add each one to the set
		//hopefully keeping them in the z-order they were in to begin with
		AIArtHandle tempArtHandle = NULL; AIArtHandle currArtHandle = NULL;
		sAIArt->GetFirstArtOfLayer(hLayer, &tempArtHandle);
		sAIArt->GetArtFirstChild(tempArtHandle, &currArtHandle);
		
		
		while (currArtHandle) {
			sAIArtSet->AddArtToArtSet(targetSet, currArtHandle);
			tempArtHandle = currArtHandle;
			sAIArt->GetArtSibling(tempArtHandle, &currArtHandle);
		}
		
		//Make sure there's art in it
		sAIArtSet->CountArtSet(targetSet, &count);
		
		//Set the layer and art attributes back the way they were
		if(eflag) { sAILayer->SetLayerEditable(hLayer, FALSE);}
		if(vflag) { sAILayer->SetLayerVisible(hLayer, FALSE); }
	}
	return count;
}

void MoveArtToTopOfLayer(AIArtHandle currArtHandle) {
	AILayerHandle layer = NULL; sAIArt->GetLayerOfArt(currArtHandle, &layer);
	if (!layer) {
		return;
	}
	AIArtHandle layerGroup; sAIArt->GetFirstArtOfLayer(layer, &layerGroup);
	
	int eflag = 0; int vflag = 0;
	ASBoolean editable = FALSE;
	ASBoolean visible = FALSE;
	
	long attr = 0;
	
	//Check if the layer is editable
	sAILayer->GetLayerEditable(layer, &editable);
	sAILayer->GetLayerVisible(layer, &visible);
	
	//Set the layer editable and visible, set flags so we can set it back the way it was
	if (!editable) { sAILayer->SetLayerEditable(layer, TRUE); eflag = 1; }
	if (!visible) { sAILayer->SetLayerVisible(layer, TRUE); vflag = 1; }
	
	//Check if the art itself is editable
	sAIArt->GetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, &attr);
	if ((attr & kArtLocked) || (attr & kArtHidden)) {
		sAIArt->SetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, 0);
	}
	
	//Move it out of the group
	sAIArt->ReorderArt(currArtHandle, kPlaceInsideOnTop, layerGroup);
	
	//Set the layer and art attributes back the way they were
	if(eflag) { sAILayer->SetLayerEditable(layer, FALSE); }
	if(vflag) { sAILayer->SetLayerVisible(layer, FALSE); }
	sAIArt->SetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, attr);
	
	return;
}


void PutArtInGroup(AIArtHandle currArtHandle, AIArtHandle theGroup) {
	AILayerHandle layer = NULL; sAIArt->GetLayerOfArt(currArtHandle, &layer);
	if (!layer) {
		return;
	}
	AIArtHandle layerGroup; sAIArt->GetFirstArtOfLayer(layer, &layerGroup);

	int eflag = 0; int vflag = 0;
	ASBoolean editable = FALSE;
	ASBoolean visible = FALSE;
	
	long attr = 0;
	
	//Check if the layer is editable
	sAILayer->GetLayerEditable(layer, &editable);
	sAILayer->GetLayerVisible(layer, &visible);
	
	//Set the layer editable and visible, set flags so we can set it back the way it was
	if (!editable) { sAILayer->SetLayerEditable(layer, TRUE); eflag = 1; }
	if (!visible) { sAILayer->SetLayerVisible(layer, TRUE); vflag = 1; }
	
	//Check if the art itself is editable
	sAIArt->GetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, &attr);
	if ((attr & kArtLocked) || (attr & kArtHidden)) {
		sAIArt->SetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, 0);
	}
	
	//Move it out of the group
	sAIArt->ReorderArt(currArtHandle, kPlaceInsideOnTop, theGroup);
	
	//Set the layer and art attributes back the way they were
	if(eflag) { sAILayer->SetLayerEditable(layer, FALSE); }
	if(vflag) { sAILayer->SetLayerVisible(layer, FALSE); }
	sAIArt->SetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, attr);
	
	return;
}

bool AllLinkedFilesValid() {
	long count = 0;
	ai::UnicodeString currArtName;
	AIArtHandle currArtObj = NULL;

	AIArtSet artSet; sAIArtSet->NewArtSet(&artSet);
	
	AIArtSpec specs[] = { { kPlacedArt , 0 , 0 } };

	sAIArtSet->MatchingArtSet( specs , 1, artSet );
	
	sAIArtSet->CountArtSet(artSet, &count);
	
	for(int i=0; i < count ; i++) {
		sAIArtSet->IndexArtSet(artSet, i, &currArtObj);
		if(currArtObj) {
			ai::FilePath path;
			sAIPlaced->GetPlacedFileSpecification(currArtObj, path);
			if (!path.Exists(TRUE)) {
				sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
				return FALSE;
			}
		}
	}
	
	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
	return TRUE;
}

AIArtHandle FindTopLevelParent(AIArtHandle currArtHandle) {
	AIArtHandle currParent = NULL;
	AIArtHandle parent = NULL;
	parent = currParent = currArtHandle;
	
	//If we have an object that is part of a group, we need to find the bounds of the top level parent group and use those for how much to move it
	while (currParent) {
		sAIArt->GetArtParent(parent, &currParent);
		if (currParent) {
			ASBoolean isLayer = FALSE;
			sAIArt->IsArtLayerGroup(currParent, &isLayer);
			if (isLayer) {
				sAIArt->GetArtParent(currParent, &currParent);
			} else {
				parent = currParent;
			}
		}
	}
	return parent;
}


bool IsArtInArtSet(AIArtSet artSet, AIArtHandle theObject)
{
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	for ( int i=0 ; i < count ; i++ ) {
		AIArtHandle currArtHandle = NULL;
		sAIArtSet->IndexArtSet( artSet, i, &currArtHandle );
		if (currArtHandle == theObject) {
			return TRUE;
		}
	}
	return FALSE;
}


void GetBoundsOfSelectionFromRoot(AIArtHandle root, AIArtHandle currArtHandle, AIRealRect* bounds, bool* boundsValid) {
	
	AIArtHandle child, sibling;
	child = sibling = NULL;
	
	bool boundsSet = FALSE;
	
/*	//Check if this object is in a clipping mask and store the bounds of the mask so we don't get bounds of stuff that's clipped
	AIBoolean clipped = FALSE;
	sAIGroup->GetGroupClipped(currArtHandle, &clipped);
	
	AIArtHandle parent = NULL;
//	sAIArt->GetArtParent(currArtHandle, &parent);
//	while (parent && !clipBoundsSet) {
		AIArtHandle tempHandle = parent;
		
		long attr = 0;
		sAIArt->GetArtUserAttr(currArtHandle, kArtIsClipMask, &attr);
		if (attr & kArtIsClipMask) {
			sAIArt->GetArtTransformBounds(currArtHandle, NULL, kVisibleBounds | kExcludeHiddenObjectBounds | kExcludeGuideBounds, &clipBounds);
			clipBoundsSet = TRUE;
		}
		sAIArt->GetArtParent(tempHandle, &parent);
//	}
*/	
	//TODO: FIX CLIPPING PATH
	// If Fully Selected, start going through children and siblings, stop drilling down when a clipping group is encountered
	// This way, we'll only get the bounds of stuff that isn't inside a clipping mask.
//	long attr = 0;
//	AIBoolean isClipMask = FALSE;
//	sAIArt->GetArtUserAttr(currArtHandle, kArtIsClipMask, &attr);
//	if (attr & kArtIsClipMask) { isClipMask = TRUE; }

	AIBoolean clipped = FALSE;
	sAIGroup->GetGroupClipped(currArtHandle, &clipped);
	
	short artType = 0;
	sAIArt->GetArtType(currArtHandle, &artType);
	if ((artType == kGroupArt) || (artType == kCompoundPathArt)) {
	
		AIRealRect tempBounds;
		bool tempBoundsValid = FALSE;
		
		if (clipped) {
			GetBoundsOfClipGroup(currArtHandle, currArtHandle, &tempBounds, &tempBoundsValid);
		} else {
			sAIArt->GetArtFirstChild(currArtHandle, &child);
			if (child) {
				GetBoundsOfSelectionFromRoot(root, child, &tempBounds, &tempBoundsValid);
			}
		}
		if (tempBoundsValid) {
			//Check if bounds has contents already
			if (!boundsSet) {
				//If we got valid bounds, store these ones
				sAIRealMath->AIRealRectSet(bounds, tempBounds.left, tempBounds.top, tempBounds.right, tempBounds.bottom);
				*boundsValid = TRUE;
				boundsSet = TRUE;
			} else {
				//If we have bounds, Union these bounds with them
				//Set existingBounds = bounds
				AIRealRect existingBounds;
				sAIRealMath->AIRealRectSet(&existingBounds, bounds->left, bounds->top, bounds->right, bounds->bottom);
				
				sAIRealMath->AIRealRectUnion(&existingBounds, &tempBounds, bounds);
				*boundsValid = TRUE;
				boundsSet = TRUE;
			}
		}
	}
	else if (artType == kPathArt){
		//RETURN BOUNDS OF SELECTED SEGMENTS
		short count;
		sAIPath->GetPathSegmentCount(currArtHandle, &count);
		AIPathSegment* segments = NULL;
		segments = new AIPathSegment[count];
		
		AIRealRect segBounds;
		bool segBoundsSetFlag = FALSE;
		
		sAIPath->GetPathSegments(currArtHandle, 0, count, segments);
		
		for (int i=0 ; i<count ; i++) {
			short selected = 0;
			sAIPath->GetPathSegmentSelected(currArtHandle, i, &selected);
			
			if (selected == kSegmentPointSelected) {
				if (!segBoundsSetFlag) {
					//If we don't have bounds yet, store these ones
					sAIRealMath->AIRealRectSet(&segBounds, segments[i].p.h, segments[i].p.v, segments[i].p.h, segments[i].p.v);
					
					sAIRealMath->AIRealRectSet(bounds, segBounds.left, segBounds.top, segBounds.right, segBounds.bottom);
					segBoundsSetFlag = TRUE;
					boundsSet = TRUE;
				} else {
					//If we have segBounds, Union these bounds with them
					AIRealRect tempBounds;
					sAIRealMath->AIRealRectSet(&tempBounds, segBounds.left, segBounds.top, segBounds.right, segBounds.bottom);
					sAIRealMath->AIRealRectSet(&segBounds, segments[i].p.h, segments[i].p.v, segments[i].p.h, segments[i].p.v);
					
					sAIRealMath->AIRealRectUnion(&segBounds, &tempBounds, bounds);
					boundsSet = TRUE;
				}
			}
		}
		delete [] segments;
		if (boundsSet) {
			*boundsValid = TRUE;
		}
	} else {
		//ANY OTHER ART TYPES
		sAIArt->GetArtTransformBounds(currArtHandle, NULL, kVisibleBounds | kExcludeHiddenObjectBounds | kExcludeGuideBounds, bounds);
		
		*boundsValid = TRUE;
		boundsSet = TRUE;			
	}

	//CHECK CURR != ROOT
	if (currArtHandle != root) {
		//GET BOUNDS OF SIBLING
		sAIArt->GetArtSibling(currArtHandle, &sibling);
		if (sibling) {
			AIRealRect tempBounds;
			bool tempBoundsValid = FALSE;
			GetBoundsOfSelectionFromRoot(root, sibling, &tempBounds, &tempBoundsValid);
			if (tempBoundsValid) {

				//Check if bounds has contents already
				if (!boundsSet) {
					//If we got valid bounds, store these ones
					sAIRealMath->AIRealRectSet(bounds, tempBounds.left, tempBounds.top, tempBounds.right, tempBounds.bottom);
					boundsSet = TRUE;
					*boundsValid = TRUE;
				} else {
					//If we have bounds, Union these bounds with them
					//Set existingBounds = bounds
					AIRealRect existingBounds;
					sAIRealMath->AIRealRectSet(&existingBounds, bounds->left, bounds->top, bounds->right, bounds->bottom);
					
					sAIRealMath->AIRealRectUnion(&existingBounds, &tempBounds, bounds);
					boundsSet = TRUE;
					*boundsValid = TRUE;
				}
			}
		}
	}
}


void GetBoundsOfClipGroup(AIArtHandle root, AIArtHandle currArtHandle, AIRealRect* bounds, bool* boundsValid) {
	AIArtHandle child, sibling;
	child = sibling = NULL;
	
	bool boundsSet = FALSE;
	
	long attr = 0;

	sAIArt->GetArtUserAttr(currArtHandle, kArtIsClipMask, &attr);
	if (attr & kArtIsClipMask) {
		sAIArt->GetArtTransformBounds(currArtHandle, NULL, kVisibleBounds | kExcludeHiddenObjectBounds | kExcludeGuideBounds, bounds);
		
		*boundsValid = TRUE;
		boundsSet = TRUE;	
	} else {
		short artType = 0;
		sAIArt->GetArtType(currArtHandle, &artType);
		
		if ((artType == kGroupArt) || (artType == kCompoundPathArt)) {
			sAIArt->GetArtFirstChild(currArtHandle, &child);
			if (child) {
				AIRealRect tempBounds;
				bool tempBoundsValid = FALSE;
				GetBoundsOfClipGroup(root, child, &tempBounds, &tempBoundsValid);
				
				if (tempBoundsValid) {
					//Check if bounds has contents already
					if (!boundsSet) {
						//If we got valid bounds, store these ones
						sAIRealMath->AIRealRectSet(bounds, tempBounds.left, tempBounds.top, tempBounds.right, tempBounds.bottom);
						boundsSet = TRUE;
						*boundsValid = TRUE;
					} else {
						//If we have bounds, Union these bounds with them
						//Set existingBounds = bounds
						AIRealRect existingBounds;
						sAIRealMath->AIRealRectSet(&existingBounds, bounds->left, bounds->top, bounds->right, bounds->bottom);
						
						sAIRealMath->AIRealRectUnion(&existingBounds, &tempBounds, bounds);
						boundsSet = TRUE;
						*boundsValid = TRUE;
					}
				}
			}			
		}
	}
	
	//CHECK CURR != ROOT
	if (currArtHandle != root) {
		//GET BOUNDS OF SIBLING
		sAIArt->GetArtSibling(currArtHandle, &sibling);
		if (sibling) {
			AIRealRect tempBounds;
			bool tempBoundsValid = FALSE;
			GetBoundsOfClipGroup(root, sibling, &tempBounds, &tempBoundsValid);
			
			if (tempBoundsValid) {
				//Check if bounds has contents already
				if (!boundsSet) {
					//If we got valid bounds, store these ones
					sAIRealMath->AIRealRectSet(bounds, tempBounds.left, tempBounds.top, tempBounds.right, tempBounds.bottom);
					boundsSet = TRUE;
					*boundsValid = TRUE;
				} else {
					//If we have bounds, Union these bounds with them
					//Set existingBounds = bounds
					AIRealRect existingBounds;
					sAIRealMath->AIRealRectSet(&existingBounds, bounds->left, bounds->top, bounds->right, bounds->bottom);
					
					sAIRealMath->AIRealRectUnion(&existingBounds, &tempBounds, bounds);
					boundsSet = TRUE;
					*boundsValid = TRUE;
				}
			}
		}
	}
}