/*
 *  ColorFuncs.cpp
 *  FixBlack
 *
 *  Created by Comp Mac 8a on 9/4/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
 
#include "ColorFuncs.h"
#include "ATEFuncs.h"
#include "IText.h"
#include "common.h"

bool colorIsEqual ( AIColor color1 , AIColor color2 , bool ignoreTints ) {
	//GRAY COLOR
	if ((color1.kind == kGrayColor) && (color1.kind == color2.kind)) {
		if (color1.c.g.gray == color2.c.g.gray) { return TRUE; }
	}
	
	//FOUR COLOR
	if ((color1.kind == kFourColor) && (color1.kind == color2.kind)) {
		if ( (color1.c.f.cyan == color2.c.f.cyan) &&
		  (color1.c.f.magenta == color2.c.f.magenta) &&
		  (color1.c.f.yellow == color2.c.f.yellow) &&
		  (color1.c.f.black == color2.c.f.black) ) { return TRUE; }
	}

	//THREE COLOR
	if ((color1.kind == kThreeColor) && (color1.kind == color2.kind)) {
		if ( (color1.c.rgb.red == color2.c.rgb.red) &&
		  (color1.c.rgb.green == color2.c.rgb.green) &&
		  (color1.c.rgb.blue == color2.c.rgb.blue) ) { return TRUE; }
	}
	
	//NONE COLOR
	if ((color1.kind == kNoneColor) && (color1.kind == color2.kind)) { return TRUE; }
	
	//CUSTOM COLOR
	if ((color1.kind == kCustomColor) && (color1.kind == color2.kind)) {
		AICustomColor ccolor1, ccolor2;
		sAICustomColor->GetCustomColor( color1.c.c.color, &ccolor1 );
		sAICustomColor->GetCustomColor( color2.c.c.color, &ccolor2 );
		
		//If ignoreTints is off we don't need to make sure the tint is the same here, just the base color, we'll check the
		//tint later and create new ones. If ignoreTints is on, we'll make sure the tints are the same.
		switch ( ignoreTints ) {
			case FALSE:
				if ( (color1.c.c.tint != color2.c.c.tint) ) { break; }
			case TRUE:
				//CUSTOM FOUR COLOR
				if ( (ccolor1.kind == kCustomFourColor ) && (ccolor1.kind == ccolor2.kind) ) {
					if ( (ccolor1.c.f.cyan == ccolor2.c.f.cyan) &&
					  (ccolor1.c.f.magenta == ccolor2.c.f.magenta) &&
					  (ccolor1.c.f.yellow == ccolor2.c.f.yellow) &&
					  (ccolor1.c.f.black == ccolor2.c.f.black) ) { return TRUE; }				
				}
				//CUSTOM THREE COLOR
				if ( (ccolor1.kind == kCustomThreeColor ) && (ccolor1.kind == ccolor2.kind) ) {
					if ( (ccolor1.c.rgb.red == ccolor2.c.rgb.red) &&
					  (ccolor1.c.rgb.green == ccolor2.c.rgb.green) &&
					  (ccolor1.c.rgb.blue == ccolor2.c.rgb.blue) ) { return TRUE; }				
				}
				//CUSTOM LAB COLOR
				if ( (ccolor1.kind == kCustomLabColor ) && (ccolor1.kind == ccolor2.kind) ) {
					if ( (ccolor1.c.lab.l == ccolor2.c.lab.l) &&
					  (ccolor1.c.lab.a == ccolor2.c.lab.a) &&
					  (ccolor1.c.lab.b == ccolor2.c.lab.b) ) { return TRUE; }				
				}
		}
	}
	return FALSE;
}


bool getBlackFromSwatchList (AISwatchRef &BlackSwatchRef) {
	ai::UnicodeString tempName;
	int numSwatches = 0;
	AIColor ListBlack;
	
/*	// 100% Custom Black
	BlackSwatchRef = sAISwatchList->GetSwatchByNameAndType( NULL , ai::UnicodeString("Black") , kCustomColor );
	if ( BlackSwatchRef ) {
		sAISwatchList->GetAIColor( BlackSwatchRef, &ListBlack );
		if ( ListBlack.c.c.tint == 0 ) {
			AICustomColor CustomBlack;
			sAICustomColor->GetCustomColor(ListBlack.c.c.color, &CustomBlack);
			if (CustomBlack.kind == kCustomFourColor && CustomBlack.c.f.black == 1 ) {
				//Jackpot! This is Black created the way it should be. Send this back no matter what else we found.
				return TRUE;
			}
		}
	}
	
	//If we didn't find it that time, the next best thing is
	// CMYK Black
	BlackSwatchRef = sAISwatchList->GetSwatchByNameAndType( NULL , ai::UnicodeString("Black") , kFourColor );
	if ( BlackSwatchRef ) {
		sAISwatchList->GetAIColor( BlackSwatchRef, &ListBlack );
		if ( ListBlack.c.f.black == 1 ) {
			return TRUE;
		}
	}
	
	// Next ... RGB Black
	BlackSwatchRef = sAISwatchList->GetSwatchByNameAndType( NULL , ai::UnicodeString("Black") , kThreeColor );
	if ( BlackSwatchRef ) {
		sAISwatchList->GetAIColor( BlackSwatchRef, &ListBlack );
		if ( ListBlack.c.rgb.red == 0 && ListBlack.c.rgb.green == 0 && ListBlack.c.rgb.blue == 0 ) {
			return TRUE;
		}
	}
	
	// Next ... Grayscale Black
	BlackSwatchRef = sAISwatchList->GetSwatchByNameAndType( NULL , ai::UnicodeString("Black") , kGrayColor );
	if ( BlackSwatchRef ) {
		sAISwatchList->GetAIColor( BlackSwatchRef, &ListBlack );
		if ( ListBlack.c.g.gray == 1 ) {
			return TRUE;
		}
	}
*/	
	numSwatches = sAISwatchList->CountSwatches( NULL );
		
	for ( int i=0; i<numSwatches; i++) {
		BlackSwatchRef = sAISwatchList->GetNthSwatch( NULL , i );
		sAISwatchList->GetSwatchName( BlackSwatchRef, tempName );
		sAISwatchList->GetAIColor( BlackSwatchRef, &ListBlack );
		
		//If the swatch is named Black
		if (! tempName.compare( ai::UnicodeString("Black") ) ) {
		//and its a 100% custom color
			if ( ListBlack.kind == kCustomColor && ListBlack.c.c.tint == 0 ) {
				return TRUE;
		//or its grayscale 100%
			} else if ( ListBlack.kind == kGrayColor && ListBlack.c.g.gray == 1 ) {
				return TRUE;
		//or its RGB r,g,b = 0%
			} else if ( ListBlack.kind == kThreeColor && ListBlack.c.rgb.red == 0 && ListBlack.c.rgb.green == 0 && ListBlack.c.rgb.blue == 0 ) {
				return TRUE;
		//or its CMYK k=100%
			} else if ( ListBlack.kind == kFourColor && ListBlack.c.f.black == 1) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

bool getWhiteFromSwatchList (AISwatchRef &WhiteSwatchRef) {
	ai::UnicodeString tempName;
	int numSwatches = 0;
	AIColor ListWhite;
	
	numSwatches = sAISwatchList->CountSwatches( NULL );
		
	for ( int i=0; i<numSwatches; i++) {
		WhiteSwatchRef = sAISwatchList->GetNthSwatch( NULL , i );
		sAISwatchList->GetSwatchName( WhiteSwatchRef, tempName );
		sAISwatchList->GetAIColor( WhiteSwatchRef, &ListWhite );
		
		//If the swatch is named White
		if (! tempName.compare( ai::UnicodeString("White") ) ) {
		//and its a 100% custom color
			if ( ListWhite.kind == kCustomColor && ListWhite.c.c.tint == 0 ) {
				return TRUE;
		//or its grayscale 0%
			} else if ( ListWhite.kind == kGrayColor && ListWhite.c.g.gray == 0 ) {
				return TRUE;
		//or its CMYK k=0%
			} else if ( ListWhite.kind == kFourColor && ListWhite.c.f.black == 0 ) {
				return TRUE;
		//or its RGB r,g,b = 100%
			} else if ( ListWhite.kind == kThreeColor && ListWhite.c.rgb.red == 1 && ListWhite.c.rgb.green == 1 && ListWhite.c.rgb.blue == 1 ) {
				return TRUE;
			}
		}
	}
	return FALSE;
}


void nameAllColors(AIColor *color, void* userData, AIErr *result, AIBoolean *altered) {
		
	if ( sAISwatchList->GetSwatchByColor( NULL , color ) )		return;
	else {
		AISwatchRef newSwatch = sAISwatchList->InsertNthSwatch( NULL , -1 );
		sAISwatchList->SetAIColor(newSwatch, color);
	}
	return;
}

void removeUnusedColors() {
	int numSwatches = sAISwatchList->CountSwatches(NULL);
	
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	
	AIArtSpec allSpecs[] = { { kPathArt , 0 , 0 },
							  { kCompoundPathArt , 0 , 0 },
							  { kPlacedArt , 0 , 0 },
							  { kRasterArt , 0 , 0 },
							  { kPluginArt , 0 , 0 },
							  { kMeshArt , 0 , 0 },
							  { kTextFrameArt , 0 , 0 },
							  { kSymbolArt , 0 , 0 },
							};
	sAIArtSet->MatchingArtSet( allSpecs , 8, artSet );
	
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	bool used = FALSE;
	
	//Loop through all the swatches in the list
	for(int i=0; i<numSwatches; i++) {
		AISwatchRef currSwatch = sAISwatchList->GetNthSwatch(NULL, i);
		AIColor currColor; AICustomColor currCustomColor;
		used = FALSE;
		
		sAISwatchList->GetAIColor(currSwatch, &currColor);
		
		ai::UnicodeString currSwatchName;
		sAISwatchList->GetSwatchName(currSwatch, currSwatchName);
		
		if (currColor.kind == kCustomColor) {
			sAICustomColor->GetCustomColor(currColor.c.c.color, &currCustomColor);
		}
		
		//Don't remove these swatches whether they're used or not
		if( !currSwatchName.compare((ai::UnicodeString)"[None]") ||             //compare returns 0 if the two strings are equal
			!currSwatchName.compare((ai::UnicodeString)"[Registration]") ||
			(!currSwatchName.compare((ai::UnicodeString)"Black") && currCustomColor.c.f.black ==  1 && currColor.c.c.tint == 0) ||
			(!currSwatchName.compare((ai::UnicodeString)"White") && currCustomColor.c.f.black == 0  && currColor.c.c.tint == 0) ) { used = TRUE; }
		
		//Loop through each art object to see if it uses the current swatch
		for ( int j=0 ; j< count ; j++ ) {
			if(used) {break;}
			AIArtHandle currArtObj = NULL;
			AIColorUsedHow usage;
			sAIArtSet->IndexArtSet( artSet, j, &currArtObj );
			if (currArtObj) {
				if(currColor.c.c.tint == 0) {
					sAIPathStyle->ObjectUsesAIColor( currArtObj , &currColor , FALSE , TRUE , &usage);
				} else {
					sAIPathStyle->ObjectUsesAIColor( currArtObj , &currColor , TRUE , TRUE , &usage);
				}
				if(usage) { used = TRUE; break; }
			} else {
				return;
			}
		}
		
		if (!used) { sAISwatchList->RemoveNthSwatch(NULL, i); numSwatches--; i--; }
	}
	//DISPOSE OF THE ART SET
	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
	
	//Loop through the swatch groups and remove any empty ones
	count = sAISwatchGroup->CountSwatchGroups(NULL);
	for ( int i=0 ; i<count; i++) {
		AISwatchGroupRef currSwatchGroup = sAISwatchGroup->GetNthSwatchGroup(NULL, i);
		int currCount = sAISwatchGroup->CountSwatches(currSwatchGroup);
		if (!currCount) { sAISwatchGroup->RemoveSwatchGroup(NULL, currSwatchGroup, FALSE); i--; count--; }
	}

}


AISwatchRef checkSwatchListForColor( AIColor matchColor , AIReal tolerance ) {
	AISwatchRef currSwatch;
	AIColor currColor;
	int numSwatches = sAISwatchList->CountSwatches(NULL);
	
	//Loop through the swatches to see if the swatch is already there
	for (int i = 0 ; i < numSwatches ; i++ ) {
		currSwatch = sAISwatchList->GetNthSwatch(NULL, i);
		if (currSwatch) {
			sAISwatchList->GetAIColor(currSwatch, &currColor);
			AIBoolean TintsCloseEnough = sAIRealMath->EqualWithinTol(currColor.c.c.tint, matchColor.c.c.tint, tolerance);
			AIBoolean ColorsSame = colorIsEqual(currColor,matchColor,TRUE);
			if (currColor.kind == kCustomColor && ColorsSame && TintsCloseEnough ) {
				return currSwatch;
			}
		}
	}
	return 0;
}


void AdjustOverprint(AIArtHandle currArtObj, AIColor color, AIBoolean ignoreTints, AIBoolean overprint, int replaceIn, AIBoolean *altered) {
	
	AIPathStyle currPathStyle;
	short type = 0; sAIArt->GetArtType(currArtObj, &type);
	*altered = FALSE;
	
	if (type != kTextFrameArt) {
		sAIPathStyle->GetPathStyle(currArtObj, &currPathStyle);
		
		if (type == kPathArt) {
			//Check if its part of a compound path and skip if it is
			long attr = 0;
			sAIArt->GetArtUserAttr(currArtObj, kArtPartOfCompound, &attr);
			if (attr & kArtPartOfCompound) {
				return;
			}
		}
		//STROKES
		if (replaceIn == 0 || replaceIn == 2) {
			if (currPathStyle.strokePaint) {
				if ( colorIsEqual (currPathStyle.stroke.color, color , ignoreTints ) ) {
					currPathStyle.stroke.overprint = overprint;
					*altered = TRUE;
				}
			} 
		}
		//FILLS
		if (replaceIn == 1 || replaceIn == 2) {
			if (currPathStyle.fillPaint) {
				if ( colorIsEqual (currPathStyle.fill.color, color , ignoreTints ) ) {
					currPathStyle.fill.overprint = overprint;
					*altered = TRUE;
				}
			} 
		}
		
		if (*altered) {
			sAIPathStyle->SetPathStyle(currArtObj, &currPathStyle);
		}		
	} else {
		ATE::TextRangeRef currRangeRef = NULL;
		sAITextFrame->GetATETextRange(currArtObj, &currRangeRef);
		ATE::ITextRange currRange(currRangeRef);
		
		ATE::ITextRunsIterator iter = currRange.GetTextRunsIterator();
		bool isAssigned = FALSE;
		AIColor textColor;
		
		while ( ! iter.IsDone() ) {
			ATE::ICharFeatures currRunCharFeatures = iter.Item().GetUniqueCharFeatures();
			
			
			//STROKES
			if (replaceIn == 0 || replaceIn == 2) {
				ATE::IApplicationPaint strokePaint = currRunCharFeatures.GetStrokeColor(&isAssigned);
				if (isAssigned) {
					sAIATEPaint->GetAIColor(strokePaint.GetRef(), &textColor);
					if ( colorIsEqual (textColor, color , ignoreTints ) ) {
						currRunCharFeatures.SetStrokeOverPrint(overprint);
						iter.Item().SetLocalCharFeatures(currRunCharFeatures);
						*altered = TRUE;
					}
				}
			}
			//FILLS
			if (replaceIn == 1 || replaceIn == 2) {
				ATE::IApplicationPaint fillPaint = currRunCharFeatures.GetFillColor(&isAssigned);
				if (isAssigned) {
					sAIATEPaint->GetAIColor(fillPaint.GetRef(), &textColor);
					if ( colorIsEqual (textColor, color , ignoreTints ) ) {
						currRunCharFeatures.SetFillOverPrint(overprint);
						iter.Item().SetLocalCharFeatures(currRunCharFeatures);
						*altered = TRUE;
						
					}
				}
			}
			
			iter.Next();
		}
	}
}


void ChangeColor(AIColor *targetColor, AIColor colorToCopy)
{
	targetColor->kind = colorToCopy.kind;
	targetColor->c.c.tint = colorToCopy.c.c.tint;
	targetColor->c.c.color = colorToCopy.c.c.color;
}