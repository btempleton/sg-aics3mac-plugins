#ifndef __AI110DocumentList__
#define __AI110DocumentList__

/*
 *        Name:	AIDocumentList.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Document Suite.
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


#include "AIDocumentList.h"

#include "AIHeaderBegin.h"

/** @file AIDocumentList.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentListSuiteVersion2		AIAPI_VERSION(2)
#define kAI110DocumentListSuiteVersion		kAIDocumentListSuiteVersion2
#define kAI110DocumentListVersion			kAI110DocumentListSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** The document list suite provides APIs that enumerate and operate on the list
	of open Illustrator documents.
	
	Most APIs do not take a document handle as a parameter. The plugin API has a
	notion of the "current" document and document view on which the APIs act. This
	is usually, but not always, the document and view of the active document window.
	The document list APIs make it possible to change the current document.

	Switching the current document or view commits any modifications that have been made.
	This means that an undo entry is added to the list of undoable operations, any
	deferred notifications are sent and the document windows are updated.
*/
typedef struct {

	/** Counts the number of open document windows. Note that there may be multiple windows
		open for a single document so this is not a count of the number of open documents. */
	AIAPI AIErr	(*Count)( long* count );
	/** Returns the document handle that identifies the document corresponding to the
		Nth open document window. The index is 0 based. */
	AIAPI AIErr	(*GetNthDocument)( AIDocumentHandle* document, long lIndex );
	/** Create a new document. A window for the new document is opened and becomes the
		frontmost document window. The plugin API switches the current document to be
		the new document. If any of the parameters colorMode, artboardWidth, artboardHeight
		are NULL default values are used. If dialogStatus is kDialogOn then the new document
		dialog will be shown. */
	AIAPI AIErr	(*New)( char* title, AIColorModel* colorMode, AIReal* artboardWidth, AIReal* artboardHeight,
						ActionDialogStatus dialogStatus, AIDocumentHandle* document );
	/** Open the indicated file. If the file is already open a new view will be opened
		for the document. If dialogStatus is not kDialogOn no user interaction is
		allowed to take place. The plugin API switches the current document and view
		to the newly opened document window.*/
	AIAPI AIErr	(*Open)( SPPlatformFileSpecification *fileSpec, AIColorModel colorMode, 
						ActionDialogStatus dialogStatus, AIDocumentHandle* document );
	/** Saves the current document. If the document has not been saved before the user
		will be prompted for a location and save options. */
	AIAPI AIErr	(*Save)( AIDocumentHandle document );
	/** Close a view for the specified document. If the document has only one open window
		this will close the document. The user will be prompted to save the document if
		it has been modified since last saved. The plugin API switches the current document
		to the active document window regardless of whether it was the current view that
		was closed. */
	AIAPI AIErr	(*Close)( AIDocumentHandle document );
	/** Close all open document windows. This is equivalent to invoking AIDocumentListSuite::Close()
		for each open window. */
	AIAPI AIErr	(*CloseAll)();
	/** The parameter bSetFocus must be true else this is a no-op. Activates a window
		for the specified document. The plugin API switches the current document and view
		to be those for the activated window. */
	AIAPI AIErr	(*Activate)( AIDocumentHandle document, ASBoolean bSetFocus );
	/** Print the specified document. */
	AIAPI AIErr	(*Print)( AIDocumentHandle document, ActionDialogStatus dialogStatus );

	// New in Illustrator 11.0

	/** Get the document handle for one of the startup documents. */
	AIAPI AIErr	(*GetStartupDocument)( AIDocumentHandle *startupDocument, AIStartupDocumentFlag flag );
	/** Make the specified startup document the current document for the plugin API.
		A plugin should not call any APIs that might attempt to modify the current
		document when it is set to the startup document. */
	AIAPI AIErr	(*ActivateStartupDocument)( AIDocumentHandle startupDocument );


} AI110DocumentListSuite;



#include "AIHeaderEnd.h"


#endif
