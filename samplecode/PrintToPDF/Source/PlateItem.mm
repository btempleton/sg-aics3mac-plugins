//
//  PlateItem.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlateItem.h"
#import "Layer.h"

#import "CException.h"
#import "NSStringAdditions.h"

#include "ArtTree.h"
#import "VPB.h"
#include "DictFuncs.h"
#import "Node.h"


AIDocumentHandle originalDoc = NULL;
AIDocumentHandle createdDoc = NULL;

extern Dialog* theDialog;
extern AIDictionaryRef dictMain;
extern Node* startNode;
extern AIColor registrationColor;

@implementation PlateItem

//*************************************************
// -init
// initializes a PlateItem object
//*************************************************
-(id)init
{
	if (self = [super init]) {
		plateNumber = @"";
		plant = @"";
		plantListArray = [[NSArray alloc] initWithObjects:@"Enter a plate number", nil];
		result = @"";
		errorCode = nil;
		layerList = [[NSMutableDictionary alloc] initWithCapacity:1];
		createdFiles = [[NSMutableSet alloc] initWithCapacity:1];
	}
	return self;
}

//*************************************************
// -initWithPlateNumber:Plant:Result
// initializes a PlateItem object with specific info
//*************************************************
- (PlateItem *) initWithPlateNumber: (NSString *) pN
							  Plant: (NSString *) pT
					 PlantListArray: (NSArray *) plA
							 Result: (NSString *) rT
{
	if (self = [super init]) {
		[self setPlateNumber: pN   Plant: pT  PlantListArray: plA	Result: rT];
		errorCode = nil;
		layerList = [[NSMutableDictionary alloc] initWithCapacity:1];
		createdFiles = [[NSMutableSet alloc] initWithCapacity:1];
	}
	return self;
}


//*************************************************
// -dealloc
// destructor
//*************************************************
-(void)dealloc
{
	[plantListArray release];
	[layerList release];
	[createdFiles release];
	[super dealloc];
}


//****************************************************************************************************
// ************************** Getters/Setters *************************************************
//****************************************************************************************************
- (NSString*)plateNumber
{
	return plateNumber;
}

- (ai::UnicodeString)plateNumberAsUnicodeString
{
	ai::UnicodeString us([plateNumber UTF8String], kAIUTF8CharacterEncoding);
	return us;
}

- (void)setPlateNumber:(NSString*)theString
{
	if (theString == plateNumber) {
		return;
	}
	
	//Check our plate number for validity before we store it
	try {
		if ([self isValidPlateNumber:theString]) {
			[theString retain];
			[plateNumber release];
			plateNumber = theString;
			
			//Set up the plant array based on the plate number
			[self setPlantListArray:[self getPlantArrayFromPlateNumber:[self plateNumber]]];
			
		} else {
			throw [CException withCode:ecBadPlate];
		}
	}
	catch(CException* e) {
		[self setErrorCode:e];
		[self displayErrorMessage];
	}
}

- (NSString*)plant
{
	return plant;
}

- (ai::UnicodeString)plantAsUnicodeString
{
	ai::UnicodeString us([plant UTF8String], kAIUTF8CharacterEncoding);
	return us;
}

- (void)setPlant:(NSString*)theString
{
	if (theString == plant) {
		return;
	}
	
	if ([theString length] == 0) {
		[plant release];
		plant = nil;
		return;
	}
	
	//Check our plant for validity before we store it
	try {
		if ([self isValidPlant:theString]) {
			[theString retain];
			[plant release];
			plant = theString;
		} else {
			throw [CException withCode:ecBadPlant];
		}
	}
	catch(CException* e) {
		[self setErrorCode:e];
		[self displayErrorMessage];
	}
}

- (NSArray*) plantListArray
{
	return plantListArray;
}

- (void) setPlantListArray: (NSArray*) theArray
{
	if (theArray == plantListArray) {
		return;
	}
	
	[theArray retain];
	[plantListArray release];
	plantListArray = theArray;	
}

- (int) countOfPlantListArray
{
	return [[self plantListArray] count];
}

- (NSString*)result
{
	return result;
}

- (void)setResult:(NSString*)theString
{
	if (theString == result) {
		return;
	}
	
	[theString retain];
	[result release];
	result = theString;
	
}

//*************************************************
// -setResultOK
// Set the result var to OK
//*************************************************
- (void) setResultOK
{
	[result release];

	[self setValue:@"OK!" forKey:@"result"];
	[self setValue:[CException withCode:ecOK] forKey:@"errorCode"];
}

//*************************************************
// -setResultBad
// Set the result var to Error and store the reason for failure in errorDescription
//*************************************************
- (void) setResultBad: (CException*) ec
{
	[result release];
	
	[self setValue:@"ERR" forKey:@"result"];
	[self setValue:ec forKey:@"errorCode"];
}

//*************************************************
// -errorCode
// Getter
//*************************************************
- (CException*) errorCode
{
	return errorCode;
}

