/***********************************************************************/
/*                                                                     */
/* IADMRect.hpp                                                         */
/* ADMRect object wrapper class                                         */
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
/***********************************************************************/

#ifndef __IADMRect_hpp__
#define __IADMRect_hpp__

/*
 * Includes
 */
 
#ifndef __ADMTypes__
#include "ADMStandardTypes.h"
#endif

/*
 * Wrapper Class
 */

struct IADMRect : public ADMRect
{
public:	
	IADMRect();
	IADMRect(const ADMRect& rect);
	IADMRect(const ADMPoint& a);
	IADMRect(const ADMPoint& a, const ADMPoint& b);
	IADMRect(int left, int top, int right, int bottom);
	
	int Width() const;
	int Height() const;
	
	ADMBoolean IsEmpty() const;
	void SetEmpty();
	
	ADMBoolean IsNormalized() const;	
	void Normalize();

	int Area() const;
	
	ADMPoint Center() const;
	
	ADMBoolean Contains(const ADMPoint& p) const;
	ADMBoolean Contains(const ADMRect& r) const;
	
	ADMBoolean Overlaps(const ADMRect& r) const;
	
	IADMRect& operator ++ ();
	IADMRect& operator -- ();
	IADMRect operator ++ (int);
	IADMRect operator -- (int);
	IADMRect& operator += (int n);
	IADMRect& operator -= (int n);
	
	IADMRect& operator += (ADMPoint& p);
	IADMRect& operator -= (ADMPoint& p);
	
	IADMRect& operator = (ADMPoint& p);
	
	void Inset(int h, int v);
	void Inflate(int h, int v);
	void Offset(int h, int v);
	
	void Union(const ADMPoint& a);
	void Union(const ADMRect& a);
	void Union(const ADMRect& a, const ADMRect& b);
	
	void Intersect(const ADMRect& a);
	void Intersect(const ADMRect& a, const ADMRect& b);
	
	void Center(const ADMRect& centerRect);
	
	friend inline ADMBoolean operator == (const ADMRect& a, const ADMRect& b);
	friend inline ADMBoolean operator != (const ADMRect& a, const ADMRect& b);

// Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96	
//	friend inline ADMRect operator + (const IADMRect& a, const IADMPoint& b);
//	friend inline ADMRect operator + (const IADMPoint& a, const IADMRect& b);
//	friend inline ADMRect operator - (const IADMRect& a, const IADMPoint& b);
//	friend inline ADMRect operator - (const IADMPoint& a, const IADMRect& b);
};

inline IADMRect::IADMRect() 					
{
}

inline IADMRect::IADMRect(const ADMRect& rect) 
{ 
	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom; 
}

inline IADMRect::IADMRect(const ADMPoint& a)	
{ 
	left = right = a.h; 
	top = bottom = a.v; 
}

inline IADMRect::IADMRect(const ADMPoint& a, const ADMPoint& b)
{
	if (a.h < b.h)
	{
		left = a.h;
		right = b.h;
	}
	else
	{
		left = b.h;
		right = a.h;
	}
	
	if (a.v < b.v)
	{
		top = a.v;
		bottom = b.v;
	}
	else
	{
		top = b.v;
		bottom = a.v;
	}
}

