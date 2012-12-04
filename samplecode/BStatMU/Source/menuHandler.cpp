/*
 *  menuHandler.cpp
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various menu handler functions.
#include "IllustratorSDK.h"

#include "BStatMU.h"

#include "common.h"
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"



extern AIErr goMenuItem( AIMenuMessage *message ) {
	
	AIErr error = kNoErr;
	
	if ( message->menuItem == g->BStatMUMenuItemSelected ) 
	{
		//Call the main function
		BStatMU();
	}
	
	return error;
}



extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// Add the menus.
	AIPlatformAddMenuItemDataUS menuData;
	AIPlatformAddMenuItemDataUS pluginMenuData;
	const char *menuGroupCStr = "BusStatGrp";
	const char *menuCStr = "Business Stationery";
	const char *pluginCStr = "BStat Master Updater";
	AIMenuGroup	menuGroup;
	//	AIMenuGroup	pluginMenuGroup;
	AIMenuGroup dummyGroup;
	AIMenuItemHandle dummyItem = NULL;
	bool sdkGroupAlreadyMade = false;
	//	bool admGroupAlreadyMade = false;
	
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
		//		if(std::strcmp(name,pluginCStr) == 0)
		//		{
		//			admGroupAlreadyMade = true;
		//		}
		count--;
	}
	
	if ( !sdkGroupAlreadyMade )
	{
		error = sAIMenu->AddMenuItem( message->d.self, menuGroupCStr, &menuData, 0, &dummyItem );
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuGroupAsSubMenu( menuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		if ( error ) goto error;
	}
	
	//	if(!admGroupAlreadyMade)
	//	{
	//		error = sAIMenu->AddMenuItem( message->d.self, pluginCStr, &pluginMenuData, 0, &dummyItem );
	//		if ( error ) goto error;
	//
	//		error = sAIMenu->AddMenuGroupAsSubMenu( pluginCStr, 0, dummyItem, &pluginMenuGroup );
	//		if ( error ) goto error;
	//	}
	//	pluginMenuData.groupName = pluginCStr;
	error = sAIMenu->AddMenuItem( message->d.self, menuGroupCStr, &pluginMenuData, kMenuItemWantsUpdateOption, &g->BStatMUMenuItemSelected );
	if ( error ) goto error;
	
error:
	return error;
}
