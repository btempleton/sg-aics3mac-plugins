//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Webter/Source/WebterSuites.cpp $
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

#include "IllustratorSDK.h"

#include "Suites.hpp"

#include "AppContext.hpp"

#include "ADMDialog.h"
#include "ADMDialogGroup.h"
#include "ADMEntry.h"
#include "ADMItem.h"
#include "ADMList.h"
#include "ADMNotifier.h"
#include "ADMDrawer.h"
#include "ADMImage.h"

#include "AIArt.h"
#include "AIDocument.h"
#include "AIMatchingArt.h"
#include "AIMdMemory.h"
#include "AIPreference.h"
#include "AIMenu.h"
#include "AIDictionary.h"

extern "C" {
	SPBlocksSuite *sSPBlocks;
	ADMDialogSuite *sADMDialog;
	ADMDialogGroupSuite *sADMDialogGroup;
	ADMEntrySuite *sADMEntry;
	ADMItemSuite7 *sADMItem;
	ADMListSuite *sADMList;
	ADMNotifierSuite2 *sADMNotifier;
	ADMDrawerSuite *sADMDrawer;
	ADMImageSuite *sADMImage;
	ADMHierarchyListSuite2 *sADMHierarchyList;

	AI110ArtSuite *sAIArt;
	AI110DocumentSuite *sAIDocument;
	AIMatchingArtSuite *sAIMatchingArt;
	AIMdMemorySuite *sAIMdMemory;
	AIPreferenceSuite *sAIPreference;
	AIMenuSuite *sAIMenu;
	AIDictionarySuite *sAIDictionary;
	AIDictionaryIteratorSuite *sAIDictionaryIterator;
	AIUnicodeStringSuite *sAIUnicodeString;
}

ImportSuite gImportSuites[] = 
{
	kADMDialogSuite, kADMDialogSuiteVersion, &sADMDialog,
	kADMDialogGroupSuite, kADMDialogGroupSuiteVersion, &sADMDialogGroup,
	kADMEntrySuite, kADMEntrySuiteVersion, &sADMEntry,
	kADMItemSuite, kADMItemSuiteVersion7, &sADMItem,
	kADMListSuite, kADMListSuiteVersion, &sADMList,
	kADMNotifierSuite, kADMNotifierSuiteVersion2, &sADMNotifier,
	kADMDrawerSuite, kADMDrawerSuiteVersion6, &sADMDrawer,
	kADMImageSuite, kADMImageSuiteVersion2, &sADMImage,
	kADMHierarchyListSuite, kADMHierarchyListSuiteVersion5, &sADMHierarchyList,

	kAIArtSuite, kAI110ArtSuiteVersion, &sAIArt,
	kAIDocumentSuite, kAI110DocumentVersion, &sAIDocument,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, &sAIMatchingArt,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMdMemory,
	kAIPreferenceSuite, kAIPreferenceSuiteVersion, &sAIPreference,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIDictionarySuite, kAIDictionarySuiteVersion, &sAIDictionary,
	kAIDictionaryIteratorSuite, kAIDictionaryIteratorSuiteVersion, &sAIDictionaryIterator,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion,&sAIUnicodeString,

	nil, 0, nil
};

