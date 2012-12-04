#ifndef __AI120CursorSnap__
#define __AI120CursorSnap__

/*
 *        Name:	AICursorSnap.h
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Cursor Snapping Suite.
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

#include "AICursorSnap.h"

#include "AIHeaderBegin.h"

/** @file AI120CursorSnap.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAICursorSnapSuiteVersion12		AIAPI_VERSION(1)
#define kAI120CursorSnapSuiteVersion	kAICursorSnapSuiteVersion12
#define kAI120CursorSnapSuite			kAICursorSnapSuite


typedef struct {

	/**
		Returns true if smart guides should be employed when snapping the
		cursor in the document view.
	 */
	AIAPI AIBoolean		(*UseSmartGuides)		(AIDocumentViewHandle view);

	/**
		Resets the snapping engine. This clears out all custom constraints
		and all automatically generated constraint lines.
	 */
	AIAPI AIErr			(*Reset)				(void);

	/**
		Clear all custom constraints without clearing automatically
		generated constraint lines.
	 */
	AIAPI AIErr			(*ClearCustom)			(void);
	/**
		Replace the current set of custom constraints with the specified set.
		The first parameter is the number of constraints being defined. The
		second is an array of custom constraints. A copy of the constraints
		is made so the caller may free the area afterward.
	 */
	AIAPI AIErr			(*SetCustom)			(long count, const AICursorConstraint* constraints);

	/**
		Snap the cursor in the given document view. The "Snap To Point" preference 
		is tested for snapping to art objects. The input point is the actual cursor 
		location in view coordinates. The event record is used to determine the state 
		of modifier keys. The control string specifies how snapping is performed. On 
		return dstpoint is filled in with the snapped cursor position.
	 */
	AIAPI AIErr			(*Track)				(AIDocumentViewHandle view, AIRealPoint srcpoint,
												const AIEvent* event, const char* control,
												AIRealPoint* dstpoint);

} AI120CursorSnapSuite;


#include "AIHeaderEnd.h"


#endif
