#ifndef __BaseADMImageItem__
#define __BaseADMImageItem__
/***********************************************************************/
/*                                                                     */
/* BaseADMImageItem.hpp                                                */
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
 
#include "BaseADMItem.hpp"

#ifndef __IADMImage_hpp__
#include "IADMImage.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMImageItem : public BaseADMItem
{

protected:
	IADMImage fImage;

	virtual ASBoolean UseImage();
	virtual void BaseDraw(IADMDrawer drawer);

public:	
	BaseADMImageItem(IADMItem item, ADMUserData data = NULL);
	
	virtual ~BaseADMImageItem();
};

#endif //__BaseADMImageItem__