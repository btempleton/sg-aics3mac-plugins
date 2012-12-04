#ifndef __AI110PaintStyle__
#define __AI110PaintStyle__

/*
 *        Name:	AIPaintStyle.h
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

#include "AIPaintStyle.h"

#include "AIHeaderBegin.h"

/** @file AI110PaintStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110PaintStyleSuite			"AI Paint Style Suite"
#define kAIPaintStyleSuiteVersion5		AIAPI_VERSION(5)
#define kAI110PaintStyleSuiteVersion	kAIPaintStyleSuiteVersion5


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
	
	void ASAPI (*SwapFillStroke)();
	
	/** Puts up a dialog that allows the user to choose a color. Returns the color in
		currentColor and true if the the dialog was OK'ed. */
	ASBoolean ASAPI (*DisplayColorPicker)(AIColor *currentColor);
	
} AI110PaintStyleSuite;


#include "AIHeaderEnd.h"

#endif