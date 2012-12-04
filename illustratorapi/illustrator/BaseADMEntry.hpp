#ifndef __BaseADMEntry__
#define __BaseADMEntry__
/***********************************************************************/
/*                                                                     */
/* BaseADMEntry.hpp                                                    */
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

#ifndef __IADMEntry_hpp__
#include "IADMEntry.hpp"
#endif

#include "IADMList.hpp"
#include "ASTypes.h"
#include "IADMDrawer.hpp"
#include "IADMTracker.hpp"
#include "IADMNotifier.hpp"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

// BaseADMEntry, the original class, supported specific versions of the ADMDrawer, ADMTracker and ADMNotifier
// suites.  BaseADMEntryClass is a new templated implementation that allows a client to specify any required
// version of the IADM* suite in the virtual functions.
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
class BaseADMEntryClass : public IADMEntry
{
private:
	static ASErr ASAPI InitProc(ADMEntryRef entry);
	static void ASAPI DrawProc(ADMEntryRef entry, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMEntryRef entry, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMEntryRef entry, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMEntryRef entry);

protected:
//	IADMEntry fEntry;
	IADMList fList;
	ADMUserData fUserData;

	virtual ASErr Init();
	virtual void Draw(ADMDrawerClass drawer);
	virtual ASBoolean Track(ADMTrackerClass tracker);
	virtual void Notify(ADMNotifierClass notifier);

	virtual void BaseDraw(ADMDrawerClass drawer);

public:
	BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>(IADMEntry entry, ADMUserData data = NULL);
	BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>(IADMList list, ADMUserData entryUserData = NULL);
	virtual ~BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>();

	virtual ADMEntryRef Create(ADMListRef list, ADMUserData data = NULL);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();

//	IADMEntry GetEntry();

	ASErr DoInit();
};


// A typedef for the original BaseADMEntry class.  Most clients will use this.
// Understand that IADMDrawer is version 3.  IADMTracker is version 1.  IADMNotifier is version 1.
typedef BaseADMEntryClass<IADMDrawer, IADMTracker, IADMNotifier> BaseADMEntry;


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
inline void BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
inline ADMUserData BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::GetUserData()
{
	return fUserData;
}

/*
inline IADMEntry BaseADMEntryClass::GetEntry()
{
	return fEntry;
}
*/
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
inline ASErr BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::DoInit()
{
	return Init();
}


/*
 * Constructor
 */

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::BaseADMEntryClass(IADMEntry entry, ADMUserData data)
: IADMEntry(entry),
  fUserData(data),
  fList(GetList())
{
	if (fEntry && fList)
	{
		sADMEntry->SetUserData(fEntry, this);
		sADMList->SetDrawProc(fList, DrawProc);
		sADMList->SetTrackProc(fList, TrackProc);
		sADMList->SetNotifyProc(fList, NotifyProc);
		sADMList->SetDestroyProc(fList, DestroyProc);
	}
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::BaseADMEntryClass(IADMList list, ADMUserData entryUserData)
: IADMEntry((ADMEntryRef) NULL),
  fUserData(entryUserData),
  fList(list)
{
	if (fList){
		fEntry = sADMEntry->Create( fList );

		if (fEntry)
		{
			sADMEntry->SetUserData(fEntry, this);
			sADMList->SetDrawProc(fList, DrawProc);
			sADMList->SetTrackProc(fList, TrackProc);
			sADMList->SetNotifyProc(fList, NotifyProc);
			sADMList->SetDestroyProc(fList, DestroyProc);
		}
	}
}

/*
 * Destructor
 */

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::~BaseADMEntryClass()
{
	if (sADMEntry)
	{
		sADMEntry->SetUserData(fEntry, NULL);

		/* We can't do this since other entries depend on these
		   procs.

		sADMList->SetDrawProc(fList, NULL);
		sADMList->SetTrackProc(fList, NULL);
		sADMList->SetNotifyProc(fList, NULL);
		sADMList->SetDestroyProc(fList, NULL);
		*/

		sADMEntry->Destroy(*this);
	}
			
//	fEntry = NULL;
}


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
ADMEntryRef BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::Create(ADMListRef list, ADMUserData data)								
{
	fList = list;
	fUserData = data;

	if (fList)
	{
		fEntry = sADMEntry->Create( fList );

		if (fEntry)
		{
			SetUserData(this);
			sADMList->SetDrawProc(fList, DrawProc);
			sADMList->SetTrackProc(fList, TrackProc);
			sADMList->SetNotifyProc(fList, NotifyProc);
			sADMList->SetDestroyProc(fList, DestroyProc);
		}
	}

	return fEntry;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
ASErr BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::Init()
{
	return kNoErr;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::Draw(ADMDrawerClass drawer)
{
	sADMEntry->DefaultDraw(fEntry, drawer);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
ASBoolean BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::Track(ADMTrackerClass tracker)
{
	return 	sADMEntry->DefaultTrack(fEntry, tracker);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::Notify(ADMNotifierClass notifier)
{
	sADMEntry->DefaultNotify(fEntry, notifier);
}



/*
 * Static Procs that call Virtual Functions.
 */
	
template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
ASErr ASAPI BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::InitProc(ADMEntryRef entry)
{
	BaseADMEntryClass* admEntry = (BaseADMEntryClass*) sADMEntry->GetUserData(entry);
	
	admEntry->fEntry = entry;

	if (admEntry)
		return admEntry->Init();
	else
		return kBadParameterErr;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void ASAPI BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::DrawProc(ADMEntryRef entry, ADMDrawerRef drawer)
{
	BaseADMEntryClass* admEntry = (BaseADMEntryClass*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->BaseDraw(drawer);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
ASBoolean ASAPI BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::TrackProc(ADMEntryRef entry, ADMTrackerRef tracker)
{
	BaseADMEntryClass* admEntry = (BaseADMEntryClass*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		return admEntry->Track(tracker);
	else
		return false;
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void ASAPI BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::NotifyProc(ADMEntryRef entry, ADMNotifierRef notifier)
{
	BaseADMEntryClass* admEntry = (BaseADMEntryClass*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->Notify(notifier);
}

template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void ASAPI BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::DestroyProc(ADMEntryRef entry)
{
	BaseADMEntryClass* admEntry = (BaseADMEntryClass*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		delete admEntry;
}


template <class ADMDrawerClass, class ADMTrackerClass, class ADMNotifierClass>
void BaseADMEntryClass<ADMDrawerClass, ADMTrackerClass, ADMNotifierClass>::BaseDraw(ADMDrawerClass drawer)
{
	Draw(drawer);
}

#endif