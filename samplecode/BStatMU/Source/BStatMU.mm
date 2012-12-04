
// Tell Xcode to export the following symbols
//#if defined(__GNUC__)
//#pragma GCC visibility push(default)
//#endif

#include "ColorFuncs.h"
#include "ArtTree.h"
#include "ATEFuncs.h"
#include "DictFuncs.h"
#include "CropAreaFuncs.h"
#include "error.h"

#import "Node.h"
#import "Plate.h"
#import "CException.h"

#include "common.h"
#include "stdio.h"
#include "BStatMU.h"
#include "IText.h"

AIColor registrationColor;

extern AIDictionaryRef dictMain;
extern Node* startNode;

//Declare a global pointer to the Find Functions array
const FIND_FUNCTIONS* find_functions = NULL;

bool BStatMU() {
	//Set the undo/redo text
	sAIUndo->SetUndoText("Undo BStat Master Update", "Redo BStat Master Update");
	
	try {
		//Check that we're not using the crop tool
		AIToolType toolNumber = NULL;
		AIToolHandle toolHandle = NULL;
		AIToolHandle cropToolHandle = NULL;
		sAITool->GetToolNumberFromName(kCropTool, &toolNumber);
		sAITool->GetToolHandleFromNumber(toolNumber, &cropToolHandle);
		sAITool->GetSelectedTool(&toolHandle);
		if ( toolHandle == cropToolHandle ) { throw [CException withCode:ecCropToolSelected]; }
		
		//Check for an open document
		long count = 0;	sAIDocumentList->Count(&count); if (!count) { throw [CException withCode:ecNoDocOpen]; }
		
	
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
		
		
		SetUpNodes();
		
		//Now we need to cycle through each crop area and set the objects that belong to it
		//We do this after the Plates have all been constructed so that we know how many there are and also so 
		//we know where each one is. In general, we'll use proximity to determine what belongs to what.
		Node* currNode = startNode;
		do {
			//Do all the initialization
			
			FindAllObjects(startNode, currNode);
			currNode->SetupAdditionalVars();
			
			currNode->p->PlateDictionaryStore();
			
			currNode = currNode->nextNode;
		} while (currNode);
		
		
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
//		sAIUndo->UndoChanges();
		sAIDictionary->Release(dictMain);
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
					if (artName != REGISTRATION_BOX_LABEL) {
						throw [CException withCode:ecKeyObjectNotFound];
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
						throw [CException withCode:ecKeyObjectNotFound];
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
						throw [CException withCode:ecKeyObjectNotFound];
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
						throw [CException withCode:ecKeyObjectNotFound];
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