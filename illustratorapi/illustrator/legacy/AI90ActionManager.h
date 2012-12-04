#ifndef __AI90ActionManager_h__
#define __AI90ActionManager_h__

/*
 *        Name:	AI90ActionManager.h
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

#include "AIActionManager.h"

#include "AIHeaderBegin.h"

/*
 * Constants
 */

#define kAI90ActionManagerSuite			kAIActionManagerSuite
#define kAIActionManagerSuiteVersion1	AIAPI_VERSION(1)
#define kAI90ActionManagerSuiteVersion	kAIActionManagerSuiteVersion1


/*
	Action Suite
 */

typedef struct 
{		
	ASErr ASAPI (*RegisterActionEvent)(const char *eventName, const char *localizedName, 
									   int version, int flag,
									   AIActionCallbackProc callback,
									   SPPluginRef plugin, 
									   AIActionUserData userData,
									   AIActionParamTypeRef parameters);

	ASBoolean ASAPI (*IsActionEventRegistered)(const char *eventName);
	
	ASErr ASAPI (*GetActionEventLocalizedName)(const char *eventName, char *localizedName);
	ASErr ASAPI (*GetActionEventVersion)(const char *eventName, int *version);
	ASErr ASAPI (*GetActionEventFlag)(const char *eventName, int *flag);
	ASErr ASAPI (*GetActionEventCallbackProc)(const char *eventName, AIActionCallbackProc *callback);
	ASErr ASAPI (*GetActionEventPluginRef)(const char *eventName, SPPluginRef *pluginRef);
	ASErr ASAPI (*GetActionEventUserData)(const char *eventName, AIActionUserData *userData);
	ASErr ASAPI (*SetActionEventUserData)(const char *eventName, AIActionUserData userData);
	ASErr ASAPI (*GetActionEventParamType)(const char *eventName, AIActionParamTypeRef *param);

	ASErr ASAPI (*Idle)(void);
	ASErr ASAPI (*SetActionIdleProc)(AIActionIdleProc idleProc);
	ASErr ASAPI (*GetActionIdleProc)(AIActionIdleProc *idleProc);

	ASErr ASAPI (*SetActionSetFolder)(SPPlatformFileSpecification path);
	ASErr ASAPI (*GetActionSetFolder)(SPPlatformFileSpecification *path);

	ASErr ASAPI (*AINewActionParamType)(AIActionParamTypeRef *param);
	ASErr ASAPI (*AIDeleteActionParamType)(AIActionParamTypeRef param);

	ASErr ASAPI (*AIActionGetTypeKey)(AIActionParamTypeRef param, ASUInt32 index, ActionParamKeyID *key);
	
	/** Given a TPB and a key (a four character long), this function returns whether
		that TPB contains such a key.*/		
	ASErr ASAPI (*AIActionHasTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, ASBoolean *hasKey);

	ASErr ASAPI (*AIActionGetTypeCount)(AIActionParamTypeRef param, ASUInt32 *count);

	ASErr ASAPI (*AIActionSetTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, const char* name, ActionParamTypeID type, ASBoolean show);

	ASErr ASAPI (*AIActionGetName)(AIActionParamTypeRef param, ActionParamKeyID key, char* value);
	ASErr ASAPI (*AIActionGetType)(AIActionParamTypeRef param, ActionParamKeyID key, ActionParamTypeID* value);
	
	ASBoolean ASAPI (*AIActionTypeIsShow)(AIActionParamTypeRef param, ActionParamKeyID key);


	ASErr ASAPI (*AcquirePalette)(void);
	ASErr ASAPI (*ReleasePalette)(void);
	
	ASErr ASAPI (*RecordActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	ASErr ASAPI (*PlayActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	ASBoolean ASAPI (*InRecordMode)(void);

	ASBoolean ASAPI (*InInsertMenuItemState)(void);

	ASErr ASAPI (*ActivateInsertMennuItemDialog)(void);

	ASErr ASAPI (*SetCurrentCommandLocalizedName)(const char *localizedName);

	ASErr ASAPI (*DoFunctionKey)(int fkey, unsigned long modifier);
	
	ASErr ASAPI (*AINewActionParamValue)(AIActionParamValueRef *param);
	ASErr ASAPI (*AIDeleteActionParamValue)(AIActionParamValueRef param);

	ASErr ASAPI (*AIActionGetValueKey)(AIActionParamValueRef param, ASUInt32 index, ActionParamKeyID *key);

	ASErr ASAPI (*AIActionHasValueKey)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean *hasKey);

	ASErr ASAPI (*AIActionGetValueCount)(AIActionParamValueRef param, ASUInt32 *count);
	
	ASErr ASAPI (*AIActionGetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ASInt32* value);
	ASErr ASAPI (*AIActionSetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ASInt32 value);

	ASErr ASAPI (*AIActionGetReal)(AIActionParamValueRef param, ActionParamKeyID key, ASReal* value);
	ASErr ASAPI (*AIActionSetReal)(AIActionParamValueRef param, ActionParamKeyID key, ASReal value);

	ASErr ASAPI (*AIActionGetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID* unit, ASReal* value);
	ASErr ASAPI (*AIActionSetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID unit, ASReal value);

	ASErr ASAPI (*AIActionGetString)(AIActionParamValueRef param, ActionParamKeyID key, char* value);
	ASErr ASAPI (*AIActionSetString)(AIActionParamValueRef param, ActionParamKeyID key, const char* value);

	ASErr ASAPI (*AIActionGetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean* value);
	ASErr ASAPI (*AIActionSetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean value);

	ASErr ASAPI (*AIActionGetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  char* name, ASInt32* value);
	ASErr ASAPI (*AIActionSetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  const char* name, ASInt32 value);

	ASErr ASAPI (*AIActionSetRawDataBytes)(AIActionParamValueRef param, ActionParamKeyID key,  ASUInt32 size, const char* value);		
	ASErr ASAPI (*AIActionGetRawDataSize)(AIActionParamValueRef param, ActionParamKeyID key,  ASUInt32* size);
	ASErr ASAPI (*AIActionGetRawData)(AIActionParamValueRef param, ActionParamKeyID key, char* value);

	ASErr ASAPI (*UndoLastTransaction)();
	ASErr ASAPI (*RedoLastTransaction)();

	ASErr ASAPI (*IgnoreRecording)(ASBoolean ignore);

} AIActionManagerSuite1;



#include "AIHeaderEnd.h"

#endif