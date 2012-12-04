/*
 *  notifierHandler.cpp
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various notifier handler functions.
#include "IllustratorSDK.h"

#include "common.h"
#include "notifierHandler.h"

#include "FixBlack.h"
#include "AddColor.h"
#include "FindReplaceGraphics.h"

extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// This notifier is needed because we create ADM dialogs when we recieve this notifier
	error = sAINotifier->AddNotifier ( message->d.self, "ColorTools", 
									  kAIApplicationStartedNotifier, &g->appStartedNotifier );
	error = sAINotifier->AddNotifier ( message->d.self, "ColorTools", 
									  kAIDocumentOpenedNotifier, &g->docOpenedNotifier );
									  
	error = sAINotifier->AddNotifier ( message->d.self, "ColorTools", 
									  kAIArtCustomColorChangedNotifier, &g->custColorChangeNotifier );
	error = sAINotifier->AddNotifier ( message->d.self, "ColorTools", 
									  kAISwatchLibraryChangedNotifier, &g->swatchLibraryChangeNotifier );
	error = sAINotifier->AddNotifier ( message->d.self, "ColorTools",
									  kAIArtSelectionChangedNotifier, &g->artSelectionChangeNotifier );
									  

	if (error) goto error;
	
error:
	return error;
}


AIErr goNotifier( AINotifierMessage *message ) {
	AIErr error = kNoErr;
	
	if (message->notifier == g->appStartedNotifier ) {
		// Whatever we want to do when the app starts
		createAddColorDialog( message );
		createFindReplaceDialog( message );
	}
	
	if (message->notifier == g->docOpenedNotifier ||
		message->notifier == g->custColorChangeNotifier ||
		message->notifier == g->swatchLibraryChangeNotifier ) {
		//calls the color list update when a document is opened
		//550 is the from list
		changeSwatchList( 550 );
		//551 is the to list
		changeSwatchList( 551 );
	}
	
	if (message->notifier == g->artSelectionChangeNotifier ) {
		//Call the notifier handler for when the selection changes
		changeChangeInList();
	}
	
	if (error) goto error;
	
error:
	return error;
}