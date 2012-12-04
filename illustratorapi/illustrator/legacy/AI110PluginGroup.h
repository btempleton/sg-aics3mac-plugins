#ifndef __AI110PluginGroup__
#define __AI110PluginGroup__

/*
 *        Name:	AI110PluginGroup.h
 *     Purpose:	Adobe Illustrator 11.0 Plugin Group Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/** @file AI110PluginGroup.h */

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIPluginGroup.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110PluginGroupSuite			kAIPluginGroupSuite
#define kAI110PluginGroupSuiteVersion	AIAPI_VERSION(3)
#define kAI110PluginGroupVersion		kAI110PluginGroupSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

// Illustrator 11.0 PluginGroup suite
typedef struct _AI110PluginGroupSuite {

	AIAPI AIErr (*AddAIPluginGroup) ( SPPluginRef self, char *name, AIAddPluginGroupData *data, long options, 
									  AIPluginGroupHandle *entry );
	AIAPI AIErr (*UseAIPluginGroup) ( AIArtHandle art, AIPluginGroupHandle entry );

	AIAPI AIErr (*GetAIPluginGroupName) ( AIPluginGroupHandle entry, char **name );
	AIAPI AIErr (*GetAIPluginGroupVersion) ( AIPluginGroupHandle entry, long *major, long *minor );
	AIAPI AIErr (*GetAIPluginGroupDescription) ( AIPluginGroupHandle entry, char **desc );
	AIAPI AIErr (*GetAIPluginGroupOptions) ( AIPluginGroupHandle entry, long *options );
	AIAPI AIErr (*GetAIPluginGroupPlugin) ( AIPluginGroupHandle entry, SPPluginRef *plugin );

	AIAPI AIErr (*CountAIPluginGroups) ( long *count );
	AIAPI AIErr (*GetNthAIPluginGroup) ( long index, AIPluginGroupHandle *entry );

	AIAPI AIErr (*GetPluginArtName) ( AIArtHandle art, char **name );
	AIAPI AIErr (*SetPluginArtName) ( AIArtHandle art, char *name );
	AIAPI AIErr (*GetPluginArtVersion) ( AIArtHandle art, long *major, long *minor );
	AIAPI AIErr (*SetPluginArtVersion) ( AIArtHandle art, long major, long minor );
	AIAPI AIErr (*GetPluginArtPluginGroup) ( AIArtHandle art,  AIPluginGroupHandle *entry );
	AIAPI AIErr (*SetPluginArtPluginGroup) ( AIArtHandle art );
	AIAPI AIErr (*GetPluginArtEditArt) ( AIArtHandle art, AIArtHandle *editArt );
	AIAPI AIErr (*SetPluginArtEditArt) ( AIArtHandle art, AIArtHandle editArt );
	AIAPI AIErr (*GetPluginArtResultArt) ( AIArtHandle art, AIArtHandle *resultArt  );
	AIAPI AIErr (*SetPluginArtResultArt) ( AIArtHandle art, AIArtHandle resultArt  );

	AIAPI AIErr (*GetPluginArtDataCount) ( AIArtHandle art, unsigned long *count );
	AIAPI AIErr (*SetPluginArtDataCount) ( AIArtHandle art, unsigned long count );
	AIAPI AIErr (*GetPluginArtDataRange) ( AIArtHandle art, void *data, unsigned long index, unsigned long count );
	AIAPI AIErr (*SetPluginArtDataRange) ( AIArtHandle art, void *data, unsigned long index, unsigned long count );

	AIAPI AIErr (*MarkPluginArtDirty) ( AIArtHandle art );
	AIAPI AIErr (*MarkPluginArtClean) ( AIArtHandle art );

	// New for AI10

	AIAPI AIErr (*GetPluginArtClipping) ( AIArtHandle art, AIBoolean *clipping );
	AIAPI AIErr (*SetPluginArtClipping) ( AIArtHandle art, AIBoolean clipping );

	AIAPI AIErr (*GetAIPluginGroupDefaultName) ( AIPluginGroupHandle entry, char** name );
	AIAPI AIErr (*SetAIPluginGroupDefaultName) ( AIPluginGroupHandle entry, const char* name );

	AIAPI AIErr (*GetAIPluginGroupAppVersion) ( AIPluginGroupHandle entry, AIVersion* appVersion );
	AIAPI AIErr (*SetAIPluginGroupAppVersion) ( AIPluginGroupHandle entry, AIVersion appVersion );


} AI110PluginGroupSuite;


#include "AIHeaderEnd.h"

#endif

