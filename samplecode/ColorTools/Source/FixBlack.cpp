
// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

#include "ColorFuncs.h"
#include "common.h"
#include "stdio.h"
#include "FixBlack.h"

bool FixBlack() {

	//Set the undo/redo text
	sAIUndo->SetUndoText("Undo Fix Black", "Redo Fix Black");
	
	AIBoolean converted = FALSE;
	sAIDocument->SetDocumentSpotColorMode(NULL, kAILegacySpotColorMode, TRUE, &converted);
	
	//DEFINE OUR CUSTOM BLACK
	AICustomColor customBlack;
	customBlack.kind = kCustomFourColor;
	customBlack.c.f.cyan = 0;
	customBlack.c.f.magenta = 0;
	customBlack.c.f.yellow = 0;
	customBlack.c.f.black = 1;
	customBlack.flag = 0;
	AICustomColorHandle hCurrentBlack;
	sAICustomColor->NewCustomColor(&customBlack , ai::UnicodeString("CustomBlack") , &hCurrentBlack );
	AIColor BLACK;
	BLACK.kind = kCustomColor;
	BLACK.c.c.tint = 0;
	BLACK.c.c.color = NULL;
	BLACK.c.c.color = hCurrentBlack;

	
	AIColor CurrentWhite, tempColor;
	AISwatchRef BlackSwatchRef, WhiteSwatchRef;
	AICustomColor customWhite, tempCustColor;
	AICustomColorHandle hCurrentWhite;
	
	CurrentWhite.kind = kCustomColor;
	CurrentWhite.c.c.tint = 0;
	customWhite.kind = kCustomFourColor;
	customWhite.c.f.cyan = 0;
	customWhite.c.f.magenta = 0;
	customWhite.c.f.yellow = 0;
	customWhite.c.f.black = 0;
	customWhite.flag = 0;
	
	sAICustomColor->NewCustomColor(&customWhite , ai::UnicodeString("CustomWhite") , &hCurrentWhite );
	CurrentWhite.c.c.color = hCurrentWhite;

	
	//If Black swatch doesn't exist, create one	
	if ( !getBlackFromSwatchList ( BlackSwatchRef ) ) {
		BlackSwatchRef = sAISwatchList->InsertNthSwatch(NULL, 2);
	}
	//Check whether Black is already defined correct and only redefine it if it needs to be
	sAISwatchList->GetAIColor( BlackSwatchRef , &tempColor );
	
	if (tempColor.kind == kCustomColor) {
		sAICustomColor->GetCustomColor(tempColor.c.c.color, &tempCustColor);
		tempCustColor.kind = kCustomFourColor;
		tempCustColor.c.f.cyan = 0;
		tempCustColor.c.f.magenta = 0;
		tempCustColor.c.f.yellow = 0;
		tempCustColor.c.f.black = 1;
		tempCustColor.flag = 0;
		sAICustomColor->SetCustomColor(tempColor.c.c.color, &tempCustColor);
		sAISwatchList->SetAIColor( BlackSwatchRef , &tempColor);
	} else {	
		sAISwatchList->SetAIColor( BlackSwatchRef , &BLACK );
		sAISwatchList->SetSwatchName( BlackSwatchRef , ai::UnicodeString("Black") );
	}
	
	//Do the same for White
	if ( !getWhiteFromSwatchList ( WhiteSwatchRef ) ) {
		WhiteSwatchRef = sAISwatchList->InsertNthSwatch(NULL, 2);
	}
	sAISwatchList->GetAIColor( WhiteSwatchRef , &tempColor );
	
	if (tempColor.kind == kCustomColor) {
		sAICustomColor->GetCustomColor(tempColor.c.c.color, &tempCustColor);
		tempCustColor.kind = kCustomFourColor;
		tempCustColor.c.f.cyan = 0;
		tempCustColor.c.f.magenta = 0;
		tempCustColor.c.f.yellow = 0;
		tempCustColor.c.f.black = 0;
		tempCustColor.flag = 0;
		sAICustomColor->SetCustomColor(tempColor.c.c.color, &tempCustColor);
		sAISwatchList->SetAIColor( WhiteSwatchRef , &tempColor);
	} else {	
		sAISwatchList->SetAIColor( WhiteSwatchRef , &CurrentWhite );
		sAISwatchList->SetSwatchName( WhiteSwatchRef , ai::UnicodeString("White") );
	}

	//TODO: Look into spot color mode
	//sAIDocument->SetDocumentSpotColorMode(NULL, kAIStandardSpotColorMode, TRUE, &converted);
	
	// 3. Loop through all the objects, convert each color to the right type of Black
	VisitAIColorFlags controlFlags = kVisitColorsSolidOnly | kVisitGlobalObjectsOnceOnly;
	sAIPathStyle->AdjustObjectAIColors( NULL , convertObjectsToGlobalBlack , NULL , controlFlags , NULL );
	sAIPathStyle->AdjustObjectAIColors( NULL , convertObjectsToGlobalCMYK , NULL , controlFlags , NULL );
	sAIPathStyle->AdjustObjectAIColors( NULL , convertZeroTintToWhite , NULL , controlFlags , NULL );
	
	removeWhiteOverprint();
	
	// 4. Name all the colors
	sAIPathStyle->AdjustObjectAIColors( NULL , nameAllColors , NULL , controlFlags , NULL );
	
	// 5. Remove unused colors
	removeUnusedColors();
	
	
	
	return TRUE;
}


