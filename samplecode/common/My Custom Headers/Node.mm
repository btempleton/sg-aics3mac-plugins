/*
 *  Node.cpp
 *  
 *
 *  Created by Comp Mac 8a on 1/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#import <Cocoa/Cocoa.h>

#include "Node.h"
#include "ArtTree.h"
#include "ATEFuncs.h"
#include "ColorFuncs.h"
#import "CException.h"
#include "DictFuncs.h"

AIDictionaryRef dictMain = NULL;
Node* startNode = NULL;

//Declare a global pointer to the Find Functions array
const FIND_FUNCTIONS* find_functions = NULL;

extern AIColor registrationColor;


//Constructor
Node::Node(Node* const pNode, int CAIndex) {
	prevNode = pNode;
	nextNode = NULL;
	
	p = new Plate(CAIndex);
		
	if (prevNode) { prevNode->nextNode = this; }
	else { startNode = this; }
}

Node::~Node() {
	//Remove this node from our linked list
	if ( nextNode ) {
		if (prevNode) {
			prevNode->nextNode = nextNode;      // Case for middle Nodes
			nextNode->prevNode = prevNode;
		} else {
			startNode = nextNode;
			nextNode->prevNode = NULL;         // Case for first Node
		}
	} else {
		if (prevNode) {
			prevNode->nextNode = NULL;         // Case for last Node
		}
	}
	
	//Clean up the plate
	delete p;
}


void SetUpNodes() {
	//We need to find the crop areas and make a specific plate for each one
	ASInt32 cropCount;
	sAICropArea->GetCount(&cropCount);
	
	Node* currNode = NULL;
	startNode = NULL;
	
	//If there are no crop areas, we need one node
	if (cropCount == 0) {
		currNode = new Node();
		startNode = currNode;
	}	
	//If there are multiple crop areas, we need a node for each one
	else {
		for ( int i=0 ; i < cropCount ; i++ ) {
			//Create the new Node/Plate
			currNode = new Node(currNode, i);
			if (i==0) startNode = currNode;
		}
	}
	
	//Set up the array of callback functions and tags, then store the pointer to it
	FIND_FUNCTIONS const callbackDataArray[] = {
		{ &Node::FindExtraColorListGroup,	LAYER_WITH_EXTRA_COLOR_GROUP,	EXTRA_COLOR_GROUP_LABEL,		LOWER_LEFT},	//0
		{ &Node::FindColorList,				LAYER_WITH_PLATE_INFO,			COLOR_LIST_LABEL,				LOWER_LEFT },	//1
		{ &Node::FindPlateNumber,			LAYER_WITH_PLATE_INFO,			PLATE_NUMBER_LABEL,				LOWER_RIGHT },	//2
		{ &Node::FindDate,					LAYER_WITH_PLATE_INFO,			DATE_LABEL,						LOWER_RIGHT },	//3
		{ &Node::FindProofTag,				LAYER_WITH_PROOF_INFO,			PROOF_TAG_LABEL,				UPPER_LEFT },	//4
		{ &Node::FindKeylineRegBox,			LAYER_WITH_KEYLINE_INFO,		KEYLINE_REGISTRATION_LABEL,		LOWER_LEFT },	//5
		{ &Node::FindKeylineEnvFlap,		LAYER_WITH_KEYLINE_INFO,		KEYLINE_ENV_FLAP_LABEL,			UPPER_LEFT },	//6
		{ &Node::FindKeylineSafeEmbossBox,	LAYER_WITH_KEYLINE_INFO,		KEYLINE_SAFE_EMBOSS_LABEL,		LOWER_LEFT },	//7
		{ &Node::FindKeylineFace,			LAYER_WITH_KEYLINE_INFO,		KEYLINE_FACE_LABEL,				LOWER_LEFT },	//8
		{ &Node::FindRegBox,				LAYER_WITH_REGISTRATION,		REGISTRATION_BOX_LABEL,			LOWER_LEFT },	//9
		{ &Node::FindRegEnvFlap,			LAYER_WITH_REGISTRATION,		REGISTRATION_ENV_FLAP_LABEL,	UPPER_LEFT },	//10
		{ &Node::FindRegSafeEmbossBox,		LAYER_WITH_REGISTRATION,		REGISTRATION_SAFE_EMBOSS_LABEL,	LOWER_LEFT },	//11
		{ &Node::FindBleedBox,				LAYER_WITH_BLEED,				BLEED_BOX_LABEL,				UPPER_LEFT },	//12
		{ &Node::FindGripperTop,			LAYER_WITH_GRIPPER,				GRIPPER_TOP_LABEL,				UPPER_LEFT },	//13
		{ &Node::FindGripperBottom,			LAYER_WITH_GRIPPER,				GRIPPER_BOTTOM_LABEL,			LOWER_LEFT },	//14
		{ &Node::FindGripperLeft,			LAYER_WITH_GRIPPER,				GRIPPER_LEFT_LABEL,				LOWER_LEFT },	//15
		{ &Node::FindGripperRight,			LAYER_WITH_GRIPPER,				GRIPPER_RIGHT_LABEL,			LOWER_RIGHT }	//16
	}; find_functions = callbackDataArray;
	
	//Now we need to cycle through each crop area and set the objects that belong to it
	//We do this after the Plates have all been constructed so that we know how many there are and also so 
	//we know where each one is. In general, we'll use proximity to determine what belongs to what.
	currNode = startNode;
	do {
		//Do all the initialization
		
		FindAllObjects(startNode, currNode);
		currNode->SetupAdditionalVars();
		
		currNode->p->PlateDictionaryStore();
		
		currNode = currNode->nextNode;
	} while (currNode);
	
	//Go through our nodes and make sure that the first node is the one that matches the filename
	currNode = startNode;
	
	//Get the file name
	ai::FilePath currDocPath;
	sAIDocument->GetDocumentFileSpecification(currDocPath);
	std::string fileNameStr = (currDocPath.GetFileNameNoExt()).as_UTF8();
	
	while(currNode) {
		if (currNode->p->PlateNumberStr().find(fileNameStr) != string::npos) {
			if (startNode == currNode) { break; }
			
			currNode->prevNode->nextNode = currNode->nextNode;
			if(currNode->nextNode) { currNode->nextNode->prevNode = currNode->prevNode; }
			currNode->prevNode = NULL;
			currNode->nextNode = startNode;
			startNode->prevNode = currNode;
			startNode = currNode;
		} else {
			currNode = currNode->nextNode;
		}
	}
	
}

void CleanUpNodes() {
	Node* currNode = NULL;
	
	currNode = startNode;
	
	//If there are multiple crop areas, we need a node for each one
	while ( startNode ) {
		startNode = currNode->nextNode;
		//Delete the node
		delete currNode;
		currNode = startNode;
	}
}



//Plate info
AIArtHandle Node::FindExtraColorListGroup(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
		short type = 0;
		sAIArt->GetArtType(currArtHandle, &type);
		
		//If this is the group with the extra colors in it, we have to find out if its closer to this plate, or some other one
		ASBoolean isLayer = FALSE;
		sAIArt->IsArtLayerGroup(currArtHandle, &isLayer);
		if (type == kGroupArt && isLayer == FALSE) {
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
				return currArtHandle;
			}
		}
	
	return NULL;
}

AIArtHandle Node::FindColorList(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere) {
	AIArtHandle hColorList = GetArtHandleFromUIDRef(this->p->ColorListUIDRef());
	AIArtHandle hExtraColorList = GetArtHandleFromUIDRef(this->p->ExtraColorListUIDRef());
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//We're only looking for text frames with the default name
	ASBoolean isDefault = FALSE; ai::UnicodeString artName;
	sAIArt->GetArtName(currArtHandle, artName, &isDefault);
	if (type == kTextFrameArt && isDefault) {
		
		//We check here to make sure the parent of this object is not the extra color list group
		AIArtHandle parent = NULL;
		ASBoolean isLayer;
		sAIArt->GetArtParent(currArtHandle, &parent);
		if (!parent) {
			return NULL;
		}
		sAIArt->IsArtLayerGroup(parent, &isLayer);
		if ( parent != hExtraColorList ) {
			//Now we know we've got a real color list and we can process it
			
			//If this art is closer to some other node, we don't even need to worry about it
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
								
				//Create the runs iterator
				ATE::TextRangeRef currATETextRangeRef;
				sAITextFrame->GetATETextRange(currArtHandle, &currATETextRangeRef);
				ATE::ITextRange currTextRange(currATETextRangeRef);
				
				ATE::ITextRunsIterator currTextRunsIterator = currTextRange.GetTextRunsIterator();
				
				//If there is stuff to iterate through
				if ( !currTextRunsIterator.IsEmpty() ) {
				
					//Loop through the runs
					while ( currTextRunsIterator.IsNotDone() ) {
						
						//Get the color of the current run
						AIColor currAIColor = GetAIColorFromATETextRange( currTextRunsIterator.Item() );
						
						//If the text is not in registration, we've got a color name
						if ( ! colorIsEqual(currAIColor, registrationColor , TRUE ) ) {
							
							//Get the contents of the current run to the buffer itemText
							char itemText[75];
							(currTextRunsIterator.Item()).GetContents(itemText, 75);
							
							//Now we can start stripping white spaces out to get the actual color words
							size_t begin, end;
							begin = string(itemText).find_first_not_of(WHITESPACES);
							//If the item is not completely whitespace we can add it to  our new point text
							if ( begin != string::npos ) {
								
								//If the color list point text hasn't been created, create it now
								if ( !hColorList ) {
									//Create a new Point Text
									//Set the anchor point based on the bounds of the other frame and the crop rectangle
									AIRealPoint anchor;
									AIRealRect bounds;
									sAIArt->GetArtBounds(currArtHandle, &bounds);
									AIRealRect cropArea = p->GetCropAreaRect();
									AIRealPoint a = {cropArea.left+3, bounds.bottom};
									AIRealPoint b = {cropArea.left+3, bounds.top};
									sAIRealMath->AIRealPointInterpolate(&a, &b, .7 , &anchor);
									
									//Create the object
									sAITextFrame->NewPointText(kPlaceAbove, currArtHandle, kHorizontalTextOrientation, anchor, &hColorList );
								}
								
								
								//Create the stripped string
								end = string(itemText).find_last_not_of(WHITESPACES);
								//Check this -- ColorListStr only contains the last color added
								p->ColorListStr( string(itemText).substr(begin, end+1) );
								
								//Get the range for our color list point text object
								ATE::TextRangeRef colorListRangeRef;
								sAITextFrame->GetATETextRange(hColorList, &colorListRangeRef);
								ATE::ITextRange colorListRange(colorListRangeRef);
								
								//Store the features, specifically we want the font, size, and color so the new text has the same look as the old one
								ATE::ICharFeatures currCharFeatures = (currTextRunsIterator.Item()).GetUniqueCharFeatures();
								
								//If there's text in the range, we'll put some spaces after it before we add the next color to it
								if ( colorListRange.GetSize() != 0 ) {
									colorListRange.InsertAfter("  ");
								}
								AddTextToRangeWithFeatures(p->ColorListStr(), currCharFeatures, currArtHandle, &colorListRange);
								
								
								currTextRunsIterator.Next();
								
								if ( currTextRunsIterator.IsDone() ) {
									//If this was the last run, we can delete art object we're pulling from
									sAIArt->DisposeArt(currArtHandle);
									currArtHandle = NULL;
								}
							} else {
								currTextRunsIterator.Next();
							}
						} else {
							currTextRunsIterator.Next();
						}
					}
				}
			}
		}
	}
	return hColorList; //Should still be NULL if the color list wasn't found
}

AIArtHandle Node::FindPlateNumber(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere) {
	AIArtHandle hPlateNumber = GetArtHandleFromUIDRef(this->p->PlateNumberUIDRef());
	AIArtHandle hDate = GetArtHandleFromUIDRef(this->p->DateUIDRef());
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//We're only looking for text frames with the default name
	ASBoolean isDefault = FALSE; ai::UnicodeString artName;
	sAIArt->GetArtName(currArtHandle, artName, &isDefault);
	if (type != kTextFrameArt || !isDefault) { return NULL; }
	
	//If this art is closer to some other node, we don't even need to worry about it
	if ( FindClosestNode(currArtHandle, lookWhere) != this ) { return NULL; }
	
	//We need to make sure the object is closer to the bottom right corner than to the upper left corner
	if ( FindClosestCorner(currArtHandle, this ) != LOWER_RIGHT ) { return NULL; }
	
	//Make sure the font size is less than 10
	if ( GetFontSizeFromAITextFrame(currArtHandle) > 10 ) { return NULL; }
	
	//Create the runs iterator
	ATE::TextRangeRef currATETextRangeRef;
	sAITextFrame->GetATETextRange(currArtHandle, &currATETextRangeRef);
	ATE::ITextRange currTextRange(currATETextRangeRef);
/*	ATE::ITextRunsIterator currTextRunsIterator = currTextRange.GetTextRunsIterator();
	
	//Check if there is stuff to iterate through
	if ( currTextRunsIterator.IsEmpty() ) { return NULL; }
	
	//Loop through the runs
	while ( currTextRunsIterator.IsNotDone() ) {
		
		//Get the color of the current run
		AIColor currAIColor = GetAIColorFromATETextRange( currTextRunsIterator.Item() );
		
		//We only want things that are in registration
		if ( !colorIsEqual(currAIColor, registrationColor , TRUE ) ) { currTextRunsIterator.Next(); continue; }
*/		
		//Get the contents of the current run to the buffer itemText
		char itemText[150];
		currTextRange.GetContents(itemText, 150);
