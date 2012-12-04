//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/LiveDropShadow/Source/menuHandler.cpp $
//
//  $Revision: #5 $
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
#include "pluginGroupHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

extern AIErr addMenu(SPInterfaceMessage *message)
{
    AIErr result = kNoErr;

	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"LiveDropShadow...", 
				&g->aboutPluginMenu);

	// Add other menus.
	AIPlatformAddMenuItemData sdkMenuData;
	AIPlatformAddMenuItemData menuItemData;
	char sdkText[] = "SDK";
	char itemText[255];

	AIMenuGroup throwawayMenuGroup = NULL;
	AIAddPluginGroupData	pluginGroupData;
	AIMenuItemHandle		throwawayMenu = NULL;

	sdkMenuData.groupName = kObjectPathsMenuGroup;
	sdkMenuData.itemText = SUctopstr(sdkText);
	AIMenuItemHandle sdkMenuItemHandle = NULL;

	result = sMenu->AddMenuItem(message->d.self, "SDKObject", &sdkMenuData, 0, &sdkMenuItemHandle);
	if(result) return result;

	AIMenuGroup sdkGroupMenu = nil;

	result = sMenu->AddMenuGroupAsSubMenu("SDKObject", kMenuGroupNoOptions, sdkMenuItemHandle, &sdkGroupMenu);
	if(result) return result;

	pluginGroupData.minor = kMinorVersion;
	pluginGroupData.major = kMajorVersion;
	pluginGroupData.desc  = "Live Drop Shadow Plug-in Group";
	result = sAIPluginGroup->AddAIPluginGroup( message->d.self, kNameSuffix "class", &pluginGroupData, kPluginGroupWantsAutoTranslateOption, &g->dsPluginGroupHandle );
		
	if ( result == kNoErr ) {
	
		sADMBasic->GetIndexString( message->d.self, kMenuStringsResID, kGroupMenuIndex, itemText, sizeof(itemText) );
		menuItemData.groupName = "SDKObject";
		menuItemData.itemText = SUctopstr ( itemText );
		result = sMenu->AddMenuItem( message->d.self, kNameSuffix "group", &menuItemData, 0, &throwawayMenu );
	
	}
		
	if ( result == kNoErr ) {

		sMenu->AddMenuGroupAsSubMenu(kNameSuffix "group", 0, throwawayMenu, &throwawayMenuGroup );
		if ( throwawayMenuGroup == NULL )
			result = kTooManyMenuItemsErr;
	
	}
		
	if ( result == kNoErr ) {

		sADMBasic->GetIndexString( message->d.self, kMenuStringsResID, kMakeMenuIndex, itemText, sizeof(itemText) );
		menuItemData.groupName = kNameSuffix "group";
		menuItemData.itemText = SUctopstr ( itemText );
		result = sMenu->AddMenuItem( message->d.self, kNameSuffix "make menu", &menuItemData, kMenuItemWantsUpdateOption, &g->dsMakeMenuHandle );
	
	}
		
	if ( result == kNoErr ) {

		sADMBasic->GetIndexString( message->d.self, kMenuStringsResID, kReleaseMenuIndex, itemText, sizeof(itemText) );
		menuItemData.groupName = kNameSuffix "group";
		menuItemData.itemText = SUctopstr ( itemText );
		result = sMenu->AddMenuItem( message->d.self, kNameSuffix "release menu", &menuItemData, kMenuItemWantsUpdateOption, &g->dsReleaseMenuHandle );
	
	}
		
/*
	if ( result == kNoErr ) {
		sADMBasic->GetIndexString( message->d.self, kMenuStringsResID, kSeparatorMenuIndex, itemText, sizeof(itemText) );
		menuItemData.groupName = kNameSuffix "group";
		//menuItemData.itemText = "separator"; // "/001-";
		menuItemData.itemText = SUctopstr (itemText);
		result = sMenu->AddMenuItem( message->d.self, kNameSuffix "separator menu", &menuItemData, kMenuItemWantsUpdateOption, &menuItem );
	
	}
*/
		
	if ( result == kNoErr ) {

		sADMBasic->GetIndexString( message->d.self, kMenuStringsResID, kAdjustMenuIndex, itemText, sizeof(itemText) );
		menuItemData.groupName = kNameSuffix "group";
		menuItemData.itemText = SUctopstr (itemText);
		result = sMenu->AddMenuItem( message->d.self, kNameSuffix "adjust menu", &menuItemData, kMenuItemWantsUpdateOption, &g->dsAdjustMenuHandle );
	
	}
	
	return result;
}

