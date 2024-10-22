/***********************************************************************/
/*                                                                     */
/* ADMListOld.h                                                        */
/* Old versions of ADM List Suite                                      */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMListOld__
#define __ADMListOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMList__
#include "ADMList.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// =============================================================================
//		* ADM List Suite, version 1
// =============================================================================

#define kADMListSuiteVersion1 1
#define kADMListSuiteVersion kADMListSuiteVersion1

// -----------------------------------------------------------------------------

typedef struct ADMListSuite1
{

	// menu IDs

	void ADMAPI (*SetMenuID)(ADMListRef inList, ADMInt32 inMenuResID);
	ADMInt32 ADMAPI (*GetMenuID)(ADMListRef inList);
	
	// container accessor
	
	ADMItemRef ADMAPI (*GetItem)(ADMListRef inList);
	
	// user data storage
	
	void ADMAPI (*SetUserData)(ADMListRef inList, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMListRef inList);

	// override hooks

	void ADMAPI (*SetInitProc)(ADMListRef inList, ADMEntryInitProc inInitProc);
	ADMEntryInitProc ADMAPI (*GetInitProc)(ADMListRef inList);
	
	void ADMAPI (*SetDrawProc)(ADMListRef inList, ADMEntryDrawProc inDrawProc);
	ADMEntryDrawProc ADMAPI (*GetDrawProc)(ADMListRef inList);
	
	void ADMAPI (*SetTrackProc)(ADMListRef inList, ADMEntryTrackProc inTrackProc);
	ADMEntryTrackProc ADMAPI (*GetTrackProc)(ADMListRef inList);
	
	void ADMAPI (*SetNotifyProc)(ADMListRef inList, ADMEntryNotifyProc inNotifyProc);
	ADMEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMListRef inList);
	
	void ADMAPI (*SetDestroyProc)(ADMListRef inList, ADMEntryDestroyProc inDestroyProc);
	ADMEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMListRef inList);
	
	// entry bounds accessors
	
	void ADMAPI (*SetEntryWidth)(ADMListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMListRef inList, ADMRect* outRect);
	
	// entry array accessors
	
	ADMEntryRef ADMAPI (*InsertEntry)(ADMListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMListRef inList, ADMInt32 inIndex);
	
	ADMEntryRef ADMAPI (*GetEntry)(ADMListRef inList, ADMInt32 inEntryID);
	ADMEntryRef ADMAPI (*IndexEntry)(ADMListRef inList, ADMInt32 inIndex);
	ADMEntryRef ADMAPI (*FindEntry)(ADMListRef inList, const char* inText);
	ADMEntryRef ADMAPI (*PickEntry)(ADMListRef inList, const ADMPoint* inPoint);
	
	ADMEntryRef ADMAPI (*GetActiveEntry)(ADMListRef inList);
	ADMEntryRef ADMAPI (*IndexSelectedEntry)(ADMListRef inList, ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMListRef inList);
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMListRef inList);
	
	// item action mask
	
	void ADMAPI (*SetMask)(ADMListRef inEntry, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMListRef inEntry);

	// user data storage for notifiers

	void ADMAPI (*SetNotifierData)(ADMListRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMListRef inEntry);

} ADMListSuite1;

typedef ADMListSuite1 ADMListSuite;


// =============================================================================
//		* ADM List Suite, version 2
// =============================================================================

