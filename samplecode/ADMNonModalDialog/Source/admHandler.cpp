//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/admHandler.cpp $
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

#include "common.h"
#include "admHandler.h"
#include "ADMResource.h"
#include "Resource.h"

// This file contains createADMDialog() which initializes the ADM dialog
// It also the initialization and destroy procedures for the dialog
// Private functions include all the notifier procs.


/*******************************************************************************
 **
 ** ADM Dialog
 **
 **/

// Create the Non-modal dialog. This does not necessarily show the dialog on 
// the screen. If the dialog was hidden at last shutdown, it will not be shown 
// until sADMDialog->Show() is called. 
// Note: the init proc, DlgInit, will be called immediately following sADMDialog->Create()
AIErr createADMDialog( AINotifierMessage *message ) {
	AIErr error = kNoErr;

	g->nonModalDialog = sADMDialog->Create( message->d.self,"ADMNonModalDialog", kADMNonModalDialogID,
	 kADMTabbedFloatingDialogStyle, DlgInit, nil, 0 );

	if (error)
		goto error;
error:
	return error;
}

// Initialize dialog items and notification procedures for the ADM dialog
ASErr ASAPI DlgInit(ADMDialogRef dlg)
{
	ASErr					fxErr = kNoErr;
	AIAppContextHandle		AppContext;
	ADMItemRef				menuItemRef, popupItemRef, beepButtonItemRef, beepBeepButtonItemRef, spinEditPopupItemRef;

	ADMListRef				menuListRef, popupListRef, spinEditPopupListRef;
	ADMEntryRef				entry;
	SPPluginRef				pluginRef;
	char					tipString[64];
	char					groupName[64] = "SDK Dialogs";

	ADMPoint location, size;
	ADMRect	rect, dimensions, boundsRect;
	long	positionCode;
	tipString[0] = 0;
	
	// Set up the application context, so that suite calls will work
	pluginRef = sADMDialog->GetPluginRef(dlg);
	sAIAppContext->PushAppContext(pluginRef, &AppContext);

	// Acquire yourself to stay in memory
	sSPAccess->AcquirePlugin( pluginRef, &g->accessRef );
	
	// Acquire suites to stay in memory
	acquireSuites( g->basic );

	/*******************************************************************************
 	 **	Dialog level stuff
	 **/
	 
	// Attach the dialog-level callbacks
	sADMDialog->SetDestroyProc( dlg, DlgDestroyProc );
	// sADMDialog->SetNotifyProc( dlg, DlgNotifyProc );

	// Do this only if you have a resizable dialog of type kADMTabbedResizingFloatingDialogStyle or kADMResizingFloatingDialogStyle
	// Set the increments and min/max sizes to limit grow behavior.
	//sADMDialog->SetMinWidth( dlg, layerMinWidth );
	//sADMDialog->SetMinHeight( dlg, layerMinHeight );
	//sADMDialog->SetMaxWidth( dlg, layerMaxWidth );
	//sADMDialog->SetVerticalIncrement( dlg, layerLineHeight );
	
	// Setup popup menu on dialog
	menuItemRef = sADMDialog->GetItem(dlg, kADMMenuItemID);
	sADMItem->SetNotifyProc( menuItemRef, dialogPopupMenuProc );
	if (menuItemRef)
	{
		menuListRef = sADMItem->GetList(menuItemRef);
		if (menuListRef)
		{
			// 700 is the MENU resource of the list
			sADMList->SetMenuID(menuListRef, 700);
			//	CheckPastePref(menuListRef);
		}
		sADMItem->SetTrackProc(menuItemRef, dialogPopupMenuTrackProc); // catch mouse down to do setup based on modifier keys
	}

	/*******************************************************************************
 	 **	Popup menu item
	 **
	 ** Note: when building Windows resources, ALWAYS create spin edit, popup, and 
	 **       spin edit popup menus BEFORE any other controls. If these items are
	 **       defined AFTER radio buttons or checkboxes they will NOT work properly.
	 **/

	// create popup list
	popupItemRef = sADMDialog->GetItem( dlg, kpopupItem );
	sADMItem->SetNotifyProc( popupItemRef, PopupProc);
	popupListRef = sADMItem->GetList( popupItemRef );
	sADMList->SetMenuID(popupListRef, kpopupMenuID);
	// initialize popup list
	entry = sADMList->GetEntry( popupListRef, 1 ); // the number you pass is 1 based not 0 based
	sADMEntry->Select( entry, true );

	/*******************************************************************************
 	 **	SpinEditPopup menu item
	 **
	 ** Note: when building Windows resources, ALWAYS create spin edit, popup, and 
	 **       spin edit popup menus BEFORE any other controls. If these items are
	 **       defined AFTER radio buttons or checkboxes they will NOT work properly.
	 **/

	// create SpinEditPopup list
	spinEditPopupItemRef = sADMDialog->GetItem( dlg, kspinEditPopupItem );
	sADMItem->SetNotifyProc( spinEditPopupItemRef, spinEditPopupProc);
	spinEditPopupListRef = sADMItem->GetList( spinEditPopupItemRef );
	sADMList->SetMenuID(spinEditPopupListRef, kspinEditPopuMenuID);
	// initialize SpinEditPopup list
	entry = sADMList->GetEntry( spinEditPopupListRef, 4 );
	sADMItem->Invalidate( spinEditPopupItemRef );
	sADMEntry->Select( entry, true );

	/*******************************************************************************
 	 **	Radio button items
	 **/

	// all 3 radio button items will have the same notifier proc.
	sADMItem->SetNotifyProc( sADMDialog->GetItem(dlg, kradioButton1Item), radioButtonProc );
	sADMItem->SetNotifyProc( sADMDialog->GetItem(dlg, kradioButton2Item), radioButtonProc );
	sADMItem->SetNotifyProc( sADMDialog->GetItem(dlg, kradioButton3Item), radioButtonProc );

	// initialize radio button group (items 7-9)
	// note: radio buttons with consecutive item numbers will automatically 
	//       be grouped by ADM
	sADMItem->SetBooleanValue( sADMDialog->GetItem(dlg, kradioButton1Item), true );
	sADMItem->SetBooleanValue( sADMDialog->GetItem(dlg, kradioButton2Item), false );
	sADMItem->SetBooleanValue( sADMDialog->GetItem(dlg, kradioButton3Item), false );	

	/*******************************************************************************
 	 **	Checkbox Items
	 **/

	// each check box item will have its own notifier proc.
	sADMItem->SetNotifyProc( sADMDialog->GetItem(dlg, kcheckBox1Item), checkBox1Proc );
	sADMItem->SetNotifyProc( sADMDialog->GetItem(dlg, kcheckBox2Item), checkBox2Proc );

	// initialize checkboxes
	sADMItem->SetBooleanValue( sADMDialog->GetItem(dlg, kcheckBox1Item), true );
	sADMItem->SetBooleanValue( sADMDialog->GetItem(dlg, kcheckBox2Item), false );

	/*******************************************************************************
 	 **	Button Items
	 **/

	// Attach the callbacks for the beep buttons
	beepButtonItemRef = sADMDialog->GetItem(dlg, kbeepItem);
	if (beepButtonItemRef)
	{
		sADMItem->SetNotifyProc(beepButtonItemRef, beepButtonUp);
		
	//	You could also do this stuff:
	//	sADMItem->SetItemStyle(beepButtonItemRef, kADMBlackRectPictureButtonStyle);
	//	sADMItem->SetTrackProc(beepButtonItemRef, ButtonTrackProc);
	//	sADMItem->SetPictureID(beepButtonItemRef, kADMDeleteEntryPictureID, NULL);
	//	sADMItem->SetSelectedPictureID(beepButtonItemRef, kADMDeleteEntryPictureID, NULL);
	//	sADMItem->SetDisabledPictureID(beepButtonItemRef, kADMDeleteEntryDisabledPictureID, NULL);
	//	sADMItem->SetCursorID(beepButtonItemRef, pluginRef, kADMFingerCursorID, NULL);
	//	fxErr = sADMBasic->GetIndexString(
    //  		pluginRef, kTooltipStrings, trashButtonTipIndex, tipString, 62);
	//	if (fxErr)
	//		fxErr = kNoErr;	// don't let lack of a tool tip stop the show
	//	else if (tipString[0])
	//		sADMItem->SetTipString(beepButtonItemRef, tipString);
	}
	
	beepBeepButtonItemRef = sADMDialog->GetItem(dlg, kbeepBeepItem);
	if (beepBeepButtonItemRef)
	{
		sADMItem->SetNotifyProc(beepBeepButtonItemRef, beepBeepButtonUp);
		
	//	You could also do this stuff:
	//	sADMItem->SetItemStyle(beepBeepButtonItemRef, kADMBlackRectPictureButtonStyle);
	//	sADMItem->SetTrackProc(beepBeepButtonItemRef, ButtonTrackProc);
	//	sADMItem->SetPictureID(beepBeepButtonItemRef, kADMNewEntryPictureID, NULL);
	//	sADMItem->SetSelectedPictureID(beepBeepButtonItemRef, kADMNewEntryPictureID, NULL);
	//	sADMItem->SetDisabledPictureID(beepBeepButtonItemRef, kADMNewEntryDisabledPictureID, NULL);
	//	sADMItem->SetCursorID(beepBeepButtonItemRef, pluginRef, kADMFingerCursorID, NULL); 
	//	fxErr = sADMBasic->GetIndexString(
    // 		pluginRef, kTooltipStrings, newButtonTipIndex, tipString, 62);
	//	if (fxErr)
	//		fxErr = kNoErr;	// don't let lack of a tool tip stop the show
	//	else if (tipString[0])
	//		sADMItem->SetTipString(beepBeepButtonItemRef, tipString);
	}


	/*******************************************************************************
 	 *	Restore dialog position
	 *
 	 *	A note about Dialog position code:
 	 *  positionCode is a code to restore a 
 	 *  dialog's position within a docked/tabbed group.  The group is 
 	 *  referred to by name, this being the name of the ADM Dialog that is
 	 *  the first tab in the top dock of the group. 
 	 *
 	 *  You don't need to know what positionCode means, but if you are curious:
 	 *
 	 *  byte		  		meaning
 	 *  ----		 		------------------------------
 	 *	1 (0x000000ff)	dock position. 0 is no dock, 1 is first docked (i.e. top dock), 2 etc.
 	 *	2 (0x0000ff00)	tab position, 0 is no tab group, 1 is the 1st tab, 2 etc.
	 *	3 (0x00010000)	bit 16, boolean, 1 for front tab.
 	 *	3 (0x00020000)	bit 17, boolean, 0 is zoom up, 1 is zoom down.
 	 *	3 (0x00040000)	bit 18, boolean, 0 is in hidden dock, 1 is in visible dock.
 	 *	4 (0x00000000)	reserved. currently unused
	 *
	 **/
	 
	// Get the last known Docking group and Docking code out of the Prefs file
	//sASLib->strcpy( groupName, kLayersPaletteDockGroup ); // is this a default value?
	sAIPreference->GetStringPreference( "ADMNonModalDialog", "kADM_DPDockGroupStr", groupName );
	positionCode = 0x00001c00; // Default: no dock, no tab group, front tab, zoom down, visible
	sAIPreference->GetIntegerPreference( "ADMNonModalDialog", "kADM_DPDockCodeStr", &positionCode );

	// Pick a default location in case it has never come up before on this machine
	sADMDialog->GetBoundsRect( dlg, &boundsRect );
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);

	// Get the last known location out of the Prefs file
	sAIPreference->GetPointPreference( "ADMNonModalDialog", "kADM_DPLocationStr", &location );

	size.h = 208;	// minimum width (which governs the inner client rect) + 2
	//size.v = layerMinHeight;
	size.v = 258;
