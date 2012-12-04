//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/actionManagerHandler.cpp $
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
#include "actionManagerHandler.h"


// Execute an Action that your plug-in registered.
// This routine gets called when your plug-in is
// called with kActionCaller/kDoActionSelector
extern AIErr doAction( DoActionMessage *message ){
	
	/*  
		Illustrator is calling your plug-in to execute.
	 	This normally involves:
	 		1. getting parameters from the VPM in the AIActoinMessage
	 		2. if a showDialog is requested, display the dialog with default values
	 		3. if not, execute immediately
	*/
	
	AIErr error = kNoErr;

	return error;
}
