#ifndef _AISVGACTION_H_
#define _AISVGACTION_H_

/*
 *        Name:	AISVGAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator SVG Action Parameters.
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

#ifndef _AICOREDOCUMENTACTION_H_
#include "AIDocumentAction.h"
#endif

// -----------------------------------------------------------------------------
//	Types.
// -----------------------------------------------------------------------------

/** The format for images within an SVG file.*/
typedef enum _AISVGImageFormats
{
	kAISVGFormatDefault  = 1,
	kAISVGFormatJPEG,
	kAISVGFormatGIF,
	kAISVGFormatPNG
} AISVGImageFormats;

/** The number of digits of precision after the decimal when rounding numbers. */
typedef enum _AISVGCoordinatePrecision
{
	kAISVGPrecision_1 = 1,
	kAISVGPrecision_2,
	kAISVGPrecision_3,
	kAISVGPrecision_4,
	kAISVGPrecision_5,
	kAISVGPrecision_6,
	kAISVGPrecision_7

} AISVGCoordinatePrecision;

/** The type of SVG rendering.  */
typedef enum _AISVGRendering
{
	kAISVGRenderingProgressive = 1,
	kAISVGRenderingBatched
} AISVGRendering;

/** How to subset fonts in the SVG. */
typedef enum _AISVGFontSubsetting
{
	kAISVGSubsettingNone = 1,
	kAISVGSubsettingGlyphsOnly,
	kAISVGSubsettingCommonEnglishOnly,
	kAISVGSubsettingGlyphsPlusEnglish,
	kAISVGSubsettingCommonRomanOnly,
	kAISVGSubsettingGlyphsPlusRoman,
	kAISVGSubsettingOutputEntireFont
} AISVGFontSubsetting;

/** Whether to embed fonts or create separate, linked files. */
typedef enum _AISVGFileLocation
{
	kAISVGLocationEmbed = 1,
	kAISVGLocationLink
} AISVGFileLocation;

/** The character set to use for the SVG file. */
typedef enum _AISVGDocumentEncoding
{
	/** ASCII */
	kAISVGISO8859Encoding = 1,
	/** UTF 8 */
	kAISVGUTF8Encoding,
	/** UTF 16 */
	kAISVGUTF16Encoding
} AISVGDocumentEncoding;

/** The compression to use for the SVG file. */
typedef enum _AISVGFileCompression
{
	kAISVGCompressionNone = 1,
	kAISVGCompressionGZIP

} AISVGFileCompression;

/** How style information should be exported. */
typedef enum _AISVGStyle
{
	kAISVGInLineStyle = 1,			// 'style' attributes on the SVG elements
	kAISVGEntityStyle,				// 'style' attributes that contain entity references
	kAISVGCSSStyle,					// 'class' attributes with corresponding CSS styles
	kAISVGPresentationAttrsStyle	// presentation attributes on the SVG elements
} AISVGStyle;

/** Units to use for dimensions and positions */
typedef enum _AISVGUnits
{
	kAISVGUnitCentimeters = 0,
	kAISVGUnitEms,
	kAISVGUnitInches,
	kAISVGUnitPicas,
	kAISVGUnitPixels,
	kAISVGUnitPoints,
	kAISVGUnitMillimeters
} AISVGUnits;

/** The resolution measurement unit. */
typedef enum _AISVGResolution
{
	kAISVGPixelsPerInch = 0,
	kAISVGPixelsPerCentimeter
} AISVGResolution;

/** What types of fonts to embed. */
typedef enum _AISVGEmbedFontFormats
{
	kAISVGEmbedFontTrueType = 0,
	kAISVGEmbedFontType1 ,
	kAISVGEmbedFontBoth
} AISVGEmbedFontFormats;

/** Whether images are embedded or saved as separate files. */
typedef enum _AISVGRasterLocation
{
	kAISVGImageEmbed = 1,
	kAISVGImagelink
} AISVGRasterLocation;

//** The SVG DTD type. */
typedef enum _AISVGDTD
{
	kAISVGDTD10 = -1,
	kAISVGDTD11,
	kAISVGDTDTiny11,
	kAISVGDTDTiny11Plus,
	kAISVGDTDBasic11,
	kAISVGDTDTiny12
} AISVGDTD;

/** What type of font to use. */
typedef enum _AISVGFontType
{
	kAISVGFontCEF = 0,
	kAISVGFontSVG,
	kAISVGFontOutline
} AISVGFontType;

/** How to treat text in paths. */
typedef enum _AISVGTextOnPath
{
	kAISVGTextOnPathSVG = 0,
	kAISVGTextOnPathIllustrator
} AISVGTextOnPath;

/** Rectangle, defined by upper left corner point, width and height */
typedef struct _AISVGRect
{
	float x;
	float y;
	float width;
	float height;
} AISVGRect;


// -----------------------------------------------------------------------------
// The following parameters can be specified when saving to SVG. To save a file
// as SVG issue an export action (kAISaveDocumentAsAction). Specify one of the
// formats and extensions below for the format key.
// -----------------------------------------------------------------------------

/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentFormatKey The format to write, \c #kAISVGFileFormat
			to export an uncompressed SVG file. */
#define  kAISVGFileFormat								"svg file format"
/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentExtensionKey The file extension,
			\c #kAISVGFileFormatExtension for uncompressed SVG.	*/
#define kAISVGFileFormatExtension						"svg"

/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentFormatKey The format to write, \c #kAISVGCompressedFileFormat
			to export a compressed SVG file. */
#define kAISVGCompressedFileFormat						"svg compressed file format"
/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentExtensionKey The file extension,
			\c #kAISVGCompressedFileFormatExtension for compressed SVG.	*/
#define kAISVGCompressedFileFormatExtension				"svgz"

