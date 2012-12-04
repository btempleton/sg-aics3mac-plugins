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
#include "ADMNonModalDialogID.h"
#include "SnippetRunnerParameter.h"
#include <string.h>
#include <ctype.h>

//GLOBAL HANDLES TO THE TEXT BOX AND BUTTON
ADMItemRef ghEditTextItemRef, ghAddButtonItemRef;


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

	g->nonModalDialog = sADMDialog->Create( message->d.self,"Add Color", kADMNonModalDialogID,
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
//	ADMItemRef				ghAddButtonItemRef, ghEditTextItemRef;

	//ADMEntryRef				entry;
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
	
	//CREATE THE BUTTON
	ADMRect boxloc = {6, 137, 18, 200}; // top, left, bottom, right
	ghAddButtonItemRef = sADMItem->Create(dlg, kAddButton, kADMTextPushButtonType, &boxloc, NULL, NULL, NULL);
	sADMItem->SetText(ghAddButtonItemRef, "Add Color");
	sADMDialog->SetDefaultItemID(dlg, kAddButton);
	
	//SET THE NOTIFY PROCEDURE FOR ADD COLOR BUTTON
	if (ghAddButtonItemRef)	{ sADMItem->SetNotifyProc(ghAddButtonItemRef, addButtonUp); }
	
	
	//CREATE THE TEXT BOX
	boxloc.top=7; boxloc.left=10; boxloc.bottom=25; boxloc.right=130; // top, left, bottom, right
	ghEditTextItemRef = sADMItem->Create(dlg, kEditText, kADMTextEditType, &boxloc, NULL, NULL, NULL);
	sADMItem->SetItemStyle(ghEditTextItemRef, kADMSingleLineTextEditStyle);
	sADMItem->SetMaxTextLength(ghEditTextItemRef, 30);
	
	//Highlight and select whatevers in the box
	sADMItem->Activate(ghEditTextItemRef, true); 
	sADMItem->SelectAll(ghEditTextItemRef);
	
	//SET THE TRACKER PROCEDURE FOR TEXT BOX, WE NEED TO HANDLE THE ENTER KEYPRESS
	if (ghEditTextItemRef)	{
		sADMItem->SetTrackProc(ghEditTextItemRef, editTextEnter);
		//sADMItem->SetMask(ghEditTextItemRef, kADMEnterMask || kADMKeyStrokeMask);
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
	sAIPreference->GetStringPreference( "Add Color", "kADM_DPDockGroupStr", groupName );
	positionCode = 0x00001c00; // Default: no dock, no tab group, front tab, zoom down, visible
	sAIPreference->GetIntegerPreference( "Add Color", "kADM_DPDockCodeStr", &positionCode );

	// Pick a default location in case it has never come up before on this machine
	sADMDialog->GetBoundsRect( dlg, &boundsRect );
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);

	// Get the last known location out of the Prefs file
	sAIPreference->GetPointPreference( "Add Color", "kADM_DPLocationStr", &location );

	size.h = 208;	// minimum width (which governs the inner client rect) + 2
	//size.v = layerMinHeight;
	size.v = 258;  //was: 258
#ifdef WIN_ENV	// different rules about whether the borders and tabs are in the dlg rect
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif
	// Get the last known size out of the Prefs file
	sAIPreference->GetPointPreference( "Add Color", "kADM_DPSizeStr", &size );
	rect.left = location.h;
	rect.right = location.h + size.h;
	rect.top = location.v;
	rect.bottom = location.v + size.v;

	// restore the size and location of the dialog
	//THIS LINE IS COMMENTED OUT SO SIZE CAN BE SET IN RESOURCE FILE
	// sADMDialog->SetBoundsRect(dlg, &rect);

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

	sAIPreference->PutIntegerPreference( "Add Color", "kADM_DPDockCodeStr", positionCode );
	sAIPreference->PutStringPreference( "Add Color", "kADM_DPDockGroupStr", groupName );
	sAIPreference->PutPointPreference( "Add Color", "kADM_DPLocationStr", &location );
	sAIPreference->PutPointPreference( "Add Color", "kADM_DPSizeStr", &size );
	sAIPreference->PutBooleanPreference( "Add Color", "kADM_DPVisibleStr", Visible );
	
	g->nonModalDialog = NULL;
	sSPAccess->ReleasePlugin( g->accessRef );
	
	// release suites from memory
	releaseSuites( g->basic );
	
}



