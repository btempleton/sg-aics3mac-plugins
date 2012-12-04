#ifndef __AI110ActionManager_h__
#define __AI110ActionManager_h__

/*
 *        Name:	AIActionManager.h
 *   $Revision: 22 $
 *      Author:	Grace Ge
 *        Date:	10/14/97
 *     Purpose:	AI Action Manager Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIActionManager.h */

/*
 * Constants
 */

#define kAI110ActionManagerSuite		kAIActionManagerSuite
#define kAIActionManagerSuiteVersion2	AIAPI_VERSION(2)
#define kAI110ActionManagerSuiteVersion	kAIActionManagerSuiteVersion2

/**
	The Action Manager suite allows you to access the internal scripting system built into
	Adobe Illustrator. The Action Manager allows you to record and play actions which
	execute Illustrator menu commands or plug-in commands. The Action Manager suite allows
	your plug-in to play actions or register itself to the Illustrator application to enable
	your plug-in to be scriptable via the Actions palette.

	An action event is an execution of an Illustrator command. An action event
	can originate from the Illustrator application or a plug-in. It is normally, but
	not limited to, an evaluation or modification to Illustrator artwork. Adobe
	Illustrator’s Action Manager dispatches action events.

	In order for your plug-in’s action events to be recorded or played back you
	must register them with the Action Manager and specify the parameters
	associated with your action event. In addition to registering you actions,
	your plug-in must respond to the Action Manager when it tells you to play
	your plug-in’s action event.

	The Action Manager suite is exported by a plug-in. It may be disabled by removing
	the Action Manager plug-in. Because of this, during startup you must always check for
	the presence of the AIActionManager suite pointer before calling any Action Manager
	functions.
 */

