#ifndef __AI100OverrideColorConversion__
#define __AI100OverrideColorConversion__

/*
 *        Name:	AI100OverrideColorConversion.h
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

#include "AIOverrideColorConversion.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100OverrideColorConversionSuite			kAIOverrideColorConversionSuite
#define kAIOverrideColorConversionSuiteVersion3		AIAPI_VERSION(3)
#define kAI100OverrideColorConversionSuiteVersion	kAIOverrideColorConversionSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **
 *
 * Description:
 *
 * All image data is 8 bits / color component.
 *
 *
 * GamutRGBToCMYKImage
 *
 * Converts RGB image samples into CMYK to figure out if any of the samples
 * were out of gamut. Return value inGamut will be true iff ALL the samples are in
 * Gamut.
 *
 */

typedef struct {

  AIAPI AIErr ( *GamutRGBToCMYKImage )( void *srcBuf, const ASUInt32 numSamples, 
  										const ASUInt32 rgbFormat, ASBoolean *inGamut );

  /* These allow more general access to RB to allow color conversions using
   * arbitrary profiles. JM
   *
   * CreateXform - creates a transformation using the given source & destination profiles.
   *               renderIntent can be NULL to use default as selected by OverrideCC dialog.
   *
   * FreeXform - frees a transform created above.
   *
   * ApplyXformSample - applies the given transform to a single color value
   *
   * ApplyXformImage - applies the given transform to a buffer of image data
   *
   * CreateProfileFromTag - converts an ICC tag into a profile (must be free'ed)
   *
   * GetWSProfile - get a current working space profile (must be free'ed)
   *
   * FreeProfile - once a transform is created, the profile can be free'ed.
   *
   * GetOpenPolicy - given a profile, consults the current settings to see how that profile
   *				 should be used during a file open.
   *
   * GetSavePolicy - given a color space, tells which profile, if any, should be saved with a file.
   *				 The default state of the "embed profile?" checkbox is also returned.
   *
   * GetProfileData - if data is null, returns the size of the buffer needed.
   *				  if data is non-null, puts the profiles tag data into the buffer
   *
   * GetProfileName - given a profile, returns a description string.
   *
   * CreateInternalTransform - creates and caches transforms to be used for *all* internal color conversions
   *							1. Call CreateInternalTransform() to create a transfrom
   *							2. Call the ColorConversionSuite, with the appropriate src and dest colorspaces
   *							3. Call FreeAllInternalTransforms() when done.
   *
   *							For example, to do a calibrated CMYK to RGB conversion of a single sample (images work too)
   *							1. CreateInternalTransform(CMYK2RGB, cmykProfile, rgbProfile)
   *							2. ConvertSampleColor(kAICMYKColorSpace, cmykSample, kAIRGBColorSpace, rgbSample)
   *							3. FreeAllInternalTransforms()
   * 
   *							For the first four, supply the source and destination profiles.
   *							For the "2sRGB" transforms, if the source profile is null the profile of the top doc
   *							If the top doc has no profile, then the corresponding working space
   *							will be used instead. The destination profile is ignored and will be set internally to sRGB.
   *							For the ""LAB2RGB", source RGB data is interpreted as LAB. The source profile is
   *							ignored and is set internally to LAB. If the destination profile is null, the profile of the
   *							top doc will be used. If that is NULL, the RGB working space will be used instead.
   *							So, to convert a sample in the top doc from RGB to sRGB,
   *							1. CreateInternalTransform(RGB2sRGB, NULL, NULL)
   *							2. ConvertSampleColor(kAIRGBColorSpace, rgbSample, kAIRGBColorSpace, sRGBSample)
   *							3. FreeAllInternalTransforms()
   *							To convert from LAB to RGB, 
   *							1. CreateInternalTransform(LAB2RGB, NULL, NULL)
   *							2. ConvertSampleColor(kAIRGBColorSpace, labSample, kAIRGBColorSpace, rgbSample)
   *							3. FreeAllInternalTransforms()
   *							
   *
   * FreeAllInternalTransforms - frees all cached transforms. Default color conversion is done once xform is free'ed.
   *
   * ProfsEqual - returns true if profiles are the same, false if different or are not valid profiles
   *
   * GetInternalTransform - gets a transform created by CreateInternalTransform, so it can be used in ApplyXformSample or Image
   *							For example,						
   *							1. CreateInternalTranforms(LAB2RGB, NULL, NULL)
   *							2. GetInternalTransform(LAB2RGB, &xform);
   *							3. ApplyInternalTransformSample(xform, incolor, outcolor, KLAB2RGB. false);
   *						    4. FreeAllInternalTransforms()
   *							5. Note that input LAB data must be scaled from	L 0 to 100 => 0 to 255
   *																			A,B -128 to 127  => 0 to 255
   * BPCOn - signals that Black Point Compensation should be on for any color transforms subsequently performed.
   *		 (This should be used for ADM drawing operations) 
   *
   * RestoreBPC - set Black Point Compensation back to what it was
  
  */
  
  AIAPI AIErr ( *CreateXform )(const ASUInt32 srcProfile, const ASUInt32 destProfile, ASUInt32 *xform ); 
  AIAPI void  ( *FreeXform )( const ASUInt32 xform ); 
  AIAPI AIErr ( *ApplyXformSample )( const ASUInt32 xform, ASFixed *inColor, ASFixed *outColor, const InternalColorTransformType convType, ASBoolean isLAB ); 
  AIAPI AIErr ( *ApplyXformImage )( const ASUInt32 xform, void *inBuffer, void *outBuffer, const ASUInt32 numPixels, const InternalColorTransformType convType, ASBoolean isLAB , ASInt16 format); 
  AIAPI AIErr ( *CreateProfileFromTag )( void *buffer, const ASUInt32 size, ASUInt32 *profile ); 
  AIAPI AIErr ( *GetWSProfile )( const ASUInt32 whichProfile, ASUInt32 *profile );
  AIAPI void  ( *FreeProfile )( ASUInt32 profile );
  AIAPI ASUInt32  ( *GetOpenPolicy )(ASUInt32 *profile, ASUInt32 colorModel);
  AIAPI void  ( *GetSavePolicy )( const ASUInt32 whichSpace, ASUInt32 *policy, ASUInt32 *defaultState, char *profName);
  AIAPI AIErr ( *GetProfileData ) (const ASUInt32 profile, ASUInt32 *size, void *data );
  AIAPI AIErr ( *GetProfileName) (const ASUInt32 profile, char profileName[256] ) ;
  AIAPI AIErr ( *CreateInternalTransform) (const InternalColorTransformType whichOne, ASUInt32 scrProfile, ASUInt32 destProfile);
  AIAPI void  ( *FreeAllInternalTransforms) (void);
  AIAPI void  ( *ProfsEqual) (const ASUInt32 srcProfile, const ASUInt32 destProfile, ASUInt32 *match); 
  AIAPI	void  ( *GetInternalTransform)(const InternalColorTransformType whichOne,  ASUInt32 *xform);
  AIAPI void  ( *BPCOn ) (void) ;
  AIAPI void  ( *RestoreBPC )(void);

} AI100OverrideColorConversionSuite;


#include "AIHeaderEnd.h"


#endif
