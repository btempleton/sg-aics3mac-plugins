//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Webter/Source/WebterPlugin.cpp $
//
//  $Revision: #9 $
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

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "ADMDialog.h"
#include "ADMBasic.h"
#include "ADMIcon.h"
#include "IADMDrawer.hpp"
#include "IADMListEntry.hpp"

#include "AIPluginGroup.h"
#include "AIMatchingArt.h"
#include "AIMdMemory.h"
#include "AIPluginNames.h"
#include "AITypes.h"
#include "AIMenu.h"
#include "AIMenuGroups.h"
#include "AIUnicodeString.h"

#include "stringUtils.h"

#include "WebterPlugin.hpp"
#include "WebterDialog.hpp"

#include "IADMRect.hpp"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

extern "C" SPAccessSuite *sSPAccess;
extern	"C" SPBlocksSuite *sSPBlocks;

extern "C" ADMBasicSuite *sADMBasic;
extern "C" ADMDialogSuite *sADMDialog;

extern "C" AI110ArtSuite *sAIArt;
extern "C" AIMatchingArtSuite *sAIMatchingArt;
extern "C" AIMdMemorySuite *sAIMdMemory;
extern "C" AIMenuSuite *sAIMenu;
extern "C" AINotifierSuite *sAINotifier;
extern "C" AI110DocumentSuite *sAIDocument;
extern "C" AIUnicodeStringSuite *sAIUnicodeString;

#define kADMNonModalDialogID	16000

WebterPlugin *gPlugin = nil;

Plugin *AllocatePlugin(SPPluginRef pluginRef);
Plugin *AllocatePlugin(SPPluginRef pluginRef)
{
	return new WebterPlugin(pluginRef);
}

ASErr WebterPlugin::SetGlobal(Plugin *plugin)
{
	gPlugin = (WebterPlugin *) plugin;
	return kNoErr;
}

WebterPlugin::WebterPlugin(SPPluginRef pluginRef) :
	Plugin(pluginRef)
{
	fMenuItem = nil;
	fNonModalDialog = nil;
	fDialogRef = nil;
	fTool[0] = fTool[1] = fTool[2] = nil;
	fAboutPluginMenu = nil;

	strncpy(fPluginName, "Webter", kMaxStringLength);
	fArtSelectionChangedNotifier = nil;
}

WebterPlugin::~WebterPlugin()
{
}

ASErr WebterPlugin::GoMenuItem( AIMenuMessage *message )
{
	if ( message->menuItem == fMenuItem ) 
	{
		fNonModalDialog->Show( !fNonModalDialog->IsVisible() );
	}
	else if (message->menuItem == fAboutPluginMenu) 
	{
			SDKAboutPluginsHelper aboutPluginsHelper;
			aboutPluginsHelper.PopAboutBox(message, "About Webter", kSDKDefAboutSDKCompanyPluginsAlertString);
	}
	
	return kNoErr;
}

ASErr WebterPlugin::UpdateMenuItem( AIMenuMessage *message )
{
	if ( fNonModalDialog->IsVisible(  ) )
	{
		sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Hide Webter Dialog") );
	}
	else
	{
		sAIMenu->SetItemText( message->menuItem, ai::UnicodeString("Show Webter Dialog" ));
	}
	
	return kNoErr;
}

