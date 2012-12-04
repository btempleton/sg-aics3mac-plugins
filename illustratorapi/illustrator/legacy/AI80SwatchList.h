#ifndef __AI80SwatchList__
#define __AI80SwatchList__

/*
 *        Name:	AI80SwatchList.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Swatch list management
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



#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kAI80SwatchListSuite					"AI Swatch List Suite"
#define kAI80SwatchListSuiteVersion				AIAPI_VERSION(2)




/*******************************************************************************
 **
 **	Suite
 **
 **
 ** Note: Indexing is zero based, for example index 2 means 3rd swatch.
 **       You can pass -1 for index while inserting a swatch in which
 **       case swatch will be appended to the list.
 **/

typedef struct {

	int ASAPI (*CountSwatches)				(AISwatchListRef list);

	AISwatchRef ASAPI (*GetFirstSwatch)		(AISwatchListRef list);
	AISwatchRef ASAPI (*GetNextSwatch)		(AISwatchRef prev);
	AISwatchRef ASAPI (*GetNthSwatch)		(AISwatchListRef list, int index);
	AISwatchRef ASAPI (*GetSwatchByName)	(AISwatchListRef list, const char *name);

	AISwatchRef ASAPI (*InsertNthSwatch)	(AISwatchListRef list, int index);
	ASErr ASAPI (*RemoveNthSwatch)			(AISwatchListRef list, int index);

	ASErr ASAPI (*GetAIColor)				(AISwatchRef swatch, AIColor *aicolor);
	ASErr ASAPI (*SetAIColor)				(AISwatchRef swatch, AIColor *aicolor);

	ASErr ASAPI (*GetSwatchName)			(AISwatchRef swatch, char *name);
	ASErr ASAPI (*SetSwatchName)			(AISwatchRef swatch, const char *name);

	ASErr ASAPI (*GetSwatchList)			(AIDocumentHandle document, AISwatchListRef *list);

} AI80SwatchListSuite;


#include "AIHeaderEnd.h"

#endif
