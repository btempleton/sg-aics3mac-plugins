//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Tutorial/Source/Tutorial.cpp $
//
//  $Revision: #19 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#ifdef MAC_ENV   
#include <Types.h>   
#endif 

#include "TutorialID.h"

// System Suites
#include "AITypes.h"
#include "AIPlugin.h"
#include <string.h>

// General Suites
#include "SPBlocks.h"
#include "AIArt.h"
#include "AIPath.h"
#include "AIRealMath.h"
#include "AIRandom.h"
#include "AIDocumentView.h"
#include "AIMatchingArt.h"
#include "AIMdMemory.h"

// Plug-in Types
#include "AIFilter.h"
#include "AITool.h"
#include "AIActionManager.h"
#include "AIMenu.h"

// ADM Suites
#include "ADMBasic.h"
#include "ADMDialog.h"
#include "ADMItem.h"
#include "ADMIcon.h"

// SDK
#include "SDKAboutPluginsHelper.h"

/////////////////////////////////////////
//
// Declarations and constants
//
/////////////////////////////////////////

/** This plug-in's globals.
*/
typedef struct {
	AIFilterHandle		filterVariation1;
	AIToolHandle		toolVariation1;
	AIMenuItemHandle	aboutPluginMenu;
} Globals;

/** Identifies a suite used by this plug-in.
	@see AcquireSuites() and ReleaseSuites()
*/
typedef struct {	
	char *name;		
	long version;
	void **suite;
} MySuiteImport;

/** Parameters for this plug-in's filter.
*/
typedef struct {
	ASInt32 corners;	// number of corners on the polygon
	ASInt32 size;		// the maximum size, in points
	// or any other values your filter needs...
} MyFilterParameters;

const MyFilterParameters kDefaultFilterParameters = {7, 72};
const MyFilterParameters kMinFilterParameters = {1, 72};
const MyFilterParameters kMaxFilterParameters = {100, 7200};

/////////////////////////////////////////
//
// Function prototypes
//
/////////////////////////////////////////

// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

/** Plug-in entry point.
*/
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message);

// Tell Xcode to return to default visibility for symbols
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

/** Handles startup.
*/
static AIErr StartupPlugin( SPInterfaceMessage* message );

/** Handles shutdown.
*/
static AIErr ShutdownPlugin( SPInterfaceMessage* message );

/** Handles reload.
*/
static AIErr ReloadPlugin( SPAccessMessage* message );

/** Handles unload.
*/
static AIErr UnloadPlugin( SPAccessMessage* message );


/** Aquires suites used by this plug-in.
	@see imports
*/
static AIErr AcquireSuites( SPBasicSuite* sSPBasic );

/** Releases suites used by this plug-in.
	@see imports
*/
static AIErr ReleaseSuites( SPBasicSuite* sSPBasic );


/** Adds this plug-in's menu items to Illustrator.
*/
static AIErr AddMenu ( SPInterfaceMessage* message );

/** Handles this plug-in's menu items.
*/
static AIErr GoMenu ( AIMenuMessage* message );

/** Adds this plug-in's filter to Illustrator.
*/
static AIErr AddFilter ( SPInterfaceMessage* message );

/** Prompts the user for the parameters used by this plug-in's filter.
*/
static AIErr GetFilterParameters( AIFilterMessage* message );

/** Initializes the parameter dialog for this plug-in's filter.
*/
static ASErr ASAPI InitializeFilterDialog(ADMDialogRef dialog);

/** Handles dismissal of the parameter dialog for this plug-in's filter.
*/
static void ASAPI HandleFilterDialogOKButton(ADMItemRef item, ADMNotifierRef notifier);

/** Applies this plug-in's filter.
*/
static AIErr GoFilter( AIFilterMessage* message );


/** Adds this plug-in's tool to Illustrator.
*/
static AIErr AddTool( SPInterfaceMessage* message );

/** Handles mouse down messages for this plug-in's tool.
*/
static AIErr ToolMouseDown( AIToolMessage* message );


/** Adds this plug-in's action event to Illustrator.
*/
static AIErr AddAction ( SPInterfaceMessage* message );

/** Records this plug-in's filter as an action event.
*/
static AIErr RecordFilterAction(const MyFilterParameters& myParameters);

