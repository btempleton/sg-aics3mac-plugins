#ifndef __AIGeometry__
#define __AIGeometry__

/*
 *        Name:	AIGeometry.h
 *     Purpose:	Adobe Illustrator Geometry Suite
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
 */

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIArt.h"
#include "AIPathStyle.h"
#include "AIRaster.h"


#include "AIHeaderBegin.h"

/** @file AIGeometry.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIGeometrySuite		"AI Geometry Suite"
#define kAIGeometryVersion		AIAPI_VERSION(3)
#define kAIGeometrySuiteVersion	kAIGeometryVersion


/** @ingroup Errors */
#define kCancelledErr			'CAN!'
/** @ingroup Errors */
#define kFormatErr				'FRM!'


/** Types of art objects that can be enumerated to \c #AIGeometryOrganizationProcs.
	These correspond to \c #AIArtType values for objects.
	*/
typedef enum {
	/** Marks the end of an object enumeration. */
	kAIGeometryOrganizeNull = 0,
	/** A path object. */
	kAIGeometryOrganizePath,
	/** A group object. */
	kAIGeometryOrganizeGroup,
	/** A compound object. */
	kAIGeometryOrganizeCompound,
	/** A placed object. */
	kAIGeometryOrganizePlaced,
	/** A raster object. */
	kAIGeometryOrganizeRaster,
	/** A text frame object.
		(As of AI11 the text organization callbacks are called for each text frame.) */
	kAIGeometryOrganizeText,
	/** A text path object.
		(As of AI11 this is called if the text frame has a confining path--that is,
		it is area text or text on a path). */
	kAIGeometryOrganizeTextPath,
	/** A text line object.
		(Obsolete, not invoked by AI11 or later.) */
	kAIGeometryOrganizeTextLine,
	/** A clipping group object. */
	kAIGeometryOrganizeClipGroup,
	/** A mask object.  */
	kAIGeometryOrganizeMask,
	/** A mesh object. */
	kAIGeometryOrganizeMesh,
	/** A symbol object. */
	kAIGeometryOrganizeSymbol,
	/** A foreign object.
		@note AI11 and later.*/
	kAIGeometryOrganizeForeignObject,
	/** A legacy text object.
		@note AI11 and later. */
	kAIGeometryOrganizeLegacyText,
	/** Internal */
	kAIGeometryOrganizeDummy = 0xFFFFFFFF

} AIGeometryOrganizationType;


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Developer-defined data for geometry callbacks.  */
typedef void *AIGeometryUserData;

