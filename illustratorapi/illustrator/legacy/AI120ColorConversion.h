#ifndef __AI120ColorConversion__
#define __AI120ColorConversion__

/*
 *        Name:	AI120ColorConversion.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Color Conversion Suite.
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

#ifndef __AIColorConversion__
#include "AIColorConversion.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI120ColorConversion.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIColorConversionVersion7			AIAPI_VERSION(7)
#define kAI120ColorConversionSuiteVersion	kAIColorConversionVersion7
#define kAI120ColorConversionVersion		kAI120ColorConversionSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The color conversion suite contains basic facilities for conversion of color
	values and image sample values beween color spaces.
	
	If color management is on, it uses the document profile if it has one, otherwise
	the profiles from the color settings dialog.

	If color management is off, device conversions are done.
*/
typedef struct {

	/** Convert a color from the source space to the destination. See
		#AIColorConversionSpaceValue for the possible values for srcSpace and
		dstSpace. The srcColor and dstColor parameters must be arrays holding
		the appropriate number of color values for the space. If inGamut is
		non-NULL then on return it indicates whether the source color was
		within the gamut of the destination space. */
	AIAPI AIErr (*ConvertSampleColor) ( long srcSpace, AISampleComponent *srcColor,
		                                long dstSpace, AISampleComponent *dstColor,
										const AIColorConvertOptions& options,
										ASBoolean *inGamut);
									   
	/** Convert an array of image pixels from the source space to the destination. See
		#AIColorConversionSpaceValue for the possible values for srcSpace and
		dstSpace. The srcColor and dstColor parameters must be arrays of "pixelCount"
		pixels with the appropriate number of components. The flag #kRasterInvertBits
		can be specified in order to indicate that the bits of a 1-bit color space
		are inverted. */
	AIAPI AIErr (*ConvertImageColor)   ( long srcSpace, AIImageComponent *srcColor,
		                               	 long dstSpace, AIImageComponent *dstColor,
									   	 long pixelCount, unsigned short flags,
										 const AIColorConvertOptions& options);

} AI120ColorConversionSuite;


#include "AIHeaderEnd.h"


#endif
