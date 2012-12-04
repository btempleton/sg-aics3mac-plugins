/*
 *  notifierHandler.cpp
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various notifier handler functions.
#include "IllustratorSDK.h"

#include "common.h"
#include "notifierHandler.h"

#include "BStatMU.h"
#import "CException.h"

extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// This notifier is needed because we create ADM dialogs when we recieve this notifier
	error = sAINotifier->AddNotifier ( message->d.self, "BStatMU", 
									  kAIApplicationStartedNotifier, &g->appStartedNotifier );
	error = sAINotifier->AddNotifier ( message->d.self, "BStatMU", 
									  kAIDocumentOpenedNotifier, &g->docOpenedNotifier );
	/*	
	 //We need to ensure our plate dictionaries are kept up to date	
	 error = sAINotifier->AddNotifier ( message->d.self, "BStatMU", 
	 kAIMetadataSyncNotifier, &g->preSaveNotifier );
	 error = sAINotifier->AddNotifier ( message->d.self, "BStatMU", 
	 kAIDocumentAboutToCloseNotifier, &g->preCloseNotifier );
	 */	
	
	if (error) goto error;
	
error:
	return error;
}


AIErr goNotifier( AINotifierMessage *message ) {
	
	//	try {
	if (message->notifier == g->appStartedNotifier ) {
		// Whatever we want to do when the app starts
	}
	
	if (message->notifier == g->docOpenedNotifier ) {
		DocOpened();
	}
	/*		
	 if (message->notifier == g->preSaveNotifier ) {
	 DocWillBeSaved();
	 }
	 
	 if (message->notifier == g->preCloseNotifier ) {
	 DocWillBeClosed();
	 }
	 */		
	return TRUE;
	//	}
	/*	catch(CException* e) {
	 e.Report();
	 return FALSE;
	 } */
}

//For now, we'll just do the same stuff for each of these.
//In the future, we may need to do different things.
ASBoolean DocOpened() {
	//Retrieve the dictionary for this file
	sAIDocument->GetDictionary(&dictMain);
	
	AIReal version;
	sAIDictionary->GetRealEntry(dictMain, sAIDictionary->Key("BSTATMU_VERSION"), &version);
	
	//So, everytime we open a file, we check if it has a BStat MU version.
	//If its the current version, we try and read the dictionary and check
	//all of the art objects in there to see if they still exist. If they don't,
	//we can inform now that it needs to be reconverted.
	if (sAIRealMath->EqualWithinTol(version, BSTATMU_VERSION, .01)) {
		try {
			SetUpNodes();
			CleanUpNodes();
			sAIDictionary->SetRealEntry(dictMain, sAIDictionary->Key("BSTATMU_VERSION"), BSTATMU_VERSION);
			return TRUE;
		}
		catch(CException* e) {
			throw;
		}
	}
}


ASBoolean DocWillBeSaved() {
	DocOpened();
}


ASBoolean DocWillBeClosed() {
	DocOpened();
}