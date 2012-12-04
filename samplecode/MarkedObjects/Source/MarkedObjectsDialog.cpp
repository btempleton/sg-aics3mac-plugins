//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsDialog.cpp $
//
//  $Revision: #8 $
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

#include "MarkedObjectsDialog.hpp"

// Most of this just calls the base class to do all the work
MarkedObjectsDialog::MarkedObjectsDialog( ) : BaseADMDialog()
{
}

ADMDialogRef MarkedObjectsDialog::Create(SPPluginRef pluginRef, char *name, int dialogID, ADMDialogStyle style, int options ) 
{
	// Let the base class Create
	return ( BaseADMDialog::Create( pluginRef, name, dialogID, style, options ) );
}

ASErr MarkedObjectsDialog::Init()
{
	// Let the base class initialize
	ASErr error = BaseADMDialog::Init();
	
	// remember how big we are for the resize
	GetBoundsRect( bounds );

	// set the dialog according to the last preferences
	gPlugin->SetDialogPreferences();
	
	// hide the non-implemented items on the dialog
	IADMItem item = GetItem( kTypeStr );
	item.Hide();
	item.Disable();

	item = GetItem( kTypePopup );
	item.Hide();
	item.Disable();

	// set the type popup with the menu from the resource and select the first entry
	item = GetItem( kTypePopup );
	IADMList list = item.GetList();
	list.SetMenuID( kTypeMenuResource );
	IADMEntry entry( list.GetEntry(1) );
	entry.Select();
	
	// Set the options triangle menu
	IADMItem options = GetItem( kADMMenuItemID );
	options.SetNotifyProc( DialogPopupMenuProc );

	IADMList menuList( options.GetList() );
	menuList.SetMenuID( kDialogOptions );

	// no units on the X, Y, ID, width, and height text boxes	
	item = GetItem( kXText );
	item.SetUnits( kADMNoUnits );
	item.SetPrecision( 4 );
	
	item = GetItem( kYText );
	item.SetUnits( kADMNoUnits );
	item.SetPrecision( 4 );

	item = GetItem( kBBWidth );
	item.SetUnits( kADMNoUnits );
	item.SetPrecision( 4 );

	item = GetItem( kBBHeight );
	item.SetUnits( kADMNoUnits );
	item.SetPrecision( 4 );

	item = GetItem( kGlobalObjectsList );
	item.SetMaxTextLength( 256 );
	
	item = GetItem( kLabelText );
	item.SetItemStyle( kADMSingleLineTextEditStyle );
	 
	item = GetItem( kIDText );
	item.SetItemStyle( kADMSingleLineTextEditStyle );
	
	Clear();
	 
	return error;
}

void MarkedObjectsDialog::ClearMarkedObjectList( void)
{
	IADMItem childrenPopUp = GetItem( kGlobalObjectsList );

	childrenPopUp.Enable(true);

	IADMList childrenList = childrenPopUp.GetList();

	int entries = childrenList.NumberOfEntries();

	for( int counter = entries; counter >= 0; counter--)
		childrenList.RemoveEntry(counter);
}

void MarkedObjectsDialog::AddMarkedObject( MarkedObject* markedObject )
{
	IADMItem childrenPopUp = GetItem( kGlobalObjectsList );

	IADMList list = childrenPopUp.GetList();

	int entries = list.NumberOfEntries();
	
	int insertHere = entries;
	
	if ( markedObject == NULL ) return;
	
	if (gPreferences->GetAutoSort())
	{
		for (int x = 0; x < entries; x++ )
		{
			IADMEntry currentEntry( list.IndexEntry( x ));
			MarkedObject* currentObject = (MarkedObject*)currentEntry.GetUserData();
			if ( currentObject != NULL )
			{
				if ( *currentObject > *markedObject )
				{
					insertHere = x;
					x = entries;
				}
			}
		}
	}

	IADMEntry entry( list.InsertEntry( insertHere ));

	const string fullString = markedObject->GetFullString();

	entry.SetText( fullString.c_str() );
	
	entry.SetUserData( markedObject );
}

