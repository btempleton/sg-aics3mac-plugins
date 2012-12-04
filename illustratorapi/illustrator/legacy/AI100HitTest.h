#ifndef __AI100HitTest__
#define __AI100HitTest__

/*
 *        Name:	AI100HitTest.h
 *   $Revision: 3 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Hit Testing Suite.
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

#include "AIHitTest.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI100HitTestSuite			kAIHitTestSuite
#define kAIHitTestSuiteVersion8		AIAPI_VERSION(1)
#define kAI100HitTestSuiteVersion	kAIHitTestSuiteVersion8


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {
	AIAPI AIErr (*HitTest) ( AIArtHandle art, AIRealPoint *point, long option, AIHitRef *hit );

	AIAPI long (*AddRef) ( AIHitRef hit );
	AIAPI long (*Release) ( AIHitRef hit );

	AIAPI AIErr (*GetHitData) ( AIHitRef hit, AIToolHitData *toolHit );

	AIAPI AIBoolean (*IsHit) ( AIHitRef hit );
	AIAPI long (*GetType) ( AIHitRef hit );
	AIAPI AIArtHandle (*GetArt) ( AIHitRef hit );
	AIAPI AIArtHandle (*GetGroup) ( AIHitRef hit );
	AIAPI AIRealPoint (*GetPoint) ( AIHitRef hit );

	/* Path specific */
	AIAPI short (*GetPathSegment) ( AIHitRef hit );
	AIAPI AIReal (*GetPathParameter) ( AIHitRef hit );

} AI100HitTestSuite;


#include "AIHeaderEnd.h"


#endif
