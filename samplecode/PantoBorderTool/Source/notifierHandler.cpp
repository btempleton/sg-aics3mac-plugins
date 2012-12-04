//========================================================================================
//  
//  $File: Panto Border Tool notifierHandler.cpp $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// This file defines the various notifier handler functions.
#include "IllustratorSDK.h"

#include "common.h"
#include "notifierHandler.h"




extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// This notifier is needed because we create ADM dialogs when we recieve this notifier
	error = sAINotifier->AddNotifier ( message->d.self, "AppStart", 
									  kAIApplicationStartedNotifier, &g->appStartedNotifier );
	
	error = sAINotifier->AddNotifier ( message->d.self, "ArtChange", 
									  kAIArtSelectionChangedNotifier, NULL );
	
	
	if (error) goto error;
	
error:
	return error;
}


AIErr goNotifier( AINotifierMessage *message ) {
	AIErr error = kNoErr;
	
	if (message->notifier == g->appStartedNotifier ) {
		// Whatever we want to do when the app starts
	}
	
	if (message->notifier == g->docOpenedNotifier ) {
		//Whatever we want to do when a doc is opened
	}
	
	
	
	
	if (error) goto error;
	
error:
	return error;
}