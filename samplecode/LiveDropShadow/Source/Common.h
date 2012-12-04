//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/LiveDropShadow/Source/Common.h $
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

#ifndef __Common_Shell_H__
#define __Common_Shell_H__

// Enables / disables plug-in features using #defines which control
// conditionally compiled code in other source files.
// Declares globals shared by source files.


// These defines are used to control plug-in type-specific sections of code.
// Comment out the types your plug-in doesn't add, and remove the appropriate 
// *Handler.cpp source files from the project.

#ifndef ADDS_MENU
#define ADDS_MENU
#endif

//#ifndef ADDS_FILTER
//#define ADDS_FILTER
//#endif

//#ifndef ADDS_FILE_FORMAT
//#define ADDS_FILE_FORMAT
//#endif

//#ifndef ADDS_TOOL
//#define ADDS_TOOL
//#endif

//#ifndef ADDS_TIMER
//#define ADDS_TIMER
//#endif

//#ifndef ADDS_NOTIFIER
//#define ADDS_NOTIFIER
//#endif

//#ifndef ADDS_TRANSFORM_AGAIN
//#define ADDS_TRANSFORM_AGAIN
//#endif

#ifndef ADDS_PLUGINGROUP
#define ADDS_PLUGINGROUP
#endif

//#ifndef ADDS_ACTIONMANAGER
//#define ADDS_ACTIONMANAGER
//#endif

#include "SPConfig.h"

#ifdef MAC_ENV
#include <string.h>
#include <Types.h>
#endif

#ifdef WIN_ENV
#include "windows.h"
#endif


// System Suites
#include "AIPlugin.h"
#include "SPBlocks.h"
#include "AIMdMemory.h"
#include "stringUtils.h"
#include "plugin.h"


// General Suites
#include 	"AIFixedMath.h"
#include 	"AIArt.h"
#include 	"AIUser.h"
#include	"AIUndo.h"
#include	"AITypes.h"
#include	"AIBlock.h"
#include	"AICustomColor.h"
#include 	"AIFilter.h"
#include	"AIRealMath.h"
#include	"AIGroup.h"
#include	"AILayer.h"
#include	"AIMatchingArt.h"
#include	"AIMenu.h"
#include	"AIMenuGroups.h"
#include	"AIPathfinder.h"
#include	"AITransformArt.h"

/*
#include	<stdio.h>
#include	<string.h>
#include	<Resources.h>
#include	<OSUtils.h>
#include	<ToolUtils.h>
*/

// Plug-in Types
#ifdef ADDS_MENU
#include "AIMenu.h"
#endif

#ifdef ADDS_FILTER
#include "AIFilter.h"
#include "filterHandler.h"
#endif

#ifdef ADDS_FILE_FORMAT
#include "AIFileFormat.h"
#endif

#ifdef ADDS_TOOL
#include "AITool.h"
#endif

#ifdef ADDS_TIMER
#include "AITimer.h"
#endif

#ifdef ADDS_NOTIFIER
#include "AINotifier.h"
#endif

#ifdef ADDS_TRANSFORM_AGAIN
#include "AITransformAgain.h"
#endif

#ifdef ADDS_PLUGINGROUP
#include "AIPluginGroup.h"
#endif

#ifdef ADDS_ACTIONMANAGER
#include "AIActionManager.h"
#endif

// ADM Suites
#include "ADMBasic.h"
#include "ADMDialog.h"
#include "ADMItem.h"
#include "ADMIcon.h"


/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/


#ifndef GLOBALSTRUCT
#define GLOBALSTRUCT
	
	typedef struct {

#ifdef ADDS_MENU
	AIMenuItemHandle		dsMakeMenuHandle;
	AIMenuItemHandle		dsReleaseMenuHandle;
	AIMenuItemHandle		dsAdjustMenuHandle;
	AIMenuItemHandle		aboutPluginMenu;
#endif
	
#ifdef ADDS_FILTER
	// these are used by filterHandler.c, addFilters( )
	AIFilterHandle filters[kMaxFilters];
	int numFilters;		
#endif

#ifdef ADDS_TOOL
	// these are used by toolHandler.c
	AIBoolean cursorLoaded;
	AIRealPoint startingPoint, endPoint;	
#ifdef MAC_ENV
	CursHandle	cursor;
#endif // MAC_ENV
#ifdef WIN_ENV
	HCURSOR		cursor;
#endif // WIN_ENV

#endif // ADDS_TOOL

	SPBasicSuite *basic;
	AIPluginGroupHandle		dsPluginGroupHandle;

	} Globals;

#endif

typedef struct {

	long nothing;
	
} ObjectData;

#define memFullErr -108
#define noErr       0


/**-----------------------------------------------------------------------------
 **
 **	Globals
 **
 **/


// general globals
extern	Globals *g;
extern 	SPAccessRef gSelfAccess;

// suite stuff
extern	"C" SPAccessSuite	*sSPAccess;
extern "C"	AIArtSuite 				*sAIArt;
extern "C" SPBlocksSuite		*sSPBlocks;
extern "C" 	AIMdMemorySuite			*sAIMdMemory;
extern "C"	AIPluginGroupSuite		*sAIPluginGroup;
extern "C"	AICustomColorSuite		*gCustomColor;
extern "C"	AIFilterSuite			*sAIFilter;
extern "C"	AIRealMathSuite			*sAIRealMath;
extern "C"	AIGroupSuite			*sAIGroup;
extern "C"	AILayerSuite			*sAILayer;
extern "C"	AIMatchingArtSuite		*sAIMatchingArt;
extern "C"	AIPathStyleSuite		*sAIPathStyle;
extern "C"	AITransformArtSuite		*sAITransformArt;
extern "C"  AI110UserSuite			*sAIUser;

// plug-in types
#ifdef  ADDS_MENU
extern "C" 	AIMenuSuite7 *sMenu;
#endif
#ifdef  ADDS_FILE_FORMAT
extern "C" 	AIFileFormatSuite *sFileFormat;
#endif
#ifdef  ADDS_FILTER
extern "C"	AIFilterSuite *sFilter;
#endif
#ifdef  ADDS_TOOL
extern "C"	AIToolSuite *sTool;
#endif
#ifdef  ADDS_TIMER
extern "C"	AITimerSuite *sTimer;
#endif
#ifdef  ADDS_NOTIFIER
extern "C"	AINotifierSuite *sNotifier;
#endif
#ifdef  ADDS_TRANSFORM_AGAIN
extern "C"	AITransformAgainSuite *sTransformAgain;
#endif
#ifdef	ADDS_PLUGINGROUP
extern "C"	AIPluginGroupSuite *sPluginGroup;
#endif
#ifdef	ADDS_ACTIONMANAGER
extern "C"	AIActionManagerSuite *sActionManager;
#endif

extern "C" ADMBasicSuite10* sADMBasic;
extern "C" ADMDialogSuite* sADMDialog;
extern "C" ADMItemSuite7* sADMItem;
extern "C"  ADMIconSuite    *sADMIcon;
extern "C" AIUnicodeStringSuite*	sAIUnicodeString;


/**-----------------------------------------------------------------------------
 **
 **	suite support
 **
 **/

extern	AIErr acquireSuites( SPBasicSuite *sBasic );
extern	AIErr releaseSuites( SPBasicSuite *sBasic );

#endif // __Common_Shell_H__