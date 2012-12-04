//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/LiveDropShadow/Source/Suites.h $
//
//  $Revision: #4 $
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
	SPBlocksSuite 			*sSPBlocks = nil;
	AIMdMemorySuite			*sAIMdMemory = nil;

	AIArtSuite 				*sAIArt = nil;
	AIPluginGroupSuite		*sAIPluginGroup = nil;
	AIFilterSuite			*sAIFilter = nil;
	AIRealMathSuite			*sAIRealMath = nil;
	AIGroupSuite			*sAIGroup = nil;
	AILayerSuite			*sAILayer = nil;
	AIMatchingArtSuite		*sAIMatchingArt = nil;
	AIPathStyleSuite		*sAIPathStyle = nil;
	AITransformArtSuite		*sAITransformArt = nil;
	AI110UserSuite			*sAIUser = nil;

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

	ADMBasicSuite10* sADMBasic = nil;
	ADMDialogSuite* sADMDialog = nil;
	ADMItemSuite7* sADMItem = nil;
	ADMIconSuite    *sADMIcon = nil;
	AIUnicodeStringSuite*	sAIUnicodeString = nil;
}

// property globals
ImportBunch imports[] = {

	kAIArtSuite, kAIArtVersion, (void**)&sAIArt,
	kSPBlocksSuite, kSPBlocksSuiteVersion, (void**)&sSPBlocks,
	kAIMdMemorySuite, kAIMdMemoryVersion, (void**)&sAIMdMemory,
	kAIPluginGroupSuite, kAIPluginGroupVersion, (void**)&sAIPluginGroup,
	kAIRealMathSuite, kAIRealMathVersion, (void**)&sAIRealMath,
	kAIGroupSuite, kAIGroupVersion, (void**)&sAIGroup,
	kAILayerSuite, kAILayerVersion, (void**)&sAILayer,
	kAIMatchingArtSuite, kAIMatchingArtVersion, (void**)&sAIMatchingArt,
	kAIPathStyleSuite, kAIPathStyleVersion, (void**)&sAIPathStyle,
	kAITransformArtSuite, kAITransformArtSuiteVersion, (void**)&sAITransformArt,
	kAIUserSuite, kAI110UserSuiteVersion, (void**)&sAIUser,

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

	kADMBasicSuite, kADMBasicSuiteVersion10, (void**)&sADMBasic,
	kADMDialogSuite, kADMDialogSuiteVersion, (void**)&sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, (void**)&sADMItem,
	kADMIconSuite, kADMIconSuiteVersion, (void**)&sADMIcon,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, (void**)&sAIUnicodeString,
};

#endif __Suites_Shell_H__