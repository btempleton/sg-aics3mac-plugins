//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/pluginHandler.cpp $
//
//  $Revision: #5 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#include "common.h"
#include "pluginHandler.h"

#ifdef ADDS_MENU
#include "menuHandler.h"
#endif

#ifdef ADDS_FILTER
#include "filterHandler.h"
#endif

#ifdef ADDS_LIVE_EFFECT
#include "liveEffectHandler.h"
#endif

#ifdef ADDS_FILE_FORMAT
#include "fileFormatHandler.h"
#endif

#ifdef ADDS_TOOL
#include "toolHandler.h"
#endif

#ifdef ADDS_NOTIFIER
#include "notifierHandler.h"
#endif

#ifdef ADDS_TIMER
#include "timerHandler.h"
#endif

#ifdef ADDS_TRANSFORM_AGAIN
#include "transformAgainHandler.h"
#endif

#include "admHandler.h"


AIErr handlePluginCaller( char* caller, char* selector, void *message ) {
	AIErr error = kNoErr;

	// This is just an easy way of not having to cast message to ( SPMessageData* )
	// everytime we use IsEqual()
	SPBasicSuite *sSPBasic = ( ( SPMessageData* )message)->basic;

#ifdef ADDS_MENU
	if ( sSPBasic->IsEqual( caller, kCallerAIMenu ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGoMenuItem ) )
			error = goMenuItem( ( AIMenuMessage* )message );
		
		else if ( sSPBasic->IsEqual( selector, kSelectorAIUpdateMenuItem ) )
			error = updateMenuItem( ( AIMenuMessage* )message );
	} 
	else 
#endif

#ifdef ADDS_FILTER
	if ( sSPBasic->IsEqual( caller, kCallerAIFilter ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGetFilterParameters ) )
			error = filterGetParms( ( AIFilterMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIGoFilter ) )
			error = goFilter( ( AIFilterMessage* )message );
	}
	else 
#endif

#ifdef ADDS_LIVE_EFFECT
	if ( sSPBasic->IsEqual(caller, kCallerAILiveEffect ) )	{
		if ( sSPBasic->IsEqual( selector, kSelectorAIEditLiveEffectParameters ) )
			error = liveEffectGetParms( ( AILiveEffectEditParamMessage* )message );

		else if ( sSPBasic->IsEqual( selector, kSelectorAIGoLiveEffect ) )
			error = goLiveEffect( ( AILiveEffectGoMessage* )message );

		else if ( sSPBasic->IsEqual( selector, kSelectorAILiveEffectInterpolate ) )
			error = liveEffectInterpolate( ( AILiveEffectInterpParamMessage* )message );
		
		else if ( sSPBasic->IsEqual( selector, kSelectorAILiveEffectInputType ) )
			error = liveEffectGetInputType( ( AILiveEffectInputTypeMessage* )message );
		}
	else
#endif

#ifdef ADDS_FILE_FORMAT
	if ( sSPBasic->IsEqual( caller, kCallerAIFileFormat ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGetFileFormatParameters ) )
			error = goGetFormatParms( ( AIFileFormatMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIGoFileFormat ) )
			error = goFileFormat( ( AIFileFormatMessage* )message );
			
		else if ( sSPBasic->IsEqual( selector, kSelectorAICheckFileFormat ) )
			error = goCheckFormat( ( AIFileFormatMessage* )message );
	}
	else 
#endif
	
#ifdef ADDS_TOOL	
	if ( sSPBasic->IsEqual( caller, kCallerAITool ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIEditToolOptions ) )
			error = toolOptions( ( AIToolMessage* )message );

		else if ( sSPBasic->IsEqual( selector, kSelectorAITrackToolCursor ) )
			error = toolTrackCursor( ( AIToolMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIToolMouseDown ) )
			error = toolMouseDown( ( AIToolMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIToolMouseDrag ) )
			error = toolMouseDrag( ( AIToolMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIToolMouseUp ) )
			error = toolMouseUp( ( AIToolMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAISelectTool ) )
			error = toolSelect( ( AIToolMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIDeselectTool ) )
			error = toolDeselect( ( AIToolMessage* )message );
	}
	else
#endif

/*	Window plug-in types are gone. I will replace this with ADM routines.
	if ( strcmp( caller, kCallerAIWindow ) == 0 ) {
		if ( strcmp( selector, kSelectorAIWindowEvent ) == 0 )
			error = windowEvent( message );
			
		else if ( strcmp( selector, kSelectorAIMacHideWindow ) == 0 )
			error = windowHide( message );
			
		else if ( strcmp( selector, kSelectorAIMacShowWindow ) == 0 )
			error = windowShow( message );
	
		else if ( strcmp( selector, kSelectorAIMacZoomWindow ) == 0 )
			error = windowZoom( message );

		else if ( strcmp( selector, kSelectorAIWindowTrackCursor ) == 0 )
			error = windowTrackCursor( message );

		else if ( strcmp( selector, kSelectorAIGainWindowKeyboardFocus ) == 0 )
			error = windowGainKeyboardFocus( message );
			
		else if ( strcmp( selector, kSelectorAILoseWindowKeyboardFocus ) == 0 )
			error = windowLoseKeyboardFocus( message );
	}
	else
*/

#ifdef ADDS_TIMER
	if ( sSPBasic->IsEqual( caller, kCallerAITimer ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGoTimer ) )
			error = goTimer( ( AITimerMessage* )message );
	}
	else 
#endif

#ifdef ADDS_NOTIFIER
	if ( sSPBasic->IsEqual( caller, kCallerAINotify ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAINotify ) )
			error = goNotifier( ( AINotifierMessage* )message );
	}
	else
#endif
	
#ifdef ADDS_TRANSFORM_AGAIN	
	 if ( sSPBasic->IsEqual( caller, kCallerAITransformAgain ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAITransformAgain ) )
			error = repeatTransform( ( AITransformAgainMessage* )message );
	} 
	else
#endif
	
	;
	return error;

}


// extend startup here
AIErr pluginStartup( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// globals block has been allocated and is pointed to by the variable g
	if (!error)
		error = addMenu( message );
	if (!error)
		error = addFilters( message );

	if (!error)
		error = addLiveEffects( message );
	return error;
}


void pluginShutdown( SPInterfaceMessage *message ) {

	
/*	There are no suites acquired at this point, as you should mostly be doing
	system stuff here.  You might do something like:
	
	error = sBasic->AcquireSuite( kAIPreferencesSuite, kAIPreferencesSuiteVersion, &sPrefs );
	if ( error )
		goto error;

	sPrefs->PutPointPreference) ( "Window", "Position", g->windowPosition );
	
	sBasic->ReleaseSuite( kSPBlocksSuite, kSPBlocksSuiteVersion );
*/

}


AIErr reloadPluginSuiteFunctions( SPAccessMessage *message ) {
	AIErr error = kNoErr;
	
// ok to reload our suite functions 
//	reloadSuiteFunctions( );
	
	return error;
}


void unloadPluginSuiteFunctions( SPAccessMessage *message ) {

	
// set our suite functions to undefined
//	unloadSuiteFunctions( );

}
