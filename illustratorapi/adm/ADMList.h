/*******************************************************************************
*
* ADMList.h -- ADM List Suite
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
* Started by Dave Lazarony, 07 May 1996
*
********************************************************************************/

/** @file ADMList.h ADM List Suite */

#ifndef __ADMList__
#define __ADMList__

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
//	User-provided function types

/** Prototype for an entry initialization procedure associated with a list.
	It is called when an entry is added to the list with
	\c #ADMListSuite4::InsertEntry(). The procedure can, for example,
	allocate memory or resources, or initialize variables.
		@param inEntry The entry object.
		@return An ADM error code.
		@see \c #ADMListSuite4::SetInitProc()
	*/
typedef ADMErr ADMAPI (*ADMEntryInitProc)(ADMEntryRef inEntry);

/** Prototype for an entry drawing procedure associated with a list.
	Your function can completely draw a custom entry, or call the default
	drawer to draw the basic appearance, then modify it.
		@param inEntry The entry object.
		@param inDrawer The drawing object.
		@return Nothing.
		@see \c #ADMListSuite4::SetDrawProc(), \c #ADMEntrySuite6::DefaultDraw()
	*/
typedef void ADMAPI (*ADMEntryDrawProc)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);

/** Prototype for an entry event tracking procedure associated with a list.
	Use \c #ADMListSuite4::SetMask() to specify which high-level events are sent to
	the tracker. You can call the entry's default tracker from this function, using
	\c #ADMEntrySuite6::DefaultTrack(). The default tracker handles entry selection,
	including multiple selection.

	If you do not call the default tracker from your custom tracker,
	call \c #ADMTrackerSuite2::Abort() to exit the tracking loop.

		@param inEntry The entry object.
		@param inTracker The tracker object.
		@return True to send a notification to the entry when the mouse button
			is released, or for edit-text items, to indicate that a keystroke
			was handled. False to send no notification, or indicate that the
			keystroke was not handled.
		@see \c #ADMListSuite4::SetTrackProc(), \c #ADMEntrySuite6::DefaultTrack()
	*/
typedef ADMBoolean ADMAPI (*ADMEntryTrackProc)(ADMEntryRef inEntry, ADMTrackerRef inTracker);

/** Prototype for an entry notification-handling procedure associated with a list.
	Notifications are sent after a low-level event, such as mouse-button-up, occurs
	in an entry.
	Your function can completely implement the entry's behavior, or call the default
	notify function for the standard behavior before or after performing some additional action.
		@param inEntry The entry object.
		@param inNotifier The notification object.
		@return Nothing.
		@see \c #ADMListSuite4::SetNotifyProc(), \c #ADMEntrySuite6::DefaultNotify()
	*/
typedef void ADMAPI (*ADMEntryNotifyProc)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);

/** Prototype for an entry termination procedure associated with a list.
	It is called when an entry is removed from the list with
	\c #ADMListSuite4::RemoveEntry(). The procedure should free
	allocated memory or resources.
		@param inEntry The entry object.
		@return Nothing.
		@see \c #ADMListSuite4::SetDestroyProc()
	*/
typedef void ADMAPI (*ADMEntryDestroyProc)(ADMEntryRef inEntry);


// =============================================================================
//		* ADM List Suite
// =============================================================================

/** List suite name */
#define kADMListSuite "ADM List Suite"
/** List suite version */
#define kADMListSuiteVersion4 4

// -----------------------------------------------------------------------------

/** @ingroup Suites
	List objects are associated with dialog items of types that provide
	a list of choices, including list boxes, popup lists, popup menus,
	spin-edit popups, and text-edit popups. A list, \c #ADMListRef, contains
	\e entries, \c #ADMEntryRef. The individual entry objects contain the entry
	appearance and state information; see \c #ADMEntrySuite6.

	This suite allows you to create and manipulate a set of entries that make
	up a list, and iterate through them. It also provides access to	the
	platform menu resource that implements the list.

	The default behavior of a list is controlled at the item level, and
	additional behavior is associated with individual entries. You can provide
	a set of callback procedures for a list, like those associated with a dialog
	or item, which affect the appearance and behavior of the contained entries.
	A list callback can modify or replace the default behavior of the entries.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMListSuite and \c #kADMListSuiteVersion4.
	*/
