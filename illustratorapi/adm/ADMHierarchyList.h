/*******************************************************************************
*
* ADMHierarchyList.h -- ADM Hierarchy List Suite
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

/** @file ADMHierarchyList.h ADM Hierarchy List Suite */

#ifndef __ADMHierarchyList__
#define __ADMHierarchyList__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// Mac OS headers #define GetItem, but we want to use it as a name.
#ifdef GetItem
#undef GetItem
#endif


// -----------------------------------------------------------------------------
//	Hierarchy list flags

/** Hierarchy list bit flag. When set, enables selection across levels. */
#define kMultiSelectAcrossHierarchyLevels 0x00000001
/** Hierarchy list bit flag. When set, draws a black line at the bottom of the list. */
#define kHierarchyListEndedWithFrame 0x00000002
/** Hierarchy list bit flag. When set, draws a gray background. */
#define kHierarchyListTopLevelSpecialBackground 0x00000004
/** Hierarchy list bit flag. When set, root-level entries cannot have sublists.
	The organizational features of hierarchy lists can still be useful. */
#define kHierarchyListLeafOnly 0x00000008


// -----------------------------------------------------------------------------
//	User defined procedures

/** Prototype for an entry initialization procedure associated with a list.
	It is called when an entry is added to the list with
	\c #ADMHierarchyListSuite5::InsertEntry(). The procedure can, for example,
	allocate memory or resources, or initialize variables.
		@param inEntry The entry object.
		@return An ADM error code.
		@see \c #ADMHierarchyListSuite5::SetInitProc()
	*/
typedef ADMErr ADMAPI (*ADMListEntryInitProc)(ADMListEntryRef inEntry);

/** Prototype for an entry drawing procedure associated with a list.
	Your function can completely draw a custom entry, or call the default
	drawer to draw the basic appearance, then modify it.
		@param inEntry The entry object.
		@param inDrawer The drawing object.
		@return Nothing.
		@see \c #ADMHierarchyListSuite5::SetDrawProc(), \c #ADMListEntrySuite4::DefaultDraw()
	*/
typedef void ADMAPI (*ADMListEntryDrawProc)(ADMListEntryRef inEntry, ADMDrawerRef inDrawer);

/** Prototype for an entry event tracking procedure associated with a list.
	Use \c #ADMHierarchyListSuite5::SetMask() to specify which high-level events are sent to
	the tracker. You can call the entry's default tracker from this function, using
	\c #ADMListEntrySuite4::DefaultTrack(). The default tracker handles entry selection,
	including multiple selection.

	If you do not call the default tracker from your custom tracker,
	call \c #ADMTrackerSuite2::Abort() to exit the tracking loop.

		@param inEntry The entry object.
		@param inTracker The tracker object.
		@return True to send a notification to the entry when the mouse button
			is released, or for edit-text items, to indicate that a keystroke
			was handled. False to send no notification, or indicate that the
			keystroke was not handled.
		@see \c #ADMHierarchyListSuite5::SetTrackProc(), \c #ADMListEntrySuite4::DefaultTrack()
	*/
typedef ADMBoolean ADMAPI (*ADMListEntryTrackProc)(ADMListEntryRef inEntry, ADMTrackerRef inTracker);

/** Prototype for an entry notification-handling procedure associated with a list.
	Notifications are sent after a low-level event, such as mouse-button-up, occurs
	in an entry.
	Your function can completely implement the entry's behavior, or call the default
	notify function for the standard behavior before or after performing some additional action.
		@param inEntry The entry object.
		@param inNotifier The notification object.
		@return Nothing.
		@see \c #ADMHierarchyListSuite5::SetNotifyProc(), \c #ADMListEntrySuite4::DefaultNotify()
	*/
typedef void ADMAPI (*ADMListEntryNotifyProc)(ADMListEntryRef inEntry, ADMNotifierRef inNotifier);

/** Prototype for an entry termination procedure associated with a list.
	It is called when an entry is removed from the list with
	\c #ADMHierarchyListSuite5::RemoveEntry(). The procedure should free
	allocated memory or resources.
		@param inEntry The entry object.
		@return Nothing.
		@see \c #ADMHierarchyListSuite5::SetDestroyProc()
	*/
typedef void ADMAPI (*ADMListEntryDestroyProc)(ADMListEntryRef inEntry);


// =============================================================================
//		* ADM Hierarchy List Suite
// =============================================================================

