//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/notifierHandler.cpp $
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
#include "notifierHandler.h"

extern AIErr addNotifiers( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;

	error = sNotifier->AddNotifier ( message->d.self, "notifierName", 
			kAIArtSelectionChangedNotifier, NULL );

	if (error) goto error;

error:
	return error;
}




AIErr goNotifier( AINotifierMessage *message ) {
	AIErr error = kNoErr;


	if (error) goto error;

error:
	return error;
}

