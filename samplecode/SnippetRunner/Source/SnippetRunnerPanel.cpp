//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerPanel.cpp $
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

#include "IADMHierarchyList.hpp"
#include "IADMListEntry.hpp"
#include "IADMDrawer.hpp"
#include "ADMItem.h"

// Project includes
#include "SDKErrors.h"
#include "SnippetRunnerSuites.h"
#include "SnippetRunnerID.h"
#include "SnippetRunnerPanel.h"
#include "SnippetRunnerManager.h"
#include "SnpRunnable.h"
#include "SnippetRunnerLog.h"
#include "SnippetRunnerParameter.h"
#include "SnippetRunnerPreferences.h"
#include "SnpDocumentHelper.h"
#include "SnpUnitTestHelper.h"

/*
*/
SnippetRunnerPanel::SnippetRunnerPanel(SPPluginRef pluginRef) : BaseADMDialog()
{
	int options = 0;
	this->Create( pluginRef, kSnippetRunnerPanelName, kSnippetRunnerPanelDialogID, kADMTabbedResizingFloatingDialogStyle,  options);
}

/*
*/
SnippetRunnerPanel::~SnippetRunnerPanel( )
{
}

/*
*/
ASErr SnippetRunnerPanel::Init () 
{
	ASErr result = BaseADMDialog::Init();
	
	if (!result) {
		// Set the min and max width and height.
		this->GetBoundsRect(fBounds);
		this->SetMinWidth(kSnippetRunnerPanelMinWidth);
		this->SetMinHeight(kSnippetRunnerPanelMinHeight);
		this->SetMaxWidth(kSnippetRunnerPanelMaxWidth);
		this->SetMaxHeight(kSnippetRunnerPanelMaxHeight);
		this->SetVerticalIncrement(kSnippetRunnerPanelSnippetListLineHeight);

		// Initialise the snippet list.
		IADMItem snippetListItem = this->GetItem(kSnippetRunnerPanelSnippetListItemID);
		snippetListItem.SetItemStyle(kADMDividedListBoxStyle | kADMBlackRectListBoxStyle | kADMEntryAlwaysSelectedListBoxStyle);
		IADMHierarchyList snippetListRoot = snippetListItem.GetHierarchyList();
		snippetListRoot.SetEntryHeightRecursive(kSnippetRunnerPanelSnippetListLineHeight);
		snippetListRoot.SetEntryWidthRecursive(kSnippetRunnerPanelMinWidth);
		snippetListRoot.SetEntryTextRectRecursive(IADMRect(2,0,kSnippetRunnerPanelMinWidth,kSnippetRunnerPanelSnippetListLineHeight));
		snippetListRoot.SetNotifyProcRecursive(&this->SnippetListNotifyProc);
		snippetListItem.SetUserData(this);

		// Create top level snippet list.
		SnippetRunnerManager& snipRunnerManager = SnippetRunnerManager::Instance();
		SnippetRunnerManager::Snippets snippets = snipRunnerManager.GetSnippets();
		IADMListEntry allSnippetsParent = snippetListRoot.InsertEntry(-1);
		allSnippetsParent.SetText("All Snippets");
		IADMHierarchyList allSnippetsList = allSnippetsParent.CreateChildList();
		allSnippetsParent.ExpandHierarchy(false);

		// Add snippets to the snippet list, adding each snippet to the categories it belongs to.
		for (SnippetRunnerManager::Snippets::const_iterator iter = snippets.begin(); iter != snippets.end(); iter++) {
			SnpRunnable* snippet = *iter;
			std::vector<std::string> categories = snippet->GetCategories();
			std::vector<std::string>::iterator catIter;
			for (catIter = categories.begin(); catIter != categories.end(); catIter++) {
				const char* category = catIter->c_str();
				ADMListEntryRef listEntryRef = snippetListRoot.FindEntry(category);
				IADMHierarchyList categorySnippetsList;
				if (listEntryRef) {
					IADMListEntry categoryEntry(listEntryRef);
					categorySnippetsList = categoryEntry.GetChildList();
				}
				else {
					IADMListEntry categoryEntry = snippetListRoot.InsertEntry(-1);
					categoryEntry.SetText(category);
					categorySnippetsList = categoryEntry.CreateChildList();
					categoryEntry.ExpandHierarchy(false);
				}
				IADMListEntry snippetListEntry = categorySnippetsList.InsertEntry(-1);
				snippetListEntry.SetText(snippet->GetName().c_str());
				IADMHierarchyList snippetMetaDataList = snippetListEntry.CreateChildList();
				snippetListEntry.ExpandHierarchy(false);

				IADMListEntry descriptionMetaData = snippetMetaDataList.InsertEntry(-1);
				std::string description = "Description: " + snippet->GetDescription();
				descriptionMetaData.SetText(description.c_str());

				SnpRunnable::Operations operations = snippet->GetOperations();
				if (operations.size()) {
					IADMListEntry operationsMetaData = snippetMetaDataList.InsertEntry(-1);
					operationsMetaData.SetText("Operations");
					IADMHierarchyList operationsMetaDataList = operationsMetaData.CreateChildList();
					operationsMetaData.ExpandHierarchy(false);
					for (SnpRunnable::Operations::iterator iter = operations.begin(); iter != operations.end(); iter++) {
						IADMListEntry optionList = operationsMetaDataList.InsertEntry(-1);
						optionList.SetText(iter->GetName().c_str());
						if (iter->GetPreconditions().size() > 0) {
							IADMHierarchyList optionMetaDataList = optionList.CreateChildList();
							optionList.ExpandHierarchy(false);
							IADMListEntry preconditionListEntry = optionMetaDataList.InsertEntry(-1);
							std::string preconditions = "Preconditions: " + iter->GetPreconditions();
							preconditionListEntry.SetText(preconditions.c_str());
						}
					}
				}
			}
		}

		// Initialise the log view.
		IADMItem logItem = this->GetItem(kSnippetRunnerPanelLogItemID);
		IADMList logList = logItem.GetList();
		logList.SetEntryHeight(kSnippetRunnerPanelLogLineHeight);
		logList.SetEntryTextRect(IADMRect(2,0,kSnippetRunnerPanelMinWidth,kSnippetRunnerPanelLogLineHeight));

		// Initialise the Run button.
		IADMItem runButtonItem = this->GetItem(kSnippetRunnerPanelRunButtonItemID);
		runButtonItem.SetNotifyProc(&this->RunButtonNotifyProc);
		runButtonItem.SetItemStyle(kADMBlackRectPictureButtonStyle);
		runButtonItem.SetPictureID(kSnippetRunnerPanelRunButtonIconResourceID);
		runButtonItem.SetRolloverPictureID(kSnippetRunnerPanelRunButtonRolloverIconResourceID);
		runButtonItem.SetHasRollOverProperty(true);
		runButtonItem.SetDisabledPictureID (kSnippetRunnerPanelRunButtonDisabledIconResourceID);
		runButtonItem.SetTipString("Run Snippet");
		runButtonItem.Enable(false);

		// Initialise the Save button.
		IADMItem saveButtonItem = this->GetItem(kSnippetRunnerPanelSaveButtonItemID);
		saveButtonItem.SetNotifyProc(&this->SaveButtonNotifyProc);
		saveButtonItem.SetItemStyle(kADMBlackRectPictureButtonStyle);
		saveButtonItem.SetPictureID(kSnippetRunnerPanelSaveButtonIconResourceID);
		saveButtonItem.SetRolloverPictureID(kSnippetRunnerPanelSaveButtonRolloverIconResourceID);
		saveButtonItem.SetHasRollOverProperty(true);
		saveButtonItem.SetDisabledPictureID (kSnippetRunnerPanelSaveButtonDisabledIconResourceID);
		saveButtonItem.SetTipString("Save Log");

		// Initialise the Delete button.
		IADMItem deleteButtonItem = this->GetItem(kSnippetRunnerPanelDeleteButtonItemID);
		deleteButtonItem.SetNotifyProc(&this->DeleteButtonNotifyProc);
		deleteButtonItem.SetItemStyle(kADMBlackRectPictureButtonStyle);
		deleteButtonItem.SetPictureID(kSnippetRunnerPanelDeleteButtonIconResourceID);
		deleteButtonItem.SetRolloverPictureID(kSnippetRunnerPanelDeleteButtonRolloverIconResourceID);
		deleteButtonItem.SetHasRollOverProperty(true);
		deleteButtonItem.SetDisabledPictureID (kSnippetRunnerPanelDeleteButtonDisabledIconResourceID);
		deleteButtonItem.SetTipString("Clear Log");

		// Initialise the panel's flyout menu.
		IADMItem panelMenu = this->GetItem(kADMMenuItemID);
		panelMenu.SetNotifyProc(&this->PanelMenuNotifyProc);
		panelMenu.SetUserData(this);
		IADMList panelMenuList(panelMenu.GetList());
		panelMenuList.SetMenuID(kSnippetRunnerPanelMenuResourceID);
		SnippetRunnerParameter::ParameterInputMode mode = SnippetRunnerParameter::Instance()->GetParameterInputMode();
		switch (mode) {
			default:
			case SnippetRunnerParameter::kDefaultParameterInputMode: 
				{
					IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(true);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(false);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(false);
				}
				break;
			case SnippetRunnerParameter::kPromptParameterInputMode:
				{
				IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(false);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(true);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(false);
				}
				break;
			case SnippetRunnerParameter::kCSVParameterInputMode:
				{
					IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(false);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(false);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(true);
				}
				break;
		} //end switch
		ASBoolean unitTest = SnippetRunnerPreferences::Instance()->GetUnitTest();
		IADMEntry unitTestEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuUnitTestItemID);
		unitTestEntry.Check(unitTest);

		// Initialise the parameter edit box.
		IADMItem parameterEditItem = this->GetItem(kSnippetRunnerPanelParameterEditItemID);
		parameterEditItem.SetItemStyle(kADMSingleLineTextEditStyle);
		parameterEditItem.Hide(); // Only shown when parameter input mode is CSV (see SnippetRunnerParameter::SetParameterInputMode).

		// Define the panels icon resource.
		SPPluginRef pluginRef = this->GetPluginRef();
		SDK_ASSERT(pluginRef);
		ADMIconRef icon = sADMIcon2->GetFromResource(pluginRef, 0, kSnippetRunnerPanelIconResourceID, 0);
		SDK_ASSERT(icon);
		result = this->SetIcon(false, icon);
		aisdk::check_ai_error(result);

		icon = sADMIcon2->GetFromResource(pluginRef, 0, kSnippetRunnerPanelRolloverIconResourceID, 0);
		SDK_ASSERT(icon);
		result = this->SetIcon(true, icon);
		aisdk::check_ai_error(result);
	}

	return result;
}

