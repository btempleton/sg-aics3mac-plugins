//========================================================================================
//  
//  $File: BstatMU Suites.h $
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

#include "ATETextSuitesImportHelper.h"



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
	
	AIDictionarySuite *sAIDictionary = nil;
	AIDictionaryIteratorSuite *sAIDictionaryIterator = nil;
	AIEntrySuite *sAIEntry = nil;
	
	AIUIDSuite *sAIUID = nil;
	AIUIDREFSuite *sAIUIDREF = nil;
	AIUIDUtilsSuite *sAIUIDUtils = nil;
	AIUIDPoolSuite *sAIUIDPool = nil;
	
	AIDocumentListSuite *sAIDocumentList = nil;
	AIDocumentSuite *sAIDocument = nil;
	AIDocumentViewSuite *sAIDocumentView = nil;
	AIArtSetSuite *sAIArtSet = nil;
	AIArtStyleSuite *sAIArtStyle = nil;
	AIPathStyleSuite *sAIPathStyle = nil;
	AIRealMathSuite *sAIRealMath = nil;
	AIPlacedSuite *sAIPlaced = nil;
	AIForeignObjectSuite *sAIForeignObject = nil;
	AIFOConversionSuite *sAIFOConversion = nil;
	AILayerSuite *sAILayer = nil;
	AIMatchingArtSuite *sAIMatchingArt = nil;
	AIMdMemorySuite *sAIMdMemory = nil;
	AITextFrameSuite *sAITextFrame = nil;
	AIHardSoftSuite *sAIHardSoft = nil;
	AIShapeConstructionSuite *sAIShapeConstruction = nil;
	AITransformArtSuite *sAITransformArt = nil;
	AIATEPaintSuite *sAIATEPaint = nil;
	AIATETextUtilSuite *sAIATETextUtil = nil;
	AICropAreaSuite *sAICropArea = nil;
	AIPathSuite *sAIPath = nil;
	
	AIFilePathSuite *sAIFilePath = nil;
	AIUndoSuite *sAIUndo = nil;
	
	EXTERN_TEXT_SUITES
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
	
	kAIDictionarySuite, kAIDictionarySuiteVersion, (void**)&sAIDictionary,
	kAIDictionaryIteratorSuite, kAIDictionaryIteratorSuiteVersion, (void**)&sAIDictionaryIterator,
	kAIEntrySuite, kAIEntrySuiteVersion, (void**)&sAIEntry,
	
	kAIUIDSuite, kAIUIDSuiteVersion, (void**)&sAIUID,
	kAIUIDREFSuite, kAIUIDREFSuiteVersion, (void**)&sAIUIDREF,
	kAIUIDUtilsSuite, kAIUIDUtilsSuiteVersion, (void**)&sAIUIDUtils,
	kAIUIDPoolSuite, kAIUIDPoolSuiteVersion, (void**)&sAIUIDPool,
	
	kAIDocumentListSuite, kAIDocumentListVersion, (void**)&sAIDocumentList,
	kAIDocumentSuite, kAIDocumentSuiteVersion, (void**)&sAIDocument,
	kAIDocumentViewSuite, kAIDocumentViewSuiteVersion, (void**)&sAIDocumentView,
	kAIArtSetSuite, kAIArtSetSuiteVersion, (void**)&sAIArtSet,
	kAIArtStyleSuite, kAIArtStyleSuiteVersion, (void**)&sAIArtStyle,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, (void**)&sAIPathStyle,
	kAIRealMathSuite, kAIRealMathSuiteVersion, (void**)&sAIRealMath,
	kAIPlacedSuite, kAIPlacedSuiteVersion, (void**)&sAIPlaced,
	kAIForeignObjectSuite, kAIForeignObjectVersion, (void**)&sAIForeignObject,
	kAIFOConversionSuite, kAIFOConversionVersion, (void**)&sAIFOConversion,
	kAILayerSuite, kAILayerVersion, (void**)&sAILayer,
	kAIMatchingArtSuite, kAIMatchingArtVersion, (void**)&sAIMatchingArt,
	kAIMdMemorySuite, kAIMdMemoryVersion, (void**)&sAIMdMemory,
	kAIHardSoftSuite, kAIHardSoftVersion, (void**)&sAIHardSoft,
	kAIShapeConstructionSuite, kAIShapeConstructionVersion, (void**)&sAIShapeConstruction,
	kAIPathSuite, kAIPathSuiteVersion, (void**)&sAIPath,
	
	// I couldn't use the macro IMPORT_TEXT_SUITES because I need the (void**)
	kApplicationPaintSuite, kApplicationPaintSuiteVersion, (void**)&sApplicationPaint,\
	kCompFontSuite, kCompFontSuiteVersion, (void**)&sCompFont,\
	kCompFontClassSuite, kCompFontClassSuiteVersion, (void**)&sCompFontClass,\
	kCompFontClassSetSuite, kCompFontClassSetSuiteVersion, (void**)&sCompFontClassSet,\
	kCompFontComponentSuite, kCompFontComponentSuiteVersion, (void**)&sCompFontComponent,\
	kCompFontSetSuite, kCompFontSetSuiteVersion, (void**)&sCompFontSet,\
	kGlyphRunSuite, kGlyphRunSuiteVersion, (void**)&sGlyphRun,\
	kGlyphRunsIteratorSuite, kGlyphRunsIteratorSuiteVersion, (void**)&sGlyphRunsIterator,\
	kMojiKumiSuite, kMojiKumiSuiteVersion, (void**)&sMojiKumi,\
	kMojiKumiSetSuite, kMojiKumiSetSuiteVersion, (void**)&sMojiKumiSet,\
	kTextFrameSuite, kTextFrameSuiteVersion, (void**)&sTextFrame,\
	kTextFramesIteratorSuite, kTextFramesIteratorSuiteVersion, (void**)&sTextFramesIterator,\
	kTextLineSuite, kTextLineSuiteVersion, (void**)&sTextLine,\
	kTextLinesIteratorSuite, kTextLinesIteratorSuiteVersion, (void**)&sTextLinesIterator,\
	kTextResourcesSuite, kTextResourcesSuiteVersion, (void**)&sTextResources,\
	kApplicationTextResourcesSuite, kApplicationTextResourcesSuiteVersion, (void**)&sApplicationTextResources,\
	kDocumentTextResourcesSuite, kDocumentTextResourcesSuiteVersion, (void**)&sDocumentTextResources,\
	kArrayApplicationPaintRefSuite, kArrayApplicationPaintRefSuiteVersion, (void**)&sArrayApplicationPaintRef,\
	kArrayRealSuite, kArrayRealSuiteVersion, (void**)&sArrayReal,\
	kArrayBoolSuite, kArrayBoolSuiteVersion, (void**)&sArrayBool,\
	kArrayIntegerSuite, kArrayIntegerSuiteVersion, (void**)&sArrayInteger,\
	kArrayLineCapTypeSuite, kArrayLineCapTypeSuiteVersion, (void**)&sArrayLineCapType,\
	kArrayFigureStyleSuite, kArrayFigureStyleSuiteVersion, (void**)&sArrayFigureStyle,\
	kArrayLineJoinTypeSuite, kArrayLineJoinTypeSuiteVersion, (void**)&sArrayLineJoinType,\
	kArrayWariChuJustificationSuite, kArrayWariChuJustificationSuiteVersion, (void**)&sArrayWariChuJustification,\
	kArrayStyleRunAlignmentSuite, kArrayStyleRunAlignmentSuiteVersion, (void**)&sArrayStyleRunAlignment,\
	kArrayAutoKernTypeSuite, kArrayAutoKernTypeSuiteVersion, (void**)&sArrayAutoKernType,\
	kArrayBaselineDirectionSuite, kArrayBaselineDirectionSuiteVersion, (void**)&sArrayBaselineDirection,\
	kArrayLanguageSuite, kArrayLanguageSuiteVersion, (void**)&sArrayLanguage,\
	kArrayFontCapsOptionSuite, kArrayFontCapsOptionSuiteVersion, (void**)&sArrayFontCapsOption,\
	kArrayFontBaselineOptionSuite, kArrayFontBaselineOptionSuiteVersion, (void**)&sArrayFontBaselineOption,\
	/*	kArrayVerticalUnderlinePositionSuite, kArrayVerticalUnderlinePositionSuiteVersion, (void**)&sArrayVerticalUnderlinePosition,\*/
	kArrayParagraphJustificationSuite, kArrayParagraphJustificationSuiteVersion, (void**)&sArrayParagraphJustification,\
	kArrayArrayRealSuite, kArrayArrayRealSuiteVersion, (void**)&sArrayArrayReal,\
	kArrayBurasagariTypeSuite, kArrayBurasagariTypeSuiteVersion, (void**)&sArrayBurasagariType,\
	kArrayPreferredKinsokuOrderSuite, kArrayPreferredKinsokuOrderSuiteVersion, (void**)&sArrayPreferredKinsokuOrder,\
	kArrayKinsokuRefSuite, kArrayKinsokuRefSuiteVersion, (void**)&sArrayKinsokuRef,\
	kArrayMojiKumiRefSuite, kArrayMojiKumiRefSuiteVersion, (void**)&sArrayMojiKumiRef,\
	kArrayMojiKumiSetRefSuite, kArrayMojiKumiSetRefSuiteVersion, (void**)&sArrayMojiKumiSetRef,\
	kArrayTabStopsRefSuite, kArrayTabStopsRefSuiteVersion, (void**)&sArrayTabStopsRef,\
	kArrayLeadingTypeSuite, kArrayLeadingTypeSuiteVersion, (void**)&sArrayLeadingType,\
	kArrayFontRefSuite, kArrayFontRefSuiteVersion, (void**)&sArrayFontRef,\
	kArrayGlyphIDSuite, kArrayGlyphIDSuiteVersion, (void**)&sArrayGlyphID,\
	kArrayRealPointSuite, kArrayRealPointSuiteVersion, (void**)&sArrayRealPoint,\
	kArrayRealMatrixSuite, kArrayRealMatrixSuiteVersion, (void**)&sArrayRealMatrix,\
	kCharFeaturesSuite, kCharFeaturesSuiteVersion, (void**)&sCharFeatures,\
	kCharInspectorSuite, kCharInspectorSuiteVersion, (void**)&sCharInspector,\
	kCharStyleSuite, kCharStyleSuiteVersion, (void**)&sCharStyle,\
	kCharStylesSuite, kCharStylesSuiteVersion, (void**)&sCharStyles,\
	kCharStylesIteratorSuite, kCharStylesIteratorSuiteVersion, (void**)&sCharStylesIterator,\
	kFindSuite, kFindSuiteVersion, (void**)&sFind,\
	kFontSuite, kFontSuiteVersion, (void**)&sFont,\
	kGlyphSuite, kGlyphSuiteVersion, (void**)&sGlyph,\
	kGlyphsSuite, kGlyphsSuiteVersion, (void**)&sGlyphs,\
	kGlyphsIteratorSuite, kGlyphsIteratorSuiteVersion, (void**)&sGlyphsIterator,\
	kKinsokuSuite, kKinsokuSuiteVersion, (void**)&sKinsoku,\
	kKinsokuSetSuite, kKinsokuSetSuiteVersion, (void**)&sKinsokuSet,\
	kParaFeaturesSuite, kParaFeaturesSuiteVersion, (void**)&sParaFeatures,\
	kParagraphSuite, kParagraphSuiteVersion, (void**)&sParagraph,\
	kParagraphsIteratorSuite, kParagraphsIteratorSuiteVersion, (void**)&sParagraphsIterator,\
	kParaInspectorSuite, kParaInspectorSuiteVersion, (void**)&sParaInspector,\
	kParaStyleSuite, kParaStyleSuiteVersion, (void**)&sParaStyle,\
	kParaStylesSuite, kParaStylesSuiteVersion, (void**)&sParaStyles,\
	kParaStylesIteratorSuite, kParaStylesIteratorSuiteVersion, (void**)&sParaStylesIterator,\
	kSpellSuite, kSpellSuiteVersion, (void**)&sSpell,\
	kStoriesSuite, kStoriesSuiteVersion, (void**)&sStories,\
	kStorySuite, kStorySuiteVersion, (void**)&sStory,\
	kTabStopSuite, kTabStopSuiteVersion, (void**)&sTabStop,\
	kTabStopsSuite, kTabStopsSuiteVersion, (void**)&sTabStops,\
	kTabStopsIteratorSuite, kTabStopsIteratorSuiteVersion, (void**)&sTabStopsIterator,\
	kTextRangeSuite, kTextRangeSuiteVersion, (void**)&sTextRange,\
	kTextRangesSuite, kTextRangesSuiteVersion, (void**)&sTextRanges,\
	kTextRangesIteratorSuite, kTextRangesIteratorSuiteVersion, (void**)&sTextRangesIterator,\
	kTextRunsIteratorSuite, kTextRunsIteratorSuiteVersion, (void**)&sTextRunsIterator,\
	kWordsIteratorSuite, kWordsIteratorSuiteVersion, (void**)&sWordsIterator,\
	
	kAITextFrameSuite, kAITextFrameVersion, (void**)&sAITextFrame,
	kAITransformArtSuite, kAITransformArtVersion, (void**)&sAITransformArt,
	kAIATEPaintSuite, kAIATEPaintVersion, (void**)&sAIATEPaint,
	kAIATETextUtilSuite, kAIATETextUtilSuiteVersion, (void**)&sAIATETextUtil,
	kAICropAreaSuite, kAICropAreaSuiteVersion, (void**)&sAICropArea,
	
	kAIFilePathSuite, kAIFilePathSuiteVersion, (void**)&sAIFilePath,
	kAIUndoSuite, kAIUndoSuiteVersion, (void**)&sAIUndo,
	
	
};

#endif __Suites_Shell_H__