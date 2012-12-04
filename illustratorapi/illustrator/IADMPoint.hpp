/***********************************************************************/
/*                                                                     */
/* IADMPoint.hpp                                                        */
/* ADMPoint object wrapper class                                        */
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

#ifndef __IADMPoint_hpp__
#define __IADMPoint_hpp__

/*
 * Includes
 */
 
#ifndef __ADMTypes__
#include "ADMStandardTypes.h"
#endif

/*
 * Wrapper Class
 */

struct IADMPoint : public ADMPoint
{
public:	
	IADMPoint();
	IADMPoint(const ADMPoint& p);
	IADMPoint(int h, int v);
	
	friend inline ADMBoolean operator == (const ADMPoint& a, const ADMPoint& b);
	friend inline ADMBoolean operator != (const ADMPoint& a, const ADMPoint& b);
	
	friend inline ADMPoint operator + (const ADMPoint& a, const ADMPoint& b);
	friend inline ADMPoint operator - (const ADMPoint& a, const ADMPoint& b);

	friend inline ADMPoint operator * (const ADMPoint& p, int s);
	friend inline ADMPoint operator * (int s, const ADMPoint& p);

	friend inline ADMPoint operator / (const ADMPoint& p, int s);

	friend inline ADMPoint operator - (const ADMPoint& p);

	IADMPoint &operator = (const ADMPoint& p);
	void operator += (const ADMPoint& p);
	void operator -= (const ADMPoint& p);

	void operator *= (int s);
	void operator /= (int s);
};

inline IADMPoint::IADMPoint()
{
}

inline IADMPoint::IADMPoint(const ADMPoint& p)	
{ 
	h = p.h; 
	v = p.v; 
}

inline IADMPoint::IADMPoint(int h, int v)
{ 
	this->h = h; this->v = v; 
}

inline ADMBoolean operator == (const ADMPoint& a, const ADMPoint& b)
{
	return a.h == b.h && a.v == b.v;
}
	

inline ADMBoolean operator != (const ADMPoint& a, const ADMPoint& b)
{
	return a.h != b.h || a.v != b.v;
}

inline ADMPoint operator + (const ADMPoint& a, const ADMPoint& b)
{
	return IADMPoint(a.h + b.h, a.v + b.v);
}

inline ADMPoint operator - (const ADMPoint& a, const ADMPoint& b)
{
	return IADMPoint(a.h - b.h, a.v - b.v);
}

inline ADMPoint operator * (const ADMPoint& p, int s)
{
	return IADMPoint(p.h * s, p.v * s);
}

inline ADMPoint operator * (int s, const ADMPoint& p)
{
	return IADMPoint(p.h * s, p.v * s);
}

inline ADMPoint operator / (const ADMPoint& p, int s)
{
	return IADMPoint(p.h / s, p.v / s);
}

inline ADMPoint operator - (const ADMPoint& p)
{
	return IADMPoint(-p.h, -p.v);
}

inline IADMPoint &IADMPoint::operator = (const ADMPoint& p) 
{
	h = p.h;
	v = p.v;
	return *this;
}

inline void IADMPoint::operator += (const ADMPoint& p) 
{ 
	h += p.h;
	v += p.v; 
}

inline void IADMPoint::operator -= (const ADMPoint& p) 
{ 
	h -= p.h; 
	v -= p.v; 
}

inline void IADMPoint::operator *= (int s)
{ 
	h *= s;
	v *= s; 
}

inline void IADMPoint::operator /= (int s)
{
	h /= s;
	v /= s; 
}

#endif
