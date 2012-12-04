/***********************************************************************/
/*                                                                     */
/* IADMEntry.hpp                                                       */
/* Object wrapper for ADM Entry Suite                                  */
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
/* Started by Dave Lazarony, 07/07/1998                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMEntry_hpp__
#define __IADMEntry_hpp__

/*
 * Includes
 */
 
#ifndef __ADMEntry__
#include "ADMEntry.h"
#endif

#ifndef __IADMTypes_hpp__
#include "IADMTypes.hpp"
#endif

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif


/*
 * Global Suite Pointer
 */

extern "C" ADMEntrySuite* sADMEntry;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Interface Wrapper Class
 */

class IADMEntry
{
protected:
	ADMEntryRef fEntry;

public:	
	IADMEntry();
	IADMEntry(ADMEntryRef entry);

	operator ADMEntryRef(void);
		
	void SendNotify(const char* notifierType = NULL);
	
	int GetIndex();
	
	ADMListRef GetList();
	
	void SetID(int entryID);
	int GetID();
	
	void SetUserData(ADMUserData data);
	ADMUserData GetUserData();

	void Select(ADMBoolean show = true);
	void Deselect();
	ADMBoolean IsSelected();

	void MakeInBounds();
	ADMBoolean IsInBounds();
	
	void Enable(ADMBoolean enable = true);
	void Disable();
	ADMBoolean IsEnabled();
	
	void Activate(ADMBoolean activate = true);
	void Deactivate();
	ADMBoolean IsActive();
	
	void Check(ADMBoolean check = true);
	void Uncheck();
	ADMBoolean IsChecked();
	
	void MakeSeparator(ADMBoolean separator);
	ADMBoolean IsSeparator();

	void GetLocalRect(IADMRect& localRect);
	
	void GetBoundsRect(IADMRect& boundsRect);
	
	void LocalToScreenPoint(IADMPoint& point);
	void ScreenToLocalPoint(IADMPoint& point);
	
	void LocalToScreenRect(IADMRect& rect);
	void ScreenToLocalRect(IADMRect& rect);
	
	void Invalidate();
	void Update();
	
	void SetPictureID(int pictureResID);
	int GetPictureID();
	
	void SetSelectedPictureID(int pictureResID);
	int GetSelectedPictureID();
	
	void SetDisabledPictureID(int pictureResID);
	int GetDisabledPictureID();
	
#ifdef USING_ZADM
	void SetText(const ASZString text);
	void GetText(ASZString* text);
#else
	void SetText(const char* text);
	void GetText(char* text, int maxLength = 0);
#endif
	int GetTextLength();

	ADMTimerRef CreateTimer(unsigned long milliseconds,
							ADMActionMask abortMask,
							ADMEntryTimerProc timerProc,
							ADMEntryTimerAbortProc abortProc);

	void AbortTimer(ADMTimerRef timer);
};

inline IADMEntry::IADMEntry()								
{
	fEntry = NULL;
}

inline IADMEntry::IADMEntry(ADMEntryRef entry)	
{
	fEntry = entry;
}

inline IADMEntry::operator ADMEntryRef(void)
{
	return fEntry;
}

inline void IADMEntry::SendNotify(const char* notifierType)
{
	sADMEntry->SendNotify(fEntry, notifierType);
}
	
inline int IADMEntry::GetIndex()
{
	return sADMEntry->GetIndex(fEntry);
}

inline ADMListRef IADMEntry::GetList()
{
	return sADMEntry->GetList(fEntry);
}

inline void IADMEntry::SetID(int entryID)
{
	sADMEntry->SetID(fEntry, entryID);
}

inline int IADMEntry::GetID()
{
	return sADMEntry->GetID(fEntry);
}

inline void IADMEntry::SetUserData(ADMUserData data)
{
	sADMEntry->SetUserData(fEntry, data);
}

inline ADMUserData IADMEntry::GetUserData()
{
	return sADMEntry->GetUserData(fEntry);
}

inline void IADMEntry::Select(ADMBoolean show)
{
	sADMEntry->Select(fEntry, show);
}

inline void IADMEntry::Deselect()
{
	sADMEntry->Select(fEntry, false);
}

inline ADMBoolean IADMEntry::IsSelected()
{
	return sADMEntry->IsSelected(fEntry);
}

inline void IADMEntry::MakeInBounds()
{
	sADMEntry->MakeInBounds(fEntry);
}

inline ADMBoolean IADMEntry::IsInBounds()
{
	return sADMEntry->IsInBounds(fEntry);
}

