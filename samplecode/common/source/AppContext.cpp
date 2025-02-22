//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/AppContext.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/*
	NOTE: this file was yanked out of the PaintStyle plugin and stuck in the GlobLists
	experimental plugin.  If this code is ever stuck into the real PlugInDev tree, this
	file should be shared with the corresponding file in PaintStyle.
	THERE IS NO GLOBLISTS SPECIFIC CODE HERE
*/

#include "AI90Context.h"
#include "AppContext.hpp"

extern "C" AI90AppContextSuite *sAIAppContext;

AppContext::AppContext(SPPluginRef pluginRef)
{
	fAppContext = nil;
	if (sAIAppContext)
		sAIAppContext->PushAppContext(pluginRef, (AIAppContextHandle *)&fAppContext);
}

AppContext::~AppContext()
{
	if (sAIAppContext)
		sAIAppContext->PopAppContext((AIAppContextHandle)fAppContext);
}
