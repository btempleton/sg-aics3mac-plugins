/*******************************************************************************
*
* ADMNotifier.h -- ADM Notifier Suite
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
* Started by Dave Lazarony, 06 Mar 1996
*
********************************************************************************/

/** @file ADMNotifier.h ADM Notifier Suite */

#ifndef __ADMNotifier__
#define __ADMNotifier__

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
//	Notifier type constants

/** The default notifier, received by all ADM objects, for any events
	that cannot be classified explicitly as one of the other types. */
#define kADMUserChangedNotifier "ADM User Changed Notifier"

/** Received by items when the user is in process of changing
	the value (dragging a slider thumb, for instance) but has
	not yet completed the task. */
#define kADMIntermediateChangedNotifier "ADM Intermediate Changed Notifier"

/** Received when an item or dialog is resized. If a dialog receives
	this notification and resizes the contained items, each item also
	receives it. */
#define kADMBoundsChangedNotifier "ADM Bounds Changed Notifier"

/** Received when a view of a dialog is resized.
		\li In Windows, this notifier is the same as the \c # kADMBoundsChangedNotifier.
		\li In MacOS, this notifier is received on the content view
			of a dialog for \c HView based objects. */
#define kADMViewBoundsChangedNotifier "ADM View Bounds Changed Notifier"

/** Received by list entries (not text-edit items) when text has been changed
	by in-place editing. (A text change in a text-edit item sends
	the \c #kADMUserChangedNotifier.)
	*/
#define kADMEntryTextChangedNotifier "ADM Entry Text Changed Notifier"

/** Received by dialogs when user has clicked the close box.
	Your handler must hide the dialog; ADM does not do so automatically.*/
#define kADMCloseHitNotifier "ADM Close Hit Notifier"

/** Received by dialogs when user has clicked the zoom box.
	Your handler must resize the dialog; ADM does not do so automatically. */
#define kADMZoomHitNotifier "ADM Zoom Hit Notifier"

/** Received by dialogs when the user double clicks or triple clicks
	in the title bar of a tab palette. */
#define kADMCycleNotifier "ADM Cycle Notifier"

/** Received by dialogs when the user collapses a palette using a tab. */
#define kADMCollapseNotifier "ADM Collapse Notifier"

/** Received by dialogs when the user expands a palette using a tab.*/
#define kADMExpandNotifier "ADM Expand Notifier"

/** Received by dialogs when an edit operation has occurred via a clipboard
	operation. */
#define kADMContextMenuChangedNotifier "ADM Context Menu Changed Notifier"

/** Received by dialogs when the user shows the window, before the window is drawn. */
#define kADMWindowShowNotifier "ADM Show Window Notifier"

/** Received by dialogs when the user hides the window, before the window
	is undrawn.  */
#define kADMWindowHideNotifier "ADM Hide Window Notifier"

/** Received by an item group when it is shown, before items are drawn. */
#define kADMGroupShowNotifier "ADM Show Group Notifier"

/** Received by an item group when it is hidden, before items are undrawn. */
#define kADMGroupHideNotifier "ADM Hide Group Notifier"

/** Received by dialogs when the user activates the window (that is,
	it gains input focus). */
#define kADMWindowActivateNotifier "ADM Activate Window Notifier"

/** Received by dialogs when the user deactivates the window (that is,
	it loses input focus). */
#define	kADMWindowDeactivateNotifier "ADM Deactivate Window Notifier"

/** Received by dialogs when the user enters a number that is greater
	than the allowed maximum or less than the allowed minimum. */
#define kADMNumberOutOfBoundsNotifier "ADM Number Out Of Bounds Notifier"

/** Received by dialogs when the user moves the window by dragging it. */
#define kADMWindowDragMovedNotifier "ADM Window Moved By Drag"

/** Received by dialogs when the user docks a frame. */
#define kADMFrameDockedNotifier "ADM Frame Docked Notifier"

/** Received by dialogs when the user undocks a frame.  */
#define kADMFrameUndockedNotifier "ADM Frame Undocked Notifier"

/** Received by dialogs with a style of \c #kADMHostDefinedDialogStyle when docks change size. */
#define kADMDocAreaChangedNotifier "ADM Document Area Changed Notifier"


	// text item notifiers
/** Received by text-edit items when the user initiates a clipboard cut operation,
	before the operation occurs. */
#define	kADMPreClipboardCutNotifier "ADM Pre Clipboard Cut Notifier"

/** Received by text-edit items after a clipboard cut operation is completed. */
#define	kADMPostClipboardCutNotifier "ADM Post Clipboard Cut Notifier"

/** Received by text-edit items when the user initiates a clipboard copy operation,
	before the operation occurs. */
#define	kADMPreClipboardCopyNotifier "ADM Pre Clipboard Copy Notifier"

/** Received by text-edit items after a clipboard copy operation is completed.  */
#define	kADMPostClipboardCopyNotifier "ADM Post Clipboard Copy Notifier"

/** Received by text-edit items when the user initiates a clipboard paste operation,
	before the operation occurs. */
#define	kADMPreClipboardPasteNotifier "ADM Pre Clipboard Paste Notifier"

