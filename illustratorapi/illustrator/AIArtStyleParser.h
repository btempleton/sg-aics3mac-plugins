#ifndef __AIArtStyleParser__
#define __AIArtStyleParser__

/*
 *        Name:	AIArtStyleParser.h
 *     Purpose:	Adobe Illustrator Art Style Parser Suite.
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

#ifndef __AIArtStyle__
#include "AIArtStyle.h"
#endif

#ifndef __AILiveEffect__
#include "AILiveEffect.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIArtStyleParser.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIArtStyleParserSuite				"AI Art Style Parser Suite"
#define kAIArtStyleParserSuiteVersion4		AIAPI_VERSION(4)
#define kAIArtStyleParserSuiteVersion		kAIArtStyleParserSuiteVersion4
#define kAIArtStyleParserVersion			kAIArtStyleParserSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

// Opaque references to data structures inside app.
/** Opaque reference to an art style parser. */
typedef struct _t_AIStyleParser* AIStyleParser;
/** Opaque reference to a Live Effect data structure in an art style parser.
		\li Pre-Effects are Live Effects that show up before any fills and strokes in the
	Appearance palette.
		\li Post-Effects are Live Effects that show up after all the fills and strokes in the
	Appearance palette.
	*/
typedef struct _t_AIParserLiveEffect* AIParserLiveEffect;
/** Opaque reference to a Paint Field data structure in an art style parser.
	A Paint Field corresponds to either a fill or a stroke in the art style. It
	can contain Live Effects and a Blend Field. <br><br>
	@note A Paint Field can contain effects that affect only that Paint Field	and not the entire art style.
		Effects are executed in sequence, and the output of one becomes the input of the next.
		Filling or stroking is performed within this order. A Color Position is the spot
		in a Paint Field's effect order at which painting occurs.
	*/
typedef struct _t_AIParserPaintField* AIParserPaintField;
/** Opaque reference to a Blend Field in a Paint Field data structure in an art style parser.
	Controls the overall transparency of the style. This is listed last  in the Appearance palette.
	*/
typedef struct _t_AIParserBlendField* AIParserBlendField;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The \c AIArtStyleParser allows you to manipulate art styles, and access
	information typically shown in the Appearance palette.

	The parser constructs its own data structures when asked to parse an art style, which
	are tied to that art style unless modified. When parser data structures are modified,
	the relationship between the parser structure and art style becomes unreliable, and you should
	avoid making calls to \c #SetFocus() and \c #EditEffectParameters(), which depend on
	that relationship.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArtStyleParserSuite and \c #kAIArtStyleParserVersion.

	You can call \c #CreateNewStyle() to build a new style from an existing parser data structure,
	using a workflow like this:

@code
NewParser(&parser)
ParseStyle(parser, artStyle)
...
<Manipulate the data structures - reordering, adding, removing, redefining properties, and so on.>
	...
CreateNewStyle(parser, &newArtStyle)
DisposeParser(parser)
@endcode