/*
*/
void SnippetRunnerPanel::HandleModelChanged(void)
{
	// Enable the run button if the selected snippet can run.
	ASBoolean canRun = false;
	const ASBoolean isUnitTestRunning = SnippetRunnerManager::Instance().IsUnitTestRunning();

	// Get selected entry in list - if any.
	IADMItem snippetListItem = this->GetItem(kSnippetRunnerPanelSnippetListItemID);
	IADMHierarchyList snippetListRoot = snippetListItem.GetHierarchyList();
	IADMListEntry activeListEntry(snippetListRoot.GetActiveLeafEntry());

	if (SnippetRunnerPreferences::Instance()->GetUnitTest()) {
		// Unit test preference is checked.
		if (!isUnitTestRunning && activeListEntry) {
			// Enable if unit test is not running.
			canRun  = true;
		}
	}
	else if (!isUnitTestRunning) {
		if (activeListEntry) {
			// Get associated snippet.
			std::string snippetName;
			std::string snippetOperation;
			SnippetRunnerPanel::GetSnippet(activeListEntry, snippetName, snippetOperation);

			// Find out if the snippet can run.
			canRun = SnippetRunnerManager::Instance().CanRun(snippetName, snippetOperation);
		}
	}

	// Enable / disable the run button.
	IADMItem runButtonItem = this->GetItem(kSnippetRunnerPanelRunButtonItemID);
	runButtonItem.Enable(canRun);
}

