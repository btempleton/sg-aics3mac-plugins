#ifndef __AI110CommandManager__
#define __AI110CommandManager__

/*
 *        Name:	AICommandManager.h
 *   $Revision: 6 $
 *      Author:	Grace Ge
 *        Date:	   
 *     Purpose: .	
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

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AICommandManager__
#include "AICommandManager.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI110CommandManager.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110CommandManagerSuite			"AI Command Manager Suite"
#define kAI110CommandManagerSuiteVersion	kAICommandManagerSuiteVersion1
#define kAICommandManagerSuiteVersion1	AIAPI_VERSION(1)
#define kAICommandManagerSuiteVersion2	AIAPI_VERSION(2)

/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*AddCommand) (AICommandID commandID, const char *name, const char *localizedName);

	AIAPI AIErr (*GetCommandIDFromName) (const char *name, AICommandID *commandID);
	AIAPI AIErr (*GetCommandIDFromLocalizedName) (const char *localizedName, AICommandID *commandID);
	AIAPI AIErr (*GetCommandName) (AICommandID commandID, char *name);
	AIAPI AIErr (*GetCommandLocalizedName) (AICommandID commandID, char *localizedName);

	AIAPI AIErr (*TestFunctionKey) (int fkey, unsigned long admModifiers, AIBoolean *used);
	AIAPI AIErr (*SetActionFunctionKey) (int fkey, unsigned long admModifiers);
	AIAPI AIErr (*ClearActionFunctionKey) (int fkey, unsigned long admModifiers);

	AIAPI AIErr (*GetCommandIDFromShortCutKey) (int key, unsigned long admModifiers, AICommandID *commandID);

	AIAPI AIErr (*SearchCommandLocalizedName) (char *partialName, char *localizedName);

	AIAPI AIErr (*GetShortCutKeyFromCommandID) (AICommandID commandID, int context, int *key, unsigned long *admModifiers, int *represent);
	AIAPI AIErr (*SetShortCutKeyFromCommandID) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent);
	AIAPI AIErr (*DeleteShortCutKeyFromCommandID) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent);

	AIAPI AIErr (*GetShortCutKeyOfCommandEx) (AICommandID commandID, int context, char *commandStr, int *key, unsigned long *admModifiers, int *represent);
	AIAPI AIErr (*SetShortCutKeyOfCommandEx) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent,
												char *commandStr, char *localizedStr, SPPluginRef pluginRef);
	AIAPI AIErr (*DeleteShortCutKeyOfCommandEx) (AICommandID commandID, int context, char *commandStr, int key, unsigned long admModifiers, int represent);
	AIAPI AIErr (*GetCommandExFromShortCutKey) (int key, unsigned long admModifiers, int context, AICommandID *commandID,
												SPPluginRef *pluginRef, char *commandStr, int maxCommandStr, char *localizedStr, int maxLocalizedStr);
} AI110CommandManagerSuite;


/** Most plugins should not need to use this suite. Its primary use is for the actions mechanism.
	In previous versions of Illustrator it supplied functionality necessary to implement keyboard
	shortcuts. That is no longer the case. The keyboard shortcut related functions of the suite
	are no longer implemented.

	The command manager suite maintains an association between command ids, their non-localized
	names and their localized names. Each menu command is assigned a command id and has a
	non-localized and localized names. These are registered and unregistered with the command manager
	as menu items are created and removed. For example, when a plugin menu item is registered
	it is assigned a command id and the menu item is registered with the command manager. */
typedef struct {

	/** Add a command. This adds an association between a command id, a name and a 
		localized name. */
	AIAPI AIErr (*AddCommand) (AICommandID commandID, const char *name, const char *localizedName);

	/** Given the non-localized name for a command, get the command id. */
	AIAPI AIErr (*GetCommandIDFromName) (const char *name, AICommandID *commandID);
	/** Given the localized name for a command, get the command id. */
	AIAPI AIErr (*GetCommandIDFromLocalizedName) (const char *localizedName, AICommandID *commandID);
	/** Given the command id get its non-localized name. */
	AIAPI AIErr (*GetCommandName) (AICommandID commandID, char *name);
	/** Given the command id get its localized name. */
	AIAPI AIErr (*GetCommandLocalizedName) (AICommandID commandID, char *localizedName);

	/** Not implemented */
	AIAPI AIErr (*TestFunctionKey) (int fkey, unsigned long admModifiers, AIBoolean *used);
	/** Not implemented */
	AIAPI AIErr (*SetActionFunctionKey) (int fkey, unsigned long admModifiers);
	/** Not implemented */
	AIAPI AIErr (*ClearActionFunctionKey) (int fkey, unsigned long admModifiers);

	/** Given a keyboard shortcut, retrieve the command id for the corresponding command.
		Assumes the keyboard shortcut is a valid shortcut for a command (ie. it has the
		kADMMenuKeyDownModifier). Returns kBadParameterErr if no command id exists for
		this shortcut. */
	AIAPI AIErr (*GetCommandIDFromShortCutKey) (int key, unsigned long admModifiers, AICommandID *commandID);

	AIAPI AIErr (*SearchCommandLocalizedName) (char *partialName, char *localizedName);

	/** Not implemented */
	AIAPI AIErr (*GetShortCutKeyFromCommandID) (AICommandID commandID, int context, int *key, unsigned long *admModifiers, int *represent);
	/** Not implemented */
	AIAPI AIErr (*SetShortCutKeyFromCommandID) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent);
	/** Not implemented */
	AIAPI AIErr (*DeleteShortCutKeyFromCommandID) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent);

	/** Not implemented */
	AIAPI AIErr (*GetShortCutKeyOfCommandEx) (AICommandID commandID, int context, char *commandStr, int *key, unsigned long *admModifiers, int *represent);
	/** Not implemented */
	AIAPI AIErr (*SetShortCutKeyOfCommandEx) (AICommandID commandID, int context, int key, unsigned long admModifiers, int represent,
												char *commandStr, char *localizedStr, SPPluginRef pluginRef);
	/** Not implemented */
	AIAPI AIErr (*DeleteShortCutKeyOfCommandEx) (AICommandID commandID, int context, char *commandStr, int key, unsigned long admModifiers, int represent);
	/** Not implemented */
	AIAPI AIErr (*GetCommandExFromShortCutKey) (int key, unsigned long admModifiers, int context, AICommandID *commandID,
												SPPluginRef *pluginRef, char *commandStr, int maxCommandStr, char *localizedStr, int maxLocalizedStr);

	/** Not implemented */
	AIAPI AIErr (*SetActionFunctionKeyEx) (int fkey, unsigned long admModifiers, char *commandStr);

	/** Not implemented */
	AIAPI AIErr (*CountCommands)(int *totalCommands);
	/** Not implemented */
	AIAPI AIErr (*GetNthCommandInfo)(int index, AICommandID *commandID, int *context, int *key, int *represent, unsigned long *admModifiers,
									SPPluginRef *pluginRef, char *commandStr, int maxCommandStr, char *localizedStr, int maxLocalizedStr);

	/** Remove the associations for the given command id. */
	AIAPI AIErr (*DeleteCommand) (AICommandID commandID);

} AICommandManagerSuite2;


#include "AIHeaderEnd.h"

#endif
