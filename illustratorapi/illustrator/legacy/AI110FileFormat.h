#ifndef __AI110FileFormat__
#define __AI110FileFormat__

/*
 *        Name:	AI110FileFormat.h
 *   $Revision: 25 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator File Format Suite.
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

/** @file AI110FileFormat.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIFileFormatSuiteVersion8		AIAPI_VERSION(8)
#define kAI110FileFormatSuiteVersion	kAIFileFormatSuiteVersion8
#define kAI110FileFormatVersion			kAI110FileFormatSuiteVersion

/** @ingroup Selectors
	Sent to file format plugins. This is a request to update a linked object in
	the document. The data is an AI110UpdateFileFormatMessage. Note: A plug-in
	should handle only one of kAI110SelectorAIUpdateFileFormat or
	kSelectorAIUpdateFileFormat. */
#define kAI110SelectorAIUpdateFileFormat			"AI Update"

/*******************************************************************************
 **
 ** Types
 **
 **/

/** Message data sent by the file format selectors. */
struct AI110FileFormatMessage {
	SPMessageData d;
	/** Identifies the file format for which the message is intended. This can be
		compared against the format handle returned when the format was added. */
	AIFileFormatHandle fileFormat;
	/** The file to read, write or check. */
	SPPlatformFileSpecification file;
	/** The function the plug-in is to perform, (e.g. read or write). */
	long option;
	/** Additional information. Only used if the plugin indicated it supports
		extended data in its options when registering the format. */
	FileFormatExtData *m_pExtData;
	void *actionParm;
};

/** Message structure for kSelectorAIUpdateFileFormat */
struct AI110UpdateFileFormatMessage {
	struct AI110FileFormatMessage ffm;
	AIArtHandle art;
	void* data;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	Plug-in file formats give Illustrator the ability to read and write new file
	formats. File formats that read a format may be transparent to the user; files
	of their type simply appear in the open dialog. Your file format plug-in
	simply creates artwork in the Illustrator document. Writing file formats
	appear in the Save As dialog as an option for the user to select. These plugins
	walk the artwork tree and write out information on the artwork in the
	appropriate manner. If either needs more parameters, they can use a modal
	dialog to interact with the user.
 
	Plug-in File Formats are used to extend the number of file types Illustrator
	can read and write. Plug-ins tell Illustrator about the file formats they
	support by specifying platform file information: types (e.g 'ART3') under
	Mac OS and extensions (e.g '.AI') under Windows. Plug–ins also indicate
	what read/write capabilities they support.

	One plug-in can register multiple formats. Illustrator will handle parts of the
	file i/o process and have the plug-in do the remainder.
	
	A File Format plug–in receives message actions telling it to:
	
	- check if a file can be read,
	- ask for parameters, and
	- go.
	
	The check selector will only be received by file formats that can read files
	and extends the simple type checking done by the open dialog.
	
	The ask for parameters selector can be ignored if the plug-in does not need
	user input.
	
	The go selector is where the file format actually reads or writes a file.
	If a file format plug–in can read, files of its registered file type will appear in
	the file list of the open dialog. In addition to screening by file type, Illustrator
	will send a selector giving a plug-in a chance to check the file can be
	read. This is useful in the case of text files or files from a different computer.
	If more than one format matches the type, Illustrator will determine which
	should actually open the file, asking the user if necessary.

	If a file format plug–in supports reading and writing, when reading it should
	store any information about the file needed to write the file back to disk in
	the plug-in's globals or a parameter block (for example, the pixel depth of
	an EPS preview). The reference to the block should be attached to the document
	using the AIDocumentSuite::SetDocumentFileFormatParameters() function. Illustrator
	keeps this parameters reference with the document; the plug–in can retrieve
	it when the document is being saved.

	When the user does a Save, Illustrator will automatically default to the file
	format used to read in the file. If the file format does not support saving, the
	Save As... dialog will automatically appear to let the user chose the save format.
	All file format plug-ins that support saving will appear in the format menu of
	this dialog.

	If you need information from the user to open or save a file, you can present
	a dialog when the ask for parameters message is received. When saving files,
	this will be after the Save As dialog has appeared. This information should
	be kept with the document and used for later saves.

	When the go message is received, file formats that read files typically parse
	the input file and create Illustrator artwork using API calls. File formats for
	saving Illustrator artwork traverse the artwork database and write out all
	pertinent information.
