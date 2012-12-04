#ifndef __AI120AssetMgmt__
#define __AI120AssetMgmt__

/*
 *        Name:	AI120AssetMgmt.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Asset Management Suite.
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

#include "AIHeaderBegin.h"

/** @file AI120AssetMgmt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI120AssetMgmtSuite				kAIAssetMgmtSuite
#define kAIAssetMgmtSuiteVersion5			AIAPI_VERSION(5)
#define kAI120AssetMgmtSuiteVersion			kAIAssetMgmtSuiteVersion5
#define kAI120AssetMgmtVersion				kAIAsset120MgmtSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The asset managment suite is a suite that exposes some simple XMP metadata
    manipulation routines and the Adobe Version Cue(TM) functionalities. 
 */

typedef struct AI120AssetMgmtSuite {
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

	/** 
		@mimeType		- param to Update the "Format" property (MIME-type) of the XMP metadata for the current document.
		@managedURL		- URL of the file whose metadata is being updated.Is NULL for local(unmanaged) files.
							Updates "ManageTo" field of kXMP_NS_XMP_MM namespace.
		@preserveDocID	- This param if true ensures that a old DocumentID(128-bit  uuid) is retained
		in the XMP Packet, otherwise a new "DocumentID" is associated with(created in) XMP Packet.
		preserveDocID is generally set to true when a Document "Save" is done.
		preserveDocID may be set to false for the case of Document=>
		"Save As...","Save As Copy" and All Export operations. 
		The API is currently used only by Illustrator core and it updates AI document's XMP packet.
    */
	AIAPI AIErr (*UpdateDynamicMetadata) (const char *mimeType, const char* managedURL /* = NULL */, AIBoolean	preserveDocID);

	/** Progress callback for Adobe Version Cue(TM) related network operation. Legacy API for
        internal Illustrator use only. 
	    Return true to continue the operation, false to cancel. 
    */
	AIAPI AIBoolean (*Progress) ( ASInt32 bytesTransferred, ASInt32 contentLength,
								  char *server, char *uri, char *method,
								  char *contentType, const ai::FilePath &localFile);

	/** Create a new XMP session object given xmpIn buffer.  Use this object to manipulate xmp data.
		xmpIn is the input buffer containing xmp data, encoded in UTF-8.  If xmpIn is null, a session object is still created and can be used with SetProperty() API.
		Return error if out of memory.
	*/
	AIAPI AIErr (*CreateXMPSession) (const char *xmpIn , AIXMPSession* xmp);
	/** Dispose the xmp session object that was created from CreateXMPSession().*/
	AIAPI AIErr (*DisposeXMPSession) (AIXMPSession xmp);
	/** Return the size of this xmp session object.  Use this size to allocate memory before calling GetXMPSessionBuffer()*/
	AIAPI AIErr (*GetXMPSessionSize) (AIXMPSession xmp , int* xmpSize);
	/** Return the buffer of the xmp session object.  The buffer size should be enough and can be determined by GetXMPSessionSize().*/
	AIAPI AIErr (*GetXMPSessionBuffer) (AIXMPSession xmp , char *xmpOut);
	/** Get the size of a certain key.  
		Return error kNoSuchKey if key doesn't exist.*/
	AIAPI AIErr (*GetPropertySize) (AIXMPSession xmp, const char *nameSpace, const char* key, int* valueSize);
	/** Get the value if a given key.  Make sure to call GetPropertySize() to get the proper size of the returned value.*/
	AIAPI AIErr (*GetProperty) (AIXMPSession xmp, const char *nameSpace, const char* key , char* value);
	/** Set the value of a given key.*/
	AIAPI AIErr (*SetProperty) (AIXMPSession xmp, const char *nameSpace, const char* key , const char* value);
	/** Remove the given key from xmp data.*/
	AIAPI AIErr (*DeleteProperty) (AIXMPSession xmp, const char *nameSpace, const char* key);

	/** 
	1. Show FileInfo Dialog for a given XMP packet. Currently used by Stock-Photo.
	2. Memory to xmpOut is allocated by "SPBasic::AllocateBlock". Clients, Please use "SPBasic::FreeBlock" appropriately.
	3. If you do not want to get a copy of new updated XMP pass "xmpOut = NULL". In this case a read-only FileInfo dialog will be shown to user.
	4. This API does not check whether UserInteraction is turned on/off. So, Clients should do that at their end before calling this API.
	5. The dialogTitle (UTF-8 string) is typically the name of the artwork where the xmpIn is coming from. When NULL pointer is passed in,
	   the generic dialog title "File Info" will be used.
	*/
	AIAPI AIErr (*ShowMetadataDialog) (const char *xmpIn, char **xmpOut, const char *dialogTitle);

} AI120AssetMgmtSuite;

#include "AIHeaderEnd.h"


#endif
