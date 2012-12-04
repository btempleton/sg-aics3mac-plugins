#ifndef __AITracing__
#define __AITracing__

/*
 *        Name:	AITracing.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tracing Suite.
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

#ifndef __AIRaster__
#include "AIRaster.h"
#endif

#ifndef __AIDictionary__
#include "AIDictionary.h"
#endif

#ifndef __AIImageOptimization__
#include "AIImageOptimization.h"
#endif


#include "AIHeaderBegin.h"

/** @file AITracing.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAITracingSuite				"AI Tracing Suite"
#define kAITracingSuiteVersion1		AIAPI_VERSION(1)
#define kAITracingSuiteVersion		kAITracingSuiteVersion1
#define kAITracingVersion			kAITracingSuiteVersion


#define kAITracingIPSuite			"AI Tracing IP Suite"
#define kAITracingIPSuiteVersion1	AIAPI_VERSION(1)
#define kAITracingIPSuiteVersion	kAITracingIPSuiteVersion1
#define kAITracingIPVersion			kAITracingIPSuiteVersion


/** @ingroup Notifiers
	Sent after an Update call is made and completed.
  	Message data contains the tracing object being updated.
  	See \c #AITracingSuite. */
#define kAITracingUpdateNotifier			"AI Tracing Update Notifier"
/** @ingroup Notifiers
	Sent when a tracing preset (a named collection of configuration state data
	for a specific tracing operation) is created or renamed.
	See \c #AITracingSuite. */
#define kAITracingPresetNameChangedNotifier	"AI Tracing Preset Name Changed Notifier"



/*******************************************************************************
 **
 ** Catalog Keys - Presets
 **
 **/

/** Catalog key for tracing presets. See \c #AITracingSuite. */
#define kAITracingPresetsCatalogName 		"Adobe Tracing Presets"

/*******************************************************************************
 **
 ** Dictionary Keys - Options
 **
 **/

/** @ingroup DictKeys
	Internal. The document dictionary key for the most recently used preset, a string.
	If the key is missing or \c NULL, the "Custom" global preset is assumed. */
#define kTracingGlobalPresetKey				"-adobe/tracing/options/global/preset"
/** @ingroup DictKeys
	Key for the main options dictionary for tracing. See \c #AITracingSuite. */
#define kTracingOptionsKey					"adobe/tracing/options"
/** @ingroup DictKeys
	Internal. Key for the old options dictionary for tracing. */
#define kTracingOptionsOldKey				"-adobe/tracing/options/old"
/** @ingroup DictKeys
	Internal. Key for the artwork cache dictionary for tracing. */
#define kTracingCacheKey					"-adobe/tracing/cache"
/** @ingroup DictKeys
	Key for the tracing statistics dictionary. Includes the path count, color count, PPI, and so on. */
#define kTracingStatisticsKey				"adobe/tracing/statistics"

// options contents
/** @ingroup DictKeys
	Tracing option key for preset . String. */
#define kTracingPresetKey					"adobe/tracing/preset"
/** @ingroup DictKeys
	Tracing option key for whether to resample. Boolean. */
#define kTracingResampleKey					"adobe/tracing/resample"
/** @ingroup DictKeys
	Tracing option key for resample resolution. Float, PPI. */
#define kTracingResampleResolutionKey		"adobe/tracing/resolution"
/** @ingroup DictKeys
	Tracing option key for mode. an \c #AITracingMode constant. */
#define kTracingModeKey						"adobe/tracing/mode"
/** @ingroup DictKeys
	Tracing option key for blur. Float. */
#define kTracingBlurKey						"adobe/tracing/ip/blur"
/** @ingroup DictKeys
	Tracing option key for threshold. Long. */
#define kTracingThresholdKey				"adobe/tracing/ip/threshold"
/** @ingroup DictKeys
	Tracing option key for palette. String. */
#define kTracingPaletteKey					"adobe/tracing/ip/palette"
/** @ingroup DictKeys
	Internal. Tracing option key for embedded palette. Hidden dictionary, use EmbedSwatches instead. */
