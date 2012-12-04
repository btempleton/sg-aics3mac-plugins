/*******************************************************************************
*
* ADMListEntry.h -- ADM List Entry Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1997-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Wei Huang, 17 Oct 1997
*
********************************************************************************/

/** @file ADMListEntry.h ADM List Entry Suite */

#ifndef __ADMListEntry__
#define __ADMListEntry__

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

/** Prototype for a timer procedure associated with a list entry.
	Your function performs the scheduled action after the timer's delay
	period is up.
		@param inItem The item object.
		@param inTimer The timer object.
		@return True to repeat the timed operation, false to terminate.
		@see \c #ADMListEntrySuite4::CreateTimer()
	*/
typedef ADMBoolean ADMAPI (*ADMListEntryTimerProc)(ADMListEntryRef inEntry,
			ADMTimerRef inTimer);


/** Prototype for a timer cancellation procedure associated with a list entry.
	Your function should clean up data associated with the scheduled action.
		@param inItem The item object.
		@param inTimerID The timer object.
		@param inAbortAction The action that triggered the cancellation.
		@return Nothing.
	*/
typedef void ADMAPI (*ADMListEntryTimerAbortProc)(ADMListEntryRef inEntry,
			ADMTimerRef inTimer, ADMAction abortAction);


// =============================================================================
//		* ADM List Entry Suite
// =============================================================================

/** Suite name constant */
#define kADMListEntrySuite "ADM List Entry Suite"
/** Suite version constant */
#define kADMListEntrySuiteVersion4 4

// -----------------------------------------------------------------------------

/** @ingroup Suites
	Hierarchy list objects are, like list objects, are associated with
	dialog items of types that provide a list of choices, including
	list boxes, popup lists, popup menus, spin-edit popups, and text-edit popups.
	Hierarchy lists contain a tree structure of entries, whose branches can
	be opened and closed.

	A hierarchy list object, \c #ADMHierarchyListRef, contains entries represented
	by \c #ADMListEntryRef. These are like ordinary list entry objects (\c #ADMEntryRef),
	and contain the entry appearance and state information.
	These, however, can in turn contain child lists with nested entries, and information
	about their position in the parent-child hierarchy of the entry tree structure.
	See \c #ADMListEntrySuite4.

	This suite allows you to create and manipulate individual entries that make
	up a hierarchical list, and manage their child lists.

	Individual entries have default behavior, such as responding to a click by
	becoming selected or deselected, or by opening the child list. You can
	provide a set of entry callback procedures for the containing list, like
	those associated with a dialog or item, which affect the appearance and
	behavior of the contained entries.
	A list callback can modify the default behavior of an entry, which you
	access through the entry object using functions in this suite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMListEntrySuite and \c #kADMListEntrySuiteVersion4.
	*/