/** Executes this plug-in's filter as an action event.
*/
static AIErr DoAction( DoActionMessage* message);


/** Converts given C string into a Pascal string.
*/
static void CStrToPStr(char *s, unsigned long len);

/////////////////////////////////////////
//
// Global data
//
/////////////////////////////////////////
extern "C" {
	Globals*				g = nil;
	AIFilterSuite*			sAIFilter = nil;
	SPBlocksSuite*			sSPBlocks = nil;
	AIArtSuite*				sAIArt = nil;
	AIPathSuite*			sAIPath = nil;
	AIRealMathSuite*		sAIMath = nil;
	AIRandomSuite*			sAIRandom = nil;
	AIDocumentViewSuite*	sAIDocumentView = nil;
	AIToolSuite*			sAITool = nil;
	AIMatchingArtSuite*		sAIMatchingArt = nil;
	AIActionManagerSuite*	sAIActionManager = nil;
	AIMenuSuite*			sAIMenu = nil;
	AIUnicodeStringSuite*	sAIUnicodeString = nil;
	ADMBasicSuite10*		sADMBasic = nil;
	ADMDialogSuite*			sADMDialog = nil;
	ADMItemSuite7*			sADMItem = nil;
	ADMIconSuite*			sADMIcon = nil;
	AIMdMemorySuite*		sAIMDMemory = nil;
};

// This is used by AcquireSuites() and ReleaseSuites()
MySuiteImport imports[] = {
	kAIFilterSuite, kAIFilterVersion, (void**)&sAIFilter,
	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kAIPathSuite, kAIPathVersion, (void**)&sAIPath,
	kAIRealMathSuite, kAIRealMathVersion, (void**)&sAIMath,
	kAIRandomSuite, kAIRandomVersion, (void**)&sAIRandom,
	kAIDocumentViewSuite, kAIDocumentViewVersion, (void**)&sAIDocumentView,
	kAIToolSuite, kAIToolVersion, (void**)&sAITool,
	kAIMatchingArtSuite, kAIMatchingArtVersion, (void**)&sAIMatchingArt,
	kAIActionManagerSuite, kAIActionManagerSuiteVersion, (void**)&sAIActionManager,
	kAIMenuSuite, kAIMenuSuiteVersion, (void**)&sAIMenu,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, (void**) &sAIUnicodeString,
	kADMBasicSuite, kADMBasicSuiteVersion10, (void**)&sADMBasic,
	kADMDialogSuite, kADMDialogSuiteVersion, (void**)&sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, (void**)&sADMItem,
	kADMIconSuite, kADMIconSuiteVersion, (void**)&sADMIcon,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, (void**)&sAIMDMemory,
};

/////////////////////////////////////////
//
// Plug-in entry point.
//
/////////////////////////////////////////

/* Handles message actions for this plug-in.
*/
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	ASErr error = kASNoError;
	if ( strcmp( caller, kSPAccessCaller ) == 0 ) {
		if ( strcmp( selector, kSPAccessUnloadSelector ) == 0 )
			error = UnloadPlugin( ( SPAccessMessage* )message );
		else if ( strcmp( selector, kSPAccessReloadSelector ) == 0 )
			error = ReloadPlugin( ( SPAccessMessage* )message );

	} 
	else if ( strcmp( caller, kSPInterfaceCaller ) == 0 ) {
		if ( strcmp( selector, kSPInterfaceStartupSelector ) == 0 )
			error = StartupPlugin( ( SPInterfaceMessage* )message );
		else if ( strcmp( selector, kSPInterfaceShutdownSelector ) == 0 )
			error = ShutdownPlugin( ( SPInterfaceMessage* )message );

	} 
	else if ( strcmp( caller, kCallerAIMenu ) == 0  ) {
		if ( strcmp( selector, kSelectorAIGoMenuItem ) == 0 ) 
			error = GoMenu( ( AIMenuMessage* )message );

	} 
	else if ( strcmp( caller, kCallerAIFilter ) == 0 ) {
		if ( strcmp( selector, kSelectorAIGetFilterParameters ) == 0 )
			error = GetFilterParameters( ( AIFilterMessage* )message );
		else if ( strcmp( selector, kSelectorAIGoFilter ) == 0 )
			error = GoFilter( ( AIFilterMessage* )message );
		
	} 
	else if ( strcmp( caller, kCallerAITool ) == 0  ) {
		if ( strcmp( selector, kSelectorAIToolMouseDown ) == 0 ) 
			error = ToolMouseDown( ( AIToolMessage* )message );

	} 
	else if ( strcmp( caller, kActionCaller ) == 0 ) {
		if ( strcmp( selector, kDoActionSelector ) == 0 )
			error = DoAction( ( DoActionMessage* )message );
	}
	return error;
}