inline IADMRect::IADMRect(int left, int top, int right, int bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

inline int IADMRect::Width()	const				
{ 
	return right - left; 
}

inline int IADMRect::Height() const			
{ 
	return bottom - top; 
}

inline ADMBoolean IADMRect::IsEmpty()	const		
{ 
	return top == bottom && right == left; 
}

inline void IADMRect::SetEmpty()				
{ 
	left = top = right = bottom = 0; 
}

inline ADMBoolean IADMRect::IsNormalized() const
{
	return left <= right && top <= bottom;
}

inline void IADMRect::Normalize()
{
	if (left > right) 
	{
		long saveLeft = left; left = right; right = saveLeft;
	}
	if (top > bottom)
	{
		long saveTop = top; top = bottom; bottom = saveTop;
	}
}

inline int IADMRect::Area() const					
{ 
	return Width() * Height(); 
}

inline ADMPoint IADMRect::Center() const
{
	ADMPoint center;
	
	center.h = (left + Width() / 2);
	center.v = (top + Height() / 2);
	
	return center;
}

inline ADMBoolean IADMRect::Contains(const ADMPoint& p) const
{
	return left <= p.h && right >= p.h && top <= p.v && bottom >= p.v;
}

inline ADMBoolean IADMRect::Contains(const ADMRect& r) const
{
	return left <= r.left && right >= r.left && top <= r.top && bottom >= r.top &&
		   left <= r.right && right >= r.right && top <= r.bottom && bottom >= r.bottom;
}

inline ADMBoolean IADMRect::Overlaps(const ADMRect& r) const
{
	return  right  >= r.left && left <= r.right  && 
		    bottom >= r.top  && top  <= r.bottom;
}

inline IADMRect& IADMRect::operator ++ ()
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IADMRect& IADMRect::operator -- ()		
{ 	
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}

inline IADMRect IADMRect::operator ++ (int)
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IADMRect IADMRect::operator -- (int)		
{ 
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}

inline IADMRect& IADMRect::operator += (int n)	
{ 
	left -= n; 
	top -= n; 
	right += n; 
	bottom += n; 
	
	return *this; 
}

inline IADMRect& IADMRect::operator -= (int n)
{ 
	left += n; 
	top += n; 
	right -= n; 
	bottom -= n; 
	
	return *this; 
}

inline IADMRect& IADMRect::operator += (ADMPoint& p)	
{ 
	left += p.h; 
	top += p.v; 
	right += p.h; 
	bottom += p.v; 
	
	return *this; 
}

inline IADMRect& IADMRect::operator -= (ADMPoint& p)
{ 
	left -= p.h; 
	top -= p.v; 
	right -= p.h; 
	bottom -= p.v; 
	
	return *this; 
}

	
inline IADMRect& IADMRect::operator = (ADMPoint& p)
{
	left = right = p.h;
	top = bottom = p.h;
	
	return *this;
}

inline ADMBoolean operator == (const ADMRect& a, const ADMRect& b)
{
	return a.left == b.left &&
		   a.top == b.top &&
		   a.right == b.right &&
		   a.bottom == b.bottom;
}

inline ADMBoolean operator != (const ADMRect& a, const ADMRect& b)
{
	return a.left != b.left ||
		   a.top != b.top ||
		   a.right != b.right ||
		   a.bottom != b.bottom;
}

inline void IADMRect::Inset(int h, int v)
{ 
	left += h; 
	top += v; 
	right -= h; 
	bottom -= v; 
}	

inline void IADMRect::Inflate(int h, int v)
{ 
	left -= h; 
	top -= v; 
	right += h; 
	bottom += v; 
}	

inline void IADMRect::Offset(int h, int v)
{ 
	left += h; 
	top += v; 
	right += h; 
	bottom += v; 
}	

inline void IADMRect::Union(const ADMPoint& a)
{
	if (left > a.h)
		left = a.h;
	if (top > a.v)
		top = a.v;
	if (right < a.h)
		right = a.h;
	if (bottom < a.v)
		bottom = a.v; 
}

inline void IADMRect::Union(const ADMRect& a)
{
	if (left > a.left)
		left = a.left;
	if (top > a.top)
		top = a.top;
	if (right < a.right)
		right = a.right;
	if (bottom < a.bottom)
		bottom = a.bottom; 
}

inline void IADMRect::Union(const ADMRect& a, const ADMRect& b)
{
	if (b.left > a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top > a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right < a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom < a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom; 
}

inline void IADMRect::Intersect(const ADMRect& a)
{
	if (left < a.left)
		left = a.left;
	if (top < a.top)
		top = a.top;
	if (right > a.right)
		right = a.right;
	if (bottom > a.bottom)
		bottom = a.bottom;
		
	if (!Overlaps(a))
		SetEmpty();	
}

inline void IADMRect::Intersect(const ADMRect& a, const ADMRect& b)
{
	if (b.left < a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top < a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right > a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom > a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom;			
	if (!Overlaps(a))
		SetEmpty();	
} 

inline void IADMRect::Center(const ADMRect& centerRect)
{
	Offset(centerRect.left + ((centerRect.right - centerRect.left) - Width()) / 2,
		   centerRect.top + ((centerRect.bottom - centerRect.top) - Height()) / 2);
}

/*
 * Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96.
inline ADMRect operator + (const IADMRect& a, const IADMPoint& b)
{
	return IADMRect(a.left + b.h, a.top + b.v, a.right + b.h, a.bottom + b.v);
}

inline ADMRect operator + (const IADMPoint& a, const IADMRect& b)
{
	IADMRect r;
	
	r.left = b.left + a.h;
	r.top = b.top + a.v;
	r.right = b.right + a.h;
	r.bottom = b.bottom + a.v;
	
	return r;
}

inline ADMRect operator - (const IADMRect& a, const IADMPoint& b)
{
	IADMRect r;
	
	r.left = a.left - b.h;
	r.top = a.top - b.v;
	r.right = a.right - b.h;
	r.bottom = a.bottom - b.v;
	
	return r;
}

inline ADMRect operator - (const IADMPoint& a, const IADMRect& b)
{
	IADMRect r;
	
	r.left = b.left - a.h;
	r.top = b.top - a.v;
	r.right = b.right - a.h;
	r.bottom = b.bottom - a.v;
	
	return r;
}
*/

#endif
