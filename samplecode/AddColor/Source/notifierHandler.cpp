//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/notifierHandler.cpp $
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

#include "admHandler.h"

extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;

	// This notifier is needed because we create ADM dialogs when we recieve this notifier
	error = sAINotifier->AddNotifier ( message->d.self, "notifierName", 
			kAIApplicationStartedNotifier, &g->appStartedNotifier );

	if (error) goto error;

error:
	return error;
}


AIErr goNotifier( AINotifierMessage *message ) {
	AIErr error = kNoErr;

	if (message->notifier == g->appStartedNotifier ) {
		// Creates an ADM Non-Modal dialog, but does not necessarily show it
		// Defined in admHandler.c
		createADMDialog( message );
	}

	if (error) goto error;

error:
	return error;
}