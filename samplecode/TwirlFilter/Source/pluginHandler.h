//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/pluginHandler.h $
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

#include "SPInterf.h"


AIErr handlePluginCaller( char* caller, char* selector, void *message );

AIErr pluginStartup( SPInterfaceMessage *message );
void pluginShutdown( SPInterfaceMessage *message );
AIErr reloadPluginSuiteFunctions( SPAccessMessage *message );
void unloadPluginSuiteFunctions( SPAccessMessage *message );
