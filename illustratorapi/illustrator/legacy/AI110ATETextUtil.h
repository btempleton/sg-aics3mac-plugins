#ifndef __AI110ATETextUtil__
#define __AI110ATETextUtil__

/*
 *        Name:	AI110ATETextUtil.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Text Frame Object Suite.
 *
 *				REQUIREMENT: This won't compile without a C++ compiler!
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __ATETextUtil__
#include "AIATETextUtil.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI110ATETextUtil.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110ATETextUtilSuite			kAIATETextUtilSuite
#define kAIATETextUtilSuiteVersion1		AIAPI_VERSION(1)
#define kAI110ATETextUtilSuiteVersion	kAIATETextUtilSuiteVersion1


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Utilities for working with text.
 */
struct AI110ATETextUtilSuite {
	/** Return the bounds of the text range (tr).  If the text range is hidden due to smaller
		frame size then an error #kAIATEInvalidBounds returned. */
	AIAPI AIErr (*GetBoundsFromTextRange)( ATE::TextRangeRef tr, ASRealRect* bounds );

	/** The application text resources object contains application global resources related
		to text. See the ATE APIs for more information. */
	AIAPI AIErr (*GetApplicationTextResources)( ATE::ApplicationTextResourcesRef *result );
	/** The document text resources object contains per document global resources related
		to text. See the ATE APIs for more information. */
	AIAPI AIErr (*GetTextResourcesFromDocument)( AIDocumentHandle pDocument, ATE::TextResourcesRef* pResources );

	// Comp Font
	AIAPI AIErr (*GetCompositeFont)( SPPlatformFileSpecification * file , ATE::CompFontRef * compFont );
	AIAPI AIErr (*WriteCompositeFont)( SPPlatformFileSpecification * spSpec, const ATE::CompFontRef compFontRef);

	// Kinsoku
	AIAPI AIErr (*GetKinsokuFile)( SPPlatformFileSpecification * file , ATE::KinsokuRef *kinsokuRef );
	AIAPI AIErr (*WriteKinsokuFile)( SPPlatformFileSpecification * spSpec, const ATE::KinsokuRef kinsokuRef );
	
	// Mojukumi
	AIAPI AIErr (*GetMojiKumiFile) ( SPPlatformFileSpecification * file , ATE::MojiKumiRef *mojikumeRef );
	AIAPI AIErr (*WriteMojiKumiFile)( SPPlatformFileSpecification * file, const ATE::MojiKumiRef mojikumeRef);

	AIAPI AIErr (*UpdateParagraphPaletteKinsoku) (int index);
	AIAPI AIErr (*UpdateParagraphPaletteMojiKumi)(int index);

	AIAPI AIErr (*GetSpellFile)( const SPPlatformFileSpecification* pSrcFileSpec, ATE::SpellRef* pDst );

	// Getting and setting the current font
	AIAPI AIErr (*SetCurrentFont)(AIFontKey theFont);
	AIAPI AIErr (*GetCurrentFont)(AIFontKey *result);
};


#include "AIHeaderEnd.h"


#endif
