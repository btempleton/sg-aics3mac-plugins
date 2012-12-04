#ifndef __AI110Preference__
#define __AI110Preference__

/*
 *        Name:	AI110Preference.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Preference Suite.
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

#include "AIPreference.h"

#include "AIHeaderBegin.h"

/** @file AI110Preference.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPreferenceSuiteVersion2		AIAPI_VERSION(2)
#define kAIPreferenceSuiteVersion3		AIAPI_VERSION(3)
#define kAI110PreferenceSuiteVersion	kAIPreferenceSuiteVersion3
#define kAI110PreferenceVersion			kAI110PreferenceSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

struct AIPreferenceSuite2 {

	AIAPI AIErr (*GetBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean *value );
	AIAPI AIErr (*PutBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean value );
	AIAPI AIErr (*GetIntegerPreference) ( const char *prefix, const char *suffix, long *value );
	AIAPI AIErr (*PutIntegerPreference) ( const char *prefix, const char *suffix, long value );
	AIAPI AIErr (*GetRealPreference) ( const char *prefix, const char *suffix, double *value );
	AIAPI AIErr (*PutRealPreference) ( const char *prefix, const char *suffix, double value );
	AIAPI AIErr (*GetStringPreference) ( const char *prefix, const char *suffix, char *value );
	AIAPI AIErr (*PutStringPreference) ( const char *prefix, const char *suffix, const char *value );
	AIAPI AIErr (*GetBlockPreference) ( const char *prefix, const char *suffix, void *address, long size );
	AIAPI AIErr (*PutBlockPreference) ( const char *prefix, const char *suffix, void *address, long size );
	
	AIAPI AIErr (*GetFixedPreference) ( const char *prefix, const char *suffix, AIFixed *value );
	AIAPI AIErr (*PutFixedPreference) ( const char *prefix, const char *suffix, AIFixed value );
	AIAPI AIErr (*GetFractPreference) ( const char *prefix, const char *suffix, AIFract *value );
	AIAPI AIErr (*PutFractPreference) ( const char *prefix, const char *suffix, AIFract value );
	AIAPI AIErr (*GetPascalPreference) ( const char *prefix, const char *suffix, unsigned char *value );
	AIAPI AIErr (*PutPascalPreference) ( const char *prefix, const char *suffix, const unsigned char *value );
	AIAPI AIErr (*GetDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );
	AIAPI AIErr (*PutDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );
	
	AIAPI AIErr (*GetPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );
	AIAPI AIErr (*PutPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );
	AIAPI AIErr (*GetRectPreference) ( const char *prefix, const char *suffix, AIRect *value );
	AIAPI AIErr (*PutRectPreference) ( const char *prefix, const char *suffix, AIRect *value );
	AIAPI AIErr (*GetFileSpecificationPreference) ( const char *prefix, const char *suffix, SPPlatformFileSpecification *value );
	AIAPI AIErr (*PutFileSpecificationPreference) ( const char *prefix, const char *suffix, SPPlatformFileSpecification *value );

	AIAPI AIErr (*RemovePreference) ( const char *prefix, const char *suffix );

};


/** The Preference Suite allows you to store information in the Adobe Illustrator
	preferences file.

	The Preference Suite provides a cross-platform way to store your plug-in’s
	preferences. You can restore your preferences during startup, and save them
	during shutdown. The Preference Suite stores information in the Illustrator
	Preferences file.

	Each function in the suite takes three arguments:

	- a prefix, which is generally your plug–in’s name,
	- a suffix names a specific preference item in your plug–in, and
	- a value for the preference item.
	
	The Preference Suite supports a number of basic types: boolean, integer,
	real, C string, block, fixed, fract, Pascal string, date/time stamp, point, rect,
	and file spec. For each data type, the suite contains a Get and a Put function
	to read or write the corresponding value for a prefix/suffix pair.

	This example shows saving preferences for a window position and visibility
	status:

@code
	// save preferences for our dialog
	error = sPref->PutBooleanPreference( kPluginName, "dialogShowing", g->dialogShowing );
	error = sPref->PutPointPreference( kPluginName, "dialogPosition", &g->dialogPosition );
@endcode

	When you want to retrieve your preference info, use the corresponding Get
	calls. If a prefix/suffix pair isn't found in the preferences file, the third argument
	(value) will be unchanged. You should preset the default value for the
	preference you are retrieving.

@code
	//retrieve preferences for our dialog
	g->dialogShowing = false; // default is not visible
	error = sPref->GetBooleanPreference( kPluginName, "dialogShowing", &g->dialogShowing );
	g->dialogPosition = { 100 , 100 }; // default position
	error = sPref->GetPointPreference( kPluginName, "dialogPosition", &g->dialogPosition );
@endcode

	Generally, you read your prefs during the startup message action and write
	them at shutdown.

	You can get the current application preferences at any time. For instance,
	the constrain angle used by the Illustrator tools is an application preference.

	Note: The Illustrator preferences file is read once when the application is
	first launched and written once when the application quits. The Preference
	suite functions interact with the preferences stored in memory, not with the
	preferences file on disk.

	To get an application preference, use nil for the prefix. Use the paths
	derived from the preference file without the leading '/' to make the suffix.
	There is no direct way to determine the data type of an application preference,
	however, you should be able to determine the data type based on your
	knowledge of Illustrator and the appearance of the value in the preference
	file. For example:

	The following is from the preference file:

@code
	/constrain {
		/sin 0.0
		/cos 16.0
		/angle 0.0
	}
@endcode

	The values in this example indicate AIReal values. To retrieve the value of
	sin:

@code
	AIReal r;
	error = sPref->GetRealPreference( nil, "constrain/sin", &r );
@endcode

	The following is from the preference file:

@code
	/snapToPoint 1
@endcode

	This option is displayed as a checkbox in the General Preferences dialog,
	which suggests it is a boolean value. To get the snap to point setting:

@code
	AIBoolean snap;
	error = sPref->GetBooleanPreference( nil, "snapToPoint", &snap );
@endcode
*/
struct AI110PreferenceSuite {

