//
//  Dialog.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PlateItem.h"
#import "OutputFolderItem.h"
#import "PlantComboBoxCell.h"
#import "NSTreeController-DMExtensions.h"
#import "NSOutlineView-DMExtensions.h"


@interface Dialog : NSWindowController {
	IBOutlet NSButton *chooseButton;
	IBOutlet NSButton *exportButton;
	IBOutlet NSButton *cancelButton;
	IBOutlet NSButton *addButton;
	IBOutlet NSButton *removeButton;
	
	IBOutlet NSButton *showPrefsShtButton;
	
	IBOutlet NSComboBoxCell *plantCombo;

	IBOutlet NSTableView *tableView;
	IBOutlet NSArrayController *tvArrayController;
	NSMutableArray *thePlateList;
	
	IBOutlet NSOutlineView *plantPrefOutlineView;
	IBOutlet NSTreeController *ppTreeController;
	NSMutableArray *theTree;
	
	IBOutlet NSTextField *outputPathTextField;
	NSString *outputPathString;
	
	BOOL bBatchMode;
	BOOL outputToPlants;
	
	IBOutlet NSWindow *prefsSheet;
}


//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (NSOutlineView *) plantPrefOutlineView;
- (void) setPlantPrefOutlineView:(NSOutlineView *) ov;

- (NSTableView *) tableView;
- (void) setTableView:(NSTableView *) tv;

- (NSMutableArray *) thePlateList;
- (void) setThePlateList:(NSMutableArray *)a;

- (NSMutableArray *) theTree;
- (void) setTheTree:(NSMutableArray *)a;

- (NSString*) outputPathString;
- (void) setOutputPathString: (NSString *) theString;
- (ai::FilePath) outputPathAsAIFilePath;

- (BOOL) bBatchMode;
- (void) setBBatchMode:(BOOL) boolean;

- (BOOL) outputToPlants;
- (void) setOutputToPlants:(BOOL) boolean;
- (BOOL) isPlantManufacturingRootPath:(NSString *) path;

- (void)checkJobOptions;

//**************************************************************
//*********** Add/Remove PlateItems ****************************
//**************************************************************
- (IBAction)createPlateItem:(id)sender;
- (IBAction)deleteSelectedPlateItems:(id)sender;
- (IBAction)addPlateItem:(PlateItem*)aPlateItem;
- (IBAction)removePlateItem:(PlateItem*)aPlateItem;

- (void)insertObject:(PlateItem *)aPlateItem inThePlateListAtIndex:(unsigned int)index;
- (unsigned int)countOfThePlateList;

- (void)editFirstColumnOfRow:(NSNumber*)rowIndex;
- (void)editSecondColumnOfRow:(NSNumber*)rowIndex;

//**************************************************************
//*********** Add/Remove OutputFolderItems *********************
//**************************************************************
- (IBAction)importOutputFolderFile:(id)sender;
- (void)processOutputFolderFile:(NSString*)filename;
- (void)addOutputFolderItem:(OutputFolderItem*)aOutputFolderItem;
//- (IBAction)removeOutputFolderItem:(OutputFolderItem*)aOutputFolderItem;

//- (void)insertObject:(OutputFolderItem *)aOutputFolderItem inPlantOutputFolderListAtIndex:(unsigned int)index;
//- (unsigned int)countOfPlantOutputFolderList;


//**************************************************************
//*********** Button Handlers **********************************
//**************************************************************
- (IBAction)choose:(id)sender;
- (IBAction)export:(id)sender;
- (void) runMainExportLoop;
- (IBAction)cancel:(id)sender;
- (IBAction)showPrefsSheet:(id)sender;
- (IBAction)endPrefsSheet:(id)sender;

- (IBAction)plDoubleClick:(id)sender;
- (IBAction)plSingleClick:(id)sender;

- (IBAction)ofDoubleClick:(id)sender;

//**************************************************************
//*********** Dialog Handlers **********************************
//**************************************************************
- (void)show;
- (void)close;
- (id)init;
- (void)loadPreferences;
- (void)setDefaultPlants;
- (void)storePreferences;

//**************************************************************
//*********** MAKE PDF *****************************************
//**************************************************************
- (void) generatePDF:(PlateItem*)plate;

//**************************************************************
//*********** Delegates ****************************************
//**************************************************************
//End Modal Delegate
- (void)windowWillClose:(NSNotification *)notification;

//Window loaded Delegate
- (void)awakeFromNib;

//TableView Delegates
- (void)tableView:(NSTableView *)aTableView willDisplayCell:(id)aCell forTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;
- (BOOL)tableView:(NSTableView *)aTableView shouldEditTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;
- (void)controlTextDidEndEditing:(NSNotification *)aNotification;
- (void)tableViewSelectionDidChange:(NSNotification *)aNotification;
@end