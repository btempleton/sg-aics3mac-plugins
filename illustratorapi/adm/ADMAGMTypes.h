/*******************************************************************************
*
* ADMAGMTypes.h -- Abstract references to AGM types for ADM interfaces
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1999-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
********************************************************************************/

/** @file ADMAGMTypes.h Abstract references to AGM color management types for ADM interfaces */

#ifndef _ADMAGMTYPES_H_
#define _ADMAGMTYPES_H_

#include "ADMTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque reference to a color space. */
typedef struct _t_ADMAGMColrSpace ADMAGMColorSpace;

/** Colorspace family.  */
typedef int ADMAGMColorSpaceFamily;

/** Opaque reference to an AGM raster port. */
typedef struct _t_ADMAGMRasterPort ADMAGMRasterPort;

/** Opaque reference to an AGM port. */
typedef struct _t_ADMAGMPort ADMAGMPort;

/** Pointer to an AGM port. */
typedef ADMAGMPort* ADMAGMPortPtr;

/** Data type for color table structure. */
typedef struct _t_ADMAGMColorTab ADMAGMColorTab;

/** @deprecated Data type for image record structure. Do not use. */
typedef struct _t_ADMAGMImageRecord ADMAGMImageRecord;

/** Line cap type constants. */
enum _ADMLineCap {
	/** Butt line caps */
	kButtCap = 0,
	/** Round line caps */
	kRoundCap,
	/** Projecting line caps */
	kProjectingCap
};

/** Data type for line cap constants.  */
typedef enum _ADMLineCap ADMLineCap;

/** Color table structure. */
struct _t_ADMAGMColorTab	{
	/** The number of colors in the table. */
	ADMInt32	numColors;
	/** Pointer to the color data. */
	void*	theColors;
};

/** Rectangle with 16-bit integer coordinates */
typedef struct _t_ADMAGMInt16Rect {
	/** Left edge.  */
	ADMInt16	xMin;
	/** Bottom edge. */
	ADMInt16	yMin;
	/** Right edge. */
	ADMInt16	xMax;
	/** Top edge. */
	ADMInt16	yMax;
}
ADMAGMInt16Rect;

/** @deprecated Image record structure. Do not use. */
struct _t_ADMAGMImageRecord	{
	/** The bounding box of the image. */
	ADMAGMInt16Rect	bounds;
	/** Pointer to the image data. */
	void*			baseAddr;
	/** The width of the image in bytes. The number of bytes
		varies with the bits-per-pixel of the color space. */
	ADMInt32			byteWidth;
	/** The color space. */
	ADMInt16			colorSpace;
	/** The number of bits per pixel. */
	ADMInt16			bitsPerPixel;
	/** Decode array.  */
	float*		decodeArray;
	/** The color table. */
	ADMAGMColorTab	colorTab;
};

#ifdef __cplusplus
}
#endif

#endif // _ADMAGMTYPES_H_
