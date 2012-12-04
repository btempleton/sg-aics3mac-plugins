//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/menuHandler.cpp $
//
//  $Revision: #6 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// This file defines the various menu handler functions.
#include "IllustratorSDK.h"

#include "common.h"
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"



extern AIErr goMenuItem( AIMenuMessage *message ) {

	AIErr error = kNoErr;
	
	if ( message->menuItem == g->showADMNonModalDialog ) 
	{
		sADMDialog->Show( g->nonModalDialog, !( sADMDialog->IsVisible( g->nonModalDialog ) ) );
	}
	else if (message->menuItem == g->aboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About ADMNonModalDialog", kSDKDefAboutSDKCompanyPluginsAlertString);
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

	if ( sADMDialog->IsVisible( g->nonModalDialog ) )
	{
		sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Hide Add Color") );
	}
	else
	{
		sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Show Add Color") );
	}


/*
	// This is only valid when kSelectorAIMacUpdateMenuItem is received, which is why we're here
	error = sAIMenu->GetUpdateFlags( &inArtwork, &isSelected, &isTrue );
	if ( error )
		goto error;		

	// We get this here because the menu group into which we are installing automatically alphabetizes
	error = sAIMenu->GetPlatformMenuItem( g->manualUpdateAIMenu, &pmanualMenuItem );
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

	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"Add Color...", 
				&g->aboutPluginMenu);

	// Add other menus.
	AIPlatformAddMenuItemDataUS menuData;
	AIPlatformAddMenuItemDataUS pluginMenuData;
	const char *menuGroupCStr = "SDKEditGroup";
	const char *menuCStr = "Modify Swatches";
	const char *pluginCStr = "Add Color";
	AIMenuGroup	menuGroup;
	AIMenuGroup	pluginMenuGroup;
	AIMenuGroup dummyGroup;
	AIMenuItemHandle dummyItem;
	bool sdkGroupAlreadyMade = false;
	bool admGroupAlreadyMade = false;

//This line tells AI to put the new item in the Edit menu
	menuData.groupName = kEditMenuGroup;
	menuData.itemText = ai::UnicodeString(menuCStr);

	pluginMenuData.groupName = menuGroupCStr;
	pluginMenuData.itemText = ai::UnicodeString(pluginCStr);
	
	// search through the menus and 
	// see if another SDK plug in has already set up the group
	long count;
	error = sAIMenu->CountMenuGroups( &count );
	if ( error ) goto error;
	while (count > 0)
	{
		error = sAIMenu->GetNthMenuGroup( count-1, &dummyGroup );
		if ( error ) goto error;
		char *name;
		error = sAIMenu->GetMenuGroupName( dummyGroup, (const char**)&name );
		if ( error ) goto error;
		if ( std::strcmp(name, menuGroupCStr ) == 0 )
		{
			sdkGroupAlreadyMade = true;
			count = -1;
		}
		if(std::strcmp(name,pluginCStr) == 0)
		{
			admGroupAlreadyMade = true;
		}
		count--;
	}

	if ( !sdkGroupAlreadyMade )
	{
		error = sAIMenu->AddMenuItem( message->d.self, menuGroupCStr, &menuData, 0, &dummyItem );
		if ( error ) goto error;

		error = sAIMenu->AddMenuGroupAsSubMenu( menuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		if ( error ) goto error;
	}
	
	if(!admGroupAlreadyMade)
	{
		error = sAIMenu->AddMenuItem( message->d.self, pluginCStr, &pluginMenuData, 0, &dummyItem );
		if ( error ) goto error;

		error = sAIMenu->AddMenuGroupAsSubMenu( pluginCStr, 0, dummyItem, &pluginMenuGroup );
		if ( error ) goto error;
	}
	pluginMenuData.groupName = pluginCStr;
	error = sAIMenu->AddMenuItem( message->d.self, pluginCStr, &pluginMenuData, kMenuItemWantsUpdateOption, &g->showADMNonModalDialog );
	if ( error ) goto error;

error:
	return error;
}
