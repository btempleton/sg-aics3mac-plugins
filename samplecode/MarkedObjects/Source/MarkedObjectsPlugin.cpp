//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsPlugin.cpp $
//
//  $Revision: #18 $
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
#include "MarkedObjectsPlugin.hpp"

extern SPBasicSuite *sSPBasic;

MarkedObjectsPlugin *gPlugin = NULL;

Plugin *AllocatePlugin(SPPluginRef pluginRef);
Plugin *AllocatePlugin(SPPluginRef pluginRef)
{
	return new MarkedObjectsPlugin(pluginRef);
}

ASErr MarkedObjectsPlugin::SetGlobal(Plugin *plugin)
{
	gPlugin = (MarkedObjectsPlugin *) plugin;
	return kNoErr;
}

MarkedObjectsPlugin::MarkedObjectsPlugin(SPPluginRef pluginRef) :
	Plugin(pluginRef)
{

	menuItem = NULL;
	nonModalDialog = NULL;
	strncpy(fPluginName, "MarkedObjects", kMaxStringLength);
	artSelectionChangedNotifier = NULL;
	toolHandle = NULL;
	objectManager = NULL;
	preferences = NULL;
	aboutPluginMenu = nil;
}

MarkedObjectsPlugin::~MarkedObjectsPlugin()
{
}

ASErr MarkedObjectsPlugin::GoMenuItem( AIMenuMessage *message )
{
	try 
	{
		if ( message->menuItem == menuItem ) {
			nonModalDialog->Show( !nonModalDialog->IsVisible() );
		} else if (message->menuItem == aboutPluginMenu) {
			SDKAboutPluginsHelper aboutPluginsHelper;
			aboutPluginsHelper.PopAboutBox(message, "About MarkedObjects", kSDKDefAboutSDKCompanyPluginsAlertString);
		}
	}
	
	catch(...)
	{
		return 'ESHD';
	}
	
	return kNoErr;
}

ASErr MarkedObjectsPlugin::UpdateMenuItem( AIMenuMessage *message )
{
	if ( nonModalDialog != NULL )
		if ( nonModalDialog->IsVisible() )
		{
			ai::UnicodeString strMenu( "Hide Marked Objects Dialog" );
			sAIMenu->SetItemText( message->menuItem, strMenu );
		}
		else
		{
			ai::UnicodeString strMenu( "Show Marked Objects Dialog" );
			sAIMenu->SetItemText( message->menuItem, strMenu );
		}

	return kNoErr;
}

