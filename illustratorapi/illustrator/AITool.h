#ifndef __AITool__
#define __AITool__

/*
 *        Name:	AITool.h
 *   $Revision: 31 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tool Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIEvent__
#include "AIEvent.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AIToolNames__
#include "AIToolNames.h"
#endif

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ASHelp__
#include "ASHelp.h"
#endif

#ifndef FLT_MAX
#include <float.h>
#endif

#include "AIHeaderBegin.h"

/** @file AITool.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIToolSuite			"AI Tool Suite"
#define kAIToolSuiteVersion6	AIAPI_VERSION(6)
#define kAIToolSuiteVersion10	AIAPI_VERSION(10)
#define kAIToolSuiteVersion		kAIToolSuiteVersion10
#define kAIToolVersion			kAIToolSuiteVersion

/** @ingroup Notifiers
	Sent when a property of a plug-in tool is changed, such as
	its options, title, icon, or tooltip. */
#define kAIUserToolChangedNotifier		"AI User Tool Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool is selected. The data is the \c #AIToolHandle.
	Reselection of an already selected tool sends both
	\c #kAIToolDeselectedNotifier and \c #kAIToolSelectedNotifier
	with the \c #kSelectorAIReselectTool message. */
#define kAIToolSelectedNotifier			"AI Tool Selected Notifier"
/** @ingroup Notifiers
	Sent when a tool is deselected. The data is the \c #AIToolHandle. */
#define kAIToolDeselectedNotifier		"AI Tool Deselected Notifier"
/** @ingroup Notifiers
	Sent to notify tools that they should clear any editing state that
	they maintain.  Tools other than the current tool might
	maintain editing state; for example, selecting the zoom tool
	does not clear the editing state of the pen tool, which remembers
	the path to which it is adding points. */
#define kAIToolClearStateNotifier		"AI Tool Clear State Notifier"
/** @ingroup Notifiers
	Sent when the title string of a tool is changed.
	See \c #AIToolSuite::SetToolTitle() */
#define kAIToolTitleChangedNotifier		"AI Tool Title Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool's icon is changed. See \c #AIToolSuite::SetToolIcon()
	and \c #AIToolSuite::SetToolRolloverIcon() */
#define kAIToolIconChangedNotifier		"AI Tool Icon Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool's rollover tooltip is changed.  */
#define kAIToolTooltipChangedNotifier	"AI Tool Tooltip Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool's help ID is changed. See \c #AIToolSuite::SetToolHelpID() */
#define kAIToolHelpIDChangedNotifier	"AI Tool Help ID Changed Notifier"
/** @ingroup Notifiers
	Sent when the current tool is changed to a different tool. */
#define kAIToolChangedNotifier			"AI Tool Changed Notifier"
/** @ingroup Notifiers
	Sent when the tool window has changed. */
#define kAIToolWindowChangedNotifier	"AI Tool Window Changed Notifier"
/** @ingroup Notifiers
	Sent when the cursor leaves a document window.
	See also \c #kAIToolResumeNotifier. */
#define kAIToolSuspendNotifier			"AI Tool Suspend Notifier"
/** @ingroup Notifiers
	Sent when the cursor enters a document window.
	See also \c #kAIToolSuspendNotifier. */
#define kAIToolResumeNotifier			"AI Tool Resume Notifier"
/** @ingroup Notifiers
	Sent when \c #AIToolTabletPointerType is changed. */
#define kAIToolTabletPointerTypeChangedNotifier	"AI Tablet Pointer Type Changed Notifier"
/** @ingroup Notifiers
	Sent when the modifier keys for the current tool are changed. */
#define kAIToolModifiersChangedNotifier	"AI Tool Modifiers Changed Notifier"
/** @ingroup Notifiers
	Sent when the user presses the space bar to select the scroll tool (\c #kScrollTool)
	or zoom tool (\c #kZoomTool), or presses Ctrl+spacebar, or Ctrl+Alt+spacebar
	while using another tool. */
