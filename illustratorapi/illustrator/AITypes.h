#ifndef __AITypes__
#define __AITypes__

/*
 *        Name:	AITypes.h
 *   $Revision: 17 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator core type definitions.
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
 *
 *  Includes
 *
 */
#ifdef __cplusplus
#include <exception>
#endif

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#include "ADMTypes.h"

#ifndef __SPFiles__
#include "SPFiles.h"
#endif

#include "AIHeaderBegin.h"

/** @file AITypes.h */



/*******************************************************************************
 *
 *  Constants
 *
 */

#define kPluginInterfaceVersion6001		0x06000001  // 6.0x1
#define kPluginInterfaceVersion6002		0x06000020

#define kPluginInterfaceVersion7001		0x07000001	// AI 7.0

#define kPluginInterfaceVersion6021		0x06000021  // Joe's AI6-based prototype (only needed to run his plugins)
#define kPluginInterfaceVersion8001		0x08000001	// AI 8.0
#define kPluginInterfaceVersion9001		0x09000001	// AI 9.0
#define kPluginInterfaceVersion10001	0x10000001	// AI 10.0
#define kPluginInterfaceVersion11001	0x11000001	// AI 11.0
#define kPluginInterfaceVersion12001	0x12000001	// AI 12.0
#define kPluginInterfaceVersion13001	0x13000001	// AI 13.0

#define kPluginInterfaceVersion			kPluginInterfaceVersion13001

#ifdef MAC_ENV
#define AIAPI_VERSION(x) (x + 1000)
#endif

#ifdef WIN_ENV
#define AIAPI_VERSION(x) (x)
#endif

#define kPlatformUnloadedSuiteProc	NULL

#if !defined(__BUILD_PLUGIN__)
#if defined(ILLUSTRATOR_H)
#define __BUILD_PLUGIN__ 0
#else
#define __BUILD_PLUGIN__ 1
#endif
#endif

//These are no longer needed.
/** @deprecated */
#define PUSH_GLOBALS
/** @deprecated */
#define POP_GLOBALS

// Determine the platform.
#if defined(MAC_ENV)
#define Macintosh 1
#else
#define Macintosh 0
#endif

#if !defined(MSWindows)
#if defined(WIN_ENV)
#define MSWindows 1
#else
#define MSWindows 0
#endif
#endif

// Some common error codes.
/** @ingroup Errors
	Operation canceled by user */
#define kCanceledErr			'STOP'
/** @ingroup Errors
	No current document */
#define kNoDocumentErr			'DOC?'
/** @ingroup Errors
	A selector was called at an inappropriate time.  */
#define kSelectorClashErr		'CLSH'
/** @ingroup Errors
	Specified name not found.  */
#define kNameNotFoundErr		'NAM?'
/** @ingroup Errors
	Specified name not unique.  */
#define kNameInUseErr			'NAM2'
/** @ingroup Errors
	Specified name not valid.  */
#define kInvalidNameErr			'NA*!'
/** @ingroup Errors
	Specified name too long.  */
#define kNameTooLongErr			'NAL!'


/*******************************************************************************
 *
 *  Types
 *
 */

#define AIAPI ASAPI

/** Opaque reference to an art object. Access using \c #AIArtSuite. */
typedef struct ArtObject *AIArtHandle;
/** Opaque reference to a layer. Access using \c #AILayerSuite.  */
typedef struct _t_AILayerOpaque *AILayerHandle;
/** Fixed number (obsolete) See \c #AIFixedMathSuite. */
typedef ASFixed AIFixed;
/** A fractional number greater than -2 and less than 2. Obsolete, use \c AIReal. */
typedef ASFract AIFract;
/** An unsigned fractional number greater than 0 and less than 4. Obsolete, use \c AIReal.  */
typedef unsigned long AIUFract;
/** Real number. See \c #AIRealMathSuite. */
typedef	ASReal AIReal, *AIRealPtr;
/** Floating-point numeric value */
typedef float AIFloat;
/** Double-byte numeric value */
typedef double AIDouble;
/** Data stream */
typedef struct _t_AIStreamOpaque *AIStream;
 /** Rectangle specified with \c #AIFixed coordinates. Obsolete, use \c #AIRealRect. */
