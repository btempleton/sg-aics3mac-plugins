//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerPlugin.cpp $
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
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"
#include "SnippetRunnerID.h"
#include "SnippetRunnerPlugin.h"
#include "SnippetRunnerSuites.h"
#include "SnippetRunnerPanel.h"
#include "SnippetRunnerLog.h"
#include "SnippetRunnerParameter.h"
#include "SnippetRunnerPreferences.h"
#include "SDKErrors.h"
#include "SnippetRunnerUnitTestManager.h"

extern ImportSuite gPostStartupSuites[];

SnippetRunnerPlugin*	gPlugin = NULL;

Plugin* AllocatePlugin(SPPluginRef pluginRef);

/*
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef)
{
	return new SnippetRunnerPlugin(pluginRef);
}

/*
*/
ASErr SnippetRunnerPlugin::SetGlobal(Plugin *plugin)
{
	gPlugin = (SnippetRunnerPlugin *) plugin;
	return kNoErr;
}

/*
*/
SnippetRunnerPlugin::SnippetRunnerPlugin(SPPluginRef pluginRef) :
	Plugin(pluginRef)
{
	strncpy(fPluginName, kSnippetRunnerPluginName, kMaxStringLength);
	fAboutPluginMenu = NULL;
	fShowHidePanelMenu = NULL;
	fSnippetRunnerPanel = NULL;
}

/*
*/
SnippetRunnerPlugin::~SnippetRunnerPlugin()
{
}