/////////////////////////////////////////
//
// Standard Selector Functions
//
/////////////////////////////////////////

/* Handles startup.
*/
static AIErr StartupPlugin ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	error = AcquireSuites( message->d.basic );
	if (!error) {
		// Allocate our globals - Illustrator will keep track of these.
		error = message->d.basic->AllocateBlock( sizeof(Globals), (void **) &g );
		if ( !error ) { 
			message->d.globals = g;
		}
	}
	if (!error) {
		error = AddMenu(message);
	}
	if (!error) {	
		error = AddFilter(message);
	}
	if (!error) {
		error = AddTool(message);
	}
	if (!error) {
		error = AddAction(message);
	}
	ReleaseSuites( message->d.basic );
	return error;
}

/* Handles shutdown.
*/
static AIErr ShutdownPlugin( SPInterfaceMessage* message ) 
{
	AIErr error = kNoErr;		
	if ( g != nil ) {
		message->d.basic->FreeBlock(g);
		g = nil;
		message->d.globals = nil;
	}
	return error;
}

/* Restores this plug-in's globals from pointer preserved by Illustrator.
*/
static AIErr ReloadPlugin( SPAccessMessage* message ) 
{	
	AIErr error = kNoErr;
	g = ( Globals* )message->d.globals;
	return error;
}

/* Asks Illustrator to preserve this plug-in's globals.
*/
static AIErr UnloadPlugin( SPAccessMessage* message ) 
{
	AIErr error = kNoErr;
	message->d.globals = g; 
	return error;					
}

/////////////////////////////////////////
//
// Suite Management Functions
//
/////////////////////////////////////////

/* Acquires the suites declared in the global imports variable.
*/
static AIErr AcquireSuites( SPBasicSuite* sSPBasic ) 
{
	AIErr error = kNoErr;
	long i;
	for ( i = 0; i < sizeof(imports)/sizeof(imports[0]); ++i ) {
		if ( imports[i].suite != nil ) {
			AIErr tmpError = sSPBasic->AcquireSuite( imports[i].name, imports[i].version, (const void **)imports[i].suite );
			if ( !error && tmpError ) { // Record first bad status in error
				error = tmpError;
			}
		}
	}
	return error;
}

/* Releases the suites declared in the global imports variable.
*/
static AIErr ReleaseSuites( SPBasicSuite* sSPBasic ) 
{
	AIErr error = kNoErr;
	long i;
	for ( i = 0; i < sizeof(imports)/sizeof(imports[0]); ++i ) {
		void** procs = imports[i].suite;
		if ( procs != nil && *procs != nil ) {
			AIErr tmpError = sSPBasic->ReleaseSuite( imports[i].name, imports[i].version );
			if ( tmpError == kNoErr ) {
				*procs = nil;
			} else if ( !error ) {
				error = tmpError;
			}
		}
	}
	return error;
}

/////////////////////////////////////////
//
// Menu Functions
//
/////////////////////////////////////////

/* Adds this plug-in's menus.
*/
static AIErr AddMenu ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	g->aboutPluginMenu = nil;
	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"Tutorial...", 
				&g->aboutPluginMenu);
	return error;
}

/* Handles this plug-in's menus.
*/
static AIErr GoMenu ( AIMenuMessage* message )
{
	AIErr error = kNoErr;
	error = AcquireSuites( message->d.basic );
	if (!error) {
		if (message->menuItem == g->aboutPluginMenu) {
			// Pop this plug-ins about box.
			SDKAboutPluginsHelper aboutPluginsHelper;
			aboutPluginsHelper.PopAboutBox(message, "About Tutorial", kSDKDefAboutSDKCompanyPluginsAlertString);
		}
	}
	ReleaseSuites( message->d.basic );
	return error;
}