#ifdef WIN_ENV	// different rules about whether the borders and tabs are in the dlg rect
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif
	// Get the last known size out of the Prefs file
	sAIPreference->GetPointPreference( "ADMNonModalDialog", "kADM_DPSizeStr", &size );
	rect.left = location.h;
	rect.right = location.h + size.h;
	rect.top = location.v;
	rect.bottom = location.v + size.v;

	// restore the size and location of the dialog
	sADMDialog->SetBoundsRect(dlg, &rect);
	// restore the position code of the dialog
	sADMDialogGroup->SetDialogGroupInfo(dlg, groupName, positionCode );

	// Initialize the palette internals
	//result = LayersDlgInit(dlg);

	ADMIconRef icon = sADMIcon2->GetFromResource(pluginRef, 0, ID_DIALOG_ICON, 0);
	sADMDialog->SetIcon(dlg,false, icon);

	icon = sADMIcon2->GetFromResource(pluginRef, 0, ID_DIALOG_ICON_ROLLOVER, 0);
	sADMDialog->SetIcon(dlg,true, icon);

	// Clean up the application context and return
	sAIAppContext->PopAppContext(AppContext);

	return fxErr;
}

/*******************************************************************************
 **	Notification Procedures
 **/

static void ASAPI DlgDestroyProc(ADMDialogRef dlg) {
	
	ADMRect		boundsRect;
	ADMPoint 	location, size;
	const char		*groupName;
	long		positionCode;
	ASBoolean	Visible;

	// saving the palette position, tab/dock preference.
	sADMDialogGroup->GetDialogGroupInfo( dlg, &groupName, &positionCode );
	sADMDialog->GetBoundsRect( dlg, &boundsRect );
	Visible = sADMDialog->IsVisible(dlg);

	location.h = boundsRect.left;
	location.v = boundsRect.top;
	size.h = boundsRect.right - boundsRect.left;
	size.v = boundsRect.bottom - boundsRect.top; 

	sAIPreference->PutIntegerPreference( "ADMNonModalDialog", "kADM_DPDockCodeStr", positionCode );
	sAIPreference->PutStringPreference( "ADMNonModalDialog", "kADM_DPDockGroupStr", groupName );
	sAIPreference->PutPointPreference( "ADMNonModalDialog", "kADM_DPLocationStr", &location );
	sAIPreference->PutPointPreference( "ADMNonModalDialog", "kADM_DPSizeStr", &size );
	sAIPreference->PutBooleanPreference( "ADMNonModalDialog", "kADM_DPVisibleStr", Visible );
	
	g->nonModalDialog = NULL;
	sSPAccess->ReleasePlugin( g->accessRef );
	
	// release suites from memory
	releaseSuites( g->basic );
	
}


