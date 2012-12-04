#ifndef __AI80PathStyle__
#define __AI80PathStyle__

/*
 *        Name:	AI80PathStyle.h
 *   $Revision: 19 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Path Style Suite.
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


#include "AI110PathStyle.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI80PathStyleSuite			kAIPathStyleSuite
#define kAIPathStyleSuiteVersion4	AIAPI_VERSION(4)
#define kAI80PathStyleSuiteVersion	kAIPathStyleSuiteVersion4


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Version 4 of path style suite */
typedef struct {

	/* For GetPathStyle & SetPathStyle, the object "path" must be of type
		kPathArt, kMeshArt, or kRasterArt. All other types return kBadParameterErr.
	*/
	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AI110PathStyle *style );
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, AI110PathStyle *style );
	AIAPI AIErr (*GetCurrentPathStyle) ( AI110PathStyle *style, AI110PathStyleMap* stylemap );
	AIAPI AIErr (*SetCurrentPathStyle) ( AI110PathStyle *style, AI110PathStyleMap* stylemap );
	AIAPI AIErr (*ImportStyles) ( SPPlatformFileSpecification *source, AIDocumentHandle *newdoc );

	/* Apply the AIColor to the object.  This does what is generally wanted when you've
	  got an AIColor and you've got an object, and you want the object painted with the
	  color. It handles setting the gradient vector to the default, enumerates groups,
	  does the right thing on compound paths, etc. (If, for example, you have an object
	  that's stroked with a dashed line and you pass in a new color with the onStroke
	  parameter true, the old dash pattern will be retained. If the object didn't have
	  a stroke before, the current paint style is looked at. If the current paint style
	  also doesn't have a stroke, a sensible default is used.)

	  The art object can be any type except kUnknownArt, kPlacedArt, or kMysteryPathArt.

	  Since the routine enumerates container objects, for efficiency care should be taken
	  that you do not call SetObjectAIColor on both a container and its children.
	*/
	AIAPI AIErr (*SetObjectAIColor) ( AIArtHandle art, AIColor *color, AIBoolean onStroke );

	/* Simple routines to convert from AIColor to AI70Color and vice versa. */
	AIAPI AIErr	(*AIColorToAI70Color) ( AIColor *from, AI70Color *to);
	AIAPI AIErr	(*AI70ColorToAIColor) ( AI70Color *from, AIColor *to);

	AIAPI AIErr (*PathStyleUsesAIColor) ( AI110PathStyle *pathStyle,
											AI110PathStyleMap *psMap, // optional
											AIColor *color,
											AIBoolean matchTint,
											AIBoolean lookForIndirectUsage,
											AIColorUsedHow *usage );

	AIAPI AIErr (*ApplyAIColorToPathStyle) ( AI110PathStyle *pathStyle,
											AI110PathStyleMap	*psMap,	// can be null
											AIColor			*newColor,
											AIColor			*matchColor,
											AIBoolean		onStroke,
											AIBoolean		useOldTint,
											AIArtHandle		destination,
											AIColorUsedHow	*whatChanged );

	/* Examine the art object, which can be any type, for usage of the targetColor,
		and return a vector of AIColorUsedHow values in *usage.

		If lookForIndirectUsage is true, it returns whether the art object would
		cause the color to be considered "in use" on the swatch palette. This
		includes usage inside patterns, gradients, and graph designs.

		If lookForIndirectUsage is false, the scan will not look inside of patterns,
		gradients, or graph designs. It will still look inside the graph style change
		records of graph objects.
	*/
	AIAPI AIErr (*ObjectUsesAIColor) ( AIArtHandle art,
										AIColor *targetColor,
										AIBoolean matchTint,
										AIBoolean lookForIndirectUsage,
										AIColorUsedHow *usage );

	/* For any direct usage of the oldColor in the art object, do a SetObjectAIColor to the
		newColor. "Direct" usage means the color of a stroke or fill, including inside graph
		path style change records. It does not cover colors used *inside* gradients, patterns,
		or graph designs that are attached to the object. (Indirect usages inside patterns
		and gradients are to be replaced by defining a new pattern or gradient, then calling
		ReplaceObjectAIColor with the oldColor and newColor being the pattern or gradient
		that was redefined. Indirect usage inside graph designs are similar, except that
		one doesn't call ReplaceObjectAIColor because a graph design isn't a color.)

		If useOldTint is true, and both oldColor and newColor are custom colors, then
		the tint from the oldColor is used, otherwise the tint from the newColor is used.

		Sets *madeReplacement to true if it found oldColor and made a replacement, and
		to false if it didn't.

		The art object can any type except kPlacedArt, including those which are reported
		as kMysteryPathArt (paths inside text paths and graphs), and those which are
		reported as kUnknownArt, such as graphs and layer masks. (Since kPlacedArt is a
		reference to an external file, colors cannot be replaced inside of it.)
	*/
	AIAPI AIErr (*ReplaceObjectAIColor) ( AIArtHandle art,
											AIColor *oldColor, AIColor *newColor,
											AIBoolean useOldTint,
											AIBoolean *madeReplacement /* can be NULL */ );

	/* Get/set the style used when creating objects. */
	AIAPI AIErr (*GetInitialPathStyle) ( AI110PathStyle *style );
	AIAPI AIErr (*SetInitialPathStyle) ( AI110PathStyle *style );
	AIAPI AIErr (*GetInitialTextStyle) ( AI110PathStyle *style );
	AIAPI AIErr (*SetInitialTextStyle) ( AI110PathStyle *style );

} AI80PathStyleSuite;


#include "AIHeaderEnd.h"

#endif
