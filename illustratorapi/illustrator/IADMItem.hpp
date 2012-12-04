/***********************************************************************/
/*                                                                     */
/* IADMItem.hpp                                                        */
/* Object wrapper for ADM Item Suite                                   */
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

#ifndef __IADMItem_hpp__
#define __IADMItem_hpp__

/*
 * Includes
 */
 
#ifndef __ADMItem__
#include "ADMItem.h"
#endif

#ifndef __ADMIcon__
#include "ADMIcon.h"
#endif

#ifndef __IADMTypes_hpp__
#include "IADMTypes.hpp"
#endif

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif

// Macintosh Headers #define GetItem.
#ifdef GetItem
#undef GetItem
#endif


/*
 * Global Suite Pointer
 */

extern "C" ADMItemSuite7* sADMItem;
extern "C" ADMIconSuite2* sADMIcon2;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Interface Wrapper Class
 */

class IADMItem
{
protected:
	ADMItemRef fItem;

public:	 
	IADMItem();
	IADMItem(ADMItemRef item);
//	IADMItem(int nilItem);

	operator ADMItemRef(void);

	void SetDrawProc(ADMItemDrawProc inDrawProc);
	ADMItemDrawProc GetDrawProc();
	void DefaultDraw(ADMDrawerRef inDrawer);

	void SendNotify(const char* notifierType = NULL);
	void SetNotifyProc(ADMItemNotifyProc proc);
	ADMItemNotifyProc GetNotifyProc();
	void DefaultNotify(ADMNotifierRef inNotifier);

	void SetTrackProc(ADMItemTrackProc proc);
	ADMItemTrackProc GetTrackProc();
	ADMBoolean DefaultTrack(ADMTrackerRef inTracker);
	
	int GetID();
	ADMDialogRef GetDialog();
	ADMWindowRef GetWindowRef();
	ADMListRef GetList();
	ADMHierarchyListRef GetHierarchyList();

	SPPluginRef GetPluginRef();
	void SetPluginRef(SPPluginRef pluginRef);

	void SetItemType(ADMItemType type);
	ADMItemType GetItemType();
	
	void SetItemStyle(ADMItemStyle style);
	ADMItemStyle GetItemStyle();
	
	void Show(ADMBoolean show = true);
	void Hide();
	ADMBoolean IsVisible();
	
	void Enable(ADMBoolean enable = true);
	void Disable();
	ADMBoolean IsEnabled();
	
	void Activate(ADMBoolean activate = true);
	void Deactivate();
	ADMBoolean IsActive();
	
	void Known(ADMBoolean known = true);
	void Unknown();
	ADMBoolean IsKnown();
	
	void SetLocalRect(const IADMRect& localRect);
	void GetLocalRect(IADMRect& localRect);
	
	void SetBoundsRect(const IADMRect& boundsRect);
	void GetBoundsRect(IADMRect& boundsRect);
	
	void Move(int x, int y);
	void Size(int width, int height);
	
	void LocalToScreenPoint(IADMPoint& point);
	void ScreenToLocalPoint(IADMPoint& point);
	
	void LocalToScreenRect(IADMRect& rect);
	void ScreenToLocalRect(IADMRect& rect);
	
	void Invalidate();
	void Update();
	
	void SetCursorID(int cursorResID);
	ADMInt32 GetCursorID();

	void GetCursorID(SPPluginRef* pluginRef, ADMInt32* cursorID);

	ADMFont GetFont();
	void SetFont(ADMFont font);
	
	void SetPictureID(int pictureResID);
	bool SetPicture(const char* inName);
	ADMInt32 GetPictureID();
	
	
	void SetSelectedPictureID(int pictureResID);
	bool SetSelectedPicture(const char* inName);
	ADMInt32 GetSelectedPictureID();
	
	
	void SetDisabledPictureID(int pictureResID);
	bool SetDisabledPicture(const char* inName);
	ADMInt32 GetDisabledPictureID();
	
	
	void SetHasRollOverProperty(ADMBoolean enable = false);

	void SetRolloverPictureID(int pictureResID);
	bool SetRolloverPicture(const char* inName);
	ADMInt32 GetRolloverPictureID();

	void SetMask(ADMActionMask mask);
	ADMActionMask GetMask();

