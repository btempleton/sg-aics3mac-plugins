/***********************************************************************/
/*                                                                     */
/* ADMDialogGroupOld.h                                                 */
/* Old versions of ADM Dialog Group Suite                              */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMDialogGroupOld__
#define __ADMDialogGroupOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// -----------------------------------------------------------------------------
//	For the xxGroupInfo() functions, positionCode is a code to restore a
//	dialog's position within a docked/tabbed group. The group is
//	referred to by name, this being the name of the ADM Dialog that is
//	the first tab in the top dcok of the group.
//
//	You don't need to know what positionCode means, but if you are curious:
//
//	byte		  		meaning
//	----		 		------------------------------
//	1 (0x000000ff)		dock position. 0 is no dock, 1 is first docked (i.e. top dock), 2 etc.
//	2 (0x0000ff00)		tab position, 0 is no tab group, 1 is the 1st tab, 2 etc.
//	3 (0x00010000)		bit 16, boolean, 1 for front tab.
//	3 (0x00020000)		bit 17, boolean, 0 is zoom up, 1 is zoom down.
//	3 (0x00040000)		bit 18, boolean, 0 is in hidden dock, 1 is in visible dock.
//	3 (0x00080000)		bit 19, boolean, 1 for a docked frame-dockable window (ex. control palette).
//	3 (0x00100000)		bit 20, boolean, 1 for a frame-dockable window docked to the bottom
//	4 (0x00000000)		reserved. currently unused
//
//	So for stand alone palette, the tab, dock position code is (0, ?, 0, 0)
//

/** Frame-docked window boolean offset. Valid through ADMDialogGroupSuite5. */
#define kADM_DPFrameDockBit 19
/** Frame-docked-to-bottom boolean offset. Valid through ADMDialogGroupSuite5. */
#define kADM_DPFrameDockToBottomBit 20

///** Frame-docked window boolean mask. Valid through ADMDialogGroupSuite5. */
#define kADM_DPFrameDockMask 0x00080000
///** Frame-docked-to-bottom boolean mask. Valid through ADMDialogGroupSuite5. */
#define kADM_DPFrameDockToBottomMask 0x00100000


// =============================================================================
//		* ADM Dialog Group Suite, version 1
// =============================================================================

#define kADMDialogGroupSuiteVersion1 1
#define kADMDialogGroupSuiteVersion 1
#define kADMDialogGroupVersion kADMDialogGroupSuiteVersion1

// -----------------------------------------------------------------------------

typedef struct ADMDialogGroupSuite1
{

	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// The queries below take a docking position code obtained from above functions or prefs

		// You should always create a palette that is not stand alone
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code returns true for
		// IsDockVisible() and IsFrontTab(). 
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	void ADMAPI (*ToggleAllFloatingDialogs)();

} ADMDialogGroupSuite1;

typedef ADMDialogGroupSuite1 ADMDialogGroupSuite;	// for historical reasons


// =============================================================================
//		* ADM Dialog Group Suite, version 2
// =============================================================================

#define kADMDialogGroupSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMDialogGroupSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// dialog info

	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	void ADMAPI (*ToggleAllFloatingDialogs)();
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);

}
ADMDialogGroupSuite2;


// =============================================================================
//		* ADM Dialog Group Suite, version 3
// =============================================================================

#define kADMDialogGroupSuiteVersion3 3

// -----------------------------------------------------------------------------



typedef struct ADMDialogGroupSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// dialog info

	/** ... */
	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	/** ... */
	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	/** ... */
	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	/** ... */
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	/** ... */
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	/** ... */
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	/** ... */
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	/** ... */
	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	/** ... */
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	/** ... */
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	/** ... */
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	/** ... */
	void ADMAPI (*ToggleAllFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ToggleAllButNoCloseFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);
}
ADMDialogGroupSuite3;


// =============================================================================
//		* ADM Dialog Group Suite, version 4
// =============================================================================

#define kADMDialogGroupSuiteVersion4 4

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMDialogGroupSuite4
{

	// dialog info

	/** ... */
	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	/** ... */
	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	/** ... */
	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	/** ... */
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	/** ... */
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	/** ... */
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	/** ... */
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	/** ... */
	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	/** ... */
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	/** ... */
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	/** ... */
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	/** ... */
	void ADMAPI (*ToggleAllFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ToggleAllButNoCloseFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);
	
	/** defer distribution of tabbed palettes. */
	void ADMAPI (*DeferTabDialogsDistribution)(ADMBoolean defer);

}
ADMDialogGroupSuite4;

// =============================================================================
//		* ADM Dialog Group Suite 5
// =============================================================================

#define kADMDialogGroupSuiteVersion5 5

// -----------------------------------------------------------------------------

/** ... */
struct ADMDialogGroupSuite5
{

	// dialog info

	/** ... */
	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	/** ... */
	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	/** ... */
	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	/** ... */
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	/** ... */
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	/** ... */
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	/** ... */
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	/** ... */
	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	/** ... */
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	/** ... */
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	/** ... */
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	/** ... */
	void ADMAPI (*ToggleAllFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ToggleAllButNoCloseFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);
	
	/** defer distribution of tabbed palettes. */
	void ADMAPI (*DeferTabDialogsDistribution)(ADMBoolean defer);
	
	/** Return whether the dock associated with this dialog is truly visible.
		This will return false if the dock is hidden via the Toggle functionality
		above. */
	ADMBoolean ADMAPI (*IsDockReallyVisible)(ADMDialogRef inDialog);

};

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

#endif
