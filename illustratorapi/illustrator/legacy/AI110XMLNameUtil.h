#ifndef __AI110XMLNameUtil__
#define __AI110XMLNameUtil__

/*
 *        Name:	AI110XMLNameUtil.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 XML Name Utilties Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

#ifndef __AIXMLNameUtil__
#include "AIXMLNameUtil.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIXMLNameUtil.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110XMLNameUtilSuite					kAIXMLNameUtilSuite
#define kAIXMLNameUtilSuiteVersion1				AIAPI_VERSION(1)
#define kAI110XMLNameUtilSuiteVersion			kAIXMLNameUtilSuiteVersion1
#define kAI110XMLNameUtilVersion				kAI110XMLNameUtilSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** The XML standard requires that names conform to a specific syntax. For
	example it cannot contain the space character and must start with a
	letter. This suite provides APIs for working with XML names. In particular
	it contains some utilities for converting between general strings and
	names. Illustrator uses these facilities to convert between art object
	names and UIDs (see the AIUIDUtilsSuite).

	See http://www.w3.org/TR/REC-xml#NT-Name for the XML name syntax.
*/
typedef struct AI110XMLNameUtilSuite {

	/** Given a base name and number constructs an XML name. The
		constructed name will be no longer than the maximum specified
		length. The return value is the input buffer pointer. */
	AIAPI char* (*NameFromBaseAndNumber) (const char* base, int number, char* buffer, ASInt32 bufsize);

	/** Given a possibly uniquified XML name returns the base name. The
		space needed for base is always less than or equal to that of
		the name. */
	AIAPI char* (*BaseFromName) (const char* name, char* buffer);

	/** Checks that the name is a valid XML name. */
	AIAPI AIBoolean (*IsValidName) (const char* name);

	/** Given an arbitrary string constructs a valid XML name. if 'needed'
		is supplied then the buffer size needed is returned. Returns the buffer. */
	AIAPI char* (*XMLNameFromString) (const char* str, char* buffer, ASInt32 bufsize, ASInt32* needed);

	/** Reverse the action of the preceding. the space needed is always
		less than or equal to the input string size. */
	AIAPI char* (*StringFromXMLName) (const char* name, char* buffer);

} AI110XMLNameUtilSuite;


#include "AIHeaderEnd.h"


#endif
