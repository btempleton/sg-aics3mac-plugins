/*******************************************************************************
*
* ADMHostWin.h -- ADM Host Window Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1998-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Joe Ault and Rick Doty, 27 May 1998
*
********************************************************************************/

/** @file ADMHostWin.h ADM Host Window Suite */

#ifndef __ADMHostWin__
#define __ADMHostWin__

#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// =============================================================================
//		* ADM Host Window Suite
// =============================================================================

/** Host window suite name */
#define kADMHostWindowSuite ("ADM Host Window Suite")
/** Host window suite version 1 */
#define kADMHostWindowSuiteVersion1 (1)
/** Current host window suite version */
#define kADMHostWindowSuiteVersion (kADMHostWindowSuiteVersion1)

// -----------------------------------------------------------------------------

/**
	Host window suite

	The host of ADM provides this suite for ADM as the window handler for
	kADMHostDefinedDialogStyle dialogs.  ADM will draw into a panel provided by
	the host.
*/
typedef struct ADMHostWindowSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/** ... */
	void ADMAPI (*GetWindowRef)(SPPluginRef inPluginRef, ADMWindowRef* inWindow,
				ADMDialogStyle inStyle);

	/** ... */
	void ADMAPI (*ShowWindow)(SPPluginRef inPluginRef, ADMWindowRef* inWindow,
				ADMBoolean inShowState);

	// Also need others depending on feedback. Hide, create, destroy, activate?
	// Separate from SetProcs?
	
}
ADMHostWindowSuite;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMHostWin__
