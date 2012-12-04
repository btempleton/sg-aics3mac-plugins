#ifndef __AIPaintStyle__
#define __AIPaintStyle__

/*
 *        Name:	AIPaintStyle.h
 *      Author:	Dave Lazarony
 *        Date:	6/17/96
 *     Purpose:	AI Paint Style Suite.
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
#ifndef __ADMItem__
#include "ADMItem.h"
#endif

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIPaintStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPaintStyleSuite			"AI Paint Style Suite"
#define kAIPaintStyleSuiteVersion7	AIAPI_VERSION(7)
#define kAIPaintStyleSuiteVersion	kAIPaintStyleSuiteVersion7

/** @ingroup Notifiers
    The eyedropper sends this while tracking a mouse drag, to notify the Color palette
    to update its proxies during the drag, using the path style and map
	in the \c #AIUpdatePathStyleNotifyData. See \c #AIPaintStyleSuite */
#define kAIUpdatePathStyleNotifier					"AI Update PathStyle Notifier"
/** @ingroup Notifiers
	See \c #AIPaintStyleSuite */
#define kAIPaintStyleFillStrokeChangedNotifier		"AI Paint Style Fill Stroke Changed Notifier"
/** @ingroup Notifiers
	See \c #AIPaintStyleSuite */
#define kAIPaintStyleGradientStopChangedNotifier	"AI Paint Style Gradient Stop Changed Notifier"

/** @ingroup Selectors
	Used by the Control palette to set stroke width with \c #AIStrokeWidthMessage.
	If there is no stroke currently applied, and a non-zero stroke width
	is set through this selector, the previously applied stroke color is restored.
	*/
#define kAIPaintStyleSetStrokeWidthSelector			"AI Paint Style Set Stroke Width Selector"

/** The new stroke width for a \c #kAIPaintStyleSetStrokeWidthSelector */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** The stroke width in points. */
	float newStrokeWidth;
} AIStrokeWidthMessage;

/** Indicator type for ADM.	 */
#define kAIPaintStyleIndicatorType					"AI Paint Style Indicator Type"
/** Indicator type for ADM.	 */
#define kAIPaintStyleIndicatorSmallType				"AI Paint Style Indicator Small Type"

/** Color editor type for ADM.	 */
#define kAIPaintStyleColorEditorType				"AI Paint Style Color Editor Type"

/** Minimum dash stroke length. */
#define kMinStrokeDashLength		0.01


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Data for \c #kAIUpdatePathStyleNotifier */
typedef struct
{
	/** Path style to update. */
	AIPathStyle	pathStyle;
	/** Path style map. The map indicates which fields of an \c #AIPathStyle
		are specified by a partial style. A path style can contain unknown or mixed
		attributes, which are indicated by a value of false for that attribute in the map. */
	AIPathStyleMap pathStyleMap;
} AIUpdatePathStyleNotifyData;


/** Colorspaces that can be displayed by the Color palette for editing colors. */
typedef enum
{
	kUnknownSpace = 0,
	kGrayscaleSpace,
	kRGBSpace,
	kHSVSpace,
	kCMYKSpace,
	kWebSpace,
	kTintSpace,
	kLabSpace
} ColorSpace;


/** Behavior options for Color Editor. See  \c #AIPaintStyleSuite. */
typedef struct
{
	/** When true, colors are converted to the document color space for
		display in the color indicator. This gamut limits them to the
		document color space. Default is true. */
	AIBoolean showSampleInDocCs;

	/** When true, Lab is allowed as a color model in the Color Editor.
		Default is false. */
	AIBoolean allowLabColorModel;
 
	/** When true, a square representing the current color is drawn to
	    the left of the color sliders. When false, the color indicator
  		is hidden. Default is true. */
  	AIBoolean showColorIndicator;
	/** When true, the web-safe and gamut indicators are drawn to the right of the color sliders.
	When false, they are drawn to the left of the color sliders. Default is false. */
	AIBoolean warningIndicatorsOnRight;

	/** When true, global objects are verified against the current document's swatch list
		before they are displayed. When false, they are assumed to be valid. Default is true.

		\li A Color Editor installed in a palette should always set this to true, because colors can
			become invalid asynchronously with palette updates.

		\li A Color Editor in a modal dialog may wish to set this to false,
			especially if it allows modification of tints on \c #AIColor values
		from swatch libraries that have not yet been targeted to the current document.
	*/
	AIBoolean verifyColors;
} AIColorEditorOptions;