//		(currTextRunsIterator.Item()).GetContents(itemText, 50);
		
		//Store the charFeatures
//		ATE::ICharFeatures currCharFeatures = (currTextRunsIterator.Item()).GetUniqueCharFeatures();
		ATE::ICharFeatures currCharFeatures = currTextRange.GetUniqueCharFeatures();
		
		//Strip out everything but the plate number
		std::string pn = CreatePlateNumberStringFromCharArray(itemText);
//		if (pn.empty()) { currTextRunsIterator.Next(); continue; }
		
		//Store pn in our nodes Plate Number field
		p->PlateNumberStr( pn );
		
		//Create a new Point Text
		//Set the anchor point based on the bounds of the other frame
		AIRealPoint anchor;
		AIRealRect bounds;
		sAIArt->GetArtBounds(currArtHandle, &bounds);
		AIRealRect cropArea = p->GetCropAreaRect();								
		AIRealPoint a = { (cropArea.right-((cropArea.right - cropArea.left)*.13)), bounds.bottom};
		AIRealPoint b = { (cropArea.right-((cropArea.right - cropArea.left)*.13)), bounds.top};
		sAIRealMath->AIRealPointInterpolate(&a, &b, .7 , &anchor);
		
		//Create the object
		sAITextFrame->NewPointText(kPlaceAbove, currArtHandle, kHorizontalTextOrientation, anchor, &hPlateNumber );
		
		//Get the range for text object we just made
		ATE::TextRangeRef plateNumberRangeRef;
		sAITextFrame->GetATETextRange(hPlateNumber, &plateNumberRangeRef);
		ATE::ITextRange plateNumberRange(plateNumberRangeRef);
		
		AddTextToRangeWithFeatures(p->PlateNumberStr(), currCharFeatures, currArtHandle, &plateNumberRange);
		
		//Set the justification to right for our new text
		ATE::IParaFeatures paraFeatures = plateNumberRange.GetUniqueLocalParaFeatures();
		paraFeatures.SetJustification(ATE::kRightJustify);
		plateNumberRange.ReplaceOrAddLocalParaFeatures(paraFeatures);
		
		//Remove the old text frame if Date and Plate Number have been created
		if ( hDate && hPlateNumber ) { 
			sAIArt->DisposeArt(currArtHandle);
			currArtHandle = NULL;
		}
		
