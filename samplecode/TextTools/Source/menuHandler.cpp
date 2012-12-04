/*
 *  menuHandler.cpp
 *  TextTools
 *
 *  Created by Comp Mac 8a on 10/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

// This file defines the various menu handler functions.
#include "IllustratorSDK.h"

#include "TextTools.h"
#include "FixFreehandType.h"
#include "DictFuncs.h"

#include "common.h"
#include "menuHandler.h"
#include "AIMenuGroups.h"
#include "stringUtils.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

extern AIErr goMenuItem( AIMenuMessage *message ) {
	
	AIErr error = kNoErr;

	if ( message->menuItem == g->ConvertToPointTypeMenuItemSelected ) 
	{
		//Call the main function
		if ( ConvertToPointType() ) {
			//What to do if it worked.
		}
	} else if ( message->menuItem == g->FixFreehandTypeMenuItemSelected ) 
	{
		//Call the main function
		if ( FixFreehandType() ) {
			//What to do if it worked.
		}
	} else if ( message->menuItem == g->AlignLeftMenuItemSelected ) 
	{
		//Call the main function
		if ( Align(ATE::kLeftJustify) ) {
			//Set the undo/redo text
			error = sAIUndo->SetUndoText("Undo Align", "Redo Align");
		}
	} else if ( message->menuItem == g->AlignCenterMenuItemSelected ) 
	{
		//Call the main function
		if ( Align(ATE::kCenterJustify) ) {
			//Set the undo/redo text
			error = sAIUndo->SetUndoText("Undo Align", "Redo Align");
		}
	} else if ( message->menuItem == g->AlignRightMenuItemSelected ) 
	{
		//Call the main function
		if ( Align(ATE::kRightJustify) ) {
			//Set the undo/redo text
			error = sAIUndo->SetUndoText("Undo Align", "Redo Align");
		}
	} else if ( message->menuItem == g->CreateMICRBarcodeMenuItemSelected ) 
	{
		//Call the main function
		if ( CreateMICRBarcode() ) {
			//Set the undo/redo text
			error = sAIUndo->SetUndoText("Undo Create MICR Barcode", "Redo Create MICR Barcode");
		}
	}
	
	
	
	if (error)
		goto error;
	
error:
	return error;
	
}



extern AIErr addMenu( SPInterfaceMessage *message ) {
	AIErr error = kNoErr;
	AIMenuGroup	menuGroup;
	
//*********** Text Tools
	{
		AIPlatformAddMenuItemDataUS textToolsMenuData;
		const char *textToolsMenuGroupCStr = "SDKTextToolsGroup";
		const char *textToolsMenuCStr = "Text Tools";
		AIPlatformAddMenuItemDataUS convertToPointTypeMenuData;
		const char *convertToPointTypeCStr = "Make Point Type";
		AIPlatformAddMenuItemDataUS fixFreehandMenuData;
		const char *fixFreehandTypeCStr = "Fix Freehand Type";
		
		//This line tells AI to put the text tools menu in the Type menu
		textToolsMenuData.groupName = kTypeLayoutMenuGroup;
		textToolsMenuData.itemText = ai::UnicodeString(textToolsMenuCStr);
		
		convertToPointTypeMenuData.groupName = textToolsMenuGroupCStr;
		convertToPointTypeMenuData.itemText = ai::UnicodeString(convertToPointTypeCStr);
		fixFreehandMenuData.groupName = textToolsMenuGroupCStr;
		fixFreehandMenuData.itemText = ai::UnicodeString(fixFreehandTypeCStr);
		
		//Check for Text Tools Menu and add menu items
		if ( !SDKGroupAlreadyMade(textToolsMenuGroupCStr) ) {
			AIMenuItemHandle dummyItem;
			error = sAIMenu->AddMenuItem( message->d.self, textToolsMenuGroupCStr, &textToolsMenuData, 0, &dummyItem );
			if ( error ) goto error;
			
			error = sAIMenu->AddMenuGroupAsSubMenu( textToolsMenuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
			if ( error ) goto error;
		}
		
		error = sAIMenu->AddMenuItem( message->d.self, convertToPointTypeCStr, &convertToPointTypeMenuData, kMenuItemNoOptions, &g->ConvertToPointTypeMenuItemSelected );
		sAIMenu->UpdateMenuItemAutomatically(g->ConvertToPointTypeMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, kIfText, 0, 0, 0);
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuItem( message->d.self, fixFreehandTypeCStr, &fixFreehandMenuData, kMenuItemNoOptions, &g->FixFreehandTypeMenuItemSelected );
		sAIMenu->UpdateMenuItemAutomatically(g->FixFreehandTypeMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, kIfText, 0, 0, 0);
		if ( error ) goto error;
	}
	
//************* Align
	{
		AIPlatformAddMenuItemDataUS alignMenuData;
		const char *alignMenuGroupCStr = "SDKAlignGroup";
		const char *alignMenuCStr = "Align";
		//Add the align menu to the objects menu
		alignMenuData.groupName = kObjectAttribsMenuGroup;
		alignMenuData.itemText = ai::UnicodeString(alignMenuCStr);
	
	//****Align Left
		AIPlatformAddMenuItemDataUS alignLeftMenuData;
		const char *alignLeftCStr = "Left";
		alignLeftMenuData.groupName = alignMenuGroupCStr;
		alignLeftMenuData.itemText = ai::UnicodeString(alignLeftCStr);
		
	//****Align Center
		AIPlatformAddMenuItemDataUS alignCenterMenuData;
		const char *alignCenterCStr = "Center";
		alignCenterMenuData.groupName = alignMenuGroupCStr;
		alignCenterMenuData.itemText = ai::UnicodeString(alignCenterCStr);

	//****Align Right
		AIPlatformAddMenuItemDataUS alignRightMenuData;
		const char *alignRightCStr = "Right";
		alignRightMenuData.groupName = alignMenuGroupCStr;
		alignRightMenuData.itemText = ai::UnicodeString(alignRightCStr);
		
		//Check for Align Menu and add menu items
		if ( !SDKGroupAlreadyMade(alignMenuGroupCStr) ) {
			AIMenuItemHandle dummyItem;
			error = sAIMenu->AddMenuItem( message->d.self, alignMenuGroupCStr, &alignMenuData, 0, &dummyItem );
			if ( error ) goto error;
			
			error = sAIMenu->AddMenuGroupAsSubMenu( alignMenuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
			if ( error ) goto error;
		}
		
		error = sAIMenu->AddMenuItem( message->d.self, alignLeftCStr, &alignLeftMenuData, kMenuItemIgnoreSort, &g->AlignLeftMenuItemSelected );
		sAIMenu->UpdateMenuItemAutomatically(g->AlignLeftMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, kIfAnyArt, 0, 0, 0);
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuItem( message->d.self, alignCenterCStr, &alignCenterMenuData, kMenuItemIgnoreSort, &g->AlignCenterMenuItemSelected );
		sAIMenu->UpdateMenuItemAutomatically(g->AlignCenterMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, kIfAnyArt, 0, 0, 0);
		if ( error ) goto error;
		
		error = sAIMenu->AddMenuItem( message->d.self, alignRightCStr, &alignRightMenuData, kMenuItemIgnoreSort, &g->AlignRightMenuItemSelected );
		sAIMenu->UpdateMenuItemAutomatically(g->AlignRightMenuItemSelected, kAutoEnableMenuItemAction, 0, 0, kIfAnyArt, 0, 0, 0);
		if ( error ) goto error;
	}

//************* MICR BARCODE
	{
		AIPlatformAddMenuItemDataUS micrbarcodeMenuData;
		const char *micrbarcodeMenuGroupCStr = "SDKMICRGroup";
		const char *micrbarcodeMenuCStr = "MICR Barcode";
		//Add the micr barcode menu to the objects menu
		micrbarcodeMenuData.groupName = kTypePluginsMenuGroup1;
		micrbarcodeMenuData.itemText = ai::UnicodeString(micrbarcodeMenuCStr);
		
		//****Create MICR Barcode
		AIPlatformAddMenuItemDataUS createMicrbarcodeMenuData;
		const char *createMicrbarcodeCStr = "Create MICR Barcode";
		createMicrbarcodeMenuData.groupName = micrbarcodeMenuGroupCStr;
		createMicrbarcodeMenuData.itemText = ai::UnicodeString(createMicrbarcodeCStr);
		
		//Check for Align Menu and add menu items
		if ( !SDKGroupAlreadyMade(micrbarcodeMenuGroupCStr) ) {
			AIMenuItemHandle dummyItem;
			error = sAIMenu->AddMenuItem( message->d.self, micrbarcodeMenuGroupCStr, &micrbarcodeMenuData, 0, &dummyItem );
			if ( error ) goto error;
			
			error = sAIMenu->AddMenuGroupAsSubMenu( micrbarcodeMenuGroupCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
			if ( error ) goto error;
		}
		
		error = sAIMenu->AddMenuItem( message->d.self, createMicrbarcodeCStr, &createMicrbarcodeMenuData, kMenuItemIgnoreSort|kMenuItemWantsUpdateOption, &g->CreateMICRBarcodeMenuItemSelected );
		if ( error ) goto error;
	}

	
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
		const char *name;
		sAIMenu->GetMenuGroupName( dummyGroup, &name );
		if ( std::strcmp(name, menuGroupCStr ) == 0 )
		{
			return true;
		}
		count--;
	}
	return false;
}

extern AIErr updateMenuItem( AIMenuMessage *message ) {
//Check if we have a micr line object in the document dictionary
//If we do, nothing needs to be selected, as we already know where the micr line is
	if ( CheckDictionaryForArtObjectWithIdentifier(MICR_LINE_LABEL) ) {
		sAIMenu->EnableItem(message->menuItem);
	} else {
		//If we couldn't find a micr number in the dictionary, we'll check if some text is selected
		long inArtwork, isSelected, isTrue;
		sAIMenu->GetUpdateFlags(&inArtwork, &isSelected, &isTrue);
		if (isSelected & kIfText) {
			sAIMenu->EnableItem(message->menuItem);
		} else {
			sAIMenu->DisableItem(message->menuItem);
		}
	}
	return kNoErr;
}
