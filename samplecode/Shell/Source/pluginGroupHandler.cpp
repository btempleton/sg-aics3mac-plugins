//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/pluginGroupHandler.cpp $
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
#include "plugingroupHandler.h"

extern AIErr goUpdateResultArt( AIPluginGroupMessage *message ){
	
	/*  
		This gets called when the Edit Art is modified
		This is your opportunity to delete and recreate the result art
	 	This normally involves:
	 		1. deleting the result art
	 		2. putting a copy of the edit art into the result art
	 		3. modifying the edit art and putting additional art into the result art
	*/
	
	
	AIErr error = kNoErr;

	return error;
}

extern AIErr goNotifyEdits( AIPluginGroupMessage *message ) {
	
	/*  This is another opportunity to delete and recreate the result art
		This gets called less ofthen than goUpdateResultArt()
		and according to the options parameter which you passed to AddAIPluginGroup()
	*/
	
	AIErr error = kNoErr;


	return error;
}

