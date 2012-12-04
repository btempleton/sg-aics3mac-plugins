/***********************************************************************/
/*                                                                     */
/* IADMDrawer5.hpp                                                     */
/* Object wrapper for ADM Drawer Suite Version 5                       */
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

#ifndef __IADMDrawer5_hpp__
#define __IADMDrawer5_hpp__

/*
 * Includes
 */
 
#ifndef __ADMDrawer__
#include "ADMDrawer.h"
#endif

#ifndef __IADMTypes_hpp__
#include "IADMTypes.hpp"
#endif

#include "ADMAGMTypes.h"

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif


/*
 * Forward Declarations
 */
 
extern "C" typedef struct SPPlugin SPPlugin;

/*
 * Global Suite Pointer
 */

extern "C" ADMDrawerSuite5* sADMDrawer5;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif

// majones: UNICODE 12/19/02 DrawText needs to be undefined as it it clashes with
//          a Microsoft API definition in Winuser.h when the UNICODE pre-processor
//          option is used.
#undef DrawText	


/*
 * Wrapper Class
 */

class IADMDrawer5
{
private:
	ADMDrawerRef fDrawer;

public:	
	IADMDrawer5();
	IADMDrawer5(ADMDrawerRef c);
	
	operator ADMDrawerRef (void);
	
	
	ADMPortRef GetPortRef();
	
	void Clear();
	
	void GetBoundsRect(IADMRect& boundsRect);
	
	
	void GetClipRect(IADMRect& clipRect);
	void SetClipRect(const IADMRect& clipRect);
	void IntersectClipRect(const IADMRect& clipRect);
	void UnionClipRect(const IADMRect& clipRect);
	void SubtractClipRect(const IADMRect& clipRect);

	void SetClipPolygon(const IADMPoint* points, int numPoints);
	void IntersectClipPolygon(const IADMPoint* points, int numPoints);
	void UnionClipPolygon(const IADMPoint* points, int numPoints);
	void SubtractClipPolygon(const IADMPoint* points, int numPoints);

	void GetOrigin(IADMPoint& origin);
	void SetOrigin(const IADMPoint& origin);
	
	void GetRGBColor(ADMRGBColor& color);
	void SetRGBColor(const ADMRGBColor& color);
	
	ADMColor GetADMColor();
	void SetADMColor(ADMColor color);
	
	ADMDrawMode GetDrawMode();
	void SetDrawMode(ADMDrawMode drawMode);
	
	ADMFont GetFont();
	void SetFont(ADMFont font);
	
	
	void DrawLine(const IADMPoint& startPoint, const IADMPoint& endPoint);
	
	void DrawPolygon(const IADMPoint* points, int numPoints);
	void FillPolygon(const IADMPoint* points, int numPoints);
	
	void DrawRect(const IADMRect& rect);
	void FillRect(const IADMRect& rect);
	void ClearRect(const IADMRect& rect);
	void DrawSunkenRect(const IADMRect& rect);
	void DrawRaisedRect(const IADMRect& rect);
	void InvertRect(const IADMRect& rect);
	
	void DrawOval(const IADMRect& rect);
	void FillOval(const IADMRect& rect);
	
	ADMAGMPortPtr GetAGMPort();
	void DrawAGMImage(ADMAGMImageRecord* image, ADMFixedMatrix* matrix, long flags);

	void DrawADMImage(ADMImageRef image, const IADMPoint& topLeftPoint);
	void DrawADMImageCentered(ADMImageRef image, const IADMRect& rect);

	void DrawResPicture(SPPlugin* pluginRef, int resID, const IADMPoint& topLeftPoint, ADMRecolorStyle style = kADMNoRecolor);
	void DrawResPictureCentered(SPPlugin* pluginRef, int resID, const IADMRect& rect, ADMRecolorStyle style = kADMNoRecolor);

	void DrawIcon(ADMIconRef icon, const IADMPoint& topLeftPoint, ADMRecolorStyle style = kADMNoRecolor);
	void DrawIconCentered(ADMIconRef icon, const IADMRect& rect, ADMRecolorStyle style = kADMNoRecolor);

	void GetResPictureBounds(struct SPPlugin* pluginRef, int resID, IADMRect& boundsRect);

#ifdef USING_ZADM
	int GetTextWidth( const ASZString text );
#else
	int GetTextWidth(const char* text);
#endif
	ADMInt32 GetTextWidthW(const ADMUnicode* inText);

	void GetFontInfo(const ADMFontInfo& fontInfo);
	
#ifdef USING_ZADM
	void DrawText( const ASZString text, const IADMPoint& point );
	
	void DrawTextLeft( const ASZString text, const IADMRect& rect );
	void DrawTextCentered( const ASZString text, const IADMRect& rect );
	void DrawTextRight( const ASZString text, const IADMRect& rect );
#else
	void DrawText(const char* text, const IADMPoint& point);

