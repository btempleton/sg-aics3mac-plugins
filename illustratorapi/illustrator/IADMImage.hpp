/***********************************************************************/
/*                                                                     */
/* IADMImage.hpp                                                       */
/* Object wrapper for ADM Image Suite                                  */
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
/* Started by Dave Lazarony, 11/20/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMImage_hpp__
#define __IADMImage_hpp__

/*
 * Includes
 */
 
#ifndef __ADMImage__
#include "ADMImage.h"
#endif

#ifndef __IADMDrawer_hpp__
#include "IADMDrawer.hpp"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMImageSuite2* sADMImage;

/*
 * Wrapper Class
 */

class IADMImage
{
private:
	ADMImageRef fImage;

public:	
	IADMImage();
	IADMImage(ADMImageRef Image);

	operator ADMImageRef();

	int GetWidth();
	int GetHeight();
	int GetByteWidth();
	int GetBitsPerPixel();
	
	ADMByte* BeginBaseAddressAccess();
	void EndBaseAddressAccess();
	
	IADMDrawer BeginADMDrawer();
	void EndADMDrawer();
	
	void BeginAGMImageAccess(struct _t_ADMAGMImageRecord* imageRecord);
	void EndAGMImageAccess();
	
	ADMErr GetPixel(const IADMPoint& point, ADMRGBColor& color);
	ADMErr SetPixel(const IADMPoint& point, const ADMRGBColor& color);
};


inline IADMImage::IADMImage()	
{ 
	fImage = NULL; 
}

inline IADMImage::IADMImage(ADMImageRef Image)		
{ 
	fImage = Image; 
}

inline IADMImage::operator ADMImageRef()				
{ 
	return fImage; 
}

inline int IADMImage::GetWidth()						
{ 
	return sADMImage->GetWidth(fImage); 
}

inline int IADMImage::GetHeight()						
{ 
	return sADMImage->GetHeight(fImage); 
}

inline int IADMImage::GetByteWidth()					
{ 
	return sADMImage->GetByteWidth(fImage); 
}

inline int IADMImage::GetBitsPerPixel()				
{ 
	return sADMImage->GetBitsPerPixel(fImage); 
}

inline ADMByte* IADMImage::BeginBaseAddressAccess()				
{ 
	return sADMImage->BeginBaseAddressAccess(fImage); 
}

inline void IADMImage::EndBaseAddressAccess()				
{ 
	sADMImage->EndBaseAddressAccess(fImage); 
}

inline IADMDrawer IADMImage::BeginADMDrawer()		
{ 
	return sADMImage->BeginADMDrawer(fImage); 
}

inline void IADMImage::EndADMDrawer()		
{ 
	sADMImage->EndADMDrawer(fImage); 
}

inline void IADMImage::BeginAGMImageAccess(struct _t_ADMAGMImageRecord* imageRecord)	
{ 
	sADMImage->BeginAGMImageAccess(fImage, imageRecord); 
}

inline void IADMImage::EndAGMImageAccess()	
{ 
	sADMImage->EndAGMImageAccess(fImage); 
}

inline ADMErr IADMImage::GetPixel(const IADMPoint& point, ADMRGBColor& color)
{
	return sADMImage->GetPixel(fImage, &point, &color);
}

inline ADMErr IADMImage::SetPixel(const IADMPoint& point, const ADMRGBColor& color)
{
	return sADMImage->SetPixel(fImage, &point, &color);
}

#endif
