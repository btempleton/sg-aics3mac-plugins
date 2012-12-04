//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MultiArrowTool/Source/menuHandler.cpp $
//
//  $Revision: #4 $
//
//  Copyright 1995-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include "common.h"
#include "menuHandler.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"


extern AIErr goMenuItem( AIMenuMessage *message ) {
	AIErr error = kNoErr;
	if (message->menuItem == g->aboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About MultiArrowTool", kSDKDefAboutSDKCompanyPluginsAlertString);
	}	
	return error;
}


AIErr updateMenuItem( AIMenuMessage *message ) {

	AIErr error = kNoErr;
	return error;
}



extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"MultiArrowTool...", 
				&g->aboutPluginMenu);
	return error;
}
