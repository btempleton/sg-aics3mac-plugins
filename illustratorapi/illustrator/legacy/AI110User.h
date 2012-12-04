#ifndef __AI110User__
#define __AI110User__

/*
 *        Name: AI110User.h
 *   $Revision: 15 $
 *      Author:	 
 *        Date:	   
 *     Purpose: Adobe Illustrator 11.0 User Utilities Suite.	
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

#include "AIUser.h"

#include "AIHeaderBegin.h"

/** @file AI110User.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

// v.11.0
#define kAI110UserSuite				"AI User Suite"
#define kAIUserSuiteVersion6		AIAPI_VERSION(6)
#define kAI110UserSuiteVersion		kAIUserSuiteVersion6
#define kAI110UserVersion			kAI110UserSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** 
	AIUserSuite
*/
struct AI110UserSuite {

	AIAPI AIBoolean (*Cancel) ( void );
	AIAPI void (*UpdateProgress) ( long current, long max );
	AIAPI void (*SetProgressText) ( const char *text );
	AIAPI void (*CloseProgress) ( void );
	AIAPI void (*AIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*StringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*IUStringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToStringUnits) ( AIReal value, unsigned char *string );
	AIAPI void (*IUStringUnitsToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI AIErr (*GetUnitsString) ( short format, unsigned char *string );

	AIAPI AIErr (*AIUnitsToADMUnits) ( short aiUnits, ADMUnits *admUnits);
	AIAPI AIErr (*ADMUnitsToAIUnits) ( ADMUnits admUnits, short *aiUnits);
	AIAPI AIErr (*GetGlobalObjectDisplayName) ( char *name ); //name is modified in place
	
	/** Open the appropriate app to edit the object.  This is only meaningful for
	  Placed and Raster objects, and is equivalent to the user option-double-clicking
	  on the object with the selection tool.  See errors above. */
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	AIAPI AIErr (*AppIdle) ( void );

	AIAPI AIErr (*BuildDirectoryMenu) ( AIPlatformMenuHandle menu, SPPlatformFileSpecification *fileSpec);
	AIAPI AIErr (*GetIndexedDirectorySpec) ( SPPlatformFileSpecification *fileSpec, int index);
	AIAPI AIErr (*RevealTheFile) ( SPPlatformFileSpecification *fileSpec);
	
	AIAPI void (*DisableProgressCancel) ( void );

	AIAPI AIErr (*SPPlatformFileSpecification2Path) ( const SPPlatformFileSpecification *fileSpec, char *path );
	AIAPI AIErr (*Path2SPPlatformFileSpecification) ( const char *path, SPPlatformFileSpecification *fileSpec );

	/** This method should be called by plugins when a timer or other asynchronous event
		like updating triggers some action that may  allocate memory.  If it returns false,
		the plugin should reschedule the action and try again later.  It is not necessary to
		call this when handling notifications or user events; the plugin should never receive
		these when it's not ok to allocate memory. */
	AIAPI AIBoolean (*OKToAllocateMemory) ( void );

	// New for AI 11 
	AIAPI AIErr (*GetDateAndTime)(AIUserDateTime *ioValue);
	/* if ioValue is NULL, it will get current time. */
	AIAPI AIErr (*GetDateString)(const AIUserDateTime *ioValue, const int formatFlag, char *dateString);
	AIAPI AIErr (*GetTimeString)(const AIUserDateTime *ioValue, const int formatFlag, char *timeString);
	AIAPI AIErr (*GetYear)(const AIUserDateTime *ioValue, int *year);
	AIAPI AIErr (*GetMonth)(const AIUserDateTime *ioValue, int *month);
	AIAPI AIErr (*GetDay)(const AIUserDateTime *ioValue, int *day);
	AIAPI AIErr (*GetHour)(const AIUserDateTime *ioValue, int *hour);
	AIAPI AIErr (*GetMinute)(const AIUserDateTime *ioValue, int *minute);
	AIAPI AIErr (*GetSecond)(const AIUserDateTime *ioValue, int *second);
	AIAPI AIErr (*GetDayOfWeek)(const AIUserDateTime *ioValue, int *dayOfWeek);
	AIAPI AIErr (*LaunchApp)(SPPlatformFileSpecification *spFileSpec, ASBoolean openDoc);


	/** There are many collections of named entities. Examples are layers, swatches
		and styles. Illustrator has a standard set of rules governing automatic
		generation of names for such collections. This API can be used to manufacture
		the next name to use for a newly created object. The name  buffer must be at
		least AIAutoNameGenerator::maximumLength + 1 ASUnicode elements in size. Note
		that the AIAutoNameGenerator::nextNewNameIndex member of the is incremented. */
	AIAPI AIErr (*NextName) (AIAutoNameGenerator* set, ASUnicode* name);

	/** There are many collections of named entities. Examples are layers, swatches
		and styles. Illustrator has a standard set of rules governing automatic
		generation of names for such collections. This API can be used to manufacture
		a name for a copy of an existing object. The name  buffer must be at
		least AIAutoNameGenerator::maximumLength + 1 ASUnicode elements in size. */
    AIAPI AIErr (*CopyOfName) (AIAutoNameGenerator* set, const ASUnicode* original, ASUnicode* copy);

	/** There are many collections of named entities. Examples are layers, swatches
		and styles. Illustrator has a standard set of rules governing automatic
		generation of names for such collections. This API is to be used by the
		AIAutoNameGenerator::HasName() callback function to determine whether an automatically
		generated name matches a name in the collection. It may be, but does not need to be
		used to test for equality of user entered names. */
	AIAPI AIErr (*SameName) (const ASUnicode* name1, const ASUnicode* name2, AIBoolean* same);

};


#include "AIHeaderEnd.h"


#endif
