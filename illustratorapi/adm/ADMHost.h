/*******************************************************************************
*
* ADMHost.h -- ADM Host Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Dave Lazarony, 09 Mar 1996
*
********************************************************************************/

/** @file ADMHost.h ADM Host Suite */

#ifndef __ADMHost__
#define __ADMHost__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef	__ADMVERSION_H__
#include "ADMVersion.h"
#endif

#ifndef __SPMessageData__
#include "SPMData.h"
#endif

#ifndef __SPAccess__
#include "SPAccess.h"
#endif

#ifndef _ADMAGMTYPES_H_
#include "ADMAGMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
//	SweetPea callback interface

/** ... */
#define kADMPluginName "ADM Plugin"

/** ... */
#define kADMHostCaller "ADM Host"
/** ... */
#define kADMHostStartSelector "ADM Started"
/** ... */
#define kADMHostEndSelector "ADM Ending"

/** ... */
typedef struct ADMHostInterfaceMessage
{
	/** ... */
	SPMessageData d;
}
ADMHostInterfaceMessage;


// -----------------------------------------------------------------------------
//	GetADMVersion returns the version number ADM is compiled with. This number
//	consists of a hi word which is the major version number, and a low word which
//	is the minor revision number. Beginning with 2.30, the minor version is in
//	the low word, high byte. The low word, low byte is for branch versions.
//	
//	The macro ADM_VERSION can be used to make sure you are running the version
//	you think you are.

/** ... */
#define ADM_VERSION (0x00 | (ADMVMajor << 16) | (ADMVMinor << 8) | (ADMVBuildNumber))


// -----------------------------------------------------------------------------
//	User define procedures callbacks

/** ... */
typedef void ADMAPI (*ADMAGMCalibrationProc)(ADMAGMPort* inPort);
/** ... */
typedef void ADMAPI (*ModifyPaletteLayoutBoundsProc)(ADMRect* ioDimensions);
/** Callback procedure type for setting user interface preferences */
typedef void ADMAPI (*ShowUIPreferencesProc)(void);

// -----------------------------------------------------------------------------
//	Application context

/** ... */
typedef struct _t_ADMHostAppContextOpaque* ADMHostAppContextRef;

/** ... */
typedef ADMErr ADMAPI (*BeginHostAppContextProc)(ADMPluginRef inPlugin,
			ADMHostAppContextRef* inAppContext);
/** ... */
typedef ADMErr ADMAPI (*EndHostAppContextProc)(ADMHostAppContextRef inAppContext);

/** ... */
typedef struct ADMHostAppContextProcs
{
	/** ... */
	BeginHostAppContextProc beginAppContext;
	/** ... */
	EndHostAppContextProc endAppContext;
} 
ADMHostAppContextProcs;


// -----------------------------------------------------------------------------
//	Resource context

/** ... */
typedef struct _t_ADMResContextOpaque* ADMResContextRef;

	// This is basically the same as the SPAccess suite call GetAccessInfo().
	// Use it on Windows to supply an instance handle and on Mac if you have
	// highly managed resource chain.
/** ... */
typedef ADMErr ADMAPI (*GetResourceAccessInfoProc)(ADMPluginRef inPlugin,
			SPPlatformAccessInfo* inInfo);

	// These can be used to order the MacResource chain (e.g. bring a plug-in
	// to the top) and restore a previous order if necessary. Restore doesn't
	// necessarily have to do anything. The resContext you return to the set
	// function will be returned by restore if you need it.
/** ... */
typedef ADMErr ADMAPI (*SetResourceContextProc)(ADMPluginRef inPlugin, ADMResContextRef* inResContext);
/** ... */
typedef ADMErr ADMAPI (*RestoreResourceContextProc)(ADMResContextRef inResContext);

/** ... */
typedef struct ADMResourceAccessProcs
{
		// Supply functions getResAccessInfo() *OR* set/resetResContext() 
	/** ... */
	GetResourceAccessInfoProc getResAccessInfo;
		
	/** ... */
	SetResourceContextProc setResContext;		
	/** ... */
	RestoreResourceContextProc resetResContext;
}
ADMResourceAccessProcs;


// -----------------------------------------------------------------------------
//	Overridable defaults for text items