#define kAIToolSuspendedBySpacebarNotifier	"AI Tool Suspended by Spacebar Notifier"
/** @ingroup Notifiers
	Sent when the user releases the spacebar (or Ctrl+spacebar, or Ctrl+Alt+spacebar)
	to resume using the original tool.
	*/
#define kAIToolResumedBySpacebarNotifier	"AI Tool Resumed by Spacebar Notifier"
/** @ingroup Notifiers
	Sent when \c #kSelectTool, \c #kDirectSelectTool, or \c #kDirectObjectSelectTool
	is temporarily reselected by pressing Ctrl(Windows) or Cmd(Macintosh) key while
	using another tool.
	For example, if \c #kDirectSelectTool is selected and you then choose the eraser tool,
	pressing the Ctrl or Cmd key temporarily switches back to \c #kDirectSelectTool, and
	sends this notification. */
#define kAIToolSuspendedByCmdKeyNotifier	"AI Tool Suspended by Cmd Key Notifier"
/** @ingroup Notifiers
	Sent when the original tool is restored from a temporary switch back to
	\c #kSelectTool, \c #kDirectSelectTool, or \c #kDirectObjectSelectTool.
	Sent when the Ctrl or Cmd key is released. */
#define kAIToolResumedByCmdKeyNotifier	"AI Tool Resumed by Cmd Key Notifier"


// Notifiers sent by built-in tools

/** @ingroup Notifiers
	Sent by the eyedropper when it is selected and dragged. The data is
	an \c #AIEyedropperDragNotifyData specifying the event and whether the
	path style has changed as a result. */
#define kAIEyedropperDragNotifier		"AI Eyedropper Drag Notifier"



/** @ingroup Callers
	The tool caller. See \c #AIToolSuite. */
#define kCallerAITool					"AI Tool"

/** @ingroup Selectors
	Sent when the tool has been selected (double-clicked) in the Tool palette.
	The plug-in can display a tool options dialog.
	The message data is an \c #AIToolMessage. */
#define kSelectorAIEditToolOptions		"AI Edit Options"
/** @ingroup Selectors
	Sent when the tool is selected and as the cursor is moved over the
	artboard with the button up. The plug-in can set the
	cursor based on location or some other factor. The message data is an \c #AIToolMessage. */
#define kSelectorAITrackToolCursor		"AI Track Cursor"
/** @ingroup Selectors
	Sent when the mouse button is pressed. The message data is an \c #AIToolMessage
	that contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseDown		"AI Mouse Down"
/** @ingroup Selectors
	Sent on drag (cursor move with button down). The plug-in receives a series
	of these selectors. The message data is an \c #AIToolMessage that
	contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseDrag		"AI Mouse Drag"
/** @ingroup Selectors
	Either follows the mouse-down selector immediately or ends
	the mouse-drag selectors. The message data is an \c #AIToolMessage
	that contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseUp			"AI Mouse Up"
/** @ingroup Selectors
	Sent to a plug-in when its tool has been selected, to allow
	initialization. The message data is an \c #AIToolMessage. */
#define kSelectorAISelectTool			"AI Select"
/** @ingroup Selectors
	Sent to a plug-in when a different tool is selected, to allow cleanup
	of any run-time variables. The message data is an \c #AIToolMessage. */
#define kSelectorAIDeselectTool			"AI Deselect"
/** @ingroup Selectors
	Sent when an already-selected tool is reselected, with both
	\c #kAIToolDeselectedNotifier and \c #kAIToolSelectedNotifier.
	The message data is an \c #AIToolMessage.  */
#define kSelectorAIReselectTool			"AI Reselect"
/** @ingroup Selectors
	Sent when shortcut '[' is activated to decrease a diameter. */
#define kSelectorAIToolDecreaseDiameter	"AI Decrease Diameter"
/** @ingroup Selectors
	Sent when shortcut ']' is activated to increase a diameter. */
#define kSelectorAIToolIncreaseDiameter	"AI Increase Diameter"


