/*
 *  CException.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 4/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "CException.h"

@implementation CException

- (id) init
{
	if (self = [super init]) {
		[self setCode:ecOK];
	}
	return self;
}

- (id) initWithCode: (errorcode) ec
{
	if (self = [super init]) {
		[self setCode:ec];
	}
	return self;
}

+ (CException*) withCode: (errorcode) ec
{
	return [[[CException alloc] initWithCode:ec] autorelease];
}

- (void) dealloc
{
	[super dealloc];
}

//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (errorcode) code
{
	return code;
}
- (void) setCode: (errorcode) ec
{
	code = ec;
}


- (NSString*) getDescription
{
	switch ([self code]) {
	
//Master Updater errors	
	case ecUpdaterNotRun:
		return @"You must run BStat Master Updater before using this tool.";
	case ecPlateNumberNotFound:
		return @"Plate Number and/or Registration Box were not found.";

	case ecNoDocOpen:
		return @"There is no open document.";

	case ecBadOriginPoint:
		return @"The document origin must be in the lower left.";
	
	case ecFaceMismatch:
		return @"There was an error determining which side is front and which is back.";
			

	case ecCropToolSelected:
		return @"The Crop Tool must not be selected.";
		
	case ecNoValidArtInLayer:
		return @"An art object could not be located in one of the layers.\nThis plate must be placed on a new master.";

	case ecDictArtObjectNotValid:
		return @"An art object needed by this file could not be found.\nThis plate must be placed on a new master.";

	case ecPlateStructArtObjectNotValid:
		return @"A necessary art object has been deleted.\nThis plate must be placed on a new master.";


//Incorrectly loaded errors
	case ecPlateNotFound:
		return @"The plate could not be located.";
	case ecPlateNotCopied:
		return @"The plate could not be copied from the Archive to the WIP.";
	case ecWIPFolderChanged:
		return @"The plate could not be found because the name of the folders on the WIP has changed.";	
	case ecArchiveFolderChanged:
		return @"The plate could not be found because the name of the folders on the Archive has changed.";
	case ecManufacturingFolderChanged:
		return @"The Manufacturing folder could not be found.";
	
	case ecMissingLink:
		return @"There are missing linked files.";
	case ecNoFontsFolder:
		return @"Could not locate \"Temp Fonts\" folder.";
	case ecMissingFont:
		return @"A necessary font was not loaded.";
	case ecFontNotCopied:
		return @"A font file could not be copied to Temp Fonts.";
	case ecNoIllustratorFile:
		return @"Could not find a valid Illustrator file.";
	case ecNoJobOptions:
		return @"There was a problem finding a required PDF options file.";



//Incorrect PDF print settings
	case ecBadOutputPath:
		return @"You must select a valid output path.";
	case ecBadPlant:
		return @"You must enter a valid Plant.";
	case ecBadPlate:
		return @"You must enter a valid Plate.";
	case ecPDFError:
		return @"There was an error outputting the PDF.";
		
		
//Key objects not found
	case ecKeyObjectNotFound:
		return @"One or more necessary objects were not found.\nThis plate must be placed on a new master.";
	case ecKeyObjectNotFoundRegBox:
		return @"A Registration Box was not found.\nThis plate must be placed on a new master.";
	case ecKeyObjectNotFoundPlateNum:
		return @"A Plate Number was not found.\nThis plate must be placed on a new master.";
	case ecKeyObjectNotFoundDate:
		return @"A Plate Date was not found.\nThis plate must be placed on a new master.";
	case ecKeyObjectNotFoundColorList:
		return @"A Color List was not found.\nThis plate must be placed on a new master.";
	
//Misc Illustrator errors	
	default:
		unsigned char byteArray[4];
		
		// convert from an unsigned long int to a 4-byte array
		byteArray[0] = (int)(([self code] >> 24) & 0xFF) ;
		byteArray[1] = (int)(([self code] >> 16) & 0xFF) ;
		byteArray[2] = (int)(([self code] >> 8) & 0XFF);
		byteArray[3] = (int)(([self code] & 0XFF));
		
		return [@"An Illustrator error occurred: " stringByAppendingString:[NSString stringWithCString:(const char*)byteArray encoding:4]];
	}//end switch
}

@end