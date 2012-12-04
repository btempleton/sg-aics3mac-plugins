#ifndef __AI120PaintStyle__
#define __AI120PaintStyle__

/*
 *        Name:	AI120PaintStyle.h
 *   $Revision: 17 $
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
#include "AIPaintStyle.h"

#include "AIHeaderBegin.h"

/** @file AI120PaintStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

// AI120PaintStyle Suite
#define kAI120PaintStyleSuite			"AI Paint Style Suite"
#define kAIPaintStyleSuiteVersion6		AIAPI_VERSION(6)
#define kAI120PaintStyleSuiteVersion	kAIPaintStyleSuiteVersion6

/*******************************************************************************
**
**	Types
**
**/

/** Behavior options for Color Editor. See
\c #AIPaintStyleSuite. */
typedef struct
{
	/** When true, colors are converted to the document color space for
	display in the color indicator. This gamut limits them to the
	document color space. Default is true. */
	AIBoolean showSampleInDocCs;
	/** When true, Lab is allowed as a color model in the Color Editor.
	Default is false. */
	AIBoolean allowLabColorModel;

} AI120ColorEditorOptions;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The paint style suite provides APIs for interacting with the palettes that display
and modify the paint style of the current selection. These include the color
palette and the gradient palette.

It also contains APIs for interacting with color editors. A color editor is the
set of controls that allow entry of a color. They consist of a popup menu for
selecting the color model, the sliders and edit boxes for the color values, the
proxy for the current color and the in gamut and web safe color selectors. A
color editor is instantiated by putting a special control type into a dialog
resource. Instantiating the dialog then instantiates the color editor. The APIs
in the AIPaintStyleSuite can then be used to interact with the control.
*/

/** Illustrator 12.0 PaintStyle suite */
typedef struct 
{	
	void ASAPI (*SetStrokeActive)();
	ASBoolean ASAPI (*IsStrokeActive)();
	void ASAPI (*SetFillActive)();
	ASBoolean ASAPI (*IsFillActive)();
	void ASAPI (*SetDefaultFillStroke)();
	int ASAPI (*GetActiveGradientStopIndex)();
	ASErr ASAPI (*GetCurrentGradient)(AIColor *color);
	ASErr ASAPI (*GetCurrentColor)(AIColor *color);
	ASErr ASAPI (*ShowGradientDialog)();
	ASErr ASAPI (*ShowColorDialog)();
	/** Updates the active gradient stop, fill or stroke color.  Only updates the proxies if
	caching is started. */
	ASErr ASAPI (*SetActiveColor)(AIColor *color, ASBoolean useGradientStop);
	/** Starts caching the current PathStyle. */
	ASErr ASAPI (*BeginActiveColor)();
	/** Finishes caching the current PathStyle. */
	ASErr ASAPI (*EndActiveColor)();
	ASBoolean ASAPI (*IsCurrentColorStroke)();
	ASErr ASAPI (*SetAIColor)(AIColor *color, AIColorMap *colorMap, ASBoolean isStroke);
	ASErr ASAPI (*SetCurrentGradient)(AIColor *color);
	ASErr ASAPI (*SetCurrentColor)(AIColor *color);
	ASErr ASAPI (*ToggleColorDialog)();

	/** Set the color displayed by a color editor control. */
	ASErr ASAPI (*SetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);
	/** Get the color displayed by a color editor control. */
	ASErr ASAPI (*GetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);
	/** Set the current color space of a color editor control. */
	ASErr ASAPI (*SetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace space);
	/** Get the current color space of a color editor control. */
	ASErr ASAPI (*GetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace *space);
	/** Sets options that affect the behaviour of a color editor control group. */
	ASErr ASAPI (*SetColorEditorOptions)(ADMItemRef colorEditor, const AI120ColorEditorOptions& options);
	/** Gets the current options for a color editor control group. */
	ASErr ASAPI (*GetColorEditorOptions)(ADMItemRef colorEditor, AI120ColorEditorOptions& options);

	void ASAPI (*SwapFillStroke)();
	/** Puts up a dialog that allows the user to choose a color. Returns the color in
	currentColor and true if the the dialog was OK'ed. */
	ASBoolean ASAPI (*DisplayColorPicker)(AIColor *currentColor);

	/** Set the color displayed by a color editor control. */
	ASErr ASAPI (*SetColorEditorColor)(ADMItemRef colorEditor, AIColorEditorColor *color);
	/** Get the color displayed by a color editor control. */
	ASErr ASAPI (*GetColorEditorColor)(ADMItemRef colorEditor, AIColorEditorColor *color);
	/** Sets whether the editor is in read only mode or not. In read only mode
	the editor displays the color and its values but does not allow it to
	be modified. The options allow additional configuration of what is shown
	in read only mode. See #AIColorEditorReadOnlyOption. */
	ASErr ASAPI (*SetColorEditorReadOnly)(ADMItemRef colorEditor, ASBoolean readOnly, ASInt32 options);

} AI120PaintStyleSuite;


#include "AIHeaderEnd.h"

#endif