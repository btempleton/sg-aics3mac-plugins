/*
 *  Plate.h
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 12/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef PLATE_H
#define PLATE_H 

#include "common.h"
#include "error.h"

#include "Node.h"
//Forward declarations
class Node;

//Declare a global pointer to the Find Functions array
struct FIND_FUNCTIONS;
extern const FIND_FUNCTIONS* find_functions;

//GLOBAL
extern AIDictionaryRef dictMain;


struct TextArtItem {
	string strContents;
	AIUIDRef uidrefArt;
};

enum FACE { UN, FRONT, BACK };


class Plate {
//Member variables
	AIDictionaryRef dictPlate;

	AIRealRect cropAreaRect;
	int cropAreaIndex;

	bool prints; //Whether this plate should print or not
	
	FACE face; //  (based on plate number or keyline face info)
	bool mpplate; // Whether this plate is an MP plate or not (based on plate number)

	TextArtItem colorList;
	TextArtItem plateNumber;
	TextArtItem date;
	
	AIUIDRef uidrefProofTag;
	AIUIDRef uidrefExtraColorListGroup;
	AIUIDRef uidrefKeylineRegBox;
	AIUIDRef uidrefKeylineEnvFlap;
	AIUIDRef uidrefKeylineSafeEmbossBox;
	AIUIDRef uidrefKeylineFace;
	AIUIDRef uidrefRegBox;
	AIUIDRef uidrefRegEnvFlap;
	AIUIDRef uidrefRegSafeEmbossBox;
	AIUIDRef uidrefBleedBox;
	AIUIDRef uidrefGripperTop;
	AIUIDRef uidrefGripperBottom;
	AIUIDRef uidrefGripperLeft;
	AIUIDRef uidrefGripperRight;
	
public:
//Default constructor
	//CAIndex - The crop area's index position in the list of crop areas
	Plate(const int CAIndex = -1);
//Default destructor
	~Plate();

typedef AIUIDRef (Plate::*GetFunction)() const;
typedef void (Plate::*SetFunction)(const AIUIDRef);	

void UpdateDate();

//Accessor functions
//Plate Dictionary REFERENCE
	AIDictionaryRef PlateDictionary() const { return dictPlate; }										//Get
	void PlateDictionary(const AIDictionaryRef newDictionaryRef);										//Set
		
//Plate Dictionary Store and Retrieval
	ASBoolean PlateDictionaryRetrieve();																//Get
	ASBoolean PlateDictionaryStore();																	//Set

	
//Crop area index
	int CropAreaIndex() const { return cropAreaIndex; }													//Get
	void CropAreaIndex(const int newIndex) { cropAreaIndex = newIndex; }								//Set
	
//Prints
	bool Prints() const { return prints; }																//Get
	void Prints(const bool newPrints) { prints = newPrints; }											//Set

//Face
	bool Face() const { return face; }																	//Get
	void Face(const FACE newFace) { face = newFace; }													//Set

//MP Plate
	bool MPPlate() const { return mpplate; }															//Get
	void MPPlate(const bool newMPPlate) { mpplate = newMPPlate; }										//Set
	

//I've overloaded these, so the same function can be used to get and set the value
//ExtraColorListGroup
	AIUIDRef ExtraColorListUIDRef() const { return uidrefExtraColorListGroup; }					//Get
	void ExtraColorListUIDRef(const AIUIDRef newHandle) {											//Set
		sAIUID->Release(uidrefExtraColorListGroup);
		uidrefExtraColorListGroup = newHandle;
		sAIUID->AddRef(uidrefExtraColorListGroup); }
		
//Proof Tag
	AIUIDRef ProofTagUIDRef() const { return uidrefProofTag; }									//Get
	void ProofTagUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefProofTag); 
														  uidrefProofTag = newHandle; 
														  sAIUID->AddRef(uidrefProofTag);}				//Set

//Keyline Registration Box
	AIUIDRef KeylineRegBoxUIDRef() const { return uidrefKeylineRegBox; }							//Get
	void KeylineRegBoxUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefKeylineRegBox);
															   uidrefKeylineRegBox = newHandle;
															   sAIUID->AddRef(uidrefKeylineRegBox);}			//Set
	
//Keyline Envelope Flap
	AIUIDRef KeylineEnvFlapUIDRef() const { return uidrefKeylineEnvFlap; }						//Get
	void KeylineEnvFlapUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefKeylineEnvFlap);
																uidrefKeylineEnvFlap = newHandle;
																sAIUID->AddRef(uidrefKeylineEnvFlap);}			//Set
	
//Keyline Safe Emboss Box
	AIUIDRef KeylineSafeEmbossBoxUIDRef() const { return uidrefKeylineSafeEmbossBox; }			//Get
	void KeylineSafeEmbossBoxUIDRef(const AIUIDRef newHandle) {									//Set
													  sAIUID->Release(uidrefKeylineSafeEmbossBox);
													  uidrefKeylineSafeEmbossBox = newHandle;
													  sAIUID->AddRef(uidrefKeylineSafeEmbossBox);}

//Keyline Face Indicator
	AIUIDRef KeylineFaceUIDRef() const { return uidrefKeylineFace; }								//Get
	void KeylineFaceUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefKeylineFace);
															 uidrefKeylineFace = newHandle;
															 sAIUID->AddRef(uidrefKeylineFace);}				//Set

//Registration Box
	AIUIDRef RegBoxUIDRef() const { return uidrefRegBox; }										//Get
	void RegBoxUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefRegBox);
														uidrefRegBox = newHandle;
														sAIUID->AddRef(uidrefRegBox);}					//Set

//Registration Envelope Flap
	AIUIDRef RegEnvFlapUIDRef() const { return uidrefRegEnvFlap; }								//Get
	void RegEnvFlapUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefRegEnvFlap);
															uidrefRegEnvFlap = newHandle;
														    sAIUID->AddRef(uidrefRegEnvFlap); }				//Set

//Registration Safe Emboss Box
	AIUIDRef RegSafeEmbossBoxUIDRef() const { return uidrefRegSafeEmbossBox; }					//Get
	void RegSafeEmbossBoxUIDRef(const AIUIDRef newHandle) {										//Set
															sAIUID->Release(uidrefRegSafeEmbossBox);
															uidrefRegSafeEmbossBox = newHandle;
															sAIUID->AddRef(uidrefRegSafeEmbossBox); }

//Bleed guide box
	AIUIDRef BleedBoxUIDRef() const { return uidrefBleedBox; }									//Get
	void BleedBoxUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefBleedBox);
														  uidrefBleedBox = newHandle;
														  sAIUID->AddRef(uidrefBleedBox); }				//Set
	
//Gripper
	AIUIDRef GripperTopUIDRef() const { return uidrefGripperTop; }								//Get
	void GripperTopUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefGripperTop);
															uidrefGripperTop = newHandle;
															sAIUID->AddRef(uidrefGripperTop);}				//Set
	AIUIDRef GripperBottomUIDRef() const { return uidrefGripperBottom; }							//Get
	void GripperBottomUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefGripperBottom);
															   uidrefGripperBottom = newHandle;
															   sAIUID->AddRef(uidrefGripperBottom); }			//Set
	AIUIDRef GripperLeftUIDRef() const { return uidrefGripperLeft; }								//Get
	void GripperLeftUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefGripperLeft);
															 uidrefGripperLeft = newHandle;
															 sAIUID->AddRef(uidrefGripperLeft); }			//Set
	AIUIDRef GripperRightUIDRef() const { return uidrefGripperRight; }							//Get
	void GripperRightUIDRef(const AIUIDRef newHandle) { sAIUID->Release(uidrefGripperRight);
															  uidrefGripperRight = newHandle;
															  sAIUID->AddRef(uidrefGripperRight); }			//Set

// ColorList	
	AIUIDRef ColorListUIDRef() const { return colorList.uidrefArt; }								//Get
	void ColorListUIDRef(const AIUIDRef newHandle) {	sAIUID->Release(colorList.uidrefArt);
															colorList.uidrefArt = newHandle;
															sAIUID->AddRef(colorList.uidrefArt); }				//Set
	string ColorListStr() const { return colorList.strContents; }										//Get
	void ColorListStr(const string newContents) { colorList.strContents = newContents; }				//Set

//Plate Number
	AIUIDRef PlateNumberUIDRef() const { return plateNumber.uidrefArt; }							//Get
	void PlateNumberUIDRef(const AIUIDRef newHandle) { sAIUID->Release(plateNumber.uidrefArt);
															 plateNumber.uidrefArt = newHandle;
															 sAIUID->AddRef(plateNumber.uidrefArt);}			//Set
	string PlateNumberStr() const { return plateNumber.strContents; }									//Get
	void PlateNumberStr(const string newContents) { plateNumber.strContents = newContents; }			//Set

//Date
	AIUIDRef DateUIDRef() const { return date.uidrefArt; }										//Get
	void DateUIDRef(const AIUIDRef newHandle) { sAIUID->Release(date.uidrefArt);
													  date.uidrefArt = newHandle;
													  sAIUID->AddRef(date.uidrefArt); }					//Set
	string DateStr() const { return date.strContents; }													//Get
	void DateStr(const string newContents) { date.strContents = newContents; }							//Set

//CropAreaRect	
	AIRealRect GetCropAreaRect() const { return cropAreaRect; }											//Get
	void SetCropAreaRect(const int CAIndex = -1);														//Set



	
//*******Other Member functions
	//Moves the information so it doesn't overlap
	void RepositionPlateNumberAndDate();
	void RepositionColorList();

	//Retrieves a UIDREFRef as a UIDRef from the plate's dictionary
	void GetUIDRefFromPlateDict(ai::UnicodeString objectLabel, int CAIndex, AIUIDRef* uidRef);
	
	//Puts UIDRef to the plate's dictionary as a UIDREFRef
	void PutUIDRefInPlateDict(AIUIDRef uidRef, ai::UnicodeString objectLabel, int CAIndex);
};


#define NUMFUNCS 17 //s/b 17
Plate::GetFunction const get_functions[] = {
	&Plate::ExtraColorListUIDRef,
	&Plate::ColorListUIDRef,
	&Plate::PlateNumberUIDRef,
	&Plate::DateUIDRef,
	&Plate::ProofTagUIDRef,
	&Plate::KeylineRegBoxUIDRef,
	&Plate::KeylineEnvFlapUIDRef,
	&Plate::KeylineSafeEmbossBoxUIDRef,
	&Plate::KeylineFaceUIDRef,
	&Plate::RegBoxUIDRef,
	&Plate::RegEnvFlapUIDRef,
	&Plate::RegSafeEmbossBoxUIDRef,
	&Plate::BleedBoxUIDRef,
	&Plate::GripperTopUIDRef,
	&Plate::GripperBottomUIDRef,
	&Plate::GripperLeftUIDRef,
	&Plate::GripperRightUIDRef,
};
Plate::SetFunction const set_functions[] = {
	&Plate::ExtraColorListUIDRef,
	&Plate::ColorListUIDRef,
	&Plate::PlateNumberUIDRef,
	&Plate::DateUIDRef,
	&Plate::ProofTagUIDRef,
	&Plate::KeylineRegBoxUIDRef,
	&Plate::KeylineEnvFlapUIDRef,
	&Plate::KeylineSafeEmbossBoxUIDRef,
	&Plate::KeylineFaceUIDRef,
	&Plate::RegBoxUIDRef,
	&Plate::RegEnvFlapUIDRef,
	&Plate::RegSafeEmbossBoxUIDRef,
	&Plate::BleedBoxUIDRef,
	&Plate::GripperTopUIDRef,
	&Plate::GripperBottomUIDRef,
	&Plate::GripperLeftUIDRef,
	&Plate::GripperRightUIDRef,
};

#endif