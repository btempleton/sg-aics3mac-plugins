/***********************************************************************/
/*                                                                     */
/* IADMDrawer.hpp                                                      */
/* Object wrapper for ADM Drawer Suite                                 */
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

#ifndef __IADMDrawer_hpp__
#define __IADMDrawer_hpp__

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

extern "C" ADMDrawerSuite* sADMDrawer;

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

class IADMDrawer
{
private:
	ADMDrawerRef fDrawer;

public:	
	IADMDrawer();
	IADMDrawer(ADMDrawerRef c);
	
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

	ADMBoolean GetUsePaletteBGColor();
	void SetUsePaletteBGColor(ADMBoolean inUsePaletteBGColor);
	
	
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
	int GetTextWidthW(const ADMUnicode* text);
	void GetFontInfo(const ADMFontInfo& fontInfo);
	
#ifdef USING_ZADM
	void DrawText( const ASZString text, const IADMPoint& point );
	
	void DrawTextLeft( const ASZString text, const IADMRect& rect );
	void DrawTextCentered( const ASZString text, const IADMRect& rect );
	void DrawTextRight( const ASZString text, const IADMRect& rect );
#else
	void DrawText(const char* text, const IADMPoint& point);
	
	void DrawTextLeft(const char* text, const IADMRect& rect);
	void DrawTextCentered(const char* text, const IADMRect& rect);
	void DrawTextRight(const char* text, const IADMRect& rect);
#endif
	
	void DrawTextW(const ADMUnicode* text, const IADMPoint& point);
	
	void DrawTextLeftW(const ADMUnicode* text, const IADMRect& rect);
	void DrawTextCenteredW(const ADMUnicode* text, const IADMRect& rect);
	void DrawTextRightW(const ADMUnicode* text, const IADMRect& rect);

	void DrawUpArrow(const IADMRect& rect);
	void DrawDownArrow(const IADMRect& rect);
	void DrawLeftArrow(const IADMRect& rect);
	void DrawRightArrow(const IADMRect& rect);	
};

inline IADMDrawer::IADMDrawer()								
{
	fDrawer = NULL;
}

inline IADMDrawer::IADMDrawer(ADMDrawerRef drawer)	
{
	fDrawer = drawer;
}

inline IADMDrawer::operator ADMDrawerRef (void)
{
	return fDrawer;
}

inline ADMPortRef IADMDrawer::GetPortRef()
{
	return sADMDrawer->GetPortRef(fDrawer);
}

inline void IADMDrawer::Clear()
{
	sADMDrawer->Clear(fDrawer);
}
	
inline void IADMDrawer::GetBoundsRect(IADMRect& boundsRect)
{
	sADMDrawer->GetBoundsRect(fDrawer, &boundsRect);
}

