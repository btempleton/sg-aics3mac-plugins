//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerPromptDialog.cpp $
//
//  $Revision: #2 $
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

#include "ADMItem.h"
#include "IAIStringFormatUtils.h"

// Project includes
#include "SnippetRunnerID.h"
#include "SnippetRunnerPromptDialog.h"
#include "SnippetRunnerPlugin.h"
#include "SnippetRunnerSuites.h"

extern SnippetRunnerPlugin*	gPlugin;

/*
*/
SnippetRunnerPromptDialog::SnippetRunnerPromptDialog() : BaseADMDialog()
{
}

/*
*/
SnippetRunnerPromptDialog::~SnippetRunnerPromptDialog( )
{
}

/*
*/
ASBoolean SnippetRunnerPromptDialog::GetString(ai::UnicodeString& value, const ai::UnicodeString& prompt)
{
	ASBoolean result = false;
	this->fMode = SnippetRunnerPromptDialog::kStringMode;
	this->fPrompt = prompt;
	this->fStringValue = value;
	int item = this->Modal( gPlugin->GetPluginRef(), kSnippetRunnerPromptDialogName, kSnippetRunnerPromptDialogID);
	result = (kDlgOKButton == item) ? true : false; 
	if (result) {
		value = this->fStringValue;
	}
	return result;
}

/*
*/
ASBoolean SnippetRunnerPromptDialog::GetReal(ASReal& value, const ai::UnicodeString& prompt, const ASReal lowerLimit, const ASReal upperLimit)
{
	ASBoolean result = false;
	this->fMode = SnippetRunnerPromptDialog::kRealMode;
	this->fPrompt = prompt;
	this->fLowerLimit = lowerLimit;
	this->fUpperLimit = upperLimit;
	
	this->fRealValue = value;
	int item = this->Modal( gPlugin->GetPluginRef(), kSnippetRunnerPromptDialogName, kSnippetRunnerPromptDialogID);
	result = (kDlgOKButton == item) ? true : false;
	if (result) {
		value = this->fRealValue;
	}
	return result;
}

/*
*/
ASBoolean SnippetRunnerPromptDialog::GetInt(ASInt32& value, const ai::UnicodeString& prompt, const ASInt32 lowerLimit, const ASInt32 upperLimit)
{
	ASBoolean result = false;
	this->fMode = SnippetRunnerPromptDialog::kIntMode;
	this->fPrompt = prompt;
	this->fLowerLimit = static_cast<ASReal>(lowerLimit);
	this->fUpperLimit = static_cast<ASReal>(upperLimit);
	this->fIntValue = value;
	int item = this->Modal( gPlugin->GetPluginRef(), kSnippetRunnerPromptDialogName, kSnippetRunnerPromptDialogID);
	result = (kDlgOKButton == item) ? true : false;
	if (result) {
		value = this->fIntValue;
	}
	return result;
}

/*
*/
ASBoolean SnippetRunnerPromptDialog::GetChoice(ASUInt32& value, const ai::UnicodeString& prompt, const std::vector<ai::UnicodeString>& choices)
{
	ASBoolean result = false;
	this->fMode = SnippetRunnerPromptDialog::kChoiceMode;
	this->fPrompt = prompt;
	this->fChoiceValue = value;
	this->fChoices = choices;
	int item = this->Modal( gPlugin->GetPluginRef(), kSnippetRunnerPromptDialogName, kSnippetRunnerPromptDialogID);
	result = (kDlgOKButton == item) ? true : false;
	if (result) {
		value = this->fChoiceValue;
	}
	return result;
}

/*
*/
ASBoolean SnippetRunnerPromptDialog::Alert(const ai::UnicodeString& prompt)
{
	ASBoolean result = false;
	this->fMode = SnippetRunnerPromptDialog::kAlertMode;
	this->fPrompt = prompt;
	int item = this->Modal( gPlugin->GetPluginRef(), kSnippetRunnerPromptDialogName, kSnippetRunnerPromptDialogID);
	result = (kDlgOKButton == item) ? true : false; 
	return result;
}