/*
*/
void SnippetRunnerPanel::HandleLogChanged(void)
{
	// Refresh the log view.
	IADMItem logItem = this->GetItem(kSnippetRunnerPanelLogItemID);
	IADMList logList = logItem.GetList();
	int logListLength = logList.NumberOfEntries();
	const SnippetRunnerLog::Log& logData = SnippetRunnerLog::Instance()->GetLog();
	for (unsigned int i = logListLength; i < logData.size(); i++) {
		IADMEntry entry = logList.InsertEntry(-1);
		// Have to use more recent suite for Unicode
		sADMEntry6->SetTextW(entry, logData[i].as_ASUnicode().c_str());
	}

	// Scroll view to the bottom of the log.
	logListLength = logList.NumberOfEntries();
	if (logListLength) {
		IADMEntry lastEntry = logList.IndexEntry(logListLength-1);
		lastEntry.MakeInBounds();
	}
}

/*
*/
void ASAPI SnippetRunnerPanel::RunButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	IADMItem myItem(item);
	myItem.DefaultNotify(notifier);
	IADMNotifier myNotifier(notifier);
	if (myNotifier.IsNotifierType(kADMUserChangedNotifier)) {
		IADMDialog dialog = myItem.GetDialog();

		// Get selected snippet and operation (if any).
		IADMItem snippetListItem = dialog.GetItem(kSnippetRunnerPanelSnippetListItemID);
		IADMHierarchyList snippetListRoot = snippetListItem.GetHierarchyList();
		IADMListEntry activeListEntry(snippetListRoot.GetActiveLeafEntry());
		std::string snippetName;
		std::string snippetOperation;
		SnippetRunnerPanel::GetSnippet(activeListEntry, snippetName, snippetOperation);

		if (!SnippetRunnerPreferences::Instance()->GetUnitTest()) {
			// Run.

			// Set the parameters (if any) - they'll only be used in kCSVParameterInputMode.
			IADMItem parameterEditItem = dialog.GetItem(kSnippetRunnerPanelParameterEditItemID);
			ai::AutoBuffer<ADMUnicode> paramBuf(parameterEditItem.GetTextLengthW());
			parameterEditItem.GetTextW(paramBuf, parameterEditItem.GetTextLengthW());
			SnippetRunnerParameter::Instance()->SetParameters(ai::UnicodeString(paramBuf, parameterEditItem.GetTextLengthW()));
			
			// Run the snippet.
			SnippetRunnerManager::Instance().Run(snippetName, snippetOperation);
		}
		else {
			// Unit test.

			SnippetRunnerManager& snipRunnerManager = SnippetRunnerManager::Instance();
			std::vector<std::string> snippetNames;
			if (snippetName.size() != 0) {
				// Test the selected snippet.
				snippetNames.push_back(snippetName);
			}
			else {
				// Test all snippets in the selected category.
				char text[256];
				activeListEntry.GetText(text, 256);
				//std::string category(text);
				SnippetRunnerManager::Snippets snippets = snipRunnerManager.GetSnippets(text);
				for (SnippetRunnerManager::Snippets::const_iterator iter = snippets.begin(); iter != snippets.end(); iter++) {
					SnpRunnable* snp = *iter;
					snippetNames.push_back(snp->GetName());
					
				}
			}
			if (!snipRunnerManager.RunUnitTest(snippetNames, snippetOperation)) {
				// Disable the run button.
				myItem.Enable(false);
			}
		}
	}
}

