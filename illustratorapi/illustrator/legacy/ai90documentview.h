#ifndef __AIDocumentView90__
#define __AIDocumentView90__

/*
 *        Name:	AIDocumentView90.h
 *   $Revision: 20 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Document View Suite.
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


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentViewSuiteVersion6	AIAPI_VERSION(6)


/*******************************************************************************
 **
 **	Suite
 **
 **/


// version 6
typedef struct {

	AIAPI AIErr (*GetDocumentViewBounds) ( AIDocumentViewHandle view, AIRealRect *bounds );
	AIAPI AIErr (*GetDocumentViewCenter) ( AIDocumentViewHandle view, AIRealPoint *center );
	AIAPI AIErr (*SetDocumentViewCenter) ( AIDocumentViewHandle view, AIRealPoint *center );
	AIAPI AIErr (*GetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal *zoom );
	AIAPI AIErr (*SetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal zoom );

	AIAPI AIErr (*ArtworkPointToViewPoint) ( AIDocumentViewHandle view, AIRealPoint *artworkPoint, AIPoint *viewPoint );
	AIAPI AIErr (*ViewPointToArtworkPoint) ( AIDocumentViewHandle view, AIPoint *viewPoint, AIRealPoint *artworkPoint );

	AIAPI AIErr (*CountDocumentViews)( long *count );
	AIAPI AIErr (*GetNthDocumentView)( long n, AIDocumentViewHandle *view );

	AIAPI AIErr (*FixedArtworkPointToViewPoint) ( AIDocumentViewHandle view, AIRealPoint *artworkPoint, AIRealPoint *viewPoint );
	AIAPI AIErr (*FixedViewPointToArtworkPoint) ( AIDocumentViewHandle view, AIRealPoint *viewPoint, AIRealPoint *artworkPoint );

	AIAPI AIErr (*SetScreenMode) ( AIDocumentViewHandle view, AIScreenMode mode );
	AIAPI AIErr (*GetScreenMode) ( AIDocumentViewHandle view, AIScreenMode *mode );

	AIAPI AIErr (*GetPageTiling) ( AIPageTiling *pageTiling );

	AIAPI AIErr (*GetTemplateVisible) ( AIDocumentViewHandle view, AIBoolean *visible );

	AIAPI AIErr (*DocumentViewScrollDelta)( AIDocumentViewHandle view, AIRealPoint *delta);
	AIAPI AIErr (*GetDocumentViewInvalidRect)( AIDocumentViewHandle view, AIRealRect *invalidRect );
	AIAPI AIErr (*SetDocumentViewInvalidRect)( AIDocumentViewHandle view, AIRealRect *invalidRect );

	AIAPI AIErr (*GetDocumentViewStyle)( AIDocumentViewHandle view,  short *style );

	AIAPI AIErr (*SetDocumentViewInvalidDocumentRect)( AIDocumentViewHandle view, AIRealRect *invalidRect );

	AIAPI AIErr (*GetShowPageTiling) ( ASBoolean *show );
	AIAPI AIErr (*SetShowPageTiling) ( ASBoolean show );

	AIAPI AIErr (*GetGridOptions) ( AIDocumentViewHandle view, ASBoolean* show, ASBoolean* snap );
	AIAPI AIErr (*SetGridOptions) ( AIDocumentViewHandle view, ASBoolean show, ASBoolean snap );

	AIAPI AIErr (*GetShowTransparencyGrid) ( AIDocumentViewHandle view, ASBoolean* show );
	AIAPI AIErr (*SetShowTransparencyGrid) ( AIDocumentViewHandle view, ASBoolean show );

} AI90DocumentViewSuite;


#include "AIHeaderEnd.h"


#endif