void convertObjectsToGlobalBlack(AIColor *color, void *userData, AIErr *result, AIBoolean *altered) {
	AISwatchRef tempSwatch;
	AIColor tempColor;
	
	
	// If its CMYK black
	if (color->kind == kFourColor) {
		if (color->c.f.cyan == 0 && color->c.f.magenta == 0 && color->c.f.yellow == 0) {
			
			if ( color->c.f.black == 0 ) { //White
				getWhiteFromSwatchList ( tempSwatch );
				sAISwatchList->GetAIColor( tempSwatch , &tempColor );
				*color = tempColor;
				*altered = TRUE; return;
			} else if ( color->c.f.black == 1 ) { //Black
				getBlackFromSwatchList ( tempSwatch );
				sAISwatchList->GetAIColor( tempSwatch , &tempColor );
				//*color = tempColor;
				ChangeColor(color, tempColor);
				*altered = TRUE; return;
			} else { //Tint
				getBlackFromSwatchList ( tempSwatch );
				sAISwatchList->GetAIColor( tempSwatch , &tempColor );
				tempColor.c.c.tint = 1 - color->c.f.black;
				
				//Check swatch list for a close tint
				AISwatchRef tempSwatch = checkSwatchListForColor( tempColor , .01 );
				if ( tempSwatch ) {
					AIColor currColor;
					sAISwatchList->GetAIColor(tempSwatch, &currColor);
					*color = currColor;
					*altered = TRUE; return;
				}
				*color = tempColor;
				*altered = TRUE; return;
			}
		}
	}
	
	// If its K black
	if (color->kind == kGrayColor) {
		if ( color->c.g.gray == 0 ) { //White
			getWhiteFromSwatchList ( tempSwatch );
			sAISwatchList->GetAIColor( tempSwatch , &tempColor );
			*color = tempColor;
			*altered = TRUE; return;
		} else if ( color->c.g.gray == 1 ) { //Black
			getBlackFromSwatchList ( tempSwatch );
			sAISwatchList->GetAIColor( tempSwatch , &tempColor );
			*color = tempColor;
			*altered = TRUE; return;
		} else { //Tint
			getBlackFromSwatchList ( tempSwatch );
			sAISwatchList->GetAIColor( tempSwatch , &tempColor );
			tempColor.c.c.tint = 1 - color->c.g.gray;
			
			//Check swatch list for a close tint
			AISwatchRef tempSwatch = checkSwatchListForColor( tempColor , .01 );
			if ( tempSwatch ) {
				AIColor currColor;
				sAISwatchList->GetAIColor(tempSwatch, &currColor);
				*color = currColor;
				*altered = TRUE; return;
			}
			*color = tempColor;
			*altered = TRUE; return;
		}
	}
	
	// If its RGB black
	if (color->kind == kThreeColor) {
		if ( color->c.rgb.red == 0 && color->c.rgb.green == 0 && color->c.rgb.blue == 0) { //White
			getWhiteFromSwatchList ( tempSwatch );
			sAISwatchList->GetAIColor( tempSwatch , &tempColor );
			*color = tempColor;
			*altered = TRUE; return;
		} else if ( color->c.rgb.red == 1 && color->c.rgb.green == 1 && color->c.rgb.blue == 1 ) { //Black
			getBlackFromSwatchList ( tempSwatch );
			sAISwatchList->GetAIColor( tempSwatch , &tempColor );
			*color = tempColor;
			*altered = TRUE; return;
		} else { //Some other RGB color
		}
	}
	
	
	//CUSTOM COLOR SECTION!!!
	if (color->kind == kCustomColor) {
		
		AICustomColor tColor;	sAICustomColor->GetCustomColor( color->c.c.color , &tColor );
		
		//If the swatch name includes "PANTONE" we're going to adjust the color to the color book definition
		ai::UnicodeString colorName;
		sAICustomColor->GetCustomColorName(color->c.c.color, colorName);
		if (colorName.caseFind(ai::UnicodeString("PANTONE"), 0) != string::npos) {
			//Get the definition from the swatch book and replace the current definition
			//If the name matches one in the book, store the attributes in customColor
			if ( sAISwatchLibrary->FindStandardBookColor(colorName, &tColor) ) {
				//Replace the object's color with the book color
				sAICustomColor->SetCustomColor(color->c.c.color, &tColor);
				*altered = TRUE; return;
			}
		}
		
		//If the color is one of our special colors, adjust to the appropriate definition.
		if (colorName.caseFind(ai::UnicodeString(MICR_BLACK_MAG_COLOR_NAME), 0) != string::npos) {
			AIColor tempColor; AICustomColor tColor; AICustomColorHandle htColor;
			
			tColor.kind = kCustomFourColor;
			tColor.c.f.cyan = 0;
			tColor.c.f.magenta = 0;
			tColor.c.f.yellow = 0;
			tColor.c.f.black = 1;
			tColor.flag = kCustomSpotColor;
			
			sAICustomColor->NewCustomColor( &tColor , ai::UnicodeString(MICR_BLACK_MAG_COLOR_NAME) , &htColor );
						
			tempColor.kind = kCustomColor;
			tempColor.c.c.tint = 0;
			tempColor.c.c.color = htColor;
			
			sAICustomColor->SetCustomColor(color->c.c.color, &tColor);
			*altered = TRUE; return;
		}
		
		
		
		//If its a Custom Four Color Black, switch it to a Black tint
		if (color->c.c.tint == 0 && tColor.c.f.cyan == 0 && tColor.c.f.magenta == 0 && tColor.c.f.yellow == 0) { //Tint
			//Make sure its not k=100 black
			//We have several custom four color blacks for micr ink at 100% black these *should* be the only custom
			//four color blacks we ever see, if it is a custom four color black tint, we'll still convert it to a tint of black
			//we just skip it if its 100%
			if (tColor.c.f.black != 1) {
				getBlackFromSwatchList ( tempSwatch );
				sAISwatchList->GetAIColor( tempSwatch , &tempColor );
				tempColor.c.c.tint = 1 - tColor.c.f.black;
					
				//Check swatch list for a close tint
				AISwatchRef tempSwatch = checkSwatchListForColor( tempColor , .01 );
				if ( tempSwatch ) {
					AIColor currColor;
					sAISwatchList->GetAIColor(tempSwatch, &currColor);
					*color = currColor;
					*altered = TRUE; return;
				}
				*color = tempColor;
				*altered = TRUE; return;					
			}
		}
	
		
		//If its a Custom 3 Color (of any color, not just black), we're going to convert it here to a Custom 4 Color
		if (color->c.c.tint == 0 && tColor.kind == kCustomThreeColor) {
			AIReal rgb[3] = { tColor.c.rgb.red,
							  tColor.c.rgb.green,
							  tColor.c.rgb.blue };
			AIReal cmyk[4];
			AIBoolean inGamut = FALSE;
			sAIColorConversion->ConvertSampleColor(kAIRGBColorSpace, rgb, kAICMYKColorSpace, cmyk, AIColorConvertOptions::kDefault, &inGamut);
			
			//Not sure if we need to check gamut here. Doesn't seem to be anything wrong if its out-of-gamut
			//if (inGamut) {
				tColor.kind = kCustomFourColor;
				tColor.c.f.cyan = cmyk[0];
				tColor.c.f.magenta = cmyk[1];
				tColor.c.f.yellow = cmyk[2];
				tColor.c.f.black = cmyk[3];
				tColor.flag = kCustomSpotColor;
				
				sAICustomColor->SetCustomColor(color->c.c.color, &tColor);
				*altered = TRUE; return;
			//}
		}
		
		
		*altered = FALSE; return;
		
		
		/*//If its a custom CMYK make sure its a spot not a process
		 if (tColor.kind == kCustomFourColor ) {
		 tColor.flag = kCustomSpotColor;
		 sAICustomColor->SetCustomColor( color->c.c.color , &tColor );
		 *altered = TRUE; return;
		 }*/
	}
}


