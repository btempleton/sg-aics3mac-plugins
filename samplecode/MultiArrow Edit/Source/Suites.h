//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MultiArrowTool/Source/Suites.h $
//
//  $Revision: #6 $
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

	AIPluginSuite		*sAIPlugin = nil;
	AIMdMemorySuite 	*sAIMDMemory = nil;
	AIRealMathSuite 	*sAIRealMath = nil;
	AIArtSuite 			*sAIArt = nil;
	AI110UserSuite			*sAIUser = nil;
	AIUndoSuite 		*sAIUndo = nil;
	AIPathSuite			*sAIPath = nil;
	AIPathStyleSuite	*sAIPathStyle = nil;

	#ifdef ADDS_MENU
	AIMenuSuite 		*sMenu = nil;
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
	AINotifierSuite 	*sNotify = nil;
	#endif

	#ifdef ADDS_TIMER
	AITimerSuite 		*sTimer = nil;
	#endif

	#ifdef ADDS_TRANSFORM_AGAIN
	AITransformAgainSuite *sAgain = nil;
	#endif

	ADMBasicSuite 	*sADMBasic = nil;
	ADMDialogSuite	*sADMDialog = nil;
	ADMItemSuite7	*sADMItem = nil;
	ADMIconSuite    *sADMIcon = nil;
	ADMTrackerSuite *sADMTracker = nil;
	AIUnicodeStringSuite*	sAIUnicodeString = nil;
}

// property globals
ImportBunch imports[] = {

	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kSPAccessSuite, kSPAccessSuiteVersion, (void**)&sSPAccess,
	kAIPluginSuite, kAIPluginSuiteVersion, (void**)&sAIPlugin,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, (void**)&sAIMDMemory,
	kAIRealMathSuite, kAIRealMathVersion, (void**)&sAIRealMath,
	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kAIUserSuite, kAI110UserVersion, (void**)&sAIUser,
	kAIPathSuite, kAIPathSuiteVersion, (void**)&sAIPath,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, (void**)&sAIPathStyle,
	kAIUndoSuite, kAIUndoSuiteVersion, (void**)&sAIUndo,

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
	kAITransformAgainSuite, kAITransformAgainVersion, (void**)&sAgain,
#endif

#ifdef ADDS_NOTIFIER
	kAINotifierSuite, kAINotifierVersion, (void**)&sNotify,
#endif

	kADMBasicSuite, kADMBasicSuiteVersion, (void**)&sADMBasic,
	kADMDialogSuite, kADMDialogSuiteVersion, (void**)&sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, (void**)&sADMItem,
	kADMIconSuite, kADMIconSuiteVersion, (void**)&sADMIcon,
	kADMTrackerSuite, kADMTrackerSuiteVersion, (void**)&sADMTracker,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, (void**)&sAIUnicodeString,
};

#endif __Suites_Shell_H__