	void SetUserData(ADMUserData data);
	ADMUserData GetUserData();

	void SetNotifierData(ADMUserData data);
	ADMUserData GetNotifierData();

	ADMTimerRef CreateTimer(unsigned long milliseconds,
							ADMActionMask abortMask,
							ADMItemTimerProc timerProc,
							ADMItemTimerAbortProc abortProc);

	void AbortTimer(ADMTimerRef timer);

	/*
	 * Text
	 */
	 
#ifdef USING_ZADM
	void SetText(const ASZString text);
	void GetText(ASZString* text);
#else
	void SetText(const char* text);
	void GetText(char* text, int maxLength = 0);
#endif
	void SetTextW(const ADMUnicode* inText);
	void GetTextW(ADMUnicode* outText, ADMInt32 inMaxLength);
	int GetTextLength();
	int GetTextLengthW();
	
	void SetMaxTextLength(int length);
	int GetMaxTextLength();
	
	void SelectAll();
	void SetSelectionRange(ADMInt32 selStart, ADMInt32 selEnd);
	void GetSelectionRange(ADMInt32& selStart, ADMInt32& selEnd);

	void SetJustify(ADMJustify justify);
	ADMJustify GetJustify();
	
	void SetUnits(ADMUnits units);
	ADMUnits GetUnits();	
	
	void SetAllowUnits(ADMBoolean allow);
	ADMBoolean GetAllowUnits();
	
	void SetAllowMath(ADMBoolean allow);
	ADMBoolean GetAllowMath();
	
	void ShowUnits(ADMBoolean show);
	ADMBoolean GetShowUnits();

	void SetFloatToTextProc(ADMItemFloatToTextProc proc);
	ADMItemFloatToTextProc GetFloatToTextProc();
	ADMBoolean DefaultFloatToText(float value, char* text, int textLength);
	
	void SetTextToFloatProc(ADMItemTextToFloatProc proc);
	ADMItemTextToFloatProc GetTextToFloatProc();
	ADMBoolean DefaultTextToFloat(char* text, float* value);

	ADMBoolean WasPercentageChange();

	/*	

	 * Numerics
	 */
	 
	void SetPrecision(int numberOfDecimalPlaces);
	int GetPrecision();
	
	void SetBooleanValue(ADMBoolean value);
	ADMBoolean GetBooleanValue();
	
	void SetIntValue(int value);
	int GetIntValue();
		
	void SetFixedValue(ADMFixed value);	
	IADMFixed GetFixedValue();
	
	void SetFloatValue(float value);	
	float GetFloatValue();
	
	void SetMinIntValue(int value);
	int GetMinIntValue();
		
	void SetMinFixedValue(ADMFixed value);	
	IADMFixed GetMinFixedValue();
	
	void SetMaxIntValue(int value);
	int GetMaxIntValue();
	
	void SetMinFloatValue(float value);	
	float GetMinFloatValue();
	
	void SetMaxFixedValue(ADMFixed value);	
	IADMFixed GetMaxFixedValue();
	
	void SetMaxFloatValue(float value);	
	float GetMaxFloatValue();
	
	void SetSmallIncrement(float increment);	
	float GetSmallIncrement();
	
	void SetLargeIncrement(float increment);
	float GetLargeIncrement();	
	
	ADMItemRef GetChildItem(int childID);	

#ifdef USING_ZADM
	void SetTipString( const ASZString tipStr );
	void GetTipString( ASZString* tipStr );
#else
	void SetTipString(const char* tipStr);
	void GetTipString(char* tipStr, int maxLen);
#endif
	int GetTipStringLength();

	void SetTipStringW(const ADMUnicode* inTipString);
	void GetTipStringW(ADMUnicode* outTipString, ADMInt32 inMaxLength);
	ADMInt32 GetTipStringLengthW();

	void EnableTip(ADMBoolean enable = true);
	ADMBoolean IsTipEnabled();
	void ShowToolTip(ADMPoint* where = NULL);
	void HideToolTip();

/*		Set/GetHelpID has been removed from ADM	-cquartet 8/2002
	void SetHelpID(ASHelpID helpID);
	ASHelpID GetHelpID();
	void Help();
*/

	void GetBestSize(ADMPoint* size);
};

inline IADMItem::IADMItem()								
{
	fItem = NULL;
}