//  Brush tools share these options, so if you add new ones,
//	make sure they do not overlap with the brush tool options defined in
//	AIBrushMgr.h, which start at 1L<<16 and go up.

/**  Bit flags for options that can be set by a plug-in tool when it is installed
	 with \c #AIToolSuite::AddTool(), or later with \c #AIToolSuite::SetToolOptions(). */
enum AIToolOptions {
	/** Set to receive \c #kSelectorAITrackToolCursor, which allows you to
		control the cursor for your too. When off (the default), a standard arrow
		cursor is used for the tool.  */
	kToolWantsToTrackCursorOption		= (1L<<0),
	/** Set to disable automatic scrolling. When off (the default), the Illustrator window
		scrolls when a tool reaches the edge. For tools that manipulate artwork,
		autoscroll is useful. Set this to turn autoscroll off for a tool that
		draws to the screen directly, like the built-in Brush tool. */
	kToolDoesntWantAutoScrollOption		= (1L<<1),
	/**	Set to buffer the drag selectors and messages and send all of them
		to the tool at once. Useful if a tool is calculation intensive.  The effect
		is no longer real-time, but has a smoother final output.
		When off (the default), the tool processes drag selectors and returns frequently,
		resulting in near real-time feedback. If there are intensive calculations
		during the drag selector, the tool could miss drag notifications, resulting in rougher
		tracking.  */
	kToolWantsBufferedDraggingOption	= (1L<<2),
	/** Set to maintain the edit context when this tool is selected. For art objects,
		keeps all current points and handles selected. For text, keeps the insertion
		point in the current location. Set this option for navigational tools like
		the Zoom and Scroll tools. */
	kToolMaintainEditContextOption 		= (1L<<3),
	/** Set to maintain the text edit context when the tool is selected,
		if \c #kToolMaintainEditContextOption is also set. */
	kToolIsTextToolOption 				= (1L<<4),
	/** Set to receive \c #kSelectorAIToolDecreaseDiameter and
		\c #kSelectorAIToolIncreaseDiameter. Use if the tool needs to change
		diameter when either '[' or ']' is pressed. */
	kToolWantsToChangeDiameterOption 				= (1L<<5)

};


/** Tool information values. See \c #AIToolSuite::SetToolInfoVars().
	All values are real numbers, except these string values,
	which are  platform-encoded strings passed as \c char*:
	<br> \c kInfoFontAndSize
	<br> \c kInfoTrackOrKern
	<br> \c kInfoText1-6 and \c kInfoLongText1-3
	<br><br> \c kInfoTextUnicode1-6 and \c kInfoLongTextUnicode1-3 refer to the
	same Info palette slots as \c kInfoText1-6 and \c kInfoLongText1-3, but
	values are \c ai::UnicodeString*, which is treated as \c const.
	*/
enum AIToolInfoVariable {
	kInfoPageX = 0,
	kInfoPageY,
	kInfoSizeX,
	kInfoSizeY,
	kInfoDistance,
	kInfoVectorAngle,
	kInfoScaleX,
	kInfoScaleY,
	kInfoZoom,
	kInfoCornerRoundness,
	kInfoRotAngle,
	kInfoShearAngle,
	kInfoFontAndSize,
	kInfoTrackOrKern,
	kInfoRawRotAngle,
	kInfoDocX,
	kInfoDocY,
	kInfoText1,
	kInfoText2,
	kInfoText3,
	kInfoText4,
	kInfoText5,
	kInfoText6,
	kInfoLongText3,
	kInfoNumVars,
	kInfoBlank,

	// new in AI 12
	kInfoTextUnicode1,
	kInfoTextUnicode2,
	kInfoTextUnicode3,
	kInfoTextUnicode4,
	kInfoTextUnicode5,
	kInfoTextUnicode6,
	kInfoLongTextUnicode1,
	kInfoLongTextUnicode2,
	kInfoLongTextUnicode3,

	// overlayed items.
	kInfoLongText1 = kInfoFontAndSize,
	kInfoLongText2 = kInfoTrackOrKern,


	kInfoEndOfList = -1	 // Use this to terminate the infoVars list
};

