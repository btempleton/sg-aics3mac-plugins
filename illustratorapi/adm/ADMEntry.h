/*******************************************************************************
*
* ADMEntry.h -- ADM Entry Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Dave Lazarony, 09 Mar 1996
*
********************************************************************************/

/** @file ADMEntry.h ADM Entry Suite */

#ifndef __ADMEntry__
#define __ADMEntry__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMTracker__
#include "ADMTracker.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// Mac OS headers #define GetItem, but we want to use it as a name.
#ifdef GetItem
#undef GetItem
#endif


// -----------------------------------------------------------------------------
//	User provided procedures.

/** Prototype for a timer procedure associated with an entry.
	Your function performs the scheduled action after the timer's delay
	period is up.
		@param inEntry The entry object.
		@param inTimer The timer object.
		@return True to repeat the timed operation, false to terminate.
		@see \c #ADMEntrySuite6::CreateTimer()
	*/
typedef ADMBoolean ADMAPI (*ADMEntryTimerProc)(ADMEntryRef inEntry, ADMTimerRef inTimer);

/** Prototype for a timer cancellation procedure associated with an entry.
	Your function should clean up data associated with the scheduled action.
		@param inEntry The entry object.
		@param inTimerID The timer object.
		@param inAbortAction The action that triggered the cancellation.
		@return Nothing.
		@see \c #ADMEntrySuite6::CreateTimer()
	*/
typedef void ADMAPI (*ADMEntryTimerAbortProc)(ADMEntryRef inEntry, ADMTimerRef inTimer,
			ADMAction inAbortAction);


// -----------------------------------------------------------------------------
//	Standard checkmark glyphs

/** Predefined glyphs that can be drawn next to the text or image
	of a list entry. See \c #ADMEntrySuite6. */
typedef enum
{
	/** Checkmark */
	kADMCheckmarkGlyphID = 0,
	/** Bullet */
	kADMBulletGlyphID = 1,
	/** Hyphen */
	kADMHyphenGlyphID = 2,
	/** Internal */
	kADMDummyGlyphID = 0xFFFFFFFF
}
ADMStandardCheckGlyphID;


// =============================================================================
//		* ADM Entry Suite
// =============================================================================

/** Entry suite name */
#define kADMEntrySuite "ADM Entry Suite"
/** Entry suite version */
#define kADMEntrySuiteVersion6 6

// -----------------------------------------------------------------------------

/** @ingroup Suites
	Lists are associated with dialog items of types that provides
	a list of choices, including list boxes, popup lists, popup menus,
	spin-edit popups, and text-edit popups. A list object, \c #ADMListRef, contains
	\e entries, \c #ADMEntryRef. The individual entry objects contain the entry
	appearance and state information.

	You create entries by adding them to a list, using either
	\c #ADMListSuite4::InsertEntry() or \c #Create().

	This suite allows you to access and manipulate individual entries.

	Individual entries have default behavior, such as responding to a click by
	becoming selected or deselected. You can provide a set of entry callback
	procedures for the containing list, like those associated with a dialog
	or item, which affect the appearance and behavior of the contained entries.
	A list callback can modify the default behavior of an entry, which you
	access through the entry object using functions in this suite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMEntrySuite and \c #kADMEntrySuiteVersion6.
	*/