/////////////////////////////////////////
//
// Filter Functions
//
/////////////////////////////////////////

/* Adds this plug-in's filter.
*/
static AIErr AddFilter ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	AIMenuItemHandle menuItem = nil;

	// This method uses ADM to get the filter Category and Title from platform string resources
	// which are stored in string resource 16001 and 16002 (remember to pad member 0 in Windows resources)
	// This uses stringUtils
	// We pass (and then get returned) fromCategoryStr. 
	// This is a pointer to the beginning of the char array fromCategoryStr.
	PlatformAddFilterData filterData;
	int nIndex = 1;
	char fromCategoryStr[ kMaxFilterStringLength ]; // from string resource: Category
	sADMBasic->GetIndexString( message->d.self, kFilterStrings, nIndex, 
							   (char*) fromCategoryStr, kMaxFilterStringLength );
	CStrToPStr(fromCategoryStr, kMaxFilterStringLength);
	filterData.category = (unsigned char*)fromCategoryStr;
		
	// We pass (and then get returned) fromTitleStr. 
	// This is a pointer to the beginning of the char array fromTitleStr.
	char fromTitleStr[ kMaxFilterStringLength ];    // from string resource: Title
	sADMBasic->GetIndexString( message->d.self, kFilterStrings, ( nIndex + 1 ), 
							   (char*)fromTitleStr, kMaxFilterStringLength );
	CStrToPStr(fromTitleStr, kMaxFilterStringLength);
	filterData.title = (unsigned char*)fromTitleStr;
  
	// Add the filter.
	error = sAIFilter->AddFilter( message->d.self, "Tutorial", &filterData,
								kToolWantsToTrackCursorOption, &g->filterVariation1);
	if ( !error ) {
		// Only enable the filter's menu item if a document is open.
		error = sAIFilter->GetFilterMenuItem(g->filterVariation1, &menuItem);
		if ( !error ) {
			error = sAIMenu->UpdateMenuItemAutomatically(menuItem,
				kAutoEnableMenuItemAction,
				0, 0,	// don't care about what's in artwork
				0, 0,	// don't care about selection
				kIfOpenDocument, 0 );	// Enable if a document is open
		}
	}

	return error;
}

/* Prompts for input parameters for this plug-in's filter.
*/
static AIErr GetFilterParameters( AIFilterMessage* message ) 
{
	AIErr error = kNoErr;
	MyFilterParameters** parms_handle;

	error = AcquireSuites( ((SPInterfaceMessage*)message)->d.basic );

	// Create buffer for filter parameters if we are not given a buffer to use.
	if (!error) {
		parms_handle = (MyFilterParameters **) message->parameters;
		if ( !parms_handle ) {
			error = sAIMDMemory->MdMemoryNewHandle( sizeof( MyFilterParameters ), ( AIMdMemoryHandle *)&message->parameters);
			if ( !error && !message->parameters) {
					error = kOutOfMemoryErr;
			}
			if (!error) {
				// Set default parameter values.
				parms_handle = ( MyFilterParameters **) message->parameters;
				**parms_handle = kDefaultFilterParameters;
			}
		}
	}

	// Pop a dialog to allow the user to tune the filter's parameters.
	if (!error) {
		// See InitializeFilterDialog() for the dialog initialization procedure.
		// See HandleFilterDialogOKButton() for the dialog dismissal procedure.
		MyFilterParameters orig_params = **parms_handle;
		AIErr result = sADMDialog->Modal(message->d.self, "Tutorial Dialog", kTutorialDLOG, 
			kADMModalDialogStyle, InitializeFilterDialog, (ADMUserData)parms_handle, 0);
		bool cancelled = kDlgOKButton == result ? false : true; 
		
		// If the cancel button was hit, restore original parameters.
		if (cancelled)
		{
			**parms_handle = orig_params;
			error = kCanceledErr;
		}
	}

	ReleaseSuites( message->d.basic );
	return error;
}

