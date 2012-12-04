#ifndef __AI120Raster__
#define __AI120Raster__

/*
 *        Name:	AI120Raster.h
 *   $Revision: 24 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Raster Object Suite.
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

#include "AIRaster.h"


#include "AIHeaderBegin.h"

/** @file AI120Raster.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIRasterSuiteVersion6		AIAPI_VERSION(6)
#define kAI120RasterSuiteVersion	kAIRasterSuiteVersion6
#define kAI120RasterVersion			kAI120RasterSuiteVersion


/** Maximum number of channels per image pixel */
#define kAI120MaxChannels  16

typedef struct AI120Tile {
	/** A pointer to the memory containing the local copy of the pixels. It can be an
		generic block of memory or a platform specific data structure. In any case it
		must be allocated by the plug-in. */
	void		*data;
	/** The bounds field of the tile is the rectangle containing the pixel map, but
		also contains the depth information of the slice. */
	AISlice		bounds;
	/** Specifies the number of bytes in a row of pixel data. */
	long		rowBytes;
	/** The number of bytes used to specify a single pixel. For a raw RGB pixel, it
		would be 3. */
	long		colBytes;
	/** Indicates whether the tile is to receive the pixel data in a chunky mode (all
		color data for a single pixel together) or seperated into planes (all data for
		a color component together). If planeBytes is 0, the pixel data is chunky. If
		it is non-zero, the pixel information is in a planar form and the value is the
		number of bytes making up a single plane. For instance if pixel map were 80 by
		80 pixels and the RGB data were in a planar form, the value of planeBytes would
		be 6400. */
	long		planeBytes;
	/** The channelInterleave array and the slice information specify changes in the
		order of the bytes making up a pixel when transfering between a raster
		object and the tile's data. See the description of the AITile structure for
		more information. */
	short		channelInterleave[kAI120MaxChannels];
} AI120Tile;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The Raster Suite enables you to access and modify the data associated with
	an art object of type #kRasterArt.

	The functions allow you to work with the art as an object, for instance by
	getting and setting its transformation matrix, or at a pixel level by using the
	get and set tile functions.

	The suite is used in conjunction with at least one additional suite for
	accessing or creating the raster art object reference (the AIArtSuite, the
	AIMatchingArtSuite, or the AIArtSetSuite).

	A raster object is defined by its pixel data and a matrix that positions the
	pixel data in the document. The configuration of the pixel data is defined
	by its AIRasterRecord.

	The bounds of the raster object are initialized to zero when the AIArtSuite::NewArt()
	API is first used to create a raster art object. They should be set to the rectangle
	containing the pixel map using the SetRasterInfo call. This is not necessarily the
	same rectangle as the artwork bounds, which Illustrator will calculate and provide.
	The origin of a raster object is in the top left corner. This means that the coordinate
	system used by a raster object is inverted on the vertical axis compared to the
	Illustrator artboard coordinate system.

	All pixel data in an Adobe Illustrator raster object uses a base resolution of
	72 pixels per inch (ppi). Other resolutions cannot be directly specified.
	Instead, the bounds and the raster matrix are used to set a resolution. For
	a one inch square image at 72 ppi, the scale component of the raster
	matrix is set to 1.0 and the bounds would be 72 x 72. To have a one inch square
	image at 300 ppi, the bounds would be 300 x 300 and the scale component
	of the raster matrix would be 0.24 (72/300).

	To get or set the value of the pixel map data, a plug-in uses the raster suites
	GetRasterTile() and SetRasterTile() functions. The get function retrieves pixels
	from a pixel map while the set function copies pixel information to a pixel
	map. The plug-in's local data to or from which the pixels copied is called a
	tile and is described by the AITile structure.
 */
