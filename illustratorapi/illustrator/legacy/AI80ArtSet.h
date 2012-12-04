#ifndef __AI80ArtSet__
#define __AI80ArtSet__

/*
 *        Name:	AI80ArtSet.h
 *   $Revision: 5 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Art Set Suite.
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

#include "AIArtSet.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI80ArtSetSuite		"AI Art Set Suite"
#define kAI80ArtSetSuiteVersion	AIAPI_VERSION(5)
#define kAI80ArtSetVersion		kAI80ArtSetSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*NewArtSet) ( AIArtSet *artSet );
	AIAPI AIErr (*DisposeArtSet) ( AIArtSet *artSet );
	AIAPI AIErr (*CountArtSet) ( AIArtSet artSet, long *count );
	AIAPI AIErr (*IndexArtSet) ( AIArtSet artSet, long index, AIArtHandle *art );

	AIAPI AIErr (*ArrayArtSet) ( AIArtSet artSet, AIArtHandle *artArray, long count );
	AIAPI AIErr (*SelectedArtSet) ( AIArtSet artSet );
	AIAPI AIErr (*MatchingArtSet) ( AIArtSpec *specs, short numSpecs, AIArtSet artSet );
	AIAPI AIErr (*LayerArtSet) ( AILayerHandle layer, AIArtSet artSet );
	
	AIAPI AIErr (*NotArtSet) ( AIArtSet src, AIArtSet dst );
	AIAPI AIErr (*UnionArtSet) ( AIArtSet src0, AIArtSet src1, AIArtSet dst );
	AIAPI AIErr (*IntersectArtSet) ( AIArtSet src0, AIArtSet src1, AIArtSet dst );

	AIAPI AIErr (*NextInArtSet) ( AIArtSet artSet, AIArtHandle prevArt, AIArtHandle *nextArt );

} AI80ArtSetSuite;


#include "AIHeaderEnd.h"


#endif
