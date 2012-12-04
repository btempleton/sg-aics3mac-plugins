//
//  Dialog.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Node.h"
#import "resultImageTransformer.h"
#import "validPathImageTransformer.h"

extern AIDictionaryRef dictMain;
extern Node* startNode;
extern AIDocumentHandle originalDoc;
extern AIDocumentHandle createdDoc;
extern OutputFolderItem* rootItem;

#import "Dialog.h"
Dialog *theDialog = nil;


@implementation Dialog

//****************************************************************************************************
// ************************** Getters/Setters *************************************************
//****************************************************************************************************
//*************************************************
// -tableView
// Getter
//*************************************************
- (NSTableView *) tableView
{
	return tableView;
}
//*************************************************
// -setTableView
// Setter
//*************************************************
- (void) setTableView:(NSTableView *) tv
{
	if (tv == tableView) {
		return;
	}
	[tv retain];
	[tableView release];
	tableView = tv;
}

//*************************************************
// -plantPrefOutlineView
// Getter
//*************************************************
- (NSOutlineView *) plantPrefOutlineView
{
	return plantPrefOutlineView;
}
//*************************************************
// -setTableView
// Setter
//*************************************************
- (void) setPlantPrefOutlineView:(NSOutlineView *) ov
{
	if (ov == plantPrefOutlineView) {
		return;
	}
	[ov retain];
	[plantPrefOutlineView release];
	plantPrefOutlineView = ov;
}



//*************************************************
// -thePlateList
// Getter
//*************************************************
- (NSMutableArray *) thePlateList
{
	return thePlateList;
}
//*************************************************
// -setThePlateList
// Setter
//*************************************************
- (void) setThePlateList:(NSMutableArray *)a
{
	if (a == thePlateList) {
		return;
	}
	[a retain];
	[thePlateList release];
	thePlateList = a;
}
//*************************************************
// -theTree
// Getter
//*************************************************
- (NSMutableArray *) theTree
{
	return theTree;
}
//*************************************************
// -setTheTree
// Setter
//*************************************************
- (void) setTheTree:(NSMutableArray *)a
{
	if (a == theTree) {
		return;
	}
	[a retain];
	[theTree release];
	theTree = a;
}


//*************************************************
// -outputPathString
// Getter
//*************************************************
- (NSString *) outputPathString
{
	return outputPathString;
}
//*************************************************
// -setOutputPathString
// Setter
//*************************************************
- (void) setOutputPathString:(NSString *)theString
{
	if (theString == outputPathString) {
		return;
	}
	
	[theString retain];
	[outputPathString release];
	outputPathString = theString;
	
	//Check if our output path is Plant Manufacturing so we can enable/disable plant column editing
	if (outputPathString == @"/Volumes/Plant_Manufacturing") {
		[theDialog setValue:[NSNumber numberWithBool:YES] forKey:@"outputToPlants"];
	} else {
		[theDialog setValue:[NSNumber numberWithBool:NO] forKey:@"outputToPlants"];
	}
}
//*************************************************
// -outputPathAsAIFilePath
// Setter
//*************************************************
- (ai::FilePath) outputPathAsAIFilePath {
	ai::UnicodeString us([[theDialog valueForKey:@"outputPathString"] UTF8String], kAIPlatformCharacterEncoding);
	ai::FilePath fp(us);
	return fp;
}
//*************************************************
// -bBatchMode
// Getter
//*************************************************
- (BOOL) bBatchMode
{
	return bBatchMode;
}
//*************************************************
// -setBBatchMode
// Setter
//*************************************************
- (void) setBBatchMode:(BOOL)boolean
{
	if (boolean == bBatchMode) {
		return;
	}
	bBatchMode = boolean;
}
//*************************************************
// -outputToPlants
// Getter
//*************************************************
- (BOOL) outputToPlants
{
	return outputToPlants;
}
//*************************************************
// -setOutputToPlants
// Setter
//*************************************************
- (void) setOutputToPlants:(BOOL)boolean
{
	if (boolean == outputToPlants) {
		return;
	}
	outputToPlants = boolean;
}

//*************************************************
// -isPlantManufacturingRootPath:path
// Setter
//*************************************************
- (BOOL) isPlantManufacturingRootPath:(NSString *) path
{
	if (![@"/Volumes/Plant_Manufacturing" caseInsensitiveCompare:path]) {
		return YES;
	} else {
		return NO;
	}
}


//****************************************************************************************************
// ************************** Plate List Add/Remove *************************************************
//****************************************************************************************************
//*************************************************
// -createPlateItem
// Adds a blank member to the plate list
//*************************************************
- (IBAction)createPlateItem:(id)sender
{
	PlateItem *newPlateItem = [[PlateItem alloc] init];
	[thePlateList addObject:newPlateItem];
	[newPlateItem release];
//	[tableView reloadData];
}