inline void IADMEntry::Enable(ADMBoolean enable)
{
	sADMEntry->Enable(fEntry, enable);
}

inline void IADMEntry::Disable()
{
	sADMEntry->Enable(fEntry, false);
}

inline ADMBoolean IADMEntry::IsEnabled()
{
	return sADMEntry->IsEnabled(fEntry);
}

inline void IADMEntry::Activate(ADMBoolean activate)
{
	sADMEntry->Activate(fEntry, activate);
}

inline void IADMEntry::Deactivate()
{
	sADMEntry->Activate(fEntry, false);
}

inline ADMBoolean IADMEntry::IsActive()
{
	return sADMEntry->IsActive(fEntry);
}

inline void IADMEntry::Check(ADMBoolean check)
{
	sADMEntry->Check(fEntry, check);
}

inline void IADMEntry::Uncheck()
{
	sADMEntry->Check(fEntry, false);
}

inline ADMBoolean IADMEntry::IsChecked()
{
	return sADMEntry->IsChecked(fEntry);
}

inline void IADMEntry::MakeSeparator(ADMBoolean separator)
{
	sADMEntry->MakeSeparator(fEntry, separator);
}

inline ADMBoolean IADMEntry::IsSeparator()
{
	return sADMEntry->IsSeparator(fEntry);
}

inline void IADMEntry::GetLocalRect(IADMRect& localRect)
{
	sADMEntry->GetLocalRect(fEntry, &localRect);
}

inline void IADMEntry::GetBoundsRect(IADMRect& boundsRect)
{
	sADMEntry->GetBoundsRect(fEntry, &boundsRect);
}

inline void IADMEntry::LocalToScreenPoint(IADMPoint& point)
{
	sADMEntry->LocalToScreenPoint(fEntry, &point);
}

inline void IADMEntry::ScreenToLocalPoint(IADMPoint& point)
{
	sADMEntry->ScreenToLocalPoint(fEntry, &point);
}

inline void IADMEntry::LocalToScreenRect(IADMRect& rect)
{
	sADMEntry->LocalToScreenRect(fEntry, &rect);
}

inline void IADMEntry::ScreenToLocalRect(IADMRect& rect)
{
	sADMEntry->ScreenToLocalRect(fEntry, &rect);
}

inline void IADMEntry::Invalidate()
{
	sADMEntry->Invalidate(fEntry);
}

inline void IADMEntry::Update()
{
	sADMEntry->Update(fEntry);
}

inline void IADMEntry::SetPictureID(int pictureResID)
{
	sADMEntry->SetPictureID(fEntry, pictureResID);
}

inline int IADMEntry::GetPictureID()
{
	return sADMEntry->GetPictureID(fEntry);
}

inline void IADMEntry::SetSelectedPictureID(int pictureResID)
{
	sADMEntry->SetSelectedPictureID(fEntry, pictureResID);
}

inline int IADMEntry::GetSelectedPictureID()
{
	return sADMEntry->GetSelectedPictureID(fEntry);
}

inline void IADMEntry::SetDisabledPictureID(int pictureResID)
{
	sADMEntry->SetDisabledPictureID(fEntry, pictureResID);
}

inline int IADMEntry::GetDisabledPictureID()
{
	return sADMEntry->GetDisabledPictureID(fEntry);
}

#ifdef USING_ZADM
inline void IADMEntry::SetText( const ASZString text )
{
	sZADM->EntrySetText( fEntry, const_cast< ASZString >( text ) );
}
#else
inline void IADMEntry::SetText(const char* text)
{
	sADMEntry->SetText(fEntry, text);
}
#endif

#ifdef USING_ZADM
inline void IADMEntry::GetText( ASZString* text )
{
	sZADM->EntryGetText( fEntry, text );
}
#else
inline void IADMEntry::GetText(char* text, int maxLength )
{
	sADMEntry->GetText(fEntry, text, maxLength);
}
#endif

inline int IADMEntry::GetTextLength()
{
	return sADMEntry->GetTextLength(fEntry);
}


inline ADMTimerRef IADMEntry::CreateTimer(unsigned long milliseconds,
		ADMActionMask abortMask, ADMEntryTimerProc timerProc,
		ADMEntryTimerAbortProc abortProc)
{
	return sADMEntry->CreateTimer(fEntry, milliseconds,
		abortMask, timerProc, abortProc);
}

inline void IADMEntry::AbortTimer(ADMTimerRef timer)
{
	sADMEntry->AbortTimer(fEntry, timer);
}

#endif