#define kTracingEmbeddedPaletteKey			"adobe/tracing/ip/embedded/palette"		// dictionary (hidden, use EmbedSwatches instead)
/** @ingroup DictKeys
	Internal. Tracing option key for custom color references.  */
#define kTracingCustomColorsKey				"adobe/tracing/ip/custom/colors"		// dictionary (hidden, do not access, housekeeping of referenced custom colors)
/** @ingroup DictKeys
	Tracing option key for swatch name. String. */
#define kTracingSwatchNameKey				"adobe/tracing/swatch/name"
/** @ingroup DictKeys
	Tracing option key for swatch color, stores embedded custom colors. A fill style. */
#define kTracingSwatchColorKey				"adobe/tracing/swatch/color"
/** @ingroup DictKeys
	Tracing option key for maximum number of colors. Long. */
#define kTracingMaxColorsKey				"adobe/tracing/ip/maxcolors"
/** @ingroup DictKeys
	Tracing option key for whether to trace fills. Boolean. */
#define kTracingFillsKey					"adobe/tracing/tracing/fills"
/** @ingroup DictKeys
	Tracing option key for whether to trace strokes. Boolean. */
#define kTracingStrokesKey					"adobe/tracing/tracing/strokes"
/** @ingroup DictKeys
	Tracing option key for stroke weight. Float. */
#define kTracingMaxStrokeWeightKey			"adobe/tracing/tracing/maxstrokeweight"
/** @ingroup DictKeys
	Tracing option key for stroke length. Float.  */
#define kTracingMinStrokeLengthKey			"adobe/tracing/tracing/minstrokelength"
/** @ingroup DictKeys
	Tracing option key for path tightness. Float.  */
#define kTracingPathTightnessKey			"adobe/tracing/tracing/pathtightness"
/** @ingroup DictKeys
	Tracing option key for corner angle. Float.  */
#define kTracingCornerAngleKey				"adobe/tracing/tracing/cornerangle"
/** @ingroup DictKeys
	Tracing option key for minimum area. Long.  */
#define kTracingMinimumAreaKey				"adobe/tracing/tracing/minimumarea"
/** @ingroup DictKeys
	Tracing option key for how to visualize vectors. An \c #AITracingVisualizeVectorType constant.  */
#define kTracingVisualizeVectorKey			"adobe/tracing/visualize/vector"
/** @ingroup DictKeys
	Tracing option key for how to visualize rasters. An \c #AITracingVisualizeRasterType constant.  */
#define kTracingVisualizeRasterKey			"adobe/tracing/visualize/raster"
/** @ingroup DictKeys
	Tracing option key for whether to use Live Paint. Boolean. */
#define kTracingLivePaintKey				"adobe/tracing/output/livepaint"
/** @ingroup DictKeys
	Tracing option key for whether to output to swatches. Boolean. */
#define kTracingOutputToSwatchesKey			"adobe/tracing/output/outputtoswatches"
/** @ingroup DictKeys
	Tracing option key for whether to output "white" background or not.  Boolean.  New for CS3. */
#define kTracingIgnoreWhiteKey				"adobe/tracing/output/ignorewhite"


// cache contents
/** @ingroup DictKeys
	Tracing cache key for tracing art. Art object. */
#define kTracingTracingArtKey				"adobe/tracing/tracing/art"
/** @ingroup DictKeys
	Tracing cache key for preprocessed images. Raster art object. */
#define kTracingPreprocessedImageKey		"adobe/tracing/preprocessed/image"
/** @ingroup DictKeys
	Tracing cache key for whether source art has changed
	(used to optimize art regeneration). Boolean. */
#define kTracingSourceArtChangedKey			"adobe/tracing/src/changed"
/** @ingroup DictKeys
	Internal. Tracing cache key for scratch group. Group art object. */
#define kTracingScratchGroupKey				"adobe/tracing/scratch/group"
/** @ingroup DictKeys
	Tracing cache key for the adjusted raster transformation matrix. Matrix. */
#define kTracingAdjustedRasterMatrixKey		"adobe/tracing/raster/matrix"
/** @ingroup DictKeys
	Tracing cache key for the adjusted raster checksum. Integer. */
