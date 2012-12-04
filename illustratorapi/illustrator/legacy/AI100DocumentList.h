#ifndef __AI100DocumentList__
#define __AI100DocumentList__

/*
 *        Name:	AI100DocumentList.h
 *     Purpose:	Adobe Illustrator 10.0 Document Suite.
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

#include "AIDocumentList.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100DocumentListSuite			kAIDocumentListSuite
#define kAIDocumentListSuiteVersion1	AIAPI_VERSION(1)
#define kAI100DocumentListSuiteVersion	kAIDocumentListSuiteVersion1


/*******************************************************************************
 **
 **	Suite
 **
 **/


// Illustrator 10.0 Document List Suite
typedef struct {

	AIAPI AIErr	(*Count)(long* count);
	AIAPI AIErr	(*GetNthDocument)(AIDocumentHandle* document , long lIndex);
	AIAPI AIErr	(*New)(char* title, AIColorModel* colorMode, 
						 AIReal* artboardWidth, AIReal* artboardHeight , ActionDialogStatus dialogStatus , AIDocumentHandle* document);
	AIAPI AIErr	(*Open)(SPPlatformFileSpecification *fileSpec , AIColorModel colorMode, 
							ActionDialogStatus dialogStatus , AIDocumentHandle* document);
	AIAPI AIErr	(*Save)(AIDocumentHandle document);
	AIAPI AIErr	(*Close)(AIDocumentHandle document);
	AIAPI AIErr	(*CloseAll)();
	AIAPI AIErr	(*Activate)(AIDocumentHandle document , ASBoolean bSetFocus);
	AIAPI AIErr	(*Print)(AIDocumentHandle document , ActionDialogStatus dialogStatus);
} AI100DocumentListSuite;



#include "AIHeaderEnd.h"


#endif