ASErr WebterPlugin::StartupPlugin( SPInterfaceMessage *message )
{
	ASErr error = Plugin::StartupPlugin( message );

	if (!error) 
	{
		// Add About Plugins menu item for this plug-in.
		SDKAboutPluginsHelper aboutPluginsHelper;
		error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
					kSDKDefAboutSDKCompanyPluginsGroupName, 
					ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
					"Webter...", 
					&fAboutPluginMenu);
	}

	// Add other menu items.
	if ( !error )
	{
		// search through the menus and
		// see if another SDK plug in has already set up the group
		AIMenuGroup menuGroup, pluginMenuGroup,dummyGroup;
		AIMenuItemHandle dummyItem;
		AIPlatformAddMenuItemDataUS menuData;
		bool groupAlreadyMade = false;
		const char *sdkMenuStr = "SDK";
		const char *menuGroupStr = "SDKWindowGroup";
		const char *pluginMenuStr = "Webter";

		menuData.groupName = kToolPalettesMenuGroup;//kOthersPalettesMenuGroup;
		menuData.itemText = ai::UnicodeString( sdkMenuStr );
		
		long count;
		error = sAIMenu->CountMenuGroups( &count );
		if ( error ) return error;
		while (count > 0)
		{
			error = sAIMenu->GetNthMenuGroup( count-1, &dummyGroup );
			if ( error ) return error;
			char *name;
			error = sAIMenu->GetMenuGroupName( dummyGroup, (const char**)&name );
			if ( error ) return error;
			if ( std::strcmp(name, menuGroupStr ) == 0 )
			{
				groupAlreadyMade = true;
				count = -1;
			}
			count--;
		}

		if ( !groupAlreadyMade && !error)
		{
			error = sAIMenu->AddMenuItem( message->d.self,
				                          menuGroupStr,
										  &menuData,
										  0,
										  &dummyItem );
			if (!error)
				error = sAIMenu->AddMenuGroupAsSubMenu(menuGroupStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		}

		menuData.groupName = menuGroupStr;
		menuData.itemText = ai::UnicodeString(pluginMenuStr);
		error = sAIMenu->AddMenuItem( message->d.self, 
								      pluginMenuStr, 
								      &menuData, 
								      0,
  								      &dummyItem );
		if ( error ) return error;

		error = sAIMenu->AddMenuGroupAsSubMenu( pluginMenuStr, 0, dummyItem, &pluginMenuGroup );
		if ( error ) return error;

		menuData.groupName = pluginMenuStr;
		char menuStr[] = "Show Webter Dialog";
		menuData.itemText = ai::UnicodeString( menuStr );

		if (!error)
			error = sAIMenu->AddMenuItem( message->d.self, 
								  	      "Webter Menu Item", 
										  &menuData, 
										  kMenuItemWantsUpdateOption,
										  &fMenuItem );
	}
	
	// add a notifier	
	if (!error)
	{
		error = sAINotifier->AddNotifier(fPluginRef, "WebterPlugin",
									 kAIArtSelectionChangedNotifier, &fArtSelectionChangedNotifier);
		if (!error)
		{
			error = sAINotifier->AddNotifier(fPluginRef, "WebterPlugin",
									 kAIDocumentChangedNotifier, &fDocumentChangedNotifier);
		}
	}
										

	return error;
}

ASErr WebterPlugin::ShutdownPlugin( SPInterfaceMessage *message )
{
	// We destroy the dialog only if it still exists
	// If ADM shuts down before our plug-in, then ADM will automatically 
	// destroy the dialog
	if ( fNonModalDialog ) 
	{									
		delete fNonModalDialog;
	}
			
	ASErr error = Plugin::ShutdownPlugin( message );

	return error;

}

ASErr WebterPlugin::Notify( AINotifierMessage *message )
{
	ASErr error = kNoErr;
	
	if (message->notifier == fAppStartedNotifier )
	{
		fNonModalDialog = new WebterDialog();
			
		if ( fNonModalDialog == nil )
		{
			error = -1;
		}
		else
		{
			fDialogRef = fNonModalDialog->Create( message->d.self,
									 "Webter Dialog",
									 kADMNonModalDialogID,
									 kADMTabbedFloatingDialogStyle,
									 0 );
			if ( fDialogRef == nil )
			{
				error = -1;
			}
		}
	}
	
	if (message->notifier == fArtSelectionChangedNotifier)
	{
		AIDictionaryRef theDictionary = NULL;
		long theArtCount = 0;
		AIArtHandle **theArtStore = NULL;
		AIMatchingArtSpec spec;
		spec.type = kAnyArt;
		spec.whichAttr = kArtSelected;
		spec.attr = kArtSelected;
		sAIMatchingArt->GetMatchingArt(&spec, 1, &theArtStore, &theArtCount);
		if (theArtStore)
		{
			AIArtHandle theArt = (*theArtStore)[0];
			AIArtHandle child = theArt;
			while (child)
			{
				theArt = child;
				sAIArt->GetArtFirstChild(theArt, &child);
			}
			sAIArt->GetDictionary(theArt, &theDictionary);
			ASBoolean isDefaultName;
			char artName[256];
			sAIArt->GetArtName(theArt, artName, 255, &isDefaultName);
			fNonModalDialog->SetArtDictionary(theDictionary, artName);
			sAIMdMemory->MdMemoryDisposeHandle((void**)theArtStore);
		}
		else
		{
			fNonModalDialog->SetArtDictionary(NULL, "no Art selected");
		}
	}

	if (message->notifier == fDocumentChangedNotifier)
	{
		AIDictionaryRef theDictionary = NULL;
		sAIDocument->GetDictionary(&theDictionary);
		if (theDictionary)
		{
			SPPlatformFileSpecification theFileSpec;
			sAIDocument->GetDocumentFileSpecification(&theFileSpec);
#if WIN32
			fNonModalDialog->SetDocumentDictionary(theDictionary, (const char *)theFileSpec.path);
#else
			SUptocstr(theFileSpec.name);
			fNonModalDialog->SetDocumentDictionary(theDictionary, (const char *)theFileSpec.name);
#endif
		}
	}
	return error;
}


