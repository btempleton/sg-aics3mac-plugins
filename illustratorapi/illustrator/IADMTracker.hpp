/***********************************************************************/
/*                                                                     */
/* IADMTracker.hpp                                                     */
/* Object wrapper for ADM Tracker Suite                                */
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
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Dave Lazarony, 03/06/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMTracker_hpp__
#define __IADMTracker_hpp__

/*
 * Includes
 */
 
#ifndef __ADMTracker__
#include "ADMTracker.h"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMTrackerSuite* sADMTracker;

/*
 * Wrapper Class
 */

class IADMTracker
{
private:
	ADMTrackerRef fTracker;

public:	
	IADMTracker() 									{ fTracker = NULL; }
	IADMTracker(ADMTrackerRef tracker) 				{ fTracker = tracker; }
	
	operator ADMTrackerRef(void) 					{ return fTracker; }

	void Abort()									{ sADMTracker->Abort(fTracker); }
	
	void GetPoint(IADMPoint& point) 					{ sADMTracker->GetPoint(fTracker, &point); }
	
	ADMAction GetAction() 							{ return sADMTracker->GetAction(fTracker); }
	ADMModifiers GetModifiers()						{ return sADMTracker->GetModifiers(fTracker); }
	
	ADMBoolean TestAction(ADMAction action) 			{ return sADMTracker->TestAction(fTracker, action); }
	ADMBoolean TestModifier(ADMModifiers modifier)	{ return sADMTracker->TestModifier(fTracker, modifier); }
	
	ADMTime GetTime()								{ return sADMTracker->GetTime(fTracker); }

	ADMMouseState GetMouseState()					{ return sADMTracker->GetMouseState(fTracker); }
	void ReleaseMouseCapture()						{ sADMTracker->ReleaseMouseCapture(fTracker); }

	ADMChar GetVirtualKey()							{ return sADMTracker->GetVirtualKey(fTracker); }
	ADMChar GetCharacter()							{ return sADMTracker->GetCharacter(fTracker); }


	/*
	 * Action Testers
	 */
	ADMBoolean DidMouseMove()						{ return TestAction(kADMMouseMoveAction); }		/**** Get rid of this  FIX ME pja****/

	ADMBoolean DidMouseMoveWhileDown()				{ return TestAction(kADMMouseMovedDownAction); }
	ADMBoolean DidMouseMoveWhileUp()					{ return TestAction(kADMMouseMovedUpAction); }
	ADMBoolean DidButtonGoDown() 					{ return TestAction(kADMButtonDownAction); }
	ADMBoolean DidButtonGoUp() 						{ return TestAction(kADMButtonUpAction); }
	ADMBoolean DidShiftKeyGoDown() 					{ return TestAction(kADMShiftKeyDownAction); }
	ADMBoolean DidShiftKeyGoUp() 					{ return TestAction(kADMShiftKeyUpAction); }
	ADMBoolean DidMenuKeyGoDown() 					{ return TestAction(kADMMenuKeyDownAction); }
	ADMBoolean DidMenuKeyGoUp() 						{ return TestAction(kADMMenuKeyUpAction); }
	ADMBoolean DidModKeyGoDown() 					{ return TestAction(kADMModKeyDownAction); }
	ADMBoolean DidModKeyGoUp() 						{ return TestAction(kADMModKeyUpAction); }
	ADMBoolean DidSpaceKeyGoDown() 					{ return TestAction(kADMSpaceKeyDownAction); }
	ADMBoolean DidSpaceKeyGoUp() 					{ return TestAction(kADMSpaceKeyUpAction); }
	ADMBoolean DidTabKeyGoDown() 					{ return TestAction(kADMTabKeyDownAction); }
	ADMBoolean DidTabKeyGoUp() 						{ return TestAction(kADMTabKeyUpAction); }
	ADMBoolean DidEnter()							{ return TestAction(kADMEnterAction); }
	ADMBoolean DidLeave()							{ return TestAction(kADMLeaveAction); }
	ADMBoolean DidUncapturedButtonGoUp()				{ return TestAction(kADMUncapturedButtonUpAction); }
	
