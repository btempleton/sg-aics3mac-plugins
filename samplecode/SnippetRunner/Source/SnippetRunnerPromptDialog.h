//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerPromptDialog.h $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __SnippetRunnerPromptDialog_h__
#define __SnippetRunnerPromptDialog_h__

#include "BaseADMDialog.hpp"

/**	Provides dialog which prompts for parameter input.

	@ingroup snippetrunner
*/
class SnippetRunnerPromptDialog : public BaseADMDialog
{
public:
	/**	Constructor.
	*/
	SnippetRunnerPromptDialog();

	/**	Destructor.
	*/
	virtual ~SnippetRunnerPromptDialog();

	/** Prompts the user for a string.
		@param value OUT the string entered by the user.
		@param prompt IN string prompt to display in the dialog.
		@return true if user pressed OK button, false otherwise.
	*/
	ASBoolean GetString(ai::UnicodeString& value, const ai::UnicodeString& prompt);

	/** Prompts the user for a real value.
		@param value OUT the value entered by the user.
		@param prompt IN string prompt to display in the dialog.
		@param lowerLimit IN the smallest value that can be entered.
		@param upperLimit IN the largest value that can be entered.
		@return true if user pressed OK button, false otherwise.
	*/
	ASBoolean GetReal(ASReal& value, const ai::UnicodeString& prompt, const ASReal lowerLimit=0.0, const ASReal upperLimit=0.0);

	/** Prompts the user for an integer value.
		@param value OUT the value entered by the user.
		@param prompt IN string prompt to display in the dialog.
		@param lowerLimit IN the smallest value that can be entered.
		@param upperLimit IN the largest value that can be entered.
		@return true if user pressed OK button, false otherwise.
	*/
	ASBoolean GetInt(ASInt32& value, const ai::UnicodeString& prompt, const ASInt32 lowerLimit=0, const ASInt32 upperLimit=0);

	/** Prompts the user to choose from a list of string options.
		@param value OUT the users choice.
		@param prompt IN string prompt to display in the dialog.
		@param choices IN vector of strings to represent choices.
		@return true if user pressed OK button, false otherwise.
	*/
	ASBoolean GetChoice(ASUInt32& value, const ai::UnicodeString& prompt, const std::vector<ai::UnicodeString>& choices);

	/** Displays a message to the user.
		@param prompt IN string message.
		@return true if user pressed OK button, false otherwise.
	*/
	ASBoolean Alert(const ai::UnicodeString& prompt);

protected:
	/**	Initialises the dialog.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr  Init ();

private:
	/**	Handles dismissal of the modal prompt dialog.
		@param item IN reference to OK button.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI HandleOKButton(ADMItemRef item, ADMNotifierRef notifier);

private:
	/** Mode indicating type of data the dialog is to gather and return to the caller.
	*/
	typedef enum { kStringMode, kIntMode, kRealMode, kChoiceMode, kAlertMode } DialogMode;

	/** Prompt to display in the dialog
	*/
	ai::UnicodeString fPrompt;

	/** Current mode.
	*/
	DialogMode fMode;

	/** Minimum value allowed.
	*/
	ASReal fLowerLimit;

	/** Maximum value allowed.
	*/
	ASReal fUpperLimit;

	/** String entered by user.
	*/
	ai::UnicodeString fStringValue;

	/** Real value entered by user.
	*/
	ASReal fRealValue;

	/** Integer value entered by user.
	*/
	ASInt32 fIntValue;

	/** Choice made by user.
	*/
	ASUInt32 fChoiceValue;

	/** List of choices available to user.
	*/
	std::vector<ai::UnicodeString> fChoices;
};

#endif // __SnippetRunnerPromptDialog_h__

// End SnippetRunnerPromptDialog.h