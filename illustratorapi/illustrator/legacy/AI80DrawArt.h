#ifndef __AI80DrawArt__
#define __AI80DrawArt__

/*
 *        Name:	AI80DrawArt.h
 *   $Revision: 17 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Draw Art Suite.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIRaster__
#include "AIRaster.h"
#endif

#ifndef __AIDrawArt__
#include "AIDrawArt.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDrawArtSuite				"AI Draw Art Suite"
#define kAIDrawArtSuiteVersion4		AIAPI_VERSION(4)
#define kAI80DrawArtSuiteVersion	kAIDrawArtSuiteVersion4




/*******************************************************************************
 **
 **	Types
 **
 **/



typedef struct {
	short version;
	
	AIDrawArtFlags flags;
	AIDrawArtOutputType type;
	AIRealPoint origin;
	AIRealMatrix matrix;
	AIArtHandle art;
	AIRealRect destClipRect;
	AIBoolean eraseDestClipRect; // erase destClipRect before arts are drawn.


	AIReal greekThreshold;
	AIExtendedRGBColorRec selectionColor;
	
	union {
		AIDrawArtGWorld gWorld;
		AIDrawArtAGMPort port;
	} output;
} AI80DrawArtData;

typedef struct AI80DrawColorData {
	AIDrawArtOutputType type;

	AIDrawColorStyle style;
	AIDrawColorOptions options;
	AIColor color;
	AIRealRect rect;
	AIReal width;							// when style is frame
	
	union {
		AIDrawArtGWorld gWorld;
		AIDrawArtAGMPort port;
	} output;
} AI80DrawColorData;

/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*DrawArt)( AI80DrawArtData *data );
	AIAPI AIErr (*DrawColorSwatch)( AI80DrawColorData *data );
	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color );
	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

} AI80DrawArtSuite;


#include "AIHeaderEnd.h"


#endif
