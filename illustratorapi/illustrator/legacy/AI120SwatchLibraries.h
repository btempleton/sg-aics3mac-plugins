#ifndef __AI120SwatchLibraries__
#define __AI120SwatchLibraries__

/*
 *        Name:	AISwatchLibraries.h
 *      Author:	Neal Tucker
 *        Date:	3/11/97
 *     Purpose:	AI SwatchLibraries Suite.
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

#include "AISwatchLibraries.h"

#include "AIHeaderBegin.h"

/** @file AI120SwatchLibraries.h */

// AISwatchLibs Suite
#define kAI120SwatchLibrariesSuite			"AI Swatch Libraries Suite"
#define kAI120SwatchLibrariesSuiteVersion	AIAPI_VERSION(2)
#define kAI120SwatchLibrariesVersion		kAI120SwatchLibrariesSuiteVersion

/** The swatch libraries suite is supplied by the swatch libraries plugin. This plugin
	allows the user to open libraries of color, pattern and gradient swatches. Once
	opened these libraries are accessible through this suite. The AISwatchListSuite
	provides APIs for manipulating a swatch list.

	The swatch libraries suite also contains APIs that allow the swatches in the open
	libraries to be accessed in aggregate. This APIs collect up all the swatches
	from all open libraries into one big list that is sorted by name and allow
	access to the entries in that list.
 */
typedef struct 
{	
	/** Return a count of the number of currently open libraries. */
	ASErr ASAPI (*CountLibraries)(long *num);
	/** Get the swatch list of the nth open library or if num < 0 the current document
		swatch list. The AISwatchListSuite can be used to access and modify the 
		returned list. */
	ASErr ASAPI (*GetNthLibrary)(long num, AISwatchListRef *swatchlist);
	/** Count the aggregate number of all swatches in all open libraries. */
	ASErr ASAPI (*CountLibrarySwatches)(long *num);
	/** Get the nth swatch in the aggregate of all open libraries. */
	ASErr ASAPI (*GetNthLibrarySwatch)(long num, AISwatchRef *swatch);
	/** Count the aggregate number of all pattern swatches in all open libraries. */
	ASErr ASAPI (*CountLibraryPatterns)(long *num);
	/** Get the nth pattern swatch in the aggregate of all open libraries. */
	ASErr ASAPI (*GetNthLibraryPattern)(long num, AIPatternHandle *pattern);
	/** Count the aggregate number of all gradient swatches in all open libraries. */
	ASErr ASAPI (*CountLibraryGradients)(long *num);
	/** Get the nth gradient swatch in the aggregate of all open libraries. */
	ASErr ASAPI (*GetNthLibraryGradient)(long num, AIGradientHandle *gradient);
	/** Count the aggregate number of all custom color swatches in all open libraries. */
	ASErr ASAPI (*CountLibraryCustomColors)(long *num);
	/** Get the nth custom color swatch in the aggregate of all open libraries. */
	ASErr ASAPI (*GetNthLibraryCustomColor)(long num, AICustomColorHandle *ccolor);

	// New for AI 12:

	/** Searches the color books to find the definition of a specific named color. Color books
		contain collections of pre-defined colors, such as the Pantone colors. A color book
		need not have been opened to be included in the search.
		(Note that this function returns a boolean value, not an error code.)
			@param name The name string of the desired color.
			@param color [out] A buffer in which to return the custom color definition, if found.
			@return True if the color is found in a color book, false otherwise.
		*/
	ASBoolean ASAPI (*FindStandardBookColor)(const ai::UnicodeString& name, AICustomColor* color);

	/** Searches the legacy color books to find the previous definition of a specific named
		color. A legacy color book need not have been opened to be included in the search.
		(Note that this function returns a boolean value, not an error code.)
			@param name The name string of the desired color.
			@param color [out] A buffer in which to return the custom color definition, if found.
			@return True if the color is found in a legacy color book, false otherwise.
		*/
	ASBoolean ASAPI (*FindLegacyBookColor)(const ai::UnicodeString& name, AICustomColor* color);

	/** Retrieves the name of any swatch library in the list, whether it has been opened
		or not.
			@param num The 0-based position index of the library.
			@param name [out] A buffer in which to return the name.	The name of the
				swatch library for the current document (\c num < 0) is the empty string.
		*/
	ASErr ASAPI (*GetNthLibraryName)(long num, ai::UnicodeString& name);

	/** Maps a legacy color name to its corresponding name in the current color books.
			@param src The legacy color-book name.
			@param dst [out] A buffer in which to return the current color-book name,
				or the empty string if no mapping is defined.
		*/
	ASErr ASAPI (*MapLegacyColorName)(const ai::UnicodeString& src, ai::UnicodeString& dst);


} AI120SwatchLibrariesSuite;


#include "AIHeaderEnd.h"

#endif