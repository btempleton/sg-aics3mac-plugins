//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/SDKAboutPluginsHelper.cpp $
//
//  $Revision: #2 $
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
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

/*
*/
SDKAboutPluginsHelper::SDKAboutPluginsHelper() : fAIMenu(nil), fADMBasic(nil)
{
}

/*
*/
SDKAboutPluginsHelper::~SDKAboutPluginsHelper()
{
}

/*
*/
AIErr SDKAboutPluginsHelper::AddAboutPluginsMenuItem(SPInterfaceMessage* message, 
													 char* companyMenuGroupName, 
													 const ai::UnicodeString& companyName, 
													 char* pluginName, 
													 AIMenuItemHandle* menuItemHandle)
{
	AIErr error = kNoErr;

	if (fAIMenu == nil) {
		error = message->d.basic->AcquireSuite( kAIMenuSuite, kAIMenuSuiteVersion, (const void **) &fAIMenu );
	}
	
	if (!error && fAIMenu != nil) {
		// Add an about plug-ins menu group for the given company under Illustrator's about group.
		bool exists = false;
		error = this->GroupExists(companyMenuGroupName, exists);
		if (!error && !exists) {
			AIPlatformAddMenuItemDataUS companyRootMenuData;
			companyRootMenuData.groupName = kAboutMenuGroup;
			companyRootMenuData.itemText = companyName;	
			AIMenuItemHandle companyRootMenuItemHandle = nil;
			error = fAIMenu->AddMenuItem(message->d.self, NULL, &companyRootMenuData, kMenuItemNoOptions, &companyRootMenuItemHandle);
			if (!error) {
				AIMenuGroup companyRootMenuGroup = nil;
				error = fAIMenu->AddMenuGroupAsSubMenu(companyMenuGroupName, kMenuGroupSortedAlphabeticallyOption, companyRootMenuItemHandle, &companyRootMenuGroup);
			}
		}
	}
	
	if (!error && fAIMenu != nil) {
		// Add menu item for this plug-in under the company's about plug-ins menu group.
		AIPlatformAddMenuItemDataUS aboutPluginMenuData;
		aboutPluginMenuData.groupName = companyMenuGroupName;
		aboutPluginMenuData.itemText = ai::UnicodeString(pluginName);
		AIMenuItemHandle aboutPluginMenuItemHandle = nil;
		error = fAIMenu->AddMenuItem(message->d.self, NULL, &aboutPluginMenuData, kMenuItemNoOptions, &aboutPluginMenuItemHandle);
		if (!error) {
			*menuItemHandle = aboutPluginMenuItemHandle;
		}
	}

	if (fAIMenu != nil) {
		message->d.basic->ReleaseSuite( kAIMenuSuite, kAIMenuSuiteVersion );
		fAIMenu = nil;
	}

	return error;
}

/*
*/
void SDKAboutPluginsHelper::PopAboutBox(AIMenuMessage* message, const char* title, const char* description)
{
	AIErr error = kNoErr;
	if (fADMBasic == nil) {
		error = message->d.basic->AcquireSuite( kADMBasicSuite, kADMBasicSuiteVersion10, (const void **) &fADMBasic );
	}
	if (!error && fADMBasic != nil) {
		// Pop an about box for this plug-in.
		fADMBasic->PluginAboutBox( title, description );
	}
	if (fADMBasic != nil) {
		message->d.basic->ReleaseSuite( kADMBasicSuite, kADMBasicSuiteVersion10 );
		fADMBasic = nil;
	}
}

/*
*/
AIErr SDKAboutPluginsHelper::GroupExists(const char* targetGroupName, bool& groupAlreadyMade)
{
	AIErr error = kNoErr;
	groupAlreadyMade = false;
	long count = 0;
	AIMenuGroup dummyGroup = nil;
	error = fAIMenu->CountMenuGroups( &count );
	if ( error ) return error;
	for (long i = 0; i < count; i++) {
		error = fAIMenu->GetNthMenuGroup( i, &dummyGroup );
		if ( error ) return error;
		const char* name;
		error = fAIMenu->GetMenuGroupName( dummyGroup, &name );
		if ( error ) return error;
		if ( std::strcmp(name, targetGroupName ) == 0 )
		{
			groupAlreadyMade = true;
			break;
		}
	}
	return error;
}

// End SDKAboutPluginsHelper.cpp