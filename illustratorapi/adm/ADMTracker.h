/*******************************************************************************
*
* ADMTracker.h -- ADM Tracker Suite
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
* Started by Dave Lazarony, 25 Mar 1996
*
********************************************************************************/

/** @file ADMTracker.h ADM Tracker Suite */

#ifndef __ADMTracker__
#define __ADMTracker__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// -----------------------------------------------------------------------------

/** Mouse capture state constants, returned by \c #ADMTrackerSuite2::GetMouseState()  */
typedef enum {
	/** The normal state when the mouse is not captured. */
	kADMMouseNormal,
	/** The captured state, entered when the tracker receives a mouse-down event. */
	kADMMouseCaptured,
	/** Not used. */
	kADMMouseUncaptured
}
ADMMouseState;

/** A date-time value, as returned by \c #ADMTrackerSuite2::GetTime(). */
typedef unsigned long ADMTime;


// -----------------------------------------------------------------------------
//	Tracker event codes

/** Low-level events that can trigger a tracker callback procedure.
	One of these constants is returned by \c #ADMTrackerSuite2::GetAction().
	Some events are platform-specific, as noted. */
typedef enum
{
	/** Cursor moved. The specific MovedDown and MovedUp cases are generally of more interest. */
	kADMMouseMoveAction			= 1,
	/** Cursor moved down. */
	kADMMouseMovedDownAction	= 1,

	/** Any mouse button down.  */
	kADMButtonDownAction		= 2,
	/** In Windows only, left button down. */
	kWinLeftButtonDownAction		= 2,
	/** In Windows only, middle button down. */
	kWinMiddleButtonDownAction		= 3,
	/** In Windows only, right button down. */
	kWinRightButtonDownAction		= 4,

	/** Shift key down */
	kADMShiftKeyDownAction		= 5,
	/** Menu key down */
	kADMMenuKeyDownAction		= 6,
	/** In Mac OS only, Command key down */
	kMacCommandKeyDownAction	= 6,
	/** In Windows only, Ctrl key down. */
	kWinControlKeyDownAction		= 6,
	/** Any modifier key down */
	kADMModKeyDownAction		= 7,
	/** In Mac OS only, Option key down */
	kMacOptionKeyDownAction		= 7,
	/** In Windows only, Alt key down. */
	kWinAltKeyDownAction			= 7,
	/** In Mac OS only, Control key down */
	kMacControlKeyDownAction	= 8,

	/** Space bar pressed */
	kADMSpaceKeyDownAction		= 9,
	/** Tab key pressed */
	kADMTabKeyDownAction		= 10,
	/** Enter or Return key pressed */
	kADMEnterAction				= 11,

	/** Cursor moved up.  */
	kADMMouseMovedUpAction		= -1,

	/** Any mouse button released. */
	kADMButtonUpAction			= -2,
	/** In Windows only, left button released. */
	kWinLeftButtonUpAction			= -2,
	/** In Windows only, middle button released. */
	kWinMiddleButtonUpAction		= -3,
	/** In Windows only, right button released. */
	kWinRightButtonUpAction			= -4,

	/** Shift key released */
	kADMShiftKeyUpAction		= -5,
	/** Menu key released */
	kADMMenuKeyUpAction			= -6,
	/** In Mac OS only, Command key released */
	kMacCommandKeyUpAction		= -6,
	/** In Windows only, Ctrl key released. */
	kWinControlKeyUpAction			= -6,
	/** Any modifier key released */
	kADMModKeyUpAction			= -7,
	/** In Mac OS only, Option key released */
	kMacOptionKeyUpAction		= -7,
	/** In Windows only, Alt key released. */
	kWinAltKeyUpAction				= -7,
	/** In Mac OS only, Control key released */
	kMacControlKeyUpAction		= -8,

	/** Space bar released */
	kADMSpaceKeyUpAction		= -9,
	/** Tab key released */
	kADMTabKeyUpAction			= -10,

	/** Mouse cursor is leaving area. */
	kADMLeaveAction				= -11,
	/** Not used */
	kADMUncapturedButtonUpAction= -12,
	/** Not used */
	kWinUncapturedLeftButtonUpAction	= -12,
	/** Not used */
	kWinUncapturedMiddleButtonUpAction	= -13,
	 /** Not used */
	kWinUncapturedRightButtonUpAction	= -14,

	/** Any key pressed except modifiers and first of double-byte characters. */
	kADMKeyStrokeAction			= -15,

	/** Internal */
	kADMDummyAction				= 0x7FFFFFFF
}
ADMAction;


