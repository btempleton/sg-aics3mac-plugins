//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsPlugin.hpp $
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

#ifndef __MarkedObjectsPlugin_hpp__
#define __MarkedObjectsPlugin_hpp__

#include "MarkedObjectManager.hpp"
#include "MarkedObjectsDialog.hpp"
#include "MarkedObjectsPreferences.hpp"

static const int kToolStrings 	= 16100;
static const int kToolIcons 	= 16050;
static const int kCursorID		= 16000;
static const int kNoIconErr		= '!ico';

class MarkedObjectsDialog;
class MarkedObjectsPreferences;
class MarkedObjectManager;

class MarkedObjectsPlugin : public Plugin
{
private:
	AIMenuItemHandle			menuItem;
	MarkedObjectsDialog *		nonModalDialog;
	AINotifierHandle			artSelectionChangedNotifier;
	AINotifierHandle			documentChangedNotifier;
	AINotifierHandle			documentSaveNotifierBefore;
	AINotifierHandle			documentSaveAsNotifierBefore;
	AINotifierHandle			documentSaveNotifierAfter;
	AINotifierHandle			documentSaveAsNotifierAfter;
	AIToolHandle				toolHandle;
	MarkedObjectManager *		objectManager;
	MarkedObjectsPreferences *	preferences;
	AIMenuItemHandle			aboutPluginMenu;
	
protected:

	ASErr SetGlobal(Plugin * plugin);

	ASErr GoMenuItem( AIMenuMessage * message );
	ASErr UpdateMenuItem( AIMenuMessage * message );
	
	ASErr StartupPlugin( SPInterfaceMessage * message );
	ASErr ShutdownPlugin( SPInterfaceMessage * message );

	ASErr Notify( AINotifierMessage * message );
	
	// add tool handlers
	ASErr EditTool( AIToolMessage * message );
	ASErr TrackToolCursor( AIToolMessage * message );
	ASErr ToolMouseDown( AIToolMessage * message );
	ASErr ToolMouseDrag( AIToolMessage * message );
	ASErr ToolMouseUp( AIToolMessage * message );
	ASErr SelectTool( AIToolMessage * message );
	ASErr DeselectTool( AIToolMessage * message );
	ASErr ReselectTool( AIToolMessage * message );
	
	ASErr Timer(AITimerMessage * message );
	
	bool IsMarkedObjectSelected( void );
	
public:
	MarkedObjectsPlugin(SPPluginRef pluginRef);
	virtual ~MarkedObjectsPlugin();
	
	ASErr HideMarkedObjectsLayer( AIBoolean hide );
	ASErr SelectMarkedObject(int index);
	void GetMarkedObjects(void);
	
	void WriteMarkedPoints( const ai::FilePath & fileSpec );
	void UpdateMarkedObjectString( int itemSelected, const string & newString );

	void ResetIDs( void );
	
	void SelectOurTool( void );
	
	void UnSelectAllArt( void );

	void ResetInsertionPoint( void );
	
	void SetDialogPreferences( void );
	
	void DoModalPrefs( void );
	
};

#endif
