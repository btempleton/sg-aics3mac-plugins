/*******************************************************************************
*
* ADMDialogGroup.h -- ADM Dialog Group Suite
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
* Started by Matt Foster, 28 Sep 1996
*
********************************************************************************/

/** @file ADMDialogGroup.h ADM Dialog Group Suite */

#ifndef __ADMDialogGroup__
#define __ADMDialogGroup__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
//	Error codes.

/** @ingroup Errors \c #ADMDialogGroupSuite6 error code: Error setting host dialog
 		with \c #ADMDialogGroupSuite6::SetDialogGroupInfo().
 		Can be caused by duplicate host dialog names. */
#define kDockHostConflictError	'DOCK'
/** @ingroup Errors \c #ADMDialogGroupSuite6 error code: A specified tab
		was not found in a dialog group by \c #ADMDialogGroupSuite6::SetTabGroup(). */
#define kTabGroupNotFoundError	'T!FD'
/** @ingroup Errors \c #ADMDialogGroupSuite6 error code: Attempted to add a dialog
		to a group as a dock when it is already docked.  */
#define kAlreadyDockedError		'DCKD'


// -----------------------------------------------------------------------------
//	For the xxGroupInfo() functions, positionCode is a code to restore a
//	dialog's position within a docked/tabbed group. The group is
//	referred to by name, this being the name of the ADM Dialog that is
//	the first tab in the top dock of the group.
//
//	You don't need to know what positionCode means, but if you are curious:
//
//	byte		  		meaning
//	----		 		------------------------------
//	  1 (0x000000ff)	bits 0-7, dock position, 0 is no dock, 1 is first docked (i.e. top dock), 2 etc.
//	  2 (0x0000ff00)	bits 8-15, tab position, 0 is no tab group, 1 is the 1st tab, 2 etc.
//	  3 (0x00010000)	bit 16, boolean, 1 for front tab.
//	  3 (0x00020000)	bit 17, boolean, 0 is zoom up, 1 is zoom down/collapsed.
//	  3 (0x00040000)	bit 18, boolean, 0 is in hidden dock, 1 is in visible dock.
//	3-4 (0x00780000)	4 bits 19-22, pane index, 0 is no pane, 1 is the 1st pane counting from the center of the screen, etc.
//	3-4 (0x01800000)	2 bits 23-24, pane location, see enum ADMPaneLocation
//	  4 (0x06000000)	2 bits 25-26, pane state, see enum ADMPaneState
//	  4 (0x08000000)	bit 27, 1 for palette drawer open in iconic pane
//	  4 (0x10000000)	bit 28, boolean, tab/icon hidden in parent: 1 for hidden, 0 for visible
//	  4 (0x00000000)	reserved, currently unused
//
//	So for stand alone palette, the tab, dock position code is (0, ?, 0, 0)

/** Dialog group position code: The default code for standalone palette. */
#define kADM_DPDefaultCode 0x00030000

/** Dialog group position value: Dock position. 0 is no dock, 1 is the topmost dock in the group. */
#define kADM_DPDockBit 0

/** Dialog group position value: Tab position. 0 is no tab, 1 is the leftmost tab is the dock.  */
#define kADM_DPTabBit 8

/** Dialog group position flag: True if this tab is currently at the front (exposed) within its tab group.
	For a dialog to actually be shown, its own visibility must be true, it must
	be the front tab in its tab group, and floating dialogs must not be toggled off,
	as with the Tab key or \c #ADMDialogGroupSuite6::ToggleAllFloatingDialogs().
	@see \c #ADMDialogGroupSuite6::IsDockReallyVisible().
	*/
#define kADM_DPFrontTabBit 16

/** Dialog group position flag: True if the dialog is zoomed up, false if zoomed down/collapsed. */
#define kADM_DPZoomBit 17

/** Dialog group position flag: True if the docked dialog is visible, false if it is hidden.
	For a dialog to actually be shown, its own visibility must be true, it must
	be the front tab in its tab group, and floating dialogs must not be toggled off,
	as with the Tab key or \c #ADMDialogGroupSuite6::ToggleAllFloatingDialogs().
	@see \c #ADMDialogGroupSuite6::IsDockReallyVisible().
	*/
#define kADM_DPDockVisibleBit 18

/** Frame-docked window pane index offset.  */
#define kADM_DPFrameDockIndexBit 19