// -----------------------------------------------------------------------------
//	Tracker event masks


/** Bit flags for an event mask, which determines what events
	trigger calls to an object's tracker procedure. Pass a logical
	OR of these values as the action-mask parameter for an object's
	set-mask function such as \c #ADMItemSuite9::SetMask().

	Some event masks are platform-specific, as noted.
	*/
enum ADMActionBitFlags {
	/** Track no events. */
	kADMNullMask				= 0x00000000,

	/** Track uncaptured events. Not used. */
	kADMUncapturedActionMask	= 0x00000001,

	/** Track mouse-moved-down events.  */
	kADMMouseMovedDownMask		= 0x00000002,

	/** Track all mouse-button-down events. */
	kADMButtonDownMask			= 0x00000004,
	/** In Windows only. Track left-button-down events. */
	kWinLeftButtonDownMask		= 0x00000004,
	/** In Windows only. Track middle-button-down events. */
	kWinMiddleButtonDownMask	= 0x00000008,
	/** In Windows only. Track right-button-down events. */
	kWinRightButtonDownMask		= 0x00000010,

	/** Track shift-key-down events. */
	kADMShiftKeyDownMask		= 0x00000020,
	/** Track menu-key-down events. */
	kADMMenuKeyDownMask			= 0x00000040,
	/** In Mac OS only. Track Command-key-down events. */
	kMacCommandKeyDownMask		= 0x00000040,
	/** In Windows only. Track Ctrl-key-down events. */
	kWinControlKeyDownMask		= 0x00000040,
	/** Track any modifier-key-down events */
	kADMModKeyDownMask			= 0x00000080,
	/** In Mac OS only. Track Option-key-down events. */
	kMacOptionKeyDownMask		= 0x00000080,
	/** In Windows only. Track Alt-key-down events. */
	kWinAltKeyDownMask			= 0x00000080,
	/** In Mac OS only. Track Control-key-down events. */
	kMacControlKeyDownMask		= 0x00000100,

	/** Track space-bar-down events */
	kADMSpaceKeyDownMask		= 0x00000200,
	/** Track tab-key-down events */
	kADMTabKeyDownMask			= 0x00000400,
	/** Track Enter/Return-key-down events */
	kADMEnterMask				= 0x00000800,

	/** Track mouse-moved-up events */
	kADMMouseMovedUpMask		= 0x00020000,

	/** Track any button-release events */
	kADMButtonUpMask			= 0x00040000,
	/** In Windows only. Track left-button-release events. */
	kWinLeftButtonUpMask		= 0x00040000,
	/** In Windows only. Track middle-button-release events. */
	kWinMiddleButtonUpMask		= 0x00080000,
	/** In Windows only. Track right-button-release events. */
	kWinRightButtonUpMask		= 0x00100000,
	/** Track shift-key-release events */
	kADMShiftKeyUpMask			= 0x00200000,
	/** Track menu-key-release events */
	kADMMenuKeyUpMask			= 0x00400000,
	/** In Mac OS only. Track Command-key-release events. */
	kMacCommandKeyUpMask		= 0x00400000,
	/** In Windows only. Track Ctrl-key-release events. */
	kWinControlKeyUpMask		= 0x00400000,
	/** Track any modifier-key-release events */
	kADMModKeyUpMask			= 0x00800000,
	/** In Mac OS only. Track Option-key-release events. */
	kMacOptionKeyUpMask			= 0x00800000,
	/** In Windows only. Track Alt-key-release events. */
	kWinAltKeyUpMask			= 0x00800000,
	/** In Mac OS only. Track Control-key-release events. */
	kMacControlKeyUpMask		= 0x01000000,

