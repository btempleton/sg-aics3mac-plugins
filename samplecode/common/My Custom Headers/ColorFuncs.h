/*
 *  ColorFuncs.h
 *  FixBlack
 *
 *  Created by Comp Mac 8a on 9/4/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef COLORFUNCS_H
#define COLORFUNCS_H
 
#include "IllustratorSDK.h"
#include "common.h"

#define MICR_BLACK_MAG_COLOR_NAME "MICR - BLACK MAG"

bool colorIsEqual (AIColor color1, AIColor color2 , bool ignoreTints ); //returns TRUE if they're the same color
bool getBlackFromSwatchList (AISwatchRef &BlackSwatchRef); //Stores the swatchref for black
bool getWhiteFromSwatchList (AISwatchRef &WhiteSwatchRef); //Stores the swatchref for white

AISwatchRef checkSwatchListForColor( AIColor matchColor , AIReal tolerance ); //Checks the swatchlist for a swatch that matches the color passed
																		//Returns the close swatch if found, or NULL if theres none    Tolerance =.01 for close match

void nameAllColors(AIColor *color, void *userData, AIErr *result, AIBoolean *altered);
void removeUnusedColors();

void AdjustOverprint(AIArtHandle currArtObj, AIColor color, AIBoolean ignoreTints, AIBoolean overprint, int replaceIn, AIBoolean *altered);
	// currArtObj - Handle to the art object to adjust
	// color - the color to adjust
	// ignoreTints - TRUE to change all tints of color   FALSE to only change the color selected and no tints
	// overprint - true to turn overprint on, false to turn off
	// replaceIn - 0 = strokes  1 = fills  2 = strokes and fills
	// altered - flag to show if a change was made
	
void ChangeColor(AIColor *targetColor, AIColor colorToCopy);
	
#endif