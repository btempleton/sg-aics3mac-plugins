/***********************************************************************/
/*                                                                     */
/* ADMStandardTypes.h                                                  */
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
/* Started by David Hearst, 05/20/2002                                 */
/*                                                                     */
/***********************************************************************/

/** @file ADMStandardTypes.h Adobe Standard Types */

#ifndef __ADMStandardTypes__
#define __ADMStandardTypes__

/*
 * Includes
 */

#ifndef __PlatformConfig__
#include "PlatformConfig.h"
#endif

#ifdef MAC_ENV
	#ifndef __MACTYPES__
		#include <CoreServices/CoreServices.h>
	#endif
#endif

#include "ADMHeaderBegin.h"


/*
 * Constants
 */

// true and false

#ifndef __cplusplus

#ifndef true
/** Boolean true */
#define true	1
#endif

#ifndef false
/** Boolean false */
#define false	0
#endif

#endif // __cplusplus

#ifndef TRUE
/** Boolean true */
#define TRUE	true
#endif

#ifndef FALSE
/** Boolean false */
#define FALSE	false
#endif

// error codes
/** @ingroup Errors
	Operation was successful. */
#define kNoErr					0
/** @ingroup Errors
	Out of memory. */
#define kOutOfMemoryErr			'!MEM'
/** @ingroup Errors
	A parameter was not of the proper type
	or otherwise failed constraints. */
#define kBadParameterErr		'PARM'
/** @ingroup Errors
	The function is not implemented. */
#define kNotImplementedErr		'!IMP'
/** @ingroup Errors
	An unanticipated condition occurred. */
#define kCantHappenErr			'CANT'


// NULL

#ifndef NULL

#ifdef MAC_ENV
#if !defined(__cplusplus) && (defined(__SC__) || defined(THINK_C))
/** Null value */
#define NULL	((void *) 0)
#else
/** Null value  */
#define NULL	0
#endif
#endif

#ifdef WIN_ENV
#ifdef __cplusplus
/** Null value  */
#define NULL    0
#else
/** Null value  */
#define NULL    ((void *)0)
#endif
#endif

#endif

// dhearst 8/11/99 - we now specifically prefer NULL, so nil
// is obsolete. We no longer provide it, but can't enforce this
// policy because platform headers often provide nil.
//#ifndef nil
//#define nil NULL
//#endif


// AMPAPI  Adobe Standard Plugin API calling convention.

#ifndef AMPAPI
#define ADMAPI
#endif

// C calling convention for those places that need it.
// This doesn't really do anything, but is  more for
// an explicit declaration when it matters.
#define ADMCAPI


/*
 * Types
 */

// Integer Types

/** 8-bit integer */
typedef signed char ADMInt8;
/** 16-bit integer  */
typedef signed short ADMInt16;
/** 32-bit integer  */
typedef signed long ADMInt32;

/** 8-bit character code  */
typedef unsigned char ADMUInt8;
/** 16-bit character code */
typedef unsigned short ADMUInt16;
/** 32-bit character code */
typedef unsigned long ADMUInt32;

/** Error code; see @ref Errors */
typedef long ADMErr;

// Storage Types

/** Byte character code */
typedef unsigned char ADMByte;
/** Pointer to a byte character code */
typedef ADMByte* ADMBytePtr;

// Unicode Types
/** Unicode character */
typedef ADMUInt16 ADMUnicode;

// Pointer Types

/** Pointer to a memory location */
typedef void* ADMPtr;
/** Pointer to an object reference */
typedef void** ADMHandle;

// Fixed Types

/** Fixed numeric type */
typedef	long ADMFixed;
/** Fractional numeric type */
typedef long ADMFract;
/** Real number type */
typedef float ADMReal;

/** A point with fixed-number coordinate values */
typedef struct _t_ADMFixedPoint {
	/** Fixed-number coordinate values */
	ADMFixed h, v;
} ADMFixedPoint;

/** A rectangle with fixed-number coordinate values */
typedef struct _t_ADMFixedRect {
	/** Fixed-number coordinate values */
	ADMFixed left, top, right, bottom;
} ADMFixedRect;

