#ifndef __AI80DataFilter__
#define __AI80DataFilter__

/*
 *        Name:	AIDataFilter.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Data Filter Suite.
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

#include "AIDataFilter.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDataFilterSuite				"AI Data Filter Suite"
#define kAIDataFilterSuiteVersion2		AIAPI_VERSION(2)
#define kAI80DataFilterVersion			kAIDataFilterSuiteVersion2



/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*LinkDataFilter) ( AIDataFilter *prev, AIDataFilter *next );
	AIAPI AIErr (*UnlinkDataFilter) ( AIDataFilter *next, AIDataFilter **prev );
	AIAPI AIErr (*ReadDataFilter) ( AIDataFilter *filter, char *store, long *count );
	AIAPI AIErr (*WriteDataFilter) ( AIDataFilter *filter, char *store, long *count );
	AIAPI AIErr (*SeekDataFilter) ( AIDataFilter *filter, long *count );
	AIAPI AIErr (*MarkDataFilter) ( AIDataFilter *filter, long *count );
	AIAPI AIErr (*NewFileDataFilter) ( SPPlatformFileSpecification spec, char *mode, long creator, long type, AIDataFilter **filter );
	AIAPI AIErr (*NewBufferDataFilter) ( long size, AIDataFilter **filter );
	AIAPI AIErr (*NewHexdecDataFilter) ( char *state, long shift, AIDataFilter **filter );
	AIAPI AIErr (*NewBlockDataFilter) ( void *address, long size, AIDataFilter **filter );

} AI80DataFilterSuite;


#include "AIHeaderEnd.h"


#endif
