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
	
	if ( message->menuItem == g->CombinePBItemSelected ) 
	{
		int foo = 0;//Call main combine function
	}
	
	
	if (error)
		goto error;
	
error:
	return error;
	
}


extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	AIMenuGroup	menuGroup;
	
	AIPlatformAddMenuItemDataUS pbMenuData;
	const char *pbMenuGroupCStr = "btPB";
	const char *pbMenuCStr = "Panto/Border";
	AIPlatformAddMenuItemDataUS combinePBMenuData;
	const char *combinePBCStr = "Combine Panto/Border";
	
	//This line tells AI not to put the command in a menu, but allow shortcut key to be created
	pbMenuData.groupName = kHiddenOtherObjectMenuGroup;
	pbMenuData.itemText = ai::UnicodeString(pbMenuCStr);
	
	combinePBMenuData.groupName = pbMenuGroupCStr;
	combinePBMenuData.itemText = ai::UnicodeString(combinePBCStr);
	
	//Add menu items (invisible!)
	if ( !SDKGroupAlreadyMade(pbMenuGroupCStr) ) {
		AIMenuItemHandle dummyItem;
		error = sAIMenu->AddMenuItem( message->d.self, pbMenuGroupCStr, &pbMenuData, 0, &dummyItem );
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuGroupAsSubMenu( pbMenuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		if ( error ) goto error;
	}
	
	error = sAIMenu->AddMenuItem( message->d.self, combinePBCStr, &combinePBMenuData, kMenuItemNoOptions, &g->CombinePBItemSelected );
	if ( error ) goto error;
	
	
error:
	return error;
}

bool SDKGroupAlreadyMade(const char *menuGroupCStr) {
	// search through the menus and 
	// see if another SDK plug in has already set up the group
	AIMenuGroup dummyGroup;
	
	long count;
	sAIMenu->CountMenuGroups( &count );
	while (count > 0)
	{
		sAIMenu->GetNthMenuGroup( count-1, &dummyGroup );
		char *name;
		sAIMenu->GetMenuGroupName( dummyGroup, (const char**)&name );
		if ( std::strcmp(name, menuGroupCStr ) == 0 )
		{
			return true;
		}
		count--;
	}
	return false;
}