	/** Track space-bar-release events */
	kADMSpaceKeyUpMask			= 0x02000000,
	/** Track tab-key-release events */
	kADMTabKeyUpMask			= 0x04000000,

	/** Track mouse-leave events.  */
	kADMLeaveMask				= 0x08000000,
	/** Track all uncaptured button-up events (including Windows-only events). */
	kADMUncapturedButtonUpMask	= 0x10000000,

	/** Track all keystroke events. */
	kADMKeyStrokeMask			= 0x80000000
};

/** Track all events. */
#define kADMAllActionsMask ((unsigned long) 0xFFFFFFFF)


// -----------------------------------------------------------------------------
//	Tracker modifier key masks

/** Bit flags for event modifiers. A logical OR of these is returned by
	\c #ADMTrackerSuite2::GetModifiers().  Modifiers indicate
	event states that are simultaneous with the event that triggered
	a tracker.

	Some event modifiers are platform-specific, as noted.
	*/
typedef enum
{
	/** Clears all modifier flags */
	kADMNullModifier			= 0x00000000,

	/** Any mouse button down. */
	kADMButtonDownModifier		= 0x00000004,
	/** In Windows only. Left mouse button down. */
	kWinLeftButtonDownModifier		= 0x00000004,
	/** Middle mouse button down. */
	kADMMiddleButtonDownModifier= 0x00000008,
	/** In Windows only. Middle mouse button down. */
	kWinMiddleButtonDownModifier	= 0x00000008,
	/** Right mouse button down. */
	kADMRightButtonDownModifier	= 0x00000010,
	/** In Windows only. Right mouse button down. */
	kWinRightButtonDownModifier		= 0x00000010,

	/** Shift key down. */
	kADMShiftKeyDownModifier	= 0x00000020,
	/** Menu key down  */
	kADMMenuKeyDownModifier		= 0x00000040,
	/** In Mac OS only. Command key down. */
	kMacCommandKeyDownModifier	= 0x00000040,
	/** In Windows only. Ctrl key down. */
	kWinControlKeyDownModifier		= 0x00000040,
	/** Any modifier key down */
	kADMModKeyDownModifier		= 0x00000080,
	/** In Mac OS only. Option key down. */
	kMacOptionKeyDownModifier	= 0x00000080,
	/** In Windows only. Alt key down. */
	kWinAltKeyDownModifier			= 0x00000080,
	/** In Mac OS only. Control key down. */
	kMacControlKeyDownModifier	= 0x00000100,
	/** Space bar down */
	kADMSpaceKeyDownModifier	= 0x00000200,
	/** Tab key down */
	kADMTabKeyDownModifier		= 0x00000400,
	/** Double click */
	kADMDoubleClickModifier		= 0x00000800,

	/** Caps lock on */
	kADMCapsLockOnModifier		= 0x00001000,

	/** Triple click */
	kADMTripleClickModifier		= 0x00002000,

	/** Mouse click that can invoke a context menu. */
    kADMContextualMenuClickModifier = 0x00004000,

	/** Internal */
	kADMDummyModifier			= 0xFFFFFFFF
}
ADMModifiers;


// -----------------------------------------------------------------------------
//	Virtual keys

/** Virtual key mappings
	@see \c #ADMTrackerSuite2::GetVirtualKey(),
	\c #ADMTrackerSuite2::GetKeysState() */
enum {

