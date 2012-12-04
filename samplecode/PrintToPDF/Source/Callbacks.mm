/*
 *  Callbacks.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 4/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import "Callbacks.h"
#import "Dialog.h"

extern Dialog* theDialog;


//****************************************************************************************************
// ************************** DIALOG LEVEL CALLBACKS *************************************************
//****************************************************************************************************

//*************************************************
// CreatePDFDlg
// Sets up the Cocoa stuff, unpacks the nib
//*************************************************
void createPDFDlg( AINotifierMessage *message ) {
	NSApplicationLoad();
	theDialog = [[Dialog alloc] init];
}


//*************************************************
// showDialog
// Displays the dialog and starts the event loop
//*************************************************
void showDialog(  ) {
	if (theDialog != nil) {
		[theDialog show];
	}
}


//*************************************************
// CloseWindow
// Called by pluginShutdown to destroy our dialog if its still hanging around when Illustrator closes
//*************************************************
void CloseWindow() {
	[theDialog close];
}


/*{
 if (sAIActionManager && sAIActionManager->IsActionEventRegistered("btFixBlack")) {
 sAIActionManager->PlayActionEvent("btFixBlack", kDialogNone, NULL);
 } else {sADMBasic->MessageAlert("Action Manager not loaded."); }
 }*/