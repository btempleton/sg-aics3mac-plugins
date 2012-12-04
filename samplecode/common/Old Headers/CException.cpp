/*
 *  CException.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 4/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CException.h"

std::string CException::GetDescription() {

	switch (ecode) {
	
//Master Updater errors	
	case ecUpdaterNotRun:
		return "You must run BStat Master Updater before using this tool.";
	case ecPlateNumberNotFound:
		return "Plate Number and/or Registration Box were not found.";

	case ecKeyObjectNotFound:
		return "One or more necessary objects were not found.\nThis plate must be placed on a new master.";
		
	case ecNoDocOpen:
		return "There is no open document.";

	case ecBadOriginPoint:
		return "The document origin must be in the lower left.";
	
	case ecFaceMismatch:
		return "There was an error determining which side is front and which is back.";
			

	case ecCropToolSelected:
		return "The Crop Tool must not be selected.";
		
	case ecNoValidArtInLayer:
		return "An art object could not be located in one of the layers.\nThis plate must be placed on a new master.";

	case ecDictArtObjectNotValid:
		return "An art object needed by this file could not be found.\nThis plate must be placed on a new master.";

	case ecPlateStructArtObjectNotValid:
		return "A necessary art object has been deleted.\nThis plate must be placed on a new master.";


//Incorrectly loaded errors
	case ecPlateNotFound:
		return "The plate could not be located.";
	case ecPlateNotCopied:
		return "The plate could not be copied from the Archive to the WIP.";
	case ecMissingLink:
		return "There are missing linked files.";
	case ecNoFontsFolder:
		return "Could not locate \"Temp Fonts\" folder.";
	case ecMissingFont:
		return "A necessary font was not loaded.";
	case ecFontNotCopied:
		return "A font file could not be copied to Temp Fonts.";


//Incorrect PDF print settings
	case ecBadOutputPath:
		return "You must select a valid output path.";
	case ecBadPlant:
		return "You must enter a valid Plant.";
	case ecBadPlate:
		return "You must enter a valid Plate.";
	case ecPDFError:
		return "There was an error outputting the PDF.";

	
//Misc Illustrator errors	
	default:
		unsigned char byteArray[4];
		
		// convert from an unsigned long int to a 4-byte array
		byteArray[0] = (int)((ecode >> 24) & 0xFF) ;
		byteArray[1] = (int)((ecode >> 16) & 0xFF) ;
		byteArray[2] = (int)((ecode >> 8) & 0XFF);
		byteArray[3] = (int)((ecode & 0XFF));
		
		std::string buffer("An Illustrator error occurred: ");
		return buffer.append((const char*)byteArray);
	}//end switch
}