ASErr MarkedObjectsPlugin::StartupPlugin( SPInterfaceMessage *message )
{
	ASErr error = Plugin::StartupPlugin( message );
	if ( error ) throw ( error );

	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"MarkedObjects...", 
				&aboutPluginMenu);
	if ( error ) throw ( error );

	// Add other menu items.
	AIPlatformAddMenuItemDataUS menuData;
	AIPlatformAddMenuItemDataUS pluginMenuData;
	AIMenuGroup	menuGroup;
	AIMenuGroup	pluginMenuGroup;
	AIMenuGroup dummyGroup;
	AIMenuItemHandle dummyItem;
	AIMenuItemHandle pluginMenuItemHandle;
	bool groupAlreadyMade = false;
		
	const char * menuCStr = "SDKWindowGroup";
	const char * pluginCStr = "Marked Objects";

	long count;
	error = sAIMenu->CountMenuGroups( &count );
	if ( error ) throw ( error );
	while (count > 0)
	{
		error = sAIMenu->GetNthMenuGroup( count-1, &dummyGroup );
		if ( error ) throw error;
		char *name;
		error = sAIMenu->GetMenuGroupName( dummyGroup, (const char**)&name );
		if ( error ) throw error;
		if ( std::strcmp(name, menuCStr ) == 0 )
		{
			groupAlreadyMade = true;
			count = -1;
		}
		count--;
	}

	menuData.groupName = kOtherPalettesMenuGroup;
	ai::UnicodeString menuStr( "SDK" );
	menuData.itemText = menuStr;
	
	if ( !groupAlreadyMade )
	{
		error = sAIMenu->AddMenuItem( message->d.self, menuCStr, &menuData, 0, &dummyItem );
		if ( error ) throw( error );
		
		error = sAIMenu->AddMenuGroupAsSubMenu( menuCStr, kMenuGroupSortedAlphabeticallyOption, dummyItem, &menuGroup );
		if ( error ) throw( error );
	}
	

	pluginMenuData.groupName = menuCStr;
	pluginMenuData.itemText = ai::UnicodeString(pluginCStr);

	error = sAIMenu->AddMenuItem( message->d.self, pluginCStr, &pluginMenuData, 0,&pluginMenuItemHandle );
	if ( error ) throw error;

	error = sAIMenu->AddMenuGroupAsSubMenu( pluginCStr, 0, pluginMenuItemHandle, &pluginMenuGroup );
	if ( error ) throw error;
		
	pluginMenuData.groupName = pluginCStr;
	error = sAIMenu->AddMenuItem( message->d.self, 
								  "Marked Objects Menu", 
								  &pluginMenuData, 
								  kMenuItemWantsUpdateOption,
								  &menuItem );
	if ( error ) throw( error );
		
	
	// add some notifiers	
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
								      kAIArtSelectionChangedNotifier, &artSelectionChangedNotifier);
	if ( error ) throw( error );
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
									 kAIDocumentChangedNotifier, &documentChangedNotifier);
	if ( error ) throw( error );
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
									 "AI Command Notifier: Before Save", &documentSaveNotifierBefore );
	if ( error ) throw( error );
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
									 "AI Command Notifier: Before Save As", &documentSaveAsNotifierBefore );
	if ( error ) throw( error );
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
									 "AI Command Notifier: After Save", &documentSaveNotifierAfter );
	if ( error ) throw( error );
	error = sAINotifier->AddNotifier( fPluginRef, "MarkedObjectsPlugin",
									 "AI Command Notifier: After Save As", &documentSaveAsNotifierAfter );
	if ( error ) throw( error );

	// add a tool
	AIAddToolData toolData;
		
	toolData.title = "Marked Object Tool";
	toolData.tooltip = "Marked Object Tool";
		
	toolData.icon = sADMIcon->GetFromResource( message->d.self, 1, kToolIcons );
		
	if ( sADMIcon->GetType( toolData.icon ) == kUnknown )
		throw ((AIErr)kNoIconErr);
			
	toolData.sameGroupAs = kNoTool;
			
	sAITool->GetToolNumberFromName( kAddAnchorPointTool, &toolData.sameGroupAs );
			
	toolData.sameToolsetAs = toolData.sameGroupAs;
			
	error = sAITool->AddTool( message->d.self, "Marked Object Tool", 
			                  &toolData, kToolWantsToTrackCursorOption, &toolHandle );
	if ( error ) throw ( error );

	return error;
}

ASErr MarkedObjectsPlugin::ShutdownPlugin( SPInterfaceMessage *message )
{
	delete preferences;
	
	// We destroy the dialog only if it still exists
	// If ADM shuts down before our plug-in, then ADM will automatically 
	// destroy the dialog
	if ( nonModalDialog != NULL ) 
	{									
		delete nonModalDialog;
	}
			
	delete objectManager;

	ASErr error = Plugin::ShutdownPlugin( message );

	return error;

}

