#ifndef __AICommandManager__
#define __AICommandManager__

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

#include "AIUnicodeString.h"

#include "AIHeaderBegin.h"

/** @file AICommandManager.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAICommandManagerSuite			"AI Command Manager Suite"
#define kAICommandManagerSuiteVersion1	AIAPI_VERSION(1)
#define kAICommandManagerSuiteVersion2	AIAPI_VERSION(2)
#define kAICommandManagerSuiteVersion3	AIAPI_VERSION(3)
#define kAICommandManagerSuiteVersion	kAICommandManagerSuiteVersion3
#define kAICommandManagerVersion		kAICommandManagerSuiteVersion

/*******************************************************************************
 **
 **	Types
 **
 **/

/** @deprecated	Use \c #AIMenuSuite instead. */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** Command ID is always zero for plug-ins */
	AICommandID commandID;
	/** Keyboard shortcut key code. */
	int key;
	/** ADM style modifiers. */
	unsigned long admModifiers;
	/** Unique identifying name string for the command. */
	char *commandStr;
	/** Localized display label for the command. */
	char *localizedStr;
} AICommandMessage;

/*
 * PluginCommand Message
 */

/** @ingroup Callers
	Caller for deprecated \c #AICommandManagerSuite.
	@deprecated	Use \c #AIMenuSuite instead. */
#define kCallerAICommand					"Plugin Command Manager"
/** @ingroup Selectors
	Execute a \c #AICommandManagerSuite command.
	@deprecated	Use \c #AIMenuSuite instead. */
#define kSelectorAICommand					"Do Plugin Command"

/** @deprecated	Use \c #AIMenuSuite instead.  */
#define kAICommandNormalContext				0x0000
/** @deprecated	Use \c #AIMenuSuite instead.  */
#define kAICommandTextEditContext			0x0001
/** @deprecated	Use \c #AIMenuSuite instead.*/
#define kAICommandToolBoxContext			0x0002
/** @deprecated	Use \c #AIMenuSuite instead. */
#define kAICommandPluginContext				0x0004

/*******************************************************************************
 **
 **	Suite
 **
 **/

 /** @deprecated Use \c #AIMenuSuite instead.
 	This suite provides an older mechanism for manipulating Illustrator menu commands,
 	It is provided for compatibility, but has been superseded by
 	\c #AIMenuSuite. */

typedef struct {

	/** For internal use only. Creates a menu command.
			@param commandID The unique identifier for the command.
			@param name The unique identifying name string of the command.
			@param localizedName The localized display label for the command,
				which appears in the menu.
		*/
	AIAPI AIErr (*AddCommand) (AICommandID commandID, const char *name, const ai::UnicodeString& localizedName);

	/** Retrieves a command identifier from the name.
			@param name The unique identifying name string of the command.
			@param commandID [out] A buffer in which to return the ID.
		*/
	AIAPI AIErr (*GetCommandIDFromName) (const char *name, AICommandID *commandID);

	/** Retrieves a command identifier from the display label.
				@param localizedName The localized label string of the command.
				@param commandID [out] A buffer in which to return the ID.
		*/
	AIAPI AIErr (*GetCommandIDFromLocalizedName) (const ai::UnicodeString& localizedName, AICommandID *commandID);

	/** Retrieves a command name from the identifier.
			@param commandID  The command ID.
			@param name [out] A buffer in which to return the unique identifying
					name string.
		*/
	AIAPI AIErr (*GetCommandName) (AICommandID commandID, char *name);

	/** Retrieves a command display label from the identifier.
				@param commandID  The command ID.
				@param localizedName [out] A buffer in which to return the localized
						display label string.
		*/
	AIAPI AIErr (*GetCommandLocalizedName) (AICommandID commandID, ai::UnicodeString& localizedName);

	/** Not implemented */
	AIAPI AIErr (*TestFunctionKey) (int fkey, unsigned long admModifiers, AIBoolean *used);
	/** Not implemented */
	AIAPI AIErr (*SetActionFunctionKey) (int fkey, unsigned long admModifiers);
	/** Not implemented */
	AIAPI AIErr (*ClearActionFunctionKey) (int fkey, unsigned long admModifiers);

	/** Retrieves a command identifier from the keyboard shortcut.
			@param key The keyboard shortcut key code. See ADM documentation.
			@param admModifiers A logical OR of modifier key flags,
				such as \c #kADMMenuKeyDownModifier. See ADM documentation.
			@param commandID [out] A buffer in which to return the command ID.
			@return The error \c #kBadParameterErr if no command ID exists for
				this shortcut.
		*/
	AIAPI AIErr (*GetCommandIDFromShortCutKey) (int key, unsigned long admModifiers, AICommandID *commandID);

	/** Retrieves a command display label by matching a string containing a partial version
		of the name.
					@param partialName  The string to match.
					@param localizedName [out] A buffer in which to return the localized
							display label string of a command.
		*/
	AIAPI AIErr (*SearchCommandLocalizedName) (const ai::UnicodeString& partialName, ai::UnicodeString& localizedName);

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

	/**  For internal use only. Deletes a menu command.
			@param commandID The command identifier.
		*/
	AIAPI AIErr (*DeleteCommand) (AICommandID commandID);

} AICommandManagerSuite;

#include "AIHeaderEnd.h"

#endif
