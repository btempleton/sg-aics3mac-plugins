/***********************************************************************/
/*                                                                     */
/* IADMList.hpp                                                        */
/* Object wrapper for ADM List Suite                                   */
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
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Dave Lazarony, 05/07/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMList_hpp__
#define __IADMList_hpp__

/*
 * Includes
 */
 
#ifndef __ADMList__
#include "ADMList.h"
#endif

#ifndef __IADMTypes_hpp__
#include "IADMTypes.hpp"
#endif


/*
 * Global Suite Pointer
 */

extern "C" ADMListSuite* sADMList;


/*
 * Interface Wrapper Class
 */

class IADMList
{
protected:
	ADMListRef fList;

public:	
	IADMList();
	IADMList(ADMListRef list);

	operator ADMListRef(void);
		
	void SetMenuID(int menuResID);
	int GetMenuID();
	
	ADMItemRef GetItem();
	
	void SetUserData(ADMUserData data);
	ADMUserData GetUserData();

	void SetEntryWidth(int width);
	int GetEntryWidth();
	
	void SetEntryHeight(int height);
	int GetEntryHeight();
	
	void SetEntryTextRect(const IADMRect& rect);
	void GetEntryTextRect(IADMRect& rect);
	
	ADMEntryRef InsertEntry(int index);
	void RemoveEntry(int index);
	
	ADMEntryRef GetEntry(int entryID);
	
	ADMEntryRef IndexEntry(int index);
	
	ADMEntryRef FindEntry(const char* text);
	
	ADMEntryRef PickEntry(const ADMPoint& point);
	
	ADMEntryRef GetActiveEntry();
	
	ADMEntryRef IndexSelectedEntry(int selectionIndex);
	
	int NumberOfEntries();
	
	int NumberOfSelectedEntries();

	void SetMask(ADMActionMask mask);
	ADMActionMask GetMask();

	void SetNotifierData(ADMUserData data);
	ADMUserData GetNotifierData();

};

inline IADMList::IADMList()								
{
	fList = NULL;
}

inline IADMList::IADMList(ADMListRef list)	
{
	fList = list;
}

inline IADMList::operator ADMListRef(void)
{
	return fList;
}

inline void IADMList::SetMenuID(int menuResID)
{
	sADMList->SetMenuID(fList, menuResID);
}

inline int IADMList::GetMenuID()
{
	return sADMList->GetMenuID(fList);
}

inline void IADMList::SetUserData(ADMUserData data)
{
	sADMList->SetUserData(fList, data);
}

inline ADMUserData IADMList::GetUserData()
{
	return sADMList->GetUserData(fList);
}

inline ADMItemRef IADMList::GetItem()
{
	return sADMList->GetItem(fList);
}

inline void IADMList::SetEntryWidth(int width)
{
	sADMList->SetEntryWidth(fList, width);
}

inline int IADMList::GetEntryWidth()
{
	return sADMList->GetEntryWidth(fList);
}

inline void IADMList::SetEntryHeight(int height)
{
	sADMList->SetEntryHeight(fList, height);
}

inline int IADMList::GetEntryHeight()
{
	return sADMList->GetEntryHeight(fList);
}

inline void IADMList::SetEntryTextRect(const IADMRect& rect)
{
	sADMList->SetEntryTextRect(fList, &rect);
}

inline void IADMList::GetEntryTextRect(IADMRect& rect)
{
	sADMList->GetEntryTextRect(fList, &rect);
}
		
inline ADMEntryRef IADMList::InsertEntry(int index)
{
	return sADMList->InsertEntry(fList, index);
}

inline void IADMList::RemoveEntry(int index)
{
	sADMList->RemoveEntry(fList, index);
}

inline ADMEntryRef IADMList::GetEntry(int entryID)
{
	return sADMList->GetEntry(fList, entryID);
}

inline ADMEntryRef IADMList::IndexEntry(int index)
{
	return sADMList->IndexEntry(fList, index);
}

inline ADMEntryRef IADMList::FindEntry(const char* text)
{
	return sADMList->FindEntry(fList, text);
}

inline ADMEntryRef IADMList::PickEntry(const ADMPoint& point)
{
	return sADMList->PickEntry(fList, &point);
}

inline ADMEntryRef IADMList::GetActiveEntry()
{
	return sADMList->GetActiveEntry(fList);
}

inline ADMEntryRef IADMList::IndexSelectedEntry(int selectionIndex)
{
	return sADMList->IndexSelectedEntry(fList, selectionIndex);
}

inline int IADMList::NumberOfEntries()
{
	return sADMList->NumberOfEntries(fList);
}

inline int IADMList::NumberOfSelectedEntries()
{
	return sADMList->NumberOfSelectedEntries(fList);
}

inline void IADMList::SetMask(ADMActionMask mask)
{
	sADMList->SetMask(fList, mask);
}

inline ADMActionMask IADMList::GetMask()
{
	return sADMList->GetMask(fList);
}

inline void IADMList::SetNotifierData(ADMUserData data)
{
	sADMList->SetNotifierData(fList, data);
}

inline ADMUserData IADMList::GetNotifierData()
{
	return sADMList->GetNotifierData(fList);
}

#endif