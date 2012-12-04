#ifndef __IASPoint_hpp__
#define __IASPoint_hpp__

/*
 *        Name:	IASRealPoint.hpp
 *   $Revision: $
 *      Author:	David Holloway 
 *        Date:	
 *     Purpose:	IASRealPoint Wrapper Class.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*
 * Includes
 */
 
#ifndef __ASTypes__
#include "ASTypes.h"
#endif

/*
 * Wrapper Class
 */

struct IASRealPoint : public ASRealPoint
{
public:	
	IASRealPoint();
	IASRealPoint(const ASRealPoint &p);
	IASRealPoint(int h, int v);
	IASRealPoint(float h, float v);
	
	friend inline ASBoolean operator == (const ASRealPoint &a, const ASRealPoint &b);
	friend inline ASBoolean operator != (const ASRealPoint &a, const ASRealPoint &b);
	
	friend inline ASRealPoint operator + (const ASRealPoint &a, const ASRealPoint& b);
	friend inline ASRealPoint operator - (const ASRealPoint &a, const ASRealPoint& b);

	friend inline ASRealPoint operator * (const ASRealPoint &p, int s);
	friend inline ASRealPoint operator * (int s, const ASRealPoint& p);

	friend inline ASRealPoint operator / (const ASRealPoint &p, int s);

	friend inline ASRealPoint operator - (const ASRealPoint &p);

	void operator = (const ASRealPoint &p);
	void operator += (const ASRealPoint &p);
	void operator -= (const ASRealPoint &p);

	void operator *= (int s);
	void operator /= (int s);
};


inline IASRealPoint::IASRealPoint()
{
}


inline IASRealPoint::IASRealPoint(const ASRealPoint &p)	
{ 
	h = p.h; 
	v = p.v; 
}


inline IASRealPoint::IASRealPoint(int h, int v)
{ 
	this->h = static_cast<ASReal>(h);
	this->v = static_cast<ASReal>(v);
}

inline IASRealPoint::IASRealPoint(float h, float v)
{ 
	this->h = h; this->v = v; 
}


inline ASBoolean operator == (const ASRealPoint &a, const ASRealPoint &b)
{
	return a.h == b.h && a.v == b.v;
}
	

inline ASBoolean operator != (const ASRealPoint &a, const ASRealPoint &b)
{
	return a.h != b.h || a.v != b.v;
}


inline ASRealPoint operator + (const ASRealPoint &a, const ASRealPoint &b)
{
	return IASRealPoint(a.h + b.h, a.v + b.v);
}


inline ASRealPoint operator - (const ASRealPoint &a, const ASRealPoint &b)
{
	return IASRealPoint(a.h - b.h, a.v - b.v);
}


inline ASRealPoint operator * (const ASRealPoint &p, int s)
{
	return IASRealPoint(p.h * s, p.v * s);
}


inline ASRealPoint operator * (int s, const ASRealPoint &p)
{
	return IASRealPoint(p.h * s, p.v * s);
}


inline ASRealPoint operator / (const ASRealPoint &p, int s)
{
	return IASRealPoint(p.h / s, p.v / s);
}


inline ASRealPoint operator - (const ASRealPoint &p)
{
	return IASRealPoint(-p.h, -p.v);
}


inline void IASRealPoint::operator = (const ASRealPoint& p) 
{
	h = p.h;
	v = p.v;
}


inline void IASRealPoint::operator += (const ASRealPoint& p) 
{ 
	h += p.h;
	v += p.v; 
}


inline void IASRealPoint::operator -= (const ASRealPoint& p) 
{ 
	h -= p.h; 
	v -= p.v; 
}


inline void IASRealPoint::operator *= (int s)
{ 
	h *= s;
	v *= s; 
}


inline void IASRealPoint::operator /= (int s)
{
	h /= s;
	v /= s; 
}


#endif








