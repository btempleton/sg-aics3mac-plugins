#ifndef __AIFixedMath__
#define __AIFixedMath__

/*
 *        Name:	AIFixedMath.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Fixed-Point Math Suite.
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIFixedMath.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIFixedMathSuite		"AI Fixed Math Suite"
#define kAIFixedMathSuiteVersion		AIAPI_VERSION(2)
#define kAIFixedMathVersion		kAIFixedMathSuiteVersion


// common AIFixed constants
#define kFixedMin			((AIFixed) 0x80000000L)
#define kFixedMax 			((AIFixed) 0x7FFFFFFFL)
#define kFixedUnknown 		((AIFixed) 0x80000000L)

#ifndef kFixedOne
#define kFixedOne			((AIFixed) 0x00010000L)
#endif
#ifndef kFixedZero
#define kFixedZero			((AIFixed) 0x00000000L)
#endif
#define kFixedHundredth		((AIFixed) 0x0000028FL)
#define kFixedSixteenth		((AIFixed) 0x00001000L)
#define kFixedTenth			((AIFixed) 0x00001999L)
#define kFixedEighth		((AIFixed) 0x00002000L)
#ifndef kFixedQuarter
#define kFixedQuarter 		((AIFixed) 0x00004000L)
#endif
#ifndef kFixedHalf
#define kFixedHalf 			((AIFixed) 0x00008000L)
#endif
#define kFixedSevenEighths	((AIFixed) 0x0000E000L)
#define kFixedOne1			((AIFixed) 0x0000FFFFL)
#define kFixedOneThird		((AIFixed) 0x00005555L)
#define kFixedFourThirds	((AIFixed) 0x00015555L)
#define kFixedThreeHalves	((AIFixed) 0x00018000L)

#define kFixedPi4 			((AIFixed) 0x0000C910L)
#define kFixedPi2 			((AIFixed) 0x00019220L)
#define kFixedPi			((AIFixed) 0x00032440L)
#define kFixedTwoPi 		((AIFixed) 0x00064880L)
#define kFixedGolden 		((AIFixed) 0x00019E37L)

// common AIFract constants
#define kFractZero			((AIFract) 0x00000000L)
#define kFractFixedRound	((AIFract) 0x00002000L)
#define kFractPi180			((AIFract) 0x011DF4A0L)
#define kFractQuarter		((AIFract) 0x10000000L)
#define kFractHalf			((AIFract) 0x20000000L)
#define kFractOne			((AIFract) 0x40000000L)
#define kFractFourThirds	((AIFract) 0x55555555L)
#define kFractSqrtTwo		((AIFract) 0x5A82799AL)
#define kFractUnknown		((AIFract) 0x80000000L)


/*******************************************************************************
 **
 **	Macros
 **
 **/

#if __BUILD_PLUGIN__

// type conversion macros
#define _FixedToFract(a)		((AIFract)(a) << 14)
#define _FractRoundToFixed(a)	((AIFixed) (((a) + kFractFixedRound) >> 14))
#define _FractTruncToFixed(a)	((AIFixed) ((a) >> 14))

#define _ShortToFixed(a)		((AIFixed)(a) << 16)
#define _FixedRoundToShort(a)	((short) (((a) + kFixedHalf) >> 16))
#define _FixedTruncToShort(a)	((short) ((a) >> 16))

#define _FloatToFixed(a)		((AIFixed)((a) * 65536.0))  // useful for constants; eg, _FloatToFixed(1.5) generates 0x00018000


// other macros
#define _FixedFloor(a)			((AIFixed) ((a) & 0xFFFF0000L))
#define _FixedCeiling(a)		_FixedFloor((a) + kFixedOne1)
#define _FixedRound(a)			_FixedFloor((a) + kFixedHalf)
#define _FixedFraction(a)		((a) & 0x0000FFFFL)
#define _FixedAverage(a, b) 	(((a) + (b) + 1) >> 1)
#define _FixedHalf(a) 			(((a) + 1) >> 1)
#define _FixedOverflow(a)		((a) == kFixedMax || (a) == kFixedMin)

#endif

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Use these functions to work with fixed-point numbers. These
	exist primarily for use by older plug-ins that were fixed-point based. Modern
	plug-ins should use the \c #AIRealMathSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFixedMathSuite and \c #kAIFixedMathVersion.
	*/