//*************************************************
// -deleteSelectedPlateItems
// Deletes items from the list
//*************************************************
- (IBAction)deleteSelectedPlateItems:(id)sender
{
	//Which row?
	NSIndexSet *rows = [tableView selectedRowIndexes];
	
	//Is it empty?
	if ([rows count] == 0) {
		NSBeep();
		return;
	}
	[thePlateList removeObjectsAtIndexes:rows];
//	[tableView reloadData];
}

//*************************************************
// -addPlateItem
// Adds a specified PlateItem to the plate list
//*************************************************
- (IBAction)addPlateItem:(PlateItem*)aPlateItem
{
	[self insertObject:aPlateItem inThePlateListAtIndex:[self countOfThePlateList]];
}

//*************************************************
// -removePlateItem
// Removes a specified PlateItem from the plate list
//*************************************************
- (IBAction)removePlateItem:(PlateItem*)aPlateItem
{
	[[self mutableArrayValueForKey:@"thePlateList"] removeObject:aPlateItem];
}


//****************************************************************************************************
// ************************** PlantOutputFolderList Add/Remove ***************************************
//****************************************************************************************************
//*************************************************
// -importOutputFolderFile
// Loads a list of output folders from a text file
//*************************************************
- (IBAction)importOutputFolderFile:(id)sender
{
/*	//Warn that this will overwrite the current files
	if ( NSAlertDefaultReturn == NSRunAlertPanel(nil, @"Are you sure you want to import new output folders? This will overwrite the current settings.", @"Yes", @"No", nil) ) {
		
		//If they said yes, pop the file chooser dialog
		// Create the File Open Dialog class.
		NSOpenPanel* openDlg = [NSOpenPanel openPanel];
		
		// Enable the selection of files in the dialog.
		[openDlg setCanChooseDirectories:NO];
		[openDlg setCanChooseFiles:YES];
		
		//Disable multiple selection
		[openDlg setAllowsMultipleSelection:NO];
		
		// Display the dialog. Send the file to our unarchive function.
		if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
		{
			[self processOutputFolderFile:[openDlg filename]];
		}
		
	}*/
	
	//Add our directories to the tree
	rootItem = [[OutputFolderItem alloc] initWithParent: nil
																 Children: nil
																 NodeName: @"NEW"
															   FolderPath: @""
																   IsRoot: YES];
	[ppTreeController insertObject:rootItem atArrangedObjectIndexPath:[NSIndexPath indexPathWithIndex:0]];
	
	OutputFolderItem* childItem = [[OutputFolderItem alloc] initWithParent: rootItem
																  Children: nil
																  NodeName: @"NTWG"
																FolderPath: @"/Volumes/Plant_Manufacturing/Townsend Files/Bus Stat to be plated"
																	IsRoot: NO];
	[childItem setIsRoot:NO];
//	[rootItem addChild:childItem];
//	unsigned int indexes[] = {0,0};
//	[ppTreeController insertObject:rootItem atArrangedObjectIndexPath:[NSIndexPath indexPathWithIndexes:indexes length:2]];
//	[childItem release];
	
/*	childItem = [[OutputFolderItem alloc] initWithParent: rootItem
												Children: nil
												NodeName: @"FSJLJ"
											  FolderPath: @"/Volumes/Plant_Manufacturing/Salt Lake City Files/BS to be Plated"
												  IsRoot: NO];
	[childItem setIsRoot:NO];
	[rootItem addChild:childItem];
//	[childItem release];
	
	
	childItem = [[OutputFolderItem alloc] initWithParent: rootItem
												Children: nil
												NodeName: @"JG:LSJ"
											  FolderPath: @"/Volumes/Plant_Manufacturing/Midland Files/BC to be Plated"
												  IsRoot: NO];
	[childItem setIsRoot:NO];
	[rootItem addChild:childItem];
	//[childItem release];
*/
}

