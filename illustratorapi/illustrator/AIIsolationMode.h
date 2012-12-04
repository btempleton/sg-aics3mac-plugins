#ifndef __AIIsolationMode__
#define __AIIsolationMode__

/*
 *        Name:	AIIsolationMode.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 13.0 Isolation Mode Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2006-2007 Adobe Systems Incorporated.
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

#ifndef __AIMdMemory__
#include "AIMdMemory.h"
#endif

#ifndef _IAIAUTOBUFFER_H_
#include "IAIAutoBuffer.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIIsolationMode.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIIsolationModeSuite				"AI Isolation Mode"
#define kAIIsolationModeSuiteVersion1		AIAPI_VERSION(1)
#define kAIIsolationModeSuiteVersion		kAIIsolationModeSuiteVersion1
#define kAIIsolationModeVersion				kAIIsolationModeSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/** @ingroup Notifiers
	Sent when isolation mode is entered or exited or the isolated art changes. See \c #AIIsolationModeSuite
 */
#define kAIIsolationModeChangedNotifier	"AI Isolation Mode Changed Notifier"

/** @ingroup Notifiers
	Sent when in isolation mode and just before isolation mode changes. The change could be an exit
	from isolation mode or the isolated art changes. See \c #AIIsolationModeSuite.
 */
#define kAIBeforeIsolationModeChangedNotifier	"AI Before Isolation Mode Changed Notifier"

/** Data sent with \c #kAIIsolationModeChangedNotifier.  */
typedef struct {
	/** True if notification was caused by entering isolation mode. False if it was caused by
		exiting isolation mode. */
	AIBoolean inIsolationMode;
	/** The isolated art object. */
	AIArtHandle isolatedArt;
	/** The parent of the isolated art. */
	AIArtHandle isolatedArtParent;
} AIIsolationModeChangedNotifierData;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that handle isolation mode, in which an artwork selection
	is copied, and the copy placed on the artboard in a special isolation layer for editing.
	See \c #AILayerListSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIIsolationModeSuite and \c #kAIIsolationModeVersion.
*/
typedef struct {

	/** Enters isolation mode for a specific group or plug-in group. This art becomes
		the isolated art, replacing any art that was previously isolated. In this mode,
		the user can edit only the isolated art.

		While the art is isolated, \c #AIArtSuite::GetArtParent() does not properly
		retrieve the parent; use \c #GetIsolatedArtAndParents() instead.
			@param art The group or plug-in group art object. Can be in the main art tree
				or in an isolated art tree. Cannot be art inside a dictionary or plug-in group.
			@param invisibleFlag  When true, artwork that is not isolated is made invisible.
			    When false, non-isolated artwork is dimmed.
		*/
	AIAPI AIErr (*EnterIsolationMode)(AIArtHandle art, AIBoolean invisibleFlag);

	/** Exits isolation mode and returns to normal editing mode. The parent chain of
		any previously isolated art is restored. */
	AIAPI AIErr (*ExitIsolationMode)(void);

	/** Retrieves the parent and ancestors of an isolated artwork tree; that is,
		a group or plug-in group that has been passed to \c #EnterIsolationMode().
		(Note that this function does not return an error code.)
			@param isolatedArtParent [out] A buffer in which to return the parent
				art object of the isolated art tree.
			@param parentChain [out] Optional. A buffer in which to return an array of
				0 or more art objects (\c #AIArtHandle) for the ancestors of the
				parent art object.
		*/
	AIAPI void (*GetIsolatedArtAndParents)(AIArtHandle *isolatedArtParent, ai::AutoBuffer<AIArtHandle> *parentChain);


	/** Reports whether isolation mode is in effect.
		(Note that this function returns a boolean value, not an error code.)
			@return True if isolation mode is on, false if it is off.
		*/
	AIAPI ASBoolean (*IsInIsolationMode)(void);

	/** Reports whether artwork is in the isolated layer.
		(Note that this function returns a boolean value, not an error code.)
			@param art The parent art object of the art tree.
			@return True if the artwork is in the isolated layer, false otherwise.
		*/
	AIAPI ASBoolean (*IsIsolatedLayer)(AIArtHandle art);

	/** Reports whether artwork is in a non-isolated layer. Non-isolated art layers
		hold the artwork that is not being edited in isolation mode. Non-isolated artwork
		can be shown in a 50% opacity state in isolation mode, or can be hidden entirely
		when in symbol-editing mode. The Layers palette uses this function to
		exclude non-isolated layers from the palette.
		(Note that this function returns a boolean value, not an error code.)
			@param art The parent art object of the art tree.
			@return True if the artwork is in a non-isolated layer, false otherwise.
		*/
	AIAPI ASBoolean (*IsNonIsolatedLayer)(AIArtHandle art);
	/** Reports whether an art tree is a legal target for isolation mode.
		Art that cannot be isolated includes, for example, art that is
		neither a group nor a plug-in group, groups that are inside
		plug-in groups, or that are locked or hidden, top-level layers,
		and template layers.
			@param art The parent art object of the art tree.
			@return True if the artwork can be isolated or if it is
				already isolated, false otherwise.
		*/
	AIAPI ASBoolean (*CanIsolateArt)(AIArtHandle art);
	
} AIIsolationModeSuite;


#include "AIHeaderEnd.h"


#endif
