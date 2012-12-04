/*******************************************************************************
*
* ADMCustomResource.h -- ADM Custom Resource Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
********************************************************************************/

/** @file ADMCustomResource.h ADM Custom Resource Suite */

#ifndef __ADMCustomResource__
#define __ADMCustomResource__

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif

#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif

#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------
//	Predefined resource formats

/** Opaque reference to a developer-defined resource format. See \c #ADMCustomResourceSuite3 */
typedef struct ADMCustomResource* ADMCustomResourceRef;
/** Data type for types of developer-defined resource formats. One of:
	<br> \c #kADMDialogResource
	<br> \c #kADMStringResource
	<br> \c #kADMListResource
	<br> \c #kADMIconResource
	<br> \c #kASZStringDictionary
	<br> \c #kADMMixedResource
	*/
typedef const char* ADMResourceType;

/** Custom resource format type: A pre-defined dialog. */
#define kADMDialogResource 		"ADM Dialog Resource"
/**  Custom resource format type: A pre-defined string. Can be language-specific. */
#define kADMStringResource 		"ADM String Resource"
/** Custom resource format type: A pre-defined list. */
#define kADMListResource 		"ADM List Resource"
/** Custom resource format type: A pre-defined icon. */
#define kADMIconResource		"ADM Icon Resource"
/** Internal. Custom resource format type: A pre-defined Z-string dictionary. */
#define kASZStringDictionary	"ASZString Dictionary"
/** Custom resource format type: A composite resource, composed of sub-resources. */
#define kADMMixedResource		"ADM Mixed Resource"


// -----------------------------------------------------------------------------
//	Error codes

/** @ingroup Errors  See \c #ADMCustomResourceSuite3 */
#define kADMCustomResourceError 		'rErr'
/** @ingroup Errors See \c #ADMCustomResourceSuite3 */
#define kADMCustomResourceExistsError 	'!Unq'
/** @ingroup Errors See \c #ADMCustomResourceSuite3 */
#define kADMStreamUnavailableError 		'noSe'
/** @ingroup Errors See \c #ADMCustomResourceSuite3 */
#define kADMResourceNotFoundError		'r!fd'


// -----------------------------------------------------------------------------
//	PICA interface

/** @ingroup Callers Custom resource format caller.  See \c #ADMCustomResourceSuite3  */
#define kADMCustomResourceCaller "ADM Resource Caller"

	// for resource parsers
/** @ingroup Selectors
	Read a custom resource format. See \c #ADMCustomResourceSuite3 */
#define kADMReadSelector "ADM Read Resource"
/** @ingroup Selectors
	Reload a custom resource format. See \c #ADMCustomResourceSuite3 */
#define kADMReloadSelector "ADM Reload Resource"

	// for composite parsers
/** @ingroup Selectors
	Find a custom resource format. See \c #ADMCustomResourceSuite3 */
#define kADMFindSelector "ADM Find Resource"
/** @ingroup Selectors
	Read a sub-resource of a custom resource format.  See \c #ADMCustomResourceSuite3 */
#define kADMReadSubResourceSelector "ADM Read Subresource"


/** Message sent with \c #kADMCustomResourceCaller for a custom resource format event.  */
typedef struct
{
	/** The message data. */
	SPMessageData d;

	/** The resource format object.  */
	ADMCustomResourceRef resourceRef;
	/** The resource type.  */
	ADMResourceType resourceType;

	/** The defining plug-in. */
	SPPluginRef resourcePlugin;
	/** The resource identifier. */
	ADMInt32 resourceID;
	/** The resource name. */
	const char* resourceName;

	/** Error code. */
	SPErr error;
	/** Error data. */
	ADMInt32  errorData;
}
ADMCustomResourceBaseMessage;


// -----------------------------------------------------------------------------

/** Prototype for a memory allocation callback procedure for a custom
	resource loader. A composite resource parser can either create the object,
	or use this to return a block of data to be handled by another parser.
		@param inSize The number of bytes to allocate.
		@param outBlock [out] A buffer in which to return a pointer to the
			allocate block.
		@return An ADM error, \c #kNoErr on success.
	*/
typedef ADMErr ADMAPI ADMAllocateBlockProc(ADMInt32 inSize, void** outBlock);

/** A composite resource parser can either create the object,
	or return a block of data to be handled by another parser.
	This structure, returned in response to the \c #kADMCustomResourceCaller,
	contains the new object or block, and the associated resource data.
	*/
