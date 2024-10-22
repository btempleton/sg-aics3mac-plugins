#ifndef __AISLICING__
#define __AISLICING__

/*
 *        Name:	AISlicing.h
 *   $Revision: 2 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Slicing Suite.
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

#ifndef __SLICETYPES__
#include "AISliceTypes.h"
#endif

#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif

#ifndef __AIEntry__
#include "AIEntry.h"
#endif

#ifndef __AIPlatformMemory__
#include "AIPlatformMemory.h"
#endif

#ifndef __AIHTMLCONVERSION__
#include "AIHTMLConversion.h"
#endif

#ifndef AIFLASHPREFS_H
#include "AIFlashPrefs.h"
#endif

#ifndef _AISVGACTION_H_
#include "AISVGAction.h"
#endif

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#include "AIHeaderBegin.h"

/** @file AISlicing.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAISlicingSuite							"AI Slicing Suite"
#define kAISlicingSuiteVersion2					AIAPI_VERSION(2)
#define kAISlicingSuiteVersion					kAISlicingSuiteVersion2

#define kAIOptimizationSettingsSuite			"AI Optimization Settings Suite"
#define kAIOptimizationSettingsSuiteVersion1	AIAPI_VERSION(1)
#define kAIOptimizationSettingsSuiteVersion		kAIOptimizationSettingsSuiteVersion1


/** @ingroup Notifiers
	See \c #AISlicingSuite */
#define kAISlicingChangedNotifier	"AI Slicing Changed"
/** @ingroup MenuGroups
	See \c #AISlicingSuite */
#define kAISliceCommandsMenuGroup 	"AI Slice Commands Menu Group"


/*******************************************************************************
 **
 **	Types
 **
 **/
/** Image formats for slices.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
enum ASOptimizedFileFormat
{
	/** GIF format*/
	asffGIF89a,
	/** JPEG format */
	asffJPEG,
	/** PNG8 format */
	asffPNG8,
	/** PNG24 format */
	asffPNG24,
	/** Automatic format choice ("auto") */
	asffAuto,
	/** Invalid format ("") */
	asffInvalidFormat,
	/** Mixed formats ("mixed") */
	asffMixedFormat,
	/** SWF format */
	asffSWF,
	/** SVG format */
	asffSVG
};

/** Slice dithering methods; see \c #ASGIFSettings, \c #ASPNG8Settings. */
enum ASDitherAlgorithm
{
	/** "none" */
	asdaNone,
	/** "diffusion" */
	asdaDiffusion,
	/** "pattern" */
	asdaPattern,
	/** "whiteNoise */
	asdaWhiteNoise,
	/** "noise" */
	asdaBlueNoise
};

/** Slice noise-reduction methods; see \c #ASGIFSettings, \c #ASPNG8Settings. */
enum ASReductionAlgorithm
{
	/** "adaptive" */
	asraAdaptive,
	/** "selective" */
	asraSelective,
	/** "perceptual" */
	asraPerceptual,
	/** "macintoshSystem" */
	asraMacintoshSystem,
	/** "windowsSystem" */
	asraWindowsSystem,
	/** "web" */
	asraWeb,
	/** "custom" */
	asraImageReadyCustom,
	/** "fileBased" */
	asraFileBased,
	/** "neuralNet" */
	asraNeuralNet,
	/** "fauxPerceptual" */
	asraFauxPerceptual
};

/** A array entry for a color-shifting optimization setting.
	Allows you to map a range of colors to a single
	color, in order to reduce the overall number of colors for optimization.
	@see \c #AIOptimizationSettingsSuite::GetColorShiftEntries()
	*/
typedef struct
{
	/** Start of range */
	ADMRGBColor rangeStart;
	/** End of range */
	ADMRGBColor rangeEnd;
	/** A color to which all the colors in this range can be mapped. */
	ADMRGBColor remapColor;
}
ASColorShiftEntry;