//*************************************************
// -processOutputFolderFile:filename
// Turns the text file into our tree structure
//*************************************************
- (void)processOutputFolderFile:(NSString*)filename
{
	NSStringEncoding enc;
	NSString* f = [NSString stringWithContentsOfFile:filename usedEncoding:&enc error:nil];
	if (f) {
		//Init theTree
		[theDialog setValue:[[NSMutableArray alloc] init] forKey:@"theTree"];
		OutputFolderItem* realRoot = [[OutputFolderItem alloc] initWithParent: nil
																	 Children: nil
																	 NodeName: @"ROOT"
																   FolderPath: @""
																	   IsRoot: YES];
																	   
		NSArray* products = [f componentsSeparatedByString:@">"];
		NSEnumerator* productEnumerator = [products objectEnumerator];
		NSString* productFolders;
		
		while (productFolders = [productEnumerator nextObject]) {
			productFolders = [productFolders stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"\n"]];
			NSArray* plants = [productFolders componentsSeparatedByString:@"\n"];
			NSEnumerator* plantEnumerator = [plants objectEnumerator];
			NSString* plantNameAndFolder;
			
			OutputFolderItem* rootItem = nil;
			
			while (plantNameAndFolder = [plantEnumerator nextObject]) {
				NSArray* nameAndFolderPair = [plantNameAndFolder componentsSeparatedByString:@";"];
				NSEnumerator* nameAndFolderEnumerator = [nameAndFolderPair objectEnumerator];
				NSString* nameAndFolder;
				
				//Here is the product code
				if ([nameAndFolderPair count] == 1) {
					//Create the root
					rootItem = [[OutputFolderItem alloc] initWithParent: realRoot
															   Children: nil
															   NodeName: [nameAndFolderEnumerator nextObject]
															 FolderPath: @""
																 IsRoot: NO];
				}
				//Here is Plant/Folder pair
				else {
					//Create the children of the root
					while (nameAndFolder = [nameAndFolderEnumerator nextObject]) {
						OutputFolderItem* childItem = [[OutputFolderItem alloc] initWithParent: rootItem
																					  Children: nil
																					  NodeName: nameAndFolder
																					FolderPath: [nameAndFolderEnumerator nextObject]
																						IsRoot: NO];
						[rootItem addChild:childItem];
						[childItem release];
						
					}
				}
			}
			
			if (rootItem) {
				[realRoot addChild:rootItem];
				[rootItem release];
			}
		}
		
		[theDialog addOutputFolderItem:realRoot];
		[realRoot release];
	}
}







//*************************************************
// -addOutputFolderItem
// Adds a specified outputfolderitem to the list
//*************************************************
- (void)addOutputFolderItem:(OutputFolderItem*)aOutputFolderItem
{
	if (theTree) {
		[theDialog willChangeValueForKey:@"theTree"];
		[theTree addObject:aOutputFolderItem];
		[theDialog didChangeValueForKey:@"theTree"];
	} else {
		[theDialog setTheTree:[NSMutableArray arrayWithObject:aOutputFolderItem]];
	}	
	[plantPrefOutlineView reloadData];
}



//****************************************************************************************************
// ************************** Button handlers *************************************************
//****************************************************************************************************
//*************************************************
// -choose
// Handles the output folder selection
//*************************************************
- (IBAction)choose:(id)sender
{
	ai::FilePath defaultPath(ai::UnicodeString("/Volumes/Plant_Manufacturing"));
	SPPlatformFileSpecification defaultStartLoc, chosenPath;
	defaultPath.GetAsSPPlatformFileSpec( defaultStartLoc );
	
	//Pop choose dialog box
	if ( sADMBasic->StandardGetDirectoryDialog("Choose output folder:", &defaultStartLoc, &chosenPath) ) {
		ai::FilePath tpath;
		tpath.SetFromSPFileSpec(chosenPath);
		
		ai::UnicodeString pathUS = tpath.GetFullPath();
		char* buffer = new char[pathUS.length() + 3];
		pathUS.getToBuffer(buffer, pathUS.length()+3, kAIUTF8CharacterEncoding);
		
		[theDialog setValue:[[NSString alloc] initWithCString:buffer encoding:4] forKey:@"outputPathString"]; //UTF8 encoding
		
		delete[] buffer;
	}
	[self setValue:[NSNumber numberWithBool:[self isPlantManufacturingRootPath:[self outputPathString]]] forKey:@"outputToPlants"];
}


//*************************************************
// -export
// Handles the Export button... perform some checks, then start the main loop on a new thread
//*************************************************
- (IBAction)export:(id)sender
{
	//Force any editing to complete
	[[sender window] makeFirstResponder:nil];
	
	//If we don't have an output path, they will need to choose one
	if ( ![theDialog outputPathString] ) {
		NSRunAlertPanel(@"Error!", 
                        @"You must choose an output folder.",
                        @"OK", nil, nil);
		return;
	}
	
	//Go through our plate list and remove any entries that don't have a plate number entered
	//We'll also use this opportunity to reset any result codes that may have been set
	NSEnumerator *enumerator = [[self thePlateList] objectEnumerator];
	PlateItem* anObject;
	
	while (anObject = [enumerator nextObject]) {
		if ( [@"" caseInsensitiveCompare:[anObject result]] ) {
			[anObject setValue:@"" forKey:@"result"];
		}
		if (! [[anObject plateNumber] length]) {
			[self removePlateItem:anObject];
		}
	}
	
	
	//Check to make sure our joboptions file is the most current.
	try {
		[theDialog checkJobOptions];
	}
	catch(CException* e) {
		NSRunAlertPanel(@"Error!", 
                        @"There was a problem finding a required PDF options file.",
                        @"OK", nil, nil);
		return;		
	}
	
	[self runMainExportLoop];
	
//	[[self tableView] reloadData];
}