/*
*/
void ASAPI SnippetRunnerPanel::SaveButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	IADMItem myItem(item);
	myItem.DefaultNotify(notifier);
	IADMNotifier myNotifier(notifier);
	if (myNotifier.IsNotifierType(kADMUserChangedNotifier)) {
		SnippetRunnerLog::Instance()->Save();
	}
}

/*
*/
void ASAPI SnippetRunnerPanel::DeleteButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	IADMItem myItem(item);
	myItem.DefaultNotify(notifier);
	IADMNotifier myNotifier(notifier);
	if (myNotifier.IsNotifierType(kADMUserChangedNotifier)) {
		// Clear the log.
		SnippetRunnerLog::Instance()->Clear();

		// Clear the log view.
		IADMDialog dialog = myItem.GetDialog();
		IADMItem logItem = dialog.GetItem(kSnippetRunnerPanelLogItemID);
		IADMList logList = logItem.GetList();
		for (int i = logList.NumberOfEntries(); i > 0; i--) {
			logList.RemoveEntry(i-1);
		}
	}
}

/*
*/
void ASAPI SnippetRunnerPanel::SnippetListNotifyProc(ADMListEntryRef inEntry, ADMNotifierRef notifier)
{
	IADMListEntry myListEntry(inEntry);
	IADMItem myItem(myListEntry.GetItem());
	myItem.DefaultNotify(notifier);
	IADMNotifier myNotifier(notifier);
	if (myNotifier.IsNotifierType(kADMUserChangedNotifier)) {
		IADMDialog dialog = myItem.GetDialog();
		IADMItem snippetListItem = dialog.GetItem(kSnippetRunnerPanelSnippetListItemID);
		SnippetRunnerPanel* self = static_cast<SnippetRunnerPanel*>(snippetListItem.GetUserData());
		if (self) {
			self->HandleModelChanged();
		}
	}
}