/* Initializes the modal dialog for this plug-in's filter.
*/
static ASErr ASAPI InitializeFilterDialog(ADMDialogRef dialog)
{	
	MyFilterParameters **parms_handle;
	int defaultCornersValue, defaultSizeValue;
	ADMItemRef cornersEditItem, sizeEditItem;

	parms_handle = (MyFilterParameters **)sADMDialog->GetUserData(dialog);

	// Restore default values
	defaultCornersValue = (**parms_handle).corners;
	defaultSizeValue = (**parms_handle).size;
	cornersEditItem = sADMDialog->GetItem(dialog, kCornersItem);
	sizeEditItem = sADMDialog->GetItem(dialog, kSizeItem);
		
	// No need to add the buttons.
		
	// By default OK is assumed to be item 1 and Cancel is assumed to be item 2.
	// See TutorialID.h for definitions of these constants.
		
	sADMItem->SetUnits(cornersEditItem, kADMNoUnits);	
	sADMItem->SetMinIntValue(cornersEditItem, kMinFilterParameters.corners);
	sADMItem->SetMaxIntValue(cornersEditItem, kMaxFilterParameters.corners); 
	sADMItem->SetIntValue(cornersEditItem, defaultCornersValue);
		
	sADMItem->SetUnits(sizeEditItem, kADMPointUnits);
	sADMItem->SetMinIntValue(sizeEditItem, kMinFilterParameters.size);
	sADMItem->SetMaxIntValue(sizeEditItem, kMaxFilterParameters.size);
	sADMItem->SetIntValue(sizeEditItem, defaultSizeValue);

	sADMItem->Activate(cornersEditItem, true);	
	sADMItem->Activate(sizeEditItem, true);	// It should do this automaticly, but for now. DRL 4/15/96
	
	sADMItem->SelectAll(cornersEditItem);
	sADMItem->SelectAll(sizeEditItem);
		
	// Specify the procedure that gets called when the user dismisses the dialog
	sADMItem->SetNotifyProc(sADMDialog->GetItem(dialog, kDlgOKButton), HandleFilterDialogOKButton);

	return kNoErr;
}

/** Handles dismissal of the modal dialog for this plug-in's filter.
*/
static void ASAPI HandleFilterDialogOKButton(ADMItemRef item, ADMNotifierRef notifier)
{
	ADMDialogRef dialog = sADMItem->GetDialog(item);
	int cornersValue, sizeValue;
	MyFilterParameters **parms_handle = (MyFilterParameters **)sADMDialog->GetUserData(dialog);
	
	// Call the default Notify so the dialog knows the OK button was hit.
	sADMItem->DefaultNotify(item, notifier);

	// Fetch the value the user inputted for corners and save in params
	cornersValue = sADMItem->GetIntValue(sADMDialog->GetItem(dialog, kCornersItem));
	(**parms_handle).corners = cornersValue;

	// Fetch the value the user inputted for size and save in params
	sizeValue = sADMItem->GetIntValue(sADMDialog->GetItem(dialog, kSizeItem));
	(**parms_handle).size = sizeValue;
}	

/* Applies this plug-in's filter.
*/
static AIErr GoFilter( AIFilterMessage* message )
{
	AIErr 	error = kNoErr;
	MyFilterParameters** parms_handle = (MyFilterParameters **) message->parameters;

	error = AcquireSuites( ((SPInterfaceMessage*)message)->d.basic );

	// Do your stuff here, for example...

	// Create a new path.
	AIArtHandle path;
	if ( !error ) {
		error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, nil, &path );
	}

	// Find the point on the page that's in the middle of the window.
	AIRealPoint center;
	if ( !error ) {
		error = sAIDocumentView->GetDocumentViewCenter( nil, &center );
	}

	// Create the polygon points, randomly located around the center.
	if ( !error ) {
		ASInt32  corners = (**parms_handle).corners;
		ASInt32  size = (**parms_handle).size;
		AIPathSegment segment;
		// All of the segments are corners
		segment.corner = true;
		for (short i = 0; i < corners; ++i ) {
			segment.p.h = center.h +
						  sAIMath->AIRealMul( sAIRandom->FloatRnd() - kAIRealHalf, (AIReal) size );
			segment.p.v = center.v +
						  sAIMath->AIRealMul( sAIRandom->FloatRnd() - kAIRealHalf, (AIReal) size );
			segment.in = segment.out = segment.p;
			error = sAIPath->SetPathSegments( path, i, 1, &segment );
			if ( error ) 
				break;
		}
	}

	// Close the path.
	if ( !error ) {
		error = sAIPath->SetPathClosed( path, true );
	}

	// Allow the filter to be recorded as an action event.
	if ( !error ) {
		error = RecordFilterAction(**parms_handle);
	}
	
	ReleaseSuites( message->d.basic );
	return error;
}