typedef struct ADMListEntrySuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// entry creation/destruction

	/** Creates a new entry object and inserts it at the head of a list.
		calling the list's entry initialization procedure if one
		has been specified.	The new entry's ID is 0 until you set it with \c #SetID().
			@param inList The list object.
			@return The new entry object.
			@see \c #ADMHierarchyListSuite5::SetInitProc(),	\c #ADMHierarchyListSuite5::SetInitProcRecursive(),
				\c #ADMHierarchyListSuite5::InsertEntry()
		*/
	ADMListEntryRef ADMAPI (*Create)(ADMHierarchyListRef inList);

	/** Destroys an entry object, first calling the containing list's entry
		termination procedure if one has been specified.
			@param inEntry The entry object.
			@return Nothing
			@see \c #ADMHierarchyListSuite5::SetDestroyProc(), \c #ADMHierarchyListSuite5::SetDestroyProcRecursive()
		*/
	void ADMAPI (*Destroy)(ADMListEntryRef inEntry);

	// entry sequence

	/** Retrieves the index position of an entry in its containing list.
			@param inEntry The entry object.
			@return The 0-based position index.
		*/
	ADMInt32 ADMAPI (*GetIndex)(ADMListEntryRef inEntry);

	// container accessors

	/** Retrieves the dialog item to which an entry belongs.
			@param inEntry The entry object.
			@return The item object.
		*/
	ADMItemRef ADMAPI (*GetItem)(ADMListEntryRef inEntry);

	/** Retrieves the list that contains an entry.
			@param inEntry The entry object.
			@return The list object.
		*/
	ADMHierarchyListRef ADMAPI (*GetList)(ADMListEntryRef inEntry);

	// hierarchy accessors

	/** Retrieves the child list from an entry.
			@param inEntry The entry object.
			@return The list object.
		*/
	ADMHierarchyListRef ADMAPI (*GetChildList)(ADMListEntryRef inEntry);

	/** Creates a child list for an entry. Use \c #ADMHierarchyListSuite5 to
		add entries to the child list.
			@param inEntry The entry object.
			@return The new list object.
		*/
	ADMHierarchyListRef ADMAPI (*CreateChildList)(ADMListEntryRef inEntry);
	/** Deletes the child list of an entry, destroying the list
		and all of its child entries.
			@param inEntry The entry object.
			@return Nothing.
		*/
	void ADMAPI (*DeleteChildList)(ADMListEntryRef inEntry);

	/** Expands or closes an entry. When an entry is expanded,
		its child list, if any, is visible.
			@param inEntry The entry object.
			@param inExpand	True to expand the entry, false to close it.
			@return Nothing.
		*/
	void ADMAPI (*ExpandHierarchy)(ADMListEntryRef inEntry, ADMBoolean inExpand);

	/** Reports whether an entry is expanded. When an entry is expanded,
		its child list, if any, is visible.
			@param inEntry The entry object.
			@return True if the entry is expanded, false if it is closed.
		*/
	ADMBoolean ADMAPI (*IsHierarchyExpanded)(ADMListEntryRef inEntry);

	/** Hides or shows an entry. When an entry is hidden, the child list entries
		are shown at the parent entry's level. Use this to group choices
		without the open/close behavior of a nested list.
			@param inEntry The entry object.
			@param inHideName True to hide the parent entry, false to show it.
			@return Nothing.
		*/
	void ADMAPI (*HideEntryName)(ADMListEntryRef inEntry, ADMBoolean inHideName);

	/** Reports whether an entry is hidden or shown.  When an entry is hidden,
		the child list entries are shown at the parent entry's level.
			@param inEntry The entry object.
			@return True if the parent entry is hidden, false if it is shown.
			@see \c #HideEntryName()
		*/
	ADMBoolean ADMAPI (*IsEntryNameHidden)(ADMListEntryRef inEntry);

	/** Enable or disable the selection of children for an entry.
			@param inEntry The entry object.
			@param inHideName True to enable child selection, false to disable it.
			@return Nothing.
		*/
	void ADMAPI (*EnableChildSelection)(ADMListEntryRef inEntry, ADMBoolean inEnable);

	/** Reports whether the children of an entry can be selected.
			@param inEntry The entry object.
			@return True if child selection is enabled, false if it is disabled.
		*/
	ADMBoolean ADMAPI (*IsChildSelectable)(ADMListEntryRef inEntry);

	/** Reports the nesting level of an entry. Root-level entries have a depth of 0.
			@param inEntry The entry object.
			@return The 0-based nesting depth.
		*/
	ADMInt32 ADMAPI (*GetHierarchyDepth)(ADMListEntryRef inEntry);
	/** Reports the nesting level of an entry, not counting parent
		entries whose names are hidden. See \c #HideEntryName().
			@param inEntry The entry object.
			@return The 0-based nesting depth.
		 */
	ADMInt32 ADMAPI (*GetVisualHierarchyDepth)(ADMListEntryRef inEntry);

	// entry ID

	/** Sets an identifier for an entry. When an entry is created, its ID is 0.
			@param inEntry The entry object.
			@param inEntryID The identifying number.
			@return Nothing.
		*/
	void ADMAPI (*SetID)(ADMListEntryRef inEntry, ADMInt32 inEntryID);

	/** Retrieves the identifier for an entry. When an entry is created, its ID is 0.
			@param inEntry The entry object.
			@return  The identifying number.
		*/
	ADMInt32 ADMAPI (*GetID)(ADMListEntryRef inEntry);

	// entry user storage

	/** Associates an entry with developer-defined data.
			@param inEntry The entry object.
			@param inUserData The data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMListEntryRef inEntry, ADMUserData inUserData);

	/** Retrieves developer-defined data associated with an entry.
			@param inEntry The entry object.
			@return  The data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMListEntryRef inEntry);

	// default behaviors

	/** Calls the default drawing procedure for an entry from within a
		developer-defined custom entry drawing procedure for the
		containing list. Typically used to draw the basic appearance
		before modifying it.
			@param inEntry The entry object.
			@param inDrawer The drawing object.
			@return Nothing.
			@see \c #ADMHierarchyListSuite5::SetDrawProc()
		*/
	void ADMAPI (*DefaultDraw)(ADMListEntryRef inEntry, ADMDrawerRef inDrawer);

	/** Calls the default event tracking procedure for an entry from within a
		developer-defined custom entry drawing procedure for the
		containing list. The default tracker handles entry selection, including
		multiple selection.
			@param inEntry The entry object.
			@param inTracker The tracking object.
			@return True if action was taken such that the entry's notifier function
				should be called.
			@see \c #ADMHierarchyListSuite5::SetTrackProc()
		*/
	ADMBoolean ADMAPI (*DefaultTrack)(ADMListEntryRef inEntry, ADMTrackerRef inTracker);

	/** Calls the default notification-handling procedure for an entry from within a
		developer-defined custom entry notification procedure for the
		containing list. Use to get standard behavior for notifiers.
			@param inEntry The entry object.
			@param inNotifier The notification object.
			@return Nothing.
			@see \c #ADMHierarchyListSuite5::SetNotifyProc()
		*/
	void ADMAPI (*DefaultNotify)(ADMListEntryRef inEntry, ADMNotifierRef inNotifier);

	/** Sends a notification to an entry.
			@param inEntry The entry object.
			@param inNotifierType The notification type constant,
				typically \c #kADMIntermediateChangedNotifier or
				\c #kADMUserChangedNotifier. See \c ADMNotifier.h.
			@return Nothing.
		*/
	void ADMAPI (*SendNotify)(ADMListEntryRef inEntry, const char* inNotifierType);

	// selection

	/** Selects or deselects an entry programmatically. If the
		containing list does not allow multiple selection, selecting
		an entry automatically deselects all other entries.
			@param inEntry The entry object.
			@param inSelect True to select the entry, false to deselect it.
			@return Nothing.
			@see \c #Activate()	(Active is the same as selected.)
			*/
	void ADMAPI (*Select)(ADMListEntryRef inEntry, ADMBoolean inSelect);

	/** Reports whether an entry is selected.
			@param inEntry The entry object.
			@return True if the entry is selected, false otherwise.
			@see \c #IsActive() (Active is the same as selected.)
				<br>\c #AreChildrenSelected()
		*/
	ADMBoolean ADMAPI (*IsSelected)(ADMListEntryRef inEntry);

	/** Reports whether any of the children of an entry is selected.
			@param inEntry The entry object.
			@return True if one or more children of the entry is selected, false otherwise.
		*/
	ADMBoolean ADMAPI (*AreChildrenSelected)(ADMListEntryRef inEntry);

	// display settings

	/** Enables or disables an entry. A disabled entry cannot be selected.
			@param inEntry The entry object.
			@param inEnable True to enable the entry, false to disable it.
			@return Nothing.
	*/
	void ADMAPI (*Enable)(ADMListEntryRef inEntry, ADMBoolean inEnable);

	/** Reports whether an entry is enabled.
			@param inEntry The entry object.
			@return True if the entry is enabled, false if it is disabled.
		*/
	ADMBoolean ADMAPI (*IsEnabled)(ADMListEntryRef inEntry);

	/** Selects or deselects an entry.
			@param inEntry The entry object.
			@param inActivate True to select the entry, false to deselect it.
			@return Nothing.
			@see \c #Select() (Active is the same as selected.)
		*/
	void ADMAPI (*Activate)(ADMListEntryRef inEntry, ADMBoolean inActivate);

	/** Reports whether an entry is selected.
			@param inEntry The entry object.
			@return True if the entry is selected, false otherwise.
			@see \c #IsSelected() (Active is the same as selected.)
		*/
	ADMBoolean ADMAPI (*IsActive)(ADMListEntryRef inEntry);

	/** Turns the checkmark for an entry on or off.	By default, only
		members of menu lists are drawn with checkmarks. You can set
		the state for other list entries for use with a custom drawing
		procedure.
			@param inEntry The entry object.
			@param inCheck True to turn the checkmark on, false to turn it off.
			@return Nothing.
		*/
	void ADMAPI (*Check)(ADMListEntryRef inEntry, ADMBoolean inCheck);

	/** Reports whether the checkmark for an entry is on or off.
			@param inEntry The entry object.
			@return True if the checkmark is on, false if it is off.
			@see \c #Check()
		*/
	ADMBoolean ADMAPI (*IsChecked)(ADMListEntryRef inEntry);

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
	void ADMAPI (*MakeSeparator)(ADMListEntryRef inEntry, ADMBoolean inSeparator);

	/** Reports whether the separator state for an entry is on or off.
			@param inEntry The entry object.
			@return True if the separator state is on, false if it is off.
			@see \c #MakeSeparator()
		*/
	ADMBoolean ADMAPI (*IsSeparator)(ADMListEntryRef inEntry);

	// bounds accessors

	/** Retrieves the size of an entry, relative to its own origin.
			@param inEntry The entry object.
			@param outLocalRect [out] A buffer in which to return the bounding box,
				where the \c top and \c left values are 0,
				and the \c bottom and \c right members indicate the size.
			@return Nothing
		*/
	void ADMAPI (*GetLocalRect)(ADMListEntryRef inEntry, ADMRect* outLocalRect);

	/** Retrieves the position and size of the expand/collapse arrow of an entry.
			@param inEntry The entry object.
			@param outLocalRect [out] A buffer in which to return the bounding box,
				relative to the bounding box of the entry.
			@return Nothing
			@see \c #GetLocalRect()
		*/
	void ADMAPI (*GetExpandArrowLocalRect)(ADMListEntryRef inEntry, ADMRect* outLocalRect);

	/** Retrieves the size and position of an entry within the containing dialog.
			@param inEntry The entry object.
			@param outBoundsRect [out] A buffer in which to return the bounding box,
				in local dialog coordinates.
			@return Nothing
		*/
	void ADMAPI (*GetBoundsRect)(ADMListEntryRef inEntry, ADMRect* outBoundsRect);

	// coordinate transformations

	/** Transforms a point from local coordinates for an entry to screen coordinates.
			@param inEntry The entry object.
			@param ioPoint [in, out] A buffer in which to pass the point in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenPoint)(ADMListEntryRef inEntry, ADMPoint* ioPoint);

	/** Transforms a point from screen coordinates to local coordinates for an entry.
			@param inEntry The entry object.
			@param ioPoint [in, out] A buffer in which to pass the point in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalPoint)(ADMListEntryRef inEntry, ADMPoint* ioPoint);

	/** Transforms a rectangle from local coordinates for an entry to screen coordinates.
			@param inEntry The entry object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenRect)(ADMListEntryRef inEntry, ADMRect* inRect);

	/** Transforms a rectangle from screen coordinates to local coordinates foran entry.
			@param inEntry The entry object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalRect)(ADMListEntryRef inEntry, ADMRect* inRect);

	// redrawing

	/** Marks an entry as being in need of redrawing.
			@param inEntry The entry object.
			@return Nothing
			@see \c #Update()
		*/
	void ADMAPI (*Invalidate)(ADMListEntryRef inEntry);

	/** Redraws an entry that has been invalidated, or any invalid areas within it.
			@param inEntry The entry object.
			@return Nothing
			@see \c #Invalidate()
		*/
	void ADMAPI (*Update)(ADMListEntryRef inEntry);

	// entry pictures

	/** Sets the picture resource used to draw an entry. 
		Resources can be identified by numeric ID or name.
			@param inEntry The entry object.
			@param inPictureResID The picture resource identifier, developer-defined
				or one of the predefined picture constants, \c kADM*PictureID.
				See @ref AdmResources.
			@param inPictureResName The picture resource name.
			@return Nothing
		*/
	void ADMAPI (*SetPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
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
	void ADMAPI (*GetPictureID)(ADMListEntryRef inEntry, ADMInt32* inPictureResID,
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
	void ADMAPI (*SetSelectedPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
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
	void ADMAPI (*GetSelectedPictureID)(ADMListEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture resource used to draw an entry when it is disabled.
		Resources can be identified by numeric ID or name.
		@see \c #SetPictureID() for more about entries and picture resources.

			@param inEntry The entry object.
			@param inPictureResID The picture resource identifier, developer-defined
				or one of the predefined picture constants, \c kADM*PictureID.
				See @ref AdmResources.
			@param inPictureResName The picture resource name.
			@return Nothing
		*/
	void ADMAPI (*SetDisabledPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
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
	void ADMAPI (*GetDisabledPictureID)(ADMListEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// entry text

	/**  Sets the text to be displayed in an entry, using a C string.
			@param inEntry The entry object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetText)(ADMListEntryRef inEntry, const char* inText);

	/**  Sets the text to be displayed in an entry, using a Unicode string.
			@param inEntry The entry object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetTextW)(ADMListEntryRef inEntry, const ADMUnicode* inText);

	/**  Retrieves the text from an entry as a C string.
			@param inEntry The entry object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLength() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetText)(ADMListEntryRef inEntry, char* outText, ADMInt32 inMaxLength);

	/**  Retrieves the text from an entry as a Unicode string.
			@param inEntry The entry object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLengthW() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetTextW)(ADMListEntryRef inEntry, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** Reports the length of an entry's text as a C string. Use to allocate
		a buffer for \c #GetText().
			@param inEntry The entry object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLength)(ADMListEntryRef inEntry);

	/** Reports the length of an entry's text as a Unicode string. Use to allocate
		a buffer for \c #GetTextW().
			@param inEntry The entry object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMListEntryRef inEntry);

	// entry timer

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
	ADMTimerRef ADMAPI (*CreateTimer)(ADMListEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMListEntryTimerProc inTimerProc,
				ADMListEntryTimerAbortProc inAbortProc, ADMInt32 inOptions);

	/** Cancels a scheduled action associated with an entry. It is used if an event
		specified by the \c inAbortMask of \c #CreateTimer() occurs, or if
		you destroy the entry before the timer expires.
			@param inEntry The entry object.
			@param inTimerID The timer object containing the scheduled action.
			@return Nothing. */
	void ADMAPI (*AbortTimer)(ADMListEntryRef inEntry, ADMTimerRef inTimer);

	// entry visibility

	/** Forces an entry to be visible within the bounds of its containing
		list, scrolling the list if necessary.
			@param inEntry The entry object.
			@return Nothing.
		*/
	void ADMAPI (*MakeInBounds)(ADMListEntryRef inEntry);
	/** Reports whether an entry is fully or partially visible
		within the bounds of its containing list.
			@param inEntry The entry object.
			@return True if the entry is visible, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsInBounds)(ADMListEntryRef inEntry);

	// entry help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	/** @deprecated Do not use. */
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMListEntryRef inEntry);
	/** @deprecated Do not use. */
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMListEntryRef inEntry, ADMInt32 inHelpID);
	/** @deprecated Do not use. */
	void ADMAPI (*Help_DEPRECATED)(ADMListEntryRef inEntry);

	// entry pictures

	/** Sets the picture used to draw an entry.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
			@see \c #SetPictureID()
		*/
	void ADMAPI (*SetPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture for an entry.
			@param inEntry The entry object.
			@return The icon object for the picture,
				or \c NULL if the entry has no picture.
			@see \c #SetPicture()
		*/
	ADMIconRef ADMAPI (*GetPicture)(ADMListEntryRef inEntry);

	/** Sets the picture used to draw an entry when it is selected.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
		*/
	void ADMAPI (*SetSelectedPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture used for an entry when it is selected.
			@param inEntry The entry object.
			@return The icon object for the picture.
			@see \c #SetSelectedPicture()
		*/
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMListEntryRef inEntry);

	/** Sets the picture used to draw an entry when it is disabled.
			@param inEntry The entry object.
			@param inPicture The icon object for the picture.
			@return Nothing
		*/
	void ADMAPI (*SetDisabledPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);

	/** Retrieves the picture used for an entry when it is disabled.
			@param inEntry The entry object.
			@return The icon object for the picture.
			@see \c #SetDisabledPicture()
		*/
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMListEntryRef inEntry);

	/** Sets the rectangle in which entry text is drawn.
			@param inEntry The entry object.
			@param inRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle.
				See \c #GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*SetEntryTextRect)(ADMListEntryRef inEntry, ADMRect* inRect);

	// for controls in lists

	/** @deprecated Do not use.	*/
	ADMItemRef ADMAPI (*GetEntryItem)(ADMListEntryRef inEntry);
	/** @deprecated Do not use.	 */
	void ADMAPI (*SetEntryItem)(ADMListEntryRef inEntry, ADMItemRef inItem);

	// customizing appearance

	/** Sets the font style for text in an entry that displays text.
			@param inEntry The entry object.
			@param inFont The font style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetFont)(ADMListEntryRef inEntry, ADMFont inFont);

	/** Sets the color style for text in an entry that displays text.
			@param inEntry The entry object.
			@param inColor The color style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetTextColor)(ADMListEntryRef inEntry, ADMColor inColor);

	/** Sets the background color for an entry.
			@param inEntry The entry object.
			@param inColor The color style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetBackgroundColor)(ADMListEntryRef inEntry, ADMColor inColor);

	/** Sets the line color for an entry that is a separator.
			@param inEntry The entry object.
			@param inColor The color style constant.
			@return Nothing.
			@see \c #MakeSeparator()
		*/
	void ADMAPI (*SetDividingLineColor)(ADMListEntryRef inEntry, ADMColor inColor);

}
ADMListEntrySuite4;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMListEntryOld__
#ifdef MAC_ENV
#include "ADMListEntryOld.h"
#else
#include ".\Legacy\ADMListEntryOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMListEntry__
