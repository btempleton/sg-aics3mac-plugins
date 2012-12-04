//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/transformAgainHandler.cpp $
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
#include "transformAgainHandler.h"

extern AIErr repeatTransform ( AITransformAgainMessage *message ) {
	AIErr error = kNoErr;
	
	// repeat the last transformation based on values stashed in the globals structure

	if (error) 
		goto error;

error:
	return error;
}
