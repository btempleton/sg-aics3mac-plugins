/*
 *  pluginHandler.h
 *  TextTools
 *
 *  Created by Comp Mac 8a on 10/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SPInterf.h"


AIErr handlePluginCaller( char* caller, char* selector, void *message );

AIErr pluginStartup( SPInterfaceMessage *message );
void pluginShutdown( SPInterfaceMessage *message );
AIErr reloadPluginSuiteFunctions( SPAccessMessage *message );
void unloadPluginSuiteFunctions( SPAccessMessage *message );
