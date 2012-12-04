#ifndef __AI80Raster__
#define __AI80Raster__

/*
 *        Name:	AI80Raster.h
 *   $Revision: 24 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Raster Object Suite.
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

#include "AI110Raster.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI80RasterSuite		kAIRasterSuite
#define kAIRasterSuiteVersion4	AIAPI_VERSION(4)
#define kAI80RasterSuiteVersion	kAIRasterSuiteVersion4


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct _t_AI80RasterRecord	{
	uint16			flags;
	AIRect			bounds;
	int32			byteWidth;
	int16			colorSpace; // look at the colorSpace flags...
	int16			bitsPerPixel;
	int16			originalColorSpace; // if -1 the raster is unconverted, else the color space before conversion
} AI80RasterRecord;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Suite supporting embedded images only */
typedef struct AI80RasterSuite {

	AIAPI AIErr (*GetRasterInfo) ( AIArtHandle raster, AI80RasterRecord *info );
	AIAPI AIErr (*SetRasterInfo) ( AIArtHandle raster, AI80RasterRecord *info );
	AIAPI AIErr (*GetRasterFileSpecification) ( AIArtHandle raster, SPPlatformFileSpecification *file );
	AIAPI AIErr (*SetRasterFileSpecification) ( AIArtHandle raster, SPPlatformFileSpecification *file );
	AIAPI AIErr (*GetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );
	AIAPI AIErr (*SetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );
	AIAPI AIErr (*GetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );
	AIAPI AIErr (*SetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );
	AIAPI AIErr (*GetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AITile *workTile, AISlice *workSlice );
	AIAPI AIErr (*SetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AITile *workTile, AISlice *workSlice );

	AIAPI AIErr (*GetRasterLink) ( AIArtHandle raster, AI110RasterLink *link );
	AIAPI AIErr (*SetRasterLink) ( AIArtHandle raster, AI110RasterLink *link );
	AIAPI AIErr (*ResolveRasterLink) ( AIArtHandle raster, long flags );

	AIAPI AIErr (*GetRasterFileInfoFromArt) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );
	AIAPI AIErr (*GetRasterFileInfoFromFile) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );
	AIAPI AIErr (*GetRasterFilePathFromArt) ( AIArtHandle raster, char *pszPath, int iMaxLen );

} AI80RasterSuite;


#include "AIHeaderEnd.h"


#endif
