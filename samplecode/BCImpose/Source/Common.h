//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/Common.h $
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

#ifndef ADDS_NOTIFIER
#define ADDS_NOTIFIER
#endif

//#ifndef ADDS_TRANSFORM_AGAIN
//#define ADDS_TRANSFORM_AGAIN
//#endif

#include "SPConfig.h"

#ifdef MAC_ENV
#include <string.h>

#endif

#ifdef WIN_ENV
#include "windows.h"
#endif


// System Suites
#include "AIPlugin.h"
#include "SPBlocks.h"
#include "AIMDMemory.h"

// General Suites
#include "AIFixedMath.h"
#include "AIArt.h"
#include "AI110User.h"
#include "AIUndo.h"
#include "AIContext.h"
#include "AIPreference.h"
#include "SPAccess.h"
#include "AIUnicodeString.h"

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

// ADM Suites
#include "ADMBasic.h"
//#include "ADMDialog.h"
//#include "ADMItem.h"
//#include "ADMIcon.h"
//#include "ADMList.h"
//#include "ADMDialogGroup.h"
//#include "ADMNotifier.h"
//#include "ADMEntry.h"
//#include "ADMTracker.h"

//Added this
#include "AISwatchLibraries.h"
#include "AISwatchList.h"
#include "AICustomColor.h"
#include "AIUID.h"
#include "AIDictionary.h"
#include "AIEntry.h"

#include "AIDocumentList.h"
#include "AIDocument.h"
#include "AIDocumentView.h"
#include "AIArtSet.h"
#include "AIArtStyle.h"
#include "AIPathStyle.h"
#include "AIGradient.h"
#include "AIForeignObject.h"
#include "AIFOConversion.h"
#include "AILayer.h"
#include "AIMatchingArt.h"
#include "AIMdMemory.h"
#include "AITextFrame.h"
#include "AIShapeConstruction.h"
#include "AITransformArt.h"
#include "AICropArea.h"
#include "AIPath.h"

#include "ATETextSuitesImportHelper.h"
#include "AIATEPaint.h"
#include "AIATETextUtil.h"

#include "AIFilePath.h"

/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/


#ifndef GLOBALSTRUCT
#define GLOBALSTRUCT
	
	typedef struct {

#ifdef ADDS_MENU
	AIMenuItemHandle BCImposeMenuItemSelected;	
#endif
	
#ifdef ADDS_FILTER
	// these are used by filterHandler.c, addFilters( )
	AIFilterHandle filters[kMaxFilters];
	int numFilters;		
#endif

#ifdef ADDS_TOOL
	// these are used by toolHandler.c
	AIBoolean cursorLoaded;
	AIFixedPoint startingPoint, endPoint;	
#ifdef MAC_ENV
	CursHandle	cursor;
#endif // MAC_ENV
#ifdef WIN_ENV
	HCURSOR		cursor;
#endif // WIN_ENV

#endif // ADDS_TOOL
	
	ADMDialogRef nonModalDialog;
	SPAccessRef accessRef;
	SPBasicSuite *basic;
	AINotifierHandle appStartedNotifier, docOpenedNotifier, custColorChangeNotifier, swatchLibraryChangeNotifier,
			menuAfterNotifier;

	} Globals;

#endif

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
extern "C"  SPAccessSuite	*sSPAccess;
extern "C"	AIFixedMathSuite *sAIMath;
extern "C"	AIArtSuite *sAIArt;
extern "C" 	AI110UserSuite	*sAIUser;
extern "C"	AIAppContextSuite *sAIAppContext;
extern "C"	AIPreferenceSuite *sAIPreference;
extern "C"	SPAccessSuite *sSPAccess;

//added this
extern "C"	AIFilePathSuite *sAIFilePath;

extern "C"  AISwatchLibrariesSuite *sAISwatchLibrary;
extern "C"  AISwatchListSuite *sAISwatchList;
extern "C"  AISwatchGroupSuite *sAISwatchGroup;
extern "C"  AICustomColorSuite *sAICustomColor;

