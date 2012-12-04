/*******************************************************************************
*
* ADMTypes.h -- ADM standard interface types
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
* Started by Dave Lazarony, 10 Mar 1996
*
********************************************************************************/

/** @file ADMTypes.h ADM standard interface types */

#ifndef __ADMTypes__
#define __ADMTypes__

#ifndef __ADMStandardTypes__
#include "ADMStandardTypes.h"
#endif

#ifndef __SPPlugs__
#include "SPPlugs.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// -----------------------------------------------------------------------------

#define kADMMaxTextLength 256

// -----------------------------------------------------------------------------
//	References to ADM types

/** Opaque reference to a dialog object. See \c #ADMDialogSuite10.  */
typedef struct _Opaque_ADMDialog* ADMDialogRef;
/** Opaque reference to a dialog/palette pane object. See \c #ADMDialogGroupSuite6.  */
typedef struct _Opaque_ADMPane* ADMPaneRef;
/** Opaque reference to a drawing object. See \c #ADMDrawerSuite6. */
typedef struct _Opaque_ADMDrawer* ADMDrawerRef;
/** Opaque reference to an item object. See \c #ADMItemSuite9 */
typedef struct _Opaque_ADMItem* ADMItemRef;
/** Opaque reference to a list object. See \c #ADMListSuite4 */
typedef struct _Opaque_ADMList* ADMListRef;
/** Opaque reference to a tree list object. See \c #ADMHierarchyListSuite5 */
typedef struct _Opaque_ADMHierarchyList* ADMHierarchyListRef;
/** Opaque reference to an entry object. See \c #ADMEntrySuite6 */
typedef struct _Opaque_ADMEntry* ADMEntryRef;
/** Opaque reference to a list entry object. See \c #ADMListEntrySuite4 */
typedef struct _Opaque_ADMListEntry* ADMListEntryRef;
/** Opaque reference to a notification object. See \c #ADMNotifierSuite2 */
typedef struct _Opaque_ADMNotifier* ADMNotifierRef;
/** Opaque reference to a tracker object. See \c #ADMTrackerSuite2 */
typedef struct _Opaque_ADMTracker* ADMTrackerRef;
/** Opaque reference to an icon object. See \c #ADMIconSuite2 */
typedef struct _Opaque_ADMIcon* ADMIconRef;
/** Opaque reference to an image object. See \c #ADMImageSuite2 */
typedef struct _Opaque_ADMImage* ADMImageRef;
/** Opaque reference to a radio group object. See \c #ADMRadioGroupSuite1 */
typedef struct _Opaque_ADMRadioGroup* ADMRadioGroupRef;

/** A developer-defined data object. See \c # */
typedef void* ADMUserData;

/** Opaque reference to a dialog timer object associated with a dialog, entry,
	list entry, or item.
	@see \c #ADMDialogSuite10::CreateTimer()
		<br>\c #ADMEntrySuite6::CreateTimer()
		<br>\c #ADMListEntrySuite4::CreateTimer()
		<br>\c #ADMItemSuite9::CreateTimer()*/
typedef struct _Opaque_ADMTimerRef* ADMTimerRef;

/** An event mask object associated with a dialog,
	item, list, or hierarchy list. See \c #ADMActionBitFlags.
	@see \c #ADMDialogSuite10::SetMask()
		<br>\c #ADMItemSuite9::SetMask()
		<br>\c #ADMListSuite4::SetMask()
		<br>\c #ADMHierarchyListSuite5::SetMask()	*/
typedef unsigned long ADMActionMask;

/** A character returned by a tracker. See \c #ADMTrackerSuite2 */
typedef unsigned short ADMChar;

/** A dialog resource object. See \c #ADMCustomResourceSuite3 */
typedef void* ADMRsrcInfo;

/** A plug-in object, for use with ADM. */
typedef SPPluginRef ADMPluginRef;


// -----------------------------------------------------------------------------
//

