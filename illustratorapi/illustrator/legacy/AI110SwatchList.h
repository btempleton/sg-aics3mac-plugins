#ifndef __AI110SwatchList__
#define __AI110SwatchList__

/*
 *        Name:	AISwatchList.h
 *   $Revision: 7 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 7.0 Swatch list management
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#ifndef __AISwatchLibraries__
#include "AISwatchLibraries.h"
#endif

#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI110SwatchList.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
#define k110AISwatchListSuite				"AI Swatch List Suite"
#define kAI90SwatchListSuiteVersion			AIAPI_VERSION(3)
#define kAI110SwatchListSuiteVersion		AIAPI_VERSION(4)	// available in AI9.0.1
#define kAI110SwatchListVersion				kAI110SwatchListSuiteVersion
#define kAI110SwatchListSuite				kAISwatchListSuite

/*******************************************************************************
 **
 **	Suite
 **
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
	
	AISwatchRef ASAPI (*GetSwatchByColor)	(AISwatchListRef list, const AIColor *aicolor);
	AISwatchRef ASAPI (*GetSwatchByNameAndType)
											(AISwatchListRef list, const char *name, AIColorTag type);
	ASErr ASAPI (*RemoveSwatch)				(AISwatchListRef list, AISwatchRef swatch, ASBoolean deleteCustomColor);

} AI90SwatchListSuite;


/** Each Illustrator document has an associated swatch list which contains the
	document’s swatches as seen in the Swatches palette. The routines in the
	Swatch List suite are used to access and modify swatch lists and swatches.

	Most functions in the Swatch List Suite take an AISwatchListRef argument.
	This is an opaque reference to a document's swatch list, and can be
	obtained using the GetSwatchList() function or from the AISwatchLibrariesSuite.

	However, plug–ins are usually only concerned with the current document's
	swatch list, so for convenience all of the functions which require an
	AISwatchListRef will accept NULL to indicate the current document's
	swatch list.

	The elements in a swatch list are of type AISwatchRef, which is an opaque
	reference to a swatch. A swatch is simply an AIColor struct and an associated
	name. For AIColor types that are themselves defined by a named object such
	as custom colors, patterns and gradients the swatch name is always the
	same as the name of the object. For other types of AIColor the swatch name
	is independent.

	Note: Indexing is zero based, for example index 2 means 3rd swatch.
	You can pass -1 for index while inserting a swatch in which
	case swatch will be appended to the list.

	There are three notifiers associated with swatch lists:

	- #kAISwatchListChangedNotifier
	- #kAISwatchListChangedInternallyNotifier
	- #kAISwatchReplaceColorNotifier
*/
typedef struct {

	/** Get number of swatches in a swatch list */
	int ASAPI (*CountSwatches)				(AISwatchListRef list);

	/** Get first swatch in a swatch list */
	AISwatchRef ASAPI (*GetFirstSwatch)		(AISwatchListRef list);
	/** Get next swatch in a swatch list */
	AISwatchRef ASAPI (*GetNextSwatch)		(AISwatchRef prev);
	/** Get nth swatch in a swatch list. This is more efficient than GetNextSwatch() for
		iterating through the list.  */
	AISwatchRef ASAPI (*GetNthSwatch)		(AISwatchListRef list, int index);
	/** Find swatch with the specified name. Names are C strings. If no match is found,
		a NULL AISwatchRef is returned by the function. */
	AISwatchRef ASAPI (*GetSwatchByName)	(AISwatchListRef list, const char *name);

	/** This function creates a new swatch and places it in the specified list at
		position N. The swatch previously at position N and all swatches following it in
		the list are bumped down the list by one position. To append a swatch specify
		-1 for N.

		You must set the name and color of the swatch after it has been inserted
		using SetAIColor and SetSwatchName. */
	AISwatchRef ASAPI (*InsertNthSwatch)	(AISwatchListRef list, int index);
	/** This function removes the nth swatch from the list. All swatches in the list
		from position N+1 on are moved up the list one position. The error #kCantDeleteSwatchErr
		is returned if an improper index is specified. */
	ASErr ASAPI (*RemoveNthSwatch)			(AISwatchListRef list, int index);

	/** This function reads the color definition from the specified swatch and fills in
		aicolor with the corresponding values. The AIColor can be any color type
		supported by Illustrator. */
	ASErr ASAPI (*GetAIColor)				(AISwatchRef swatch, AIColor *aicolor);
	/** This function takes the values from aicolor and puts them in the swatch.
		The AIColor can be any color type supported by Illustrator. */
	ASErr ASAPI (*SetAIColor)				(AISwatchRef swatch, AIColor *aicolor);

	/** Returns a C string containing the swatch name. If the name is longer than the the bufferLength,
		the buffer is filled with the truncated name and -1 is returned for the buffer length (normally
		has the length of the string). */
	ASErr ASAPI (*GetSwatchName)			(AISwatchRef swatch, char *name, short *bufferSize);
	/** Set the name of the swatch. If the swatch identifies a custom color, pattern or gradient then
		this changes the name of the underlying object. */
	ASErr ASAPI (*SetSwatchName)			(AISwatchRef swatch, const char *name);

	/** Get document's swatch list. Specify NULL for the AIDocumentHandle to indicate the current
		document. An AIDocumentHandle may be obtained from the AIDocumentListSuite or the
		AIPathStyleSuite::ImportStyles() API. */
	ASErr ASAPI (*GetSwatchList)			(AIDocumentHandle document, AISwatchListRef *list);
	
	/** Returns the first swatch with a color matching the input color. For patterns and gradients
		this API only checks that the gradient or pattern objects match, it does not check that
		the other parameters such as the gradient matrix also match. For all other types all fields
		are checked for a match. */
	AISwatchRef ASAPI (*GetSwatchByColor)	(AISwatchListRef list, const AIColor *aicolor);
	/** Returns the first swatch in the list with the given name and color type. */
	AISwatchRef ASAPI (*GetSwatchByNameAndType)(AISwatchListRef list, const char *name, AIColorTag type);
	
	/** Remove the swatch from the list. */
	ASErr ASAPI (*RemoveSwatch)				(AISwatchListRef list, AISwatchRef swatch, ASBoolean deleteCustomColor);

} AI110SwatchListSuite;


#include "AIHeaderEnd.h"

#endif
