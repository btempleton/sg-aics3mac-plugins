#ifndef __BaseADMList__
#define __BaseADMList__
/***********************************************************************/
/*                                                                     */
/* BaseADMList.hpp                                                     */
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
 
#ifndef __IADMList_hpp__
#include "IADMList.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMList : public IADMList
{
protected:
//	IADMList fList;
	ADMUserData fUserData;

public:	
	BaseADMList(IADMList list, ADMUserData data = NULL);
	virtual ~BaseADMList();

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
//	IADMList GetList();
};


inline void BaseADMList::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMList::GetUserData()
{
	return fUserData;
}

/*
inline IADMList BaseADMList::GetList()
{
	return fList;
}
*/

#endif //__BaseADMList__
