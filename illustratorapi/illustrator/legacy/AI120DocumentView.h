#ifndef __AIDocumentView120__
#define __AIDocumentView120__

/*
*        Name:	AI120DocumentView.h
*     Purpose:	Adobe Illustrator 12.0 Document View Suite.
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

#include "AIDocumentView.h"

#include "AIHeaderBegin.h"

/** @file AIDocumentView120.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAIDocumentViewSuiteVersion8	AIAPI_VERSION(8)

/*******************************************************************************
**
**	Suite
**
**/


// version 8
struct AI120DocumentViewSuite {

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

	AIAPI AIErr (*GetDocumentViewDocument) ( AIDocumentViewHandle view, AIDocumentHandle *document );

	AIAPI AIErr (*ForceDocumentViewsOnScreen) ( void );

	AIAPI AIErr (*GetShowGuides) ( AIDocumentViewHandle view, ASBoolean* show );

	AIAPI AIErr (*SetShowGuides) ( AIDocumentViewHandle view, ASBoolean show );

};


#include "AIHeaderEnd.h"


#endif
