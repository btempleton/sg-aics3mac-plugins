/*
 *  CException.h
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 4/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import <Cocoa/Cocoa.h>

#include "string.h"

typedef long errorcode;

#define ecOK							0 //No Error

//****Master Updater Errors
#define ecUpdaterNotRun					1 //Master Updater not run
#define	ecPlateNumberNotFound			2 //The Plate number text or the registration box could not be found

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
#define ecWIPFolderChanged				103 //The WIP folder could not be found
#define ecArchiveFolderChanged			104	//The Archive folder could not be found
#define ecManufacturingFolderChanged	105	//The Manufacturing folder could not be found

#define ecMissingLink					150 //There are missing linked files
#define ecNoFontsFolder					151 //The Temp Fonts folder could not be found
#define ecMissingFont					152 //There are missing fonts
#define ecFontNotCopied					153 //A font file could not be copied to Temp Fonts
#define ecNoIllustratorFile				154 //Could not find an Illustrator file for the plate
#define ecNoJobOptions					155 //There was a problem finding the pdf joboptions file

//Incorrect PDF print settings
#define ecBadOutputPath					201 //No output path selected or output path doesn't exist
#define ecBadPlant						202 //No or invalid plant selected
#define ecBadPlate						203 //No or invalid plate selected
#define ecPDFError						204 //Some error outputting PDF file

//Key objects not found
#define ecKeyObjectNotFound				500 //One of several required objects was not found
#define ecKeyObjectNotFoundRegBox		501	//Registration Box wasn't found
#define ecKeyObjectNotFoundPlateNum		502 //Plate number wasn't found
#define ecKeyObjectNotFoundDate			503	//Date wasn't found
#define ecKeyObjectNotFoundColorList	504 //Color List wasn't found


@interface CException : NSObject {
	errorcode code;
}

//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (errorcode) code;
- (void) setCode: (errorcode) ec;

- (id)init;
+ (CException*)withCode:(errorcode) ec;
- (id)initWithCode: (errorcode) ec;
- (void) dealloc;

- (NSString*) getDescription;

@end