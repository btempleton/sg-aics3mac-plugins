/*
 *  notifierHandler.cpp
 *  TextTools
 *
 *  Created by Comp Mac 8a on 10/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various notifier handler functions.
#include "IllustratorSDK.h"

#include "common.h"
#include "notifierHandler.h"

#include "TextTools.h"

extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// This notifier is needed because we create ADM dialogs when we recieve this notifier
	error = sAINotifier->AddNotifier ( message->d.self, "TextTools", 
									  kAIApplicationStartedNotifier, &g->appStartedNotifier );
	error = sAINotifier->AddNotifier ( message->d.self, "TextTools", 
									  kAIDocumentOpenedNotifier, &g->docOpenedNotifier );
	
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