	/**  */
	kADMUnknownKey			= 0x0000,
	/**  */
	kADMCancelKey			= 0x0001,
	/**  */
	kADMEnterKey			= 0x0003,
	/**  */
	kADMHomeKey				= 0x0004,
	/**  */
	kADMEndKey				= 0x0005,
	/**  */
	kADMPageUpKey			= 0x0006,
	/**  */
	kADMPageDownKey			= 0x0007,
	/**  */
	kADMBackspaceKey		= 0x0008,
	/**  */
	kADMTabKey				= 0x0009,
	/**  */
	kADMInsertKey			= 0x000A,
	/**  */
	kADMReturnKey			= 0x000D,
	/**  */
	kADMF1Key				= 0x000E,
	/**  */
	kADMF2Key				= 0x000F,
	/**  */
	kADMF3Key				= 0x0010,
	/**  */
	kADMF4Key				= 0x0011,
	/**  */
	kADMF5Key				= 0x0012,
	/**  */
	kADMF6Key				= 0x0013,
	/**  */
	kADMF7Key				= 0x0014,
	/**  */
	kADMF8Key				= 0x0015,
	/**  */
	kADMF9Key				= 0x0016,
	/**  */
	kADMF10Key				= 0x0017,
	/**  */
	kADMF11Key				= 0x0018,
	/**  */
	kADMF12Key				= 0x0019,
	/**  */
	kADMClearKey			= 0x001A,
	/**  */
	kADMEscapeKey			= 0x001B,
	/**  */
	kADMLeftKey				= 0x001C,
	/**  */
	kADMRightKey			= 0x001D,
	/**  */
	kADMUpKey				= 0x001E,
	/**  */
	kADMDownKey				= 0x001F,
	/**  */
	kADMSpaceKey			= 0x0020,

		// Virtual keys from 0x0020 through the slash key (/) are their ASCII equivalents
	/** The ' character.  */
	kADMApostropheKey		= 0x0027,	// '
	/**  The , character. */
	kADMCommaKey			= 0x002C,	// ,
	/** The - character.  */
	kADMMinusKey			= 0x002D,	// -
	/** The . character.  */
	kADMPeriodKey			= 0x002E,	// .
	/** The / character.  */
	kADMSlashKey			= 0x002F,	// /

	// kADM0Key - kADM9Key are the same as ASCII '0' thru '9' (0x30 - 0x39)

 	kADM0Key				= 0x0030,
 	kADM1Key,
 	kADM2Key,
 	kADM3Key,
 	kADM4Key,
 	kADM5Key,
 	kADM6Key,
 	kADM7Key,
 	kADM8Key,
 	kADM9Key,
	/** The ; character. */
	kADMSemicolonKey		= 0x003B,	// ;
	/** The = character. */
	kADMEqualKey			= 0x003D,	// =

	// kADMAKey - kADMZKey are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)

 	kADMAKey				= 0x0041,
 	kADMBKey,
 	kADMCKey,
 	kADMDKey,
 	kADMEKey,
 	kADMFKey,
 	kADMGKey,
 	kADMHKey,
 	kADMIKey,
 	kADMJKey,
 	kADMKKey,
 	kADMLKey,
 	kADMMKey,
 	kADMNKey,
 	kADMOKey,
 	kADMPKey,
 	kADMQKey,
 	kADMRKey,
 	kADMSKey,
 	kADMTKey,
 	kADMUKey,
 	kADMVKey,
 	kADMWKey,
 	kADMXKey,
 	kADMYKey,
 	kADMZKey,

	/** The [ character. */
	kADMLeftSqrBracketKey	= 0x005B,	// [
	/** The \ character. */
	kADMBackSlashKey		= 0x005C,	// "\"
	/** The ] character.  */
	kADMRightSqrBracketKey	= 0x005D,	// ] (last ASCII value)

	/**  */
 	kADMBackTickKey			= 0x0060,
 	/**  */
	kADMDeleteKey			= 0x007F,

