#ifndef __AI110ObjectSet__
#define __AI110ObjectSet__

/*
 *        Name:	AI110ObjectSet.h
 *   $Revision: 17 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Pattern Fill Suite.
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

#include "AIObjectSet.h"

#include "AIHeaderBegin.h"

/** @file AI110ObjectSet.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110ObjectSetSuite			kAIObjectSetSuite
#define kAIObjectSetSuiteVersion1		AIAPI_VERSION(1)
#define kAI110ObjectSetSuiteVersion		kAIObjectSetSuiteVersion1
#define kAI110ObjectSetVersion			kAI110ObjectSetSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	Object sets provide a mechanism for attaching global information to a document. Their use is
	deprecated in favor of dictionaries. The document contains a dictionary where arbitrary information
	can be stored. See AIDocumentSuite::GetDictionary() and AIDocumentSuite::GetNonRecordedDictionary().
 */
typedef struct {

	AIAPI AIErr (*NewObjectSet) ( SPPluginRef self, unsigned char *name, AIObjectMap *map, AIObjectSetHandle *set );
	AIAPI AIErr (*CountObjectSets) ( long *count );
	AIAPI AIErr (*GetNthObjectSet) ( long n, AIObjectSetHandle *set );
	AIAPI AIErr (*GetObjectSetName) ( AIObjectSetHandle set, unsigned char *name );
	AIAPI AIErr (*GetObjectSetByName) ( unsigned char *name, AIObjectSetHandle *set );
	AIAPI AIErr (*GetObjectSetMap) ( AIObjectSetHandle set, AIObjectMap **map );
	AIAPI AIErr (*NewObject) ( AIObjectSetHandle setHandle, unsigned char *name, void *def, int defLen, AIObjectHandle *object);
	AIAPI AIErr (*DeleteObject) ( AIObjectSetHandle setHandle, AIObjectHandle object);
	AIAPI AIErr (*SetObjectInternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, void *data, long dataLen);
	AIAPI AIErr (*SetObjectExternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, char *data);
	AIAPI AIErr (*GetObjectInternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, void **data, long *dataLen);
	AIAPI AIErr (*GetObjectExternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, char **data);
	AIAPI AIErr (*CountObjects) ( AIObjectSetHandle setHandle, long *count);
	AIAPI AIErr (*GetNthObject) ( AIObjectSetHandle setHandle, long n, AIObjectHandle *object);
	AIAPI AIErr (*GetObjectName) ( AIObjectSetHandle setHandle, AIObjectHandle object, unsigned char *name);
	AIAPI AIErr (*SetObjectName) ( AIObjectSetHandle setHandle, AIObjectHandle object, unsigned char *name);
	AIAPI AIErr (*GetObjectByName) ( AIObjectSetHandle setHandle, unsigned char *name, AIObjectHandle *object);
	AIAPI AIErr (*NewObjectName) ( AIObjectSetHandle setHandle, char *name, int maxLen );
	AIAPI AIErr (*GetObjectDisplayName) ( char *name );
	AIAPI AIErr (*MarkObjectInUse) ( AIObjectSetHandle setHandle, AIObjectHandle object);
	AIAPI AIErr (*RetargetForCurrentDocument) ( AIObjectHandle object, AIObjectHandle *newObj );

} AI110ObjectSetSuite;


#include "AIHeaderEnd.h"


#endif
