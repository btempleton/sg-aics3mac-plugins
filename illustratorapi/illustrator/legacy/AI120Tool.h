#ifndef __AI120Tool__
#define __AI120Tool__

/*
 *        Name:	AI120Tool.h
 *   $Revision: 31 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Tool Suite.
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

#include "AITool.h"

#include "AIHeaderBegin.h"


/** @file AI120Tool.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120ToolSuite			kAIToolSuite
#define kAIToolSuiteVersion6	AIAPI_VERSION(6)
#define kAIToolSuiteVersion9	AIAPI_VERSION(9)
#define kAI120ToolVersion		kAIToolSuiteVersion9

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	Plug-in Tools provide the same level of interaction with the Illustrator
	artwork that native Illustrator Tools provide. They can work on existing
	artwork or create new objects. Plug-in Tools are added to the Illustrator Tool
	Palette in their own set or as part of an existing ToolSet. Feedback can be
	implemented using Illustrator API calls or at a lower level. Tools work fine by
	themselves but can be used in conjunction with other plug-in types.

	This section describes how to install and use plug-in tools. It describes the
	caller/selector pairs and messages that plug-in tools receive, as well as the
	functions to add tools, set options, and control the tool’s appearance in a
	tool palette.
 
	The caller for Tool plug-ins is #kCallerAITool. The following selectors
	may be sent. The mouse selectors are where the main work of a plug-in tool
	is done. The selectors would be checked for in the plug-in's main function.

	- #kSelectorAIEditToolOptions
	- #kSelectorAITrackToolCursor
	- #kSelectorAIToolMouseDown
	- #kSelectorAIToolMouseDrag
	- #kSelectorAIToolMouseUp
	- #kSelectorAISelectTool
	- #kSelectorAIDeselectTool
	- #kSelectorAIReselectTool

	A number of options control the behaviour of plug-in tools. These options are
	typically set when the tool is installed by AddTool() but they may be modified
	using SetToolOptions(). The options are defined by #AIToolOptions.

	The following notifiers are related to tools:

	- #kAIUserToolChangedNotifier
	- #kAIToolSelectedNotifier
	- #kAIToolDeselectedNotifier
	- #kAIToolClearStateNotifier
	- #kAIToolTitleChangedNotifier
	- #kAIToolIconChangedNotifier
	- #kAIToolTooltipChangedNotifier
	- #kAIToolHelpIDChangedNotifier
	- #kAIToolChangedNotifier
	- #kAIToolWindowChangedNotifier
	- #kAIToolSuspendNotifier
	- #kAIToolResumeNotifier
	- #kAIEyedropperDragNotifier

	A plug-in tool uses the Illustrator API calls and creates or modifies Illustrator
	art objects directly when the mouse selectors are received. The application
	updates the window between calls to the plug-in, so the new or changed
	artwork appears as the mouse moves. The AIUndoSuite::UndoChanges() function
	can be used before the tool drag is processed, allowing the plugin a known artwork
	state from which it can redraw its changes.

	Some tools may work on several art objects that they select. Since multiple
	plug-ins can be running at a given time, it is possible that the artwork state
	will change in the course of using a tool. If the tool needs an opportunity to
	verify that a specific artwork state exists, it can be combined with a plug-in
	notifier. The notifier would indicate that the artwork selection or properties
	have been changed. The tool would be aware of this before it selects or
	processes artwork further.
 */