ASErr MarkedObjectsPlugin::Notify( AINotifierMessage *message )
{
	ASErr error = kNoErr;
	
	try 
	{
	
		if ( message->notifier == fAppStartedNotifier )
		{
		
			preferences = new MarkedObjectsPreferences();
			nonModalDialog = new MarkedObjectsDialog();
				
			if ( nonModalDialog == NULL )
			{
				error = -1;
			}
			else
			{
				ADMDialogRef dialogRef = nonModalDialog->Create( message->d.self,
										 "MarkedObjects Dialog",
										 kADMNonModalDialogID,
										 kADMTabbedResizingFloatingDialogStyle,
										 0 );
				if ( dialogRef == NULL )
				{
					error = -1;
				}
			}
		}
		
		if ( message->notifier == artSelectionChangedNotifier )
		{
			GetMarkedObjects();

			nonModalDialog->UpdateMarkedObjectSelected();

			if ( !IsMarkedObjectSelected() )
				nonModalDialog->Clear();
			// else
			//	SelectOurTool();
				
			nonModalDialog->UpdateBoundingBoxInfo();
		}

		if ( message->notifier == documentChangedNotifier )
		{
			nonModalDialog->Clear();

			nonModalDialog->UpdateMarkedObjectSelected();

			GetMarkedObjects();

			// if ( IsMarkedObjectSelected() )
			//	SelectOurTool();

		}
		
		if ( ( message->notifier == documentSaveNotifierBefore ) || ( message->notifier == documentSaveAsNotifierBefore ) )
		{
			objectManager->MakeLayerTemplate( true );
		}

		if ( ( message->notifier == documentSaveNotifierAfter ) || ( message->notifier == documentSaveAsNotifierAfter ) )
		{
			if (objectManager->HasMarkedObjects())
			{
				ai::FilePath fileSpec;
		
				sAIDocument->GetDocumentFileSpecification( fileSpec );
			
				WriteMarkedPoints( fileSpec );
			}
		}
	}
	
	catch(...)
	{
		return 'EPN ';
	}

	return error;
}

ASErr MarkedObjectsPlugin::EditTool( AIToolMessage* message )
{
	return kNoErr;
}

ASErr MarkedObjectsPlugin::TrackToolCursor( AIToolMessage* message )
{
#if Macintosh
	CursHandle cursor; 

	cursor = GetCursor(16001);
	if ( cursor )
		SetCursor( *cursor );
#else
	HCURSOR cursor;
	SPAccessRef access;
	SPPlatformAccessInfo spAccessInfo;

	ASErr error = sSPAccess->GetPluginAccess(message->d.self, &access);
	if( kNoErr == error)
		error = sSPAccess->GetAccessInfo(access, &spAccessInfo);
	if( kNoErr == error)
	{
		cursor = LoadCursor((HINSTANCE)spAccessInfo.defaultAccess, MAKEINTRESOURCE(16001));
		if ( cursor )
			SetCursor(cursor);
	}
#endif
	return kNoErr;
}

ASErr MarkedObjectsPlugin::ToolMouseDown( AIToolMessage* message )
{
	return kNoErr;
}

ASErr MarkedObjectsPlugin::ToolMouseDrag( AIToolMessage* message )
{
	return kNoErr;
}

ASErr MarkedObjectsPlugin::ToolMouseUp( AIToolMessage* message )
{
	ASErr error = kNoErr;
	
	try 
	{
		objectManager->CreateLayer();
		
		AIBoolean editState = objectManager->Edit( true );

		AIBoolean hiddenState = objectManager->Hide( false );

		objectManager->SetInsertionPoint();
		
		ostringstream idAsString;
		
		idAsString << objectManager->GetNextMarkedObjectID();
		
		MarkedObject* newMarkedObject = new MarkedObject( message->cursor, idAsString.str() );
		
		nonModalDialog->AddMarkedObject( newMarkedObject );
			
		objectManager->AddMarkedObject( newMarkedObject );
		
		UnSelectAllArt();
		
		newMarkedObject->Select();

		objectManager->Edit( editState );

		objectManager->Hide( hiddenState );

	}
	
	catch (...)
	{
		return 'EDTM';
	}
	
	return error;
}

ASErr MarkedObjectsPlugin::SelectTool( AIToolMessage* message )
{
	return kNoErr;
}


// if the user deselects using the shortcut keys the ResetInsertionPoint will throw
// i then start a timer and try to ResetInsertionPoint later
// hey, that worked !!!!
ASErr MarkedObjectsPlugin::DeselectTool( AIToolMessage* message )
{
	try 
	{
		UnSelectAllArt();
		
		objectManager->ResetInsertionPoint();
	}
	
	catch(...)
	{
		AITimerHandle timer;
		sAITimer->AddTimer( message->d.self, "ResetInsertionPointTimer", 10, &timer );
	}
	
	return kNoErr;
}

