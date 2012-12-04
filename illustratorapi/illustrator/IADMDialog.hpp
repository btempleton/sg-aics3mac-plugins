/***********************************************************************/
/*                                                                     */
/* IADMDialog.hpp                                                      */
/* Object wrapper for ADM Dialog Suite                                 */
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

#ifndef __IADMDialog_hpp__
#define __IADMDialog_hpp__

/*
 * Includes
 */
 
#ifndef __ADMDialog__
#include "ADMDialog.h"
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

extern "C" ADMDialogSuite* sADMDialog;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Interface Wrapper Class
 */

class IADMDialog
{
protected:
	ADMDialogRef fDialog;
	
public:	
	IADMDialog();
	IADMDialog(ADMDialogRef dialog);
//	IADMDialog(int nilDialog);
	
	operator ADMDialogRef(void);
	
	ADMDialogRef GetDialogRef(void);
	void SetDialogRef(ADMDialogRef);
	
	void SendNotify(const char* notifierType = NULL);
	void DefaultNotify(ADMNotifierRef notifier);
	
	int GetID();
	SPPluginRef GetPluginRef();
	ADMWindowRef GetWindowRef();

	void SetName(const char* inName);
	const char* GetName();
	
	void SetDialogStyle(ADMDialogStyle style);
	ADMDialogStyle GetDialogStyle();
	
	void Show(ADMBoolean show = true);
	void Hide();
	ADMBoolean IsVisible();

	ADMBoolean IsTabHidden();
	ADMBoolean IsContextHidden();

	void Enable(ADMBoolean enable = true);
	void Disable();
	ADMBoolean IsEnabled();
	
	void Activate(ADMBoolean activate = true);
	void Deactivate();
	ADMBoolean IsActive();
	
	void SetLocalRect(const IADMRect& localRect);
	void GetLocalRect(IADMRect& localRect);
	
	void SetBoundsRect(const IADMRect& boundsRect);
	void GetBoundsRect(IADMRect& boundsRect);

	void GetMainViewRect(ADMRect* outBoundsRect);

	void Move(int x, int y);
	void Size(int width, int height);

	void SetPreferredSizes(const ADMPoint *inConstrained, const ADMPoint *inUnconstrained);
	void GetPreferredSizes(ADMPoint *outConstrained, ADMPoint *outUnconstrained);

	void LocalToScreenPoint(IADMPoint& point);
	void ScreenToLocalPoint(IADMPoint& point);
	
	void LocalToScreenRect(IADMRect& rect);
	void ScreenToLocalRect(IADMRect& rect);
	
	void Invalidate();
	void Update();
	
	void SetCursorID(int cursorResID);
	int GetCursorID();

	void GetCursorID(SPPluginRef* plugin, ADMInt32* cursorResID);

	ADMFont GetFont();
	void SetFont(ADMFont font);
	
#ifdef USING_ZADM
	void SetText(const ADMZString text);
	void GetText(ADMZString* text);
#else
	void SetText(const char* text);
	void GetText(char* text, int maxLength = 0);
#endif