/** Callback prototype for \c #AIGeometryOrganizationProcs. Called before enumeration
	begins for an object of an associated \c #AIGeometryOrganizationType.
		@param userData Developer-defined data.
		@param object The art object to be enumerated.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryBeginProc)(AIGeometryUserData userData, AIArtHandle object);

/** Callback prototype for \c #AIGeometryOrganizationProcs. Called after enumeration
	ends or is halted by a 1 result for an object of an associated \c #AIGeometryOrganizationType.
		@param userData Developer-defined data.
		@param object The art object that was enumerated.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryEndProc)(AIGeometryUserData userData, AIArtHandle object);

/** Callback prototype for \c #AIGeometryConstructionProcs.	Called to describe paths
	and outlines within a shape.
		@param userData Developer-defined data.
		@param p The destination location of the move.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryMoveToProc)(AIGeometryUserData userData, AIRealPoint *p);

/** Callback prototype for \c #AIGeometryConstructionProcs.	Called to describe each
	path or outline within an element of the art tree being iterated.
		@param userData Developer-defined data.
		@param p The destination location of the line draw.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryLineToProc)(AIGeometryUserData userData, AIRealPoint *p);

/** Callback prototype for \c #AIGeometryConstructionProcs. Called to describe each
	path or outline within an element of the art tree being iterated.
		@param userData Developer-defined data.
		@param p1 The first curve point.
		@param p2 The second curve point.
		@param p3 The third curve point.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryCurveToProc)(AIGeometryUserData userData, AIRealPoint *p1, AIRealPoint *p2, AIRealPoint *p3);

/** Callback prototype for \c #AIGeometryConstructionProcs.	Called to describe each
	path or outline within an element of the art tree being iterated.
		@param userData Developer-defined data.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryClosePathProc)(AIGeometryUserData userData);

/** Callback prototype for \c #AIGeometryPaintingProcs.	Called to describe the fill
	of an element of the art tree being iterated.
		@param userData Developer-defined data.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryFillProc)(AIGeometryUserData userData);

/** Callback prototype for \c #AIGeometryPaintingProcs.	Called to describe the strokes
	of an element of the art tree being iterated.
		@param userData Developer-defined data.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryStrokeProc)(AIGeometryUserData userData);

/** Callback prototype for \c #AIGeometryPaintingProcs. Called to describe the clipping
	of an element of the art tree being iterated.
		@param userData Developer-defined data.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryClipProc)(AIGeometryUserData userData);

/** Callback prototype for \c #AIGeometryPaintingProcs.	Called when an outline
	within the  art tree being iterated is filled with an image.
		@param userData Developer-defined data.
		@param raster The image object.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryImageProc)(AIGeometryUserData userData, AIArtHandle raster);

 /** Callback prototype for \c #AIGeometryPaintingProcs. Called when an outline
	within the  art tree being iterated is filled with an image.
		@param userData Developer-defined data.
		@param raster The image mask object.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryImageMaskProc)(AIGeometryUserData userData, AIArtHandle raster);

 /** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param gray The grayscale value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetGrayProc)(AIGeometryUserData userData, AIReal gray);

/** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param cyan The CMYK cyan value.
		@param magenta The CMYK magenta value.
		@param yellow The CMYK yellow value.
		@param black The CMYK black value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetCMYKColorProc)(AIGeometryUserData userData, AIReal cyan, AIReal magenta, AIReal yellow, AIReal black);

/** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param red The RGB red value.
		@param green The RGB green value.
		@param blue The RGB blue value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetRGBColorProc)(AIGeometryUserData userData, AIReal red, AIReal green, AIReal blue);

 /** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param alpha The alpha channel value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetAlphaProc)(AIGeometryUserData userData, AIReal alpha);

 /** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param customColor The custom color.
		@param tint The amount of the color, a percentage in the range [0..1].
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetCustomColorProc)(AIGeometryUserData userData, AICustomColorHandle customColor, AIReal tint);

 /** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param gradient The gradient object.
		@param gradientOrigin The origin point.
		@param gradientAngle The angle.
		@param gradientLength The length.
		@param hiliteAngle The highlight angle.
		@param hiliteLength	The highlight length.
		@param matrix The transformation matrix.
		@return 0 for enumeration to continue, 1 to halt enumeration.
		@see \c #AIGradientStyle
	*/
typedef short (*AIGeometrySetGradientColorProc)(AIGeometryUserData userData,
												AIGradientHandle gradient,
												AIRealPoint *gradientOrigin,
												AIReal gradientAngle,
												AIReal gradientLength,
												AIReal hiliteAngle,
												AIReal hiliteLength,
												AIRealMatrix *matrix);

/** Callback prototype for \c #AIGeometryStateProcs. Called for the fill and
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param pattern The pattern object.
		@param shiftDistance  Pattern style value.
		@param shiftAngle Pattern style value.
		@param scale  Pattern style value.
		@param rotateAngle	Pattern style value.
		@param reflect Pattern style value.
		@param reflectAngle	Pattern style value.
		@param shearAngle Pattern style value.
		@param shearAxis Pattern style value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
		@see \c #AIPatternStyle
	*/
typedef short (*AIGeometrySetPatternColorProc)(AIGeometryUserData userData,
											   AIPatternHandle pattern,
											   AIReal shiftDistance,
											   AIReal shiftAngle,
											   AIRealPoint *scale,
											   AIReal rotateAngle,
											   AIBoolean reflect,
											   AIReal reflectAngle,
											   AIReal shearAngle,
											   AIReal shearAxis,
											   AIRealMatrix *matrix);
/** Callback prototype for \c #AIGeometryStateProcs.  Called when an outline
	within the  art tree being iterated is filled with an image.
		@param userData Developer-defined data.
		@param alpha The alpha channel value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometryImageCallback)(AIGeometryUserData userData,
										 AIArtHandle raster,
										 AISlice *artSlice,
										 AITile *workTile,
										 AISlice *workSlice);

/** Callback prototype for \c #AIGeometryStateProcs.  Called for the
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param lineWidth The line width value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetLineWidthProc)(AIGeometryUserData userData, AIReal lineWidth);

 /** Callback prototype for \c #AIGeometryStateProcs. Called for the
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param lineCap The line cap value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetLineCapProc)(AIGeometryUserData userData, AILineCap lineCap);

/** Callback prototype for \c #AIGeometryStateProcs. Called for the
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param lineJoin The line join value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetLineJoinProc)(AIGeometryUserData userData, AILineJoin lineJoin);

/** Callback prototype for \c #AIGeometryStateProcs. Called for the
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param miterLimit The miter limit value.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	*/
typedef short (*AIGeometrySetMiterLimitProc)(AIGeometryUserData userData, AIReal miterLimit);

