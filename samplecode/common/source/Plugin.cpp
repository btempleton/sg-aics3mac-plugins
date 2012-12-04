//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/Plugin.cpp $
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

#include "IllustratorSDK.h"

 #include "Plugin.hpp"

//ADM includes
#include "ADMBasic.h"

//AI includes
#include "AIRuntime.h"
#include "AppContext.hpp"

#include "plugin.h"

//standard includes
#include <string.h>
#include <stdio.h> 
#include <time.h>

//ADM suites
extern "C" ADMBasicSuite *sADMBasic;

//AI suites
extern "C" AINotifierSuite *sAINotifier;

//SP suites
extern "C" SPAccessSuite *sSPAccess;
extern "C" SPBasicSuite *sSPBasic;
extern "C" SPPluginsSuite *sSPPlugins;

// Dialog support
ASErr ASAPI	AboutPluginInitProc(ADMDialogRef dialog);
void ASAPI 	AboutDlgOKButtonProc(ADMItemRef item, ADMNotifierRef notifier);

//------------

Plugin::Plugin(SPPluginRef pluginRef)
{
	fPluginRef = pluginRef;
	fSuites = NULL;
	strncpy(fPluginName, "Plugin", kMaxStringLength);
	fLockCount = 0;
	fPluginAccess = nil;
	fLastError = kNoErr;
	fSupressDuplicateErrors = true;
	fErrorTimeout = 5;		// seconds
	fLastErrorTime = 0;
	fAppStartedNotifier = nil;
}


Plugin::~Plugin()
{
}

ASErr Plugin::StartupPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;

	if (!error)
		error = SetGlobal(this);
		
	AllocateSuiteTables();
	if (!fSuites)
		fSuites = new Suites;

	if(!fSuites)
		error = kOutOfMemoryErr;
	else
	{
		error = fSuites->Error();
		fSuites->InitializeRefCount();
	}
	
	if (error)
	{
		if (fSuites)
			delete fSuites;
		fSuites = nil;
	}

	if (!error)
	{
		if(!error)
			error = sSPPlugins->SetPluginName( message->d.self, fPluginName );
		
		if (!error)
		{
			char notifierName[kMaxStringLength];
			sprintf(notifierName, "%s App Started Notifier", fPluginName);
			error = sAINotifier->AddNotifier(message->d.self, notifierName, kAIApplicationStartedNotifier, &fAppStartedNotifier);
		}
	}
	

	if (!error)
	{
		FillSuiteTables();
	}

	return error;
}
 
ASErr Plugin::ShutdownPlugin(SPInterfaceMessage *message)
{


	if(fSuites) {
		delete fSuites;
		fSuites = nil;
	}
	
	SetGlobal(nil);

	return kNoErr;
}

ASErr Plugin::LockPlugin(ASBoolean lock)
{
	if (lock)
	{
		fLockCount++;
		if (fLockCount == 1)
			sSPAccess->AcquirePlugin(fPluginRef, &fPluginAccess );
	}
	else
	{
		fLockCount--;
		if (fLockCount == 0)
		{
			sSPAccess->ReleasePlugin( fPluginAccess );
			fPluginAccess = nil;
		}
		else if (fLockCount < 0)
			fLockCount = 0;			// Shouldn't happen, but...
	}

	return kNoErr;
}

void Plugin::GetPluginName(char *name, unsigned int maxlen)
{
#ifdef MAC_ENV
	strncpy(name, fPluginName, maxlen);
#else
	unsigned int nameSize = strlen(name);
	strncpy(name, nameSize, fPluginName, maxlen);
#endif

	if(maxlen < strlen(fPluginName))
	{
		name[maxlen] = 0;
	}
}

ASErr Plugin::About(SPInterfaceMessage *message)
{
	// Initialize the dialog
	sADMDialog->Modal(message->d.self, "About Dialog", kAboutDLOG, kADMModalDialogStyle, 
						AboutPluginInitProc, NULL, 0);
	return kNoErr;	
}

ASErr ASAPI  AboutPluginInitProc(ADMDialogRef dialog)
{
	// Call the default Init first to create the modal dialog and items.
	// By default OK is assumed to be item 1
	sADMItem->SetNotifyProc(sADMDialog->GetItem(dialog, kDlgOKButton), AboutDlgOKButtonProc);

	return kNoErr;
}

