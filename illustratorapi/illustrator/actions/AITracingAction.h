#ifndef _AITRACINGACTION_H_
#define _AITRACINGACTION_H_

/*
 *        Name:	AITracingAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 10.0 Actions for envelopes.
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

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif



// -----------------------------------------------------------------------------
// Action: kAITracingMenuAction
// Purpose: runs some functionality accessible through the Tracing submenus
//
// Parameters:
//	- kAITracingMenuItem, enum: the menu item to run
// -----------------------------------------------------------------------------

/** @ingroup Actions
	Executes items in the Tracing submenus.
		@param #kAITracingMenuItem The menu item to run,
			a \c kTracingAction* constant.See \c AITracingAction.h.
	*/
#define kTracingPluginActionName	"ai_plugin_tracing"

/**	Parameter to \c #kTracingPluginActionName.
	The menu item to run, a \c kTracingAction* constant. */
const ActionParamKeyID kAITracingMenuItem	= 'menu'; // enum

/** Menu item identifier for \c #kAITracingMenuItem: Make */
#define kTracingActionMake						1
/** Menu item identifier for \c #kAITracingMenuItem: Make and Expand  */
#define kTracingActionMakeAndExpand				2
/** Menu item identifier for \c #kAITracingMenuItem: Make and LivePaint */
#define kTracingActionMakeAndLivePaint			3
/** Menu item identifier for \c #kAITracingMenuItem: Release */
#define kTracingActionRelease					4
/** Menu item identifier for \c #kAITracingMenuItem: Options */
#define kTracingActionOptions					5
/** Menu item identifier for \c #kAITracingMenuItem: Expand */
#define kTracingActionExpand					6
/** Menu item identifier for \c #kAITracingMenuItem: Expand as Viewed */
#define kTracingActionExpandAsViewed			7
/** Menu item identifier for \c #kAITracingMenuItem: Expand as Live Paint */
#define kTracingActionExpandAsLivePaint			8
/** Menu item identifier for \c #kAITracingMenuItem: Show No Tracing Result */
#define kTracingActionShowNoTracingResult		9
/** Menu item identifier for \c #kAITracingMenuItem: Show Tracing Result */
#define kTracingActionShowTracingResult			10
/** Menu item identifier for \c #kAITracingMenuItem: Show Outlines */
#define kTracingActionShowOutlines				11
/** Menu item identifier for \c #kAITracingMenuItem: Show Outlines and Tracing */
#define kTracingActionShowOutlinesAndTracing	12
/** Menu item identifier for \c #kAITracingMenuItem: Show No Image */
#define kTracingActionShowNoImage				13
/** Menu item identifier for \c #kAITracingMenuItem: Show Original Image */
#define kTracingActionShowOriginalImage			14
/** Menu item identifier for \c #kAITracingMenuItem: Show Adjusted Image */
#define kTracingActionShowAdjustedImage			15
/** Menu item identifier for \c #kAITracingMenuItem: Show Transparent Image */
#define kTracingActionShowTransparentImage		16
/** Menu item identifier for \c #kAITracingMenuItem: Presets */
#define kTracingActionPresets					17




#endif // _AITRACINGACTION_H_