#ifndef __AI80DocumentView__
#define __AI80DocumentView__

/*
 *        Name:	AI80DocumentView.h
 *   $Revision: 20 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Document View Suite.
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


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentViewSuiteVersion5	AIAPI_VERSION(5)
#define kAI80DocumentViewSuiteVersion		kAIDocumentViewSuiteVersion5



/*******************************************************************************
 **
 **	Suite
 **
 **/


// version 5
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

} AI80DocumentViewSuite;


#include "AIHeaderEnd.h"


#endif
