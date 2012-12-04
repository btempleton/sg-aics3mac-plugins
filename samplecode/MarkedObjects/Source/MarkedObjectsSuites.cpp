//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsSuites.cpp $
//
//  $Revision: #5 $
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

#include "MarkedObjectsSuites.h"

extern "C" 
{ 
	ADMDialogSuite *sADMDialog; // old suite(s) needed for IADM usage
	ADMEntrySuite *sADMEntry;
	ADMItemSuite7* sADMItem;
	ADMListSuite *sADMList;
	ADMNotifierSuite2 *sADMNotifier;
	ADMIconSuite *sADMIcon;
	ADMDialogGroupSuite* sADMDialogGroup;

	AIArtSuite *sAIArt;
	AIDocumentSuite *sAIDocument;
	AIFileFormatSuite *sAIFileFormat;
	AIMatchingArtSuite *sAIMatchingArt;
	AIMdMemorySuite *sAIMdMemory;
	AIMenuSuite *sAIMenu;
	AIDictionarySuite *sAIDictionary;
	AIDictionaryIteratorSuite *sAIDictionaryIterator;
	AIPathSuite *sAIPath;
	AIPathStyleSuite *sAIPathStyle;
	AIPreferenceSuite* sAIPreference;
	AIToolSuite *sAITool;
	AILayerSuite* sAILayer;
	AITimerSuite* sAITimer;
	AIRuntimeSuite *sAIRuntime;
	AIUndoSuite *sAIUndo;
	AIUserSuite *sAIUser;


	AITextFrameSuite *sAITextFrame;
	AIFontSuite *sAIFont;


	AIFilePathSuite *sAIFilePath;
	AIUnicodeStringSuite *sAIUnicodeString;
	SPBlocksSuite *sSPBlocks;

	EXTERN_TEXT_SUITES 
}

ImportSuite gImportSuites[] = 
{
	kADMDialogSuite, kADMDialogSuiteVersion, &sADMDialog,
	kADMEntrySuite, kADMEntrySuiteVersion, &sADMEntry,

	kADMItemSuite, kADMItemSuiteVersion7, &sADMItem,

	kADMListSuite, kADMListSuiteVersion, &sADMList,
	kADMNotifierSuite, kADMNotifierSuiteVersion2, &sADMNotifier,
	kADMIconSuite, kADMIconSuiteVersion, &sADMIcon,
	kADMDialogGroupSuite, kADMDialogGroupSuiteVersion, &sADMDialogGroup,

	kAIArtSuite, kAIArtSuiteVersion, &sAIArt,
	kAIDocumentSuite, kAIDocumentVersion, &sAIDocument, 
	kAIFileFormatSuite, kAIFileFormatSuiteVersion, &sAIFileFormat,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, &sAIMatchingArt,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMdMemory,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIDictionarySuite, kAIDictionarySuiteVersion, &sAIDictionary,
	kAIDictionaryIteratorSuite, kAIDictionaryIteratorSuiteVersion, &sAIDictionaryIterator,
	kAIPathSuite, kAIPathSuiteVersion, &sAIPath,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, &sAIPathStyle,
	kAIPreferenceSuite, kAIPreferenceSuiteVersion, &sAIPreference,
	kAIToolSuite, kAIToolSuiteVersion, &sAITool,
	kAILayerSuite, kAILayerSuiteVersion, &sAILayer,
	kAITimerSuite, kAITimerSuiteVersion, &sAITimer,
	kAIRuntimeSuite, kAIRuntimeSuiteVersion, &sAIRuntime,
	kAIUndoSuite, kAIUndoSuiteVersion, &sAIUndo,
	kAIUserSuite, kAIUserSuiteVersion, &sAIUser,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kAIFilePathSuite, kAIFilePathSuiteVersion, &sAIFilePath,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	
	kAITextFrameSuite, kAITextFrameSuiteVersion, &sAITextFrame,
	kAIFontSuite, kAIFontSuiteVersion, &sAIFont,

	IMPORT_TEXT_SUITES

	nil, 0, nil
};
// end MarkedObjectsSuites.cpp