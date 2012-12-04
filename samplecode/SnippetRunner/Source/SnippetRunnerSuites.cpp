//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerSuites.cpp $
//
//  $Revision: #14 $
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
#include "SnippetRunnerSuites.h"
#include "ATETextSuitesImportHelper.h"

// Defines pointers for suites used by code snippets.
extern "C" 
{
	AIDocumentListSuite*			sAIDocumentList = NULL;
	AIDocumentSuite*				sAIDocument = NULL;
	AITracingSuite*					sAITracing = NULL;
	AIArtSuite*						sAIArt = NULL;
	AICountedObjectSuite*			sAICountedObject = NULL;
	AIDictionarySuite*				sAIDictionary = NULL;
	AIArtSetSuite*					sAIArtSet = NULL;
	AIPlacedSuite*					sAIPlaced = NULL;
	AISymbolSuite*					sAISymbol = NULL;
	AIRasterizeSuite*				sAIRasterize = NULL;
	AILayerSuite*					sAILayer = NULL;
	AIPluginGroupSuite*				sAIPluginGroup = NULL;
	AIFilePathSuite*				sAIFilePath = NULL;
	AIUserSuite*					sAIUser = NULL;
	AISwatchListSuite*				sAISwatchList = NULL;
	AISwatchGroupSuite*				sAISwatchGroup = NULL;
	AICustomColorSuite*				sAICustomColor = NULL;
	AIColorHarmonySuite*			sAIColorHarmony = NULL;
	AIPathStyleSuite*				sAIPathStyle = NULL;
	AIMatchingArtSuite*				sAIMatchingArt = NULL;
	ASUserInteractionSuite*			sASUserInteraction = NULL;
	AIActionManagerSuite*			sAIActionManager = NULL;
	AIFoldersSuite*					sAIFolders = NULL;
	AIRealMathSuite*				sAIRealMath = NULL;
	AIColorConversionSuite*			sAIColorConversion = NULL;
	AITextFrameSuite*				sAITextFrame = NULL;
	AILegacyTextConversionSuite*	sAILegacyTextConversion = NULL;
	AIToolSuite*					sAITool = NULL;
	AIATEPaintSuite*				sAIATEPaint = NULL;
	AIFontSuite*					sAIFont = NULL;
	AIHardSoftSuite*				sAIHardSoft = NULL;
	AIPathSuite*					sAIPath = NULL;
	AIATETextUtilSuite*				sAIATETextUtil = NULL;
	AIATECurrentTextFeaturesSuite*	sAIATECurrentTextFeatures = NULL;
	AITextFrameHitSuite*			sAITextFrameHit = NULL;
	AIHitTestSuite*					sAIHitTest = NULL;
	AIShapeConstructionSuite*		sAIShapeConstruction = NULL;
	EXTERN_TEXT_SUITES
	// Add a line above for each additional suite your snippet needs.
	// NOTE: Also add a line to gPostStartupSuites and edit SnippetRunnerSuites.h to declare your suite pointer.
};

