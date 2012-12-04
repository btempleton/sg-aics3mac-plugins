
// Tell Xcode to export the following symbols
//#if defined(__GNUC__)
//#pragma GCC visibility push(default)
//#endif


#include "DictFuncs.h"
#include "CropAreaFuncs.h"

#import "Node.h"
#import "CException.h"

#include "common.h"
#import "BStatMU.h"

AIColor registrationColor;

extern AIDictionaryRef dictMain;
extern Node* startNode;


bool BStatMU() {
	//Set the undo/redo text
	sAIUndo->SetUndoText("Undo BStat Master Updater", "Redo BStat Master Updater");
	
	try {
		//Check that we're not using the crop tool
		AIToolType toolNumber = NULL;
		AIToolHandle toolHandle = NULL;
		AIToolHandle cropToolHandle = NULL;
		sAITool->GetToolNumberFromName(kCropTool, &toolNumber);
		sAITool->GetToolHandleFromNumber(toolNumber, &cropToolHandle);
		sAITool->GetSelectedTool(&toolHandle);
		if ( toolHandle == cropToolHandle ) { throw [CException withCode:ecCropToolSelected]; }
		
		//Retrieve the dictionary for this file
		sAIDocument->GetDictionary(&dictMain);
		
		//Initialize the offset rectangle
		sAIRealMath->AIRealRectSet(&offsetRect, 0, 0, 0, 0);
		
		//Force the crop area to update
		ForceCropCoordUpdate();
		
		//We need to check the document origin before we do anything else
		if ( !DocumentOriginInLowerLeft() ) { throw [CException withCode:ecBadOriginPoint]; }
		
		//Store "Registration" in registrationColor
		AICustomColorHandle cchReg;
		sAICustomColor->GetCurrentRegistrationColor(&cchReg);
		registrationColor.kind = kCustomColor;
		registrationColor.c.c.tint = 0;
		registrationColor.c.c.color = cchReg;
	
		
		SetUpNodes();
	
		
		//We need to check for a couple specific things
		KeyObjectsFound();
				
		//Now that we've run successfully, we'll store a BStat Version number in the main dict
		sAIDictionary->SetRealEntry(dictMain, sAIDictionary->Key("BSTATMU_VERSION"), BSTATMU_VERSION);
		
		//Set the insertion point at the foreground layer
		AILayerHandle foregroundLayer = NULL;
		sAILayer->GetLayerByTitle(&foregroundLayer, FOREGROUND_LAYER );
		sAILayer->SetCurrentLayer( foregroundLayer );
		//Set the current tool to something useful -- seems to get stuck on the blend tool otherwise
		sAITool->GetToolNumberFromName(kTypeTool, &toolNumber);
		sAITool->GetToolHandleFromNumber(toolNumber, &toolHandle);
		sAITool->SetSelectedTool(toolHandle);
		
		//Set our layer visibilities back to default
		AILayerHandle layer = NULL;
		sAILayer->GetLayerByTitle(&layer, KEYLINE_LAYER );
		sAILayer->SetLayerVisible(layer, FALSE);
		sAILayer->GetLayerByTitle(&layer, REG_LAYER );
		sAILayer->SetLayerVisible(layer, TRUE);
		sAILayer->GetLayerByTitle(&layer, SLUG_LAYER );
		sAILayer->SetLayerVisible(layer, TRUE);
		sAILayer->GetLayerByTitle(&layer, FOREGROUND_LAYER );
		sAILayer->SetLayerVisible(layer, TRUE);
		sAILayer->GetLayerByTitle(&layer, GUIDE_LAYER );
		sAILayer->SetLayerVisible(layer, FALSE);
		sAILayer->GetLayerByTitle(&layer, BACKGROUND_LAYER );
		sAILayer->SetLayerVisible(layer, FALSE);
		
		CleanUpNodes();
		
		sAIDictionary->Release(dictMain);
		return TRUE;
	}
	
	
	catch(CException* e) {
		NSRunAlertPanel(@"Error!", 
                        [e getDescription],
                        @"OK", nil, nil);
		sAIUndo->UndoChanges();
		
		return FALSE;
	}
}