inline IADMItem::IADMItem(ADMItemRef item)	
{
	fItem = item;
}

//inline IADMItem::IADMItem(int)
//{
//	fItem = NULL;
//}

inline IADMItem::operator ADMItemRef(void)
{
	return fItem;
}

inline void IADMItem::SetDrawProc(ADMItemDrawProc inDrawProc)
{
	sADMItem->SetDrawProc(fItem, inDrawProc);
}

inline ADMItemDrawProc IADMItem::GetDrawProc()
{
	return 	sADMItem->GetDrawProc(fItem);
}

inline void IADMItem::DefaultDraw(ADMDrawerRef inDrawer)
{
	sADMItem->DefaultDraw(fItem, inDrawer);
}

inline void IADMItem::SendNotify(const char* notifierType)
{
	sADMItem->SendNotify(fItem, notifierType);
}
	
inline void IADMItem::SetNotifyProc(ADMItemNotifyProc proc)
{
	sADMItem->SetNotifyProc(fItem, proc);
}

inline ADMItemNotifyProc IADMItem::GetNotifyProc()
{
	return	sADMItem->GetNotifyProc(fItem);
}

inline void IADMItem::DefaultNotify(ADMNotifierRef inNotifier)
{
	sADMItem->DefaultNotify(fItem, inNotifier);
}

inline void IADMItem::SetTrackProc(ADMItemTrackProc proc)
{
	sADMItem->SetTrackProc(fItem, proc);
}

inline ADMItemTrackProc IADMItem::GetTrackProc()
{
	return	sADMItem->GetTrackProc(fItem);
}

inline ADMBoolean IADMItem::DefaultTrack(ADMTrackerRef inTracker)
{
	return sADMItem->DefaultTrack(fItem, inTracker);
}
	
inline int IADMItem::GetID()
{
	return sADMItem->GetID(fItem);
}

inline ADMDialogRef IADMItem::GetDialog()
{
	return sADMItem->GetDialog(fItem);
}

inline ADMWindowRef IADMItem::GetWindowRef()
{
	return sADMItem->GetWindowRef(fItem);
}

inline ADMListRef IADMItem::GetList()
{
	return sADMItem->GetList(fItem);
}

inline ADMHierarchyListRef IADMItem::GetHierarchyList()
{
	return sADMItem->GetHierarchyList(fItem);
}

inline void IADMItem::SetPluginRef(struct SPPlugin* pluginRef)
{
	sADMItem->SetPluginRef(fItem, pluginRef);
}

inline struct SPPlugin* IADMItem::GetPluginRef()
{
	return sADMItem->GetPluginRef(fItem);
}

inline void IADMItem::SetItemType(ADMItemType type)
{
	sADMItem->SetItemType(fItem, type);
}

inline ADMItemType IADMItem::GetItemType()
{
	return sADMItem->GetItemType(fItem);
}

inline void IADMItem::SetItemStyle(ADMItemStyle style)
{
	sADMItem->SetItemStyle(fItem, style);
}

inline ADMItemStyle IADMItem::GetItemStyle()
{
	return sADMItem->GetItemStyle(fItem);
}

inline void IADMItem::Show(ADMBoolean show)
{
	sADMItem->Show(fItem, show);
}

inline void IADMItem::Hide()
{
	sADMItem->Show(fItem, false);
}

inline ADMBoolean IADMItem::IsVisible()
{
	return sADMItem->IsVisible(fItem);
}

inline void IADMItem::Enable(ADMBoolean enable)
{
	sADMItem->Enable(fItem, enable);
}

inline void IADMItem::Disable()
{
	sADMItem->Enable(fItem, false);
}

inline ADMBoolean IADMItem::IsEnabled()
{
	return sADMItem->IsEnabled(fItem);
}

inline void IADMItem::Activate(ADMBoolean activate)
{
	sADMItem->Activate(fItem, activate);
}

inline void IADMItem::Deactivate()
{
	sADMItem->Activate(fItem, false);
}

inline ADMBoolean IADMItem::IsActive()
{
	return sADMItem->IsActive(fItem);
}

inline void IADMItem::Known(ADMBoolean known)
{
	sADMItem->Known(fItem, known);
}

inline void IADMItem::Unknown()
{
	sADMItem->Known(fItem, false);
}

