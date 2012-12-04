#include "IllustratorSDK.h"

#include "Common.h"
#include "FindReplaceGraphics.h"
#include "ADMResource.h"
#include "ADMNonModalDialogID.h"
#include "string.h"
#include "stdlib.h"

#include "ColorFuncs.h"
#include "populateDialog.h"

//GLOBAL HANDLES TO DIALOG ITEMS
ADMItemRef ghAttributeLabel, ghChangeInLabel, ghFromLabel, ghToLabel, ghApplyToLabel, ghNumberChangedLabel,
	ghAttributeList, ghChangeInList, ghFromList, ghFromColorBox, ghToList, ghToColorBox, ghApplyToList, ghIncludeTintsCheckBox, ghChangeButton, ghRemoveUnused,
	ghColorSelectLabel, ghAddRemoveList;
	


// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif


// Tell Xcode to return to default visibility for symbols
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

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

	g->nonModalDialog = sADMDialog->Create( message->d.self,"Find & Replace Graphics", kADMNonModalDialogID,
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
	
	populateDialog(dlg, 0);
	
	//SET THE NOTIFY PROCEDURE FOR Change BUTTON
	if (ghChangeButton)	{ sADMItem->SetNotifyProc(ghChangeButton, changeButtonUp); }
	
	//SET THE NOTIFY PROCEDURE FOR RemoveColors BUTTON
	if (ghChangeButton)	{ sADMItem->SetNotifyProc(ghRemoveUnused, removeUnusedButtonUp); }
	
	//SET THE NOTIFY and TRACK PROCEDURE FOR From List
	if (ghFromList)	{
		sADMItem->SetTrackProc(ghFromList, fromListClicked);
		sADMItem->SetNotifyProc(ghFromList, listChanged);
	}
	
	//SET THE NOTIFY and TRACK PROCEDURE FOR To List
	if (ghToList)	{
		sADMItem->SetTrackProc(ghToList, toListClicked);
		sADMItem->SetNotifyProc(ghToList, listChanged);
	}
	
	//SET THE NOTIFY PROCEDURE FOR Attribute List
	if (ghAttributeList)	{
		sADMItem->SetNotifyProc(ghAttributeList, attributeListChanged);
	}
	
	//SET THE NOTIFY PROCEDURE FOR Add/Remove List
	if (ghAttributeList)	{
		sADMItem->SetNotifyProc(ghAddRemoveList, addRemoveListChanged);
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
	sAIPreference->GetStringPreference( "FindReplaceGraphics", "kADM_DPDockGroupStr", groupName );
	positionCode = 0x00001c00; // Default: no dock, no tab group, front tab, zoom down, visible
	sAIPreference->GetIntegerPreference( "FindReplaceGraphics", "kADM_DPDockCodeStr", &positionCode );

	// Pick a default location in case it has never come up before on this machine
	sADMDialog->GetBoundsRect( dlg, &boundsRect );
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);

	// Get the last known location out of the Prefs file
	sAIPreference->GetPointPreference( "FindReplaceGraphics", "kADM_DPLocationStr", &location );

	size.h = 208;	// minimum width (which governs the inner client rect) + 2
	//size.v = layerMinHeight;
	size.v = 258;  //was: 258
#ifdef WIN_ENV	// different rules about whether the borders and tabs are in the dlg rect
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif
	// Get the last known size out of the Prefs file
	sAIPreference->GetPointPreference( "FindReplaceGraphics", "kADM_DPSizeStr", &size );
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

	sAIPreference->PutIntegerPreference( "FindReplaceGraphics", "kADM_DPDockCodeStr", positionCode );
	sAIPreference->PutStringPreference( "FindReplaceGraphics", "kADM_DPDockGroupStr", groupName );
	sAIPreference->PutPointPreference( "FindReplaceGraphics", "kADM_DPLocationStr", &location );
	sAIPreference->PutPointPreference( "FindReplaceGraphics", "kADM_DPSizeStr", &size );
	sAIPreference->PutBooleanPreference( "FindReplaceGraphics", "kADM_DPVisibleStr", Visible );
	
	g->nonModalDialog = NULL;
	sSPAccess->ReleasePlugin( g->accessRef );
	
	// release suites from memory
	releaseSuites( g->basic );
	
}