/////////////////////////////////////////
//
// Tool Functions
//
/////////////////////////////////////////

/* Adds this plug-in's tool to Illustrator.
*/
static AIErr AddTool( SPInterfaceMessage* message ) 
{
	AIErr error = kNoErr;
	AIAddToolData toolData;
	toolData.title = "Tutorial Line Tool"; 
	toolData.tooltip = "Tutorial Line Tool";
	toolData.sameGroupAs = kNoTool;
	toolData.sameToolsetAs = kNoTool;
	toolData.icon = sADMIcon->GetFromResource (  message->d.self, 
		kTutorialLineToolIcon, kTutorialIcons );
	if ( ( sADMIcon->GetType( toolData.icon ) ) == kUnknown  ) {
		error = kNoIconErr;
	}

	if (!error) {
		error = sAITool->AddTool( message->d.self, toolData.title, &toolData,
					kToolWantsToTrackCursorOption, &g->toolVariation1 );
	}

	return error;
}
		
/* Handles mouse down event for this plug-in's tool.
*/
static AIErr ToolMouseDown( AIToolMessage* message ) 
{

	AIErr 	error = kNoErr;
	AIArtHandle path;
	AIPathSegment segment;	
	long 	count = 0;
	AIMatchingArtSpec spec[1];
	AIArtHandle **matches;
	short segmentCount = 0;

	error = AcquireSuites( ((SPInterfaceMessage*)message)->d.basic );

	// Get the current selection (if any).
	if ( !error ) {
		spec[0].type = kPathArt;
		spec[0].whichAttr = kArtSelected;
		spec[0].attr = kArtSelected;
		error = sAIMatchingArt->GetMatchingArt( spec, 1, &matches, &count );
	}

	bool addPoint = false;
	if ( !error ) {
		if ( count == 0 ) {
			addPoint = true;
			// There is no selection, so make a new path.
			error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, nil, &path );
			
			// Select it so we find it later.
			if (!error) {
				error = sAIArt->SetArtUserAttr( path, kArtSelected, kArtSelected );
			}
		}
		else if ( count == 1 ) {
			addPoint = true;
			path = (*matches)[0];
		}
	}

	//  Add point to the path at the mouse down location.
	if ( !error && addPoint) {
		error = sAIPath->GetPathSegmentCount( path, &segmentCount );
		// All of the segments are corners
		if ( !error) {
			segment.corner = true;  
			segment.p.h = message->cursor.h;
			segment.p.v = message->cursor.v;
			segment.in = segment.out = segment.p;
			error = sAIPath->SetPathSegments( path, segmentCount, 1, &segment );
		}
	}

	ReleaseSuites( message->d.basic );
	return error;
}

/////////////////////////////////////////
//
// Action Functions
//
/////////////////////////////////////////

/* Registers this plug-in's action with Illustrator.
*/
static AIErr AddAction ( SPInterfaceMessage* message )
{
	AIErr 	error = kNoErr;

	// This is your opportunity to register your plug-in to the Action Manager and
	// describe its parameter block.
	// verify that the sAIActionManager suite pointer is valid
	// if the Action plug-in was disabled (taken from the Plug-ins folder)
	// then the sAIActionManager suite pointer would not be valid.
	// We acquire and release this suite individually during reload and unload
	if (sAIActionManager)
	{
		AIActionParamTypeRef actionParam = nil;
		SPPluginRef	pluginRef = message->d.self;

		// Create a new Type Parameter Block (TPB)
		sAIActionManager->AINewActionParamType(&actionParam);	
		
		if (actionParam && pluginRef)
		{
			// Fill in the TPB.
			// This describes which parameters your filter requires.

			// Localized string buffer
			char localizedName[256];
			
			// Set the 'Corners' parameter in the Type Parameter Block (TPB)
			// The 'localizedName' parameter will be shown in the Actions Palette
			sADMBasic->GetIndexString(pluginRef, kActionStrings, 1, localizedName, 256);
			sAIActionManager->AIActionSetTypeKey(actionParam, 'crnr', localizedName, actionTypeInteger, true);
			// Set the 'Size' parameter in the TPB
			// The 'localizedName' parameter will be shown in the Actions Palette
			sADMBasic->GetIndexString(pluginRef, kActionStrings, 2, localizedName, 256);
			sAIActionManager->AIActionSetTypeKey(actionParam, 'size', localizedName, actionTypeInteger, true);
			
			// Register the your plug-in to the Action Manager
			// The 'localizedName' parameter is the name of the Action which
			// will be shown in the Action Palette.
			sADMBasic->GetIndexString(pluginRef, kActionStrings, 3, localizedName, 256);
			error = sAIActionManager->RegisterActionEvent("AISDK_Tutorial", localizedName,
															1, 0, nil, pluginRef,
															nil, 
															actionParam);

			// Dispose the TPB. The Action Manager has already made a copy of it internally.
			sAIActionManager->AIDeleteActionParamType(actionParam);		
		}
	}
	return error;
}

