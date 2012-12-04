#ifndef __AI110ArtStyle__
#define __AI110ArtStyle__

/*
 *        Name:	AI110ArtStyle.h
 *     Purpose:	Adobe Illustrator Art Style Suite.
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

#include "AIArtStyle.h"

#include "AIHeaderBegin.h"

/** @file AIArtStyle.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110ArtStyleSuite				kAIArtStyleSuite
#define kAIArtStyleSuiteVersion3		AIAPI_VERSION(3)
#define kAI110ArtStyleSuiteVersion		kAIArtStyleSuiteVersion3



/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The functions in the Art Style suite are used for retrieving and setting
	art styles on artwork in Illustrator documents. 
	
	In AI8, Illustrator introduced the concept of plugin groups, where the art
	that was actually printed (result art) was separate from the art that the 
	user edited (edit art).	This concept was extended in AI9 with the introduction
	of art styles. Now, any art object in the document (including groups and
	text objects) can optionally have "styled art" attached to it. It is this 
	"styled art" that gets printed, not the original "source art".

	In the UI, the appearance palette controls the "styled art" that gets 
	generated. Therefore, it is not wise to modify the "styled art" through a 
	plug-in, since the "styled art" can get re-generated at any time. (This is 
	similar to plugin groups.)
	
	In the implementation, the art style applied to an Illustrator art object
	controls the "styled art" that gets generated. Developers can influence the
	styled art by modifying the art style applied to an art object. Export plug-ins
	should export the "styled art," if any, applied to the object, rather than
	the original "source art." 
	
	In the UI, the art style applied to an Illustrator art object is known as the
	object's "appearance" and is most often manipulated through the appearance 
	palette. Appearances can also be saved and reused on other objects through the
	graphic styles palette.
*/
typedef struct {

	/** Return the art objects that make up the "styled art" of an Illustrator
		art object. There is an assumption that objects inside "styled art" do
		not themselves contain different "styled art". In other words, there is
		only one level of indirection. This API may return the same source art
		passed in, meaning there is no other different representation for 
		printing. Additionally, the API may return NULL if processing the object's
		art style (aka "appearance" in Illustrator's UI) produced an error of 
		some kind (eg. a live effect failed to execute because of memory constraints). */
	AIAPI AIErr (*GetStyledArt) ( AIArtHandle art, AIArtHandle* styledArt );

	/** Return the art style handle attached the given art object. This may return
		NULL for the art style if there currently is no art style applied. NULL 
		art styles are common on kGroupArt, kPlacedArt, and kPluginArt. */
	AIAPI AIErr (*GetArtStyle) ( AIArtHandle art, AIArtStyleHandle* artStyle );
	/** Return the art style currently displayed in the appearance palette. If the
		appearance palette shows "Mixed," then mixedState will return true. If that is
		the case, then the art style returned is a simple style which is an attempt to 
		gather the common attributes of the art styles attached to the currently 
		selected objects in the current document. */
	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* artStyle, AIBoolean* mixedState );
	/** Art styles also fall into two buckets: "named" and "anonymous". Those that are
		named are listed in the graphic styles palette. All art styles have a unique 
		name, regardless of whether they are "named" or "anonymous". This API returns 
		the art style with the given name. If searchAllStyles is false, then only the
		art styles listed in the graphic styles palette are searched. If searchAllStyles 
		is true, then all art styles in the current document, including "anonymous" art
		styles, are searched. */
	AIAPI AIErr (*GetArtStyleByName) ( AIArtStyleHandle* artStyle, const char* name,
									   AIBoolean searchAllStyles );
	/** Return the number of art styles currently listed in the graphic styles palette. */
	AIAPI AIErr (*CountNamedArtStyles) ( long* count );
	/** Return the nth art style currently listed in the graphic styles palette. 0-based. */
	AIAPI AIErr (*GetNthNamedArtStyle) ( long n, AIArtStyleHandle* artStyle );

	/** Apply the given art style to the given art object. This can return 
		#kStyleNotInCurrentDocument if the given art style is not in the current document.
		NULL is an acceptable value for the artStyle parameter, which essentially strips
		off any appearance applied to the object. */
	AIAPI AIErr (*SetArtStyle) ( AIArtHandle art, AIArtStyleHandle artStyle );
	/** Apply the given art style to the currently targeted objects on the artboard. This
		is the same API that the graphic styles palette uses when a user clicks on one of
		the styles there. This can return #kStyleNotInCurrentDocument if the given art 
		style is not in the current document.*/
	AIAPI AIErr (*SetCurrentArtStyle) ( AIArtStyleHandle artStyle );

	/** Art styles also fall into two buckets: "named" and "anonymous". Those that are
		named are listed in the graphic styles palette. All art styles have a unique 
		name, regardless of whether they are "named" or "anonymous". This API retrieves
		the name of the given art style. The isAnonymous parameter indicates whether 
		the art style is "named" or "anonymous". */
	AIAPI AIErr (*GetArtStyleName) ( AIArtStyleHandle artStyle, char* name, long maxChars,
									 AIBoolean* isAnonymous );
	/** Set the name of the given art style. Style names are limited to 64 characters
		(including the terminating NULL character).	The style must be a "named" 
		style. Renaming "anonymous" styles is not allowed.	Clients must use
		#AddNamedStyle if they wish to convert an "anonymous" style to a "named" style. 
		This can return #kStyleNotInCurrentDocument if the given art style is not in
		the current document. Returns kNameInUseErr if another art style already exists
		with the given name. Empty ("") names are not allowed. */
	AIAPI AIErr (*SetArtStyleName) ( AIArtStyleHandle artStyle, const char* name );
	/** Returns the paint information for the given art style, using the #AIPathStyle
		to return information about the fill and stroke and the even-odd fill rule.
		Because the AIPathStyle struct is not equipped to report the gradient vector
		length and origin independent of an object's location on the artboard, the 
		paintData parameter can be used to retrieve the gradient vector and origin 
		independent of artboard location. The information in paintData is reported
		relative to an object's bounding box. */
	AIAPI AIErr (*GetPaintAttributes) ( AIArtStyleHandle artStyle, AIPathStyle* aiPathStyle,
										AIArtStylePaintData* paintData );
	
	/** Create a new art style based on the given parameters. The aiPathStyle 
		parameter controls the fill and stroke, the paintData parameter controls
		gradient vector and origin information, and the blendDict parameter controls
		the transparency information. Both paintData and blendDict are allowed to be
		NULL. */
	AIAPI AIErr (*NewStyle) ( AIPathStyle* aiPathStyle, AIArtStylePaintData* paintData,
							  AIDictionaryRef blendDict, AIArtStyleHandle* newStyle );
	/** Create a new identical "named" art style from the art style given and assign
		the given name to it. If uniquify is true, then this API may use a different
		name (ie. append a "1" or "2") for the new art style if the given name is 
		already in use. If uniquify is false, then this API will return kNameInUseErr
		if the name is already in use. Style names are limited to 64 characters 
		(including the terminating NULL character). The new art style should appear in
		the graphic styles palette after this call. */
	AIAPI AIErr (*AddNamedStyle) ( AIArtStyleHandle artStyle, const char* name, AIBoolean uniquify,
								   AIArtStyleHandle* namedStyle );
	/** Remove the given art style from the list of "named" styles listed in the graphic
		styles palette. This API will also return a new "anonymous" style that contains
		the same properties as the named style. This can return #kStyleNotInCurrentDocument
		if the given art style is not in the current document. */
	AIAPI AIErr (*RemoveNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );
	/** Create an "anonymous" copy of the "named" art style passed in. If the given art
		style is already anonymous, then it is simply copied to the output art style. */
	AIAPI AIErr (*CreateAnonymousStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );
	/** Redefine the given "named" art style to have the same characteristics as the
		given dstStyle. Returns an error if the given namedStyle is not actually a
		"named" style. This can return #kStyleNotInCurrentDocument if the given namedStyle
		is not in the current document. */
	AIAPI AIErr (*RedefineNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle dstStyle );
	/** Moves the given "named" art style to the index specified in the graphic styles 
		palette. Use -1 to move the art style to the end of the list of graphic styles. */
	AIAPI AIErr (*MoveNamedStyle) (AIArtStyleHandle namedStyle, int index);
	
	/** Equivalent to GetArtStyleByName() except that this API can be used to retrieve
		art styles that are not in the current document. Additionally, this API only 
		searches the "named" art styles that would be listed in the graphic styles palette
		if the given document were the current document. */
	AIAPI AIErr (*GetArtStyleByNameFromDocument) ( AIArtStyleHandle* artStyle, const char* name,
												   AIDocumentHandle document );
	/** Equivalent to CountNamedArtStyles() except that this API can be used to get
		information from documents that aren't the current document. */
	AIAPI AIErr (*CountNamedArtStylesFromDocument) ( long* count, AIDocumentHandle document );
	/** Equivalent to GetNthNamedArtStyle() except that this API can be used to get
		information from documents that aren't the current document. */
	AIAPI AIErr (*GetNthNamedArtStyleFromDocument) ( long n, AIArtStyleHandle* artStyle,
													 AIDocumentHandle document );
	
	/** Tests equivalence between two art styles. Due to the current implementation,
		there may be some instances where this API still returns false when given two art
		styles that should otherwise be considered equivalent. */
	AIAPI AIErr (*Equiv) ( AIArtStyleHandle artStyle1, AIArtStyleHandle artStyle2,
							  AIBoolean* result );

	/** Sort the "named" art styles in the current document by their name. The order
		will be reflected in the graphic styles palette. */
	AIAPI AIErr (*SortNamedStyles) ( void );
	
	/** Retrieve the default art style of the document, always listed first in the graphic
		styles palette. */
	AIAPI AIErr (*GetDefaultArtStyle) (AIArtStyleHandle* artStyle);
	
	/** Validating that the given art style exists in the current document. */
	AIAPI AIBoolean (*ValidateArtStyle) ( AIArtStyleHandle artStyle );
	
	/** Flattens (expands) the style of an art object.

		This replaces the given art object with the art that would have been returned
		in a call to GetStyledArt. It takes care of doing such things as transferring
		opacity masks, URLs, tags, etc. from the input art to the flattened art.
		Clients should be wary that the art handle passed in might be invalidated
		after this call returns. Clients should not depend on the value of 'art' after
		this call returns.

		Note: The routine GetFlattenedArt, added for AI 10, should be used instead
		if you want to do anything else with the flattened art. This version is kept
		here mainly for backward-compatibility with older plugins. */
	AIAPI AIErr (*FlattenStyle) ( AIArtHandle art );
	
	/** Gets the style type, for efficiency reasons. See #AIArtStyleType. */
	AIAPI AIErr (*GetArtStyleType) ( AIArtStyleHandle artStyle, short* type );
	
	/** Returns true if the given art style contains all the pieces it needs in order
		to execute. Will return false if the given art style contains an effect that is
		provided by a plug-in which is currently not found in the Plug-Ins folder. */
	AIAPI AIBoolean (*CanExecute) ( AIArtStyleHandle artStyle );
	
	/** Get the scale factor for the given object's style.

		There is an option "Scale Strokes & Effects" inside Illustrator. Scaling operations
		now have the ability to scale the stroke weight and effects attached to the art.
		However, if the art style is a "named" style, we do not want to break the link to
		the "named" style just because the object was scaled. To get around this, we added
		a scale factor that is stored on a per object basis. So, even if the style attached
		to an object has a stroke with a weight of 2 pt, if the object's scale factor is 2.5, 
		then the visual stroke weight is 5 pt.

		Here is a small subtle point: Calling GetPaintAttributes from this suite will return
		the _unscaled_ stroke weight. In addition, going through the AIArtStyleParser suite, you
		will get the _unscaled_ parameters of all the strokes and effects. However, the old 
		AIPathStyle suite calls will always return the _scaled_ stroke weights attached to 
		the objects.

		The call ResetArtStyleScaleFactor will attach a new style to the given object with
		all the strokes and effects scaled appropriately according to the object's original scale
		factor. The object's scale factor is then reverted back to 1.0 after the new style is 
		attached. */
	AIAPI AIReal (*GetArtStyleScaleFactor) ( AIArtHandle art );
	/** Set the scale factor for the given object's style. See GetArtStyleScaleFactor() for
		more information. */
	AIAPI AIErr (*SetArtStyleScaleFactor) ( AIArtHandle art, AIReal scaleFactor );
	/** Applies a new style to the object that is scaled by the current scale factor and
		resets the scale factor for the object to 1. See GetArtStyleScaleFactor() for more
		information. */
	AIAPI AIErr (*ResetArtStyleScaleFactor) ( AIArtHandle art );

	/** Transform the artStyle of an object (flags are from AITransformArt.h)

		If the kTransformObjects flag is on, the assumption is made that the art object itself
		has also been transformed by the same matrix, and that any transformation of the points,
		descendant art, etc. has already been performed. (This allows gradient vectors and
		other style attributes that are dependent upon object bounds to be adjusted immediately
		rather than deferred until artwork synchronization.) */
	AIAPI AIErr (*TransformObjectArtStyle) ( AIArtHandle art, AIRealMatrix *matrix, AIReal lineScale, long flags );
	
	/** Retrieve the name of the default style. This can vary from language to language. */
	AIAPI AIErr (*GetDefaultArtStyleName) ( char* name, long maxChars );
	
	/** Examine the artStyle for specified contents, and return which ones were found. */
	AIAPI AIArtStyleHasAttrs (*ExamineStyle) ( AIArtStyleHandle artStyle, AIArtStyleHasAttrs checkFor );

	/** Get the art style that will be used for new art. Based on preferences. */
	AIAPI AIErr (*GetToolArtStyle) ( AIArtStyleHandle* artStyle );

	// ===================== NEW FOR Illustrator 10.0 =========================

	/** Flattening (expanding) the style of an art object and returning the results.

		This is exactly like FlattenStyle(), except that it returns the flattened art,
		so that you don't have to try to find it by following links from a sibling,
		parent, layer, dictionary entry, etc. It will still generally dispose the
		input 'art', unless no flattening was needed. */
	AIAPI AIErr (*GetFlattenedArt) ( AIArtHandle art, AIArtHandle *flattenedArt );

	/** Returns true if the object has a style that would be equivalent to a null style.
		(Saves the client from having to verify that the style has no fill, no stroke, 
		no effects, and default transparency attributes.) */
	AIAPI AIBoolean (*HasEffectiveNullStyle) ( AIArtHandle art );

	/** Returns the map that parallels the path style you can get through GetPaintAttributes.
	   The only time you should get unknowns is if this is an art style associated with a 
	   graph object. */
	AIAPI AIErr (*GetPaintMap) ( AIArtStyleHandle artStyle, AIPathStyleMap* aiPathStyleMap );


} AI110ArtStyleSuite;


#include "AIHeaderEnd.h"


#endif //__AI110ArtStyle__