static void ASAPI changeButtonUp( ADMItemRef item, ADMNotifierRef notifier) {

	
	int ApplyTo; //0 = Strokes , 1 = Fills , 2 = Strokes and Fills
	ApplyTo = sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghApplyToList)));
	
	AIBoolean flag = FALSE;
	int numChanged = 0;
	
	//CREATE THE ART SET
	AIArtSet artSet;
	sAIArtSet->NewArtSet(&artSet);
	
	//SET UP AND INITIALIZE WHAT SCOPE WE'RE DEALING WITH
	int ChangeIn;	
	ChangeIn = sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghChangeInList)));
	
	//FILL THE ART SET BASED ON THE "CHANGE IN" LIST
	fillArtSet( artSet , ChangeIn );
	
	//Set the VisitFlags based on the apply to and whatnot
	VisitAIColorFlags controlFlags = kVisitColorsNullFlags; //change universally to direct only
	if ( ApplyTo == 0 ) {	controlFlags = kVisitColorsUniversally | /*kVisitColorsSolidOnly |*/ kVisitColorsStrokesOnly | kVisitGlobalObjectsOnceOnly;  }
	if ( ApplyTo == 1 ) {	controlFlags = kVisitColorsUniversally | /*kVisitColorsSolidOnly |*/ kVisitColorsFillsOnly | kVisitGlobalObjectsOnceOnly;  }
	if ( ApplyTo == 2 ) {	controlFlags = kVisitColorsUniversally | /*kVisitColorsSolidOnly |*/ kVisitGlobalObjectsOnceOnly;  }
	
	//LOOP THROUGH THE SET AND CHECK THE STROKES AND FILLS FOR THE COLOR WE're CHANGING from

	
	long count;		sAIArtSet->CountArtSet( artSet, &count );
	
	for ( int i=0 ; i < count ; i++ ) {
		AIArtHandle currArtObj;
		sAIArtSet->IndexArtSet( artSet, i, &currArtObj );
		
		/*// TEMP STUFF TO CHECK THE SELECTED OBJECTS COLOR
		AIPathStyle tempstyle; AICustomColor tempcolor;
		sAIPathStyle->GetPathStyle( currArtObj, &tempstyle);
		tempstyle.fill.color.kind;
		tempstyle.fill.color.c.c.tint;
		sAICustomColor->GetCustomColor(tempstyle.fill.color.c.c.color, &tempcolor);
		tempcolor.kind;
		tempcolor.c;*/ 
		

/*********** FIND AND REPLACE COLORS *************/
		if ( sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghAttributeList))) == 0) {
			
			//CREATE THE HANDLES and color specs FOR THE TO AND FROM COLORS
			COLORS FromToColors;
			char name[30];
			//initialize the colors
			sADMEntry->GetText( sADMList->GetActiveEntry(sADMItem->GetList(ghFromList)), name, 30 );
			setColorByName( name , FromToColors.FromColor );
			sADMEntry->GetText( sADMList->GetActiveEntry(sADMItem->GetList(ghToList)), name, 30 );
			setColorByName( name , FromToColors.ToColor );
			
			//do the color replacing
			sAIPathStyle->AdjustObjectAIColors( currArtObj , adjustColor , &FromToColors , controlFlags , &flag );
			
			//increment counter if a switch was made
			if (flag) { numChanged++; }
			flag = FALSE;
		}


