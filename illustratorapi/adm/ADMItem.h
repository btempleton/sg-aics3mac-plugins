/*******************************************************************************
*
* ADMItem.h -- ADM Item Suite
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

/** @file ADMItem.h ADM Item Suite */

#ifndef __ADMItem__
#define __ADMItem__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMTracker__
#include "ADMTracker.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
//	Item types

/** Data type for ADM item control types (\c kADM*Type). */
typedef const char* ADMItemType;

/** Dialog item type: A dial control with a pointer that displays and allows input of
	a numeric value, used for calibration.  See \c #ADMDialStyle.
	To initialize, set the minimum, maximum, and current values, and assign a
	notification procedure. */
#define kADMDialType "ADM Dial Type"

/** Dialog item type: A container that visually groups other items.
	It is drawn as a rectangle around the contained items; see \c #ADMFrameStyle.
	Any text is displayed as a title.
	No initialization needed. */
#define kADMFrameType "ADM Frame Type"

/** Dialog item type: A container that groups items logically, so that they can be
	enabled or disabled together. The group object does not have a visible representation,
	and does not affect the appearance or position of its members.
	No initialization needed. Add items to the group with \c #ADMItemSuite9::AddItem() */
#define kADMItemGroupType "ADM Item Group Type"

/** Obsolete, do not use.  */
#define kADMTabbedMenuType "ADM Tabbed Menu Type"

/** Dialog item type: A box that contains list entries of which none, one, or more can be selected.
	See \c #ADMListEntrySuite4.	To initialize, get the item’s list and set its menu ID. If
	necessary, activate an entry or entries. Assign a notification procedure for the entries.

	This item is a composite of child items; to manipulate or examine the individual elements,
	retrieve them with \c #ADMItemSuite9::GetChildItem().*/
#define kADMListBoxType "ADM List Box Type"

/** Dialog item type: A group of list entries with a tree structure.
	See \c #ADMHierarchyListSuite5.
	To initialize, get the item’s list and set its menu ID. If necessary,
	activate an entry or entries. Assign initialization, notification, and
	drawing procedures for the entries.

	This item is a composite of child items; to manipulate or examine the individual elements,
	retrieve them with \c #ADMItemSuite9::GetChildItem().*/
#define kADMHierarchyListBoxType "ADM Hierarchy List Box Type"

/** Dialog item type: A checkbox button with an image (picture) label.
	It can be enabled or disabled, and when enabled can be selected or deselected,
	A checkbox by the picture indicates the selected/deselected state.
	To initialize, set the boolean value and the picture ID. You can also provide picture IDs
	for the selected and disabled states, and an optional notification procedure.*/
#define kADMPictureCheckBoxType "ADM Picture Check Box Button Type"

/** Dialog item type: A pushbutton represented by an image (picture).
	It can be enabled or disabled, and when enabled can be selected or deselected,
	Different pictures are associated with each state.
	To initialize, set the picture ID and assign a notification function.
	You can also provide picture IDs for the selected and disabled states. */
#define kADMPicturePushButtonType "ADM Picture Push Button Type"

/** Dialog item type: A radiobutton choice with an image (picture) label,
	which is part of a radiobutton group in which selections are mutually exclusive.
	Items with consecutive IDs are automatically grouped together.
	Radio-buttons that do not have sequential ID numbers
	can be added to a radio-group object; see \c #ADMRadioGroupSuite1::Add().
	It can be enabled or disabled, and when enabled can be selected or deselected,
	A small circle by the picture indicates the state.
	To initialize, set the picture ID and set the boolean value.
	One radio button in a group must be true if the group's style is
	\c #kADMRadioButtonOneAlwaysSetStyle. You can also provide picture IDs
	for the selected and disabled states. No notification procedure is needed
	for groups with consecutive IDs. */
#define kADMPictureRadioButtonType "ADM Picture Radio Button Type"

/** Dialog item type: An image (picture) which handles a click by automatically activating
	the edit item next to it, or the one previous, if the next item is not an edit item.
 	To initialize, set the picture ID. Set \c #kADMDisableAutoActivatePictureStaticStyle
 	to disable the default behavior. */
#define kADMPictureStaticType "ADM Picture Static Type"

/** Dialog item type: A pop-up arrow that pops up a predefined or custom dialog.
	Predefined popups are \c #kADMPopupSliderDialogID (the default) and
	\c #kADMPopupDialDialogID. You can define a custom dialog popup with
	\c #kADMPopupControlDialogStyle.
	The appearance is defined by the \c #ADMPopupControlStyle.
	To initialize, set a notification procedure, and minimum and maximum range
	values for numeric selection controls. Use \c #ADMItemSuite9::SetPopupDialog()
	to associate the dialog popup with the item. */
#define kADMPopupControlType "ADM Popup Control Type"

/** Dialog item type: A pop-up button.
	To initialize, set a notification procedure.
	Set button text with \c #ADMItemSuite9::SetText(). */
#define kADMPopupControlButtonType "ADM Popup Control Button Type"

/** Dialog item type: A pop-up spin-edit that sets a numeric value.
	Differs from \c #kADMSpinEditPopupType in that it does not have a menu.
	It can, for example, pop up a slider.
	To initialize, set a notification procedure, minimum and maximum range
	values, and small increment value. */
#define kADMPopupSpinEditControlType "ADM Popup Spin Edit Control Type"

/** Dialog item type: An arrow indicator that pops up a list of entries.
	To initialize, get the item’s list and set its menu ID. If
	necessary, activate an entry or entries. */
#define kADMPopupListType "ADM Popup List Type"

/** Dialog item type: An arrow indicator that pops up a menu, whose
	choices are associated with immediate actions.
	To initialize, get the item’s list and set its menu ID. If
	necessary, activate an entry or entries. */
#define kADMPopupMenuType "ADM Popup Menu Type"

/** Dialog item type: A platform-specific resize icon for a dialog.
	To initialize, set a notification procedure that handles the resizing
	or repositioning of other items when the dialog is resized. */
#define kADMResizeType "ADM Resize Type"

/** Dialog item type: Allows selection of a numeric value within a range,
	with a draggable thumb indicator (a rectangle within a bar) that changes
	the value by the small increment, and arrows at each end that change the
	value by the large increment; see \c #ADMItemSuite9::SetSmallIncrement() and
	\c #ADMItemSuite9::SetLargeIncrement().
	To initialize, set the range and small and large increments.
	Assign notification and tracking procedures, and a draw procedure
	for graphic feedback (such as a current picture).*/
#define kADMScrollbarType "ADM Scrollbar Type"

/** Dialog item type:  An arrow indicator that pops up a scrolling list of entries.
	To initialize, get the item’s list and set its menu ID. If
	necessary, activate an entry or entries. */
#define kADMScrollingPopupListType "ADM Scrolling Popup List Type"

/** Dialog item type: Allows selection of a numeric value within a range,
	with a draggable thumb indicator, a triangle below a bar.
	To initialize, set the numeric value, range, and small increment value.
	Assign a notification procedure if necessary, and a draw procedure for graphic feedback
	(color, for example).*/
#define kADMSliderType "ADM Slider Type"

/** Dialog item type: A small edit field with an associated pair of arrow buttons
	(up arrow and down arrow). The edit field contains a numeric value that can be
	directly edited or incremented/decremented by clicking the up or down arrows.
	To initialize, set the item’s text, the numeric range, value, units, and small increment value.

	This item is a composite of child items; to manipulate or examine the individual elements,
	retrieve them with \c #ADMItemSuite9::GetChildItem().*/
#define kADMSpinEditType "ADM Spin Edit Type"

/** Dialog item type: A spin edit that also has a popup list of choices.
	To initialize, set the item’s text, the numeric range, units, and small increment value.
	Get the item’s list and set its menu ID. If necessary, activate an entry or entries.

	This item is a composite of child items; to manipulate or examine the individual elements,
	retrieve them with \c #ADMItemSuite9::GetChildItem().*/
#define kADMSpinEditPopupType "ADM Spin Edit Popup Type"

/** Dialog item type: A spin edit with a popup list of choices that scrolls.
	To initialize, set the item’s text, the numeric range, units, and small increment value.
	Get the item’s list and set its menu ID. If necessary, activate an entry or entries.

	This item is a composite of child items; to manipulate or examine the individual elements,
	retrieve them with \c #ADMItemSuite9::GetChildItem().*/
#define kADMSpinEditScrollingPopupType "ADM Spin Edit Scrolling Popup Type"

/** Dialog item type: A checkbox button with a text label.
	To initialize, set the item's boolean value. */
#define kADMTextCheckBoxType "ADM Text Check Box Type"

/** Dialog item type: An editable text box.
	To initialize, set the item’s text and maximum text length.
	If the style is numeric, set the range, units, and precision. */
#define kADMTextEditType "ADM Text Edit Type"

/** Dialog item type: A text box whose value can only be changed
	programmatically. Unlike static style, allows user
	to copy the text to the clipboard. */
#define kADMTextEditReadOnlyType "ADM Text Edit Read-only Type"

/** Dialog item type: An editable text box that allows user to enter text that
	contains Return characters.
	To initialize, set the item’s text and maximum text length.
	If the style is numeric, set the range, units, and precision. */
#define kADMTextEditMultiLineType "ADM Text Edit Multi Line Type"
/** Dialog item type: A multi-line text box whose value can
	only be changed programmatically. Unlike static style, allows user
	to copy the text to the clipboard.
	To initialize, set the item's text. */
#define kADMTextEditMultiLineReadOnlyType "ADM Text Edit Multi Line Read-only Type"

/** Dialog item type: An editable text box with choices available in
	a popup list. Displays the current choice, or allows text entry
	according to style constraints (see \c #ADMTextEditPopupStyle).
	User can enter values not listed in popup.
	To initialize, set the item’s text and maximum text length.
	If the style is numeric, set the range, units, and precision.
	Get the item’s list and set its menu ID. If necessary, activate an entry or entries. */
#define kADMTextEditPopupType "ADM Text Edit Popup Type"

/** Dialog item type: An editable text box with choices available in
	a scrolling popup list.
	To initialize, set the item’s text and maximum text length.
	If the style is numeric, set the range, units, and precision.
	Get the item’s list and set its menu ID. If necessary, activate an entry or entries. */
#define kADMTextEditScrollingPopupType "ADM Text Edit Scrolling Popup Type"

/** Dialog item type: Displays the ADM item text within a rounded rectangle.
	Can be enabled/disabled, and when enabled can be selected/deselected.
	Selection has associated behavior. A dialog can have a default button, which
	is enclosed in an additional rectangle.
	To initialize, set the text and notification procedure. */
#define kADMTextPushButtonType "ADM Text Push Button Type"

/** Dialog item type: A radiobutton choice with a text label,
	which is part of a radiobutton group in which selections
	are mutually exclusive. Items with consecutive IDs are automatically
	grouped together. Radio-buttons that do not have sequential ID numbers
	can be added to a radio-group object; see \c #ADMRadioGroupSuite1::Add().
	To initialize, set the boolean value. One radio button in a group must
	be true if the group's style is	\c #kADMRadioButtonOneAlwaysSetStyle.
	No notification procedure is needed for groups with consecutive IDs.*/
#define kADMTextRadioButtonType "ADM Text Radio Button Type"

/** Dialog item type: A single-line text box which handles a click by automatically activating
	the edit item next to it, or the one previous, if the next item is not an edit item.
 	To initialize, set the item's. Set \c #kADMDisableAutoActivateTextStaticStyle
 	to disable the default behavior. */
#define kADMTextStaticType "ADM Text Static Type"