static void ASAPI addButtonUp( ADMItemRef item, ADMNotifierRef notifier) {

	// dispatch the notifier type
	if ( sADMNotifier->IsNotifierType( notifier, kADMUserChangedNotifier ) )
	{

		AISwatchRef newSwatch = NULL;
		AIColor color;
		ai::UnicodeString swatchName;	//The swatch name in the form "PANTONE ### U"
		bool wasMICR = FALSE;
		AICustomColor customColor;
		
		AIBoolean converted = FALSE;
		sAIDocument->SetDocumentSpotColorMode(NULL, kAILegacySpotColorMode, TRUE, &converted);
			
		//Build the color name string in the form "PANTONE ### U" store it in swatchName
		//We have to check if we're making the MICR color
		swatchName = createNameFromInput(); //Returns "0" if the color wasn't created
		if ( swatchName == ai::UnicodeString("MICR") ) {
			wasMICR = TRUE;
			swatchName = ai::UnicodeString("PANTONE Process Black U");
		}
		
		if ( swatchName.compare( (ai::UnicodeString)"0" ) ) {
		
			//If the name matches one in the book, store the attributes in customColor
			if ( sAISwatchLibrary->FindStandardBookColor(swatchName, &customColor) ) {
			
				//WE'LL JUST ADD THE SWATCH TO THE MAIN GROUP FOR NOW
				newSwatch = sAISwatchList->InsertNthSwatch(NULL, -1);
			
				//IF IT WORKED, WE NEED TO SET ALL THE PARAMETERS FOR OUR NEW COLOR
				if (newSwatch) {
		
					// Make color a custom color
					color.kind = kCustomColor;

					// Use the swatchName for the new color name
					if (wasMICR) {
						swatchName = ai::UnicodeString("MICR - BLACK MAG");
					}
					sAICustomColor->NewCustomColorName(swatchName);
										
					// Create the customColorHandle that will point to the new color
					AICustomColorHandle customColorHandle = NULL;
					
					//Make the custom color using attributes we got from the book, the color name,
					//and store a reference in the handle we just made
					sAICustomColor->NewCustomColor(&customColor, swatchName, &customColorHandle);
					
					//Store the custom color in "color"
					color.c.c.color = customColorHandle;
					color.c.c.tint = 0;
					
					//This is where we actually apply the color to the swatch we made
					sAISwatchList->SetAIColor(newSwatch, &color);

				}	
			} 
			else {
					sADMBasic->MessageAlert("That color doesn't seem to be in the book."); 
			}
		}
		else {
				sADMBasic->MessageAlert("Invalid Entry. Either try again, or create the color \nusing the color list.");
		}
	}
	//Highlight and select whatevers in the box
	sADMItem->Activate(ghEditTextItemRef, true);
	sADMItem->SelectAll(ghEditTextItemRef);
}



static ASBoolean ASAPI editTextEnter( ADMItemRef item, ADMTrackerRef tracker) {
	
	ADMAction action;
	ASBoolean doNotify;
	
	action = sADMTracker->GetAction(tracker);
	
	// dispatch the tracker type
	if ( action == kADMKeyStrokeAction)
	{
		if( (sADMTracker->GetVirtualKey(tracker) == kADMEnterKey) || (sADMTracker->GetVirtualKey(tracker) == kADMReturnKey)) {
			
			if(sADMItem->IsActive(ghEditTextItemRef) ) { sADMItem->Activate(ghAddButtonItemRef, true);	}
			
			sADMItem->SendNotify(ghAddButtonItemRef, kADMUserChangedNotifier);
			
			sADMTracker->Abort(tracker);
		} else {
			doNotify = sADMItem->DefaultTrack(item, tracker);
		}
	} 
	return doNotify;
}