inline ADMBoolean IADMItem::IsKnown()
{
	return sADMItem->IsKnown(fItem);
}

inline void IADMItem::SetLocalRect(const IADMRect& localRect)
{
	sADMItem->SetLocalRect(fItem, &localRect);
}

inline void IADMItem::GetLocalRect(IADMRect& localRect)
{
	sADMItem->GetLocalRect(fItem, &localRect);
}

inline void IADMItem::SetBoundsRect(const IADMRect& boundsRect)
{
	sADMItem->SetBoundsRect(fItem, &boundsRect);
}

inline void IADMItem::GetBoundsRect(IADMRect& boundsRect)
{
	sADMItem->GetBoundsRect(fItem, &boundsRect);
}

inline void IADMItem::Move(int x, int y)
{
	sADMItem->Move(fItem, x, y);
}

inline void IADMItem::Size(int width, int height)
{
	sADMItem->Size(fItem, width, height);
}

inline void IADMItem::LocalToScreenPoint(IADMPoint& point)
{
	sADMItem->LocalToScreenPoint(fItem, &point);
}

inline void IADMItem::ScreenToLocalPoint(IADMPoint& point)
{
	sADMItem->ScreenToLocalPoint(fItem, &point);
}

inline void IADMItem::LocalToScreenRect(IADMRect& rect)
{
	sADMItem->LocalToScreenRect(fItem, &rect);
}

inline void IADMItem::ScreenToLocalRect(IADMRect& rect)
{
	sADMItem->ScreenToLocalRect(fItem, &rect);
}
		
inline void IADMItem::Invalidate()
{
	sADMItem->Invalidate(fItem);
}

inline void IADMItem::Update()
{
	sADMItem->Update(fItem);
}

inline void IADMItem::SetCursorID(int cursorResID)
{
	sADMItem->SetCursorID(fItem, sADMItem->GetPluginRef(fItem), cursorResID, NULL);
}

inline ADMInt32 IADMItem::GetCursorID()
{
	ADMInt32 cursorID = 0;
	SPPluginRef itsPlugin;
	sADMItem->GetCursorID(fItem, &itsPlugin, &cursorID, NULL);
	return cursorID;
}

inline void IADMItem::GetCursorID(SPPluginRef* plugin,  ADMInt32* cursorResID)
{
	*cursorResID = 0;
	sADMItem->GetCursorID(fItem, plugin, cursorResID, NULL);
}

inline ADMFont IADMItem::GetFont()
{
	return sADMItem->GetFont(fItem);
}

inline void IADMItem::SetFont(ADMFont font)
{
	sADMItem->SetFont(fItem, font);
}
	
inline void IADMItem::SetPictureID(int pictureResID)
{
	sADMItem->SetPictureID(fItem, pictureResID, NULL);
}

inline bool IADMItem::SetPicture(const char* inName)
{
	ADMIconRef theIcon = sADMIcon2->GetFromResource(sADMItem->GetPluginRef(fItem),inName,0,0);
	bool theValue = theIcon != NULL;
	if(theValue) sADMItem->SetPicture(fItem, theIcon);
	return theValue;
}

inline ADMInt32 IADMItem::GetPictureID()
{
	ADMInt32 pictureResID = 0;
	sADMItem->GetPictureID(fItem, &pictureResID, NULL);
	return pictureResID;
}

inline void IADMItem::SetSelectedPictureID(int pictureResID)
{
	sADMItem->SetSelectedPictureID(fItem, pictureResID, NULL);
}

inline bool IADMItem::SetSelectedPicture(const char* inName)
{
	ADMIconRef theIcon = sADMIcon2->GetFromResource(sADMItem->GetPluginRef(fItem),inName,0,0);
	bool theValue = theIcon != NULL;
	if(theValue) sADMItem->SetSelectedPicture(fItem, theIcon);
	return theValue;
}

inline ADMInt32 IADMItem::GetSelectedPictureID()
{
	ADMInt32 pictureResID = 0;
	sADMItem->GetSelectedPictureID(fItem, &pictureResID, NULL);
	return pictureResID;
}

inline void IADMItem::SetDisabledPictureID(int pictureResID)
{
	sADMItem->SetDisabledPictureID(fItem, pictureResID, NULL);
}

