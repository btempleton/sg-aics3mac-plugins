//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/Main.cpp $
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

#include "Plugin.hpp"

extern "C"
{
	SPBasicSuite *sSPBasic = NULL;
}

static bool unloaded = true;

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	SPErr error = kNoErr;

	SPMessageData *msgData = static_cast<SPMessageData *>(message);
		
	Plugin *plugin = static_cast<Plugin *>(msgData->globals);
	
	bool shouldDelete = false;

	try 
	{
		sSPBasic = msgData->basic;

		if (plugin != NULL && unloaded)
			throw((SPErr)kBadParameterErr);

		if (plugin == NULL)
		{
			plugin = AllocatePlugin(msgData->self);
			
			if (plugin != NULL)
			{
				msgData->globals = plugin;
				unloaded = false;
			}
			else
			{
				error = kOutOfMemoryErr;
				throw((SPErr)error);
			}
			
		}

		error = plugin->Message(caller, selector, message);
		if (error) throw((SPErr)error);

		if (plugin->IsUnloadMsg(caller, selector))
			shouldDelete = true;
	}

	catch (SPErr inError)
	{
		error = inError;

		if (plugin != NULL && ( plugin->IsUnloadMsg(caller, selector) || 
		     					plugin->IsReloadMsg(caller, selector) ))
			shouldDelete = true;
	}

	catch (...)
	{
		error = kBadParameterErr;

		if (plugin != NULL && ( plugin->IsUnloadMsg(caller, selector) || 
		     					plugin->IsReloadMsg(caller, selector) ))
			shouldDelete = true;
	}

	if (shouldDelete)
	{
		delete plugin;
		msgData->globals = plugin = NULL;
		unloaded = true;
	}

	return error;
}