/*********** FIND AND REPLACE OVERPRINTING *************/
		if ( sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghAttributeList))) == 1) {		
		
			//Get the AIColor from the color in the drop down
			char name[30];
			//initialize the colors
			AIColor fcolor;
			sADMEntry->GetText( sADMList->GetActiveEntry(sADMItem->GetList(ghFromList)), name, 30 );
			setColorByName( name , fcolor );
			
			//Get whether we're including tints or not
			AIBoolean ignoreTints = ( sADMItem->GetBooleanValue(ghIncludeTintsCheckBox) && sADMItem->IsEnabled(ghIncludeTintsCheckBox) );
			
			//Get whether we're turning overprint off or on
			AIBoolean overprint = sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghAddRemoveList)));
			
			//Get whether we're doing strokes or fills
			int replaceIn = sADMEntry->GetIndex(sADMList->GetActiveEntry(sADMItem->GetList(ghApplyToList)));
			
			AdjustOverprint(currArtObj, fcolor, ignoreTints, overprint, replaceIn, &flag);
			
			if (flag) { numChanged++; }
			flag = FALSE;
		}
	}
	
	//Show the counter
	char buffer[100];
	sprintf(buffer,"Changed %d items",numChanged);
	sADMItem->SetText(ghNumberChangedLabel, buffer);
	
	//DISPOSE OF THE ART SET
	sAIArtSet->DisposeArtSet(&artSet);
}


static void ASAPI removeUnusedButtonUp( ADMItemRef item, ADMNotifierRef notifier) {
	removeUnusedColors();
	changeSwatchList(550);
	changeSwatchList(551);
}


static ASBoolean ASAPI fromListClicked(  ADMItemRef item, ADMTrackerRef tracker) {
	ADMAction action;
	
	action = sADMTracker->GetAction(tracker);
	
	// dispatch the tracker type
	if ( action == kADMButtonDownAction)
	{
		changeSwatchList(550);
	}
	return sADMItem->DefaultTrack(item, tracker);
}


static ASBoolean ASAPI toListClicked(  ADMItemRef item, ADMTrackerRef tracker) {
	ADMAction action;
	
	action = sADMTracker->GetAction(tracker);
	
	// dispatch the tracker type
	if ( action == kADMButtonDownAction)
	{
		changeSwatchList(551);
	}
	return sADMItem->DefaultTrack(item, tracker);
}

static void ASAPI listChanged( ADMItemRef item, ADMNotifierRef notifier) {
	if ( sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier) ) {
		ADMListRef fListRef = sADMItem->GetList(ghFromList),
				   tListRef = sADMItem->GetList(ghToList);
		char fname[30], tname[30];
		
		ADMEntryRef fselectedEntry = sADMList->GetActiveEntry( fListRef ),
					tselectedEntry = sADMList->GetActiveEntry( tListRef );
					
		sADMEntry->GetText(fselectedEntry, fname, 30);
		sADMEntry->GetText(tselectedEntry, tname, 30);
		
		if ( strchr(fname, '%') || strchr(tname, '%') ) {
			sADMItem->Enable(ghIncludeTintsCheckBox, FALSE);
		} else {
			sADMItem->Enable(ghIncludeTintsCheckBox, TRUE);
		}
	}
}


static void ASAPI attributeListChanged( ADMItemRef item, ADMNotifierRef notifier) {
	if ( sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier) ) {
		ADMListRef listRef = sADMItem->GetList(ghAttributeList);
				
		ADMEntryRef selectedEntry = sADMList->GetActiveEntry( listRef );
		
		ADMInt32 entryIndex = sADMEntry->GetIndex(selectedEntry);
		
		
		ADMDialogRef dlg = sADMItem->GetDialog(item);
		populateDialog(dlg, entryIndex);
		
		//This is a neat little expression which turns the Include Tints checkbox on and off depending on whether Overprint is selected
		// and whether Add or Remove is selected
		// We take the Active Entry in Add/Remove ( 0 == Remove , 1 == Add )
		// We take the Active Entry in Attribute  ( 0 == Color  , 1 == Overprint)
		// Now we bitwise AND them then NOT the result, so we only turn the check box OFF if we are ADD OVERPRINT otherwise we turn it on
		sADMItem->SetBooleanValue(ghIncludeTintsCheckBox, !(bool(entryIndex) & bool(sADMEntry->GetIndex(sADMList->GetActiveEntry( sADMItem->GetList(ghAddRemoveList) )))) );
	}
}