extern AIErr goEnable( AIMenuMessage *message ) {

	AIErr result = kNoErr;

	long index, count;
	AIArtHandle **store = NULL;
//	AIMenuItemHandle MenuItem;

	int havePaths = false;
	int havePlugins = false;
	int haveOthers = false;
	int enable = false;

	if ( result == kNoErr ) {
	
		if ( sAIMatchingArt->GetSelectedArt( &store, &count ) ) {
		
			store = NULL;
			count = 0;
		
		}
	
	}

	if ( store != NULL ) {
	
		for ( index = 0; ( result == kNoErr ) && ( index < count ); index++ ) {
		
			AIArtHandle art = (*store)[index];
			short artType = kUnknownArt;
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtType( art, &artType );
			
			}
			
			if ( artType == kPluginArt ) {
				
				AIPluginGroupHandle artEntry;
				
				if ( result == kNoErr ) {
				
					result = sAIPluginGroup->GetPluginArtPluginGroup( art, &artEntry );
				
				}
				
				if ( result == kNoErr ) {
				
					if ( artEntry != g->dsPluginGroupHandle) {
					
						artType = kUnknownArt;
					
					}
					
				}
			
			}
			
			switch ( artType ) {
			
				case kPathArt:
					havePaths = true;
				break;

				case kGroupArt:
				case kCompoundPathArt:
					// nothing
				break;
				case kTextFrameArt:
					havePaths = true;
				break;
				case kPluginArt:
					havePlugins = true;
				break;
				
				default:
					haveOthers = true;
				break;
			
			}
		
		}
	
	}
	
	if ( result == kNoErr ) {
	
		if ( message->menuItem == g->dsMakeMenuHandle ) {
		
			enable = havePaths && !haveOthers;
			
		} else if ( message->menuItem == g->dsReleaseMenuHandle ) {
		
			enable = havePlugins;
			
		} else if ( message->menuItem == g->dsAdjustMenuHandle ) {
		
			enable = havePlugins;
			
		} else {
		
			// unknown menu item
			
		}
	
	}
	
	
	if ( result == kNoErr ) {
	
		if ( enable ) {
		
			sMenu->EnableItem( message->menuItem );
		
		} else {
		
			sMenu->DisableItem( message->menuItem );
		
		}
	
	}

	if ( store != NULL ) {
	
		sAIMdMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle) store );
	
	}
	
	return result;
	
}


extern AIErr goMenu( AIMenuMessage *message ) {

	AIErr result = kNoErr;

	if (message->menuItem == g->aboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About LiveDropShadow", kSDKDefAboutSDKCompanyPluginsAlertString);
		return result;
	}	

	long index, count;
	AIArtHandle **store = NULL;

	if ( result == kNoErr ) {
	
		if ( sAIMatchingArt->GetSelectedArt( &store, &count ) ) {
		
			store = NULL;
			count = 0;
		
		}
	
	}

	if ( store != NULL ) {

		AIArtHandle object = NULL;
		ObjectData data;
		
		if ( message->menuItem == g->dsMakeMenuHandle ) {
		
			StartLensObject( &object, &data );
			
		} else if ( message->menuItem == g->dsAdjustMenuHandle ) {
		
			FirstLensObject( &object, &data );
		
		}
		
		for ( index = 0; ( result == kNoErr ) && ( index < count ); index++ ) {
		
			AIArtHandle art = (*store)[index];
			short artType = kUnknownArt;
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtType( art, &artType );
			
			}

			if ( artType == kPluginArt ) {
			
				AIPluginGroupHandle artEntry;
				
				if ( result == kNoErr ) {
				
					result = sAIPluginGroup->GetPluginArtPluginGroup(art, &artEntry);
				
				}
				
				if ( result == kNoErr ) {
				
					if ( artEntry != g->dsPluginGroupHandle ) {
					
						artType = kUnknownArt;
					
					}
				
				}
			
			}

			if ( ( message->menuItem == g->dsMakeMenuHandle ) && ( artType == kPathArt ) || ( artType == kTextFrameArt )   ) {
			
				if ( result == kNoErr ) {
				
					result = appendPluginGroup( &object, &data, art );
				
				}
			
			} else if ( ( message->menuItem == g->dsReleaseMenuHandle ) && ( artType == kPluginArt ) ) {
			
				if ( result == kNoErr ) {
				
					result = ReleaseLensObject( art );
				
				}
			
			} else if ( ( message->menuItem == g->dsAdjustMenuHandle ) && ( artType == kPluginArt ) ) {
			
				if ( result == kNoErr ) {
				
					result = ModifyLensObject( &object, &data, art );
				
				}
			
			} else {
			
				// unknown menu item or unknown art type
			
			}
		
		}

		if ( message->menuItem == g->dsMakeMenuHandle ) {
		
			FinishLensObject( &object, &data );
			
		} else if ( message->menuItem == g->dsAdjustMenuHandle ) {
		
			LastLensObject( &object, &data );

		}
				
	}

	if ( store != NULL ) {
	
		sAIMdMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle) store );
	
	}
	
	return result;
	
}
