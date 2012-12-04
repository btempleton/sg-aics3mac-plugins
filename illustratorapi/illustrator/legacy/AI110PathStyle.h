#ifndef __AI110PathStyle__
#define __AI110PathStyle__

/*
 *        Name:	AI110PathStyle.h
 *   $Revision: 19 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Path Style Suite.
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

#include "AIPathStyle.h"

#include "AIHeaderBegin.h"

/** @file AI110PathStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPathStyleSuiteVersion5	AIAPI_VERSION(5)
#define kAI110PathStyleSuiteVersion	kAIPathStyleSuiteVersion5
#define kAI110PathStyleVersion		kAI110PathStyleSuiteVersion

/** The AI110PathStyle structure stores information describing how to paint a path.
	It contains information both for how to fill a path and how to stroke a
	path.

	Most APIs take and return fully specified path styles. However, some APIs
	use partial styles. A partial style is a style that only specifies a subset
	of the painting information. For example such styles are used to represent
	the common paint attributes of a selection or to modify a subset of attributes
	without affecting the others. In this case the path style is paired with a
	AI110PathStyleMap specifying the subset of attributes. Clients should be
	careful not to pass partial styles to APIs that require full styles since
	unspecified fields may contain invalid values.
 */
typedef struct AI110PathStyle {
	/** Whether or not to fill the path. */
	AIBoolean fillPaint;
	/** Whether or not to stroke the path */
	AIBoolean strokePaint;
	/** Fill style, if fillPaint is true */
	struct AIFillStyle fill;
	/** Stroke style, if strokePaint is true */
	struct AIStrokeStyle stroke;
	/** Whether or not to use this as a clipping path */
	AIBoolean clip;
	/** Whether or not to lock the clipping path */
	AIBoolean lockClip;
	/** Whether or not to use the even-odd rule to determine path insideness */
	AIBoolean evenodd;
	/** Path's resolution */
	AIReal resolution;
	/** The note field is ASCII text entered by the user. For private data a plug-in
		should use the art dictionary (see AIArtSuite::GetDictionary()) rather than
		modify this field. */
	unsigned char note[256];
} AI110PathStyle;

/** Indicates the fields of an AI110PathStyle that are specified by a partial
	style. */
typedef struct AI110PathStyleMap {
	AIBoolean fillPaint;
	AIBoolean strokePaint;
	struct AIFillStyleMap fill;
	struct AIStrokeStyleMap stroke;
	AIBoolean clip;
	AIBoolean lockClip;
	AIBoolean evenodd;	
	AIBoolean resolution;
	AIBoolean note;
} AI110PathStyleMap;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** A path style describes the paint information for an object, including stroke
	and fill. Use the Path Style Suite to access or set path style information for
	paths.
*/
struct AI110PathStyleSuite {

