/*
 *  CException.h
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 4/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include "string.h"

typedef long errorcode;

#define ecOK							0 //No Error

//****Master Updater Errors
#define ecUpdaterNotRun					1 //Master Updater not run
#define	ecPlateNumberNotFound			2 //The Plate number text or the registration box could not be found
#define ecKeyObjectNotFound				10 //One of several required objects was not found
#define ecNoDocOpen						11 //There is no current document
#define ecBadOriginPoint				12 //The document origin is not in the correct location relative to the artboard
#define ecFaceMismatch					13 //Front and backer could not be determined

#define ecCropToolSelected				15 //The crop tool was selected

#define ecNoValidArtInLayer				25 //The layer does not have any valid art in it

#define ecDictArtObjectNotValid			50 //The art object referred to in the plate dictionary was invalid
#define ecPlateStructArtObjectNotValid	51 //The art object stored in the Plate node was invalid

//Incorrectly loaded errors
#define ecPlateNotFound					101 //Could not locate plate
#define ecPlateNotCopied				102 //Could not copy folder from archive to wip
#define ecMissingLink					103 //There are missing linked files
#define ecNoFontsFolder					104 //The Temp Fonts folder could not be found
#define ecMissingFont					105 //There are missing fonts
#define ecFontNotCopied					106 //A font file could not be copied to Temp Fonts

//Incorrect PDF print settings
#define ecBadOutputPath					201 //No output path selected or output path doesn't exist
#define ecBadPlant						202 //No or invalid plant selected
#define ecBadPlate						203 //No or invalid plate selected
#define ecPDFError						204 //Some error outputting PDF file




class __attribute__((visibility("default"))) CException {
	errorcode ecode;
	
public:
	CException() {ecode = ecOK; }
	CException( errorcode c ) { ecode = c; }
	
	errorcode Code() { return ecode; }
	
	std::string GetDescription();
};


#endif //CEXCEPTION_H