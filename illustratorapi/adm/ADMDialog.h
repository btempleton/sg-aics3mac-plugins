/*******************************************************************************
*
* ADMDialog.h -- ADM Dialog Suite
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
* Started by Dave Lazarony, 10 Mar 1996
*
********************************************************************************/

/** @file ADMDialog.h ADM Dialog Suite */

#ifndef __ADMDialog__
#define __ADMDialog__

#ifndef __ADMItem__
#include "ADMItem.h"
#endif

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __SPInterface__
#include "SPInterf.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// Mac OS headers #define GetItem, but we want to use it as a name.
#ifdef GetItem
#undef GetItem
#endif


// -----------------------------------------------------------------------------
//	Create custom item message.

/** @ingroup Callers
	Caller for Adobe Dialog Manager (ADM). See \c #ADMDialogSuite10. */
#define kADMCaller "Adobe Dialog Manager"

/** @ingroup Selectors
	A custom item is being created. Used for dialog item types that do
 	not correspond to known ADM item types (such as
 	\c #kADMDialType, kADMFrameType, and so on.)

	The message, of type \c #ADMCreateCustomItemMessage, contains
	information about the type and location of the item. */
#define kADMCreateCustomItem "Create Custom Item"

/** A message that identifies a user selection in response
	to ADM notifications for customized control items.
	See \c #ADMNotifierSuite2. */
struct ADMCreateCustomItemMessage
{
	/** The message data. */
	SPMessageData d;
	/** The dialog object in which the event occurred. */
	ADMDialogRef dialog;
	/** The custom item identifier. */
	ADMInt32 itemID;
	/** The custom item type */
	ADMItemType itemType;
	/** The bounding box for the location of the item,
		relative to the containing dialog. */
	ADMRect boundsRect;
	/** The initialization callback procedure that was passed to
		the creation function. */
	ADMItemInitProc initProc;
	/** Developer-defined data passed to the callback. */
	ADMUserData data;
	/** The custom item object. */
	ADMItemRef item;
};


// -----------------------------------------------------------------------------
//	Dialog options (for Create() call).
//	Options above 1L << 28 are reserved for internal use.

/** Dialog creation option: Shows the cycle button for a tabbed dialog.

	This is for palettes that support a zoom cycle state. The cycle
	button allows you to cycle for different palette sizes (states) by
	clicking the cycle button instead of double clicking the drag bar
	or tab. The cycle button is a small pair of up and down arrows
	drawn before the tab title. The Gradient palette is an example.*/
#define kADMTabbedDialogShowsCycleOption (1L << 0)

/** Modal dialog creation option: Allows modal dialogs to pass mouse down events
	through to the developer-defined dialog tracker.
	See \c #ADMDialogSuite10::SetTrackProc(). */
#define kADMPassMouseDownEventInModalDialogOption (1L << 1)

/**  Internal. */
#define kReservedForUseByCustomResourcesOption (1L << 2)

/** Dialog creation option: Keypad Enter key does not activate the default item. */
#define kADMKeypadEnterNotDefault (1L << 3)

/** Dialog creation option: Reduces flicker during dialog creation
	by hiding components as they are created.  */
#define kADMCreateDialogItemsHiddenByDefault (1L << 4)

/** Dialog creation option: Uses Roman font for all items in the dialog,
	except where explicitly overridden for an item by
	the \c #kADMIgnoreRomanFontForcing creation option, or with
	\c #ADMItemSuite9::IgnoreForceRoman(). */
#define kADMForceRomanFontForDialog (1L << 5)

/** Dialog creation option: (Mac OS only) Sends enter events
	(Return key and keypad Enter) to a modal dialog's tracker before
	activating the OK behavior, and prevents that behavior if the
	tracker returns true. See \c #ADMDialogSuite10::SetTrackProc().
	By default, enter events cause text item trackers to commit their text
	and return true, so this option normally prevents the "OK" behavior
	when Enter is pressed within a text item. For modal dialogs. */
#define kADMTrackEnterBeforeDialogDoesOK	(1L << 6)

/** Modal dialog creation option: Shows a close box in the top right corner
	of modal dialogs. Off by default.
	An application user preference can set this behavior for all
	dialogs.  */
#define kADMModalDialogHasPaletteSystemControlsOption (1L << 7)

/** Dialog creation option: (Mac OS X only) Causes a popup control dialog of type
	\c #kADMPopupControlDialogStyle to be implemented as a floating window,
	which makes it layer correctly in palettes. */
#define kADMCreatePopupDialogAsFloatingClassOption (1L << 8)

/** Dialog creation option: For a no-close floating dialog
	(type \c #kADMNoCloseFloatingDialogStyle), attaches all
	properties of a typical toolbar to the dialog. */
#define kADMToolbarDialogOption (1L << 9)

/** Dialog creation option: For a floating dialog
	(type \c #kADMFloatingDialogStyle), causes the dialog to reside in
	the same Z-space as document window dialogs. */
#define kADMDocumentWindowLayerDialogOption	(1L << 10)

/** Dialog creation option: For a floating dialog
	(type \c #kADMFloatingDialogStyle), causes the dialog to reside in
	the same Z-space as \c #kADMTabbedFloatingDialogStyle dialogs. */
#define kADMPaletteLayerDialogOption	(1L << 11)

// -----------------------------------------------------------------------------
/** Dialog group creation option: When set, the lower 16 bits of the \c options
	flag indicate the specific base ID for item relocation. Otherwise,
	items are renumbered with the dialog identifier as a base and the
	lower 16 bits of the \c options flag are ignored.
	See \c #ADMDialogSuite10::CreateGroupInDialog().*/
#define kADMDefineItemRelocationOption (1L << 16)

// -----------------------------------------------------------------------------
/** Types of dialogs, used in \c #ADMDialogSuite10::Create() and \c #ADMDialogSuite10::Modal().
	The type controls the behavior and appearance, including which predefined
	items are automatically added.

	You can modify the type with \c #ADMDialogSuite10::SetDialogStyle() */
enum ADMDialogStyle
{
	/** Modal dialog, disallows event detection in other
		windows while the dialog is shown. Activates the application
		when invoked. Compare \c #kADMNoAppActivateModalDialogStyle. */
	kADMModalDialogStyle = 0,

	/** Alert dialog. A modal dialog used to display a text message,
		specified in the dialog's text property. It contains only predefined
		standard dialog items. */
	kADMAlertDialogStyle = 1,

	/** Floating, non-modal dialog, or palette. can be moved by user, drag bar on top.  */
	kADMFloatingDialogStyle = 2,
	/** Palette with a table that can be moved by user, drag bar on top.
		Tabbed palettes can be docked together. See \c #ADMDialogGroupSuite6. */
	kADMTabbedFloatingDialogStyle = 3,

