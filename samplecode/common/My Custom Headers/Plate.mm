/*
 *  Plate.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 12/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import <Cocoa/Cocoa.h>

#import "Plate.h"
#include "ArtTree.h"
#include "ATEFuncs.h"
#include "CropAreaFuncs.h"
#include "DictFuncs.h"
#import "CException.h"

#include "stdlib.h"
#include "time.h"

//Constructor
Plate::Plate(int CAIndex) {
	//Try to find the dictionary for this plate
	//The Key function creates a new key if not found
	this->dictPlate = NULL;
	if (dictMain) {
		char buffer[50];
		sprintf(buffer,"p%d",CAIndex);
		AIDictKey keyPlate = sAIDictionary->Key( buffer );
		AIEntryRef entryPlate = sAIDictionary->Get(dictMain, keyPlate);
		sAIEntry->ToDict(entryPlate, &(this->dictPlate));
		
		if (!(this->dictPlate)) {
			sAIDictionary->CreateDictionary(&(this->dictPlate));
			entryPlate = sAIEntry->FromDict((this->dictPlate));
			sAIDictionary->Set(dictMain, keyPlate, entryPlate);
			sAIEntry->Release(entryPlate);
		}
	}
	
	prints = TRUE;
	face = UN;
	mpplate = FALSE;
	
	//Initialize all these to NULL
	colorList.uidrefArt = NULL;
	colorList.strContents = "";
	
	plateNumber.uidrefArt = NULL;
	plateNumber.strContents = "";
	
	date.uidrefArt = NULL;
	date.strContents = "";
	
	uidrefProofTag = NULL;
	uidrefExtraColorListGroup = NULL;
	uidrefKeylineRegBox = NULL;
	uidrefKeylineEnvFlap = NULL;
	uidrefKeylineSafeEmbossBox = NULL;
	uidrefKeylineFace = NULL;
	uidrefRegBox = NULL;
	uidrefRegEnvFlap = NULL;
	uidrefRegSafeEmbossBox = NULL;
	uidrefBleedBox = NULL;
	uidrefGripperTop = NULL;
	uidrefGripperBottom = NULL;
	uidrefGripperLeft = NULL;
	uidrefGripperRight = NULL;
	
	//Store the crop area index so we know which one it is
	cropAreaIndex = CAIndex;
	
	//Try to load info from the plate dictionary into our new plate struct
	PlateDictionaryRetrieve();
	
	//Store the crop area rect so we can use it to find the other stuff
	sAIRealMath->AIRealRectSet(&cropAreaRect, 0, 0, 0, 0);
	SetCropAreaRect(cropAreaIndex);
}

//Destructor
Plate::~Plate() {
	//Save our plate structure
	//If this fails for some reason, we can't throw anything from the destructor.
	PlateDictionaryStore();
		
	//Release all our UIDRefs
	sAIDictionary->Release(this->dictPlate);
	
	if (colorList.uidrefArt) { sAIUID->Release(colorList.uidrefArt); }
	if (plateNumber.uidrefArt) { sAIUID->Release(plateNumber.uidrefArt); }
	if (date.uidrefArt) { sAIUID->Release(date.uidrefArt); }

	if (uidrefProofTag) { sAIUID->Release(uidrefProofTag); }
	if (uidrefExtraColorListGroup) { sAIUID->Release(uidrefExtraColorListGroup); }
	if (uidrefKeylineRegBox) { sAIUID->Release(uidrefKeylineRegBox); }
	if (uidrefKeylineEnvFlap) { sAIUID->Release(uidrefKeylineEnvFlap); }
	if (uidrefKeylineSafeEmbossBox) { sAIUID->Release(uidrefKeylineSafeEmbossBox); }
	if (uidrefKeylineFace) { sAIUID->Release(uidrefKeylineFace); }
	if (uidrefRegBox) { sAIUID->Release(uidrefRegBox); }
	if (uidrefRegEnvFlap) { sAIUID->Release(uidrefRegEnvFlap); }
	if (uidrefRegSafeEmbossBox) { sAIUID->Release(uidrefRegSafeEmbossBox); }
	if (uidrefBleedBox) { sAIUID->Release(uidrefBleedBox); }
	if (uidrefGripperTop) { sAIUID->Release(uidrefGripperTop); }
	if (uidrefGripperBottom) { sAIUID->Release(uidrefGripperBottom); }
	if (uidrefGripperLeft) { sAIUID->Release(uidrefGripperLeft); }
	if (uidrefGripperRight) { sAIUID->Release(uidrefGripperRight); }

}

void Plate::PlateDictionary(const AIDictionaryRef newDictionaryRef) {
	if (!this->dictPlate) {
		sAIDictionary->AddRef(newDictionaryRef);
		dictPlate = newDictionaryRef;
	} else {
		sAIDictionary->Release(dictPlate);
		dictPlate = newDictionaryRef;
		sAIDictionary->AddRef(newDictionaryRef);
	}
	return;
}
	


ASBoolean Plate::PlateDictionaryRetrieve() {
	
	
	sAIDictionary->GetBooleanEntry(this->dictPlate, GenerateKey("print", cropAreaIndex), (ASBoolean*)&prints);
	sAIDictionary->GetIntegerEntry(this->dictPlate, GenerateKey("face", cropAreaIndex), (ASInt32*)&face);
	sAIDictionary->GetBooleanEntry(this->dictPlate, GenerateKey("mpplate", cropAreaIndex), (ASBoolean*)&mpplate);
	
	AIUIDRef uidRef = NULL;
	GetUIDRefFromPlateDict(COLOR_LIST_LABEL, cropAreaIndex, &uidRef);
	ColorListUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	//Store the text of the color list
	//Check if the art is valid and store the text from it
	if ( CheckArtHandleFromUIDRef(colorList.uidrefArt) ) {
		AIArtHandle reffedArt = GetArtHandleFromUIDRef(colorList.uidrefArt);
		colorList.strContents = GetStdStringFromAITextFrame(reffedArt);
	}
	
	GetUIDRefFromPlateDict(PLATE_NUMBER_LABEL, cropAreaIndex, &uidRef);
	PlateNumberUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	//Store the text of the plate number
	//Check if the art is valid and store the text from it
	if ( CheckArtHandleFromUIDRef(plateNumber.uidrefArt) ) {
		AIArtHandle reffedArt = GetArtHandleFromUIDRef(plateNumber.uidrefArt);
		plateNumber.strContents = GetStdStringFromAITextFrame(reffedArt);
	}
	
	GetUIDRefFromPlateDict(DATE_LABEL, cropAreaIndex, &uidRef);
	DateUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	//Store the text of the date
	//Check if the art is valid and store the text from it
	if ( CheckArtHandleFromUIDRef(date.uidrefArt) ) {
		AIArtHandle reffedArt = GetArtHandleFromUIDRef(date.uidrefArt);
		date.strContents = GetStdStringFromAITextFrame(reffedArt);
	}
	
	GetUIDRefFromPlateDict(PROOF_TAG_LABEL, cropAreaIndex, &uidRef);
	ProofTagUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(EXTRA_COLOR_GROUP_LABEL, cropAreaIndex, &uidRef);
	ExtraColorListUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(KEYLINE_REGISTRATION_LABEL, cropAreaIndex, &uidRef);
	KeylineRegBoxUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(KEYLINE_ENV_FLAP_LABEL, cropAreaIndex, &uidRef);
	KeylineEnvFlapUIDRef( uidRef );
	//sAIUID->Release(uidRef);
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(KEYLINE_SAFE_EMBOSS_LABEL, cropAreaIndex, &uidRef);
	KeylineSafeEmbossBoxUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(KEYLINE_FACE_LABEL, cropAreaIndex, &uidRef);
	KeylineFaceUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(REGISTRATION_BOX_LABEL, cropAreaIndex, &uidRef);
	RegBoxUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(REGISTRATION_ENV_FLAP_LABEL, cropAreaIndex, &uidRef);
	RegEnvFlapUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(REGISTRATION_SAFE_EMBOSS_LABEL, cropAreaIndex, &uidRef);
	RegSafeEmbossBoxUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(BLEED_BOX_LABEL, cropAreaIndex, &uidRef);
	BleedBoxUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(GRIPPER_TOP_LABEL, cropAreaIndex, &uidRef);
	GripperTopUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(GRIPPER_BOTTOM_LABEL, cropAreaIndex, &uidRef);
	GripperBottomUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(GRIPPER_LEFT_LABEL, cropAreaIndex, &uidRef);
	GripperLeftUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;
	
	GetUIDRefFromPlateDict(GRIPPER_RIGHT_LABEL, cropAreaIndex, &uidRef);
	GripperRightUIDRef( uidRef );
	//sAIUID->Release(uidRef); 
	uidRef = NULL;

	return TRUE;
}

ASBoolean Plate::PlateDictionaryStore() {
	
	sAIDictionary->SetBooleanEntry(this->dictPlate, GenerateKey("print", cropAreaIndex), prints);
	sAIDictionary->SetIntegerEntry(this->dictPlate, GenerateKey("face", cropAreaIndex), face);
	sAIDictionary->SetBooleanEntry(this->dictPlate, GenerateKey("mpplate", cropAreaIndex), mpplate);
	
	//Make sure our art handles are valid before we store them
	//COLOR LIST
	if ( !CheckArtHandleFromUIDRef(colorList.uidrefArt) ) {
		ColorListUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(colorList.uidrefArt, COLOR_LIST_LABEL, cropAreaIndex);
	}
	
	//PLATE NUMBER
	if ( !CheckArtHandleFromUIDRef(plateNumber.uidrefArt) ) {
		PlateNumberUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(plateNumber.uidrefArt, PLATE_NUMBER_LABEL, cropAreaIndex);
	}

	//DATE
	if ( !CheckArtHandleFromUIDRef(date.uidrefArt) ) {
		DateUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(date.uidrefArt, DATE_LABEL, cropAreaIndex);
	}

	//PROOF TAG
	if ( !CheckArtHandleFromUIDRef(uidrefProofTag) ) {
		ProofTagUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefProofTag, PROOF_TAG_LABEL, cropAreaIndex);
	}

	//EXTRA COLOR GROUP
	if ( !CheckArtHandleFromUIDRef(uidrefExtraColorListGroup) ) {
		ExtraColorListUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefExtraColorListGroup, EXTRA_COLOR_GROUP_LABEL, cropAreaIndex);
	}

	//KEYLINE REGISTRATION BOX
	if ( !CheckArtHandleFromUIDRef(uidrefKeylineRegBox) ) {
		KeylineRegBoxUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefKeylineRegBox, KEYLINE_REGISTRATION_LABEL, cropAreaIndex);
	}

	//KEYLINE ENVELOPE FLAP
	if ( !CheckArtHandleFromUIDRef(uidrefKeylineEnvFlap) ) {
		KeylineEnvFlapUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefKeylineEnvFlap, KEYLINE_ENV_FLAP_LABEL, cropAreaIndex);
	}

	//KEYLINE SAFE EMBOSS BOX
	if ( !CheckArtHandleFromUIDRef(uidrefKeylineSafeEmbossBox) ) {
		KeylineSafeEmbossBoxUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefKeylineSafeEmbossBox, KEYLINE_SAFE_EMBOSS_LABEL, cropAreaIndex);
	}
	
	//KEYLINE FACE LABEL
	if ( !CheckArtHandleFromUIDRef(uidrefKeylineFace) ) {
		KeylineFaceUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefKeylineFace, KEYLINE_FACE_LABEL, cropAreaIndex);
	}
		
	//REGISTRATION BOX LABEL
	if ( !CheckArtHandleFromUIDRef(uidrefRegBox) ) {
		RegBoxUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefRegBox, REGISTRATION_BOX_LABEL, cropAreaIndex);
	}

	//REGISTRATION ENV FLAP LABEL
	if ( !CheckArtHandleFromUIDRef(uidrefRegEnvFlap) ) {
		RegEnvFlapUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefRegEnvFlap, REGISTRATION_ENV_FLAP_LABEL, cropAreaIndex);
	}

	//REGISTRATION SAFE EMBOSS LABEL
	if ( !CheckArtHandleFromUIDRef(uidrefRegSafeEmbossBox) ) {
		RegSafeEmbossBoxUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefRegSafeEmbossBox, REGISTRATION_SAFE_EMBOSS_LABEL, cropAreaIndex);
	}
		
	//BLEED BOX LABEL
	if ( !CheckArtHandleFromUIDRef(uidrefBleedBox) ) {
		BleedBoxUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefBleedBox, BLEED_BOX_LABEL, cropAreaIndex);
	}
		
	//GRIPPER TOP
	if ( !CheckArtHandleFromUIDRef(uidrefGripperTop) ) {
		GripperTopUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefGripperTop, GRIPPER_TOP_LABEL, cropAreaIndex);
	}
	
	//GRIPPER BOTTOM
	if ( !CheckArtHandleFromUIDRef(uidrefGripperBottom) ) {
		GripperBottomUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefGripperBottom, GRIPPER_BOTTOM_LABEL, cropAreaIndex);
	}
		
	//GRIPPER LEFT
	if ( !CheckArtHandleFromUIDRef(uidrefGripperLeft) ) {
		GripperLeftUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefGripperLeft, GRIPPER_LEFT_LABEL, cropAreaIndex);
	}
	
	//GRIPPER RIGHT
	if ( !CheckArtHandleFromUIDRef(uidrefGripperRight) ) {
		GripperRightUIDRef( NULL );
	} else {
		PutUIDRefInPlateDict(uidrefGripperRight, GRIPPER_RIGHT_LABEL, cropAreaIndex);
	}

	return TRUE;
}


void Plate::SetCropAreaRect(int CAIndex) {
	//If we have crop areas
	if (CAIndex >= 0) {
		ForceCropCoordUpdate();
		
		//Store the crop area rect
		AICropAreaPtr cropArea;
		sAICropArea->Get(CAIndex, &cropArea);
		cropAreaRect = cropArea->m_CropAreaRect;
	}
	
	//If we only have one plate, set the crop area to the page boundary
	else {
		//We get it from the Page Tiling
		AIPageTiling pageTiling;
		sAIDocumentView->GetPageTiling(&pageTiling);

		sAIRealMath->AIRealRectSet(&cropAreaRect, pageTiling.bounds.left, pageTiling.bounds.top, pageTiling.bounds.right, pageTiling.bounds.bottom);
	}
}


void Plate::UpdateDate() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	strftime (buffer,80,"%m/%y",timeinfo);
	
	AIArtHandle hDate = NULL;
	hDate = GetArtHandleFromUIDRef(date.uidrefArt);
	
	
	if (hDate) {
		ATE::TextRangeRef dateRangeRef = NULL;
		sAITextFrame->GetATETextRange(hDate, &dateRangeRef);
		ATE::ITextRange dateRange(dateRangeRef);
		
		dateRange.Remove();
		dateRange.InsertBefore(buffer);
	}
	
	return;
}

void Plate::GetUIDRefFromPlateDict(ai::UnicodeString objectLabel, int CAIndex, AIUIDRef* uidRef) {
	AIEntryRef foundEntry = NULL;
	foundEntry = sAIDictionary->Get(this->dictPlate, GenerateKey(objectLabel, CAIndex) );
	
	if (foundEntry) {
		AIUIDREFRef foundRef = NULL;
		sAIEntry->ToUIDREF(foundEntry, &foundRef);
		
		//uidRef = NULL;
		sAIUIDREF->GetUID(foundRef, uidRef);
		
		sAIUIDREF->Release(foundRef); foundRef = NULL;
	} else {
		sAIEntry->Release(foundEntry); foundEntry = NULL;
	}
}

void Plate::PutUIDRefInPlateDict(AIUIDRef uidRef, ai::UnicodeString objectLabel, int CAIndex) {
	if (uidRef) {
		AIUIDREFRef uidREFRef = NULL;
		sAIUID->NewUIDREF(uidRef, &uidREFRef);
		
		AIEntryRef newEntry = NULL;
		newEntry = sAIEntry->FromUIDREF(uidREFRef);
		sAIDictionary->Set(this->dictPlate, GenerateKey(objectLabel, CAIndex), newEntry);
		
		sAIEntry->Release(newEntry);
		sAIUIDREF->Release(uidREFRef);
	}
}


void Plate::RepositionPlateNumberAndDate() {
	AIArtHandle hPlate = GetArtHandleFromUIDRef(PlateNumberUIDRef());
	AIArtHandle hDate = GetArtHandleFromUIDRef(DateUIDRef());
	
	if (hPlate && hDate){
		//Get the bounds for the two arts
		AIRealRect plateNumberBounds, dateBounds;
		
		sAIArt->GetArtBounds(hPlate, &plateNumberBounds);
		sAIArt->GetArtBounds(hDate, &dateBounds);
		
		//Check if they overlap
		if ( sAIRealMath->AIRealRectOverlap(&plateNumberBounds, &dateBounds) ) {
			//Create and initialize the transformation matrix
			AIRealMatrix matrix; sAIRealMath->AIRealMatrixSetIdentity( &matrix );
			AIReal offset;
			
			offset = (dateBounds.left-((cropAreaRect.right - (dateBounds.right - dateBounds.left))-3))*-1;
			sAIRealMath->AIRealMatrixSetTranslate( &matrix, offset, 0); 
			
			sAITransformArt->TransformArt(hDate, &matrix, 1, kTransformObjects);
			sAIArt->GetArtBounds(hDate, &dateBounds);
			
			sAIRealMath->AIRealMatrixSetIdentity( &matrix );
			offset = (plateNumberBounds.left-((dateBounds.left - (plateNumberBounds.right - plateNumberBounds.left))-5))*-1;
			sAIRealMath->AIRealMatrixSetTranslate( &matrix, offset, 0); 
			
			sAITransformArt->TransformArt(hPlate, &matrix, 1, kTransformObjects);
			
			//Check if they still overlap
			sAIArt->GetArtBounds(hPlate, &plateNumberBounds);
			if ( sAIRealMath->AIRealRectOverlap(&plateNumberBounds, &dateBounds) ) {
				offset = -((plateNumberBounds.right - dateBounds.left) + 10);
				sAIRealMath->AIRealMatrixSetTranslate( &matrix, offset, 0); 
				
				sAITransformArt->TransformArt(hPlate, &matrix, 1, kTransformObjects);
			} 
		}
	}
}

void Plate::RepositionColorList() {
	AIArtHandle hColorList = GetArtHandleFromUIDRef(ColorListUIDRef());
	
	if (hColorList) {
		//Get the bounds of the color list
		AIRealRect startBounds; sAIArt->GetArtBounds(hColorList, &startBounds);
		
		//Determine the maximum width our color list can be
		//Get the handle to the plate number
		AIArtHandle hPlateNumber = GetArtHandleFromUIDRef(this->PlateNumberUIDRef());
		//Get the bounds of the plate number
		AIRealRect pnBounds; sAIArt->GetArtBounds(hPlateNumber, &pnBounds);
		//Get the point that is near the plate number, but won't overlap
		int MAX_WIDTH_POINT = pnBounds.left - 25;
		
		//Check if the color list goes past this point, if not, we're good already
		if (startBounds.right < MAX_WIDTH_POINT) {
			return;
		}
		
		//Set up the ATE variables for the Color List
		TextFrameRef ATEcolorListFrameRef = NULL;
		sAITextFrame->GetATETextFrame(hColorList , &ATEcolorListFrameRef );
		ATE::ITextFrame ATEcolorListFrame(ATEcolorListFrameRef);
		ATE::ITextRange currTextRange = ATEcolorListFrame.GetTextRange();
		
		//Create the iterator
		ATE::ITextRunsIterator currTextRunsIterator = currTextRange.GetTextRunsIterator();
		
		//If there is stuff to iterate through
		if ( !currTextRunsIterator.IsEmpty() ) {
			
			//Loop through the runs and insert returns before any run that makes the text object too wide
			while ( currTextRunsIterator.IsNotDone() ) {
				AIRealRect newBounds; sAIATETextUtil->GetBoundsFromTextRange(currTextRunsIterator.Item().GetRef(), &newBounds);
				//If our range is too far to the right
				if (newBounds.right > MAX_WIDTH_POINT) {
					//If the left is all the way left
					if (newBounds.left == startBounds.left) {
						currTextRunsIterator.Next();
					} else {
						//Insert a return
						currTextRunsIterator.Item().InsertBefore("\r");
						
						//Reset the iterator
						sAITextFrame->GetATETextFrame(hColorList , &ATEcolorListFrameRef );
						ATE::ITextFrame ATEcolorListFrame(ATEcolorListFrameRef);
						ATE::ITextRange currTextRange = ATEcolorListFrame.GetTextRange();
						ATE::ITextRunsIterator currTextRunsIterator = currTextRange.GetTextRunsIterator();
					}								
				} else {
					currTextRunsIterator.Next();
				}
			}
		}		
	}
	return;
}



/*
//STUFF TO DISPLAY WHAT WE'VE GOT FOR TESTING
	ai::UnicodeString name;
	sAISwatchList->GetSwatchName(sAISwatchList->GetSwatchByColor(NULL, &currAIColor), name);
	string message((string)"\"" + (string)itemText + (string)"\"" + (string)"\n" + name.as_Platform());
	sADMBasic->MessageAlert( message.c_str() );
*/