/** ... */
typedef struct ADMDefaultTextInfo
{

	// text

	/** ... */
	ADMInt32 maxTextLen;
	/** ... */
	ADMJustify justify;

	// numerics

	/** ... */
	ADMUnits units;
	/** ... */
	ADMInt32 numberOfDecimalPlaces;
	/** ... */
	ADMBoolean allowUnits;
	/** ... */
	ADMBoolean allowMath;

}
ADMDefaultTextInfo;


// -----------------------------------------------------------------------------

// majones: This was renamed from kMaxHostNameLen so it does not conflict with Mac OS headers
#ifndef kADMMaxHostNameLen
/** ... */
#define kADMMaxHostNameLen 256
#endif

#ifndef kADMMaxLanguageCode
/** ... */
#define kADMMaxLanguageCode 34
#endif

// =============================================================================
//		* ADM Host Suite
// =============================================================================

/** ... */
#define kADMHostSuite "ADM Host Suite"

/** ... */
#define kADMHostSuiteVersion7 7

// -----------------------------------------------------------------------------

/** ... */
struct ADMHostSuite7
{
	/** Set AGM calibration procedure. */
	void ADMAPI (*SetAGMCalibrationProc)(ADMAGMCalibrationProc inCalibrationProc);
	/** Get AGM calibration procedure. */
	ADMAGMCalibrationProc ADMAPI (*GetAGMCalibrationProc)();
	
	/** Check if a special mouse is in use. */
	ADMBoolean ADMAPI (*PointerInUse)();
	
	/** Set palette layout bounds modifier procedure */
	void ADMAPI (*SetModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc inModifyBoundsProc);
	/** Get palette layout bounds modifier procedure */
	ModifyPaletteLayoutBoundsProc ADMAPI (*GetModifyPaletteLayoutBoundsProc)();

	// host information accessors

	/** ... */
	void ADMAPI (*SetADMHostAppContextProcs)(const ADMHostAppContextProcs* inAppContextProcs);
	/** ... */
	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	
	/** ... */
	void ADMAPI (*SetADMHostAppName)(const char* inHostName);
	/** ... */
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);

	/** ... */
	void ADMAPI (*SetADMHostAppNameW)(const ADMUnicode* inHostName);
	/** ... */
	void ADMAPI (*GetADMHostAppNameW)(ADMUnicode* outHostName, ADMInt16 inMaxLength);

	/** ... */
	void ADMAPI (*SetADMResourceAccessProcs)(const ADMResourceAccessProcs* inResProcs);
	/** ... */
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);

	/** Get ADM build version. */
	ADMUInt32 ADMAPI (*GetADMVersion)();
	
	// text behaviors
	
	/** ... */
	void ADMAPI (*SetADMDefaultTextInfo)(const ADMDefaultTextInfo* inDefaultTextInfo);
	/** ... */
	void ADMAPI (*GetADMDefaultTextInfo)(ADMDefaultTextInfo* outDefaultTextInfo);

	/** ... */
	void ADMAPI (*SetADMLanguageCode)(const char* inLanguageCode);
	/** ... */
	void ADMAPI (*GetADMLanguageCode)(char* outLanguageCode);
										// max length is kADMMaxLanguageCode

	/** Test for ADM-handled keys. */
	ADMBoolean ADMAPI (*IsADMHandledKey)(const char inKeyCode);

	/** Commit active text item. */
	ADMBoolean ADMAPI (*CommitActiveTextItem)(void);

	/** Set procedure to display user interface options dialog. */
	void ADMAPI (*SetShowUIPreferencesProc)(ShowUIPreferencesProc);
};


// =============================================================================
//		* ADM MacOS Host Suite
// =============================================================================

#ifdef MAC_ENV

/** ... */
#define kADMMacHostSuite "ADM Mac Host Suite"
/** ... */
#define kADMMacHostSuiteVersion3 3

// -----------------------------------------------------------------------------

