//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/SnippetRunner/Source/SnippetRunnerPanel.h $
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

#ifndef __SnippetRunnerPanel_h__
#define __SnippetRunnerPanel_h__

#include "BaseADMDialog.hpp"

/** Provides panel which allows snippets to be chosen, run
	and to view a log of their results.

	@ingroup snippetrunner
*/
class SnippetRunnerPanel : public BaseADMDialog
{
public:
	/** Constructor - creates this plug-in's panel.
		@param reference to this plugin.
	*/
	SnippetRunnerPanel(SPPluginRef pluginRef);

	/** Destructor.
	*/
	virtual ~SnippetRunnerPanel(void);

	/** Enables and disables the state of the Run button on the panel.
	*/
	void HandleModelChanged(void);

	/** Refreshes the view of the log - see SnippetRunnerLog.
	*/
	void HandleLogChanged(void);

protected:
	/** Initialises the contols on this plug-in's panel.
		@return kNoErr on success, other error code otherwise.
	*/
	virtual ASErr  Init();

	/** Handles notifications from ADM.
		@param notifier IN object providing access to notifier details.
	*/
	void Notify(IADMNotifier notifier); 

private:
	/** Handles resize of this plug-in's panel.
		@param notifier IN object providing access to notifier details.
	*/
	void ResizePanel(IADMNotifier notifier);

	/** Gets the selected snippet and operation from the list in this plug-in's panel.
		@param listEntry IN active list entry.
		@param snippetName OUT - name of the selected snippet.
		@param snippetOperation OUT - name of the selected operation - may be empty if no operation is chosen.
	*/
	static void GetSnippet(IADMListEntry listEntry, std::string& snippetName, std::string& snippetOption);

	/** Handles clicks on the snippet list.
		@param inEntry IN reference to the list entry item.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI SnippetListNotifyProc(ADMListEntryRef inEntry, ADMNotifierRef notifier);

	/** Handles clicks on the Run button - runs a snippet or a unit test in response.
		@param item IN reference to the item.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI RunButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier);

	/** Handles clicks on the Save button - saves the log in response.
		@param item IN reference to the item.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI SaveButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier);

	/** Handles clicks on the delete button - clears the log in response.
		@param item IN reference to the item.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI DeleteButtonNotifyProc(ADMItemRef item, ADMNotifierRef notifier);

	/** Handles clicks on this panel's menu.
		@param item IN reference to the item.
		@param notifier IN reference to notifier object.
	*/
	static void ASAPI PanelMenuNotifyProc(ADMItemRef item, ADMNotifierRef notifier);

private:
	/**	Container for position and size of the panel.
	*/
	IADMRect fBounds;
};

#endif // __SnippetRunnerPanel_h__

// End SnippetRunnerPanel.h