/**Callback prototype for \c #AIGeometryStateProcs.	Called for the
	stroke of each element within the art tree being iterated.
		@param userData Developer-defined data.
		@param offset The dash offset value.
		@param length The number of dash values.
		@param array The array of dash values.
		@return 0 for enumeration to continue, 1 to halt enumeration.
	 */
typedef short (*AIGeometrySetDashProc)(AIGeometryUserData userData, AIReal offset, short length, AIReal array[]);

/** Passed as a pointer to a list of organization types
	with associated begin/end procedures.
	The list is terminated by an entry with an organization type of 0. */
typedef struct {

	/** The type of object to which these procedures apply. */
	AIGeometryOrganizationType type;
	/** Procedure called before enumerating an object of this type. */
	AIGeometryBeginProc begin;
	/** Procedure called after enumerating an object of this type. */
	AIGeometryEndProc end;

} AIGeometryOrganizationProcs;

/** Callbacks that get information about how paths are constructed.
	Called for leaf objects. */
typedef struct {
	AIGeometryMoveToProc moveTo;
	AIGeometryLineToProc lineTo;
	AIGeometryCurveToProc curveTo;
	AIGeometryClosePathProc closePath;

} AIGeometryConstructionProcs;

/** Callbacks that get information about how objects are painted.
	Called for leaf objects.*/
typedef struct {

	AIGeometryFillProc fill;
	AIGeometryFillProc eofill;
	AIGeometryStrokeProc stroke;
	AIGeometryClipProc clip;
	AIGeometryClipProc eoclip;
	AIGeometryImageProc image;
	AIGeometryImageMaskProc imageMask;

} AIGeometryPaintingProcs;

/** Callbacks that get information about painting options.
	Called for leaf objects. */
typedef struct {

	AIGeometrySetGrayProc setWhiteColor;
	AIGeometrySetGrayProc setBlackColor;
	AIGeometrySetGrayProc setGrayColor;
	AIGeometrySetCMYKColorProc setCMYKColor;
	AIGeometrySetRGBColorProc setRGBColor; /* unimplemented */
	AIGeometrySetAlphaProc setAlpha; /* unimplemented */
	AIGeometrySetCustomColorProc setCustomColor;
	AIGeometrySetGradientColorProc setGradientColor;
	AIGeometrySetPatternColorProc setPatternColor;

	AIGeometrySetLineWidthProc setLineWidth;
	AIGeometrySetLineCapProc setLineCap;
	AIGeometrySetLineJoinProc setLineJoin;
	AIGeometrySetMiterLimitProc setMiterLimit;
	AIGeometrySetDashProc setDash;

} AIGeometryStateProcs;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides an iteration mechanism for collecting information about
	the art objects in the various kinds of	artwork trees.
	It allows you to define a set of callback procedures to work with
	various aspects of artwork, including the placement, style, and color attributes.
	The \c #GeometryIterate() function enumerates the contents of an artwork
	subtree to a set of callback functions that receive various kinds
	of information about each object. You need supply only the callbacks of interest
	to your plug-in.

	All of the object information passed to the callbacks is public information that
	can be accessed directly through SDK functions. You can also define and pass
	arbitrary data to the callbacks, to use together with the object data.

	All callbacks should return 0 to continue processing the next
	artwork element, or nonzero to halt processing. This allows you to prune
	the traversal of the artwork tree.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIGeometrySuite and \c #kAIGeometryVersion.
	*/
typedef struct {

	/** Supplies information to developer-defined callback procedures,
		calling the procedures iteratively for each member of an artwork tree whose
		root is a specified art object.
			@param art The root art object.
			@param organizationProcs For each object in the tree, calls the begin and end procedure
				associated the type before and after enumerating the object.
			@param constructionProcs Contains pointers to callbacks that receive a geometric
				description of each leaf art object.
			@param paintingProcs Contains pointers to callbacks that receive information
				about how each leaf object is painted.
			@param stateProcs Contains pointers to callbacks that receive additional parameters
				to the painting operations.
			@param userData Developer-defined data to be passed to callbacks.
		*/
	ASAPI AIErr (*GeometryIterate) ( AIArtHandle art,
									 AIGeometryOrganizationProcs *organizationProcs,
									 AIGeometryConstructionProcs *constructionProcs,
									 AIGeometryPaintingProcs *paintingProcs,
									 AIGeometryStateProcs *stateProcs,
									 AIGeometryUserData userData );

} AIGeometrySuite;


#include "AIHeaderEnd.h"


#endif