typedef ASFixedRect AIFixedRect;
 /** Point specified with \c #AIFixed coordinates. Obsolete, use \c #AIRealPoint. */
typedef ASFixedPoint AIFixedPoint;
 /** Transformation matrix specified with \c #AIFixed values. Obsolete, use \c #AIRealMatrix. */
typedef ASFixedMatrix AIFixedMatrix;
 /** Rectangle specified with \c #AIReal coordinates.*/
typedef ASRealRect AIRealRect, *AIRealRectPtr;
/** Point specified with \c #AIReal coordinates.*/
typedef ASRealPoint AIRealPoint, *AIRealPointPtr;
/** Transformation matrix specified with \c #AIReal values.*/
typedef ASRealMatrix AIRealMatrix, *AIRealMatrixPtr;
/** True (1) or false (0) */
typedef ASBoolean AIBoolean;
/** 1-byte boolean value, true (1) or false (0) */
typedef ASByte AIBool8;
/** Rectangle specified with Adobe Dialog Manager (ADM) coordinates.*/
typedef ADMRect AIRect;
/** Point specified with ADM coordinates.*/
typedef ADMPoint AIPoint;
/** Rectangle specified with \c #AIDouble coordinates.*/
struct AIDoubleRect {
	AIDouble left, top, right, bottom;
};

#ifdef MAC_ENV
/** Port reference, Mac OS only, same as Mac OS \c CGrafPtr. */
typedef CGrafPtr AIPortRef;

/** Window reference, Mac OS only, same as Mac OS \c WindowPtr. */
typedef WindowRef AIWindowRef;

/** Dialog reference, Mac OS only, same as Mac OS \c DialogPtr. */
typedef DialogRef AIDialogRef;
#endif

#ifdef WIN_ENV
/** Port reference, Windows only, same as Windows \c HDC. */
typedef void* AIPortRef;

/** Window reference, Windows only, same as Windows \c HWND. */
typedef void* AIWindowRef;

/** Dialog reference, Windows only, same as Windows \c HWND. */
typedef void* AIDialogRef;
#endif

/** Opaque RGB color, access with \c #AIColorConversionSuite. */
typedef ADMRGBColor AIRGBColor;
/** Event information structure, used by \c #AIToolSuite, \c #AICursorSnapSuite. See also @ref adm_api */
typedef ADMEvent AIEvent;
/** Opaque error, returned by most suite functions. See @ref Errors */
typedef ASErr AIErr;

/** Use the \c #AIColorProfile type instead of an \c ACEProfile* */
class ACEProfile;
/** Opaque color profile. See \c #AIColorConversionSuite. */
typedef ACEProfile *AIColorProfile;

/** An Illustrator menu command identifier. See \c #AICommandManagerSuite. */
typedef unsigned long AICommandID;

/** A ZString (localizable string) reference.
	Enforces the passing of ZStrings.
	A ZStrings is a \c char* with a conventional format,
	so it is easy to pass a non-ZString by accident. When this
	type is specified, the function expects a ZString.
	You can cast it back to a \c char* if you need to look inside it. */
typedef const struct ZREFStruct *ZRef;
#define ZREF(x) (ZRef)x

/** The position of an art object, which determines how it is drawn relative to another,
	overlapping art object, known as the prep (prepositional) object,
	and also whether a path is inside a compound path or group.
		\li If the paint order is \c kPlaceAbove or \c kPlaceBelow, the object is drawn above or below the prep object
		when the boundaries overlap.
		\li If the paint order is \c kPlaceInsideOnTop or \c kPlaceInsideOnBottom,the object is inside the prep object,
		which must be a container.
		\li If the paint order is \c kPlaceAboveAll or \c kPlaceBelowAll,
		the prep object is ignored and the object is placed on top of or at the bottom of the entire document
		(that is, inside-on-top the topmost group or inside-on-bottom the bottommost group).

	The paint order is the back-to-front ordering of art objects, also called the occlusion order or Z-order.
	It determines which objects obscure others when their bounds overlap. If objects do not overlap,
	the paint order is irrelevant to rendering.

	Paint order values are used, for example, when creating art objects with \c #AIArtSuite::NewArt(), copying
	or moving art objects, or specifying insertion points for art.
	*/