#define kADMListSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMListSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// menu IDs

	void ADMAPI (*SetMenuID)(ADMListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	ADMInt32 ADMAPI (*GetMenuID)(ADMListRef inList);

	// container accessor
	
	ADMItemRef ADMAPI (*GetItem)(ADMListRef inList);

	// user data storage
	
	void ADMAPI (*SetUserData)(ADMListRef inList, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMListRef inList);

	// override hooks

	void ADMAPI (*SetInitProc)(ADMListRef inList, ADMEntryInitProc inInitProc);
	ADMEntryInitProc ADMAPI (*GetInitProc)(ADMListRef inList);
	
	void ADMAPI (*SetDrawProc)(ADMListRef inList, ADMEntryDrawProc inDrawProc);
	ADMEntryDrawProc ADMAPI (*GetDrawProc)(ADMListRef inList);
	
	void ADMAPI (*SetTrackProc)(ADMListRef inList, ADMEntryTrackProc inTrackProc);
	ADMEntryTrackProc ADMAPI (*GetTrackProc)(ADMListRef inList);
	
	void ADMAPI (*SetNotifyProc)(ADMListRef inList, ADMEntryNotifyProc inNotifyProc);
	ADMEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMListRef inList);
	
	void ADMAPI (*SetDestroyProc)(ADMListRef inList, ADMEntryDestroyProc inDestroyProc);
	ADMEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMListRef inList);

	// entry bounds accessors
	
	void ADMAPI (*SetEntryWidth)(ADMListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMListRef inList, ADMRect* outRect);
	
	// entry array accessors
	
	ADMEntryRef ADMAPI (*InsertEntry)(ADMListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMListRef inList, ADMInt32 inIndex);
	
	ADMEntryRef ADMAPI (*GetEntry)(ADMListRef inList, ADMInt32 inEntryID);
	ADMEntryRef ADMAPI (*IndexEntry)(ADMListRef inList, ADMInt32 inIndex);
	ADMEntryRef ADMAPI (*FindEntry)(ADMListRef inList, const char* inText);
	ADMEntryRef ADMAPI (*PickEntry)(ADMListRef inList, const ADMPoint* inPoint);
	
	ADMEntryRef ADMAPI (*GetActiveEntry)(ADMListRef inList);
	ADMEntryRef ADMAPI (*IndexSelectedEntry)(ADMListRef inList, ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMListRef inList);
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMListRef inList);

	// item action mask
	
	void ADMAPI (*SetMask)(ADMListRef inEntry, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMListRef inEntry);

	// user data storage for notifiers

	void ADMAPI (*SetNotifierData)(ADMListRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMListRef inEntry);

}
ADMListSuite2;

// =============================================================================

#define kADMListSuiteVersion3 3

// =============================================================================

typedef struct ADMListSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// menu IDs

	void ADMAPI (*SetMenuID)(ADMListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	ADMInt32 ADMAPI (*GetMenuID)(ADMListRef inList);

	// container accessor
	
	ADMItemRef ADMAPI (*GetItem)(ADMListRef inList);

	// user data storage
	
	void ADMAPI (*SetUserData)(ADMListRef inList, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMListRef inList);

	// override hooks

	void ADMAPI (*SetInitProc)(ADMListRef inList, ADMEntryInitProc inInitProc);
	ADMEntryInitProc ADMAPI (*GetInitProc)(ADMListRef inList);
	
	void ADMAPI (*SetDrawProc)(ADMListRef inList, ADMEntryDrawProc inDrawProc);
	ADMEntryDrawProc ADMAPI (*GetDrawProc)(ADMListRef inList);
	
	void ADMAPI (*SetTrackProc)(ADMListRef inList, ADMEntryTrackProc inTrackProc);
	ADMEntryTrackProc ADMAPI (*GetTrackProc)(ADMListRef inList);
	
	void ADMAPI (*SetNotifyProc)(ADMListRef inList, ADMEntryNotifyProc inNotifyProc);
	ADMEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMListRef inList);
	
	void ADMAPI (*SetDestroyProc)(ADMListRef inList, ADMEntryDestroyProc inDestroyProc);
	ADMEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMListRef inList);

	// entry bounds accessors
	
	void ADMAPI (*SetEntryWidth)(ADMListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMListRef inList, ADMRect* outRect);
	
	// entry array accessors
	
	ADMEntryRef ADMAPI (*InsertEntry)(ADMListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMListRef inList, ADMInt32 inIndex);
	
	ADMEntryRef ADMAPI (*GetEntry)(ADMListRef inList, ADMInt32 inEntryID);
	ADMEntryRef ADMAPI (*IndexEntry)(ADMListRef inList, ADMInt32 inIndex);
	ADMEntryRef ADMAPI (*FindEntry)(ADMListRef inList, const char* inText);
	ADMEntryRef ADMAPI (*PickEntry)(ADMListRef inList, const ADMPoint* inPoint);
	
	ADMEntryRef ADMAPI (*GetActiveEntry)(ADMListRef inList);
	ADMEntryRef ADMAPI (*IndexSelectedEntry)(ADMListRef inList, ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMListRef inList);
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMListRef inList);

	// item action mask
	
	void ADMAPI (*SetMask)(ADMListRef inEntry, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMListRef inEntry);

	// user data storage for notifiers

	void ADMAPI (*SetNotifierData)(ADMListRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMListRef inEntry);

	// customizing appearance
	
	void ADMAPI (*SetBackgroundColor)(ADMListRef inList, ADMColor inColor);
	
	// searching
	
	void ADMAPI (*SelectByText)(ADMListRef inList, const char* inFindText);

} ADMListSuite3;

#include "ADMHeaderEnd.h"

#endif