typedef struct {

	AIAPI AIFixed (*FixedAdd) ( AIFixed a, AIFixed b );
	AIAPI AIFixed (*FixedMul) ( AIFixed a, AIFixed b );
	AIAPI AIFract (*FractMul) ( AIFract a, AIFract b );
	AIAPI AIFixed (*FractFixedMul) ( AIFract a, AIFixed b );
	AIAPI AIFixed (*FixedDiv) ( AIFixed a, AIFixed b );
	AIAPI AIFract (*FractDiv) ( AIFract a, AIFract b );
	AIAPI AIFixed (*ShortRatio) ( short a, short b );
	AIAPI AIFract (*FixedRatio) ( AIFixed a, AIFixed b );
	AIAPI AIFixed (*FractRatio) ( AIFract a, AIFract b );
	AIAPI AIFixed (*FixedMulAdd) ( AIFixed a, AIFixed b, AIFixed c, AIFixed d );
	AIAPI AIFixed (*FixedMultiple) (AIFixed a, AIFixed multiple, AIBoolean ceiling );

	AIAPI AIFract (*FixedSin) ( AIFixed a );
	AIAPI AIFract (*FixedCos) ( AIFixed a );
	AIAPI AIFixed (*FixedATan) ( AIFixed a, AIFixed b );
	AIAPI AIFixed (*DegreeToRadian) ( AIFixed degree );
	AIAPI AIFixed (*RadianToDegree) ( AIFixed radian );

	AIAPI AIUFract (*FractSqrt) ( AIUFract a );
	AIAPI AIFixed (*FixedLength) ( AIFixed a, AIFixed b );
	AIAPI AIFixed (*FixedInterpolate) ( AIFixed a, AIFixed b, AIFixed t );

	AIAPI AIFloat (*FixedToFloat) ( AIFixed a );
	AIAPI AIFixed (*FloatToFixed) ( AIFloat a );
	AIAPI AIFloat (*FractToFloat) ( AIFract a );
	AIAPI AIFract (*FloatToFract) ( AIFloat a );

	AIAPI void (*FixedPointAdd) ( AIFixedPoint *a, AIFixedPoint *b, AIFixedPoint *result );
	AIAPI void (*FixedPointSubtract) ( AIFixedPoint *a, AIFixedPoint *b, AIFixedPoint *result );
	AIAPI AIBoolean (*FixedPointEqual) ( AIFixedPoint *a, AIFixedPoint *b );
	AIAPI AIBoolean (*FixedPointClose) ( AIFixedPoint *a, AIFixedPoint *b, AIFixed tolerance );
	AIAPI AIFixed (*FixedPointAngle) ( AIFixedPoint *a, AIFixedPoint *b );
	AIAPI AIFixed (*FixedPointLength) ( AIFixedPoint *a, AIFixedPoint *b );
	AIAPI void (*FixedPointLengthAngle) ( AIFixed length, AIFixed angle, AIFixedPoint *result );
	AIAPI void (*FixedPointInterpolate) ( AIFixedPoint *a, AIFixedPoint *b, AIFixed t, AIFixedPoint *result );

	AIAPI void (*FixedRectSet) ( AIFixedRect *a, AIFixed left, AIFixed top, AIFixed right, AIFixed bottom );
	AIAPI AIBoolean (*FixedRectEqual) ( AIFixedRect *a, AIFixedRect *b );
	AIAPI AIBoolean (*FixedRectEmpty) ( AIFixedRect *a );
	AIAPI void (*FixedRectInset) ( AIFixedRect *a, AIFixed h, AIFixed v );
	AIAPI void (*FixedRectOffset) ( AIFixedRect *a, AIFixed h, AIFixed v );
	AIAPI void (*FixedRectUnion) ( AIFixedRect *a, AIFixedRect *b, AIFixedRect *result );
	AIAPI void (*FixedPointUnion) ( AIFixedPoint *a, AIFixedRect *b, AIFixedRect *result );
	AIAPI AIBoolean (*FixedRectOverlap) ( AIFixedRect *a, AIFixedRect *b );
	AIAPI AIBoolean (*FixedRectIntersect) ( AIFixedRect *a, AIFixedRect *b, AIFixedRect *result );
	AIAPI AIBoolean (*FixedRectInFixedRect) ( AIFixedRect *a, AIFixedRect *b );
	AIAPI AIBoolean (*FixedPointInFixedRect) ( AIFixedPoint *a, AIFixedRect *b );
	AIAPI void (*FixedRectAlign) ( AIFixedRect *a, AIFixedRect *result );

	AIAPI void (*FixedMatrixSet) ( AIFixedMatrix *m, AIFixed a, AIFixed b, AIFixed c, AIFixed d, AIFixed tx, AIFixed ty );
	AIAPI void (*FixedMatrixSetIdentity) ( AIFixedMatrix *m );
	AIAPI AIBoolean (*FixedMatrixEqual) ( AIFixedMatrix *m, AIFixedMatrix *n );
	AIAPI AIBoolean (*FixedMatrixIdentity) ( AIFixedMatrix *m );
	AIAPI AIBoolean (*FixedMatrixSingular) ( AIFixedMatrix *m );
	AIAPI void (*FixedMatrixSetTranslate) ( AIFixedMatrix *m, AIFixed tx, AIFixed ty );
	AIAPI void (*FixedMatrixSetScale) ( AIFixedMatrix *m, AIFixed h, AIFixed v );
	AIAPI void (*FixedMatrixSetRotate) ( AIFixedMatrix *m, AIFixed angle );
	AIAPI void (*FixedMatrixConcatTranslate) ( AIFixedMatrix *m, AIFixed tx, AIFixed ty );
	AIAPI void (*FixedMatrixConcatScale) ( AIFixedMatrix *m, AIFixed h, AIFixed v );
	AIAPI void (*FixedMatrixConcatRotate) ( AIFixedMatrix *m, AIFixed angle );
	AIAPI void (*FixedMatrixConcat) (AIFixedMatrix *m, AIFixedMatrix *n, AIFixedMatrix *result );
	AIAPI short (*FixedMatrixInvert) (AIFixedMatrix *m );
	AIAPI void (*FixedMatrixXformPoint) ( AIFixedMatrix *m, AIFixedPoint *a, AIFixedPoint *result );

} AIFixedMathSuite;


#include "AIHeaderEnd.h"


#endif
