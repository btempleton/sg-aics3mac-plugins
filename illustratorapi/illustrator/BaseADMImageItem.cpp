/***********************************************************************/
/*                                                                     */
/* BaseADMImageItem.cpp                                                */
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

#include "BaseADMImageItem.hpp"
#include "IADMDrawer.hpp"

//#include "AGMImage.h"

/*
 * Constructor
 */

BaseADMImageItem::BaseADMImageItem(IADMItem item, ADMUserData data) : BaseADMItem(item, data)								
{
	fImage = NULL;
}


/*
 * Destructor
 */

BaseADMImageItem::~BaseADMImageItem()
{
	if (fImage && sADMImage)
	{
		sADMImage->Destroy(fImage);
		fImage = NULL;
	}
}


/*
 * Virtual Functions that call Defaults.
 */
	
/*
 * Static Procs that call Virtual Functions.
 */
	
ASBoolean BaseADMImageItem::UseImage()
{
	return true;
}

void BaseADMImageItem::BaseDraw(IADMDrawer drawer)
{
	ASBoolean needNormalDraw = true;

	if (UseImage())
	{
		IADMRect boundsRect;

		drawer.GetBoundsRect(boundsRect);
	
		if (fImage && (fImage.GetWidth() != boundsRect.Width() || fImage.GetHeight() != boundsRect.Height()))
		{
			sADMImage->Destroy(fImage);
			fImage = NULL;
		}

		if (!fImage && boundsRect.Width() != 0 && boundsRect.Height() != 0)
			fImage = sADMImage->CreateOffscreen(boundsRect.Width(), boundsRect.Height(), 0);
		
		if (fImage)	
		{
			IADMDrawer imageDrawer = fImage.BeginADMDrawer();
			
			if (imageDrawer)
			{
				// Make sure we are using the same background color as original drawer
				imageDrawer.SetUsePaletteBGColor( drawer.GetUsePaletteBGColor() );
				
				imageDrawer.ClearRect(boundsRect);
				
				Draw(imageDrawer);

				fImage.EndADMDrawer();

				needNormalDraw = false;
			}
			
			IADMPoint point(0, 0);

			drawer.DrawADMImage(fImage, point);
		}
	}
	
	if (needNormalDraw)
		Draw(drawer);
}