ASErr MarkedObjectsPlugin::Timer( AITimerMessage* message )
{
	try
	{
		UnSelectAllArt();
		
		objectManager->ResetInsertionPoint();

		sAITimer->SetTimerActive( message->timer, false );
	}
	
	catch(...)
	{
		sAITimer->SetTimerActive( message->timer, true );
	}
	
	return kNoErr;
}

ASErr MarkedObjectsPlugin::ReselectTool( AIToolMessage* message )
{
	return kNoErr;
}

ASErr MarkedObjectsPlugin::HideMarkedObjectsLayer( AIBoolean hide )
{
	objectManager->Hide(hide);
	return kNoErr;
}

void MarkedObjectsPlugin::WriteMarkedPoints( const ai::FilePath & fileSpec )
{
	ai::FilePath fullPath( fileSpec );
	
	fullPath.RemoveExtension();
	
	fullPath.AddExtension( ".bb" );
	
	ofstream fileOut( fullPath.GetFullPath().as_Platform().c_str(), ios_base::trunc|ios_base::out );

	int documentVersion = sAIDocument->GetAIVersion();
	
	fileOut << "%%Creator: Adobe Illustrator " << documentVersion << endl;

	fileOut << "%%Title: ";

	string fileName = fileSpec.GetFileName().as_Roman();
	
	fileOut << fileName << endl;

	AIFileFormatHandle fileformat = NULL;
	char *fileformatname;

	AIErr error = sAIDocument->GetDocumentFileFormat( &fileformat );
	if( error ) throw( error );

	if(fileformat != NULL)
	{
		error = sAIFileFormat->GetFileFormatName( fileformat, &fileformatname );
		if( error ) throw( error );
	}
	else
	{
		fileformatname = "Document not saved to a format";
	}
	
	fileOut << "%%File Format: " << fileformatname << endl;

	fileOut << "%%Date: ";

	AIUserDateTime dateTime;    	
    error = sAIUser->GetDateAndTime(&dateTime);
	if(error) throw( error );
	
	ai::UnicodeString timeString, dateString;	
	error = sAIUser->GetDateString(&dateTime,0,dateString);
	error = sAIUser->GetTimeString(&dateTime,0,timeString);
	if(!error)
	{
		fileOut << dateString.as_Platform().c_str() << " ";
		fileOut << timeString.as_Platform().c_str() << endl;
	}
	else
	{
		fileOut << "Error getting date/time";
	}
				
	fileOut << "%%BoundingBox: ";
	
	AIRealRect mainArtBounds = MarkedObject::GetMainArtBounds();

	short left = 0;
	short bottom = 0;
	short right = 0;
	short top = 0;

	if ( documentVersion >= 9 )
	{
		right = MarkedObject::GetBoundingBoxWidth();
		top = MarkedObject::GetBoundingBoxHeight();
	}
	else
	{
		left = static_cast<short>( _AIRealTrunc( mainArtBounds.left ));
		bottom = static_cast<short>( _AIRealTrunc( mainArtBounds.bottom ));
		AIReal temp = (AIReal)( mainArtBounds.right ) - static_cast<short>( mainArtBounds.right );
		right = static_cast<short>( mainArtBounds.right );
		if ( temp > 0.0 )
			right++;
		temp = (AIReal)( mainArtBounds.top ) - static_cast<short>( mainArtBounds.top );
		top = static_cast<short>( mainArtBounds.top );
		if ( temp > 0.0 )
			top++;
	}

	fileOut << left << " " << bottom << " " << right << " " << top << endl;
	
	fileOut << "%%HiResBoundingBox: ";

	ASReal leftHiRes;
	ASReal bottomHiRes;
	ASReal rightHiRes;
	ASReal topHiRes;

	if ( documentVersion >= 9 )
	{
		leftHiRes = 0;
		bottomHiRes = 0;
		rightHiRes = mainArtBounds.right - mainArtBounds.left;
		topHiRes = mainArtBounds.top - mainArtBounds.bottom;
	}
	else
	{
		leftHiRes = mainArtBounds.left;
		bottomHiRes = mainArtBounds.bottom;
		rightHiRes = mainArtBounds.right;
		topHiRes = mainArtBounds.top;
	}

	ios::fmtflags flags_old = fileOut.flags();
	fileOut.flags( flags_old | ios::fixed );

	int prec_old = fileOut.precision();
	
	fileOut.precision( 6 );

	fileOut << leftHiRes << " " << bottomHiRes << " " << rightHiRes << " " << topHiRes << endl;

	fileOut.precision( prec_old );
	fileOut.flags( flags_old );


	fileOut << "%%ArtBox: ";
	left = static_cast<short>( _AIRealTrunc( mainArtBounds.left ));
	bottom = static_cast<short>( _AIRealTrunc( mainArtBounds.bottom ));
	AIReal temp = (AIReal)( mainArtBounds.right ) - static_cast<short>( mainArtBounds.right );
	right = static_cast<short>( mainArtBounds.right );
	if ( temp > 0.0 )
		right++;
	temp = (AIReal)( mainArtBounds.top ) - static_cast<short>( mainArtBounds.top );
	top = static_cast<short>( mainArtBounds.top );
	if ( temp > 0.0 )
		top++;

	fileOut << left << " " << bottom << " " << right << " " << top << endl;

	fileOut << "%%HiResArtBox: ";
	leftHiRes = mainArtBounds.left;
	bottomHiRes = mainArtBounds.bottom;
	rightHiRes = mainArtBounds.right;
	topHiRes = mainArtBounds.top;

	flags_old = fileOut.flags();
	fileOut.flags( flags_old | ios::fixed );

	prec_old = fileOut.precision();
	fileOut.precision( 6 );

	fileOut << leftHiRes << " " << bottomHiRes << " " << rightHiRes << " " << topHiRes << endl;

	fileOut.precision( prec_old );
	fileOut.flags( flags_old );
	
	fileOut << "%%Coordinates: LL" << endl;

	fileOut << "%%StartMarkedPoints" << endl;

	objectManager->WriteAll( fileOut );

	fileOut << "%%EndMarkedPoints" << endl;
}