#define kTracingAdjustedRasterChecksumKey	"adobe/tracing/raster/checksum"

// statistics contents
/** @ingroup DictKeys
	Tracing statistics key for number of paths generated. Long.  */
#define kTracingPathCountKey				"adobe/tracing/statistics/pathcount"
/** @ingroup DictKeys
	Tracing statistics key for number of anchors generated. Long.  */
#define kTracingAnchorCountKey				"adobe/tracing/statistics/anchorcount"
/** @ingroup DictKeys
	Tracing statistics key for number of colors used. Long.  */
#define kTracingColorCountKey				"adobe/tracing/statistics/colorcount"
/** @ingroup DictKeys
	Tracing statistics key for number of enclosed areas generated. Long.  */
#define kTracingAreaCountKey				"adobe/tracing/statistics/areacount"
/** @ingroup DictKeys
	Tracing statistics key for effective PPI of the source image. Float.  */
#define kTracingSourceImagePPIKey			"adobe/tracing/statistics/sourceppi"


#define kTracingResampleDefault				(false)
/** Internal */
#define kTracingResampleResolutionDynamic	(0.0f)		// secret resolution used to indicate use of "native" dynamically derived resolution.
#define kTracingResampleResolutionDefault	(72.0f)
#define kTracingResampleResolutionMinimum	(1.0f)
#define kTracingResampleResolutionMaximum	(600.0f)
#define kTracingResampleResolutionIncrement	(1.0f)
#define kTracingModeDefault					(2)
#define kTracingBlurDefault					(0.0f)
#define kTracingBlurMinimum					(0.0f)
#define kTracingBlurMaximum					(20.0f)
#define kTracingBlurIncrement				(0.1f)
#define kTracingThresholdDefault			(128)
#define kTracingThresholdMinimum			(1)
#define kTracingThresholdMaximum			(255)
/** Empty string means Automatic. */
#define kTracingPaletteDefault				("")
#define kTracingMaxColorsDefault			(6)
#define kTracingMaxColorsMinimum			(2)
#define kTracingMaxColorsMaximum			(256)
#define kTracingMaxColorsIncrement			(1)
#define kTracingFillsDefault				(true)
#define kTracingStrokesDefault				(false)
#define kTracingMaxStrokeWeightDefault		(10.0f)
#define kTracingMaxStrokeWeightMinimum		(0.01f)
#define kTracingMaxStrokeWeightMaximum		(100.0f)
#define kTracingMaxStrokeWeightIncrement	(1.0f)
#define kTracingMinStrokeLengthDefault		(20.0f)
#define kTracingMinStrokeLengthMinimum		(0.0f)
#define kTracingMinStrokeLengthMaximum		(200.0f)
#define kTracingMinStrokeLengthIncrement	(1.0f)
#define kTracingPathTightnessDefault		(2.0f)
#define kTracingPathTightnessMinimum		(0.0f)
#define kTracingPathTightnessMaximum		(10.0f)
#define kTracingPathTightnessIncrement		(0.1f)
#define kTracingMinimumAreaDefault			(10)
#define kTracingMinimumAreaMinimum			(0)
#define kTracingMinimumAreaMaximum			(3000)
#define kTracingMinimumAreaIncrement		(1)
/** Default is \c #kAITracingVisualizeVectorArtwork */
#define kTracingVisualizeVectorDefault		(1)
/** Default is \c #kAITracingVisualizeRasterNone */
#define kTracingVisualizeRasterDefault		(0)
#define kTracingLivePaintDefault			(false)
#define kTracingOutputToSwatchesDefault		(false)
#define kTracingIgnoreWhiteDefault			(false)
#define kTracingROIInitialStateDefault		(true)
/** Internal */
#define kTracingSourceArtChangedDefault		(true)

#define kTracingCornerAngleDefault			(20.0f)
#define kTracingCornerAngleMinimum			(0.0f)
#define kTracingCornerAngleMaximum			(180.0f)


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a tracing state object, never dereferenced.
	Access with \c #AITracingSuite. */