typedef struct
{

	/** For \c #kADMFindSelector and \c #kADMReadSubResourceSelector,
		the custom resource object that can parse the data. */
	ADMCustomResourceRef forCustomResource;

	/** The memory-allocation callback, to use when reading a subresource that
		must be parsed by some other resource format.  */
	ADMAllocateBlockProc* allocateBlock;

	/** A pointer to the developer-defined resource data, as registered for the format
		with \c #ADMCustomResourceSuite3::RegisterResourceData(). */
	void* returnedBlock;

	/** The number of bytes in the resource data. */
	ADMInt32 returnedSize;
}
ADMFoundResourceData;

/** Message sent with \c #kADMCustomResourceCaller for a custom resource format event. */
typedef struct
{
	/** The base message. */
	ADMCustomResourceBaseMessage r;

	/** A pointer to the callback object (such as \c #ADMDialogRef, \c #ADMIconRef).  */
	void* base;
	/** A pointer to a custom callback procedure (such as \c #ADMCustomDialogProcs, \c #ADMCustomIconProcs). */
	void* makeProc;

	/** For composite resources, the object or allocated block for the subresource. */
	ADMFoundResourceData subResource;
}
ADMCustomResourceMessage;


// -----------------------------------------------------------------------------
//	Dialog creation interface

/** Not used.  */
#define kADMDialogCanRelayoutOption (1L << 2)

/** Callback procedure prototype for a custom dialog resource (type \c #kADMDialogResource).
	Called when the dialog window is created.
		@param inDialog The dialog object.
		@param inDialogStyle The dialog-type constant.
		@param inDialogName The unique identifying name of the dialog.
		@return Nothing.
	*/
typedef void ADMAPI (*ADMMakeDialogWindowProc)(ADMDialogRef inDialog,
			ADMDialogStyle inDialogStyle, const char* inDialogName);

/** Callback procedure prototype for a custom dialog resource (type \c #kADMDialogResource).
	Called when the dialog is centered.
		@param inDialog The dialog object.
		@return Nothing.
 */
typedef void ADMAPI (*ADMCenterDialogWindowProc)(ADMDialogRef inDialog);

/** Callback procedure prototype for a custom dialog resource (type \c #kADMDialogResource).
	Retrieves developer-defined options from the dialog resource.
		@param inDialog The dialog object.
		@return The options flags, a logical OR of developer-defined option flag bits.
 */
typedef ADMInt32 ADMAPI (*ADMGetDialogOptionsProc)(ADMDialogRef inDialog);

/** Callback procedure prototype for a custom dialog resource (type \c #kADMDialogResource).
	Sets developer-defined options for the dialog resource.
		@param inDialog The dialog object.
		@param inOptions The options flags, a logical OR of developer-defined option flag bits.
		@return Nothing
 */
typedef void ADMAPI (*ADMSetDialogOptionsProc)(ADMDialogRef inDialog, ADMInt32 inOptions);


/** Callback procedures for a custom dialog resource (type \c #kADMDialogResource).  */
typedef struct
{
	/** Called when the dialog window is created. */
	ADMMakeDialogWindowProc makeDialogWindow;
	/** Called when the dialog is centered.  */
	ADMCenterDialogWindowProc centerDialogWindow;
	/** Called when the dialog options are set. */
	ADMSetDialogOptionsProc setDialogOptions;
	/** Called when the dialog options are accessed. */
	ADMGetDialogOptionsProc getDialogOptions;

}
ADMCustomDialogProcs;

/** Message sent with \c #kADMCustomResourceCaller for an event
	in a custom dialog resource (type \c #kADMDialogResource). */
typedef struct
{
	/** The base message. */
	ADMCustomResourceBaseMessage r;

	/** The dialog object. */
	ADMDialogRef createdDialog;
	/** The resource callback procedures.  */
	const ADMCustomDialogProcs* dialogProcs;

	/** For composite resources, the object or allocated block for the subresource.  */
	ADMFoundResourceData subResource;
}
ADMCustomDialogMessage;

/** Callback procedure prototype for a custom icon resource (type \c #kADMIconResource).
	Sets the image for the icon resource.
		@param inIcon The icon object.
		@param inImage The image object.
		@return Nothing
 */
typedef void ADMAPI (*ADMSetIconImageProc)(ADMIconRef inIcon, ADMImageRef inImage);

/** Callback procedure prototype for a custom icon resource (type \c #kADMIconResource).
	Retrieves the image for the icon resource.
		@param inIcon The icon object.
		@return The image object.
 	*/
typedef ADMItemRef ADMAPI (*ADMGetIconItemProc)(ADMIconRef inIcon);

/** Callback procedures for a custom icon resource (type \c #kADMIconResource).  */
typedef struct
{
	/** Sets the image for the icon. */
	ADMSetIconImageProc setImage;
	/** Sets \c #ADMCustomIconMessage::createdIcon. */
	ADMGetIconItemProc getItem;
}
ADMCustomIconProcs;