/** Measurement units within dialogs. The unit can be displayed automatically
	after the value for items with numeric values.
		@see \c #ADMItemSuite9::ShowUnits(), \c #ADMItemSuite9::SetUnits(),
		 \c #ADMBasicSuite10::ValueToString(), \c #ADMBasicSuite10::StringToValue(),

	You can create up to 10 application unit preferences, using the constants
	\c #kADMAppUnits1 to \c #kADMAppUnits10. Use \c #ADMBasicSuite10::SetAppUnits()
	to associate the numbered unit type with a normal unit type. Retrieve
	the associated unit type with \c #ADMBasicSuite10::SetAppUnits().
	*/
typedef enum
{

		// If you add new units, do not insert them into the list. Instead, add
		// them to the end of the "normal" units, and adjust kADMMaxNormalUnits.
		// (The actual values of these constants are used in STR# 4300, the
		// unit input strings, to associate units with input strings.)

	/** Does not display units, even if show-units is on. */
	kADMNoUnits = 0,
	/** Document points (1/72 inch) */
	kADMPointUnits = 1,
	/** Inches */
	kADMInchUnits = 2,
	/** Millimeters */
	kADMMillimeterUnits = 3,
	/** Centimeters */
	kADMCentimeterUnits = 4,
	/** Picas */
	kADMPicaUnits = 5,
	/** Percentage values */
	kADMPercentUnits = 6,
	/** Degrees  */
	kADMDegreeUnits = 7,
	/** Kyu units (Japanese linear measure, 0.25 mm)  */
	kADMQUnits = 8,
	/** Base 16 values, usually shown and entered as 0xHH  (H = hexadecimal digit) */
	kADMBase16Units = 9,
	/** Pixels  */
	kADMPixelUnits = 10,
	/** Time units, generally \c hours:minutes:seconds:frames */
	kADMTimeUnits = 11,
	/** Ha units (Japanese linear measure, 0.25 mm)  */
	kADMHaUnits = 12,
	/** Internal */
	kADMMinNormalUnits = kADMPointUnits,
	/** Internal */
	kADMMaxNormalUnits = kADMHaUnits,

	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits1 = 101,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits2 = 102,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits3 = 103,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits4 = 104,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits5 = 105,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits6 = 106,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits7 = 107,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits8 = 108,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits9 = 109,
	/** Developer-defined unit preference. See \c #ADMBasicSuite10::SetAppUnits() */
	kADMAppUnits10 = 110,

	/** Internal */
	kADMMaxAppUnits = kADMAppUnits10,
	/** Internal */
	kADMDummyUnits = 0xFFFFFFFF

}
ADMUnits;


// -----------------------------------------------------------------------------
//	Fonts

/** Font information for text in dialogs. */
typedef enum
{
	/** Default font. */
	kADMDefaultFont = 0,
	/** Basic font for modal dialogs. */
	kADMDialogFont,
	/** Basic font for floating dialogs. */
	kADMPaletteFont,
	/** Italic font for modal dialogs. */
	kADMItalicDialogFont,
	/** Italic font for floating dialogs. */
	kADMItalicPaletteFont,
	/** Bold font for modal dialogs. */
	kADMBoldDialogFont,
	/** Bold font for floating dialogs. */
	kADMBoldPaletteFont,
	/** Bold italic font for modal dialogs. */
	kADMBoldItalicDialogFont,
	/** Bold italic font for floating dialogs. */
	kADMBoldItalicPaletteFont,
	/** Fixed-width font for dialogs. */
	kADMFixedWidthFont,
	/** Italic fixed-width font for dialogs. */
	kADMItalicFixedWidthFont,
	/** Bold fixed-width font for dialogs. */
	kADMBoldFixedWidthFont,
	/** Bold italic fixed-width font for dialogs. */
	kADMBoldItalicFixedWidthFont,
	/** Font to match system tooltips. */
	kADMTooltipFont,
	/** Internal */
	kADMDummyFont = 0xFFFFFFFF
}
ADMFont;

