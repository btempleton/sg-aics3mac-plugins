#ifndef __AI120Toolbox__
#define __AI120Toolbox__

/*
 *        Name:	AIToolbox.h
 *   $Revision: 14 $
 *      Author:	Paul Asente 
 *        Date:	3/19/96
 *     Purpose:	Adobe Illustrator 6.0 Toolbox Suite.
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
#include "AIToolbox.h"

#include "AIHeaderBegin.h"

/** @file AI120Toolbox.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120ToolboxSuite			"AI Toolbox Suite"
#define kAIToolboxVersion3			AIAPI_VERSION(3)
#define kAIToolboxVersion2			AIAPI_VERSION(2)
#define kAI120ToolboxSuiteVersion	kAIToolboxVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The tool box suite is for plug-ins that want to create tool palettes.  There
	can be arbitrarily many of them.  Some of the selectors are also useful for
	non-tool-palette plug-ins that want to know when the current tool changes.
	
	At startup time, after all the tools have been added, the application will send a set
	of messages that describe the current tools.  They can also be sent later in the unlikely
	event that a plug-in adds additional tools later on.

	The following message selectors are associated with the tool box suite.
	The caller for each is #kCallerAIToolbox.
	
	- #kSelectorAIStartToolbox.	Sent to signal the start of a series of calls
		describing tools to be added.  It will always immediately be followed by a
		#kSelectorAIStartToolGroup.  The only valid information in the message is
		the toolbox.
		
	- #kSelectorAIEndToolbox. Sent to signal the end of a series of calls describing
		tools to be added. The only valid information in the message is the toolbox.
		
	- #kSelectorAIStartToolGroup. Sent to signal the start of a tool group.  In the
		default tool palette, tools in a group have a little space between them.
		There will typically be many of these sent.  It will always immediately be
		followed by a #kSelectorAIStartToolSet. The only valid information in the
		message is the toolbox.
		
	- #kSelectorAIEndToolGroup. Sent to signal the end of a tool group.  It will
		always be followed by a new #kSelectorAIStartToolGroup or the #kSelectorAIEndToolbox.
		The only valid information in the message is the toolbox.
		
	- #kSelectorAIStartToolSet.	Sent to signal the start of a tool set.  In the
		default tool palette, tools in a set are in a fly-out menu.  There will
		typically be many of these sent.  It will always immediately be followed by
		a #kSelectorAIAddTool. The only valid information in the message is the toolbox.
		
	- #kSelectorAIEndToolSet. Sent to signal the end of a tool set.  It will always be
		followed by a new #kSelectorAIStartToolSet or the #kSelectorAIEndToolGroup. The
		only valid information in the message is the toolbox.
		
	- #kSelectorAIAddTool. Sent to signal the addition of a tool.  It will always be
		followed by another #kSelectorAIAddTool or a #kSelectorAIEndToolSet.  The message
		is completely filled out for this selector.
		
	- #kSelectorAIAddRollover. Sent to add a rollover icon of a tool.  This may be sent
		any time after the tool has been added.  The toolbox, tool, and icon fields are
		valid in the message.
		
		
	The remaining messages are sent during the the execution of the program to notify
	additional toolboxes of actions taken by a toolbox.  For all these messages, the
	toolbox and tool fields are valid.
	
	- #kSelectorAIToolSelected. Sent to signal that a tool has been selected.
		
	- #kSelectorAIAlternateToolActionSelected. Sent to signal that a tool's alternate
		action has been invoked.  (Typically bringing up a tool options dialog.)
		
	- #kSelectorAICycleTool. Sent to signal a tool cycle.  If the currently selected
		tool is not in the message tool's tool set, make the message tool the current
		tool.  If the currently selected tool is in the message tool's tool set, switch
		to the next tool in the tool set.  
		
	- #kSelectorAISoftCycleTool. Sent to signal a tool soft cycle.  If the currently
		selected tool is not in the message tool's tool set, make the message tool the
		current tool.  If the currently selected tool is in the message tool's tool
		set, do nothing.  
*/

typedef struct {
	/** Register a plugin to receive toolbox selector messages and be allowed to use the
		other suite methods. */
	AIAPI AIErr (*AddToolbox) (SPPluginRef self, char *name,
							   AIToolboxHandle *toolbox);
	
	/** Make a new tool the current tool */							   
	AIAPI AIErr (*SetTool) (AIToolboxHandle toolbox, AIToolType tool);
	
	/** Tell a tool to perform its alternate action, typically an options dialog.
		This does not change the current tool. */
	AIAPI AIErr (*AlternateAction) (AIToolboxHandle toolbox, AIToolType tool );
	
	/** Send a CycleTool selector. */
	AIAPI AIErr (*CycleTool) (AIToolboxHandle toolbox, AIToolType tool);

	/** Find out about which toolboxes exist */
	AIAPI AIErr (*CountToolboxes) (long *count);
	AIAPI AIErr (*GetNthToolbox) (long n, AIToolboxHandle *toolbox);
} AI120ToolboxSuite;


#include "AIHeaderEnd.h"


#endif