// Identifies suites used by code snippets.
// Acquired on application startup (kAIApplicationStartupNotifier) and released on plug-in shutdown.
ImportSuite		gPostStartupSuites[] = {

	kAIDocumentListSuite, kAIDocumentListSuiteVersion, &sAIDocumentList,
	kAIDocumentSuite, kAIDocumentSuiteVersion, &sAIDocument,
	kAITracingSuite, kAITracingVersion, &sAITracing,
	kAIArtSuite, kAIArtSuiteVersion, &sAIArt,
	kAICountedObjectSuite, kAICountedObjectSuiteVersion, &sAICountedObject,
	kAIDictionarySuite, kAIDictionarySuiteVersion, &sAIDictionary,
	kAIArtSetSuite, kAIArtSetSuiteVersion, &sAIArtSet,
	kAIPlacedSuite, kAIPlacedSuiteVersion, &sAIPlaced,
	kAISymbolSuite, kAISymbolSuiteVersion, &sAISymbol,
	kAIRasterizeSuite, kAIRasterizeSuiteVersion, &sAIRasterize,
	kAILayerSuite,kAILayerSuiteVersion, &sAILayer,
	kAIPluginGroupSuite, kAIPluginGroupSuiteVersion, &sAIPluginGroup,
	kAIFilePathSuite, kAIFilePathVersion, &sAIFilePath,
	kAIUserSuite, kAIUserSuiteVersion, &sAIUser,
	kAISwatchListSuite, kAISwatchListSuiteVersion, &sAISwatchList,
	kAISwatchGroupSuite, kAISwatchGroupSuiteVersion, &sAISwatchGroup,
	kAICustomColorSuite, kAICustomColorSuiteVersion, &sAICustomColor,
	kAIColorHarmonySuite, kAIColorHarmonySuiteVersion, &sAIColorHarmony,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, &sAIPathStyle,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, &sAIMatchingArt,
	kASUserInteractionSuite, kASUserInteractionSuiteVersion, &sASUserInteraction,
	kAIActionManagerSuite, kAIActionManagerVersion, &sAIActionManager,
	kAIFoldersSuite, kAIFoldersVersion, &sAIFolders,
	kAIRealMathSuite, kAIRealMathSuiteVersion, &sAIRealMath,
	kAIColorConversionSuite, kAIColorConversionSuiteVersion, &sAIColorConversion,
	kAITextFrameSuite, kAITextFrameSuiteVersion, &sAITextFrame,
	kAILegacyTextConversionSuite, kAILegacyTextConversionSuiteVersion, &sAILegacyTextConversion,
	kAIToolSuite, kAIToolSuiteVersion, &sAITool,
	kAIATEPaintSuite, kAIATEPaintSuiteVersion, &sAIATEPaint,
	kAIFontSuite, kAIFontSuiteVersion, &sAIFont,
	kAIHardSoftSuite, kAIHardSoftSuiteVersion, &sAIHardSoft,
	kAIPathSuite, kAIPathSuiteVersion, &sAIPath,
	kAIATETextUtilSuite, kAIATETextUtilSuiteVersion, &sAIATETextUtil,
	kAIATECurrentTextFeaturesSuite, kAIATECurrentTextFeaturesSuiteVersion, &sAIATECurrentTextFeatures,
	kAITextFrameHitSuite, kAITextFrameHitSuiteVersion, &sAITextFrameHit,
	kAIHitTestSuite, kAIHitTestSuiteVersion, &sAIHitTest,
	kAIShapeConstructionSuite, kAIShapeConstructionSuiteVersion, &sAIShapeConstruction,
	// Add a line above for each additional suite your snippet needs.
	IMPORT_TEXT_SUITES
	nil, 0, nil
};

// Defines pointers for suites used by the SnippetRunner framework.
extern "C" 
{
	AIUnicodeStringSuite*		sAIUnicodeString = NULL;
	SPBlocksSuite*				sSPBlocks = NULL;
	ADMDialogSuite*				sADMDialog = NULL; // old suite(s) needed for IADM usage
	ADMItemSuite7*				sADMItem = NULL;
	ADMHierarchyListSuite2*		sADMHierarchyList = NULL;
	ADMListEntrySuite*			sADMListEntry = NULL;
	ADMEntrySuite*				sADMEntry = NULL;
	ADMListSuite*				sADMList = NULL;
	ADMNotifierSuite2*			sADMNotifier = NULL;
	AIMenuSuite*				sAIMenu = NULL;
	AIStringFormatUtilsSuite*	sAIStringFormatUtils = NULL;
	ADMEntrySuite6*				sADMEntry6 = NULL;
	AIPreferenceSuite*			sAIPreference = NULL;
	ADMTrackerSuite*			sADMTracker = NULL;
	AITimerSuite*				sAITimer = NULL;
	AIDataFilterSuite*			sAIDataFilter = NULL;
	ADMIconSuite2*				sADMIcon2 = NULL;
};

// Identifies the suites acquired on plug-in startup (Plugin::StartupPlugin) and released on plug-in shutdown.
ImportSuite gImportSuites[] = 
{
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kADMDialogSuite, kADMDialogSuiteVersion, &sADMDialog,
	kADMItemSuite, kADMItemSuiteVersion7, &sADMItem,
	kADMHierarchyListSuite, kADMHierarchyListSuiteVersion2, &sADMHierarchyList,
	kADMListEntrySuite, kADMListEntrySuiteVersion, &sADMListEntry,
	kADMEntrySuite, kADMEntrySuiteVersion, &sADMEntry,
	kADMListSuite, kADMListSuiteVersion, &sADMList,
	kADMNotifierSuite, kADMNotifierSuiteVersion2, &sADMNotifier,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsVersion, &sAIStringFormatUtils,
	kADMEntrySuite, kADMEntrySuiteVersion6, &sADMEntry6,
	kAIPreferenceSuite, kAIPreferenceSuiteVersion, &sAIPreference,
	kADMTrackerSuite, kADMTrackerSuiteVersion, &sADMTracker,
	kAITimerSuite, kAITimerSuiteVersion, &sAITimer,
	kAIDataFilterSuite, kAIDataFilterSuiteVersion, &sAIDataFilter,
	kADMIconSuite, kADMIconSuiteVersion2, &sADMIcon2,
	nil, 0, nil
};

// End SnippetRunnerSuites.cpp
