//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/Suites.h $
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

	AIMdMemorySuite 	*sAIMDMemory = nil;
	AIRealMathSuite 	*sAIMath = nil;
	AIArtSuite 			*sAIArt = nil;
	AI110UserSuite			*sAIUser = nil;
	AIUndoSuite 		*sAIUndo = nil;

	AIMatchingArtSuite 		*sAIMatch = nil;
	AIPathSuite 			*sAIPath = nil;
	AIPathStyleSuite		*sAIPathStyle = nil;
	AIRandomSuite 			*sAIRandom = nil;

	#ifdef ADDS_MENU
	AIMenuSuite7 		*sMenu = nil;
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

	#ifdef ADDS_LIVE_EFFECT
	AILiveEffectSuite	*sLiveEffect = nil;
	AIDictionarySuite	*sDictionary = nil;
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
	AIUnicodeStringSuite*	sAIUnicodeString = nil;
}

// property globals
ImportBunch imports[] = {

	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kSPAccessSuite, kSPAccessSuiteVersion, (void**)&sSPAccess,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, (void**)&sAIMDMemory,
	kAIRealMathSuite, kAIRealMathVersion, (void**)&sAIMath,
	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kAIUserSuite, kAI110UserVersion, (void**)&sAIUser,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, (void**)&sAIMatch,
	kAIPathSuite, kAIPathSuiteVersion,	(void**)&sAIPath,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, (void**)&sAIPathStyle,
	kAIRandomSuite, kAIRandomSuiteVersion,	(void**)&sAIRandom,

#ifdef ADDS_MENU
	kAIMenuSuite, kAI110MenuSuiteVersion, (void**)&sMenu,
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

#ifdef ADDS_LIVE_EFFECT
	kAILiveEffectSuite, kAILiveEffectVersion, (void**)&sLiveEffect,
	kAIDictionarySuite, kAIDictionaryVersion, (void**)&sDictionary,
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
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, (void**)&sAIUnicodeString,
};

#endif __Suites_Shell_H__