ai::UnicodeString createNameFromInput() {

			char enterNum[30] = "";			//This will hold what the user enters in the box
			//char fullColorName[256] = "";	//This will hold the full color name in the form "PANTONE #### U"
			
			//Get the number from the text box and store in enterNum
			sADMItem->GetText(ghEditTextItemRef, enterNum, 30);
			
			bool isAllNumbers = TRUE;
			
			//Make it all lowercase
			for (int i=0; i<30; i++) {
				if ( enterNum[i] == '\0' ) { break; }
				if ( isalpha(enterNum[i]) ) { enterNum[i] = tolower(enterNum[i]);	}
			}
			
			//Strip out any spaces
			stripSpaces(enterNum);
					
		
			//Check each character in the string to see if its all numbers
			for (int i=0; i<30; i++) {
				if ( enterNum[i] == '\0' ) { break; }
				if ( isAllNumbers) {
					if ( !isdigit(enterNum[i]) ) {	isAllNumbers = FALSE;	}
				}
			}
			
			if ( isAllNumbers ) { //If its all numbers, then we have to check for a few special colors
			
				if ( strcmp(enterNum, "12") == 0 || strcmp(enterNum, "012") == 0 ) { return makeColorName("Yellow 012"); }
				if ( strcmp(enterNum, "21") == 0 || strcmp(enterNum, "021") == 0 ) { return makeColorName("Orange 021"); }
				if ( strcmp(enterNum, "32") == 0 || strcmp(enterNum, "032") == 0 ) { return makeColorName("Red 032"); }
				if ( strcmp(enterNum, "72") == 0 || strcmp(enterNum, "072") == 0 ) { return makeColorName("Blue 072"); }
				
				//If the number is between 100 and 8321 we can probably use it how it is and just make sure its a valid color
				if ( atoi(enterNum) >= 100 && atoi(enterNum) <= 8312) { 
					return makeColorName(enterNum);
				}


			} else {              //If theres characters there, we have to determine which color it is
				if ( strcmp(enterNum, "black") == 0 || strcmp(enterNum, "k") == 0 || strcmp(enterNum, "blk") == 0 ) { return makeColorName("Black"); }
				if ( strcmp(enterNum, "cg1") == 0 || strcmp(enterNum, "coolgray1") == 0 ) { return makeColorName("Cool Gray 1"); }
				if ( strcmp(enterNum, "cg2") == 0 || strcmp(enterNum, "coolgray2") == 0 ) { return makeColorName("Cool Gray 2"); }
				if ( strcmp(enterNum, "cg3") == 0 || strcmp(enterNum, "coolgray3") == 0 ) { return makeColorName("Cool Gray 3"); }
				if ( strcmp(enterNum, "cg4") == 0 || strcmp(enterNum, "coolgray4") == 0 ) { return makeColorName("Cool Gray 4"); }
				if ( strcmp(enterNum, "cg5") == 0 || strcmp(enterNum, "coolgray5") == 0 ) { return makeColorName("Cool Gray 5"); }
				if ( strcmp(enterNum, "cg6") == 0 || strcmp(enterNum, "coolgray6") == 0 ) { return makeColorName("Cool Gray 6"); }
				if ( strcmp(enterNum, "cg7") == 0 || strcmp(enterNum, "coolgray7") == 0 ) { return makeColorName("Cool Gray 7"); }
				if ( strcmp(enterNum, "cg8") == 0 || strcmp(enterNum, "coolgray8") == 0 ) { return makeColorName("Cool Gray 8"); }
				if ( strcmp(enterNum, "cg9") == 0 || strcmp(enterNum, "coolgray9") == 0 ) { return makeColorName("Cool Gray 9"); }
				if ( strcmp(enterNum, "cg10") == 0 || strcmp(enterNum, "coolgray10") == 0 ) { return makeColorName("Cool Gray 10"); }
				if ( strcmp(enterNum, "cg11") == 0 || strcmp(enterNum, "coolgray11") == 0 ) { return makeColorName("Cool Gray 11"); }
				if ( strcmp(enterNum, "green") == 0 || strcmp(enterNum, "grn") == 0 ) { return makeColorName("Green"); }
				if ( strcmp(enterNum, "orange") == 0 || strcmp(enterNum, "org") == 0 ) { return makeColorName("Orange 021"); }
				if ( strcmp(enterNum, "processblack") == 0 || strcmp(enterNum, "pbk") == 0 || strcmp(enterNum, "procblack") == 0) { return makeColorName("Process Black"); }
				if ( strcmp(enterNum, "processblue") == 0 || strcmp(enterNum, "pbl") == 0 || strcmp(enterNum, "procblue") == 0 ) { return makeColorName("Process Blue"); }
				if ( strcmp(enterNum, "processcyan") == 0 || strcmp(enterNum, "pc") == 0 || strcmp(enterNum, "proccyan") == 0 ) { return makeColorName("Process Cyan"); }
				if ( strcmp(enterNum, "processmagenta") == 0 || strcmp(enterNum, "pm") == 0 || strcmp(enterNum, "procmag") == 0) { return makeColorName("Process Magenta"); }
				if ( strcmp(enterNum, "processyellow") == 0 || strcmp(enterNum, "py") == 0 || strcmp(enterNum, "procyel") == 0 ) { return makeColorName("Process Yellow"); }
				if ( strcmp(enterNum, "purple") == 0 || strcmp(enterNum, "pur") == 0 ) { return makeColorName("Purple"); }
				if ( strcmp(enterNum, "reflexblue") == 0 || strcmp(enterNum, "rbl") == 0 || strcmp(enterNum, "refblue") == 0 || strcmp(enterNum, "reflex") == 0 || strcmp(enterNum, "ref") == 0 ) { return makeColorName("Reflex Blue"); }
				if ( strcmp(enterNum, "rhodamine") == 0 || strcmp(enterNum, "rho") == 0 ) { return makeColorName("Rhodamine Red"); }
				if ( strcmp(enterNum, "rubine") == 0 || strcmp(enterNum, "rub") == 0 ) { return makeColorName("Rubine Red"); }
				if ( strcmp(enterNum, "violet") == 0 || strcmp(enterNum, "vlt") == 0 ) { return makeColorName("Violet"); }
				if ( strcmp(enterNum, "wg1") == 0 || strcmp(enterNum, "warmgray1") == 0 ) { return makeColorName("Warm Gray 1"); }
				if ( strcmp(enterNum, "wg2") == 0 || strcmp(enterNum, "warmgray2") == 0 ) { return makeColorName("Warm Gray 2"); }
				if ( strcmp(enterNum, "wg3") == 0 || strcmp(enterNum, "warmgray3") == 0 ) { return makeColorName("Warm Gray 3"); }
				if ( strcmp(enterNum, "wg4") == 0 || strcmp(enterNum, "warmgray4") == 0 ) { return makeColorName("Warm Gray 4"); }
				if ( strcmp(enterNum, "wg5") == 0 || strcmp(enterNum, "warmgray5") == 0 ) { return makeColorName("Warm Gray 5"); }
				if ( strcmp(enterNum, "wg6") == 0 || strcmp(enterNum, "warmgray6") == 0 ) { return makeColorName("Warm Gray 6"); }
				if ( strcmp(enterNum, "wg7") == 0 || strcmp(enterNum, "warmgray7") == 0 ) { return makeColorName("Warm Gray 7"); }
				if ( strcmp(enterNum, "wg8") == 0 || strcmp(enterNum, "warmgray8") == 0 ) { return makeColorName("Warm Gray 8"); }
				if ( strcmp(enterNum, "wg9") == 0 || strcmp(enterNum, "warmgray9") == 0 ) { return makeColorName("Warm Gray 9"); }
				if ( strcmp(enterNum, "wg10") == 0 || strcmp(enterNum, "warmgray10") == 0 ) { return makeColorName("Warm Gray 10"); }
				if ( strcmp(enterNum, "wg11") == 0 || strcmp(enterNum, "warmgray11") == 0 ) { return makeColorName("Warm Gray 11"); }
				if ( strcmp(enterNum, "warmred") == 0 || strcmp(enterNum, "wred") == 0 ) { return makeColorName("Warm Red"); }
				if ( strcmp(enterNum, "yellow") == 0 || strcmp(enterNum, "yel") == 0 ) { return makeColorName("Yellow"); }
				
				if ( strcmp(enterNum, "thermo") == 0 ) { return makeColorName("1767"); }
				if ( strcmp(enterNum, "backer") == 0 ) { return makeColorName("431"); }
				
				//If they're asking for MICR ink we need to create Process Black and rename it
				if ( strcmp(enterNum, "magblack") == 0 || strcmp(enterNum, "micr") == 0 ) { return makeColorName("MICR"); }


				
			}
	return (ai::UnicodeString) "0";
}

ai::UnicodeString makeColorName ( char* middle ) {
	//We have to check if we're making the MICR color
	if ( ai::UnicodeString(middle) == ai::UnicodeString("MICR") ) {
		return ai::UnicodeString("MICR");
	} else {
		char str[80];
		strcpy (str,"PANTONE ");
		strcat (str, middle);
		strcat (str," U");
		return (ai::UnicodeString) str;		
	}
}


void stripSpaces(char *Str)
{
	int Pntr = 0;
	int Dest = 0;
 
	while (Str [Pntr])
	{
		if (Str [Pntr] != ' ')
			Str [Dest++] = Str [Pntr];
		Pntr++;
	}
 
	Str [Dest] = '\0';
}