//*************************************************
// -runMainExportLoop
// This is the main export loop, goes through the plates in the list and copies/pdfs them
// We'll check in here to see if the cancel button has been clicked so we can clean stuff up and stop gracefully
//*************************************************
- (void) runMainExportLoop
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	
	//Reset the enumerator and start the loop
	NSEnumerator *enumerator = [[self thePlateList] objectEnumerator];
	PlateItem* anObject;

	while (anObject = [enumerator nextObject]) {
		try {
			BOOL atLeastOneFileFound = NO;
			//Check that we have a valid plate number
			if (! [anObject isValidPlateNumber:[anObject plateNumber]]) {
				throw [CException withCode:ecBadPlate];
			}
			//Check that we have a valid plant, if we need one
			if ( ([self outputToPlants]) && (![anObject isValidPlant:[anObject plant]]) ) {
				throw [CException withCode:ecBadPlant];
			}
			
			if ([self bBatchMode]) {
				[anObject fileToWIP];
				[anObject loadFonts];
				
				//Get a list of each AI file in the folder (non-recursive)
				//Then open each file and generate the PDF for each
				
				NSArray *dirArray = [MyFileManager directoryContentsAtPath:[anObject createWIPPath]];
				NSEnumerator *dirEnum = [dirArray objectEnumerator];
				
				NSString* file;
				while (file = [dirEnum nextObject]) {
					FSRef fsRefToItem;
					FSPathMakeRefWithOptions( (const UInt8 *)[[[anObject createWIPPath] stringByAppendingPathComponent:file] fileSystemRepresentation], kFSPathMakeRefDefaultOptions, &fsRefToItem, NULL );
					
					CFStringRef itemUTI = NULL;
					LSCopyItemAttribute( &fsRefToItem, kLSRolesAll, kLSItemContentType, (CFTypeRef*)&itemUTI );
					
					if (UTTypeConformsTo(itemUTI, CFSTR("com.adobe.illustrator.ai-image"))) {
						//Check to make sure our plate number is in the filename (so we don't get other miscellaneous art files, etc.)
						NSRange range = [file rangeOfString:[anObject plateNumber] options:NSCaseInsensitiveSearch];
						if (range.location != NSNotFound) {
							atLeastOneFileFound = YES;
							
							[anObject openPlate:[[anObject createWIPPath] stringByAppendingPathComponent:file]];
							
							//Create a timer to check that all fonts have been loaded, sometimes it takes a little while to recognize the font has been loaded,
							//so if there's a missing font the first time, we'll close the file, wait a little while, then try again
							if (![anObject allFontsLoaded]) {
								[NSThread sleepUntilDate:[NSDate dateWithTimeIntervalSinceNow:10]];
								
								[anObject closeOpenFiles];
								[anObject openPlate:[[anObject createWIPPath] stringByAppendingPathComponent:file]];
								if (![anObject allFontsLoaded]) {
									throw [CException withCode:ecMissingFont];
								}
							}
							
							[self generatePDF:anObject];
						}
					}
				}
				if (!atLeastOneFileFound)
				{
					throw [CException withCode:ecNoIllustratorFile];
				}
			}
			//If we're not in batch mode, the plate is already open, so we can just make the pdf
			else {
				//TODO: May want to check fonts and images here too just to be sure
				[self generatePDF:anObject];
			}
			
			//When we're done....
			if ([self bBatchMode]) {
				[anObject cleanUpTempFonts];
				[anObject closeOpenFiles];
			}
			[anObject setResultOK];
			
			//Dismiss the dialog if we're in single plate mode
			if (![self bBatchMode]) {
				[self close];
			}
			
//			[[self tableView] reloadData];
		}
		
		//If there was a problem.....
		catch(CException* e) {
			[anObject setResultBad:e];
//			[[self tableView] reloadData];
			
			if ([self bBatchMode]) {
				[anObject closeOpenFiles];
				[anObject cleanUpTempFonts];
				[anObject cleanUpWIPFiles];
			}			
		}
	}

	[MyFileManager release];
	[pool release];
}


//*************************************************
// -generatePDF
// Opens each Illustrator file, performs some checks, and outputs the PDF to the proper output folder
//*************************************************
- (void) generatePDF:(PlateItem*)plate
{
	//Store our layer settings
	[plate storeLayerSettings];
	
	[plate printToPDF:self];
	
	//Reset our layer settings
	[plate recallLayerSettings];
}


//*************************************************
// -cancel
// Handles the Cancel button
//*************************************************
- (IBAction)cancel:(id)sender
{	
	[self close];
}


//*************************************************
// -plDoubleClick
// Handles a double click on the Plate List TableView
//*************************************************
- (IBAction)plDoubleClick:(id)sender
{	
	NSTableHeaderView * header = [sender headerView];
	NSEvent *  event = [NSApp currentEvent];
	NSPoint    location = [event locationInWindow];
	location = [[header superview] convertPoint: location fromView: nil];
	if ([header hitTest: location])
	{
		//NSLog(@"In header view");
	}
	else
	{
		if([sender clickedRow] == -1) {
			return;
		} else {
			//Turn clickedRow into the PlateItem it represents
			PlateItem* clickedItem = [[tvArrayController arrangedObjects] objectAtIndex:[sender clickedRow]];
			
			//Check if there's an error logged for the clicked row
			if (![[clickedItem result] caseInsensitiveCompare:@"ERR"]){
				[clickedItem displayErrorMessage];
			}
		}
	}
}

