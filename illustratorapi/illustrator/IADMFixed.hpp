/***********************************************************************/
/*                                                                     */
/* IADMFixed.hpp                                                        */
/* ADMFixed object wrapper class                                        */
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

#ifndef __IADMFixed_hpp__
#define __IADMFixed_hpp__

/*
 * Includes
 */
 
#include "ADMStandardTypes.h"

/*
 * Types and Defines
 */

// Mac headers define GetItem.  DRL 7/29/96
#ifdef GetItem
#undef GetItem
#endif

#define kADMFixedZero		 	((ADMFixed) 0x00000000L)
#define kADMFixedHalf			((ADMFixed) 0x00008000L)	
#define kADMFixedOne				((ADMFixed) 0x00010000L)
#define kADMFixedMin			 	((ADMFixed) 0x80000000L)
#define kADMFixedMax 			((ADMFixed) 0x7FFFFFFFL)
#define kADMFixedUnknown 		((ADMFixed) 0x80000000L)

typedef long double asdouble_t;

#define _ShortToADMFixed(a)		((ADMFixed)(a) << 16)

/*
 * Global Suite Pointer
 */

class IADMFixed;
inline int operator != (const IADMFixed& a, const IADMFixed& b);
inline int operator > (const IADMFixed& a, const IADMFixed& b);
inline int operator >= (const IADMFixed& a, const IADMFixed& b);
inline int operator <= (const IADMFixed& a, const IADMFixed& b);

class IADMFixed
{

public:
	IADMFixed();			
	IADMFixed(const ADMFixed a);
	IADMFixed(const short a);
	IADMFixed(const int a);
	IADMFixed(const float a);
	IADMFixed(const double a);

	// conversion operators

	operator ADMFixed() const;
	operator short() const;
	operator int() const;
	operator float() const;
	operator double() const;

	// comparison operators

