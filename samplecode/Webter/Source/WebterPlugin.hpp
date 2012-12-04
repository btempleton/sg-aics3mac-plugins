//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Webter/Source/WebterPlugin.hpp $
//
//  $Revision: #4 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __WebterPlugin_hpp__
#define __WebterPlugin_hpp__

#include "Plugin.hpp"
#include "WebterDialog.hpp"

static const int kToolStrings 	= 16100;
static const int kToolIcons 	= 16050;
static const int kCursorID		= 16000;
static const int kNoIconErr		= '!ico';

class WebterPlugin : public Plugin
{
private:
	AIMenuItemHandle	fMenuItem;
	WebterDialog		*fNonModalDialog;
	ADMDialogRef		fDialogRef; //do we need this
	AIToolHandle		fTool[3];
	AIRealPoint			fStartingPoint, fEndPoint;
	AIArtHandle			fArtHandle;
	AINotifierHandle	fArtSelectionChangedNotifier;
	AINotifierHandle	fDocumentChangedNotifier;
	AIMenuItemHandle	fAboutPluginMenu;

protected:

	ASErr SetGlobal(Plugin *plugin);

	ASErr GoMenuItem( AIMenuMessage *message );
	ASErr UpdateMenuItem( AIMenuMessage *message );
	
	ASErr StartupPlugin( SPInterfaceMessage *message );
	ASErr ShutdownPlugin( SPInterfaceMessage *message );

	ASErr Notify( AINotifierMessage *message );
	
public:
	WebterPlugin(SPPluginRef pluginRef);
	virtual ~WebterPlugin();
};

#endif
