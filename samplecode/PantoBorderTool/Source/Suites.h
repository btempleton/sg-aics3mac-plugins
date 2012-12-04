//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/Suites.h $
//
//  $Revision: #7 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __Suites_Shell_H__
#define __Suites_Shell_H__

#include "Common.h" // Declares globals.


// Defines global suite pointers and imports array.
// Modify if your plug-in uses other suites.
// Included by shellMain.cpp - do not include in other files.

typedef struct {	
	char *name;		
	long version;
	void **suite;
} ImportBunch;

// suite globals
extern "C" {
	SPBlocksSuite 		*sSPBlocks = nil;
	SPAccessSuite		*sSPAccess = nil;
	
	AIFixedMathSuite 	*sAIMath = nil;
	AIArtSuite 			*sAIArt = nil;
	AI110UserSuite			*sAIUser = nil;
	AIUndoSuite 		*sAIUndo = nil;
	AIAppContextSuite	*sAIAppContext = nil;
	AIPreferenceSuite	*sAIPreference = nil;
	AIUnicodeStringSuite  *sAIUnicodeString = nil;
	
#ifdef ADDS_MENU
	AIMenuSuite 		*sAIMenu = nil;
#endif
	
#ifdef ADDS_FILE_FORMAT
	AIFileFormatSuite	*sAIFileFormat = nil;
#endif
	
#ifdef ADDS_TOOL
	AIToolSuite			*sAITool = nil;
#endif
	
#ifdef ADDS_FILTER
	AIFilterSuite 		*sAIFilter = nil;
#endif
	
#ifdef ADDS_NOTIFIER
	AINotifierSuite 	*sAINotifier = nil;
#endif
	
#ifdef ADDS_TIMER
	AITimerSuite 		*sAITimer = nil;
#endif
	
#ifdef ADDS_TRANSFORM_AGAIN
	AITransformAgainSuite *sAITransformAgain = nil;
#endif
	
	ADMBasicSuite 	*sADMBasic = nil;
	ADMDialogSuite	*sADMDialog = nil;
	ADMItemSuite7	*sADMItem = nil;
	ADMIconSuite    *sADMIcon = nil;
	ADMIconSuite2    *sADMIcon2 = nil;
	ADMListSuite	*sADMList = nil;
	ADMDialogGroupSuite *sADMDialogGroup = nil;
	ADMNotifierSuite2	*sADMNotifier = nil;
	ADMEntrySuite	*sADMEntry = nil;
	ADMTrackerSuite	*sADMTracker = nil;
	
	//added this
	AISwatchLibrariesSuite *sAISwatchLibrary = nil;
	AISwatchListSuite *sAISwatchList = nil;
	AISwatchGroupSuite *sAISwatchGroup = nil;
	AICustomColorSuite *sAICustomColor = nil;
	AIPluginSuite *sAIPlugin = nil;
	AIPathSuite *sAIPath = nil;
	AIPathStyleSuite *sAIPathStyle = nil;
	AIRealMathSuite *sAIRealMath = nil;
	
}


// The imports array contains all the suites which
// are aquired by the AcquireSuites() routine
ImportBunch imports[] = {
	
	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kSPAccessSuite, kSPAccessSuiteVersion, (void**)&sSPAccess,
	kAIFixedMathSuite, kAIFixedMathVersion, (void**)&sAIMath,
	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kAIUserSuite, kAI110UserVersion, (void**)&sAIUser,
	kAIAppContextSuite, kAIAppContextSuiteVersion, (void**)&sAIAppContext,
	kAIPreferenceSuite, kAIPreferenceSuiteVersion, (void**)&sAIPreference,
	kSPAccessSuite, kSPAccessSuiteVersion, (void**)&sSPAccess,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, (void**)&sAIUnicodeString,
	
#ifdef ADDS_MENU
	kAIMenuSuite, kAIMenuSuiteVersion, (void**)&sAIMenu,
#endif
	
#ifdef ADDS_FILE_FORMAT
	kAIFileFormatSuite, kAIFileFormatVersion, (void**)&sAIFileFormat,
#endif
	
#ifdef ADDS_TOOL
	kAIToolSuite, kAIToolVersion, (void**)&sAITool,
#endif
	
#ifdef ADDS_FILTER
	kAIFilterSuite, kAIFilterVersion, (void**)&sAIFilter,
#endif
	
#ifdef ADDS_TIMER
	kAITimerSuite, kAITimerVersion, (void**)&sAITimer,
#endif
	
#ifdef ADDS_TRANSFORM_AGAIN
	kAITransformAgainSuite, kAITransformAgainVersion, (void**)&sAITransformAgain,
#endif
	
#ifdef ADDS_NOTIFIER
	kAINotifierSuite, kAINotifierVersion, (void**)&sAINotifier,
#endif
	
	kADMBasicSuite, kADMBasicSuiteVersion, (void**)&sADMBasic,
	kADMDialogSuite, kADMDialogSuiteVersion10, (void**)&sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, (void**)&sADMItem,
	kADMIconSuite, kADMIconSuiteVersion, (void**)&sADMIcon,
	kADMIconSuite, kADMIconSuiteVersion2, (void**)&sADMIcon2,
	kADMListSuite, kADMListSuiteVersion, (void**)&sADMList,
	kADMDialogGroupSuite, kADMDialogGroupSuiteVersion, (void**)&sADMDialogGroup,
	kADMNotifierSuite, kADMNotifierSuiteVersion2, (void**)&sADMNotifier,
	kADMEntrySuite, kADMEntrySuiteVersion, (void**)&sADMEntry,
	kADMTrackerSuite, kADMTrackerSuiteVersion, (void**)&sADMTracker,
	
	//Added this
	kAISwatchLibrariesSuite, kAISwatchLibrariesSuiteVersion, (void**)&sAISwatchLibrary,
	kAISwatchListSuite, kAISwatchListSuiteVersion, (void**)&sAISwatchList,
	kAISwatchGroupSuite, kAISwatchGroupSuiteVersion, (void**)&sAISwatchGroup,
	kAICustomColorSuite, kAICustomColorSuiteVersion, (void**)&sAICustomColor,
	kAIPluginSuite, kAIPluginSuiteVersion, (void**)&sAIPlugin,
	kAIPathSuite, kAIPathSuiteVersion, (void**)&sAIPath,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, (void**)&sAIPathStyle,
	kAIRealMathSuite, kAIRealMathVersion, (void**)&sAIRealMath,
	kAIUndoSuite, kAIUndoSuiteVersion, (void**)&sAIUndo,
};

#endif __Suites_Shell_H__