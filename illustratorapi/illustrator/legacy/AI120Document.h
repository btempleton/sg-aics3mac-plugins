#ifndef __AI120Document__
#define __AI120Document__

/*
 *        Name:	AI120Document.h
 *   $Revision: 25 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 12.0 Document Suite.
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

#include "AIDocument.h"

#include "AIHeaderBegin.h"

/** @file AIDocument.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentSuiteVersion9		AIAPI_VERSION(9)

// AI12 version
#define kAI120DocumentSuiteVersion		kAIDocumentSuiteVersion9
#define kAI120DocumentVersion			kAI120DocumentSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Use these functions to get and set information about the current document.

	Some functions are only applicable while reading a file format.
	Some are intended for use during a file format write, but can
	be used at any time.
	*/
typedef struct {

	/** Retrieves the file specification for the current document.
			@param file [out] A buffer in which to return the file specification.
		*/
	AIAPI AIErr (*GetDocumentFileSpecification) ( ai::FilePath &file );

	/** Retrieves the coordinates of the lower left corner of the imageable
		page, specified relative to the ruler origin..
			@param origin [out] A buffer in which to return the origin point.
		*/
	AIAPI AIErr (*GetDocumentPageOrigin) ( AIRealPoint *origin );

	/** Sets the coordinates of the lower left corner of the imageable
		page. The origin for artwork
		coordinates is not changed; affects only what is printed.
			@param origin The new imageable page origin, specified relative
				to the ruler origin.
		 */
	AIAPI AIErr (*SetDocumentPageOrigin) ( AIRealPoint *origin );

	/** Sets the ruler origin for the current document. Positive ruler values
		go the right and above the origin. Negative values go the left and below the
		origin,
			@param origin The new ruler origin, specified relative to the lower left
				of the artboard page, which is always (0,0).
		*/
	AIAPI AIErr (*SetDocumentRulerOrigin) ( AIRealPoint *origin );

	/** Retrieves the current unit of measurement, shown in the ruler and
		displayed in dialog boxes.
			@param units The new ruler unit, an \c #AIDocumentRulerUnitValue.
		*/
	AIAPI AIErr (*GetDocumentRulerUnits) ( short *units );

	/** Sets the current unit of measurement, shown in the ruler and
		displayed in dialog boxes. Can be used only when reading
		a document.
			@param units [out] A buffer in which to return the ruler unit,
			an \c #AIDocumentRulerUnitValue.
		*/
	AIAPI AIErr (*SetDocumentRulerUnits) ( short units );

	/** Unimplemented. */
	AIAPI AIErr (*GetDocumentCropBoxGroupHandle) ( AIArtHandle *cropHandle );

	/** Retrieves the current crop box, if defined. This is the size of the visible area of
		an EPS file.
			@param cropBox [out] A buffer in which to return the crop box.
		*/
	AIAPI AIErr (*GetDocumentCropBox) ( AIRealRect *cropBox );

	/** Sets the crop box for the current document.
			@param cropBox The new crop box.
		*/
	AIAPI AIErr (*SetDocumentCropBox) ( AIRealRect *cropBox );

	/** Retrieves the style of crop marks that are created by the Create Crop Marks command
		and filter. This is not a document setting; it is an application preference.
		In AI11 and later this no longer affects separations printing.
			@param cropStyle [out] A buffer in which to return the style.
		*/
	AIAPI AIErr (*GetDocumentCropStyle) ( AICropMarkStyle *cropStyle );

	/** Sets the style of crop marks that are created by the Create Crop Marks command
		and filter. This is not a document setting. It is an application preference.
		In AI11 and later this no longer affects separations printing. */
	AIAPI AIErr (*SetDocumentCropStyle) ( AICropMarkStyle cropStyle );

	/** Not implemented. */
	AIAPI AIErr (*GetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord *print );

	/** Not implemented. */
	AIAPI AIErr (*SetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord print );

	/** Retrieves information about the current document that is set through the
		document Setup dialog.
			@param setup [out] A buffer in which to return the setup information.
		*/
	AIAPI AIErr (*GetDocumentSetup) ( AIDocumentSetup *setup );

	/** Sets the document setup information, as set through the document Setup dialog.
		Can be used only when reading a document.
			@param setup A pointer to a structure containing the new setup information.
		*/
	AIAPI AIErr (*SetDocumentSetup) ( AIDocumentSetup *setup );

	/** Reports whether the document has been edited since it was last saved.
		When it has, the user is prompted to save the document before closing it.
			@param modified [out] A buffer in which to return true if the document has
				been modified.
		*/
	AIAPI AIErr (*GetDocumentModified) ( AIBoolean *modified );

	/** Sets the modification state of the current document. When a document is marked
		as modified, the user is prompted to save before closing it.
			@param modified True to mark the document as modified, false to mark it
				as unmodified.
		*/
	AIAPI AIErr (*SetDocumentModified) ( AIBoolean modified );

	/** Retrieves the file format to be used when saving the current document.
		By default, this is the format that opened the document
		or the latest native file format for a new document.
		If the user changes the file format from the Save As dialog, the new format
		is assigned to the document.
			@param fileFormat [out] A buffer in which to return the file format.
			@see \c #AIFileFormatSuite
		 */
	AIAPI AIErr (*GetDocumentFileFormat) ( AIFileFormatHandle *fileFormat );

	/** Sets the file format to be used when saving the current document.
			@param fileFormat The file format.
			@see \c #AIFileFormatSuite
		*/
	AIAPI AIErr (*SetDocumentFileFormat) ( AIFileFormatHandle fileFormat );

	/** Retrieves the block of user parameters associated with the current document's
		associated file format.
			@param parameters [out] A buffer in which to return the parameter block.
				This is a \c void* pointer. The actual format of the parameter block
				is determined by the file format.
			@see \c #AIFileFormatSuite
		*/
	AIAPI AIErr (*GetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters *parameters );

	/** Sets the block of user parameters associated with the current document's
		associated file format.
			@param parameters [out] A buffer in which to return the parameter block.
				This is a \c void* pointer. The actual format of the parameter block
				is determined by the file format. Use the \c #AIBlockSuite functions
				to allocate this memory, so that Illustrator can release it when
				it is no longer needed.
			@see \c #AIFileFormatSuite
		*/
	AIAPI AIErr (*SetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters parameters );

	/** Forces the current document to be redrawn. Illustrator automatically redraws
		the document when a plug-in returns, so this function is not usually needed.
		*/
	AIAPI AIErr (*RedrawDocument) ( void );

	/** Retrieves an opaque reference for the current document, to use with functions
		that can operate on documents other than the current one.
			@param document [out] A buffer in which to return the document reference.
		*/
	AIAPI AIErr (*GetDocument) ( AIDocumentHandle *document );

	/** Writes the current document to a file without modifying the document
		or changing its modification status.
			@param file The file specification.
			@param fileFormatName The file format name.
			@param askForParms When true, show a dialog to query user for file-format parameters.
				If no format parameters are available, the function queries the user even if this
				value is false.
	 		@see \c #WriteDocumentWithOptions()
	 	*/
	AIAPI AIErr (*WriteDocument) ( const ai::FilePath &file, const char *fileFormatName, ASBoolean askForParms);

	/**  Retrieves the print record for the current document.
			@param print [in, out] A print record with the \c version and \c recordSize
				members initialized, in which to return the print information.
		*/
	AIAPI AIErr (*GetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );

	/** Not implemented.*/
	AIAPI AIErr (*SetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );

	/** Retrieves the ruler origin for the current document. Positive ruler values
		go the right and above the origin. Negative values go the left and below the
		origin.
			@param origin [out] A buffer in which to return the ruler origin,
				relative to the lower left of the artboard page, which is always (0,0).
		*/
	AIAPI AIErr (*GetDocumentRulerOrigin) ( AIRealPoint *origin );

	/** Updates linked objects in the current document, if needed.
			@param updatedSomething [out] Optional. A buffer in which to
				return true if any links were found that needed update.
		*/
	AIAPI AIErr (*UpdateLinks) ( AIBoolean *updatedSomething );

	/** Retrieves the limits of zooming as scale factors.
			@param min [out] A buffer in which to return the minimum zoom scale factor.
			@param max [out] A buffer in which to return the maximum zoom scale factor.
		*/
	AIAPI AIErr (*GetDocumentZoomLimit) ( AIReal *min, AIReal *max );

	/** Retrieves the maximum bounds of the art board for the current document.
			@param bounds [out] A buffer in which to return a rectangle
				that would fit over the artwork board.
		*/
	AIAPI AIErr (*GetDocumentMaxArtboardBounds)( AIRealRect *bounds );

	/** Reports whether a document exists; that is, is an open document or a clipboard document.
			@param document The document reference.
			@param exists [out] A buffer in which to return true if the document
				is open or in the clipboard.
		*/
	AIAPI AIErr (*DocumentExists) ( AIDocumentHandle document, AIBoolean *exists );

	/** Retrieves the recorded dictionary associated with the current document.
		Changes in this dictionary and its contents are recorded in the undo history.

		Dictionaries are reference counted. You must call \c #AIDictionarySuite::Release()
		when you no longer need the reference.
			@param dictionary [out] A buffer in which to return a pointer to
				the dictionary reference.
			@see \c #GetNonRecordedDictionary()
		*/
	AIAPI AIErr (*GetDictionary) ( struct _AIDictionary** dictionary );

	/** Retrieves the document color model.
			@param colorModel [out] A buffer in which to return the color model,
				an \c #AIDocumentColorModelValue.
		*/
	AIAPI AIErr (*GetDocumentColorModel) ( short *colorModel);

	/** Sets the intended color model for documents upon load.
		Use when reading a file. This function does not convert artwork in
		the current document to the new model. After Illustrator reads
		a file, it processes artwork in the document to ensure it matches
		the model.
			@param colorModel The color model, an \c #AIDocumentColorModelValue.
		*/
	AIAPI AIErr (*SetDocumentColorModel) ( short colorModel);

	/** Retrieves the color calibration profiles for the current document.
			@param rgbProfile [out] A buffer in which to return the RGB profile or \c NULL.
			@param cmykProfile [out] A buffer in which to return the CMYK profile or \c NULL.
			@param grayProfile [out] A buffer in which to return the grayscale profile or \c NULL.
		*/
	AIAPI AIErr (*GetDocumentProfiles) ( AIColorProfile* rgbProfile, AIColorProfile *cmykProfile, AIColorProfile *grayProfile );

	/** Sets the color calibration profiles for the current document.
			@param rgbProfile The RGB profile. Can be \c NULL.
			@param cmykProfile The CMYK profile. Can be \c NULL.
			@param grayProfile The grayscale profile. Can be \c NULL.
		*/
	AIAPI AIErr (*SetDocumentProfiles) ( AIColorProfile rgbProfile, AIColorProfile cmykProfile, AIColorProfile grayProfile );

	/** Copies the currently selected objects to the clipboard. This is the same as
		the Copy menu command.
			@note Use only when this plug-in is issuing a command and is entirely
			in control of that command. Do not call when responding to messages
			invoked by other commands, such as save, close, update, and so on.
		 */
	AIAPI AIErr (*Copy) ();

	/** Cuts the currently selected objects to the clipboard. This is the same as
		the Cut menu command.
			@note Use only when this plug-in is issuing a command and is entirely
			in control of that command. Do not call when responding to messages
			invoked by other commands, such as save, close, update, and so on.
		*/
	AIAPI AIErr (*Cut) ();

	/** Pastes the contents of the clipboard into the document. This is the same as
		the Paste menu command.
			@note Use only when this plug-in is issuing a command and is entirely
			in control of that command. Do not call when responding to messages
			invoked by other commands, such as save, close, update, and so on.
		*/
	AIAPI AIErr (*Paste) ();

	/** Updates cached artwork properties. For example, the selection state
		of a group is cached, and is determined from the states of its children.
		You do not typically need to call this function. Illustrator recomputes
		cached properties as needed.
		*/
	AIAPI AIErr (*SyncDocument) ( void );

	/** Unimplemented. Always returns \c #kDocTargetExplicit */
	AIAPI AIErr (*GetDocumentTargeting) ( short *paintTarget, short *transparencyTarget, short *effectsTarget );
	/** Unimplemented. A no-op. */
	AIAPI AIErr (*SetDocumentTargeting) ( short paintTarget, short transparencyTarget, short effectsTarget );

	/** Retrieves the non-recorded dictionary associated with the current document.
		Changes to this dictionary and its contents are not recorded in the undo
		history.

		Dictionaries are reference counted. You must call \c #AIDictionarySuite::Release()
		when you no longer need the reference.
			@param dictionary [out] A buffer in which to return a pointer to
				the dictionary reference.
			@see \c #GetNonRecordedDictionary()
		*/
	AIAPI AIErr (*GetNonRecordedDictionary) ( struct _AIDictionary** dictionary );

	/** Retrieves the version of the Illustrator file format in which
		the current document was last saved. (Note that this function returns
		a constant value, not an error code.)
			@return The version number, an \c #AIVersion value, or 0 if the
				version is unknown or the file is not an AI file.
		 */
	AIAPI int (*GetAIVersion) ();

	/** Reports whether rendering the current document according to its current
		view settings requires any non-opqaue drawing operations.
			@param hasTransparency [out] A buffer in which to return true if the
				the document has transparency.
			@param detectOverprint When true, drawing an overprinted object
				is considered a non-opaque operation.
		*/
	AIAPI AIErr (*DocumentHasTransparency) ( AIBoolean *hasTransparency, AIBoolean detectOverprint );

	/** Reports whether rendering the current document according to its current
		view settings requires painting any spot colors.
			  @param hasSpotColorArt [out] A buffer in which to return true if the
				the document has art that uses spot colors.
		*/
	AIAPI AIErr (*DocumentHasSpotColorArt) ( AIBoolean *hasSpotColorArt );

	// New for AI 10

	/** Retrieves asset management information. Pass \c null for any parameter whose
		state you do not want to retrieve.
		 	@param managed [out] A buffer in which to return true if the file has an associated server URL.
			@param pNAlternates [out] A buffer in which to return the number
				of alternates for a document that is part of Version Cue project,
				or 0 if it is not part of a Version Cue project.
			@param checkedOut [out] A buffer in which to return true if the document is being
				managed by a version-control system and is currently checked out (that is,
				editable and locked by the current user).
			@param URL [out] A buffer in which to return the server URL of a managed file.
			@param canEdit Deprecated, pass \c null.
			@param fileType [out] A buffer in which to return the name of the plug-in
				used to open the current document, or to perform the last Save As operation.
		*/
	AIAPI AIErr (*GetDocumentAssetMgmtInfo) (AIBoolean *managed, ASInt32* pNAlternates, AIBoolean *checkedOut, const char **URL, AIBoolean *canEdit, char *fileType);

	/** Sets asset management information. Pass \c null for any parameter whose
		state you do not want to set.
		 	@param managed When true, the file has an associated server URL.
			@param checkedOut Deprecated, pass \c null.
			@param URL The server URL of a managed file.
			@param canEdit Deprecated, pass \c null.
		*/
	AIAPI AIErr (*SetDocumentAssetMgmtInfo) (AIBoolean *managed, AIBoolean *checkedOut, const char *URL, AIBoolean *canEdit);

	/**	Retrieves the URL associated with a document.
			@param document The document reference.
			@param URL [out] A buffer in which to return the URL.
		*/
	AIAPI AIErr (*GetDocumentURL)(AIDocumentHandle document, const char **URL);

	/** Retrieves the XMP metadata for the current the document.
			@param xap [out] A buffer in which to return the XML packet
				(in UTF-8 Unicode format).
		*/
	AIAPI AIErr (*GetDocumentXAP)(const char **xap);

	/** Sets the XMP metadata of the current document. Replaces any existing XMP metadata
			@param xap The new XML packet (must be in UTF-8 Unicode format). This is
				copied into the document, and can be deleted after the call.
		*/
	AIAPI AIErr (*SetDocumentXAP)(const char *xap);

	/** Halts any text reflow for all text objects in the current document.
		Match this call with a call to \c #ResumeTextReflow().

		If you manipulate \c #kTextFrameArt objects and do not need text reflow
		after each access, this speeds up the manipulation process.
		Some functions that causes text reflow are:  <br>
		\c #ATE::ITextRange::InsertAfter(), \c #ATE::ITextRange::InsertBefore()	<br>
		\c #ATE::ITextRange::SetLocalCharFeatures(), \c #ATE::ITextRange::SetLocalParaFeatures() <br>
		\c #ATE::ITextRange::Remove()

		@return The error \c #kNoDocumentErr if no document is open.
	*/
	AIAPI AIErr (*SuspendTextReflow)();

	/**  Resumes text reflow. Reflows any text objects that modified after the
		call to \c #SuspendTextReflow().
			@return The error \c #kNoDocumentErr if no document is open.
	*/
	AIAPI AIErr (*ResumeTextReflow)();

	/** Retrieves the text selection object for the current document.
		You must release the object when it is no longer needed.
		It is recommended that you use \c ITextRanges to wrap this object,
		which takes care of memory management. For example:
	@code
ATE::TextRangesRef selectionRef = NULL;
sAIDocument->GetTextSelection(&selectionRef);
{
	ITextRanges mySelection(selectionRef);
	...
}
	@endcode
		At this point \c selectionRef is released.The reference is invalid, and you must
		call \c #GetTextSelection() again to get a valid object.

		The text selection can describe multiple discontiguous ranges of text across multiple art objects.
		 \li If the document is in text editing mode, the result is a range representing the caret
		or the user selection.
		\li If the document is not in text editing mode, there are multiple ranges
		for the selected text frame objects.

			@param pTextSelection [out] A buffer in which to return the text selection object.
		*/
	AIAPI AIErr (*GetTextSelection)( TextRangesRef* pTextSelection );

	/** Reports whether the current document is in text editing mode.
		  @param focus [out] A buffer in which to return true if the document has the text focus.
		*/
	AIAPI AIErr (*HasTextFocus)( AIBoolean *focus);

	/** Reports whether the current document is in text editing mode and the caret
		is blinking (as opposed to a range of text being selected).
			@param caret [out] A buffer in which to return true if the document has
				the text focus and the caret is blinking.
		*/
	AIAPI AIErr (*HasTextCaret)( AIBoolean *caret);

	/** Retrieves the current story that is in editing mode.
		You must release the object when it is no longer needed.
		It is recommended that you use \c IStory to wrap this object,
		which takes care of memory management.
			@param pStory [out] A buffer in which to return the story object,
				or \c NULL if the current document is not in text editing mode.
		*/
	AIAPI AIErr (*GetTextFocus)( StoryRef* pStory);

	/** Sets a story to be in editing mode. The insertion point is positioned at the
		start of the story.
			@param story The story object.
		*/
	AIAPI AIErr (*SetTextFocus)( StoryRef story);

	/** Exits text editing mode. */
	AIAPI AIErr (*LoseTextFocus)();

	/** Retrieves the text resource object for the current document.
		You must release the object when it is no longer needed.
		It is recommended that you use \c IDocumentTextResource to wrap this object,
		which takes care of memory management.

	 	The document text resources object contains various document-wide
		utilities and objects such as the character and paragraph styles.

			@param pDocResources [out] A buffer in which to return the text resources object.
			@see \c ATE suites and \c IText.h.
		*/
	AIAPI AIErr (*GetDocumentTextResources)( DocumentTextResourcesRef* pDocResources);

	/** Attaches a thumbnail of the current document to the resources of the specified file. This
		is the thumbnail displayed in the Finder in Mac OS.
		NOTE: Deprecated as of AI13/CS3.  Now is a no-op.
			@param file The file.
		*/
	AIAPI AIErr (*WriteDocumentMacInformationResource)( const ai::FilePath &file );

	/** Writes the current document to a file with specified write options,
		without modifying the document or changing its modification status.
			@param file The file specification.
			@param fileFormatName The file format name.
			@param options The write options, a logical OR of \c #AIFileFormatOptions values.
			@param askForParms When true, show a dialog to query user for file-format parameters.
						If no format parameters are available, the function queries the user
						even if this value is false.
	 		@see \c #WriteDocument()
		*/
	AIAPI AIErr (*WriteDocumentWithOptions) (const ai::FilePath &file, const char *fileFormatName, long options, ASBoolean askForParms);

	/** Reports whether rendering the current document according to its current
		view settings requires painting any overprinted objects.
			@param hasOverprint [out] A buffer in which to return true if the
				the document has overprint.
		*/
	AIAPI AIErr (*DocumentHasOverprint)(AIBoolean *hasOverprint);

	/** Reports whether a document contains any managed links.
		A managed link is a URL to an Adobe Workgroup Server where
		one can share and keep versions of the linked document.
			@param document The document reference.
			@param hasManagedLinks [out] A buffer in which to return true if the document
				has managed links.
			@see \c #GetDocumentAssetMgmtInfo(), \c #GetDocumentURL()

        	@note In AI 10, only a managed document could have managed links. In later versions,
        	 non-managed documents can also have managed links.
        */
	AIAPI AIErr (*DocumentHasManagedLinks)(AIDocumentHandle document, AIBoolean *hasManagedLinks);

	/** Retrieves the spot color mode of a document, which controls the
		appearance definitions of new spot colors that are added to the document.
			@param document The document reference, or \c NULL for the current document.
			@param mode [out] A buffer in which to return the mode, an \c #AISpotColorMode value.
			@return The error \c #kNoDocumentErr if \c document is \c NULL and there is no
				current document.
		*/
	AIAPI AIErr (*GetDocumentSpotColorMode)(AIDocumentHandle document, AISpotColorMode *mode);

	/** Sets the spot color mode of a document, which controls the appearance
		definitions of new spot colors that are added to the document.
			@param document The document reference, or \c NULL for the current document.
			@param mode The new mode, an \c #AISpotColorMode value.
			@param convert When true, converts existing spot color definitions to the new mode.
			@param converted [out] Optional. A buffer inm which to return true if any colors
				were actually modified.
			@return The error \c #kNoDocumentErr if \c document is \c NULL and there is no
				current document.
		*/
	AIAPI AIErr (*SetDocumentSpotColorMode)(AIDocumentHandle document, AISpotColorMode mode,
			AIBoolean convert, AIBoolean* converted);

} AI120DocumentSuite;



#include "AIHeaderEnd.h"


#endif