	void DrawTextLeftW(const ADMUnicode* text, const IADMRect& rect);
	void DrawTextCenteredW(const ADMUnicode* text, const IADMRect& rect);
	void DrawTextRightW(const ADMUnicode* text, const IADMRect& rect);
	void DrawTextLeft(const char* text, const IADMRect& rect);
	void DrawTextCentered(const char* text, const IADMRect& rect);
	void DrawTextRight(const char* text, const IADMRect& rect);
#endif
	
	void DrawUpArrow(const IADMRect& rect);
	void DrawDownArrow(const IADMRect& rect);
	void DrawLeftArrow(const IADMRect& rect);
	void DrawRightArrow(const IADMRect& rect);	
};

inline IADMDrawer5::IADMDrawer5()								
{
	fDrawer = NULL;
}

inline IADMDrawer5::IADMDrawer5(ADMDrawerRef drawer)	
{
	fDrawer = drawer;
}

inline IADMDrawer5::operator ADMDrawerRef (void)
{
	return fDrawer;
}

inline ADMPortRef IADMDrawer5::GetPortRef()
{
	return sADMDrawer5->GetPortRef(fDrawer);
}

inline void IADMDrawer5::Clear()
{
	sADMDrawer5->Clear(fDrawer);
}
	
inline void IADMDrawer5::GetBoundsRect(IADMRect& boundsRect)
{
	sADMDrawer5->GetBoundsRect(fDrawer, &boundsRect);
}

