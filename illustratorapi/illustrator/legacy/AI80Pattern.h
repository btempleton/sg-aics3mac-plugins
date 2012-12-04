#ifndef __AI80Pattern__
#define __AI80Pattern__

/*
 *        Name:	AI80Pattern.h
 *   $Revision: 10 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Pattern Fill Suite.
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


#ifndef __AIPattern__
#include "AIPattern.h"
#endif

#include "AI110PathStyle.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kAI80PatternSuite			kAIPatternSuite
#define kAIPatternSuiteVersion5		AIAPI_VERSION(5)
#define kAIPatternSuiteVersion6		AIAPI_VERSION(6)
#define kAI80PatternSuiteVersion	kAIPatternSuiteVersion6





/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*NewPattern) ( AIPatternHandle *newPattern );
	AIAPI AIErr (*DeletePattern) ( AIPatternHandle pattern );
	AIAPI AIErr (*GetPattern) ( AIPatternHandle pattern );
	AIAPI AIErr (*SetPattern) ( AIPatternHandle pattern );
	AIAPI AIErr (*CountPatterns) ( long *count );
	AIAPI AIErr (*GetNthPattern) ( long n, AIPatternHandle *pattern );
	AIAPI AIErr (*GetPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );
	AIAPI AIErr (*SetPatternArt) ( AIPatternHandle pattern, AIArtHandle art );
	AIAPI AIErr (*GetPatternName) ( AIPatternHandle pattern, unsigned char *name );
	AIAPI AIErr (*SetPatternName) ( AIPatternHandle pattern, unsigned char *name );
	AIAPI AIErr (*GetPatternByName) ( unsigned char *name, AIPatternHandle *pattern );
	AIAPI AIErr (*IteratePattern) ( AIArtHandle art, AI110PathStyle *style, AIPatternProcPtr proc );
	AIAPI AIErr (*NewPatternName) ( char *name, int maxlen ); //name is modified in place
	AIAPI AIErr (*GetPatternDisplayName) ( char *name ); //name is modified in place
	AIAPI AIErr (*GetPatternTileBounds) ( AIPatternHandle pattern, AIRealRectPtr bounds );

} AI80PatternSuite;


#include "AIHeaderEnd.h"


#endif
