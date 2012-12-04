#ifndef __AI100Path__
#define __AI100Path__

/*
 *        Name:	AI100Path.h
 *     Purpose:	Adobe Illustrator 10.0 Path Object Suite.
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

#include "AIPath.h"
#include "AI110PathStyle.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100PathSuite			kAIPathSuite
#define kAIPathSuiteVersion4	AIAPI_VERSION(4)
#define kAI100PathSuiteVersion	kAIPathSuiteVersion4


/*******************************************************************************
 **
 **	Suite
 **
 **/


// Illustrator 10.0 Path Suite
typedef struct {

	AIAPI AIErr (*GetPathSegmentCount) ( AIArtHandle path, short *count );
	AIAPI AIErr (*SetPathSegmentCount) ( AIArtHandle path, short count );
	AIAPI AIErr (*GetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );
	AIAPI AIErr (*SetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );
	AIAPI AIErr (*InsertPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );
	AIAPI AIErr (*DeletePathSegments) ( AIArtHandle path, short segNumber, short count );

	AIAPI AIErr (*GetPathClosed) ( AIArtHandle path, AIBoolean *closed );
	AIAPI AIErr (*SetPathClosed) ( AIArtHandle path, AIBoolean closed );
	AIAPI AIErr (*GetPathGuide) ( AIArtHandle path, AIBoolean *isGuide );
	AIAPI AIErr (*SetPathGuide) ( AIArtHandle path, AIBoolean isGuide );

	AIAPI AIErr (*GetPathSegmentSelected)( AIArtHandle path, short segNumber, short *selected );

	AIAPI AIErr (*SetPathSegmentSelected)( AIArtHandle path, short segNumber, short selected );

	AIAPI AIErr (*ReversePathSegments) ( AIArtHandle path );
	AIAPI AIErr (*GetPathArea) ( AIArtHandle path, AIReal *area );

	// New for AI8.0:
	AIAPI AIErr (*GetPathLength) ( AIArtHandle path, AIReal *length, AIReal flatness );
	AIAPI AIErr (*GetPathBezier) ( AIArtHandle path, short segNumber, AIRealBezier *bezier );
	AIAPI AIErr (*PathHasLength) ( AIArtHandle path, AIBoolean *hasLength );
	
	AIAPI AIErr (*GetPathIsClip) ( AIArtHandle path, AIBoolean *isClip );	// path can be a compound path
																			// there is no SetIsClip because that is
																			// supposed to be done through AIGroup
	AIAPI AIErr (*AIPathStyleToAI70PathStyle)( AI110PathStyle *from, AI70PathStyle *to );
	AIAPI AIErr (*AI70PathStyleToAIPathStyle)( AI70PathStyle *from, AI110PathStyle *to );

} AI100PathSuite;


#include "AIHeaderEnd.h"


#endif