void MarkedObjectsDialog::Notify(IADMNotifier notifier)
{
	AIErr error = kNoErr;
	AILayerHandle layerHandle;
	ai::UnicodeString layerTitle("Marked Objects DO NOT MODIFY"); // set in MarkedObjectManager.cpp
	sAILayer->GetLayerByTitle(&layerHandle,layerTitle);
	AIBoolean visible = true;
	try 
	{
	
		if (notifier.IsNotifierType(kADMUserChangedNotifier))
		{
			IADMItem item(notifier.GetItem());

			if (item)
			{
				int itemID = item.GetID();

				switch (itemID)
				{
					case kGlobalObjectsList:
						error = sAILayer->GetLayerVisible(layerHandle,&visible);
						if(error) throw(error);
						if(visible)							
							NewGlobalObjectSelected();
						break;
					case kUpdateButton:
						UpdateMarkedObject();
						break;
					case kHideShowAllButton:
						char text[100];
						item.GetText( text, 100 );
						if ( strcmp( text, "Hide All" ) == 0 )
						{
							gPlugin->HideMarkedObjectsLayer( true );
							item.SetText( "Show All" );
						}
						else
						{
							gPlugin->HideMarkedObjectsLayer( false );
							item.SetText( "Hide All" );
						}
						break;
					default:
						break;
				}
			}
		}
		
		if ( notifier.IsNotifierType( kADMBoundsChangedNotifier ) )
			ResizeLabelFrame();

		BaseADMDialog::Notify(notifier);
	}
	
	catch(...)
	{
		return;
	}
}

void MarkedObjectsDialog::Destroy()
{
	BaseADMDialog::Destroy();
}

MarkedObjectsDialog::~MarkedObjectsDialog()
{
}

void MarkedObjectsDialog::ResizeLabelFrame( void )
{
	IADMRect newBounds;
	GetBoundsRect( newBounds );
	
	int newWidth = ( newBounds.right - newBounds.left ) - ( bounds.right - bounds.left );
	int newHeight = ( newBounds.bottom - newBounds.top ) - ( bounds.bottom - bounds.top );
	
	if ( newWidth || newHeight )
	{
		IADMItem item = GetItem( kGlobalObjectsList );
		IADMRect itemBounds;
		item.GetBoundsRect( itemBounds );
		item.Invalidate();
		itemBounds.right += newWidth;
		itemBounds.bottom += newHeight;
		
		// you have to set the global bounds here or this
		// will recurse and crash
		bounds.top = newBounds.top;
		bounds.left = newBounds.left;
		bounds.right = newBounds.right;
		bounds.bottom = newBounds.bottom;

		item.SetBoundsRect( itemBounds );

		IADMList list( item.GetList() );
		IADMRect entryTextRect;
		list.GetEntryTextRect( entryTextRect );
		entryTextRect.right = bounds.right;
		list.SetEntryTextRect( entryTextRect );

		item = GetItem( kIDText );
		item.GetBoundsRect( itemBounds );
		item.Invalidate();
		itemBounds.right += newWidth;
		item.SetBoundsRect( itemBounds );

		item = GetItem( kLabelText );
		item.GetBoundsRect( itemBounds );
		item.Invalidate();
		itemBounds.right += newWidth;
		item.SetBoundsRect( itemBounds );

	}
}

void MarkedObjectsDialog::NewGlobalObjectSelected(void)
{
	IADMItem item = GetItem( kGlobalObjectsList );
	IADMList list( item.GetList() );
	ADMEntryRef entryRef = list.GetActiveEntry();
	if (entryRef == NULL)
	{
		gPlugin->UnSelectAllArt();
		gPlugin->ResetInsertionPoint();
		return;
	}
	IADMEntry entry( entryRef );
	
	MarkedObject * markedObject = (MarkedObject*)entry.GetUserData();
	if ( markedObject == NULL ) return;
		
	AIRealPoint location = markedObject->GetLocation();
	
	item = GetItem( kXText );
	item.SetFloatValue( location.h );
	
	item = GetItem( kYText );
	item.SetFloatValue( location.v );
	
	item = GetItem( kIDText );
	item.SetText( markedObject->GetID().c_str() );
	
	item = GetItem( kLabelText );
	const string label = markedObject->GetLabel();
	item.SetText( label.c_str() );

	gPlugin->UnSelectAllArt();
	
	markedObject->Select();
	
}

