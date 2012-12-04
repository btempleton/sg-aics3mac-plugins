//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerID.h $
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

#ifndef __SnippetRunnerID_H__
#define __SnippetRunnerID_H__

#define kSnippetRunnerPluginName								"SnippetRunner"

// SnippetRunner panel
#define kSnippetRunnerPanelName									kSnippetRunnerPluginName
#define	kSnippetRunnerPanelIconResourceID						5041
#define	kSnippetRunnerPanelRolloverIconResourceID				5042

#define	kSnippetRunnerPanelDialogID								16100
#define	kSnippetRunnerPanelSnippetListItemID					1
#define	kSnippetRunnerPanelLogItemID							2
#define	kSnippetRunnerPanelParameterEditItemID					3

#define	kSnippetRunnerPanelRunButtonItemID						4
#define	kSnippetRunnerPanelRunButtonIconResourceID				16140	
#define	kSnippetRunnerPanelRunButtonRolloverIconResourceID		16141
#define	kSnippetRunnerPanelRunButtonDisabledIconResourceID		16142

#define	kSnippetRunnerPanelSaveButtonItemID						5
#define	kSnippetRunnerPanelSaveButtonIconResourceID				16150	
#define	kSnippetRunnerPanelSaveButtonRolloverIconResourceID		16151
#define	kSnippetRunnerPanelSaveButtonDisabledIconResourceID		16152

#define	kSnippetRunnerPanelDeleteButtonItemID					6
#define	kSnippetRunnerPanelDeleteButtonIconResourceID			16160	
#define	kSnippetRunnerPanelDeleteButtonRolloverIconResourceID	16161
#define	kSnippetRunnerPanelDeleteButtonDisabledIconResourceID	16162

// ItemID for panel's fly out menu is predefined by the API as kADMMenuItemID
#define	kSnippetRunnerPanelMenuResourceID						16170	
#define	kSnippetRunnerPanelMenuDefaultParamItemID				1
#define	kSnippetRunnerPanelMenuPromptParamItemID				2
#define	kSnippetRunnerPanelMenuCSVParamItemID					3
#define	kSnippetRunnerPanelMenuSeparator1ItemID					4
#define	kSnippetRunnerPanelMenuUnitTestItemID					5
#define	kSnippetRunnerPanelMenuSeparator2ItemID					6
#define	kSnippetRunnerPanelMenuSetAssetsFolderItemID			7

#define	kSnippetRunnerPanelMinWidth								206
#define kSnippetRunnerPanelMaxWidth								30000
#define	kSnippetRunnerPanelMinHeight							196
#define kSnippetRunnerPanelMaxHeight							30000
#define kSnippetRunnerPanelSnippetListLineHeight				20
#define kSnippetRunnerPanelIndentation							16
#define kSnippetRunnerPanelLogLineHeight						12


// SnippetRunner parameter dialog
#define kSnippetRunnerPromptDialogName							"SnippetRunner Parameter"
#define	kSnippetRunnerPromptDialogID							16200
#define	kSnippetRunnerParameterPromptItemID						3
#define	kSnippetRunnerParameterValueItemID						4
#define kSnippetRunnerParameterChoiceItemID						5
#define	kSnippetRunnerParameterTypeItemID						6

#define kDlgOKButton				1							// TODO Plugin.cpp demands it
#define kDlgCancelButton			2							// TODO Plugin.cpp demands it

#define kAboutDLOG					16050						// TODO Plugin.cpp demands it

#endif

// End SnippetRunnerID.h
