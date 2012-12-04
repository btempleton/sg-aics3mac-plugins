#ifndef __AIBackward__
#define __AIBackward__

/*
 *        Name:	AIBackward.h
 *   $Revision: 7 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Backward Compatibility.
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


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIBackwardSuite			"AI Backward Compatibility Suite"
#define kAIBackwardSuiteVersion		AIAPI_VERSION(2)
#define kAIBackwardVersion			kAIBackwardSuiteVersion


#define kPluginInterfaceVersion50	0x05000001
#define kPluginInterfaceVersion55	0x05010001
#define kPluginInterfaceVersion55J	0x05020001

enum {
	kSelectorPluginInterfaceVersion = 0,
	kSelectorPluginStartUp,
	kSelectorPluginAbout,

	kSelectorGetParameters,
	kSelectorGo,

	kSelectorUnused0,
	kSelectorUnused1,

	kSelectorFileFormatCheck
};


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef char **AIHandle;

typedef struct {

	void *functions;
	long interfaceVersion;

	short selector;
	short variation;

	AIHandle globals;
	AIHandle parameters;
	AIHandle message;

} AIEffect50;


typedef struct {

	void *functions;
	long interfaceVersion;

	short selector;
	void *globals;

} AIPluginPB55;


typedef struct {

	AIPluginPB55 plugin;

	AIHandle parameters;
	short variation;

} AIFilterPB55;


typedef struct {

	AIPluginPB55 plugin;

	AIHandle parameters;
	long capability;
	SPPlatformFileSpecification *file;
	short variation;

} AIFileFormatPB55;


/*******************************************************************************
 **
 ** Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*SetupAIEffect50) ( SPPluginRef plugin, AIEffect50 *pb );
	AIAPI AIErr (*EmptyAIEffect50) ( SPPluginRef plugin, AIEffect50 *pb );

	AIAPI AIErr (*SetupAIPluginPB55) ( SPPluginRef plugin, AIPluginPB55 *pb );
	AIAPI AIErr (*EmptyAIPluginPB55) ( SPPluginRef plugin, AIPluginPB55 *pb );

	AIAPI long (*CallPlugin50) ( SPPluginRef plugin, AIEffect50 *pb );
	AIAPI long (*CallPlugin55) ( SPPluginRef plugin, AIPluginPB55 *pb );

} AIBackwardSuite;


#include "AIHeaderEnd.h"


#endif