//		currTextRunsIterator.Next();
//	}
	
	return hPlateNumber; //Should still be NULL if the plate number wasn't found
}

AIArtHandle Node::FindDate(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere) {
	AIArtHandle hPlateNumber = GetArtHandleFromUIDRef(this->p->PlateNumberUIDRef());
	AIArtHandle hDate = GetArtHandleFromUIDRef(this->p->DateUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//We're only looking for text frames with the default name
	ASBoolean isDefault = FALSE; ai::UnicodeString artName;
	sAIArt->GetArtName(currArtHandle, artName, &isDefault);
	if (type != kTextFrameArt || !isDefault) { return NULL; }
	
	//If this art is closer to some other node, we don't even need to worry about it
	if ( FindClosestNode(currArtHandle, lookWhere) != this ) { return NULL; }
	
	//We need to make sure the object is closer to the bottom right corner than to the upper left corner
	if ( FindClosestCorner(currArtHandle, this ) != LOWER_RIGHT ) { return NULL; }
	
	//Make sure the font size is less than 10
	if ( GetFontSizeFromAITextFrame(currArtHandle) > 10 ) { return NULL; }
	
	//Create the runs iterator
	ATE::TextRangeRef currATETextRangeRef;
	sAITextFrame->GetATETextRange(currArtHandle, &currATETextRangeRef);
	ATE::ITextRange currTextRange(currATETextRangeRef);
	ATE::ITextRunsIterator currTextRunsIterator = currTextRange.GetTextRunsIterator();
	
	//Check if there is stuff to iterate through
	if ( currTextRunsIterator.IsEmpty() ) { return NULL; }
	
	//Loop through the runs
	while ( currTextRunsIterator.IsNotDone() ) {
		
		//Get the color of the current run
		AIColor currAIColor = GetAIColorFromATETextRange( currTextRunsIterator.Item() );
		
		//We only want things that are in registration
		if ( !colorIsEqual(currAIColor, registrationColor , TRUE ) ) { currTextRunsIterator.Next(); continue; }
		
		//Get the contents of the current run to the buffer itemText
		char itemText[50];
		(currTextRunsIterator.Item()).GetContents(itemText, 50);
		
		//Store the charFeatures
		ATE::ICharFeatures currCharFeatures = (currTextRunsIterator.Item()).GetUniqueCharFeatures();
		
		//Strip out everything but the date
		std::string dt = CreateDateStringFromCharArray(itemText);
		if (dt.empty()) { currTextRunsIterator.Next(); continue; }
		
		//Store dt in our nodes Date field
		p->DateStr( dt );
		
		
		//Create a new Point Text
		//Set the anchor point based on the bounds of the other frame
		AIRealPoint anchor;
		AIRealRect bounds;
		sAIArt->GetArtBounds(currArtHandle, &bounds);
		AIRealRect cropArea = p->GetCropAreaRect();								
		AIRealPoint a = { (cropArea.right-((cropArea.right - cropArea.left)*.01)), bounds.bottom};
		AIRealPoint b = { (cropArea.right-((cropArea.right - cropArea.left)*.01)), bounds.top};
		
		sAIRealMath->AIRealPointInterpolate(&a, &b, .7 , &anchor);
		
		//Create the object
		sAITextFrame->NewPointText(kPlaceAbove, currArtHandle, kHorizontalTextOrientation, anchor, &hDate );
		
		//Get the range for text object we just made
		ATE::TextRangeRef dateRangeRef;
		sAITextFrame->GetATETextRange(hDate, &dateRangeRef);
		ATE::ITextRange dateRange(dateRangeRef);
		
		AddTextToRangeWithFeatures(p->DateStr(), currCharFeatures, currArtHandle, &dateRange);
		
		//Set the justification to right for our new text
		ATE::IParaFeatures paraFeatures = dateRange.GetUniqueLocalParaFeatures();
		paraFeatures.SetJustification(ATE::kRightJustify);
		dateRange.ReplaceOrAddLocalParaFeatures(paraFeatures);
	
		//Remove the old text frame if Date and Plate Number have been created
		if ( hDate && hPlateNumber ) { 
			sAIArt->DisposeArt(currArtHandle);
			currArtHandle = NULL;
		}
		
		currTextRunsIterator.Next();
	}
	
	return hDate; //Should still be NULL if the date wasn't found
}

//Proof
AIArtHandle Node::FindProofTag(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//We're only looking for text frames with the default name
	ASBoolean isDefault = FALSE; ai::UnicodeString artName;
	sAIArt->GetArtName(currArtHandle, artName, &isDefault);
	if (type == kTextFrameArt && isDefault) {
		
		//If this art is closer to some other node, we don't even need to worry about it
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			
			string textFrameText = GetStdStringFromAITextFrame(currArtHandle);
			
			//Convert it to lowercase
			for(int i=0; i<textFrameText.size(); i++) { textFrameText[i] = tolower(textFrameText[i]); }				
			size_t pos = string::npos;
			pos = textFrameText.find("proof");
			if ( pos != string::npos ) {
				return currArtHandle;
			}
		}
	}

	return NULL;
}

