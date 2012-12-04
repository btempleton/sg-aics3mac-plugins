//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/Suites.h $
//
//  $Revision: #8 $
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
	AIMdMemorySuite		*sAIMdMemory = nil;
	SPAccessSuite		*sSPAccess = nil;

	AIFixedMathSuite 	*sAIMath = nil;
	AIArtSuite 			*sAIArt = nil;
	AI110UserSuite			*sAIUser = nil;
	AIUndoSuite 		*sAIUndo = nil;
	AIUnicodeStringSuite *sAIUnicodeString = nil;

	#ifdef ADDS_MENU
	AIMenuSuite *sMenu = nil;
	#endif

	#ifdef ADDS_FILE_FORMAT
	AIFileFormatSuite	*sFileFormat = nil;
	#endif

	#ifdef ADDS_TOOL
	AIToolSuite			*sTool = nil;
	#endif

	#ifdef ADDS_FILTER
	AIFilterSuite 		*sFilter = nil;
	#endif

	#ifdef ADDS_NOTIFIER
	AINotifierSuite 	*sNotifier = nil;
	#endif

	#ifdef ADDS_TIMER
	AITimerSuite 		*sTimer = nil;
	#endif

	#ifdef ADDS_TRANSFORM_AGAIN
	AITransformAgainSuite *sTransformAgain = nil;
	#endif

	#ifdef ADDS_PLUGINGROUP
	AIPluginGroupSuite *sPluginGroup = nil;
	#endif

	#ifdef ADDS_ACTIONMANAGER
	AIActionManagerSuite *sActionManager = nil;
	#endif

	ADMBasicSuite 	*sADMBasic = nil;
	ADMDialogSuite	*sADMDialog = nil;
	ADMItemSuite7	*sADMItem = nil;
	ADMIconSuite    *sADMIcon = nil;
}

// property globals
ImportBunch imports[] = {

	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, (void**)&sAIMdMemory,
	kSPAccessSuite, kSPAccessSuiteVersion, (void**)&sSPAccess,
	kAIFixedMathSuite, kAIFixedMathVersion, (void**)&sAIMath,
	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kAIUserSuite, kAI110UserVersion, (void**)&sAIUser,
	kAIUndoSuite, kAIUndoSuiteVersion, (void**)&sAIUndo,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, (void**)&sAIUnicodeString,

#ifdef ADDS_MENU
	kAIMenuSuite, kAIMenuSuiteVersion, (void**)&sMenu,
#endif
	
#ifdef ADDS_FILE_FORMAT
	kAIFileFormatSuite, kAIFileFormatVersion, (void**)&sFileFormat,
#endif

#ifdef ADDS_TOOL
	kAIToolSuite, kAIToolVersion, (void**)&sTool,
#endif

#ifdef ADDS_FILTER
	kAIFilterSuite, kAIFilterVersion, (void**)&sFilter,
#endif

#ifdef ADDS_TIMER
	kAITimerSuite, kAITimerVersion, (void**)&sTimer,
#endif

#ifdef ADDS_TRANSFORM_AGAIN
	kAITransformAgainSuite, kAITransformAgainVersion, (void**)&sTransformAgain,
#endif

#ifdef ADDS_NOTIFIER
	kAINotifierSuite, kAINotifierVersion, (void**)&sNotifier,
#endif

#ifdef ADDS_PLUGINGROUP
	kAIPluginGroupSuite, kAIPluginGroupSuiteVersion, (void**)&sPluginGroup,
#endif

#ifdef ADDS_ACTIONMANAGER
	kAIActionManagerSuite, kAIActionManagerSuiteVersion, (void**)&sActionManager,
#endif


	kADMBasicSuite, kADMBasicSuiteVersion, (void**)&sADMBasic,
	kADMDialogSuite, kADMDialogSuiteVersion, (void**)&sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, (void**)&sADMItem,
	kADMIconSuite, kADMIconSuiteVersion, (void**)&sADMIcon,
};

#endif __Suites_Shell_H__