/** An \c #AIToolType value that creates a new group or toolset.
	See @ref Toolsets */
#define kNoTool -2

/** A tool number used to indicate a tool group or toolset.
	See @ref Toolsets and \c #AIToolSuite::GetToolNumberFromName() */
typedef short AIToolType;

/** Tool numbers less than this value are built-in,
	numbers greater than this are plug-in. See @ref Toolsets
	and \c #AIToolSuite::GetToolNumberFromName()  */
#define kPluginToolOffset 1000

/** @ingroup Errors
	See \c #AIToolSuite */
#define kToolCantTrackCursorErr		'TLTK'

//ToolTime for GetToolNullEventInterval. This type is to be deprecated ASAP.
// <<LET ME KNOW IF THIS DOESN'T HAPPEN>>
typedef double AIToolTime; //Time in Seconds

#define kToolTimeDurationSecond            ((AIToolTime)1.0)
#define kToolTimeDurationMillisecond       ((AIToolTime)(kToolTimeDurationSecond/1000))
#define kToolTimeDurationNoWait            ((AIToolTime)0.0)
#define kToolTimeDurationForever           ((AIToolTime)(-1.0))


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a tool plug-in, never dereferenced.
	Access with \c #AIToolSuite. */
typedef struct _t_AIToolOpaque *AIToolHandle;

/** Information needed to add a tool using \c #AIToolSuite::AddTool(). */
typedef struct {
	/** Display name for tool. */
	char *title;
	/** Short descriptive string shown when tool is activated. */
	char *tooltip;
	/** The Help system identifier. */
	ASHelpID helpID;
	/** The icon shown in the Tools palette. See \c #ADMIconSuite2. */
	ADMIconRef icon;
	/** The Tools palette group to which this tool belongs.
		A tool number or \c #kNoTool to create a new group.
		See @ref Toolsets. */
	AIToolType sameGroupAs;
	/** The Tools palette toolset to which this tool belongs.
		A tool number or \c #kNoTool to create a new toolset.
		See @ref Toolsets. */
	AIToolType sameToolsetAs;
} AIAddToolData;


/** An \c #AIToolTabletPointerTypeValue describing a type of pointing device.
	Used with a pressure-sensitive input device, such as a graphic tablet. */
typedef short AIToolTabletPointerType;

/** \c #AIToolTabletPointerType constants that describe the type of
	input being received from input devices. */
enum AIToolTabletPointerTypeValue
{
	kAIToolTabletPointerTypeUnknown = 0,
	/** Pen end of a stylus. */
	kAIToolTabletPointerTypePen,
	/** Mouse or other non-pressure-sensitive pointer device. */
	kAIToolTabletPointerTypeCursor,
	/** Eraser end of a stylus. */
	kAIToolTabletPointerTypeEraser
};

/** An \c #AIToolPressureValue indicating the amount of force being
	applied with a pressure-sensitive input device, such as a graphic tablet. */
typedef short AIToolPressure;
/** \c #AIToolPressure constants that indicate an amount of force applied to a
	pressure-sensitive input device. */
enum AIToolPressureValue
{
	/** The maximum pressure applied by a tool */
	kAIMaxToolPressure = 255,
	/** The minimal pressure applied by a tool */
	kAIMinToolPressure = 0,
	/** A default value for when there is no pressure data.  */
	kAINormalToolPressure = 127
};

/** An \c #AIToolAngleValue describing values of an input device
	such as tilt, rotation and bearing of a pen on a graphic tablet. */
typedef short AIToolAngle;
/** \c #AIToolAngle constants that describe values of an input device
	such as tilt, rotation and bearing of a pen on a graphic tablet. */
enum AIToolAngleValue
{
	/** Angle constants in degrees */
	kAIToolAngle0 = 0,
	kAIToolAngle90 = 90,
	kAIToolAngleNegative179 = -179,
	kAIToolAngle180 = 180,
	kAIToolAngle360 = 360,

