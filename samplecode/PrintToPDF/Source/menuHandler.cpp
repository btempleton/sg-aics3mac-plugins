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

#include "BStatMU.h"
#include "Callbacks.h"

#include "common.h"
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"



extern AIErr goMenuItem( AIMenuMessage *message ) {

	AIErr error = kNoErr;
	
	if ( message->menuItem == g->PrintToPDFMenuItemSelected ) 
	{
		//Show the dialog
		showDialog(  );
	} else if ( message->menuItem == g->BStatMUMenuItemSelected ) 
	{
		if ( BStatMU() ) {
			//What to do if it worked.
		}
	}
	
	return error;
}



extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;

	
//	AIMenuGroup	pluginMenuGroup;
	AIMenuGroup dummyGroup;
	AIMenuItemHandle dummyItem;
	bool sdkGroupAlreadyMade = false;
//	bool admGroupAlreadyMade = false;

	//Setup menu data for Print to PDF
	const char *printToPDFPluginCStr = "Export PDF for Manufacturing...";
	AIPlatformAddMenuItemDataUS printToPDFMenuData;
	printToPDFMenuData.groupName = kSaveForMenuGroup;
	printToPDFMenuData.itemText = ai::UnicodeString(printToPDFPluginCStr);
	
	//Set up sub-menu and menu item for Bstat Updater
	const char *bstatUpdaterMenuGroupCStr = "BusStatGrp";
	const char *bstatUpdaterMenuCStr = "Business Stationery";
	const char *bstatUpdaterPluginCStr = "BStat Master Updater";
	AIPlatformAddMenuItemDataUS menuData;
	AIMenuGroup	menuGroup;
	AIPlatformAddMenuItemDataUS bstatUpdaterMenuData;
	menuData.groupName = kEditMenuGroup;
	menuData.itemText = ai::UnicodeString(bstatUpdaterMenuCStr);
	bstatUpdaterMenuData.groupName = bstatUpdaterMenuGroupCStr;
	bstatUpdaterMenuData.itemText = ai::UnicodeString(bstatUpdaterPluginCStr);


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
		if ( std::strcmp(name, bstatUpdaterMenuGroupCStr ) == 0 )
		{
			sdkGroupAlreadyMade = true;
			count = -1;
		}
		count--;
	}

	if ( !sdkGroupAlreadyMade )
	{
		error = sAIMenu->AddMenuItem( message->d.self, bstatUpdaterMenuGroupCStr, &menuData, 0, &dummyItem );
		if ( error ) goto error;

		error = sAIMenu->AddMenuGroupAsSubMenu( bstatUpdaterMenuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		if ( error ) goto error;
	}
	

	error = sAIMenu->AddMenuItem( message->d.self, printToPDFPluginCStr, &printToPDFMenuData, kMenuItemNoOptions, &g->PrintToPDFMenuItemSelected );
	if ( error ) goto error;
	
	
	error = sAIMenu->AddMenuItem( message->d.self, bstatUpdaterPluginCStr, &bstatUpdaterMenuData, kMenuItemNoOptions, &g->BStatMUMenuItemSelected );
	sAIMenu->UpdateMenuItemAutomatically(g->BStatMUMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, 0, 0, kIfOpenDocument, 0);
	if ( error ) goto error;

error:
	return error;
}
