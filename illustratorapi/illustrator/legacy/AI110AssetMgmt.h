#ifndef __AI110AssetMgmt__
#define __AI110AssetMgmt__

/*
 *        Name:	AI110AssetMgmt.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Asset Management Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "AIAssetMgmt.h"

/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI110AssetMgmt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110AssetMgmtSuite			kAIAssetMgmtSuite
#define kAIAssetMgmtSuiteVersion3		AIAPI_VERSION(3)
#define kAI110AssetMgmtSuiteVersion		kAIAssetMgmtSuiteVersion3
#define kAI110AssetMgmtVersion			kAI110AssetMgmtSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The asset managment suite is a suite that exposes some simple XMP metadata
    manipulation routines and the Adobe Version Cue(TM) functionalities. 
 */

struct AI110AssetMgmtSuite {
	/** Is Adobe Version Cue(TM) enabled?
    */
	AIAPI AIBoolean (*IsAssetMgmtEnabled)();

	/** Manipulate the input XMP metadata buffer: update the XMP property name/value pair
        as specified in the input XMP fields array, and creates a new XMP metadata buffer
        upon output. The caller is responsible for releasing the returned output buffer.
        For details on the XMP properties, please refer to "XMP Specification Version 1.6", 
        August 15, 2002, Adobe Systems Inc. See also AIDocumentSuite::GetDocumentXAP() and
        AIDocumentSuite::SetDocumentXAP() for getting and setting the XMP metadata buffer
        for the current document.
    */
	AIAPI AIErr (*UpdateDynamicMetadataFields) (const char *xapIn, 
												const AIXMPDataFieldMap *fields, const int length, 
												char **xapOut);

	/** Update the "Format" property (MIME-type) of the XMP metadata for the current document.
    */
	AIAPI AIErr (*UpdateDynamicMetadata) (const char *mimeType);

	/** Progress callback for Adobe Version Cue(TM) related network operation. Legacy API for
        internal Illustrator use only. 
	    Return true to continue the operation, false to cancel. 
    */
	AIAPI AIBoolean (*Progress) ( ASInt32 bytesTransferred, ASInt32 contentLength,
								  char *server, char *uri, char *method,
								  char *contentType, SPPlatformFileSpecification localFile);

};


#include "AIHeaderEnd.h"


#endif