typedef struct _t_AITracingState *AITracingStateHandle;

/** Opaque reference to a view options object, never dereferenced.
	Access with \c #AITracingSuite.  */
typedef struct _t_AITracingViewOptions *AITracingViewOptionsHandle;



/** Color models to which an image processing code can be reduced,
	an \c #AITracingModeValue. */
typedef long AITracingMode;
/** Color models for \c #AITracingMode  */
enum AITracingModeValue
{
	/** Color, either RGB or CMYK depending on source image.  */
	kAITracingModeColor,
	/** Grayscale. */
	kAITracingModeGray,
	/** Monochrome bitmap. */
	kAITracingModeBlackAndWhite
};

/** Visualization modes for the vector portion of tracing output,
	an \c #AITracingVisualizeVectorValue.*/
typedef long AITracingVisualizeVectorType;
/** Vector modes for tracing output in \c #AITracingVisualizeVectorType. */
enum AITracingVisualizeVectorValue
{
	/** No Artwork.  */
	kAITracingVisualizeVectorArtworkNone,
	/** Artwork. The full result, paths and fills, of the tracing.  */
	kAITracingVisualizeVectorArtwork,
	/** Paths. A paths-only version of the art with black stroked paths.  */
	kAITracingVisualizeVectorPaths,
	/** Paths and Transparency.  A transparent version of the art with black stroked paths overlayed.  */
	kAITracingVisualizeVectorPathsAndTransparency
};


/** Visualization modes for the raster portion of tracing output,
	an \c #AITracingVisualizeRasterValue.*/
typedef long AITracingVisualizeRasterType;
/** Raster modes for tracing output in \c #AITracingVisualizeRasterType. */
enum AITracingVisualizeRasterValue
{
	/** None. No raster is included in the visualization.  */
	kAITracingVisualizeRasterNone,
	/** Original. Include the original raster input
		(before preprocessing).  */
	kAITracingVisualizeRasterOriginal,
	/** Preprocessed. Include the preprocessed image.  */
	kAITracingVisualizeRasterPreprocessed,
	/** Transparency. Include a transparent version of the
		original raster input (before preprocessing).   */
	kAITracingVisualizeRasterTransparency
};



/*******************************************************************************
 **
 **	Suite Record
 **
 **/


/**	@ingroup Suites
	This suite gives you access to the object model for the \e tracing art type,
	a plug-in group containing:
		\li A source image.
		\li A posterized/preprocessed version of the source image, called the tracing result or result group.
		\li The options used for tracing.
		\li The internal tracing state kept by the vectorization engine.
		\li The view options that determine which elements of the group to display during update.

	A tracing \e preset is a named collection of state information that can be used to recreate
	a commonly used tracing configuration. It includes parameters specific to the
	various tracing tasks such as color tracing, black and white tracing, high resolution
	tracing, low resolution tracing, and so on.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITracingSuite and \c #kAITracingVersion.
 */
