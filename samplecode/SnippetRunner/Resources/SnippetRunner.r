#define PIPL_PLUGIN_NAME "SnippetRunner"
#include "Plugin.r"

#include "SnippetRunnerID.h"

#include "Types.r"

read 'PNGI'(kSnippetRunnerPanelRunButtonIconResourceID, "Info Icon", purgeable) "RunButton_N.png";
read 'PNGI'(kSnippetRunnerPanelRunButtonRolloverIconResourceID, "Info Icon", purgeable) "RunButton_R.png";
read 'PNGI'(kSnippetRunnerPanelRunButtonDisabledIconResourceID, "Info Icon", purgeable) "RunButton_D.png";
read 'PNGI'(kSnippetRunnerPanelDeleteButtonIconResourceID, "Info Icon", purgeable) "DeleteButton_N.png";
read 'PNGI'(kSnippetRunnerPanelDeleteButtonRolloverIconResourceID, "Info Icon", purgeable) "DeleteButton_R.png";
read 'PNGI'(kSnippetRunnerPanelDeleteButtonDisabledIconResourceID, "Info Icon", purgeable) "DeleteButton_D.png";
read 'PNGI'(kSnippetRunnerPanelSaveButtonIconResourceID, "Info Icon", purgeable) "SaveButton_N.png";
read 'PNGI'(kSnippetRunnerPanelSaveButtonRolloverIconResourceID, "Info Icon", purgeable) "SaveButton_R.png";
read 'PNGI'(kSnippetRunnerPanelSaveButtonDisabledIconResourceID, "Info Icon", purgeable) "SaveButton_D.png";

/** SnippetRunner panel.
*/
resource 'DLOG' (kSnippetRunnerPanelDialogID, kSnippetRunnerPanelName, purgeable) { 
	{100, 200, 306, 406}, 
	1991, // floatZoomGrowProc
	visible, 
	goAway, 
	0x0, 
	kSnippetRunnerPanelDialogID, 
	kSnippetRunnerPluginName, 
	0x0 // noAutoCenter 
}; 

/** List of controls in SnippetRunner panel.
*/
resource 'DITL' (kSnippetRunnerPanelDialogID, kSnippetRunnerPanelName, purgeable) {
	{
		{0,0,80,206}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPanelDialogID+kSnippetRunnerPanelSnippetListItemID
		},
		{85,0,165,206}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPanelDialogID+kSnippetRunnerPanelLogItemID
		},
		{170,0,190,206}, // top, left, bottom, right
		EditText {
			enabled,
			""
		},
		{190,99,206,130}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPanelDialogID+kSnippetRunnerPanelRunButtonItemID
		},
		{190,129,206,160}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPanelDialogID+kSnippetRunnerPanelSaveButtonItemID
		},
		{190,159,206,190}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPanelDialogID+kSnippetRunnerPanelDeleteButtonItemID
		},
	}
};

resource 'CNTL' (kSnippetRunnerPanelDialogID+kSnippetRunnerPanelSnippetListItemID, "SnippetRunnerPanelSnippetList", purgeable) {
	{0,0,80,206},
	0,
	visible,
	100,
	0,
	16176,	// kADMHierarchyListBoxType ProcID = CDEFResID * 16 + Variation
	0,
	""
};

resource 'CNTL' (kSnippetRunnerPanelDialogID+kSnippetRunnerPanelLogItemID, "SnippetRunnerPanelLog", purgeable) {
	{0,0,80,206},
	0,
	visible,
	100,
	0,
	16160, // kADMListBoxType ProcID
	0,
	""
};

resource 'CNTL' (kSnippetRunnerPanelDialogID+kSnippetRunnerPanelRunButtonItemID, "SnippetRunnerPanelRunButton", purgeable) {
	{0,0,16,31},
	kSnippetRunnerPanelRunButtonIconResourceID,
	visible,
	kSnippetRunnerPanelRunButtonRolloverIconResourceID,
	kSnippetRunnerPanelRunButtonDisabledIconResourceID,
	16320, // kADMPicturePushButton ProcID
	0,
	""
};

resource 'CNTL' (kSnippetRunnerPanelDialogID+kSnippetRunnerPanelSaveButtonItemID, "SnippetRunnerPanelSaveButton", purgeable) {
	{0,0,16,31},
	kSnippetRunnerPanelSaveButtonIconResourceID,
	visible,
	kSnippetRunnerPanelSaveButtonRolloverIconResourceID,
	kSnippetRunnerPanelSaveButtonDisabledIconResourceID,
	16320, // kADMPicturePushButton ProcID
	0,
	""
};

resource 'CNTL' (kSnippetRunnerPanelDialogID+kSnippetRunnerPanelDeleteButtonItemID, "SnippetRunnerPanelDeleteButton", purgeable) {
	{0,0,16,31},
	kSnippetRunnerPanelDeleteButtonIconResourceID,
	visible,
	kSnippetRunnerPanelDeleteButtonRolloverIconResourceID,
	kSnippetRunnerPanelDeleteButtonDisabledIconResourceID,
	16320, // kADMPicturePushButton ProcID
	0,
	""
};

resource 'MENU' (kSnippetRunnerPanelMenuResourceID) {
	kSnippetRunnerPanelMenuResourceID,
	textMenuProc,
	-1,
	enabled,
	"SnippetRunner Panel Menu",
	{
		"Default Parameters",			noIcon, noKey, noMark, plain;
		"Prompt Parameters",			noIcon, noKey, noMark, plain;
		"CSV Parameters",				noIcon, noKey, noMark, plain;
		"-",							noIcon, noKey, noMark, plain;
		"Unit Test",					noIcon, noKey, noMark, plain;
		"-",							noIcon, noKey, noMark, plain;
		"Set Assets Folder",			noIcon, noKey, noMark, plain;		
	}
};


/** Parameter prompt dialog.
*/
resource 'DLOG' (kSnippetRunnerPromptDialogID, kSnippetRunnerPromptDialogName, purgeable) { 
	//{200, 200, 400, 500},
	{200, 200, 330, 600}, 
	5, // movableDBoxProc
	visible, 
	goAway, 
	0x0, 
	kSnippetRunnerPromptDialogID, 
	kSnippetRunnerPromptDialogName, 
	0x0 // noAutoCenter 
}; 

/** List of controls in parameter prompt dialog.
*/
resource 'DITL' (kSnippetRunnerPromptDialogID, kSnippetRunnerPromptDialogName, purgeable) {
	{
		{15,315,35,395}, // top, left, bottom, right
		Button {
			enabled,
			"OK"
		},
		{50,315,70,395}, // top, left, bottom, right
		Button {
			enabled,
			"Cancel"
		},
		{5,5,40,300}, // top, left, bottom, right
		StaticText {
			enabled,
			"Prompt: "
		},
		{50,5,70,300}, // top, left, bottom, right
		EditText {
			enabled,
			""
		},
		{50,5,70,300}, // top, left, bottom, right
		Control {
			enabled,
			kSnippetRunnerPromptDialogID+kSnippetRunnerParameterChoiceItemID
		},
		{90,5,110,175}, // top, left, bottom, right
		StaticText {
			enabled,
			"Type: "
		},
	}
};

resource 'CNTL' (kSnippetRunnerPromptDialogID+kSnippetRunnerParameterChoiceItemID, "SnippetRunnerParameterChoice", purgeable) {
	{0,0,14,170},
	0,
	invisible,
	0,
	0,
	1008, // kADMPopupListType ProcID
	0,
	""
};