typedef struct AI120RasterSuite {

	/** This call provides the basic information a plug-in needs to use other Raster
		Suite calls, such as GetRasterTile(), on a raster art object. */
	AIAPI AIErr (*GetRasterInfo) ( AIArtHandle raster, AIRasterRecord *info );
	/** When a raster art object is first created, the raster record is unitialized. The
		AIArtSuite::NewArt() call should be followed by SetRasterInfo() to specify the
		objects color space, bounds, etc. */
	AIAPI AIErr (*SetRasterInfo) ( AIArtHandle raster, AIRasterRecord *info );
	/** Returns the value of the file member of the AIRasterLink information returned
		by GetRasterLink(). */
	AIAPI AIErr (*GetRasterFileSpecification) ( AIArtHandle raster, ai::FilePath& );
	/** Returns #kNotImplementedErr. */
	AIAPI AIErr (*SetRasterFileSpecification) ( AIArtHandle raster, const ai::FilePath& );
	/** Use this to get the transformation matrix of a raster art object. The transformation
		matrix of a raster object is the concatenation of all the transforms applied to
		the image after it was created. In addition to an initial translation, it will
		likely have a scale as described in SetRasterMatrix(). */
	AIAPI AIErr (*GetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );
	/** Use this to set the transformation matrix of a raster art object. In addition
		to using the raster object’s matrix for general transforms, it is used to set
		the pixel resolution of the object. This function will be used to set this and
		other transformations. */
	AIAPI AIErr (*SetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );
	/** Use this to get the raster object's bounds. This call will return the orginal
		bounding box of a raster object. This is not necessarily the same rectangle as
		the artwork bounds, which Illustrator will calculate and provide. */
	AIAPI AIErr (*GetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );
	/** Use this to set the raster object’s bounds. This call will set the bounding box
		of a raster object. This is not necessarily the same rectangle as the artwork
		bounds, which Illustrator will calculate and provide. */
	AIAPI AIErr (*SetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );
	/** Get a tile of data from the raster object. */
	AIAPI AIErr (*GetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AI120Tile *workTile, AISlice *workSlice );
	/** Copy pixel data in a local buffer to all or part of a raster object’s pixel map. */
	AIAPI AIErr (*SetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AI120Tile *workTile, AISlice *workSlice );

	/** Gets the link information specified for the raster object. Direct linking of
		images is deprecated but still supported. All linked objects should be created
		using the AIPlacedSuite. */
	AIAPI AIErr (*GetRasterLink) ( AIArtHandle raster, AIRasterLink &link );
	/** Sets the link information for the raster object. Direct linking of images is
		deprecated but still supported. All linked objects should be created using
		the AIPlacedSuite. */
	AIAPI AIErr (*SetRasterLink) ( AIArtHandle raster, const AIRasterLink &link );
	/** Resolve the link for the raster object. If needed the raster data will be
		reloaded from the source of the link. Note that the embedded and modified
		state of the link data is ignored. If succesful, the raster data will be marked
		as unmodified (i.e the modified flag is cleared), the embed flag is not
		changed.

		Attempting to resolve a link can fail for any of the following reasons:

		- no link source specified
		- link source not found (#kRasterLinkFileNotFoundErr)
		- a plugin which can load the link source data cannot be found
			(#kRasterLinkPluginNotFoundErr)
		- the link source data cannot be read
		- out of memory

		If the flags do not specify that resolution should be forced it will only be
		done if the linked to data is more recent than the current copy.
	*/
	AIAPI AIErr (*ResolveRasterLink) ( AIArtHandle raster, long flags );

	/** The SPPlatformFileInfo contains information about the linked file such as the time
		it was created and last modified. The raster object stores the information from
		the time the file was last read. This API returns the file information stored with
		the raster object. It can be compared against the current information for the file
		itself to determine if the file has changed. */
	AIAPI AIErr (*GetRasterFileInfoFromArt) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );
	/** The SPPlatformFileInfo contains information about the linked file such as the time
		it was created and last modified. This API returns the file information of the linked
		file itself. It can be compared against the information stored with the raster object
		to determine if the file has changed. */
	AIAPI AIErr (*GetRasterFileInfoFromFile) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );
	/** Get the path specification for the raster object. A platform specific path is
		returned. */
	AIAPI AIErr (*GetRasterFilePathFromArt) ( AIArtHandle raster, ai::UnicodeString &path );

	/** Raster data is stored in a MIP map. CountLevels() returns the number of levels in
		the map. This is presently hard coded at 6 but may change to be based on the source
		image dimensions in the future. */
	AIAPI AIErr (*CountLevels) ( AIArtHandle raster, long* count );
	/** GetLevelInfo returns an AIRasterRecord describing the format of the image
		data in a given level of the MIP map. The level number is zero based.

		- The flags are always a copy of the flags you'd get if querying the image
			as a whole.
		- The bounds are the bounds of the image at the given level of the MIP map.
			Each level is a power of two less than the previous one with odd dimensions
			being rounded up. Thus for example, levelWidth = (prevLevelWidth + 1) / 2.
			Of course you shouldn't rely on this algorithm. The only important property
			which will be maintained is that any rectangle contained within the base
			image is contained within an image at a given level after scaling to that
			level even if its dimensions are rounded up.
		- The byteWidth field should be ignored.
		- The colorSpace and bitsPerPixel describe the format of the pixel data at
			the given level of the MIP map. At present this is always the same as that
			of the base image but may change in the future. In particular the
			subsampled levels of a bitmap's MIP map are bitmaps--random sampling is
			used to avoid aliasing. In the future this may change to subsample
			into a grayscale image.
	*/
	AIAPI AIErr (*GetLevelInfo) ( AIArtHandle raster, long level, AIRasterRecord *info );
	/** GetLevelTile is equivalent to GetRasterTile but accesses the data from the
		given level of the MIP map. The level number is zero based.
	*/
	AIAPI AIErr (*GetLevelTile) ( AIArtHandle raster, long level, AISlice *artSlice,
			AI120Tile *workTile, AISlice *workSlice );

	/** Extract an outline path from the image data. The params object provides parameters
		for the extraction process. The consumer receives the path data. */
	AIAPI AIErr (*ExtractOutline) ( AIArtHandle raster, const AIRasterOutlineParams* params,
			AIRasterOutlineConsumer* consumer );

	/** Post-concatenate a transformation onto the matrix applied to the placed object. */
	AIAPI AIErr (*ConcatRasterMatrix) ( AIArtHandle raster, AIRealMatrix *concat );

} AI120RasterSuite;


#include "AIHeaderEnd.h"


#endif