//Keyline info
AIArtHandle Node::FindKeylineRegBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path, or a group of paths
	if (type == kPathArt || type == kGroupArt) {
		//If it belongs to this node
		//We also need to make sure its actually contained inside the node
		Node* closestNode = FindClosestNode(currArtHandle, lookWhere);
		AIRealRect artBounds; sAIArt->GetArtBounds(currArtHandle, &artBounds);
		AIRealRect cropBounds = p->GetCropAreaRect();
		ASBoolean isInside = sAIRealMath->AIRealRectInAIRealRect(&artBounds, &cropBounds);
		ASBoolean isEqual = FALSE;
		if (sAIRealMath->EqualWithinTol(cropBounds.left, artBounds.left, 1) && 
			sAIRealMath->EqualWithinTol(cropBounds.top, artBounds.top, 1) &&
			sAIRealMath->EqualWithinTol(cropBounds.right, artBounds.right, 1) &&
			sAIRealMath->EqualWithinTol(cropBounds.bottom, artBounds.bottom, 1)) { isEqual = TRUE;	}
		if ( (closestNode == this) && (isInside || isEqual)) {
			//If it is a group
			if (type == kGroupArt) {
				//We have to make sure its not the keyline layer-group
				ASBoolean isLayer = FALSE;
				sAIArt->IsArtLayerGroup(currArtHandle, &isLayer);
				if (!isLayer) {
					//We have to find the safe emboss box and move it out of this group
					//Go into the group and check each object
					AIArtHandle embossArtHandle = NULL; AIArtHandle nextHandle = NULL;
					sAIArt->GetArtFirstChild(currArtHandle, &embossArtHandle);
					while (embossArtHandle) {
						AIRealRect nodeRect = p->GetCropAreaRect();
						AIRealRect artRect; sAIArt->GetArtBounds(embossArtHandle, &artRect);
						//Check to make sure it doesn't share any edges with the crop box
						if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 1) && 
							!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 1)) {
							//We found the emboss box, so we move it to the top of the layer and return the group that
							//now only contains the reg boxes
							MoveArtToTopOfLayer(embossArtHandle);							
							return currArtHandle;
						}
						sAIArt->GetArtSibling(embossArtHandle, &nextHandle);
						embossArtHandle = nextHandle;
					}
				}
			//if it is a path
			} else {
				//We need to make sure this isn't a safe emboss box, which is inside of the crop box,
				//in the case of an envelope, the box is just very close to the crop box
				
				AIRealRect nodeRect = p->GetCropAreaRect();	
					
				//If it shares left, right, and top, we got the top of a foldover
				//If it shares left, right, and bottom, we got the bottom of a foldover
				//We need to take either one of these and stick it inside a group, then find the other one and stick it in the group
				//Then return the group
				AIArtHandle top = NULL;
				AIArtHandle bottom = NULL;
				AIArtHandle it = currArtHandle;
				
				while ( (!top || !bottom) && it ) {
					AIRealRect artRect; sAIArt->GetArtBounds(it, &artRect);
					
					//Check if it shares ANY edges with the crop box and keep track which edges it shares
					ASBoolean shareLeft, shareTop, shareRight, shareBottom;
					shareLeft = shareTop = shareRight = shareBottom = FALSE;
					
					if (sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 5) ) { shareLeft = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 5) ) { shareTop = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 5) ) { shareRight = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 5) ) { shareBottom = TRUE; }
					
					//We need to count the path segments to make sure this isn't the envelope flap
					short segCount;
					sAIPath->GetPathSegmentCount(it, &segCount);
					if (segCount != 5 && segCount != 6 && segCount != 9) {
						//If it shares all edges, we found it
						if (shareLeft && shareTop && shareRight && shareBottom) { return it; }
						
						
						//If it only shares some of the edges, we gotta get two for the foldover
						if (shareLeft && shareRight) {
							if ( shareTop) {
								top = it;
								sAIArt->GetArtSibling(top, &it);
							} else if ( shareBottom ) {
								bottom = it;
								sAIArt->GetArtSibling(bottom, &it);
							} else {
								AIArtHandle temp = it;
								sAIArt->GetArtSibling(temp, &it );
							}
						} else {
							AIArtHandle temp = it;
							sAIArt->GetArtSibling(temp, &it );
						}
					} else {
						AIArtHandle temp = it;
						sAIArt->GetArtSibling(temp, &it );
					}
					
				}
				
				if (top && bottom) {
					//Create a new group and put top and bottom in it, then return the group
					AIArtHandle theGroup = NULL;
					AILayerHandle layer = NULL; sAIArt->GetLayerOfArt(currArtHandle, &layer);
					AIArtHandle layerArt = NULL; sAIArt->GetFirstArtOfLayer(layer, &layerArt);
					sAIArt->NewArt(kGroupArt, kPlaceInsideOnTop, layerArt, &theGroup);
					
					if (theGroup) {
						PutArtInGroup(top, theGroup);
						PutArtInGroup(bottom, theGroup);
					} else {
						return NULL;
					}
					
					
					return theGroup;
				}
			}
		}
	}
	return NULL;
}

AIArtHandle Node::FindKeylineEnvFlap(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//If it belongs to this node
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			//We need to count the path segments
			short segCount;
			sAIPath->GetPathSegmentCount(currArtHandle, &segCount);
			if (segCount == 5 || segCount == 6 || segCount == 9) {
				return currArtHandle;
			}
		}
	}
	return NULL;
}

AIArtHandle Node::FindKeylineSafeEmbossBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path, or a group of paths
	if (type == kPathArt || type == kGroupArt) {
		//If it belongs to this node
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			//If it is a group
			if (type == kGroupArt) {
				//We have to make sure its not the keyline layer-group
				ASBoolean isLayer = FALSE;
				sAIArt->IsArtLayerGroup(currArtHandle, &isLayer);
				if (!isLayer) {
					//We have to find the safe emboss box and move it out of this group
					//Go into the group and check each object
					AIArtHandle embossArtHandle = NULL; AIArtHandle nextHandle = NULL;
					sAIArt->GetArtFirstChild(currArtHandle, &embossArtHandle);
					while (embossArtHandle) {
						AIRealRect nodeRect = p->GetCropAreaRect();
						AIRealRect artRect; sAIArt->GetArtBounds(embossArtHandle, &artRect);
						//Check to make sure it doesn't share any edges with the crop box
						if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 1) && 
							!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 1)) {
							
							//We need to count the path segments and make sure there are 4
							short segCount;
							sAIPath->GetPathSegmentCount(currArtHandle, &segCount);
							if (segCount == 4) {
								//We found the emboss box, so we move it to the top of the layer and return it
								MoveArtToTopOfLayer(embossArtHandle);
								return embossArtHandle;
							}
						}
						sAIArt->GetArtSibling(embossArtHandle, &nextHandle);
						embossArtHandle = nextHandle;
					}
				}
				//if it is a path
			} else {
				//We need to make sure this is a safe emboss box, which is inside of the crop box
				//It also shouldn't be real close the the crop box so we set the tolerance to 5
				AIRealRect nodeRect = p->GetCropAreaRect();
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				//Check to make sure it doesn't share any edges with the crop box
				if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 5) && 
					!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 5) &&
					!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 5) &&
					!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 5)) {
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}