	/** Bearing ranges from -179 to 180 where 0 is up */
	kAIToolMinBearing = kAIToolAngleNegative179,
	kAIToolMaxBearing = kAIToolAngle180,
	kAIToolNormalBearing = kAIToolAngle0,

	/** Rotation ranges from -179 to 180 where 0 is up */
	kAIToolMinRotation = kAIToolAngleNegative179,
	kAIToolMaxRotation = kAIToolAngle180,
	kAIToolNormalRotation = kAIToolAngle0,

	/** Tilt ranges from 0 to 90 where 0 means the pen barrel is perpendicular to the tablet's plane
		and 90 means the pen barrel is parallel to the tablet's plane. */
	kAIToolMinTilt = kAIToolAngle0,
	kAIToolMaxTilt = kAIToolAngle90,
	kAIToolNormalTilt = kAIToolMinTilt
};

/** The contents of a tool message. */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** The tool plug-in receiving the message.
		If the plug-in has more than one tool installed, it can
		determine which one was selected by comparing this handle
		to those it has saved in the \c globals variable. */
	AIToolHandle tool;
	/** The location of the mouse cursor in page coordinates. */
	AIRealPoint cursor;
	/** The amount of force being applied to a pressure-sensitive input device,
		such as a graphics tablet.  Use \c #AIToolSuite::SystemHasPressure()
		to determine if such a device is in use. */
	AIToolPressure pressure;
	/** For mouse selectors, the ADM event record for the mouse event,
		containing additional information about the event; see \c #ADMEvent. */
	AIEvent *event;
	/** For graphic tablets, tangential pressure on the finger wheel of the airbrush tool. */
	AIToolPressure stylusWheel;
	/** How the tool is angled, also called altitude or elevation. */
	AIToolAngle tilt;
	/** The direction of tilt, measured clockwise in degrees around the Z axis, also called azimuth, */
	AIToolAngle bearing;
	/**  Rotation of the tool, measured clockwise in degrees around the tool's barrel. */
	AIToolAngle rotation;
} AIToolMessage;


/** The contents of a tool notification. */
typedef struct {
	/** The tool plug-in receiving the notification. If you install more than one tool,
		compare to your saved reference to decide how to handle the notification. */
	AIToolHandle tool;
} AIToolNotifyData;

/** The contents of an eyedropper drag notification, \c #kAIEyedropperDragNotifier. */
typedef struct {
	/** The ADM event record for the mouse event.  */
	AIEvent event;
	/** True if the path style has changed as a result of the drag event. */
	AIBoolean pathStyleChanged;
} AIEyedropperDragNotifyData;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite allows you to provide plug-in tools for Illustrator.
	Plug-in tools can work on existing artwork or create new objects.
	Tools that you add appear in the Illustrator Tool palette in their own set,
	or as part of an existing tool set. Use the functions in this suite
	to add tools, set options, and control the tool’s appearance in the palette.

	Typically, you set the options that control the behavior of a plug-in tool
	when you install the tool with \c #AIToolSuite::AddTool(). You can modify
	them later with \c #AIToolSuite::SetToolOptions().

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIToolSuite and \c #kAIToolVersion.

	@section Toolsets Toolsets and Groups in the Tools Palette

	In the Tools palette, \e a toolset is a collection related tools.
	When there is more than one tool in a toolset, only the frontmost tool's
	icon is shown in the palette, with a triangle in the lower left corner
	to indicate the presence of additional tools. The entire toolset
	is shown when the user holds the mouse button down on the topmost tool.

	A \e group is a collection of toolsets. Groups are separated by vertical
	space in the palette.

	To create a new group or toolset, pass \c #kNoTool for
	\c #AIAddToolData::sameGroupAs or \c #AIAddToolData::sameToolsetAs.
	For example, to create a new tool group:
	@code
toolData.title = "MyTool1";
toolData.tooltip = "MyTool1 Tooltip";
toolData.sameGroupAs = kNoTool;
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add a new toolset to this group:
	@code
