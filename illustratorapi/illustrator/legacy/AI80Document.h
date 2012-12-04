#ifndef __AI80Document__
#define __AI80Document__

/*
 *        Name:	AI80Document.h
 *   $Revision: 25 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Document Suite.
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

#include "AIDocument.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentSuite			"AI Document Suite"
#define kAIDocumentSuiteVersion4	AIAPI_VERSION(4)
#define kAIDocumentSuiteVersion5	AIAPI_VERSION(5)

// 8.0 version
#define kAI80DocumentSuiteVersion	kAIDocumentSuiteVersion5


/*******************************************************************************
 **
 **	Suite
 **
 **/


typedef struct {

	AIAPI AIErr (*GetDocumentFileSpecification) ( SPPlatformFileSpecification *file );
	AIAPI AIErr (*GetDocumentPageOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*SetDocumentPageOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*SetDocumentRulerOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*GetDocumentRulerUnits) ( short *units );
	AIAPI AIErr (*SetDocumentRulerUnits) ( short units );
	AIAPI AIErr (*GetDocumentCropBoxGroupHandle) ( AIArtHandle *cropHandle );
	AIAPI AIErr (*GetDocumentCropBox) ( AIRealRect *cropBox );
	AIAPI AIErr (*SetDocumentCropBox) ( AIRealRect *cropBox );
	AIAPI AIErr (*GetDocumentCropStyle) ( AICropMarkStyle *cropStyle );
	AIAPI AIErr (*SetDocumentCropStyle) ( AICropMarkStyle cropStyle );
	AIAPI AIErr (*GetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord *print );
	AIAPI AIErr (*SetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord print );
	AIAPI AIErr (*GetDocumentSetup) ( AIDocumentSetup *setup );
	AIAPI AIErr (*SetDocumentSetup) ( AIDocumentSetup *setup );
	AIAPI AIErr (*GetDocumentModified) ( AIBoolean *modified );
	AIAPI AIErr (*SetDocumentModified) ( AIBoolean modified );
	AIAPI AIErr (*GetDocumentFileFormat) ( AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*SetDocumentFileFormat) ( AIFileFormatHandle fileFormat );
	AIAPI AIErr (*GetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters *parameters );
	AIAPI AIErr (*SetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters parameters );

	AIAPI AIErr (*RedrawDocument) ( void );

	AIAPI AIErr (*GetDocument) ( AIDocumentHandle *document );
	
	AIAPI AIErr (*WriteDocument) (SPPlatformFileSpecification *file, char *fileFormatName, ASBoolean askForParms);

	AIAPI AIErr (*GetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );
	AIAPI AIErr (*SetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );

	AIAPI AIErr (*GetDocumentRulerOrigin) ( AIRealPoint *origin );
	
	AIAPI AIErr (*UpdateLinks) ( AIBoolean *updatedSomething );

	AIAPI AIErr (*GetDocumentZoomLimit) ( AIReal *min, AIReal *max );
	AIAPI AIErr (*GetDocumentMaxArtboardBounds)( AIRealRect *bounds );
	AIAPI AIErr (*DocumentExists) ( AIDocumentHandle document, AIBoolean *exists );

} AI80DocumentSuite;



#include "AIHeaderEnd.h"


#endif