		// key pad keys
	/**  */
	kADMKP0Key				= 0x00E0,
	/**  */
	kADMKP1Key				= 0x00E1,
	/**  */
	kADMKP2Key				= 0x00E2,
	/**  */
	kADMKP3Key				= 0x00E3,
	/**  */
	kADMKP4Key				= 0x00E4,
	/**  */
	kADMKP5Key				= 0x00E5,
	/**  */
	kADMKP6Key				= 0x00E6,
	/**  */
	kADMKP7Key				= 0x00E7,
	/**  */
	kADMKP8Key				= 0x00E8,
	/**  */
	kADMKP9Key 				= 0x00E9,
	/**  */
	kADMKPEqualKey 			= 0x00EA,
	/**  */
	kADMKPMultiplyKey		= 0x00EB,
	/**  */
	kADMKPMinusKey 			= 0x00EC,
	/**  */
	kADMKPPlusKey 			= 0x00ED,
	/**  */
	kADMKPDivideKey		 	= 0x00EE,
	/**  */
	kADMKPDecimalKey		= 0x00EF,

 	/**  */
 	kADMCommandKey			= 0x00F0,
 	/**  */
 	kADMShiftKey            = 0x00F1,
 	/**  */
 	kADMCapsLockKey			= 0x00F2,
 	/**  */
 	kADMOptionKey			= 0x00F3,
 	/**  */
 	kADMControlKey			= 0x00F4,
 	/**  */
 	kADMF13Key				= 0x00F5,
 	/**  */
 	kADMF14Key				= 0x00F6,
 	/**  */
 	kADMF15Key				= 0x00F7,
 	/**  */
 	kADMF16Key				= 0x00F8,
 	/**  */
 	kADMHelpKey				= 0x00F9,


		// kADMDoubleByteChar indicates that we have a double-byte character.
		// This occurs only if the kADMTrackerGetsDoubleByteInput host option is set.
	/**  */
	kADMDoubleByteChar		= 0x8000,

	/** Internal */
	kADMDummyKey			= 0xFFFF

};

/** Number of virtual key codes. */
#define kADMVirtualKeyCount 256
/** Number of mouse button codes. */
#define kADMMouseButtonCount 32
/** Array of virtual-key values. */
typedef ADMBoolean ADMVirtualKeyArray[kADMVirtualKeyCount];

// =============================================================================
//		* ADM Tracker Suite
// =============================================================================

