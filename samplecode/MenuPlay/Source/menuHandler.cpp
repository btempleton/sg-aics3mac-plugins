//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MenuPlay/Source/menuHandler.cpp $
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
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "plugindlg.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

extern AIErr goMenuItem( AIMenuMessage *message ) {



	AIErr error = kNoErr;
//	AIPlatformMenuItem	pmenuThrowAway;

	error = acquireSuites( message->d.basic );
	if ( error )
		goto error;

	// Compare the menuItem selected (in the message) with our stored values to see if we do anything
	if (message->menuItem == g->aboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About MenuPlay", kSDKDefAboutSDKCompanyPluginsAlertString);
	}	
	else if ( message->menuItem == g->checkMeAIMenu ) { // Check Me menu item
		g->checkMeChecked = !g->checkMeChecked;
		sMenu->CheckItem(  g->checkMeAIMenu, g->checkMeChecked );
		}
	else if ( message->menuItem == g->multiDemoAIMenu ) { // Disable Check Me menu item
		if ( g->checkMeEnabled ) {
			error = sMenu->DisableItem( g->checkMeAIMenu ); // disable checkMeMenu
		
			sMenu->SetItemIcon( g->multiDemoAIMenu, 1 );	
			}
		else { 
			error = sMenu->EnableItem( g->checkMeAIMenu ); // enable checkMeMenu

			sMenu->SetItemIcon( g->multiDemoAIMenu, 2 );
			}
		
		g->checkMeEnabled = !g->checkMeEnabled;
		}
		
error:
	releaseSuites( message->d.basic );
	return error;





}


AIErr updateMenuItem( AIMenuMessage *message ) {



	long inArtwork;
	long isSelected;
	long isTrue;
	AIErr error;

	error = acquireSuites( message->d.basic );
	if ( error )
		goto error;

	// This is only valid when kSelectorAIMacUpdateMenuItem is received, which is why we're here
	error = sMenu->GetUpdateFlags( &inArtwork, &isSelected, &isTrue );
	if ( error )
		goto error;		

	// Do something based on the result.  It's easier than GetMatchingArt for this example, and can
	// also be used for a quick check before more processing.
	if ( isSelected & kIfGuide ) {
		sMenu->SetItemText( g->manualUpdateAIMenu, "Do Something To Selected Guides" );
		}
	else if ( inArtwork & kIfGuide ) {
		sMenu->SetItemText( g->manualUpdateAIMenu, "Do Something To All Guides" );
		}

error:
	releaseSuites( message->d.basic );
	return error;





}



extern AIErr addMenu( SPInterfaceMessage *message ) {

	AIErr error = kNoErr;

	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"MenuPlay...", 
				&g->aboutPluginMenu);

	// Add other menus.
	AIMenuItemHandle		throwAwayAIMenu;
	AIPlatformAddMenuItemData throwAwayMenuData;
	AIMenuGroup				throwAwayMenuGroup;
	char strBuffer[255];
	
	#define kMenuPlayMenuGroup	"Menu Play Group"
	#define kSDKMenuGroup	"SDK Group"
	
	// First we create a normal plug-in menu to use a hierarchical root							
	throwAwayMenuData.groupName = "Window Utilities";
	
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 1, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );
  
	error = sMenu->AddMenuItem( message->d.self, kSDKMenuGroup, &throwAwayMenuData, 
								0, &throwAwayAIMenu );
	if ( error )
		goto error;

	// Now we declare the menu item a menu group
	sMenu->AddMenuGroupAsSubMenu( kSDKMenuGroup, 0, throwAwayAIMenu, &throwAwayMenuGroup );
	
	// Now we can add menu items to it.
	throwAwayMenuData.groupName = kSDKMenuGroup;
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 8, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );	

	error = sMenu->AddMenuItem( message->d.self, "Auto Update 1", &throwAwayMenuData, 0,
								&throwAwayAIMenu );
	if ( error )
		goto error;		

	// enabled for paths and no masks in the selection
	error = sMenu->UpdateMenuItemAutomatically( throwAwayAIMenu, kAutoEnableMenuItemAction,
				kIfPath | kIfGuide, kIfMask,
				0, 0,
				0, 0 );	 // don't care about other update options
		
	if ( error )
		goto error;	

	sMenu->AddMenuGroupAsSubMenu( kMenuPlayMenuGroup, 0, throwAwayAIMenu, &throwAwayMenuGroup );

	throwAwayMenuData.groupName = kMenuPlayMenuGroup;
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 2, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );	

	error = sMenu->AddMenuItem( message->d.self, "Menu Play", &throwAwayMenuData, 0,
								&throwAwayAIMenu );
	if ( error )
		goto error;		

	error = sMenu->UpdateMenuItemAutomatically( throwAwayAIMenu, kAutoEnableMenuItemAction,
				0, 0,	 // don't care about what's in artwork
				kIfGroup, // is selected and
				kIfTextPath,	 // are not selected
				0, 0 );	 // don't care about other update options
		
	if ( error )
		goto error;		
	


	// The second item just auto dims if the layer is locked or has locked objects.
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 3, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );	
	error = sMenu->AddMenuItem( message->d.self, "Auto Update 2", &throwAwayMenuData, 0,
								&throwAwayAIMenu );
	if ( error )
		goto error;		
	error = sMenu->UpdateMenuItemAutomatically( throwAwayAIMenu, kAutoEnableMenuItemAction,
				0, 0,	 // don't care about what's in artwork
				0, // is selected and
				0,	 // are not selected
				kIfCurrentLayerIsEditable, // is true
				kIfAnyLockedObjects );	 // is false
						
	if ( error )
		goto error;		

	// The third item doesn't auto dim, but requests the update selector.
	// The automatic update option is the best way to handle menu updates.
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 4, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );

	error = sMenu->AddMenuItem( message->d.self, "Manual Update 1", &throwAwayMenuData, 
								kMenuItemWantsUpdateOption, &g->manualUpdateAIMenu );
	if ( error )
		goto error;		


	// Seperators work just like std. mac menus
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 5, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );
	error = sMenu->AddMenuItem( message->d.self, "seperator", &throwAwayMenuData, 
								kMenuItemWantsUpdateOption, &throwAwayAIMenu );
	if ( error )
		goto error;		



	// These menus we'll actually make do something, in this case check and uncheck itself
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 6, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );

	// We keep the AIMenuItemHandle to figure out which menu was selected later
	error = sMenu->AddMenuItem( message->d.self, "Check me", &throwAwayMenuData, 
								0, &g->checkMeAIMenu );
	if ( error )
		goto error;		

	//sMenu->SetItemCmd( g->checkMeAIMenu, 'u', kMenuItemCmdShiftModifier );
	g->checkMeChecked = false;


	// This menu will dim the above menu and change it's own icon
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	*strBuffer = '\0';
	error = sADMBasic->GetIndexString(message->d.self, kMenuStringResID, 7, strBuffer, sizeof(strBuffer));
	if (error)
		goto error;
	throwAwayMenuData.itemText = SUctopstr ( strBuffer );
	error = sMenu->AddMenuItem( message->d.self, "Disable Check Me", &throwAwayMenuData, 
								0, &g->multiDemoAIMenu );
	if ( error )
		goto error;		
	
	sMenu->SetItemIcon( g->multiDemoAIMenu, 2 );

	g->checkMeEnabled = true;




error:
	return error;





}
