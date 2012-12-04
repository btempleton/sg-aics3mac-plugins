#ifndef __AIDocumentList__
#define __AIDocumentList__

/*
 *        Name:	AIDocumentList.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Document Suite.
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

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif

#ifndef __AIUnicodeString__
#include "AIUnicodeString.h"
#endif

#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIDocumentList.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentListSuite			"AI Document List Suite"
#define kAIDocumentListSuiteVersion4	AIAPI_VERSION(5)

// latest version
#define kAIDocumentListSuiteVersion		kAIDocumentListSuiteVersion4
#define kAIDocumentListVersion			kAIDocumentListSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

/** @ingroup Errors See \c #kAIDocumentListSuite */
#define kCantCreateNewDocumentErr	'ENEW'

/** The document color model used when creating a new document or opening
	a document, set in \c #AINewDocumentPreset::docColorMode.*/
typedef enum
{
	kAIUnknownColorModel = -1,
	/** Grayscale (Unimplemented. If specified, an RGB document is created.) */
	kAIGrayColorModel = 0,
	/** RGB */
	kAIRGBColorModel,
	/** CMYK */
	kAICMYKColorModel
} AIColorModel;

/** @deprecated
	The startup documents that are used as templates
	for creating new documents. */
typedef enum
{
	/** Template for creating a new RGB color model document. */
	kAIRGBStartupDocument = 0,
	/** Template for creating a new CMYK color model document. */
	kAICMYKStartupDocument,
	/** Template defining the PDF portion of a native Illustrator file when saved
		without PDF compatibility. This usually contains some form of warning
		message. */
	kAINoPDFDataStartupDocument
} AIStartupDocumentFlag;

/** The preferred grid style for a new document,
	set in \c #AINewDocumentPreset::docTransparencyGrid.  */
typedef enum
{
	/** No grid */
	kAITransparencyGridNone = 0,
	/** Light gray lines */
	kAITransparencyGridLight,
	/** Medium gray lines */
	kAITransparencyGridMedium,
	/** Dark gray lines */
	kAITransparencyGridDark,
	/** Red lines */
	kAITransparencyGridRed,
	/** Orange lines */
	kAITransparencyGridOrange,
	/** Green lines */
	kAITransparencyGridGreen,
	/** Blue lines */
	kAITransparencyGridBlue,
	/** Purple lines */
	kAITransparencyGridPurple
} AITransparencyGrid;

/** The preferred preview mode for a new document,
	set in \c #AINewDocumentPreset::docPreviewMode.  */
typedef enum
{
	/* The default preview mode */
	kAIPreviewModeDefault = 0,
	/* Pixel preview mode */
	kAIPreviewModePixelPreview,
	/* Overprint preview mode */
	kAIPreviewModeOverprintPreview
} AIPreviewMode;

/** Raster resolution values for creating a new document,
	set in \c #AINewDocumentPreset::docRasterResolution.
	Values are in pixels-per-inch. This becomes the
	Raster Effect Settings value for the document. */
typedef enum
{
	/** Low or screen resolution, 72 PPI.  This is the default. */
	kAIRasterResolutionScreen = 0,
	/** Medium resolution, 150 PPI. */
	kAIRasterResolutionMedium,
	/** High resolution, 300 PPI. */
	kAIRasterResolutionHigh
} AIRasterResolution;


/**  Parameters for creating a new document with \c #AIDocumentListSuite::New(). */
typedef struct {
	/** The title of the new document. An empty string results in the default
		title, "Untitled \e nn". */
	ai::UnicodeString	docTitle;
	/** The width of the new document in document points. */
	AIReal				docWidth;
	/** The height of the new document in document points. */
	AIReal				docHeight;
	/** The color mode of the new document, an \c #AIColorModel value.  */
	AIColorModel		docColorMode;
	/** Ruler unit type for the new document. See \c #AIDocumentSuite::GetDocumentRulerUnits() */
	AIDocumentRulerUnitValue docUnits;
	/** The preview mode for the new document, an \c #AIPreviewMode value. */
	AIPreviewMode		docPreviewMode;
	/** The style of transparency grid for the new document, an \c #AITransparencyGrid value.  */
	AITransparencyGrid	docTransparencyGrid;
	/** The raster resolution for the new document, an \c AIRasterResolution value.  */
	AIRasterResolution	docRasterResolution;
} AINewDocumentPreset;



/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	These functions enumerate and operate on the list of open Illustrator documents.

	Many functions act on the current document and document view, which is
	usually, but not always, the document and view of the active document window.
	Use \c #Activate() to change the current document. Documents that you create
	or open become current.

	Switching the current document or view commits any modifications that have been made.
	This means that an undo entry is added to the list of undoable operations, any
	deferred notifications are sent, and the document windows are updated.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDocumentListSuite and \c #kAIDocumentListVersion.
*/
struct AIDocumentListSuite {

	/** Counts the number of open document windows. Multiple windows can be
		open for a single document, so this is not a count of the number of open
		documents. Use with \c #GetNthDocument() to retrieve documents.
			@param count [out] A buffer in which to return the number of windows.
		*/
	AIAPI AIErr	(*Count)( long* count );

