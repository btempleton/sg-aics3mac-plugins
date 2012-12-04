/*******************************************************************************
*
* ADMImage.h -- ADM Image Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Dave Lazarony, 20 Nov 1996
*
********************************************************************************/

/** @file ADMImage.h ADM Image Suite */

#ifndef __ADMImage__
#define __ADMImage__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------

/** Creation options for ADM images. When set, the image has an alpha channel.
	See \c #ADMImageSuite2::Create(). */
#define kADMImageHasAlphaChannelOption (1L << 0)


// =============================================================================
//		* ADM Image Suite
// =============================================================================

/** Image suite name */
#define kADMImageSuite "ADM Image Suite"
/** Image suite version */
#define kADMImageSuiteVersion2 2

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides a means for creating off-screen images that can be
	displayed and manipulated with \c #ADMDrawerSuite6.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMImageSuite and \c #kADMImageSuiteVersion2.
	*/
typedef struct ADMImageSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// image creation/destruction

	/** Creates an ADM image object.
			@param inWidth The image width in pixels.
			@param inHeight The image height in pixels.
			@param inOptions Creation options, \c #kADMImageHasAlphaChannelOption or 0.
			@return The ADM image object.
		*/
	ADMImageRef ADMAPI (*Create)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);
	/** Removes an ADM image object from memory.
			@param inImage The ADM image object.
			@return Nothing.
		*/
	void ADMAPI (*Destroy)(ADMImageRef inImage);

	// image data accessors

	/** Retrieves the width of an ADM image in pixels.
			@param inImage The ADM image object.
			@return The width in pixels.
		*/
	ADMInt32 ADMAPI (*GetWidth)(ADMImageRef inImage);
	/** Retrieves the height of an ADM image.
			@param inImage The ADM image object.
			@return The height in pixels.
		*/
	ADMInt32 ADMAPI (*GetHeight)(ADMImageRef inImage);
	/** Retrieves the width of an ADM image in bytes. The number of bytes
		varies with the bits-per-pixel of the color space.
			@param inImage The ADM image object.
			@return The byte width value.
		*/
	ADMInt32 ADMAPI (*GetByteWidth)(ADMImageRef inImage);
	/** Retrieves the number of bits used to specify a pixel in the image.
		This value varies with the color space.
			@param inImage The ADM image object.
			@return The bits-per-pixel value.
		*/
	ADMInt32 ADMAPI (*GetBitsPerPixel)(ADMImageRef inImage);

	// raw pixel data access

	/** Begins an operation that accesses the image data associated with
		an image object. Locks the object so that the data pointer remains
		valid. When the data access operation is finished, unlock the object
		with \c #EndBaseAddressAccess().
			@param inImage The ADM image object.
			@return A pointer to the beginning address of the image data.
		*/
	ADMBytePtr ADMAPI (*BeginBaseAddressAccess)(ADMImageRef inImage);
	/** Unlocks an image after accessing the image data, in an operation
		opened by \c #BeginBaseAddressAccess().
			@param inImage The ADM image object.
			@return Nothing.
		*/
	void ADMAPI (*EndBaseAddressAccess)(ADMImageRef inImage);

	// ADMDrawer access

	/** Opens a sequence of calls to \c #ADMDrawerSuite6 functions
		that operation on an image. Locks the image object so that the drawer's
		data pointer remains valid.When the sequence is complete,
		call \c #EndADMDrawer() to unlock the object.
			@param inImage The ADM image object.
			@return The drawer object with which to manipulate the image.
		*/
	ADMDrawerRef ADMAPI (*BeginADMDrawer)(ADMImageRef inImage);
	/** Unlocks an image after accessing the image data with a drawer object,
		in a sequence opened by \c #BeginADMDrawer().
			@param inImage The ADM image object.
			@return Nothing.
		*/
	void ADMAPI (*EndADMDrawer)(ADMImageRef inImage);

	// AGMImage access
		// only available if host app exports AGM suites

	/** @deprecated Use AGM image functions instead. */
	void ADMAPI (*BeginAGMImageAccess)(ADMImageRef inImage, struct _t_ADMAGMImageRecord* outImageRecord);
	/** @deprecated Use AGM image functions instead. */
	void ADMAPI (*EndAGMImageAccess)(ADMImageRef inImage);

	// single pixel access

	/** Retrieves the color data for a pixel at a specified position in an image.
			@param inImage The ADM image object.
			@param inPoint The position of the pixel.
			@param outColor [out] A buffer in which to return the color data.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, ADMRGBColor* outColor);
	/** Sets the color data for a pixel at a specified position in an image.
			@param inImage The ADM image object.
			@param inPoint The position of the pixel.
			@param inColor The new color data.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*SetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, const ADMRGBColor* inColor);

	// more image creation options

	/** Creates a bitmap image, which uses 1 bit per pixel.
			@param inWidth The image width in pixels.
			@param inHeight The image height in pixels.
			@param inOptions Not used. Pass 0.
			@return The ADM image object.
		*/
	ADMImageRef ADMAPI (*CreateBitmap)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);
	/** Creates an image using the color depth of the current screen settings.
			@param inWidth The image width in pixels.
			@param inHeight The image height in pixels.
			@param inOptions Creation options, \c #kADMImageHasAlphaChannelOption or 0.
			@return The ADM image object.
		*/
	ADMImageRef ADMAPI (*CreateOffscreen)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);

}
ADMImageSuite2;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMImageOld__
#ifdef MAC_ENV
#include "ADMImageOld.h"
#else
#include ".\Legacy\ADMImageOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMImage__
