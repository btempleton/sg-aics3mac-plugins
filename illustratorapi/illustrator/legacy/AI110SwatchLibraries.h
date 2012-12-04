#ifndef __AI110SwatchLibraries__
#define __AI110SwatchLibraries__

/*
 *        Name:	AISwatchLibraries.h
 *   $Revision: 2 $
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

/** @file AI110SwatchLibraries.h */

// AISwatchLibs Suite
#define kAI110SwatchLibrariesSuite			"AI Swatch Libraries Suite"
#define kAI110SwatchLibrariesSuiteVersion	AIAPI_VERSION(1)
#define kAI110SwatchLibrariesVersion		kAI110SwatchLibrariesSuiteVersion

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


} AI110SwatchLibrariesSuite;


#include "AIHeaderEnd.h"

#endif