	AIAPI AIErr (*GetBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean *value );
	AIAPI AIErr (*PutBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean value );
	AIAPI AIErr (*GetIntegerPreference) ( const char *prefix, const char *suffix, long *value );
	AIAPI AIErr (*PutIntegerPreference) ( const char *prefix, const char *suffix, long value );
	AIAPI AIErr (*GetRealPreference) ( const char *prefix, const char *suffix, double *value );
	AIAPI AIErr (*PutRealPreference) ( const char *prefix, const char *suffix, double value );
	AIAPI AIErr (*GetStringPreference) ( const char *prefix, const char *suffix, char *value );
	AIAPI AIErr (*PutStringPreference) ( const char *prefix, const char *suffix, const char *value );
	/** Since the preferences file is an ASCII text file that can be edited avoid using raw
		block data unless absolutely necessary. */
	AIAPI AIErr (*GetBlockPreference) ( const char *prefix, const char *suffix, void *address, long size );
	/** Since the preferences file is an ASCII text file that can be edited avoid using raw
		block data unless absolutely necessary. */
	AIAPI AIErr (*PutBlockPreference) ( const char *prefix, const char *suffix, void *address, long size );

	/** For compatibility with AI7 and earlier. */	
	AIAPI AIErr (*GetFixedPreference) ( const char *prefix, const char *suffix, AIFixed *value );
	/** For compatibility with AI7 and earlier. */	
	AIAPI AIErr (*PutFixedPreference) ( const char *prefix, const char *suffix, AIFixed value );
	/** For compatibility with AI7 and earlier. */	
	AIAPI AIErr (*GetFractPreference) ( const char *prefix, const char *suffix, AIFract *value );
	/** For compatibility with AI7 and earlier. */	
	AIAPI AIErr (*PutFractPreference) ( const char *prefix, const char *suffix, AIFract value );
	AIAPI AIErr (*GetPascalPreference) ( const char *prefix, const char *suffix, unsigned char *value );
	AIAPI AIErr (*PutPascalPreference) ( const char *prefix, const char *suffix, const unsigned char *value );
	AIAPI AIErr (*GetDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );
	AIAPI AIErr (*PutDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );
	
	AIAPI AIErr (*GetPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );
	AIAPI AIErr (*PutPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );
	AIAPI AIErr (*GetRectPreference) ( const char *prefix, const char *suffix, AIRect *value );
	AIAPI AIErr (*PutRectPreference) ( const char *prefix, const char *suffix, AIRect *value );
	AIAPI AIErr (*GetFileSpecificationPreference) ( const char *prefix, const char *suffix, SPPlatformFileSpecification *value );
	AIAPI AIErr (*PutFileSpecificationPreference) ( const char *prefix, const char *suffix, SPPlatformFileSpecification *value );

	AIAPI AIErr (*RemovePreference) ( const char *prefix, const char *suffix );

	AIAPI AIErr (*AddPreferencePanel) (SPPluginRef pluginRef, unsigned char *itemText, int dialogID, int options,
			AIPreferenceItemGroupHandle *prefItemGroup, AIMenuItemHandle *menuItem);
	AIAPI AIErr (*GetPreferencePanelItemRef) (AIPreferenceItemGroupHandle prefItemGroup, ADMItemRef *itemRef);
	AIAPI AIErr (*GetPreferencePanelBaseItemIndex) (AIPreferenceItemGroupHandle prefItemGroup, int *baseIndex);
	AIAPI AIErr (*ShowPreferencePanel) (AIPreferenceItemGroupHandle prefItemGroup);

};


#include "AIHeaderEnd.h"


#endif