static void ASAPI addRemoveListChanged( ADMItemRef item, ADMNotifierRef notifier) {
	if ( sADMNotifier->IsNotifierType(notifier, kADMUserChangedNotifier) ) {
		ADMListRef listRef = sADMItem->GetList(ghAddRemoveList);
		
		ADMEntryRef selectedEntry = sADMList->GetActiveEntry( listRef );
		
		ADMInt32 entryIndex = sADMEntry->GetIndex(selectedEntry);
		
		if(entryIndex == 1) {
			sADMItem->SetBooleanValue(ghIncludeTintsCheckBox, FALSE);
		} else {
			sADMItem->SetBooleanValue(ghIncludeTintsCheckBox, TRUE);
		}
	}
}


void changeSwatchList( int list ) {
	
	AISwatchListRef swatchList = NULL;
	ADMListRef ListRef;
		if (list == 550 ) { ListRef = sADMItem->GetList(ghFromList); }
		if (list == 551 ) { ListRef = sADMItem->GetList(ghToList); }
	int numSwatches;
	int numEntries;
	AISwatchRef currSwatch;
	AIColor currColor;
	ADMEntryRef entry, selectedEntry;
	ai::UnicodeString currSwatchName;
	char * cstrSwatchName;
	std::string stdSwatchName;
	
	long numDocs;	sAIDocumentList->Count(&numDocs);
	
	//If there is at least one document open, get the swatch list for the active one
	if ( numDocs ) {
		sAISwatchList->GetSwatchList(NULL, &swatchList);
	}
	
	//Loop throught the swatch list and add each color to the From List
	if ( swatchList ) {
	
		numSwatches = sAISwatchList->CountSwatches(swatchList);
			
		numEntries = sADMList->NumberOfEntries( ListRef );
	
		//Store the name of the currently selected entry
		char name[30];
		selectedEntry = sADMList->GetActiveEntry( ListRef );
		sADMEntry->GetText(selectedEntry, name, 30);

	
		//Clear the list
		for ( int i=0; i < numEntries ; i++) {
			sADMList->RemoveEntry( ListRef, 0);
		}
	
		for ( int i=0; i < numSwatches ; i++) {
			currSwatch = sAISwatchList->GetNthSwatch(swatchList, i);
			
			sAISwatchList->GetSwatchName(currSwatch, currSwatchName);
			
			sAISwatchList->GetAIColor(currSwatch, &currColor);
			
			stdSwatchName = currSwatchName.as_UTF8();
			if ( currColor.c.c.tint > 0 && stdSwatchName != "[None]") {
				int percent = 100-((currColor.c.c.tint*100 -.5));
				char buffer[10];
				sprintf(buffer,"%d%% ",percent);
				stdSwatchName.insert(0, buffer);
			}
			cstrSwatchName = new char [stdSwatchName.size()+1];
			strcpy (cstrSwatchName, stdSwatchName.c_str());

			if( currColor.kind != kPattern && currColor.kind != kGradient ) {
				entry = sADMList->InsertEntry( ListRef, i );
				sADMEntry->SetText(entry, cstrSwatchName);
			}
		}
		
		//SELECT A COLOR FROM THE LIST BY DEFAULT
		if( sADMList->FindEntry( ListRef , name ) ){
			//SELECT THE PREVIOUS SELECTED ONE IF ITS STILL THERE
			sADMEntry->Select(sADMList->FindEntry(ListRef, name) , true);	
		} else {
			//OTHERWISE SELECT BLACK by default
			sADMEntry->Select(sADMList->FindEntry(ListRef, "Black") , true);		
		}

	} else if ( numDocs ) {
		sADMBasic->MessageAlert("No Swatch List for the active document was found.");
	}
}




