/***********************************************************************/
/*                                                                     */
/* BaseADMItem.cpp                                                     */
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
/* Started by Dave Lazarony, 03/11/1996                                */
/*                                                                     */
/***********************************************************************/

/*
 * Includes
 */

#include "BaseADMItem.hpp"
#include "IADMDrawer.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"

/*
 * Constructor
 */

BaseADMItem::BaseADMItem(IADMItem item, ADMUserData data)	
: IADMItem(item)							
{
	fUserData = data;

	if (fItem)
	{
		sADMItem->SetUserData(fItem, this);

		sADMItem->SetDrawProc(fItem, DrawProc);
		sADMItem->SetTrackProc(fItem, TrackProc);
		sADMItem->SetNotifyProc(fItem, NotifyProc);
		sADMItem->SetDestroyProc(fItem, DestroyProc);
		sADMItem->SetTextToFloatProc(fItem, TextToFloatProc);
		sADMItem->SetFloatToTextProc(fItem, FloatToTextProc);
	}
}


/*
 * Destructor
 */

BaseADMItem::~BaseADMItem()
{
	if (sADMItem)
	{
		sADMItem->SetUserData(fItem, NULL);
		sADMItem->SetDrawProc(fItem, NULL);
		sADMItem->SetTrackProc(fItem, NULL);
		sADMItem->SetNotifyProc(fItem, NULL);
		sADMItem->SetDestroyProc(fItem, NULL);
// Spin Edit Popup controls will crash if the next two methods are called within the destructor mechanism.
// Fortunately, these services are not needed during destruction and neglecting to set them to NULL is harmless.
//		sADMItem->SetTextToFloatProc(fItem, NULL);
//		sADMItem->SetFloatToTextProc(fItem, NULL);
	
		sADMItem->Destroy(fItem);
	}
			
	fItem = NULL;
}


ADMItemRef BaseADMItem::Create(ADMDialogRef dialog, const IADMRect& boundsRect, ADMItemType itemType, int itemID)								
{
	fItem = sADMItem->Create(dialog, itemID, itemType, (ADMRect*) &boundsRect, InitProc, this, 0);
	
	if (fItem)
	{
		sADMItem->SetDrawProc(fItem, DrawProc);
		sADMItem->SetTrackProc(fItem, TrackProc);
		sADMItem->SetNotifyProc(fItem, NotifyProc);
		sADMItem->SetDestroyProc(fItem, DestroyProc);
		sADMItem->SetTextToFloatProc(fItem, TextToFloatProc);
		sADMItem->SetFloatToTextProc(fItem, FloatToTextProc);
	}

	return fItem;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
ASErr BaseADMItem::Init()
{
	return kNoErr;
}

void BaseADMItem::Draw(IADMDrawer drawer)
{
	sADMItem->DefaultDraw(fItem, drawer);
}

ASBoolean BaseADMItem::Track(IADMTracker tracker)
{
	return sADMItem->DefaultTrack(fItem, tracker);
}

void BaseADMItem::Notify(IADMNotifier notifier)
{
	sADMItem->DefaultNotify(fItem, notifier);
}

ASBoolean BaseADMItem::TextToFloat(const char* text, float& value)
{
	return sADMItem->DefaultTextToFloat(fItem, text, &value);
}

ASBoolean BaseADMItem::FloatToText(float value, char* text, int textLength)
{
	return sADMItem->DefaultFloatToText(fItem, value, text, textLength);
}


/*
 * Static Procs that call Virtual Functions.
 */
	
ASErr ASAPI BaseADMItem::InitProc(ADMItemRef item)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	admItem->fItem = item;

	if (admItem)
		return admItem->Init();
	else
		return kBadParameterErr;
}

void ASAPI BaseADMItem::DrawProc(ADMItemRef item, ADMDrawerRef drawer)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		admItem->BaseDraw(drawer);
}

ASBoolean ASAPI BaseADMItem::TrackProc(ADMItemRef item, ADMTrackerRef tracker)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->Track(tracker);
	else
		return false;
}

void ASAPI BaseADMItem::NotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		admItem->Notify(notifier);
}

void ASAPI BaseADMItem::DestroyProc(ADMItemRef item)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		delete admItem;
}

ASBoolean ASAPI BaseADMItem::TextToFloatProc(ADMItemRef item, const char* text, float* value)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->TextToFloat(text,* value);
	else
		return false;
}

ASBoolean ASAPI BaseADMItem::FloatToTextProc(ADMItemRef item, float value, char* text, long textLength)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->FloatToText(value, text, textLength);
	else
		return false;
}

void BaseADMItem::BaseDraw(IADMDrawer drawer)
{
	Draw(drawer);
}


BaseADMSpinEditPopupItem::BaseADMSpinEditPopupItem(IADMItem item, ADMUserData data) : BaseADMItem(item, data)
{
	ADMItemRef childItem = sADMItem->GetChildItem(fItem, kADMSpinEditTextEditChildID);
	if (childItem)
		sADMItem->SetUserData(childItem, this);
}


BaseADMEditTextPopupItem::BaseADMEditTextPopupItem(IADMItem item, ADMUserData data) : BaseADMItem(item, data)
{
	ADMItemRef childItem = sADMItem->GetChildItem(fItem, kADMTextEditPopupTextEditChildID);
	if (childItem)
		sADMItem->SetUserData(childItem, this);
}

