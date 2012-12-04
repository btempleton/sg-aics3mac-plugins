/*
 *  Node.h
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 1/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef NODE_H
#define NODE_H


#include "common.h"
#include "string.h"

#include "Plate.h"
class Plate;



#define BSVERSION 
//#define CUSTVERSION

//CONSTANT DEFINITIONS

#ifdef BSVERSION
	#define KEYLINE_LAYER ai::UnicodeString("KEY LINE")
	#define REG_LAYER ai::UnicodeString("Registration Guide for Proof")
	#define SLUG_LAYER ai::UnicodeString("SLUG")
	#define FOREGROUND_LAYER ai::UnicodeString("Foreground")
	#define GUIDE_LAYER ai::UnicodeString("Guides")
	#define BACKGROUND_LAYER ai::UnicodeString("Background")

	#define LAYER_WITH_PLATE_INFO			SLUG_LAYER
	#define LAYER_WITH_PROOF_INFO			FOREGROUND_LAYER
	#define LAYER_WITH_PROOF_INFO_ALT		BACKGROUND_LAYER
	#define LAYER_WITH_EXTRA_COLOR_GROUP	SLUG_LAYER
	#define LAYER_WITH_KEYLINE_INFO			KEYLINE_LAYER
	#define LAYER_WITH_REGISTRATION			REG_LAYER
	#define LAYER_WITH_BLEED				BACKGROUND_LAYER
	#define LAYER_WITH_GRIPPER				BACKGROUND_LAYER
#endif

#define PLATE_NUMBER_LABEL ai::UnicodeString("__plate_number__")
#define DATE_LABEL ai::UnicodeString("__date__")
#define COLOR_LIST_LABEL ai::UnicodeString("__color_list__")
#define EXTRA_COLOR_GROUP_LABEL ai::UnicodeString("__extra_colors__")
#define PROOF_TAG_LABEL ai::UnicodeString("__proof_tag__")
#define KEYLINE_FACE_LABEL ai::UnicodeString("__keyline_face__")
#define KEYLINE_ENV_FLAP_LABEL ai::UnicodeString("__keyline_envelope_flap__")
#define KEYLINE_REGISTRATION_LABEL ai::UnicodeString("__keyline_registration__")
#define KEYLINE_SAFE_EMBOSS_LABEL ai::UnicodeString("__keyline_safe_emboss__")
#define REGISTRATION_BOX_LABEL ai::UnicodeString("__registration_box__")
#define REGISTRATION_ENV_FLAP_LABEL ai::UnicodeString("__registration_envelope_flap__")
#define REGISTRATION_SAFE_EMBOSS_LABEL ai::UnicodeString("__registration_safe_emboss__")
#define BLEED_BOX_LABEL ai::UnicodeString("__bleed_guide__")
#define GRIPPER_TOP_LABEL ai::UnicodeString("__gripper_top__")
#define GRIPPER_BOTTOM_LABEL ai::UnicodeString("__gripper_bottom__")
#define GRIPPER_LEFT_LABEL ai::UnicodeString("__gripper_left__")
#define GRIPPER_RIGHT_LABEL ai::UnicodeString("__gripper_right__")


#define PLATE_NUMBER_TEXT "PLATE NUMBER"
#define PLATE_NUMBER_MIN_LENGTH 6
#define PLATE_NUMBER_MAX_LENGTH 20
#define DATE_TEXT "00/00"
#define DATE_MIN_LENGTH 4
#define DATE_MAX_LENGTH 7

#define UPPER_LEFT	1
#define UPPER_RIGHT	2
#define LOWER_RIGHT	3
#define LOWER_LEFT	4




void SetUpNodes();
void CleanUpNodes();


class Node {
public:
	Plate* p;
	Node* nextNode;
	Node* prevNode;
	
	//Find Object Callback prototype
	typedef AIArtHandle (Node::*FindObjectFunc) ( Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere );
	
//Default constructor
	Node(Node* const prevNode = NULL, const int CAIndex = -1);
	//prevNode - Passed in should be the pointer to the last node that was made, so we can set this node's previous node to it
	//CAIndex - The crop area's index position in the list of crop areas -- passed on to the Plate constructor via the initializer list
//Default destructor
	~Node();

//Member functions
	//Fills in some node specific plate variables
	void SetupAdditionalVars();
		
	//Locates the extra color group
	//If its already been named, it returns that object, otherwise it tries to find it in the document
	AIArtHandle FindExtraColorListGroup(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);

	//Locates the color list text frame
	//Extracts the color list and creates a new point text if no named object is found
	AIArtHandle FindColorList(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere);
	
	//Locates the plate number text frame
	//Extracts the plate number and creates a new point text if no named object is found
	AIArtHandle FindPlateNumber(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere);
	
	//Locates the date text frame
	//Extracts the date and creates a new point text if no named object is found
	AIArtHandle FindDate(Node* const startNode, AIArtHandle currArtHandle, int const lookWhere);
	
	//Locates the proof tag
	//Creates one if none exists
	AIArtHandle FindProofTag(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the keyline registration box
	AIArtHandle FindKeylineRegBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the keyline Envelope Flap
	AIArtHandle FindKeylineEnvFlap(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);

	//Locates the keyline safe emboss box
	AIArtHandle FindKeylineSafeEmbossBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the keyline face indicator
	AIArtHandle FindKeylineFace(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the registration box
	AIArtHandle FindRegBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the Registration Envelope Flap
	AIArtHandle FindRegEnvFlap(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the registration box
	AIArtHandle FindRegSafeEmbossBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the bleed guide path
	AIArtHandle FindBleedBox(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	
	//Locates the gripper areas
	AIArtHandle FindGripperTop(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	AIArtHandle FindGripperBottom(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	AIArtHandle FindGripperLeft(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
	AIArtHandle FindGripperRight(Node* const startNode, AIArtHandle const currArtHandle, int const lookWhere);
};

struct FIND_FUNCTIONS {
	Node::FindObjectFunc callback;
	ai::UnicodeString layerLabel;
	ai::UnicodeString objectLabel;
	int lookWhere;
};

//Find everything
void FindAllObjects(Node* const startNode, Node* const currNode);
//Main Find Function
AIArtHandle Find(Node* const startNode, Node* const inNode, FIND_FUNCTIONS const &find);


Node* FindClosestNode(AIArtHandle object, int CORNER);
// object -- the object we're using
// CORNER -- the corner of the node to check distance to
// Returns a pointer to the closest Node, or NULL if there was an error

int FindClosestCorner(AIArtHandle object, Node* const node );
// object -- the object we're checking
// node -- the Node we're checking
// Returns the Corner Constant defined above or 0 if some were equal distance

std::string CreatePlateNumberStringFromCharArray(const char* inChars);
// inChars -- the array of chars to search for the plate number
// Returns a standard string that contains the plate number

std::string CreateDateStringFromCharArray(const char* inChars);
// inChars -- the array of chars to search for the date
// Returns a standard string that contains the date

#endif