void MarkedObjectsPlugin::GetMarkedObjects( void )
{
	if ( nonModalDialog != NULL )
	{

		nonModalDialog->ClearMarkedObjectList();

		delete objectManager;
		
		objectManager = new MarkedObjectManager;
					
		AIArtHandle **artStore = NULL;
		long artCount = 0;
				
		AIMatchingArtSpec spec;
		spec.type = kAnyArt;
		spec.whichAttr = 0;
		spec.attr = 0;

		// ignore the error, we could be searching when there is no document
		// and we don't want that error reported, just let the null artStore
		// take over and silently quit the routine				
		sAIMatchingArt->GetMatchingArt( &spec, 1, &artStore, &artCount );
				
		if ( artStore != NULL )
		{
			// go through all the art deal with the non-MOs now
			// the MOs will be dealt with after calculating the bounding box of the real art
			
			vector<MarkedObject*> MOs;

			AIRealRect boundsOfMainArt = { 0, 0, 0, 0 };
			
			MOs.reserve( artCount );
			
			bool firstArtBounds = true;
			
			for ( long x = 0; x < artCount; x++ )
			{
				AIArtHandle artHandle = (*artStore)[x];
				
				MarkedObject* markedObject = new MarkedObject( artHandle );
				
				if ( markedObject == NULL ) return;
					
				if ( markedObject->IsValid() )
				{
					MOs.push_back( markedObject );
				}
				else 
				{
				
					if ( ! ( markedObject->IsParentValid() ) )
					{
						AIRealRect nonMOBounds;
						short artType;
						
						AIErr error = sAIArt->GetArtType( artHandle, &artType );
						if ( error ) throw( error );
						
						long attr = kArtHidden;
						error = sAIArt->GetArtUserAttr( artHandle, kArtHidden, &attr );
						if ( error ) throw( error );
						
						if ( artType != kGroupArt && !attr )
						{
							error = sAIArt->GetArtBounds( artHandle, &nonMOBounds );
							if ( error ) throw( error );
							
							if ( firstArtBounds )
							{
								boundsOfMainArt.top = nonMOBounds.top;
								boundsOfMainArt.left = nonMOBounds.left;
								boundsOfMainArt.bottom = nonMOBounds.bottom;
								boundsOfMainArt.right = nonMOBounds.right;
								firstArtBounds = false;
							}
							else
							{
								if ( nonMOBounds.top > boundsOfMainArt.top )
									boundsOfMainArt.top = nonMOBounds.top;
								if ( nonMOBounds.left < boundsOfMainArt.left )
									boundsOfMainArt.left = nonMOBounds.left;
								if ( nonMOBounds.bottom < boundsOfMainArt.bottom )
									boundsOfMainArt.bottom = nonMOBounds.bottom;
								if ( nonMOBounds.right > boundsOfMainArt.right )
									boundsOfMainArt.right = nonMOBounds.right;
							}
						}
					}
					
					delete markedObject;
				}
			}
			
			MarkedObject::SetMainArtBounds( boundsOfMainArt );

			// go through all the MOs and add them to the manager and the dialog

			vector<MarkedObject*>::iterator mo_iter = MOs.begin();
			vector<MarkedObject*>::iterator mo_iter_end = MOs.end();
			
			while ( mo_iter != mo_iter_end )
			{
				objectManager->AddMarkedObject( *mo_iter );
				nonModalDialog->AddMarkedObject( *mo_iter );
				mo_iter++;
			}
			
			AIErr error = sAIMdMemory->MdMemoryDisposeHandle( (void**) artStore );
			if ( error ) throw( error );
		}
	}
}

