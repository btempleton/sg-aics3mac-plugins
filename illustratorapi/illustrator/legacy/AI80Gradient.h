#ifndef __AI80Gradient__
#define __AI80Gradient__

/*
 *        Name:	AI80Gradient.h
 *   $Revision: 10 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Gradient Fill Suite.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AI80PathStyle__
#include "AI80PathStyle.h"
#endif

#include "AIGradient.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI80GradientSuite				kAIGradientSuite
#define kAIGradientSuiteVersion3		AIAPI_VERSION(3)
#define kAI80GradientSuiteVersion		kAIGradientSuiteVersion3


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct {

	AIGradientSetGrayUPP setGray;
	AIGradientSetCMYKUPP setCMYK;
	AIGradientBeginFillUPP beginFill;
	AIGradientEndFillUPP endFill;
	AIGradientMoveToUPP moveTo;
	AIGradientLineToUPP lineTo;
	AIGradientCurveToUPP curveTo;

} AI80GradientProcs;


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*NewGradient) ( AIGradientHandle *gradient );
	AIAPI AIErr (*DeleteGradient) ( AIGradientHandle gradient );
	AIAPI AIErr (*CountGradients) ( long *count );
	AIAPI AIErr (*GetNthGradient) ( long n, AIGradientHandle *gradient );
	AIAPI AIErr (*GetGradientByName) ( unsigned char *name, AIGradientHandle *gradient );
	AIAPI AIErr (*GetGradientName) ( AIGradientHandle gradient, unsigned char *name );
	AIAPI AIErr (*SetGradientName) ( AIGradientHandle gradient, unsigned char *name );
	AIAPI AIErr (*GetGradientType) ( AIGradientHandle gradient, short *type );
	AIAPI AIErr (*SetGradientType) ( AIGradientHandle gradient, short type );
	AIAPI AIErr (*GetGradientStopCount) ( AIGradientHandle gradient, short *count );
	AIAPI AIErr (*GetNthGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	AIAPI AIErr (*SetNthGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	AIAPI AIErr (*InsertGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	AIAPI AIErr (*DeleteGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	AIAPI AIErr (*IterateGradient) ( AIArtHandle art, AI110PathStyle *style, AI80GradientProcs *procs, short iterations );
	AIAPI AIErr (*NewGradientName) ( char *name, int maxlen ); //name is modified in place
	AIAPI AIErr (*GetGradientDisplayName) ( char *name ); //name is modified in place

	// New for AI8.0: report whether some AIGradientStop uses the given color
	// If matchTint is false and it is a custom color, any tint of that color counts
	AIAPI AIErr (*GradientUsesAIColor) (AIGradientHandle gradient, AIColor *color,
										AIBoolean matchTint, AIBoolean *usesColor);

} AI80GradientSuite;


#include "AIHeaderEnd.h"


#endif