/** Message sent with \c #kADMCustomResourceCaller for an event
	in a custom icon resource (type \c #kADMIconResource).  */
typedef struct
{
	/** The base message. */
	ADMCustomResourceBaseMessage r;

	/** The icon object. */
	ADMIconRef createdIcon;
	/** The resource callback procedures. */
	const ADMCustomIconProcs* iconProcs;

	/** For composite resources, the object or allocated block for the subresource. */
	ADMFoundResourceData subResource;
}
ADMCustomIconMessage;

/** Callback procedure prototype for a custom list resource (type \c #kADMListResource).
	Reports whether this is a hierarchical or simple list.
		@return True if this is a hierarchical list, false if it is a simple list.
 	*/
typedef ADMBoolean ADMAPI (*ADMListTypeProc)();

/** Callback procedures for a custom list resource (type \c #kADMListResource). */
typedef struct
{
	/** Reports whether this is a hierarchical or simple list.  */
	ADMListTypeProc isHierarchical;
}
ADMCustomListProcs;


/** Message sent with \c #kADMCustomResourceCaller for an event
	in a custom list resource (type \c #kADMListResource). */
typedef struct
{
	/** The base message. */
	ADMCustomResourceBaseMessage r;

	/** The list object, either an \c #ADMListRef or \c #ADMHierarchyListRef. */
	ADMListRef createdList;
	/** The resource callback procedures. */
	const ADMCustomListProcs* listProcs;

	/** For composite resources, the object or allocated block for the subresource. */
	ADMFoundResourceData subResource;
}
ADMCustomListMessage;


// Custom resource options

/** Custom resource format option: when set, the resource is composite;
	that is, it contains subresources.Atomic resources readers have priority. */
#define kADMCompositeResourceFile (1L << 0)
/** Custom resource format option: when set, the resource is language-specific. */
#define kADMUseLanguageCodeForFileSearch (1L << 1)	// for language specific

/** Descriptive information about a custom resource format.
	See \c #ADMCustomResourceSuite3::AddCustomResource().*/
typedef struct
{
	/** Identifying name string. */
	const char* name;
	/** Version number. */
	ADMInt32 version;
	/** Type of format. */
	ADMInt32 kind;
	/** The file extension that identifies the format. */
	const char* extension;
	/** The option flags, a logical OR of \c #kADMCompositeResourceFile and
		\c #kADMUseLanguageCodeForFileSearch */
	ADMInt32 options;
}
ADMCustomResourceInfo;


/** The disk location of a custom resource format, together with developer-defined
	data registered for that format using \c #ADMCustomResourceSuite3::RegisterResourceData().
	See \c #ADMCustomResourceSuite3::FindAResource().*/
typedef struct
{
	/** The plug-in that defined the resource format. If supplied, the
		resource is one of the plug-in resources.  */
	SPPluginRef resourcePlugin;

	/** The file specification of the resource file. */
	SPPlatformFileSpecification resourceFile;

	/** A pointer to developer-defined data for a composite resource, associated with the
		resource format using \c #ADMCustomResourceSuite3::RegisterResourceData(). */
	void* resourceData;
	/** The number of bytes in the resource data. */
	ADMInt32 resourceSize;
}
ADMResourceLocationInfo;


// =============================================================================
//		* ADM Custom Resource Suite
// =============================================================================

/** Custom resource suite name */
#define kADMCustomResourceSuite			"ADM Custom Resource Suite"
/** Custom resource suite version */
#define kADMCustomResourceSuiteVersion3	3

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite allows you to define your own resource format. A custom resource
	can be language-specific, and can be \e atomic or \e composite--that is,
	composed of subresources. Atomic resource readers have priority.

	Your plug-in defines a set of callback functions that read and parse data
	in your format, to create pre-defined dialogs, lists, strings, or icons, or
	a mixture of these elements.

	The functions in this suite allow you to register your resource format, and
	allow you to find, query, and manipulate custom resources defined by other plug-ins.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMCustomResourceSuite and \c #kADMCustomResourceSuiteVersion3.