	/** Retrieves a document by position index in the list of open document windows.
		Use with \c #Count() to iterate through windows.
			@param document	[out] A buffer in which to return the document reference.
			@param lIndex  The 0-based position index, in the range <code>[0..numWindows-1]</code>.
		*/
	AIAPI AIErr	(*GetNthDocument)( AIDocumentHandle* document, long lIndex );

	/** Creates a new document and makes it the current document, and opens a window
		for the new document, which becomes the	front most document window.
			@param preset (New in AICS3) The name of a startup preset to
				use when creating the new document. If empty or invalid, the function uses the
				startup template for the color mode specified in the \c parameter overrides.
				Preset names are those that appear in the New Document dialog.
				such as "Mobile", "Basic RGB", and so on.
			@param parameter (New in AICS3) The parameters for the new document. These values
				override those in the preset. When a parameter has a \c NULL value here,
				the function uses the value from the preset.
			@param dialogStatus An \c #ActionDialogStatus value. When \c #kDialogOn, shows the New
				dialog to query user for parameters.
		@param document [out] A buffer in which to return the document reference.
			@note The parameters for this function changed in Illustrator 13 (Creative Suite 3).
	*/
	AIAPI AIErr	(*New)( ai::UnicodeString& preset, AINewDocumentPreset *parameter, ActionDialogStatus dialogStatus, AIDocumentHandle* document );

	/** Opens a document from a file in a new window, and makes the new document and view current.
		If the document is already open, opens a new view for the document,
		and makes that document and view current.
			@param fileSpec The file.
			@param colorMode The color mode for the new document.
			@param dialogStatus An \c #ActionDialogStatus value. When \c #kDialogOn, shows the New
				dialog to query user for parameters. Otherwise, allows no user interaction.
			@param forceCopy When true, duplicates the file and names the copy "Untitled",
				regardless of whether it is marked as a template file.
			@param document [out] A buffer in which to return the document reference.
		*/
	AIAPI AIErr	(*Open)( const ai::FilePath &fileSpec, AIColorModel colorMode,
						ActionDialogStatus dialogStatus, AIBoolean forceCopy, AIDocumentHandle* document );

	/** Saves a document. If the document has not been saved before, prompts
		the user for a location and save options.
			@param document The document reference.
		*/
	AIAPI AIErr	(*Save)( AIDocumentHandle document );

	/** Closes a view for a document. If the document has only one open window,
		this closes the document. If the document has been modified since last saved.
		prompts the user to save.  Switches the current document
		to the active document window, regardless of whether it was the current view that
		was closed.
			@param document The document reference.
		*/
	AIAPI AIErr	(*Close)( AIDocumentHandle document );

	/** Closes all open document windows. This is equivalent to calling \c #Close()
		for each open window.
		*/
	AIAPI AIErr	(*CloseAll)();

	/** Activates a window for a document, and makes that document and view current.
			@param document The document reference.
			@param bSetFocus Must be true. If false, the function does nothing.
		*/
	AIAPI AIErr	(*Activate)( AIDocumentHandle document, ASBoolean bSetFocus );

	/** Prints a document.
			@param document The document reference.
			@param dialogStatus An \c #ActionDialogStatus value. When \c #kDialogOn, shows the
				Print dialog to query user for parameters.
		*/
	AIAPI AIErr	(*Print)( AIDocumentHandle document, ActionDialogStatus dialogStatus );

	// New in Illustrator 11.0

	/** Retrieves one of the startup template documents.
		   @param startupDocument [out] A buffer in which to return the document reference.
		   @param flag The document to retrieve, a \c #AIStartupDocumentFlag value.
		*/
	AIAPI AIErr	(*GetStartupDocument)( AIDocumentHandle *startupDocument, AIStartupDocumentFlag flag );

	/** Retrieves the preset settings from one of the startup template documents.
			@param preset The preset name. Preset names are those that appear in the
				New Document dialog. such as "Mobile", "Basic RGB", and so on.
			@param param [out] A buffer in which to return the settings.
		*/
	AIAPI AIErr	(*GetPresetSettings)( ai::UnicodeString &preset, AINewDocumentPreset *param );

	/** Makes one of the startup template documents the current document.
		    @param startupDocument The startup document reference, as returned by
				\c #GetStartupDocument().
			@note Do not modify the current document when it is set to a startup document.
				Use this function only to examine a startup template.
		*/
	AIAPI AIErr	(*ActivateStartupDocument)( AIDocumentHandle startupDocument );

	/**	Reports the number of recent documents. Use with \c #GetNthRecentDocument()
		to iterate through recent-documents list.
		(Note that this function returns a numeric value, not an error code.)
			@return The number of recent documents in the list.
		*/
	AIAPI ASInt32 (*CountRecentDocuments)();

	/**	Retrieves the location of a document from the recent-documents list.
		Use with \c #CountRecentDocuments() to iterate through recent-document list.
			@param index The 0-based position index of the document in the list.
			@param document [out] The path of the document.
		*/
	AIAPI AIErr (*GetNthRecentDocument)( ASInt32 index, ai::FilePath& document );

	/**	Open a document in the recent-documents list.
			@param index The 0-based position index of the document in the list.
		*/
	AIAPI AIErr (*OpenNthRecentDocument)( ASInt32 index );

};

#include "AIHeaderEnd.h"

#endif