	void SetTextW(const ADMUnicode* inText);
	void GetTextW(ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 GetTextLength();
	ADMInt32 GetTextLengthW();

	void SetMinWidth(int width);
	int GetMinWidth();
	
	void SetMinHeight(int height);
	int GetMinHeight();
	
	void SetMaxWidth(int width);
	int GetMaxWidth();
	
	void SetMaxHeight(int height);
	int GetMaxHeight();
	
	void SetHorizontalIncrement(int height);
	int GetHorizontalIncrement();
	
	void SetVerticalIncrement(int height);
	int GetVerticalIncrement();
	
	ADMItemRef GetItem(int itemID);
	
	ADMItemRef CreateItem(int itemID, ADMItemType itemType, const IADMRect& boundsRect, ADMItemInitProc initProc = NULL, ADMUserData data = 0, int options = 0);
	void DestroyItem(ADMItemRef item);
	
	ADMItemRef GetNextItem(ADMItemRef item);
	ADMItemRef GetPreviousItem(ADMItemRef item);

	void SetDefaultItemID(int itemID);
	int GetDefaultItemID();
	void SetCancelItemID(int itemID);
	int GetCancelItemID();
	
	void EndModal(int modalResultID, ADMBoolean cancelling = false);

	void LoadToolTips(int stringID);

/*		Set/GetHelpID has been removed from ADM	-cquartet 8/2002
	void SetHelpID(ASHelpID helpID);
	ASHelpID GetHelpID();
	void Help();
*/

	void SetMask(ADMActionMask mask);
	ADMActionMask GetMask();

	void SetNotifyProc(ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc GetNotifyProc();

	void SetNotifierData(ADMUserData data);
	ADMUserData GetNotifierData();

	ADMTimerRef CreateTimer(unsigned long milliseconds,
							ADMActionMask abortMask,
							ADMDialogTimerProc timerProc,
							ADMDialogTimerAbortProc abortProc,
							int options = 0);

	void AbortTimer(ADMTimerRef timer);

	ADMBoolean IsCollapsed();
	
	void SetForcedOnScreen(ADMBoolean inForcedOnScreen);

	ADMErr SetIcon(bool rollover, ADMIconRef);
	ADMErr SetToolbarIcon(ADMToolbarIconType, ADMIconRef);

	ADMErr SetToolbarMode(ADMToolbarMode);
	ADMErr GetToolbarMode(ADMToolbarMode&);

};


inline IADMDialog::IADMDialog()								
{
	fDialog = NULL;
}

inline IADMDialog::IADMDialog(ADMDialogRef dialog)	
{
	fDialog = dialog;
}

//inline IADMDialog::IADMDialog(int)
//{
//	fDialog = NULL;
//}

inline IADMDialog::operator ADMDialogRef(void)
{
	return fDialog;
}

inline ADMDialogRef IADMDialog::GetDialogRef(void)
{
	return fDialog;
}

inline void IADMDialog::SetDialogRef(ADMDialogRef dialog)
{
	fDialog = dialog;
}


inline void IADMDialog::SendNotify(const char* notifierType)
{
	sADMDialog->SendNotify(fDialog, notifierType);
}

inline void IADMDialog::DefaultNotify(ADMNotifierRef notifier)
{
	sADMDialog->DefaultNotify(fDialog, notifier);
}

inline int IADMDialog::GetID()
{
	return sADMDialog->GetID(fDialog);
}

inline struct SPPlugin* IADMDialog::GetPluginRef()
{
	return sADMDialog->GetPluginRef(fDialog);
}

inline ADMWindowRef IADMDialog::GetWindowRef()
{
	return sADMDialog->GetWindowRef(fDialog);
}


inline void IADMDialog::SetName(const char* inName)
{
	sADMDialog->SetDialogName(fDialog, inName);
}

inline const char* IADMDialog::GetName()
{
	return sADMDialog->GetDialogName(fDialog);
}


inline void IADMDialog::SetDialogStyle(ADMDialogStyle style)
{
	sADMDialog->SetDialogStyle(fDialog, style);
}

inline ADMDialogStyle IADMDialog::GetDialogStyle()
{
	return sADMDialog->GetDialogStyle(fDialog);
}

inline void IADMDialog::Show(ADMBoolean show)
{
	sADMDialog->Show(fDialog, show);
}

inline void IADMDialog::Hide()
{
	sADMDialog->Show(fDialog, false);
}

inline ADMBoolean IADMDialog::IsVisible()
{
	return sADMDialog->IsVisible(fDialog);
}

inline ADMBoolean IADMDialog::IsTabHidden()
{
	return sADMDialog->IsDialogTabHidden(fDialog);
}

inline ADMBoolean IADMDialog::IsContextHidden()
{
	return sADMDialog->IsDialogContextHidden(fDialog);
}

inline void IADMDialog::Enable(ADMBoolean enable)
{
	sADMDialog->Enable(fDialog, enable);
}

inline void IADMDialog::Disable()
{
	sADMDialog->Enable(fDialog, false);
}

inline ADMBoolean IADMDialog::IsEnabled()
{
	return sADMDialog->IsEnabled(fDialog);
}

inline void IADMDialog::Activate(ADMBoolean activate)
{
	sADMDialog->Activate(fDialog, activate);
}

inline void IADMDialog::Deactivate()
{
	sADMDialog->Activate(fDialog, false);
}

inline ADMBoolean IADMDialog::IsActive()
{
	return sADMDialog->IsActive(fDialog);
}

inline void IADMDialog::SetLocalRect(const IADMRect& localRect)
{
	sADMDialog->SetLocalRect(fDialog, &localRect);
}

inline void IADMDialog::GetLocalRect(IADMRect& localRect)
{
	sADMDialog->GetLocalRect(fDialog, &localRect);
}

inline void IADMDialog::SetBoundsRect(const IADMRect& boundsRect)
{
	sADMDialog->SetBoundsRect(fDialog, &boundsRect);
}

inline void IADMDialog::GetBoundsRect(IADMRect& boundsRect)
{
	sADMDialog->GetBoundsRect(fDialog, &boundsRect);
}

inline void IADMDialog::GetMainViewRect(ADMRect* outBoundsRect)
{
	sADMDialog->GetMainViewRect(fDialog, outBoundsRect);
}

inline void IADMDialog::Move(int x, int y)
{
	sADMDialog->Move(fDialog, x, y);
}

inline void IADMDialog::Size(int width, int height)
{
	sADMDialog->Size(fDialog, width, height);
}

inline void IADMDialog::SetPreferredSizes(const ADMPoint *inConstrained, const ADMPoint *inUnconstrained)
{
	sADMDialog->SetPreferredSizes(fDialog, inConstrained, inUnconstrained);
}

inline void IADMDialog::GetPreferredSizes(ADMPoint *outConstrained, ADMPoint *outUnconstrained)
{
	sADMDialog->GetPreferredSizes(fDialog, outConstrained, outUnconstrained);
}

inline void IADMDialog::LocalToScreenPoint(IADMPoint& point)
{
	sADMDialog->LocalToScreenPoint(fDialog, (ADMPoint*)& point);
}

inline void IADMDialog::ScreenToLocalPoint(IADMPoint& point)
{
	sADMDialog->ScreenToLocalPoint(fDialog, (ADMPoint*)& point);
}

inline void IADMDialog::LocalToScreenRect(IADMRect& rect)
{
	sADMDialog->LocalToScreenRect(fDialog, (ADMRect*)& rect);
}

inline void IADMDialog::ScreenToLocalRect(IADMRect& rect)
{
	sADMDialog->ScreenToLocalRect(fDialog, (ADMRect*)& rect);
}
		
inline void IADMDialog::Invalidate()
{
	sADMDialog->Invalidate(fDialog);
}

inline void IADMDialog::Update()
{
	sADMDialog->Update(fDialog);
}



inline void IADMDialog::SetCursorID(int cursorResID)
{
	sADMDialog->SetCursorID(fDialog, sADMDialog->GetPluginRef(fDialog), cursorResID);
}

inline int IADMDialog::GetCursorID()
{
	ADMInt32 cursorID = 0;
	SPPluginRef itsPlugin;
	sADMDialog->GetCursorID(fDialog, &itsPlugin, &cursorID);
	return cursorID;
}

inline void IADMDialog::GetCursorID(SPPluginRef* plugin, ADMInt32* cursorResID)
{
	*cursorResID = 0;
	sADMDialog->GetCursorID(fDialog, plugin, cursorResID);
}

inline ADMFont IADMDialog::GetFont()
{
	return sADMDialog->GetFont(fDialog);
}

inline void IADMDialog::SetFont(ADMFont font)
{
	sADMDialog->SetFont(fDialog, font);
}
	
#ifdef USING_ZADM
inline void IADMDialog::SetText( const ADMZString text )
{
	sZADM->DialogSetText( fDialog, const_cast< ADMZString >( text ) );
}
#else
inline void IADMDialog::SetText(const char* text)
{
	sADMDialog->SetText(fDialog, text);
}
#endif

#ifdef USING_ZADM
inline void IADMDialog::GetText( ADMZString* text )
{
	sZADM->DialogGetText( fDialog, text );
}
#else
inline void IADMDialog::GetText(char* text, int maxLength)
{
	sADMDialog->GetText(fDialog, text, maxLength);
}
#endif

inline void IADMDialog::SetTextW(const ADMUnicode* inText)
{
	sADMDialog->SetTextW(fDialog, inText);
}

inline void IADMDialog::GetTextW(ADMUnicode* outText, ADMInt32 inMaxLength)
{
	sADMDialog->GetTextW(fDialog, outText, inMaxLength);
}

inline ADMInt32 IADMDialog::GetTextLength()
{
	return sADMDialog->GetTextLength(fDialog);
}

inline ADMInt32 IADMDialog::GetTextLengthW()
{
	return sADMDialog->GetTextLengthW(fDialog);
}

inline void IADMDialog::SetMinWidth(int width)
{
	sADMDialog->SetMinWidth(fDialog, width);
}

inline int IADMDialog::GetMinWidth()
{
	return sADMDialog->GetMinWidth(fDialog);
}

inline void IADMDialog::SetMinHeight(int height)
{
	sADMDialog->SetMinHeight(fDialog, height);
}

inline int IADMDialog::GetMinHeight()
{
	return sADMDialog->GetMinHeight(fDialog);
}

inline void IADMDialog::SetMaxWidth(int width)
{
	sADMDialog->SetMaxWidth(fDialog, width);
}

inline int IADMDialog::GetMaxWidth()
{
	return sADMDialog->GetMaxWidth(fDialog);
}

inline void IADMDialog::SetMaxHeight(int height)
{
	sADMDialog->SetMaxHeight(fDialog, height);
}

inline int IADMDialog::GetMaxHeight()
{
	return sADMDialog->GetMaxHeight(fDialog);
}

inline void IADMDialog::SetHorizontalIncrement(int increment)
{
	sADMDialog->SetHorizontalIncrement(fDialog, increment);
}

inline int IADMDialog::GetHorizontalIncrement()
{
	return sADMDialog->GetHorizontalIncrement(fDialog);
}

inline void IADMDialog::SetVerticalIncrement(int increment)
{
	sADMDialog->SetVerticalIncrement(fDialog, increment);
}

inline int IADMDialog::GetVerticalIncrement()
{
	return sADMDialog->GetVerticalIncrement(fDialog);
}

inline ADMItemRef IADMDialog::GetItem(int itemID)
{
	return sADMDialog->GetItem(fDialog, itemID);
}

inline ADMItemRef IADMDialog::CreateItem(int itemID, ADMItemType itemType, const IADMRect& boundsRect, ADMItemInitProc initProc, ADMUserData data, int options)
{
	return sADMDialog->CreateItem(fDialog, itemID, itemType, (ADMRect*) &boundsRect, initProc, data, options);
}

inline void IADMDialog::DestroyItem(ADMItemRef item)	
{
	sADMDialog->DestroyItem(fDialog, item);
}

inline ADMItemRef IADMDialog::GetNextItem(ADMItemRef item)
{
	return sADMDialog->GetNextItem(fDialog, item);
}

inline ADMItemRef IADMDialog::GetPreviousItem(ADMItemRef item)
{
	return sADMDialog->GetPreviousItem(fDialog, item);
}

inline void IADMDialog::SetDefaultItemID(int itemID)
{
	sADMDialog->SetDefaultItemID(fDialog, itemID);
}

inline int IADMDialog::GetDefaultItemID()
{
	return sADMDialog->GetDefaultItemID(fDialog);
}

inline void IADMDialog::SetCancelItemID(int itemID)
{
	sADMDialog->SetCancelItemID(fDialog, itemID);
}

inline int IADMDialog::GetCancelItemID()
{
	return sADMDialog->GetCancelItemID(fDialog);
}

inline void IADMDialog::EndModal(int modalResultID, ADMBoolean cancelling)
{
	sADMDialog->EndModal(fDialog, modalResultID, cancelling);
}
	
inline void IADMDialog::LoadToolTips(int stringID)
{
	sADMDialog->LoadToolTips(fDialog, stringID);
}

/*
inline void IADMDialog::SetHelpID(ASHelpID helpID)
{
	sADMDialog->SetHelpID(fDialog, helpID);
}

inline ASHelpID IADMDialog::GetHelpID()
{
	return sADMDialog->GetHelpID(fDialog);
}

inline void IADMDialog::Help()
{
	sADMDialog->Help(fDialog);
}
*/

inline void IADMDialog::SetMask(ADMActionMask mask)
{
	sADMDialog->SetMask(fDialog, mask);
}

inline ADMActionMask IADMDialog::GetMask()
{
	return sADMDialog->GetMask(fDialog);
}

inline void IADMDialog::SetNotifyProc(ADMDialogNotifyProc inNotifyProc)
{
	sADMDialog->SetNotifyProc(fDialog, inNotifyProc);
}

inline ADMDialogNotifyProc IADMDialog::GetNotifyProc()
{
	return sADMDialog->GetNotifyProc(fDialog);
}

inline void IADMDialog::SetNotifierData(ADMUserData data)
{
	sADMDialog->SetNotifierData(fDialog, data);
}

inline ADMUserData IADMDialog::GetNotifierData()
{
	return sADMDialog->GetNotifierData(fDialog);
}

inline ADMTimerRef IADMDialog::CreateTimer(unsigned long milliseconds,
		ADMActionMask abortMask, ADMDialogTimerProc timerProc,
		ADMDialogTimerAbortProc abortProc, int options)
{
	return sADMDialog->CreateTimer(fDialog, milliseconds,
		abortMask, timerProc, abortProc, options);
}

inline void IADMDialog::AbortTimer(ADMTimerRef timer)
{
	sADMDialog->AbortTimer(fDialog, timer);
}

inline ADMBoolean IADMDialog::IsCollapsed()
{
	return sADMDialog->IsCollapsed(fDialog);
}

#if 0
inline void IADMDialog::SetForcedOnScreen(ADMBoolean inForcedOnScreen)
{
	sADMDialog->SetForcedOnScreen(fDialog, inForcedOnScreen);
}
#endif

inline ADMErr IADMDialog::SetIcon(bool rollover, ADMIconRef icon)
{
	return sADMDialog->SetIcon(fDialog, rollover, icon);
}

inline ADMErr IADMDialog::SetToolbarIcon(ADMToolbarIconType type, ADMIconRef icon)
{
	return sADMDialog->SetToolbarIcon(fDialog, type, icon);
}

inline ADMErr IADMDialog::SetToolbarMode(ADMToolbarMode mode)
{
	return sADMDialog->SetToolbarMode(fDialog, mode);
}

inline ADMErr IADMDialog::GetToolbarMode(ADMToolbarMode &mode)
{
	return sADMDialog->GetToolbarMode(fDialog, mode);
}

#endif
