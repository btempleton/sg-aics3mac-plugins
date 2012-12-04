#ifndef __BaseADMHierarchyList__
#define __BaseADMHierarchyList__
/***********************************************************************/
/*                                                                     */
/* BaseADMHierarchyList.hpp                                            */
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
 
#ifndef __IADMHierarchyList_hpp__
#include "IADMHierarchyList.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMHierarchyList : public IADMHierarchyList
{
protected:
	ADMUserData fUserData;

public:	
	BaseADMHierarchyList(IADMHierarchyList list, ADMUserData data = NULL);
	virtual ~BaseADMHierarchyList();

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
};


inline void BaseADMHierarchyList::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMHierarchyList::GetUserData()
{
	return fUserData;
}

#endif //BaseADMHierarchyList