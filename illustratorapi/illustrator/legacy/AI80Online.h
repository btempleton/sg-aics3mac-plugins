#ifndef __AI80Online__
#define __AI80Online__

/*
 *        Name:	AI80Online.h
 *   $Revision: 1 $
 *      Author:	I'lam Mougy
 *        Date:	23 June 1998
 *     Purpose:	AI Online suit.
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

#include "AIHeaderBegin.h"

// AIOnline Suite
#define kAI80OnlineSuite							"AI Online Suite"
#define kAIOnlineSuiteVersion1				AIAPI_VERSION(1)
#define kAI80OnlineSuiteVersion				kAIOnlineSuiteVersion1


typedef struct 
{	
	AIAPI AIErr			(*ShowOnlineDialog)();
} AI80OnlineSuite;


#include "AIHeaderEnd.h"

#endif