typedef struct 
{
	/**	This function registers a plug-in’s action event with the Adobe Illustrator
		application. This is necessary for your plug-in event to be recognized by the
		Actions palette. This is the first step in "actionizing" your plug-in. You
		should call this during the startup procedure of your plug-in.

		eventName is a C style string which will identify your plug-in event internally,
		it is not to be localized. You could use the name of your plug-in.
		
		localizedName is a C style string which is shown in the Adobe Illustrator Actions
		Palette. This should be localized.
		
		callback is currently not being used for plug-ins; you should always pass a
		null value.
		
		SPPluginRef is the plug-in registering the event (usually message.d->self).
		
		AIActionUserData must be allocated by your plug-in (using SPBlocks.h) at startup
		This is passed back to you: 1. using GetActionEventUserData 2. Inside the
		DoActionMessage.
		
		parameters is reference to a Type Parameter Block (TPB). A TPB contains keys
		which describe the parameter block of your plug-in. Your plug-in must create an
		AIActionParamTypeRef, fill it with keys that describe your parameter block,
		pass it to RegisterActionEvent and finally, destroy it. */
	ASErr ASAPI (*RegisterActionEvent)(const char *eventName, const char *localizedName, 
									   int version, int flag,
									   AIActionCallbackProc callback,
									   SPPluginRef plugin, 
									   AIActionUserData userData,
									   AIActionParamTypeRef parameters);

	/**	Pass the eventName (which is the internal id of your event) to test 
			if it has been registered */
	ASBoolean ASAPI (*IsActionEventRegistered)(const char *eventName);
	
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventLocalizedName)(const char *eventName, char *localizedName);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventVersion)(const char *eventName, int *version);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventFlag)(const char *eventName, int *flag);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventCallbackProc)(const char *eventName, AIActionCallbackProc *callback);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventPluginRef)(const char *eventName, SPPluginRef *pluginRef);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventUserData)(const char *eventName, AIActionUserData *userData);
	/**	Set the AIActionUserData which was allocated by your plug-in during startup. */	
	ASErr ASAPI (*SetActionEventUserData)(const char *eventName, AIActionUserData userData);
	/**	Given an event name registered by RegisterActionEvent this function returns the
		specified value associated with the event. */
	ASErr ASAPI (*GetActionEventParamType)(const char *eventName, AIActionParamTypeRef *param);

	/** Idle */
	ASErr ASAPI (*Idle)(void);
	/** Set the idle procedure for actions. */
	ASErr ASAPI (*SetActionIdleProc)(AIActionIdleProc idleProc);
	/** Get the idle procedure for actions. */
	ASErr ASAPI (*GetActionIdleProc)(AIActionIdleProc *idleProc);

	/** Set ActionSet Folder. */
	ASErr ASAPI (*SetActionSetFolder)(SPPlatformFileSpecification path);
	/** Get ActionSet Folder. */
	ASErr ASAPI (*GetActionSetFolder)(SPPlatformFileSpecification *path);

	/** A Type Parameter Block is used to describe the parameter block of your
		action event. The TPB does not contain actual values, just type descriptors. Once
		you create a TPB using this function, you add keys to it which represent data
		types. These data types usually coincide with information that is gathered
		when your plug-in presents a modal dialog to the user.

		In order for your plug-in to be compatible with Illustrator’s Actions Palette
		you must first register it with the Action Manager. The normal procedure for
		registering your plug-in with the Action Manager is as follows:
		
		- create a TPB during startup (using AINewActionParamType)
		- fill the TPB with keys (using AIActionSetTypeKey)
		- pass the TPB to RegisterActionEvent
		- destroy the TPB (using AIDeleteActionParamType) */
	ASErr ASAPI (*AINewActionParamType)(AIActionParamTypeRef *param);
	/** Once a Type Parameter Block (TPB) has been used you must delete it using
		this function. You do not need to keep a reference to it because Illustrator
		will maintain a copy of it and pass it back to you when you need it. */
	ASErr ASAPI (*AIDeleteActionParamType)(AIActionParamTypeRef param);

	/** This function is used to examine the contents of a TPB. Since each TPB
		contains one or more type keys, you could use this function to index directly
		or iterate through all of the type keys. If you want to iterate through all of
		them you could first call AIActionGetTypeCount.

		The key returned from this function is of type ActionParamKeyID which is
		really a long. The convention is 4 character longs which describe the
		parameter. */
	ASErr ASAPI (*AIActionGetTypeKey)(AIActionParamTypeRef param, ASUInt32 index, ActionParamKeyID *key);
	
	/** Given a TPB and a key (a four character long), this function returns whether
		that TPB contains such a key.*/		
	ASErr ASAPI (*AIActionHasTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, ASBoolean *hasKey);

	/** Given a TPB this function returns the number of keys it contains. Will likely
		be used along with AIActionGetTypeKey( ) to enumerate and access all the
		keys associated with one TPB. */
	ASErr ASAPI (*AIActionGetTypeCount)(AIActionParamTypeRef param, ASUInt32 *count);

	/** This function associates a type key with a Type Parameter Block (TPB). The
		TPB must first be created using AINewActionParamType. The "key" parameter
		is a four character long which will identify the key, the "name" parameter
		is the name of the parameter which will appear in the Actions Palette
		(this is localizable), the "type" parameter is the data type of the key, and
		the "show" parameter specifies if this type will be shown in the Actions
		Palette.

		If 'key' already exists, sets new values for 'name', 'type', and 'show' */
	ASErr ASAPI (*AIActionSetTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, const char* name, ActionParamTypeID type, ASBoolean show);

	/** Given a TPB and a key, this function returns the localized name which is
		associated with the key. The localized name is specified in the
		AIActionSetTypeKey function. This is the text which will appear in the
		Action Manager palette after an action has been recorded. */		
	ASErr ASAPI (*AIActionGetName)(AIActionParamTypeRef param, ActionParamKeyID key, char* value);
	/** Given a TPB and a type key, this function returns the data type which is associated
		with that key. The data type is returned as an ActionParamTypeID */
	ASErr ASAPI (*AIActionGetType)(AIActionParamTypeRef param, ActionParamKeyID key, ActionParamTypeID* value);
	
	/** Given a TPB and a type key, this function returns the "show" flag. The
		"show" flag is set in AIActionSetTypeKey. It specifies whether a particular
		type will be shown in the Actions Palette. Note that this function returns an
		ASBoolean and not an ASErr. */		
	ASBoolean ASAPI (*AIActionTypeIsShow)(AIActionParamTypeRef param, ActionParamKeyID key);


	/** Wrapper functions for access the suite in Action Palette. Currently, third party plug-ins
		have no use for this function. */
	ASErr ASAPI (*AcquirePalette)(void);
	/** Wrapper functions for access the suite in Action Palette. Currently, third party plug-ins
		have no use for this function. */
	ASErr ASAPI (*ReleasePalette)(void);
	
	/** Your plug-in should call this when it executes an event it has registered
		and the application is in record mode. This function notifies the Actions Palette
		that someone has executed your plug-in event. You should call this only when you
		have determined that the user is in Record Mode. You can determine if a user
		is in Record Mode by calling InRecordMode.

		The "eventName" parameter is a C style string which identifies your action
		event. Normally you would pass your plug-in name preceded by your
		company name. This name must be unique to all other plug-ins which Illustrator
		loads. An example of one of Illustrator’s event names is
		adobe_saveDocumentAs. Note that this is not the name that appears in the
		Actions Palette, it is an internal identifier.

		The "dialogStatus" parameter specifies whether, by default, the dialog will
		appear when the action is played back. The dialog status is visually represented
		with a dialog icon to the left of the event name in the Actions
		Palette.

		The "parameters" parameter is a Value Parameter Block or (VPB.) This struct
		contains the values which were used during the action event. Normally the
		values coincide with values entered by the user in a dialog. If your action
		event does not have any values, pass NULL. The VPB is created by calling
		AINewActionParamValue. The VPB contains values which correspond to
		the type specified in the TPB.

		After this function is called, your action event will be displayed in the
		Actions Palette. Under your action event will be the parameter list which
		was specified in the Type Parameter Block. */
	ASErr ASAPI (*RecordActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	/** This function plays back an action event which you specify by the eventName
		parameter. The event name is the internal identifier for an action event that
		either a plug-in or the Illustrator application provides.

		'eventName' is a C style string which identifies the event

		'dialogStatus' specifies whether to show a dialog

		'parameters' is the VPB. You need to create and fill this before you call PlayActionEvent.

		In addition to playing back a plug-in’s action event, you can use this function
		to play back any of Illustrator’s action events. Most of Illustrator’s menu
		commands and plug-ins have event names. The event names along with their
		corresponding parameter types are documented in individual header files. */
	ASErr ASAPI (*PlayActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	/** Note that this function returns an ASBoolean and not an ASErr.
		When a new action is first created or whenever the record button is pressed
		in the Actions Palette, the user is in record mode. Once in record mode, the
		user’s actions will be recorded into the Actions Palette.

		If your plug-in registers an action event at startup, you are responsible for
		recording your action event and any associated parameters whenever the
		user is in record mode.

		This function is often used within a conditional statement during the normal
		execution of a plug-in. For example:
		@code
		// If in record mode, we must record the event
		if (sAIActionManager && sAIActionManager->InRecordMode()) {
			// create a VPB
			// load the VPB with values
			// record the action event
			// delete the VPB
		}
		@endcode
	*/
	ASBoolean ASAPI (*InRecordMode)(void);

	/** Currently, third party plug-ins have no use for this function. Note that this
		function returns an ASBoolean and not an ASErr. */		
	ASBoolean ASAPI (*InInsertMenuItemState)(void);

	/** Currently, third party plug-ins have no use for this function. */		
	ASErr ASAPI (*ActivateInsertMennuItemDialog)(void);

	/** Set the localized name of the current command. */
	ASErr ASAPI (*SetCurrentCommandLocalizedName)(const char *localizedName);

	/** Executes the command associted with a function key + modifier key combination. */
	ASErr ASAPI (*DoFunctionKey)(int fkey, unsigned long modifier);
	
	/** A Value Parameter Block contains values associated with an action event.
		Once you create a VPB using this function, you add key/value pairs to it
		which contain the data which is associated with your action event. This data
		coincides with the data types described in the Type Parameter Block (TPB.)
		This data usually coincides with information that is gathered when your
		plug-in presents a dialog to the user.

		When your plug-in is executing and the user is in record mode, you must
		record your plug-in’s action event. You do this by:
		- Creating a VPB
		- Loading the VPB with values (usually from user input via a dialog)
		- Passing the VPB to RecordActionEvent
		- Deleting the VPB */
	ASErr ASAPI (*AINewActionParamValue)(AIActionParamValueRef *param);
	/** Once a Value Parameter Block (VPB) has been used you must delete it using
		this function. You do not need to keep a reference to it because Illustrator
		will maintain a copy of it and pass it back to you when you need it. */
	ASErr ASAPI (*AIDeleteActionParamValue)(AIActionParamValueRef param);

	/** This function is used to examine the contents of a VPB. Since each VPB
		contains one or more value keys, you could use this function to index
		directly or iterate through all of the value keys. If you want to iterate
		through all of them you could first call AIActionGetValueCount.

		The key returned from this function is of type ActionParamKeyID which is
		really a long. The convention is 4 character longs which describe the parameter.

		Once you have the key you could then extract the value associated with that
		key by using the appropriate accessor functions such as AIActionGetInteger. */	
	ASErr ASAPI (*AIActionGetValueKey)(AIActionParamValueRef param, ASUInt32 index, ActionParamKeyID *key);

	/** Given a VPB and a key (a four character long), this function returns whether
		that VPB contains such a key. */		
	ASErr ASAPI (*AIActionHasValueKey)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean *hasKey);

	/** Given a VPB this function returns the number of keys it contains. Will likely
		be used along with AIActionGetValueKey and the various accessor functions
		to enumerate and access all the key/value pairs associated with one
		VPB. */
	ASErr ASAPI (*AIActionGetValueCount)(AIActionParamValueRef param, ASUInt32 *count);
	
	/* Given a VPB and a key returns the type of the value associated with the key. */		
	ASErr ASAPI (*AIActionGetValueType)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamTypeID *type);
	
	/** Given a VPB and a key returns the value of the specified type associated with the key */
	ASErr ASAPI (*AIActionGetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ASInt32* value);
	/** Given a VPB and a key sets the value associated with the key to the given value */
	ASErr ASAPI (*AIActionSetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ASInt32 value);

	/** Given a VPB and a key returns the value of the specified type associated with the key */
	ASErr ASAPI (*AIActionGetReal)(AIActionParamValueRef param, ActionParamKeyID key, ASReal* value);
	/** Given a VPB and a key sets the value associated with the key to the given value */
	ASErr ASAPI (*AIActionSetReal)(AIActionParamValueRef param, ActionParamKeyID key, ASReal value);

	/** Given a VPB and a key this function returns the real value associated with
		that key. Unit real types are special in that when displayed in the Actions
		Palette, the values are appended by unit labels. */
	ASErr ASAPI (*AIActionGetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID* unit, ASReal* value);
	/** Given a VPB and a key this function returns the real value associated with
		that key. Unit real types are special in that when displayed in the Actions
		Palette, the values are append by unit labels. */
	ASErr ASAPI (*AIActionSetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID unit, ASReal value);

	/** Given a VPB and a key returns the value of the specified type associated with the key */
	ASErr ASAPI (*AIActionGetString)(AIActionParamValueRef param, ActionParamKeyID key, char* value);
	/** Given a VPB and a key sets the value associated with the key to the given value */
	ASErr ASAPI (*AIActionSetString)(AIActionParamValueRef param, ActionParamKeyID key, const char* value);

	/** Given a VPB and a key returns the value of the specified type associated with the key */
	ASErr ASAPI (*AIActionGetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean* value);
	/** Given a VPB and a key sets the value associated with the key to the given value */
	ASErr ASAPI (*AIActionSetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean value);

	/** Given a VPB and a key this function returns the enumerated value associated
		with that key. Pass the name of the enumeration as the name parameter.
		This name is the name shown in the Actions Palette. This is a way to keep
		track of the enumeration value as well as present the user with a meaningful
		name. */
	ASErr ASAPI (*AIActionGetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  char* name, ASInt32* value);
	/** Given a VPB and a key this function sets the enumerated value associated
		with that key. Pass the name of the enumeration as the name parameter.
		This name will be shown in the Actions Palette. This is a way to keep track of
		the enumeration value as well as present the user with a meaningful name. */
	ASErr ASAPI (*AIActionSetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  const char* name, ASInt32 value);

	/** Given a VPB and a key sets the value associated with the key to the given value */
	ASErr ASAPI (*AIActionSetRawDataBytes)(AIActionParamValueRef param, ActionParamKeyID key,  ASUInt32 size, const char* value);		
	/** Given a VPB and a key returns the size of the raw data associated with the key */
	ASErr ASAPI (*AIActionGetRawDataSize)(AIActionParamValueRef param, ActionParamKeyID key,  ASUInt32* size);
	/** Given a VPB and a key returns the value of the specified type associated with the key */
	ASErr ASAPI (*AIActionGetRawData)(AIActionParamValueRef param, ActionParamKeyID key, char* value);

	ActionValueVisibility ASAPI (*AIActionValueGetVisibility)(AIActionParamValueRef param, ActionParamKeyID key);
	ASErr ASAPI (*AIActionValueSetVisibility)(AIActionParamValueRef param, ActionParamKeyID key, ActionValueVisibility value);

	ASErr ASAPI (*UndoLastTransaction)();
	ASErr ASAPI (*RedoLastTransaction)();

	ASErr ASAPI (*IgnoreRecording)(ASBoolean ignore);

} AIActionManagerSuite2;


#include "AIHeaderEnd.h"

#endif
