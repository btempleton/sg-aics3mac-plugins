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

#ifndef __ADMTrackerOld__
#define __ADMTrackerOld__

#include "ADMTracker.h"

// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// =============================================================================
//		* ADM Tracker Suite
// =============================================================================

/** ... */
#define kADMTrackerSuiteVersion1 1

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMTrackerSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/** ... */
	void ADMAPI (*GetPoint)(ADMTrackerRef inTracker, ADMPoint* outPoint);
	
	/** ... */
	ADMAction ADMAPI (*GetAction)(ADMTrackerRef inTracker);
	/** ... */
	ADMModifiers ADMAPI (*GetModifiers)(ADMTrackerRef inTracker);
	
	/** ... */
	ADMBoolean ADMAPI (*TestAction)(ADMTrackerRef inTracker, ADMAction inAction);
	/** ... */
	ADMBoolean ADMAPI (*TestModifier)(ADMTrackerRef inTracker, ADMModifiers inModifier);
	
	/** ... */
	ADMTime ADMAPI (*GetTime)(ADMTrackerRef inTracker);

	/** ... */
	void ADMAPI (*Abort)(ADMTrackerRef inTracker);

	/** ... */
	ADMMouseState ADMAPI (*GetMouseState)(ADMTrackerRef inTracker);
	/** ... */
	void ADMAPI (*ReleaseMouseCapture)(ADMTrackerRef inTracker);
	
	/** ... */
	ADMChar ADMAPI (*GetVirtualKey)(ADMTrackerRef inTracker);
	/** ... */
	ADMChar ADMAPI (*GetCharacter)(ADMTrackerRef inTracker);
	
}
ADMTrackerSuite1;

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMTrackerOld__
