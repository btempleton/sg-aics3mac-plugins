#ifndef __AI110Gradient__
#define __AI110Gradient__

/*
 *        Name:	AIGradient.h
 *   $Revision: 11 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Gradient Fill Suite.
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

#include "AI80Gradient.h"


#include "AIHeaderBegin.h"

/** @file AI110Gradient.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110GradientSuite				kAIGradientSuite
#define kAIGradientSuiteVersion5		AIAPI_VERSION(5)
#define kAI110GradientSuiteVersion		kAIGradientSuiteVersion5
#define kAI110GradientVersion			kAI110GradientSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** A gradient is a graduated blend between two or more colors. The Gradient
	Suite provides functions to examine or modify existing gradients, create new
	gradients, or delete existing ones. The Gradient Suite provides for the basic
	definition of the gradient. A gradient instance applied to an art object is
	further defined by an AIGradientStyle which is part of an object's fill or
	stroke style.

	For other color information, see the AIPathStyleSuite, the AIPatternSuite, and
	the AICustomColorSuite.

	The suite functions are used to get and set the information which defines
	the gradient.

	The definition of an Illustrator blend is basically a description of the settings
	in the Illustrator Gradient palette. A gradient has three basic descriptors: the
	name, the type, and the number of color stops. The gradient name is required and
	is used when an object with a gradient is saved in a file. The gradient type can be
	one of two kinds of blends indicated by a constant: #kLinearGradient or
	#kRadialGradient.

	The gradient ramp describes where the color changes of the gradient occur and the
	points at which the change occurs are called gradient stops. The ramp has a range
	from 0 to 100, so the gradient stops will be within this range. The number of
	gradient stops is equal to the number of colors specified and there will always be
	at least two. The actual colors and their positions on the ramp are defined with the
	AIGradientStop structure.

	When a gradient is applied to an object, the gradient ramp will be scaled to
	the length of the gradient vector. The gradient stops are from 0 to 100% of
	the length needed to fully create the gradient along the vector.
*/
typedef struct {

	/** This function creates a new gradient and returns the handle in newGradient.
		The gradient is initialized as a linear gradient with two gradient stops, white
		and black. Once created, you should set the gradient’s name and type, and
		add gradient stops as needed. */
	AIAPI AIErr (*NewGradient) ( AIGradientHandle *gradient );
	/** Anywhere the gradient being deleted is being used will be replaced by black. */
	AIAPI AIErr (*DeleteGradient) ( AIGradientHandle gradient );
	/** Returns the number of gradients defined in the current document. Not all gradients
		need appear in the swatches palette so the count returned can exceed the number
		of gradient swatches defined. */
	AIAPI AIErr (*CountGradients) ( long *count );
	/** Get the nth gradient of the current document. The index is zero based. */
	AIAPI AIErr (*GetNthGradient) ( long n, AIGradientHandle *gradient );
	/** Pass a Pascal string with the name of an existing gradient to the function,
		which returns the corresponding gradient handle. If a gradient with that
		name is not found the value #kNameNotFoundErr is returned in the error
		code. */
	AIAPI AIErr (*GetGradientByName) ( unsigned char *name, AIGradientHandle *gradient );
	/** Returns the name of the gradient in the string pointed to by name.
		The name returned is a Pascal string. */
	AIAPI AIErr (*GetGradientName) ( AIGradientHandle gradient, unsigned char *name );
	/** The name must be a Pascal string. If the name already exists, #kNameNotFoundErr
		is returned. */
	AIAPI AIErr (*SetGradientName) ( AIGradientHandle gradient, unsigned char *name );
	/** The short that is returned will be one of two constants, #kLinearGradient
		or #kRadialGradient. */
	AIAPI AIErr (*GetGradientType) ( AIGradientHandle gradient, short *type );
	/** Sets the type of the gradient to the constant passed in type.
		type should be #kRadialGradient or #kLinearGradient. */
	AIAPI AIErr (*SetGradientType) ( AIGradientHandle gradient, short type );
	/** A gradient ramp has at least two stops (color transition points). This function
		will return the actual number for gradient in count. */
	AIAPI AIErr (*GetGradientStopCount) ( AIGradientHandle gradient, short *count );
	/** This is used to obtain information about the colors and blending of a
		gradient. Each of the color transition points on a gradient is called a stop.
		This function returns the stop of the gradient at index n. */
	AIAPI AIErr (*GetNthGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	/** Use this with GetNthGradientStop to modify an existing gradient stop. To
		create a new stop, you would use InsertGradientStop. */
	AIAPI AIErr (*SetNthGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	/** Add a new stop (color transition) to a gradient ramp. The new stop is created at
		position n, before stops equal to or greater than n. The gradient stop must be set
		to valid values before it is inserted into the gradient ramp. */
	AIAPI AIErr (*InsertGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	/** This function removes the gradient stop at index n from the indicated
		gradient. The information for the deleted stop is returned in the structure
		*stop. There must be at least two gradient stops. */
	AIAPI AIErr (*DeleteGradientStop) ( AIGradientHandle gradient, short n, AIGradientStop *stop );
	
	/** IterateGradient is called with a handle to art filled with a gradient. The
		gradient filling the artwork will be broken into sections along the gradient’s
		vector. The iterations parameter determines the number of sections. Each section
		is a region filled with a single color that can be represented by a path. These
		sections are enumerated to the AIGradientProcs supplied to IterateGradient, which
		can process them further. If you pass in 0 for the number of iterations, Illustrator
		will use the minimum number of iterations needed to produce a smooth color appearance.*/
	AIAPI AIErr (*IterateGradient) ( AIArtHandle art, AI110PathStyle *style, AI80GradientProcs *procs, short iterations );
	
	/** If no gradient exisits in the document with the specified name then it is
		unchanged. Otherwise a unique name is generated based on the given name. The
		name is modified in place. */
	AIAPI AIErr (*NewGradientName) ( char *name, int maxlen );
	AIAPI AIErr (*GetGradientDisplayName) ( char *name );

	/** Report whether some AIGradientStop uses the given color. If matchTint is false
		and it is a custom color, any tint of that color counts. */
	AIAPI AIErr (*GradientUsesAIColor) (AIGradientHandle gradient, AIColor *color,
										AIBoolean matchTint, AIBoolean *usesColor);

	/** Looks through the set of gradients defined for the current document to check that
		the input parameter is one of them. */
	AIAPI AIBoolean (*ValidateGradient) ( AIGradientHandle gradient );

	/* New in Illustrator 11.0 */
	
	/** Returns the color of the gradient ramp at the point 'percent' between 0 and 100.
		If the point matches a color stop it will be the color of the stop. Otherwise
		it is the interpolated color between stops. */
	AIAPI AIErr (*GetGradientColor) ( AIGradientHandle gradient, AIReal percent, AIColor *color );

} AI110GradientSuite;



#include "AIHeaderEnd.h"


#endif
