#ifndef __BaseADMListEntry__
#define __BaseADMListEntry__
/***********************************************************************/
/*                                                                     */
/* BaseADMListEntry.hpp                                                */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1998-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Darin Tomack, 02/02/1998                                 */
/*                                                                     */
/***********************************************************************/


/*
 * Includes
 */

#ifndef __IADMListEntry_hpp__
#include "IADMListEntry.hpp"
#endif

#include "IADMHierarchyList.hpp"
#include "IADMDrawer.hpp"
#include "IADMTracker.hpp"
#include "IADMNotifier.hpp"
#include "ASTypes.h"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
class BaseADMListEntryClass : public BaseIADMListEntryClass
{
private:
	static ASErr ASAPI InitProc(ADMListEntryRef entry);
	static void ASAPI DrawProc(ADMListEntryRef entry, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMListEntryRef entry, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMListEntryRef entry, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMListEntryRef entry);

protected:
	IADMHierarchyList fHierarchyList;
	ADMUserData fUserData;

	virtual ASErr Init();
	virtual void Draw(ADMDrawerClass drawer);
	virtual ASBoolean Track(ADMTrackerClass tracker);
	virtual void Notify(ADMNotifierClass notifier);

	virtual void BaseDraw(ADMDrawerClass drawer);

public:
	BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>(BaseIADMListEntryClass entry, ADMUserData data = NULL);
	BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>(IADMHierarchyList list, ADMUserData entryUserData = NULL);
	virtual ~BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>();

	virtual ADMListEntryRef Create(ADMHierarchyListRef list, ADMUserData data = NULL);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();

	ASErr DoInit();
};


typedef BaseADMListEntryClass<IADMDrawer, IADMTracker, IADMNotifier, IADMListEntry> BaseADMListEntry;


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ADMUserData BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass,ADMNotifierClass, BaseIADMListEntryClass>::GetUserData()
{
	return fUserData;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ASErr BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass,ADMNotifierClass, BaseIADMListEntryClass>::DoInit()
{
	return Init();
}


////////////////////////////////////////
/*
 * Constructor
 */

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass,ADMNotifierClass, BaseIADMListEntryClass>::BaseADMListEntryClass(BaseIADMListEntryClass entry, ADMUserData data)
: BaseIADMListEntryClass(entry),
  fUserData(data),
  fHierarchyList(BaseIADMListEntryClass::GetList())
{
	if (BaseIADMListEntryClass::fEntry && fHierarchyList)
	{
		sADMListEntry->SetUserData(BaseIADMListEntryClass::fEntry, this);
		sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
		sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
		sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
		sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
	}
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass,ADMNotifierClass, BaseIADMListEntryClass>::BaseADMListEntryClass(IADMHierarchyList list, ADMUserData entryUserData)
: BaseIADMListEntryClass((ADMListEntryRef) NULL),
  fUserData(entryUserData),
  fHierarchyList(list)
{
	if (fHierarchyList){
		BaseIADMListEntryClass::fEntry = sADMListEntry->Create( fHierarchyList );

		if (BaseIADMListEntryClass::fEntry)
		{
			sADMListEntry->SetUserData(BaseIADMListEntryClass::fEntry, this);
			sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
			sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
			sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
			sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
		}
	}
}

/*
 * Destructor
 */

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass,ADMNotifierClass, BaseIADMListEntryClass>::~BaseADMListEntryClass()
{
	if (sADMListEntry)
	{
		sADMListEntry->SetUserData(BaseIADMListEntryClass::fEntry, NULL);

		/* We can't do this since other entries depend on these
		   procs.

		sADMHierarchyList->SetDrawProc(fHierarchyList, NULL);
		sADMHierarchyList->SetTrackProc(fHierarchyList, NULL);
		sADMHierarchyList->SetNotifyProc(fHierarchyList, NULL);
		sADMHierarchyList->SetDestroyProc(fHierarchyList, NULL);
		*/

		sADMListEntry->Destroy(*this);
	}
			
//	BaseIADMListEntryClass::fEntry = NULL;
}


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ADMListEntryRef BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::Create(ADMHierarchyListRef list, ADMUserData data)								
{
	fHierarchyList = list;
	fUserData = data;

	if (fHierarchyList)
	{
		BaseIADMListEntryClass::fEntry = sADMListEntry->Create( fHierarchyList );

		if (BaseIADMListEntryClass::fEntry)
		{
			SetUserData(this);
			sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
			sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
			sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
			sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
		}
	}

	return BaseIADMListEntryClass::fEntry;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ASErr BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::Init()
{
	return kNoErr;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::Draw(ADMDrawerClass drawer)
{
	sADMListEntry->DefaultDraw(BaseIADMListEntryClass::fEntry, drawer);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ASBoolean BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::Track(ADMTrackerClass tracker)
{
	return 	sADMListEntry->DefaultTrack(BaseIADMListEntryClass::fEntry, tracker);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::Notify(ADMNotifierClass notifier)
{
	sADMListEntry->DefaultNotify(BaseIADMListEntryClass::fEntry, notifier);
}



/*
 * Static Procs that call Virtual Functions.
 */
	
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ASErr ASAPI BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::InitProc(ADMListEntryRef entry)
{
	BaseADMListEntryClass* admEntry = (BaseADMListEntryClass*) sADMListEntry->GetUserData(entry);
	
	admEntry->fEntry = entry;

	if (admEntry)
		return admEntry->Init();
	else
		return kBadParameterErr;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void ASAPI BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::DrawProc(ADMListEntryRef entry, ADMDrawerRef drawer)
{
	BaseADMListEntryClass* admEntry = (BaseADMListEntryClass*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->BaseDraw(drawer);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
ASBoolean ASAPI BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::TrackProc(ADMListEntryRef entry, ADMTrackerRef tracker)
{
	BaseADMListEntryClass* admEntry = (BaseADMListEntryClass*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		return admEntry->Track(tracker);
	else
		return false;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void ASAPI BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::NotifyProc(ADMListEntryRef entry, ADMNotifierRef notifier)
{
	BaseADMListEntryClass* admEntry = (BaseADMListEntryClass*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->Notify(notifier);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void ASAPI BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::DestroyProc(ADMListEntryRef entry)
{
	BaseADMListEntryClass* admEntry = (BaseADMListEntryClass*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		delete admEntry;
}


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass, class BaseIADMListEntryClass>
void BaseADMListEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass, BaseIADMListEntryClass>::BaseDraw(ADMDrawerClass drawer)
{
	Draw(drawer);
}

#endif //__BaseADMListEntry__
