//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MenuPlay/Source/admHandler.cpp $
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

#include "IllustratorSDK.h"

#include "common.h"
#include "admHandler.h"


// This file is mostly a place holder.  It would have the "go" routine for
// a given dialog, probably triggered from your menu handler.  Private functions
// would be dialog init and notifier procs, etc.  
// Destruction of the dialog is handler in pluginHandler.h

AIErr createADMDialog( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;


	if (error)
		goto error;

error:
	return error;
}