//*************************************************
// -setErrorCode
// Setter
//*************************************************
- (void) setErrorCode: (CException*) ec
{
	if (ec == errorCode) {
		return;
	}
	[ec retain];
	[errorCode release];
	errorCode = ec;
}

//*************************************************
// -convertErrorCodeToDescription:errorCode
// Returns the text description of the errorCode passed
//*************************************************
- (NSString*) convertErrorCodeToDescription: (CException*) ec
{
	return [ec getDescription];
}

//*************************************************
// -displayErrorMessage
// Displays an alert informing the user of an error
//*************************************************
- (void) displayErrorMessage
{
	if ( [self errorCode] && ([[self errorCode] code] != ecOK) ) {
		NSRunAlertPanel(@"Error!", [self convertErrorCodeToDescription:[self errorCode]], @"OK", nil, nil);
		return;
	}
}

//*************************************************
// -layerList
// Getter
//*************************************************

- (NSMutableDictionary*)layerList
{
	return layerList;
}

//*************************************************
// -setLayerList
// Setter
//*************************************************
- (void)setLayerList:(NSMutableDictionary*)theDictionary
{
	if (theDictionary == layerList) {
		return;
	}
	
	[theDictionary retain];
	[layerList release];
	layerList = theDictionary;
}

//*************************************************
// -storeLayerSettings
// Gets each layer to our layer list dictionary
//*************************************************
- (void) storeLayerSettings
{
	long count = 0; sAILayer->CountLayers(&count);
	for (int i=0 ; i < count ; i++) {
		AILayerHandle currLayer= NULL; sAILayer->GetNthLayer(i, &currLayer);
		ai::UnicodeString layerName; sAILayer->GetLayerTitle(currLayer, layerName);
		
		[layerList setValue:[Layer layerWithLayerNamed:[NSString withAIUnicodeString:layerName]]
					 forKey:[NSString withAIUnicodeString:layerName]];
	}
}


//*************************************************
// -recallLayerSettings
// Gets the settings stored in our layer list dictionary and re-applies them to the the AI layers
//*************************************************
- (void) recallLayerSettings
{
	NSEnumerator *keyEnum = [layerList keyEnumerator];
	NSString* key;
	
	while ((key = [keyEnum nextObject]))
	{
		Layer* object = [layerList objectForKey:key];
		AILayerHandle currLayer = NULL; sAILayer->GetLayerByTitle(&currLayer, ai::UnicodeString((CFStringRef)key));
		sAILayer->SetLayerEditable(currLayer, (int)[[object valueForKey:@"editable"] boolValue]);
		sAILayer->SetLayerVisible(currLayer, (int)[[object valueForKey:@"visible"] boolValue]);
		sAILayer->SetLayerPreview(currLayer, (int)[[object valueForKey:@"preview"] boolValue]);
	}
}



//*************************************************
// -createdFiles
// Getter
//*************************************************
- (NSMutableSet *) createdFiles
{
	return createdFiles;
}
//*************************************************
// -setCreatedFiles
// Setter
//*************************************************
- (void) setCreatedFiles:(NSMutableSet *)a
{
	if (a == createdFiles) {
		return;
	}
	[a retain];
	[createdFiles release];
	createdFiles = a;
}
//*************************************************
// -addCreatedFile:pathToFile
// Adds a specified PlateItem to the plate list
//*************************************************
- (void) addCreatedFile: (NSString *) pathToFile
{
	[createdFiles addObject:pathToFile];
}


//*************************************************
// -createBlankPlateItem
// Adds a specified PlateItem to the plate list
//*************************************************
+ (PlateItem*)createBlankItem
{
	return [[[PlateItem alloc] init] autorelease];
}


//*************************************************
// -setPlateNumber:Plant:Result
// sets a PlateItem object with specific info
//*************************************************
- (void) setPlateNumber: (NSString *) pN
				  Plant: (NSString *) pT
		 PlantListArray: (NSArray *) plA
				 Result: (NSString *) rT
{
	[self setPlateNumber:pN];
	[self setPlant:pT];
	[self setPlantListArray:plA];
	[self setResult:rT];
}



//*************************************************
// -isValidPlateNumber:theString
// Checks whether the plate number matches the correct format
//*************************************************
- (BOOL) isValidPlateNumber: (NSString *) theString
{
	//Check the length is in range
	if (([theString length] > 11) || [theString length] < 6) { return NO; }
	
	//If the first character isn't one of the plant indicator letters
	if ( !([@"F" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] ||
		   [@"M" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] ||
		   [@"S" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] ||
		   [@"W" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] ||
		   [@"X" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] ||
		   [@"Y" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(0, 1)]] 
		  )
		) { return NO; }
	
	//If the second two characters aren't a number
	if (! [[theString substringWithRange:NSMakeRange(1, 2)] intValue] ) { return NO; }
	
	//If the 4 and 5 characters aren't a valid product key
	//If the two strings are equal, caseInsensitiveCompare returns 0, so if any one of these comparisons is non-0, we want to fail
	if ( [@"BA" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]] &&
		 [@"BC" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]] &&
		 [@"BE" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]] &&
		 [@"BL" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]] &&
		 [@"MP" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]] &&
		 [@"SP" caseInsensitiveCompare:[theString substringWithRange:NSMakeRange(3, 2)]]
	   ) { return NO; }
	
	//Get the rest of the string and make sure its all numbers
	if (! [[theString substringFromIndex:5] intValue] ) { return NO; }
	
	return YES;
}