//*************************************************
// -plSingleClick
// Handles a single click on the Plate List TableView
//*************************************************
- (IBAction)plSingleClick:(id)sender
{
/*	NSTableHeaderView * header = [sender headerView];
	NSEvent *  event = [NSApp currentEvent];
	NSPoint    location = [event locationInWindow];
	location = [[header superview] convertPoint: location fromView: nil];
	if ([header hitTest: location])
	{
		//NSLog(@"In header view");
	}
	else
	{
		if([sender clickedRow] == -1) {
			return;
		} else {
			//Turn clickedRow into the PlateItem it represents
			PlateItem* clickedItem = [[tvArrayController arrangedObjects] objectAtIndex:[sender clickedRow]];
			if ([self outputToPlants]) {
				[theDialog setValue:[theDialog getPlantArrayFromPlateNumber:[clickedItem plateNumber]] forKey:@"thePlantList"];
			}
		}
	}
*/	
	//We only care if there is nothing in the list, then we'll add one if the table is clicked
	if ([self countOfThePlateList] == 0) {
		[self insertObject:[PlateItem createBlankItem] inThePlateListAtIndex:[self countOfThePlateList]];
		
		[[self tableView] editColumn:[[self tableView] columnWithIdentifier:@"plateColumnID"] row:([self countOfThePlateList]-1) withEvent:nil select:NO];
	}
}


//*************************************************
// -ofDoubleClick
// Handles a double click on the Output Folder outline view
//*************************************************
- (IBAction)ofDoubleClick:(id)sender
{	
	if([sender clickedRow] == -1) {
		return;
	} else {
		//Turn clickedRow into the OutputFolderItem it represents
		OutputFolderItem* clickedItem = [sender realItemForOpaqueItem:[sender itemAtRow:[sender clickedRow]]];
		
		//Check if there's a folder path for this row, so we don't try to change folder path for a "Product" line
		if ([[clickedItem folderPath] length]){
			[clickedItem changeFolderPath];
		}
	}
}


//****************************************************************************************************
// ************************** DIALOG LEVEL CALLBACKS *************************************************
//****************************************************************************************************

//*************************************************
// -show
// Displays the dialog
//*************************************************
- (void)show
{
    assert (self != nil); // or other error handling
	
	// Acquire suites to stay in memory
	acquireSuites( g->basic );
	
	//Initialize our doc vars
	originalDoc = NULL;
	createdDoc = NULL;
	
	//Init vars stored in AI Preferences
	[self loadPreferences];


	//Init the plate list
	NSMutableArray * array = [[NSMutableArray alloc] init];
	[theDialog setValue:array forKey:@"thePlateList"];
	[array release];
	
	//Init batchMode and add current document to thePlateList
	long docCount = 0;
	sAIDocumentList->Count(&docCount);
	try {
		if (docCount) {
			[theDialog setValue:[NSNumber numberWithBool:NO] forKey:@"bBatchMode"];
			sAIDocument->GetDocument(&(originalDoc));
			
			//Add our current plate to the list
			//Retrieve the dictionary for this file
			sAIDocument->GetDictionary(&dictMain);
			
			
			//Check whether the updater was run
			if ( !sAIDictionary->IsKnown(dictMain, sAIDictionary->Key("BSTATMU_VERSION")) ) {
				throw [CException withCode:ecUpdaterNotRun];
			}
			
			SetUpNodes();
			if (startNode) {
				//Add the current document's plate to the list
				PlateItem* newItem = [[PlateItem alloc] init];
				[newItem setPlateNumber:[NSString stringWithCString:startNode->p->PlateNumberStr().c_str() encoding:NSUTF8StringEncoding]];
				[theDialog addPlateItem:newItem];
				[newItem release];
			}
			CleanUpNodes();
			
			
		} else {
			//Enable plate entry
			[theDialog setValue:[NSNumber numberWithBool:YES] forKey:@"bBatchMode"];
		}
	}
	catch(CException* e) {
		sAIDictionary->Release(dictMain);
		NSRunAlertPanel(@"Error!", 
                        [e getDescription],
                        @"OK", nil, nil);
		return;
	}
	
	//Start the modal loop
	NSWindow* w = [self window];
	[NSApp runModalForWindow:w];
	
	
}

//*************************************************
// -close
// Closes the dialog
//*************************************************
- (void)close
{
	//[thePlateList release];
	originalDoc = NULL;
	createdDoc = NULL;

	//theDialog = nil;
	
	// release suites from memory
	releaseSuites( g->basic );
	
    [[self window] performClose:self];
}