	ADMBoolean DidWinLeftButtonGoDown() 				{ return TestAction(kWinLeftButtonDownAction); }
	ADMBoolean DidWinLeftButtonGoUp() 				{ return TestAction(kWinLeftButtonUpAction); }
	ADMBoolean DidWinMiddleButtonGoDown()			{ return TestAction(kWinMiddleButtonDownAction); }
	ADMBoolean DidWinMiddleButtonGoUp() 				{ return TestAction(kWinMiddleButtonUpAction); }
	ADMBoolean DidWinRightButtonGoDown() 			{ return TestAction(kWinRightButtonDownAction); }
	ADMBoolean DidWinRightButtonGoUp() 				{ return TestAction(kWinRightButtonUpAction); }
	ADMBoolean DidWinAltKeyGoDown() 					{ return TestAction(kWinAltKeyDownAction); }
	ADMBoolean DidWinAltKeyGoUp() 					{ return TestAction(kWinAltKeyUpAction); }
	ADMBoolean DidWinControlKeyGoDown() 				{ return TestAction(kWinControlKeyDownAction); }
	ADMBoolean DidWinControlKeyGoUp() 				{ return TestAction(kWinControlKeyUpAction); }
	ADMBoolean DidWinUncapturedLeftButtonGoUp()		{ return TestAction(kWinUncapturedLeftButtonUpAction); }
	ADMBoolean DidWinUncapturedMiddleButtonGoUp()	{ return TestAction(kWinUncapturedMiddleButtonUpAction); }
	ADMBoolean DidWinUncapturedRightButtonGoUp()		{ return TestAction(kWinUncapturedRightButtonUpAction); }

	
	ADMBoolean DidMacCommandKeyGoDown() 				{ return TestAction(kMacCommandKeyDownAction); }
	ADMBoolean DidMacCommandKeyGoUp() 				{ return TestAction(kMacCommandKeyUpAction); }
	ADMBoolean DidMacOptionKeyGoDown() 				{ return TestAction(kMacOptionKeyDownAction); }
	ADMBoolean DidMacOptionKeyGoUp() 				{ return TestAction(kMacOptionKeyUpAction); }
	ADMBoolean DidMacControlKeyGoDown() 				{ return TestAction(kMacControlKeyDownAction); }
	ADMBoolean DidMacControlKeyGoUp() 				{ return TestAction(kMacControlKeyUpAction); }
		
	/*
	 * Modifier Testers
	 */
	ADMBoolean IsButtonDown() 						{ return TestModifier(kADMButtonDownModifier); }
	ADMBoolean IsShiftKeyDown() 						{ return TestModifier(kADMShiftKeyDownModifier); }
	ADMBoolean IsMenuKeyDown() 						{ return TestModifier(kADMMenuKeyDownModifier); }
	ADMBoolean IsModKeyDown() 						{ return TestModifier(kADMModKeyDownModifier); }
	ADMBoolean IsSpaceKeyDown() 						{ return TestModifier(kADMSpaceKeyDownModifier); }
	ADMBoolean IsTabKeyDown() 						{ return TestModifier(kADMTabKeyDownModifier); }
	ADMBoolean IsDoubleClick() 						{ return TestModifier(kADMDoubleClickModifier); }
		
	ADMBoolean IsWinLeftButtonDown() 				{ return TestModifier(kWinLeftButtonDownModifier); }
	ADMBoolean IsWinMiddleButtonDown()				{ return TestModifier(kWinMiddleButtonDownModifier); }
	ADMBoolean IsWinRightButtonDown() 				{ return TestModifier(kWinRightButtonDownModifier); }
	ADMBoolean IsWinAltKeyDown() 					{ return TestModifier(kWinAltKeyDownModifier); }
	ADMBoolean IsWinControlKeyDown() 				{ return TestModifier(kWinControlKeyDownModifier); }
		
	ADMBoolean IsMacCommandKeyDown() 				{ return TestModifier(kMacCommandKeyDownModifier); }
	ADMBoolean IsMacOptionKeyDown() 					{ return TestModifier(kMacOptionKeyDownModifier); }
	ADMBoolean IsMacControlKeyDown() 				{ return TestModifier(kMacControlKeyDownModifier); }
};

#endif