/** Behavior options for opening the Color Picker using
	\c #AIPaintStyleSuite::DisplayColorPickerWithOptions(). */
typedef struct
{
	/** The swatch list to display in the swatch-list view of
		the Color Picker. When \c NULL, the current document's
		swatch list is used. 

		When the Color Picker is displayed, the  swatch-list view
		is shown if the initial color exactly matches the color
		from a swatch in this list.
	*/
	AISwatchListRef		swatchList;

} AIColorPickerOptions;

/** Possible colorspaces for specifying colors for a Color Editor */
typedef enum
{
	kAIColorEditorColorUnknown = 0,
	kAIColorEditorColorGray,
	kAIColorEditorColorRGB,
	kAIColorEditorColorCMYK,
	kAIColorEditorColorLab,
	/** Internal */
	kAIColorEditorColorDummy = 0xFFFFFFFF
} AIColorEditorColorSpace;

/** Color specification for the Color Editor */
typedef struct
{
	/** The colorspace */
	AIColorEditorColorSpace space;
	/** The color values. Which array members have values, and what
		they mean, depends on the colorspace. */
	AIReal values[4];
	/** Each member of this array that is true corresponds to a
		member of the \c values array with a meaningful value. */
	AIBoolean defined[4];
} AIColorEditorColor;

/** Color Editor read-only flag. See \c #AIPaintStyleSuite::SetColorEditorReadOnly(). */
typedef enum
{
	kAIColorEditorReadOnlyDefault = 0
} AIColorEditorReadOnlyOption;

// New for AI13:

/** Developer-defined data to pass to your color-editor
	tracking procedure.
	@see \c #ColorEditorTrackProc, \c #AIPaintStyleSuite::SetColorEditorTrackProc()
*/
typedef void* ColorEditorClientData;

/** Prototype for an event tracking procedure associated with a color-editor
	dialog item. Called when the user makes any change in the editor.
	Use it to update other UI features according to the current
	Color Editor state. If supplied, it must not modify the state
	of the Color Editor itself.
 		@param clientData Developer-defined data passed with the event.
 		@return Nothing.
		@see \c #AIPaintStyleSuite::SetColorEditorTrackProc()
	*/
typedef void (*ColorEditorTrackProc)(ColorEditorClientData clientData);




/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to examine and operate on the Color and Gradient
	palettes, which display and modify the paint style of the current selection,
	and the Color Editor, which allows a user to choose and edit colors.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPaintStyleSuite and \c #kAIPaintStyleSuiteVersion.
 */