inline bool IADMItem::SetDisabledPicture(const char* inName)
{
	ADMIconRef theIcon = sADMIcon2->GetFromResource(sADMItem->GetPluginRef(fItem),inName,0,0);
	bool theValue = theIcon != NULL;
	if(theValue) sADMItem->SetDisabledPicture(fItem, theIcon);
	return theValue;
}

inline ADMInt32 IADMItem::GetDisabledPictureID()
{
	ADMInt32 pictureResID = 0;
	sADMItem->GetDisabledPictureID(fItem, &pictureResID, NULL);
	return pictureResID;
}

inline void IADMItem::SetHasRollOverProperty(ADMBoolean enable)
{
	sADMItem->SetHasRollOverProperty(fItem, enable);
}

inline void IADMItem::SetRolloverPictureID(int pictureResID)
{
	sADMItem->SetRolloverPictureID(fItem, pictureResID, NULL);
}

inline bool IADMItem::SetRolloverPicture(const char* inName)
{
	ADMIconRef theIcon = sADMIcon2->GetFromResource(sADMItem->GetPluginRef(fItem),inName,0,0);
	bool theValue = theIcon != NULL;
	if(theValue) sADMItem->SetRolloverPicture(fItem, theIcon);
	return theValue;
}

inline ADMInt32 IADMItem::GetRolloverPictureID()
{
	ADMInt32 pictureResID = 0;
	sADMItem->GetRolloverPictureID(fItem, &pictureResID, NULL);
	return pictureResID;
}

/*
 * Text
 */

#ifdef USING_ZADM
inline void IADMItem::SetText( const ASZString text )
{
	sZADM->ItemSetText( fItem, const_cast< ASZString >( text ) );
}
#else 
inline void IADMItem::SetText(const char* text)
{
	sADMItem->SetText(fItem, text);
}
#endif

#ifdef USING_ZADM
inline void IADMItem::GetText( ASZString* text )
{
	sZADM->ItemGetText( fItem, text );
}
#else 
inline void IADMItem::GetText(char* text, int maxLength)
{
	sADMItem->GetText(fItem, text, maxLength);
}
#endif

inline void IADMItem :: SetTextW(const ADMUnicode* inText)
{
	sADMItem->SetTextW(fItem, inText);
}

inline void IADMItem :: GetTextW(ADMUnicode* outText, ADMInt32 inMaxLength)
{
	sADMItem->GetTextW(fItem, outText, inMaxLength);
}

inline int IADMItem::GetTextLength()
{
	return sADMItem->GetTextLength(fItem);
}

inline int IADMItem::GetTextLengthW()
{
	return sADMItem->GetTextLengthW(fItem);
}

inline void IADMItem::SetMaxTextLength(int length)
{
	sADMItem->SetMaxTextLength(fItem, length);
}

inline int IADMItem::GetMaxTextLength()
{
	return sADMItem->GetMaxTextLength(fItem);
}

inline void IADMItem::SelectAll()
{
	sADMItem->SelectAll(fItem);
}

inline void IADMItem::SetSelectionRange(ADMInt32 selStart, ADMInt32 selEnd)
{
	sADMItem->SetSelectionRange(fItem, selStart, selEnd);
}

inline void IADMItem::GetSelectionRange(ADMInt32& selStart, ADMInt32& selEnd)
{
	sADMItem->GetSelectionRange(fItem, &selStart, &selEnd);
}

inline void IADMItem::SetJustify(ADMJustify justify)
{
	sADMItem->SetJustify(fItem, justify);
}

inline ADMJustify IADMItem::GetJustify()
{
	return sADMItem->GetJustify(fItem);
}

inline void IADMItem::SetUnits(ADMUnits units)
{
	sADMItem->SetUnits(fItem, units);
}

inline ADMUnits IADMItem::GetUnits()
{
	return sADMItem->GetUnits(fItem);
}

inline void IADMItem::SetAllowUnits(ADMBoolean allow)
{
	sADMItem->SetAllowUnits(fItem, allow);
}

inline ADMBoolean IADMItem::GetAllowUnits()
{
	return sADMItem->GetAllowUnits(fItem);
}

inline void IADMItem::SetAllowMath(ADMBoolean allow)
{
	sADMItem->SetAllowMath(fItem, allow);
}