/** Frame-docked window pane location offset.  */
#define kADM_DPFrameDockLocationBit 23

/** Frame-docked window pane state bit offset. */
#define kADM_DPFrameDockPaneStateBit 25

/** Frame-docked palette drawer open bit offset.  */
#define kADM_DPDrawerBit 27

/** Tab/icon mode icon hidden bit offset. */
#define kADM_DPTabHiddenBit		28

// WARNING: Illustrator uses a floating point value to store this dock code.  That means that we must avoid using bits 23 and up!

	// dialog position code masks
/** Dialog group position mask. Provides access to the dock position byte. */
#define kADM_DPDockMask					0x000000ff

/** Dialog group position mask. Provides access to the tab position byte. */
#define kADM_DPTabMask					0x0000ff00

/** Dialog group position mask. Provides access to the front-tab position bit flag. */
#define kADM_DPFrontTabMask				0x00010000

/** Dialog group position mask. Provides access to the zoom position bit flag. */
#define kADM_DPZoomMask					0x00020000

/** Dialog group position mask. Provides access to the dock-visible position bit flag. */
#define kADM_DPDockVisibleMask			0x00040000

/** Dialog group position mask. Provides access to the frame-docked window pane index byte. */
#define kADM_DPFrameDockIndexMask		0x00780000

/** Dialog group position mask. Provides access to the frame-docked window pane location byte. */
#define kADM_DPFrameDockLocationMask	0x01800000

/** Dialog group position mask. Provides access to the frame-docked window pane state. */
#define kADM_DPFrameDockPaneStateMask	0x06000000

/** Dialog group position mask. Provides access to the frame-docked open drawer. */
#define kADM_DPDrawerMask				0x08000000

/** Tab/iconic mode icon hidden bit mask. */
#define kADM_DPTabHiddenMask	0x10000000

/** The edge of the frame (the main application window or screen) to which
	a frame-docked palette is docked. A value of \c #kADM_DPFrameDockLocationBit. */
enum ADMPaneLocation
{
	/** This pane docked at the top edge of the frame. */
 	kADM_DPTopPane,
 	/** This pane docked at the bottom edge of the frame. */
 	kADM_DPBottomPane,
 	/** This pane docked at the left edge of the frame. */
 	kADM_DPLeftPane,
 	/** This pane docked at the right edge of the frame. */
 	kADM_DPRightPane,
 	kADM_DPDummy = 0xFFFFFFFF
};

/** Expansion state constants for panes in a dialog-group position code. */
enum ADMPaneState
{
	kADM_PaneExpanded,
	kADM_PaneIconic,
	kADM_PaneDummy = 0xFFFFFFFF
};

// strings for saving palette state into preference file. Deprecated with the
// introduction of workspaces plug-in.

// deprecated with the introduction	of workspaces plug-in.
/** @deprecated Preference key for palette state: screen location.  */
#define kADM_DPLocationStr "Location"

/** @deprecated Preference key for palette state: dimensions, can be saved only for resizable, standalone palettes. */
#define kADM_DPSizeStr "Size"

/** @deprecated Preference key for palette state: visibility. */
#define kADM_DPVisibleStr "Visible"

/** @deprecated Preference key for palette state: docking code. */
#define kADM_DPDockCodeStr "DockCode"

/** @deprecated Preference key for palette state: docking group. */
#define kADM_DPDockGroupStr "DockGroup"

/** @deprecated Maximum number of characters allowed in a docking group name string
	(including \c NULL terminator). */
#define kADM_DPDockGroupStrMaxLen 65

// -----------------------------------------------------------------------------

/** Pane layout mode, controls whether a pane is sized automatically or by the user.
	@see /c #ADMPaneProperties */
enum ADMPaneLayoutMode
{
	/** The pane is automatically sized to fill the bottom of the screen (in Mac OS),
		or the bottom of the parent window (in Windows). */
	kADM_PaneModeAutoFlow,
	/** The pane size can be set by the user. */
	kADM_PaneModeManual,
	kADM_PaneModeDummy = 0xFFFFFFFF
};

/** Pane properties, which control sizing for a pane and its associated icon
    when it is minimized or iconified.
	@see /c #ADMDialogGroupSuite6::SetPaneProperties(), <br>
		/c #ADMDialogGroupSuite6::GetPaneProperties() */