AIArtHandle Node::FindKeylineFace(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	AIArtHandle hKeyRegBox = GetArtHandleFromUIDRef(this->p->KeylineRegBoxUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is the text box keyline info in it, we have to find out if its closer to this plate, or some other one
	if (type == kTextFrameArt) {
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			
			//Check if the art is actually inside of the RegBox
			AIRealRect regBoxBounds, artBounds;
			sAIArt->GetArtBounds(hKeyRegBox, &regBoxBounds);
			sAIArt->GetArtBounds(currArtHandle, &artBounds);
			if (sAIRealMath->AIRealRectInAIRealRect(&artBounds, &regBoxBounds) ) {
				
				//We need to store the handle for this one, then check if there's any other face text on this node
				//If we find more than one, we need to put them in a group and return the group
				AIArtHandle it = currArtHandle;
				AIArtHandle top = NULL;
				AIArtHandle bottom = NULL;
				
				while ( (!top || !bottom) && it ) {
					//We gotta check each one to see if its a textFrame
					//The only text frames in keyline layer should be faces
					//There should be only two
					sAIArt->GetArtType(it, &type);
					if (type == kTextFrameArt) {
						if ( FindClosestNode(it, lookWhere) == this ) {
							if ( !top ) {
								top = it;
								sAIArt->GetArtSibling(top, &it);
							} else if ( !bottom ) {
								bottom = it;
								sAIArt->GetArtSibling(bottom, &it);
							}
						} else {
							AIArtHandle temp = it;
							sAIArt->GetArtSibling(temp, &it );
						}
					} else {
						AIArtHandle temp = it;
						sAIArt->GetArtSibling(temp, &it );
					}
				}
				
				//If there is a top and bottom, create a new group and put top and bottom in it, then return the group
				if ( top && bottom ) {
					AIArtHandle theGroup = NULL;
					AILayerHandle layer; sAIArt->GetLayerOfArt(currArtHandle, &layer);
					AIArtHandle layerArt; sAIArt->GetFirstArtOfLayer(layer, &layerArt);
					sAIArt->NewArt(kGroupArt, kPlaceInsideOnTop, layerArt, &theGroup);
					
					if (theGroup) {
						PutArtInGroup(top, theGroup);
						PutArtInGroup(bottom, theGroup);
					} else {
						return NULL;
					}
					
					return theGroup;
				}
				//Otherwise, there was only a top, we'll just return that one
				return top;
			}
		}
	}
	return NULL;
}

//Registration info
AIArtHandle Node::FindRegBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path, or a group of paths
	if (type == kPathArt || type == kGroupArt) {
		//If it belongs to this node
		//We also need to make sure its actually contained inside the node
		Node* closestNode = FindClosestNode(currArtHandle, lookWhere);
		AIRealRect artBounds; sAIArt->GetArtBounds(currArtHandle, &artBounds);
		AIRealRect cropBounds = p->GetCropAreaRect();
		ASBoolean isInside = sAIRealMath->AIRealRectInAIRealRect(&artBounds, &cropBounds);
		ASBoolean isEqual = FALSE;
		if (sAIRealMath->EqualWithinTol(cropBounds.left, artBounds.left, 1) && 
			sAIRealMath->EqualWithinTol(cropBounds.top, artBounds.top, 1) &&
			sAIRealMath->EqualWithinTol(cropBounds.right, artBounds.right, 1) &&
			sAIRealMath->EqualWithinTol(cropBounds.bottom, artBounds.bottom, 1)) { isEqual = TRUE;	}
		if ( (closestNode == this) && (isInside || isEqual)) {
			//If it is a group
			if (type == kGroupArt) {
				//We have to make sure its not the registration layer-group
				ASBoolean isLayer = FALSE;
				sAIArt->IsArtLayerGroup(currArtHandle, &isLayer);
				if (!isLayer) {
					//We have to find the safe emboss box and move it out of this group
					//Go into the group and check each object
					AIArtHandle embossArtHandle = NULL; AIArtHandle nextHandle = NULL;
					sAIArt->GetArtFirstChild(currArtHandle, &embossArtHandle);
					while (embossArtHandle) {
						AIRealRect nodeRect = p->GetCropAreaRect();
						AIRealRect artRect; sAIArt->GetArtBounds(embossArtHandle, &artRect);
						//Check to make sure it doesn't share any edges with the crop box
						if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 1) && 
							!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 1)) {
							//We found the emboss box, so we move it to the top of the layer and return the group that
							//now only contains the reg boxes
							MoveArtToTopOfLayer(embossArtHandle);
							return currArtHandle;
						}
						sAIArt->GetArtSibling(embossArtHandle, &nextHandle);
						embossArtHandle = nextHandle;
					}
				}
			//if it is a path
			} else {
				//We need to make sure this isn't a safe emboss box, which is inside of the crop box,
				//in the case of an envelope, the box is just very close to the crop box
				
				AIRealRect nodeRect = p->GetCropAreaRect();	
					
				//If it shares left, right, and top, we got the top of a foldover
				//If it shares left, right, and bottom, we got the bottom of a foldover
				//We need to take either one of these and stick it inside a group, then find the other one and stick it in the group
				//Then return the group
				AIArtHandle top = NULL;
				AIArtHandle bottom = NULL;
				AIArtHandle it = currArtHandle;
				
				while ( (!top || !bottom) && it ) {
					AIRealRect artRect; sAIArt->GetArtBounds(it, &artRect);
					
					//Check if it shares ANY edges with the crop box and keep track which edges it shares
					ASBoolean shareLeft, shareTop, shareRight, shareBottom;
					shareLeft = shareTop = shareRight = shareBottom = FALSE;
					
					if (sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 5) ) { shareLeft = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 5) ) { shareTop = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 5) ) { shareRight = TRUE; }
					if (sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 5) ) { shareBottom = TRUE; }

//TODO: If we have too many segments here, make sure that the endpoints are not on top of each other
					
					//We need to count the path segments to make sure this isn't the envelope flap
					short segCount;
					sAIPath->GetPathSegmentCount(it, &segCount);
					if (segCount != 5 && segCount != 6 && segCount != 9) {
						
						//If it shares all edges, we found it
						if (shareLeft && shareTop && shareRight && shareBottom) { return it; }
						
						//If it only shares some of the edges, we gotta get two for the foldover
						if (shareLeft && shareRight) {
							if ( shareTop) {
								top = it;
								sAIArt->GetArtSibling(top, &it);
							} else if ( shareBottom ) {
								bottom = it;
								sAIArt->GetArtSibling(bottom, &it);
							} else {
								AIArtHandle temp = it;
								sAIArt->GetArtSibling(temp, &it );
							}
						} else {
							AIArtHandle temp = it;
							sAIArt->GetArtSibling(temp, &it );
						}
					} else {
						AIArtHandle temp = it;
						sAIArt->GetArtSibling(temp, &it );
					}
					
				}
				
				
				//Create a new group and put top and bottom in it, then return the group
				if (top && bottom) {
					//Create a new group and put top and bottom in it, then return the group
					AIArtHandle theGroup;
					AILayerHandle layer; sAIArt->GetLayerOfArt(currArtHandle, &layer);
					AIArtHandle layerArt; sAIArt->GetFirstArtOfLayer(layer, &layerArt);
					sAIArt->NewArt(kGroupArt, kPlaceInsideOnTop, layerArt, &theGroup);
					
					PutArtInGroup(top, theGroup);
					PutArtInGroup(bottom, theGroup);
					
					return theGroup;
				}
			}
		}
	}
	return NULL;
}