void fillArtSet( AIArtSet &artSet, int ChangeIn) {

	AIArtSpec selectedSpecs[] = { { kPathArt , kArtFullySelected , kArtFullySelected },
								  { kCompoundPathArt , kArtFullySelected , kArtFullySelected },
								  { kPlacedArt , kArtFullySelected , kArtFullySelected },
								  { kRasterArt , kArtFullySelected , kArtFullySelected },
								  { kPluginArt , kArtFullySelected , kArtFullySelected },
								  { kMeshArt , kArtFullySelected , kArtFullySelected },
								  { kTextFrameArt , kArtFullySelected , kArtFullySelected },
								  { kSymbolArt , kArtFullySelected , kArtFullySelected },
								};
	AIArtSpec allSpecs[] = { { kPathArt , 0 , 0 },
								  { kCompoundPathArt , 0 , 0 },
								  { kPlacedArt , 0 , 0 },
								  { kRasterArt , 0 , 0 },
								  { kPluginArt , 0 , 0 },
								  { kMeshArt , 0 , 0 },
								  { kTextFrameArt , 0 , 0 },
								  { kSymbolArt , 0 , 0 },
								};
	//SELECTION
	if (ChangeIn == 0) { sAIArtSet->MatchingArtSet( selectedSpecs , 8, artSet ); }
	//PAGE or DOCUMENT for now
	if (ChangeIn == 1 || ChangeIn == 2) { sAIArtSet->MatchingArtSet( allSpecs , 8, artSet ); }
}



bool setColorByName( string name , AIColor &color) {
	if (name.compare("[Registration]") == 0) {
		color.kind = kCustomColor;
		color.c.c.tint = 0;
		sAICustomColor->NewRegistrationColor(&color.c.c.color, 1, 1, 1, 1, kCustomFourColor);
		return TRUE;
	}
	
	string colorName;
	float tint = 0;
	size_t found = 0;
	string buffer;
	
	AISwatchRef swatchRef;
	int numSwatches = 0;
	AIColor tempColor;
	ai::UnicodeString tempName;

	found = name.find("%");
	
	if (found != string::npos) {	
		buffer = name.substr(0, found);
		tint = .01 * (100 - atoi(buffer.c_str()));
	}
	
	if(found == string::npos) { colorName = name.substr(found+1); }
	else { colorName = name.substr(found+2); }
	
	
	numSwatches = sAISwatchList->CountSwatches( NULL );
	for ( int i=0; i<numSwatches; i++) {
		swatchRef = sAISwatchList->GetNthSwatch( NULL , i );
		sAISwatchList->GetSwatchName( swatchRef, tempName );
		sAISwatchList->GetAIColor( swatchRef, &tempColor );
		if ( tempName == (ai::UnicodeString)colorName ) {
			if ( sAIRealMath->EqualWithinTol(tempColor.c.c.tint, tint, .01) ) {     
				color = tempColor;
			}
		}
	}
	
	return TRUE;
}


void changeChangeInList() {
	if (ghChangeInList) {
		AIArtHandle** matches;
		long count;
		ADMListRef ApplyToListRef = sADMItem->GetList(ghChangeInList);
		ADMEntryRef ApplyToEntryRef;
		
		sAIDocumentList->Count(&count);
		if (count) {
			
			sAIMatchingArt->GetSelectedArt(&matches, &count);
			
			if (count) {
				ApplyToEntryRef = sADMList->IndexEntry(ApplyToListRef, 0);
				sADMEntry->Select(ApplyToEntryRef, TRUE);
			} else {
				ApplyToEntryRef = sADMList->IndexEntry(ApplyToListRef, 1);
				sADMEntry->Select(ApplyToEntryRef, TRUE);
			}
			
			sAIMdMemory->MdMemoryDisposeHandle((void**)matches);
		}
	}
}