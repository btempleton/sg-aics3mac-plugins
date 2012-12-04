/*
 *  adjustColor.cpp
 *  FindReplaceGraphics
 *
 *  Created by Comp Mac 8a on 6/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "FindReplaceGraphics.h"
#include "common.h"

#include "ColorFuncs.h"

extern ADMItemRef ghIncludeTintsCheckBox;

void adjustColor(AIColor *color, void* userData, AIErr *result, AIBoolean *altered) {
	//Cast userData back to the COLORS struct
	COLORS *FromToColor = (COLORS*)userData;
	
	*altered = FALSE;
	
	AISwatchRef fromSwatchRef = sAISwatchList->GetSwatchByColor(NULL, &(FromToColor->FromColor));
	AISwatchRef colorSwatchRef = sAISwatchList->GetSwatchByColor(NULL, color);
	
	
	
	if (color->kind == kGrayColor ||
		color->kind == kFourColor ||
		color->kind == kCustomColor ||
		color->kind == kThreeColor ||
		color->kind == kNoneColor ) {
		
		if ( colorIsEqual( FromToColor->FromColor , *color , ( sADMItem->GetBooleanValue(ghIncludeTintsCheckBox) && sADMItem->IsEnabled(ghIncludeTintsCheckBox) )  ) ){
			if ( FromToColor->FromColor.c.c.tint == color->c.c.tint ) { //IF THE TINTS ARE THE SAME
				if (fromSwatchRef == colorSwatchRef) {
					
					*color = FromToColor->ToColor; *altered = TRUE;			//Change to the To color
				}
			} else {										//IF THE TINTS ARE DIFFERENT
				AIColor tempColor = FromToColor->ToColor; //Make a new temporary color that is the same as the ToColor,
				tempColor.c.c.tint = color->c.c.tint;     //except the tint is the same as the object's
				
				AISwatchRef toColorTintSwatch = checkSwatchListForColor(tempColor, .01);
				
				if ( toColorTintSwatch ) {//If the swatch already exists
					sAISwatchList->GetAIColor(toColorTintSwatch, color);
					*altered = TRUE; //Send back the color of the existing swatch
				}
				else {
					//Insert a new Swatch into the main group
					toColorTintSwatch = sAISwatchList->InsertNthSwatch(NULL, -1);
					if (toColorTintSwatch) {
						//Apply the tempColor to the new swatch
						sAISwatchList->SetAIColor(toColorTintSwatch, &tempColor);
						*color = tempColor; *altered = TRUE; //Send back tempColor (ToColor with the current Objects Tint)
					} else { sADMBasic->MessageAlert("Could not create new tint swatch.");  }
				}
			}
		}
	}
	else if (color->kind == kPattern) {
		AIArtHandle patternArt = NULL;
		sAIPattern->GetPatternArt(color->c.p.pattern, &patternArt);
		
		
		
/*		VisitAIColorFlags controlFlags = kVisitColorsDirectOnly | kVisitGlobalObjectsOnceOnly | kVisitColorsReadOnly;
		AIBoolean flag = FALSE;
		sAIPathStyle->AdjustObjectAIColors( patternArt , adjustColor , FromToColor , controlFlags , &flag );
		
		if (flag) {
			sAIPattern->SetPatternArt(color->c.p.pattern, patternArt);
			*altered = TRUE;
		}
*/	}
}