void ASAPI AboutDlgOKButtonProc(ADMItemRef item, ADMNotifierRef notifier)
{
	// This is here more by way of example, since there really isn't any
	// other reason to be overriding this handler.  The SetNotifyProc( ) call
	// above could be removed entirely.
	// Call the default Notify so the dialog knows the OK button was hit.
	sADMItem->DefaultNotify(item, notifier);
}
// end

ASBoolean Plugin::Purge()
{
	return false;
}

ASBoolean Plugin::IsReloadMsg(char *caller, char *selector)
{
	return (sSPBasic->IsEqual(caller, kSPAccessCaller ) &&
		sSPBasic->IsEqual( selector, kSPAccessReloadSelector));
}

ASBoolean Plugin::IsUnloadMsg(char *caller, char *selector)
{
	return (sSPBasic->IsEqual(caller, kSPAccessCaller ) &&
		sSPBasic->IsEqual( selector, kSPAccessUnloadSelector));
}

ASErr Plugin::Message(char *caller, char *selector, void *message)
{
	ASErr error = kUnhandledMsgErr;

	/* Sweet Pea messages */

	if (sSPBasic->IsEqual(caller, kSPAccessCaller )) 
	{
		if (sSPBasic->IsEqual( selector, kSPAccessUnloadSelector))
			error = UnloadPlugin(static_cast<SPInterfaceMessage *>(message));
			
		else if (sSPBasic->IsEqual( selector, kSPAccessReloadSelector))
			error = ReloadPlugin(static_cast<SPInterfaceMessage *>(message));
	}
	else if (sSPBasic->IsEqual(caller, kSPInterfaceCaller)) 
	{	
		if (sSPBasic->IsEqual(selector, kSPInterfaceAboutSelector))
			error = About(static_cast<SPInterfaceMessage *>(message));

		else if (sSPBasic->IsEqual(selector, kSPInterfaceStartupSelector))
			error = StartupPlugin(static_cast<SPInterfaceMessage *>(message));

		else if (sSPBasic->IsEqual(selector, kSPInterfaceShutdownSelector))
			error = ShutdownPlugin(static_cast<SPInterfaceMessage *>(message));
	}
	else if (sSPBasic->IsEqual(caller, kSPCacheCaller)) 
	{	
		if (sSPBasic->IsEqual(selector, kSPPluginPurgeCachesSelector))
		{
			if (Purge())
				error = kSPPluginCachesFlushResponse;
			else
				error = kSPPluginCouldntFlushResponse;
		}
	}
	else if (sSPBasic->IsEqual( caller, kSPPropertiesCaller ))
	{
		if (sSPBasic->IsEqual( selector, kSPPropertiesAcquireSelector ))
		{
			error = AcquireProperty((SPPropertiesMessage *) message);
		}
		else if (sSPBasic->IsEqual( selector, kSPPropertiesReleaseSelector ))
		{
			error = ReleaseProperty((SPPropertiesMessage *) message);
		}
	}

	/* Some common AI messages */

	else if (sSPBasic->IsEqual(caller, kCallerAINotify)) 
	{
		AppContext appContext(((SPInterfaceMessage *)message)->d.self);

		// Ideally we would rely upon the caller to envelop our Notify method.
		// But since we won't work right if he doesn't, do this ourselves

		AINotifierMessage *msg = (AINotifierMessage *)message;

		if (sSPBasic->IsEqual(msg->type, kAIApplicationStartedNotifier))
			error = PostStartupPlugin();

		if (!error || error == kUnhandledMsgErr)
		{
			if (sSPBasic->IsEqual( selector, kSelectorAINotify ))
				error = Notify(msg);
		}
	}
	else if (sSPBasic->IsEqual(caller, kCallerAIMenu))
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIGoMenuItem ))
		{
			error = GoMenuItem((AIMenuMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIUpdateMenuItem ))
		{
			error = UpdateMenuItem((AIMenuMessage *)message);
		}
	}
	else if (sSPBasic->IsEqual(caller, kCallerAIFilter))
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIGetFilterParameters ))
		{
			error = GetFilterParameters((AIFilterMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIGoFilter ))
		{
			error = GoFilter((AIFilterMessage *)message);
		}
	}
	else if (sSPBasic->IsEqual(caller, kCallerAIPluginGroup))
	{
		if (sSPBasic->IsEqual( selector, kSelectorAINotifyEdits ))
		{
			error = PluginGroupNotify((AIPluginGroupMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIUpdateArt ))
		{
			error = PluginGroupUpdate((AIPluginGroupMessage *)message);
		}
	}
	else if (sSPBasic->IsEqual(caller, kCallerAIFileFormat))
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIGetFileFormatParameters ))
		{
			error = GetFileFormatParameters((AIFileFormatMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIGoFileFormat ))
		{
			error = GoFileFormat((AIFileFormatMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAICheckFileFormat ))
		{
			error = CheckFileFormat((AIFileFormatMessage *)message);
		}
	}
	else if (sSPBasic->IsEqual(caller, kCallerAITool))
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIEditToolOptions ))
		{
			error = EditTool((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAITrackToolCursor ))
		{
			error = TrackToolCursor((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIToolMouseDown ))
		{
			error = ToolMouseDown((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIToolMouseDrag ))
		{
			error = ToolMouseDrag((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIToolMouseUp ))
		{
			error = ToolMouseUp((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAISelectTool ))
		{
			error = SelectTool((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIDeselectTool ))
		{
			error = DeselectTool((AIToolMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIReselectTool ))
		{
			error = ReselectTool((AIToolMessage *)message);
		}
	} 
	else if (sSPBasic->IsEqual(caller, kCallerAILiveEffect )) 
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIEditLiveEffectParameters ))
		{
			error = EditLiveEffectParameters((AILiveEffectEditParamMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAIGoLiveEffect ))
		{
			error = GoLiveEffect((AILiveEffectGoMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAILiveEffectInterpolate ))
		{
			error = LiveEffectInterpolate((AILiveEffectInterpParamMessage *)message);
		}
		else if (sSPBasic->IsEqual( selector, kSelectorAILiveEffectInputType ))
		{
			error = LiveEffectGetInputType((AILiveEffectInputTypeMessage *)message);
		}

	}
	else if (sSPBasic->IsEqual(caller, kCallerAITimer )) 
	{
		if (sSPBasic->IsEqual( selector, kSelectorAIGoTimer ))
		{
			error = Timer((AITimerMessage *)message);
		}
	}
	// We should probably handle some ADM messages too, but I don't know
	// which ones right now...

	return error;
}

ASErr Plugin::UnloadPlugin(SPInterfaceMessage *message)
{
	EmptySuiteTables();

	SetGlobal(nil);

	if (fSuites) {
		delete fSuites;
		fSuites = nil;
	}

	return kNoErr;
}


ASErr Plugin::ReloadPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;

	if (!error)
		error = SetGlobal(this);

	// fSuites should always be nil here, but check just to be sure
	if (!fSuites)
		fSuites = new Suites;

	if(!fSuites)
		error = kOutOfMemoryErr;
	else
	{
		error = fSuites->Error();
		fSuites->InitializeRefCount();
	}

	if (error)
	{
		if (fSuites)
			delete fSuites;
		fSuites = nil;
	}

	if (!error)
		FillSuiteTables();

	return error;
}


void Plugin::ReportError(ASErr error, char *caller, char *selector, void *message)
{
	if (FilterError(error))
		return;
		
	time_t now = time(nil);
	
	if (error == fLastError && fSupressDuplicateErrors &&
		now < fLastErrorTime + fErrorTimeout)
		return;

	fLastError = error;
	fLastErrorTime = now;
	DefaultError(GetPluginRef(), error);
}

void Plugin::DefaultError(SPPluginRef ref, ASErr error)
{
	if (FilterError(error))
		return;
	
	ASBoolean gotBasic = false;
	if (sADMBasic == nil) {
		if (sSPBasic == nil)
			return;
		ASErr err = sSPBasic->AcquireSuite(kADMBasicSuite, 
				kADMBasicSuiteVersion, (const void **) &sADMBasic);
		if (err || sADMBasic == nil)
			return;
		gotBasic = true;
	}

	char msg[128];
	char *m;
	m = FindMsg(ref, error, msg, sizeof(msg));
	if (m == nil)
		goto release;
	
	char mbuf[128];

	if (strlen(m) < 120) {
		char errString[10];
		if (error < 16385) {  // Then probably a plain ol' number
			sprintf(errString, "%d", error);

		} else {	// Yucky 4-byte string
			int i;
			for (i = 3; i >= 0; i--) {
				errString[i] = (char) ((unsigned long) error) & 0xff;
				error = ((unsigned long) error) >> 8;
			}
			errString[4] = '\0';
		}
		sprintf(mbuf, m, errString);
		m = mbuf;
	}

	sADMBasic->ErrorAlert(m);

release:
	if (gotBasic) {
		sSPBasic->ReleaseSuite(kADMBasicSuite, kADMBasicSuiteVersion);
		sADMBasic = nil;
	}
}

char *Plugin::FindMsg(SPPluginRef ref, ASErr error, char *buf, int len)
{
	int n = 1;
	ASErr err;
	while (1) {
		char code[10];
		err = sADMBasic->GetIndexString(ref,  
					16050, n, code, sizeof(code));
		// If we got an error, back off and use the last string, which should be
		// the default message
		if (err || code[0] == '\0') {
			if (n == 1)
				return nil;		// no error strings found
			else {
				n--;
				goto getString;
			}
		}

		if (code[0] == '-' || (code[0] >= '0' && code[0] <= '9')) {
			// This is a number, so see if it matches
			int c = atoi(code);
			if (c == error) {
				n++;
				goto getString;
			}

		} else {
			// non numeric 4 byte err code.  (e.g.) '!sel'.
			int	c, i;
			c = 0;

			for (i = 0; i < 4; i++)
				c = (c << 8) + code[i];

			if (c == error) {
				n++;
				goto getString;
			}
		}

		n += 2;
	}

getString:
	err = sADMBasic->GetIndexString(ref, 16050, n, buf, len);
	if (err || buf[0] == '\0')
		return nil;
	else
		return buf;
}

ASBoolean Plugin::FilterError(ASErr error)
{
	static ASErr errors[] = {
		kRefusePluginGroupReply,
		kWantsAfterMsgPluginGroupReply,
		kMarkValidPluginGroupReply,
		kDontCarePluginGroupReply,
		kToolCantTrackCursorErr,
		kSPPluginCachesFlushResponse,
		kSPSuiteNotFoundError,
		kSPCantAcquirePluginError,
		0
	};

	int i;
	for (i = 0; errors[i] != 0 && errors[i] != error; i++) {}
	return errors[i] != 0;
}

/* Stubbies */

ASErr Plugin::AllocateSuiteTables()
{
	return kNoErr;
}

ASErr Plugin::FillSuiteTables()
{
	return kNoErr;
}

ASErr Plugin::EmptySuiteTables()
{
	return kNoErr;
}

ASErr Plugin::PostStartupPlugin()
{
	return kNoErr;
}

ASErr Plugin::SetGlobal(Plugin *plugin)
{
	return kNoErr;
}

ASErr Plugin::AcquireProperty(SPPropertiesMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ReleaseProperty(SPPropertiesMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::Notify(AINotifierMessage *message)
{
	return kNoErr;
}

ASErr Plugin::GoMenuItem(AIMenuMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::UpdateMenuItem(AIMenuMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GetFilterParameters(AIFilterMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoFilter(AIFilterMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::PluginGroupNotify(AIPluginGroupMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::PluginGroupUpdate(AIPluginGroupMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GetFileFormatParameters(AIFileFormatMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoFileFormat(AIFileFormatMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::CheckFileFormat(AIFileFormatMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::EditTool(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::TrackToolCursor(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseDown(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseDrag(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseUp(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::SelectTool(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::DeselectTool(AIToolMessage *message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ReselectTool(AIToolMessage *message)
{
	return kNoErr;
}

ASErr Plugin::EditLiveEffectParameters(AILiveEffectEditParamMessage * message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoLiveEffect(AILiveEffectGoMessage * message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectInterpolate(AILiveEffectInterpParamMessage * message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectGetInputType(AILiveEffectInputTypeMessage * message)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::Timer(AITimerMessage* message )
{
	return kUnhandledMsgErr;
}