inline ADMBoolean IADMItem::GetAllowMath()
{
	return sADMItem->GetAllowMath(fItem);
}

inline void IADMItem::ShowUnits(ADMBoolean show)
{
	sADMItem->ShowUnits(fItem, show);
}

inline ADMBoolean IADMItem::GetShowUnits()
{
	return sADMItem->GetShowUnits(fItem);
}

inline void IADMItem::SetFloatToTextProc(ADMItemFloatToTextProc proc)
{
	sADMItem->SetFloatToTextProc(fItem, proc);
}

inline ADMItemFloatToTextProc IADMItem::GetFloatToTextProc()
{
	return sADMItem->GetFloatToTextProc(fItem);
}

inline ADMBoolean IADMItem::DefaultFloatToText(float value, char* text, int textLength)
{
	return sADMItem->DefaultFloatToText(fItem, value, text, textLength);
}

inline void IADMItem::SetTextToFloatProc(ADMItemTextToFloatProc proc)
{
	sADMItem->SetTextToFloatProc(fItem, proc);
}

inline ADMItemTextToFloatProc IADMItem::GetTextToFloatProc()
{
	return sADMItem->GetTextToFloatProc(fItem);
}

inline ADMBoolean IADMItem::DefaultTextToFloat(char* text, float* value)
{
	return sADMItem->DefaultTextToFloat(fItem, text, value);
}

inline ADMBoolean IADMItem::WasPercentageChange()
{
	return sADMItem->WasPercentageChange(fItem);
}

/*
 * Numerics
 */
 
inline void IADMItem::SetPrecision(int numberOfDecimalPlaces)
{
	sADMItem->SetPrecision(fItem, numberOfDecimalPlaces);
}

inline int IADMItem::GetPrecision()
{
	return sADMItem->GetPrecision(fItem);
}

inline void IADMItem::SetBooleanValue(ADMBoolean value)
{
	sADMItem->SetBooleanValue(fItem, value);
}

inline ADMBoolean IADMItem::GetBooleanValue()
{
	return sADMItem->GetBooleanValue(fItem);
}

inline void IADMItem::SetIntValue(int value)
{
	sADMItem->SetIntValue(fItem, value);
}

inline int IADMItem::GetIntValue()
{
	return sADMItem->GetIntValue(fItem);
}

inline void IADMItem::SetFixedValue(ADMFixed value)
{
	sADMItem->SetFixedValue(fItem, value);
}
	
inline IADMFixed IADMItem::GetFixedValue()
{
	return sADMItem->GetFixedValue(fItem);
}

inline void IADMItem::SetFloatValue(float value)
{
	sADMItem->SetFloatValue(fItem, value);
}
	
inline float IADMItem::GetFloatValue()
{
	return sADMItem->GetFloatValue(fItem);
}

inline void IADMItem::SetMinIntValue(int value)
{
	sADMItem->SetMinIntValue(fItem, value);
}

inline int IADMItem::GetMinIntValue()
{
	return sADMItem->GetMinIntValue(fItem);
}

inline void IADMItem::SetMinFixedValue(ADMFixed value)
{
	sADMItem->SetMinFixedValue(fItem, value);
}
	
inline IADMFixed IADMItem::GetMinFixedValue()
{
	return sADMItem->GetMinFixedValue(fItem);
}

inline void IADMItem::SetMaxIntValue(int value)
{
	sADMItem->SetMaxIntValue(fItem, value);
}

inline int IADMItem::GetMaxIntValue()
{
	return sADMItem->GetMaxIntValue(fItem);
}

inline void IADMItem::SetMinFloatValue(float value)
{
	sADMItem->SetMinFloatValue(fItem, value);
}
	
inline float IADMItem::GetMinFloatValue()
{
	return sADMItem->GetMinFloatValue(fItem);
}

inline void IADMItem::SetMaxFixedValue(ADMFixed value)
{
	sADMItem->SetMaxFixedValue(fItem, value);
}
	
inline IADMFixed IADMItem::GetMaxFixedValue()
{
	return sADMItem->GetMaxFixedValue(fItem);
}

inline void IADMItem::SetMaxFloatValue(float value)
{
	sADMItem->SetMaxFloatValue(fItem, value);
}
	
