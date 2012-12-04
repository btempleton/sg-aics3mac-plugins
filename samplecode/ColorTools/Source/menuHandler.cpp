/*
 *  menuHandler.cpp
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various menu handler functions.
#include "IllustratorSDK.h"

#include "FixBlack.h"

#include "common.h"
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"



extern AIErr goMenuItem( AIMenuMessage *message ) {
	
	AIErr error = kNoErr;
	
	if ( message->menuItem == g->FixBlackMenuItemSelected ) 
	{
		//Call the main function
		if ( FixBlack() ) {
			//			sADMBasic->MessageAlert("Black was fixed.");
			//		} else {
			//			sADMBasic->MessageAlert("Black was not fixed.");
		}
	}
	if ( message->menuItem == g->AddColorMenuItemSelected ) 
	{
		sADMDialog->Show( g->AddColorDialog, !( sADMDialog->IsVisible( g->AddColorDialog ) ) );
	}
	if ( message->menuItem == g->FindReplaceMenuItemSelected ) 
	{
		sADMDialog->Show( g->FindReplaceDialog, !( sADMDialog->IsVisible( g->FindReplaceDialog ) ) );
	}
	
	if (error)
		goto error;
	
error:
	return error;
	
}


extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	
	// Add the menus.
	AIPlatformAddMenuItemDataUS menuData;
	AIPlatformAddMenuItemDataUS fixBlackMenuData;
	AIPlatformAddMenuItemDataUS addColorMenuData;
	AIPlatformAddMenuItemDataUS findReplaceMenuData;
	
	const char *menuGroupCStr = "SDKEditGroup";
	const char *menuCStr = "Modify Swatches";
	const char *fixBlackCStr = "Fix Black";
	const char *addColorCStr = "Add Color";
	const char *findReplaceCStr = "Find and Replace Graphics";
	AIMenuGroup	menuGroup;
	AIMenuGroup	pluginMenuGroup;
	AIMenuGroup dummyGroup;
	AIMenuItemHandle dummyItem;
	bool sdkGroupAlreadyMade = false;
	bool addColorGroupAlreadyMade = false;
	bool findReplaceGroupAlreadyMade = false;
	
	//This line tells AI to put the new item in the Type menu
	menuData.groupName = kEditMenuGroup;
	menuData.itemText = ai::UnicodeString(menuCStr);
	
	fixBlackMenuData.groupName = menuGroupCStr;
	fixBlackMenuData.itemText = ai::UnicodeString(fixBlackCStr);
	
	addColorMenuData.groupName = menuGroupCStr;
	addColorMenuData.itemText = ai::UnicodeString(addColorCStr);
	
	findReplaceMenuData.groupName = menuGroupCStr;
	findReplaceMenuData.itemText = ai::UnicodeString(findReplaceCStr);

	
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
		if(std::strcmp(name,addColorCStr) == 0)
		{
			addColorGroupAlreadyMade = true;
		}
		if(std::strcmp(name,findReplaceCStr) == 0)
		{
			findReplaceGroupAlreadyMade = true;
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
	
	
	if(!addColorGroupAlreadyMade)
	{
		error = sAIMenu->AddMenuItem( message->d.self, addColorCStr, &addColorMenuData, 0, &dummyItem );
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuGroupAsSubMenu( addColorCStr, 0, dummyItem, &pluginMenuGroup );
		if ( error ) goto error;
	}
	
	if(!findReplaceGroupAlreadyMade)
	{
		error = sAIMenu->AddMenuItem( message->d.self, findReplaceCStr, &findReplaceMenuData, 0, &dummyItem );
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuGroupAsSubMenu( findReplaceCStr, 0, dummyItem, &pluginMenuGroup );
		if ( error ) goto error;
	}
	
	
	error = sAIMenu->AddMenuItem( message->d.self, fixBlackCStr, &fixBlackMenuData, kMenuItemNoOptions, &g->FixBlackMenuItemSelected );
	if ( error ) goto error;
	
	addColorMenuData.groupName = addColorCStr;
	error = sAIMenu->AddMenuItem( message->d.self, addColorCStr, &addColorMenuData, kMenuItemWantsUpdateOption, &g->AddColorMenuItemSelected );
	if ( error ) goto error;
	
	findReplaceMenuData.groupName = findReplaceCStr;
	error = sAIMenu->AddMenuItem( message->d.self, findReplaceCStr, &findReplaceMenuData, kMenuItemWantsUpdateOption, &g->FindReplaceMenuItemSelected );
	if ( error ) goto error;
	
error:
	return error;
}

AIErr updateMenuItem( AIMenuMessage *message ) {
	
	//	long inArtwork;
	//	long isSelected;
	//	long isTrue;
	AIErr error = kNoErr;
	
	if (message->menuItem == g->AddColorMenuItemSelected) {
		if ( sADMDialog->IsVisible( g->AddColorDialog ) )
		{
			sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Hide Add Color") );
		}
		else
		{
			sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Show Add Color") );
		}		
	}
	if (message->menuItem == g->FindReplaceMenuItemSelected) {
		if ( sADMDialog->IsVisible( g->FindReplaceDialog ) )
		{
			sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Hide Find and Replace Graphics") );
		}
		else
		{
			sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Show Find and Replace Graphics") );
		}
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