//*************************************************
// -init
// Extracts our nib and sends the handle to our Dialog window controller back
//*************************************************
- (id)init {
    if (self = [super initWithWindowNibName:@"pPDFcocoa"]) {
		
		//Init Value Transformer
		resultImageTransformer* riTrans = [[[resultImageTransformer alloc] init] autorelease];
		[resultImageTransformer setValueTransformer:riTrans	forName:@"resultImageTransformer"];
		
		validPathImageTransformer* vpTrans = [[[validPathImageTransformer alloc] init] autorelease];
		[validPathImageTransformer setValueTransformer:vpTrans	forName:@"validPathImageTransformer"];
	}
    return self;
}


//*************************************************
// -loadPreferences
// Checks the AI Preferences file and sets up our dialog vars stored there
//*************************************************
- (void) loadPreferences
{
	[theDialog setDefaultPlants];
	
	//This should overwrite our defaults with what is in the Preferences
	//Get the output folder stuff to a memory block and store that
	long byteLength = 0;
	sAIPreference->GetIntegerPreference("PrintToPDF", "OutputFolderByteLength", &byteLength);
	void* theData = nil;
	sAIBlock->AllocateBlock(byteLength, &theData);
	if (byteLength) {
		sAIPreference->GetBlockPreference("PrintToPDF", "OutputFolderTree", theData, byteLength);
		NSData* tdata = [NSData dataWithBytes:theData length:byteLength];
		[theDialog setTheTree:[NSKeyedUnarchiver unarchiveObjectWithData:tdata]];
	}
		
	//Init outputPathString and outputToPlants
	//We have to check the preferences for this plugin and see if there is a path stored there
	ai::FilePath tpath;
	if (kNoErr == sAIPreference->GetFilePathSpecificationPreference("PrintToPDF", "OutputFolder", tpath) ) {
		if ( tpath.Exists(TRUE) ) {
			//Convert tpath to a string
			ai::UnicodeString pathUS = tpath.GetFullPath();
			char* buffer = new char[pathUS.length() + 3];
			pathUS.getToBuffer(buffer, pathUS.length() + 3, kAIUTF8CharacterEncoding);
			[theDialog setValue:[NSString stringWithCString:buffer encoding:NSUTF8StringEncoding] forKey:@"outputPathString"]; //UTF8 encoding
			delete[] buffer;
		} else {
			//Filepath no longer exists
			[theDialog setValue:nil forKey:@"outputPathString"];
		}
	} else {
		//Else there was no preference stored. They will be required to select an output folder.
		[theDialog setValue:nil forKey:@"outputPathString"];
	}
	[self setValue:[NSNumber numberWithBool:[self isPlantManufacturingRootPath:[self outputPathString]]] forKey:@"outputToPlants"];
}

//*************************************************
// -setDefaultPlants
// Sets up "theTree" with our default list of output folders, this will get overwritten with whatever was stored
// in ai preferences.
//*************************************************
- (void) setDefaultPlants
{
	//Init theTree
	[theDialog setValue:[[NSMutableArray alloc] init] forKey:@"theTree"];
	
	//Add our directories to the tree
	OutputFolderItem* rootItem = [[OutputFolderItem alloc] initWithParent: nil
																Children: nil
																NodeName: @"BS"
															  FolderPath: @""
																  IsRoot: YES];
	
	OutputFolderItem* childItem = [[OutputFolderItem alloc] initWithParent: rootItem
											  Children: nil
											  NodeName: @"Townsend"
											FolderPath: @"/Volumes/Plant_Manufacturing/Townsend Files/Bus Stat to be plated"
												IsRoot: NO];
	[childItem setIsRoot:NO];
	[rootItem addChild:childItem];
	[childItem release];
	
	childItem = [[OutputFolderItem alloc] initWithParent: rootItem
												Children: nil
												NodeName: @"Salt Lake City"
											  FolderPath: @"/Volumes/Plant_Manufacturing/Salt Lake City Files/BS to be Plated"
												  IsRoot: NO];
	[childItem setIsRoot:NO];
	[rootItem addChild:childItem];
	[childItem release];


	childItem = [[OutputFolderItem alloc] initWithParent: rootItem
												Children: nil
												NodeName: @"Midland"
											  FolderPath: @"/Volumes/Plant_Manufacturing/Midland Files/BC to be Plated"
												  IsRoot: NO];
	[childItem setIsRoot:NO];
	[rootItem addChild:childItem];
	[childItem release];
	

	[theDialog addOutputFolderItem:rootItem];
	[rootItem release];
}



//*************************************************
// -storePreferences
// Checks the AI Preferences file and sets up our dialog vars stored there
//*************************************************
- (void) storePreferences
{
	sAIPreference->PutFilePathSpecificationPreference("PrintToPDF", "OutputFolder", [theDialog outputPathAsAIFilePath]);
	
	//Get the output folder stuff to a memory block and store that
	NSData* myData = [NSKeyedArchiver archivedDataWithRootObject:theTree];
	
	sAIPreference->PutBlockPreference("PrintToPDF", "OutputFolderTree", const_cast<void *>([myData bytes]), [myData length]);
	sAIPreference->PutIntegerPreference("PrintToPDF", "OutputFolderByteLength", [myData length]);
}	


