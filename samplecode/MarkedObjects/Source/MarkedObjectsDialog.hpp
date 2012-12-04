//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsDialog.hpp $
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

#ifndef __MarkedObjectsDialog_hpp__
#define __MarkedObjectsDialog_hpp__

#include "MarkedObjectsSuites.h"
#include "MarkedObjectsPlugin.hpp"

const int kLocationStr		= 1;
const int kXStr				= 2;
const int kXText			= 3;
const int kYStr				= 4;
const int kYText			= 5;
const int kIDStr			= 6;
const int kIDText			= 7;
const int kTypeStr			= 8;
const int kTypePopup		= 9;
const int kLabelStr			= 10;
const int kLabelText		= 11;
const int kUpdateButton		= 12;
const int kHideShowAllButton= 13;
const int kGlobalObjectsList= 14;
const int kBBText			= 15;
const int kBBWidth			= 16;
const int kBBHeight			= 17;

const int kTypeMenuResource 	= 800;
const int kDialogOptions		= 900;

const int kOptionsSave			= 1;
const int kOptionsResetIDs		= 2;
const int kOptionsPreferences	= 3;

const int kADMNonModalDialogID = 16000;

class MarkedObjectsPlugin;

extern MarkedObjectsPlugin * gPlugin;

class MarkedObject;
class MarkedObjectsDialog;

class MarkedObjectsDialog : public BaseADMDialog
{
private:
	IADMRect bounds;
	static void ASAPI DialogPopupMenuProc( ADMItemRef item, ADMNotifierRef notifier );

public:
	MarkedObjectsDialog();
	ADMDialogRef Create(SPPluginRef pluginRef, char * name, int dialogID, ADMDialogStyle style, int options );
	virtual ~MarkedObjectsDialog();
	
	void ClearMarkedObjectList(void);
	void AddMarkedObject( MarkedObject * markedObject );
	
	void UpdateMarkedObjectSelected(void);
	
	void Clear( void );

	void UpdateBoundingBoxInfo( void );
	
protected:

	ASErr Init();
	void Notify( IADMNotifier notifier );
	void Destroy();
	
	void NewGlobalObjectSelected(void);
	void UpdateMarkedObject(void);
	
	void ResizeLabelFrame( void );
	
};

#endif
//end MarkedObjectsDialog.hpp