toolData.title = "MyTool2";
toolData.tooltip = "MyTool2 Tooltip";
error = sTool->GetToolNumberFromName("MyTool1", &toolData.sameGroupAs);
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add tools to this toolset:
	@code
toolData.title = "MyTool2a";
toolData.tooltip = "Tool2a Tooltip";
error = sTool->GetToolNumberFromName("MyTool1",	&toolData.sameGroupAs);
error = sTool->GetToolNumberFromName("MyTool2", &toolData.sameToolsetAs);
	@endcode

	@section ToolBehavior Tool Behavior

	Implement tool behavior by defining handlers for the caller/selector pairs
	and messages that plug-in tools receive, particularly the mouse selectors.
	Check for selectors in the plug-in's main function.

	Your mouse selector handlers can create or modify art objects directly.
	A tool can select and work on several art objects at once.
	The application updates the window between calls to the plug-in, so the
	new or changed artwork appears as the mouse moves.
	Use \c #AIUndoSuite::UndoChanges() before processing the tool drag,
	in order to maintain a known artwork state from which to redraw changes.

	Because multiple  plug-ins can be running at once,
	the artwork state can change in the course of using your tool.
	To verify that a specific artwork state exists, you can use a plug-in
	notifier to indicate that the artwork selection or properties
	have been changed. See the \c #AINotifierSuite.

	The caller for tool plug-ins is \c #kCallerAITool.

	These selectors are sent:
	<br> \c #kSelectorAIEditToolOptions
	<br> \c #kSelectorAITrackToolCursor
	<br> \c #kSelectorAIToolMouseDown
	<br> \c #kSelectorAIToolMouseDrag
	<br> \c #kSelectorAIToolMouseUp
	<br> \c #kSelectorAISelectTool
	<br> \c #kSelectorAIDeselectTool
	<br> \c #kSelectorAIReselectTool

	These notifiers are related to tools:
	<br> \c #kAIUserToolChangedNotifier
	<br> \c #kAIToolSelectedNotifier
	<br> \c #kAIToolDeselectedNotifier
	<br> \c #kAIToolClearStateNotifier
	<br> \c #kAIToolTitleChangedNotifier
	<br> \c #kAIToolIconChangedNotifier
	<br> \c #kAIToolTooltipChangedNotifier
	<br> \c #kAIToolHelpIDChangedNotifier
	<br> \c #kAIToolChangedNotifier
	<br> \c #kAIToolWindowChangedNotifier
	<br> \c #kAIToolSuspendNotifier
	<br> \c #kAIToolResumeNotifier
	<br> \c #kAIEyedropperDragNotifier

 */