/** Dialog item type: A multi-line text box which handles a click by automatically activating
	the edit item next to it, or the one previous, if the next item is not an edit item.
 	To initialize, set the item's. Set \c #kADMDisableAutoActivateTextStaticStyle
 	to disable the default behavior.  */
#define kADMTextStaticMultiLineType "ADM Text Static Multi Line Type"

/** Dialog item type: A bar that indicates progress during a lengthy operation,
	in a platform-specific style. Bar shows current value as percentage of
	distance between minimum and maximum.
	To initialize, set the initial value, minimum, and maximum values.  */
#define kADMProgressBarType "ADM Progress Bar Type"

/** Dialog item type: Mac OS only. Two small animated arrows pointing at each other in a circle,
	used to indicate that an operation is in progress. No initialization required. */
#define kADMChasingArrowsType "ADM Chasing Arrows Type"

/** Dialog item type: A developer-defined custom control type. To initialize, assign
	draw, notification, and tracking procedures, and other properties as required. */
#define kADMUserType "ADM User Type"

//As much as I would like to avoid this, Win9x doesn't respect ES_ after
//the control is created.  So this 'style' must be a type so that the style can
//be set in time.  The alternative is to have the application set the style in
//their resource.  This deals with creating one without using the resource file.
/** Dialog item type: An editable text box for password entry,
	which does not echo input text.
	To initialize, set the maximum length and assign a notification procedure. */
#define kADMPasswordTextEditType "ADM Password Text Edit Type"

// majones: These three types added so that new UIT items types can be created through CreateItem and CreateNestedItem
/** Dialog item type: A list box that displays entries in multiple columns.   */
#define kADMMultiColumnListViewType "ADM Multi Column List View Type"

/** Dialog item type: A scrolling view. */
#define kADMScrollingViewType "ADM Scrolling View Type"

/** Dialog item type: A tab group.  */
#define kADMTabGroupType "ADM Tab Group Type"

/** Dialog item type: An embedded Flash player control type. To initialize, register the appropriate
callback function to enable the invocation of the application-side function via the ActionScript
\c ExternalInterface call from the Flash movie. */
#define kADMFlashPlayerType "ADM Flash Player Type"

// -----------------------------------------------------------------------------
//	Style codes

/** Data type for dialog item visual styles.

	These styles are set with \c #ADMItemSuite9::SetItemStyle():
		<br>\c #ADMFrameStyle, for items of type \c #kADMFrameType
		<br>\c #ADMPictureButtonStyle, for picture-button types.
		<br>\c #ADMPopupMenuStyle, for popup-menu types
		<br>\c #ADMPopupControlStyle, for items of popup types.
		<br>\c #ADMSpinEditStyle, for spin-edit types.
		<br>\c #ADMSpinEditPopupStyle, for spin-edit popup types.
		<br>\c #ADMTextEditStyle, for text-edit types.
		<br>\c #ADMRadioButtonStyle, for items of type \c #kADMTextRadioButtonType and \c #kADMPictureRadioButtonType
		<br>\c #ADMDialStyle, for items of type \c #kADMDialType
		<br>\c #ADMSliderStyle, for items of type \c #kADMSliderType
		<br>\c #kADMDisableAutoActivatePictureStaticStyle, for picture types.
		<br> static text styles, for types that display static text; see \c #kADMClippedTextStaticStyle
		<br> list box styles, for list types; see \c #kADMMultiSelectListBoxStyle

	These styles are set as creation options with \c #ADMItemSuite9::Create():
		<br>\c #kADMPasswordEditCreateOption, for items of type \c #kADMPasswordTextEditType
		<br>\c #kADMUnicodeEditCreateOption, for items of text-edit types
		<br>\c #kADMDisableDragDropEditCreateOption, for items of text-edit types
		<br>\c #kADMHierarchyPopupCreateOption, only valid with \c #kADMPopupMenuType for hierarchical menus
	*/
typedef ADMInt32 ADMItemStyle;

/** Dialog item styles: How the frame is drawn
	for an item of type \c #kADMFrameType. */
typedef enum
{
	/** Solid black line. */
	kADMBlackFrameStyle = 0,
	/** Solid gray line. */
	kADMGrayFrameStyle = 1,
	/** A sunken 3D effect, as for a pressed button. The bottom and right
		edges are highlighted. */
	kADMSunkenFrameStyle = 2,
	/** A raised 3D effect, as for an unpressed button. The top and left
		edges are highlighted. */
	kADMRaisedFrameStyle = 3,
	/** An etched effect. Each edge is highlighted on its right or bottom side. */
	kADMEtchedFrameStyle = 4,
	/** Internal */
	kADMDummyFrameStyle = 0xFFFFFFFF
}
ADMFrameStyle;

/** Dialog item styles: How the picture outline is drawn
	for an item of any of the picture-button types:
	<br>\c #kADMPicturePushButtonType
	<br>\c #kADMPictureCheckBoxType
	<br>\c #kADMPictureRadioButtonType	  */
typedef enum
{
	/** Black outline with sunken 3D effect (pushed button).  */
	kADMBlackAndSunkenRectPictureButtonStyle = 0,

	/** Solid black outline.  */
	kADMBlackRectPictureButtonStyle = 1,

	/** Draws a border and pop-up arrow around a control whose appearance is otherwise
		controlled by a developer-defined drawing procedure. */
	kADMComboBoxPictureButtonStyle = 4, // A user-drawn control with a pop-up arrow and border

	/** Draws a border around a control whose appearance is otherwise
		controlled by a developer-defined drawing procedure. */
	kADMBorderPictureButtonStyle = 8, // A user-drawn control with a border

	/** Internal */
	kADMDummyPictureButtonStyle = 0xFFFFFFFF
}
ADMPictureButtonStyle;
	/* Warning: Do not assign a meaning to 2. The ADMPictureButtonStyle options are shared by
		items of type kADMPicturePushButtonType and kADMPictureRadioButtonType, so they must
		not overlap with the values for ADMRadioButtonStyle.
	*/

	// Picture static styles
/** Dialog item style for items of type \c #kADMPictureStaticType.
	Disables the default behavior, which is to handle a click by automatically activating
	the edit item next to it, or the one previous, if the next item is not an edit item.  */
#define kADMDisableAutoActivatePictureStaticStyle (1L << 1)

	// Integer numeric style (used in the precision of a numeric)
/** Dialog item style for items that display numeric values.
	Allows entry of integer values only (rather than rounding down to x.0, as a
	precision of 0 does). <<*/
#define kADMIntegerNumeric -1

	// List box styles
/** Dialog item display style for list items. Allows multiple selection of list entries. */
#define kADMMultiSelectListBoxStyle (1L << 0)
/** Dialog item display style for \c #ADMHierarchyListRef items.
	Draws lines between entries. */
#define kADMDividedListBoxStyle (1L << 1)

/** Dialog item display style for list items.
	Displays list entries as squares in as many columns
	as the width of the list allows. */
#define kADMTileListBoxStyle (1L << 2)

/** Dialog item display style for list items.
	Constrains the box to always have at least one entry selected. */
#define kADMEntryAlwaysSelectedListBoxStyle (1L << 3)

/** Dialog item display style for list items.
	Draws a solid black outline around the list box. */
#define kADMBlackRectListBoxStyle (1L << 4)

/** Dialog item display style for list items.
	Draws the entry list off-screen and displays it as an image, to avoid redraw flicker. */
#define kADMUseImageListBoxStyle (1L << 5)

/** Dialog item display style for list items.
	Displays a list of text entries, in which a list entry can be made editable
 	by clicking and hovering on it for one second. */
#define kADMEntryTextEditableListBoxStyle (1L << 6)


/** Editable text creation option: Use for an item of type \c #kADMPasswordTextEditType when
	creating programmatically (rather than as a resource). */
#define kADMPasswordEditCreateOption (1L << 1)

/** Editable text creation option: Returns a Unicode string, if possible,
	when the text value of a text-edit item is queried.  */
#define kADMUnicodeEditCreateOption (1L << 2) // [cpaduan] 6/18/02 - Creates a Unicode based edit box (if possible). FIXME: Currently has no effect on Windows.

/** Editable text creation option: (Mac OS only) Disables drag-and-drop to or from the text box.  */
#define kADMDisableDragDropEditCreateOption (1L << 3) // Disables drag & drop from or to text edits. Currently mac-only.

	// hathaway : 8/22/02 : Added to support creation of hierarchical palette popups for Pangea
	// Popup menu creation options
/** Pop-up dialog item creation option: allows hierarchical pop-up lists. */
#define kADMHierarchyPopupCreateOption (1L << 0)

/** Dialog item styles: Controls the appearance of a dialog item of type
	\c #kADMPopupMenuType, which pops up a menu.   */
typedef enum
{
	/** Draws a right-facing pop-up arrow, and places menu to the right side. */
	kADMRightPopupMenuStyle = 0,
	/** Draws a down-facing pop-up arrow, and places menu under it. */
	kADMBottomPopupMenuStyle = 1,
	/** Draws a round menu button. */
	kADMRoundPopupMenuStyle = 2,
	/** Draws a round menu button for a hierarchy menu. */
	kADMRoundHierarchyPopupMenuStyle = 4,
	/** Draws a right-facing pop-up arrow with a border. */
	kADMRightBorderPopupMenuStyle = 8,
	/** Draws a picture button using the picture set with \c #ADMItemSuite9::SetPictureID() or
		\c #ADMItemSuite9::SetPicture() */
	kADMPictureButtonPopupMenuStyle = 16,
	/** Draws a static text control with rollover feedback */
	kADMActiveLabelPopupMenuStyle = 32,
	/** Draws a control that is not repositioned. */
	kADMNoPositionAdjustmentPopupMenuStyle = 64, // Stops draw code from repositioning the control.
	/** Draws a picture button with a hierarchical menu style. */
	kADMPictureButtonHierarchyPopupMenuStyle = 128,
	/** Internal */
	kADMDummyPopupMenuStyle = 0xFFFFFFFF
}
ADMPopupMenuStyle;

/**  Dialog item styles:  Controls the appearance of a dialog item of type
	\c #kADMPopupControlType, which pops up a dialog containing a slider,
	dial, or custom controls. */
typedef enum
{
	/** Draws a right-facing pop-up arrow button. */
	kADMRightPopupControlStyle = 0,
	/** Draws the current choice in a text box with a pop-up arrow button. */
	kADMComboBoxPopupControlStyle = 1,
	/** Draws a border.  */
	kADMBorderPopupControlStyle = 2,
	/** Draws an active label.  */
	kADMActiveLabelPopupControlStyle = 4,
	/** Internal */
	kADMDummyPopupControlStyle = 0xFFFFFFFF
}
ADMPopupControlStyle;

/** Dialog item style for spin-edit types, controls how the arrows
	that increment and decrement values are displayed. */
typedef enum
{
	/** Displays arrows pointing up and down. */
	kADMVerticalSpinEditStyle = 0,
	/** Displays arrows pointing left and right. */
	kADMHorizontalSpinEditStyle = 1,
	/** Internal */
	kADMDummySpinEditStyle = 0xFFFFFFFF
}
ADMSpinEditStyle;

/** Dialog item style for spin-edit pop-up types, controls how the arrows
	that increment and decrement values are displayed. */
typedef enum
{
	/** Displays arrows pointing up and down. */
	kADMVerticalSpinEditPopupStyle = 0,
	/** Displays arrows pointing left and right. */
	kADMHorizontalSpinEditPopupStyle = 4,
	/** Internal */
	kADMDummySpinEditPopupStyle = 0xFFFFFFFF
}
ADMSpinEditPopupStyle;