/** Tracker suite name. */
#define kADMTrackerSuite "ADM Tracker Suite"
/** Tracker suite version */
#define kADMTrackerSuiteVersion2 2
/** Tracker suite version */
#define kADMTrackerSuiteVersion kADMTrackerSuiteVersion2

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides access to low-level user-interaction events, such
	as mouse-up, mouse-down, and mouse-move. To work with high-level events,
	such as the value of an item changing, use the \c #ADMNotifierSuite2.

	You can modify or replace the default behavior of a dialog or dialog
	item by providing your own handler, in the form of a tracker callback
	procedure, \c #ADMItemTrackProc, associated with the dialog or item. See
	\c #ADMDialogSuite10::SetTrackProc() and \c #ADMItemSuite9::SetTrackProc().

	The behavior of list entries (\c #ADMEntryRef or \c #ADMListEntryRef) is handled
	by the tracker callback (\c #ADMEntryTrackProc) of the containing list
	(\c #ADMListRef or	\c #ADMHierarchyListRef). See \c #ADMListSuite4::SetTrackProc()
	and \c #ADMHierarchyListSuite5::SetTrackProc().

	To register an interest in specific low-level events, set the \e event \e mask
	for the dialog, item, or list. See, for example, \c #ADMItemSuite9::SetMask().
	Only those events of interest trigger your tracking procedure.

	The tracker object, \c #ADMTrackerRef, provides the event context.
	It stores input state information, and provides a snapshot of input
	activity that is in progress when the tracker is activated.

	To invoke the default behavior of a dialog, item, or list, call that object's
	default tracker handler from within your handler; for example,
	\c #ADMItemSuite9::DefaultTrack().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMTrackerSuite and \c #kADMTrackerSuiteVersion2.
*/
typedef struct ADMTrackerSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/** Retrieves the cursor position when the triggering event
		for a tracker occurred, or the current cursor position.
			@param inTracker The tracker object, or \c NULL to get the current cursor position.
			@param outPoint [out] A buffer in which to return the position,
				in coordinates relative to the object in which the event occurred,
				or in screen coordinates for the current position.
			@return Nothing.
		*/
	void ADMAPI (*GetPoint)(ADMTrackerRef inTracker, ADMPoint* outPoint);

	/** Retrieves the low-level event that triggered a tracker.
			@param inTracker The tracker object.
			@return The action constant for the event.
		*/
	ADMAction ADMAPI (*GetAction)(ADMTrackerRef inTracker);

	/** Retrieves the modifiers that were active when the triggering event
		for a tracker occurred, or the current modifier keys.
			@param inTracker The tracker object, or \c NULL to get the current state.
			@return The modifiers, a logical OR of modifier bit-flag values.
		*/
	ADMModifiers ADMAPI (*GetModifiers)(ADMTrackerRef inTracker);

	/** Reports whether a specific event triggered a tracker.
			@param inTracker The tracker object.
			@param inAction The action constant for the event.
			@return	True if the tracker was triggered by the event, false otherwise.
		*/
	ADMBoolean ADMAPI (*TestAction)(ADMTrackerRef inTracker, ADMAction inAction);

	/** Reports whether a specific combination of modifiers was active when
		the triggering event for a tracker occurred.
			@param inTracker The tracker object.
			@param inModifier The modifier combination, a logical OR of modifier bit-flag values.
			@return	True if the modifier combination was active, false otherwise.
		*/
	ADMBoolean ADMAPI (*TestModifier)(ADMTrackerRef inTracker, ADMModifiers inModifier);

	/** Retrieves the time at which the event that triggered a tracker occurred.
			@param inTracker The tracker object.
			@return The time value.
		*/
	ADMTime ADMAPI (*GetTime)(ADMTrackerRef inTracker);

	/** Terminates a tracker procedure.
			@param inTracker The tracker object.
			@return Nothing.
		*/
	void ADMAPI (*Abort)(ADMTrackerRef inTracker);

	/** Retrieves the current mouse state; normal (uncaptured) or captured.
		The mouse is captured when the tracker receives a mouse-down event.
			@param inTracker The tracker object.
			@return The mouse state constant.
		*/
	ADMMouseState ADMAPI (*GetMouseState)(ADMTrackerRef inTracker);

	/** Not implemented. */
	void ADMAPI (*ReleaseMouseCapture)(ADMTrackerRef inTracker);

	/** Retrieves the current keypress state as a virtual key value,
		using a cross-platform mapping of special keys. See \c kADM*Key.
			@param inTracker The tracker object.
			@return The virtual key constant.
		*/
	ADMChar ADMAPI (*GetVirtualKey)(ADMTrackerRef inTracker);

	/** Retrieves the most recent character input from the keyboard.
		Initial value is \c #kADMUnknownKey.
			@param inTracker The tracker object.
			@return The ASCII value of the character that was input.
		*/
	ADMChar ADMAPI (*GetCharacter)(ADMTrackerRef inTracker);

	/**	Retrieves the current keypress state for all keys,
		using a cross-platform mapping of special keys. See \c kADM*Key.
			@param outVirtualKeyArray [out] A buffer in which to return an array whose members
				correspond to all defined virtual key codes. A true value for a key code indicates
				that the key is currently pressed.
			@return True if any keys are down.
 		*/
  	ADMBoolean ADMAPI (*GetKeysState)(ADMVirtualKeyArray *outVirtualKeyArray);

}
ADMTrackerSuite2;

/** Tracker suite name */
typedef ADMTrackerSuite2 ADMTrackerSuite;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMTracker__
