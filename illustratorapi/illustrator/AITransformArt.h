#ifndef __AITransformArt__
#define __AITransformArt__

/*
 *        Name:	AITransformArt.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Transform Art Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#include "AIHeaderBegin.h"

/** @file AITransformArt.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAITransformArtSuite			"AI Transform Art Suite"
#define kAITransformArtSuiteVersion1	AIAPI_VERSION(1)
#define kAITransformArtSuiteVersion		kAITransformArtSuiteVersion1
#define kAITransformArtVersion			kAITransformArtSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Options that control the behavior of \c #AITransformArtSuite::TransformArt() */
enum AITransformArtOptions {
	/** Transform object geometry */
	kTransformObjects			= ((long) (1<<0)),
	/** Apply the transform to gradient fills */
	kTransformFillGradients		= ((long) (1<<1)),
	/** Apply the transform to pattern fills */
	kTransformFillPatterns		= ((long) (1<<2)),
	/** Apply the transform to pattern strokes */
	kTransformStrokePatterns	= ((long) (1<<3)),
	/** Scale the stroke weights by the linescale factor */
	kScaleLines					= ((long) (1<<4)),
	/** Transform any opacity masks attached to the objects
		if they are set as linked. */
	kTransformLinkedMasks		= ((long) (1<<5)),
	/** Apply the transformation recursively. */
	kTransformChildren			= ((long) (1<<6)),
	/** Apply the transformation only to selected segments of path objects. */
	kTransformSelectionOnly		= ((long) (1<<7)),
	/** Notify parent plug-in groups of the transformation. Affects performance
		if \c #AITransformArtSuite::TransformArt() is called during a mouse drag loop. */
	kTransformNotifyPluginGroups = ((long) (1<<8))
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides a function that transforms an art object of any
	type by a given transformation matrix, making special transformation routines
	for the different art types unnecessary.

		\li Text art, raster art, and placed art objects have associated
			transformation matrices. Functions such as \c #AIRasterSuite::GetRasterMatrix()
			in the related suites provide access to the matrices.
			\c #TransformArt() does not use the associated matrix, but instead uses
			a matrix that you pass to the function.
		\li Path art objects are simple collections of connected line segments, and
			do not have an associated transformation matrix. For these, you must use
			the \c #TransformArt() function.

  	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITransformArtSuite and \c #kAITransformArtSuiteVersion.
 */
typedef struct {

	/** Transforms an art object by a given transformation matrix.
			@param art The art object.
			@param matrix The transformation matrix.
			@param lineScale The scale factor to apply if the object has a stroke
				and the \c #kScaleLines option is set.  Expressed as a percentage
				in the range [0..1], where 1 is 100%, meaning no scaling. Calculate the
                appropriate linescale as a function of the horizontal and vertical scale
				factors of the matrix: <code>lineScale = sqrt(Sx) * sqrt(Sy)</code>.
			@param flags Behavior options, a logical OR of \c #AITransformArtOptions constants.
			@note This function does not do a "deep" transform; that is, it does not
				automatically traverse into the members of group or compound art objects.
				If you wish to do this, you must traverse the artwork tree and call the
				function on the member art objects.
		*/
	AIAPI AIErr (*TransformArt) ( AIArtHandle art, AIRealMatrix *matrix, AIReal lineScale, long flags );

} AITransformArtSuite;

#include "AIHeaderEnd.h"


#endif