AIArtHandle Node::FindRegEnvFlap(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//If it belongs to this node
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			//We need to count the path segments
			short segCount;
			sAIPath->GetPathSegmentCount(currArtHandle, &segCount);
			if (segCount == 5 || segCount == 6 || segCount == 9) {
				return currArtHandle;
			}
		}
	}
	return NULL;
}

AIArtHandle Node::FindRegSafeEmbossBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path, or a group of paths
	if (type == kPathArt || type == kGroupArt) {
		//If it belongs to this node
		if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
			//If it is a group
			if (type == kGroupArt) {
				//We have to make sure its not the keyline layer-group
				ASBoolean isLayer = FALSE;
				sAIArt->IsArtLayerGroup(currArtHandle, &isLayer);
				if (!isLayer) {
					//We have to find the safe emboss box and move it out of this group
					//Go into the group and check each object
					AIArtHandle embossArtHandle = NULL; AIArtHandle nextHandle = NULL;
					sAIArt->GetArtFirstChild(currArtHandle, &embossArtHandle);
					while (embossArtHandle) {
						AIRealRect nodeRect = p->GetCropAreaRect();
						AIRealRect artRect; sAIArt->GetArtBounds(embossArtHandle, &artRect);
						//Check to make sure it doesn't share any edges with the crop box
						if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 1) && 
							!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 1) &&
							!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 1)) {
							
							//We need to count the path segments and make sure there are 4
							short segCount;
							sAIPath->GetPathSegmentCount(currArtHandle, &segCount);
							if (segCount == 4) {
								//We found the emboss box, so we move it to the top of the layer and return it
								MoveArtToTopOfLayer(embossArtHandle);
								return embossArtHandle;
							}
						}
						sAIArt->GetArtSibling(embossArtHandle, &nextHandle);
						embossArtHandle = nextHandle;
					}
				}
			//if it is a path
			} else {
				//We need to make sure this isn't a safe emboss box, which is inside of the crop box
				//Set the tolerance to 5 to make sure its not even close, evelopes have a box that is close to the edge
				AIRealRect nodeRect = p->GetCropAreaRect();
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				//Check to make sure it doesn't share any edges with the crop box
				if (!sAIRealMath->EqualWithinTol(nodeRect.left, artRect.left, 5) && 
					!sAIRealMath->EqualWithinTol(nodeRect.top, artRect.top, 5) &&
					!sAIRealMath->EqualWithinTol(nodeRect.right, artRect.right, 5) &&
					!sAIRealMath->EqualWithinTol(nodeRect.bottom, artRect.bottom, 5)) {
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}

//Bleed
AIArtHandle Node::FindBleedBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
		
	//If this is the bleed box path
	if (type == kPathArt) {
		//Make sure its a guide or if its in registration, we'll make it a guide
		//Get the color of the object
		AIColorUsedHow usage;
		sAIPathStyle->ObjectUsesAIColor(currArtHandle, &registrationColor, FALSE, FALSE, &usage );
		if (usage == 1) {
			sAIPath->SetPathGuide(currArtHandle, TRUE);
		}
		
		ASBoolean isGuide = FALSE;
		sAIPath->GetPathGuide(currArtHandle, &isGuide);
		if (isGuide) {
			//If it belongs to this node
			//We also need to make sure the node is actually contained inside this
			Node* closestNode = FindClosestNode(currArtHandle, lookWhere);
			
			//We have to temporarily make it not a guide so we can get the bounds
			sAIPath->SetPathGuide(currArtHandle, FALSE);			
			AIRealRect artBounds; sAIArt->GetArtBounds(currArtHandle, &artBounds);
			//Now change it back
			sAIPath->SetPathGuide(currArtHandle, TRUE);
			AIRealRect cropBounds = p->GetCropAreaRect();
			ASBoolean isInside = sAIRealMath->AIRealRectInAIRealRect(&cropBounds, &artBounds);
			if ( (closestNode == this) && isInside) {
				
				//We need to make sure the object is at the top level of its layer
				MoveArtToTopOfLayer(currArtHandle);
				
				return currArtHandle;
			}
		}
	}
	
	return NULL;
}

