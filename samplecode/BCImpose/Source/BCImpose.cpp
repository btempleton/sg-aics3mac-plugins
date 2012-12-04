
// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

#include "ColorFuncs.h"
#include "ArtTree.h"
#include "ATEFuncs.h"

#include "common.h"
#include "stdio.h"
#include "BCImpose.h"
#include "IText.h"

#define MAX_LENGTH 250

Node* startNode = NULL;

bool BCImpose() {
	
	//CREATE THE ART SET
	AIArtSet artSet;
	AIRealRect bounds;
	AIRealMatrix colorNamePosition;
	sAIArtSet->NewArtSet(&artSet);
	AIArtHandle colorNames = NULL, plateNumbers = NULL; //The handles to text boxes for list of color names and plate numbers
	
	
	//FILL THE ART SET with all placed art objects
	AIArtSpec artSpecs[] = { { kPlacedArt , 0 , 0 } };
	sAIArtSet->MatchingArtSet(artSpecs , 1 , artSet );
	
	//Error if there aren't any placed objects
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	if(count == 0) { sADMBasic->MessageAlert("No valid Placed Art was found."); sAIArtSet->DisposeArtSet(&artSet); return FALSE; }
	
	for ( int i=0 ; i < count ; i++ ) {
		AIArtHandle currArtObj, placedArtGroup, child;
		short type;
		std::string artName;
		ai::UnicodeString tempName;
		sAIArtSet->IndexArtSet( artSet, i, &currArtObj );
		
		sAIArt->GetArtType(currArtObj, &type);
		if (type == kPlacedArt) {
			AILayerHandle currLayer;
			AIArtHandle convertedPDF;
			
						
			sAIPlaced->GetPlacedChild(currArtObj, &placedArtGroup );
			sAIArt->GetArtFirstChild(placedArtGroup, &child);
			
			AIFOConversionInfoCollector aifoCollector = { NULL , NULL };  // Callback Proc , void* data
			AIFOConversionOptions aifoOptions = { kAIFOConversionDefault , aifoCollector , 0 , 0 , NULL };
			sAIFOConversion->ConvertToNative( child , &aifoOptions , kPlaceAboveAll , currArtObj );
			
			sAILayer->GetFirstLayer( &currLayer );
			sAIArt->GetFirstArtOfLayer( currLayer , &convertedPDF );
			sAIArt->GetArtFirstChild( convertedPDF , &convertedPDF ); //Now convertedPDF contains the new group we created from the placed PDF
			
			colorNames = GetArtObjectByName(ai::UnicodeString("__color_names__"));
			plateNumbers = GetArtObjectByName(ai::UnicodeString("__plate_numbers__"));
			
			if (! CreateColorNameAndPlateNumberLists( convertedPDF , colorNames , plateNumbers ) ) { 
				sAIArt->DisposeArt(convertedPDF);
				sAIArtSet->DisposeArtSet(&artSet);
				return FALSE;
			}
						
			//Delete the copy of the placed art
			sAIArt->DisposeArt(convertedPDF);
		} 
	}
	
	
	AIArtHandle alignObject = GetArtObjectByName(ai::UnicodeString("__bc_alignment__"));
	if(alignObject) { 
		//Move the colornames text box down below the alignment box
		sAIArt->GetArtBounds(alignObject, &bounds);
		
		AIReal offset = bounds.bottom;
		sAIArt->GetArtBounds(colorNames, &bounds);
		offset -= bounds.top;
		
		sAIRealMath->AIRealMatrixSetIdentity( &colorNamePosition );
		sAIRealMath->AIRealMatrixSetTranslate( &colorNamePosition, 0, offset); 
		sAITransformArt->TransformArt(colorNames, &colorNamePosition, 0, kTransformObjects);
		
	} else {
		sADMBasic->MessageAlert("The Alignment Object was not found.");
	}
	
	
	//DISPOSE OF THE ART SET
	sAIArtSet->DisposeArtSet(&artSet);
	
	
	return TRUE;
}