/*
*/
ASErr SnippetRunnerPlugin::Message(char *caller, char *selector, void *message)
{
	ASErr result = kNoErr;
	try {
		result = Plugin::Message(caller, selector, message);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	catch (...) {
		result = kCantHappenErr;
	}
	if (result) {
		if (result == kUnhandledMsgErr) {
			// Defined by Plugin.hpp and used in Plugin::Message - ignore
			result = kNoErr;
		}
		else {
			// TODO should really call gPlugin->ReportError
			aisdk::report_error(result);
		}
	}
	return result;
}

/*
*/
ASErr SnippetRunnerPlugin::GoMenuItem( AIMenuMessage *message )
{
	ASErr result = kNoErr;
	try {
		if (message->menuItem == this->fAboutPluginMenu) {
			SDKAboutPluginsHelper aboutPluginsHelper;
			aboutPluginsHelper.PopAboutBox(message, "About SnippetRunner", kSDKDefAboutSDKCompanyPluginsAlertString);
		}
		else if (message->menuItem == this->fShowHidePanelMenu) {
			if (this->fSnippetRunnerPanel) {
				ASBoolean visible = this->fSnippetRunnerPanel->IsVisible();
				this->fSnippetRunnerPanel->Show(!visible);
			}
		}
	}
	catch(ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnippetRunnerPlugin::UpdateMenuItem( AIMenuMessage *message )
{
	// Update the Show/Hide panel menu.
	ASBoolean visible = false;
	if (fSnippetRunnerPanel) {
		visible = fSnippetRunnerPanel->GetDialog().IsVisible();
	}
	sAIMenu->CheckItem(fShowHidePanelMenu, visible);
	return kNoErr;
}

/*
*/
ASErr SnippetRunnerPlugin::StartupPlugin( SPInterfaceMessage *message )
{
	ASErr error = kNoErr;
	try {
		error = Plugin::StartupPlugin( message );
		aisdk::check_ai_error(error);
		error = this->AddNotifiers(message);
		aisdk::check_ai_error(error);
		error = this->AddMenus(message);
		aisdk::check_ai_error(error);
	}
	catch (ai::Error& ex) {
		error = ex;
	}
	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::ShutdownPlugin( SPInterfaceMessage *message )
{
	ASErr error = kNoErr;
	this->ReleasePostStartupSuites();
	error = Plugin::ShutdownPlugin( message );
	return error;
}

ASErr SnippetRunnerPlugin::PostStartupPlugin()
{
	ASErr error = kNoErr;
	try {
		// Acquire suites we could not get on plug-in startup.
		error = this->AcquirePostStartupSuites();
		if (error) {
			error = kNoErr;
			// Ignore - this should not be a fatal error.
			// We want the SnippetRunner panel to open and
			// we want snippets to be checking that the
			// suite pointers they depend on are not NULL
			// before using them.
		}

		// Read preferences.
		SnippetRunnerPreferences::Instance();

		// Create SnippetRunner panel.
		if (fSnippetRunnerPanel == NULL) {
			fSnippetRunnerPanel = new SnippetRunnerPanel(fPluginRef);	
			SDK_ASSERT(fSnippetRunnerPanel);
		}
	} 
	catch (ai::Error ex) {
		error = ex;
	}
	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::AddNotifiers( SPInterfaceMessage *message )
{
	ASErr error = kNoErr;
	try {
		error = sAINotifier->AddNotifier(message->d.self, "SnippetRunner " kAIApplicationShutdownNotifier, kAIApplicationShutdownNotifier, &fAppShutdownNotifier);
		aisdk::check_ai_error(error);
		error = sAINotifier->AddNotifier(message->d.self, "SnippetRunner " kAIArtSelectionChangedNotifier,  kAIArtSelectionChangedNotifier, &fArtSelectionChangedNotifier);
		aisdk::check_ai_error(error);
	}
	catch (ai::Error& ex) {
		error = ex;
	}
	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::Notify( AINotifierMessage *message )
{
	ASErr error = kNoErr;

	if ( message->notifier == fAppShutdownNotifier ) {
		if ( fSnippetRunnerPanel != NULL ) {									
			delete fSnippetRunnerPanel;
		}
		SnippetRunnerLog::DeleteInstance();
		SnippetRunnerParameter::DeleteInstance();
		SnippetRunnerPreferences::Instance()->DeleteInstance();
		SnippetRunnerUnitTestManager::Instance()->DeleteInstance();
	}
	else if (message->notifier == fArtSelectionChangedNotifier) {
		fSnippetRunnerPanel->HandleModelChanged();
	}

	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::AddMenus( SPInterfaceMessage *message )
{
	ASErr error = kNoErr;

	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				kSnippetRunnerPluginName "...", 
				&fAboutPluginMenu);
	aisdk::check_ai_error(error);

	// Add an SDK menu group to the Windows menu.
	const char* kSDKWindowsMenuGroup = "SDKWindowGroup";
	bool exists = false;
	error = this->MenuGroupExists(kSDKWindowsMenuGroup, exists);
	aisdk::check_ai_error(error);
	if (!exists) {
		AIPlatformAddMenuItemDataUS menuItemData;
		menuItemData.groupName = kOtherPalettesMenuGroup;
		menuItemData.itemText = ai::UnicodeString("SDK");	
		AIMenuItemHandle menuItemHandle = nil;
		error = sAIMenu->AddMenuItem(message->d.self, NULL, &menuItemData, kMenuItemNoOptions, &menuItemHandle);
		aisdk::check_ai_error(error);
		AIMenuGroup menuGroup = nil;
		error = sAIMenu->AddMenuGroupAsSubMenu(kSDKWindowsMenuGroup, kMenuGroupSortedAlphabeticallyOption, menuItemHandle, &menuGroup);
		aisdk::check_ai_error(error);
	}
	
	// Add menu item for this plug-in under the company's about plug-ins menu group.
	AIPlatformAddMenuItemDataUS showHidePanelMenuData;
	showHidePanelMenuData.groupName = kSDKWindowsMenuGroup;
	showHidePanelMenuData.itemText = ai::UnicodeString(kSnippetRunnerPluginName);
	AIMenuItemHandle showHidePanelMenuItemHandle = nil;
	error = sAIMenu->AddMenuItem(message->d.self, NULL, &showHidePanelMenuData, kMenuItemWantsUpdateOption, &showHidePanelMenuItemHandle);
	aisdk::check_ai_error(error);
	fShowHidePanelMenu = showHidePanelMenuItemHandle;

	return error;
}

/*
*/
AIErr SnippetRunnerPlugin::MenuGroupExists(const char* targetGroupName, bool& groupAlreadyMade)
{
	AIErr error = kNoErr;
	groupAlreadyMade = false;
	long count = 0;
	AIMenuGroup dummyGroup = nil;
	error = sAIMenu->CountMenuGroups( &count );
	if ( error ) return error;
	for (long i = 0; i < count; i++) {
		error = sAIMenu->GetNthMenuGroup( i, &dummyGroup );
		aisdk::check_ai_error(error);
		const char* name;
		error = sAIMenu->GetMenuGroupName( dummyGroup, &name );
		aisdk::check_ai_error(error);
		if ( std::strcmp(name, targetGroupName ) == 0 )
		{
			groupAlreadyMade = true;
			break;
		}
	}
	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::AcquirePostStartupSuites()
{
	ASErr error = kNoErr;
	for ( int i = 0; gPostStartupSuites[i].name != nil; ++i ) {
		if ( gPostStartupSuites[i].suite != nil ) {
			ASErr tmperr = sSPBasic->AcquireSuite( gPostStartupSuites[i].name, 
										gPostStartupSuites[i].version, 
										(const void **) gPostStartupSuites[i].suite );
			SDK_ASSERT_MSG_NOTHROW(!tmperr, 
				aisdk::format_args("AcquireSuite failed for suite=%s version=%d", 
					gPostStartupSuites[i].name, 
					gPostStartupSuites[i].version));
			if (tmperr && !error) {
				// A suite could not be acquired - note first error encountered for later return to caller then carry on.
				error = tmperr;
			}
		}
	}
	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::ReleasePostStartupSuites()
{
	ASErr error = kNoErr;

	for ( int i = 0; gPostStartupSuites[i].name != nil; ++i ) {
		if ( gPostStartupSuites[i].suite != nil ) {
			void **s = (void **) gPostStartupSuites[i].suite;
			if (*s != nil) {
				ASErr tmperr = sSPBasic->ReleaseSuite( gPostStartupSuites[i].name, gPostStartupSuites[i].version );
				*s = nil;
				SDK_ASSERT_MSG_NOTHROW(!tmperr, 
					aisdk::format_args("ReleaseSuite failed for suite=%s version=%d", 
						gPostStartupSuites[i].name, 
						gPostStartupSuites[i].version));
				if (tmperr && !error) {
					// A suite could not be released - note first error encountered for later return to caller then carry on.
					error = tmperr;
				}
			}
		}
	}

	return error;
}

/*
*/
ASErr SnippetRunnerPlugin::Timer(AITimerMessage* message)
{
	// This plug-in only has one timer - used for running unit tests.
	SnippetRunnerUnitTestManager::Instance()->GoTimer(message);
	return kNoErr;
}

/*
*/
void SnippetRunnerPlugin::NotifyLogChanged()
{
	if (fSnippetRunnerPanel) {
		fSnippetRunnerPanel->HandleLogChanged();
	}
}

/*
*/
void SnippetRunnerPlugin::NotifyEndUnitTest()
{
	if (fSnippetRunnerPanel) {
		fSnippetRunnerPanel->HandleModelChanged();
	}
}

// End SnippetRunnerPlugin.cpp