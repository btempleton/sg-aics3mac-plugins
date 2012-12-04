/***********************************************************************/
/*                                                                     */
/* BaseADMHierarchyList.cpp                                            */
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

#include "BaseADMHierarchyList.hpp"

/*
 * Constructor
 */

BaseADMHierarchyList::BaseADMHierarchyList(IADMHierarchyList list, ADMUserData data)								
{
	fList = list;
	fUserData = data;

	if (fList)
	{
		sADMHierarchyList->SetUserData(fList, this);
	}
}


/*
 * Destructor
 */

BaseADMHierarchyList::~BaseADMHierarchyList()
{
	if (sADMHierarchyList)
	{
		sADMHierarchyList->SetUserData(fList, NULL);
			
		/* Don't touch these. If this list class object
		   is deleted in the plug-in before associated ADMList
		   object is deleted in ADM, we'll need these procs
		   still set on that side of ADM to make sure any entry
		   data on this side is cleaned up.

		sADMHierarchyList->SetUserData(fList, NULL);
		sADMHierarchyList->SetDrawProc(fList, NULL);
		sADMHierarchyList->SetNotifyProc(fList, NULL);
		sADMHierarchyList->SetDestroyProc(fList, NULL);

		*/
	}
			
	fList = NULL;
}