void convertObjectsToGlobalCMYK(AIColor *color, void *userData, AIErr *result, AIBoolean *altered) {
	if (color->kind == kFourColor) {
		if ( color->c.f.cyan != 0 || color->c.f.magenta != 0 || color->c.f.yellow != 0 ) {
			AIColor tempColor; AICustomColor tColor; AICustomColorHandle htColor;
			
			tColor.kind = kCustomFourColor;
			tColor.c.f.cyan = color->c.f.cyan;
			tColor.c.f.magenta = color->c.f.magenta;
			tColor.c.f.yellow = color->c.f.yellow;
			tColor.c.f.black = color->c.f.black;
			tColor.flag = NULL;
			
			ai::UnicodeString CMYKName; char buffer[30];
			CMYKName = ai::UnicodeString("C=");
			sprintf(buffer, "%i", int(tColor.c.f.cyan*100+.5) );
			CMYKName += ai::UnicodeString(buffer);
			CMYKName += ai::UnicodeString(" M=");
			sprintf(buffer, "%i", int(tColor.c.f.magenta*100+.5) );
			CMYKName += ai::UnicodeString(buffer);
			CMYKName += ai::UnicodeString(" Y=");
			sprintf(buffer, "%i", int(tColor.c.f.yellow*100+.5) );
			CMYKName += ai::UnicodeString(buffer);
			CMYKName += ai::UnicodeString(" K=");
			sprintf(buffer, "%i", int(tColor.c.f.black*100+.5) );
			CMYKName += ai::UnicodeString(buffer);
			
			
			AIErr error = sAICustomColor->GetCustomColorByName( CMYKName, &htColor );
			if ( error != kNoErr ) {
				sAICustomColor->NewCustomColor( &tColor , CMYKName , &htColor );
			}						
			
			tempColor.kind = kCustomColor;
			tempColor.c.c.tint = 0;
			tempColor.c.c.color = htColor;
			
			//Check swatch list for a close tint
			AISwatchRef tempSwatch = checkSwatchListForColor( tempColor , .01 );
			if ( tempSwatch ) {
				AIColor currColor;
				sAISwatchList->GetAIColor(tempSwatch, &currColor);
				*color = currColor;
				*altered = TRUE; return;
			}
			
			
			*color = tempColor;
			*altered = TRUE; return;
		}
	}
}



