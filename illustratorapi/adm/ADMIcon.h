/*******************************************************************************
*
* ADMIcon.h -- ADM Icon Suite
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
* Started by Paul Asente, 01 Aug 1996
*
********************************************************************************/

/** @file ADMIcon.h ADM Icon Suite */

#ifndef __ADMIcon__
#define __ADMIcon__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
/**	Icon types. Used as input when creating icons, or as output to determine the
 	type of icons retrieved from resources. See \c #\c #ADMIconSuite2::GetFromResource().  */
enum ADMIconType {

	/** Mac OS 'CICN' icon type	  */
	kCICN,
	/** Mac OS 'PICT' icon type	  */
	kPICT,
	/** Mac OS Icon Suite icon type	  */
	kIconSuite,

	/** Windows icon type	  */
	kWinIcon,
	/** Windows BMP icon type	  */
	kBMP,

	/** Platform-independent icon type	  */
	kADMImageIcon,

	/** Mac OS X CG image icon type	  */
	kCGImage,	// Only supported on OS X (10.2 and later)
	/** Unknown icon type. An icon of this type is created when
		you call \c #ADMIconSuite2::GetFromResource() if the
		specified resource is not found.*/
	kUnknown

};

/** Predefined icons */
enum {
	/** Predefined caution icon */
	kADMCautionIcon = -1000,
	/** Predefined stop icon */
	kADMStopIcon = -1001
};

#ifndef __cplusplus
typedef enum ADMIconType ADMIconType;
#endif

// =============================================================================
//		* ADM Icon Suite
// =============================================================================

/** Icon suite name */
#define kADMIconSuite				("ADM Icon Suite")
/** Icon suite version */
#define kADMIconSuiteVersion2		(2)

// -----------------------------------------------------------------------------

/**	@ingroup Suites
	This suite provides a platform-independent interface to picture resources
	in Mac OS and Windows, which are represented as ADM icons.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMIconSuite and \c #kADMIconSuiteVersion2.
*/
typedef struct ADMIconSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/** Creates an ADM icon using a resource loaded from a plug-in.
		Searches the plug-in's resources for a PICT or BMP, and if
		not found, for an IconSuite or Icon. Does not load resources of
		type CICN.
			@param inPluginRef The plug-in reference.
			@param inName The unique, identifying name of the icon.
			@param inIconID The platform-specific resource identifier.
			@param inIconIndex A 1-based index added to the ID to get the
				final resource identifier of the icon.
			@return An ADM icon object. The type is \c #kUnknown if a
				resource could not be loaded.
			@see \c #GetType()
		*/
	ADMIconRef ADMAPI (*GetFromResource)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inIconID, ADMInt32 inIconIndex);

	/** Creates an ADM icon using supplied image data. The image data is not
		copied; if you release the memory, or if the image is in static memory
		that becomes invalid when the plug-in is unloaded, you must also destroy
		the icon object using \c #Destroy().
			@param inIconType The icon type constant.
			@param inWidth The icon width in pixels.
				Families of icons should all be the same size.
			@param inHeight The icon height in pixels.
			@param inData A pointer to the image data.
			@return An ADM icon object.
		*/
	ADMIconRef ADMAPI (*Create)(ADMIconType inIconType, ADMInt32 inWidth,
				ADMInt32 inHeight, void* inData);

	/** Removes an ADM icon object from memory. If it was created using
		\c #GetFromResource(), frees the image data. If it was created
		using \c #Create(), you must free the image memory before calling
		this function.
			@param inIcon The ADM icon object.
			@return Nothing.
		*/
	void ADMAPI (*Destroy)(ADMIconRef inIcon);

	/** Retrieves the type of an ADM icon.
			@param inIcon The ADM icon object.
			@return The type constant.
		*/
	ADMIconType ADMAPI (*GetType)(ADMIconRef inIcon);

	/** Retrieves the width of an ADM icon.
			@param inIcon The ADM icon object.
			@return The width in pixels.
		*/
	ADMInt32 ADMAPI (*GetWidth)(ADMIconRef inIcon);

	/** Retrieves the height of an ADM icon.
			@param inIcon The ADM icon object.
			@return The height in pixels.
		*/
	ADMInt32 ADMAPI (*GetHeight)(ADMIconRef inIcon);

	/** Retrieves the image data reference by an ADM icon.
		If you need the actual pixel information, you must
		parse the referenced data according to the platform
		resource specification or use platform-specific functions.
			@param inIcon The ADM icon object.
			@return A pointer to the image data.
		*/
	ADMAPI void* (*GetData)(ADMIconRef inIcon);


	/** Reports whether an ADM icon is references image data
		loaded from a plug-in resource file, or was created
		with a direct reference to image data.
			@param inIcon The ADM icon object.
			@return True if the icon was created from a resource, false otherwise.
			@see \c #GetFromResource(), \c #Create()
		*/
	ADMBoolean ADMAPI (*IsFromResource)(ADMIconRef inIcon);

	/** Converts an ADM image to an ADM icon.
		The ADM icon takes ownership of the image, so the caller does not
		need to deallocate it.
			@param inImage The ADM image object; see \c #ADMImageSuite2.
			@return The ADM icon object.
		*/
	ADMIconRef ADMAPI (*CreateFromImage)(ADMImageRef inImage);

}
ADMIconSuite2;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMIconOld__
#ifdef MAC_ENV
#include "ADMIconOld.h"
#else
#include ".\Legacy\ADMIconOld.h"
#endif
#endif



// -----------------------------------------------------------------------------

#endif	// __ADMIcon__