	/** Palette that allows resize, can be moved by user, drag bar on top.  */
	kADMResizingFloatingDialogStyle = 4,

	/** Palette with a tab that allows resize, can be moved by user, drag bar on top.
		Tabbed palettes can be docked together. See \c #ADMDialogGroupSuite6. */
	kADMTabbedResizingFloatingDialogStyle = 5,

	/** Popup palette. Cannot be moved by user. */
	kADMPopupDialogStyle = 6,

	/** Palette that cannot be closed by user (toolbar). */
	kADMNoCloseFloatingDialogStyle = 7,

	/** System alert dialog. A modal dialog used to display a text message,
		specified in the dialog's text property. It contains only predefined
		standard dialog items. This differs from \c #kADMAlertDialogStyle
 		in Windows in that it always has the system buttons regardless of the
		state of \c #kADMModalDialogHasPaletteSystemControlsOption settings.  */
	kADMSystemAlertDialogStyle = 8,

	/** A popup dialog containing a UI control, associated with a dialog item of type
		\c #kADMPopupControlType. See \c #ADMItemSuite9::SetPopupDialog(). */
	kADMPopupControlDialogStyle = 9,

	/** Modal dialog that allows resize.  */
	kADMResizingModalDialogStyle = 10,

	/** Left-side palette (drag bar is on left side instead of top). */
	kADMLeftSidedFloatingDialogStyle = 11,

	/** Left-side palette that cannot be closed by user (toolbar).*/
	kADMLeftSidedNoCloseFloatingDialogStyle = 12,			// Implementation of this variant was completed to support the Control Palette

	/** @deprecated Untitled palette. Deprecated, do not use. */
	kADMNoTitleDockFloatingDialogStyle = 13,  // deprecated -cquartet 2005.11

	/** Palette with a tab that can contain tree controls.
		Tabbed palettes can be docked together. See \c #ADMDialogGroupSuite6. */
	kADMTabbedHierarchyFloatingDialogStyle = 14,

	/** Palette with a tab that can contain tree controls, and allows resize.
		Tabbed palettes can be docked together. See \c #ADMDialogGroupSuite6. */
	kADMTabbedResizingHierarchyFloatingDialogStyle = 15,

	/** Palette with non-hierarchical popup menu, that allows resize. */
	kADMResizingPopupPaletteDialogStyle = 16,

	/** Palette with non-hierarchical popup menu. */
	kADMPopupPaletteDialogStyle = 17,

	/** Palette with hierarchical popup menu */
	kADMHierarchyPopupPaletteDialogStyle = 18,

	/** Palette with hierarchical popup menu, that allows resize. */
	kADMResizingHierarchyPopupPaletteDialogStyle = 19,

	/** A modal dialog that does not activate the application when invoked.  */
	kADMNoAppActivateModalDialogStyle = 20,
	/** A platform-specific host-created dialog.*/
	kADMHostDefinedDialogStyle = 65536,

	/** Internal */
	kADMDummyDialogStyle = 0xFFFFFFFF
};


// -----------------------------------------------------------------------------
//	Standard dialog item IDs

/** Item identifier constants that provide access to item objects according
	to their usage in the dialog. See \c #ADMDialogSuite10::GetItem.
 */
enum ADMStandardDialogItemID
{
	/** Specify as the item ID on creation to generate a unique identifying number for the item.
		@see \c #ADMItemSuite9::Create(),
			\c #ADMDialogSuite10::CreateItem(),
			\c #ADMDialogSuite10::CreateNestedItem()*/
	kADMUniqueItemID = 0,
	/** The first item in the tab order. */
	kADMFirstItemID = -1,
	/** The last item in the tab order. */
	kADMLastItemID = -2,
	/** The default item. */
	kADMDefaultItemID = -3,
	/** The cancel button. */
	kADMCancelItemID = -4,
	/** The menu item for a palette's popup or flyout menu. */
	kADMMenuItemID = -5,
	/** The resize drag area. */
	kADMResizeItemID = -6,
	/** Internal */
	kADMPrivateUniqueItemID = -7,	// dhearst 1/31/01 - changed from -10 to kADMFirstUnusedPrivateItemID.
									// Part of fix for EveParser Bug (ABTS #409214)
	// The constant kADMFirstUnusedPrivateItemID should ALWAYS be one more negative than the last
	// non-Dummy value in this enum. If you add more enum values, be sure to update kADMFirstUnusedPrivateItemID.
	/** Internal  */
	kADMFirstUnusedPrivateItemID = -8,
	kADMDummyItemID = 0x7FFFFFFF
};

/** The toolbar mode for dialogs with \c #kADMToolbarDialogOption set.
	Use \c #ADMDialogSuite10::SetToolbarSizeForMode() to set the
	pixel dimensions for each mode to be used, and
	\c #ADMDialogSuite10::SetToolbarIcon() to associate an icon with each mode.
	Set the preferred mode with \c #ADMDialogSuite10::SetToolbarMode(). */
enum ADMToolbarMode
{
	/** Display vertically in a wide format. */
	ADMToolBarMode_VerticalWide,
	/** Display vertically in a narrow format. */
	ADMToolBarMode_VerticalNarrow,
	/** Display horizontally. */
	ADMToolBarMode_Horizontal,

	ADMToolBarMode_Dummy = 0xFFFFFFFF
};

/** Associates an \c #ADMToolbarMode with an icon, which
	is automatically drawn at the top of toolbars for dialogs
	that have \c #kADMToolbarDialogOption set.
	A normal and a rollover icon can be associated with each \c #ADMToolbarMode.
	Rollover icons are not required.
	@see \c #ADMDialogSuite10::SetToolbarIcon() */
enum ADMToolbarIconType
{
	/** Set the normal icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_VerticalWide. */
	ADMToolbarIconType_VerticalWideNormal,
	/** Set the rollover icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_VerticalWide.*/
	ADMToolbarIconType_VerticalWideRollover,
	/** Set the normal icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_VerticalNarrow.*/
	ADMToolbarIconType_VerticalNarrowNormal,
	/** Set the rollover icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_VerticalNarrow.*/
	ADMToolbarIconType_VerticalNarrowRollover,
	/** Set the normal icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_Horizontal.*/
	ADMToolbarIconType_HorizontalNormal,
	/** Set the rollover icon associated with
		\c #ADMToolbarMode::ADMToolBarMode_Horizontal.*/
	ADMToolbarIconType_HorizontalRollover,

	ADMToolbarIconType_Dummy = 0xFFFFFFFF
};

// -----------------------------------------------------------------------------
//	Dialog error codes

/** @ingroup Errors ADM error, see \c #ADMDialogSuite10 */
#define kDialogResourceNotFoundError 'DLOG'
			// error data == resID