inline void IADMDrawer::GetClipRect(IADMRect& clipRect)
{
	sADMDrawer->GetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SetClipRect(const IADMRect& clipRect)
{
	sADMDrawer->SetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::IntersectClipRect(const IADMRect& clipRect)
{
	sADMDrawer->IntersectClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::UnionClipRect(const IADMRect& clipRect)
{
	sADMDrawer->UnionClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SubtractClipRect(const IADMRect& clipRect)
{
	sADMDrawer->SubtractClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SetClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->SetClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::IntersectClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->IntersectClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::UnionClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->UnionClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::SubtractClipPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->SubtractClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::GetOrigin(IADMPoint& origin)
{
	sADMDrawer->GetOrigin(fDrawer, &origin);
}

inline void IADMDrawer::SetOrigin(const IADMPoint& origin)
{
	sADMDrawer->SetOrigin(fDrawer, &origin);
}

inline void IADMDrawer::GetRGBColor(ADMRGBColor& color)
{
	sADMDrawer->GetRGBColor(fDrawer, &color);
}

inline void IADMDrawer::SetRGBColor(const ADMRGBColor& color)
{
	sADMDrawer->SetRGBColor(fDrawer, &color);
}

inline ADMColor IADMDrawer::GetADMColor()
{
	return sADMDrawer->GetADMColor(fDrawer);
}

inline void IADMDrawer::SetADMColor(ADMColor color)
{
	sADMDrawer->SetADMColor(fDrawer, color);
}

inline ADMDrawMode IADMDrawer::GetDrawMode()
{
	return sADMDrawer->GetDrawMode(fDrawer);
}

inline void IADMDrawer::SetDrawMode(ADMDrawMode drawMode)
{
	sADMDrawer->SetDrawMode(fDrawer, drawMode);
}

inline ADMFont IADMDrawer::GetFont()
{
	return sADMDrawer->GetFont(fDrawer);
}

inline void IADMDrawer::SetFont(ADMFont font)
{
	sADMDrawer->SetFont(fDrawer, font);
}

inline ADMBoolean IADMDrawer::GetUsePaletteBGColor()
{
	return sADMDrawer->GetUsePaletteBGColor(fDrawer);
}

inline void IADMDrawer::SetUsePaletteBGColor(ADMBoolean inUsePaletteBGColor)
{
	sADMDrawer->SetUsePaletteBGColor(fDrawer, inUsePaletteBGColor);
}

inline void IADMDrawer::DrawLine(const IADMPoint& startPoint, const IADMPoint& endPoint)
{
	sADMDrawer->DrawLine(fDrawer, &startPoint, &endPoint);
}

inline void IADMDrawer::DrawPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->DrawPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::FillPolygon(const IADMPoint* points, int numPoints)
{
	sADMDrawer->FillPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::DrawRect(const IADMRect& rect)
{
	sADMDrawer->DrawRect(fDrawer, &rect);
}

inline void IADMDrawer::FillRect(const IADMRect& rect)
{
	sADMDrawer->FillRect(fDrawer, &rect);
}

inline void IADMDrawer::ClearRect(const IADMRect& rect)
{
	sADMDrawer->ClearRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawSunkenRect(const IADMRect& rect)
{
	sADMDrawer->DrawSunkenRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawRaisedRect(const IADMRect& rect)
{
	sADMDrawer->DrawRaisedRect(fDrawer, &rect);
}

inline void IADMDrawer::InvertRect(const IADMRect& rect)
{
	sADMDrawer->InvertRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawOval(const IADMRect& rect)
{
	sADMDrawer->DrawOval(fDrawer, &rect);
}

inline void IADMDrawer::FillOval(const IADMRect& rect)
{
	sADMDrawer->FillOval(fDrawer, &rect);
}

inline ADMAGMPortPtr IADMDrawer::GetAGMPort()
{
	return sADMDrawer->GetAGMPort(fDrawer);
}

inline void IADMDrawer::DrawAGMImage(ADMAGMImageRecord* image, ADMFixedMatrix* matrix, long flags)
{
	sADMDrawer->DrawAGMImage(fDrawer, (struct _t_ADMAGMImageRecord*) image, matrix, flags);
}

inline void IADMDrawer::DrawADMImage(ADMImageRef image, const IADMPoint& topLeftPoint)
{
	sADMDrawer->DrawADMImage(fDrawer, image, &topLeftPoint);
}

inline void IADMDrawer::DrawADMImageCentered(ADMImageRef image, const IADMRect& rect)
{
	sADMDrawer->DrawADMImageCentered(fDrawer, image, &rect);
}

inline void IADMDrawer::DrawResPicture(SPPlugin* pluginRef, int resID, const IADMPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredResPicture(fDrawer, pluginRef, resID, &topLeftPoint, style);
}

inline void IADMDrawer::DrawResPictureCentered(SPPlugin* pluginRef, int resID, const IADMRect& rect, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredResPictureCentered(fDrawer, pluginRef, resID, &rect, style);
}

inline void IADMDrawer::DrawIcon(ADMIconRef icon, const IADMPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredIcon(fDrawer, icon, &topLeftPoint, style);
}

inline void IADMDrawer::DrawIconCentered(ADMIconRef icon, const IADMRect& rect, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredIconCentered(fDrawer, icon, &rect, style);
}

inline void IADMDrawer::GetResPictureBounds(struct SPPlugin* pluginRef, int resID, IADMRect& boundsRect)
{
	sADMDrawer->GetResPictureBounds(fDrawer, pluginRef, resID, &boundsRect);
}

#ifdef USING_ZADM
inline int IADMDrawer::GetTextWidth( ASZString text )
{
	return sZADM->DrawerGetTextWidth( fDrawer, text );
}
#else
inline int IADMDrawer::GetTextWidth(const char* text)
{
	return sADMDrawer->GetTextWidth(fDrawer, text);
}
#endif

inline int IADMDrawer::GetTextWidthW(const ADMUnicode* text)
{
	return sADMDrawer->GetTextWidthW(fDrawer, text);
}

inline void IADMDrawer::GetFontInfo(const ADMFontInfo& fontInfo)
{
	sADMDrawer->GetFontInfo(fDrawer, (ADMFontInfo*)&fontInfo);
}

#ifdef USING_ZADM
inline void IADMDrawer::DrawText( const ASZString text, const IADMPoint& point )
{
	sZADM->DrawerDrawText( fDrawer, const_cast< ASZString >( text ), const_cast< IADMPoint* >(& point ) );
}
#else
inline void IADMDrawer::DrawText(const char* text, const IADMPoint& point)
{
	sADMDrawer->DrawText(fDrawer, text, &point);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextLeft( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextLeft( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextLeft(const char* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextLeft(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextCentered( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextCentered( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextCentered(const char* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextCentered(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextRight( const ASZString text, const IADMRect& rect )
{
	sZADM->DrawerDrawTextRight( fDrawer, const_cast< ASZString >( text ), const_cast< IADMRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextRight(const char* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextRight(fDrawer, text, &rect);
}
#endif

inline void IADMDrawer::DrawTextW(const ADMUnicode* text, const IADMPoint& point)
{
	sADMDrawer->DrawTextW(fDrawer, text, &point);
}

inline void IADMDrawer::DrawTextLeftW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextLeftW(fDrawer, text, &rect);
}

inline void IADMDrawer::DrawTextCenteredW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextCenteredW(fDrawer, text, &rect);
}

inline void IADMDrawer::DrawTextRightW(const ADMUnicode* text, const IADMRect& rect)
{
	sADMDrawer->DrawTextRightW(fDrawer, text, &rect);
}

inline void IADMDrawer::DrawUpArrow(const IADMRect& rect)
{
	sADMDrawer->DrawUpArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawDownArrow(const IADMRect& rect)
{
	sADMDrawer->DrawDownArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawLeftArrow(const IADMRect& rect)
{
	sADMDrawer->DrawLeftArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawRightArrow(const IADMRect& rect)
{
	sADMDrawer->DrawRightArrow(fDrawer, &rect);
}	

#endif
