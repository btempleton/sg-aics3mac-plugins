//
//  PlateItem.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CException.h"

@class Dialog;

@interface PlateItem : NSObject {
	NSString *plateNumber;
	NSString *plant;
	NSArray *plantListArray;
	NSString *result;
	
	CException* errorCode;
	
	//layerList dictionary: each key is the name of the layer, each object is a Layer object that contains the properties of the layer
	NSMutableDictionary *layerList;
	
	NSMutableSet *createdFiles;
}

//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (NSString*) plateNumber;
- (ai::UnicodeString) plateNumberAsUnicodeString;
- (void) setPlateNumber: (NSString *) theString;

- (NSString*) plant;
- (ai::UnicodeString) plantAsUnicodeString;
- (void) setPlant: (NSString *) theString;

- (NSArray*) plantListArray;
- (void) setPlantListArray: (NSArray*) theArray;
- (int) countOfPlantListArray;

- (NSString*) result;
- (void) setResult: (NSString *) theString;
- (void) setResultOK;
- (void) setResultBad: (CException*) ec;

- (CException*) errorCode;
- (void) setErrorCode: (CException*) ec;
- (NSString*) convertErrorCodeToDescription: (CException*) ec;
- (void) displayErrorMessage;

- (NSMutableDictionary*) layerList;
- (void) setLayerList: (NSMutableDictionary *) theDictionary;
- (void) storeLayerSettings;
- (void) recallLayerSettings;

- (NSMutableSet*) createdFiles;
- (void) setCreatedFiles: (NSMutableSet *)a;
- (void) addCreatedFile: (NSString *) pathToFile;

//**************************************************************
//*********** Convenience init and set *************************
//**************************************************************
- (PlateItem *) initWithPlateNumber: (NSString *) pN
							  Plant: (NSString *) pT
					 PlantListArray: (NSArray *) plA
							 Result: (NSString *) rT;

- (void) setPlateNumber: (NSString *) pN
				  Plant: (NSString *) pT
		 PlantListArray: (NSArray *) plA
		         Result: (NSString *) rT;
				 
+ (PlateItem *) createBlankItem;

//**************************************************************
//*********** Validation ***************************************
//**************************************************************
- (BOOL) isValidPlateNumber: (NSString *) theString;
- (BOOL) isValidPlant: (NSString *) theString;

- (NSArray *) getPlantArrayFromPlateNumber:(NSString*)theString;
- (NSString *) determineProductFromPlateNumber:(NSString*)theString;
				 
//**************************************************************
//*********** File Copying *************************************
//**************************************************************
- (void) fileToWIP;
- (BOOL) fileExistsOnWIP;
- (BOOL) fileExistsOnArchive;
- (NSString*) createWIPPath;
- (NSString*) createArchivePath;
- (NSString*) createManufacturingPath;
- (void) copyPlateFromArchiveToWIP;
- (void) loadFonts;
- (BOOL) allFontsLoaded;
- (void) cleanUpTempFonts;
- (void) cleanUpWIPFiles;

//**************************************************************
//*********** Making PDF   *************************************
//**************************************************************
- (BOOL) printToPDF:(Dialog *) dlg;
- (void) createNewFileFromNode:(NSValue *) node; //node will be cast back to a Node*
- (void) moveArtByOffset:(NSValue *)objCOffset;
- (void) convertToPaths;

- (void) openPlate: (NSString *) pathToFile;
- (void) closeOpenFiles;

@end