/** Dialog item styles for editable text boxes.*/
typedef enum
{
	/** Constrains input to a single line of text.  */
	kADMSingleLineTextEditStyle = 0,
	/** Constrains input to numeric values, floating-point by default.  */
	kADMNumericTextEditStyle = 2,		// 'Numeric' means float. Default.
	/** Mac OS only. Ignores default Carbon event processing;
		not compatible with \c #kADMUnicodeEditCreateOption 	*/
	kADMTrackRawKeysTextEditStyle = 4,
	/** Does not echo input text, but displays placeholder characters. */
	kADMPasswordTextEditStyle = 32,		// Win32 value for ES_PADMSWORD
	/** Internal */
	kADMDummyTextEditStyle = 0xFFFFFFFF
}
ADMTextEditStyle;

	// Text static styles
/** Dialog item styles for static text boxes, of type
	\c #kADMTextStaticType or \c #kADMTextStaticMultiLineType.
	Text is clipped. */
#define kADMClippedTextStaticStyle (1L << 0)

/** Dialog item styles for static text boxes, of type
	\c #kADMTextStaticType or \c #kADMTextStaticMultiLineType.
	Disables the default behavior, which is to handle a click by automatically activating
	the edit item next to it, or the one previous, if the next item is not an edit item.  */
#define kADMDisableAutoActivateTextStaticStyle (1L << 1)

/** Dialog item styles for static text boxes, of type
	\c #kADMTextStaticType or \c #kADMTextStaticMultiLineType.
	Text that does not fit is truncated at the end. */
#define kADMTruncateEndTextStaticStyle (1L << 2)	// clipped style has priority

/** Dialog item styles for static text boxes, of type
	\c #kADMTextStaticType or \c #kADMTextStaticMultiLineType.
	Text that does not fit is truncated in the middle. */
#define kADMTruncateMiddleTextStaticStyle (1L << 3)	// truncate end has priority

/** Dialog item styles for editable text boxes with associated pop-ups, */
typedef enum
{
	/** Allows entry of a single line of text in edit-box portion.*/
	kADMSingleLineEditPopupStyle = 0,
	/** Constrains text entry to numeric values in edit-box portion. */
	kADMNumericEditPopupStyle = 2,
	/**  */
	kADMExclusiveEditPopupStyle = 5,
	/** Internal */
	kADMDummyTextEditPopupStyle = 0xFFFFFFFF
}
ADMTextEditPopupStyle;

/** Dialog item styles for radio buttons, items of type
	\c #kADMTextRadioButtonType and \c #kADMPictureRadioButtonType.
	All buttons in a radio group must have the same style. */
typedef enum
{
	/** One button in the group must always be set. */
	kADMRadioButtonOneAlwaysSetStyle = 0,
	/** Allows all buttons in the group to be off.  */
	kADMRadioButtonAllowNoneSetStyle = 2,
	/** Internal */
	kADMDummyRadioButtonStyle = 0xFFFFFFFF
}
ADMRadioButtonStyle;
	/* Note: If adding any more options to this style, they must not overlap with the values from
		ADMPictureButtonStyle, since items of type kADMPictureRadioButton use the style options from
		both ADMPictureButtonStyle and ADMRadioButtonStyle.
	*/

/** Dialog item styles for dials, items of type	\c #kADMDialType */
typedef enum
{
	/** The dial pointer has no arrow. */
	kADMNoArrowDialStyle = 0,
	/** The dial pointer has an arrow at the end. */
	kADMArrowAtEndDialStyle = 1,
	/** The dial pointer has an arrow in the middle. */
	kADMArrowAtCenterDialStyle = 2,
	/** Internal */
	kADMDummyDialStyle = 0xFFFFFFFF
}
ADMDialStyle;

/**  Dialog item styles for sliders, items of type
	\c #kADMSliderType */
typedef enum
{
	/** Slider style not set.  */
	kADMNoSliderStyle = 0,
	/** The scale of values is non-linear.
		That is, it increments by one from the low point
		to the  midpoint, then non-linearly from the midpoint
		to the endpoint.*/
	kADMNonLinearSliderStyle = 1,
	/** The slider scale shows fractional values. */
	kADMShowFractionSliderStyle = 2,
	/** Draws tick marks at each integer value along the slider.*/
	kADMTickmarkSliderStyle = 4,
	/** Internal */
	kADMDummySliderStyle = 0xFFFFFFFF
}
ADMSliderStyle;


// -----------------------------------------------------------------------------
//	Child item IDs

/** Types of predefined component elements of list-box item types.
	Retrieve the item reference for the component with \c #ADMItemSuite9::GetChildItem(). */
typedef enum
{
	/** The scrollbar component. */
	kADMListBoxScrollbarChildID = 1,
	/** The choice-list component.  */
	kADMListBoxListChildID = 2,
	/** The edit-box component. */
	kADMListBoxTextEditBoxChildID = 3,
	/** The choice-list pop-up component. */
	kADMListBoxPopupChildID = 4,
	/** Internal */
	kADMListBoxDummyChildID = 0xFFFFFFFF
}
ADMListBoxChildID;

/** Types of predefined component elements of spin-edit item type.
	Retrieve the item reference for the component with \c #ADMItemSuite9::GetChildItem(). */
typedef enum
{
	/** The up-arrow (or left-arrow) button component. */
	kADMSpinEditUpButtonChildID = 1,
	/** The down-arrow (or right-arrow) button component. */
	kADMSpinEditDownButtonChildID = 2,
	/** The edit-box component. */
	kADMSpinEditTextEditChildID = 3,
	/** Internal */
	kADMSpinEditDummyChildID = 0xFFFFFFFF
}
ADMSpinEditChildID;

/** Types of predefined component elements of spin-edit pop-up item type.
	Retrieve the item reference for the component with \c #ADMItemSuite9::GetChildItem(). */
typedef enum
{
	/** The up-arrow (or left-arrow) button component. */
	kADMSpinEditPopupUpButtonChildID = 1,
	/** The down-arrow (or right-arrow) button component. */
	kADMSpinEditPopupDownButtonChildID = 2,
	/** The edit-box component. */
	kADMSpinEditPopupTextEditChildID = 3,
	/** The popup-box component. */
	kADMSpinEditPopupPopupChildID = 4,
	/** Internal */
	kADMSpinEditPopupDummyChildID = 0xFFFFFFFF
}
ADMSpinEditPopupChildID;

/** Types of predefined component elements of the text-edit pop-up item type.
	Retrieve the item reference for the component with \c #ADMItemSuite9::GetChildItem().*/
typedef enum
{
	/** The edit box component. */
	kADMTextEditPopupTextEditChildID = 3,
	/** The popup-box component. */
	kADMTextEditPopupPopupChildID = 4,
	/** Internal */
	kADMTextEditPopupDummyChildID = 0xFFFFFFFF
}
ADMTextEditPopupChildID;


// -----------------------------------------------------------------------------

// jsbache: Creator options for new UIT items types

/// MultiColumnListView create options
/** Creation options for the multi-column list view item,
	\c #kADMMultiColumnListViewType */
enum
{
	/** Default order of entries, which allows users to
		click column headings to change the sort order.  */
	kADMMCLVNoOptions		= 0,
	/** Entries are sorted in the order in which
		they were added to the list and user cannot resort. */
	kADMMCLVFixedSortOrder	= (1L << 0)
};

// -----------------------------------------------------------------------------
//	User-provided function types

/** Prototype for an initialization procedure associated with a custom dialog item.
		@param inItem The item object.
		@return An ADM error code.
		@see \c #ADMItemSuite9::Create()
		*/
typedef ADMErr ADMAPI (*ADMItemInitProc)(ADMItemRef inItem);
/** Prototype for a drawing procedure associated with a custom dialog item.
	Your function can completely draw a custom item, or call the default
	drawer to draw the basic appearance, then modify it.
		@param inItem The item object.
		@param inDrawer The drawing object.
		@return Nothing.
		@see \c #ADMItemSuite9::SetDrawProc(), \c #ADMItemSuite9::DefaultDraw()
	*/
typedef void ADMAPI (*ADMItemDrawProc)(ADMItemRef inItem, ADMDrawerRef inDrawer);

/** Prototype for an event tracking procedure associated with a custom dialog item.
	Use \c #ADMItemSuite9::SetMask() to specify which events are sent to the tracker. By default,
	the events that are tracked depend on the item type. You can call the
	default tracker from this function. If you do not call the default tracker
	from your custom tracker, call \c #ADMTrackerSuite2::Abort() to exit
	the tracking loop.

	You might use a custom tracker, for example, to check for a modifier key,
	save the modifier state, and then call the default tracker.
	The default tracker returns true if the item is to be notified.
	Your item notifier procedure would act on the saved modifier state.
		@param inItem The item object.
		@param inTracker The tracker object.
		@return True to send a notification to the item when the mouse button
			is released, or for edit-text items, to indicate that a keystroke
			was handled. False to send no notification, or indicate that the
			keystroke was not handled.
		@see \c #ADMItemSuite9::SetTrackProc(), \c #ADMItemSuite9::DefaultTrack()
	*/
typedef ADMBoolean ADMAPI (*ADMItemTrackProc)(ADMItemRef inItem, ADMTrackerRef inTracker);

/** Prototype for a notification-handling procedure associated with a custom dialog item.
	Your function can completely implement the item's behavior, or call the default
	notify function for the standard behavior, such as list selection and radio button
	group behavior.	before or after performing some additional action.
		@param inItem The item object.
		@param inNotifier The notification object.
		@return Nothing.
		@see \c #ADMItemSuite9::SetNotifyProc(), \c #ADMItemSuite9::DefaultNotify()
	*/
typedef void ADMAPI (*ADMItemNotifyProc)(ADMItemRef inItem, ADMNotifierRef inNotifier);

/** Prototype for a termination procedure associated with a custom dialog item.
	Your function should clean up any data associated with the item before it is destroyed.
		@param inItem The item object.
		@return Nothing.
		@see \c #ADMItemSuite9::SetDestroyProc()
	*/
typedef void ADMAPI (*ADMItemDestroyProc)(ADMItemRef inItem);

/** Prototype for a timer procedure associated with a custom dialog item.
	Your function performs the scheduled action after the timer's delay
	period is up.
		@param inItem The item object.
		@param inTimer The timer object.
		@return True to repeat the timed operation, false to terminate.
		@see \c #ADMItemSuite9::CreateTimer()
	*/
typedef ADMBoolean ADMAPI (*ADMItemTimerProc)(ADMItemRef inItem, ADMTimerRef inTimer);

/** Prototype for a timer cancellation procedure associated with a custom dialog item.
	Your function should clean up data associated with the scheduled action.
		@param inItem The item object.
		@param inTimerID The timer object.
		@param inAbortAction The action that triggered the cancellation.
		@return Nothing.
		@see \c #ADMItemSuite9::CreateTimer()
	*/
typedef void ADMAPI (*ADMItemTimerAbortProc)(ADMItemRef inItem, ADMTimerRef inTimer,
			ADMAction inAbortAction);

/** Prototype for a float-to-text conversion procedure associated with a custom dialog item.
	Your function converts user-input floating-point values to display text.
	ADM provides a default conversion. Use this to override it when, for example, you
	want a special value to indicate an unused or null value. By default, ADM uses 0 for
	a value that is missing or cannot be converted.
		@param inItem The item object.
		@param inValue The input value.
		@param outText [out] A buffer in which to return the display text.
		@param inMaxLength The number of characters in the buffer.
		@return True if the value could be successfully converted and is known;
			see c #ADMItemSuite9::IsKnown().
		@see \c #ADMItemSuite9::SetTextToFloatProc()
	*/