/*
*/
void SnippetRunnerPanel::GetSnippet(IADMListEntry myListEntry, std::string& snippetName, std::string& snippetOperation)
{
		// Get name of snippet and any option
		IADMListEntry snippetListEntry;
		if (myListEntry.GetHierarchyDepth() == 1) { // Snippet
			snippetListEntry = myListEntry;
		}
		else if (myListEntry.GetHierarchyDepth() == 2) { // Snippet description
			IADMHierarchyList hierarchyList = myListEntry.GetList();
			snippetListEntry = hierarchyList.GetParentEntry();
		}
		else if (myListEntry.GetHierarchyDepth() == 3) { // Operation
			int len = myListEntry.GetTextLength();
			ai::AutoBuffer<char> option(len+1);
			myListEntry.GetText(option, len);
			snippetOperation = option.GetBuffer();
			IADMHierarchyList hierarchyList = myListEntry.GetList();
			IADMListEntry parentListEntry(hierarchyList.GetParentEntry());
			IADMHierarchyList parentHierarchyList = parentListEntry.GetList();
			snippetListEntry = parentHierarchyList.GetParentEntry();
		}
		else if (myListEntry.GetHierarchyDepth() == 4) { // Operation precondition's
			IADMHierarchyList hierarchyList = myListEntry.GetList();
			IADMListEntry parentListEntry(hierarchyList.GetParentEntry());
			int len = parentListEntry.GetTextLength();
			ai::AutoBuffer<char> option(len+1);
			parentListEntry.GetText(option, len);
			snippetOperation = option.GetBuffer();
			IADMHierarchyList parentHierarchyList = parentListEntry.GetList();
			IADMListEntry grandparentListEntry(parentHierarchyList.GetParentEntry());
			IADMHierarchyList grandparentHierarchyList = grandparentListEntry.GetList();
			snippetListEntry = grandparentHierarchyList.GetParentEntry();
		}

		if (snippetListEntry) {
			int len = snippetListEntry.GetTextLength();
			ai::AutoBuffer<char> name(len+1);
			snippetListEntry.GetText(name, len);
			snippetName = name.GetBuffer();
		}
}

/*
*/
void ASAPI SnippetRunnerPanel::PanelMenuNotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	IADMItem myItem(item);
	myItem.DefaultNotify(notifier);
	IADMNotifier myNotifier(notifier);
	if (myNotifier.IsNotifierType(kADMUserChangedNotifier)) {
		IADMList panelMenuList = myItem.GetList();
		IADMEntry activeEntry = panelMenuList.GetActiveEntry();
		if (activeEntry) {
			int menuID = activeEntry.GetID();
			switch (menuID) {
				case kSnippetRunnerPanelMenuDefaultParamItemID: {
					IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(true);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(false);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(false);
					IADMDialog dialog = myItem.GetDialog();
					IADMItem parameterEditItem = dialog.GetItem(kSnippetRunnerPanelParameterEditItemID);
					parameterEditItem.Show(false);
					SnippetRunnerParameter::Instance()->SetParameterInputMode(SnippetRunnerParameter::kDefaultParameterInputMode);
					break;
				}
				case kSnippetRunnerPanelMenuPromptParamItemID: {
					IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(false);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(true);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(false);
					IADMDialog dialog = myItem.GetDialog();
					IADMItem parameterEditItem = dialog.GetItem(kSnippetRunnerPanelParameterEditItemID);
					parameterEditItem.Show(false);
					SnippetRunnerParameter::Instance()->SetParameterInputMode(SnippetRunnerParameter::kPromptParameterInputMode);
					break;
				}
				case kSnippetRunnerPanelMenuCSVParamItemID: { 
					IADMEntry defaultParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuDefaultParamItemID);
					defaultParamEntry.Check(false);
					IADMEntry promptParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuPromptParamItemID);
					promptParamEntry.Check(false);
					IADMEntry csvParamEntry = panelMenuList.GetEntry(kSnippetRunnerPanelMenuCSVParamItemID);
					csvParamEntry.Check(true);
					IADMDialog dialog = myItem.GetDialog();
					IADMItem parameterEditItem = dialog.GetItem(kSnippetRunnerPanelParameterEditItemID);
					parameterEditItem.Show(true);
					SnippetRunnerParameter::Instance()->SetParameterInputMode(SnippetRunnerParameter::kCSVParameterInputMode);
					break;
				}
				case kSnippetRunnerPanelMenuUnitTestItemID: {
					ASBoolean unitTest = SnippetRunnerPreferences::Instance()->GetUnitTest();
					unitTest = !unitTest;
					SnippetRunnerPreferences::Instance()->SetUnitTest(unitTest);
					activeEntry.Check(unitTest);
					SnippetRunnerPanel* self = static_cast<SnippetRunnerPanel*>(myItem.GetUserData());
					if (self) {
						// Refresh the state of the Run button.
						self->HandleModelChanged();
					}
					break;
				}
				case kSnippetRunnerPanelMenuSetAssetsFolderItemID: {
					SnippetRunnerPreferences::Instance()->PromptAssetsFolderPath();
					break;
				}
				default: {
				}
			} // end switch
		}
	}
}