bool DocumentOriginInLowerLeft() {
	ForceCropCoordUpdate();
	
	ASInt32 cropCount;
	sAICropArea->GetCount(&cropCount);
	
	AIRealPoint origin = {0,0};
	AIRealPoint nodeOrigin, hardOrigin, hardNodeOrigin;
	AIRealRect nodeRect;
	
	//If there aren't any crop areas, we can store the page boundary
	if (cropCount == 0) {
		AIPageTiling pageTiling;
		sAIDocumentView->GetPageTiling(&pageTiling);
		sAIRealMath->AIRealRectSet(&nodeRect, pageTiling.bounds.left, pageTiling.bounds.top, pageTiling.bounds.right, pageTiling.bounds.bottom);
	}
	//If there are crop areas, store the first one
	else {
		AICropAreaPtr cropArea;
		sAICropArea->Get(0, &cropArea);
		nodeRect = cropArea->m_CropAreaRect;
	}
	
	//Store the Node Origin
	nodeOrigin.h = nodeRect.left;
	nodeOrigin.v = nodeRect.bottom;
	
	sAIHardSoft->AIRealPointHarden(&origin, &hardOrigin);
	sAIHardSoft->AIRealPointHarden(&nodeOrigin, &hardNodeOrigin);
	
	if (!sAIRealMath->AIRealPointClose(&hardOrigin, &hardNodeOrigin, 4)) {
		return FALSE;
	}
	
	return TRUE;
}


bool KeyObjectsFound() {
	
	AIArtHandle currArtHandle = NULL;
	Node* currNode = startNode;
	ai::UnicodeString artName;
	
	try {
		while ( currNode ) {
			//If we have a non-printing plate, we don't need to worry about checking for stuff
			if(!currNode->p->Prints()) { currNode = currNode->nextNode; continue;}
			
			//************ REGISTRATION BOX ***************** //
			currArtHandle = NULL;
			if (!currNode->p->RegBoxUIDRef()) {
				throw [CException withCode:ecKeyObjectNotFound];		
			} else {
				currArtHandle = GetArtHandleFromUIDRef(currNode->p->RegBoxUIDRef());
				if (!currArtHandle) {
					throw [CException withCode:ecKeyObjectNotFound];
				} else {
					sAIArt->GetArtName(currArtHandle, artName, NULL);
					char name[50];
					artName.as_Platform(name, 50);
					if (artName != REGISTRATION_BOX_LABEL) {
						throw [CException withCode:ecKeyObjectNotFoundRegBox];
					}
				}
			}
			
			
			//************ PLATE NUMBER ***************** //	
			currArtHandle = NULL;
			if (!currNode->p->PlateNumberUIDRef()) {
				throw [CException withCode:ecKeyObjectNotFound];		
			} else {
				currArtHandle = GetArtHandleFromUIDRef(currNode->p->PlateNumberUIDRef());
				if (!currArtHandle) {
					throw [CException withCode:ecKeyObjectNotFound];
				} else {
					sAIArt->GetArtName(currArtHandle, artName, NULL);
					if (artName != PLATE_NUMBER_LABEL) {
						throw [CException withCode:ecKeyObjectNotFoundPlateNum];
					}
				}
			}
			
			
			//************ DATE ***************** //	
			currArtHandle = NULL;
			if (!currNode->p->DateUIDRef()) {
				throw [CException withCode:ecKeyObjectNotFound];		
			} else {
				currArtHandle = GetArtHandleFromUIDRef(currNode->p->DateUIDRef());
				if (!currArtHandle) {
					throw [CException withCode:ecKeyObjectNotFound];
				} else {
					sAIArt->GetArtName(currArtHandle, artName, NULL);
					if (artName != DATE_LABEL) {
						throw [CException withCode:ecKeyObjectNotFoundDate];
					}
				}
			}
			
			
			//************ COLOR LIST ***************** //	
			currArtHandle = NULL;
			if (!currNode->p->ColorListUIDRef()) {
				throw [CException withCode:ecKeyObjectNotFound];		
			} else {
				currArtHandle = GetArtHandleFromUIDRef(currNode->p->ColorListUIDRef());
				if (!currArtHandle) {
					throw [CException withCode:ecKeyObjectNotFound];
				} else {
					sAIArt->GetArtName(currArtHandle, artName, NULL);
					if (artName != COLOR_LIST_LABEL) {
						throw [CException withCode:ecKeyObjectNotFoundColorList];
					}
				}
			}
			
			
			currNode = currNode->nextNode;
		}
		
	return TRUE;	

	}
	
	catch(CException* e) {
		throw;
	}
}