/* dialogPopupMenuTrackProc(), this is called at mouse down on the "triangle" popup
   menu. This is your opportunity to change the status of menu items
   In this example, the modifier keys enable menu items 1 and 2                       */   
static ASBoolean ASAPI dialogPopupMenuTrackProc(ADMItemRef item, ADMTrackerRef tracker)
{
	ADMAction		action;
	ASBoolean		doNotify;

	action = sADMTracker->GetAction(tracker);

	// capture mouse down event
	if (action == kADMButtonDownAction)
	{ 	
		SPPluginRef			pluginRef;
		ADMListRef			menuListRef;
		AIBoolean			commandOptionDown, commandControlDown;
		
		// checks if the (mac)OPTION (win)ALT modifier is pressed
		commandOptionDown = sADMTracker->TestModifier(tracker, kADMModKeyDownModifier);
		// checks if the (mac)COMMAND (win)CONTROL modifier is pressed
		commandControlDown = sADMTracker->TestModifier(tracker, kADMMenuKeyDownModifier);

		pluginRef = sADMItem->GetPluginRef(item);
		menuListRef = sADMItem->GetList(item);		

		if (menuListRef)
		{
			// if command is pressed, enable the first menu item, otherwise disable
			sADMEntry->Enable( sADMList->IndexEntry(menuListRef, 0), commandOptionDown );
			// if command is pressed, enable the second menu item, otherwise disable
			sADMEntry->Enable( sADMList->IndexEntry(menuListRef, 1), commandControlDown );
		}
	} 	

	doNotify = sADMItem->DefaultTrack(item, tracker);

	return doNotify;
}