typedef struct {

	/** Pass a reference to your tool plug-in in self and the tool’s name as a C
		string.

		The AIAddToolData structure contains information used in the tool
		palette.

		The options flags controls the tool's behavior, and can be set to
		any combination of the options from #AIToolOptions.

		The AIToolHandle returned is the installed plug-in tool. If you are installing
		multiple tools, this reference must be stored in the plug-in’s globals record,
		as your plug-in will need it to determine which tool will be is being called.
		
		AddTool is generally used at startup.
	*/
	AIAPI AIErr (*AddTool) ( SPPluginRef self, char *name,
				AIAddToolData *data, long options, 
				AIToolHandle *tool );
	
	/** Returns a pointer to the name of the tool. This is the name value originally
		passed to the AddTool call. It should not be modified. */
	AIAPI AIErr (*GetToolName) ( AIToolHandle tool, char **name );
	/** Use this to get the current options of a tool. Pass the AIToolHandle from the
		tool message to get options for the current tool being called or use GetNthTool()
		to get a tool by index. The options returned are the current options flags as
		defined by #AIToolOptions. */
	AIAPI AIErr (*GetToolOptions) ( AIToolHandle tool, long *options );
	/** Use this to set the current options of a tool. Pass the AIToolHandle from the
		tool message to set options for the tool being called or use GetNthTool() to
		set a tool by index. The options variable must reflect all tool options. The
		options flags are as defined by #AIToolOptions.

		Because the options variable must reflect all tool options, this call should be
		used in conjunction with the GetToolOptions call. This will avoid destroying
		any of the plug-ins existing options. */
	AIAPI AIErr (*SetToolOptions) ( AIToolHandle tool, long options );
	/** This call will return a reference to the plug-in that installed the tool. The
		AIPluginHandle can then be used with the SPPluginSuite functions. */
	AIAPI AIErr (*GetToolPlugin) ( AIToolHandle tool, SPPluginRef *plugin );

	/** This function gets the selected plug-in tool. It can be used to implement a
		user interface for setting a tool to use. The tool palette is actually a
		plug-in that uses this call. */
	AIAPI AIErr (*GetSelectedTool) ( AIToolHandle *tool );
	/** This function sets the selected plug-in tool. It can be used to implement a
		user interface for setting a tool to use. The tool palette is actually a
		plug-in that uses this call. */
	AIAPI AIErr (*SetSelectedTool) ( AIToolHandle tool );

	/** Use CountTools() with GetNthTool() to iterate through the plug-in tools
		installed. */
	AIAPI AIErr (*CountTools) ( long *count );
	/** This call returns the AIToolHandle at the specified index. It can be used with
		CountTools() to iterate through the plug-in tools installed. */
	AIAPI AIErr (*GetNthTool) ( long n, AIToolHandle *tool );

	/** This call returns the AIToolHandle from the specified Tool number. Illustrator
		assigns a number to a plug-in tool when it is created using AddTool(). */
	AIAPI AIErr (*GetToolHandleFromNumber) ( AIToolType toolNum,  AIToolHandle *tool );
	/** This call returns the tool number from the specified tool name. The names of
		Illustrator's built in tools can be found in AIToolNames.h. The name of a plugin
		tool is the same name passed into the AddTool() function. This function can be used
		when filling the AIAddToolData structure in preparation for adding your plugin
		tool. */
	AIAPI AIErr (*GetToolNumberFromName) ( char *name, AIToolType *toolNum );
	/** This call returns the tool number from the specified AIToolHandle. */
	AIAPI AIErr (*GetToolNumberFromHandle) ( AIToolHandle tool, AIToolType *toolNum );
	/** Get the name of a tool from its number. Caller must copy result immediately. */
	AIAPI AIErr (*GetToolNameFromNumber) (AIToolType toolNum, char **name);

	/** This function gets the indicated plug-in tool's title, as specified when it was
		added or modified with SetToolTitle(). The title is a C string that may be
		displayed to the user as the current tool. It can be used to implement a user
		interface for setting a tool to use. The plug-in tool palette is actually a
		plug-in that uses this call. */
	AIAPI AIErr (*GetToolTitle) ( AIToolHandle tool, char **title );
	/** This function changes the title of the plug-in tool. It might be used in
		dynamically creating variants of a standard tool. title is a C style string. */
	AIAPI AIErr (*SetToolTitle) ( AIToolHandle tool, char *title );
	/** This function gets the icon of the indicated plug-in tool. It can be used to
		implement a user interface for setting a tool to use. The icon is an ADMIconRef.
		See the ADMIconSuite documentation for a description of an ADMIconRef. The plug-in
		tool palette is actually a plug-in that uses this call. */
	AIAPI AIErr (*GetToolIcon) ( AIToolHandle tool, ADMIconRef *icon );
	/** This function changes the icon of the plug-in tool. The icon is an ADMIconRef.
		See the ADMIconSuite documentation for a description of an ADMIconRef. */
	AIAPI AIErr (*SetToolIcon) ( AIToolHandle tool, ADMIconRef icon );
	/** This function returns a plug-in’s tooltip from the specified AIToolHandle.
		The tooltip is the same as that which was passed to the AddTool() function. */
	AIAPI AIErr (*GetTooltip) ( AIToolHandle tool, char **tooltip );
	/** This function sets the tooltip of the the specified AIToolHanlde. */
	AIAPI AIErr (*SetTooltip) ( AIToolHandle tool, char *tooltip );
	/** This function returns the help id for the tool which can be an integer or
		a pooled string. */
	AIAPI AIErr (*GetToolHelpID) ( AIToolHandle tool, ASHelpID *helpID );
	/** Sets the tool's help id. */
	AIAPI AIErr (*SetToolHelpID) ( AIToolHandle tool, ASHelpID helpID );

	/** This API is typically called once, at startup, to initialize which fields in the
		info palette the tool will use. The infoVars parameter is a pointer to the first
		member of an array of information variables terminated by the special variable
		#kInfoEndOfList. Each variable that is displayed on Illustrator's Info Palette has
		a label. The information variable you pass into this function will determine which
		label is displayed with your info value. The variables are defined in
		#AIToolInfoVariable. */
	AIAPI AIErr (*SetToolInfoVars) ( AIToolHandle tool, const long * infoVars );
	/** Unlike SetToolInfoVars(), this call can be used anytime to set the tool's info
		values displayed in the Info Palette. infoVars is a pointer to an array of info
		variables. This list corresponds to the list passed to SetToolInfoVars(). The
		code below illustrates it's use.

@code
	AIErr UpdateInfoPalette( AIToolHandle tool, AIRealPoint origin, AIArtHandle art )
	{
		ASErr error = kNoErr;
		if (art)
		{
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
	
	/** Check whether a pressure sensitive tablet is being used. */
	AIAPI AIErr (*SystemHasPressure) ( ASBoolean *hasPressure );
	
	// New for AI10
	
	/** Gets the rollover icon for the given tool. If the plugin tool never sets
		a rollover icon, then the regular icon is also used as the rollover icon. */
	AIAPI AIErr (*GetToolRolloverIcon) ( AIToolHandle tool, ADMIconRef *icon );
	/** Sets the rollover icon for the given tool. If the plugin tool never sets
		a rollover icon, then the regular icon is also used as the rollover icon. */
	AIAPI AIErr (*SetToolRolloverIcon) ( AIToolHandle tool, ADMIconRef icon );

	/** Deprecated in AI11. Please do not use. */
	AIAPI AIErr (*GetToolNullEventInterval) (AIToolHandle tool, AIToolTime *outTime);
	/** Deprecated in AI11. Please do not use. */
	AIAPI AIErr (*SetToolNullEventInterval) (AIToolHandle tool, AIToolTime inTime);
	
} AI120ToolSuite;




#include "AIHeaderEnd.h"


#endif