// Standard SVG Options
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The format for images in the SVG, an \c #AISVGImageFormats value */
const ActionParamKeyID kAISVGImageFormatKey				= 'iFmt'; // enum AIImageFormats
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The precision for number rounding, an \c #AISVGCoordinatePrecision value */
const ActionParamKeyID kAISVGPrecisionKey				= 'Prcs'; // enum AISVGCoordinatePrecision
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The type of SVG rendering, an \c #AISVGRendering value */
const ActionParamKeyID kAISVGRenderingKey				= 'Rndr'; // enum AISVGRendering
/** Parameter to \c #kAIExportDocumentAction for SVG. True to zoom. */
const ActionParamKeyID kAISVGZoomKey					= 'ZooM'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG. True to use the system font. */
const ActionParamKeyID kAISVGSystemFontKey				= 'SYFt'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to subset fonts, an \c #AISVGFontSubsetting value */
const ActionParamKeyID kAISVGFontSubsettingKey			= 'FSbs'; // enum AISVGFontSubsetting
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to embed fonts or create separate, linked files, an \c #AISVGFileLocation value */
const ActionParamKeyID kAISVGFontLocationKey			= 'FLct'; // enum AISVGFileLocation
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The character encoding, an \c #AISVGDocumentEncoding value */
const ActionParamKeyID kAISVGEncodingKey				= 'Encd'; // enum AISVGDocumentEncoding
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The file compression, an \c #AISVGFileCompression value */
const ActionParamKeyID kAISVGCompressionKey				= 'Cmzn'; // enum AISVGFileCompression
/** Parameter to \c #kAIExportDocumentAction for SVG.
	How style information should be exported, an \c #AISVGStyle value */
const ActionParamKeyID kAISVGStyleTypeKey				= 'StTp'; // enum AISVGStyle
/** Parameter to \c #kAIExportDocumentAction for SVG.
	What type of fonts to use, an \c #AISVGFontType value  */
const ActionParamKeyID kAISVGFontFormatKey				= 'fFmt'; // enum AIImageFormats



// Illustrator-specific SVG Options

/** Parameter to \c #kAIExportDocumentAction for SVG.
	Width unit, an \c #AISVGUnits value */
const ActionParamKeyID kAISVGWidthUnitKey				= 'WunT'; // enum AISVGUnits
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Height unit, an \c #AISVGUnits value */
const ActionParamKeyID kAISVGHeightUnitKey				= 'HunT'; // enum AISVGUnits
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Resolution unit, an \c #AISVGResolution value */
const ActionParamKeyID kAISVGResolutionUnitKey			= 'RzUt'; // enum AISVGResolution
/** Parameter to \c #kAIExportDocumentAction for SVG.
	What types of fonts to embed, an \c #AISVGEmbedFontFormats value */
const ActionParamKeyID kAISVGEmbedFontFormatsKey		= 'EFFt'; // enum AISVGEmbedFontFormats
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to embed or link images, an \c #AISVGRasterLocation value */
const ActionParamKeyID kAISVGEmbedRasterLocationKey		= 'RLoc'; // enum AISVGRasterLocation
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Resolution for images (in the unit specified by \c #kAISVGResolutionUnitKey) */
const ActionParamKeyID kAISVGRasterResolutionKey		= 'RsRl'; // integer
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Gradient tolerance. */
const ActionParamKeyID kAISVGGradientTolerenceKey		= 'GrTl'; // real
/** Parameter to \c #kAIExportDocumentAction for SVG.
	How to treat text in paths, an \c #AISVGTextOnPath value */
const ActionParamKeyID kAISVGTextOnPathKey				= 'ToPt'; // enum AISVGTextOnPath
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to use anti-aliasing. */
const ActionParamKeyID kAISVGAntiAliasKey				= 'AAlz'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to export hidden objects. */
const ActionParamKeyID kAISVGExportHiddenObjectKey		= 'HoBj'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to export the title layer as the title.*/
const ActionParamKeyID kAISVGExportLayerAsTitleKey		= 'LasT'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to export a key */
const ActionParamKeyID kAISVGExportAlsoExportKey		= 'Aexp'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to constrain proportions. */
const ActionParamKeyID kAISVGExportConstrainProportionsKey = 'Cstp'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to clip to the artboard. */
const ActionParamKeyID kAISVGExportClipToArtboardKey	= 'CTab'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to round-trip. */
const ActionParamKeyID kAISVGExportRoundTripKey			= 'Rrtr'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include the Adobe namespace. */
const ActionParamKeyID kAISVGIncludeAdobeNameSpaceKey	= 'Anxp'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include a template. */
const ActionParamKeyID kAISVGIncludeTemplateKey			= 'Temt'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The rectangle to use as the viewing box, an \c #AISVGRect. */
const ActionParamKeyID kAISVGViewBoxKey					= 'VieW'; // data AISVGRect
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include round-trip data.   */
const ActionParamKeyID kAISVGIncludePGFKey				= 'Ipgf'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include XMP metadata.  */
const ActionParamKeyID kAISVGIncludeXAPKey				= 'IXAP'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include slicing information.  */
const ActionParamKeyID kAISVGIncludeSlicesKey			= 'ISlc'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The SVG DTD to use, an \c #AISVGDTD value */
const ActionParamKeyID kAISVGDTDKey						= 'DTDt'; // enum AISVGDTD
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The font type to use, an \c #AISVGFontType value. */
const ActionParamKeyID kAISVGFontTypeKey				= 'FTKt'; // enum AISVGFontType
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include automatic kerning data.  */
const ActionParamKeyID kAISVGDisbleAutoKerningKey		= 'IDAK'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to SVG Text On Path, false to write each character separately.  */
const ActionParamKeyID kAISVGUseSVGTextOnPathKey		= 'ITOP'; // bool

#endif