/** GIF optimization settings for slices.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** True to use transparency. */
	ASBoolean transparency;
	/** True to include caption with slice. */
	ASBoolean includeCaption;
	/** True to use interlacing. */
	ASBoolean interlaced;

	/** True to use no matte color. */
	ASBoolean noMatteColor;
	/** The matte color, if used. */
	ADMRGBColor matteColor;

	/** True to do automatic reduction. */
	ASBoolean autoReduced;
	/** True to use a rollover master palette. */
	ASBoolean rolloverMasterPalette;

	/** Percentage of color shifting for web, range [0..100].  */
	ASInt32 webShiftedPercentage;
	/** Number of colors. */
	ASInt32 numberOfColors;
	/** Quality, range  */
	ASInt32 qualitySetting;
	/** The dithering method. */
	ASDitherAlgorithm ditherAlgorithm;
	/** The dithering percentage, [0..100], where 100 is maximum dithering.  */
	ASInt32 ditherPercentage;
	/** The reduction method. */
	ASReductionAlgorithm reductionAlgorithm;

	/** The reduction algorithm file.
		See \c #ASSliceSettings for memory allocation rules. */
	ASHandle reductionAlgorithmFilename;
	/** The dithering method for transparency. */
	ASDitherAlgorithm	transparencyDitherAlgorithm;
} ASGIFSettings;

/** JPEG optimization settings.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** Obsolete, ignored */
	ASBoolean transparency;
	/** True to use no matte color. */
	ASBoolean noMatteColor;
	/** The matte color, if used. */
	ADMRGBColor matteColor;
	/** True to optimize. */
	ASBoolean optimized;
	/** Quality setting */
	ASInt32 qualitySetting;
	/** True to create slice progressively. */
	ASBoolean multiplePasses;
	/** Blurring amount */
	AIReal blurAmount;
	/** True to embed the color profile. */
	ASBoolean embedICCProfile;
} ASJPEGSettings;

/** PNG8 optimization settings.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** True to use transparency. */
	ASBoolean transparency;
	/** Not used */
	ASBoolean includeCaption;
	/** True to use interlacing. */
	ASBoolean interlaced;
	/** True to use no matte color. */
	ASBoolean noMatteColor;
	/** The matte color, if used. */
	ADMRGBColor matteColor;

	/** True to do automatic reduction. */
	ASBoolean autoReduced;
	/** True to use a rollover master palette. */
	ASBoolean rolloverMasterPalette;
	/** Percentage of color shifting for web, range [0..100].  */
	ASInt32 webShiftedPercentage;
	/** Number of colors. */
	ASInt32 numberOfColors;

	/** The dithering method. */
	ASDitherAlgorithm ditherAlgorithm;
	/** The dithering percentage, [0..100], where 100 is maximum dithering.   */
	ASInt32 ditherPercentage;
	/** The reduction method. */
	ASReductionAlgorithm reductionAlgorithm;

	/** The reduction algorithm file.
		See \c #ASSliceSettings for memory allocation rules. */
	ASHandle reductionAlgorithmFilename;
	/** The dithering method for transparency. */
	ASDitherAlgorithm	transparencyDitherAlgorithm;
} ASPNG8Settings;

/** PNG24 optimization settings.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** True to use transparency. */
	ASBoolean transparency;
	/** Not used */
	ASBoolean includeCaption;
	/** True to use interlacing. */
	ASBoolean interlaced;
	/** True to use no matte color. */
	ASBoolean noMatteColor;
	/** The matte color, if used. */
	ADMRGBColor matteColor;
	/** True to filter image. */
	ASBoolean filtered;
} ASPNG24Settings;

/** SVG optimization settings.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** How to subset fonts in the SVG. */
 	AISVGFontSubsetting fontSubsetting;
	/** Whether to embed or link fonts. */
 	AISVGFileLocation fontLocation;
 	/** Whether to embed or link raster data. */
	AISVGRasterLocation imageLocation;
	/** True if obsolete. */
	ASBoolean obsolete;
	/** The compression method. */
 	AISVGFileCompression compression;
 	/** The number of digits of precision after the decimal when rounding numbers. */
 	AISVGCoordinatePrecision precision;
 	/** The character set to use for the SVG file. */
 	AISVGDocumentEncoding  encoding;
 	/** How style information should be exported. */
 	AISVGStyle style;
	/** The SVG DTD type. */
	AISVGDTD dtd;
	/** What type of font to use. */
	AISVGFontType fontType;
	/** True to optimize the SVG. */
	ASBoolean optimize;
} ASSVGSettings;

