/***********************************************************************/
/*                                                                     */
/* ADMHierarchyListOld.h                                               */
/* Old versions of ADM Hierarchy List Suite                            */
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

#ifndef __ADMHierarchyListOld__
#define __ADMHierarchyListOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMHierarchyList__
#include "ADMHierarchyList.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// =============================================================================
//		* ADM Hierarchy List Suite, version 1
// =============================================================================

#define kADMHierarchyListSuiteVersion1	1

// -----------------------------------------------------------------------------

typedef struct ADMHierarchyListSuite1
{

	// menu items

	void ADMAPI (*SetMenuID)(ADMHierarchyListRef inList, ADMInt32 inMenuResID);
	ADMInt32 ADMAPI (*GetMenuID)(ADMHierarchyListRef inList);
	
	// item dereference

	ADMItemRef ADMAPI (*GetItem)(ADMHierarchyListRef inList);
	
	// user storage
	
	void ADMAPI (*SetUserData)(ADMHierarchyListRef inList, ADMUserData inData);
	ADMUserData ADMAPI (*GetUserData)(ADMHierarchyListRef inList);

	// item initialization proc

	void ADMAPI (*SetInitProc)(ADMHierarchyListRef inList, ADMListEntryInitProc inInitProc);

	void ADMAPI (*SetInitProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryInitProc inInitProc);

	ADMListEntryInitProc ADMAPI (*GetInitProc)(ADMHierarchyListRef inList);

	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMHierarchyListRef inList, ADMListEntryDrawProc inDrawProc);

	void ADMAPI (*SetDrawProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDrawProc inDrawProc);

	ADMListEntryDrawProc ADMAPI (*GetDrawProc)(ADMHierarchyListRef inList);
	
	// item tracking proc
	
	void ADMAPI (*SetTrackProc)(ADMHierarchyListRef inList, ADMListEntryTrackProc inTrackProc);

	void ADMAPI (*SetTrackProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryTrackProc inTrackProc);

	ADMListEntryTrackProc ADMAPI (*GetTrackProc)(ADMHierarchyListRef inList);
	
	// item action mask
	
	void ADMAPI (*SetMask)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	void ADMAPI (*SetMaskRecursive)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMHierarchyListRef inEntry);

	// item notify proc
	
	void ADMAPI (*SetNotifyProc)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	void ADMAPI (*SetNotifyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	ADMListEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMHierarchyListRef inList);
	
	// user data for item notifier proc
	
	void ADMAPI (*SetNotifierData)(ADMHierarchyListRef inEntry, ADMUserData inData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMHierarchyListRef inEntry);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	void ADMAPI (*SetDestroyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	ADMListEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMHierarchyListRef inList);
	
	// item entry bounds
	
	void ADMAPI (*SetEntryWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetEntryWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetNonLeafEntryWidth)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	void ADMAPI (*SetEntryHeightRecursive)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMHierarchyListRef inList, ADMRect* rect);

	void ADMAPI (*SetNonLeafEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetNonLeafEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetNonLeafEntryTextRect)(ADMHierarchyListRef inList, ADMRect* inRect);
	
	// item list manipulation
	
	ADMListEntryRef ADMAPI (*InsertEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	
	ADMListEntryRef ADMAPI (*GetEntry)(ADMHierarchyListRef inList, ADMInt32 inEntryID);
	ADMListEntryRef ADMAPI (*IndexEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	ADMListEntryRef ADMAPI (*FindEntry)(ADMHierarchyListRef inList, const char* inText);
	
	ADMListEntryRef ADMAPI (*PickEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	ADMListEntryRef ADMAPI (*PickLeafEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	
	ADMListEntryRef ADMAPI (*GetActiveEntry)(ADMHierarchyListRef inList);
	ADMListEntryRef ADMAPI (*GetActiveLeafEntry)(ADMHierarchyListRef inList);
	
	// selection list manipulation
	
	ADMListEntryRef ADMAPI (*IndexSelectedEntry)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMHierarchyListRef inList);
	
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	
	// item hierarchy
	
	ADMListEntryRef ADMAPI (*GetParentEntry)(ADMHierarchyListRef inList);

	// coordinate system conversion

	void ADMAPI (*GetLocalRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*LocalToScreenPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*GlobalToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);
	void ADMAPI (*GlobalToLocalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	// item margin accessors

	void ADMAPI (*SetIndentationWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetIndentationWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetIndentationWidth)(ADMHierarchyListRef inList);

	void ADMAPI (*SetLocalLeftMargin)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetLocalLeftMargin)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetGlobalLeftMargin)(ADMHierarchyListRef inList);

	void ADMAPI (*SetDivided)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	void ADMAPI (*SetDividedRecursive)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	ADMBoolean ADMAPI (*GetDivided)(ADMHierarchyListRef inList);

	void ADMAPI (*SetFlags)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	void ADMAPI (*SetFlagsRecursive)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	ADMInt32 ADMAPI (*GetFlags)(ADMHierarchyListRef inList);

	// item invalidation

	void ADMAPI (*Invalidate)(ADMHierarchyListRef inList);

	// leaf item accessors

	ADMListEntryRef ADMAPI (*IndexLeafEntry)(ADMHierarchyListRef inList, ADMInt32 inLeafItem);
	ADMInt32 ADMAPI (*GetLeafIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfLeafEntries)(ADMHierarchyListRef inList);

	// item sequence manipulation
	
	void ADMAPI (*SwapEntries)(ADMHierarchyListRef inList, ADMInt32 inFromIndex,
				ADMInt32 inToIndex);

	ADMListEntryRef ADMAPI (*InsertGivenEntry)(ADMHierarchyListRef inList,
				ADMListEntryRef inEntry, ADMInt32 inIndex);

} ADMHierarchyListSuite1;

typedef ADMHierarchyListSuite1 ADMHierarchyListSuite;


// =============================================================================
//		* ADM Hierarchy List Suite, version 2
// =============================================================================

#define kADMHierarchyListSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMHierarchyListSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// menu items

	void ADMAPI (*SetMenuID)(ADMHierarchyListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	ADMInt32 ADMAPI (*GetMenuID)(ADMHierarchyListRef inList);
	
	// item dereference
	
	ADMItemRef ADMAPI (*GetItem)(ADMHierarchyListRef inList);

	// user storage
	
	void ADMAPI (*SetUserData)(ADMHierarchyListRef inList, ADMUserData inData);
	ADMUserData ADMAPI (*GetUserData)(ADMHierarchyListRef inList);

	// item initialization proc

	void ADMAPI (*SetInitProc)(ADMHierarchyListRef inList, ADMListEntryInitProc inInitProc);

	void ADMAPI (*SetInitProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryInitProc inInitProc);

	ADMListEntryInitProc ADMAPI (*GetInitProc)(ADMHierarchyListRef inList);

	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMHierarchyListRef inList, ADMListEntryDrawProc inDrawProc);

	void ADMAPI (*SetDrawProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDrawProc inDrawProc);

	ADMListEntryDrawProc ADMAPI (*GetDrawProc)(ADMHierarchyListRef inList);
	
	// item tracking proc
	
	void ADMAPI (*SetTrackProc)(ADMHierarchyListRef inList, ADMListEntryTrackProc inTrackProc);

	void ADMAPI (*SetTrackProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryTrackProc inTrackProc);

	ADMListEntryTrackProc ADMAPI (*GetTrackProc)(ADMHierarchyListRef inList);

	// item action mask
	
	void ADMAPI (*SetMask)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	void ADMAPI (*SetMaskRecursive)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMHierarchyListRef inEntry);

	// item notify proc
	
	void ADMAPI (*SetNotifyProc)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	void ADMAPI (*SetNotifyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	ADMListEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMHierarchyListRef inList);

	// user data for item notifier proc
	
	void ADMAPI (*SetNotifierData)(ADMHierarchyListRef inEntry, ADMUserData inData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMHierarchyListRef inEntry);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	void ADMAPI (*SetDestroyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	ADMListEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMHierarchyListRef inList);

	// item entry bounds
	
	void ADMAPI (*SetEntryWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetEntryWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetNonLeafEntryWidth)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	void ADMAPI (*SetEntryHeightRecursive)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*SetNonLeafEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetNonLeafEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetNonLeafEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);
	
	// item list manipulation
	
	ADMListEntryRef ADMAPI (*InsertEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	
	ADMListEntryRef ADMAPI (*GetEntry)(ADMHierarchyListRef inList, ADMInt32 inEntryID);
	ADMListEntryRef ADMAPI (*IndexEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	ADMListEntryRef ADMAPI (*FindEntry)(ADMHierarchyListRef inList, const char* inText);
	
	ADMListEntryRef ADMAPI (*PickEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	ADMListEntryRef ADMAPI (*PickLeafEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	// Note: PickExpandedEntry is not needed because PickLeafEntry returns non-leaf entries as well.
	
	ADMListEntryRef ADMAPI (*GetActiveEntry)(ADMHierarchyListRef inList);
	ADMListEntryRef ADMAPI (*GetActiveLeafEntry)(ADMHierarchyListRef inList);
	
	// selection list manipulation
	
	ADMListEntryRef ADMAPI (*IndexSelectedEntry)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMHierarchyListRef inList);
	
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	
	// item hierarchy
	
	ADMListEntryRef ADMAPI (*GetParentEntry)(ADMHierarchyListRef inList);

	// coordinate system conversion

	void ADMAPI (*GetLocalRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*LocalToScreenPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*GlobalToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);
	void ADMAPI (*GlobalToLocalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	// item margin accessors

	void ADMAPI (*SetIndentationWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetIndentationWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetIndentationWidth)(ADMHierarchyListRef inList);

	void ADMAPI (*SetLocalLeftMargin)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetLocalLeftMargin)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetGlobalLeftMargin)(ADMHierarchyListRef inList);

	void ADMAPI (*SetDivided)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	void ADMAPI (*SetDividedRecursive)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	ADMBoolean ADMAPI (*GetDivided)(ADMHierarchyListRef inList);

	void ADMAPI (*SetFlags)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	void ADMAPI (*SetFlagsRecursive)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	ADMInt32 ADMAPI (*GetFlags)(ADMHierarchyListRef inList);

	// item invalidation

	void ADMAPI (*Invalidate)(ADMHierarchyListRef inList);

	// leaf item accessors

	ADMListEntryRef ADMAPI (*IndexLeafEntry)(ADMHierarchyListRef inList, ADMInt32 inLeafItem);
	ADMInt32 ADMAPI (*GetLeafIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfLeafEntries)(ADMHierarchyListRef inList);

	// item sequence manipulation
	
	void ADMAPI (*SwapEntries)(ADMHierarchyListRef inList, ADMInt32 inFromIndex,
				ADMInt32 inToIndex);

	ADMListEntryRef ADMAPI (*InsertGivenEntry)(ADMHierarchyListRef inList,
				ADMListEntryRef inEntry, ADMInt32 inIndex);

	ADMListEntryRef ADMAPI (*UnlinkEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	// item selection

	void ADMAPI (*DeselectAll)(ADMHierarchyListRef inList);

}
ADMHierarchyListSuite2;

// =============================================================================
//		* ADM Hierarchy List Suite, version 3
// =============================================================================

#define kADMHierarchyListSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMHierarchyListSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// menu items

	void ADMAPI (*SetMenuID)(ADMHierarchyListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	ADMInt32 ADMAPI (*GetMenuID)(ADMHierarchyListRef inList);
	
	// item dereference
	
	ADMItemRef ADMAPI (*GetItem)(ADMHierarchyListRef inList);

	// user storage
	
	void ADMAPI (*SetUserData)(ADMHierarchyListRef inList, ADMUserData inData);
	ADMUserData ADMAPI (*GetUserData)(ADMHierarchyListRef inList);

	// item initialization proc

	void ADMAPI (*SetInitProc)(ADMHierarchyListRef inList, ADMListEntryInitProc inInitProc);

	void ADMAPI (*SetInitProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryInitProc inInitProc);

	ADMListEntryInitProc ADMAPI (*GetInitProc)(ADMHierarchyListRef inList);

	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMHierarchyListRef inList, ADMListEntryDrawProc inDrawProc);

	void ADMAPI (*SetDrawProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDrawProc inDrawProc);

	ADMListEntryDrawProc ADMAPI (*GetDrawProc)(ADMHierarchyListRef inList);
	
	// item tracking proc
	
	void ADMAPI (*SetTrackProc)(ADMHierarchyListRef inList, ADMListEntryTrackProc inTrackProc);

	void ADMAPI (*SetTrackProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryTrackProc inTrackProc);

	ADMListEntryTrackProc ADMAPI (*GetTrackProc)(ADMHierarchyListRef inList);

	// item action mask
	
	void ADMAPI (*SetMask)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	void ADMAPI (*SetMaskRecursive)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMHierarchyListRef inEntry);

	// item notify proc
	
	void ADMAPI (*SetNotifyProc)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	void ADMAPI (*SetNotifyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	ADMListEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMHierarchyListRef inList);

	// user data for item notifier proc
	
	void ADMAPI (*SetNotifierData)(ADMHierarchyListRef inEntry, ADMUserData inData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMHierarchyListRef inEntry);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	void ADMAPI (*SetDestroyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	ADMListEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMHierarchyListRef inList);

	// item entry bounds
	
	void ADMAPI (*SetEntryWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetEntryWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetNonLeafEntryWidth)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	void ADMAPI (*SetEntryHeightRecursive)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*SetNonLeafEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetNonLeafEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetNonLeafEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);
	
	// item list manipulation
	
	ADMListEntryRef ADMAPI (*InsertEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	
	ADMListEntryRef ADMAPI (*GetEntry)(ADMHierarchyListRef inList, ADMInt32 inEntryID);
	ADMListEntryRef ADMAPI (*IndexEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	ADMListEntryRef ADMAPI (*FindEntry)(ADMHierarchyListRef inList, const char* inText);
	
	ADMListEntryRef ADMAPI (*PickEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	ADMListEntryRef ADMAPI (*PickLeafEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	
	ADMListEntryRef ADMAPI (*GetActiveEntry)(ADMHierarchyListRef inList);
	ADMListEntryRef ADMAPI (*GetActiveLeafEntry)(ADMHierarchyListRef inList);
	
	// selection list manipulation
	
	ADMListEntryRef ADMAPI (*IndexSelectedEntry)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMHierarchyListRef inList);
	
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	
	// item hierarchy
	
	ADMListEntryRef ADMAPI (*GetParentEntry)(ADMHierarchyListRef inList);

	// coordinate system conversion

	void ADMAPI (*GetLocalRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*LocalToScreenPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*GlobalToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);
	void ADMAPI (*GlobalToLocalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	// item margin accessors

	void ADMAPI (*SetIndentationWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetIndentationWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetIndentationWidth)(ADMHierarchyListRef inList);

	void ADMAPI (*SetLocalLeftMargin)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetLocalLeftMargin)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetGlobalLeftMargin)(ADMHierarchyListRef inList);

	void ADMAPI (*SetDivided)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	void ADMAPI (*SetDividedRecursive)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	ADMBoolean ADMAPI (*GetDivided)(ADMHierarchyListRef inList);

	void ADMAPI (*SetFlags)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	void ADMAPI (*SetFlagsRecursive)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	ADMInt32 ADMAPI (*GetFlags)(ADMHierarchyListRef inList);

	// item invalidation

	void ADMAPI (*Invalidate)(ADMHierarchyListRef inList);

	// leaf item accessors

	ADMListEntryRef ADMAPI (*IndexLeafEntry)(ADMHierarchyListRef inList, ADMInt32 inLeafItem);
	ADMInt32 ADMAPI (*GetLeafIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfLeafEntries)(ADMHierarchyListRef inList);

	// item sequence manipulation
	
	void ADMAPI (*SwapEntries)(ADMHierarchyListRef inList, ADMInt32 inFromIndex,
				ADMInt32 inToIndex);

	ADMListEntryRef ADMAPI (*InsertGivenEntry)(ADMHierarchyListRef inList,
				ADMListEntryRef inEntry, ADMInt32 inIndex);

	ADMListEntryRef ADMAPI (*UnlinkEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	// item selection

	void ADMAPI (*DeselectAll)(ADMHierarchyListRef inList);
	
	// customizing appearance
	
	void ADMAPI (*SetBackgroundColor)(ADMHierarchyListRef inList,
				ADMColor inColor);

	// expanded item accessors

	ADMListEntryRef ADMAPI (*IndexExpandedEntry)(ADMHierarchyListRef inList, ADMInt32 inExpandedItem);
	ADMInt32 ADMAPI (*GetExpandedIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfExpandedEntries)(ADMHierarchyListRef inList);

} ADMHierarchyListSuite3;

// =============================================================================
//		* ADM Hierarchy List Suite, version 4
// =============================================================================

#define kADMHierarchyListSuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMHierarchyListSuite4
{

	// *** This suite is FROZEN for changes.
	// *** It shipped with Illustrator 10

	// menu items

	void ADMAPI (*SetMenuID)(ADMHierarchyListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	ADMInt32 ADMAPI (*GetMenuID)(ADMHierarchyListRef inList);
	
	// item dereference
	
	ADMItemRef ADMAPI (*GetItem)(ADMHierarchyListRef inList);

	// user storage
	
	void ADMAPI (*SetUserData)(ADMHierarchyListRef inList, ADMUserData inData);
	ADMUserData ADMAPI (*GetUserData)(ADMHierarchyListRef inList);

	// item initialization proc

	void ADMAPI (*SetInitProc)(ADMHierarchyListRef inList, ADMListEntryInitProc inInitProc);

	void ADMAPI (*SetInitProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryInitProc inInitProc);

	ADMListEntryInitProc ADMAPI (*GetInitProc)(ADMHierarchyListRef inList);

	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMHierarchyListRef inList, ADMListEntryDrawProc inDrawProc);

	void ADMAPI (*SetDrawProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDrawProc inDrawProc);

	ADMListEntryDrawProc ADMAPI (*GetDrawProc)(ADMHierarchyListRef inList);
	
	// item tracking proc
	
	void ADMAPI (*SetTrackProc)(ADMHierarchyListRef inList, ADMListEntryTrackProc inTrackProc);

	void ADMAPI (*SetTrackProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryTrackProc inTrackProc);

	ADMListEntryTrackProc ADMAPI (*GetTrackProc)(ADMHierarchyListRef inList);

	// item action mask
	
	void ADMAPI (*SetMask)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	void ADMAPI (*SetMaskRecursive)(ADMHierarchyListRef inEntry, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMHierarchyListRef inEntry);

	// item notify proc
	
	void ADMAPI (*SetNotifyProc)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	void ADMAPI (*SetNotifyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryNotifyProc inNotifyProc);

	ADMListEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMHierarchyListRef inList);

	// user data for item notifier proc
	
	void ADMAPI (*SetNotifierData)(ADMHierarchyListRef inEntry, ADMUserData inData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMHierarchyListRef inEntry);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	void ADMAPI (*SetDestroyProcRecursive)(ADMHierarchyListRef inList,
				ADMListEntryDestroyProc inDestroyProc);

	ADMListEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMHierarchyListRef inList);

	// item entry bounds
	
	void ADMAPI (*SetEntryWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetEntryWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetNonLeafEntryWidth)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryHeight)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	void ADMAPI (*SetEntryHeightRecursive)(ADMHierarchyListRef inList, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMHierarchyListRef inList);
	
	void ADMAPI (*SetEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*SetNonLeafEntryTextRect)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*SetNonLeafEntryTextRectRecursive)(ADMHierarchyListRef inList, const ADMRect* inRect);
	void ADMAPI (*GetNonLeafEntryTextRect)(ADMHierarchyListRef inList, ADMRect* outRect);
	
	// item list manipulation
	
	ADMListEntryRef ADMAPI (*InsertEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	void ADMAPI (*RemoveEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	
	ADMListEntryRef ADMAPI (*GetEntry)(ADMHierarchyListRef inList, ADMInt32 inEntryID);
	ADMListEntryRef ADMAPI (*IndexEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);
	ADMListEntryRef ADMAPI (*FindEntry)(ADMHierarchyListRef inList, const char* inText);
	
	ADMListEntryRef ADMAPI (*PickEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	ADMListEntryRef ADMAPI (*PickLeafEntry)(ADMHierarchyListRef inList, const ADMPoint* inPoint);
	
	ADMListEntryRef ADMAPI (*GetActiveEntry)(ADMHierarchyListRef inList);
	ADMListEntryRef ADMAPI (*GetActiveLeafEntry)(ADMHierarchyListRef inList);
	
	// selection list manipulation
	
	ADMListEntryRef ADMAPI (*IndexSelectedEntry)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);

	ADMListEntryRef ADMAPI (*IndexUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList,
				ADMInt32 inSelectionIndex);
	
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMHierarchyListRef inList);
	
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfAllSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*NumberOfUnNestedSelectedEntriesInHierarchy)(ADMHierarchyListRef inList);
	
	// item hierarchy
	
	ADMListEntryRef ADMAPI (*GetParentEntry)(ADMHierarchyListRef inList);

	// coordinate system conversion

	void ADMAPI (*GetLocalRect)(ADMHierarchyListRef inList, ADMRect* outRect);

	void ADMAPI (*LocalToScreenPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);
	void ADMAPI (*GlobalToLocalPoint)(ADMHierarchyListRef inList, ADMPoint* ioPoint);

	void ADMAPI (*LocalToGlobalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);
	void ADMAPI (*GlobalToLocalRect)(ADMHierarchyListRef inList, ADMRect* ioRect);

	// item margin accessors

	void ADMAPI (*SetIndentationWidth)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	void ADMAPI (*SetIndentationWidthRecursive)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetIndentationWidth)(ADMHierarchyListRef inList);

	void ADMAPI (*SetLocalLeftMargin)(ADMHierarchyListRef inList, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetLocalLeftMargin)(ADMHierarchyListRef inList);
	ADMInt32 ADMAPI (*GetGlobalLeftMargin)(ADMHierarchyListRef inList);

	void ADMAPI (*SetDivided)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	void ADMAPI (*SetDividedRecursive)(ADMHierarchyListRef inList, ADMBoolean inDivided);
	ADMBoolean ADMAPI (*GetDivided)(ADMHierarchyListRef inList);

	void ADMAPI (*SetFlags)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	void ADMAPI (*SetFlagsRecursive)(ADMHierarchyListRef inList, ADMInt32 inFlags);
	ADMInt32 ADMAPI (*GetFlags)(ADMHierarchyListRef inList);

	// item invalidation

	void ADMAPI (*Invalidate)(ADMHierarchyListRef inList);

	// leaf item accessors

	ADMListEntryRef ADMAPI (*IndexLeafEntry)(ADMHierarchyListRef inList, ADMInt32 inLeafItem);
	ADMInt32 ADMAPI (*GetLeafIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfLeafEntries)(ADMHierarchyListRef inList);

	// item sequence manipulation
	
	void ADMAPI (*SwapEntries)(ADMHierarchyListRef inList, ADMInt32 inFromIndex,
				ADMInt32 inToIndex);

	ADMListEntryRef ADMAPI (*InsertGivenEntry)(ADMHierarchyListRef inList,
				ADMListEntryRef inEntry, ADMInt32 inIndex);

	ADMListEntryRef ADMAPI (*UnlinkEntry)(ADMHierarchyListRef inList, ADMInt32 inIndex);

	// item selection

	void ADMAPI (*DeselectAll)(ADMHierarchyListRef inList);
	
	// customizing appearance
	
	void ADMAPI (*SetBackgroundColor)(ADMHierarchyListRef inList,
				ADMColor inColor);

	// expanded item accessors

	ADMListEntryRef ADMAPI (*IndexExpandedEntry)(ADMHierarchyListRef inList, ADMInt32 inExpandedItem);
	ADMInt32 ADMAPI (*GetExpandedIndex)(ADMHierarchyListRef inList, ADMListEntryRef inEntry);
	ADMInt32 ADMAPI (*NumberOfExpandedEntries)(ADMHierarchyListRef inList);

	// restrict item invalidation
	
	void ADMAPI (*StartMultipleItemInvalidate)(ADMHierarchyListRef inList);
	void ADMAPI (*StopMultipleItemInvalidate)(ADMHierarchyListRef inList);

} ADMHierarchyListSuite4;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

#endif