//*************************************************
// -isValidPlant:theString
// Checks whether the plant is one of the acceptable ones
//*************************************************
- (BOOL) isValidPlant: (NSString *) theString
{
	if ( //compare returns 0 if they are equal, so if any one of these is 0 we're good
		[@"TOWNSEND" caseInsensitiveCompare:theString] &&
		[@"SALT LAKE CITY" caseInsensitiveCompare:theString] &&
		[@"MIDLAND" caseInsensitiveCompare:theString] &&
		[@"BURDGE" caseInsensitiveCompare:theString]
	   ) { return NO; }
	
	return YES;	
}

//*************************************************
// -fileToWIP
// Checks the WIP for our PlateItem, copies it from the Archive if not found
// Copies any fonts to the temp fonts folder, overwriting anything that is currently there
//*************************************************
- (void) fileToWIP
{
	try {
		if ([self fileExistsOnWIP]) {
			return;
		} else if ([self fileExistsOnArchive]) {
			[self copyPlateFromArchiveToWIP];
			if ([self fileExistsOnWIP]) {
				return;
			}
		}
		
		throw [CException withCode:ecPlateNotFound];
	}
	catch(CException* e) {
		throw;
	}
}

//*************************************************
// -fileExistsOnWIP
// Checks the WIP for our PlateItem
//*************************************************
- (BOOL) fileExistsOnWIP
{
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];

	if ([MyFileManager fileExistsAtPath:[self createWIPPath]]) {
		[MyFileManager release];
		return YES;
	} else {
		if (![MyFileManager fileExistsAtPath:[[self createWIPPath] stringByDeletingLastPathComponent]]) {
			[MyFileManager release];
			throw [CException withCode:ecWIPFolderChanged];
		}
		[MyFileManager release];
		return NO;
	}	
}

//*************************************************
// -fileExistsOnArchive
// Checks the Archive for our PlateItem
//*************************************************
- (BOOL) fileExistsOnArchive
{
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	
	if ([MyFileManager fileExistsAtPath:[self createArchivePath]]) {
		[MyFileManager release];
		return YES;
	} else {
		if (![MyFileManager fileExistsAtPath:[[self createArchivePath] stringByDeletingLastPathComponent]]) {
			[MyFileManager release];
			throw [CException withCode:ecArchiveFolderChanged];
		}
		[MyFileManager release];
		return NO;
	}	
}

//*************************************************
// -createWIPPath
// Generates a path to the appropriate folder on the WIP
//*************************************************
- (NSString*) createWIPPath
{
	NSString* path = @"/Volumes/WIP/WIP/Business Stat WIP/";
	NSString* tComponent;
	
	//Take the first character of the platenumber
	tComponent = [NSString stringWithString:[[self plateNumber] substringWithRange:NSMakeRange(0, 1)]];
	tComponent = [tComponent stringByAppendingString:@" BS Wip"];
	path = [path stringByAppendingPathComponent:tComponent];
	
	path = [path stringByAppendingPathComponent:[self plateNumber]];
	
	return path;
}

