#ifndef __AI110HitTest__
#define __AI110HitTest__

/*
*        Name:	AIHitTest.h
*   $Revision: 3 $
*      Author:	 
*        Date:	   
*     Purpose:	Adobe Illustrator 11.0 Hit Testing Suite.
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

/** @file AI110HitTest.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAIHitTestSuiteVersion11	AIAPI_VERSION(2)
#define kAI110HitTestSuiteVersion	kAIHitTestSuiteVersion11
#define kAI110HitTestSuite			kAIHitTestSuite


	/*******************************************************************************
**
**	Suite
**
**/


typedef struct {

	AIAPI AIErr (*HitTest) ( AIArtHandle art, AIRealPoint *point, long option, AIHitRef *hit );
	AIAPI AIErr (*HitTestEx) ( AIArtHandle art, AIRealPoint *point, AIReal tolerance, long option, AIHitRef *hit );
	AIAPI long (*AddRef) ( AIHitRef hit );
	AIAPI long (*Release) ( AIHitRef hit );
	AIAPI AIErr (*GetHitData) ( AIHitRef hit, AIToolHitData *toolHit );
	AIAPI AIBoolean (*IsHit) ( AIHitRef hit );
	AIAPI long (*GetType) ( AIHitRef hit );
	AIAPI AIArtHandle (*GetArt) ( AIHitRef hit );
	AIAPI AIArtHandle (*GetGroup) ( AIHitRef hit );
	AIAPI AIRealPoint (*GetPoint) ( AIHitRef hit );
	AIAPI short (*GetPathSegment) ( AIHitRef hit );
	AIAPI AIReal (*GetPathParameter) ( AIHitRef hit );

} AI110HitTestSuite;



#include "AIHeaderEnd.h"


#endif