inline void IADMDrawer5::GetClipRect(IADMRect& clipRect)
{
	sADMDrawer5->GetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer5::SetClipRect(const IADMRect& clipRect)
{
	sADMDrawer5->SetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer5::IntersectClipRect(const IADMRect& clipRect)
{
	sADMDrawer5->IntersectClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer5::UnionClipRect(const IADMRect& clipRect)
{
	sADMDrawer5->UnionClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer5::SubtractClipRect(const IADMRect& clipRect)
{
	sADMDrawer5->SubtractClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer5::SetClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->SetClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::IntersectClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->IntersectClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::UnionClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->UnionClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::SubtractClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->SubtractClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::GetOrigin(IADMPoint& origin)
{
	sADMDrawer5->GetOrigin(fDrawer, &origin);
}

inline void IADMDrawer5::SetOrigin(const IADMPoint& origin)
{
	sADMDrawer5->SetOrigin(fDrawer, &origin);
}

inline void IADMDrawer5::GetRGBColor(ADMRGBColor& color)
{
	sADMDrawer5->GetRGBColor(fDrawer, &color);
}

inline void IADMDrawer5::SetRGBColor(const ADMRGBColor& color)
{
	sADMDrawer5->SetRGBColor(fDrawer, &color);
}

inline ADMColor IADMDrawer5::GetADMColor()
{
	return sADMDrawer5->GetADMColor(fDrawer);
}

inline void IADMDrawer5::SetADMColor(ADMColor color)
{
	sADMDrawer5->SetADMColor(fDrawer, color);
}

inline ADMDrawMode IADMDrawer5::GetDrawMode()
{
	return sADMDrawer5->GetDrawMode(fDrawer);
}

inline void IADMDrawer5::SetDrawMode(ADMDrawMode drawMode)
{
	sADMDrawer5->SetDrawMode(fDrawer, drawMode);
}

inline ADMFont IADMDrawer5::GetFont()
{
	return sADMDrawer5->GetFont(fDrawer);
}

inline void IADMDrawer5::SetFont(ADMFont font)
{
	sADMDrawer5->SetFont(fDrawer, font);
}

inline void IADMDrawer5::DrawLine(const IADMPoint& startPoint, const IADMPoint& endPoint)
{
	sADMDrawer5->DrawLine(fDrawer, &startPoint, &endPoint);
}

inline void IADMDrawer5::DrawPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->DrawPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::FillPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer5->FillPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer5::DrawRect(const IADMRect& rect)
{
	sADMDrawer5->DrawRect(fDrawer, &rect);
}

inline void IADMDrawer5::FillRect(const IADMRect& rect)
{
	sADMDrawer5->FillRect(fDrawer, &rect);
}

inline void IADMDrawer5::ClearRect(const IADMRect& rect)
{
	sADMDrawer5->ClearRect(fDrawer, &rect);
}

inline void IADMDrawer5::DrawSunkenRect(const IADMRect& rect)
{
	sADMDrawer5->DrawSunkenRect(fDrawer, &rect);
}

inline void IADMDrawer5::DrawRaisedRect(const IADMRect& rect)
{
	sADMDrawer5->DrawRaisedRect(fDrawer, &rect);
}

inline void IADMDrawer5::InvertRect(const IADMRect& rect)
{
	sADMDrawer5->InvertRect(fDrawer, &rect);
}

inline void IADMDrawer5::DrawOval(const IADMRect& rect)
{
	sADMDrawer5->DrawOval(fDrawer, &rect);
}

inline void IADMDrawer5::FillOval(const IADMRect& rect)
{
	sADMDrawer5->FillOval(fDrawer, &rect);
}

inline ADMAGMPortPtr IADMDrawer5::GetAGMPort()
{
	return sADMDrawer5->GetAGMPort(fDrawer);
}

inline void IADMDrawer5::DrawAGMImage(ADMAGMImageRecord* image, ADMFixedMatrix* matrix, long flags)
{
	sADMDrawer5->DrawAGMImage(fDrawer, (struct _t_ADMAGMImageRecord*) image, matrix, flags);
}

inline void IADMDrawer5::DrawADMImage(ADMImageRef image, const IADMPoint& topLeftPoint)
{
	sADMDrawer5->DrawADMImage(fDrawer, image, &topLeftPoint);
}

inline void IADMDrawer5::DrawADMImageCentered(ADMImageRef image, const IADMRect& rect)
{
	sADMDrawer5->DrawADMImageCentered(fDrawer, image, &rect);
}

inline void IADMDrawer5::DrawResPicture(SPPlugin* pluginRef, int resID, const IADMPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer5->DrawRecoloredResPicture(fDrawer, pluginRef, resID, &topLeftPoint, style);
}

inline void IADMDrawer5::DrawResPictureCentered(SPPlugin* pluginRef, int resID, const IADMRect& rect, ADMRecolorStyle style)
{
	sADMDrawer5->DrawRecoloredResPictureCentered(fDrawer, pluginRef, resID, &rect, style);
}

inline void IADMDrawer5::DrawIcon(ADMIconRef icon, const IADMPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer5->DrawRecoloredIcon(fDrawer, icon, &topLeftPoint, style);
}

inline void IADMDrawer5::DrawIconCentered(ADMIconRef icon, const IADMRect& rect, ADMRecolorStyle style)
{
	sADMDrawer5->DrawRecoloredIconCentered(fDrawer, icon, &rect, style);
}

inline void IADMDrawer5::GetResPictureBounds(struct SPPlugin* pluginRef, int resID, IADMRect& boundsRect)
{
	sADMDrawer5->GetResPictureBounds(fDrawer, pluginRef, resID, &boundsRect);
}

#ifdef USING_ZADM
inline int IADMDrawer5::GetTextWidth( ASZString text )
{
	return sZADM->DrawerGetTextWidth( fDrawer, text );
}
#else
inline int IADMDrawer5::GetTextWidth(const char* text)
{
	return sADMDrawer5->GetTextWidth(fDrawer, text);
}
#endif

inline ADMInt32 IADMDrawer5::GetTextWidthW(const ADMUnicode* inText)
{
	return sADMDrawer5->GetTextWidthW(fDrawer, inText);
}

inline void IADMDrawer5::GetFontInfo(const ADMFontInfo& fontInfo)
{
	sADMDrawer5->GetFontInfo(fDrawer, (ADMFontInfo*)&fontInfo);
}

#ifdef USING_ZADM
inline void IADMDrawer5::DrawText( const ASZString text, const IADMPoint& point )
{
	sZADM->DrawerDrawText( fDrawer, const_cast< ASZString >( text ), const_cast< IADMPoint* >(& point ) );
}
#else
inline void IADMDrawer5::DrawText(const char* text, const IADMPoint& point)
{
	sADMDrawer5->DrawText(fDrawer, text, &point);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer5::DrawTextLeft( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextLeft( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer5::DrawTextLeft(const char* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextLeft(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer5::DrawTextCentered( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextCentered( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer5::DrawTextCentered(const char* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextCentered(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer5::DrawTextRight( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextRight( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer5::DrawTextRight(const char* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextRight(fDrawer, text, &rect);
}
#endif

inline void IADMDrawer5::DrawTextLeftW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextLeftW(fDrawer, text, &rect);
}

inline void IADMDrawer5::DrawTextCenteredW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextCenteredW(fDrawer, text, &rect);
}

inline void IADMDrawer5::DrawTextRightW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer5->DrawTextRightW(fDrawer, text, &rect);
}

inline void IADMDrawer5::DrawUpArrow(const IADMRect& rect)
{
	sADMDrawer5->DrawUpArrow(fDrawer, &rect);
}	

inline void IADMDrawer5::DrawDownArrow(const IADMRect& rect)
{
	sADMDrawer5->DrawDownArrow(fDrawer, &rect);
}	

inline void IADMDrawer5::DrawLeftArrow(const IADMRect& rect)
{
	sADMDrawer5->DrawLeftArrow(fDrawer, &rect);
}	

inline void IADMDrawer5::DrawRightArrow(const IADMRect& rect)
{
	sADMDrawer5->DrawRightArrow(fDrawer, &rect);
}	

#endif
