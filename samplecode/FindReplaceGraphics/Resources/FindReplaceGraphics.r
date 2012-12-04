//========================================================================================
//  
//  $File: //ai/ai14/devtech/sdk/public/samplecode/ADMNonModalDialog/Resources/ADMNonModalDialog.r $
//
//  $Revision: #3 $
//
//  Copyright 1987-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#define PIPL_PLUGIN_NAME "Find & Replace Graphics"
#include "Plugin.r"

#include "ADMNonModalDialogID.h"

#include "Types.r"

/** ADM Non Modal Dialog resource
*/
resource 'DLOG' (kADMNonModalDialogID, kADMNonModalDialogName, purgeable) {
	{100, 200, 265, 410},  // top, left, bottom, right
	1991, // floatZoomGrowProc defined in MacWindows.h
	visible, // drawn on screen immediately
	goAway, // has close button
	0x0, // application options
	kADMNonModalDialogID, // resource ID
	kADMNonModalDialogName, // dialog title
	0x0 // dialog positioning noAutoCenter
};

resource 'DITL' (kADMNonModalDialogID, kADMNonModalDialogName, purgeable) { { } };