#ifndef __AI80PaintStyle__
#define __AI80PaintStyle__

/*
 *        Name:	AI80PaintStyle.h
 *   $Revision: 3 $
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

#ifndef __AIPaintStyle__
#include "AIPaintStyle.h"
#endif

#include "AIHeaderBegin.h"

// AIPaintStyle Suite
#define kAI80PaintStyleSuiteVersion		AIAPI_VERSION(4)

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
	ASErr ASAPI (*SetActiveColor)(AIColor *color, ASBoolean useGradientStop);
	ASErr ASAPI (*BeginActiveColor)();
	ASErr ASAPI (*EndActiveColor)();
	ASBoolean ASAPI (*IsCurrentColorStroke)();
	ASErr ASAPI (*SetAIColor)(AIColor *color, AIColorMap *colorMap, ASBoolean isStroke);
	ASErr ASAPI (*SetCurrentGradient)(AIColor *color);
	ASErr ASAPI (*SetCurrentColor)(AIColor *color);
	ASErr ASAPI (*ToggleColorDialog)();
	//version 3, new for 7.0.1
	ASErr ASAPI (*SetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);
	ASErr ASAPI (*GetColorEditorAIColor)(ADMItemRef colorEditor, AIColor *color, AIColorMap *colorMap);
	ASErr ASAPI (*SetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace space);
	ASErr ASAPI (*GetColorEditorColorSpace)(ADMItemRef colorEditor, ColorSpace *space);
	void ASAPI (*SwapFillStroke)();
} AI80PaintStyleSuite;


#include "AIHeaderEnd.h"

#endif