/** Received by text-edit items after a clipboard paste operation is completed.  */
#define	kADMPostClipboardPasteNotifier "ADM Post Clipboard Paste Notifier"

/** Received by text-edit items when the user initiates a clipboard clear operation,
	before the operation occurs. */
#define	kADMPreClipboardClearNotifier "ADM Pre Clipboard Clear Notifier"

/** Received by text-edit items after a clipboard clear operation is completed.  */
#define	kADMPostClipboardClearNotifier "ADM Post Clipboard Clear Notifier"

/** Received by text-edit items when the user initiates selection-change operation,
	before the operation occurs. */
#define kADMPreTextSelectionChangedNotifier "ADM Pre Selection Change Notification"

/** Received by text-edit items after a selection-change operation is completed. */
#define kADMTextSelectionChangedNotifier "ADM Text Selection Change Notification"


// [cpaduan] 12/04/00: new notifiers for undo/redo
/** Received by text-edit items when the user initiates a clipboard redo operation,
	before the operation occurs.  */
#define	kADMPreClipboardRedoNotifier "ADM Pre Clipboard Redo Notifier"

/** Received by text-edit items after a clipboard redo operation is completed. */
#define	kADMPostClipboardRedoNotifier "ADM Post Clipboard Redo Notifier"

/** Received by text-edit items when the user initiates a clipboard undo operation,
	before the operation occurs.  */
#define	kADMPreClipboardUndoNotifier "ADM Pre Clipboard Undo Notifier"

/** Received by text-edit items after a clipboard undo operation is completed. */
#define	kADMPostClipboardUndoNotifier "ADM Post Clipboard Undo Notifier"


// =============================================================================
//		* ADM Notifier Suite
// =============================================================================

/** Notifier suite name */
#define kADMNotifierSuite "ADM Notifier Suite"
/** Notifier suite version */
#define kADMNotifierSuiteVersion2 2

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides access to high-level user-interaction events,
	such as the value of an item changing. To work with low-level events,
	such as mouse-up, mouse-down, and mouse-move, use the \c #ADMTrackerSuite2.

	You can modify or replace the default behavior of a dialog or dialog
	item by providing your own handler, in the form of a notification callback
	procedure, \c #ADMItemNotifyProc, associated with the dialog or item. See
	\c #ADMDialogSuite10::SetNotifyProc() and \c #ADMItemSuite9::SetNotifyProc().

	The behavior of list entries (\c #ADMEntryRef or \c #ADMListEntryRef) is handled
	by the notifier callback (\c #ADMEntryNotifyProc) of the containing list
	(\c #ADMListRef or	\c #ADMHierarchyListRef). See \c #ADMListSuite4::SetNotifyProc()
	and \c #ADMHierarchyListSuite5::SetNotifyProc().

	The notification object, \c #ADMNotifierRef, provides the event context. Use
	the functions  in this suite in your notification callback procedure to
	access information about the event that caused the notification.

	To invoke the default behavior of a dialog, item, or list, call that object's
	default notification handler from within your handler; for example,
	\c #ADMItemSuite9::DefaultNotify().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMNotifierSuite and \c #kADMNotifierSuiteVersion2.
	*/
typedef struct ADMNotifierSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// notifier context

	/** Retrieves the dialog item in which the event occurred.
			@param inNotifier The notifier object.
			@return The item object.
		*/
	ADMItemRef ADMAPI (*GetItem)(ADMNotifierRef inNotifier);
	/** Retrieves the dialog in which the event occurred.
			@param inNotifier The notifier object.
			@return The dialog object.
		*/
	ADMDialogRef ADMAPI (*GetDialog)(ADMNotifierRef inNotifier);

	// notifier type

	/** Reports whether a notification is of a specified type.
			@param inNotifier The notifier object.
			@param inNotifierType The type constant's identification string. See \c ADMNotifier.h.
			@return True if the notification is of the given type, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsNotifierType)(ADMNotifierRef inNotifier, const char* inNotifierType);
	/** Retrieves the type of a notification, which identifies the event that triggered it.
			@param inNotifier The notifier object.
			@param outNotifierType [out] A buffer in which to return the
				type constant's identification string. See \c ADMNotifier.h.
			@return Nothing.
		*/
	void ADMAPI (*GetNotifierType)(ADMNotifierRef inNotifier, char* outNotifierType,
				ADMUInt32 inMaxLength);

	// notifier flags

	/** Use from within a clipboard operation to abort it. When called for
		a pre-action notification, this call is followed by a post-action
		notification.
			@param inNotifier The notifier object.
			@param inSkip True to skip the next clipboard operation specified by
				the notifier.
			@return Nothing.
		*/
	void ADMAPI (*SkipNextClipboardOperation)(ADMNotifierRef inNotifier, ADMBoolean inSkip);

}
ADMNotifierSuite2;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMNotifierOld__
#ifdef MAC_ENV
#include "ADMNotifierOld.h"
#else
#include ".\Legacy\ADMNotifierOld.h"
#endif
#endif


// -----------------------------------------------------------------------------

#endif	// __ADMNotifier__