/** Suite identifier */
#define kADMHierarchyListSuite "ADM Hierarchy List Suite"
/** Suite version */
#define kADMHierarchyListSuiteVersion5 5

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

	This suite allows you to create and manipulate a set of entries that make
	up a hierarchical list, and iterate through them recursively. It also provides access to
	the platform menu resource that implements the list.

	The default behavior of a hierarchical list itself is controlled at the item level.
	Additional behavior is associated with individual entries. You can provide
	a set of callback procedures for a hierarchical list, like those associated with a dialog
	or item, which affect the appearance and behavior of the contained entries.
	A list callback can modify or replace the default behavior of the entries.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMHierarchyListSuite and \c #kADMHierarchyListSuiteVersion5.
	*/
typedef struct ADMHierarchyListSuite5
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// menu items

	/** Sets the plug-in menu resource of a list. ADM reads the resource
		and maps the platform menu items to the ADM list entries. If called twice,
		the existing resource is freed before the new one is added.
			@param inList The list object.
			@param inMenuResPlugin The plug-in that defines the menu resource.
			@param inMenuResID The developer-defined menu resource identifier.
			@param inMenuResName The developer-defined menu resource name string.
			@return Nothing.
		 */
	void ADMAPI (*SetMenuID)(ADMHierarchyListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	/** Retrieves the plug-in menu resource of a list.
			@param inList The list object.
			@return The menu identifier.
		*/
	ADMInt32 ADMAPI (*GetMenuID)(ADMHierarchyListRef inList);

	// item dereference

	/** Retrieves the dialog item associated with a list.
			@param inList The list object.
			@return The item object.
		*/
	ADMItemRef ADMAPI (*GetItem)(ADMHierarchyListRef inList);

	// user storage

	/** Associates developer-defined data with a list.
			@param inList The list object.
			@param inUserData The data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMHierarchyListRef inList, ADMUserData inData);

	/** Retrieves developer-defined data associated with a list.
			@param inList The list object.
			@return The data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMHierarchyListRef inList);

	// item initialization proc

	/** Associates a list with a developer-defined entry initialization procedure,
		which is called when an entry is added to the list at the root level.
		The procedure is not assigned to child lists of member entries.
			@note The initialization of the list itself is handled at the item level.
			@param inList The list object.
			@param inInitProc The initialization procedure.
			@return Nothing.
			@see \c #SetInitProcRecursive()
		*/
	void ADMAPI (*SetInitProc)(ADMHierarchyListRef inList, ADMListEntryInitProc inInitProc);

	/** Associates a list with a developer-defined entry initialization procedure,
		which is called when a root-level entry is added to the list.
		The procedure is also assigned recursively to child lists of member entries.
			@note The initialization of the list itself is handled at the item level.
			@param inList The list object.
			@param inInitProc The initialization procedure.
			@return Nothing.
			@see \c #SetInitProc()
		*/
	void ADMAPI (*SetInitProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryInitProc inInitProc);

	/** Retrieves the developer-defined entry initialization procedure from a list.
			@param inList The list object.
			@return The initialization procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMListEntryInitProc ADMAPI (*GetInitProc)(ADMHierarchyListRef inList);

	// item draw proc

	/** Associates a list with a developer-defined entry drawing procedure,
		which is called for each root-level member entry when it is redrawn.
		The procedure is not assigned to child lists of member entries.

		The procedure can invoke the entry's default drawer with
		\c #ADMListEntrySuite4::DefaultDraw().
			@param inList The list object.
			@param inDrawProc The drawing procedure.
			@return Nothing.
			@see c #SetDrawProcRecursive()
		*/
	void ADMAPI (*SetDrawProc)(ADMHierarchyListRef inList, ADMListEntryDrawProc inDrawProc);

	/** Associates a list with a developer-defined entry drawing procedure,
		which is called for each member entry when it is redrawn.
		The procedure is also assigned recursively to child lists of member entries.

		The procedure can invoke the entry's default drawer with \c #ADMListEntrySuite4::DefaultDraw().
			@param inList The list object.
			@param inDrawProc The drawing procedure.
			@return Nothing.
			@see c #SetDrawProc()
		*/
	void ADMAPI (*SetDrawProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDrawProc inDrawProc);

	/** Retrieves the developer-defined entry drawing procedure from a list.
			@param inList The list object.
			@return The drawing procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMListEntryDrawProc ADMAPI (*GetDrawProc)(ADMHierarchyListRef inList);

	// item tracking proc

	/** Associates a list with a developer-defined entry event tracking procedure,
		which is called when an event of interest occurs in a root-level member entry.
		The procedure is not assigned to child lists of member entries.

		The procedure can invoke the entry's default tracker with
		\c #ADMListEntrySuite4::DefaultTrack().
			@param inList The list object.
			@param inTrackProc The tracking procedure.
			@return Nothing.
			@see c #SetTrackProcRecursive()
		*/
	void ADMAPI (*SetTrackProc)(ADMHierarchyListRef inList, ADMListEntryTrackProc inTrackProc);

	/** Associates a list with a developer-defined entry event tracking procedure,
		which is called when an event of interest occurs in a member entry.
		The procedure is also assigned recursively to child lists of member entries.

		The procedure can invoke the entry's default tracker with
		\c #ADMListEntrySuite4::DefaultTrack().
			@param inList The list object.
			@param inTrackProc The tracking procedure.
			@return Nothing.
			@see c #SetTrackProc()
		*/
	void ADMAPI (*SetTrackProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryTrackProc inTrackProc);

	/** Retrieves the developer-defined entry event tracking procedure from a list.
			@param inList The list object.
			@return The tracking procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMListEntryTrackProc ADMAPI (*GetTrackProc)(ADMHierarchyListRef inList);

	// item action mask

	/** Sets the event mask for a list. This determines which events are
		received by the list's entry event tracker, for root-level member entries.
		The procedure is not assigned to child lists of member entries.
			@param inList The list object.
			@param inMask The mask, a logical OR of \c #ADMAction constants.
			@return Nothing.
			@see \c #SetTrackProc(), \c #ADMListEntrySuite4::DefaultTrack()
		*/
	void ADMAPI (*SetMask)(ADMHierarchyListRef inList, ADMActionMask inMask);

	/** Sets the event mask for a list. This determines which events are
		received by the list's entry event tracker, for member entries.
		The mask is also assigned recursively to child lists of member entries.

			@param inList The list object.
			@param inMask The mask, a logical OR of \c #ADMAction constants.
			@return Nothing.
			@see \c #SetTrackProcRecursive(), \c #ADMListEntrySuite4::DefaultTrack()
		*/
	void ADMAPI (*SetMaskRecursive)(ADMHierarchyListRef inList, ADMActionMask inMask);

	/** Retrieves the event mask from a list. Only allowed events are
		received by the list's event tracker.
			@param inList The list object.
			@return The mask, a logical OR of \c #ADMAction constants.
		*/
	ADMActionMask ADMAPI (*GetMask)(ADMHierarchyListRef inList);

	// item notify proc

	/** Associates a list with a developer-defined entry notification-handling procedure,
		which is called when a root-level member entry receives a notification.
		The procedure is not assigned to child lists of member entries.

		The procedure can invoke the entry's default notification handler with
		\c #ADMListEntrySuite4::DefaultNotify().
			@param inList The list object.
			@param inNotifyProc The notification-handling procedure.
			@return Nothing.
			@see \c #SetNotifyProcRecursive()
		*/
	void ADMAPI (*SetNotifyProc)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	/** Associates a list with a developer-defined entry notification-handling procedure,
		which is called when a member entry at any level of nesting receives a notification.
		The procedure is also assigned recursively to child lists of member entries.

		The procedure can invoke the entry's default notification handler with
		\c #ADMListEntrySuite4::DefaultNotify().
			@param inList The list object.
			@param inNotifyProc The notification-handling procedure.
			@return Nothing.
			@see \c #SetNotifyProc()
		*/
	void ADMAPI (*SetNotifyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	/** Retrieves the developer-defined entry notification-handling procedure from a list.
			@param inList The list object.
			@return The notification-handling procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMListEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMHierarchyListRef inList);

	// user data for item notifier proc

	/** Associates a list object with developer-defined notification data.
			@param inList The list object.
			@param inUserData The notification data.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifierData)(ADMHierarchyListRef inList, ADMUserData inData);

	/** Retrieves the developer-defined notification data from a dialog item.
			@param inList The list object.
			@return The notification data.
		*/
	ADMUserData ADMAPI (*GetNotifierData)(ADMHierarchyListRef inList);

	// item destroy proc

	/** Associates a list with a developer-defined entry termination procedure,
		which is called when a root-level entry is removed from the list.
		The procedure is not assigned to child lists of member entries.

		The procedure should free memory or resources allocated for the entry at initialization.
			@note The termination of the list itself is handled at the item level.
			@param inList The list object.
			@param inDestroyProc The termination procedure.
			@return Nothing.
			@see \c #SetDestroyProcRecursive()
		*/
	void ADMAPI (*SetDestroyProc)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	/** Associates a list with a developer-defined entry termination procedure,
		which is called when an entry is removed from the list.
		The procedure is also assigned recursively to child lists of member entries.

		The procedure should free memory or resources allocated for the entry at initialization.
			@note The termination of the list itself is handled at the item level.
			@param inList The list object.
			@param inDestroyProc The termination procedure.
			@return Nothing.
			@see \c #SetDestroyProc()
		*/
	void ADMAPI (*SetDestroyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	/** Retrieves the developer-defined entry termination procedure from a list.
			@param inList The list object.
			@return The termination procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMListEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMHierarchyListRef inList);

	// item entry bounds

	/** Sets the width of the local and bounds rectangle of all member entries of
		a list, or, if the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, sets the width of a column of entries. This
		also indirectly sets the number of rows and columns.

		The width is not assigned to child lists of member entries.

			@param inList The list object.
			@param inWidth The width, in pixels, of an entry or column.
			@return Nothing.
			@see \c #SetEntryWidthRecursive()
  		*/
	void ADMAPI (*SetEntryWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);

	/** Sets the width of the local and bounds rectangle of all member entries of
		a list, or, if the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, sets the width of a column of entries. This
		also indirectly sets the number of rows and columns.

		The width is also assigned recursively to child lists of member entries.

			@param inList The list object.
			@param inWidth The width, in pixels, of an entry or column.
			@return Nothing.
			@see \c #SetEntryWidth()
  		*/
	void ADMAPI (*SetEntryWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);

	/** Retrieves the width of member entries, or, if the list belongs
		to a list-box item with style \c #kADMTileListBoxStyle, the width
		of a column. The default width of entries is the width of the list itself.
			@param inList The list object.
			@return The width, in pixels, of an entry or column.
			@see  \c #GetNonLeafEntryWidth()
		*/
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMHierarchyListRef inList);

	/** Retrieves the width of a list.
			@param inList The list object.
			@return The width, in pixels, of the list.
			@see  \c #GetEntryWidth()
		*/
	ADMInt32 ADMAPI (*GetNonLeafEntryWidth)(ADMHierarchyListRef inList);

	/** Sets the height of the local and bounds rectangle of all member entries of
		a list. If the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, this is also the row height.

		The height is not assigned to child lists of member entries.
			@param inList The list object.
			@param inHeight The height, in pixels, of an entry or row.
			@return Nothing.
 			@see  \c #SetEntryHeightRecursive()
 		*/
	void ADMAPI (*SetEntryHeight)(ADMHierarchyListRef inList, ADMInt32 inHeight);

	/** Sets the height of the local and bounds rectangle of all member entries of
		a list. If the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, this is also the row height.

		The height is also assigned recursively to child lists of member entries.
			@param inList The list object.
			@param inHeight The height, in pixels, of an entry or row.
			@return Nothing.
			@see  \c #SetEntryHeight()
  		*/
	void ADMAPI (*SetEntryHeightRecursive)(ADMHierarchyListRef inList, ADMInt32 inHeight);

	/** Retrieves the height of member entries, or, if the list belongs
		to a list-box item with style \c #kADMTileListBoxStyle, the height
		of a row.
			@param inList The list object.
			@return The height, in pixels, of an entry or row.
		*/
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMHierarchyListRef inList);

	/** Sets the rectangle in which the entry text is drawn.
		Does not assign the rectangle in child lists of member entries.
			@param inList The list object.
			@param inRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle;
				see \c #GetLocalRect().
			@return Nothing.
			@see  \c #SetEntryTextRectRecursive()
		*/
	void ADMAPI (*SetEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	/** Sets the rectangle in which the entry text is drawn.
		The rectangle is also assigned to child lists of member entries.
			@param inList The list object.
			@param inRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle;
				see \c #GetLocalRect().
			@return Nothing.
			@see  \c #SetEntryTextRect()
		*/
	void ADMAPI (*SetEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	/** Retrieves the rectangle in which entry text is drawn.
			@param inList The list object.
			@param outRect [out] A buffer in which to return the bounding box
				of the entry text. Coordinates are in pixels,
				relative to the local rectangle; see \c #GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*GetEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	/** Sets the rectangle in which entry text is drawn for those entries
		that contain child lists. Does not assign the rectangle in the child lists.
			@param inList The list object.
			@param InRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle;
				see \c #GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*SetNonLeafEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	/** Sets the rectangle in which the entry text is drawn for entries in lists
 		that contain child lists. Also assigns the rectangle recursively for
		child lists of member entries.
			@param inList The list object.
			@param InRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle;
				see \c #GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*SetNonLeafEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	/** Retrieves the rectangle in which entry text is drawn for entries in lists
 		that contain child lists.
			@param inList The list object.
			@param outRect [out] A buffer in which to return the bounding box
				of the entry text. Coordinates are in pixels,
				relative to the local rectangle; see \c #GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*GetNonLeafEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	// item list manipulation

	/** Creates a new entry object and adds it to a list, calling the list's
		entry initialization procedure if one has been specified.
		The new entry's ID is 0 until you set it with \c #ADMListEntrySuite4::SetID().
			@param inList The list object.
			@param inIndex The 0-based position index at which to insert
				the new member entry.
			@return The new entry object.
			@see \c #SetInitProc(), \c #ADMListEntrySuite4::Create(), \c #InsertGivenEntry()
		*/
	ADMListEntryRef ADMAPI (*InsertEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	/** Removes a root-level entry from a list and destroys the entry object, first
		calling the list's entry termination procedure if one has been specified.
		The function does not affect any child list or nested entries contained in this entry.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry.
			@return Nothing.
			@see \c #SetDestroyProc()
		*/
	void ADMAPI (*RemoveEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	/** Retrieves a root-level entry from a list, using the developer-assigned
		identifier.
			@param inList The list object.
			@param inEntryID The entry object identifier. You can obtain this
				with \c #ADMListEntrySuite4::GetID().
			@return The entry object, or \c NULL if the entry is not in the list at the root level.
		*/
	ADMListEntryRef ADMAPI (*GetEntry)(ADMHierarchyListRef inList, ADMInt32 inEntryID);

	/** Retrieves a root-level entry from a list by index position. Use with
		\c #NumberOfEntries() to iterate through a list.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry.
			@return The entry object.
			@see \c #IndexLeafEntry()
		*/
	ADMListEntryRef ADMAPI (*IndexEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	/** Retrieves a root-level entry from a list whose text label matches a C string.
			@param inList The list object.
			@param inText The text string.
			@return The entry object, or \c NULL if no matching entry is in the list.
			@see \c #FindEntryW()
		*/
	ADMListEntryRef ADMAPI (*FindEntry)(ADMHierarchyListRef inList, const char* inText);

	/** Retrieves the root-level entry at a given coordinate position in a list.
			@param inList The list object.
			@param inPoint The position. Coordinates are in pixels,
				relative to the list, whose origin is the top left corner.
			@return The entry object, or \c NULL if no matching entry is in the list.
		*/
	ADMListEntryRef ADMAPI (*PickEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);

	/** Retrieves the hierarchy leaf-level entry at a given coordinate position in a list.
		A leaf-level entry is one with no child list.
			@param inList The list object.
			@param inPoint The position. Coordinates are in pixels,
				relative to the list, whose origin is the top left corner.
			@return The entry object, or \c NULL if no matching entry is in the list.
		*/
	ADMListEntryRef ADMAPI (*PickLeafEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);

	/** Retrieves the selected root-level entry in a single-selection list, or
		the first selected entry in a list that allows multiple selection.
		When a child entry is selected, the parent is also in the selected state.
			@param inList The list object.
			@return The entry object, or \c NULL if no entry is selected.
			@see \c #IndexSelectedEntry()
		*/
	ADMListEntryRef ADMAPI (*GetActiveEntry)(ADMHierarchyListRef inList);

	/** Retrieves the selected leaf-level entry in a single-selection list,
		or the first selected leaf-level entry in a list that allows multiple selection.
		A leaf-level entry is one with no child list.
			@param inList The list object.
			@return The entry object, or \c NULL if no entry is selected.
			@see \c #IndexSelectedEntry()
		*/
	ADMListEntryRef ADMAPI (*GetActiveLeafEntry)(ADMHierarchyListRef inList);

	// selection list manipulation

	/** Retrieves a root-level selected leaf or parent entry from a list that allows multiple selection.
		Use with \c #NumberOfSelectedEntries() to iterate through root-level selections
		in a list. When a child entry is selected at any level of nesting, returns the root-level parent.
			@param inList The list object.
			@param inSelectionIndex The 0-based position index of the entry among selected entries.
			@return The entry object.
			@see \c #IndexAllSelectedEntriesInHierarchy(),
				\c #IndexUnNestedSelectedEntriesInHierarchy()
		*/
	ADMListEntryRef ADMAPI (*IndexSelectedEntry)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	/** Retrieves a selected leaf entry from any level of a list that allows multiple selection.
		Use with \c #IndexAllSelectedEntriesInHierarchy() to iterate through selections
		in a list at all levels of nesting.
			@param inList The list object.
			@param inSelectionIndex The 0-based position index of the entry among selected entries.
			@return The entry object.
			@see \c #IndexSelectedEntry(),
				\c #IndexUnNestedSelectedEntriesInHierarchy()
		*/
	ADMListEntryRef ADMAPI (*IndexAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	/** Retrieves a root-level selected leaf entry from a list that allows multiple selection.
		Ignores parents of selected child entries.
		Use with \c #NumberOfUnNestedSelectedEntriesInHierarchy() to iterate through
		root-level selections in a list.
			@param inList The list object.
			@param inSelectionIndex The 0-based position index of the entry among selected entries.
			@return The entry object.
			@see \c #IndexAllSelectedEntriesInHierarchy(), \c #IndexSelectedEntry()

		*/
	ADMListEntryRef ADMAPI (*IndexUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	/** Reports the number of root-level entries in a list. Use with
		\c #IndexEntry() to iterate through a list.
			@param inList The list object.
			@return The number of root-level entries.
		*/
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMHierarchyListRef inList);

	/** Reports the number of root-level selected entries in a list, counting
		the root-level parent of a selected child at any level of nesting.
		Use with \c #IndexEntry() to iterate through selections in a list that
		allows multiple selection.
			@param inList The list object.
			@return The number of root-level selected entries.
			@see \c #NumberOfAllSelectedEntriesInHierarchy(),
				\c #NumberOfUnNestedSelectedEntriesInHierarchy()
		*/
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMHierarchyListRef inList);

	/** Reports the number of selected leaf entries in a list, at any level
		of nesting. Use with \c #IndexEntry() to iterate through selections
		in a list that allows multiple selection.
			@param inList The list object.
			@return The number of selected entries.
			@see \c #NumberOfAllSelectedEntriesInHierarchy(),
				\c #NumberOfUnNestedSelectedEntriesInHierarchy()
		*/
	ADMInt32 ADMAPI (*NumberOfAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);

	/** Reports the number of root-level selected leaf entries in a list.
		Does not count the root-level parent of a selected child.
		Use with \c #IndexEntry() to iterate through selections in a list that
		allows multiple selection.
			@param inList The list object.
			@return The number of root-level selected leaf entries.
			@see \c #NumberOfAllSelectedEntriesInHierarchy(),
				\c #NumberOfUnNestedSelectedEntriesInHierarchy()
		*/
	ADMInt32 ADMAPI (*NumberOfUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);

	// item hierarchy

	/** Retrieves the parent list entry for a hierarchy list.
			@param inList The list object.
			@return The parent list entry object.
		*/
	ADMListEntryRef ADMAPI (*GetParentEntry)(ADMHierarchyListRef inList);

	// coordinate system conversion

	/** Retrieves the size of a list, relative to its own origin.
			@param inList The list object.
			@param outLocalRect [out] A buffer in which to return the bounding box,
				where the \c top and \c left values are 0,
				and the \c bottom and \c right members indicate the size.
			@return Nothing
		*/
	void ADMAPI (*GetLocalRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	/** Transforms a point from local coordinates for a list to screen coordinates.
			@param inList The list object.
			@param ioPoint [in, out] A buffer in which to pass the point in local
				coordinates, and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	/** Transforms a point from screen coordinates to local coordinates for a list.
			@param inList The list object.
			@param ioPoint [in, out] A buffer in which to pass the point in screen
				coordinates, and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	/** Transforms a point from local coordinates for a list to local coordinates for the
		parent list.
			@param inList The list object.
			@param ioPoint [in, out] A buffer in which to pass the point in local
				coordinates, and return it in item parent coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToGlobalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	/** Transforms a point from parent-list coordinates to local coordinates for a list.
			@param inList The list object.
			@param ioPoint [in, out] A buffer in which to pass the point in parent-item
				coordinates, and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*GlobalToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	/** Transforms a rectangle from local coordinates for a list to local coordinates for the
		parent list.
			@param inList The list object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in local
				coordinates, and return it in item parent coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToGlobalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	/** Transforms a rectangle from parent-list coordinates to local coordinates for a list.
			@param inList The list object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in parent-item
				coordinates, and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*GlobalToLocalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	// item margin accessors

	/** Sets the indentation spacing for the expand/collapse arrow in a list.
			@param inList The list object.
			@param inWidth The indentation in pixels.
			@return Nothing.
			@see \c #SetIndentationWidthRecursive()
		*/
	void ADMAPI (*SetIndentationWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);

	/** Sets the indentation spacing for the expand/collapse arrow in a list.
		Also sets the indentation recursively in all child lists.
			@param inList The list object.
			@param inWidth The indentation in pixels.
			@return Nothing
		*/
	void ADMAPI (*SetIndentationWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);

	/** Retrieves the indentation spacing for the expand/collapse arrow in a list.
			@param inList The list object.
			@param inWidth [out] A buffer in which to return the indentation in pixels.
			@return Nothing.
		*/
	ADMInt32 ADMAPI (*GetIndentationWidth)(ADMHierarchyListRef inList);

	/** Sets the left margin for a list. This is an indentation from the left
		edge of the bounding box where drawing begins.
			@param inList The list object.
			@param inWidth The indentation in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetLocalLeftMargin)(ADMHierarchyListRef inList, ADMInt32 inWidth);

	/** Retrieves the  left margin for a list.
			@param inList The list object.
			@param inWidth [out] A buffer in which to return the indentation in pixels.
			@return Nothing.
			@see \c #SetLocalLeftMargin()
		*/
	ADMInt32 ADMAPI (*GetLocalLeftMargin)(ADMHierarchyListRef inList);

	/** Retrieves the  left margin for the list parent of a child list.
			@param inList The list object.
			@param inWidth [out] A buffer in which to return the indentation in pixels.
			@return Nothing.
			@see \c #SetLocalLeftMargin()
		*/
	ADMInt32 ADMAPI (*GetGlobalLeftMargin)(ADMHierarchyListRef inList);

	/** Turns divisions on or off for a list. When a list is divided, a horizontal
		line is drawn between each pair of entries.
			@param inList The list object.
			@param inDivided True to turn divisions on, false to turn them off.
			@return Nothing.
			@see \c #SetDividedRecursive()
		*/
	void ADMAPI (*SetDivided)(ADMHierarchyListRef inList, ADMBoolean inDivided);

	/** Turns divisions on or off for a list, and recursively for all child lists.
			@param inList The list object.
			@param inDivided True to turn divisions on, false to turn them off.
			@return Nothing.
			@see \c #SetDivided()
		*/
	void ADMAPI (*SetDividedRecursive)(ADMHierarchyListRef inList, ADMBoolean inDivided);

	/** Reports whether a list is divided. When a list is divided, a horizontal
		line is drawn between each pair of entries.
			@param inList The list object.
			@return True if the list is divided, false if not.
		*/
	ADMBoolean ADMAPI (*GetDivided)(ADMHierarchyListRef inList);

	/** Sets options flags for a list, which control its appearance and behavior.
			@param inList The list object.
			@param inFlags A logical OR of these constants:
				<br>\c #kMultiSelectAcrossHierarchyLevels
				<br>\c #kHierarchyListEndedWithFrame
				<br>\c #kHierarchyListTopLevelSpecialBackground
				<br>\c #kHierarchyListLeafOnly
			@return Nothing.
			@see \c #SetFlagsRecursive()
		*/
	void ADMAPI (*SetFlags)(ADMHierarchyListRef inList, ADMInt32 inFlags);

	/** Sets options flags for a list, and recursively for all child lists.
		The flags control the appearance and behavior of the list.
			@param inList The list object.
			@param inFlags A logical OR of these constants:
				<br>\c #kMultiSelectAcrossHierarchyLevels
				<br>\c #kHierarchyListEndedWithFrame
				<br>\c #kHierarchyListTopLevelSpecialBackground
				<br>\c #kHierarchyListLeafOnly
			@return Nothing.
		*/
	void ADMAPI (*SetFlagsRecursive)(ADMHierarchyListRef inList, ADMInt32 inFlags);

	/** Retrieves the option flags for a list, which control its appearance and behavior.
			@param inList The list object.
			@return The flags value, a logical OR of these constants:
				<br>\c #kMultiSelectAcrossHierarchyLevels
				<br>\c #kHierarchyListEndedWithFrame
				<br>\c #kHierarchyListTopLevelSpecialBackground
				<br>\c #kHierarchyListLeafOnly
		*/
	ADMInt32 ADMAPI (*GetFlags)(ADMHierarchyListRef inList);

	// item invalidation

	/** Marks a list as being in need of redrawing.
			@param inList The list object.
			@return Nothing
		*/
	void ADMAPI (*Invalidate)(ADMHierarchyListRef inList);

	// leaf item accessors

	/** Retrieves a leaf-level entry from a list by index position, from any
		level of nesting. A leaf-level entry is one with no child list.
		Use with \c #NumberOfLeafEntries() to iterate through a list.
			@param inList The list object.
			@param inLeafItem The 0-based position index of the entry.
			@return The entry object.
			@see \c #IndexEntry()
		*/
 	ADMListEntryRef ADMAPI (*IndexLeafEntry)(ADMHierarchyListRef inList, ADMInt32 inLeafItem);

	/** Retrieves the leaf index position of an entry in a list, from the collection
		of all leaf entries at any level of nesting, which you can iterate through
		with \c #IndexLeafEntry().
			@param inList The list object.
			@param inEntry The entry object.
			@return The 0-based position index of the entry.
		*/
	ADMInt32 ADMAPI (*GetLeafIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);

	/** Reports the number of leaf-level entries in a list, at any
		level of nesting. A leaf-level entry is one with no child list.
		Use with \c #IndexLeafEntry() to iterate through a list.
			@param inList The list object.
			@return The number of leaf entries.
		*/
	ADMInt32 ADMAPI (*NumberOfLeafEntries)(ADMHierarchyListRef inList);

	// item sequence manipulation

	/** Switches the index positions of two entries in a list.
			@param inList The list object.
			@param inFromIndex The 0-based position index of the first entry.
			@param inToIndex The 0-based position index of the second entry.
			@return Nothing.
		*/
	void ADMAPI (*SwapEntries)(ADMHierarchyListRef inList, ADMInt32 inFromIndex,
				ADMInt32 inToIndex);

	/** Inserts an existing entry into a list.
			@param inList The list object.
			@param inEntry The entry object.
			@param inIndex The 0-based position index at which to insert the entry.
			@return The newly added entry object.
		*/
	ADMListEntryRef ADMAPI (*InsertGivenEntry)(ADMHierarchyListRef inList,
				ADMListEntryRef inEntry, ADMInt32 inIndex);

	/** Removes an entry from a list without destroying it. This can be used
		for a drag-and-drop operation, for example.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry to remove.
			@return The entry object.
		*/
	ADMListEntryRef ADMAPI (*UnlinkEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	// item selection

	/** Deselects all entries in a list, at any level of nesting.
			@param inList The list object.
			@return Nothing.
		*/
	void ADMAPI (*DeselectAll)(ADMHierarchyListRef inList);

	// customizing appearance

	/** Sets the background color of a list.
			@param inList The list object.
			@param inColor The color constant.
			@return Nothing.
			@see \c #SetFlags()
		*/
	void ADMAPI (*SetBackgroundColor)(ADMHierarchyListRef inList,
				ADMColor inColor);

	// expanded item accessors

	/** Retrieves an expanded entry from a list by index position, from any
		level of nesting. Use with \c #NumberOfExpandedEntries() to iterate
		through a list.
			@param inList The list object.
			@param inExpandedItem The 0-based position index of the entry.
			@return The entry object.
			@see \c #GetExpandedIndex()
		*/
	ADMListEntryRef ADMAPI (*IndexExpandedEntry)(ADMHierarchyListRef inList, ADMInt32 inExpandedItem);

	/** Retrieves the expanded-entry index position of an entry in a list, from the collection
		of all expanded entries at any level of nesting, which you can iterate through
		with \c #IndexExpandedEntry().
			@param inList The list object.
			@param inEntry The entry object.
			@return The 0-based position index of the entry.
		*/
	ADMInt32 ADMAPI (*GetExpandedIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);

	/** Reports the number of expanded entries in a list, at any
		level of nesting. Use with \c #IndexExpandedEntry() to iterate
		through a list.
			@param inList The list object.
			@return The number of expanded entries.
		*/
	ADMInt32 ADMAPI (*NumberOfExpandedEntries)(ADMHierarchyListRef inList);

	// restrict item invalidation

	/** Begins a sequence of calls to \c #Invalidate(), during which
		no redrawing occurs. End the sequence with a call to
		\c #StopMultipleItemInvalidate(). Use this for efficiency and
		to avoid flicker when updating multiple entries in a list.
			@param inList The list object.
			@return Nothing.
		*/
	void ADMAPI (*StartMultipleItemInvalidate)(ADMHierarchyListRef inList);

	/** Ends a sequence of calls to \c #Invalidate(), as begun with
		\c #StartMultipleItemInvalidate(). Use this for efficiency and
		to avoid flicker when updating multiple entries in a list.
			@param inList The list object.
			@return Nothing.
		*/
	void ADMAPI (*StopMultipleItemInvalidate)(ADMHierarchyListRef inList);

	/** Retrieves a root-level entry from a list whose text label matches a Unicode string.
			@param inList The list object.
			@param inText The text string.
			@return The entry object, or \c NULL if no matching entry is in the list.
			@see \c #FindEntry()
		*/
	ADMListEntryRef ADMAPI (*FindEntryW)(ADMHierarchyListRef inList, const ADMUnicode* inText);

} ADMHierarchyListSuite5;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMHierarchyListOld__
#ifdef MAC_ENV
#include "ADMHierarchyListOld.h"
#else
#include ".\Legacy\ADMHierarchyListOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMHierarchyList__
