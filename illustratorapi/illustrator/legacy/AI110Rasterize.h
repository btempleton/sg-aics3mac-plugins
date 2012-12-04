#ifndef __AI110Rasterize__
#define __AI110Rasterize__

/*
 *        Name:	AI110Rasterize.h
 *   $Revision: 8 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Rasterize Suite.
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

#ifndef __AIRasterize__
#include "AIRasterize.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIRasterize.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110RasterizeSuite			"AI Rasterize Suite"
#define kAI110RasterizeSuiteVersion		AIAPI_VERSION(5)


/*******************************************************************************
 **
 **	Types
 **
 **/

/**
	The rasterization settings are collected into a single structure
	describing the type of raster desired, resolution, amount of
	anti-aliasing and other options.
*/
typedef struct _t_AI110RasterizeSettings {
	/** color model and bit depth of raster to be produced */
	AIRasterizeType type;
	/** 0 or 72 provides a resolution of 72 dpi */
	AIReal resolution;
	/** < 2 for none, 2+ for antialiasing. artwork is supersampled at this factor */
 	short antialiasing;
	/** additonal options for how rasterization is performed */
	AIRasterizeOptions options;
} AI110RasterizeSettings;


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	The rasterize suite provides facilities for rasterizing collections
	of art objects creating a new raster art object as a result.
 */
typedef struct {

/**
	This returns the art bounds for the entire artSet.
	If honorCropBox is true, and there is a crop box, then it will 
	return only what's inside the Illustrator crop box (which is 
	created only if Cropmarks->Make was previously done.)
*/
	AIAPI AIErr (*ComputeArtBounds) ( AIArtSet artSet, 
									  AIRealRect *artBounds, 
									  AIBoolean honorCropBox );

/**
	This creates a raster object (type kRasterArt) from the art contained
	in artSet. You must pass in the artBounds which you can get from 
	calling ComputeArtBounds(). paintOrder and prepArt determine where
	the new kRasterArt object will be created. A pointer to the AIArtHandle
	is returned as raster.
*/
	AIAPI AIErr (*Rasterize) ( AIArtSet artSet, 
							   AI110RasterizeSettings *settings, 
							   AIRealRect *artBounds, 
							   short paintOrder, 
							   AIArtHandle prepArt, 
							   AIArtHandle *raster,
							   AIRasterizeProgressProc progressProc );

/**
	This will create a clip group containing:
	   1. A unionized version of whatever was in artSet (this is the clipArt)
	   2. Whatever kRasterArt you pass as rasterArt
	After the clip group is created, it is placed in another group and 
	this group is returned as maskGroup. You specify paintOrder to indicate
	where the maskGroup should be placed. The default value for paintOrder 
	should be kPlaceAbove.
*/
	AIAPI AIErr (*CreateMask) ( AIArtSet artSet, 
								short paintOrder, 
								AIArtHandle rasterArt, 
								AIArtHandle *maskGroup );

/**
	Almost identical to the Rasterize call above, except adds the
	specified padding to resulting raster. The padding parameter is in
	document points.
*/
	AIAPI AIErr (*RasterizeWithPadding) ( AIArtSet artSet, 
										  AI110RasterizeSettings *settings, 
										  AIRealRect *artBounds, 
										  short paintOrder, 
										  AIArtHandle prepArt, 
										  AIArtHandle *raster,
										  AIRasterizeProgressProc progressProc,
										  AIReal padding );

/**
	This creates a raster object (type kRasterArt) for the current
	document. paintOrder and prepArt determine where the new kRasterArt
	object will be created. A pointer to the AIArtHandle is returned
	as raster.
*/
	AIAPI AIErr (*RasterizeDocument) ( AI110RasterizeSettings *settings, 
							   short paintOrder, 
							   AIArtHandle prepArt, 
							   AIArtHandle *raster,
							   AIRasterizeProgressProc progressProc,
							   long options );

/**
	This downsamples a raster object. paintOrder and prepArt determine 
	where the new resampled raster object will be created. Up-sampling 
	is not implemented.(kNotImplementedErr will be returned)
*/
	AIAPI AIErr (*ImageResample) (AIArtHandle rasterArt, 
									const AIResamplingType flag, 
									const AIReal resolution,
									const short paintOrder, 
									AIArtHandle prepArt, 
									AIArtHandle *newRasterArt);

} AI110RasterizeSuite;

#include "AIHeaderEnd.h"


#endif
