//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/pluginHandler.cpp $
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

// This file defines the various plugin functions including handlePluginCaller()
// handlePluginCaller() identifies the caller/selector pair and calls the 
// appropriate functions.
#include "IllustratorSDK.h"


#include "common.h"
#include "pluginHandler.h"

#ifdef ADDS_MENU
#include "menuHandler.h"
#endif

#ifdef ADDS_FILTER
#include "filterHandler.h"
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

#include "BCImpose.h"


// handlePluginCaller()
// This function identifies the caller/selector pair and calls the appropriate functions.
// Most of the functions this calls are defined in *Handler.c
AIErr handlePluginCaller( char* caller, char* selector, void *message ) {
	AIErr error = kNoErr;

	// This is just an easy way of not having to cast message to ( SPMessageData* )
	// everytime we use IsEqual()
	SPBasicSuite *sSPBasic = ( ( SPMessageData* )message)->basic;

#ifdef ADDS_MENU
	if ( sSPBasic->IsEqual( caller, kCallerAIMenu ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGoMenuItem ) )
			error = goMenuItem( ( AIMenuMessage* )message );
		
//		else if ( sSPBasic->IsEqual( selector, kSelectorAIUpdateMenuItem ) )
//			error = updateMenuItem( ( AIMenuMessage* )message );
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


// Extend startup here
AIErr pluginStartup( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// store a pointer to basic (needed for use in callbacks)
	// we will need this later during the ADM initialization and destroy procs
	g->basic = message->d.basic;
	
	// Adds a menu item, defined in menuHandler.c
	error = addMenu( message );
	
	// Adds all notifiers used in this plug-in, see notifierHandler.c
	addNotifiers( message );
		
	return error;
}


void pluginShutdown( SPInterfaceMessage *message ) {

	
	// We destroy the dialog only if it still exists
	// If ADM shuts down before our plug-in, then ADM will automatically 
	// destroy the dialog
	if (g->nonModalDialog) {									
	sADMDialog->Destroy( g->nonModalDialog );
	}
			
}


// For this particular plug-in, we never Release the suites, so no need to reload.
// With ADM Non-modal dialogs, we need all suites in memory, all the time.
// Therefore, we acquire Suites twice, once  at startup and another time in
// the initialization proc for the dialog. This guarantees that all suites
// remain in memory until they are released during the dialog destroy proc.
AIErr reloadPluginSuiteFunctions( SPAccessMessage *message ) {
	AIErr error = kNoErr;
	
	//	reloadSuiteFunctions( );
	
	return error;
}

// see comment for reloadPluginSuiteFunctions()
void unloadPluginSuiteFunctions( SPAccessMessage *message ) {

	
	//	unloadSuiteFunctions( );

}