/** SWF optimization settings.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef struct
{
	/** Export options for layers */
 	FlashExportOption exportOption;
 	/** The frame rate. */
 	ASReal frameRate;
	/** True to create a continuous loop. */
 	ASBoolean loop;
	/** True to make SWF read-only. */
 	ASBoolean readOnly;
	/** The curve quality, [0..100] where 100 is best quality.  */
 	ASInt32 curveQuality;
	/** True to preserve appearance. */
	ASBoolean preserveAppearance;
	/** True to compress SWF. */
	ASBoolean compressed;
	/** True to save text as outline. */
	ASBoolean outlineText;
	/** The Flash Player version [1..8]*/
	ASInt32 flashPlayerVersion;
} ASSWFSettings;

/** Optimization settings for appropriate format.
	See \c #ASOptimizationSettings, \c #AIOptimizationSettingsSuite. */
typedef union
{
	ASGIFSettings	gif;
	ASJPEGSettings	jpeg;
	ASPNG8Settings	png8;
	ASPNG24Settings	png24;
	ASSVGSettings	svg;
	ASSWFSettings	swf;
} ASOptimizationSettingsUnion;

/** File format for save with appropriate optimization settings.
	See \c #AIOptimizationSettingsSuite. */
typedef struct ASOptimizationSettings
{
	/** The file format. */
	ASOptimizedFileFormat 		fileFormat;
	/** The file settings. */
	ASOptimizationSettingsUnion	s;
} ASOptimizationSettings;

/** Slice definition information.
	The handles identify blocks of memory managed by the \c #AIPlatformMemorySuite.
		\li For set calls, you must allocate the handle.
		\li For get calls, you can allocate and supply a handle, or specify NULL
			for the function to allocate a handle automatically.
		In either case, you must release handles when you no longer need them.
	@see \c #AIOptimizationSettingsSuite::SetOptimizationSettings(),
		\c #AIOptimizationSettingsSuite::GetOptimizationSettings(),
		\c #AIOptimizationSettingsSuite::SetSliceOptimizationSettings()
*/
typedef struct
{
	/** Identifies the slice group to which this slice belongs. */
	ASInt32 groupID;
	/** The type of slice. */
	ai::ESliceType type;
	/** True if text is HTML. */
	ASBoolean textIsHTML;
	/** True if text in cells is HTML. */
	ASBoolean cellTextIsHTML;
	/** The horizontal alignment type. */
	ai::ESliceHorzAlign horzAlign;
	/** The vertical alignment type. */
	ai::ESliceVertAlign vertAlign;
	/** The background color type. */
	ai::ESliceBGColorType bgColorType;
	/** The background color. */
	ADMRGBColor bgColor;

	/** The name object. */
	ASHandle hName;
	/** The URL object. */
	ASHandle hURL;
	/** The target object.  */
	ASHandle hTarget;
	/** The message object.  */
	ASHandle hMessage;
	/** The alternate tag object.   */
	ASHandle hAltTag;
	/** The cell-text object.   */
	ASHandle hCellText;
} ASSliceSettings;


typedef void* AISavedSliceListRef;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that allow you to create and manipulate
	\e image \e slices, subsets of raster data that can be used in copying from
	one buffer to another.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISlicingSuite and \c #kAISlicingSuiteVersion.
	*/
