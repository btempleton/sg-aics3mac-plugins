/*
 *  populateDialog.h
 *  FindReplaceGraphics
 *
 *  Created by Comp Mac 8a on 12/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
//GLOBAL HANDLES TO DIALOG ITEMS
extern ADMItemRef ghAttributeLabel, ghChangeInLabel, ghFromLabel, ghToLabel, ghApplyToLabel, ghNumberChangedLabel,
	ghAttributeList, ghChangeInList, ghFromList, ghFromColorBox, ghToList, ghToColorBox, ghApplyToList, ghIncludeTintsCheckBox, ghChangeButton, ghRemoveUnused,
	ghColorSelectLabel, ghAddRemoveList;



void populateDialog(ADMDialogRef dlg, int whichAttribute);