static void ASAPI dialogPopupMenuProc( ADMItemRef item, ADMNotifierRef notifier) {

	int selection;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
		selection = GetPopupSelection( item );
}

static void ASAPI PopupProc( ADMItemRef item, ADMNotifierRef notifier) {

	int selection;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
		selection = GetPopupSelection( item );
}

static void ASAPI spinEditPopupProc( ADMItemRef item, ADMNotifierRef notifier) {

	int selection;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
		selection = GetPopupSelection( item );

}

static void ASAPI beepButtonUp( ADMItemRef item, ADMNotifierRef notifier) {

	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
		sADMBasic->Beep();

}


static void ASAPI beepBeepButtonUp( ADMItemRef item, ADMNotifierRef notifier) {
	
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
		sADMBasic->Beep(); sADMBasic->Beep();
}

static void ASAPI radioButtonProc( ADMItemRef item, ADMNotifierRef notifier) {

	int selection = 0;
	ADMDialogRef dlg;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) ) {
		dlg = sADMItem->GetDialog(item);
		if (item == sADMDialog->GetItem(dlg, kradioButton1Item)) {
			selection = 1;
			sADMBasic->Beep();
		}
		else if (item == sADMDialog->GetItem(dlg, kradioButton2Item)) {
			selection = 2;
			sADMBasic->Beep();
			sADMBasic->Beep();
		}
		else {
			selection = 3;
			sADMBasic->Beep();
			sADMBasic->Beep();
			sADMBasic->Beep();
		}
	}
}

static void ASAPI checkBox1Proc( ADMItemRef item, ADMNotifierRef notifier) {
	
	AIBoolean isBox1Checked;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier) ) {
		isBox1Checked = sADMItem->GetBooleanValue(item);
	}
}

static void ASAPI checkBox2Proc( ADMItemRef item, ADMNotifierRef notifier) {

	AIBoolean isBox2Checked;
	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier) ) {
		isBox2Checked = sADMItem->GetBooleanValue(item);
	}
}

/*******************************************************************************
 ** Utility functions
 **/

static int GetPopupSelection( ADMItemRef item ) {

	ADMListRef listRef;
	ADMEntryRef activeEntry;
	int  selection;

	listRef = sADMItem->GetList(item);	
			
	// get the current active entry
	activeEntry = sADMList->GetActiveEntry( listRef );
	// get the index (0 based) of the entry
	selection = sADMEntry->GetIndex( activeEntry );

	return selection;

}