typedef struct {

	/** Installs a plug-in tool. Use at startup.
			@param self This plug-in.
			@param name The unique name of this tool.
			@param data	Information on how to display this tool in the Tool palette.
			@param options Option flags that control the tool's behavior, a logical OR
				of \c #AIToolOptions constants.
			@param tool	[out] A buffer in which to return the tool reference. If you
				install multiple tools, save to compare to the tool reference in tool
				message data.
		*/
	AIAPI AIErr (*AddTool) ( SPPluginRef self, char *name,
				AIAddToolData *data, long options,
				AIToolHandle *tool );

	/** Retrieves the unique identifying name of a tool.
		To get the localizable title that appears in the UI, use \c #GetToolTitle().
			@param tool The tool reference.
			@param name [out] A buffer in which to return the name string. Do
				not modify this string.
		*/
	AIAPI AIErr (*GetToolName) ( AIToolHandle tool, char **name );

	/** Retrieves the option flags of a tool. To retain the existing flags when
		setting options with \c #SetToolOptions(), obtain them with this function
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options [out] A buffer in which to return the options value, a logical
				OR of \c #AIToolOptions constants.
	  	*/
	AIAPI AIErr (*GetToolOptions) ( AIToolHandle tool, long *options );

	/** Sets the option flags of a tool. To retain the existing flags when
		setting options, obtain them with \c #GetToolOptions()
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options The new options value, a logical OR of \c #AIToolOptions constants.
		*/
	AIAPI AIErr (*SetToolOptions) ( AIToolHandle tool, long options );

	/** Retrieves the plug-in that installed a tool.
			@param tool The tool reference.
			@param plugin [out] A buffer in which to return the	plug-in reference,
				which can be used with \c #AIPluginSuite functions.
		*/
	AIAPI AIErr (*GetToolPlugin) ( AIToolHandle tool, SPPluginRef *plugin );

	/** Retrieves the currently selected plug-in tool.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetSelectedTool) ( AIToolHandle *tool );

	/** Selects a tool programmatically. This is the same as the user
		selecting the tool in the Tool palette.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSelectedTool) ( AIToolHandle tool );

	/** Gets the number of installed tools. Use with \c #GetNthTool()
		to iterate through plug-in tools.
			@param count [out] A buffer in which to return the number of tools.
		*/
	AIAPI AIErr (*CountTools) ( long *count );

	/** Retrieves a tool by index position. Use with \c #CountTools()
		to iterate through plug-in tools.
			@param n The 0-based position index.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetNthTool) ( long n, AIToolHandle *tool );

	/** Retrieves a tool by its tool number, as assigned when it
		is created with \c #AddTool() See @ref Toolsets.
			@param toolNum The tool number.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetToolHandleFromNumber) ( AIToolType toolNum,  AIToolHandle *tool );

	/** Retrieves a tool number from a tool's unique name. Use to find the numbers of
		built-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param name The tool name. The names of Illustrator's built-in tools
				can be found in \c AIToolNames.h.
			@param toolNum [out] A buffer in which to return the tool number.
		*/
	AIAPI AIErr (*GetToolNumberFromName) ( char *name, AIToolType *toolNum );

	/** Retrieves a tool number for a tool. Use to find the numbers of
		plug-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param tool The tool reference.
			@param toolNum [out] A buffer in which to return the tool number. 	 */
	AIAPI AIErr (*GetToolNumberFromHandle) ( AIToolHandle tool, AIToolType *toolNum );

	/** Retrieves the unique name of a tool from its number. To get the localizable
		title that appears in the UI, use \c #GetToolTitle().
			@param toolNum The tool number.
			@param name	[out] A buffer in which to return the name string. Do not modify
				this string. Copy it immediately to use it.
		 */
	AIAPI AIErr (*GetToolNameFromNumber) (AIToolType toolNum, char **name);

	/** Retrieves the localizable title of a tool, which appears in the UI.
		To get the unique, identifying name, use \c #GetToolName().
			@param tool The tool reference.
			@param title [out] A buffer in which to return the title string.
		*/
	AIAPI AIErr (*GetToolTitle) ( AIToolHandle tool, char **title );

	/** Sets the localizable title of a tool, which appears in the UI.
			@param tool The tool reference.
			@param title The new title string.
		*/
	AIAPI AIErr (*SetToolTitle) ( AIToolHandle tool, char *title );

	/** Retrieves the icon for a tool.
			@param tool The tool reference.
			@param icon [out] A buffer in which to return the icon object. See \c #ADMIconSuite2.
		*/
	AIAPI AIErr (*GetToolIcon) ( AIToolHandle tool, ADMIconRef *icon );

	/** Sets the icon for a tool.
			@param tool The tool reference.
			@param icon The new icon object. See \c #ADMIconSuite2.
		 */
	AIAPI AIErr (*SetToolIcon) ( AIToolHandle tool, ADMIconRef icon );

	/** Retrieves the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip [out] A buffer in which to return the tooltip string.
		*/
	AIAPI AIErr (*GetTooltip) ( AIToolHandle tool, char **tooltip );

	/** Sets the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip The new tooltip string.
		 */
	AIAPI AIErr (*SetTooltip) ( AIToolHandle tool, char *tooltip );

	/** Retrieves the help-system identifier for a tool.
			@param tool The tool reference.
			@param helpID [out] A buffer in which to return the help ID,
				which can be an integer or a pooled string.
		*/
	AIAPI AIErr (*GetToolHelpID) ( AIToolHandle tool, ASHelpID *helpID );

	/** Sets the help-system identifier for a tool.
			@param tool The tool reference.
			@param helpID The new help ID, which can be an integer or a pooled string.
		 */
	AIAPI AIErr (*SetToolHelpID) ( AIToolHandle tool, ASHelpID helpID );

	/** Determines which labeled fields are displayed in the Info palette for a tool.
		Typically called once at startup to initialize the Info palette.
			@param tool The tool reference.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette, as defined in \c #AIToolInfoVariable.
				Only the fields included in this array are shown for the tool.
				To initialize or set the values in the fields, use \c #SetToolInfoVarValues().
		 */
	AIAPI AIErr (*SetToolInfoVars) ( AIToolHandle tool, const long * infoVars );

	/** Sets field values in the Info palette. Only those fields specified by
		\c #SetToolInfoVars() are displayed in the palette.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette. This is the same array specified
				by \c #SetToolInfoVars().
			@param values A pointer to the first member of an array of values,
				whose positions match those in the \c infoVars array.

			\b Example:
@code
AIErr UpdateInfoPalette( AIToolHandle tool, AIRealPoint origin, AIArtHandle art )
{
	ASErr error = kNoErr;
	if (art) {
		static const long infoVars = { kInfoDocX, kInfoDocY, kInfoSizeX, kInfoSizeY, kInfoEndOfList };
		AIReal *infoValues[4];
		AIReal temp[2];
		AIRealRect artBounds;
		error = sAIArt->GetArtTransformBounds( art,0, kStroke, &artBounds);
		if ( error )
			return error;
		temp[0] = artBounds.right - artBounds.left;
		temp[1] = artBounds.bottom - artBounds.top;
		infoValues[0] = &origin.h;
		infoValues[1] = &origin.v;
		infoValues[2] = temp;
		infoValues[3] = temp +1;
		error = sAITool->SetToolInfoVarValues( infoVars, (void**)infoValues);
		if ( error )
			return error;
	}
}
@endcode
		*/
	AIAPI AIErr (*SetToolInfoVarValues) ( const long *infoVars,  void **values );

	/** Reports whether a pressure-sensitive device such as a graphics tablet
		is being used.
			@param hasPressure [out] A buffer in which to return true if
				a pressure-sensitive device is in use.
		*/
	AIAPI AIErr (*SystemHasPressure) ( ASBoolean *hasPressure );

	// New for AI10

	/** Retrieves the rollover icon for a tool. If no rollover icon is set,
		the regular icon is also used as the rollover icon.
			@param tool The tool reference.
			@param icon  [out] A buffer in which to return the rollover icon.
		*/
	AIAPI AIErr (*GetToolRolloverIcon) ( AIToolHandle tool, ADMIconRef *icon );

	/** Sets the rollover icon for a tool.
			@param tool The tool reference.
			@param icon The new rollover icon.
		*/
	AIAPI AIErr (*SetToolRolloverIcon) ( AIToolHandle tool, ADMIconRef icon );

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*GetToolNullEventInterval) (AIToolHandle tool, AIToolTime *outTime);

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*SetToolNullEventInterval) (AIToolHandle tool, AIToolTime inTime);

	// New for AI13

	/** Selects a plug-in tool, but does not highlight
		it in the palette or show its tool name in the status bar of the document
		window. Indicates this \e soft selection by setting the \c isSoftMode flag.
		\c #SetSelectedTool() turns this flag off.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSoftSelectedTool) ( AIToolHandle tool );

	/** Reports whether there is currently a \e soft tool selection.
		Soft mode is entered when a tool, such as the rectangle tool, is
		selected and the user implicitly overrides this by drawing with the eraser
		end of a tablet stylus.
			@param isSoftMode [out] A buffer in which to return true if there is a
				soft tool selection.
		*/
	AIAPI AIErr (*IsSoftModeSelection) ( AIBoolean *isSoftMode );

} AIToolSuite;


#include "AIHeaderEnd.h"


#endif