inline float IADMItem::GetMaxFloatValue()
{
	return sADMItem->GetMaxFloatValue(fItem);
}

inline void IADMItem::SetSmallIncrement(float increment)
{
	sADMItem->SetSmallIncrement(fItem, increment);
}
	
inline float IADMItem::GetSmallIncrement()
{
	return sADMItem->GetSmallIncrement(fItem);
}

inline void IADMItem::SetLargeIncrement(float increment)
{
	sADMItem->SetLargeIncrement(fItem, increment);
}

inline float IADMItem::GetLargeIncrement()
{
	return sADMItem->GetLargeIncrement(fItem);
}

inline ADMItemRef IADMItem::GetChildItem(int childID)
{
	return sADMItem->GetChildItem(fItem, childID);
}

#ifdef USING_ZADM
inline void IADMItem::SetTipString( const ASZString tipStr )
{
	sZADM->ItemSetTipString( fItem, const_cast< ASZString >( tipStr ) );
}
#else
inline void IADMItem::SetTipString(const char* tipStr)
{
	sADMItem->SetTipString(fItem, tipStr);
}
#endif

#ifdef USING_ZADM
inline void IADMItem::GetTipString( ASZString* tipStr )
{
	sZADM->ItemGetTipString( fItem, tipStr );
}
#else
inline void IADMItem::GetTipString(char* tipStr, int maxLen)
{
	sADMItem->GetTipString(fItem, tipStr, maxLen);
}
#endif

inline int IADMItem::GetTipStringLength()
{
	return sADMItem->GetTipStringLength(fItem);
}	

inline void IADMItem::SetTipStringW(const ADMUnicode* inTipString)
{
	sADMItem->SetTipStringW(fItem, inTipString);
}

inline void IADMItem::GetTipStringW(ADMUnicode* outTipString, ADMInt32 inMaxLength)
{
	sADMItem->GetTipStringW(fItem, outTipString, inMaxLength);
}

inline ADMInt32 IADMItem::GetTipStringLengthW()
{
	return sADMItem->GetTipStringLengthW(fItem);
}	

inline void IADMItem::EnableTip(ADMBoolean enable)
{
	sADMItem->EnableTip(fItem, enable);
}	

inline ADMBoolean IADMItem::IsTipEnabled()
{
	return sADMItem->IsTipEnabled(fItem);
}	

inline void IADMItem::ShowToolTip(ADMPoint* where)
{
	sADMItem->ShowToolTip(fItem, where);
}	

inline void IADMItem::HideToolTip()
{
	sADMItem->HideToolTip(fItem);
}	

/*
inline void IADMItem::SetHelpID(ASHelpID helpID)
{
	sADMItem->SetHelpID(fItem, helpID);
}

inline ASHelpID IADMItem::GetHelpID()
{
	return sADMItem->GetHelpID(fItem);
}

inline void IADMItem::Help()
{
	sADMItem->Help(fItem);
}
*/

inline void IADMItem::GetBestSize(ADMPoint* size)
{
	sADMItem->GetBestSize(fItem, size);
}	


inline void IADMItem::SetMask(ADMActionMask mask)
{
	sADMItem->SetMask(fItem, mask);
}

inline ADMActionMask IADMItem::GetMask()
{
	return sADMItem->GetMask(fItem);
}

inline void IADMItem::SetUserData(ADMUserData data)
{
	sADMItem->SetUserData(fItem, data);
}

inline ADMUserData IADMItem::GetUserData()
{
	return sADMItem->GetUserData(fItem);
}

inline void IADMItem::SetNotifierData(ADMUserData data)
{
	sADMItem->SetNotifierData(fItem, data);
}

inline ADMUserData IADMItem::GetNotifierData()
{
	return sADMItem->GetNotifierData(fItem);
}

inline ADMTimerRef IADMItem::CreateTimer(unsigned long milliseconds,
		ADMActionMask abortMask, ADMItemTimerProc timerProc,
		ADMItemTimerAbortProc abortProc)
{
	return sADMItem->CreateTimer(fItem, milliseconds,
		abortMask, timerProc, abortProc, 0);
}

inline void IADMItem::AbortTimer(ADMTimerRef timer)
{
	sADMItem->AbortTimer(fItem, timer);
}

#endif
