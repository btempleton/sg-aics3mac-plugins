//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TextFileFormat/Source/pluginHandler.cpp $
//
//  $Revision: #4 $
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
#include "pluginHandler.h"

#include "fileFormatHandler.h"
#include "menuHandler.h"

AIErr handlePluginCaller( char* caller, char* selector, void *message ) 
{
	AIErr error = kNoErr;

	// This is just an easy way of not having to cast message to ( SPMessageData* )
	// everytime we use IsEqual()
	SPBasicSuite *sSPBasic = ( ( SPMessageData* )message)->basic;

	if ( sSPBasic->IsEqual( caller, kCallerAIFileFormat ) ) 
	{
		if ( sSPBasic->IsEqual( selector, kSelectorAIGetFileFormatParameters ) )
			error = goGetFormatParms( ( AIFileFormatMessage* )message );
	
		else if ( sSPBasic->IsEqual( selector, kSelectorAIGoFileFormat ) )
			error = goFileFormat( ( AIFileFormatMessage* )message );
			
		else if ( sSPBasic->IsEqual( selector, kSelectorAICheckFileFormat ) )
			error = goCheckFormat( ( AIFileFormatMessage* )message );
	}
	else if ( sSPBasic->IsEqual( caller, kCallerAIMenu ) ) {
		if ( sSPBasic->IsEqual( selector, kSelectorAIGoMenuItem ) )
			error = goMenuItem( ( AIMenuMessage* )message );
		
		else if ( sSPBasic->IsEqual( selector, kSelectorAIUpdateMenuItem ) )
			error = updateMenuItem( ( AIMenuMessage* )message );
	} 

	return error;
}


// extend startup here
AIErr pluginStartup( SPInterfaceMessage *message ) 
{
	AIErr error = addFileFormat( message );
	if (!error) {
		error = addMenu(message);
	}
	return error;
}


/*	There are no suites acquired at this point, as you should mostly be doing
	system stuff here. */
void pluginShutdown( SPInterfaceMessage *message ) 
{
}


AIErr reloadPluginSuiteFunctions( SPAccessMessage *message ) 
{
	return kNoErr;
}


void unloadPluginSuiteFunctions( SPAccessMessage *message ) 
{
}
// end pluginHandler.cpp