//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerSuites.h $
//
//  $Revision: #13 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __SnippetRunnerSuites__
#define __SnippetRunnerSuites__

#include "IllustratorSDK.h"

#include "AIStringFormatUtils.h"
#include "AIDocumentList.h"
#include "Suites.hpp"
#include "AIContext.h"
#include "AITracing.h"
#include "AIArt.h"
#include "AICountedObject.h"
#include "AIDictionary.h"
#include "AIArtSet.h"
#include "AIPlaced.h"
#include "AISymbol.h"
#include "AIRasterize.h"
#include "AILayer.h"
#include "AIPluginGroup.h"
#include "AISwatchList.h"
#include "AICustomColor.h"
#include "AIColorHarmony.h"
#include "AIPathStyle.h"
#include "AIMatchingArt.h"
#include "AIRealMath.h"
#include "AIColorConversion.h"
#include "ASUserInteraction.h"
#include "AIActionManager.h"
#include "AIFolders.h"
#include "AIDataFilter.h"
#include "AITextFrame.h"
#include "AILegacyTextConversion.h"
#include "AITool.h"
#include "AIATEPaint.h"
#include "AIFont.h"
#include "AIHardSoft.h"
#include "AIPath.h"
#include "AIATETextUtil.h"
#include "AIATECurrTextFeatures.h"
#include "AITextFrame.h"
#include "AIHitTest.h"
#include "ADMIcon.h"
#include "AIShapeConstruction.h"

// Declares suites used by SnippetRunner framework and its code snippets.
// Suites needed by snippets are added at the foot of the file

// Basic suites acquired by all plug-ins:
extern	"C"	SPBasicSuite*					sSPBasic;
extern  "C" SPAccessSuite*					sSPAccess;
extern  "C" SPPluginsSuite*					sSPPlugins;
extern  "C" AINotifierSuite*				sAINotifier;
extern  "C" AIAppContextSuite*				sAIAppContext;
extern  "C" ADMBasicSuite*					sADMBasic;
	
// Suites used by the SnippetRunner framework:
extern  "C" AIUnicodeStringSuite*		sAIUnicodeString;
extern  "C" SPBlocksSuite*				sSPBlocks;
extern  "C" ADMDialogSuite*				sADMDialog; // old suite needed for IADM wrapper class
extern  "C" ADMItemSuite7*				sADMItem;
extern  "C" ADMHierarchyListSuite2*		sADMHierarchyList;
extern	"C"	ADMListEntrySuite*			sADMListEntry;
extern	"C"	ADMEntrySuite*				sADMEntry;
extern	"C"	ADMListSuite*				sADMList;
extern	"C"	ADMNotifierSuite2*			sADMNotifier;
extern	"C"	AIMenuSuite*				sAIMenu;
extern	"C"	AIStringFormatUtilsSuite*	sAIStringFormatUtils;
extern	"C"	ADMEntrySuite6*				sADMEntry6;
extern	"C" AIPreferenceSuite*			sAIPreference;
extern	"C"	ADMTrackerSuite*			sADMTracker;
extern	"C"	AITimerSuite*				sAITimer;
extern	"C"	AIDataFilterSuite*			sAIDataFilter;
extern	"C" ADMIconSuite2*				sADMIcon2;

// Suites used by code snippets:
extern  "C" AIDocumentListSuite*			sAIDocumentList;
extern  "C" AIDocumentSuite*				sAIDocument;
extern  "C"	AITracingSuite*					sAITracing;
extern	"C" AIArtSuite*						sAIArt;
extern	"C" AICountedObjectSuite*			sAICountedObject;
extern	"C" AIDictionarySuite*				sAIDictionary;
extern	"C" AIArtSetSuite*					sAIArtSet;
extern	"C" AIPlacedSuite*					sAIPlaced;
extern	"C" AISymbolSuite*					sAISymbol;
extern	"C" AIRasterizeSuite*				sAIRasterize;
extern	"C" AILayerSuite*					sAILayer;
extern	"C" AIPluginGroupSuite*				sAIPluginGroup;
extern  "C"	AIFilePathSuite*				sAIFilePath;
extern  "C"	AIUserSuite*					sAIUser;
extern	"C" AISwatchListSuite*				sAISwatchList;
extern	"C" AISwatchGroupSuite*				sAISwatchGroup;
extern	"C" AICustomColorSuite*				sAICustomColor;
extern	"C" AIColorHarmonySuite*			sAIColorHarmony;
extern	"C" AIPathStyleSuite*				sAIPathStyle;
extern	"C" AIMatchingArtSuite*				sAIMatchingArt;
extern	"C"	ASUserInteractionSuite*			sASUserInteraction;
extern	"C"	AIActionManagerSuite*			sAIActionManager;
extern	"C"	AIFoldersSuite*					sAIFolders;
extern	"C" AIRealMathSuite*				sAIRealMath;
extern	"C" AIColorConversionSuite*			sAIColorConversion;
extern	"C" AITextFrameSuite*				sAITextFrame;
extern	"C" AILegacyTextConversionSuite*	sAILegacyTextConversion;
extern	"C" AIToolSuite*					sAITool;
extern	"C" AIATEPaintSuite*				sAIATEPaint;
extern	"C" AIFontSuite*					sAIFont;
extern	"C" AIHardSoftSuite*				sAIHardSoft;
extern	"C" AIPathSuite*					sAIPath;
extern	"C" AIATETextUtilSuite*				sAIATETextUtil;
extern	"C" AIATECurrentTextFeaturesSuite*	sAIATECurrentTextFeatures;	
extern	"C" AITextFrameHitSuite*			sAITextFrameHit;
extern	"C" AIHitTestSuite*					sAIHitTest;
extern	"C" AIShapeConstructionSuite*		sAIShapeConstruction;
// Add a line above to declare each additional suite your snippet needs.
// NOTE: Also edit SnippetRunnerSuites.cpp to define your suite pointer and add it to gPostStartupSuites.

#endif // __SnippetRunnerSuites__

//End SnippetRunnerSuites.h
