/*
 *  populateDialog.cpp
 *  FindReplaceGraphics
 *
 *  Created by Comp Mac 8a on 12/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "populateDialog.h"

void populateDialog(ADMDialogRef dlg, int whichAttr) {
	
	ADMRect boxloc;
	ADMEntryRef entry;
	
	bool showReplaceColor, showOverprint;
	
	if (whichAttr == 0) { showReplaceColor = TRUE; showOverprint = FALSE; }
	if (whichAttr == 1) { showReplaceColor = FALSE; showOverprint = TRUE; }
	
	
	//******************************COMMON DIALOG ITEMS**********************************//
	
	
	//Attribute Label
	if (!ghAttributeLabel) {
		boxloc.top=6; boxloc.left=6; boxloc.bottom=20; boxloc.right=100; // top, left, bottom, right
		ghAttributeLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghAttributeLabel, "Attribute:");
	}
	sADMItem->Show(ghAttributeLabel, TRUE);
	
	
	//CREATE THE ATTRIBUTE LIST
	if (!ghAttributeList) {
		boxloc.top=22; boxloc.left=3; boxloc.bottom=42; boxloc.right=97; // top, left, bottom, right
		ghAttributeList = sADMItem->Create(dlg, kADMUniqueItemID, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		entry = sADMList->InsertEntry( sADMItem->GetList(ghAttributeList), 0 );
		sADMEntry->SetText(entry, "Color");
		entry = sADMList->InsertEntry( sADMItem->GetList(ghAttributeList), 1 );
		sADMEntry->SetText(entry, "Overprint");
		//SELECT THE ITEM PASSED IN
		sADMEntry->Select(sADMList->GetEntry(sADMItem->GetList(ghAttributeList), whichAttr) , true);
	}
	sADMItem->Show(ghAttributeList, TRUE);
	
	
	//Change In Label
	if (!ghChangeInLabel) {
		boxloc.top=6; boxloc.left=106; boxloc.bottom=20; boxloc.right=200; // top, left, bottom, right
		ghChangeInLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghChangeInLabel, "Change in:");
	}
	sADMItem->Show(ghChangeInLabel, TRUE);
	
	
	//CREATE THE CHANGE IN LIST
	if (!ghChangeInList) {
		boxloc.top=22; boxloc.left=103; boxloc.bottom=42; boxloc.right=197; // top, left, bottom, right
		ghChangeInList = sADMItem->Create(dlg, kADMUniqueItemID, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		entry = sADMList->InsertEntry( sADMItem->GetList(ghChangeInList), 0 );
		sADMEntry->SetText(entry, "Selection");
		entry = sADMList->InsertEntry( sADMItem->GetList(ghChangeInList), 1 );
		sADMEntry->SetText(entry, "Page");
		//entry = sADMList->InsertEntry( sADMItem->GetList(ghChangeInList), 2 );
		//sADMEntry->SetText(entry, "Document");
		//SELECT THE FIRST ITEM BY DEFAULT
		sADMEntry->Select(sADMList->GetEntry(sADMItem->GetList(ghChangeInList), 0) , true);
	}
	sADMItem->Show(ghChangeInList, TRUE);
	
	
	//CREATE THE FROM LIST
	if (!ghFromList) {
		boxloc.top=58; boxloc.left=3; boxloc.bottom=78; boxloc.right=97; // top, left, bottom, right
		ghFromList = sADMItem->Create(dlg, 550, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		//We'll initialize the list once its clicked on and add all the colors from the swatches
	}
	sADMItem->Show(ghFromList, TRUE);
	
	
	//Apply To Label
	if (!ghApplyToLabel) {
		boxloc.top=82; boxloc.left=6; boxloc.bottom=96; boxloc.right=100; // top, left, bottom, right
		ghApplyToLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghApplyToLabel, "Apply To:");
	}
	sADMItem->Show(ghApplyToLabel, TRUE);
	
	
	//CREATE THE APPLY TO LIST
	if (!ghApplyToList) {
		boxloc.top=96; boxloc.left=3; boxloc.bottom=116; boxloc.right=100; // top, left, bottom, right
		ghApplyToList = sADMItem->Create(dlg, kADMUniqueItemID, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		entry = sADMList->InsertEntry( sADMItem->GetList(ghApplyToList), 0 );
		sADMEntry->SetText(entry, "Strokes");
		entry = sADMList->InsertEntry( sADMItem->GetList(ghApplyToList), 1 );
		sADMEntry->SetText(entry, "Fills");
		entry = sADMList->InsertEntry( sADMItem->GetList(ghApplyToList), 2 );
		sADMEntry->SetText(entry, "Strokes and Fills");
		//SELECT THE STROKES AND FILLS ITEM BY DEFAULT
		sADMEntry->Select(entry, true);
	} 
	sADMItem->Show(ghApplyToList, TRUE);
	
	
	//CREATE THE INCLUDE TINTS CHECKBOX
	if (!ghIncludeTintsCheckBox) {
		boxloc.top=122; boxloc.left=3; boxloc.bottom=132; boxloc.right=85; // top, left, bottom, right
		ghIncludeTintsCheckBox = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextCheckBoxType, &boxloc, NULL, NULL, NULL);
		sADMItem->SetBooleanValue(ghIncludeTintsCheckBox, TRUE);
		sADMItem->SetText(ghIncludeTintsCheckBox, "Include Tints");
	}
	//INITIALIZE THE CHECKBOX
	sADMItem->Show(ghIncludeTintsCheckBox, TRUE);

	
	
	//Number Changed Label
	if (!ghNumberChangedLabel) {
		boxloc.top=142; boxloc.left=6; boxloc.bottom=156; boxloc.right=100; // top, left, bottom, right
		ghNumberChangedLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghNumberChangedLabel, "Changed 0 items");
	}
	sADMItem->Show(ghNumberChangedLabel, TRUE);
	
	
	//CREATE THE CHANGE BUTTON
	if (!ghChangeButton) {
		boxloc.top=138; boxloc.left=115; boxloc.bottom=156; boxloc.right=207; // top, left, bottom, right
		ghChangeButton = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextPushButtonType, &boxloc, NULL, NULL, NULL);
		sADMItem->SetText(ghChangeButton, "Change");
		sADMDialog->SetDefaultItemID(dlg, sADMItem->GetID(ghChangeButton));
	}
	sADMItem->Show(ghChangeButton, TRUE);
	
	
	
	
	//******************************COLOR DIALOG ITEMS**********************************//
	
	//From Label
	if (!ghFromLabel) {
		boxloc.top=45; boxloc.left=6; boxloc.bottom=58; boxloc.right=100; // top, left, bottom, right
		ghFromLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghFromLabel, "From:");
	}
	sADMItem->Show(ghFromLabel, showReplaceColor);
	
	//CREATE THE FROM COLOR BOX
	//boxloc.top=96; boxloc.left=103; boxloc.bottom=116; boxloc.right=123; // top, left, bottom, right
	//ghFromColorBox = sADMItem->Create(dlg, kADMUniqueItemID, kADMPicturePushButtonType, &boxloc, NULL, NULL, NULL);
	//sADMItem->SetItemStyle(ghFromColorBox, kADMBlackRectPictureButtonStyle);
	//sADMItem->SetForeColor(ghFromColorBox, kADMRedColor);
	//sADMItem->SetBackColor(ghFromColorBox, kADMRedColor);
	
	
	//To In Label
	if (!ghToLabel) {
		boxloc.top=45; boxloc.left=106; boxloc.bottom=58; boxloc.right=200; // top, left, bottom, right
		ghToLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghToLabel, "To:");
	}
	sADMItem->Show(ghToLabel, showReplaceColor);
	
	
	//CREATE THE TO LIST
	if (!ghToList) {
		boxloc.top=58; boxloc.left=103; boxloc.bottom=78; boxloc.right=197; // top, left, bottom, right
		ghToList = sADMItem->Create(dlg, 551, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		//We'll initialize the list once its clicked on and add all the colors from the swatches
	}
	sADMItem->Show(ghToList, showReplaceColor);
	
	
	//CREATE THE REMOVE UNUSED COLORS BUTTON
	if (!ghRemoveUnused) {
		boxloc.top=112; boxloc.left=115; boxloc.bottom=130; boxloc.right=207; // top, left, bottom, right
		ghRemoveUnused = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextPushButtonType, &boxloc, NULL, NULL, NULL);
		sADMItem->SetText(ghRemoveUnused, "Unused Colors");
	}
	sADMItem->Show(ghRemoveUnused, showReplaceColor);
	
	

	//******************************OVERPRINT DIALOG ITEMS**********************************//
	//Color Select Label
	if (!ghColorSelectLabel) {
		boxloc.top=45; boxloc.left=6; boxloc.bottom=58; boxloc.right=100; // top, left, bottom, right
		ghColorSelectLabel = sADMItem->Create(dlg, kADMUniqueItemID, kADMTextStaticType, &boxloc, NULL, NULL, kADMDisableAutoActivateTextStaticStyle);
		sADMItem->SetText(ghColorSelectLabel, "Color:");
	}
	sADMItem->Show(ghColorSelectLabel, showOverprint);
	
	
	//CREATE Add/Remove selector
	if (!ghAddRemoveList) {
		boxloc.top=58; boxloc.left=103; boxloc.bottom=78; boxloc.right=197; // top, left, bottom, right
		ghAddRemoveList = sADMItem->Create(dlg, 551, kADMPopupListType, &boxloc, NULL, NULL, NULL);
		//INITIALIZE THE LIST
		entry = sADMList->InsertEntry( sADMItem->GetList(ghAddRemoveList), 0 );
		sADMEntry->SetText(entry, "Remove Overprint");
		entry = sADMList->InsertEntry( sADMItem->GetList(ghAddRemoveList), 1 );
		sADMEntry->SetID(entry, 1);
		sADMEntry->SetText(entry, "Add Overprint");
		//Select default entry
		sADMEntry->Select(sADMList->GetEntry(sADMItem->GetList(ghAddRemoveList), 1) , true);
	}
	sADMItem->Show(ghAddRemoveList, showOverprint);
	
	
}
