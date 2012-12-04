//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TextFileFormat/Source/Common.h $
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

#ifndef __Common_Shell_H__
#define __Common_Shell_H__

// Declares globals shared by source files.

#include "IllustratorSDK.h"

/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/


#ifndef GLOBALSTRUCT
#define GLOBALSTRUCT
	
typedef struct {
	AIFileFormatHandle fileFormatAll;
	AIFileFormatHandle fileFormatSelected;
	AIMenuItemHandle	aboutPluginMenu;
} Globals;

#endif

/**-----------------------------------------------------------------------------
 **
 **	Globals
 **
 **/


// general globals
extern Globals *g;
extern SPAccessRef gSelfAccess;

// suite stuff
extern "C" SPAccessSuite *sSPAccess;
extern "C" SPBasicSuite *sSPBasic;
extern "C" SPBlocksSuite *sSPBlocks;

extern "C" AIMdMemorySuite *sAIMDMemory;
extern "C" AI110UserSuite *sAIUser;
extern "C" AIArtSetSuite *sAIArtSet;
extern "C" AIFileFormatSuite *sAIFileFormat;
extern "C" AIDocumentSuite *sAIDocument;
extern "C" AITextFrameSuite	*sAITextFrame;
extern "C" AIArtSuite *sAIArt;
extern "C" AIPathSuite *sAIPath;
extern "C" AIMatchingArtSuite *sAIMatchingArt;
extern "C" AIMdMemorySuite *sAIMdMemory;
extern "C" AIUnicodeStringSuite *sAIUnicodeString;
extern "C" AIFilePathSuite *sAIFilePath;

extern "C" ADMBasicSuite *sADMBasic;
extern "C" ADMDialogSuite *sADMDialog;
extern "C" ADMItemSuite7	*sADMItem;


/**-----------------------------------------------------------------------------
 **
 **	suite support
 **
 **/

extern	AIErr acquireSuites( SPBasicSuite *sBasic );
extern	AIErr releaseSuites( SPBasicSuite *sBasic );

#endif // __Common_Shell_H__