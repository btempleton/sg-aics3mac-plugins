//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/timerHandler.cpp $
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

#include "common.h"
#include "timerHandler.h"

#ifdef WIN_ENV
#define kTicksPerSecond 60
#endif

extern AIErr addTimers( SPInterfaceMessage *message ) {

	AIErr error = kNoErr;
	AITimerHandle timer;

	error = sTimer->AddTimer( message->d.self, "timerAndAgain",
				kTicksPerSecond / 10, &timer );
	if ( error )
		goto error;

error:
	return error;
}


extern AIErr goTimer( AITimerMessage *message ) {

	AIErr error = kNoErr;

if (error)
	goto error;

error:
	return error;

}