typedef enum AIPaintOrder {
	/** Default value */
	kPlaceDefault = 0,
	/** Place above the prepositional object */
	kPlaceAbove = 1,
	/** Place below the prepositional object */
	kPlaceBelow,
	/** Place within and at the top of the prepositional container */
	kPlaceInsideOnTop,
	/** Place within and at the bottom of the prepositional container */
	kPlaceInsideOnBottom,
	/** Place at the top of the paint order, ignoring prepositional object */
	kPlaceAboveAll,
	/** Place at the bottom of the paint order, ignoring prepositional object */
	kPlaceBelowAll
} AIPaintOrder;

/** How paint is applied--to fills, strokes, or both. */
typedef enum AIPaintUsage {
	kAINotUsed = 0x0000,
	/** Paint is applied to fills. */
	kAIUsedOnFill = 0x0001,
	/** Paint is applied to strokes. */
	kAIUsedOnStroke = 0x0002,
	/** Paint is applied to both fills and strokes. */
	kAIUsedOnBoth = 0x0003
} AIPaintUsage;

/** These constants identify the various shipping versions of Illustrator. */
typedef enum AIVersion {
	kAIVersion1 = 1,
	kAIVersion88,
	kAIVersion3,
	kAIVersion4,
	kAIVersion5,
	kAIVersion6,
	kAIVersion7,
	kAIVersion8,
	kAIVersion9,
	kAIVersion10,
	kAIVersion11,
	kAIVersion12,
	kAIVersion13
} AIVersion;



#ifdef __cplusplus
namespace ai {

/** This macro is used to decorate C++ functions and methods that are
	guaranteed not to throw. Due to the current state of compiler support
	for throw specifications, it is defined to be empty. */
#define AINOTHROW


/** Exception class thrown by C++ classes */
class Error : public std::exception {
public:
	Error (AIErr _err) : err(_err)
		{}
	operator AIErr () const
		{return err;}

protected:
	AIErr err;
};

} // end namespace ai
#endif


#include "AIHeaderEnd.h"

// Note: CompileTimeChecker must be after the AIHeaderEnd.h inclusion as AIHeaderBegin puts everything
// into an extern C.  You cannot declare a template to have 'C' linkage.

#ifdef __cplusplus
namespace ai {

/** Provides compile-time errors that are similar to run-time assertions.
    This is an implementation of Andrei Alexandrescu's CompileTimeChecker.
	Use the AI_STATIC_CHECK macro to instantiate a \c CompileTimeChecker object.
	For example:

<code>
		AI_STATIC_CHECK(sizeof(wchar_t) == sizeof(unsigned short), wchar_t_size_does_not_match_unsigned_short_size);
</code>
*/
template<bool> struct CompileTimeChecker
{
	CompileTimeChecker(...);
};
/** There is no instantiation of CompileTimeChecker for a false value. */
template<> struct CompileTimeChecker<false> {};

/** Use to instantiate a \c CompileTimeChecker object for an expression.
		@param expr An expression that compiles to the Boolean constant \c true.
			If the expression compiles to a false value, the checker cannot be instantiated,
			and a compile-time error occurs.
		@param msg The compile-time error message that is displayed when the condition is met.
			Must be a legal C++ identifier (that is, contains no spaces, cannot begin with a digit, and so on).  */
#define AI_STATIC_CHECK(expr, msg) \
{\
	class ERROR_##msg {};\
	(void)sizeof(ai::CompileTimeChecker<(expr) != 0>((new ERROR_##msg())));\
}

} //end namespace ai
#endif // __cplusplus 

#endif
