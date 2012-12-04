#ifndef __AI90LiveEffect__
#define __AI90LiveEffect__

/*
 *        Name:	AI90LiveEffect.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Effect Suite.
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


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90LiveEffectSuite				kAILiveEffectSuite
#define kAILiveEffectSuiteVersion2			AIAPI_VERSION(2)
#define kAI90LiveEffectVersion				kAILiveEffectSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	// Call made by a plug-in to decalare a live effect
	AIAPI AIErr (*AddLiveEffect) ( AILiveEffectData* effectInfo, AILiveEffectHandle *liveEffectHandle );

	// Add a live effect to the Effects menu.  If there is already a filter with the
	// desired category, title, and options, use AddLiveEffectFilterItem.
	// Menu parameters can be nil if the plugin doesn't care about them
	AIAPI AIErr (*AddLiveEffectFilterItem) ( AILiveEffectHandle liveEffectHandle,
		AIFilterHandle filterHandle, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );
	AIAPI AIErr (*AddLiveEffectMenuItem) ( AILiveEffectHandle liveEffectHandle,
		 AddLiveEffectMenuData *menuData, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );

	// Asks the passed live effect item to execute on the passed art with the
	// passed parameter set.
	AIAPI AIErr (*ExecuteLiveEffect) ( AILiveEffectHandle effect,
				AILiveEffectParameters parameters, AIArtHandle art );

	// Asks the passed live effect item to get parameters from the user
	AIAPI AIErr (*EditParameters) ( AILiveEffectParamContext context, ASBoolean enablePreview );
	AIAPI AIErr (*UpdateParameters) ( AILiveEffectParamContext context );
	
	// Asks the passed live effect to interpolate its parameters between startParams and
	// endParams at the 'percent' point between them.  'percent' should be in the range [0,1]
	AIAPI AIErr (*InterpolateEffectParameters) ( AILiveEffectHandle effect,
				AILiveEffectParameters startParams, AILiveEffectParameters endParams,
				AIReal percent, AILiveEffectParameters resultParams );

	// Returns the number of live effects available
	AIAPI AIErr (*CountLiveEffects) ( long* count );
	// An index into the list of known live effects 'n' is passed to the function
	// which returns the handle for the corresponding live effect.
	AIAPI AIErr (*GetNthLiveEffect) ( long n, AILiveEffectHandle* effect );

	// Return the name of the live effect associated with the passed handle.
	AIAPI AIErr (*GetLiveEffectName) ( AILiveEffectHandle effect, const char** name );
	// Return the name of the live effect associated with the passed handle.
	AIAPI AIErr (*GetLiveEffectTitle) ( AILiveEffectHandle effect, const char** name );
	// Return the version of the live effect associated with the passed handle.
	AIAPI AIErr (*GetLiveEffectVersion) ( AILiveEffectHandle effect, long* major, long* minor );
	// Return the preferred input types of the live effect associated with the passed handle.
	AIAPI AIErr (*GetInputPreference) ( AILiveEffectHandle effect, long* inputPreference );
	// Return the filter flags of the live effect associated with the passed handle.
	AIAPI AIErr (*GetStyleFilterFlags) ( AILiveEffectHandle effect, long* styleFilterFlags );

	// Merge a live effect into the style of all selected objects
	AIAPI AIErr (*MergeLiveEffectIntoSelection) ( AILiveEffectHandle effect, AILiveEffectMergeAction action );

	// Valid during while handling a AILiveEffectEditParamMessage; returns menu item used
	// to invoke the live effect.  Returns nil if called during other times, or if the
	// message was not a result of the user invoking a menu item.
	AIAPI AIMenuItemHandle (*GetMenuItem) ( AILiveEffectParamContext context );
	
	// Create a parameter dictionary to be used in constructing a style with the
	// AIStyleParserSuite.  Should not be used in other circumstances.
	// Initial reference count for this dictionary is 1; caller must release it
	// with sAIDictionary->Release when finished using it
	AIAPI AIErr (*CreateLiveEffectParameters) ( AILiveEffectParameters* params );

} AI90LiveEffectSuite;

#include "AIHeaderEnd.h"

#endif