typedef struct {

	/** Creates a tracing group whose source art is the specified raster or foreign object art.
		Use \c #Update() to create the result group.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object for the paint order.
			@param art A raster art object or a foreign object.
			@param tracing [out] A buffer in which to return the tracing plug-in group
	 */
	AIAPI AIErr (*CreateTracing) (short paintOrder, AIArtHandle prep, AIArtHandle art, AIArtHandle *tracing);

	/** Reports whether an art object is a tracing group.
		(Note that this function returns a boolean value, not an error code.)
			@param tracing The art object.
			@return True if the art is a tracing group.
		*/
	AIAPI AIBoolean (*IsTracing) (AIArtHandle tracing);

	/** Retrieves the source art of a tracing group.
			@param tracing The tracing group object.
				@param raster [out] A buffer in which to return the source art,
					a raster art object or foreign object.
		*/
	AIAPI AIErr (*GetSourceImage) (AIArtHandle tracing, AIArtHandle *raster);

	/** Copies the tracing result art of a tracing group into the current document.
			@param tracing The tracing group object.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object for the paint order.
			@param art [out] A buffer in which to return the copied result group.
			@param copyAsViewed True to copy the tracing result as viewed; that is, maintaining the
				visual appearance of viewing modes currently in effect. False to copy
				as if in the Show-No-Image/Show-Tracing-Result mode.
		*/
	AIAPI AIErr (*CopyTracingArt) (AIArtHandle tracing, short paintOrder, AIArtHandle prep, AIArtHandle *art, AIBool8 copyAsViewed);

	/** Retrieves the tracing options dictionary of a tracing group.
			@param tracing The tracing group object.
			@param options [out] A buffer in which to return the options dictionary.
				This is a counted object (see \c AICountedObject.h).
				Use the \c Ref class to access it. See \c IAIRef.h.
				@see \c #kTracingOptionsKey
		 */
	AIAPI AIErr (*AcquireTracingOptions) (AIArtHandle tracing, AIDictionaryRef *options);

	/** Retrieves the tracing statistics dictionary of a tracing group.	This is a read-only dictionary.
			@param tracing The tracing group object.
			@param options [out] A buffer in which to return the statistics dictionary.
				This is a counted object (see \c AICountedObject.h).
				Use the \c Ref class to access it. See \c IAIRef.h.
				@see \c #kTracingStatisticsKey
		*/
	AIAPI AIErr (*AcquireTracingStatistics) (AIArtHandle tracing, AIDictionaryRef *options);

 	/** Embeds swatches in the tracing result.  Call after changing
 		the \c #kTracingPaletteKey option value.
			@param tracing The tracing group object.
	 */
	AIAPI AIErr (*EmbedSwatches) (AIArtHandle tracing);

	/** Creates the tracing result from the source art of a tracing group.
		Vectorizes the preprocessed image based on the input options.
			@param tracing The tracing group object.
	  */
	AIAPI AIErr (*Update) (AIArtHandle tracing);


	/** Retrieves the native resolution (if any) of an art object.
			@param art The art object, typically a tracing group, raster, or foreign object.
			@param dpi [out] A buffer in which to return the native resolution in DPI,
				if strictly uniform scaling	has been applied to the source art.
				or 0 if no native resolution is available.
	 	*/
	AIAPI AIErr (*GetNativeResolution) (AIArtHandle art, AIReal *dpi);

	/** Retrieves the effective resolution of a tracing object.
			@param art The tracing art object.
			@param dpi [out] A buffer in which to return:
				\li The resampling DPI if resampling is turned on
				\li The effective resolution in DPI	if strictly uniform scaling has been applied to the source art.
				\li The average of x/y DPI if non-uniform scaling has been applied.
		 */
	AIAPI AIErr (*GetEffectiveResolution) (AIArtHandle art, AIReal *dpi);

	/** Reports whether the source art of a tracing group has changed.
			@param tracing The art object.
			@param changed [out] A buffer in which to return true if the source art has changed.
		*/
	AIAPI AIErr (*SetSourceArtChanged) (AIArtHandle tracing, AIBoolean changed);

} AITracingSuite;





/**	@ingroup Suites

	This suite provides image-processing functions that preprocess images
	for use with tracing, preparing raster data for vectorization.
	The image is manipulated in place.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITracingIPSuite and \c #kAITracingIPVersion.
 */
typedef struct {

	/** Posterizes a raster image.
			@param image The source raster art.
			@param palette The color palette to use.
		*/
	AIAPI AIErr (*Posterize) (AIArtHandle image, AIColorPaletteHandle palette);

	/** Converts colors to black and white by first converting
		each pixel of the input image into a grayscale value in the range of
		[0..255], then converting values below the threshold to black,
		and those at or above the threshold to white.
			@param image The source raster art.
			@param level The threshold level, in the range [0..255].
		*/
	AIAPI AIErr (*Threshold) (AIArtHandle image, long level);

	/** Converts a raster image to grayscale.
			@param image The source raster art.
		*/
	AIAPI AIErr (*ConvertToGray) (AIArtHandle image);


} AITracingIPSuite;



#include "AIHeaderEnd.h"


#endif