	friend inline int operator == (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator == (short a, const IADMFixed& b);
	//friend inline int operator == (const IADMFixed& a, short b);
	friend inline int operator == (int a, const IADMFixed& b);
	friend inline int operator == (const IADMFixed& a, int b);
	friend inline int operator == (const float& a, const IADMFixed& b);
	friend inline int operator == (const IADMFixed& a, const float& b);
	friend inline int operator == (const double& a, const IADMFixed& b);
	friend inline int operator == (const IADMFixed& a, const double& b);

	friend inline int operator != (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator != (short a, const IADMFixed& b);
	//friend inline int operator != (const IADMFixed& a, short b);
	friend inline int operator != (int a, const IADMFixed& b);
	friend inline int operator != (const IADMFixed& a, int b);
	friend inline int operator != (const float& a, const IADMFixed& b);
	friend inline int operator != (const IADMFixed& a, const float& b);
	friend inline int operator != (const double& a, const IADMFixed& b);
	friend inline int operator != (const IADMFixed& a, const double& b);

	friend inline int operator > (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator > (short a, const IADMFixed& b);
	//friend inline int operator > (const IADMFixed& a, short b);
	friend inline int operator > (int a, const IADMFixed& b);
	friend inline int operator > (const IADMFixed& a, int b);
	friend inline int operator > (const float& a, const IADMFixed& b);
	friend inline int operator > (const IADMFixed& a, const float& b);
	friend inline int operator > (const double& a, const IADMFixed& b);
	friend inline int operator > (const IADMFixed& a, const double& b);

	friend inline int operator < (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator < (short a, const IADMFixed& b);
	//friend inline int operator < (const IADMFixed& a, short b);
	friend inline int operator < (int a, const IADMFixed& b);
	friend inline int operator < (const IADMFixed& a, int b);
	friend inline int operator < (const float& a, const IADMFixed& b);
	friend inline int operator < (const IADMFixed& a, const float& b);
	friend inline int operator < (const double& a, const IADMFixed& b);
	friend inline int operator < (const IADMFixed& a, const double& b);

	friend inline int operator >= (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator >= (short a, const IADMFixed& b);
	//friend inline int operator >= (const IADMFixed& a, short b);
	friend inline int operator >= (int a, const IADMFixed& b);
	friend inline int operator >= (const IADMFixed& a, int b);
	friend inline int operator >= (const float& a, const IADMFixed& b);
	friend inline int operator >= (const IADMFixed& a, const float& b);
	friend inline int operator >= (const double& a, const IADMFixed& b);
	friend inline int operator >= (const IADMFixed& a, const double& b);

	friend inline int operator <= (const IADMFixed& a, const IADMFixed& b);
	//friend inline int operator <= (short a, const IADMFixed& b);
	//friend inline int operator <= (const IADMFixed& a, short b);
	friend inline int operator <= (int a, const IADMFixed& b);
	friend inline int operator <= (const IADMFixed& a, int b);
	friend inline int operator <= (const float& a, const IADMFixed& b);
	friend inline int operator <= (const IADMFixed& a, const float& b);
	friend inline int operator <= (const double& a, const IADMFixed& b);
	friend inline int operator <= (const IADMFixed& a, const double& b);

	// unary minus

	friend inline IADMFixed operator - (const IADMFixed& a);

	// binary arithmetic operators

	friend inline IADMFixed operator + (const IADMFixed& a, const IADMFixed& b);
	friend inline IADMFixed operator - (const IADMFixed& a, const IADMFixed& b);
	friend inline IADMFixed operator * (const IADMFixed& a, const IADMFixed& b);
	friend inline IADMFixed operator / (const IADMFixed& a, const IADMFixed& b);

	// unary arithmetic opererators

	void operator += (const IADMFixed& a);
	void operator -= (const IADMFixed& a);
	void operator *= (const IADMFixed& a);
	void operator /= (const IADMFixed& a);

	friend inline IADMFixed operator >> (const IADMFixed& a, int amount);
	friend inline IADMFixed operator << (const IADMFixed& a, int amount);

	friend inline IADMFixed abs(const IADMFixed& a);

protected:
	ADMFixed f;

	static inline asdouble_t FixToX(ADMFixed x);
	static inline ADMFixed XToFix(asdouble_t x);
	static inline ADMFixed FixedMul(ADMFixed a, ADMFixed b);
	static inline ADMFixed FixedDiv(ADMFixed x, ADMFixed y);
	static inline ADMFixed FixedSumChk(ADMFixed a, ADMFixed b);

};

inline asdouble_t IADMFixed::FixToX(ADMFixed x)
{
	return ((asdouble_t)x) / 65536.0;
}

inline ADMFixed IADMFixed::XToFix(asdouble_t x)
{
	ADMFixed fx;

	if (x - 1.0 >= (asdouble_t)0x00007fffL)
		fx = 0x7fffffffL;
	else if (x + 1.0 <= -(asdouble_t)0x00008000L)
		fx = 0x80000000L;
	else
		fx = (ADMFixed)(x * (asdouble_t)0x00010000L + (x > 0.0 ? 0.5 : -0.5));

	return fx;
}

inline ADMFixed IADMFixed::FixedMul(ADMFixed a, ADMFixed b)
{
	asdouble_t da, db;
	ADMFixed fx;

	da = FixToX(a);
	db = FixToX(b);

	fx = XToFix(da * db);

	return fx;
}

inline ADMFixed IADMFixed::FixedDiv(ADMFixed x, ADMFixed y)
{
	if (!y)
		{
		if (x < 0)
			return 0x80000000L;
		else
			return 0x7fffffffL;
		}

	return XToFix((asdouble_t)x / (asdouble_t)y);
}

inline ADMFixed IADMFixed::FixedSumChk(ADMFixed a, ADMFixed b)
{
	if (a == kADMFixedMax || b == kADMFixedMax)
		return kADMFixedMax;
	else if (a == kADMFixedMin || b == kADMFixedMin)
		return kADMFixedMin;
	else
		{
		ADMFixed c;
		bool aNeg, bNeg;

		aNeg = a < kADMFixedZero;
		bNeg = b < kADMFixedZero;
		c = a + b;
		if (aNeg == bNeg && aNeg != (c < kADMFixedZero))
			c = aNeg ? kADMFixedMin : kADMFixedMax;
		return c;
		}
}

inline IADMFixed::IADMFixed() 			
{ 
}

inline IADMFixed::IADMFixed(const ADMFixed a)
{ 
	f = a;
}

inline IADMFixed::IADMFixed(const short a)
{ 
	f = ADMFixed(a) << 16;
}

inline IADMFixed::IADMFixed(const int a)
{ 
	f = ADMFixed(a) << 16;
}

inline IADMFixed::IADMFixed(const float a)
{ 
	f = long(a * 65536.0);
}

inline IADMFixed::IADMFixed(const double a)
{ 
	f = long(a * 65536.0);
}

inline IADMFixed::operator ADMFixed() const 
{
	return f; 
}

inline IADMFixed::operator short() const 
{
	return short(f >> 16); 
}

inline IADMFixed::operator int() const 
{
	return int(f >> 16); 
}

inline IADMFixed::operator float() const 
{
	return float(f / 65536.0);
}

inline IADMFixed::operator double() const 
{
	return double(f / 65536.0);
}

inline int operator == (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f == b.f;
}

//inline int operator == (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f != b.f;
//}

//inline int operator == (const IADMFixed& a, short b) 
//{
//	return a.f == IADMFixed(b).f;
//}

inline int operator == (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f == b.f;
}

inline int operator == (const IADMFixed& a, int b) 
{
	return a.f == IADMFixed(b).f;
}

inline int operator == (const float& a, const IADMFixed& b) 
{
	return a == float(b);
}

inline int operator == (const IADMFixed& a, const float& b) 
{
	return float(a) == b;
}

inline int operator == (const double& a, const IADMFixed& b) 
{
	return a == double(b);
}

inline int operator == (const IADMFixed& a, const double& b) 
{
	return double(a) == b;
}

inline int operator != (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f != b.f;
}

//inline int operator != (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f != b.f;
//}

//inline int operator != (const IADMFixed& a, short b) 
//{
//	return a.f != IADMFixed(b).f;
//}

inline int operator != (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f != b.f;
}

inline int operator != (const IADMFixed& a, int b) 
{
	return a.f != IADMFixed(b).f;
}

inline int operator != (const float& a, const IADMFixed& b) 
{
	return a != float(b);
}

inline int operator != (const IADMFixed& a, const float& b) 
{
	return float(a) != b;
}

inline int operator != (const double& a, const IADMFixed& b) 
{
	return a != double(b);
}

inline int operator != (const IADMFixed& a, const double& b) 
{
	return double(a) != b;
}

inline int operator > (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f > b.f;
}

//inline int operator > (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f > b.f;
//}

//inline int operator > (const IADMFixed& a, short b) 
//{
//	return a.f > IADMFixed(b).f;
//}

inline int operator > (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f > b.f;
}

inline int operator > (const IADMFixed& a, int b) 
{
	return a.f > IADMFixed(b).f;
}

inline int operator > (const float& a, const IADMFixed& b) 
{
	return a > float(b);
}

inline int operator > (const IADMFixed& a, const float& b) 
{
	return float(a) > b;
}

inline int operator > (const double& a, const IADMFixed& b) 
{
	return a > double(b);
}

inline int operator > (const IADMFixed& a, const double& b) 
{
	return double(a) > b;
}

inline int operator < (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f < b.f;
}

//inline int operator < (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f < b.f;
//}

//inline int operator < (const IADMFixed& a, short b) 
//{
//	return a.f < IADMFixed(b).f;
//}

inline int operator < (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f < b.f;
}

inline int operator < (const IADMFixed& a, int b) 
{
	return a.f < IADMFixed(b).f;
}

inline int operator < (const float& a, const IADMFixed& b) 
{
	return a < float(b);
}

inline int operator < (const IADMFixed& a, const float& b) 
{
	return float(a) < b;
}

inline int operator < (const double& a, const IADMFixed& b) 
{
	return a < double(b);
}

inline int operator < (const IADMFixed& a, const double& b) 
{
	return double(a) < b;
}

inline int operator >= (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f >= b.f;
}

//inline int operator >= (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f >= b.f;
//}

//inline int operator >= (const IADMFixed& a, short b) 
//{
//	return a.f >= IADMFixed(b).f;
//}

inline int operator >= (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f >= b.f;
}

inline int operator >= (const IADMFixed& a, int b) 
{
	return a.f >= IADMFixed(b).f;
}

inline int operator >= (const float& a, const IADMFixed& b) 
{
	return a >= float(b);
}

inline int operator >= (const IADMFixed& a, const float& b) 
{
	return float(a) >= b;
}

inline int operator >= (const double& a, const IADMFixed& b) 
{
	return a >= double(b);
}

inline int operator >= (const IADMFixed& a, const double& b) 
{
	return double(a) >= b;
}

inline int operator <= (const IADMFixed& a, const IADMFixed& b) 
{
	return a.f <= b.f;
}

//inline int operator <= (short a, const IADMFixed& b) 
//{
//	return IADMFixed(a).f <= b.f;
//}

//inline int operator <= (const IADMFixed& a, short b) 
//{
//	return a.f <= IADMFixed(b).f;
//}

inline int operator <= (int a, const IADMFixed& b) 
{
	return IADMFixed(a).f <= b.f;
}

inline int operator <= (const IADMFixed& a, int b) 
{
	return a.f <= IADMFixed(b).f;
}

inline int operator <= (const float& a, const IADMFixed& b) 
{
	return a <= float(b);
}

inline int operator <= (const IADMFixed& a, const float& b) 
{
	return float(a) <= b;
}

inline int operator <= (const double& a, const IADMFixed& b) 
{
	return a <= double(b);
}

inline int operator <= (const IADMFixed& a, const double& b) 
{
	return double(a) <= b;
}

inline IADMFixed operator - (const IADMFixed& a)
{
	return -a.f;
}

inline IADMFixed operator + (const IADMFixed& a, const IADMFixed& b)
{
	return a.f + b.f;
}

inline IADMFixed operator - (const IADMFixed& a, const IADMFixed& b)
{
	return a.f - b.f;
}

inline IADMFixed operator * (const IADMFixed& a, const IADMFixed& b)
{
	return IADMFixed::FixedMul(a, b);
}

inline IADMFixed operator / (const IADMFixed& a, const IADMFixed& b)
{
	return IADMFixed::FixedDiv(a, b);
}

inline void IADMFixed::operator += (const IADMFixed& a)
{
	*this = *this + a;
}

inline void IADMFixed::operator -= (const IADMFixed& a)
{
	*this = *this - a;
}

inline void IADMFixed::operator *= (const IADMFixed& a)
{
	*this = *this * a;
}

inline void IADMFixed::operator /= (const IADMFixed& a)
{
	*this = *this / a;
}

inline IADMFixed operator >> (const IADMFixed& a, int amount)
{
	return a.f >> amount;
}

inline IADMFixed operator << (const IADMFixed& a, int amount)
{
	return a.f << amount;
}

inline IADMFixed abs(const IADMFixed& a)
{
	if (a.f >= 0)
		return a.f;
	else
		return -a.f; 
}

#endif