/*
*/
ASErr SnippetRunnerPromptDialog::Init () 
{
	ASErr result = BaseADMDialog::Init();

	if (!result) {		
		// Initialise the dialog.
		IADMItem promptItem(this->GetItem(kSnippetRunnerParameterPromptItemID));
		promptItem.SetTextW(this->fPrompt.as_ASUnicode().c_str());
		IADMItem valueItem(this->GetItem(kSnippetRunnerParameterValueItemID));
		valueItem.Hide();
		IADMItem choiceItem(this->GetItem(kSnippetRunnerParameterChoiceItemID));
		choiceItem.Hide();
		IADMItem typeItem(this->GetItem(kSnippetRunnerParameterTypeItemID));
		switch (this->fMode) {
			default:
			case SnippetRunnerPromptDialog::kStringMode: {
				valueItem.Show();
				valueItem.SetTextW(this->fStringValue.as_ASUnicode().c_str());
				typeItem.SetText("string");
				break;
			}
			case SnippetRunnerPromptDialog::kIntMode: {
				valueItem.Show();
				valueItem.SetIntValue(this->fIntValue);
				valueItem.SetUnits(kADMNoUnits);
				ai::UnicodeString type("integer");
				if (!(this->fLowerLimit==0.0 && this->fUpperLimit==0.0)) {
					valueItem.SetMinIntValue(static_cast<ASInt32>(this->fLowerLimit));
					valueItem.SetMaxIntValue(static_cast<ASInt32>(this->fUpperLimit));
					ai::UnicodeString lower;
					ai::NumberFormat().toString(static_cast<ASInt32>(this->fLowerLimit), lower);
					ai::UnicodeString upper;
					ai::NumberFormat().toString(static_cast<ASInt32>(this->fUpperLimit), upper);
					type += ai::UnicodeString(" ");
					type += lower;
					type += ai::UnicodeString(":");
					type += upper;
				}
				typeItem.SetText(type.getInStdString(kAIPlatformCharacterEncoding).c_str());
				break;
			}
			case SnippetRunnerPromptDialog::kRealMode: {
				valueItem.Show();
				valueItem.SetFloatValue(this->fRealValue);
				valueItem.SetUnits(kADMNoUnits);
				ai::UnicodeString type("real");
				if (!(this->fLowerLimit==0.0 && this->fUpperLimit==0.0)) {
					valueItem.SetMinFloatValue(this->fLowerLimit);
					valueItem.SetMaxFloatValue(this->fUpperLimit);
					ai::UnicodeString lower;
					ai::NumberFormat().toString(this->fLowerLimit, 2, lower);
					ai::UnicodeString upper;
					ai::NumberFormat().toString(this->fUpperLimit, 2, upper);
					type += ai::UnicodeString(" ");
					type += lower;
					type += ai::UnicodeString(":");
					type += upper;
				}
				typeItem.SetText(type.getInStdString(kAIPlatformCharacterEncoding).c_str());
				break;
			}
			case SnippetRunnerPromptDialog::kChoiceMode: {
				choiceItem.Show();
				IADMList choiceList(choiceItem.GetList());
				for (std::vector<ai::UnicodeString>::iterator iter = this->fChoices.begin(); iter != this->fChoices.end(); iter++) {
					IADMEntry choiceEntry = choiceList.InsertEntry(-1);
					sADMEntry6->SetTextW(choiceEntry, iter->as_ASUnicode().c_str());
				}
				IADMEntry defaultEntry(choiceList.IndexEntry(this->fChoiceValue));
				defaultEntry.Select();
				typeItem.SetText("choice");
				break;
			}
			case SnippetRunnerPromptDialog::kAlertMode: {
				typeItem.SetText("alert");
				break;
			}
		}
		// Specify the function that gets called when the user dismisses the dialog.
		// Also save off a pointer to this object so the callback function can access it.
		IADMItem okItem(this->GetItem(kDlgOKButton));
		okItem.SetUserData(this);
		okItem.SetNotifyProc(this->HandleOKButton);
	}

	return result;
}

/** Handles dismissal of the modal prompt dialog.
*/
void ASAPI SnippetRunnerPromptDialog::HandleOKButton(ADMItemRef item, ADMNotifierRef notifier)
{
	IADMItem myItem(item);
	myItem.DefaultNotify(notifier);
	IADMDialog dialog = myItem.GetDialog();
	SnippetRunnerPromptDialog* self = static_cast<SnippetRunnerPromptDialog*>(myItem.GetUserData());
	switch (self->fMode) {
		default:
		case SnippetRunnerPromptDialog::kStringMode: {
			IADMItem valueItem(dialog.GetItem(kSnippetRunnerParameterValueItemID));
			ADMInt32 len = valueItem.GetTextLengthW();
			ai::AutoBuffer<ADMUnicode> valueBuf(len);
			valueItem.GetTextW(valueBuf, len);
			self->fStringValue = ai::UnicodeString(valueBuf, len);
			break;
			}
		case SnippetRunnerPromptDialog::kIntMode: {
			IADMItem valueItem(dialog.GetItem(kSnippetRunnerParameterValueItemID));
			self->fIntValue = valueItem.GetIntValue();
			break;
			}
		case SnippetRunnerPromptDialog::kRealMode: {
			IADMItem valueItem(dialog.GetItem(kSnippetRunnerParameterValueItemID));
			self->fRealValue = valueItem.GetFloatValue();
			break;
			}
		case SnippetRunnerPromptDialog::kChoiceMode: {
			IADMItem choiceItem(dialog.GetItem(kSnippetRunnerParameterChoiceItemID));
			IADMList choiceList(choiceItem.GetList());
			IADMEntry choiceEntry(choiceList.GetActiveEntry());
			self->fChoiceValue = choiceEntry.GetIndex();
			break;
		}
	}
}

// End SnippetRunnerPromptDialog.cpp