/** ... */
typedef ADMErr ADMAPI (*ADMModalEventProc)(struct EventRecord* inEvent);
/** ... */
typedef ADMErr ADMAPI (*ADMWindowActivateProc)(struct EventRecord* inEvent);

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMMacHostSuite3
{

	// event hand-off to ADM

	/** ... */
	ADMBoolean ADMAPI (*HandleADMEvent)(struct EventRecord* inEvent);

	// modal dialog event callback
	
	/** ... */
	void ADMAPI (*SetModalEventProc)(ADMModalEventProc inModalEventProc);
	/** ... */
	ADMModalEventProc ADMAPI (*GetModalEventProc)();

	// window activation
	
	/** ... */
	void ADMAPI (*ActivateWindows)(ADMBoolean inActivate);

	// activation notification
	
	/** ... */
	void ADMAPI (*SetWindowActivateProc)(ADMWindowActivateProc inWindowActivateProc);
	/** ... */
	ADMWindowActivateProc ADMAPI (*GetWindowActivateProc)();

	// null event suppression

	/** ... */
	void ADMAPI (*DisableNullEvents)();
	/** ... */
	void ADMAPI (*EnableNullEvents)();

}
ADMMacHostSuite3;	

// -----------------------------------------------------------------------------

/** ... */
#define kADMMacHostSuiteVersion kADMMacHostSuiteVersion3
/** ... */
typedef ADMMacHostSuite3 ADMMacHostSuite;

#endif


// =============================================================================
//		* ADM Windows Host Suite
// =============================================================================

#ifdef WIN_ENV

// -----------------------------------------------------------------------------
// dhearst 6/22/00
// ADMHWNDOptimizationMode enumeration:
// Used to specify a global setting in ADM (on Windows only) for how it
// handles the use of system resources. Designed to help on Win9x, where
// there is a hard limit to the number of usable system resources and Adobe
// apps just keep using more palettes...

/** ... */
typedef enum
{
	/** ... */
	kADMDoNotOptimizeHWNDUsage = 0,		// Classic ADM performance
	/** ... */
	kADMAlwaysOptimizeHWNDUsage = 1,	// Always release HWNDs for all non-visible dialogs
	/** ... */
	kADMOptimizeHWNDUsageByDialog = 2,	// Only release HWNDs for non-visible dialogs that have specifically requested optimization
	/** ... */
	kADMDummyHWNDOptimization = 0xFFFFFFFF
}
ADMHWNDOptimizationMode;


/** ... */
#define kADMWinHostSuite "ADM Win Host Suite"
/** ... */
#define kADMWinHostSuiteVersion4 4

// -----------------------------------------------------------------------------

/** ... */
typedef ADMErr ADMAPI (*ADMModalMessageProc)(ADMUInt32 inMessage, ADMUInt32 inWParam,
			ADMInt32 inLParam);

/** ... */
typedef void ADMAPI (*ADMTextFocusChangedProc)(ADMBoolean inSetFocus);

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMWinHostSuite4
{

	// This suite version (4) was introduced during development of PS 6.0/IR 3.0
	// Should be frozen when PS 6.0 ships.	// dhearst 6/20/00

	/** ... */
	ADMBoolean ADMAPI (*HandleADMMessage)(ADMWindowRef inFrameWnd, ADMUInt16 inMessage,
				ADMUInt16 inWParam, ADMInt32 inLParam);

	/** ... */
	ADMWindowRef ADMAPI (*GetCurrentOwnerWindow)();

	/** ... */
	ADMBoolean ADMAPI (*IsADMMessage)(const struct tagMSG* inMessage);

	/** ... */
	ADMWindowRef ADMAPI (*GetPlatformAppWindow)();
	/** ... */
	void ADMAPI (*SetPlatformAppWindow)(ADMWindowRef inAppWindow);

	/** ... */
	ADMModalMessageProc ADMAPI (*GetModalMessageProc)();							
	/** ... */
	void ADMAPI (*SetModalMessageProc)(ADMModalMessageProc inModalMessageProc);

	/** ... */
	ADMTextFocusChangedProc ADMAPI (*GetTextFocusChangedProc)();						
	/** ... */
	void ADMAPI (*SetTextFocusChangedProc)(ADMTextFocusChangedProc inFocusChangedProc);

	/** ... */
	void ADMAPI (*SetHWNDOptimizationMode)(ADMHWNDOptimizationMode inOptimizationMode);

	/** ... */
	void ADMAPI (*AllowHWNDOptimizationForDialog)(ADMDialogRef inDialog,
				ADMBoolean inAllowOptimization);
}
ADMWinHostSuite4;

#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMHostOld__
#ifdef MAC_ENV
#include "ADMHostOld.h"
#else
#include ".\Legacy\ADMHostOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMHost__
