/*
 *  pluginHandler.h
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SPInterf.h"


AIErr handlePluginCaller( char* caller, char* selector, void *message );

AIErr pluginStartup( SPInterfaceMessage *message );
void pluginShutdown( SPInterfaceMessage *message );
AIErr reloadPluginSuiteFunctions( SPAccessMessage *message );
void unloadPluginSuiteFunctions( SPAccessMessage *message );
