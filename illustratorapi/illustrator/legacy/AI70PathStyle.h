#ifndef __AI70PathStyle__
#define __AI70PathStyle__

/*
 *        Name:	AI70PathStyle.h
 *   $Revision: 5 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 7.0 Path Style Suite.
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


#ifndef __AI70Color__
#include "AI70Color.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#include "AIPathStyle.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI70PathStyleSuite			kAIPathStyleSuite
#define kAIPathStyleSuiteVersion2	AIAPI_VERSION(2)
#define kAIPathStyleSuiteVersion3	AIAPI_VERSION(3)
#define kAI70PathStyleSuiteVersion	kAIPathStyleSuiteVersion3

/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct {
	AI70Color color; 				/* Fill color */
	AIBoolean overprint;			/* Overprint */
} AI70FillStyle;

typedef struct {
	short length;				/* 0 if solid */
	AIFixed offset;				/* Dash offset */
	AIFixed array[kMaxDashComponents];	/* Dash array */
} AI70DashStyle;

typedef struct {
	AI70Color color;				/* Stroke color */
	AIBoolean overprint;		/* Overprint - not meaningful if ColorTag is pattern */
	AIFixed width;				/* Line width */
	AI70DashStyle dash;			/* Stroke dash */
	AILineCap cap;				/* Line cap */
	AILineJoin join;			/* Line join */
	AIFixed miterLimit;			/* Line miter limit */
} AI70StrokeStyle;

typedef struct {
	AIBoolean fillPaint;		/* Whether or not to fill the path */
	AIBoolean strokePaint;		/* Whether or not to stroke the path */
	AI70FillStyle fill;			/* Fill style, if fillPaint is true */
	AI70StrokeStyle stroke;		/* Stroke style, if strokePaint is true */
	AIBoolean clip;				/* Whether or not to use this as a clipping path */
	AIBoolean evenodd;			/* Whether or not to use the even-odd rule to determine path insideness */	
	AIFixed resolution;			/* Path's resolution */
	unsigned char note[256];
} AI70PathStyle;

typedef AI70PathStyle AIPathStyle55;
typedef AI70PathStyle AIPathStyle60;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Version 2 of path style suite */
typedef struct {

	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AI70PathStyle *style );
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, AI70PathStyle *style );
	AIAPI AIErr (*GetCurrentPathStyle) ( AIPathStyle60 *style );

} AIPathStyleSuite2;


/* Version 3 of path style suite */
typedef struct {

	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AI70PathStyle *style );
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, AI70PathStyle *style );
	AIAPI AIErr (*GetCurrentPathStyle) ( AI70PathStyle *style, AIPathStyleMap* stylemap );
	AIAPI AIErr (*SetCurrentPathStyle) ( AI70PathStyle *style, AIPathStyleMap* stylemap );
	AIAPI AIErr (*ImportStyles) ( SPPlatformFileSpecification *source, AIDocumentHandle *newdoc );

	/*Apply the AIColor to the object.  This does what is generally wanted when you've
	  got an AIColor and you've got an object, and you want the object painted with the
	  color.  It handles setting the gradient vector to the default, does the right thing
	  on compound paths, etc. ( If, for example, you have an object that's stroked with
	  a dashed line and you pass in a new color with the onStroke parameter true, the
	  old dash pattern will be retained.  If the object didn't have a stroke before,
	  the current paint style is looked at.  If the current paint style also doesn't have
	  a stroke, a sensible default is used. )*/
	AIAPI AIErr (*SetObjectAIColor) ( AIArtHandle art, AI70Color *color, AIBoolean onStroke );

} AI70PathStyleSuite;


#include "AIHeaderEnd.h"


#endif