//*************************************************
// -windowWillClose
// Stops the modal loop when the dialog closes
//*************************************************
- (void)windowWillClose:(NSNotification *)notification
{
	[NSApp stopModalWithCode:NSCancelButton];
}


//*************************************************
// -awakeFromNib
// Initialize anything that relies on theDialog being completely inititalized
// This only runs once, the first time NSWindowController's window is accessed
//*************************************************
- (void)awakeFromNib
{	
	[[self tableView] setDoubleAction:@selector(plDoubleClick:)];
	[[self tableView] setAction:@selector(plSingleClick:)];
	
	[[self plantPrefOutlineView] setDoubleAction:@selector(ofDoubleClick:)];
	[[self plantPrefOutlineView] setTarget:self];
}



//*************************************************
// -tableView:aTableView shouldEditTableColumn:aTableColumn row:rowIndex
// If the user tries to edit a column, this returns whether they can or not
//*************************************************
- (BOOL)tableView:(NSTableView *)aTableView shouldEditTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	if (![[aTableColumn identifier] compare:@"plateColumnID"]) {
		//If we already have a result, we don't want the user to change the plate number anymore
		if ( !([[[[tvArrayController arrangedObjects] objectAtIndex:rowIndex] result] compare:@"OK!"]) || !([[[[tvArrayController arrangedObjects] objectAtIndex:rowIndex] result] compare:@"ERR"])) {
			//We'll select the row instead of editing
			[aTableView selectRowIndexes:[NSIndexSet indexSetWithIndex:rowIndex] byExtendingSelection:NO];
			return NO;
		//Otherwise, we'll just return the current editable value
		} else {
			return [aTableColumn isEditable];
		}
	} else {
		return [aTableColumn isEditable];
	}
}



//*************************************************
// -controlTextDidEndEditing:aNotification
// Called when the user is done editing a cell
//*************************************************
- (void)controlTextDidEndEditing:(NSNotification *)aNotification
{
	//If editing was ended using Return or Tab key
	if ([[[aNotification userInfo] objectForKey:@"NSTextMovement"] unsignedIntValue] == NSReturnTextMovement || [[[aNotification userInfo] objectForKey:@"NSTextMovement"] unsignedIntValue] == NSTabTextMovement)
	{
		//If this was the last row in our table
		if ( ([[aNotification object] numberOfRows] -1) == [[aNotification object] editedRow] )
		{
			//And either: output to plant mode is not enabled, and we are in the plate number cell, or
			//            output to plant mode is enabled, and we are in the plant cell
			if ( (![self outputToPlants]) && ([[aNotification object] editedColumn] == [[self tableView] columnWithIdentifier:@"plateColumnID"]) ||
				([self outputToPlants]) && ([[aNotification object] editedColumn] == [[self tableView] columnWithIdentifier:@"plantColumnID"]) )
			{
				//Add a new row and start editing the first cell
				[self insertObject:[PlateItem createBlankItem] inThePlateListAtIndex:[self countOfThePlateList]];
				
				[[self tableView] selectRowIndexes:[NSIndexSet indexSetWithIndex:([self countOfThePlateList]-1)] byExtendingSelection:NO];
				
				[ self performSelector:@selector(editFirstColumnOfRow:) withObject:[NSNumber numberWithInt:([self countOfThePlateList]-1)] afterDelay:0.0 ];
			}
		}
	}
}


//*************************************************
// -tableViewSelectionDidChange:aNotification
// Called when the selection in our tableview changes
//*************************************************
- (void)tableViewSelectionDidChange:(NSNotification *)aNotification
{   
	//If we don't have a valid plate number, start editing plate column
	if (![[[tvArrayController arrangedObjects] objectAtIndex:[[aNotification object] selectedRow]] isValidPlateNumber:[[[tvArrayController arrangedObjects] objectAtIndex:[[aNotification object] selectedRow]] plateNumber]]) {
		[self editFirstColumnOfRow:[NSNumber numberWithInt:[[aNotification object] selectedRow]]];
	}
	//Or if we are outputting to plants, and we don't have a valid plant, edit that
	else if (( [self outputToPlants]) && (![[[tvArrayController arrangedObjects] objectAtIndex:[[aNotification object] selectedRow]] isValidPlant:[[[tvArrayController arrangedObjects] objectAtIndex:[[aNotification object] selectedRow]] plant]]) ) {
		[self editSecondColumnOfRow:[NSNumber numberWithInt:[[aNotification object] selectedRow]]];
	}
}