void convertZeroTintToWhite(AIColor *color, void *userData, AIErr *result, AIBoolean *altered) {
	AISwatchRef whiteSwatch;
	AIColor whiteColor;
	
	getWhiteFromSwatchList ( whiteSwatch );
	sAISwatchList->GetAIColor( whiteSwatch , &whiteColor );
	
	//MAKE 0% Tints use White instead
	if ( color->c.c.tint == 1 ) {
		*color = whiteColor;
		*altered = TRUE; return;
	}
	
	//Make any % tint of White use 100% white
	else if(colorIsEqual(*color, whiteColor, TRUE)) {
		*color = whiteColor;
		*altered = TRUE; return;
	} else {
		*altered = FALSE; return;
	}
}


void removeWhiteOverprint() {
	AISwatchRef whiteSwatch;
	AIColor whiteColor;
	AIArtHandle currArtHandle;
	AIBoolean altered = FALSE;
	
	getWhiteFromSwatchList ( whiteSwatch );
	sAISwatchList->GetAIColor( whiteSwatch , &whiteColor );
	
	//CREATE THE ART SET
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	
	//FILL THE ART SET
	AIArtSpec artSpecs[] = { { kPathArt , 0 , 0 },
		{ kCompoundPathArt , 0 , 0 },
		{ kPlacedArt , 0 , 0 },
		{ kRasterArt , 0 , 0 },
		{ kPluginArt , 0 , 0 },
		{ kMeshArt , 0 , 0 },
		{ kTextFrameArt , 0 , 0 },
		{ kSymbolArt , 0 , 0 },
	};
	sAIArtSet->MatchingArtSet(artSpecs , 8 , artSet );
	
	//LOOP THE ART SET
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	for ( int i=0 ; i < count ; i++ ) {
		
		sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
		
		AdjustOverprint(currArtHandle, whiteColor, TRUE, FALSE, 2, &altered);
		
	}
	//DISPOSE THE ART SET
	sAIArtSet->DisposeArtSet(&artSet);
}