typedef struct {

	/** Designates an art object as a slice.
			@param art The art object.
			@param sliceID [in, out] Optionally, a unique identifier to use if possible. Upon
				return, the unique slice identifier actually assigned.
			@param fromPlace True if called from a plug-in file format.
				False if called from a menu or tool.
		*/
	AIAPI AIErr (*MakeSlice)(AIArtHandle art, ASInt32 *sliceID, ASBoolean fromPlace);

	/** Creates a rectangle with no fill and no stroke and makes it a slice.
			@param placeAboveArt The art object above which to place the new slice in the paint order.
			@param sliceID [in, out] Optionally, a unique identifier to use if possible. Upon
				return, the unique identifier actually assigned to the new slice.
			@param selected	True to select the new slice.
			@param fromPlace True if called from a plug-in file format.
				False if called from a menu or tool.
		 */
	AIAPI AIErr (*CreateSlice)(AIArtHandle placeAboveArt, ASInt32 *sliceID, AIBoolean selected, ASBoolean fromPlace);

	/** Deletes slice art and its slicing information.
			@param sliceID The unique identifier of the slice, as assigned on creation.
		*/
	AIAPI AIErr (*DeleteSlice)(ASInt32 sliceID);

	/** Removes the slicing designation from an art object, but does not delete the art.
			@param art The art object.
		*/
	AIAPI AIErr (*Unslice)(AIArtHandle art);

	/** Retrieves the unique slice identifier of an art object.
		(Note that this function returns a numeric value, not an error code.)
			@param art The art object.
			@return The unique slice identifier, or \c #kInvalidSliceID if the art is not a slice.
		*/
	AIAPI ASInt32 (*GetArtSliceID)(AIArtHandle art);

	/** Retrieves the art object for a slice
		(Note that this function returns an object value, not an error code.)
			@param sliceID The unique slice identifier.
			@return The associated art object, or \c NULL if there is no such slice.
		*/
	AIAPI AIArtHandle (*GetSliceArt)(ASInt32 sliceID);

	/** Retrieves a unique identifier suitable for a slice.
		(Note that this function returns a numeric value, not an error code.)
			@return A unique slice identifier.
		*/
	AIAPI ASInt32 (*GetUniqueSliceID)(void);

	/** Reports whether a unique identifier is currently used to identify a slice.
		(Note that this function returns a boolean value, not an error code.)
			@param sliceID The slice identifier.
			@return True if the identifier is in use.
		*/
	AIAPI AIBoolean (*SliceExists)(ASInt32 sliceID);

	/** Retrieves the number of slices in the slice list. Use with
		\c #GetIndexedSliceID() to iterate through slices.
		(Note that this function returns a numeric value, not an error code.)
			@return	The number of slices.
		*/
	AIAPI ASInt32 (*GetSliceCount)(void);

	/** Retrieves a slice from the slice list by position index. Use with
		\c #GetSliceCount() to iterate through slices.
		(Note that this function returns a numeric value, not an error code.)
			@param index The 0-based position index.
			@return	The unique slice identifier.
		*/
	AIAPI ASInt32 (*GetIndexedSliceID)(ASInt32 index);

	/** Sets the bounding rectangle for a no fill/no stroke slice.
		Does not affect a slice associated with any other art.
			@param sliceID The unique slice identifier.
			@param boundsRect The new bounding rectangle.
		*/
	AIAPI AIErr (*SetSliceBounds)(ASInt32 sliceID, AIRealRect *boundsRect);

	/**	Retrieves the bounding rectangle for a slice, including the border.
			@param sliceID The unique slice identifier.
			@param boundsRect [out] A buffer in which to return the bounding rectangle.
		*/
	AIAPI AIErr (*GetSliceBounds)(ASInt32 sliceID, AIRealRect *boundsRect);

	/** Sets a border for a slice, which is the appended to the art visual bounds
		to generate the slice bounds.
			@param sliceID The unique slice identifier.
			@param borderRect The new border rectangle.
		*/
	AIAPI AIErr (*SetSliceBorder)(ASInt32 sliceID, AIRealRect *borderRect);

	/**	Retrieves the border rectangle for a slice.
 			@param sliceID The unique slice identifier.
 			@param borderRect [out] A buffer in which to return the border rectangle.
 		*/
	AIAPI AIErr (*GetSliceBorder)(ASInt32 sliceID, AIRealRect *borderRect);

	/** Set the definition information for a slice.
			@param sliceID The unique slice identifier.
			@param settings The new slice information.
		*/
	AIAPI AIErr (*SetSliceSettings)(ASInt32 sliceID, ASSliceSettings *settings);

	/**	Retrieves the definition information for a slice.
 			@param sliceID The unique slice identifier.
 			@param settings [out] A buffer in which to return the information.
 		*/
	AIAPI AIErr (*GetSliceSettings)(ASInt32 sliceID, ASSliceSettings *settings);

	/** Sets a single slice attribute.
			@param sliceID The unique slice identifier.
			@param key The slice information attribute key.
			@param valueEntry The new attribute value.
		*/
	AIAPI AIErr (*SetSliceSetting)(ASInt32 sliceID, const AIDictKey &key, AIEntryRef valueEntry);

	/** Retrieves a single slice attribute.
			@param sliceID The unique slice identifier.
			@param key The slice information attribute key.
			@param valueEntry [out] A buffer in which to return the attribute value.
		*/
	AIAPI AIErr (*GetSliceSetting)(ASInt32 sliceID, const AIDictKey &key, AIEntryRef *valueEntry);

	/** Reports whether a slice can be converted to text.
		(Note that this function returns a boolean value, not an error code.)
			 @param sliceID The unique slice identifier.
			 @return True if the slice can be converted to text.
		*/
	AIAPI AIBoolean (*SliceIsText)(ASInt32 sliceID);

	/** Marks a slice so that it is converted to HTML text on output.
			 @param sliceID The unique slice identifier.
			 @param HTMLTextOptions The text conversion options,
			 	a logical OR of \c #AIHTMLConversionOptions values.
		*/
	AIAPI AIErr (*SetSliceIsHTMLText)(ASInt32 sliceID, long HTMLTextOptions);

	/** Reports whether a slice is converted to HTML text on output.
		(Note that this function returns a boolean value, not an error code.)
			 @param sliceID The unique slice identifier.
			 @param HTMLTextOptions [out] A buffer in which to return the
				text conversion options, a logical OR of
				\c #AIHTMLConversionOptions values.
			 @return True if the slice is marked to be converted to HTML text.
		*/
	AIAPI AIBoolean (*GetSliceIsHTMLText)(ASInt32 sliceID, long *HTMLTextOptions);

	/** Converts a slice to text.
			@param sliceID The unique slice identifier.
			@param options The text conversion options, a logical OR of
				\c #AIHTMLConversionOptions values.
			@param text [out] A buffer in which to return the text object.
				The call allocates and frees the text handle; you can
				resize it using  \c #AIPlatformMemorySuite::Resize().
		 */
	AIAPI AIErr (*GetSliceAsHTMLText)(ASInt32 sliceID, long options, ASHandle *text);

	/** Reports whether a slice is on a given layer.
		(Note that this function returns a boolean value, not an error code.)
			@param sliceID The unique slice identifier.
			@param layer The layer.
			 @return True if the slice is on the layer.
		*/
	AIAPI AIBoolean (*SliceIsOnLayer)(ASInt32 sliceID, AILayerHandle layer);

	/** Temporarily replaces the slice list with an empty slice list and the optimizations
		list with the settings of a specified slice.
			@param groupID The unique slice identifier.
			@param oldSliceList [out] A buffer in which to return an opaque references
				to the current full lists, to be passed to \c #RestoreSliceList(). */
	AIAPI AIErr (*ReplaceSliceList)(ASInt32 groupID, AISavedSliceListRef *oldSliceList);

	/**	Restores the slice list after a call to \c #ReplaceSliceList().
			@param oldSliceList The slice list to restore.
		*/
	AIAPI AIErr (*RestoreSliceList)(AISavedSliceListRef oldSliceList);

	/** Reports whether a slice is selected.
		(Note that this function returns a boolean value, not an error code.)
			@param sliceID The unique slice identifier.
			@return True if the slice is selected.
		*/
	AIAPI AIBoolean (*SliceIsSelected)(ASInt32 sliceID);

	/**	Retrieves all selected slices.
			@param sliceIDList [out] A buffer in which to return an array of unique
				slice identifiers.
			@param count [out] A buffer in which to return the number of entries in the array.
		*/
	AIAPI AIErr (*GetSelectedSliceList)(ASInt32 **sliceIDList, ASInt32 *count);

	/** Frees memory allocated for a slice list by \c #GetSelectedSliceList().
			@param sliceIDList The slice list.
		*/
	AIAPI AIErr (*ReleaseSelectedSliceList)(ASInt32 *sliceIDList);

	//	New in Illustrator 11

	/**	Duplicates all artwork in the current document that lies within a rectangle,
		and adds it to a specified art group.
			@param sliceBounds The bounding rectangle.
			@param outputGroup The group art object.
		 */
	AIAPI AIErr (*DuplicateArtWithinRect)( AIRealRect sliceBounds , AIArtHandle	outputGroup );

	/** Transfers the slicing attributes from one art object to another.
		Use with operations that create a new object that is intended replace the original and
		adopt its identity; for example, a conversion operation such as from a path to
		a gradient mesh. See also \c #AIArtSuite::TransferAttributes().
			@param srcart The source art object.
			@param dstart The destination art object.
		*/
	AIAPI AIErr (*TransferSliceAttributes)( AIArtHandle srcart, AIArtHandle dstart );

} AISlicingSuite;

