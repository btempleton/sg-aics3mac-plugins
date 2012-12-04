#ifndef __AIPreferenceKeys__
#define __AIPreferenceKeys__

/*
 *        Name:	AIPreferenceKeys.h
 *     Purpose:	To define shared preference keys, defaults, and other
 *              relevant information.
 *       Notes: When sharing preferences between plugins and the main app,
 *              either a) use a null prefix, or b) access the preferences from
 *              the main app via the AIPreference suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/** Preference prefix: Use low-resolution proxy for linked EPS files  */
const unsigned kUseLowResProxyPrefix= 0;
/** Preference suffix: Use low-resolution proxy for linked EPS files  */
#define kUseLowResProxySuffix ((const char *)"useLowResProxy")
/** Preference default: Use low-resolution proxy for linked EPS files  */
const bool kUseLowResProxyDefault= true;

/** Preference prefix: EPS rasterization resolution for linked EPS/DCS files */
const unsigned kEPSResolutionPrefix = 0;
/** Preference suffix: EPS rasterization resolution for linked EPS/DCS files */
#define kEPSResolutionSuffix	((const char *)"EPSResolution")
/** Preference default: EPS rasterization resolution for linked EPS/DCS files */
const long kEPSResolutionDefault = 300L;

/** Preference prefix: Update linked file options */
#define kFileClipboardPrefix ((const char *)"FileClipboard")
/** Preference suffix: Update linked file options */
#define kLinkOptionsSuffix ((const char *)"linkoptions")
/** Preference options: Update linked file options */
enum UpdateLinkOptions {AUTO, MANUAL, ASKWHENMODIFIED};
/** Preference default: Update linked file options */
const UpdateLinkOptions kLinkOptionsDefault= ASKWHENMODIFIED;

/** Preference prefix: Enable OPI feature for linked EPS files */
const unsigned kEnableOPIPrefix = 0;
/** Preference suffix: Enable OPI feature for linked EPS files */
#define kEnableOPISuffix	((const char *)"enableOPI")
/** Preference default: Enable OPI feature for linked EPS files */
const bool kEnableOPIDefault = false;

/** Preference suffix: Clipboard, copy as PDF*/
#define kcopyAsPDFSuffix		"copyAsPDF"
/** Preference suffix: Clipboard, copy as Illustrator clipboard */
#define kcopyAsAICBSuffix		"copyAsAICB"
/** Preference suffix: Clipboard, append extension */
#define kappendExtensionSuffix	"appendExtension"
/** Preference suffix: Clipboard, lowercase */
#define klowerCaseSuffix		"lowerCase"
/** Preference suffix: Clipboard, flatten */
#define kflattenSuffix			"flatten"
/** Preference suffix: Clipboard options */
#define kAICBOptionSuffix	    "AICBOption"

/** Preferences: Illustrator clipboard option values */
enum  AICBOptions {PRESERVE_PATH, PRESERVE_APPEARANCE_OVERPRINT};
/** Preference default:Clipboard options */
const AICBOptions kAICBOptionsDefault= PRESERVE_APPEARANCE_OVERPRINT;

/** @ingroup PreferenceKeys
	Version Cue preference */
#define kUseVersionCue			"useVersionCue"

/** @ingroup PreferenceKeys
	Whether screen display uses a black preserving color transformation
	for converting CMYK to RGB or gray. The black preserving transform maps CMYK
	0,0,0,1 to the darkest black available. Not colorimetrically accurate
	but sometimes preferable for viewing CMYK black line art and text. The
	default value is given by \c #kAIPrefDefaultOnscreenBlackPres. */
#define kAIPrefKeyOnscreenBlackPres			((const char*) "blackPreservation/Onscreen")
/** @ingroup PreferenceKeys
	Default value for \c #kAIPrefKeyOnscreenBlackPres. */
#define kAIPrefDefaultOnscreenBlackPres		true

/** @ingroup PreferenceKeys
	Whether printing and export uses a black preserving color transformation
	for converting CMYK to RGB or gray. The black preserving transform maps CMYK
	0,0,0,1 to the darkest black available. Not colorimetrically accurate
	but sometimes preferable for viewing CMYK black line art and text. The
	default value is given by \c #kAIPrefDefaultExportBlackPres. */
#define kAIPrefKeyExportBlackPres			((const char*) "blackPreservation/Export")
/** @ingroup PreferenceKeys
	Default value for \c #kAIPrefKeyExportBlackPres. */
#define kAIPrefDefaultExportBlackPres		true

/** @ingroup PreferenceKeys
	Sets the guide style (solid or dashed).
	The default value is given by \c #kAIPrefDefaultGuideStyle.  */
#define kAIPrefKeyGuideStyle ((const char*)"Guide/Style")
/** @ingroup PreferenceKeys
	The \c #kAIPrefKeyGuideStyle value for solid guides. */
#define kAIPrefGuideStyleSolid 0
/** @ingroup PreferenceKeys
	The \c #kAIPrefKeyGuideStyle value for dashed guides. */
#define kAIPrefGuideStyleDashed 1
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideStyle. */
#define kAIPrefDefaultGuideStyle kAIPrefGuideStyleSolid

/** @ingroup PreferenceKeys
	Sets the red component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorRed.  */
#define kAIPrefKeyGuideColorRed ((const char*)"Guide/Color/red")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorRed. */
#define kAIPrefDefaultGuideColorRed		(0x4A3D/65535.0f)

/** @ingroup PreferenceKeys
	Sets the green component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorGreen.  */
#define kAIPrefKeyGuideColorGreen ((const char*)"Guide/Color/green")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorGreen. */
#define kAIPrefDefaultGuideColorGreen		(1.0f)

/** @ingroup PreferenceKeys
	Sets the blue component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorBlue.  */
#define kAIPrefKeyGuideColorBlue ((const char*)"Guide/Color/blue")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorBlue. */
#define kAIPrefDefaultGuideColorBlue		(1.0f)

/** @ingroup PreferenceKeys
	Sets the greeking threshold for text drawing. Text rendered at a point size less than 
	or equal to the greeking threshold is rendered greeked.
	The default value is given by \c #kAIPrefDefaultTextGreekingThreshold.  */
#define kAIPrefKeyTextGreekingThreshold ((const char*)"text/greekingThreshold")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyTextGreekingThreshold. */
#define kAIPrefDefaultTextGreekingThreshold		(6.0f)

/** @ingroup PreferenceKeys
	Sets the legacy gradient-mesh object conversion options when opening a legacy
	document (from an Illustrator version before CS 3). */
#define kAIPrefKeyLegacyGradientMeshConversionOptions ((const char*) "open/legacyGradientMeshConversion")
/** @ingroup PreferenceKeys
	Key values for \c #kAIPrefKeyLegacyGradientMeshConversionOptions. */
enum  LegacyGradientMeshConversionOptions {MESH_UNKNOWN, MESH_PRESERVE_SPOT, MESH_PRESERVE_APPEARANCE};

/** @ingroup PreferenceKeys
	Sets the tolerance preference for selection. Integer, a number of pixels. */
#define kAIPrefKeySelectionTolerance ((const char*) "selectionTolerance")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeySelectionTolerance. */
#define  kAIPrefDefaultSelectionTolerance (3)

#endif