/** A transformation matrix with fixed-number member values */
typedef struct _t_ADMFixedMatrix {
	/** Fixed-number member values */
	ADMFixed a, b, c, d, tx, ty;
} ADMFixedMatrix;

/** A point with real-number coordinate values */
typedef struct _t_ADMRealPoint {
	/** Real-number coordinate values */
	ADMReal h, v;
} ADMRealPoint;

/** A rectangle with real-number coordinate values */
typedef struct _t_ADMRealRect {
	/** Real-number coordinate values */
	ADMReal left, top, right, bottom;
} ADMRealRect;

/** A transformation matrix with real-number member values  */
typedef struct _t_ADMRealMatrix {
	/** Real-number member values */
	ADMReal a, b, c, d, tx, ty;
} ADMRealMatrix;


// Platform Structures

#ifdef MAC_ENV


// ADMBoolean is the same a Macintosh Boolean.
/** Boolean value in Mac OS (same as \c Boolean)*/
typedef unsigned char ADMBoolean;

// ADMPortRef is the same as a Macintosh GrafPtr.
/** Port reference value in Mac OS (same as \c GrafPtr) */
typedef struct OpaqueGrafPtr* ADMPortRef;

// ADMWindowRef is the same as a Macintosh WindowPtr.
/** Window reference value in Mac OS (same as \c WindowPtr) */
typedef struct OpaqueWindowPtr* ADMWindowRef;

// ADMRect is the same size and layout as a Macintosh Rect.
/** Rectangle value in Mac OS (same as \c Rect) */
typedef struct Rect ADMRect;

// ADMPoint is the same size and layout as a Macintosh Point.
/** Point value in Mac OS  (same as \c Point) */
typedef struct Point ADMPoint;


#endif


#ifdef WIN_ENV

// ADMBoolean is the same a Windows BOOL.
/** Boolean value in Windows (same as \c BOOL) */
typedef int ADMBoolean;

// ADMPortRef is the same as a Windows HDC.
/** Port reference value in Windows (same as \c HDC) */
typedef void* ADMPortRef;

// ADMWindowRef is the same as a Windows HWND.
/** Window reference value in Windows (same as \c HWND) */
typedef void* ADMWindowRef;

// ADMRect is the same size and layout as a Windows RECT.
/** Rectangle value in Windows (same as \c RECT) */
typedef struct _t_ADMRect {
	/** Coordinate values */
	long left, top, right, bottom;
} ADMRect;

// ADMPoint is the same size and layout as a Windows POINT.
/** Point value in Windows (same as \c Point) */
typedef struct _t_ADMPoint  {
	/** Coordinate values */
	long h, v;
} ADMPoint;

#endif

// Set alignment of Macintosh types to match alignment in the MacOS headers
#ifdef MAC_ENV
#pragma options align=mac68k
#endif

// ADMRGBColor is the same as a Macintosh RGBColor on Macintosh and Windows.
/** RGB color record */
typedef struct _t_ADMRGBColor {
	/** Color values */
	unsigned short red, green, blue;
} ADMRGBColor;


// AIEvent is the same as a Macintosh EventRecord on Macintosh and Windows.
/** Event record. */
typedef struct _t_ADMEvent {
	/** The type of event */
	unsigned short	what;
	/** The event message */
	unsigned long	message;
	/** The time the event occurred */
	unsigned long	when;
	/** The location of the event */
	ADMPoint			where;
	/** Event modifiers (other simultaneous events or conditions).
		A logical OR of \c #AIEventModifersValue bit flag values. */
	unsigned short	modifiers;
} ADMEvent;

#ifdef MAC_ENV
#pragma options align=reset
#endif


// This is a generic reference to a resource/plugin file.  If not otherwise stated,
// it is assumed to be equivalent to an SPPluginRef (see "SPPlugs.h")
/** A resource or plug-in file. Generally equivalent to \c #SPPluginRef. */
typedef struct ADMAccess* ADMAccessRef;



#include "ADMHeaderEnd.h"


#endif