//Gripper
AIArtHandle Node::FindGripperTop(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	AIArtHandle hRegBox = GetArtHandleFromUIDRef(this->p->RegBoxUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//Make sure its in registration
		AIColorUsedHow usage;
		sAIPathStyle->ObjectUsesAIColor(currArtHandle, &registrationColor, FALSE, FALSE, &usage );
		if (usage == 2) {
			//Check whether its closest to this node
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
				//Check whether its top
				AIRealRect regBoxRect; sAIArt->GetArtBounds(hRegBox, &regBoxRect);
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				if (sAIRealMath->EqualWithinTol(regBoxRect.left, artRect.left, 1) && 
					sAIRealMath->EqualWithinTol(regBoxRect.top, artRect.top, 1) &&
					sAIRealMath->EqualWithinTol(regBoxRect.right, artRect.right, 1))
				{
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}
AIArtHandle Node::FindGripperBottom(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	AIArtHandle hRegBox = GetArtHandleFromUIDRef(this->p->RegBoxUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//Make sure its in registration
		AIColorUsedHow usage;
		sAIPathStyle->ObjectUsesAIColor(currArtHandle, &registrationColor, FALSE, FALSE, &usage );
		if (usage == 2) {
			//Check whether its closest to this node
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
				//Check whether its top
				AIRealRect regBoxRect; sAIArt->GetArtBounds(hRegBox, &regBoxRect);
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				if (sAIRealMath->EqualWithinTol(regBoxRect.left, artRect.left, 1) && 
					sAIRealMath->EqualWithinTol(regBoxRect.bottom, artRect.bottom, 1) &&
					sAIRealMath->EqualWithinTol(regBoxRect.right, artRect.right, 1))
				{
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}
AIArtHandle Node::FindGripperLeft(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	AIArtHandle hRegBox = GetArtHandleFromUIDRef(this->p->RegBoxUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//Make sure its in registration
		AIColorUsedHow usage;
		sAIPathStyle->ObjectUsesAIColor(currArtHandle, &registrationColor, FALSE, FALSE, &usage );
		if (usage == 2) {
			//Check whether its closest to this node
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
				//Check whether its left
				AIRealRect regBoxRect; sAIArt->GetArtBounds(hRegBox, &regBoxRect);
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				if (sAIRealMath->EqualWithinTol(regBoxRect.left, artRect.left, 1) && 
					sAIRealMath->EqualWithinTol(regBoxRect.bottom, artRect.bottom, 1) &&
					sAIRealMath->EqualWithinTol(regBoxRect.top, artRect.top, 1))
				{
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}
AIArtHandle Node::FindGripperRight(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere) {
	AIArtHandle hRegBox = GetArtHandleFromUIDRef(this->p->RegBoxUIDRef());
	short type = 0;
	
	sAIArt->GetArtType(currArtHandle, &type);
	
	//If this is a path
	if (type == kPathArt) {
		//Make sure its in registration
		AIColorUsedHow usage;
		sAIPathStyle->ObjectUsesAIColor(currArtHandle, &registrationColor, FALSE, FALSE, &usage );
		if (usage == 2) {
			//Check whether its closest to this node
			if ( FindClosestNode(currArtHandle, lookWhere) == this ) {
				//Check whether its right
				AIRealRect regBoxRect; sAIArt->GetArtBounds(hRegBox, &regBoxRect);
				AIRealRect artRect; sAIArt->GetArtBounds(currArtHandle, &artRect);
				if (sAIRealMath->EqualWithinTol(regBoxRect.right, artRect.right, 1) && 
					sAIRealMath->EqualWithinTol(regBoxRect.bottom, artRect.bottom, 1) &&
					sAIRealMath->EqualWithinTol(regBoxRect.top, artRect.top, 1))
				{
					return currArtHandle;
				}
			}
		}
	}
	return NULL;
}




//Proximity
Node* FindClosestNode(AIArtHandle object, int CORNER) {
	if(CORNER == -1) {return NULL;}
	
	Node* currNode = startNode;
	Node* closestNode = currNode;
	AIReal bestDistance = -1;
	
	do {
		AIRealRect nodeRect = currNode->p->GetCropAreaRect();
		
		
		AIRealRect artRect;
		sAIArt->GetArtTransformBounds(object, NULL, kVisibleBounds, &artRect);

		AIRealPoint a, b;
		switch (CORNER) {
		case UPPER_LEFT:
			a.h = nodeRect.left; a.v = nodeRect.top;
			b.h = artRect.left; b.v = artRect.top;
			break;
		case UPPER_RIGHT:
			a.h = nodeRect.right; a.v = nodeRect.top;
			b.h = artRect.right; b.v = artRect.top;
			break;
		case LOWER_RIGHT:
			a.h = nodeRect.right; a.v = nodeRect.bottom;
			b.h = artRect.right; b.v = artRect.bottom;
			break;
		case LOWER_LEFT:
			a.h = nodeRect.left; a.v = nodeRect.bottom;
			b.h = artRect.left; b.v = artRect.bottom;
			break;
		}
				
		
		AIReal distance = sAIRealMath->AIRealPointLength(&a, &b);
		
		//If this is the first time, set bestDistance, otherwise check if this one is closer
		if (bestDistance == -1 || distance < bestDistance) {
			bestDistance = distance;
			closestNode = currNode;
		}
		
		currNode = currNode->nextNode;
	} while ( currNode );
	
	
	return closestNode;
}


int FindClosestCorner(AIArtHandle object, Node* const node ) {
	AIRealRect artRect, cropRect;
	cropRect = node->p->GetCropAreaRect();
	sAIArt->GetArtBounds(object, &artRect);
	
	AIRealPoint a,b;
	
	//Distance from object to crop area upper left
	a.h = artRect.left;	a.v = artRect.top;
	b.h = cropRect.left; b.v = cropRect.top;
	AIReal distUL = sAIRealMath->AIRealPointLength(&a,&b);
	
	//Distance from object to crop area upper right
	a.h = artRect.right;	a.v = artRect.top;
	b.h = cropRect.right; b.v = cropRect.top;
	AIReal distUR = sAIRealMath->AIRealPointLength(&a,&b);
	
	//Distance from object to crop area lower right
	a.h = artRect.right;	a.v = artRect.bottom;
	b.h = cropRect.right; b.v = cropRect.bottom;
	AIReal distLR = sAIRealMath->AIRealPointLength(&a,&b);
	
	//Distance from object to crop area lower left
	a.h = artRect.left;	a.v = artRect.bottom;
	b.h = cropRect.left; b.v = cropRect.bottom;
	AIReal distLL = sAIRealMath->AIRealPointLength(&a,&b);
	
	
	//If its closer to the upper left
	if (distUL < distUR && distUL < distLR && distUL < distLL) { return UPPER_LEFT; }
	
	//If its closer to the upper left
	if (distUR < distUL && distUR < distLR && distUR < distLL) { return UPPER_RIGHT; }
	
	//If its closer to the upper left
	if (distLR < distUL && distLR < distUR && distLR < distLL) { return LOWER_RIGHT; }
	
	//If its closer to the upper left
	if (distLL < distUL && distLL < distLR && distLL < distUR) { return LOWER_LEFT; }
	
	//If they were equal, return 0
	return 0;	
}


std::string CreatePlateNumberStringFromCharArray(const char* inChars) {
	
	size_t begin, end, length;
	std::string theString(inChars);
	
	//Now we can start stripping white spaces out to get the actual plate number
	begin = theString.find_first_not_of(WHITESPACES);
	
	//If the item is completely whitespace we return an empty string
	if ( begin == string::npos ) { theString.clear(); return theString; }
	
	//Now, we find the next whitespace
	end = theString.find_first_of(WHITESPACES, begin);
	length = end - begin;
	if (length < 0) { theString.clear(); return theString; }
	
	//Now we make the string just what we've found
	theString = theString.substr(begin, length);
	
	//Check to make sure the length is what we expect
	if ( (theString.length() < PLATE_NUMBER_MIN_LENGTH) ||
		 (theString.length() > PLATE_NUMBER_MAX_LENGTH) ) {
		theString.clear(); return theString;
	}
	
	//Return the stripped string
	return theString;
}


std::string CreateDateStringFromCharArray(const char* inChars) {
	
	size_t begin, end, sep;
	std::string theString(inChars);
	
	//Now we can start stripping white spaces out
	begin = theString.find_first_not_of(WHITESPACES);
	
	//If the item is completely whitespace we return an empty string
	if ( begin == string::npos ) { theString.clear(); return theString; }
	
	//Now we can look for either the '/' or '-' characters
	sep = theString.find('/');
	if ( sep == string::npos ) {
		sep = theString.find('-');
		if ( sep == string::npos ) {
			//If we can't find a valid date seperator, we return an empty string
			theString.clear(); return theString;
		}
	}
	
	//So now, we should have found either a / or -
	//We need to find the first symbol before the slash and the last symbol after it
	//   ##/##
	//   ^   ^ these two
	begin = theString.find_last_of(WHITESPACES, sep) + 1; //Add 1 so we have the position of the first char after the last whitespace before sep
	end = theString.find_last_not_of(WHITESPACES);
	
	//Now we make the string just what we've found
	theString = theString.substr(begin, (end-begin+1));
	
	//Check to make sure the length is what we expect, return an empty one if not
	if ( (theString.length() < DATE_MIN_LENGTH) ||
		(theString.length() > DATE_MAX_LENGTH) ) {
		theString.clear(); return theString;
	}		

	//Return the stripped string
	return theString;
}



void FindAllObjects(Node* const startNode, Node* const currNode) {
	try {
		for (int i = 0 ; i < NUMFUNCS ; i++) {
			
			AIUIDRef currUIDRef = (currNode->p->*(get_functions[i]))();
			
			//If it was initialized from the dictionary, we'll check to see if its pointing to valid art still
			if ( !CheckArtHandleFromUIDRef(currUIDRef) ) {
				(currNode->p->*(set_functions[i]))(NULL);
				sAIUIDREF->Release(currUIDRef);
				currUIDRef = NULL;
			} else {
				//Set the art object's name in the layers panel
				AIArtHandle reffedArt = GetArtHandleFromUIDRef(currUIDRef);
				sAIArt->SetArtName(reffedArt, find_functions[i].objectLabel );
			}
			
			//If we didn't already have one, or we found it invalid in the last step, we'll search the document for it now
			if (currUIDRef == NULL){
			
				AIArtHandle foundObject = Find( startNode, currNode, find_functions[i] );
				
				if( foundObject ) {
					
					//Set up the UID in the objects dictionary
					sAIUIDUtils->GetArtUID(foundObject, TRUE /*To create one if there is none*/, &currUIDRef);
					
					//Store the new UIDRef in the plate's class
					(currNode->p->*(set_functions[i]))(currUIDRef);
										
					//Set the art object's name in the layers panel
					sAIArt->SetArtName(foundObject, find_functions[i].objectLabel );
				}
			}
			sAIUIDREF->Release(currUIDRef);			
		}
		
		//Reposition the slug stuff so it doesn't overlap
		currNode->p->RepositionPlateNumberAndDate();
		currNode->p->RepositionColorList();
	}
	catch(CException* e) {
		throw;
	}
}


//Main Find
AIArtHandle Find(Node* const startNode, Node* inNode, FIND_FUNCTIONS const &find) {
	long count = 0;
	AIArtSet artSet = NULL;
	sAIArtSet->NewArtSet(&artSet);
	
	//If this is not the proof tag just use the layer passed in
	if (find.callback != &Node::FindProofTag) {
		count = CreateArtSetFromLayer(find.layerLabel, artSet);
	}
	//If this is the proof tag, we need to add another layer to the artset too
	if (find.callback == &Node::FindProofTag) {
		AIArtSet ArtSet1 = NULL;
		sAIArtSet->NewArtSet(&ArtSet1);
		CreateArtSetFromLayer(find.layerLabel, ArtSet1);
		
		AIArtSet ArtSet2 = NULL;
		sAIArtSet->NewArtSet(&ArtSet2);
		CreateArtSetFromLayer(LAYER_WITH_PROOF_INFO_ALT, ArtSet2);
		
		sAIArtSet->UnionArtSet(ArtSet1, ArtSet2, artSet);
		
		sAIArtSet->DisposeArtSet(&ArtSet1); ArtSet1 = NULL;
		sAIArtSet->DisposeArtSet(&ArtSet2); ArtSet2 = NULL;
	}
	
	AIArtHandle foundArt = NULL;
	AIArtHandle currArtHandle = NULL;
	
	try {
		sAIArtSet->CountArtSet(artSet, &count);
		if(count == 0) {
			throw [CException withCode:ecNoValidArtInLayer];
		}
		//Loop through the art set
		for (int i = 0 ; i < count ; i++) {
			
			sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
			
			
			//Check to make sure this isn't the named one we're looking for
			ai::UnicodeString currArtName;
			ASBoolean isDefault = TRUE;
			
			sAIArt->GetArtName(currArtHandle, currArtName, &isDefault);
			
			if (find.objectLabel == currArtName) {
				if (FindClosestNode(currArtHandle, find.lookWhere) == inNode){
					foundArt = currArtHandle;
					break;
				}
			}
			
			if (!foundArt) {
				foundArt = (inNode->*(find.callback))(startNode, currArtHandle, find.lookWhere);
				if (foundArt) { break; }
			}
		}
		sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
		
		return foundArt;
	}
	catch(CException* e) {
		sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
		throw;
	}
}

void Node::SetupAdditionalVars() {
	//Get the file name
	ai::FilePath currDocPath;
	sAIDocument->GetDocumentFileSpecification(currDocPath);
	std::string fileNameStr = (currDocPath.GetFileNameNoExt()).as_UTF8();
	
	//Set up the mpplate variable based on the plate number
	if ( p->PlateNumberStr().find("MP") != string::npos ) {
		p->MPPlate(TRUE);
		if ( fileNameStr.find("MP") != string::npos ) {
			p->Prints(TRUE);
		} else {
			p->Prints(FALSE);
		}
	} else {
		p->MPPlate(FALSE);
		if ( fileNameStr.find("MP") != string::npos ) {
			p->Prints(FALSE);
		} else {
			p->Prints(TRUE);
		}
	}

	//Set the face variable based on the text, check whether it agrees with the platenumber
	FACE tface = UN;
	FACE bface = UN;
	AIArtHandle currArtHandle = GetArtHandleFromUIDRef(p->KeylineFaceUIDRef());

	try {
		short type = 0;
		sAIArt->GetArtType(currArtHandle, &type);
		if (type == kGroupArt) {
			AIArtHandle top = NULL;
			AIArtHandle bottom = NULL;
			sAIArt->GetArtFirstChild(currArtHandle, &top);
			sAIArt->GetArtSibling(top, &bottom);
			if(top) {
				string contents = GetStdStringFromAITextFrame(top);
				if ( contents.find("FRONT") != string::npos ||
					contents.find("OUTSIDE") != string::npos ) {
					tface = FRONT;
				} else if ( contents.find("BACK") != string::npos ||
						   contents.find("INSIDE") != string::npos ) {
					tface = BACK;
				} 
			}
			if(bottom) {
				string contents = GetStdStringFromAITextFrame(bottom);
				if ( contents.find("FRONT") != string::npos ||
					contents.find("OUTSIDE") != string::npos ) {
					bface = FRONT;
				} else if ( contents.find("BACK") != string::npos ||
						   contents.find("INSIDE") != string::npos ) {
					bface = BACK;
				} 			
			}
			if ( tface == bface ) {
				p->Face(tface);
			} else {
				throw [CException withCode:ecFaceMismatch];
			}
		} else {
			if(currArtHandle) {
				string contents = GetStdStringFromAITextFrame(currArtHandle);
				if ( contents.find("FRONT") != string::npos ||
					contents.find("OUTSIDE") != string::npos ) {
					p->Face(FRONT);
				} else if ( contents.find("BACK") != string::npos ||
						   contents.find("INSIDE") != string::npos ) {
					p->Face(BACK);
				}
			}
		}
		
	}
	catch(CException* e) {
		throw;
	}
}