#ifdef WIN_ENV

typedef void* ADMPlatformFontRef;
#endif

#ifdef MAC_ENV

/** Platform-specific (Mac OS only) font information for text in dialogs. */
typedef struct
{

	/** The Mac OS font number. */
	ADMInt32 textFont;			// font number
	/** The Mac OS style number. */
	ADMInt32 textStyle;
	/** The point size. */
	ADMInt32 textSize;

} ADMPlatformFontRef;

#endif


// -----------------------------------------------------------------------------
//	Justify

/** Justification constants for dialog elements. */
typedef enum
{
	/** Left justification. */
	kADMLeftJustify = 0,
	/** Center justification. */
	kADMCenterJustify = 1,
	/** Right justification. */
	kADMRightJustify = 2,
	/** Internal */
	kADMDummyJustify = 0xFFFFFFFF
}
ADMJustify;


// -----------------------------------------------------------------------------

/** Constant color values to be used for various dialog elements.
	The value of the constant specifies the actual RGB value,
	if the format is 0xRRGGBBFF. The lower 8 bits are always
	0xFF and can be ignored. The top 24 bits represent the
	amounts of red, green, and blue, where 0x00 is none, and
	0xFF is the maximum.
	  \li Black = 0x000000FF,
	  \li Red = 0xFF0000FF,
	  \li Green = 0x00FF00FF,
	  \li Blue = 0x0000FFFF,
	  \li White = 0xFFFFFFFF

  Use these constants in a drawing procedure, to make your modified
  or custom dialog elements consistent with other application dialogs.
  See \c #ADMDrawerSuite6::SetADMColor().
 */
typedef enum
{
	/** Black */
	kADMBlackColor = 0,
	/** White */
	kADMWhiteColor,
	/** Color that indicates highlighted graphics in dialog. */
	kADMHiliteColor,
	/** Color that indicates highlighted text in dialog  */
	kADMHiliteTextColor,
	/** Color for the light part of shadowed objects. */
	kADMLightColor,
	/** Color for dialog background. */
	kADMBackgroundColor,
	/** Color for the shadowed part of shadowed objects. */
	kADMShadowColor,
	/** Color that indicates a disabled control.  */
	kADMDisabledColor,
	/** Color for an unpressed button. */
	kADMButtonUpColor,
	/** Color for a pressed button. */
	kADMButtonDownColor,
	/** Color for the shadowed part of a pressed button. */
	kADMButtonDownShadowColor,
	/**  Color for a tooltip background. */
	kADMToolTipBackgroundColor,
	/** Color for the text of a tooltip.*/
	kADMToolTipForegroundColor,
	/** Color for window interiors. */
	kADMWindowColor,
	/** Color for dialog foreground. */
	kADMForegroundColor,
	/** Color for dialog text. */
	kADMTextColor,
	/** Red. */
	kADMRedColor,
	/** Obsolete, do not use. */
	kADMTabBackgroundColor,
	/** Obsolete, do not use. */
	kADMActiveTabColor,
	/** Obsolete, do not use. */
	kADMInactiveTabColor,
	/** Indicates an unspecified color. */
	kADMDummyColor = 0x000000FE,	// Probably ought to be renamed to kADMUnspecifiedColor
	/** Internal */
	kActuallyRGBWhiteButSpecifiedToForceEnumTo32Bits = 0xFFFFFFFF
}
ADMColor;


// -----------------------------------------------------------------------------

/** Creation flag for items of all types. */
enum
{
	/** Dialog item creation option: Override \c #kADMForceRomanFontForDialog
		dialog option for a particular item.
		@see \c #ADMItemSuite9::IgnoreForceRoman() */
	kADMIgnoreRomanFontForcing = (1L<<16)
};

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMTypes__
