//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/menuHandler.cpp $
//
//  $Revision: #7 $
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
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "string.h"
#include "SDKDef.h"
//#include "SDKAboutPluginsHelper.h"

extern AIErr goMenuItem( AIMenuMessage *message ) {

	AIErr error = kNoErr;
		
/*	if (message->menuItem == g->aboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About Shell", kSDKDefAboutSDKCompanyPluginsAlertString);
	}	
	else*/ if ( message->menuItem == g->showMenuItem ) {
		sADMBasic->MessageAlert("This project provides a shell from which new projects may be built from.");
	}
	
	if (error)
		goto error;

error:
	return error;

}


AIErr updateMenuItem( AIMenuMessage *message ) {

//	long inArtwork;
//	long isSelected;
//	long isTrue;
	AIErr error = kNoErr;

/*
	// This is only valid when kSelectorAIMacUpdateMenuItem is received, which is why we're here
	error = sMenu->GetUpdateFlags( &inArtwork, &isSelected, &isTrue );
	if ( error )
		goto error;		

	// We get this here because the menu group into which we are installing automatically alphabetizes
	error = sMenu->GetPlatformMenuItem( g->manualUpdateAIMenu, &pmanualMenuItem );
	if ( error )
		goto error;		

	// Do something based on the result.  It's easier than GetMatchingArt for this example, and can
	// also be used for a quick check before more processing.
	if ( isSelected & kMacIfGuide ) {
		sMacMenu->MacSetItem( pmanualMenuItem.menu, pmanualMenuItem.item, "\pDo Something To Selected Guides" );
		}
	else if ( inArtwork & kMacIfGuide ) {
		sMacMenu->MacSetItem( pmanualMenuItem.menu, pmanualMenuItem.item, "\pDo Something To All Guides" );
		}
*/

	if (error)
		goto error;

error:
	return error;
}



extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;

/*	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"Shell...", 
				&g->aboutPluginMenu);
*/
	// Add other menus.
	AIPlatformAddMenuItemDataUS sdkMenuData;
	AIPlatformAddMenuItemDataUS pluginMenuData;
	const char *pluginMenuStr = "Shell";
	const char *menuGroupStr = "SDKWindowGroup";
	const char *sdkMenuStr = "SDK";
	
	AIMenuGroup	sdkMenuGroup;
	AIMenuItemHandle dummyItem;
	AIMenuGroup dummyGroup;
	bool sdkGroupAlreadyMade = false;

	sdkMenuData.groupName = kOtherPalettesMenuGroup;
	sdkMenuData.itemText = ai::UnicodeString(sdkMenuStr);

	// search through the menus and 
	// see if another SDK plug in has already set up the group
	long count;
	error = sMenu->CountMenuGroups( &count );
	if ( error ) goto error;
	while (count > 0)
	{
		error = sMenu->GetNthMenuGroup( count-1, &dummyGroup );
		if ( error ) goto error;
		char *name;
		error = sMenu->GetMenuGroupName( dummyGroup, (const char**)&name );
		if ( error ) goto error;
		if ( std::strcmp(name, menuGroupStr ) == 0 )
		{
			sdkGroupAlreadyMade = true;
			count = -1;
		}
		count--;
	}

	if ( !sdkGroupAlreadyMade )
	{
		error = sMenu->AddMenuItem( message->d.self, menuGroupStr, &sdkMenuData, 0, &dummyItem );
		if ( error ) goto error;

		error = sMenu->AddMenuGroupAsSubMenu( menuGroupStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &sdkMenuGroup );
		if ( error ) goto error;
	}

	pluginMenuData.groupName = menuGroupStr;
	pluginMenuData.itemText = ai::UnicodeString(pluginMenuStr);
	
	error = sMenu->AddMenuItem( message->d.self, pluginMenuStr, &pluginMenuData, 0,
								&g->showMenuItem );
	if ( error )
		goto error;
		
error:
	return error;
}
