#ifndef __AI120LiveEffect__
#define __AI120LiveEffect__

/*
 *        Name:	AI120LiveEffect.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Effect Suite.
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

#include "AILiveEffect.h"

#include "AIHeaderBegin.h"

/** @file AI120LiveEffect.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120LiveEffectSuite				"AI Live Effect Suite"
#define kAILiveEffectSuiteVersion3			AIAPI_VERSION(3)
#define kAI120LiveEffectVersion				kAILiveEffectSuiteVersion3

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite allows your plug-in to implement a Live Effect.
	A Live Effect is a filter that can be attached to an art object as part of
	its style. Any time the art object is changed, the filter is automatically
	re-executed. More than one filter can be attached to an object, which allows
	filter \e chains and \e stacks.
		\li A chain is a pipeline where the output of one filter
			becomes the input to the next.
		\li A stack passes the same input art to a set of filters,
			stacking the output of each filter.

	If a document contains a Live Effect that is not available, the document
	can be opened, but art with that effect applied cannot be edited.

	Your Live Effect plug-in must respond to the caller \c #kCallerAILiveEffect
	and the following selectors:
	<br> \c #kSelectorAIEditLiveEffectParameters
	<br> \c #kSelectorAIGoLiveEffect
	<br> \c #kSelectorAILiveEffectInterpolate
	<br> \c #kSelectorAILiveEffectInputType
	<br> \c #kSelectorAILiveEffectConverColorSpace
	<br> \c #kSelectorAILiveEffectScaleParameters
	<br> \c #kSelectorAILiveEffectHandleMerge
	<br> \c #kSelectorAILiveEffectGetSVGFilter

	Most Live Effects have a set of parameters that control their behavior. For
	example, the Roughen effect has parameters for the size and detail of the roughening.
	You can store these in the parameter dictionary that is associated with the effect
	in the style.  Use the \c #AIDictionarySuite to access the contents of the dictionary.
	You can store any information in the parameter dictionary; however the following keys
	are predefined:
	<br> \c #kDisplayStringKey
	<br> \c #kExtraStringKey
	<br> \c #kFillStyleKey
	<br> \c #kEvenOddKey
	<br> \c #kStrokeStyleKey
	<br> \c #kScaleFactorKey

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAILiveEffectSuite and \c #kAILiveEffectVersion.
*/
typedef struct {

	/** Registers a Live Effect.
			@param effectInfo A pointer to the structure that defines the effect. You must
				allocate and fill the structure before making the call.
			@param liveEffectHandle [out] A buffer in which to return the effect object.
		*/
	AIAPI AIErr (*AddLiveEffect) ( AILiveEffectData* effectInfo, AILiveEffectHandle *liveEffectHandle );

	/** Adds a menu item for a Live Effect to the Effects menu, using a predefined filter.
			@param liveEffectHandle The effect object.
			@param filterHandle	The filter containing the category, title, and options,
				as returned by \c #AIFilterSuite::AddFilter(). If no filter exists with
				the correct data, use \c #AddLiveEffectMenuItem().
			@param menuItem	[out] A buffer in which to return the new menu item,
				or \c NULL if you do not need the object.
			@param menuGroup [out] A buffer in which to return the menu group to which the item
				was added, or \c NULL if you do not need the object.
		*/
	AIAPI AIErr (*AddLiveEffectFilterItem) ( AILiveEffectHandle liveEffectHandle,
		AIFilterHandle filterHandle, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );

	/** Adds a menu item for a Live Effect to the Effects menu.
			@param liveEffectHandle The effect object.
			@param menuName	The unique identifying name for the new menu item.
				Not localized.
			@param menuData	A pointer to the structure that defines the menu.
				You must allocate and fill the structure before making the call.
				If a filter already exists with the correct data, use
				\c #AddLiveEffectFilterItem().
			@param menuItem	[out] A buffer in which to return the new menu item,
				or \c NULL if you do not need the object.
			@param menuGroup [out] A buffer in which to return the menu group to which the item
				was added, or \c NULL if you do not need the object. Returns \c NULL if
				the item was added at the top level of the Effects menu.
		 */
	AIAPI AIErr (*AddLiveEffectMenuItem) ( AILiveEffectHandle liveEffectHandle, const char* menuName,
		 AddLiveEffectMenuData *menuData, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );

	/** Not implemented. */
	AIAPI AIErr (*ExecuteLiveEffect) ( AILiveEffectHandle effect,
				AILiveEffectParameters parameters, AIArtHandle art );

	/** @note Internal. Do not use.

	 	Displays a dialog box in which the use can enter parameter values.
			@param context [in, out] The parameter context passed in the
				\c #AILiveEffectEditParamMessage. Modify in place with new values.
			@param enablePreview  True if previews are enabled for this effect.
				When true, pass the returned context to \c #UpdateParameters()
				to update the associated artwork.
		*/
	AIAPI AIErr (*EditParameters) ( AILiveEffectParamContext context, ASBoolean enablePreview );

	/** If previews are enabled for an effect, call this after modifying the
		parameters to update the associated artwork. The plug-in receives
		an \c #AILiveEffectGoMessage after updating parameters.
			@param context The parameter context, as received in
				a \c #AILiveEffectEditParamMessage.
			@see \c #AILiveEffectInterpParamMessage
		*/
	AIAPI AIErr (*UpdateParameters) ( AILiveEffectParamContext context );

	/** Interpolates a point into the current parameter set for an effect.
		Sends the plug-in that owns the effect the \c #AILiveEffectInterpParamMessage.
			@param effect The effect object.
			@param startParams A parameters block for the starting point.
			@param endParams A parameters block for the ending point.
			@param percent A percentage of the distance between
				the start and end parameters, expressed as a value in the range [0..1].
				The new value is interpolated at this point.
			@param resultParams	[out] A parameters block in which the new interpolated point
				is returned.
		*/
	AIAPI AIErr (*InterpolateEffectParameters) ( AILiveEffectHandle effect,
				AILiveEffectParameters startParams, AILiveEffectParameters endParams,
				AIReal percent, AILiveEffectParameters resultParams );

	/** Gets the number of registered effects available to the application.
		Use with \c #GetNthLiveEffect() to iterate through all installed effects.
			@param count [out] A buffer in which to return the number of registered effects.
		*/
	AIAPI AIErr (*CountLiveEffects) ( long* count );

	/** Retrieves an effect reference by position index.
		Use with \c #CountLiveEffects() to iterate through all installed effects.
			@param n The index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect object.
	*/
	AIAPI AIErr (*GetNthLiveEffect) ( long n, AILiveEffectHandle* effect );

	/** Retrieves the unique identifying name of an effect.
		To get the localizable display name, use \c #GetLiveEffectTitle().
			@param effect The effect object.
			@param name [out] A buffer in which to return the name string.
		*/
	AIAPI AIErr (*GetLiveEffectName) ( AILiveEffectHandle effect, const char** name );

	/** Retrieves the localizable display name of an effect.
		To get the unique identifying name, use \c #GetLiveEffectName().
			@param effect The effect object.
			@param name [out] A buffer in which to return the display name string.
		*/
	AIAPI AIErr (*GetLiveEffectTitle) ( AILiveEffectHandle effect, const char** name );

	/** Retrieves the version information for a registered effect.
			@param effect The effect object.
			@param major [out] A buffer in which to return the major version number.
			@param minor [out] A buffer in which to return the minor version number.
		*/
	AIAPI AIErr (*GetLiveEffectVersion) ( AILiveEffectHandle effect, long* major, long* minor );

	/** Retrieves the preferred input art types of a registered effect.
			@param effect The effect object.
			@param name [out] A buffer in which to return the input art preferences,
				a logical OR of \c #AIStyleFilterPreferredInputArtType values.
		*/
	AIAPI AIErr (*GetInputPreference) ( AILiveEffectHandle effect, long* inputPreference );

	/** Retrieves the style flags of a registered effect.
			@param effect The effect object.
			@param name [out] A buffer in which to return the style flags,
				a logical OR of \c #AIStyleFilterFlags values.
		*/
	AIAPI AIErr (*GetStyleFilterFlags) ( AILiveEffectHandle effect, long* styleFilterFlags );

	/** Merges an effect into the existing style of all selected objects.
			@param effect The effect object.
			@param action The merge method (append, or replace fill and/or stroke),
				and whether to send a \c #kSelectorAILiveEffectHandleMerge message
				to handle the parameters for a replacement method.
		*/
	AIAPI AIErr (*MergeLiveEffectIntoSelection) ( AILiveEffectHandle effect, AILiveEffectMergeAction action );

	/** While handling an \c #AILiveEffectEditParamMessage, retrieves the menu item used
		to invoke the effect.
		(Note that this function returns an object value, not an error code.)
			 @param context The parameter context, as passed in the
			 	\c #AILiveEffectEditParamMessage.
			@return The menu item object, or \c NULL if the message was not invoked by a menu item.
				Returns \c NULL if not called while handling an Edit message.
		 */
	AIAPI AIMenuItemHandle (*GetMenuItem) ( AILiveEffectParamContext context );

	/** Creates a parameter dictionary to be used in constructing a style with the
		\c #AIArtStyleParserSuite. Do not use in any other context.	If you are using
		the \c #AIArtStyleParserSuite to construct a new style from scratch, and you
		need to create a parameter dictionary for an effect, use this function
		to create the parameter dictionary, rather than
		\c #AIDictionarySuite::CreateDictionary(). The dictionary created by this
		function supports Undo operations, which the generic one does not.

		Dictionaries are reference counted; the initial reference count for
		this dictionary is 1. When there are no remaining references,
		free the associated memory using \c #AIDictionarySuite::Release().
			@param params [out] A buffer in which to return the new parameters block.
		*/
	AIAPI AIErr (*CreateLiveEffectParameters) ( AILiveEffectParameters* params );

	/** Retrieves the earliest Illustrator version that an effect supports.
		If you do not use this call, the version defaults to 9 (the first version
		to support Live Effects). If an object with this effect is saved
		to an earlier version, only the styled art is written out.
			@param effect The effect object.
			@param appVersion [out] A buffer in which to return the version number.
	 */
	AIAPI AIErr (*GetLiveEffectAppVersion) ( AILiveEffectHandle effect, AIVersion* appVersion );

	/** Sets the  earliest Illustrator version that an effect supports. If an object with this
		effect is saved to an earlier version, only the styled art is written out.
			@param effect The effect object.
			@param appVersion The version number. Must be 9 or later.
	 	*/
	AIAPI AIErr (*SetLiveEffectAppVersion) ( AILiveEffectHandle effect, AIVersion appVersion );

} AI120LiveEffectSuite;


#include "AIHeaderEnd.h"



#endif // __AI120LiveEffect__