*/
typedef struct AI110FileFormatSuite {

	/** Call this during startup to install a plug-in file format.

		- The SPPluginRef self is a reference to the plug-in adding the file format.
		- name is a C string identifying the added plug-in file format to Illustrator and
			other plug-ins. Using your company name and a descriptor is one way to
			make it unique. It isn’t displayed to the user and isn’t meant to be localized.
		- The options argument passed to the AddFileFormat function contains
			flags that specify the file format capabilities. When the format is called
			with a #kSelectorAIGoFileFormat selector, one of the flags will be set indicating
			the reason the file format was triggered. See #AIFileFormatOptions
		- The PlatformAddFileFormatData structure contains the information need to
			add the file format to Illustrator.
		- The AIFileFormatHandle returned is the installed plug-in file format. If
			you are installing multiple file formats, this reference must be stored in the
			plug-in’s globals record, as your plug-in will need it to determine which file
			format command is to be processed.
	*/
	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, long options, AIFileFormatHandle *fileFormat );

	/** Returns the a pointer to the name of the fileFormat. This is the name value
		originally passed to the AddFileFormat call. It should not be modified. */
	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );
	/** Use this to get the current options of a file format. */
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, long *options );
	/** Use this to set the current options of a file format. */
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, long options );
	/** This call will return a reference to the plug-in that installed the file format. */
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	/** The number of file formats available can be obtained using the count call. */
	AIAPI AIErr (*CountFileFormats) ( long *count );
	/** This call returns the AIFileFormatHandle at the specified zero based index. */
	AIAPI AIErr (*GetNthFileFormat) ( long n, AIFileFormatHandle *fileFormat );

	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );
	/** Adds a file format using an extended set of information. See AddFileFormat() for
		a description of the parameters. */
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, long options, AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumTypes, long *typeList );

	/** The parameters for AddFileFormat() and AddFileFormatEx() only allow for filtering
		Macintosh files based on their file type. This API allows a filter to be associated
		with a file format based on (creator, type) pairs. The Macintosh wild card value
		'****' can be used for creator or type. */
	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ASInt32 numPairs, AICreatorTypePair *pairList, const char* extensions );
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ASInt32 *maxNumPairs, AICreatorTypePair *pairList );

	/** Write the currrent document to the file using the specified format. Options can be kFileFormatExport,
		kFileFormatWrite, or kFileFormatSequenceWrite */
	AIAPI AIErr (*PutFile) (long options, const unsigned char *dlgTitle, SPPlatformFileSpecification *fileSpec, AIFileFormatHandle *fileFormat, ASBoolean *good );

	/** Specifies the priority of a file format. When searching for a file format to open a
		file Illustrator first looks through all file formats with priority #kAIFileFormatPriorityNative.
		If a format is found it is used to open the file. If no format is found it repeats the process
		with the next lower priority and so on. Note that only the specific priority values in
		#AIFileFormatPriority are checked. When a file format is added it is assigned the normal
		priority. */
	AIAPI AIErr (*SetFileFormatPriority) ( AIFileFormatHandle fileFormat, int priority );
	
	/** Searches for a file format that can perform the action indicated by the options for the
		specified file. All formats capable of performing the action are returned. */
	AIAPI AIErr (*FindMatchingFileFormats) ( long options, const SPPlatformFileSpecification* file, long maxMatches, AIFileFormatHandle matchingFormats[], long* numMatches );

	/** This API is only for use when importing artwork into an existing document (e.g place link
		or place embed). It will return an error at other times. When importing artwork the file
		format handler is requested to create it in an empty scratch document. The contents of
		the scratch document are then copied into the destination document.
		
		Conflicts may exist between global resources in the imported artwork and the destination
		document. For example both might contain objects that use a spot color with the same name
		but a different definition.
		
		This API should be called after the file format handler has finished importing the artwork
		from the file and before returning control to the caller. The API will resolve any conflicts
		between custom colors in the document and those in the artwork being imported. For each
		conflict it queries the conflict resolution policy and presents a dialog to the user if
		needed to decide how the conflict should be resolved. Note that the API may return kCanceledErr
		to indicate that the import operation is to be canceled.

		It is intended that the functionality performed by this API will be moved into the standard
		import handling code in a future version. At that time this API will become a no-op.
	*/
	AIAPI AIErr (*ResolveImportConflicts) ();
} AI110FileFormatSuite;

#include "AIHeaderEnd.h"


#endif
