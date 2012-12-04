#ifndef __AI110OverrideColorConversion__
#define __AI110OverrideColorConversion__

/*
 *        Name:	AIOverrideColorConversion.h
 *   $Revision: 13 $
 *     Purpose:	Adobe Illustrator Suite to replace internal color
 *              conversion functionality.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
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
#include "AITypes.h"          /* Include Adobe Standard Types */
#endif

#include "AIOverrideColorConversion.h"

#include "AIHeaderBegin.h"

/** @file AIOverrideColorConversion.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110OverrideColorConversionSuite			"Override AI Color Conversion Suite"
#define kAIOverrideColorConversionSuiteVersion4		AIAPI_VERSION(4)
#define kAI110OverrideColorConversionSuiteVersion	kAIOverrideColorConversionSuiteVersion4
#define kAI110OverrideColorConversionVersion		kAIOverrideColorConversionSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **
 */

/** The override color conversion suite provides APIs for managing and performing color
	conversions. See also the AIColorConversionSuite.
 */
typedef struct {

	/** Converts RGB image samples into CMYK to figure out if any of the samples
		were out of gamut. Return value inGamut will be true iff ALL the samples are in
		Gamut. The samples must be 8 bits per component. See #AIRGBPixelFormat for the
		rgbFormat values. */
	AIAPI AIErr ( *GamutRGBToCMYKImage )( void *srcBuf, const ASUInt32 numSamples, 
  										const ASUInt32 rgbFormat, ASBoolean *inGamut );

	/** Creates a transformation using the given source & destination profiles.
		renderIntent can be NULL to use default as selected by OverrideCC dialog.
		Profiles can be obtained using CreateProfileFromTag() or similar API. */
	AIAPI AIErr ( *CreateXform )(const AIColorProfile srcProfile, const AIColorProfile destProfile, ASUInt32 *xform ); 
	/** Frees a transform created with CreateTransform(). */
	AIAPI void  ( *FreeXform )( const ASUInt32 xform );

	/** Applies the given transform to a single color value. The convType parameter defines the
		format and range of the color components. */
	AIAPI AIErr ( *ApplyXformSample )( const ASUInt32 xform, ASFixed *inColor, ASFixed *outColor,
			const InternalColorTransformType convType, ASBoolean isLAB );
	/** Applies the given transform to a buffer of image data. The convType parameter defines the
		format and range of the color components. */
	AIAPI AIErr ( *ApplyXformImage )( const ASUInt32 xform, void *inBuffer, void *outBuffer, const ASUInt32 numPixels,
			const InternalColorTransformType convType, ASBoolean isLAB , ASInt16 format);

	/** Converts an ICC tag into a profile (must be free'ed) */
	AIAPI AIErr ( *CreateProfileFromTag )( void *buffer, const ASUInt32 size, AIColorProfile *profile ); 
	/** Get a current working space profile (must be free'ed). See #AIWorkingColorSpace. */
	AIAPI AIErr ( *GetWSProfile )( const ASUInt32 whichProfile, AIColorProfile *profile );
	/** Once a transform is created, the profile can be free'ed. */
	AIAPI void  ( *FreeProfile )( AIColorProfile profile );

	/** GetOpenPolicy() is intended to be used when opening a document. profile is the color profile
		if any embedded in the document. colorModel is the color model of the document (see 
		#AIDocumentColorModelValue). This API consults the color management policies, putting up
		dialogs to ask the user if need be, to determine how the profile should be used. The
		return value is one of #AIFileOpenColorProfilePolicy. If *profile is NULL and the policies
		indicate that a profile should be assigned then it will be set to the correct profile on
		return. */	
	AIAPI ASUInt32  ( *GetOpenPolicy )(AIColorProfile *profile, ASUInt32 colorModel);
	/** GetSavePolicy() is intended to be used when saving a document. whichSpace is the working space
		corresponding to the document color model. See #AIWorkingColorSpace for working spaces and
		#AIDocumentColorModeValue for document color models. On return policy is set to one of the
		values of #AIFileSaveColorProfilePolicy indicating which profile, if any, should be saved with
		the file. The default state of the "embed profile?" checkbox is also returned. If a profile
		is to be embedded then its name is returned in the character buffer profName. */
	AIAPI void  ( *GetSavePolicy )( const ASUInt32 whichSpace, ASUInt32 *policy, ASUInt32 *defaultState, char *profName);

	/** If data is null, returns the size of the buffer needed. If data is non-null, puts the profiles
		tag data into the buffer */
	AIAPI AIErr ( *GetProfileData ) (const AIColorProfile profile, ASUInt32 *size, void *data );
	/** Given a profile, returns a description string. */
	AIAPI AIErr ( *GetProfileName) (const AIColorProfile profile, char profileName[256] ) ;

	/** Creates and caches transforms to be used for *all* internal color conversions and in
		particular those done by the AIColorConversionSuite.
		
		- Call CreateInternalTransform() to create a transfrom
		- Call the ColorConversionSuite, with the appropriate src and dest colorspaces
		- Call FreeAllInternalTransforms() when done.

		For example, to do a calibrated CMYK to RGB conversion of a single sample (images work too)
		
		- CreateInternalTransform(CMYK2RGB, cmykProfile, rgbProfile)
		- AIColorConversionSuite::ConvertSampleColor(kAICMYKColorSpace, cmykSample, kAIRGBColorSpace, rgbSample)
		- FreeAllInternalTransforms()

		For the first four color transform types, supply the source and destination profiles.
		
		For the "2sRGB" transforms, if the source profile is null the profile of the top
		document is used. If the top document has no profile, then the corresponding working space
		will be used instead. The destination profile is ignored and will be set internally to sRGB.
		
		For the "LAB2RGB", source RGB data is interpreted as LAB. The source profile is
		ignored and is set internally to LAB. If the destination profile is null, the profile of the
		top document will be used. If that is NULL, the RGB working space will be used instead.
		
		So, to convert a sample in the top document from RGB to sRGB,
		
		- CreateInternalTransform(RGB2sRGB, NULL, NULL)
		- ConvertSampleColor(kAIRGBColorSpace, rgbSample, kAIRGBColorSpace, sRGBSample)
		- FreeAllInternalTransforms()
		
		To convert from LAB to RGB, 
		
		- CreateInternalTransform(LAB2RGB, NULL, NULL)
		- ConvertSampleColor(kAIRGBColorSpace, labSample, kAIRGBColorSpace, rgbSample)
		- FreeAllInternalTransforms()
	*/
	AIAPI AIErr ( *CreateInternalTransform) (const InternalColorTransformType whichOne, AIColorProfile scrProfile, AIColorProfile destProfile);
	/** Frees all cached transforms. Default color conversion is done once xform is free'ed. */
	AIAPI void  ( *FreeAllInternalTransforms) (void);

	/** Returns true if profiles are the same, false if different or are not valid profiles. */
	AIAPI void  ( *ProfsEqual) (const AIColorProfile srcProfile, const AIColorProfile destProfile, ASUInt32 *match); 
	
	/** Gets a transform created by CreateInternalTransform(), so it can be used in ApplyXformSample() or
		ApplyXformImage(). For example,

		- CreateInternalTranform(LAB2RGB, NULL, NULL)
		- GetInternalTransform(LAB2RGB, &xform);
		- ApplyXformSample(xform, incolor, outcolor, KLAB2RGB. false);
		- FreeAllInternalTransforms()

		Note that input LAB data must be scaled from
		
		- L in 0 to 100 => 0 to 255
		- A,B -128 to 127  => 0 to 255
	*/
	AIAPI	void  ( *GetInternalTransform)(const InternalColorTransformType whichOne,  ASUInt32 *xform);
	
	/** Signals that Black Point Compensation should be on for any color transforms subsequently performed.
		(This should be used for ADM drawing operations) */
	AIAPI void  ( *BPCOn ) (void) ;
	/** Set Black Point Compensation back to what it was */
	AIAPI void  ( *RestoreBPC )(void);

	// New in Illustrator 11.0

	/** Construct a profile from grayscale calibration information. */
	AIAPI AIErr ( *MakeProfileFromCalGray)(AIGrayCal *grayCal, AIColorProfile *profile);
	/** Construct a profile from RGB calibration information. */
	AIAPI AIErr ( *MakeProfileFromCalRGB)(AIRGBCal *rgbCal, AIColorProfile *profile);
	/** Construct a profile from CMYK calibration information. */
	AIAPI AIErr ( *MakeProfileFromCalCMYK)(AICMYKCal *cmykCal, AIColorProfile *profile);
	/** This function is similar to function CreateInternalTransform() for creating color transforms. This
		function is used when  source has more than 8 bits per channel to the maximum of 16 bit per channel.
		For source of more than 16bit, caller will have to truncate data to 16 bit himself and then use this
		function. BitDepth is array of size of number of channels, indicating bit depth of each channel.
		JPXLabParams is additional parameter required for kCIELab_16Bit2RGB color conversion and should be NULL
		for others. For CIELab color conversion, source can have 8bits per channel data also. */
	AIAPI AIErr  ( *CreateInternalTransform_16Bit)(const InternalColorTransformType whichOne, AIColorProfile srcProfile, AIColorProfile dstProfile,
			ASUInt8* bitDepth, JPXLabParams* jpxLabParams);

	/** Returns the color conversion policies and the state of "AI6" mode from the color settings dialog */
	AIAPI void   ( *GetColorSettingsPolicies)(ASBoolean *AI6Mode, ColorConvPolicy *rgbPolicy, ColorConvPolicy *cmykPolicy);

	/** returns the render intent from the color settings dialog **/
	AIAPI AIRenderingIntent ( *GetColorSettingsRenderIntent)(void);

} AI110OverrideColorConversionSuite;


#include "AIHeaderEnd.h"


#endif