/*
*/
static AIErr RecordFilterAction(const MyFilterParameters& parameters)
{
	ASErr error = kNoErr;
	AIActionParamValueRef valueParameterBlock = nil;

	// Record Action if InRecordMode
	// If the user is InRecordMode (the Record button was pressed in the Action Palette),
	// your plug-in must report user parameters to the Action Manager so that it can
	// replay this at a later time.
	// Your plug-in will receive a kActionCaller/kDoActionSelector when the Action Manager
	// wants you to replay this action.
	if (sAIActionManager && sAIActionManager->InRecordMode()) {
		
		// create a new Value Parameter Block (VPB)
		error = sAIActionManager->AINewActionParamValue(&valueParameterBlock);		
		if (!error && valueParameterBlock) {
			// Set the 'crnr' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'crnr', parameters.corners);
			// Set the 'size' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'size', parameters.size);
			// Record this action with parameters contained in the VPB
			sAIActionManager->RecordActionEvent("AISDK_Tutorial", kDialogOn, valueParameterBlock);
			// Delete the VPB, the Action Manager makes an internal copy of it.
			sAIActionManager->AIDeleteActionParamValue(valueParameterBlock);		
		}
	}
	return error;
}

/* Executes this plug-in's action. 
 * This routine gets called when your plug-in gets called with kActionCaller/kDoActionSelector
 * Your plug-in is being run by the Actions panel.
*/
static AIErr DoAction(DoActionMessage* doActionMessage)
{
	ASErr error = kNoErr;
	MyFilterParameters** params_handle;
	AIFilterMessage filterMessageStruct, *filterMessage;
	
	error = AcquireSuites( doActionMessage->d.basic );

	// Allocate instance of struct MyFilterParameters
	if (!error) {
		filterMessage = &filterMessageStruct;
		filterMessage->d = doActionMessage->d;
		error = sAIMDMemory->MdMemoryNewHandle( sizeof( MyFilterParameters ), ( AIMdMemoryHandle *)&filterMessage->parameters);
		if ( !error && !filterMessage->parameters ) {
			error = kOutOfMemoryErr;
		}
	}

	// Extract parameter values from the the Value Parameter Block (VPB). 
	if (!error) {
		AIActionParamValueRef valueParameterBlock = doActionMessage->param;
		params_handle = ( MyFilterParameters **) filterMessage->parameters;
		error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'crnr', &(*params_handle)->corners);
		if (!error) {
			error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'size', &(*params_handle)->size);
		}
	}

	// Pop filter parameters dialog if asked to.
	if (!error && doActionMessage->showDialog) {
		error = GetFilterParameters( filterMessage );
	} 

	// Apply the filter.
	if (!error) {
		error = GoFilter( filterMessage );
	}

	ReleaseSuites( doActionMessage->d.basic );
	return error;
}

/////////////////////////////////////////
//
// Utility functions
//
/////////////////////////////////////////

/*
*/
static void CStrToPStr(char *s, unsigned long len)
{
	const ai::UnicodeString sAsUnicode((const char*)s);
	ai::PStr sAsPStr((unsigned char*) s);
	sAsUnicode.getToBuffer(sAsPStr, len, kAIUTF8CharacterEncoding );
}