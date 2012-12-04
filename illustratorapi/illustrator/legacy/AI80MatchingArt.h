#ifndef __AI80MatchingArt__
#define __AI80MatchingArt__

/*
 *        Name:	AIMatchingArt.h
 *   $Revision: 4 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Matching Art Suite.
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

#ifndef __AIMatchingArt__
#include "AIMatchingArt.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI80MatchingArtSuite		"AI Matching Art Suite"
#define kAIMatchingArtSuiteVersion2	AIAPI_VERSION(2)
#define kAI80MatchingArtVersion		kAIMatchingArtSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*GetSelectedArt) ( AIArtHandle ***matches, long *numMatches );  // how 'bout AIArtObject *****matches?
	AIAPI AIErr (*GetMatchingArt) ( AIMatchingArtSpec *specs, short numSpecs, AIArtHandle ***matches, long *numMatches );

} AI80MatchingArtSuite;

#include "AIHeaderEnd.h"

#endif
