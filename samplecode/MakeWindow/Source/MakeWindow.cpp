#include "IllustratorSDK.h"
#include "Common.h"

// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

// Plug-in entry point
extern "C" ASAPI ASErr PluginMain(char* caller,char* selector,void* message);

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

/* Adds this plug-in's menus.
*/
static AIErr AddMenu ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	g->aboutPluginMenu = nil;
	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddMenuItem(message, 
				"MAKEWINDOW1", 
				"MAKEWINDOW2", 
				"Tutorial...", 
				&g->aboutPluginMenu);
	return error;
}

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
	ReleaseSuites( message->d.basic );
	return error;
}


// Tell Xcode to return to default visibility for symbols
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	ASErr error = kNoErr;
	SPBasicSuite* sSPBasic = ((SPMessageData*)message)->basic;
	

	
	if(sSPBasic->IsEqual(caller, kSPInterfaceCaller))
	{
		AIMenuSuite *sMenuBasic = nil;
		error = sSPBasic->AcquireSuite(kAIMenuSuite, kAIMenuVersion, (const void**)&sMenuBasic);
				
		if(sSPBasic->IsEqual(selector,kSPInterfaceStartupSelector))
			error = StartupPlugin( ( SPInterfaceMessage* )message );
		else if(sSPBasic->IsEqual(selector,kSPInterfaceShutdownSelector))
			sADMBasic->MessageAlert("Goodbye from MakeWindow!");
		error = sSPBasic->ReleaseSuite(kADMBasicSuite,kADMBasicSuiteVersion10);
	}
	
	return error;
}







/*			OSStatus err;
			IBNibRef theNib;
			WindowRef theWindow;
 			err = CreateNibReference (CFSTR("MakeWindow"), &theNib); // 1
		if (!err)
			CreateWindowFromNib (theNib, CFSTR("MakeWindow"), &theWindow); // 2
 			ShowWindow(theWindow); 
*/