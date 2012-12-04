#ifndef __AI110Placed__
#define __AI110Placed__

/*
 *        Name:	AI110Placed.h
 *   $Revision: 25 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 11.0 Placed Object Suite.
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

#include "AIPlaced.h"

#include "AIHeaderBegin.h"

/** @file AI110Placed.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPlacedSuiteVersion5		AIAPI_VERSION(5)
#define kAI110PlacedSuiteVersion	kAIPlacedSuiteVersion5
#define kAI110PlacedVersion			kAI110PlacedSuiteVersion

/*******************************************************************************
 **
 ** Types
 **
 **/
typedef struct AI110PlaceRequestData
{
	/** Determines type of place request */
	ASInt32 m_lPlaceMode;
	/** Art to be replaced */
	AIArtHandle m_hOldArt;
	/** Art just read from file */
	AIArtHandle m_hNewArt;
	SPPlatformFileSpecification *m_pSPFSSpec;
	/** Depends on place mode */
	ASInt32 m_lParam;
	/** Determines how the file is read */
	short m_filemethod;
	/** Disables the Template placing option */
	ASBoolean m_disableTemplate;
} AI110PlaceRequestData;

/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	Placed art is Adobe Illustrator's means of linking artwork contained in
	external files. For a file to be linked there must be a file format plugin
	installed that supports linking that format. For all file types except
	EPS a placed object is defined by its file specification, a matrix positioning
	the file content in the document and a group of art objects that represents
	the parsed contents of the file. EPS differs in that it does not have a
	group of art objects representing the parsed contents. When a file format is
	requested to link a file other than an EPS it does the following:

	- Creates a placed object for the linked file setting its file specification
		to reference the file.
	- Calls SetPlacedObject() to get a group that will contain the artwork
		representing the content of the linked file.
	- Reads the content of the linked file creating the artwork to represent
		the content.
	- Sets the matrix of the placed object as needed to position the content
		in the document.

	A plugin can determine whether a linked file is an EPS or not by using the
	GetPlacedType() API.

	Illustrator 10 added placement options to the properties of a placed object.
	These options affect how a linked object is positioned when it is used to
	replace another object and how a linked object is scaled. In the first case
	a new object is being placed into the bounds of an original object. In the
	second case you can think of the bounds of the original object as being
	scaled and then the object being placed into those bounds. The placement
	options provide control over how the object is modified to fit those bounds.
 */
struct AI110PlacedSuite {

	/** Returns the file specification identifying the linked file. If the linked file is
		missing then the file specification only supplies the file name. */
	AIAPI AIErr (*GetPlacedFileSpecification) ( AIArtHandle placed, SPPlatformFileSpecification *file );
	/** Set the file specification for the placed object to identify the linked file. If
		the file specification identifies an EPS then its contents are immediately parsed.
		If it identifies any other file type parsing of the file contents is deferred until
		specifically requested by AIArtSuite::UpdateArtworkLink() or AIDocumentSuite::UpdateLinks(). */
	AIAPI AIErr (*SetPlacedFileSpecification) ( AIArtHandle placed, SPPlatformFileSpecification *file );

	/** Get the matrix that positions the content of the linked file in the document. */
	AIAPI AIErr (*GetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );
	/** Set the matrix that positions the content of the linked file in the document. */
	AIAPI AIErr (*SetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );

	/** Get the bounding box of the bounding box of the content of the linked file. */
	AIAPI AIErr (*GetPlacedBoundingBox) ( AIArtHandle placed, AIRealRect *bbox );

	/** File format plugins call this API when reading the content of a linked file. The API
		returns a group to hold the parsed content of the file. Any previous contents are
		discarded. */
	AIAPI AIErr (*SetPlacedObject) ( AIArtHandle placed, AIArtHandle *group );

	/** Returns #kBadParameterErr if the linked file is not an EPS otherwise returns a count
		of the number of spot colors used by the EPS. */
	AIAPI AIErr (*CountPlacedCustomColors) ( AIArtHandle art, long *count );
	/** Returns #kBadParameterErr if the linked file is not an EPS otherwise returns the name
		of the Nth spot color used by the EPS. */
	AIAPI AIErr (*GetNthPlacedCustomColorName) ( AIArtHandle art, long num, char *name, int maxlen );

	/** Embeds the placed object into the document returning the embedded object. If
		askForParam is true then the embedding process is allowed to present dialogs
		asking for user input if needed. If false it must not request user input. */
	AIAPI AIErr (*MakePlacedObjectNative) ( AIArtHandle placed, AIArtHandle *native, ASBoolean askForParam );

	/** Get the type of the placed object. See #AIPlacedObjectType. */
	AIAPI AIErr (*GetPlacedType) ( AIArtHandle placed, short *pPlacedType );
	/** Returns #kBadParameterErr for a linked EPS otherwise returns the group of artwork
		representing the parsed content of the linked file. */
	AIAPI AIErr (*GetPlacedChild) ( AIArtHandle placed, AIArtHandle *group );

	/** Executes a place request. See AI110PlaceRequestData for details. */
	AIAPI AIErr (*ExecPlaceRequest)( AI110PlaceRequestData *pPlaceRequestData );

	/** The SPPlatformFileInfo contains information about the linked file such as the time
		it was created and last modified. The placed object stores the information from
		the time the file was last read. This API returns the file information stored with
		the placed object. It can be compared against the current information for the file
		itself to determine if the file has changed. */
	AIAPI AIErr (*GetPlacedFileInfoFromArt)( AIArtHandle placed, SPPlatformFileInfo *spFileInfo );
	/** The SPPlatformFileInfo contains information about the linked file such as the time
		it was created and last modified. This API returns the file information of the linked
		file itself. It can be compared against the information stored with the placed object
		to determine if the file has changed. */
	AIAPI AIErr (*GetPlacedFileInfoFromFile)( AIArtHandle placed, SPPlatformFileInfo *spFileInfo );
	/** Get the path specification for the placed object. A platform specific path is
		returned. */
	AIAPI AIErr (*GetPlacedFilePathFromArt)( AIArtHandle placed, char *pszPath, int iMaxLen );

	/** Post-concatenate a transformation onto the matrix applied to the placed object. */
	AIAPI AIErr (*ConcatPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *concat );

	// New for Illustrator 10

	/** Specify the placement options for the object. These options are used when the object
		is scaled or replaced by a new object. */
	AIAPI AIErr (*SetPlaceOptions) ( AIArtHandle placed, enum PlaceMethod method, enum PlaceAlignment alignment, ASBoolean clip );
	/** Get the placement options for the object. These options are used when the object
		is scaled or replaced by a new object. */
	AIAPI AIErr (*GetPlaceOptions) ( AIArtHandle placed, enum PlaceMethod *method, enum PlaceAlignment *alignment, ASBoolean *clip );
	/** */
	AIAPI AIErr (*GetPlacedDimensions) ( AIArtHandle placed, ASRealPoint *size, ASRealRect *viewBounds, AIRealMatrix *viewMatrix,
			ASRealRect *imageBounds, AIRealMatrix *imageMatrix );

};


#include "AIHeaderEnd.h"


#endif