//*************************************************
// -createArchivePath
// Generates a path to the appropriate folder on the Archive
//*************************************************
- (NSString*) createArchivePath
{
	NSString* path = @"/Volumes/Archive/Archive/Business Stat Archive/";
	NSString* tComponent;
	
	//We're going to build our path....
	
	//Take the first 3 chars of the plate number... The first part of the path should be A##-  or potentially A##MP-
	tComponent = [NSString stringWithString:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]];
	//Next we need to check if we have an MP file and stick the MP in there
	// (only for M06, M07, M08, M09, M10, M11
	if ( ! [@"M06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M11" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ) {
		if ( ! [@"MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(3, 2)]] ||
			 ! [@"ML" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(3, 2)]] ) {
			tComponent = [tComponent stringByAppendingString:@"MP"];
		}		
	}
	//And the dash, which has a different number of spaces depending on the letter
	//13 spaces
	if ( ! [@"F05" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"F06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"F07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"F08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"F09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y05" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ) {
		tComponent = [tComponent stringByAppendingString:@"-             FOLDER"];
	}
	//12 spaces
	else if ( ! [@"M00" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M01" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M02" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M03" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M04" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M05" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"W09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"W10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"W11" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"Y11" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]]) {
		tComponent = [tComponent stringByAppendingString:@"-            FOLDER"];
	}
	//7 spaces
	else if ( ! [@"M06MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M06ML" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M07MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M08MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M09MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M10MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		  ! [@"M11MP" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ) {
		tComponent = [tComponent stringByAppendingString:@"-       FOLDER"];
	}
	//Then add it to our path
	path = [path stringByAppendingPathComponent:tComponent];
	
	//Next folder, there are few different ones
	// Some just have the plates right in it, so we can test for those and not add anything
	if ( ! [@"M00" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"M11" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ||
		 ! [@"S10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 3)]] ) {
	//The rest, use the first 5 characters of the plate number
	} else {
		path = [path stringByAppendingPathComponent:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]];
		//Of these ones, some are split into number folders
		tComponent = [[self plateNumber] substringWithRange:NSMakeRange(0, 7)];
		if ( ! [@"M01BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M01BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M01BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M02BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M02BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M02BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M03BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M03BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M03BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M04BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M04BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M04BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M05BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M05BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"M05BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W09BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W09BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W09BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W10BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W10BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"W10BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y06BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y06BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y06BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
		 	 ! [@"Y07BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y07BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y07BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y08BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y08BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y08BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y09BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y09BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y09BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y10BC" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y10BE" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] ||
			 ! [@"Y10BL" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(0, 5)]] )
		{
			if ( ! [@"00" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"0001-999"];
			}
			else if ( ! [@"01" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"1000-1999"];
			}
			else if ( ! [@"02" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"2000-2999"];
			}
			else if ( ! [@"03" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"3000-3999"];
			}
			else if ( ! [@"04" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"4000-4999"];
			}
			else if ( ! [@"05" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"5000-5999"];
			}
			else if ( ! [@"06" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"6000-6999"];
			}
			else if ( ! [@"07" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"7000-7999"];
			}
			else if ( ! [@"08" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"8000-8999"];
			}
			else if ( ! [@"09" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"9000-9999"];
			}
			else if ( ! [@"10" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"0000-10999"];
			}
			else if ( ! [@"11" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"1000-11999"];
			}
			else if ( ! [@"12" caseInsensitiveCompare:[[self plateNumber] substringWithRange:NSMakeRange(6, 2)]] ) {
				tComponent = [tComponent stringByAppendingString:@"2000-12999"];
			}
			//Now add this folder to the path
			path = [path stringByAppendingPathComponent:tComponent];
		}
	}
	

	//Then, we add the plate number
	path = [path stringByAppendingPathComponent:[self plateNumber]];
		
	return path;
}

//*************************************************
// -createManufacturingPath
// Generates a URL-ready path to the appropriate folder on Plant Manufacturing
//*************************************************
- (NSString*) createManufacturingPath
{
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	
	NSString* path = @"/Volumes/Plant_Manufacturing/";
	NSString* tComponent;
	
	//Depending on which plant, we need a different path
	if ( ! [@"TOWNSEND" caseInsensitiveCompare:[self plant]] ) {
		tComponent = [NSString stringWithString:@"Townsend Files/Bus Stat to be plated"];
	}
	else if ( ! [@"SALT LAKE CITY" caseInsensitiveCompare:[self plant]] ) {
		tComponent = [NSString stringWithString:@"Salt Lake City Files/BS to be Plated"];
	}
	else if ( ! [@"MIDLAND" caseInsensitiveCompare:[self plant]] ) {
		tComponent = [NSString stringWithString:@"Midland Files/BC to be Plated"];
	}
	
	path = [path stringByAppendingPathComponent:tComponent];
	
	if ([MyFileManager fileExistsAtPath:path]) {
		[MyFileManager release];
		return path;
	} else {
		[MyFileManager release];
		throw [CException withCode:ecManufacturingFolderChanged];
	}
	
	return nil;
}


//*************************************************
// -copyPlateFromArchiveToWIP
// Checks the Archive for the plate, then performs the file copy to the appropriate WIP folder
//*************************************************
- (void) copyPlateFromArchiveToWIP
{
	NSString* src = [self createArchivePath];
	NSString* dst = [[self createWIPPath] stringByDeletingLastPathComponent];
	
	if ([self fileExistsOnArchive]) {
		//FSFileOperationRef fileOp = FSFileOperationCreate(NULL);
		//FSFileOperationScheduleWithRunLoop(fileOp, [[NSRunLoop currentRunLoop] getCFRunLoop], kCFRunLoopCommonModes);
		
		OSStatus error = FSPathCopyObjectSync([src fileSystemRepresentation], [dst fileSystemRepresentation], NULL, NULL, kFSFileOperationDefaultOptions);
		
		//CFRelease(fileOp);
		
		if (error) {
			throw [CException withCode:ecPlateNotCopied];			
		} else {
			[self addCreatedFile:[self createWIPPath]];
		}
	}
}


//*************************************************
// -loadFonts
// Checks the WIP folder for any font files and copies them to the Temp Fonts folder
//*************************************************
- (void) loadFonts
{
	//Set up our paths
	//CODE TO GET DESKTOP PATH
	NSString* library_path = [NSSearchPathForDirectoriesInDomains (NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	NSString* tempFontsPath = [library_path stringByAppendingPathComponent:@"/Fonts/Temp Fonts"];
	
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	
	//Check if the folders exist
	try {
		if (! [self fileExistsOnWIP]) {
			throw [CException withCode:ecPlateNotFound];
		}
		if (! [MyFileManager fileExistsAtPath:tempFontsPath] ) {
			throw [CException withCode:ecNoFontsFolder];
		}
	}
	catch(CException* e) {
		[MyFileManager release];
		throw;
	}
	
	//Loop through the contents of our folder and copy any font files to our temp fonts folder
	NSDirectoryEnumerator *enumerator = [MyFileManager enumeratorAtPath:[self createWIPPath]];
	
	NSString* file;
	while (file = [enumerator nextObject]) {
		FSRef fsRefToItem;
		FSPathMakeRefWithOptions( (const UInt8 *)[[[self createWIPPath] stringByAppendingPathComponent:file] fileSystemRepresentation], kFSPathMakeRefDefaultOptions, &fsRefToItem, NULL );
		
		CFStringRef itemUTI = NULL;
		LSCopyItemAttribute( &fsRefToItem, kLSRolesAll, kLSItemContentType, (CFTypeRef*)&itemUTI );
		
		if (UTTypeConformsTo(itemUTI, CFSTR("public.font"))) {
			
			NSString* src = [[self createWIPPath] stringByAppendingPathComponent:file];
			NSString* dst = tempFontsPath;
			
			//Copy font files to Temp Fonts folder
			try {
								
				OSStatus error = FSPathCopyObjectSync([src fileSystemRepresentation], [dst fileSystemRepresentation], NULL, NULL, kFSFileOperationDefaultOptions);

				if (error) {
					throw [CException withCode:ecFontNotCopied];			
				} else {
					[self addCreatedFile:[dst stringByAppendingPathComponent:[file lastPathComponent]]];
				}
			}
			catch (CException* e) {
				[MyFileManager release];
				throw;
			}
		}
	}
	[MyFileManager release];
}

//*************************************************
// -allFontsLoaded
// Checks the frontmost open document for any missing fonts
//*************************************************
- (BOOL) allFontsLoaded
{
	//CREATE THE ART SET
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	AIArtSpec specs[] = { { kTextFrameArt , 0 , 0 } };
	sAIArtSet->MatchingArtSet( specs , 1, artSet );
	
	//Loop the art set
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	for ( int i=0 ; i < count ; i++ ) {
		
		AIArtHandle currArtHandle = NULL;
		sAIArtSet->IndexArtSet( artSet, i, &currArtHandle );
		
		//Create the ATE range
		ATE::TextRangeRef currATETextRangeRef;
		sAITextFrame->GetATETextRange(currArtHandle, &currATETextRangeRef);
		ATE::ITextRange currTextRange(currATETextRangeRef);
		
		//Create the runs iterator
		ATE::ITextRunsIterator it = currTextRange.GetTextRunsIterator();
		
		//Get the Features
		ATE::ICharFeatures currCharFeatures = it.Item().GetUniqueCharFeatures();
		
		//Get the font applied to the range
		bool isAssigned = false;
		ATE::IFont currFont = currCharFeatures.GetFont(&isAssigned);
		if (isAssigned) {
			//Get the FontRef
			FontRef currFontRef = currFont.GetRef();
			
			//Get the FontKey
			AIFontKey currFontKey = NULL;
			sAIFont->FontKeyFromFont(currFontRef, &currFontKey);
			
			//Get the Font info
			AIFontStyle currFontStyle;
			sAIFont->GetFontInfo(currFontKey, &currFontStyle);
			
			//Check if its a substitute
			if (currFontStyle.fauxedInstalled) {
				sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
				return NO;
			}
		}
	}

	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
	return YES;
}



//*************************************************
// -cleanUpTempFonts
// Checks createFiles for any files created in Temp Fonts and removes them
//*************************************************
- (void) cleanUpTempFonts
{
	NSEnumerator *enumerator = [[self createdFiles] objectEnumerator];
	id anObject; //NSString path to created files
	
	while (anObject = [enumerator nextObject]) {
		NSArray* components = [anObject pathComponents];
		if ([components containsObject:@"Temp Fonts"]) {
			NSFileManager* MyFileManager = [[NSFileManager alloc] init];
			if ([MyFileManager removeFileAtPath:anObject handler:nil])
			{
				[[self createdFiles] removeObject:anObject];
			}
			
			[MyFileManager release];
		}
	}
}

//*************************************************
// -cleanUpWIPFiles
// Checks createFiles for any files created in Temp Fonts and removes them
//*************************************************
- (void) cleanUpWIPFiles
{
	NSEnumerator *enumerator = [[self createdFiles] objectEnumerator];
	id anObject; //NSString path to created files
	
	while (anObject = [enumerator nextObject]) {
		NSArray* components = [anObject pathComponents];
		if ([components containsObject:@"WIP"]) {
			NSFileManager* MyFileManager = [[NSFileManager alloc] init];
			if ([MyFileManager removeFileAtPath:anObject handler:nil])
			{
				[[self createdFiles] removeObject:anObject];
			}
			
			[MyFileManager release];
		}
	}	
}


//*************************************************
// -getPlantArrayFromPlateNumber
// This will fill an array with the available plants for the entered plate number
//*************************************************
- (NSArray *) getPlantArrayFromPlateNumber:(NSString*)theString
{
	//If for some reason there's no string passed in
	if (![theString length] || !theString) return [NSArray arrayWithObjects:@"Enter a plate number", nil];
	
	NSMutableArray* theArray = nil;
	NSString* productCode = [self determineProductFromPlateNumber:theString];
	NSEnumerator* enumerator = [[theDialog theTree] objectEnumerator];
	id anObject;
	while (anObject = [enumerator nextObject]) {
		if ([[anObject nodeName] compare:productCode] == NSOrderedSame) {
			NSEnumerator* chEnum = [[anObject children] objectEnumerator];
			id chObj;
			while (chObj = [chEnum nextObject]) {
				if (theArray) {
					[theArray addObject:[chObj nodeName]];
				} else {
					theArray = [NSMutableArray arrayWithObject:[chObj nodeName]];
				}
			}
		} else {
			return [NSMutableArray arrayWithObject:@"Continuous!"];
		}
	}
	
	return theArray;
}

//*************************************************
// -determineProductFromPlateNumber
// This will return a code signifying what product a passed plate number belongs to
//*************************************************
- (NSString *) determineProductFromPlateNumber:(NSString*)theString
{
	if ([theString compare:@"M01BC000012"] == NSOrderedSame){
		return @"CF";
	} else {
		return @"BS";
	}
	
}


//*************************************************
// -printToPDF:dlg
// Prints each plate area on our illustrator file to a separate pdf file.
//*************************************************
- (BOOL) printToPDF:(Dialog*)dlg
{
	sAIUndo->SetUndoText("Undo Update Date", "Redo Update Date");
	
	//Retrieve the dictionary for this file
	sAIDocument->GetDictionary(&dictMain);
	
	//Check if the BStat Master version number is in the dictionary
	try {
		//TODO: Make this check for the most recent version?
		if ( !sAIDictionary->IsKnown(dictMain, sAIDictionary->Key("BSTATMU_VERSION")) ) {
			throw [CException withCode:ecUpdaterNotRun];
		}
		
		if (AllLinkedFilesValid()) {
			
			SetUpNodes();
			
			if ( startNode->p->PlateNumberUIDRef() && startNode->p->RegBoxUIDRef() ) {
				Node* currNode = startNode;
				Instance instance;
				
				while (currNode) {
					currNode->p->UpdateDate();
					currNode = currNode->nextNode;
				}
				
				
				currNode = startNode;
				
				//Loop through each node and make the pdf
				while (currNode) {
					if ( currNode->p->Prints() ) {
						
						//Find the offset
						AIRealPoint offset;
						
						ASInt32 cropCount;
						sAICropArea->GetCount(&cropCount);
						if (cropCount == 0) {
							offset.h = 0;
							offset.v = 0;
						} else {
							AIRealRect nodeBounds = currNode->p->GetCropAreaRect();
							AIRealPoint a = { nodeBounds.left, nodeBounds.top};
							AIRealPoint b = { nodeBounds.right, nodeBounds.bottom};
							AIRealPoint nodeCenter;
							sAIRealMath->AIRealPointInterpolate(&a, &b, .5, &nodeCenter);
							
							AICropAreaPtr cropArea;
							sAICropArea->Get(0, &cropArea);
							AIRealPoint c = { cropArea->m_CropAreaRect.left, cropArea->m_CropAreaRect.top};
							AIRealPoint d = { cropArea->m_CropAreaRect.right, cropArea->m_CropAreaRect.bottom};
							AIRealPoint pageCenter;
							sAIRealMath->AIRealPointInterpolate(&c, &d, .5, &pageCenter);
							
							sAIRealMath->AIRealPointSubtract(&pageCenter, &nodeCenter, &offset);
						}
						
						[self moveArtByOffset:[NSValue valueWithPointer:&offset]];
						
						[self createNewFileFromNode:[NSValue valueWithPointer:currNode]];
						
						[self convertToPaths];
						
						//We need to get the plate number from the plate struct
						ASErr error = instance.SaveDocumentAsPDF(dlg, self, currNode->p->PlateNumberStr() );
						
						sAIDocumentList->Activate(createdDoc, TRUE);
						sAIDocument->SetDocumentModified(FALSE);
						sAIDocumentList->Close(createdDoc);
						createdDoc = NULL;
						
						//Reverse the coords, move everything back
						offset.h = -offset.h; offset.v = -offset.v;
						[self moveArtByOffset:[NSValue valueWithPointer:&offset]];
						
						if (kNoErr != error ) {
							throw [CException withCode:error];
						}
					}
					
					currNode = currNode->nextNode;
				}
			} else {
				throw [CException withCode:ecPlateNumberNotFound];
			} 
		} else {
			throw [CException withCode:ecMissingLink];
		}
	} 
	
	catch(CException* e) {
		CleanUpNodes();
		throw;
	}
	
	CleanUpNodes();
	return YES;	
}


//*************************************************
// -createNewFileFromNode:objCNode
// Creates a new Illustrator file at the right size and copies the art we want into it
//*************************************************
- (void) createNewFileFromNode:(NSValue *)objCNode
{
	Node* node = (Node *)[objCNode pointerValue];
	
	float width = ((node->p->GetCropAreaRect()).right) - ((node->p->GetCropAreaRect()).left);
	float height = ((node->p->GetCropAreaRect()).top) - ((node->p->GetCropAreaRect()).bottom);
	
	ai::UnicodeString presetName("");
	AINewDocumentPreset preset = {
		ai::UnicodeString("none"), //DocTitle
		width, //DocWidth
		height, //DocHeight
		kAICMYKColorModel, //Color model
		kPicasUnits, //doc units
		kAIPreviewModeOverprintPreview, // preview mode
		kAITransparencyGridLight, //transparency grid
		kAIRasterResolutionHigh //raster resolution
	};
	
	
	sAIDocumentList->New(presetName, &preset, kDialogOff, &createdDoc);
	
	
	//We only want art from layers Foreground, Keyline and SLUG
	AIArtHandle dupArtHandle = NULL;
	AILayerHandle newFileLayerHandle = NULL;
	AIArtHandle newFileLayerFirstArtHandle = NULL;
	AIArtHandle currArtHandle = NULL;
	
	
	//****FOREGROUND
	sAIDocumentList->Activate(originalDoc, TRUE);
	AIArtSet artSet; sAIArtSet->NewArtSet(&artSet);
	long count = CreateArtSetFromLayer(ai::UnicodeString("Foreground"), artSet);
	
	sAIDocumentList->Activate(createdDoc, TRUE);
	sAIUndo->SetKind(kAISilentUndoContext);
	sAILayer->InsertLayer(NULL, kPlaceAboveAll, &newFileLayerHandle);
	sAILayer->SetLayerTitle(newFileLayerHandle, ai::UnicodeString("Foreground"));
	sAIArt->GetFirstArtOfLayer(newFileLayerHandle, &newFileLayerFirstArtHandle);
	
	//LOOP THE ART SET
	for ( int i=0 ; i < count ; i++ ) {
		currArtHandle = NULL;
		sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
		sAIArt->DuplicateArt(currArtHandle, kPlaceInsideOnBottom, newFileLayerFirstArtHandle, &dupArtHandle);
	}
	
	//****SLUG
	sAIDocumentList->Activate(originalDoc, TRUE);
	sAIArtSet->NewArtSet(&artSet);
	count = CreateArtSetFromLayer(ai::UnicodeString("SLUG"), artSet);
	
	sAIDocumentList->Activate(createdDoc, TRUE);
	sAILayer->InsertLayer(NULL, kPlaceAboveAll, &newFileLayerHandle);
	sAILayer->SetLayerTitle(newFileLayerHandle, ai::UnicodeString("SLUG"));
	sAIArt->GetFirstArtOfLayer(newFileLayerHandle, &newFileLayerFirstArtHandle);
	
	//Get and copy each of the 3 SLUG items to the new file
	currArtHandle = GetArtHandleFromUIDRef(node->p->ColorListUIDRef());
	sAIArt->DuplicateArt(currArtHandle, kPlaceInsideOnBottom, newFileLayerFirstArtHandle, &dupArtHandle);
	
	currArtHandle = GetArtHandleFromUIDRef(node->p->PlateNumberUIDRef());
	sAIArt->DuplicateArt(currArtHandle, kPlaceInsideOnBottom, newFileLayerFirstArtHandle, &dupArtHandle);
	
	currArtHandle = GetArtHandleFromUIDRef(node->p->DateUIDRef());
	sAIArt->DuplicateArt(currArtHandle, kPlaceInsideOnBottom, newFileLayerFirstArtHandle, &dupArtHandle);	
	
	
	
	
	
	//****KEY LINE
	sAIDocumentList->Activate(originalDoc, TRUE);
	sAIArtSet->NewArtSet(&artSet);
	count = CreateArtSetFromLayer(ai::UnicodeString("KEY LINE"), artSet);
	
	sAIDocumentList->Activate(createdDoc, TRUE);
	sAILayer->InsertLayer(NULL, kPlaceAboveAll, &newFileLayerHandle);
	sAILayer->SetLayerTitle(newFileLayerHandle, ai::UnicodeString("KEY LINE"));
	sAIArt->GetFirstArtOfLayer(newFileLayerHandle, &newFileLayerFirstArtHandle);
	
	//LOOP THE ART SET
	for ( int i=0 ; i < count ; i++ ) {
		currArtHandle = NULL;
		sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
		sAIArt->DuplicateArt(currArtHandle, kPlaceInsideOnBottom, newFileLayerFirstArtHandle, &dupArtHandle);
	}
	
	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
	
	return;
}

//*************************************************
// -moveArtByOffset:offset
// Converts the text on Foreground layer to paths
//*************************************************
- (void) moveArtByOffset:(NSValue *)objCOffset
{
	AIRealPoint offset = *((AIRealPoint*)[objCOffset pointerValue]);
	
	//CREATE THE ART SET
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	
	//FILL THE ART SET
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
	
	//LOOP THE ART SET
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	for ( int i=0 ; i < count ; i++ ) {
		AIArtHandle currArtHandle = NULL;
		sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
		
		//Get the layer of the art
		AILayerHandle layer; sAIArt->GetLayerOfArt(currArtHandle, &layer);
		
		//Store the User Attributes
		int eflag = 0; int vflag = 0;
		ASBoolean editable = FALSE;
		ASBoolean visible = FALSE;
		//Check if the layer is editable
		sAILayer->GetLayerEditable(layer, &editable);
		sAILayer->GetLayerVisible(layer, &visible);
		//Check if the art itself is editable
		long attr;
		sAIArt->GetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, &attr);
		
		
		//Set the layer editable and visible, set flags so we can set it back the way it was
		if (!editable) { sAILayer->SetLayerEditable(layer, TRUE); eflag = 1; }
		if (!visible) { sAILayer->SetLayerVisible(layer, TRUE); vflag = 1; }
		//Set the User Attributes
		if ( attr & kArtLocked ) {
			sAIArt->SetArtUserAttr(currArtHandle, kArtLocked, 0);
		}
		if ( attr & kArtHidden ) {
			sAIArt->SetArtUserAttr(currArtHandle, kArtHidden, 0);
		}
		
		
		//Move the art
		AIRealMatrix translateMatrix;
		sAIRealMath->AIRealMatrixSetIdentity( &translateMatrix );
		sAIRealMath->AIRealMatrixConcatTranslate( &translateMatrix, offset.h, offset.v ); 
		sAITransformArt->TransformArt(currArtHandle, &translateMatrix, 0, kTransformObjects);
		
		
		
		//Set the layer and art attributes back the way they were
		if(eflag) { sAILayer->SetLayerEditable(layer, FALSE);}
		if(vflag) { sAILayer->SetLayerVisible(layer, FALSE); }
		sAIArt->SetArtUserAttr(currArtHandle, kArtLocked | kArtHidden, attr);
	}
	//DISPOSE THE ART SET
	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
}


//*************************************************
// -convertToPaths
// Converts the text on Foreground layer to paths
//*************************************************
- (void) convertToPaths
{
	//CREATE THE ART SET
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	
	AIArtSet textArtSet;
	sAIArtSet->NewArtSet(&textArtSet);
	
	AIArtSet foregroundArtSet;
	sAIArtSet->NewArtSet(&foregroundArtSet);
	AILayerHandle foregroundLayerHandle = NULL;
	
	//FILL THE ART SET
	AIArtSpec specs[] = { { kTextFrameArt , 0 , 0 } };
	sAIArtSet->MatchingArtSet( specs , 1, textArtSet );
	
	sAILayer->GetLayerByTitle(&foregroundLayerHandle, ai::UnicodeString("Foreground") );
	sAIArtSet->LayerArtSet(foregroundLayerHandle, foregroundArtSet);
	
	sAIArtSet->IntersectArtSet(textArtSet, foregroundArtSet, artSet);
	
	//LOOP THE ART SET
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	for ( int i=0 ; i < count ; i++ ) {
		AIArtHandle currArtHandle = NULL;
		sAIArtSet->IndexArtSet(artSet, i, &currArtHandle);
		
		AIArtHandle newArtHandle = NULL;
		
		sAITextFrame->CreateOutline(currArtHandle, &newArtHandle);
		sAIArt->UncheckedDisposeArt(currArtHandle);
		currArtHandle = NULL;
	}
	
	sAIArtSet->DisposeArtSet(&artSet); artSet = NULL;
	sAIArtSet->DisposeArtSet(&foregroundArtSet); foregroundArtSet = NULL;
	sAIArtSet->DisposeArtSet(&textArtSet); textArtSet = NULL;	
}



//*************************************************
// -openPlate:pathToFile
// Opens each Illustrator file, performs some checks, and outputs the PDF to the proper output folder
//*************************************************
- (void) openPlate:(NSString *)pathToFile
{
	ai::FilePath path((CFURLRef)[NSURL URLWithString:[[@"file://" stringByAppendingString:pathToFile] stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]]);
	AIDocumentHandle doc = NULL;
	if ( sAIDocumentList->Open(path, kAICMYKColorModel, kDialogOff, FALSE, &doc) )
	{
		throw [CException withCode:ecPlateNotFound];
	}
	originalDoc = doc;
}

//*************************************************
// -closeOpenFiles
// Closes any files that were opened
//*************************************************
- (void) closeOpenFiles
{
	if (originalDoc) {
		sAIDocumentList->Activate(originalDoc, TRUE);
		sAIDocument->SetDocumentModified(FALSE);
		sAIDocumentList->Close(originalDoc);
		originalDoc = NULL;
	}
	if (createdDoc) {
		sAIDocumentList->Activate(createdDoc, TRUE);
		sAIDocument->SetDocumentModified(FALSE);
		sAIDocumentList->Close(createdDoc);
		createdDoc = NULL;
	}
}
@end
