#ifndef __AI100FileFormat__
#define __AI100FileFormat__

/*
 *        Name:	AI100FileFormat.h
 *   $Revision: 25 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 File Format Suite.
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

#include "AIFileFormat.h"

#include "AIHeaderBegin.h"

/** @file AI100FileFormat.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIFileFormatSuite			"AI File Format Suite"
#define kAIFileFormatSuiteVersion4		AIAPI_VERSION(4)	// In AI 6.0
#define kAIFileFormatSuiteVersion5		AIAPI_VERSION(5)	// In AI 7.0. reset back to 5 when shipping.
#define kAIFileFormatSuiteVersion6		AIAPI_VERSION(6)	// In AI 9.0
#define kAIFileFormatSuiteVersion7		AIAPI_VERSION(7)	// In AI 10.0



/*******************************************************************************
 **
 **	Suite
 **
 **/

/** version 4. In Illustrator 6.0. */
typedef struct AIFileFormatSuite4 {

	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData4 *data4, long options,
				AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, long *options );
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, long options );
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountFileFormats) ( long *count );
	AIAPI AIErr (*GetNthFileFormat) ( long n, AIFileFormatHandle *fileFormat );
} AIFileFormatSuite4;


/** version 5. In Illustrator 7.0. */
typedef struct AIFileFormatSuite5 {

	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, long options, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, long *options );
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, long options );
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountFileFormats) ( long *count );
	AIAPI AIErr (*GetNthFileFormat) ( long n, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, long options, AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumTypes, long *typeList );

	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ASInt32 numPairs, AICreatorTypePair *pairList, const char* extensions );
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumPairs, AICreatorTypePair *pairList );
} AIFileFormatSuite5;


/** version 6. In Illustrator 9.0. */
typedef struct AIFileFormatSuite6 {

	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, long options, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, long *options );
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, long options );
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountFileFormats) ( long *count );
	AIAPI AIErr (*GetNthFileFormat) ( long n, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, long options, AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumTypes, long *typeList );

	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ASInt32 numPairs, AICreatorTypePair *pairList, const char* extensions );
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumPairs, AICreatorTypePair *pairList );

	// options can be kFileFormatExport, kFileFormatWrite, or kFileFormatSequenceWrite
	AIAPI AIErr (*PutFile) (long options, const unsigned char *dlgTitle, SPPlatformFileSpecification *fileSpec, AIFileFormatHandle *fileFormat, ASBoolean *good);
	AIAPI AIErr (*SetFileFormatPriority) ( AIFileFormatHandle fileFormat, int priority );
} AIFileFormatSuite6;

/** version 7. In Illustrator 10.0 */
typedef struct AIFileFormatSuite7 {

	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, long options, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, long *options );
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, long options );
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountFileFormats) ( long *count );
	AIAPI AIErr (*GetNthFileFormat) ( long n, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, long options, AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumTypes, long *typeList );

	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ASInt32 numPairs, AICreatorTypePair *pairList, const char* extensions );
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumPairs, AICreatorTypePair *pairList );

	AIAPI AIErr (*PutFile) (long options, const unsigned char *dlgTitle, SPPlatformFileSpecification *fileSpec, AIFileFormatHandle *fileFormat, ASBoolean *good );

	AIAPI AIErr (*SetFileFormatPriority) ( AIFileFormatHandle fileFormat, int priority );
	
	AIAPI AIErr (*FindMatchingFileFormats) ( long options, const SPPlatformFileSpecification* file, long maxMatches, AIFileFormatHandle matchingFormats[], long* numMatches );
} AIFileFormatSuite7;


#include "AIHeaderEnd.h"


#endif