void MarkedObjectsPlugin::ResetIDs( void )
{
	objectManager->MakeLayerTemplate( false );
	objectManager->ResetIDs();
}

void MarkedObjectsPlugin::SelectOurTool( void )
{
	sAITool->SetSelectedTool( toolHandle );
}

bool MarkedObjectsPlugin::IsMarkedObjectSelected( void )
{
	bool result = false;
	
	AIArtHandle **artStore = NULL;
	long artCount = 0;
				
	AIMatchingArtSpec spec;
	spec.type = kAnyArt;
	spec.whichAttr = kArtSelected;
	spec.attr = kArtSelected;

	// ignore the error, we could be searching when there is no document
	// and we don't want that error reported, just let the null artStore
	// take over and silently quit the routine				
	sAIMatchingArt->GetMatchingArt( &spec, 1, &artStore, &artCount );
				
	if ( artStore != NULL )
	{
		for ( long x = 0; x < artCount && !result; x++ )
		{
			AIArtHandle artHandle = (*artStore)[x];
	
			MarkedObject* markedObject = new MarkedObject( artHandle );
			
			if ( markedObject->IsValid() )
			{
				result = true;
			}
			
			delete markedObject;
		}
	
		AIErr error = sAIMdMemory->MdMemoryDisposeHandle( (void**) artStore );
		if ( error ) throw( error );
	}

	return result;
}

void MarkedObjectsPlugin::UnSelectAllArt( void )
{
	AIArtHandle **artStore = NULL;
	long artCount = 0;
				
	AIMatchingArtSpec spec;
	spec.type = kAnyArt;
	spec.whichAttr = kArtSelected;
	spec.attr = kArtSelected;

	sAIMatchingArt->GetMatchingArt( &spec, 1, &artStore, &artCount );
				
	if ( artStore != NULL )
	{
		for ( long x = 0; x < artCount; x++ )
		{
			AIArtHandle artHandle = (*artStore)[x];
			
			short artType = kUnknownArt;
			
			sAIArt->GetArtType( artHandle, &artType );
			
			sAIArt->SetArtUserAttr( artHandle, kArtSelected | kArtFullySelected, 0 );
		}
		
		sAIMdMemory->MdMemoryDisposeHandle( (void**) artStore );
	}
}

void MarkedObjectsPlugin::SetDialogPreferences( void )
{
	preferences->SetDialogPreferences( nonModalDialog );
}

void MarkedObjectsPlugin::DoModalPrefs( void )
{
	preferences->DoModalPrefs();
}

void MarkedObjectsPlugin::ResetInsertionPoint( void )
{
	objectManager->ResetInsertionPoint();
}
// end MarkedObjectsPlugin.cpp