typedef ADMBoolean ADMAPI (*ADMItemFloatToTextProc)(ADMItemRef inItem, float inValue,
			char* outText, ADMInt32 inMaxLength);

/** Prototype for a text-to-float conversion procedure associated with a custom dialog item.
	Your function converts user-input text values to floating-point numbers.
	ADM provides a default conversion. Use this to override it when, for example, you
	want a special value to indicate an unused or null value. By default, ADM uses 0 for
	a value that is missing or cannot be converted.
		@param inItem The item object.
		@param inText The input text string.
		@param outValue [out] A buffer in which to return the numeric value.
		@return True if the text could be successfully converted and is known;
			see \c #ADMItemSuite9::IsKnown().
		@see \c #ADMItemSuite9::SetFloatToTextProc()
	*/
typedef ADMBoolean ADMAPI (*ADMItemTextToFloatProc)(ADMItemRef inItem, const char* inText,
			float* outValue);


// =============================================================================
//		* ADM Item Suite
// =============================================================================

#define kADMItemSuite "ADM Item Suite"
#define kADMItemSuiteVersion9 9

// -----------------------------------------------------------------------------

/** @ingroup Suites
	A dialog item is a control element in a dialog. Use this suite to
	create, manipulate, and query dialog items. You can also create
	items from the dialog object, using \c #ADMDialogSuite10::CreateItem()
	and \c #ADMDialogSuite10::CreateNestedItem().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMItemSuite and \c #kADMItemSuiteVersion9.

	A dialog item has a parent dialog and a parent window. It's appearance
	and behavior are controlled by its \e type (\c #ADMItemType), its
	\e style (\c #ADMItemStyle), and properties that you can set and access
	using these functions, including developer-defined initialization, termination,
	drawing, and notification procedures.

	You can specify a focus order for the items in a dialog.
	This is the order in which contained elements get input focus
	when the user presses the Tab key. To set the initial focus
	order for a dialog:
		\li Call \c #ADMDialogSuite10::BeginAdjustingFocusOrder()
		\li Make a sequence of calls to \c #SetFirstFocus() and
			\c #SetNextFocus()
		\li When the sequence is finished, call
			\c #ADMDialogSuite10::DoneAdjustingFocusOrder()
			The focus order does not take effect until this call.

	This code sequence must not be nested. Finish specifying the order in one
 	dialog before proceeding to the next one.

	To rearrange the order of an existing focus list, use \c #MoveFocusItem().

	This chart maps ADM dialog item types to Mac OS item types that can be used as dialog resources.

	<table>
		<tr><td>ADMItemType </td><td>Mac OS Dialog Item </td><td>CDEF Res ID </td><td>Variation	</td><td>Mac OS CNTL Resource--Additional Fields</td></tr>

		<tr><td>ADM Frame		</td><td>User Item</td><td>		</td><td> 				</td><td></td></tr>
		<tr><td>				</td><td>Control Item</td><td>1000	</td><td>ADMFrameStyle	</td><td>Control Title is Group Name </td></tr>
		<tr><td>ADM List Box	</td><td>Control Item</td><td>1010	</td><td>ADMListBoxStyle </td><td>Min = MenuID = MenuResID	</td></tr>
		<tr><td>ADM Picture Check Box</td><td>Control Item</td><td>1023	</td><td>ADMPictureButtonStyle</td><td>Value = PictureID, Min = PictureSelectedID, Max = PictureDisabledID</td></tr>
		<tr><td>ADM Picture Push Button</td><td>Control Item</td><td>1020	</td><td>ADMPictureButtonStyle</td><td>Value = PictureID, Min = PictureSelectedID, Max = PictureDisabledID</td></tr>
		<tr><td>ADM Picture Radio Button</td><td>Control Item</td><td>1021	</td><td>ADMPictureButtonStyle</td><td>Value = PictureID, Min = PictureSelectedID, Max = PictureDisabledID</td></tr>
		<tr><td>ADM Picture Static</td><td>Icon Item</td><td>		</td><td>				</td><td>	</td></tr>
		<tr><td>				</td><td>Picture Item</td><td>		</td><td>				</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>1022</td><td>0</td><td>Value = PictureID, Min = PictureSelectedID, Max = PictureDisabledID</td></tr>
		<tr><td>ADM Popup List</td><td>Control Item</td><td>63</td><td>0</td><td>Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Popup Menu</td><td>Control Item</td><td>1030</td><td>ADMPopupMenuStyle</td><td>Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Resize</td><td>Control Item</td><td>1040</td><td>0</td><td>	</td></tr>
		<tr><td>ADM Scrollbar</td><td>Control Item</td><td>1</td><td>0</td><td>Value = IntValue, Min = IntMin, Max = IntMax</td></tr>
		<tr><td>ADM Scrolling Popup List</td><td>Control Item</td><td>1031</td><td>0</td><td>	</td></tr>
		<tr><td>ADM Slider</td><td>Control Item</td><td>1050</td><td>0</td><td>Value = IntValue, Min = IntMin, Max = IntMax</td></tr>
		<tr><td>ADM Spin Edit</td><td>Control Item</td><td>1060</td><td>ADMSpinEditStyle</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM Spin Edit Popup</td><td>Control Item</td><td>1061</td><td>ADMSpinEditPopupStyle</td><td>Value = ADMJustify, Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Spin Edit Scrolling Popup</td><td>Control Item</td><td>1062</td><td>ADMSpinEditPopupStyle</td><td>Value = ADMJustify, Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Text Check Box</td><td>Check Box Item</td><td>		</td><td>				</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>0</td><td>1</td><td>	</td></tr>
		<tr><td>ADM Text Edit</td><td>Edit Text Item</td><td>		</td><td>				</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>1070</td><td>ADMTextEditStyle</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM Text Edit Multi Line</td><td>Control Item</td><td>1073</td><td>0</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM Text Edit Popup</td><td>Control Item</td><td>1071</td><td>ADMTextEditPopupStyle</td><td>Value = ADMJustify, Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Text Edit Scrolling Popup</td><td>Control Item</td><td>1075</td><td>ADMTextEditPopupStyle</td><td>Value = ADMJustify, Min = MenuID = MenuResID</td></tr>
		<tr><td>ADM Text Push Button</td><td>Push Button Item</td><td>	</td><td>	</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>0</td><td>0</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>0</td><td>4 = Default</td><td>itemID = 1 (automatic default)</td></tr>
		<tr><td>ADM Text Radio Button</td><td>Radio Button Item</td><td>	</td><td>	</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>0</td><td>2</td><td>	</td></tr>
		<tr><td>ADM Text Static</td><td>Static Text Item</td><td>	</td><td>	</td><td>	</td></tr>
		<tr><td>				</td><td>Control Item</td><td>1072</td><td>0</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM Text Static	Multi Line</td><td>Control Item</td><td>1074</td><td>0</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM User</td><td>Control Item</td><td>1080</td><td>0</td><td>	</td></tr>
		<tr><td>ADM Custom</td><td>Control Item</td><td>1090</td><td>CNTL</td><td>Title = "Name Registered Custom Item Type"</td></tr>
		<tr><td>ADM Hierarchical List</td><td>Control Item</td><td>1011</td><td>0</td><td>	</td></tr>
		<tr><td>ADM Progress Bar</td><td>Control Item</td><td>5</td><td>0</td><td>Value = IntValue, Min = IntMin, Max = IntMax</td></tr>
		<tr><td>ADM Chasing Arrows</td><td>Control Item</td><td>7</td><td>0</td><td>	</td></tr>
		<tr><td>ADM Unicode Text Edit</td><td>Control Item</td><td>1100</td><td>0</td><td>Value = ADMJustify</td></tr>
		<tr><td>ADM Password Text Edit</td><td>Control Item</td><td>1200</td><td>0</td><td>	</td></tr>
	</table>

	This chart maps ADM dialog item types to Windows control types that can be used as dialog resources.

  	<table>
  		<tr><td>ADMItemType </td><td>Windows Class Name</td><td>Window Style </td><td>Comments</td></tr>

		<tr><td>ADM Frame</td><td>"Button"</td><td> BS_GROUPBOX</td><td>== kADMSunkenFrameStyle</td></tr>
		<tr><td> </td><td>"Static"</td><td>SS_BLACKRECT</td><td>== kADMBlackFrameStyle</td></tr>
    	<tr><td> </td><td>"Static"</td><td>SS_GRAYRECT</td><td>== kADMGrayFrameStyle</td></tr>
		<tr><td> </td><td>"Static"</td><td>SS_WHITERECT</td><td>== kADMRaisedFrameStyle</td></tr>
	    <tr><td> </td><td>"Static"</td><td>SS_BLACKFRAME</td><td>== kADMBlackFrameStyle</td></tr>
   		<tr><td> </td><td>"Static"</td><td>SS_GRAYFRAME</td><td>== kADMGrayFrameStyle</td></tr>
  		<tr><td> </td><td>"Static"</td><td>SS_WHITEFRAME</td><td>== kADMRaisedFrameStyle</td></tr>
    	<tr><td> </td><td>"Static"</td><td>SS_ETCHEDHORZ</td><td>== kADMSunkenFrameStyle</td></tr>
    	<tr><td> </td><td>"Static"</td><td>SS_ETCHEDVERT</td><td>== kADMSunkenFrameStyle</td></tr>
    	<tr><td> </td><td>"Static"</td><td>SS_ETCHEDFRAME</td><td>== kADMSunkenFrameStyle</td></tr>
    	<tr><td> </td><td>"ADM Frame Type"</td><td>ADMFrameStyle</td><td>== </td></tr>
		<tr><td>ADM List Box</td><td>Listbox</td><td></td><td> </td></tr>
        <tr><td> </td><td>"ADM List Box Type"</td><td>ADMListBoxStyle </td><td>== </td></tr>
  		<tr><td>ADM Picture Push Button</td><td>"ADM Picture Push Button Type"</td><td>0</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
		<tr><td>ADM Picture Radio Button</td><td>"ADM Picture Radio Button Type"</td><td>0</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
		<tr><td>ADM Picture Static</td><td>"Static"</td><td>SS_BITMAP</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_ICON</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_ENHMETAFILE</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
        <tr><td> </td><td>"ADM Picture Static Type"</td><td>0</td><td>item name == MAKEINTRESOURCE(pictureID)</td></tr>
      	<tr><td>ADM Popup List</td><td>"Combobox"</td><td>CBS_DROPDOWNLIST</td><td> </td></tr>
        <tr><td> </td><td>"ADM Popup List Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Popup Menu</td><td>"ADM Popup Menu Type"</td><td>ADMPopupMenuStyle</td><td> </td></tr>
		<tr><td>ADM Resize</td><td>"ADM Resize Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Scrollbar</td><td>"Scrollbar"</td><td>0</td><td> </td></tr>
        <tr><td> </td><td>"ADM Scrollbar Type"</td><td>0</td><td></td></tr>
		<tr><td>ADM Scrolling Popup List</td><td>"Combobox"</td><td>CBS_DROPDOWNLIST | WS_VSCROLL</td><td> </td></tr>
        <tr><td> </td><td>"ADM Scrolling Popup List Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Slider</td><td>"MSCtls_Trackbar32"</td><td>0</td><td> </td></tr>
        <tr><td> </td><td>"ADM Slider Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Spin Edit</td><td>"ADM Spin Edit Type"</td><td>ADMSpinEditStyle</td><td> </td></tr>
		<tr><td>ADM Spin Edit Popup</td><td>"Combobox"</td><td>CBS_DROPDOWN</td><td>== kADMSingleLineEditPopupStyle</td></tr>
		<tr><td> </td><td>"ADM Spin Edit Popup Type"</td><td>ADMSpinEditPopupStyle</td><td> </td></tr>
		<tr><td>ADM Spin Edit Scrolling Popup</td><td>"Combobox"</td><td>CBS_DROPDOWN | WS_VSCROLL</td><td>== kADMSingleLineEditPopupStyle</td></tr>
        <tr><td> </td><td>"ADM Spin Edit Scrolling Popup Type"</td><td>ADMSpinEditPopupStyle</td><td> </td></tr>
		<tr><td>ADM Text Check Box</td><td>"Button"</td><td>BS_CHECKBOX</td><td> </td><td> </td></tr>
        <tr><td> </td><td>"Button"</td><td>BS_AUTOCHECKBOX</td><td>  </td></tr>
        <tr><td> </td><td>"Button"</td><td>BS_3STATE</td><td> </td></tr>
        <tr><td> </td><td>"Button "</td><td>BS_AUTO3STATE</td><td> </td></tr>
        <tr><td> </td><td>"ADM Text Check Box Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Text Edit</td><td>"Edit"</td><td>ES_LEFT</td><td>== kADMLeftJustify</td></tr>
        <tr><td> </td><td>"Edit"</td><td>ES_CENTER</td><td>== kADMCenterJustify</td></tr>
        <tr><td> </td><td>"Edit"</td><td>ES_RIGHT</td><td>== kADMRightJustify</td></tr>
        <tr><td> </td><td>"Edit"</td><td>ES_NUMBER</td><td>== kADMNumbericEditStyle (Auto sets if you call SetXValue().)</td></tr>
        <tr><td> </td><td>"Edit"</td><td>ES_PASSWORD</td><td>== kADMPasswordTextEditStyle</td></tr>
        <tr><td> </td><td>"ADM Text Edit Type"</td><td>ADMTextEditStyle</td><td>== </td></tr>
		<tr><td>ADM Text Edit Multi Line</td><td>"Edit"</td><td>ES_MULTILINE</td><td>== kADMNumbericEditStyle  (Auto sets if you call SetXValue().)</td></tr>
        <tr><td> </td><td>"ADM Text Edit Multi Line Type"</td><td>0</td><td>== </td></tr>
		<tr><td>ADM Text Edit Popup</td><td>"Combobox"</td><td>CBS_DROPDOWN</td><td>== kADMSingleLineEditPopupStyle</td></tr>
        <tr><td> </td><td>"ADM Text Edit Popup Type"</td><td>ADMTextEditPopupStyle</td><td> </td></tr>
 		<tr><td>ADM Text Push Button</td><td>"Button"</td><td>BS_DEFPUSHBUTTON</td><td>== Default</td></tr>
		<tr><td> </td><td>"Button"</td><td>BS_PUSHBUTTON</td><td> </td></tr>
        <tr><td> </td><td>"Button"</td><td>BS_USERBUTTON </td><td> </td></tr>
        <tr><td> </td><td>"Button"</td><td>BS_OWNERDRAW</td><td> </td></tr>
        <tr><td> </td><td>"ADM Text Push Button Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Text Radio Button</td><td>"Button"</td><td>BS_RADIOBUTTON</td><td> </td></tr>
		<tr><td> </td><td>"Button"</td><td>BS_AUTORADIOBUTTON</td><td> </td></tr>
		<tr><td> </td><td>"ADM Text Radio Button Type"</td><td>0</td><td> </td></tr>
		<tr><td>ADM Text Static</td><td>"Static"</td><td>SS_LEFT</td><td>== kADMLeftJustify</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_CENTER</td><td>== kADMCenterJustify</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_RIGHT</td><td>== kADMRightJustify</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_LEFTNOWORDWRAP</td><td>== kADMLeftJustify</td></tr>
        <tr><td> </td><td>"Static"</td><td>SS_SIMPLE</td><td>== kADMLeftJustify</td></tr>
		<tr><td> </td><td>"ADM Text Static Type"</td><td>0</td><td> </td></tr>

		<tr><td>ADM Text Static	Multi Line</td><td>"Edit"</td><td>ES_READONLY</td><td> </td></tr>
		<tr><td> </td><td>"ADM Text Static Multi Line Type"</td><td>0</td><td> </td></tr>

		<tr><td>ADM User</td><td>"ADM User Type"</td><td>0</td><td> </td></tr>
	</table>
*/
typedef struct ADMItemSuite9
{
	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// item creation/destruction

	/** Creates a control element (item) in a dialog.
			@param inDialog The dialog object.
			@param inItemID The unique identifier of the new item. When creating
				all items in a dialog, use a sequence of numbers; radio-button items
				that have sequential ID numbers are automatically grouped. When adding an item to an
				existing dialog, use the constant \c #kADMUniqueItemID to cause ADM to
				generate a unique ID. Radio-buttons that do not have sequential ID numbers
				can be added to a radio-group object; see \c #ADMRadioGroupSuite1::Add().
			@param inItemType The item type constant, \c kADM*Type. See \c #kADMDialType and following.
			@param inBoundsRect The position and size of the new item, in local coordinates
				relative to the dialog.
			@param inInitProc A developer-defined initialization procedure for the new item,
				or \c NULL if no special initialization is needed.
			@param inUserData Developer-defined data to pass to	associate with the item, or \c NULL.
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
			@see \c #ADMDialogSuite10::CreateItem(), \c #ADMDialogSuite10::CreateNestedItem()
		*/
	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	/** Deletes an item object, calling its associated \c #ADMItemDestroyProc
		first.

		ADM automatically destroys all items in a dialog when the ADM notification for
		window closure is received. Use this function only if you are creating and
		disposing of items dynamically in response to user actions.
			@param inItem The item object.
			@return Nothing.
		*/
	void ADMAPI (*Destroy)(ADMItemRef inItem);

	// item draw proc

	/** Associates a dialog item object with a developer-defined drawing procedure.
			@param inItem The item object.
			@param inDrawProc The drawing procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);

	/** Retrieves the developer-defined drawing procedure from a dialog item.
			@param inItem The item object.
			@return The drawing procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);

	/** Calls the default drawing procedure for a dialog item from within a
		developer-defined custom drawing procedure. Typically used to draw the
		basic appearance before modifying it.
			@param inItem The item object.
			@param inDrawer The drawing object.
			@return Nothing.
		*/
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc

	/** Associates a dialog item object with a developer-defined tracking procedure.
			@param inItem The item object.
			@param inTrackProc The tracking procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);

	/** Retrieves the developer-defined event tracking procedure from a dialog item.
			@param inItem The item object.
			@return The tracking procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
 	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);

	/** Calls the default event tracking procedure for a dialog item from within a
		developer-defined custom tracking procedure.

		The behavior of a default tracker function depends on the item type. For instance,
		a slider’s default tracker checks where the mouse-down event occurs and
		moves the thumb appropriately. A button tracker inverts the button while the
		mouse is within the bounds and returns it to normal when done.
			@param inItem The item object.
			@param inTracker The tracking object.
			@return True to send a notification to the item when the mouse button
				is released, or to indicate that a keystroke event was handled.
				False to send no notification, or indicate that a keystroke event
				was not handled.
		*/
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	/** Sets the event mask for a dialog item. This determines which events are
		received by the item's event tracker.
			@param inItem The item object.
			@param inMask The mask, a logical OR of \c #ADMAction constants.
			@return Nothing.
			@see \c #SetTrackProc(), \c #DefaultTrack()
		*/
	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);

	/** Retrieves the event mask from a dialog item. Only allowed events are
		received by the item's event tracker.
			@param inItem The item object.
			@return The mask, a logical OR of \c #ADMAction constants.
		*/
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	/** Associates a dialog item object with a developer-defined
		notification-handling procedure.
			@param inItem The item object.
			@param inNotifyProc The notification procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);

	/** Retrieves the developer-defined notification-handling procedure from a dialog item.
			@param inItem The item object.
			@return The notification procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);

	/** Calls the default notification-handling procedure for a dialog item from within a
		developer-defined custom notification procedure. Use to get standard
		behaviors, such as list selection and radio button group behavior.
			@param inItem The item object.
			@param inNotifier The notification object.
			@return Nothing.
		*/
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);

	/** Sends a notification to a dialog item.
			@param inItem The item object.
			@param inNotifierType The notification type constant: see \c ADMNotifier.h.
				The main notifier for items is \c #kADMUserChangedNotifier.
			@return Nothing.
		*/
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	/** Associates a dialog item object with developer-defined notification data.
			@param inItem The item object.
			@param inUserData The notification data.
			@return Nothing.
		*/
	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);

	/** Retrieves the developer-defined notification data from a dialog item.
			@param inItem The item object.
			@return The notification data.
		*/
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	/** Associates a dialog item object with a developer-defined termination procedure.
			@param inItem The item object.
			@param inDestroyProc The termination procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);

	/** Retrieves the developer-defined termination procedure from a dialog item.
			@param inItem The item object.
			@return The termination procedure, or \c NULL if no developer-defined
				procedure has been set.
		*/
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);

	// item timer

	/** Creates a dialog item timer, which allows you to schedule an action
		for the dialog item. The action can make use of developer-defined
		data associated with the dialog item; see \c #GetUserData().
			@param inItem The item object.
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
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	/** Cancels a scheduled action associated with a dialog item. It is used if an event
		specified by the \c inAbortMask of \c #CreateTimer() occurs, or if
		you destroy the dialog item before the timer expires.
			@param inItem The item object.
			@param inTimerID The timer object containing the scheduled action.
			@return Nothing. */
	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	/** Associates developer-defined data with a dialog item, which can be used
		in developer-defined callbacks and actions scheduled with \c #CreateTimer().
			@param inItem The item object.
			@param inUserData The developer-defined data.
			@return Nothing.
		*/
	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);

	/** Retrieves developer-defined data from a dialog item.
			@param inItem The item object.
			@return The developer-defined data.
		*/
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	/** Retrieves the unique identifier of a dialog item.
			@param inItem The item object.
			@return The unique identifier.
			@see \c #Create() */
	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);

	/** Retrieves the dialog that contains a dialog item.
			@param inItem The item object.
			@return The dialog object. */
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);

	/** Retrieves the platform-specific window used for dialog item.
		Use to draw directly to the window using platform-specific code.
		See \c #ADMWindowSuite1 (for Mac OS only)
			@param inItem The item object.
			@return The window object.
		*/
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);

	/** Retrieves the list object for a dialog item that uses one. These types use lists:
		<br>\c #kADMListBoxType
		<br>\c #kADMHierarchyListBoxType
		<br>\c #kADMPopupListType
		<br>\c #kADMPopupMenuType
		<br>\c #kADMSpinEditPopupType
		<br>\c #kADMSpinEditScrollingPopupType
		<br>\c #kADMTextEditPopupType
		<br>\c #kADMTextEditScrollingPopupType
			@param inItem The item object.
			@return The list object. Use with \c #ADMListSuite4.
	*/
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);

	/** Retrieves a component element of a composite dialog item. Composite item types are:
		<br>\c #kADMListBoxType
		<br>\c #kADMHierarchyListBoxType
		<br>\c #kADMSpinEditType
		<br>\c #kADMSpinEditPopupType
		<br>\c #kADMSpinEditScrollingPopupType
		<br>\c #kADMTextEditPopupType
		<br>\c #kADMTextEditScrollingPopupType
			@param inItem The item object.
			@param inChildID The role of the component:
				\li For a list box, an \c #ADMListBoxChildID constant.
				\li For a spin-edit, an \c #ADMSpinEditChildID constant.
				\li For a spin-edit popup or scrolling popup, an \c #ADMSpinEditPopupChildID constant.
				\li For a text-edit popup, an \c #ADMTextEditPopupChildID constant.
			@return The child item object. */
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);

	/** Associates a plug-in with a dialog item.
			@param inItem The item object.
			@param inPluginRef The plug-in object.
			@return Nothing.
		*/
	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);

	/** Retrieves a reference to the plug-in that owns a dialog item.
			@param inItem The item object.
			@return The plug-in object. */
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	/** Modifies the control type of a custom dialog item. Do not
		use if the original type is anything other than \c #kADMUserType.
			@param inItem The item object.
			@param inItemType The new item type constant.
			@return Nothing.
		*/
	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);

	/** Retrieves the control type of a dialog item.
			@param inItem The item object.
			@return The item type constant or \c NULL.
		*/
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);

	/** Modifies the visual style of a dialog item. Valid values
		depend on the control type; see \c kADM*Style in \c ADMItem.h.
		Call \c #Update() to redraw the item with the new appearance.
			@param inItem The item object.
			@param inItemStyle The new item style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);

	/** Retrieves the visual style of a dialog item.
			@param inItem The item object.
			@return The item style constant.
		*/
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);

	// item state accessors

	/** Turns the visibility state on or off for a dialog item.
			@param inItem The item object.
			@param inShow True to make the item visible, false to hide it.
			@return Nothing.
		*/
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);

	/** Reports whether a dialog is currently in the visible state.
			@param inItem The item object.
			@return True if the item is currently shown, false if it is hidden.
			@see \c #Show()
		*/
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);

	/** Enables or disables a dialog item. An enabled item can be selected.
		A disabled item is dimmed and cannot be selected.
			@param inItem The item object.
			@param inEnable True to enable the item, false to disable it.
			@return Nothing.
		*/
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);

	/** Reports whether a dialog item is currently enabled.
			@param inItem The item object.
			@return True if the item is currently enabled, false if disabled.
			@see \c #Enable()
		*/
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);

	/** Activates or deactivates a dialog item.	An active item has the
		keyboard focus. There can only be one active item in a dialog.
		In Windows, this can be any item in the dialog. In Mac OS, only
		text edit items can be active. Activating an item automatically
		inactivates all others.
			@param inItem The item object.
			@param inActivate True to activate the item, false to deactivate it.
			@return Nothing.
		*/
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	/** Reports whether a dialog item is currently active.
			@param inItem The item object.
			@return True if the item is currently active, false if it is inactive.
			@see \c #Activate()
		*/
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);

	/** Sets the "known" state of a dialog item. In the "known" state, the item has
		a valid value, whose type depends on the item type. In the "unknown" state,
		the value is invalid.
			\li For a boolean item (checkbox or radiobutton)
				the unknown value is an intermediate state.
			\li	For a text value, the unknown value is the empty string.
			\li For spin-edit items, setting to "unknown" disables the spin buttons,
				because the value of the edit field cannot be incremented or decremented.
			@param inItem The item object.
			@param inKnown True to make the item known, false to make it unknown.
			@return Nothing.
		*/
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);

	/** Reports whether a dialog item has a valid value. A user cannot enter
		an invalid value. A value becomes "unknown" only when you set its "known" state
		to false with \c #Known().
			@param inItem The item object.
			@return True if the item has a valid value, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);

	// item bounds accessors

	/** Sets the size of a dialog item, relative to its own origin.
			@param inItem The item object.
			@param inLocalRect The bounding box, where the \c top and \c left values are 0,
				and the \c bottom and \c right members indicate the size.
			@return Nothing
		*/
	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);

	/** Retrieves the size of a dialog item, relative to its own origin.
			@param inItem The item object.
			@param outLocalRect [out] A buffer in which to return the bounding box,
				where the \c top and \c left values are 0,
				and the \c bottom and \c right members indicate the size.
			@return Nothing
		*/
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);

	/** Sets the size and position of a dialog item within the dialog.
			@param inItem The item object.
			@param inBoundsRect The bounding box in local dialog coordinates.
			@return Nothing
			@see \c #Move()
		*/
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);

	/** Retrieves the size and position of a dialog item within the dialog.
			@param inItem The item object.
			@param outBoundsRect [out] A buffer in which to return the bounding box,
				in local dialog coordinates.
			@return Nothing
		*/
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);

	/** Retrieves the optimal dimensions of a dialog item within the dialog.
		For most items, this value is generated considering the text of the
		item and its graphic elements’ bounds (such as a button’s frame, or a check box).
		For picture items, it is the size of the largest associated picture.
			@param inItem The item object.
			@param outBestSize [out] A buffer in which to return the X and Y
				components of the size.
			@return Nothing
		*/
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	/** Modifies the absolute position of a dialog item.
			@param inItem The item object.
			@param inHorizPosition The new horizontal coordinate in screen coordinates.
			@param inVertPosition The new vertical coordinate screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);

	/** Modifies the size of a dialog item.
			@param inItem The item object.
			@param inWidth The new width in pixels.
			@param inHeight The new height in pixels.
			@return Nothing
		*/
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations

	/** Transforms a point from local coordinates for a dialog item to screen coordinates.
			@param inItem The item object.
			@param ioPoint [in, out] A buffer in which to pass the point in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);

	/** Transforms a point from screen coordinates to local coordinates for a dialog item.
			@param inItem The item object.
			@param ioPoint [in, out] A buffer in which to pass the point in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);

	/** Transforms a rectangle from local coordinates for a dialog item to screen coordinates.
			@param inItem The item object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in local coordinates,
				and return it in screen coordinates.
			@return Nothing
		*/
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);

	/** Transforms a rectangle from screen coordinates to local coordinates for a dialog item.
			@param inItem The item object.
			@param ioRect [in, out] A buffer in which to pass the rectangle in screen coordinates,
				and return it in local coordinates.
			@return Nothing
		*/
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);

	// item display

	/** Marks a dialog item as being in need of redrawing.
			@param inItem The item object.
			@return Nothing
			@see Update()
		*/
	void ADMAPI (*Invalidate)(ADMItemRef inItem);

	/** Marks an area within a dialog item as being in need of redrawing.
			@param inItem The item object.
			@param inInvalRect The rectangle, in local coordinates relative to the dialog.
			@return Nothing
		*/
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);

	/** Redraws a dialog item that has been invalidated, or any invalid areas within it.
			@param inItem The item object.
			@return Nothing
		*/
	void ADMAPI (*Update)(ADMItemRef inItem);

	// cursor ID accessors

	/** Sets the cursor shape for a dialog item; that is, the cursor shown when the
		pointer position is within the item bounds.
			@param inItem The item object.
			@param inPluginRef This plug-in, which owns the cursor ID until it is
				reset to the default arrow.
			@param inCursorID The cursor resource identifier, developer-defined or
				one of the predefined cursor constants, \c kADM*CursorID. See @ref AdmResources.
			@param inCursorName Not used.
			@return True on success.
		*/
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	/** Retrieves the cursor shape for a dialog item; that is, the cursor shown when the
		pointer position is within the item bounds.
			@param inItem The item object.
			@param outPluginRef [out] A buffer in which to return the plug-in
				that owns the cursor ID; see \c #SetCursorID().
			@param outCursorID [out] A buffer in which to return the cursor resource
				identifier, or 0 if no ID has been assigned. The ID can be developer-defined
				or a predefined cursor constant, \c kADM*CursorID. See @ref AdmResources.
			@param outCursorName Not used.
			@return Nothing
		*/
	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	/** Sets the picture resource for a dialog item with a picture.  Resources
 		can be identified by either numeric ID or name. ADM provides some
		predefined numeric IDs for use here.

	    These item types have associated pictures:
			<br>\c #kADMPictureCheckBoxType
			<br>\c #kADMPicturePushButtonType
			<br>\c #kADMPictureRadioButtonType
			<br>\c #kADMPictureStaticType

			@param inItem The item object.
			@param inPictureResID The picture resource identifier. Can be
				developer-defined, or one of the predefined picture constants,
				\c kADM*PictureID. See @ref AdmResources.
			@param inPictureResName The name of the picture resource.
			@return Nothing
		*/
	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture resource for a dialog item that has one.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the picture resource
				identifier, or 0 if no ID has been assigned. The ID can be developer-defined
				or a predefined picture constant, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the picture
				resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetPictureID(), \c #SetPicture()
		*/
	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture resource to use for a dialog item when it is selected.
		The resource can be identified by numeric identifier or name.
		See \c #SetPictureID().
			@param inItem The item object.
			@param inPictureResID The picture resource identifier. Can be
				developer-defined, or one of the predefined picture constants,
				\c kADM*PictureID. See @ref AdmResources.
			@param inPictureResName The name of the picture resource.
			@return Nothing
		*/
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture resource used for a dialog item when it is selected, if any.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the picture resource
				identifier, or 0 if no ID has been assigned. The ID can be developer-defined
				or a predefined picture constant, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the picture
				resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetSelectedPictureID()
		*/
	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture resource to use for a dialog item when it is disabled.
		The resource can be identified by numeric identifier or name.
		See \c #SetPictureID().
			@param inItem The item object.
			@param inPictureResID The picture resource identifier. Can be
				developer-defined, or one of the predefined picture constants,
				\c kADM*PictureID. See @ref AdmResources.
			@param inPictureResName The name of the picture resource.
			@return Nothing
		*/
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the resource identifier of the picture used for a dialog item when it is disabled.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the picture resource
				identifier, or 0 if no ID has been assigned. The ID can be developer-defined
				or a predefined picture constant, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the picture
				resource name, or the empty string if no name has been assigned.
			@return Nothing
			@see \c #SetDisabledPictureID()
		*/
	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	/** Sets the tooltip that is shown when the cursor hovers over a
		dialog item, using a C string.
			@param inItem The item object.
			@param inTipString The C string.
			@return Nothing
		*/
	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);

	/** Sets the tooltip that is shown when the cursor hovers over a
		dialog item, using a Unicode string.
			@param inItem The item object.
			@param inTipString The Unicode string.
			@return Nothing
		*/
	void ADMAPI (*SetTipStringW)(ADMItemRef inItem, const ADMUnicode* inTipString);

	/** Retrieves the tooltip that is shown when the cursor hovers over a
		dialog item, as a C string.
			@param inItem The item object.
			@param outTipString [out] A buffer in which to return the C string.
			@param inMaxLength The number of characters in the buffer.
			@return Nothing
		*/
	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);

	/** Retrieves the tooltip that is shown when the cursor hovers over a
		dialog item, as a Unicode string.
			@param inItem The item object.
			@param outTipString [out] A buffer in which to return the Unicode string.
			@param inMaxLength The number of characters in the buffer.
			@return Nothing
		*/
	void ADMAPI (*GetTipStringW)(ADMItemRef inItem, ADMUnicode* outTipString, ADMInt32 inMaxLength);

	/** Reports the length of a dialog item's tooltip text as a C string. Use to allocate
		a buffer for \c #GetTipString().
			@param inItem The item object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);

	/** Reports the length of a dialog item's tooltip text as a Unicode string. Use to allocate
		a buffer for \c #GetTipStringW().
			@param inItem The item object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTipStringLengthW)(ADMItemRef inItem);

	/** Enables or disables tooltips for a dialog item.
			@param inItem The item object.
			@param inEnable True to enable tooltips for the item, false to disable them.
			@return Nothing.
		*/
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);

	/** Reports whether tooltips are currently enabled for a dialog item.
			@param inItem The item object.
			@return True if tooltips are currently enabled, false if disabled.
		*/
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);

	/** Shows the tooltip for a dialog item.
			@param inItem The item object.
			@param inWhere The position at which to display the tooltip,
				in screen coordinates.
			@return Nothing.
		*/
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);

	/** Hides the tooltip for a dialog item.
			@param inItem The item object.
			@return Nothing.
		*/
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);

	// item text accessors

	/** Sets the font style for text in a dialog item that displays text.
			@param inItem The item object.
			@param inFont The font style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);

	/** Retrieves the font style used for text in a dialog item.
			@param inItem The item object.
			@return The font style constant.
		*/
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	/** Sets the text to be displayed in a dialog item, using a C string.
		Text is displayed as the title of a frame, as the contents of an
		editable or static text box, as the label of a text check-box or
		radio-button, or as programmed for custom items.
		It is not used for items of other types.
			@param inItem The item object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);

	/** Sets the text to be displayed in a dialog item, using a Unicode string.
		Text is displayed as the title of a frame, as the contents of an
		editable or static text box, and as the label of a text check-box or
		radio-button, or as programmed for custom items.
		It is not used for items of other types.
			@param inItem The item object.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*SetTextW)(ADMItemRef inItem, const ADMUnicode* inText);

	/** Retrieves the text from a dialog item as a C string.
		Text is displayed as the title of a frame, as the contents of an
		editable or static text box, and as the label of a text check-box or
		radio-button, or as programmed for custom items.
		It is not used for items of other types.
			@param inItem The item object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLength() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);

	/** Retrieves the text from a dialog item as a Unicode string.
		Text is displayed as the title of a frame, as the contents of an
		editable or static text box, and as the label of a text check-box or
		radio-button, or as programmed for custom items.
		It is not used for items of other types.
			@param inItem The item object.
			@param outText [out] A buffer in which to return the text string.
			@param inMaxLength The number of characters in the buffer. The text
				is truncated to this length. Use \c #GetTextLengthW() to allocate a
				buffer.
			@return Nothing.
		*/
	void ADMAPI (*GetTextW)(ADMItemRef inItem, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** Reports the length of a dialog item's text as a C string. Use to allocate
		a buffer for \c #GetText().
			@param inItem The item object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);

	/** Reports the length of a dialog item's text as a Unicode string. Use to allocate
		a buffer for \c #GetTextW().
			@param inItem The item object.
			@return The number of characters in the text.
		*/
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMItemRef inItem);

	/** Sets the maximum length for a dialog item's text. The user
		cannot enter more characters than this.
			@param inItem The item object.
			@param inLength The maximum number of characters.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);

	/** Retrieves the maximum length for a dialog item's text.
			@param inItem The item object.
			@return The maximum number of characters.
		*/
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);

	/** Selects and highlights all of the characters in the text
		of a dialog item, if that item is active and displays editable text.
			@param inItem The item object.
			@return Nothing.
			@see Activate()
		*/
	void ADMAPI (*SelectAll)(ADMItemRef inItem);

	/** Sets the text selection of an active edit-text dialog item. If
		the start and end character indices are the same, sets the text insertion
		point to that position but does not select any text.
			@param inItem The item object.
			@param inSelStart The 0-based index of the first selected character within the item text string.
			@param inSelEnd The 0-based index of the last selected character within the item text string.
				If greater than the text length, it is set to the last character.
	 		@return Nothing.
	 	*/
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);

	/** Retrieves the text selection of an active edit-text dialog item. If there
		is no selection, the start and end character indices are the same, and
		indicate the text insertion point.
			@param inItem The item object.
			@param outSelStart [out] A buffer in which to return
				the 0-based index of the first selected character
				within the item text string.
			@param outSelEnd [out] A buffer in which to return
				the 0-based index of the last selected character
				within the item text string. This cannot be more than the text length.
	 		@return Nothing.
	 	*/
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	/** Sets the justification style for a dialog item that displays text.
			@param inItem The item object.
			@param inJustify The justification constant.
			@return Nothing.
		*/
	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);

	/** Retrieves the justification style for a dialog item that displays text.
			@param inItem The item object.
			@return The justification constant.
		*/
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);

	/** Sets the measurement units used for a dialog item that displays numeric values.
	   	A units value can be automatically appended to the text; see \c #ShowUnits().
			@param inItem The item object.
			@param inUnits The units constant. A value of \c #kADMNoUnits
				means that units not displayed.
			@return Nothing.
		*/
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);

	/** Retrieves the measurement units used for numeric values in a dialog item.
			@param inItem The item object.
			@return The units constant.
		*/
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);

	// item value accessors

	/** Sets the degree of precision used for numeric values in a dialog item.
		If the user enters more digits than the precision allows, the value is rounded.
		If the precision is set to zero, decimals can be entered but are displayed as integers.
		To restrict input to integers, use the item style \c #kADMIntegerNumeric.
			@param inItem The item object.
			@param inNumberOfDecimalPlaces The number of decimal places of precision.
			@return Nothing.
		*/
	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	/** Retrieves the degree of precision used for numeric values in a dialog item.
			@param inItem The item object.
			@return The number of digits that can be entered after the decimal point.
		*/
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);

	/** Sets the boolean value of a dialog item. Use to set the on-off state of
		a check box or radio-button item. For radio-button items, the value is
		constrained by the style of the group; see \c #ADMRadioButtonStyle.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);

	/** Retrieves the boolean value of a dialog item. Use to get the on-off state of
		a check box or radio button item. For types that display a numeric value,
		returns true for any non-zero value.
			@param inItem The item object.
			@return The value.
		*/
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);

	/** Sets the integer value of a dialog item.
		A text item displays the text representation of the value.
		For a slider or scroll bar, the thumb moves to the correct position.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	/** Retrieves the integer value of a dialog item. If the value is
		floating point,	it is rounded to the nearest integer.
			@param inItem The item object.
			@return The value.
		*/
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);

	/** Sets the fixed numeric value of a dialog item.
		A text item displays the text representation of the value.
		For a slider or scroll bar, the thumb moves to the correct position.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);

	/** Retrieves the fixed numeric value of a dialog item. If the value is an
		integer, it is converted to a fixed decimal.
			@param inItem The item object.
			@return The value.
		*/
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);

	/** Sets the floating-point numeric value of a dialog item.
		A text item displays the text representation of the value.
		For a slider or scroll bar, the thumb moves to the correct position.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);

	/** Retrieves the floating-point numeric value of a dialog item. If the value
		is an integer, it is converted to floating-point.
			@param inItem The item object.
			@return The value.
		*/
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);

	/** Sets the minimum integer value of a dialog item that displays a
		numeric value. Entered values less than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);

	/** Retrieves the minimum integer value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);

	/** Sets the minimum fixed numeric value of a dialog item that displays a
		numeric value. Entered values less than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);

	/** Retrieves the minimum fixed numeric value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);

	/** Sets the maximum integer value of a dialog item that displays a
		numeric value. Entered values greater than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);

	/** Retrieves the maximum integer value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);

	/** Sets the minimum floating-point numeric value of a dialog item that displays a
		numeric value. Entered values less than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);

	/** Retrieves the minimum floating-point numeric value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);

	/** Sets the maximum fixed numeric value of a dialog item that displays a
		numeric value. Entered values greater than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);

	/** Retrieves the maximum fixed numeric value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);

	/** Sets the maximum floating-point numeric value of a dialog item that displays a
		numeric value. Entered values greater than this are set to this value.
			@param inItem The item object.
			@param inValue The new value.
			@return Nothing.
		*/
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);

	/** Retrieves the maximum floating-point numeric value of a dialog item.
			@param inItem The item object.
			@return The value.
		*/
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);

	/** Sets the increment for the draggable thumb of a scrollbar or slider,
		and for the arrow buttons of a spin-edit dialog item.
			@param inItem The item object.
			@param inIncrement The new increment value.
			@return Nothing.
		*/
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);

	/** Retrieves the increment for the draggable thumb of a scrollbar or slider,
		and for the arrow buttons of a spin-edit dialog item.
			@param inItem The item object.
			@return The increment value.
		*/
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);

	/** Sets the increment for the end arrows and for the bar area between the thumb and ends
		of a scrollbar dialog item.
			@param inItem The item object.
			@param inIncrement The new increment value.
			@return Nothing.
		*/
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);

	/** Retrieves the increment for the end arrows and for the bar area between the thumb and ends
		of a scrollbar dialog item.
			@param inItem The item object.
			@return The increment value.
		*/
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);

	/** Sets whether units are allowed as part of user input for a dialog item
		that displays a numeric value.
			@param inItem The item object.
			@param inAllowUnits True to allow units, false to disallow.
			@return Nothing.
		*/
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);

	/** Reports whether the units are allowed as part of user input for a dialog item
		that displays a numeric value.
			@param inItem The item object.
			@return True if units are allowed.
		*/
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	/** Sets whether arithmetic operators can be entered and used to compute
		the value for a dialog item that displays numeric values.
			@param inItem The item object.
			@param inAllowMath True to allow math, false to disallow.
			@return Nothing.
		*/
	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);

	/** Reports whether arithmetic operators can be entered and used to compute
		the value for a dialog item that displays numeric values.
			@param inItem The item object.
			@return True if math is allowed.
		*/
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);

	/** Sets the procedure that converts floating-point values to strings in a
		text-entry dialog item that requires numeric values. This overrides the
		ADM default conversion procedure.
			@param inItem The item object.
			@param inProc The conversion procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);

	/** Retrieves the procedure that converts floating-point values to strings in a
		text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@return The conversion procedure, or \c NULL if no developer-defined procedure
				has been set.
		*/
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);

	/** Converts a floating-point value to a C string using the ADM default conversion
		procedure for a text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@param inValue The floating-point value.
			@param outText [out] A buffer in which to return the converted value.
			@param inMaxLength The number of characters in the buffer.
			@return True if the conversion is successful.
			@see \c #ADMItemFloatToTextProc
		*/
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	/** Converts a floating-point value to a Unicode string using the ADM default conversion
		procedure for a text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@param inValue The floating-point value.
			@param outText [out] A buffer in which to return the converted value.
			@param inMaxLength The number of characters in the buffer.
			@return True if the conversion is successful.
			@see \c #ADMItemFloatToTextProc
		*/
	ADMBoolean ADMAPI (*DefaultFloatToTextW)(ADMItemRef inItem, float inValue, ADMUnicode* outText,
		ADMInt32 inMaxLength);

	/** Sets the procedure that converts string values to floating-point in a
		text-entry dialog item that requires numeric values. This overrides the
		ADM default conversion procedure.
			@param inItem The item object.
			@param inProc The conversion procedure.
			@return Nothing.
		*/
	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);

	/** Retrieves the procedure that converts string values to floating-point in a
		text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@return  The conversion procedure, or \c NULL if no developer-defined procedure
				has been set.
		*/
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);

	/** Converts a C string value to a floating-point value using the ADM default conversion
		procedure for a text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@param inValue The string value.
			@param outValue [out] A buffer in which to return the converted value.
			@return True if the conversion is successful.
			@see \c #ADMItemTextToFloatProc
		*/
	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);

	/** Converts a Unicode string value to a floating-point value using the ADM default conversion
		procedure for a text-entry dialog item that requires numeric values.
			@param inItem The item object.
			@param inValue The string value.
			@param outValue [out] A buffer in which to return the converted value.
			@return True if the conversion is successful.
			@see \c #ADMItemTextToFloatProc
		*/
	ADMBoolean ADMAPI (*DefaultTextToFloatW)(ADMItemRef inItem, const ADMUnicode* inText, float* outValue);

	/** Sets whether measurement units are appended to numeric values
		displayed as text in a dialog item. Set the units with \c #ADMItemSuite9::SetUnits().
		If the units value is \c #kADMNoUnits, units are not displayed regardless of this state.
			@param inItem The item object.
			@param inShowUnits True to show units, false to show only numeric value.
			@return Nothing.
		*/
	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);

	/** Reports whether units are appended to numeric values displayed as text in a dialog item.
			@param inItem The item object.
			@return True if units are shown.
		*/
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	/** Reports whether a value change in a dialog item was a percentage change.
		Use, for instance, in a notification procedure to track a history of
		changes to an object’s scale.
			@param inItem The item object.
			@return True if the notification was the result of a text value change
				that included a percentage, such as 1in+10% or 150%.
				If the item has a custom text-to-float procedure, returns true if that
				procedure called \c #DefaultTextToFloat() to do the actual parsing.
		*/
	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// hierarchy list accessor

	/** Retrieves the hierarchy list from a dialog item that has one.
			@param inItem The item object. See \c #ADMHierarchyListSuite5.
			@return The hierarchy list object, or \c NULL if there is no
				hierarchy list associated with the item.
		*/
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);

	// item group accessors

	/** Adds an item to an item group.
			@param inGroup The group object, an item of type \c #kADMItemGroupType.
			@param inItem The item object.
			@return Nothing.
	*/
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);

	/** Removes an item from an item group.
			@param inGroup The group object, an item of type \c #kADMItemGroupType.
			@param inItem The item object.
			@return Nothing.
	*/
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)

	/** Sets the picture for a dialog item that can have a picture.
		These types can have associated pictures:
			<br>\c #kADMPictureCheckBoxType
			<br>\c #kADMPicturePushButtonType
			<br>\c #kADMPictureRadioButtonType
			<br>\c #kADMPictureStaticType

			@param inItem The item object.
			@param inPicture The icon object for the picture.
			@return Nothing
			@see \c #SetPictureID()
		*/
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);

	/** Retrieves the picture for a dialog item that has one.
			@param inItem The item object.
			@return The icon object for the picture,
				or \c NULL if the item has no picture.
			@see \c #SetPicture()
		*/
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	/** Sets the picture to use when the item is selected, for a dialog item
		that has a picture. See \c #SetPicture().
			@param inItem The item object.
			@param inPicture The icon object for the picture.
			@return Nothing
			@see \c #SetSelectedPictureID()
		*/
	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);

	/** Retrieves the picture used when the item is selected, for a dialog item that has one.
			@param inItem The item object.
			@return The icon object for the picture,
				or \c NULL if the item has no picture.
			@see \c #SetSelectedPicture()
		 */
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	/** Sets the picture to use when the item is disabled, for a dialog item
		that has a picture.	See \c #SetPicture().
			@param inItem The item object.
			@param inPicture The icon object for the picture.
			@return Nothing
			@see \c #SetDisabledPictureID()
		*/
	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);

	/** Retrieves the picture used when the item is disabled, for a dialog item that has one.

			@param inItem The item object.
			@return The icon object for the picture,
				or \c NULL if the item has no picture.
			@see \c #SetDisabledPicture()
		 */
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);

	// popup control accessors

	/** Associates a predefined or custom dialog with a dialog item of type \c #kADMPopupControlType.
		This dialog pops up when the popup arrow is pressed. If both \c inPopupItemID and \c inDialog
		are \c NULL, uses the predefined slider dialog.
			@param inItem The item object, of type \c #kADMPopupControlType.
			@param inPopupItemID The type of the popup, \c #kADMPopupSliderDialogID or
				\c #kADMPopupDialDialogID, or \c NULL to use a custom dialog.
			@param inDialog The dialog to use for the popup, when the popup item ID is \c NULL,
				or \c NULL to use a predefined popup dialog. Create the
				custom dialog popup using \c #ADMDialogSuite10::Create() with the style
				\c #kADMPopupControlDialogStyle.
			@return Nothing.
		*/
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);

	/** Retrieves the popup dialog associated with a dialog item of type \c #kADMPopupControlType.
			@param inItem The item object.
			@return The dialog object.
			@see \c #SetPopupDialog()
		*/
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);


	// Basic color accessors for all applicable ADM items
	/** Sets the foreground color of a dialog item.
			@param inItem The item object.
			@param inColor The color constant.
			@return Nothing.
		*/
	void ADMAPI (*SetForeColor)(ADMItemRef inItem, ADMColor inColor);

	/** Retrieves the foreground color of a dialog item.
			@param inItem The item object.
			@return The color constant.
		*/
	ADMColor ADMAPI (*GetForeColor)(ADMItemRef inItem);

	/** Sets the background color of a dialog item.
			@param inItem The item object.
			@param inColor The color constant.
			@return Nothing.
		*/
	void ADMAPI (*SetBackColor)(ADMItemRef inItem, ADMColor inColor);

	/** Retrieves the background color of a dialog item.
			@param inItem The item object.
			@return The color constant.
		*/
	ADMColor ADMAPI (*GetBackColor)(ADMItemRef inItem);


	//Accessor functions for Rollover state.

	/** Sets the picture to use for a dialog item when it is in the rollover state, if
		it has a picture and the rollover property.
		The resource can be identified by numeric identifier or name.
		See \c #SetPictureID().

			@param inItem The item object.
			@param inPictureResID The picture resource identifier. Can be
				developer-defined, or one of the predefined picture constants,
				\c kADM*PictureID. See @ref AdmResources.
			@param inPictureResName The name of the picture resource.
			@return Nothing.
			@see \c #SetHasRollOverProperty(), \c #SetInRollOverState() */
	void ADMAPI (*SetRolloverPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** Retrieves the picture used for a dialog item when it is in the rollover state, if
		it has the rollover property.
			@param inItem The item object.
			@param outPictureResID [out] A buffer in which to return the picture resource
				identifier, or 0 if no ID has been assigned. The ID can be developer-defined
				or a predefined picture constant, \c kADM*PictureID. See @ref AdmResources.
			@param outPictureResName [out] A buffer in which to return the picture
				resource name, or the empty string if no name has been assigned.
			@see \c #SetHasRollOverProperty(), \c #SetInRollOverState()
		*/
	void ADMAPI (*GetRolloverPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** Sets the picture to use for a dialog item when it is in the rollover state, if
		it has the rollover property.
			@param inItem The item object.
			@param inPicture The picture object.
			@return Nothing.
			@see \c #SetHasRollOverProperty(), \c #SetInRollOverState()
		*/
	void ADMAPI (*SetRolloverPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	/** Retrieves the picture used for a dialog item when it is in the rollover state, if
		it has the rollover property.
			@param inItem The item object.
			@return The picture object or \c NULL if the item has no picture.
			@see \c #SetHasRollOverProperty(), \c #SetInRollOverState()
		*/
	ADMIconRef ADMAPI (*GetRolloverPicture)(ADMItemRef inItem);

	// Set/Get the Has Rollover property - whether or not the item wants to have rollover
	/** Sets whether a dialog item has the rollover property, which determines appearance
		when the mouse hovers over it.
			@param inItem The item object.
			@param inRollover True to give the item the rollover property, false to remove it.
			@return Nothing.
			@see \c #SetInRollOverState(), \c #SetRolloverPicture()
		*/
	void ADMAPI (*SetHasRollOverProperty)(ADMItemRef inItem, ADMBoolean inRollover);

	/** Reports whether a dialog item has the rollover property, which determines appearance
		when the mouse hovers over it.
			@param inItem The item object.
			@return True if the item has the rollover property.
		*/
	ADMBoolean ADMAPI (*GetHasRollOverProperty)(ADMItemRef inItem);

	/** Turns the rollover state on or off, if the item has the rollover property.
			@param inItem The item object.
			@param inRolloverState True to turn rollover on, false to turn it off.
			@return Nothing.
			@see \c #SetHasRollOverProperty(), \c #SetRolloverPicture()
		*/
	void ADMAPI (*SetInRollOverState)(ADMItemRef inItem, ADMBoolean inRolloverState);

	/** Reports whether the rollover state is on or off, if the item has the rollover property.
			@param inItem The item object.
			@return True if rollover state is on, false if it is off.
			@see \c #SetHasRollOverProperty(), \c #SetRolloverPicture()
		*/
	ADMBoolean ADMAPI (*IsInRollOverState)(ADMItemRef inItem);

	/** Sets whether to override roman script forcing of item fonts for a text-display dialog item.
		This can be set on creation by specifying the option \c #kADMIgnoreRomanFontForcing.
			@param inItem The dialog item.
			@param inIgnoreForceRoman True to override forcing, false to continue forcing.
			@return Nothing.
	*/
	void ADMAPI (*IgnoreForceRoman)(ADMItemRef inItem, ADMBoolean inIgnoreForceRoman);

	/** Sets whether a dialog item can accept the input focus. Use only to allow a
		picture push-button to receive focus.
			@param inItem The item object, of type \c #kADMPicturePushButtonType.
			@param inWantsFocus True to allow the item to accept focus, false to disallow it.
			@return Nothing.
		*/
	void ADMAPI (*SetWantsFocus)(ADMItemRef inItem, ADMBoolean inWantsFocus);

	/** Reports whether a dialog item can accept the input focus.
			@param inItem The item object.
			@return True if the item can accept focus, false if it cannot.
		*/
	ADMBoolean ADMAPI (*GetWantsFocus)(ADMItemRef inItem);

	/**	Inserts a dialog item into the focus order of its containing dialog,
		also called the tab order. This is the order in which items
		get input focus when the user presses the Tab key.

		To set the entire focus order for a dialog, Use
		\c #ADMDialogSuite10::BeginAdjustingFocusOrder() to open a sequence
		of calls to \c #SetFirstFocus() and to this function. When the
		sequence is finished, call \c #ADMDialogSuite10::DoneAdjustingFocusOrder().

		To rearrange an existing focus list, call \c #MoveFocusItem()
			@param inItem An item object currently in the focus list.
			@param inNextItem The item object to place next in the list.
	 	 	@return An error code.
		*/
	ADMErr ADMAPI (*SetNextFocus)(ADMItemRef inItem, ADMItemRef inNextItem);

	/**	Inserts the first dialog item into the focus order of its containing dialog,
		also called the tab order. This is the order in which items
		get input focus when the user presses the Tab key.

		To set the entire focus order for a dialog, Use
		\c #ADMDialogSuite10::BeginAdjustingFocusOrder() to open a sequence
		of calls to this and \c #SetNextFocus(). When the sequence is finished,
		call \c #ADMDialogSuite10::DoneAdjustingFocusOrder().

		To rearrange an existing focus list, call \c #MoveFocusItem()
			@param inItem The item object.
	 	 	@return An error code.
		*/
	ADMErr ADMAPI (*SetFirstFocus)(ADMItemRef inItem);

	/** Rearranges the order of an existing focus list; see \c #SetFirstFocus().
			@param inSource The item object to be moved.
			@param inTarget An item object in the focus list to place the
				source object after, or \c NULL to place it at the beginning
				of the list.
			@return An error code.
		*/
	ADMErr ADMAPI (*MoveFocusItem)(ADMItemRef inSource, ADMItemRef inTarget);
}
ADMItemSuite9;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMItemOld__
#ifdef MAC_ENV
#include "ADMItemOld.h"
#else
#include ".\Legacy\ADMItemOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMItem__