struct ADMPaneProperties
{
	/** Width of the associated icon when the pane is minimized or iconified. */
	ADMUInt16 iconicWidth;
	/** Whether a pane is sized automatically or by the user. */
	ADMPaneLayoutMode layoutMode;
};

// =============================================================================
//		* ADM Dialog Group Suite
// =============================================================================

/** Dialog group suite name */
#define kADMDialogGroupSuite "ADM Dialog Group Suite"
/** Dialog group suite version  */
#define kADMDialogGroupSuiteVersion6 6

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides access to all defined dialogs, and allows you to
	control the overall visibility of floating dialogs, as the user does
	with the Tab key.

	This suite also handles the grouping of dialogs into tabbed and
	docked palette groups. A dialog group can contain one or more
	tab groups or \e docks, arranged vertically, which in turn contain
	one or more tabbed palettes, arranged horizontally within the tab group.
	Member dialogs must be one of the tabbed, floating styles, which include
	tabbed, toolbar, and control palette.

	A floating dialog or group can also be docked to the frame of the
	main application window.

	You can refer to a dialog group using the name of the first (leftmost) tab
	of the first (topmost) dock, obtained with \c #GetDialogGroupInfo().

	Each dialog in a group contains coded information about the state and
	position of the dialog within its group. Obtain an information value
	from the dialog with \c #GetDialogGroupInfo(), and use functions
	in this suite to access the encoded information.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMDialogGroupSuite and \c #kADMDialogGroupSuiteVersion6.
	*/
struct ADMDialogGroupSuite6
{

	// dialog info

	/** Retrieves the unique name of a dialog, as assigned on creation.
			@param inDialog The dialog object.
			@param outName [out] A buffer in which to return the name string.
			@return An ADM error code, \c #kNoErr on success.
			@see \c #ADMDialogSuite10::Create(), \c #ADMDialogSuite10::GetDialogName()
		*/
	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	/** Retrieves the group name for the dialog group that contains a dialog, and
		the position of the dialog within the group.
			@param inDialog The dialog object.
			@param outName [out] A buffer in which to return the name string. This
				is the name of the leftmost tabbed dialog of the topmost dock group.
			@param outPositionCode [out] A buffer in which to return the position information,
				a logical OR of position bit flags and codes, \c kADM_DP*Bit. See \c #kADM_DPDockBit.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	/** Positions a dialog relative to a dialog group. Can move a dialog into or out of
		a dialog group or palette pane.
			@param inDialog The dialog object.
			@param inGroupName The group. This is the name of the leftmost
				tabbed dialog of the topmost dock group.
			@param inPositionCode The position information,	a logical OR of
				position bit flags and codes, \c kADM_DP*Bit. See \c #kADM_DPDockBit.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

	/** Reports whether a dialog is currently standalone, meaning it is not
		part of a dialog group.
			@param inPositionCode The position code for the dialog, as
				returned by \c #GetDialogGroupInfo().
			@return True if the dialog is not docked, or tabbed with another
				palette, or frame-docked; false otherwise.
	*/
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

