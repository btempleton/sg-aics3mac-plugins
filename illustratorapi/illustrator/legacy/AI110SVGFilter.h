#ifndef __AI110SVGFilter__
#define __AI110SVGFilter__

/*
 *        Name:	AISVGFilter.h
 *   $Revision: 2 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Suite.
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

#include "AISVGFilter.h"

#include "AIHeaderBegin.h"

/** @file AI110SVGFilter.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110SVGFilterSuite			kAISVGFilterSuite
#define kAISVGFilterSuiteVersion1		AIAPI_VERSION(1)
#define kAI110SVGFilterSuiteVersion		kAISVGFilterSuiteVersion1
#define kAI110SVGFilterVersion			kAI110SVGFilterSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The SVG filter effect makes it possible to apply SVG filters to Illustrator artwork.
	When an SVG file is written these filters are preserved where possible. The SVG
	filter effect applies filters from a global list associated with the current document.
	
	The APIs in SVG filter suite provide facilities for managing the global list of
	filters, for attaching filters to art and manipulating art with SVG filters attached.

	There are two notifiers associated with SVG filters:

	- #kAISVGFilterChangedNotifier
	- #kAISVGFilterAddedNotifier

	The following error codes are associated with SVG filters:

	- #kXMLIDCollisionErr
	- #kXMLIDChangedErr
	- #kNoSVGFilterErr
	- #kSVGFilterRedefErr
 */
typedef struct {

	/** Make a new SVG filter in the current document. */
	AIAPI AIErr (*NewSVGFilter) ( AISVGFilterHandle *newFilter );
	/** Delete the SVG filter from the current document. */
	AIAPI AIErr (*DeleteSVGFilter) ( AISVGFilterHandle filter );
	/** Get a count of the number of SVG filters in the current document. */
	AIAPI AIErr (*CountSVGFilters) ( long *count );
	/** Get the nth filter. */
	AIAPI AIErr (*GetNthSVGFilter) ( long n, AISVGFilterHandle *filter );

	/** SetSVGFilterContents will return #kXMLIDCollisionErr if the xml id specified as an attribute 
		of the "filter" element is already in use in the current document and forceUniqueID is false.
		If forceUniqueID is true, SetSVGFilterContents will rename the filter to have a unique id.
		It will return #kXMLIDChangedErr, if it changed the ID.  You can retreive the ID with
		GetSVGFilterUIDName(). */
	AIAPI AIErr (*SetSVGFilterContents) ( AISVGFilterHandle filter, AIXMLNodeRef filterContents, 
		AIBool8 forceUniqueID );
	AIAPI AIErr (*GetSVGFilterContents) ( AISVGFilterHandle filter, AIXMLNodeRef *filterContents );

	/** Get the filter handle associated with the id "name". */
	AIAPI AIErr (*GetSVGFilter) ( const char *name, AISVGFilterHandle *filter );
	/** Get the name/UID for the filter handle "filter" */
	AIAPI AIErr (*GetSVGFilterUIDName) (AISVGFilterHandle filter, const char **name);

	/** Returns a copy of the input art that the SVG Filter Effect is seeing; clients MUST dispose
		this art via the DisploseFilterArt() call below. */
	AIAPI AIErr (*GetSVGFilterArt) ( AIArtHandle art, AIArtHandle* svgArt );
	/** Disposes of the inout art to an SVG filter. See GetSVGFilterArt(). */
	AIAPI AIErr (*DisposeFilterArt) ( AIArtHandle art );

	/** Apply the SVG Filter "filter" to "art" */
	AIAPI AIErr (*AttachFilter) ( AIArtHandle art, AISVGFilterHandle filter );

	/** Given an AIArtStyleHandle, if the style is capable of generating an SVGFilter to represent 
		iteself, it will return a handle to said filter in "filter".  If the style isn't representable
		as SVG SVGFilterFromAIArtStyle() will return #kNoSVGFilterErr */
	AIAPI AIErr (*SVGFilterFromAIArtStyle) ( const AIArtStyleHandle artStyle, AISVGFilterHandle *filter);

} AI110SVGFilterSuite;


#include "AIHeaderEnd.h"


#endif