/** @ingroup Errors ADM error, see \c #ADMDialogSuite10.
	Error data is the resource identifier. */
#define kDialogItemListResourceNotFoundError 'DITL'

/**  @ingroup Errors ADM error, see \c #ADMDialogSuite10.
	Error data is the resource identifier. */
#define kCouldntCreateItemError '!itm'

// -----------------------------------------------------------------------------
//	Developer-provided callback procedure function prototypes

// ADMItemRef and ADMDialogRef are declared in ADMTypes.h

/** Prototype for \c #ADMCreateCustomItemMessage::initProc.
	Your function should initialize the new dialog.
		@param inDialog The dialog being created.
		@return An ADM error code.
	*/
typedef ADMErr ADMAPI (*ADMDialogInitProc)(ADMDialogRef inDialog);

/** Prototype for a drawing procedure associated with a custom dialog.
	Your function can completely draw a custom dialog, or call the default
	drawer to draw the basic appearance, then modify it.
		@param inDialog The dialog object.
		@param inDrawer The drawing object.
		@return Nothing.
		@see \c #ADMDialogSuite10::SetDrawProc()
	*/
typedef void ADMAPI (*ADMDialogDrawProc)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

/** Prototype for an event tracking procedure associated with a custom dialog.
	Your function can access the event from the tracking object, and respond as
	desired.
	Use \c #ADMDialogSuite10::SetMask() to specify which events are sent to the tracker.
	You can call the default tracker from this function. If you do not call the
	default tracker from your custom tracker, call \c #ADMTrackerSuite2::Abort()
	 to exit the tracking loop.

	You might use a custom tracker, for example, to check for a modifier key,
	save the modifier state, and then call the default tracker.
	The default tracker returns true if the dialog is to be notified.
	Your dialog notifier procedure would act on the saved modifier state.

		@param inDialog The dialog object.
		@param inTracker The tracking object.
		@return True to send a notification to the dialog when the mouse button
			is released, or to indicate that a keystroke event was handled.
			False to send no notification, or indicate that a keystroke event
			was not handled.
		@see \c #ADMDialogSuite10::SetTrackProc()
	*/
typedef ADMBoolean ADMAPI (*ADMDialogTrackProc)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

/** Prototype for a notification procedure associated with a custom dialog.
	Your function can completely implement the dialog's behavior, or call the default
	notify function for the standard behavior, before or after performing some additional action.
		@param inDialog The dialog object.
		@param inNotifier The notification object.
		@return Nothing.
		@see \c #ADMDialogSuite10::SetNotifyProc()
	*/
typedef void ADMAPI (*ADMDialogNotifyProc)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);

/** Prototype for a termination procedure associated with a custom dialog.
	Your function should clean up any data associated with the dialog before it is destroyed.
		@param inDialog The dialog object.
		@return Nothing.
		@see \c #ADMDialogSuite10::SetDestroyProc()
	*/
typedef void ADMAPI (*ADMDialogDestroyProc)(ADMDialogRef inDialog);

/** Prototype for a timer procedure associated with a custom dialog.
	Your function performs the scheduled action after the timer's delay
	period is up.
		@param inDialog The dialog object.
		@param inTimerID The timer object.
		@return Nothing.
		@see \c #ADMDialogSuite10::CreateTimer()
	*/
typedef ADMBoolean ADMAPI (*ADMDialogTimerProc)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

/** Prototype for a timer abort procedure associated with a custom dialog.
	Your function should clean up data associated with the scheduled action.
		@param inDialog The dialog object.
		@param inTimerID The timer object.
		@param inAbortAction The action that triggered the abort.
		@return Nothing.
		@see \c #ADMDialogSuite10::CreateTimer()
	*/
typedef void ADMAPI (*ADMDialogTimerAbortProc)(ADMDialogRef inDialog, ADMTimerRef inTimerID,
			ADMAction inAbortAction);


// =============================================================================
//		* ADM Dialog Suite
// =============================================================================

#define kADMDialogSuite "ADM Dialog Suite"
#define kADMDialogSuiteVersion10 10

#define kADMDialogSuiteVersion kADMDialogSuiteVersion10
typedef struct ADMDialogSuite10 ADMDialogSuite;

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite allows you to create and destroy custom ADM dialogs, to configure and query
	dialogs, to invoke them, to manipulate their location and appearance, and to set and access
	their contents.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMDialogSuite and \c #kADMDialogSuiteVersion.
*/
struct ADMDialogSuite10
{
	// dialog creation