	/** Reports whether a dialog is currently in the visible state.
		For a dialog to actually be shown, its own visibility must be true, it must
		be the front tab in its tab group, and floating dialogs must not be toggled off,
		as with the Tab key or \c #ToggleAllFloatingDialogs().
			@param inPositionCode The position code for the dialog, as
				returned by \c #GetDialogGroupInfo().
			@return True if the dialog is in the visible state, false otherwise.
			@see \c #IsDockReallyVisible(), \c #IsFrontTab()
		*/
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);

	/** Reports whether a dialog is currently at the front of its tab group.
		For a dialog to actually be shown, its own visibility must be true, it must
		be the front tab in its tab group, and floating dialogs must not be toggled off,
		as with the Tab key or \c #ToggleAllFloatingDialogs().
			@param inPositionCode The position code for the dialog, as
				returned by \c #GetDialogGroupInfo().
			@return True if the dialog is at the front of its tab group, false otherwise.
			@see \c #IsDockReallyVisible(), \c #IsFrontTab()
		*/
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// Not typically needed.
	/** Reports whether a dialog is currently collapsed or open within its dialog group.
			@param inPositionCode The position code for the dialog, as
				returned by \c #GetDialogGroupInfo().
			@return True if the dialog is collapsed, false otherwise.
		*/
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	/** Adds a tabbed palette to dialog group, as the last (rightmost) tab
		in a specified tab group, or dock.
			@param inDialog The tabbed-palette dialog object.
			@param inTabGroupName The name of the first (leftmost) tabbed
				palette in the	tab group.
			@param inBringToFront True to expose this tab, false otherwise.
			@return An ADM error code, \c #kNoErr on success, \c #kTabGroupNotFoundError
				if the named tab is not a first tab in the group.
		*/
	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);

 	// dialog list accessors

	/** Retrieve the number of defined dialogs. Use with \c #GetNthDialog() to
		iterate through dialogs.
			@param  outCount [out] A buffer in which to return the number of dialogs.
			@return An ADM error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);

	/** Retrieves a dialog by position index. Use with \c #CountDialogs() to
		iterate through all defined dialogs.
			@param inIndex The 0-based position index.
			@param outDialog [out] A buffer in which to return the dialog object.
			@return An ADM error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);

	/** Retrieves a dialog by name.
			@param inName The name string, as assigned on creation.
			@param outDialog [out] A buffer in which to return the dialog object.
			@return An ADM error code, \c #kNoErr on success.
			@see \c #ADMDialogSuite10::Create(), \c #GetDialogName()
		*/
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	/** Toggles the visibility state of all floating dialogs. If all floating
		dialogs are currently shown, this call hides them. If all or some of them
		are hidden, the call shows them all.
			@return Nothing.
			@see \c #ToggleAllButNoCloseFloatingDialogs(), \c #ShowAllFloatingDialogs()
		*/
	void ADMAPI (*ToggleAllFloatingDialogs)(void);

	/** Toggles the visibility state of all floating dialogs, except those
		without close boxes, such as the tool palette. If all closeable floating
		dialogs are currently shown, this call hides them. If all or some of them
		are hidden, the call shows them all.
			@return Nothing.
			@see \c #ToggleAllFloatingDialogs()
		*/
	void ADMAPI (*ToggleAllButNoCloseFloatingDialogs)(void);

	/** Shows or hides all floating dialogs.
			@param inShow True to show dialogs, false to hide them.
			@return Nothing.
			@see \c #ToggleAllFloatingDialogs()
		*/
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);

	/** defer distribution of tabbed palettes. */
	void ADMAPI (*DeferTabDialogsDistribution)(ADMBoolean defer);

	/** Reports whether a dialog in a group is currently actually shown.
		For a dialog to actually be shown, its own visibility must be true, it must
		be the front tab in its tab group, and floating dialogs must not be toggled off,
			@param inDialog The dialog object.
			@return True if the dialog is actually shown on screen, false if it
				is hidden for any reason.
			@see \c #IsDockVisible(), \c #IsFrontTab(), \c #ToggleAllFloatingDialogs()
		*/
	ADMBoolean ADMAPI (*IsDockReallyVisible)(ADMDialogRef inDialog);
	
	/** Retrieves all dialog or palette panes. If the actual number of panes is greater
		than the size of the array passed, the array is filled to
		capacity, the actual pane count is returned, and the function returns \c #kNoErr.
		You can increase the size of the array and call the function again to
		get all the panes.

		This is useful for saving and restoring workspaces.
			@param paneArray [out] A buffer in which to return an array of pane objects.
			@param paneCount [in, out] A buffer in which to pass number of elements
				allocated in the pane array, and return the actual number of panes.
		*/
	ADMErr ADMAPI (*GetPanes)(ADMPaneRef *paneArray, ADMUInt16 &paneCount);

	/** Sets properties for a pane, which control sizing.
			@param inPane			The pane object.
			@param inProperties	 The new properties.
		*/
	ADMErr (*SetPaneProperties)(ADMPaneRef inPane, const ADMPaneProperties &inProperties);

	/** Retrieves the properties for a pane.
			@param inPane			The pane object.
			@param outProperties [out] A buffer in which to return the current pane properties.
		*/
	ADMErr (*GetPaneProperties)(ADMPaneRef inPane, ADMPaneProperties &outProperties);

};

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMDialogGroupOld__
#ifdef MAC_ENV
#include "ADMDialogGroupOld.h"
#else
#include ".\Legacy\ADMDialogGroupOld.h"
#endif
#endif


// -----------------------------------------------------------------------------

#endif	// __ADMDialogGroup__