extern "C"  AIDictionarySuite *sAIDictionary;
extern "C"  AIDictionaryIteratorSuite *sAIDictionaryIterator;
extern "C"  AIEntrySuite *sAIEntry;

extern "C"  AIUIDSuite *sAIUID;
extern "C"  AIUIDREFSuite *sAIUIDREF;
extern "C"  AIUIDUtilsSuite *sAIUIDUtils;
extern "C"  AIUIDPoolSuite *sAIUIDPool;

extern "C"  AIDocumentListSuite *sAIDocumentList;
extern "C"  AIDocumentSuite *sAIDocument;
extern "C"  AIDocumentViewSuite *sAIDocumentView;

extern "C"  AIArtSetSuite *sAIArtSet;
extern "C"  AIArtStyleSuite *sAIArtStyle;
extern "C"  AIPathStyleSuite *sAIPathStyle;
extern "C"  AIRealMathSuite *sAIRealMath;
extern "C"  AIPlacedSuite *sAIPlaced;
extern "C"  AIForeignObjectSuite *sAIForeignObject;
extern "C"  AIFOConversionSuite *sAIFOConversion;
extern "C"  AILayerSuite *sAILayer;
extern "C"  AIMatchingArtSuite *sAIMatchingArt;
extern "C"  AIMdMemorySuite *sAIMdMemory;
extern "C"  AITextFrameSuite *sAITextFrame;
extern "C"  AIHardSoftSuite *sAIHardSoft;
extern "C"  AIShapeConstructionSuite *sAIShapeConstruction;
extern "C"  AITransformArtSuite *sAITransformArt;
extern "C"  AITransformArtSuite *sAITransformArt;
extern "C"  AIATEPaintSuite *sAIATEPaint;
extern "C"  AIATETextUtilSuite *sAIATETextUtil;
extern "C"  AICropAreaSuite *sAICropArea;
extern "C"  AIPathSuite *sAIPath;


// plug-in types
#ifdef  ADDS_MENU
extern "C" 	AIMenuSuite *sAIMenu;
#endif
#ifdef  ADDS_FILE_FORMAT
extern "C" 	AIFileFormatSuite *sAIFileFormat;
#endif
#ifdef  ADDS_FILTER
extern "C"	AIFilterSuite *sAIFilter;
#endif
#ifdef  ADDS_TOOL
extern "C"	AIToolSuite *sAITool;
#endif
#ifdef  ADDS_TIMER
extern "C"	AITimerSuite *sAITimer;
#endif
#ifdef  ADDS_NOTIFIER
extern "C"	AINotifierSuite *sAINotifier;
#endif
#ifdef  ADDS_TRANSFORM_AGAIN
extern "C"	AITransformAgainSuite *sTransformAgain;
#endif

extern "C" SPBlocksSuite *sSPBlocks;
//extern "C" ADMDialogSuite* sADMDialog;
//extern "C" ADMItemSuite7* sADMItem;
//extern "C" ADMNotifierSuite2* sADMNotifier;
//extern "C" AIUnicodeStringSuite *sAIUnicodeString;

extern "C"	ADMBasicSuite *sADMBasic;
//extern "C"  ADMIconSuite    *sADMIcon;
//extern "C"  ADMIconSuite2   *sADMIcon2;
//extern "C"	ADMListSuite	*sADMList;
//extern "C"	ADMDialogGroupSuite	*sADMDialogGroup;
//extern "C"	ADMEntrySuite	*sADMEntry;
//extern "C"	ADMTrackerSuite	*sADMTracker;



/**-----------------------------------------------------------------------------
 **
 **	suite support
 **
 **/

extern	AIErr acquireSuites( SPBasicSuite *sBasic );
extern	AIErr releaseSuites( SPBasicSuite *sBasic );



#endif // __Common_Shell_H__