void ASAPI MarkedObjectsDialog::DialogPopupMenuProc( ADMItemRef item, ADMNotifierRef notifier )
{
	try 
	{
		IADMItem iADMItem( item );
		IADMList menuList( iADMItem.GetList() );
		IADMEntry entry( menuList.GetActiveEntry() );
		int id = entry.GetID();
		
		if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier) )
		{	
			if ( id == kOptionsSave )
			{
 				const ai::UnicodeString title( "Where do you want to save the Marked Objects?" );
				const AIPlatformFileDlgOpts * dlgOpts = NULL;
				bool forceLocalFileView = false;
				const ai::UnicodeString defaultName;
				ai::FilePath ioFilePath;
				AIErr e = sAIUser->PutFileDialog( title, dlgOpts, forceLocalFileView, defaultName, ioFilePath );
				if ( e == kNoErr )
				{
					gPlugin->WriteMarkedPoints( ioFilePath );
					
					// sAIUndo->UndoChanges();
				}
				
			} 
			else if ( id == kOptionsResetIDs ) 
			{
				gPlugin->ResetIDs();
				gPlugin->GetMarkedObjects();
			} 
			else if ( id == kOptionsPreferences )
			{
				gPlugin->DoModalPrefs();
				gPlugin->GetMarkedObjects();
			}
			else 
			{
				throw( "Unkown ID in Dialog Popup Menu!" );
			}
		} 
	}
	
	catch( char * /*message*/ )
	{
		return;
	}
	
	catch(...)
	{
		return;
	}
}

void MarkedObjectsDialog::UpdateMarkedObjectSelected( void )
{
	try
	{
		IADMItem item = GetItem( kGlobalObjectsList );
		IADMList list( item.GetList() );
			
		int numberOfEntries = list.NumberOfEntries();

		for( int a = 0; a < numberOfEntries; a++ )		
		{
			IADMEntry entry( list.IndexEntry( a ) );
			
			MarkedObject* markedObject = (MarkedObject*)entry.GetUserData();
			if ( markedObject == NULL ) return;
			
			if ( markedObject->IsSelected() )
			{
				entry.Select();
				item = GetItem( kUpdateButton );
				item.Enable();
				AIRealPoint location = markedObject->GetLocation();
	
				item = GetItem( kXText );
				item.SetFloatValue( location.h );
				
				item = GetItem( kYText );
				item.SetFloatValue( location.v );
				
				item = GetItem( kIDText );
				item.SetText( markedObject->GetID().c_str() );
				
				item = GetItem( kLabelText );
				const string label = markedObject->GetLabel();
				item.SetText( label.c_str() );

				break;
			}
		}
	}
	
	catch(...)
	{
		return;
	}
}

void MarkedObjectsDialog::UpdateMarkedObject(void)
{
	try 
	{
		IADMItem item = GetItem( kGlobalObjectsList );
		IADMList list( item.GetList() );
		IADMEntry entry( list.GetActiveEntry() );
		
		MarkedObject* markedObject = (MarkedObject*)entry.GetUserData();
		if ( markedObject == NULL ) return;
		
		IADMItem itemLabel = GetItem( kLabelText );
		
		vector<char> vc(itemLabel.GetTextLength() + 1);

		itemLabel.GetText( &vc[0], vc.size() );

		string newString;
		
		newString.assign( vc.begin(), vc.begin() + vc.size() );
		
		markedObject->SetLabel( newString );
		
		IADMItem idItem = GetItem( kIDText );

		vc.reserve(idItem.GetTextLength() + 1);

		idItem.GetText( &vc[0], vc.size() );

		newString.assign( vc.begin(), vc.begin() + vc.size() );
		
		markedObject->SetID( newString );
		
		IADMItem xItem = GetItem( kXText );
		float x = xItem.GetFloatValue();
		
		IADMItem yItem = GetItem( kYText );
		float y = yItem.GetFloatValue();
		
		AIRealPoint location;
		location.h = x;
		location.v = y;
		
		markedObject->SetLocation( location );

		gPlugin->GetMarkedObjects();
		
	}
	
	catch(...)
	{
		return;
	}
}

void MarkedObjectsDialog::Clear( void )
{
	IADMItem item = GetItem( kXText );
	item.SetFloatValue( 0 );
		
	item = GetItem( kYText );
	item.SetFloatValue( 0 );

	item = GetItem( kIDText );
	item.SetText( " " );

	item = GetItem( kLabelText );
	item.SetText( " " );
	
	item = GetItem( kGlobalObjectsList );
	IADMList list( item.GetList() );
	IADMEntry entry( list.GetActiveEntry() );
	entry.Deselect();
	
	item = GetItem( kUpdateButton );
	item.Disable();
}

void MarkedObjectsDialog::UpdateBoundingBoxInfo( void )
{
	IADMItem item = GetItem( kBBWidth );
	item.SetFloatValue( MarkedObject::GetBoundingBoxWidth() );

	item = GetItem( kBBHeight );
	item.SetFloatValue( MarkedObject::GetBoundingBoxHeight() );

}
// end MarkedObjectsDialog.cpp