typedef struct
{
	/** Causes the Color palette to show the stroke color (not fill).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetStrokeActive)();

	/** Reports whether the Color palette shows the stroke color (not fill).
		(Note that this function returns a boolean value, not an error code.)
			@return True if stroke is active.
		*/
	ASBoolean ASAPI (*IsStrokeActive)();

	/** Causes the Color palette to show the fill color (not stroke).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetFillActive)();

	/** Reports whether the Color palette shows the fill color (not stroke).
		(Note that this function returns a boolean value, not an error code.)
			@return True if fill is active.
		*/
	ASBoolean ASAPI (*IsFillActive)();

	/** Sets the fill and stroke states of the current selection to those
		of the default style (usually white for fill and solid
		1-point black for stroke).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetDefaultFillStroke)();

	/** Retrieves the index position of the selected stop the current gradient.
		(Note that this function returns a numeric value, not an error code.)
			@return The 0-based position index, or -1 if a gradient stop is not
				currently being edited.
		*/
	int ASAPI (*GetActiveGradientStopIndex)();

	/** Retrieves the gradient currently shown in the Gradient palette.
			@param color [out] A buffer in which to return the gradient.
		*/
	ASErr ASAPI (*GetCurrentGradient)(AIColor *color);

	/** Retrieves the fill, stroke, or currently active gradient stop
		color currently shown in the Color palette.
			@param color [out] A buffer in which to return the color.
		*/
	ASErr ASAPI (*GetCurrentColor)(AIColor *color);

	/** Invokes the Gradient palette. */
	ASErr ASAPI (*ShowGradientDialog)();

	/** Invokes the Color palette. */
	ASErr ASAPI (*ShowColorDialog)();

	/** If caching is not active, applies a color to the selection, or to the
		active gradient stop.

		If caching is active--that is, between a call to \c #BeginActiveColor()
		and a call to \c #EndActiveColor() --applies the color to proxies (such as the
		color previews in the Tools palette) rather than to the selection or gradient stop.
		(The eyedropper tool uses this during mouse-drag.)
			@param color The new color.
			@param useGradientStop True to replace the color in the
				currently active gradient stop only, false to replace the color
				in the entire selection.
		*/
	ASErr ASAPI (*SetActiveColor)(AIColor *color, ASBoolean useGradientStop);

	/** Starts caching for color application to proxies.
		@see \c #SetActiveColor(), \c #SetAIColor() */
	ASErr ASAPI (*BeginActiveColor)();

	/** Finishes caching for color application to proxies.
		@see \c #SetActiveColor(), \c #SetAIColor() */
	ASErr ASAPI (*EndActiveColor)();

	/** Reports whether the current color in the Color palette is for a stroke or fill.
		(Note that this function returns a boolean value, not an error code.)
			@return True if the color is for a stroke, false if it is for a fill.
		*/
	ASBoolean ASAPI (*IsCurrentColorStroke)();

	/** If caching is not active, applies a stroke or fill color to the current selection,
		using a partial color specification.

		If caching is active--that is, between a call to \c #BeginActiveColor()
 		and a call to \c #EndActiveColor() --applies the color to proxies (such as the
		color previews in the Tools palette) rather than to the selection.
			@param color The color structure containing new color component values.
			@param colorMap A color map that specifies which members of the color structure
				contain valid values.
			@param isStroke True to set the current stroke color, false to set the fill color.
		*/
	ASErr ASAPI (*SetAIColor)(AIColor *color, AIColorMap *colorMap, ASBoolean isStroke);

	/**	Shows a gradient in the Gradient palette.
			@param color The gradient.
		*/
	ASErr ASAPI (*SetCurrentGradient)(AIColor *color);

	/**	Shows a color in the Color palette.
			@param color The color.
		*/
	ASErr ASAPI (*SetCurrentColor)(AIColor *color);

	/** Shows the Color palette if it is hidden, hides the Color palette if it is shown.
		*/
	ASErr ASAPI (*ToggleColorDialog)();

	/** Sets the color displayed by a Color Editor control, using a partial color specification.
			@param colorEditor The color editor control object.
			@param color The color structure containing new color component values.
			@param colorMap A color map that specifies which members of the color structure
				contain valid values.
			@see \c #SetColorEditorColor()
		*/
	ASErr ASAPI (*SetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);

	/** Retrieves the color displayed by a Color Editor control, as an
		\c #AIColor and \c #AIColorMap specification.
			@param colorEditor The color editor control object.
			@param color [out] A buffer in which to return the full or partial color.
			@param colorMap [out] A buffer in which to return the color map that specified which
				fields in the returned partial color are valid.
			@see \c #GetColorEditorColor()
	*/
	ASErr ASAPI (*GetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);

	/** Sets the current colorspace of a Color Editor control.
			@param colorEditor The color editor control object.
			@param space The new colorspace.
		*/
	ASErr ASAPI (*SetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace space);

	/** Retrieves the current colorspace of a Color Editor control.
			@param colorEditor The color editor control object.
			@param space [out] A buffer in which to return the colorspace.
		*/
	ASErr ASAPI (*GetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace *space);

	/** Sets options that affect the behavior of a Color Editor control group.
			@param colorEditor The color editor control object.
			@param options The new options structure.
		*/
	ASErr ASAPI (*SetColorEditorOptions)(ADMItemRef colorEditor, const AIColorEditorOptions& options);

	/** Retrieves the current options for a Color Editor control group.
			@param colorEditor The color editor control object.
			@param options [out] A buffer in which to return the options structure.
		*/
	ASErr ASAPI (*GetColorEditorOptions)(ADMItemRef colorEditor, AIColorEditorOptions& options);

	/** Exchanges the fill and stroke colors for the current selection.
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SwapFillStroke)();

	/** Invokes the color-chooser dialog and reports the chosen color.
		(Note that this function returns a boolean value, not an error code.)
		@param currentColor specifies the initial color the picker will display.
		When the function returns currentColor will become the color the user picked.
			@return True if the user clicked OK, false of the user clicked Cancel. */
	ASBoolean ASAPI (*DisplayColorPicker)(AIColor *currentColor);

	/** Sets the color displayed by a Color Editor control, using an
		\c #AIColorEditorColor specification.
			@param colorEditor The color editor control object.
			@param color The new color.
			@see \c #SetColorEditorAIColor()
		*/
	ASErr ASAPI (*SetColorEditorColor)(ADMItemRef colorEditor, AIColorEditorColor *color);

	/** Retrieves the color displayed by a Color Editor control, as an
		\c #AIColorEditorColor specification.
			@param colorEditor The color editor control object.
			@param color [out] A buffer in which to return the color.
			@see \c #GetColorEditorAIColor()
		*/
	ASErr ASAPI (*GetColorEditorColor)(ADMItemRef colorEditor, AIColorEditorColor *color);

	/** Turns read-only mode on or off for the Color Editor. In read-only mode
		the editor displays the color and its values but does not allow it to
		be modified.
			@param colorEditor The color editor control object.
			@param readOnly True to turn read-only mode on, false to turn it off.
			@param options Additional options that control what is shown in read-only mode,
				an \c #AIColorEditorReadOnlyOption value.
		*/
	ASErr ASAPI (*SetColorEditorReadOnly)(ADMItemRef colorEditor, ASBoolean readOnly, ASInt32 options);


	// New for AI13
	/** Creates a color-editor ADM dialog item in an ADM dialog. See \c #ADMDialogSuite10.
		(Replaces the previous mechanism, which used a platform resource of type
		 \c #kAIPaintStyleColorEditorType.)

			@param dialog The dialog window.
			@param itemID Unique identifier of the ADM dialog item; see \c #ADMItemSuite9::Create().
			@param boundsRect The bounding box of the new item, in pixel coordinates
				relative to the dialog, whose origin is the top left corner.
			@param colorEditor [out] A buffer in which to return the ADM dialog item object.
		*/
	ASErr ASAPI (*CreateColorEditor)(ADMDialogRef dialog, int itemID, const ADMRect &boundsRect, ADMItemRef *colorEditor );

	/** Calls a developer-defined callback function when the value of a color editor
	 	slider changes during mouse-moved-down events.
			@param colorEditor The Color Editor object, as returned from \c #CreateColorEditor().
			@param trackProc Optional. A callback function that you can use to update other
				UI features according to the current Color Editor state. If supplied,
				it must not modify the state of the Color Editor itself. Can be \c NULL
			@param clientData Optional. Developer-defined data to pass through to the
				callback function. Can be \c NULL.
		*/
	ASErr ASAPI (*SetColorEditorTrackProc)( ADMItemRef colorEditor, ColorEditorTrackProc trackProc, ColorEditorClientData clientData );

	/** Shows or hides the color editor. The color editor is shown by default after creation.
			@param colorEditor The Color Editor object, as returned from \c #CreateColorEditor().
			@param show True to show the color editor, false to hide it.
	*/
	ASErr ASAPI (*ShowColorEditor)( ADMItemRef colorEditor, AIBoolean show );


	/** Invokes the Color Picker dialog with options and reports the chosen color.
		(Note that this function returns a boolean value, not an error code.)
			@param currentColor [in/out] On input, the initial color to display.
				On output, the color the user selected.
			@param options Options for initial display. The Color Picker opens in
				the swatch-list view if the initial color exactly matches the color
				in a swatch from the \c #AIColorPickerOptions::swatchList.
			@return True if the user clicked OK in the Color Picker, false if the user clicked Cancel.
		*/
	ASBoolean ASAPI (*DisplayColorPickerWithOptions)(AIColor *currentColor, const AIColorPickerOptions &options );

} AIPaintStyleSuite;


#include "AIHeaderEnd.h"

#endif