typedef struct ADMListSuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// menu IDs

	/** Sets the plug-in menu resource of a list. ADM reads the resource
		and maps the platform menu items to the ADM list entries. If called twice,
		the existing resource is freed before the new one is added.
			@param inList The list object.
			@param inMenuResPlugin The plug-in that defines the menu resource.
			@param inMenuResID The menu resource identifier.
			@param inMenuResName The menu resource name string.
			@return Nothing.
		 */
	void ADMAPI (*SetMenuID)(ADMListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	/** Retrieves the plug-in menu resource of a list.
			@param inList The list object.
			@return The menu identifier.
		*/
	ADMInt32 ADMAPI (*GetMenuID)(ADMListRef inList);

	// container accessor

	/** Retrieves the dialog item associated with a list.
			@param inList The list object.
			@return The item object.
		*/
	ADMItemRef ADMAPI (*GetItem)(ADMListRef inList);

	// user data storage

	/** Associates developer-defined data with a list.
			@param inList The list object.
			@param inUserData The data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMListRef inList, ADMUserData inUserData);
	/** Retrieves developer-defined data associated with a list.
			@param inList The list object.
			@return The data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMListRef inList);

	// override hooks

	/** Associates a list with a developer-defined entry initialization procedure,
		which is called when an entry is added to the list.	The procedure can,
		for example, allocate memory or resources, or initialize variables.
			@note The initialization of the list itself is handled at the item level.
			@param inList The list object.
			@param inInitProc The initialization procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetInitProc)(ADMListRef inList, ADMEntryInitProc inInitProc);

	/** Retrieves the developer-defined entry initialization procedure from a list.
			@param inList The list object.
			@return The initialization procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMEntryInitProc ADMAPI (*GetInitProc)(ADMListRef inList);

	/** Associates a list with a developer-defined entry drawing procedure,
		which is called for each member entry when it is redrawn. The procedure
		can invoke the entry's default drawer with \c #ADMEntrySuite6::DefaultDraw().
			@param inList The list object.
			@param inDrawProc The drawing procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetDrawProc)(ADMListRef inList, ADMEntryDrawProc inDrawProc);

	/** Retrieves the developer-defined entry drawing procedure from a list.
			@param inList The list object.
			@return The drawing procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMEntryDrawProc ADMAPI (*GetDrawProc)(ADMListRef inList);

	/** Associates a list with a developer-defined entry event tracking procedure,
		which is called when an event of interest occurs in a member entry.
		The procedure can invoke the entry's default tracker with
		\c #ADMEntrySuite6::DefaultTrack().
			@param inList The list object.
			@param inTrackProc The tracking procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetTrackProc)(ADMListRef inList, ADMEntryTrackProc inTrackProc);

	/** Retrieves the developer-defined entry event tracking procedure from a list.
			@param inList The list object.
			@return The tracking procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMEntryTrackProc ADMAPI (*GetTrackProc)(ADMListRef inList);

	/** Associates a list with a developer-defined entry notification-handling procedure,
		which is called when a member entry receives a notification.
		The procedure can invoke the entry's notification handler with
		\c #ADMEntrySuite6::DefaultNotify().
			@param inList The list object.
			@param inNotifyProc The notification-handling procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifyProc)(ADMListRef inList, ADMEntryNotifyProc inNotifyProc);

	/** Retrieves the developer-defined entry notification-handling procedure from a list.
			@param inList The list object.
			@return The notification-handling procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMListRef inList);

	/** Associates a list with a developer-defined entry termination procedure,
		which is called when an entry is removed from the list.	The procedure
		should free memory or resources allocated for the entry at initialization.
			@note The termination of the list itself is handled at the item level.
			@param inList The list object.
			@param inDestroyProc The termination procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetDestroyProc)(ADMListRef inList, ADMEntryDestroyProc inDestroyProc);

	/** Retrieves the developer-defined entry termination procedure from a list.
			@param inList The list object.
			@return The termination procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMListRef inList);

	// entry bounds accessors

	/** Sets the width of the local and bounds rectangle of all member entries of
		a list, or, if the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, sets the width of a column of entries. This
		also indirectly sets the number of rows and columns.
			@param inList The list object.
			@param inWidth The width, in pixels, of an entry or column.
			@return Nothing.
  		*/
	void ADMAPI (*SetEntryWidth)(ADMListRef inList, ADMInt32 inWidth);

	/** Retrieves the width of member entries, or, if the list belongs
		to a list-box item with style \c #kADMTileListBoxStyle, the width
		of a column. The default width of entries is the width of the list itself.
			@param inList The list object.
			@return The width, in pixels, of an entry or column.
		*/
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMListRef inList);

	/** Sets the height of the local and bounds rectangle of all member entries of
		a list. If the list belongs to a list-box item with style
		\c #kADMTileListBoxStyle, this is also the row height.
			@param inList The list object.
			@param inHeight The height, in pixels, of an entry or row.
			@return Nothing.
  		*/
	void ADMAPI (*SetEntryHeight)(ADMListRef inList, ADMInt32 inHeight);

	/** Retrieves the height of member entries, or, if the list belongs
		to a list-box item with style \c #kADMTileListBoxStyle, the height
		of a row.
			@param inList The list object.
			@return The height, in pixels, of an entry or row.
		*/
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMListRef inList);

	/** Sets the rectangle in which the entry text is drawn.
			@param inList The list object.
			@param inRect The bounding box of the entry text.
				Coordinates are in pixels, relative to the local rectangle.
				See \c #ADMListEntrySuite4::GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*SetEntryTextRect)(ADMListRef inList, const ADMRect* inRect);
	/** Retrieves the rectangle in which the entry text is drawn.
			@param inList The list object.
			@param outRect [out] A buffer in which to return the bounding box
				of the entry text. Coordinates are in pixels,
				relative to the local rectangle. See \c #ADMListEntrySuite4::GetLocalRect().
			@return Nothing.
		*/
	void ADMAPI (*GetEntryTextRect)(ADMListRef inList, ADMRect* outRect);

	// entry array accessors

	/** Creates a new entry object and adds it to a list, calling the list's
		entry initialization procedure if one has been specified.
		The new entry's ID is 0 until you set it with \c #ADMEntrySuite6::SetID().
			@param inList The list object.
			@param inIndex The 0-based position index at which to insert
				the new member entry.
			@return The new entry object.
			@see \c #SetInitProc(), \c #ADMEntrySuite6::Create()
		*/
	ADMEntryRef ADMAPI (*InsertEntry)(ADMListRef inList, ADMInt32 inIndex);

	/** Removes an entry from a list and destroys the entry object, first
		calling the list's entry termination procedure if one has been specified.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry.
			@return Nothing.
			@see \c #SetDestroyProc()
		*/
	void ADMAPI (*RemoveEntry)(ADMListRef inList, ADMInt32 inIndex);

	/** Retrieves an entry from a list using the developer-assigned identifier.
			@param inList The list object.
			@param inEntryID The entry object identifier. You can obtain this
				with \c #ADMEntrySuite6::GetID().
			@return The entry object, or \c NULL if the entry is not in the list.
		*/
	ADMEntryRef ADMAPI (*GetEntry)(ADMListRef inList, ADMInt32 inEntryID);

	/** Retrieves an entry from a list by index position. Use with
		\c #NumberOfEntries() to iterate through a list.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry.
			@return The entry object.
		*/
	ADMEntryRef ADMAPI (*IndexEntry)(ADMListRef inList, ADMInt32 inIndex);

	/** Retrieves an entry from a list whose text label matches a C string.
			@param inList The list object.
			@param inText The text string.
			@return The entry object, or \c NULL if no matching entry is in the list.
			@see \c #FindEntryW()
		*/
	ADMEntryRef ADMAPI (*FindEntry)(ADMListRef inList, const char* inText);

	/** Retrieves the entry at a given coordinate position in a list.
			@param inList The list object.
			@param inPoint The position. Coordinates are in pixels,
				relative to the list, whose origin is the top left corner.
			@return The entry object, or \c NULL if no matching entry is in the list.
		*/
	ADMEntryRef ADMAPI (*PickEntry)(ADMListRef inList, const ADMPoint* inPoint);

	/** Retrieves the selected entry in a list, or the first selected entry in
		a list that allows multiple selection.
			@param inList The list object.
			@return The entry object, or \c NULL if no entry is selected.
			@see \c #IndexSelectedEntry()
		*/
	ADMEntryRef ADMAPI (*GetActiveEntry)(ADMListRef inList);

	/** Retrieves a selected entry from a list that allows multiple selection.
		Use with  \c #NumberOfSelectedEntries() to iterate through selections
		in a list.
			@param inList The list object.
			@param inIndex The 0-based position index of the entry among selected entries.
			@return The entry object.
		*/
	ADMEntryRef ADMAPI (*IndexSelectedEntry)(ADMListRef inList, ADMInt32 inSelectionIndex);

	/** Reports the number of entries in a list.  Use with
		\c #IndexEntry() to iterate through a list.
			@param inList The list object.
			@return The number of entries.
		*/
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMListRef inList);

	/** Reports the number of selected entries in a list.  Use with
		\c #IndexEntry() to iterate through selections in a list that
		allows multiple selection.
			@param inList The list object.
			@return The number of entries.
		*/
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMListRef inList);

	// item action mask

	/** Sets the event mask for a list. This determines which events are
		received by the list's entry event tracker.
			@param inList The list object.
			@param inActionMask The mask, a logical OR of \c #ADMAction constants.
			@return Nothing.
			@see \c #SetTrackProc(), \c #ADMEntrySuite6::DefaultTrack()
		*/
	void ADMAPI (*SetMask)(ADMListRef inList, ADMActionMask inActionMask);

	/** Retrieves the event mask from a list. Only allowed events are
		received by the list's event tracker.
			@param inList The list object.
			@return The mask, a logical OR of \c #ADMAction constants.
		*/
	ADMActionMask ADMAPI (*GetMask)(ADMListRef inList);

	// user data storage for notifiers

	/** Associates a list object with developer-defined notification data.
			@param inList The list object.
			@param inUserData The notification data.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifierData)(ADMListRef inList, ADMUserData inUserData);

	/** Retrieves the developer-defined notification data from a dialog item.
			@param inList The list object.
			@return The notification data.
		*/
	ADMUserData ADMAPI (*GetNotifierData)(ADMListRef inList);

	// customizing appearance

	/** Sets the background color for a list.
			@param inList The list object.
			@param inColor The color constant. Use \c #kADMDummyColor to
				restore the default.
			@return Nothing.
		*/
	void ADMAPI (*SetBackgroundColor)(ADMListRef inList, ADMColor inColor);

	// searching

	/** Selects an entry in a list whose text label matches a C string.
			@param inList The list object.
			@param inFindText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SelectByText)(ADMListRef inList, const char* inFindText);

	/** Selects an entry in a list whose text label matches a Unicode string.
			@param inList The list object.
			@param inFindText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SelectByTextW)(ADMListRef inList, const ADMUnicode* inFindText);

	/** Retrieves an entry from a list whose text label matches a Unicode string.
			@param inList The list object.
			@param inText The text string.
			@return The entry object, or \c NULL if no matching entry is in the list.
			@see \c #FindEntry()
		*/
	ADMEntryRef ADMAPI (*FindEntryW)(ADMListRef inList, const ADMUnicode* inText);

} ADMListSuite4;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMListOld__
#ifdef MAC_ENV
#include "ADMListOld.h"
#else
#include ".\Legacy\ADMListOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMList__
