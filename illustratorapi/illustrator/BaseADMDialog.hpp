#ifndef __BaseADMDialog__
#define __BaseADMDialog__

/***********************************************************************/
/*                                                                     */
/* BaseADMDialog.hpp                                                   */
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
 
#ifndef __IADMDialog_hpp__
#include "IADMDialog.hpp"
#endif

#ifndef __IADMItem_hpp__
#include "IADMItem.hpp"
#endif

#include "ASTypes.h"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMDialog : public IADMDialog
{
private:
	static ASErr ASAPI InitProc(ADMDialogRef dialog);
	static void ASAPI DrawProc(ADMDialogRef dialog, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMDialogRef dialog, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMDialogRef dialog, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMDialogRef dialog);

	ASBoolean fIsModal;

protected:
//	IADMDialog fDialog;
	ADMUserData fUserData;
	
	virtual ASErr Init();
	virtual void Draw(IADMDrawer drawer);
	virtual ASBoolean Track(IADMTracker tracker);
	virtual void Notify(IADMNotifier notifier);
	virtual void Destroy();
	
	IADMItem GetItem(int itemID);
	
public:
	BaseADMDialog();
	
	virtual ~BaseADMDialog();	
	
	virtual ADMDialogRef Create(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style, int options = 0);
	virtual int Modal(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style = kADMModalDialogStyle, int options = 0);
	virtual int PopupModal(SPPluginRef pluginRef, char* name, int dialogID, int options = 0);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
	IADMDialog GetDialog();
};


inline IADMItem BaseADMDialog::GetItem(int itemID) 
{ 
	return IADMDialog::GetItem(itemID); 
}

	
inline void BaseADMDialog::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMDialog::GetUserData()
{
	return fUserData;
}

inline IADMDialog BaseADMDialog::GetDialog()
{
	return IADMDialog::GetDialogRef(); //fDialog;
}

#endif