	/** Creates a new non-modal dialog object, which can be displayed or
		hidden with	\c #Show(), or a modal dialog that can be invoked later
		with \c #DisplayAsModal().
			@param inPluginRef This plug-in object.
			@param inName The unique name of the new dialog. By convention,
				use a leading prefix of your company’s name, as in "MyCompanyDialogxxxx".
			@param inDialogID The resource identifier for a caller-created dialog resource.
			@param inDialogStyle The type of dialog, a dialog style constant.
			@param inInitProc A developer-defined initialization callback.
			@param inUserData Developer-defined data to pass to the initialization callback.
			@param inOptions Creation options, a logical OR of the following constants:
				<br> \c #kADMTabbedDialogShowsCycleOption
				<br> \c #kADMKeypadEnterNotDefault
				<br> \c #kADMCreateDialogItemsHiddenByDefault
				<br> \c #kADMForceRomanFontForDialog
				<br> \c #kADMTrackEnterBeforeDialogDoesOK (Mac OS only)
				<br> \c #kADMToolbarDialogOption
				<br> \c #kADMPassMouseDownEventInModalDialogOption	(modal only)
				<br> \c #kADMModalDialogHasPaletteSystemControlsOption (modal only)
			@return The new dialog object.
		*/
	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	/** Creates and invokes a modal dialog. When active, no other windows respond to user input.
		This function does not return until the dialog is dismissed.
			@note For a complex modal dialog that is used frequently, create it with \c #Create(), then
				invoke it with \c #DisplayAsModal(), to avoid creation overhead on each invocation.
			@param inPluginRef This plug-in object.
			@param inName The unique name of the new dialog. By convention,
				use a leading prefix of your company’s name, as in "MyCompanyDialogxxxx".
			@param inDialogID The resource identifier for a caller-created dialog resource.
			@param inDialogStyle The type of dialog, a dialog style constant.
				This must be one of the modal styles:
				<br> \c #kADMModalDialogStyle
				<br> \c #kADMAlertDialogStyle
				<br> \c #kADMSystemAlertDialogStyle
				<br> \c #kADMResizingModalDialogStyle
				<br> \c #kADMNoAppActivateModalDialogStyle
			@param inInitProc A developer-defined initialization callback.
			@param inUserData Developer-defined data to pass to the initialization callback.
			@param inOptions Creation options, a logical OR of the following constants:
				<br> \c #kADMPassMouseDownEventInModalDialogOption
				<br> \c #kADMKeypadEnterNotDefault
				<br> \c #kADMCreateDialogItemsHiddenByDefault
				<br> \c #kADMForceRomanFontForDialog
				<br> \c #kADMTrackEnterBeforeDialogDoesOK (Mac OS only)
				<br> \c #kADMModalDialogHasPaletteSystemControlsOption
			@return The item identifier of the item used to dismiss the dialog.
		 */
	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** Creates and invokes a popup dialog (type \c #kADMPopupControlDialogStyle)
		that is associated with a dialog item of type \c #kADMPopupControlType.
		This function does not return until the dialog is dismissed.
			@param inPluginRef This plug-in object.
			@param inName The unique name of the new dialog. By convention,
				use a leading prefix of your company’s name, as in "MyCompanyDialogxxxx".
			@param inDialogID The resource identifier for a caller-created dialog resource.
			@param inDialogStyle The type of dialog, \c #kADMPopupControlDialogStyle.
			@param inInitProc A developer-defined initialization callback.
			@param inUserData Developer-defined data to pass to the initialization callback.
			@param inOptions Creation options, can be:<br>
				\c #kADMCreatePopupDialogAsFloatingClassOption (Mac OS X only)
			@return The item identifier of the item used to dismiss the dialog.
		*/
	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	/** Invokes a modal dialog that has been created with \c #Create().
		While the dialog is active, no other windows respond to user input.
		This function does not return until the dialog is dismissed.
			@param inDialog The dialog object.
			@return The item identifier of the item used to dismiss the dialog.
			@see \c #Create(), \c #Modal(), \c #PopupModal(), \c #DisplayAsPopupModal()
		*/
	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	/** Deletes a dialog object, calling its associated \c #ADMDialogDestroyProc
		first.

		Modal dialogs created with \c #Modal() are destroyed automatically when
		they are dismissed.	All dialogs are destroyed automatically on application
		shutdown. You must call this to destroy any non-modal dialogs,
		or modal dialogs created with \c #Create(), if your plug-in shuts down
		before the application does (typically in response to a plug-in shutdown
		message) or when you are finished with them (typically in response to
		an ADM close-window message).

			@note Must not be called twice for the same dialog.

			@param inDialog The dialog object.
			@return Nothing.
		*/
	void ADMAPI (*Destroy)(ADMDialogRef inDialog);

	// dialog draw proc

	/** Associates a dialog object with a developer-defined drawing procedure.
			@param inDialog The dialog object.
			@param inDrawProc The drawing procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);

	/** Retrieves the developer-defined drawing procedure from a dialog.
			@param inDialog The dialog object.
			@return The drawing procedure.
		*/
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);

	/** Calls the default drawing procedure for a dialog from within a
		developer-defined custom drawing procedure. Typically used to draw the
		basic appearance before modifying it.
			@param inDialog The dialog object.
			@param inDrawer The drawing object.
			@return Nothing. */
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc

	/** Associates a dialog object with a developer-defined event tracking procedure.
			@param inDialog The dialog object.
			@param inTrackProc The tracking procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);

	/** Retrieves the developer-defined event tracking procedure from a dialog.
			@param inDialog The dialog object.
			@return The tracking procedure.
		*/
 	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);

	/** Calls the default event tracking procedure for a dialog from within a
		developer-defined custom tracking procedure.
			@param inDialog The dialog object.
			@param inTracker The tracking object.
			@return True to send a notification to the dialog when the mouse button
				is released, or to indicate that a keystroke event was handled.
				False to send no notification, or indicate that a keystroke event
				was not handled.
			*/
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	/** Sets the event mask for a dialog. This determines which events are
		received by the dialog's event tracker.
			@param inDialog The dialog object.
			@param inMask The mask object.
			@return Nothing. */
	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);

	/** Retrieves the event mask from a dialog.	Only allowed events are
		received by the dialog's event tracker.
			@param inDialog The dialog object.
			@return The mask object.
		*/
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	/** Associates a dialog object with a developer-defined notification-handling procedure.
			@param inDialog The dialog object.
			@param inNotifyProc The notification procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);

	/** Retrieves the developer-defined notification-handling procedure from a dialog.
			@param inDialog The dialog object.
			@return The notification procedure.
		*/
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);

	/** Calls the default notification-handling procedure for a dialog from within a
		developer-defined custom notification procedure. Use to get standard
		behaviors, such as resizing.
			@param inDialog The dialog object.
			@param inNotifier The notification object.
			@return Nothing. */
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);

	/** Sends a notification to a dialog.
			@param inDialog The dialog object.
			@param inNotifierType The notification type constant: see \c ADMNotifier.h.
			@return Nothing. */
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	/** Associates a dialog object with developer-defined notification data.
			@param inDialog The dialog object.
			@param inUserData The notification data.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);

	/** Retrieves the developer-defined notification data from a dialog.
			@param inDialog The dialog object.
			@return The notification data.
		*/
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	/** Associates a dialog object with a developer-defined termination procedure.
			@param inDialog The dialog object.
			@param inDestroyProc The termination procedure.
			@return Nothing.
			@see \c #Destroy()
		*/
	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);

	/** Retrieves the developer-defined termination procedure from a dialog.
			@param inDialog The dialog object.
			@return The termination procedure.
		*/
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer

	/** Creates a dialog timer, which allows you to schedule an action
		for the dialog. The action can
		make use of developer-defined data associated with the dialog; see
		\c #GetUserData().
			@param inDialog The dialog object.
			@param inMilliseconds The delay, in milliseconds, from when this
				call is executed until the action is called.
			@param inAbortMask Events that cancel the scheduled action, if
				they occur before the timer expires. See \c #AbortTimer().
				A logical OR of \c #ADMAction constants.
			@param inTimeProc The procedure that implements the scheduled action.
			@param inAbortProc The procedure to call if the timer is aborted.
			@param inOptions Not used; pass 0.
			@return The timer object.
		*/
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);

	/** Cancels a scheduled action associated with a dialog. It is used if an event
		specified by the \c inAbortMask of \c #CreateTimer() occurs, or if
		you destroy the dialog before the timer expires.
			@param inDialog The dialog object.
			@param inTimerID The timer object containing the scheduled action.
			@return Nothing.
		*/
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data

	/** Associates developer-defined data with a dialog, which can be used
		in developer-defined callbacks and actions scheduled with \c #CreateTimer().
			@param inDialog The dialog object.
			@param inUserData The developer-defined data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);

	/** Retrieves developer-defined data from a dialog.
			@param inDialog The dialog object.
			@return The developer-defined data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	/** Retrieves the unique name of a dialog, as assigned on creation.
			@param inDialog The dialog object.
			@return The name string.
		*/
	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);

	/** Retrieves the unique identifier of the resource used to create a dialog.
			@param inDialog The dialog object.
			@return The unique identifier. */
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);

	/** Retrieves a reference to the plug-in that defined a dialog.
			@param inDialog The dialog object.
			@return The plug-in object. */
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);

	/** Retrieves the window used for dialog. This is a platform-specific
		reference you can use to draw directly to the window with
		platform-specific code.
			@param inDialog The dialog object.
			@return The window object. */
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	/** Modifies the type of a dialog.
			@param inDialog The dialog object.
			@param inDialogStyle The new dialog style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);

	/** Retrieves the type of a dialog.
			@param inDialog The dialog object.
			@return The dialog style constant.
		*/
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors

	/** Turns the visibility state on or off for a dialog. If it is a tabbed
		dialog grouped with others, the entire group is affected.
			@param inDialog The dialog object.
			@param inShow True to make the dialog visible, false to hide it.
			@return Nothing.
			@see \c #IsVisible(), \c #IsDialogTabHidden()
		*/
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);

	/** Reports whether a dialog is currently in the visible state.
		If the dialog is part of a tabbed group but is not the frontmost tab,
		it is not considered visible. This means the return value of this
		function does not correspond exactly with the state set by \c #Show().
		A dialog can also be in the visible state, and not be shown on screen,
		because all floating dialogs have been hidden, as with the Tab key;
		see \c #IsDialogTabHidden().
			@param inDialog The dialog object.
			@return True if the dialog is currently visible, and, if it is part of
				a tabbed dialog group, is the frontmost tab of its group.
				False if it is not visible, or is not the frontmost tab of its group.
		*/
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);

	/** Reports whether a dialog is currently hidden because all dialogs are
		toggled off.
			@param inDialog The dialog object.
			@return True if the dialog is not shown, regardless of visibility state.
			@see \c #ADMDialogGroupSuite6::ToggleAllFloatingDialogs()
		*/
	ADMBoolean ADMAPI (*IsDialogTabHidden)(ADMDialogRef inDialog);

	/** Enables or disables a dialog. A disabled dialog is disabled and
		does not respond to any user input. All floating dialogs are automatically
		disabled when a modal dialog is active.
			@param inDialog The dialog object.
			@param inEnable True to enable the dialog, false to disable it.
			@return Nothing.
		*/
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);

	/** Reports whether a dialog is currently in the enabled state.
			@param inDialog The dialog object.
			@return True if the dialog is currently enabled, false if it is disabled.
			@see \c #Enable()
		*/
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);

	/** Activates or deactivates a floating dialog.	The active dialog is the
		frontmost dialog, which has the input focus. When a modal dialog is
		active, no floating dialogs can become active.
			@param inDialog The dialog object.
			@param inActivate True to activate the dialog, false to deactivate it.
			@return Nothing.
		*/
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);

	/** Reports whether a floating dialog currently has the input focus.
			@param inDialog The dialog object.
			@return True if the dialog is currently active, false if it is inactive.
			@see \c #Activate()
		*/
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);

	// dialog bounds accessors

	// Set/Get*Rect functions work with pixel bounds. Bounds rectangles are in
	// screen coordinates. The absolute position of local rectangles is
	// irrelevant as they are only used to convey size.

	/** Modifies the size of a dialog by setting its bounds relative to its own origin.
			@param inDialog The dialog object.
			@param inLocalRect The new bounding box size in pixels.
			@return Nothing
			@see \c #Size()
		*/
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);

	/** Retrieves the size of a dialog.
			@param inDialog The dialog object.
			@param outLocalRect [out] A buffer in which to return the local
				 bounding box size in pixels.
			@return Nothing
		*/
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);

	/** Modifies the size and position of a dialog.
			@param inDialog The dialog object.
			@param inBoundsRect The new bounding box, using screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);

	/** Retrieves the size and position of a dialog.
			@param inDialog The dialog object.
			@param outBoundsRect [out] A buffer in which to return the bounding box
				with screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);

	/** Retrieves the inner bounds of a dialog, where items should be created.
			@note This is generally the same as \c #GetBoundsRect(), but if you find
				that is not returning the correct result, use this.
			@param inDialog The dialog object.
			@param outBoundsRect [out] A buffer in which to return the bounding box
				with screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*GetMainViewRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);

	/** Modifies the position of a dialog, relative to the screen origin.
			@param inDialog The dialog object.
			@param inHorizPosition The new horizontal coordinate, in pixels.
			@param inVertPosition The new vertical coordinate, in pixels.
			@return Nothing
		*/
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);

	/** Modifies the size of a dialog.
			@param inDialog The dialog object.
			@param inWidth The new width in pixels.
			@param inHeight The new height in pixels.
			@return Nothing
			@see \c #GetLocalRect()
		*/
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	/** Modifies the preferred constrained and unconstrained sizes of a dialog.
			\li The constrained size is used when a dialog is frame docked.
			\li The unconstrained size is used when the dialog is floating.

		This function is useful for	restoring saved workspaces. Compare
		\c #SetBoundsRect() and \c #SetLocalRect(), which modify both
		preferred sizes at once.
			@param inDialog The dialog object.
			@param inConstrained Optional. The X and Y dimensions in pixels for the constrained size, or
				\c NULL to leave the current value unchanged.
			@param inUnconstrained The X and Y dimensions in pixels for the unconstrained size, or
				\c NULL to leave the current value unchanged.
			@return Nothing
			@see \c #GetPreferredSizes()
		*/
	void ADMAPI (*SetPreferredSizes)(ADMDialogRef inDialog, const ADMPoint *inConstrained, const ADMPoint *inUnconstrained);

	/** Retrieves the preferred constrained and unconstrained sizes of a dialog.
			@param inDialog The dialog object.
			@param outConstrained [out] Optional. A buffer in which to return the X and Y dimensions
				in pixels for the constrained size.
			@param outUnconstrained [out] Optional. A buffer in which to return the X and Y dimensions
				in pixels for the unconstrained size.
			@return Nothing
			@see \c #SetPreferredSizes()
		*/
	void ADMAPI (*GetPreferredSizes)(ADMDialogRef inDialog, ADMPoint *outConstrained, ADMPoint *outUnconstrained);

	/** Modifies the toolbar size for a given mode, for dialogs with \c #kADMToolbarDialogOption set.
			@param inDialog The dialog object.
			@param inMode The toolbar mode.
			@param inSize The X and Y dimension of the new size in pixels.
			@see \c #SetToolbarMode()
		*/
	ADMErr ADMAPI (*SetToolbarSizeForMode)(ADMDialogRef inDialog, ADMToolbarMode inMode, const ADMPoint &inSize);

	/** Retrieves the toolbar size for a given mode, for dialogs with \c #kADMToolbarDialogOption set.
			@param inDialog The dialog object.
			@param inMode The toolbar mode.
			@param outSize [out] A buffer in which to return the X and Y dimensions
				in pixels
		*/
	ADMErr ADMAPI (*GetToolbarSizeForMode)(ADMDialogRef inDialog, ADMToolbarMode inMode, ADMPoint &outSize);

	// coordinate system transformations

	/** Transforms a point from local coordinates for a dialog to screen coordinates.
			@param inDialog The dialog object.
			@param ioPoint [in, out] A buffer in which to pass the point in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);

	/** Transforms a point from screen coordinates to local coordinates for a dialog.
			@param inDialog The dialog object.
			@param ioPoint [in, out] A buffer in which to pass the point in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);

	/** Transforms a rectangle from local coordinates for a dialog to screen coordinates.
			@param inDialog The dialog object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	/** Transforms a rectangle from screen coordinates to local coordinates for a dialog.
			@param inDialog The dialog object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests

	/** Marks a dialog as being in need of redrawing. Use \c #Update() to force
		immediate redrawing.
			@param inDialog The dialog object.
			@return Nothing
			@see Update()
		*/
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);

	/** Marks an area within a dialog as being in need of redrawing.
		Use \c #Update() to force immediate redrawing.
			@param inDialog The dialog object.
			@param inInvalRect The rectangle, in local coordinates, relative to the dialog.
			@return Nothing
			@see Update()
		*/
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);

	/** Redraws a dialog or any area within it that is both visible and has
		been marked as needing update.
			@param inDialog The dialog object.
			@return Nothing
			@see \c #Invalidate(), \c #InvalidateRect()
		*/
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	/** Sets the cursor shape for a dialog. This shape is used when the cursor
		position is within the dialog bounds. This plug-in owns
		the cursor ID until it is reset to the default arrow.
			@param inDialog The dialog object.
			@param inPluginRef This plug-in, which owns the cursor ID until it is
				reset to the default arrow.
			@param inCursorID One of the predefined cursor constants. See @ref AdmResources
			@return True on success.
		*/
	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	/** Retrieves the cursor shape for a dialog.
			@param inDialog The dialog object.
			@param inPluginRef [out] A buffer in which to return the plug-in
				that owns the cursor ID; see \c #SetCursorID().
			@param inCursorID [out] A buffer in which to return the predefined cursor constant.
				See @ref AdmResources
			@return Nothing */
	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);

	// dialog text accessors

	/** Sets the font style for text in a dialog. The text is used as the title.
			@param inDialog The dialog object.
			@param inFont The font constant.
			@return Nothing.
		*/
	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);

	/** Retrieves the font style used for text in a dialog. The text is used as the title.
			@param inDialog The dialog object.
			@return The font constant.
		*/
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	/** Sets the text to be displayed in a dialog, using a C string.
		The text is used as the title, displayed in the window's title bar.
			@param inDialog The dialog object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);

	/** Sets the text to be displayed in a dialog, using a Unicode string.
		The text is used as the title, displayed in the window's title bar.
			@param inDialog The dialog object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetTextW)(ADMDialogRef inDialog, const ADMUnicode* inText);

	/** Retrieves the text from a dialog as a C string.
		The text is used as the title, displayed in the window's title bar.
			@param inDialog The dialog object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer.
				Use \c #GetTextLength() to determine required size.
			@return Nothing.
		*/
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);

	/** Retrieves the text from a dialog as a Unicode string.
		The text is used as the title, displayed in the window's title bar.
			@param inDialog The dialog object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer.
				Use \c #GetTextLengthW() to determine required size.
			@return Nothing.
		*/
	void ADMAPI (*GetTextW)(ADMDialogRef inDialog, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** Reports the length of a dialog's text as a C string. Use to allocate
		a buffer for \c #GetText().
			@param inDialog The dialog object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);

	/** Reports the length of a dialog's text as a Unicode string. Use to allocate
		a buffer for \c #GetTextW().
			@param inDialog The dialog object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMDialogRef inDialog);

	// dialog size constraints

	/** Sets the minimum width to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@param inWidth The minimum width in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);

	/** Retrieves the minimum width to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@return The minimum width in pixels.
		*/
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);

	/** Sets the minimum height to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@param inHeight The minimum height in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);

	/** Retrieves the minimum height to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@return The minimum height in pixels.
		*/
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);

	/** Sets the maximum width to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@param inWidth The maximum width in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);

	/** Retrieves the minimum width for a dialog.
			@param inDialog The dialog object.
			@return The maximum width in pixels.
		*/
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);

	/** Sets the maximum height to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@param inHeight The maximum height in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);

	/** Retrieves the maximum height to which a resizable dialog can be resized.
			@param inDialog The dialog object.
			@return The maximum height in pixels.
		*/
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);

	/** Sets the horizontal increment to use when a resizable dialog is resized.
		The dialog’s width is constrained to be its minimum width plus a multiple
		of the horizontal increment. By default, this is 1, making the dialog sizable to any width.

		If a dialog has items arranged by column, such as icons in a tool palette,
		set the horizontal increment to the width of a column, so that a column
		cannot be partially hidden.
			@param inDialog The dialog object.
			@param inIncrement The increment value in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);

	/** Retrieves the horizontal increment constraint for resizing a dialog.
			@param inDialog The dialog object.
			@return The increment value in pixels.
			@see \c #SetHorizontalIncrement()
		*/
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	/** Sets the vertical increment to use when a resizable dialog is resized.
		The dialog’s height is constrained to be its minimum height plus a multiple
		of the vertical increment. By default, this is 1, making the dialog sizable to any height.

		If a dialog has items arranged by row, such as a list, set the vertical
		increment to the height of a row, so that a row cannot be partially hidden.
			@param inDialog The dialog object.
			@param inIncrement The increment value in pixels.
			@return Nothing.
		*/
	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);

	/** Retrieves the vertical increment constraint for resizing a dialog.
			@param inDialog The dialog object.
			@return The increment value in pixels.
			@see \c #SetVerticalIncrement()
		*/
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors


	/** Retrieves a dialog item (a control element) from a dialog.
			@param inDialog The dialog object.
			@param inItemID The unique identifier of the item,
				or an \c #ADMStandardDialogItemID constant that identifies the
				item's role in the dialog. Use \c #kADMFirstItemID to get
				the first item for iteration.
			@return The item object.
			@see \c #GetNextItem(), \c #GetPreviousItem()
		*/
	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);

	/** Creates a dialog item (control element) in a dialog.
			@param inDialog The dialog object.
			@param inItemID The unique identifier of the new item. When creating
				all items in a dialog, use a sequence of numbers; all members of a radio-button
				group should have sequential ID numbers. When adding an item to an
				existing dialog, use the constant \c #kADMUniqueItemID to cause ADM to
				generate a unique ID.
			@param inItemType The item type constant, \c kADM*Type. See \c #kADMDialType and following.
			@param inBoundsRect The position and size of the new item, in local coordinates
				relative to the dialog's origin.
			@param inInitProc A developer-defined initialization procedure for the new item.
			@param inUserData Developer-defined data to pass to the initialization procedure.
			@param inOptions The option flags that control the new item's behavior, a
				logical OR of item create-option constants. Applicable values depend on
				control type, and include:
				<br>\c #kADMPasswordEditCreateOption, for an item of type \c #kADMPasswordTextEditType.
				<br>\c #kADMUnicodeEditCreateOption, for text-edit types.
				<br>\c #kADMDisableDragDropEditCreateOption, for text-edit types (Mac OS only)
				<br>\c #kADMHierarchyPopupCreateOption, only valid with \c #kADMPopupMenuType
					for hierarchical menus.
				<br>\c #kADMIgnoreRomanFontForcing, text-display types. Overrides the
					\c #kADMForceRomanFontForDialog	set option set for the containing dialog.
			@return The new item object.
			@see \c #CreateNestedItem(), \c #CreateGroupInDialog(), \c #ADMItemSuite9::Create()
		*/
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** Destroys a dialog item and releases associated memory, calling the item's assigned
		termination procedure first.

		All items in a dialog are automatically destroyed using this function when the
		dialog is destroyed using \c #Destroy(), or when a modal dialog is dismissed.
			@param inDialog The dialog object.
			@param inItem The item object.
			@return Nothing.
		*/
	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	/** Retrieves the item in a dialog after a given item. Use to iterate through
		all items in a dialog. Use \c #GetItem() with \c #kADMFirstItemID to get
		the first item.
			@param inDialog The dialog object.
			@param inItem The current item object.
			@return The next item object, or \c NULL if there are no more items.
			@see \c #GetPreviousItem()
		*/
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	/** Retrieves the item in a dialog before a given item. Use to iterate through
		all items in a dialog. Use \c #GetItem() with \c #kADMLastItemID to get
		the last item.
			@param inDialog The dialog object.
			@param inItem The current item object.
			@return The previous item object, or \c NULL if there are no earlier items.
			@see \c #GetNextItem()
		*/
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	/** Makes an item the default item in a dialog. This item is notified
		when the Enter key is pressed. If the item is not in the dialog,
		and if another default item has been previously set, that designation
		is removed.
			@param inDialog The dialog object.
			@param inItemID The unique identifier of the item.
			@return Nothing.
		*/
	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);

	/** Retrieves the default item for a dialog. This item is notified
		when the Enter key is pressed.
			@param inDialog The dialog object.
			@return The unique identifier of the item.
		*/
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	/** Makes an item the cancel item in a dialog. If this item is
		in the dialog, it is notified when the Esc key is pressed,
		and (in Mac OS) when Command is pressed.
			@param inDialog The dialog object.
			@param inItemID The unique identifier of the item.
			@return Nothing.
		*/
	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);

	/** Retrieves the cancel item for a dialog.	This item is notified when the
		Esc key is pressed, and (in Mac OS) when Command is pressed.
			@param inDialog The dialog object.
			@return The unique identifier of the item.
		*/
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	/** Dismisses a modal dialog programmatically. Typically called in the notification
		handler of a contained item, such as an OK or Cancel button, or in an error handler.
			@note Do not use in your initialization procedure. Instead, when an error
				occurs during initialization, return an appropriate error code; any code
				other than \c #kNoErr prevents the dialog startup.
			@param inDialog The dialog object.
			@param inModalResultID	The item identifier to return from the invocation function.
			@param inCancelling	True if the contents are to be accepted (such as
				by clicking OK), or false if the dialog is to be canceled.
			@return True if the dialog was successfully dismissed, false to
				indicate an error condition.
		*/
	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);

	// custom item types

	/** @deprecated Custom item types are no longer supported. 	*/
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	/** @deprecated Custom item types are no longer supported. */
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	/** Defines the tool-tip strings for a dialog. Tool tips are platform-specific strings
		that describe the dialog item currently under the mouse cursor. This function loads
		the strings from the platform-specific string resource and assigns them to the dialog items.
		Illustrator uses the tool title as the tool tip.
			@param inDialog The dialog object.
			@param inStringID The base string resource identifier, in Windows.
				Ignored in Mac OS, where the string list is always ’STR#’.
			@return Nothing.
			@see \c #ADMBasicSuite10::EnableToolTips() and other tool-tip functions.
		*/
	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// dialog state accessors

	/** Reports whether a floating dialog is collapsed (minimized or iconified).
		A dialog can be explicitly collapsed or expanded by sending it the
		notifier \c #kADMCollapseNotifier or \c #kADMExpandNotifier.
			@param inDialog The dialog object.
			@return True if the dialog is collapsed.
		*/
	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	/** Creates a grouping object in a dialog, an item of type \c #kADMItemGroupType.
			@param inDialog The dialog object.
			@param inPluginRef This plug-in object.
			@param inName Not used.
			@param inDialogID  The resource identifier for a developer-defined dialog resource.
			@param inInitProc A developer-defined initialization procedure for the new item.
			@param inUserData Developer-defined data to pass to the initialization procedure.
			@param inOptions Creation options, 0 or the constant \c #kADMDefineItemRelocationOption.
			@return The new item object.
			@see \c #CreateNestedItem(), \c #Create()
		*/
	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** Sets the platform-specific window for a dialog.
			@param inDialog The dialog object.
			@param inWindowRef The window object.
				\li In MacOS, the window’s \c GrafPort
				\li In Windows, an \c HWND
			@return Nothing.
		*/
	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);

	/** Sets the unique identifying name of a dialog.
			@param inDialog The dialog object.
			@param inName The name string.
			@return Nothing.
		*/
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	/** Reports whether the application context of a dialog is currently active. The OS uses the context
		to switch between different applications or processes.
			@param inDialog The dialog object.
			@return True if the application containing this dialog is not active, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

	/** Enables or disables automatic redrawing of a dialog. Disable updates to increase
		performance or reduce flicker.
			@param inDialog The dialog object.
			@param inEnableUpdate True to enable automatic update, false to disable it.
			@return Nothing.
	*/
	void ADMAPI (*SetUpdateEnabled)(ADMDialogRef inDialog, ADMBoolean inEnableUpdate);

	/** Reports whether a dialog is automatically updated.
			@param inDialog The dialog object.
			@return True if the dialog is automatically updated.
			@see \c #SetUpdateEnabled()
		*/
	ADMBoolean ADMAPI (*IsUpdateEnabled)(ADMDialogRef inDialog);

	/** Sets whether a dialog's position is constrained to make it visible on screen.
			@param inDialog The dialog object.
			@return True if the dialog is forced to be on screen.
		*/
	void ADMAPI (*SetForcedOnScreen)(ADMDialogRef ioDialog,
				ADMBoolean inForcedOnScreen);

	/** Reports whether a dialog's position is constrained to make it visible on screen.
			@param inDialog The dialog object.
			@return True if the dialog is forced to be on screen.
		*/
	ADMBoolean ADMAPI (*IsForcedOnScreen)(ADMDialogRef inDialog);

	/** Invokes a modal dialog that has been created with \c #Create().
		While the dialog is active, no other windows respond to user input.
		This function does not return until the dialog is dismissed.
			@param inDialog The dialog object.
			@return The item identifier of the item used to dismiss the dialog.
			@see \c #Create(), \c #Modal(), \c #PopupModal(), \c #DisplayAsModal()
		*/
	ADMInt32 ADMAPI (*DisplayAsPopupModal)(ADMDialogRef inDialog);


	/** Creates a dialog item (control element). This is the same as \c #CreateItem(),
		except that if \c inParentItem has type \c #kADMItemGroupType, the new item
		is added as a child of that parent.
			@param inDialog The dialog object.
			@param inParentItem The parent item for the new item, an item of type \c #kADMItemGroupType.
			@param inItemID The unique identifier of the new item. See \c #CreateItem().
			@param inItemType The item type constant, \c kADM*Type. See \c #kADMDialType and following.
			@param inBoundsRect The position and size of the new item, in local coordinates
				relative to the dialog's origin.
			@param inInitProc A developer-defined initialization procedure for the new item.
			@param inUserData Developer-defined data to pass to the initialization procedure.
			@param inOptions The option flags that control the new item's behavior, a
				logical OR of item create-option constants. See \c #CreateItem().
			@return The new item object.
			@see \c #CreateItem(), \c #ADMItemSuite9::Create(), \c #ADMItemSuite9::AddItem()
		*/
	ADMItemRef ADMAPI (*CreateNestedItem)(ADMDialogRef inDialog, ADMItemRef inParentItem,
				ADMInt32 inItemID, ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/**	Closes a sequence of calls to \c #ADMItemSuite9::SetFirstFocus() and
		\c #ADMItemSuite9::SetNextFocus(), which set the focus order (also called tab order)
		for a set of items in a dialog. The sequence must have been opened with
		\c #BeginAdjustingFocusOrder(). The focus order does not take effect
		until this call is made.
			@param inDialog The dialog object.
			@see \c #FirstItem(), \c #LastItem()
		*/
	ADMErr ADMAPI (*DoneAdjustingFocusOrder)(ADMDialogRef inDialog);

	/**	Opens a sequence of calls to \c #ADMItemSuite9::SetFirstFocus() and
		\c #ADMItemSuite9::SetNextFocus(), which set the focus order
		(also called tab order) for a set of items in a dialog.
		This is the order in which contained elements get input focus
		when the user presses the Tab key.

		When the sequence is finished, call \c #DoneAdjustingFocusOrder().

		This code sequence must not be nested. Finish specifying the order in one
 		dialog before proceeding to the next one.
			@param inDialog The dialog object.
			@note To rearrange the order of an existing focus list,
				use \c #ADMItemSuite9::MoveFocusItem().
			@see \c #FirstItem(), \c #LastItem()
		*/
	ADMErr ADMAPI (*BeginAdjustingFocusOrder)(ADMDialogRef inDialog);


	/**	Retrieves the first item in a dialog's focus order (also called tab order),
		as set by \c #ADMItemSuite9::SetFirstFocus()
			@param inDialog The dialog object.
			@param outItem [out] A buffer in which to return the item object,
				or \c NULL if no focus list has been set.
			@see  \c #BeginAdjustingFocusOrder(), \c #DoneAdjustingFocusOrder(),
				\c #ADMItemSuite9::SetFirstFocus(), \c #ADMItemSuite9::SetNextFocus(),
				\c #ADMItemSuite9::MoveFocusItem()
		*/
	ADMErr ADMAPI (*FirstItem)(ADMDialogRef inDialog, ADMItemRef* outItem);

	/**	Retrieves the last item in a dialog's focus order (also called tab order).
			@param inDialog The dialog object.
			@param outItem [out] A buffer in which to return the item object,
				or \c NULL if no focus list has been set.
			@see \c #BeginAdjustingFocusOrder, \c #DoneAdjustingFocusOrder,
				\c #ADMItemSuite9::SetFirstFocus(), \c #ADMItemSuite9::SetNextFocus(),
				\c #ADMItemSuite9::MoveFocusItem()
		*/
	ADMErr ADMAPI (*LastItem)(ADMDialogRef inDialog, ADMItemRef* outItem);

	/** Sets the icon that is drawn when a palette (a tabbed dialog with style \c kADMTabbed*Style)
		is stashed in an icon-mode palette pane.  You can also use this function to set
		the rollover icon for this circumstance. Rollover icons are not required.
			@param inDialog The dialog object.
			@param inRollover True to set the rollover icon, false to set the normal icon.
			@param inIcon The new icon.
		*/
	ADMErr ADMAPI (*SetIcon)(ADMDialogRef inDialog, ADMBoolean inRollover, ADMIconRef inIcon);

	/** Sets the toolbar icon that is automatically drawn at the top of
		toolbars for dialogs that have \c #kADMToolbarDialogOption set.
		A normal and a rollover icon can be associated with each \c #ADMToolbarMode.
		Rollover icons are not required.
			@param inDialog The dialog object.
			@param inIconType The toolbar icon type, which identifies the associated toolbar mode
				and identifies this as the normal or rollover icon.
			@param inIcon The new icon.
		*/
	ADMErr ADMAPI (*SetToolbarIcon)(ADMDialogRef inDialog, ADMToolbarIconType inIconType, ADMIconRef inIcon);

	/** Modifies the preferred toolbar mode for dialogs that have \c #kADMToolbarDialogOption set.
 		This is the correct way to resize toolbars.
			@param inDialog The dialog object.
			@param inMode The toolbar mode.
			@see \c #SetToolbarSizeForMode()
		*/
	ADMErr ADMAPI (*SetToolbarMode)(ADMDialogRef inDialog, ADMToolbarMode inMode);

	/** Retrieves the current preferred toolbar mode for dialogs that have \c #kADMToolbarDialogOption set.
			@param inDialog The dialog object.
			@param outMode [out] A buffer in which to return the toolbar mode.
		*/
	ADMErr ADMAPI (*GetToolbarMode)(ADMDialogRef inDialog, ADMToolbarMode& outMode);

};

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMDialogOld__
#ifdef MAC_ENV
#include "ADMDialogOld.h"
#else
#include ".\Legacy\ADMDialogOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMDialog__