//*************************************************
// -tableView:willDisplayCell:forTableColumn:row:
// We'll use this to set up our plant list cell based on what is in the plate number cell
//*************************************************
- (void)tableView:(NSTableView *)aTableView willDisplayCell:(id)aCell forTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	//If they edited the Plate Number column, we will figure out which Product was entered and fill the plant list with the valid
	// plants for that product
	if ( aTableColumn == [aTableView tableColumnWithIdentifier:@"plantColumnID"])
	{
		[aCell removeAllItems];
		[aCell addItemsWithObjectValues:[[[tvArrayController arrangedObjects] objectAtIndex:rowIndex] plantListArray]];
	}
}

//*************************************************
// -countOfThePlateList
// PlateList Delegate
//*************************************************
- (unsigned int)countOfThePlateList {
    return [thePlateList count];
}

//*************************************************
// -insertObject:inThePlateListAtIndex
// PlateList Delegate
//*************************************************
- (void)insertObject:(PlateItem *)anObject inThePlateListAtIndex:(unsigned int)idx  {
	[self willChangeValueForKey:@"thePlateList"];
    [thePlateList insertObject:anObject atIndex:idx];
	[self didChangeValueForKey:@"thePlateList"];
}


//*************************************************
// -editFirstColumnOfRow:rowIndex
// Starts text editing in Plate Number column of the passed row
//*************************************************
- (void)editFirstColumnOfRow:(NSNumber*)rowIndex
{
	[[self tableView] editColumn:[[self tableView] columnWithIdentifier:@"plateColumnID"] row:[rowIndex intValue] withEvent:nil select:YES];
}

- (void)editSecondColumnOfRow:(NSNumber*)rowIndex
{
	[[self tableView] editColumn:[[self tableView] columnWithIdentifier:@"plantColumnID"] row:[rowIndex intValue] withEvent:nil select:YES];
}


//*************************************************
// -checkJobOptions
// Checks to make sure the job options files in our Illustrator directory are the most current,
// Gives the user a chance to update them if they are not.
//*************************************************
- (void)checkJobOptions
{
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	
	NSString* library_path = [NSSearchPathForDirectoriesInDomains (NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	NSString* pathToPDFPresetFolder = [library_path stringByAppendingPathComponent:@"/Application Support/Adobe/Adobe PDF/Settings"];
	NSString* pathToUserBStatJobOptions = [pathToPDFPresetFolder stringByAppendingPathComponent:@"/Bstat Preset.joboptions"];
	
	NSString* pathToGeneralResourcesAIPluginsFolder = @"/Volumes/WIP/WIP/General Resources/AI PLUGINS";
	NSString* pathToGeneralResourcesBStatJobOptions = [pathToGeneralResourcesAIPluginsFolder stringByAppendingPathComponent:@"/Bstat Preset.joboptions"];
	
	
	if ([MyFileManager fileExistsAtPath:pathToUserBStatJobOptions]) {
		//If the file does exist, we'll compare the date to the one on General Resources, and ask the user if they want to replace if that's newer
		NSDictionary* userFileAttr = [MyFileManager fileAttributesAtPath:pathToUserBStatJobOptions traverseLink:NO];
		NSDictionary* grFileAttr = [MyFileManager fileAttributesAtPath:pathToGeneralResourcesBStatJobOptions traverseLink:NO];
		
		if ( [[userFileAttr valueForKey:NSFileCreationDate] compare:[grFileAttr valueForKey:NSFileCreationDate]] == NSOrderedAscending ) {
			if ( NSRunAlertPanel(@"Attention!", 
				 @"Your PDF settings are not up to date. Would you like to update them now?",
				 @"Yes", @"No", nil) == NSAlertAlternateReturn) {
				[MyFileManager release];
				return;
			}
		}
	}

	//If the file doesn't exist there, or if the user said yes, we need to copy the one from General Resources
	NSString* src = pathToGeneralResourcesBStatJobOptions;
	NSString* dst = pathToPDFPresetFolder;
	OSStatus error = FSPathCopyObjectSync([src fileSystemRepresentation], [dst fileSystemRepresentation], NULL, NULL, kFSFileOperationOverwrite);
	if (error) {
		[MyFileManager release];
		throw [CException withCode:ecNoJobOptions];			
	}
	
	[MyFileManager release];
}

//*************************************************
// -showPrefsSheet
// Displays the preferences sheet
//*************************************************
- (IBAction)showPrefsSheet:(id)sender
{
	[NSApp beginSheet:prefsSheet
	   modalForWindow:[self window]
		modalDelegate:nil
	   didEndSelector:NULL
		  contextInfo:NULL];
}

//*************************************************
// -endPrefsSheet
// Closes the preferences sheet
//*************************************************
- (IBAction)endPrefsSheet:(id)sender
{
	//Store our preferences
	[self storePreferences];
	
	//Return to normal event handling
	[NSApp endSheet:prefsSheet];
	
	//Hide the sheet
	[prefsSheet orderOut:sender];
}



@end