	/** Retrieves the path style used to fill and/or stroke the object. The object
		must be of type kPathArt, kMeshArt, or kRasterArt. All other types return
		kBadParameterErr. */
	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AI110PathStyle *style );
	/** Sets the path style used to fill and/or stroke the object. The object
		must be of type kPathArt, kMeshArt, or kRasterArt. All other types return
		kBadParameterErr. */
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, AI110PathStyle *style );
	
	
	/** Get the common attributes of the current selected objects. Note that this
		API returns a partial style. */
	AIAPI AIErr (*GetCurrentPathStyle) ( AI110PathStyle *style, AI110PathStyleMap* stylemap );
	
	/** Apply the path style to any currently selected and paint-targetted objects.
		If a targetted object has an active style, the path style will be merged
		in to the focal fill and stroke filters. Any effects and non-focal fills
		and strokes will be unmodified. Use SetCurrentPathStyleForceSimple instead
		if you want to blow away any active styles. (The reason we didn't just add
		another parameter was so as not to have to bump the suite version number.) */ 
	AIAPI AIErr (*SetCurrentPathStyle) ( AI110PathStyle *style, AI110PathStyleMap* stylemap );

	/** Use this function to import the styles contained in the specified file. The
		styles are imported into a new document whose handle is returned. The styles
		can then be accessed through their respective APIs. For example the art
		style can be obtained through the AIArtStyleSuite and the swatches can be
		obtained through the AISwatchListSuite. */
	AIAPI AIErr (*ImportStyles) ( SPPlatformFileSpecification *source, AIDocumentHandle *newdoc );

	/** Apply the AIColor to the object.  This does what is generally wanted when you've
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

	/** Simple routine to convert from AIColor to AI70Color. */
	AIAPI AIErr	(*AIColorToAI70Color) ( AIColor *from, AI70Color *to);
	/** Simple routine to convert from AI70Color to AIColor. */
	AIAPI AIErr	(*AI70ColorToAIColor) ( AI70Color *from, AIColor *to);

	/** Determines whether the path style makes use of the supplied color in its fill
		or stroke and returns an indicator of how it is used. A style map may optionally
		be supplied for a partial style. If matchTint is false the tint percentage for
		spot and global process colors is not considered. If lookForIndirectUsage is
		true and the path style is a pattern then its definition is searched for a
		match. */
	AIAPI AIErr (*PathStyleUsesAIColor) ( AI110PathStyle *pathStyle,
											AI110PathStyleMap *psMap,
											AIColor *color,
											AIBoolean matchTint,
											AIBoolean lookForIndirectUsage,
											AIColorUsedHow *usage );

	/**	A routine which takes an AIColor and applies it to an AI110PathStyle, doing what
		is generally wanted when people ask "why is it such a pain to simply set the
		color of an object?"  

		The path style map parameter is optional.

		If the newColor is a gradient or pattern, only the global object handle is
		relevant - the vector and transform fields are ignored. When the old pathStyle
		is already of the same kind, the existing vector and transform are used; if
		it is not, then default values are used. If newColor is a spot color, though,
		the tint is used. This is because this API is mainly intended for the use of
		the Swatches palette. Swatches contain tint info for spot colors, but they
		do not record gradient vector (even relative vector) or pattern transform data.

		If matchColor is non-null, then the onStroke parameter is ignored, and the
		newColor is applied to the fill and/or the stroke, whichever of them has the
		same color as matchColor. The matching is exact, including color space. This
		will never assign paint to an unpainted stroke or fill unless the matchColor
		is kNoneColor.

		If matchColor is null, then the newColor is applied to the stroke if onStroke
		is true, or to the fill if onStroke is false. (To apply to both, you must
		call this twice.)

		When it can't gather things from the pathStyle (which is assumed to be the "old"
		color of the object in question), it first looks at the current paint style and
		if that's not helpful, uses some reasonable (to me) defaults.  Search for the
		text "DEFAULT" below to find those if you want to muck with them. Defaults
		are only necessary when changing from one kind of color to another (e.g.,
		from a solid to a pattern or gradient) or when assigning color to a fill
		or stroke that was previously unpainted.

		The destination arthandle is used for the case where it needs to figure out the
		gradient vector based on the object's bounds. In the case where the object is
		part of a compound path, the bounds are calculated from the entire compound
		group.

		If whatChanged is non-null, returns in *whatChanged an AIColorUsedHow value
		indicating what part of the pathStyle (fill and/or stroke) was changed. (It is
		not necessary to do a SetPathStyle on the object if the old path style is the
		same as the new one.)
	*/
	AIAPI AIErr (*ApplyAIColorToPathStyle) ( AI110PathStyle *pathStyle,
											AI110PathStyleMap	*psMap,	// can be null
											AIColor			*newColor,
											AIColor			*matchColor,
											AIBoolean		onStroke,
											AIBoolean		useOldTint,
											AIArtHandle		destination,
											AIColorUsedHow	*whatChanged );

	/** Examine the art object, which can be any type, for usage of the targetColor,
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

	/** For any direct usage of the oldColor in the art object, do a SetObjectAIColor to the
		newColor. "Direct" usage means the color of a stroke or fill, including inside graph
		path style change records. It does not cover colors used *inside* gradients, patterns,
		or graph designs that are attached to the object. (Indirect usages inside patterns
		and gradients are to be replaced by defining a new pattern or gradient, then calling
		ReplaceObjectAIColor with the oldColor and newColor being the pattern or gradient
		that was redefined. Indirect usage inside graph designs are similar, except that
		one doesn't call ReplaceObjectAIColor because a graph design isn't a color.)
		
		New for AI9:  if art is nil, replaces all usages in the current document

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

	/** Get the default path style that tools should use when creating new objects other
		than text objects. */
	AIAPI AIErr (*GetInitialPathStyle) ( AI110PathStyle *style );
	/** Set the default path style that tools should use when creating new objects other
		than text objects. */
	AIAPI AIErr (*SetInitialPathStyle) ( AI110PathStyle *style );
	/** Get the default path style that tools should use when creating text objects. */
	AIAPI AIErr (*GetInitialTextStyle) ( AI110PathStyle *style );
	/** Set the default path style that tools should use when creating text objects. */
	AIAPI AIErr (*SetInitialTextStyle) ( AI110PathStyle *style );
	
	/** Take an AIColor structure and make sure that everything in it is appropriate for the
		current artwork, creating replacements if necessary.  For example, if you get a
		pattern from drag&drop, the pattern may not be in the current artwork.  (Usually it
		will be in the clipboard artwork).  This would replace it with an equivalent pattern
		that is in the current artwork. */
	AIAPI AIErr (*RetargetForCurrentDoc) ( AIColor *color) ;

	/** Like SetCurrentPathStyle, except that when a selected object has an active style,
		it will merge the input style values only with the paint attributes, and give
		the object that simple style. Both of the input pointers can be nil to replace
		all selected active styles with the simple style corresponding to their focal
		fill and/or stroke filters.
	*/
	AIAPI AIErr (*SetCurrentPathStyleForceSimple) ( AI110PathStyle *style, AI110PathStyleMap* stylemap );

	/** Like SetPathStyle, except that when a selected object has an active style,
		it will merge the input style values only with the paint attributes, and give
		the object that simple style. The input style can be nil to replace an active
		style with the simple style corresponding to its focal fill and/or stroke filters.
	*/
	AIAPI AIErr (*SetPathStyleForceSimple) ( AIArtHandle path, AI110PathStyle *style );
	
	/** Interpolate the path style.  If percent is 0, styleOut is style0; if percent
		is 1, styleOut is style1. (Despite the misleading param name, percent is
		not a percentage but a value from 0 to 1.) See also the AIPathInterpolateSuite. */
	AIAPI AIErr (*InterpolatePathStyle) ( AI110PathStyle *style0, AI110PathStyle *style1,
		AI110PathStyle *styleOut, AIReal percent);

	/** Interpolate just the AIColor. If color kinds are incompatible (e.g., two patterns),
		colorOut is always returned as color0. See also the AIPathInterpolateSuite. */ 
	AIAPI AIErr (*InterpolateAIColor) ( AIColor *color0, AIColor *color1, AIColor *colorOut,
										AIReal fraction );

};


#include "AIHeaderEnd.h"

#endif