/** @ingroup Suites

	This suite provides functions that allow you to access format-specific
	optimization settings and color table information, used for saving and placing images.

	A file format plug-in must use the functions \c #SetSliceOptimizationID(),
	\c #SetSliceOptimizationSettings(), and \c #SetSliceOptimizationSetting()
	to attach settings directly to a sliced art	object during a file place operation
	when the main optimization settings database is unavailable.
	After the Place command, optimization settings attached to the object are inserted into
	the main database.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIOptimizationSettingsSuite and \c #kAIOptimizationSettingsSuiteVersion.
	*/
typedef struct
{
	/** Gets the number of optimization settings groups in the settings-group list.
		Use with \c #GetIndexedOptimizationSettingsID() to iterate through settings groups.
		(Note that this function returns a numeric value, not an error code.)
			@return The number of settings groups.
		*/
	AIAPI ASInt32 (*GetOptimizationSettingsCount)(void);

	/** Retrieves an optimization settings group from the settings-group list, by position
		index. Use with \c #GetOptimizationSettingsCount() to iterate through settings groups.
		(Note that this function returns a numeric value, not an error code.)
			@param index The 0-based position index.
			@return The unique identifier of an optimization settings group.
		*/
	AIAPI ASInt32 (*GetIndexedOptimizationSettingsID)(ASInt32 index);

	/** Removes an optimization settings group from the settings-group list.
	 	(Note that this function does not return an error code.)
			@param optimizationID The unique identifier of the optimization settings group.
		*/
	AIAPI void (*DeleteOptimizationSettings)(ASInt32 optimizationID);

	/** Retrieves a unique identifier suitable for an optimization settings group.
		(Note that this function returns a numeric value, not an error code.)
			@return A unique identifier for an optimization settings group.
		*/
	AIAPI ASInt32 (*GetUniqueOptimizationSettingsID)(void);

	/** Reports whether a unique identifier is currently used
		to identify an optimization settings group.
		(Note that this function returns a boolean value, not an error code.)
			@param optimizationID The optimization settings group identifier.
			@return True if the identifier is in use.
		*/
	AIAPI AIBoolean (*OptimizationSettingsExists)(ASInt32 optimizationID);

	/** Sets the optimization settings for a settings group.
			@param optimizationID The optimization settings group identifier.
			@param settings The new settings structure.
		*/
	AIAPI AIErr (*SetOptimizationSettings)(ASInt32 optimizationID, ASOptimizationSettings *settings);

	/** Retrieves the optimization settings for a settings group.
			@param optimizationID The optimization settings group identifier.
			@param settings [out] A buffer in which to return the settings structure.
		*/
	AIAPI AIErr (*GetOptimizationSettings)(ASInt32 optimizationID, ASOptimizationSettings *settings);

	/** Sets a single optimization settings attribute.
			@param optimizationID The optimization settings group identifier.
			@param key The settings information attribute key.
			@param valueEntry The new attribute value.
		*/
	AIAPI AIErr (*SetOptimizationSetting)(ASInt32 optimizationID, const AIDictKey& key, AIEntryRef valueEntry);

	/** Retrieves a single optimization settings attribute.
			@param optimizationID The optimization settings group identifier.
			@param key The settings information attribute key.
			@param valueEntry [out] A buffer in which to return the attribute value.
		*/
	AIAPI AIErr (*GetOptimizationSetting)(ASInt32 optimizationID, const AIDictKey& key, AIEntryRef *valueEntry);

	/** Associates a slice with an optimization group settings identifier. A file format plug-in
		should use this before placing a sliced image, followed by \c #SetSliceOptimizationSettings().
			@param slice The slice identifier.
			@param optimizationID The optimization settings group identifier.
		*/
	AIAPI AIErr (*SetSliceOptimizationID)(ASInt32 sliceID, ASInt32 optimizationID);

	/** Sets the optimization settings for a slice. A file format plug-in should use this
		before placing a sliced image.
			@param sliceID The slice identifier.
			@param settings The new settings structure.
		*/
	AIAPI AIErr (*SetSliceOptimizationSettings)(ASInt32 sliceID, ASOptimizationSettings *settings);

	/** Sets a single optimization settings attribute for a slice. Use to supplement
		optimization information after it has been created with \c #SetSliceOptimizationSettings().
			@param sliceID The slice identifier.
			@param key The settings information attribute key.
			@param valueEntry The new attribute value.
		*/
	AIAPI AIErr (*SetSliceOptimizationSetting)(ASInt32 sliceID, const AIDictKey&key, AIEntryRef valueEntry);

	/** Retrieves a color table associated with an optimization settings group.
		You must always initialize the color table to 256 \c #ADMRGBColor entries.
			@param optimizationID The optimization settings group identifier.
			@param numColors [in, out] When \c colors is \c NULL, a buffer in which to return the number of entries
				needed for the \c colors array. For subsequent calls, pass in the number of entries
				in the \c colors array.
			@param colors [in, out] A buffer in which to return the color array. For the first call, pass \c NULL,
				to get the number of entries, then allocate an array and pass it to a second call to fill the array.
			@param exact [out] A buffer in which to return true if the color exactly matches the request.
		*/
	AIAPI AIErr (*GetColorTable)(ASInt32 optimizationID, ASInt32* numColors, ADMRGBColor* colors, ASBoolean* exact);

	/**	Sets the color table associated with an optimization settings group.
			@param optimizationID The optimization settings group identifier.
			@param numColors The number of entries in the \c colors array.
			@param colors The color array. You must always initialize the color table to 256 \c #ADMRGBColor entries.
			@param exact True to use exact color matching.
		*/
	AIAPI AIErr (*SetColorTable)(ASInt32 optimizationID, ASInt32 numColors, ADMRGBColor* colors, ASBoolean exact);

	/** Retrieves the locked colors in the color table associated with an optimization settings group.
		You must always initialize the color table to 256 \c #ADMRGBColor entries.
			@param optimizationID The optimization settings group identifier.
			@param numColors [in, out] When \c colors is \c NULL, a buffer in which to return the number of entries
				needed for the \c colors array. For subsequent calls, pass in the number of entries
				in the \c colors array.
			@param colors [in, out] A buffer in which to return the locked color array. For the first call, pass \c NULL,
				to get the number of entries, then allocate an array and pass it to a second call to fill the array.
		*/
	AIAPI AIErr (*GetLockedColors)(ASInt32 optimizationID, ASInt32* numColors, ADMRGBColor* colors);

	/**	Sets locked colors in the color table associated with an optimization settings group.
			@param optimizationID The optimization settings group identifier.
			@param numColors The number of entries in the \c colors array.
			@param colors The locked color array. You must always initialize the color table to 256 \c #ADMRGBColor entries.
		*/
	AIAPI AIErr (*SetLockedColors)(ASInt32 optimizationID, ASInt32 numColors, ADMRGBColor* colors);

	/** Retrieves the color shift information for the color table associated with an optimization settings group.
		You must always initialize the color table to 256 \c #ADMRGBColor entries.
		Color shifting allows you to map a range of colors to a single
		color, in order to reduce the overall number of colors
			@param optimizationID The optimization settings group identifier.
			@param numEntries [in, out] When \c entries is \c NULL, a buffer in which to return the number of entries
				needed for the \c colors array. For subsequent calls, pass in the number of entries
				in the \c colors array.
			@param entries [in, out] A buffer in which to return the array of color-shift entries. For the first call, pass \c NULL,
				to get the number of entries, then allocate an array and pass it to a second call to fill the array.
		*/
	AIAPI AIErr (*GetColorShiftEntries)(ASInt32 optimizationID, ASInt32* numEntries, ASColorShiftEntry *entries);

	/**	Sets color shift information for the color table associated with an optimization settings group.
		Color shifting allows you to map a range of colors to a single
		color, in order to reduce the overall number of colors
			@param optimizationID The optimization settings group identifier.
			@param numEntries The number of entries in the \c entries array.
			@param entries The array of color-shift entries. You must always initialize the color table to 256 \c #ADMRGBColor entries.
		*/
	AIAPI AIErr (*SetColorShiftEntries)(ASInt32 optimizationID, ASInt32 numEntries, ASColorShiftEntry *entries);

} AIOptimizationSettingsSuite;


#include "AIHeaderEnd.h"


#endif
