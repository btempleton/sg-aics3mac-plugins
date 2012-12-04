//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/admHandler.cpp $
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
#include "admHandler.h"
#include "plugin.h"

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
extern AIErr createADMDialog( AINotifierMessage *message ) {
	AIErr error = kNoErr;

	g->transformButtonsDialog = sADMDialog->Create( message->d.self,"transformButtonsDialog", kTransformButtonsDlgID,
	 kADMTabbedFloatingDialogStyle, DlgInit, nil, 0);

	if (error)
		goto error;
error:
	return error;
}

// Initialize dialog items and notification procedures for the ADM dialog
extern ASErr ASAPI DlgInit(ADMDialogRef dlg)
{
	ASErr					fxErr = kNoErr;
	AIAppContextHandle		AppContext;
	ADMItemRef				menuItemRef;
	//ADMListRef				layerListRef = 0;
	ADMListRef				menuListRef;
	SPPluginRef				pluginRef;
	char					tipString[64], groupName[64];

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
	
	// Set button pictures
	SetPicts(dlg);
	
	
	
	
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
	sASLib->strcpy( groupName, "SDK Dialogs" ); // default
	sAIPreference->GetStringPreference( "TransformButtonsDialog", "kADM_DPDockGroupStr", groupName );
	positionCode =  0x00001c00; // default
	sAIPreference->GetIntegerPreference( "TransformButtonsDialog", "kADM_DPDockCodeStr", &positionCode );

	// Pick a default location in case it has never come up before on this machine
	sADMDialog->GetBoundsRect( dlg, &boundsRect );
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);

	// Get the last known location out of the Prefs file
	sAIPreference->GetPointPreference( "TransformButtonsDialog", "kADM_DPLocationStr", &location );

	size.h = 208;	// minimum width (which governs the inner client rect) + 2
	//size.v = layerMinHeight;
	size.v = 104;
#ifdef WIN_ENV	// different rules about whether the borders and tabs are in the dlg rect
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif
	// Get the last known size out of the Prefs file
	sAIPreference->GetPointPreference( "TransformButtonsDialog", "kADM_DPSizeStr", &size );
	rect.left = location.h;
	rect.right = location.h + size.h;
	rect.top = location.v;
	rect.bottom = location.v + size.v;

	// restore the size and location of the dialog
	sADMDialog->SetBoundsRect(dlg, &rect);
	// restore the position code of the dialog
	sADMDialogGroup->SetDialogGroupInfo(dlg, groupName, positionCode );
 //
	// Initialize the palette internals
	//result = LayersDlgInit(dlg);

	// show the dialog
	//sADMDialog->Show( dlg, true );

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

	sAIPreference->PutIntegerPreference( "TransformButtonsDialog", "kADM_DPDockCodeStr", positionCode );
	sAIPreference->PutStringPreference( "TransformButtonsDialog", "kADM_DPDockGroupStr", groupName );
	sAIPreference->PutPointPreference( "TransformButtonsDialog", "kADM_DPLocationStr", &location );
	sAIPreference->PutPointPreference( "TransformButtonsDialog", "kADM_DPSizeStr", &size );
	sAIPreference->PutBooleanPreference( "TransformButtonsDialog", "kADM_DPVisibleStr", Visible );
	
	g->transformButtonsDialog = NULL;
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


static void SetPicts(ADMDialogRef dialog)
{
	ADMItemRef editItem;
	int i, bitmap;

	for(i = kRotateCCWID, bitmap = 1001; i <= kScaleDownID; i++, bitmap++)
	{
		editItem = sADMDialog->GetItem(dialog, i);
		sADMItem->SetItemStyle(editItem, kADMBlackRectPictureButtonStyle);
		sADMItem->SetPictureID(editItem, bitmap, NULL);
		sADMItem->SetNotifyProc(editItem, PictProc);
	}
}





