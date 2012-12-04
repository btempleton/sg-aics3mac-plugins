/*******************************************************************************
*
* ADMWindow.h -- ADM Window Suite
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
********************************************************************************/

/** @file ADMWindow.h ADM Window Suite */

#ifndef __ADMWindow__
#define __ADMWindow__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
//	Window style codes

/** Window types that can be found by \c #ADMWindowSuite1::GetFrontWindow().  */
typedef enum
{

	// NOTE: These first four correspond to ADMDialogStyles
	// and are all variants of type kADMWindow.

	/** Floating window (palette) */
	kADMFloatingWindowStyle = 2,
	/** Tabbed floating window */
	kADMTabbedFloatingWindowStyle = 3,
	/** Resizable floating window */
	kADMResizingFloatingWindowStyle = 4,
	/** Tabbed resizable floating window */
	kADMTabbedResizingFloatingWindowStyle = 5,

	/** Document window. This does not correspond to any dialog window. */
	kADMDocumentWindowStyle = 100,

	/** @deprecated  Use \c #ADMDialogSuite10 to create dialogs. */
	kADMGrowNoZoomDocumentWindowStyle = 100,
				// for new window calls, use a specific type

	/** @deprecated  Use \c #ADMDialogSuite10 to create dialogs. */
	kADMNoGrowNoZoomDocumentWindowStyle = 104,
	/** @deprecated  Use \c #ADMDialogSuite10 to create dialogs. */
	kADMGrowZoomDocumentWindowStyle = 108,
	/** @deprecated  Use \c #ADMDialogSuite10 to create dialogs. */
	kADMNoGrowZoomDocumentWindowStyle = 112,

	/** Popup window  */
	kADMPopupWindowStyle = 300,
	/** Popup floating window */
	kADMPopupFloatingWindowStyle = 301,

	/** Internal */
	kADMDummyWindowStyle = 0xFFFFFFFF

}
ADMWindowStyle;


// =============================================================================
//		* ADM Window Suite
// =============================================================================
//	NOTE: This suite is currently implemented on MacOS only.

/** Window suite name */
#define kADMWindowSuite "ADM Window Suite"
/** Window suite version */
#define kADMWindowSuiteVersion1 1
/** Window suite version */
#define kADMWindowSuiteVersion kADMWindowSuiteVersion1

// -----------------------------------------------------------------------------

/** @ingroup Suites
	On Mac OS only: These functions allow you to manage the
	position of dialog windows in the platform window occlusion order.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMWindowSuite and \c #kADMWindowSuiteVersion.
*/
typedef struct ADMWindowSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// window creation/destruction

	/** @deprecated Use \c #ADMDialogSuite10 to create and destroy dialogs */
	ADMWindowRef ADMAPI (*NewLayerWindow_DEPRECATED)(ADMWindowStyle inWindowKind,
				unsigned char* inStorage, const ADMRect* inBoundsRect,
				const char* inTitle, ADMBoolean inVisible,
				ADMBoolean inGoAwayFlag, ADMInt32 inRefCon);

	/** @deprecated Use \c #ADMDialogSuite10 to create and destroy dialogs */
	ADMWindowRef ADMAPI (*GetNewLayerWindow_DEPRECATED)(SPPluginRef inPluginRef,
				ADMWindowStyle inWindowKind, ADMInt16 inWindowID,
				unsigned char* inStorage);

	/** @deprecated Use \c #ADMDialogSuite10 to create and destroy dialogs */
	void ADMAPI (*DisposeLayerWindow_DEPRECATED)(ADMWindowRef inWindow);

	// window visibility and layering

	/** Moves a window to the back in the platform window occlusion order.
			@param inWindow The window object.
			@return Nothing.
		*/
	void ADMAPI (*HideLayerWindow)(ADMWindowRef inWindow);
	/** Moves a window to the front in the platform window occlusion order,
		and gives it the input focus.
			@param inWindow The window object.
			@return Nothing.
 		*/
	void ADMAPI (*ShowAndSelectLayerWindow)(ADMWindowRef inWindow);
	/** Gives a window the input focus.
			@param inWindow The window object.
			@return Nothing.
		*/
	void ADMAPI (*SelectLayerWindow)(ADMWindowRef inWindow);
	/** Moves a window to the front in the platform window occlusion order.
			@param inWindow The window object.
			@return Nothing.
		*/
	void ADMAPI (*ShowLayerWindow)(ADMWindowRef inWindow);

	// window dragging and snapping

	/** @deprecated Use ADM notifiers for customizing behavior during a drag operation. */
	void ADMAPI (*DragLayerWindow_DEPRECATED)(ADMWindowRef inWindow, ADMPoint inStartPoint,
				const ADMRect* inDraggingBounds);

	// window order accessors

	/** Retrieves a window of a given type that is at the front of the
		platform window occlusion order.
			@param The type of window, a window-style constant.
			@return The window object.
		*/
	ADMWindowRef ADMAPI (*GetFrontWindow)(ADMWindowStyle inWindowKind);
	/** Redraws the screen after the platform window occlusion order has changed.
			@return Nothing.
		*/
	void ADMAPI (*UpdateWindowOrder)();

}
ADMWindowSuite1;

/** Window suite name */
typedef ADMWindowSuite1 ADMWindowSuite;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMWindow__