*/
typedef struct ADMCustomResourceSuite3
{
	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 10.

		// FIX_ME [scouten 08/04/99]: These function names would make more sense
		// if all instances of "CustomResource" were replaced with "ResourceFormat."
		// A future version of this suite will do that.

	/** Creates a custom resource format and adds it to the application's list of
		available formats.
			@param inPlugin This plug-in.
			@param inType The resource type constant.
			@param inResInfo An information structure that defines the new format.
			@param outFormat [out] A buffer in which to return the new custom resource
				format object.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*AddCustomResource)(SPPluginRef inPlugin, ADMResourceType inType,
				const ADMCustomResourceInfo* inResInfo,
				ADMCustomResourceRef* outFormat);

	/** Destroys a custom resource format and removes it from the application's list of
		available formats.
			@param inType The resource type constant.
			@param inName The unique identifying name of the resource format.
			@param inVersion The version number of the resource format.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*RemoveCustomResource)(ADMResourceType inType, const char* inName,
				ADMInt32 inVersion);

	/** Opens a data stream with which to read a custom resource format.
			@param inFormat The custom resource format object.
			@param inPlugin The plug-in that defined the resource format.
			@param inResID The unique identifier of the resource format.
			@param inResName The unique identifying name of the resource format.
			@param outResStream [out] A buffer in which to return a pointer to the new stream object.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*OpenResourceStream)(ADMCustomResourceRef inFormat, SPPluginRef inPlugin,
				ADMInt32 inResID, const char* inResName, AIDataFilter** outResStream);

	/** Closes a data stream opened with \c #OpenResourceStream().
			@param inResStream A pointer to the stream object.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*CloseResourceStream)(AIDataFilter* inResStream);

	/** Locates a data file in a custom resource format.
			@param inPlugin The plug-in that defined the resource format.
			@param inType The resource type constant.
			@param inResID The unique identifier of the resource format.
			@param inResName The unique identifying name of the resource format.
			@param outLocation [out] A buffer in which to return the file specification
				and related information.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*FindAResource)(SPPluginRef inPlugin, ADMResourceType inType,
				ADMInt32 inResID, const char* inResName, ADMResourceLocationInfo* outLocation);

	/** Returns the number of custom resource formats the application knows about.
		Use with \c #GetNthCustomResource() to iterate through custom formats.
			@param outCount [out] A buffer in which to return the number of formats.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*CountCustomResources)(ADMInt32* outCount);

	/** Retrieves a custom resource format by position index.
		Use with \c #CountCustomResources() to iterate through custom formats.
			@param inIndex The 0-based position index.
			@param outFormat [out] A buffer in which to return the custom resource format object.
			@return An ADM error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*GetNthCustomResource)(ADMInt32 inIndex, ADMCustomResourceRef* outFormat);

	/** Retrieves the plug-in that defined a custom resource format,
			@param inFormat The custom resource format object.
			@param outPlugin [out] A buffer in which to return the plug-in object.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetResourcePlugin)(ADMCustomResourceRef inFormat, SPPluginRef* outPlugin);

	/** Retrieves the information associated with a custom resource format,
			@param inFormat The custom resource format object.
			@param outInfo [out] A buffer in which to return the information structure.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetResourceInfo)(ADMCustomResourceRef inFormat, ADMCustomResourceInfo* outInfo);

	/** Retrieves the resource type of a custom resource format,
			@param inFormat The custom resource format object.
			@param outType [out] A buffer in which to return the type constant.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetResourceType)(ADMCustomResourceRef inFormat, ADMResourceType* outType);

	/** Retrieves a specific custom resource format.
			@param inResType The resource type constant.
			@param inResInfo An information structure that defines the format.
			@param outFormat [out] A buffer in which to return the custom resource format object.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*FindCustomResource)(ADMResourceType inResType,
				const ADMCustomResourceInfo* inResInfo,	ADMCustomResourceRef *outResource);

	/** Associates developer-defined data with a custom resource format.
		This data is returned by \c #FindAResource() in the \c #ADMResourceLocationInfo
		for a file that uses this format.
			@param inCustomResourceName	The unique identifying name of the resource format.
			@param inCustomResourceVersion The version number of the resource format.
			@param inPluginRef The plug-in that defined the resource format.
			@param inID	The unique identifier of the resource format.
			@param inData A pointer to the developer-defined data.
			@param inDataSize The number of bytes in the data.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*RegisterResourceData)(const char* inCustomResourceName,
										ADMInt32 inCustomResourceVersion,
										SPPluginRef inPluginRef, ADMInt32 inID,
										const char* inData, ADMInt32 inDataSize);

	/** Dissociates a custom resource format from any developer-defined data that
		was registered for it using \c #RegisterResourceData()
			@param inCustomResourceName	The unique identifying name of the resource format.
			@param inCustomResourceVersion The version number of the resource format.
			@param inPluginRef The plug-in that defined the resource format.
			@param inID	The unique identifier of the resource format.
			@return An ADM error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*UnregisterResourceData)(const char* inCustomResourceName,
										  ADMInt32 inCustomResourceVersion,
										  SPPluginRef inPluginRef, ADMInt32 inID);
}
ADMCustomResourceSuite3;

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMCustomResourceOld__
#ifdef MAC_ENV
#include "ADMCustomResourceOld.h"
#else
#include ".\Legacy\ADMCustomResourceOld.h"
#endif
#endif


#endif	// __ADMCustomResource__
