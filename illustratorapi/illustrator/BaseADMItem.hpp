#ifndef __BaseADMItem__
#define __BaseADMItem__
/***********************************************************************/
/*                                                                     */
/* BaseADMItem.hpp                                                     */
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
/* Started by Dave Lazarony, 03/06/1996                                */
/*                                                                     */
/***********************************************************************/


/*
 * Includes
 */

#ifndef __IADMItem_hpp__
#include "IADMItem.hpp"
#endif

#ifndef __IADMDialog_hpp__
#include "IADMDialog.hpp"
#endif

#include "ASTypes.h"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMItem : public IADMItem
{
private:
	static ASErr ASAPI InitProc(ADMItemRef item);
	static void ASAPI NotifyProc(ADMItemRef item, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMItemRef item);
	static ASBoolean ASAPI TextToFloatProc(ADMItemRef item, const char* text, float* value);
	static ASBoolean ASAPI FloatToTextProc(ADMItemRef item, float value, char* text, long textLength);

protected:
	static void ASAPI DrawProc(ADMItemRef item, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMItemRef item, ADMTrackerRef tracker);

protected:
	ADMUserData fUserData;

	virtual ASErr Init();
	virtual void Draw(IADMDrawer drawer);
	virtual ASBoolean Track(IADMTracker tracker);
	virtual void Notify(IADMNotifier notifier);
	virtual ASBoolean TextToFloat(const char* text, float& value);
	virtual ASBoolean FloatToText(float value, char* text, int textLength);

	virtual void BaseDraw(IADMDrawer drawer);

public:
	BaseADMItem(IADMItem item, ADMUserData data = NULL);

	virtual ~BaseADMItem();

	virtual ADMItemRef Create(ADMDialogRef dialog, const IADMRect& boundsRect, ADMItemType itemType = kADMUserType, int itemID = kADMUniqueItemID);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();

	IADMItem GetItem();

	ASErr DoInit();
};

class BaseADMSpinEditPopupItem : public BaseADMItem
{
public:
	BaseADMSpinEditPopupItem(IADMItem item, ADMUserData data = NULL);
	virtual ~BaseADMSpinEditPopupItem() {}
};

class BaseADMEditTextPopupItem : public BaseADMItem
{
public:
	BaseADMEditTextPopupItem(IADMItem item, ADMUserData data = NULL);
	virtual ~BaseADMEditTextPopupItem() {}
};

inline void BaseADMItem::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMItem::GetUserData()
{
	return fUserData;
}

inline IADMItem BaseADMItem::GetItem()
{
	return fItem;
}

inline ASErr BaseADMItem::DoInit()
{
	return Init();
}

#endif //BaseADMItem
