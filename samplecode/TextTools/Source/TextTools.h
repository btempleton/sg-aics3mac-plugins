//========================================================================================
//  
//  $File: TextTools.h $
//
//  $Revision: #4 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/

#include "common.h"

#define ttObjectArt				1
#define ttTextArt				2
#define ttUnknownArt			4

#define MICR_FONT_NAME			"MICR"
#define BARCODE_FONT_NAME		"IDAutomationC39XS"
#define LASER_BARCODE_OFFSET	25

#define MICR_LINE_LABEL ai::UnicodeString("__MICR_LINE__")
#define MICR_BARCODE_LABEL ai::UnicodeString("__MICR_BARCODE__")


bool ConvertToPointType();

bool Align(ATE::ParagraphJustification alignStyle);
//This is the main Align function. It checks what type of art is selected in the document and calls the appropriate align funcs
//for each different type of art

void AlignText(AIArtSet* artSet, ATE::ParagraphJustification alignStyle);
void AlignText(AIArtHandle currArt, ATE::ParagraphJustification alignStyle);
void AlignPointType(AIArtHandle currArt, ATE::ParagraphJustification alignStyle);
//Changes the alignment of text objects without changing their location.
//The artset version should only be called with an artset that only contains text art.
//If a key object is selected, aligns the text objects to the key object.
//If there is no key object selected, it simply adjusts the paragraph justification.

void AlignObject(AIArtSet* artSet, ATE::ParagraphJustification alignStyle);
//Main loop for aligning objects
//The bounds of each root object are determined, then passed to:
void AlignObject(AIArtHandle root, AIArtHandle currArtHandle, AIRealRect selBounds, AIArtSet* artSet, ATE::ParagraphJustification alignStyle);
//Changes the alignment of art objects.
//All children of the root object are moved
//The bounds of the selected parts of the root object must be supplied. These can be adjusted for various effects on alignment.
//If a key object is selected, aligns all art objects to the key object.
//If no key object is selected, aligns all art objects to the page.

short GetTypesFromArtSet(AIArtSet* artSet);

void RemoveChildrenFromArtSet(AIArtHandle root, AIArtHandle currArtHandle, AIArtSet* artSet);

bool CreateMICRBarcode();
ai::UnicodeString CreateBarcodeStringFromMICRString(ai::UnicodeString micrString);
void FindBarcodeAnchorPoint(AIRealPoint* anchor);