static void ASAPI PictProc(ADMItemRef item, ADMNotifierRef notifier)
{
	ASErr result = kNoErr;
//	Globals *pGlobals = (Globals *) PFWGetGlobals();
//	short shMenuItemIndex;
//	AIActionParamValueRef actionParam = NULL;
	ADMDialogRef dlg = sADMItem->GetDialog(item);
	
	long index, count;
	AIArtHandle **store = NULL;	
	AIAppContextHandle		appContext;
	SPPluginRef				pluginRef;
	
	// setup the app. context	
	pluginRef = sADMDialog->GetPluginRef(dlg);
	sAIAppContext->PushAppContext(pluginRef, &appContext);

	// Call the default Notify.
	sADMItem->DefaultNotify(item, notifier);
	
	
	if (sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier)) 
	{
		
		/* We don't need progress dialogs for this plug-in	
		if(id >= kUnitID && id <= kOutlineID)
		{
			char szProgressText[256];
			SPPluginRef spPluginRef;
			
			PFWPluginSelfGet(&spPluginRef);
			sADMBasic->GetIndexString(spPluginRef, kBaseStringResID, id, szProgressText, 256);
			sAI70User->SetProgressText(szProgressText);
		}
		*/
		
		if ( sAIMatchingArt->GetSelectedArt( &store, &count ) ) {
			store = NULL;
			count = 0;
		}
		
		for ( index = 0; ( result == kNoErr ) && ( index < count ); index++ ) {
				AIArtHandle art = (*store)[index];
				
				int id = sADMItem->GetID(item);
				switch(id) {
					case kRotateCCWID:
						result = transformWithParameters( art, 0, 0, (AIReal) (kAIRealPi*0.5), 1, 1 );
					break;

					case kRotateCWID:
						result = transformWithParameters( art, 0, 0, (AIReal) (kAIRealPi*1.5), 1, 1 );
						break;
		
					case kTranslateUpID:
						result = transformWithParameters( art, 0, 72, 0, 1, 1 );
						break;

					case kTranslateDownID:
						result = transformWithParameters( art, 0, -72, 0, 1, 1 );
						break;

					case kTranslateRightID:
						result = transformWithParameters( art, 72, 0, 0, 1, 1 );
						break;

					case kTranslateLeftID:
						result = transformWithParameters( art, -72, 0	, 0, 1, 1 );
						break;

					case kScaleUpID:
						result = transformWithParameters( art, 0, 0, 0, 2.0, 2.0 );
						break;

					case kScaleDownID:
						result = transformWithParameters( art, 0, 0, 0, 0.5, 0.5 );
						break;

					default:
						goto ex;
				}
		}

		/* We'll add ActionManager functionality later
		if (!result && sAIActionManager && sAIActionManager->InRecordMode() &&
			pGlobals->fData.fAlertInfoID == kNoErr)
		{
			result = sAIActionManager->AINewActionParamValue(&actionParam);

			if (actionParam)
			{
				char text[256];
				SPPluginRef spPluginRef;
				PFWPluginSelfGet(&spPluginRef);

				sADMBasic->GetIndexString(spPluginRef, kActionStrings, shMenuItemIndex+1, text, 256);
				sAIActionManager->AIActionSetEnumerated(actionParam, 'name', text, shMenuItemIndex);
				
				sAIActionManager->RecordActionEvent("ai_plugin_pathfinder", kDialogNone, actionParam);
			}
		}
		*/
		
	}

ex:
;
//	if (actionParam)
//		sAIActionManager->AIDeleteActionParamValue(actionParam);

		
	// Clean up the application context and return
	sAIAppContext->PopAppContext(appContext);
}




static AIErr transformWithParameters( AIArtHandle art, AIReal tx, AIReal ty, AIReal theta, AIReal sx, AIReal sy ) { 
	AIErr result = kNoErr;
	AIRealRect artBounds;
	AIRealPoint artCenter;
	AIRealMatrix artMatrix;	
	AIReal lineScale;
	long transformFlags = kTransformObjects | kScaleLines;
	short type;
	
	lineScale = (sAIRealMath->AIRealSqrt(sx)) * (sAIRealMath->AIRealSqrt(sy));
	
	sAIArt->GetArtType( art, &type );
	
	
	switch(type) {
	
		case kGroupArt: return result;
	
		default:
		//result = sAIDocument->GetDocumentMaxArtboardBounds( &artboardBounds );
		result = sAIArt->GetArtBounds( art, &artBounds );
		artCenter.h = artBounds.left + (artBounds.right-artBounds.left) / 2;
		artCenter.v = artBounds.bottom + (artBounds.top-artBounds.bottom) / 2;
		
		// move object so that the centerpoint is at the origin
		sAIRealMath->AIRealMatrixSetTranslate( &artMatrix, -artCenter.h, -artCenter.v );
		// translate object by tx and ty
		sAIRealMath->AIRealMatrixConcatTranslate( &artMatrix, tx, ty );
		// rotate object by theta
		sAIRealMath->AIRealMatrixConcatRotate( &artMatrix, theta );
		// scale object by sx and sy
		sAIRealMath->AIRealMatrixConcatScale( &artMatrix, sx, sy );
		// move the object back to original position
		sAIRealMath->AIRealMatrixConcatTranslate( &artMatrix, artCenter.h, artCenter.v );
		
		result = sAITransformArt->TransformArt( art, &artMatrix, lineScale, transformFlags );
		
	}
	return result;
}



	