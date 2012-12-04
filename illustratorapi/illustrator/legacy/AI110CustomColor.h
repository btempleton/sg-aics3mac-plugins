#ifndef __AI110CustomColor__
#define __AI110CustomColor__

/*
 *        Name:	AI110CustomColor.h
 *   $Revision: 10 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Custom Color Fill Suite.
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

#include "AI110Color.h"
#include "AICustomColor.h"


#include "AIHeaderBegin.h"

/** @file AI110CustomColor.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110CustomColorSuite				"AI Custom Color Suite"
#define kAICustomColorSuiteVersion5			AIAPI_VERSION(5)
#define kAI110CustomColorVersion			kAICustomColorSuiteVersion5
#define kAI110CustomColorSuiteVersion		kAI110CustomColorVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Custom colors represent both spot colors and global process colors. The
	functions in this suite are used to access custom colors, allowing a plug-in to
	create, delete, and modify them.
	
	Note that the PostScript/PDF language has special meanings for the names
	All, None, Cyan, Magenta, Yellow and Black. These names cannot be used for
	spot colors. */
typedef struct {

	/** Make a new custom color. The color is not added to the swatch list. */
	AIAPI AIErr (*NewCustomColor) ( AI110CustomColor *color, AICustomColorHandle *customColor );
	/** Delete a custom color. This will delete it from the swatches palette if present
		and replace any usages by the process equivalent. */
	AIAPI AIErr (*DeleteCustomColor) ( AICustomColorHandle customColor );

	AIAPI AIErr (*GetCustomColor) ( AICustomColorHandle customColor, AI110CustomColor *color );
	AIAPI AIErr (*SetCustomColor) ( AICustomColorHandle customColor, AI110CustomColor *color );

	AIAPI AIErr (*CountCustomColors) ( long *count );
	AIAPI AIErr (*GetNthCustomColor) ( long n, AICustomColorHandle *customColor );
	AIAPI AIErr (*GetCustomColorByName) ( unsigned char *name,  AICustomColorHandle *customColor );
	/** Generates a unique name for a custom color. On input "name" should be the
		candidate name for the new custom color. On return it will have been modified
		if need be to ensure that it is unique. */
	AIAPI AIErr (*NewCustomColorName) ( char *name, int maxlen );
	/** This function is a no-op. An earlier version of Illustrator stored different names
		for custom colors internally from those displayed to the user. */
	AIAPI AIErr (*GetCustomColorDisplayName) ( char *name );

	AIAPI AIErr (*GetCurrentRegistrationColor) ( AICustomColorHandle *customColor );
	AIAPI AIErr (*NewRegistrationColor)(AICustomColorHandle *customColor, AIReal cyan /*red*/, AIReal magenta /*grgeen*/,AIReal yellow/*blue*/, 
		AIReal black, AI110CustomColorTag kind);
	
	/** Checks that the supplied custom color handle represents a valid custom
		color in the current document. */
	AIAPI AIBoolean (*ValidateCustomColor)(AICustomColorHandle customColor);
	/** Returns true if the custom color is a spot color that is used by a linked file.
		If this is the case it cannot be modified. */
	AIAPI AIBoolean (*HasExternalUses)(AICustomColorHandle customColor);

} AI110CustomColorSuite;


#include "AIHeaderEnd.h"


#endif