*/
typedef struct {

	/** Constructs a new parser.
			@param parser [out] A buffer in which to return the new parser reference.
		*/
	AIAPI AIErr (*NewParser) ( AIStyleParser* parser );

	/** Frees memory associated with a parser that is no longer needed.
			@param The parser. Upon return, this reference in no longer valid.
	*/
	AIAPI AIErr (*DisposeParser) ( AIStyleParser parser );

	/** Parses the contents of an art style, creating parser data structures accordingly.
			@param parser The parser.
			@param artStyle The art style.
		*/
	AIAPI AIErr (*ParseStyle) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	/** Merges the properties of an art style into a parser. The same as the
		"Merge Graphic Styles" option in the Graphic Styles palette flyout menu.
			@param parser The parser.
			@param artStyle The art style.
		*/
	AIAPI AIErr (*MergeStyleIntoParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	/** Reports whether a parser was able to successfully parse an art style.
		Valid only immediately after a call to \c #ParseStyle() using this parser.
		(Note that this function returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the most recent parsing operation was successful.
		*/
	AIAPI AIBoolean (*IsStyleParseable) ( AIStyleParser parser );

	/** Counts the number of Pre-Effects in a parser. Pre-Effects are Live
		Effects that show up before any fills and strokes in the Appearance palette.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of Pre-Effects.
		*/
	AIAPI ASInt32 (*CountPreEffects) ( AIStyleParser parser );

	/** Counts the number of Post-Effects in a parser. Post-Effects are Live
		Effects that show up after all the fills and strokes in the Appearance palette.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of Post-Effects.
		*/
	AIAPI ASInt32 (*CountPostEffects) ( AIStyleParser parser );

	/** Counts the number of Paint Fields in a parser. A Paint Field corresponds
		to either a fill or a stroke in the art style. Each Paint Field can also
		contain Live Effects and transparency information.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of Paint Fields.*/
	AIAPI ASInt32 (*CountPaintFields) ( AIStyleParser parser );

	/** Counts the number of Live Effects in a Paint Field.
	(Note that this function returns a numeric value, not an error code.)
			@param parser The Paint Field.
			@return The number of Live Effects.
	*/
	AIAPI ASInt32 (*CountEffectsOfPaintField) ( AIParserPaintField paintField );

	/** Retrieves a Pre-Effect from a parser by position index. Use with \c #CountPreEffects()
		to iterate through PreEffects.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.
		 */
	AIAPI AIErr (*GetNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );

	/** Retrieves a Post-Effect from a parser by position index. Use with \c #CountPostEffects()
		to iterate through PostEffects.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.
		*/
	AIAPI AIErr (*GetNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );

	/**Retrieves a Paint Field from a parser by position index. Use with \c #CountPaintFields()
		to iterate through Paint Fields.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numFields-1]</code>.
			@param paintField [out] A buffer in which to return the Paint Field.
		*/
	AIAPI AIErr (*GetNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField* paintField );

	/** Retrieves a Live Effect from a Paint Field by position index. Use with \c #CountEffectsOfPaintField()
		to iterate through Live Effects.
			@param paintField The Paint Field.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.*/
	AIAPI AIErr (*GetNthEffectOfPaintField) ( AIParserPaintField paintField, ASInt32 n,
											  AIParserLiveEffect* effect );

	/** Retrieves the overall art style transparency from a parser in the form of a Blend Field.
			@param parser The parser.
			@param blendField [out] A buffer in which to return the Blend Field.
	*/
	AIAPI AIErr (*GetStyleBlendField) ( AIStyleParser parser, AIParserBlendField* blendField );

	/** Inserts a Pre-Effect into a parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
				insert element at the end.
			@param effect The effect.
		*/
	AIAPI AIErr (*InsertNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );

	/** Inserts a Post-Effect into the parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
				insert element at the end.
			@param effect The effect.
		*/
	AIAPI AIErr (*InsertNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );

	/** Inserts a Paint Field into a parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numFields-1]</code>. Use -1 to
				insert element at the end.
			@param paintField The Paint Field.
		*/
	AIAPI AIErr (*InsertNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField paintField );

	/** Inserts a Live Effect into a Paint Field in a parser at specified index.
			@param parser The parser.
			@param paintField The Paint Field.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
							insert element at the end.
			@param effect The Live Effect.
	 */
	AIAPI AIErr (*InsertNthEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ASInt32 n,
												 AIParserLiveEffect effect );

	/** Removes a Pre-Effect from a parser.
			@param parser The parser.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePreEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes a Post-Effect from a parser.
			@param parser The parser.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePostEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes a Paint Field from a parser.
			@param parser The parser.
			@param paintField The Paint Field.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePaintField) ( AIStyleParser parser, AIParserPaintField paintField, AIBoolean doDelete );

	/** Removes a Live Effect from a Paint Field in a parser.
			@param parser The parser.
			@param paintField The Paint Field.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemoveEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField,
											  AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes all the effects from a parser.
			@param parser The parser.
		*/
	AIAPI AIErr (*RemoveAllEffects) ( AIStyleParser parser );

	/** Removes all the effects and all the Paint Fields from a parser, except the focus fill and stroke.
		These are the ones that the user is currently editing, which show in the fill and stroke
		proxies in the Tool and Color palettes. The function also resets all transparency
		to normal 100% opaque and places the focus stroke on top of the focus fill
		in the stacking order.
			@param parser The parser.
		*/
	AIAPI AIErr (*Simplify) ( AIStyleParser parser );

	/** Retrieves the focus fill from a parser. If an art style has multiple fills,
		the user can only edit one at a time. The one currently being edited is the focus fill,
		and it is shown in the fill/stroke proxies on the Tool and Color palettes.
			@param parser The parser.
			@param paintField [out] A buffer in which to return the focus fill.
		*/
	AIAPI AIErr (*GetFocusFill) ( AIStyleParser parser, AIParserPaintField* paintField );

	/** Retrieves the focus stroke froma parser. If an art style has multiple strokes,
		the user can only edit one at a time. The one currently being edited is the focus stroke,
		and it is shown in the fill/stroke proxies on the Tool and Color palettes.
			@param parser The parser.
			@param paintField [out] A buffer in which to return the focus stroke.
		*/
	AIAPI AIErr (*GetFocusStroke) ( AIStyleParser parser, AIParserPaintField* paintField );

	/** Sets the focus fill or focus stroke for a parser.
			@param parser The parser.
			@param paintField The fill or stroke.
			@see \c #SetFocus()
		*/
	AIAPI AIErr (*SetParserFocus) ( AIStyleParser parser, AIParserPaintField paintField );

	/** Sets the focus fill or focus stroke for a parser, and also modifies the art style
		from which the parser's data structures were constructed.
		Use when the data structures in the given parser have not been
		modified since the call to \c #ParseStyle().
			@param artStyle The art style that was passed to \c #ParseStyle() for this parser
			@param parser The parser
			@param paintField The fill or stroke.
			@see \c #SetParserFocus()
		*/
	AIAPI AIErr (*SetFocus) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserPaintField paintField );

	/**  Retrieves the position in the stacking order (from top to bottom) where the Group
		Contents for a parser would be rendered. (Note that this function returns a numeric value,
		not an error code.)

		Group Contents affects the generation of styled art when applied to art container objects
		like groups or text. The Group Contents controls where the original contents inside
		the group are rendered relative to the stacking order of the fills and strokes
		in the art styles.
			@param parser The parser.
			@return The position in the stacking order.
		*/
	AIAPI ASInt32 (*GetGroupContentsPosition) ( AIStyleParser parser );

	/** Move the Group Contents position in a parser.
			@param parser The parser.
			@param position The new position in the stacking order, from top to bottom.
			@see \c #GetGroupContentsPosition()
		*/
	AIAPI AIErr (*MoveGroupContentsPosition) ( AIStyleParser parser, ASInt32 position );

	/** Constructs a new art style based on the elements in a parser.
		Call \c #ParseStyle() with the new style before using \c #SetFocus()
		or \c #EditEffectParameters().
			@param parser The parser.
			@param artStyle [out] A buffer in which to return the new art style reference.
		*/
	AIAPI AIErr (*CreateNewStyle) ( AIStyleParser parser, AIArtStyleHandle* artStyle );

	/** Reports whether a style is invisible; that is, there are no effects,
		all the paint fields have a color of \c none, and the overall transparency
		contains default values. (Note that this function returns a boolean value,
		not an error code.)
			@param parser The parser.
			@return True if the associated style is invisible.
		*/
	AIAPI AIBoolean (*IsStyleVisible) ( AIStyleParser parser );

	/** Reports whether a parser has fill or stroke. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any non-empty fill or stroke values.
		*/
	AIAPI AIBoolean (*ContainsPaint) ( AIStyleParser parser );

	/** Reports whether a parser has any Live Effects. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any effects.
		*/
	AIAPI AIBoolean (*ContainsEffects) ( AIStyleParser parser );

	/** Reports whether a parser has transparency. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any non-default transparency information.
		*/
	AIAPI AIBoolean (*ContainsTransparency) ( AIStyleParser parser );

	/** Retrieves the \c AILiveEffectHandle (see \c AILiveEffect.h) for a Live Effect
		data structure in a parser.
			@param parser The parser.
			@param liveEffectHandle [out] A buffer in which to return the Live Effect reference.
		*/
	AIAPI AIErr (*GetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle* liveEffectHandle );

	/** Retrieves the \c AILiveEffectParameters (see \c AILiveEffect.h) for a Live Effect
		data structure in a parser.
			@param effect The effect.
			@param params [out] A buffer in which to return the Live Effect parameters.
		*/
	AIAPI AIErr (*GetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters* params );

	/** Sets the Live Effect reference (see \c AILiveEffect.h) for a Live Effect data structure
		in a parser.
			@param parser The parser.
			@param liveEffectHandle The Live Effect reference.
		*/
	AIAPI AIErr (*SetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle liveEffectHandle );

	/** Sets the  Live Effect parameters (see \c AILiveEffect.h) for a Live Effect data structure
		in a parser.
			@param effect The effect.
			@param params The Live Effect parameters.
		*/
	AIAPI AIErr (*SetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters params );

	/** Copies a Live Effect data structure into a new equivalent structure. Used by
		the Appearance palette when users duplicate a Live Effect.
			@param effect The effect.
			@param clonedEffect [out] A buffer in which to return the new Live Effect.
		*/
	AIAPI AIErr (*CloneLiveEffect) ( AIParserLiveEffect effect, AIParserLiveEffect* clonedEffect );

	/** Opens the editing dialog, allowing the user to edit the parameters
		of an effect in an art style, and creates a new art style with the user's choices,
		which is applied to all the art objects currently targeted in the document.

		@note Use this function with caution.

			@param artStyle The art style, as previously passed to \c #ParseStyle().
			@param effect The effect, as retrieves from a parser whose data structures
				have not been modified since the call \c #ParseStyle().
		*/
	AIAPI AIErr (*EditEffectParameters) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect );

	/** Reports whether a Paint Field corresponds to a fill. (Note that this function
		returns a boolean value, not an error code.)
			@param paintField The Paint Field.
			@return True if the Paint Field is for a fill.
	 */
	AIAPI AIBoolean (*IsFill) ( AIParserPaintField paintField );

	/** Reports whether a Paint Field corresponds to a stroke. (Note that this function
		returns a boolean value, not an error code.)
			@param paintField The Paint Field.
			@return True if the Paint Field is for a stroke.
	 */
	AIAPI AIBoolean (*IsStroke) ( AIParserPaintField paintField );

	/** Retrieves fill information from a Paint Field.
			@param paintField The Paint Field.
			@param fill [out] A buffer in which to return the fill style.
			@param paintData [out] A buffer in which to return additional paint data.
	  */
	AIAPI AIErr (*GetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	/** Retrieves stroke information from a Paint Field.
			@param paintField The Paint Field.
			@param stroke [out] A buffer in which to return the stroke style.
			@param paintData [out] A buffer in which to return additional paint data.
		*/
	AIAPI AIErr (*GetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	/** Sets fill information for a Paint Field.
			@param paintField The Paint Field.
			@param fill The new fill style.
			@param paintData Additional paint data.
		*/
	AIAPI AIErr (*SetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	/** Sets stroke information for a Paint Field.
			@param paintField The Paint Field.
			@param stroke The new stroke style.
			@param paintData Additional paint data. */
	AIAPI AIErr (*SetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	/** Retrieves transparency information from a Paint Field. See \c AIMask.h for the
		keys used to get information from the dictionary.
			@param paintField The Paint Field.
			@param blendDict [out] A buffer in which to return the dictionary containing transparency information.
		*/
	AIAPI AIErr (*GetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	/** Sets the transparency information for a Paint Field. See \c AIMask.h for the
		keys used to set information in the dictionary.
			@param paintField The Paint Field.
			@param blendDict The dictionary containing transparency information.
		*/
	AIAPI AIErr (*SetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	/** Retrieves the color position of a Paint Field (the point in effect order at which painting occurs).
			@param paintField The Paint Field.
		*/
	AIAPI ASInt32 (*GetColorPosn) ( AIParserPaintField paintField );

	/** Sets the color position of a Paint Field (the point in the effect order at which painting occurs).
			@param paintField The Paint Field.
		*/
	AIAPI AIErr (*SetColorPosn) ( AIParserPaintField paintField, ASInt32 colorPosn );

	/** Copies a Paint Field data structure into a newly created equivalent structure. Used by
		the Appearance palette when users duplicate a fill or stroke.
			@param paintField The Paint Field.
			@param clonedPaintField [out] A buffer in which to return the new Paint Field.

		*/
	AIAPI AIErr (*ClonePaintField) ( AIParserPaintField paintField, AIParserPaintField* clonedPaintField );

	/**	Retrieves both LiveEffect and parameter references (see \c AILiveEffect.h) for Live Effects in
		a Paint Field that substitute for the built-in fill or stroke behavior.

			@note The only current example is Brushes, which is implemented
			as a Live Effect that replaces the default stroking behavior.
			@param paintField The Paint Field
			@param liveEffectHandle [out] A buffer in which to return the Live Effect reference.
			@param params [out] A buffer in which to return the Live Effect parameters,
		*/
	AIAPI AIErr (*GetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle* liveEffectHandle,
											AILiveEffectParameters* params );

	/** Sets the LiveEffect and parameter references (see \c AILiveEffect.h) for Live Effects in
		a Paint Field that substitute for the built-in fill or stroke behavior.

			@note The only current example is Brushes, which is implemented
			as a Live Effect that replaces the default stroking behavior.
			@param paintField The Paint Field
			@param liveEffectHandle The Live Effect reference.
			@param params The Live Effect parameters,
		*/
	AIAPI AIErr (*SetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle liveEffectHandle,
											AILiveEffectParameters params );

	/** Retrieves the transparency information for a Blend Field. See \c AIMask.h for the keys used
		to access information in the dictionary.
			@param blendField The Blend Field.
			@param blendDict The dictionary in which to return the transparency information.
		*/
	AIAPI AIErr (*GetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	/** Sets the transparency information for a Blend Field. See \c AIMask.h for the keys used
		to access information in the dictionary.
			@param blendField The Blend Field.
			@param blendDict The dictionary containing the transparency information.
		*/
	AIAPI AIErr (*SetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	// NEW FOR AI10

	/** Retrieves the even-odd fill rule for a Paint Field.
		(See the \c evenodd field in the \c #AIPathStyle structure.)
			@param paintField The Paint Field.
			@param evenodd [out] A buffer in which to return true if the even-odd rule is used to determine path insideness .
			@return An error \c #kBadParameterErr if the Paint Field does not correspond to a fill.
		 */
	AIAPI AIErr (*GetEvenOdd) ( AIParserPaintField paintField, AIBoolean* evenodd );

	/** Sets the even-odd fill rule for a Paint Field.
		(See the \c evenodd field in the \c #AIPathStyle structure.)
			@param paintField The Paint Field.
			@param evenodd True if the even-odd rule should be used to determine path insideness.
			@return An error \c #kBadParameterErr if the Paint Field does not correspond to a fill. */
	AIAPI AIErr (*SetEvenOdd) ( AIParserPaintField paintField, AIBoolean evenodd );

	/** Constructs a new Paint Field with a given fill, even-odd fill rule, and
		gradient vector information. The new Paint Field is not associated with any parser.
			@param fill The fill style.
			@param evenOdd True if the even-odd rule should be used to determine path insideness.
			@param paintData The paint data structure containing the gradient vector information. Can be \c NULL.
			@param paintField [out] A buffer in which to return the new Paint Field.
		 */
	AIAPI AIErr (*NewPaintFieldFill) ( const AIFillStyle* fill, AIBoolean evenOdd, const AIArtStylePaintData* paintData,
									   AIParserPaintField* paintField );

	/** Constructs a new Paint Field with a given stroke. The new Paint Field is not associated with any parser.
			@param stroke The stroke style.
			@param paintData Not used, pass \c NULL.
			@param paintField [out] A buffer in which to return the new Paint Field.
		*/
	AIAPI AIErr (*NewPaintFieldStroke) ( const AIStrokeStyle* stroke, const AIArtStylePaintData* paintData,
										 AIParserPaintField* paintField );

	/** Frees the memory associated with a Paint Field.
			@note Do not use on Paint Fields that are retrieved from or inserted into a parser.
			Freeing the parser with \c #DisposeParser() frees its contained data structures.
			@param paintField The Paint Field. Upon return, this references is no longer valid.
		*/
	AIAPI AIErr (*DisposePaintField) ( AIParserPaintField paintField );

	/** Constructs a new Live Effect parser data structure from Live Effect and
		parameters references (see \c AILiveEffect.h). The new data structure is not associated
		with any parser.
			@param liveEffectHandle The Live Effect reference.
			@param params The parameters reference.
			@param effect [out] A buffer in which to return the new effect.
		*/
	AIAPI AIErr (*NewParserLiveEffect) ( AILiveEffectHandle liveEffectHandle, AILiveEffectParameters params,
										 AIParserLiveEffect* effect );

	/** Frees the memory associated with a Live Effect parser data structure.
			@note Do not use on effects that are retrieved from or inserted into a parser.
			Freeing the parser with \c #DisposeParser() frees its contained data structures.
			@param effect The Live Effect data structure. Upon return, this references is no longer valid. */
	AIAPI AIErr (*DisposeParserLiveEffect) ( AIParserLiveEffect effect );


	/** Retrieves the art style that is currently selected in the Graphic Styles palette. Gets the first of
		multiple selected styles.
			@param style [out] A buffer in which to return the art style, or \c NULL if no style is selected.
		 */
	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* style );

	// NEW FOR AI13

	/** Opens the editing dialog, allowing the user to edit the parameters of an effect that is substituting
		for a fill or stroke. Creates a new art style with the user's choices, and applies it to all the art
		objects currently targeted in the document.
			@note Use this function with caution.

			@param artStyle The art style, as previously passed to \c #ParseStyle().
			@param paintField The paint field, as retrieved from a parser whose data structures
				have not been modified since the call \c #ParseStyle().
			@see \c #EditEffectParameters()
		*/
	AIAPI AIErr (*EditPaintEffectParameters) ( AIArtStyleHandle artStyle, AIParserPaintField paintField );

	/** Reports whether a paint field has normal 100% opacity. Does not check other
		transparency attributes, such as knockout or isolated blending. (Note that this
		function returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field is opaque.
		*/
	AIAPI AIBoolean (*IsNormalOpaquePaintBlend) ( AIParserPaintField paintField );

	/** Reports whether a blend field has normal 100% opacity. Does not check other
		transparency attributes, such as knockout or isolated blending. (Note that this
		function returns a boolean value, not an error code.)
			@param blendField The blend field.
			@return True if the blend field is opaque.
		*/
	AIAPI AIBoolean (*IsNormalOpaqueBlend) ( AIParserBlendField blendField );

	/** Reports whether a paint field has a default blend, that is, normal 100% opacity
		with non-isolated blending and the knockout attribute set to either off or inherit. (Note that this
		function returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field has a default blend.
		*/
	AIAPI AIBoolean (*IsDefaultPaintBlend) ( AIParserPaintField paintField );

	/** Sets a paint field to have a default blend; that is, normal 100% opacity, with non-isolated blending
		and the knockout attribute set to off.
			@param paintField The paint field.
		*/
	AIAPI AIErr (*SetDefaultPaintBlend) ( AIParserPaintField paintField );

	/** Reports whether a blend field is a default blend; that is, normal 100% opacity,
		with non-isolated blending and the knockout attribute set to either off or inherit. (Note that this
		function returns a boolean value, not an error code.)
			@param blendField The blend field.
			@return True if the blend field is a default blend.
		*/
	AIAPI AIBoolean (*IsDefaultBlend) ( AIParserBlendField blendField );

	/** Sets a blend field to a default blend; that is, normal 100% opacity, with non-isolated blending
		and the knockout attribute either set to off or maintained at the inherited value.
			@param blendField The blend field to set.
			@param knockoutOff True to turn knockout off. False to maintain the inherited knockout value,
				unless that value is on, in which case it is set to off.
		*/
	AIAPI AIErr (*SetDefaultBlend) ( AIParserBlendField blendField, AIBoolean knockoutOff );

	/** Reports whether the style parsed by a parser is a simple style; that is, a style
		with no effects, only one normal fully opaque fill and one normal fully opaque stroke, and the stroke
		stacked on top of the fill. (Note that this function returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parsed style is simple.
		*/
	AIAPI AIBoolean (*IsStyleSimple) ( AIStyleParser parser );

	/** Retrieves the name and major and minor versions of the Live Effect data structure in a parser.
		Gets the name and version numbers even if the  plug-in that provides the effect is
		missing and there is no \c #AILiveEffectHandle associated with the data structure.
			@param effect The Live Effect data structure.
			@param name [out] A buffer in which to return the internal name of the effect.
			@param major [out] A buffer in which to return the major version of the effect.
			@param minor [out] A buffer in which to return the minor version of the effect.
		*/
	AIAPI AIErr (*GetLiveEffectNameAndVersion) ( AIParserLiveEffect effect, const char** name, long* major, long* minor );
	/** Retrieves the name and major and minor versions of the Live Effect in a paint field data structure in a parser.
		Gets the name and version numbers even if the  plug-in that provides the effect is missing.
			@param paintField The paint field data structure.
			@param name [out] A buffer in which to return the internal name of the effect,
				or \c NULL if no Live Effect is substituting for the built-in fill or stroke behavior.
			@param major [out] A buffer in which to return the major version of the effect,
				or 0 if no Live Effect is substituting for the built-in fill or stroke behavior.
			@param minor [out] A buffer in which to return the minor version of the effect,
				or 0 if no Live Effect is substituting for the built-in fill or stroke behavior.
		*/
	AIAPI AIErr (*GetPaintLiveEffectNameAndVersion) ( AIParserPaintField paintField, const char** name, long* major, long* minor );

} AIArtStyleParserSuite;


#include "AIHeaderEnd.h"


#endif