bool CreateColorNameAndPlateNumberLists( AIArtHandle searchArt , AIArtHandle &colorNames , AIArtHandle &plateNumbers ) {
	AIArtHandle **matches, alignObject;
	long numMatches;
	AIReal textLength = 0;
	AIColorUsedHow usage;
	AIColor targetColor;
	AICustomColorHandle registrationColor;
	TextFrameRef ATEcolorNamesFrameRef = NULL, ATEplateNumbersFrameRef = NULL;
	AIRealRect bounds;
	AIArtSet alignmentBoxSet; sAIArtSet->NewArtSet(&alignmentBoxSet);
	AIRealMatrix colorNamePosition, plateNumberPosition;
	
	//Store "Registration" in targetColor
	sAICustomColor->GetCurrentRegistrationColor(&registrationColor);
	targetColor.kind = kCustomColor;
	targetColor.c.c.tint = 0;
	targetColor.c.c.color = registrationColor;
	
	//Get the alignment box and store its position
	alignObject = GetArtObjectByName(ai::UnicodeString("__bc_alignment__"));
	if(alignObject) { 
		sAIArt->GetArtBounds(alignObject, &bounds);
	} else {
		sADMBasic->MessageAlert("The Alignment Object was not found."); return FALSE;
	}
	
	//Check if colorNames has been created yet and create it if not
	AIRealPoint anchor = {0,0};
	if (!colorNames) {
		sAITextFrame->NewPointText(kPlaceAboveAll, NULL, kHorizontalTextOrientation, anchor, &colorNames);	
		sAIArt->SetArtName(colorNames, ai::UnicodeString("__color_names__"));
		
		//Rotate the text
		sAIRealMath->AIRealMatrixSetIdentity( &colorNamePosition );
		sAIRealMath->AIRealMatrixConcatRotate( &colorNamePosition, kAIRealPi2);
		sAIRealMath->AIRealMatrixConcatTranslate( &colorNamePosition, (bounds.left+((bounds.right-bounds.left)/2)+1), bounds.bottom); 
		sAITransformArt->TransformArt(colorNames, &colorNamePosition, 0, kTransformObjects);
	}
	
	//Check if plateNumbers has been created yet and create it if not
	if (!plateNumbers) {
		sAITextFrame->NewPointText(kPlaceAboveAll, NULL, kHorizontalTextOrientation, anchor, &plateNumbers);	
		sAIArt->SetArtName(plateNumbers, ai::UnicodeString("__plate_numbers__"));
		
		//Rotate the text
		sAIRealMath->AIRealMatrixSetIdentity( &plateNumberPosition );
		sAIRealMath->AIRealMatrixConcatRotate( &plateNumberPosition, kAIRealPi2);
		sAIRealMath->AIRealMatrixConcatTranslate( &plateNumberPosition, (bounds.left+((bounds.right-bounds.left)/2)+1), bounds.top); 
		sAITransformArt->TransformArt(plateNumbers, &plateNumberPosition, 0, kTransformObjects);
	}

	//Set up the ATE variables for the color names box and the plate numbers box
	sAITextFrame->GetATETextFrame(colorNames , &ATEcolorNamesFrameRef );
	ATE::ITextFrame ATEcolorNamesFrame(ATEcolorNamesFrameRef);
	ATE::ITextRange ATEcolorNamesRange = ATEcolorNamesFrame.GetTextRange();
		
	sAITextFrame->GetATETextFrame(plateNumbers , &ATEplateNumbersFrameRef );
	ATE::ITextFrame ATEplateNumbersFrame(ATEplateNumbersFrameRef);
	ATE::ITextRange ATEplateNumbersRange = ATEplateNumbersFrame.GetTextRange();
	

	//Get all the text frame art from the passed art object
	AIMatchingArtSpec specs = { kTextFrameArt , 0 , 0 };
	sAIMatchingArt->GetMatchingArtFromArt( searchArt , &specs , 1 , &matches , &numMatches );
	
	for ( int i=0; i < numMatches ; i++ ) {
		//Check the textFrame arts for registration color, anything that isn't in registration should be the color names
		sAIPathStyle->ObjectUsesAIColor( matches[0][i] , &targetColor , FALSE/*matchTint*/ , FALSE/*indirectUsage*/ , &usage  );
		

		if (usage == 0) { //Pull the stuff that's not in Registration -- ie the color names
	//put matches[0][i] in colorNames text frame
			TextFrameRef tempFrameRef;
			sAITextFrame->GetATETextFrame(matches[0][i] , &tempFrameRef );
			ATE::ITextFrame tempFrame(tempFrameRef);
			ATE::ITextRange tempRange = tempFrame.GetTextRange();
			ATE::IStory tempStory = ATEcolorNamesRange.GetStory();
			
			//Get the length of the text box and make a carriage return if its getting too long
			ASInt32 preSize = tempStory.GetSize(); //The size before the text is added
			
	//Check if the color has already been added to the list
			AIColor currColor = GetAIColorFromATETextRange(tempRange);
			sAIPathStyle->ObjectUsesAIColor(colorNames , &currColor , FALSE , FALSE , &usage  );
			
			if (usage == 0) {
				//Add a space to the end of the new color and insert it into the color list
				tempRange.InsertAfter(" ");
				ATEcolorNamesRange.InsertAfter(tempRange);
				
				//Get the size of the new text
				ASInt32 tempRangeSize = tempRange.GetSize();
				
				//Get the length of the text box after the addition
				sAIArt->GetArtBounds(colorNames, &bounds);
				textLength = sAIRealMath->AIRealSqrt((bounds.top-bounds.bottom)*(bounds.top-bounds.bottom));				
				
				//If the text box is too long after the addition, put a carriage return before it
				if( textLength > MAX_LENGTH ) {
					tempRange = tempStory.GetTextRange(preSize, preSize+tempRangeSize);
					tempRange.InsertBefore("\r");
				}
			}
		} else { //The stuff that is in Registration should be just the plate number
			TextFrameRef tempFrameRef;
			sAITextFrame->GetATETextFrame(matches[0][i] , &tempFrameRef );
			ATE::ITextFrame tempFrame(tempFrameRef);
			ATE::ITextRange tempRange = tempFrame.GetTextRange();
			
			//put matches[0][i] in plate numbers text frame
			 
			 
			 //Check whether the plate number is already in the list
			ASUnicode *ASUtargetBuffer, *ASUsearchBuffer;
			
			ASInt32 size = tempRange.GetSize();
			ASUsearchBuffer = new ASUnicode [size+1];
			tempRange.GetContents(ASUsearchBuffer,size);
			ASUsearchBuffer[size] = '\0';
			
			size = ATEplateNumbersRange.GetSize();
			ASUtargetBuffer = new ASUnicode [size];
			ATEplateNumbersRange.GetContents(ASUtargetBuffer,size);
			
			ai::UnicodeString targetBuffer(ASUtargetBuffer);
			ai::UnicodeString searchBuffer(ASUsearchBuffer);
			std::string	stdtargetBuffer = targetBuffer.getInStdString(kAIPlatformCharacterEncoding);
			
			std::string	stdsearchBuffer = searchBuffer.getInStdString(kAIPlatformCharacterEncoding);
			size_t found = stdtargetBuffer.find(stdsearchBuffer);
			
			if (found == stdtargetBuffer.npos) {
				if (size) {	tempRange.InsertBefore("\r"); }
				ATEplateNumbersRange.InsertAfter(tempRange);
			}
			
			delete ASUsearchBuffer;
			delete ASUtargetBuffer;
		}
	}
	
	//Clean up
	sAIMdMemory->MdMemoryDisposeHandle( (void**)matches );
	sAIArtSet->DisposeArtSet(&alignmentBoxSet);
	
	return TRUE;
}



/*********** TREE TRAVERSAL TEST ********/
/*			do {
				do {
					while ( sAIArt->GetArtFirstChild(parent, &child) ) {
						sAIArt->GetArtType(child, &type);
						sAIArt->GetArtName(child, tempName, &isDefault);
						artName = tempName.getInStdString(kAIPlatformCharacterEncoding);
						parent = child;
					}
				} while ( sAIArt->GetArtSibling( child, &parent) ); // parent is really "sibling" here
				sAIArt->GetArtParent(child, &parent);
			} while ( parent != currArtObj );  //if parent = currArtObj we're at the top
*/