/*
*/
void SnippetRunnerPanel::Notify(IADMNotifier notifier)
{
	BaseADMDialog::Notify(notifier);
	ADMItemRef item = notifier.GetItem();
	if( !item && notifier.IsNotifierType(kADMBoundsChangedNotifier) ) {
		this->ResizePanel(notifier);
	}
}

/*
*/
void SnippetRunnerPanel::ResizePanel(IADMNotifier notifier)
{
	// Get the new bounds and caculate the horizontal and vertical change in size.
	IADMRect newBounds;
	this->GetBoundsRect(newBounds);
	int deltaH = newBounds.Width() - this->fBounds.Width();
	int deltaV = newBounds.Height() - this->fBounds.Height();
	IADMRect itemRect;

	// Resize snippet list.
	IADMItem snippetListItem = this->GetItem(kSnippetRunnerPanelSnippetListItemID);
	snippetListItem.GetBoundsRect(itemRect);
	itemRect.right += deltaH;
	itemRect.bottom += deltaV / 2;
	snippetListItem.SetBoundsRect(itemRect);
	IADMHierarchyList snippetListRoot = snippetListItem.GetHierarchyList();
	snippetListRoot.SetEntryWidthRecursive(itemRect.Width());
	IADMRect snippetListTextRect(2,0,itemRect.Width(),kSnippetRunnerPanelSnippetListLineHeight);
	snippetListRoot.SetEntryTextRectRecursive(snippetListTextRect);
	snippetListRoot.SetNonLeafEntryTextRectRecursive(snippetListTextRect);

	// Resize log view.
	IADMItem logItem = this->GetItem(kSnippetRunnerPanelLogItemID);
	logItem.GetBoundsRect(itemRect);
	itemRect.top += deltaV / 2;
	itemRect.right += deltaH;
	itemRect.bottom += deltaV;
	logItem.SetBoundsRect(itemRect);
	IADMList logList = logItem.GetList();
	logList.SetEntryTextRect(IADMRect(2,0,itemRect.Width(),kSnippetRunnerPanelLogLineHeight));

	// Resize parameter edit box.
	IADMItem parameterEditItem = this->GetItem(kSnippetRunnerPanelParameterEditItemID);
	parameterEditItem.GetBoundsRect(itemRect);
	itemRect.top += deltaV;
	itemRect.right += deltaH;
	itemRect.bottom += deltaV;
	parameterEditItem.SetBoundsRect(itemRect);

	// Move buttons.
	IADMItem deleteButtonItem = this->GetItem(kSnippetRunnerPanelDeleteButtonItemID);
	deleteButtonItem.GetBoundsRect(itemRect);
	itemRect.Offset(deltaH,deltaV);
	deleteButtonItem.SetBoundsRect(itemRect);
	IADMItem saveButtonItem = this->GetItem(kSnippetRunnerPanelSaveButtonItemID);
	saveButtonItem.GetBoundsRect(itemRect);
	itemRect.Offset(deltaH,deltaV);
	saveButtonItem.SetBoundsRect(itemRect);
	IADMItem runButtonItem = this->GetItem(kSnippetRunnerPanelRunButtonItemID);
	runButtonItem.GetBoundsRect(itemRect);
	itemRect.Offset(deltaH,deltaV);
	runButtonItem.SetBoundsRect(itemRect);

	// Save off the new bounds for next time the panel is resized.
	this->fBounds = newBounds;

}

// End SnippetRunnerPanel.cpp