#ifndef __AI110Document__
#define __AI110Document__

/*
 *        Name:	AIDocument.h
 *   $Revision: 25 $
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

#define kAIDocumentSuiteVersion8		AIAPI_VERSION(8)

// AI11 version
#define kAI110DocumentSuiteVersion		kAIDocumentSuiteVersion8
#define kAI110DocumentVersion			kAI110DocumentSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Use the Document Suite to get and set information about the current document.

	Some of the suite’s functions are only applicable while reading a file format.
	Others make the most sense being used during a file format write, but can
	be used at any time. */
typedef struct {

	/** Get the file specification for the document. */
	AIAPI AIErr (*GetDocumentFileSpecification) ( SPPlatformFileSpecification *file );
	/** Returns the coordinates of the lower left hand coordinate of the imageable
		page. */
	AIAPI AIErr (*GetDocumentPageOrigin) ( AIRealPoint *origin );
	/** Sets the coordinates of the lower left hand coordinate of the imageable
		page to the supplied point.

		The origin is specified relative to the ruler origin. The origin for artwork
		coordinates is not changed; only what will be printed is affected. */
	AIAPI AIErr (*SetDocumentPageOrigin) ( AIRealPoint *origin );
	/** Establish the supplied point as the current ruler origin. To the right and
		above the origin will be positive ruler values. To the left and below the
		origin, the values will be negative.

		The origin is specified relative to the lower left of the artboard page. For
		this function, the origin of the artboard page does not change when the
		ruler origin is changed; it is always (0,0). */
	AIAPI AIErr (*SetDocumentRulerOrigin) ( AIRealPoint *origin );
	/** Returns the current units of measure. These are the units that are shown in
		the ruler and displayed in dialog boxes. See #AIDocumentRulerUnitValue */
	AIAPI AIErr (*GetDocumentRulerUnits) ( short *units );
	/** Sets the current units of measure. These are the units that are shown in
		the ruler and displayed in dialog boxes. Can only be used when reading
		a document. See #AIDocumentRulerUnitValue */
	AIAPI AIErr (*SetDocumentRulerUnits) ( short units );
	/** Unimplemented. */
	AIAPI AIErr (*GetDocumentCropBoxGroupHandle) ( AIArtHandle *cropHandle );
	/** Returns the current crop box if defined. This is the size of the visible area of
		an EPS file. */
	AIAPI AIErr (*GetDocumentCropBox) ( AIRealRect *cropBox );
	/** Set the crop box. */
	AIAPI AIErr (*SetDocumentCropBox) ( AIRealRect *cropBox );
	/** Gets the style of crop marks that are created by the Create Crop Marks command
		and filter. This is not a document setting. It is an application preference.
		In AI11 and later this no longer affects separations printing. */
	AIAPI AIErr (*GetDocumentCropStyle) ( AICropMarkStyle *cropStyle );
	/** Sets the style of crop marks that are created by the Create Crop Marks command
		and filter. This is not a document setting. It is an application preference.
		In AI11 and later this no longer affects separations printing. */
	AIAPI AIErr (*SetDocumentCropStyle) ( AICropMarkStyle cropStyle );
	/** Get the print record. */
	AIAPI AIErr (*GetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord *print );
	/** Set the print record. */
	AIAPI AIErr (*SetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord print );
	/** Retrieves information about the current document that is set through the
		document setup dialog. */
	AIAPI AIErr (*GetDocumentSetup) ( AIDocumentSetup *setup );
	/** Sets the document setup information to that in the record passed to it.
		Can only be used when reading a document. */
	AIAPI AIErr (*SetDocumentSetup) ( AIDocumentSetup *setup );
	/** Returns whether the document has been edited since it was last saved. If this is
		the case the user will be prompted to save the document before closing. */
	AIAPI AIErr (*GetDocumentModified) ( AIBoolean *modified );
	/** Sets whether the document should be considered to have been edited since it was
		last saved. If this is the case the user will be prompted to save the document
		before closing. */
	AIAPI AIErr (*SetDocumentModified) ( AIBoolean modified );
	/** A document has an associated file format to be used when saving. This function
		will return a handle to that file format. See the AIFileFormatSuite for more
		information about file formats.

		By default, the file format will be the format that opened the document or the
		latest native file format for a new document. If the user changes the file format
		from the save as dialog, the file format handle for the new format will be assigned
		to the document. */
	AIAPI AIErr (*GetDocumentFileFormat) ( AIFileFormatHandle *fileFormat );
	/** A document has an associated file format to be used when saving. This function
		sets the file format. See the AIFileFormatSuite for more information about file
		formats. */
	AIAPI AIErr (*SetDocumentFileFormat) ( AIFileFormatHandle fileFormat );
	/** A file format may have an associated block of user parameters. The format attaches
		its parameters to the document so that they may be retrieved when saving it. This call will
		return the parameters. The AIDocumentFileFormatParameters is just a typedef for a void*,
		the format of the parameter block is determined by the file format. */
	AIAPI AIErr (*GetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters *parameters );
	/** A file format may have an associated block of user parameters. The format attaches
		its parameters to the document so that they may be retrieved when saving it. This
		function disposes of the original parameter block and replaces them with the new
		one.

		The AIDocumentFileFormatParameters is just a typedef for a void *, the format
		of the parameter block is user defined.

		Note: You must use the Block Suite functions to allocate memory for file
		format parameters, since Illustrator will release the memory using
		the Block Suite’s DisposeBlock function. */
	AIAPI AIErr (*SetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters parameters );

	/** Use this to force the document to be redrawn. Illustrator automatically redraws
		the document when a plug-in returns, so there usually isn’t a need to use this
		function. */
	AIAPI AIErr (*RedrawDocument) ( void );

	/** Get an opaque identifier for the current document. This is useful in conjunction with
		APIs that can operate on documents other than the current one. */
	AIAPI AIErr (*GetDocument) ( AIDocumentHandle *document );
	
	/** Writes the document using the name passed into the function as file and
		the format fileFormatName without modifying the current open document.
		The document’s clean/dirty status will not be modified. If no file
		format parameters are available, the user will be asked for even if askForParms
		is false. See also WriteDocumentWithOptions() */
	AIAPI AIErr (*WriteDocument) (SPPlatformFileSpecification *file, char *fileFormatName, ASBoolean askForParms);

	/** Not implemented */
	AIAPI AIErr (*GetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );
	/** Not implemented */
	AIAPI AIErr (*SetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );

	/** Gets the document ruler origin. See SetDocumentRulerOrigin() for information about
		how the origin is specified. */
	AIAPI AIErr (*GetDocumentRulerOrigin) ( AIRealPoint *origin );
	
	/** Scans the document for linked objects that need to be updated. If it finds any
		it updates them and returns true in updatedSomething. The updatedSomething
		parameter is optional. */
	AIAPI AIErr (*UpdateLinks) ( AIBoolean *updatedSomething );

	/** Returns the limits of zooming as scale factors. */
	AIAPI AIErr (*GetDocumentZoomLimit) ( AIReal *min, AIReal *max );
	/** Use this to get the maximum bounds of the art board. It returns a AIRealRect
		that would fit over the artwork board. */
	AIAPI AIErr (*GetDocumentMaxArtboardBounds)( AIRealRect *bounds );
	/** Pass in a document Handle to see if the document exists. The document
		is considered to exist if it is an open document or a clipboard document. */
	AIAPI AIErr (*DocumentExists) ( AIDocumentHandle document, AIBoolean *exists );

	/** Returns the recorded dictionary associated with the document. Note that dictionaries
		are reference counted. You must call sAIDictionary->Release() when you're
		done with it. See the AIDictionarySuite for information about dictionaries. */
	AIAPI AIErr (*GetDictionary) ( struct _AIDictionary** dictionary );
	/** Returns the document color model. See #AIDocumentColorModelValue. */
	AIAPI AIErr (*GetDocumentColorModel) ( short *colorModel);
	/** Sets the document color model. This does not cause any artwork in the document that
		does not match the model to be converted to the new model. It is intended for use
		when reading a file to indicate the color model of the document. After a file is
		read the artwork it contains is processed to ensure it matches the model. See
		#AIDocumentColorModelValue. */
	AIAPI AIErr (*SetDocumentColorModel) ( short colorModel);
	/** Get the color calibration profiles for the current document. */
	AIAPI AIErr (*GetDocumentProfiles) ( AIColorProfile *rgbProfile, AIColorProfile *cmykProfile, AIColorProfile *grayProfile );
	/** Set the color calibration profiles for the current document. */
	AIAPI AIErr (*SetDocumentProfiles) ( AIColorProfile rgbProfile, AIColorProfile cmykProfile, AIColorProfile grayProfile );

	/** Copies the currently selected objects to the clipboard. This is identical to the
		copy command. Use this API at your own risk. There are strong constraints on how
		it must be used and it may be removed in the future. */
	AIAPI AIErr (*Copy) ();
	/** Cuts the currently selected objects to the clipboard. This is identical to the
		cut command. Use this API at your own risk. There are strong constraints on how
		it must be used and it may be removed in the future. */
	AIAPI AIErr (*Cut) ();
	/** Pastes the contents of the clipboard into the document. This is identical to the
		paste command. Use this API at your own risk. There are strong constraints on how
		it must be used and it may be removed in the future. */
	AIAPI AIErr (*Paste) ();
	
	/** Some artwork properties are cached and recomputed as needed. For example, the selection state
		of a group is determined from those of its children. This API ensures that all cached properties
		are correct. A plugin should not normally need to call this API since these cached values
		are recomputed as needed. */
	AIAPI AIErr (*SyncDocument) ( void );
	
	/** Unimplemented. Always returns kDocTargetExplicit */
	AIAPI AIErr (*GetDocumentTargeting) ( short *paintTarget, short *transparencyTarget, short *effectsTarget );
	/** Unimplemented. A no-op. */
	AIAPI AIErr (*SetDocumentTargeting) ( short paintTarget, short transparencyTarget, short effectsTarget );

	/** Returns the dictionary associated with the document for which changes to the
		dictionary and its contents will not be recorded for undo/redo purposes. You
		must call sAIDictionary->Release() when you're done with it. See the
		AIDictionarySuite for more information about dictionaries. */
	AIAPI AIErr (*GetNonRecordedDictionary) ( struct _AIDictionary** dictionary );
	
	/** Returns the Illustrator version of the current document. This is the version of the Illustrator
		file format the document was last saved as. If unknown, or not an AI file, returns 0. See
		#AIVersion for the version values. */
	AIAPI int (*GetAIVersion) ();

	/** Returns whether the rendering the document according to its current view settings involves
		any non-opqaue drawing operations. If detectOverprint is true then drawing an overprinted
		object will be treated as a non-opaque operation. */
	AIAPI AIErr (*DocumentHasTransparency) ( AIBoolean *hasTransparency, AIBoolean detectOverprint );
	/** Returns whether the rendering the document according to its current view settings involves
		painting any spot colors. */
	AIAPI AIErr (*DocumentHasSpotColorArt) ( AIBoolean *hasSpotColorArt );

	// New for AI 10

	/** Asset Management info
		Any unwanted parameter can be set to null to not "get" or "set" its state.
		
		- managed => file has associated server URL
		- checkedOut => Deprecated.
		- URL => if managed, URL of server version of file
		- canEdit => Deprecated.
		- fileType => name of plugin used to open document, or last "save as" of document */
	AIAPI AIErr (*GetDocumentAssetMgmtInfo) (AIBoolean *managed, AIBoolean *checkedOut, const char **URL, AIBoolean *canEdit, char *fileType);
	/** Set asset management info. See GetDocumentAssetMgmtInfo() for information about parameters */
	AIAPI AIErr (*SetDocumentAssetMgmtInfo) (AIBoolean *managed, AIBoolean *checkedOut, const char *URL, AIBoolean *canEdit);
	AIAPI AIErr (*GetDocumentURL)(AIDocumentHandle document, const char **URL);
	/** Returns a pointer to the xml packet associated with the document XAP data. The format is UTF-8
		unicode */
	AIAPI AIErr (*GetDocumentXAP)(const char **xap);
	/** Remove any existing XAP data and assign this xml XAP packet to the document. Format must be UTF-8
		unicode. */
	AIAPI AIErr (*SetDocumentXAP)(const char *xap);

	/**  Halts any text reflow for all text objects in this document .  
	If you manipulate kTextFrameArt objects and you don't need any text reflow 
	after each access, you should call this API to speed up the manipulate process.  
	For example, APIs that causes text reflow are:- ATE::ITextRange::InsertAfter(), ATE::ITextRange::InsertBefore()
	ATE::ITextRange::SetLocalCharFeatures(), ATE::ITextRange::SetLocalParaFeatures(), ATE::ITextRange::Remove() etc...
	Make sure to match it with ResumeTextReflow() API.
	Return error if there is no document open. 
	*/
	AIAPI AIErr (*SuspendTextReflow)();
	/**  Resume any text reflow.  Calling it will reflow any text objects that were suspended using SuspendTextReflow() API.
	Return error if there is no document open. 
	*/
	AIAPI AIErr (*ResumeTextReflow)();
	
	/** Returns text selection object for the current document. You must release the object after finished
		working with it. It is recommended to use ITextRanges to wrap this object, in this case you will
		not worry about releasing it.
		Example:
			ATE::TextRangesRef selectionRef = NULL;
			sAIDocument->GetTextSelection(&selectionRef);
			{
				ITextRanges mySelection(selectionRef);
				...
			}// at this point selectionRef is released.  You can't use it anymore, you have to call sAIDocument->GetTextSelection to get a valid object.
		The text selection can describe multiple discontiguous ranges of text across multiple art objects.
		If the document is in text editing mode, then the result with be a range representing the caret
		or the user selection. If the document is not in text editing mode there will be multiple ranges
		for the selected text frame objects. */
	AIAPI AIErr (*GetTextSelection)( TextRangesRef* pTextSelection );
	/** Returns whether the current document is in text editing mode. */
	AIAPI AIErr (*HasTextFocus)( AIBoolean *focus);
	/** Returns whether the current document is in text editing mode and the caret is blinking as
		opposed to a range of text being selected. */
	AIAPI AIErr (*HasTextCaret)( AIBoolean *caret);
	/** Returns if the current story that is in editing mode. You must release the object after finished
		working with it. It is recommended to use IStory to wrap this object, in this case you will
		not worry about releasing it. Returns an error if not in text editing mode. */
	AIAPI AIErr (*GetTextFocus)( StoryRef* pStory);
	/** Sets this story to be in editing mode. The insertion point is positioned at the
		start of the story. */
	AIAPI AIErr (*SetTextFocus)( StoryRef story);
	/** Exit text editing mode. */
	AIAPI AIErr (*LoseTextFocus)();
	/** Gets you DocumentTextResource object. You must release the object after finish working with it.
		It is recommended to use IDocumentTextResource to wrap this object, in this case you will not
		worry about releasing it. The document text resources object contains various document wide
		utilities and objects such as the character and paragraph styles. See the ATE APIs, IText.h, for
		more information. */
	AIAPI AIErr (*GetDocumentTextResources)( DocumentTextResourcesRef* pDocResources);

	/** Attaches a thumbnail of the current document to the resources of the specified file. This
		is the thumbnail displayed in the Finder on the Macintosh. */
	AIAPI AIErr (*WriteDocumentMacInformationResource)( SPPlatformFileSpecification *spFileSpec );
	/** Writes the document using the name passed into the function as file and
		the format fileFormatName without modifying the current open document.
		The document’s clean/dirty status will not be modified. If no file
		format parameters are available, the user will be asked for even if askForParms
		is false. The options parameter is a set of file format flags as defined in the
		AIFileFormatSuite. See also WriteDocument() */
	AIAPI AIErr (*WriteDocumentWithOptions) (SPPlatformFileSpecification *file, char *fileFormatName, long options, ASBoolean askForParms);
	/** Returns whether the rendering the document according to its current view settings involves
		painting any overprinted objects. */
	AIAPI AIErr (*DocumentHasOverprint)(AIBoolean *hasOverprint);

	/** Returns whether the document contains any managed links. A managed link is an URL to an Adobe Workgroup 
        Server where one can share and keep versions of the linked document. See also GetDocumentAssetMgmtInfo(). 
        In AI 10, a document can not have managed links unless itself is managed. In AI 11, such constraint is 
        elliminated. So you can have a non-managed document that contains managed links. This API along with the 
        GetDocumentURL() can give you the complete information. */
	AIAPI AIErr (*DocumentHasManagedLinks)(AIDocumentHandle document, AIBoolean *hasManagedLinks);

} AI110DocumentSuite;



#include "AIHeaderEnd.h"


#endif