typedef struct ADMEntrySuite6
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// entry creation/destruction

	/** Creates a new entry object and inserts it at the head of a list,
		calling the list's entry initialization procedure if one
		has been specified.	The new entry's ID is 0 until you set it with \c #SetID().
			@param inList The list object.
			@return The new entry object.
			@see \c #ADMListSuite4::SetInitProc(), \c #ADMListSuite4::InsertEntry()
		*/
	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);

	/** Destroys an entry object, first calling the containing list's entry
		termination procedure if one has been specified.
			@param inEntry The entry object.
			@return Nothing
			@see \c #ADMListSuite4::SetDestroyProc()
		*/
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);

	// default behaviors

	/** Calls the default drawing procedure for an entry from within a
		developer-defined custom entry drawing procedure for the
		containing list. Typically used to draw the basic appearance
		before modifying it.
			@param inEntry The entry object.
			@param inDrawer The drawing object.
			@return Nothing.
			@see \c #ADMListSuite4::SetDrawProc()
		*/
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);


	/** Calls the default event tracking procedure for an entry from within a
		developer-defined custom entry drawing procedure for the
		containing list. The default tracker handles entry selection, including
		multiple selection.
			@param inEntry The entry object.
			@param inTracker The tracking object.
			@return True if action was taken such that the entry's notifier
				function should be called.
			@see \c #ADMListSuite4::SetTrackProc()
		*/
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);

	/** Calls the default notification-handling procedure for an entry from within a
		developer-defined custom entry notification procedure for the
		containing list. Use to get standard behavior for notifiers.
			@param inEntry The entry object.
			@param inNotifier The notification object.
			@return Nothing.
			@see \c #ADMListSuite4::SetNotifyProc()
		*/
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);

	/** Sends a notification to an entry.
			@param inEntry The entry object.
			@param inNotifierType The notification type constant,
				typically \c #kADMIntermediateChangedNotifier or
				\c #kADMUserChangedNotifier. See \c ADMNotifier.h.
			@return Nothing.
		*/
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);

	// container accessors

	/** Retrieves the index position of an entry in its containing list.
			@param inEntry The entry object.
			@return The 0-based position index.
		*/
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);

	/** Retrieves the list that contains an entry.
			@param inEntry The entry object.
			@return The list object.
		*/
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);

	// entry ID

	/** Sets an identifier for an entry. When an entry is created, its ID is 0.
			@param inEntry The entry object.
			@param inEntryID The identifying number.
			@return Nothing.
		*/
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);

	/** Retrieves the identifier for an entry. When an entry is created, its ID is 0.
			@param inEntry The entry object.
			@return  The identifying number.
		*/
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);

	// entry user data storage

	/** Associates an entry with developer-defined data.
			@param inEntry The entry object.
			@param inUserData The data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);

	/** Retrieves developer-defined data associated with an entry.
			@param inEntry The entry object.
			@return  The data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	/** Selects or deselects an entry programmatically. If the
		containing list does not allow multiple selection, selecting
		an entry automatically deselects all other entries.
			@param inEntry The entry object.
			@param inSelect True to select the entry, false to deselect it.
			@return Nothing.
			@see \c #Activate()	(Active is the same as selected.)
		*/
	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);

	/** Reports whether an entry is selected.
			@param inEntry The entry object.
			@return True if the entry is selected, false otherwise.
			@see \c #IsActive() (Active is the same as selected.)
		*/
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);

	// entry visibility

	/** Forces an entry to be visible within the bounds of its containing
		list, scrolling the list if necessary.
			@param inEntry The entry object.
			@return Nothing.
		*/
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	/** Reports whether an entry is fully or partially visible within
		the bounds of its containing list.
			@param inEntry The entry object.
			@return True if the entry is visible, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	/** Enables or disables an entry. A disabled entry cannot be selected.
			@param inEntry The entry object.
			@param inEnable True to enable the entry, false to disable it.
			@return Nothing.
		*/
	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);

	/** Reports whether an entry is enabled.
			@param inEntry The entry object.
			@return True if the entry is enabled, false if it is disabled.
		*/
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);

	/** Selects or deselects an entry.
			@param inEntry The entry object.
			@param inActivate True to select the entry, false to deselect it.
			@return Nothing.
			@see \c #Select() (Active is the same as selected.)
		*/
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);

	/** Reports whether an entry is selected.
			@param inEntry The entry object.
			@return True if the entry is selected, false otherwise.
			@see \c #IsSelected() (Active is the same as selected.)
		*/
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);

	/** Turns the checkmark for an entry on or off.	By default, only
		members of menu lists are drawn with checkmarks. You can set
		the state for other list entries for use with a custom drawing
		procedure.
			@param inEntry The entry object.
			@param inCheck True to turn the checkmark on, false to turn it off.
			@return Nothing.
		*/
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);

	/** Reports whether the checkmark for an entry is on or off.
			@param inEntry The entry object.
			@return True if the checkmark is on, false if it is off.
			@see \c #Check()
		*/
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);

	/** Turns the separator state for an item on or off. By default, only
		members of menu lists make use of this state. In these lists, a
		separator entry is drawn as a horizontal line that
		divides the list into sections, and the entry cannot be selected.
		You can set the state for other list entries for use with a custom
		drawing, tracking, or notification procedure.
			@param inEntry The entry object.
			@param inSeparator True to turn the separator state on, false to turn it off.
			@return Nothing.
		*/
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);

	/** Reports whether the separator state for an entry is on or off.
			@param inEntry The entry object.
			@return True if the separator state is on, false if it is off.
			@see \c #MakeSeparator()
		*/
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	/** Retrieves the size of an entry, relative to its own origin.
			@param inEntry The entry object.
			@param outLocalRect [out] A buffer in which to return the bounding box,
				where the \c top and \c left values are 0,
				and the \c bottom and \c right members indicate the size.
			@return Nothing
		*/
	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);

	/** Retrieves the size and position of an entry within the containing dialog.
			@param inEntry The entry object.
			@param outBoundsRect [out] A buffer in which to return the bounding box,
				in local dialog coordinates.
			@return Nothing
		*/
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);

	// coordinate transformations

	/** Transforms a point from local coordinates for an entry to screen coordinates.
			@param inEntry The entry object.
			@param ioPoint [in, out] A buffer in which to pass the point in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);

	/** Transforms a point from screen coordinates to local coordinates for an entry.
			@param inEntry The entry object.
			@param ioPoint [in, out] A buffer in which to pass the point in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);

	/** Transforms a rectangle from local coordinates for an entry to screen coordinates.
			@param inEntry The entry object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);

	/** Transforms a rectangle from screen coordinates to local coordinates for an entry.
			@param inEntry The entry object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);

	// redraw requests

	/** Marks an entry as being in need of redrawing.
			@param inEntry The entry object.
			@return Nothing
			@see \c #Update()
		*/
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);

	/** Marks an area within an entry as being in need of redrawing.
			@param inEntry The entry object.
			@param inInvalRect The rectangle, in local coordinates relative to the entry.
			@return Nothing
		*/
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);

	/** Redraws an entry that has been invalidated, or any invalid areas within it.
			@param inEntry The entry object.
			@return Nothing
			@see \c #Invalidate(), \c #InvalidateRect()
		*/
	void ADMAPI (*Update)(ADMEntryRef inEntry);

	// entry picture accessors

	/** Sets the picture resource used to draw an entry. Resources can be
		identified by either numeric ID or name.
			@param inEntry The entry object.
			@param inPictureResID The picture resource identifier, developer-defined
				or one of the predefined picture constants, \c kADM*PictureID.
				See @ref AdmResources.
			@param inPictureResName The picture resource name.
			@return Nothing
		*/
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture resource for an entry.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the
				picture resource identifier, or 0 if no ID has been assigned.
				The ID is developer-defined or one of the
				predefined picture constants, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the
				picture	resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetPictureID(). \c #SetPicture()
		*/
	void ADMAPI (*GetPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture resource used to draw an entry when it is selected.
		Resources can be identified by numeric ID or name.
			@param inEntry The entry object.
			@param inPictureResID The picture resource identifier, developer-defined
				or one of the predefined picture constants, \c kADM*PictureID.
				See @ref AdmResources.
			@param inPictureResName The picture resource name.
			@return Nothing
		*/
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture resource used for an entry when it is selected.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the
				picture resource identifier, or 0 if no ID has been assigned.
				The ID is developer-defined or one of the
				predefined picture constants, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the
				picture	resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetSelectedPictureID()
		*/
	void ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture resource used to draw an entry when it is disabled.
		Resources can be identified by numeric ID or name.
			@param inEntry The entry object.
			@param inPictureResID The picture resource identifier, developer-defined
				or one of the predefined picture constants, \c kADM*PictureID.
				See @ref AdmResources.
			@param inPictureResName The picture resource name.
			@return Nothing
		*/
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture resource used for an entry when it is disabled.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the
				picture resource identifier, or 0 if no ID has been assigned.
				The ID is developer-defined or one of the
				predefined picture constants, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the
				picture	resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetDisabledPictureID()
		*/
	void ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture used to draw an entry.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
			@see \c #SetPictureID()
		*/
	void ADMAPI (*SetPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture for an entry.
			@param inEntry The entry object.
			@return The icon object for the picture,
				or \c NULL if the entry has no picture.
			@see \c #SetPicture()
		*/
	ADMIconRef ADMAPI (*GetPicture)(ADMEntryRef inEntry);

	/** Sets the picture used to draw an entry when it is selected.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
		*/
	void ADMAPI (*SetSelectedPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture used for an entry when it is selected.
			@param inEntry The entry object.
			@return The icon object for the picture.
			@see \c #SetSelectedPicture()
		*/
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMEntryRef inEntry);

	/** Sets the picture used to draw an entry when it is disabled.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
		*/
	void ADMAPI (*SetDisabledPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture used for an entry when it is disabled.
			@param inEntry The entry object.
			@return The icon object for the picture.
			@see \c #SetDisabledPicture()
		*/
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMEntryRef inEntry);

	// entry text accessors

	/**  Sets the text to be displayed in an entry, using a C string.
			@param inEntry The entry object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);

	/**  Sets the text to be displayed in an entry, using a Unicode string.
			@param inEntry The entry object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetTextW)(ADMEntryRef inEntry, const ADMUnicode* inText);

	/**  Retrieves the text from an entry as a C string.
			@param inEntry The entry object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLength() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);

	/**  Retrieves the text from an entry as a Unicode string.
			@param inEntry The entry object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLengthW() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetTextW)(ADMEntryRef inEntry, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** Reports the length of an entry's text as a C string. Use to allocate
		a buffer for \c #GetText().
			@param inEntry The entry object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);

	/** Reports the length of an entry's text as a Unicode string. Use to allocate
		a buffer for \c #GetTextW().
			@param inEntry The entry object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMEntryRef inEntry);

	// entry timer accessors

	/** Creates an entry timer, which allows you to schedule an action
		for the entry. The action can make use of developer-defined
		data associated with the entry; see \c #GetUserData().
			@param inEntry The entry object.
			@param inMilliseconds The delay, in milliseconds, from when this
				call is executed until the action is called.
			@param inAbortMask Events that cancel the scheduled action, if
				they occur before the timer expires. See \c #AbortTimer().
				A logical OR of \c #ADMAction constants.
			@param inTimeProc The procedure that implements the scheduled action.
			@param inAbortProc The procedure to call if the timer is canceled.
			@param inOptions Not used; pass 0.
			@return The timer object.
		*/
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	/** Cancels a scheduled action associated with an entry. It is used if an event
		specified by the \c inAbortMask of \c #CreateTimer() occurs, or if
		you destroy the entry before the timer expires.
			@param inEntry The entry object.
			@param inTimerID The timer object containing the scheduled action.
			@return Nothing. */
	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	/** @deprecated Do not use. */
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMEntryRef inEntry);

	/** @deprecated Do not use. */
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMEntryRef inEntry, ADMInt32 inHelpID);

	/** @deprecated Do not use. */
	void ADMAPI (*Help_DEPRECATED)(ADMEntryRef inEntry);

	// entry checkmark accessors

	/** Sets the type of glyph used to indicate the checked state for an entry.
			@param inEntry The entry object.
			@param inCheckGlyph The check glyph constant.
			@return Nothing.
		*/
	void ADMAPI (*SetCheckGlyph)(ADMEntryRef inEntry, ADMStandardCheckGlyphID inCheckGlyph);

	/** Retrieves the type of glyph used to indicate the checked state for an entry.
			@param inEntry The entry object.
			@return The check glyph constant.
		*/
	ADMStandardCheckGlyphID ADMAPI (*GetCheckGlyph)(ADMEntryRef inEntry);

	// [cpaduan] 8/23/02 - set/get entry script
	/** Sets the script for an entry.
			@param inEntry The entry object.
			@param inScript The script.
			@return Nothing.
		*/
	void ADMAPI (*SetScript)(ADMEntryRef inEntry, ADMInt16 inScript);

	/** Retrieves the script for an entry.
			@param inEntry The entry object.
			@return The script.
		*/
	ADMInt16 ADMAPI (*GetScript)(ADMEntryRef inEntry);

}
ADMEntrySuite6;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMEntryOld__
#ifdef MAC_ENV
#include "ADMEntryOld.h"
#else
#include ".\Legacy\ADMEntryOld.h"
#endif
#endif


// -----------------------------------------------------------------------------

#endif	// __ADMEntry__
