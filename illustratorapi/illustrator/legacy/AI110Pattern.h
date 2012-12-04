#ifndef __AI110Pattern__
#define __AI110Pattern__

/*
 *        Name:	AI110Pattern.h
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

#include "AIPattern.h"

#include "AI110PathStyle.h"

#include "AIHeaderBegin.h"


/** @file AI110Pattern.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110PatternSuite			kAIPatternSuite
#define kAIPatternSuiteVersion7		AIAPI_VERSION(7)
#define kAI110PatternSuiteVersion	kAIPatternSuiteVersion7
#define kAI110PatternVersion		kAIPatternSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	Patterns in Adobe Illustrator are used to fill or stroke with a repeating tile
	of art objects. The application of a pattern consists of two parts: the pattern
	definition and the instance parameters.
	
	The pattern definition is the artwork that defines the pattern tile. It is a
	group of art objects with the rear-most object being a square that defines the
	size of the tile. The square must be parallel to the x and y axes.

	The instance parameters are defined by the AIPatternStyle structure. They define
	how a pattern is used to paint a particular instance of a fill or stroke. In
	particular they define a transformation matrix that is used to position the
	pattern for the painting operation.

	Use the Pattern Suite to create, delete, and modify patterns.
 */
typedef struct {

	/** Creates a new pattern and initializes it. */
	AIAPI AIErr (*NewPattern) ( AIPatternHandle *newPattern );
	/** Deletes a pattern from the document global list. If the pattern is used for
		an object’s fill, the fill will made black. */
	AIAPI AIErr (*DeletePattern) ( AIPatternHandle pattern );
	/** The art of the specified pattern is placed into the current document at the
		center of the current view. */
	AIAPI AIErr (*GetPattern) ( AIPatternHandle pattern );
	/** SetPattern collects the artwork selected in the document and creates a
		pattern out of it. The artwork must be usable as a pattern. Basically, this
		is any object or group of objects making up the pattern with the rear-most
		object being a square the size of the tile. The square must be parallel to
		the x and y axes. Using invalid art will result in an AIErr 105. */
	AIAPI AIErr (*SetPattern) ( AIPatternHandle pattern );
	/** Returns the number of patterns in the document global list. */
	AIAPI AIErr (*CountPatterns) ( long *count );
	/** Returns the nth pattern in the document global list. If a pattern with that
		index is not found (index is out of bounds) the value #kNameNotFoundErr is
		return in the error code.*/
	AIAPI AIErr (*GetNthPattern) ( long n, AIPatternHandle *pattern );
	/** The function returns a reference to the art defining a pattern. The art object
		returned will be of type #kGroupArt. The AIArtHandle returned can be processed
		as any other AIArtHandle. */
	AIAPI AIErr (*GetPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );
	/** Sets the art used for the pattern to the group passed in art.
		The art object must be a group. The backmost object of the group must be a
		bounding rectangle with no fill and no stroke, and will be used in tiling the
		pattern. If you want to create a pattern with a particular fill, you would
		create a second rectangle with the appropriate fill and stroke above and
		with the same bounds as the bottommost one. If the backmost object of a group
		is not a no fill, no stroke rectangle, an error 105 will be returned. */
	AIAPI AIErr (*SetPatternArt) ( AIPatternHandle pattern, AIArtHandle art );
	/** Gets the pattern name. The returned name is a pascal string. */
	AIAPI AIErr (*GetPatternName) ( AIPatternHandle pattern, unsigned char *name );\
	/** Sets the pattern name from the pascal string. Pattern names must be unique
		within a document's global list. */
	AIAPI AIErr (*SetPatternName) ( AIPatternHandle pattern, unsigned char *name );
	/** Pass a Pascal string with the name of an existing pattern to the function,
		which returns the corresponding pattern handle. If a pattern with that name
		is not found, the value kNameNotFoundErr is returned in the error code. */
	AIAPI AIErr (*GetPatternByName) ( unsigned char *name, AIPatternHandle *pattern );
	/** Call IteratePattern with a handle to a path object and a pointer to a path
		style with a pattern fill. The path will be broken into tiles the size of the
		pattern. For each tile, any artwork needed to draw that tile on the page is
		generated. The generated artwork is passed to the AIPatternProc supplied to
		IteratePattern, which can process it further. */
	AIAPI AIErr (*IteratePattern) ( AIArtHandle art, AI110PathStyle *style, AIPatternProcPtr proc );
	/** Given a candidate name for a new pattern generates a name that is guaranteed
		to be unique. If the name is already unique it is not modified. maxlen
		should be the size of the character buffer. */
	AIAPI AIErr (*NewPatternName) ( char *name, int maxlen );
	/** Obsolete */
	AIAPI AIErr (*GetPatternDisplayName) ( char *name );
	/** Returns the bounds of the pattern tile. */
	AIAPI AIErr (*GetPatternTileBounds) ( AIPatternHandle pattern, AIRealRectPtr bounds );
	/** Returns true if the input pattern handle identifies a pattern in the current
		document's global list. */
	AIAPI AIBoolean (*ValidatePattern) ( AIPatternHandle pattern );

} AI110PatternSuite;


#include "AIHeaderEnd.h"


#endif
