#ifndef __AIPath__
#define __AIPath__

/*
 *        Name:	AIPath.h
 *   $Revision: 13 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Path Object Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIRealBezier__
#include "AIRealBezier.h"
#endif

#ifndef __AI70PathStyle__
#include "AI70PathStyle.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIPath.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPathSuite			"AI Path Suite"
#define kAIPathSuiteVersion7	AIAPI_VERSION(7)
#define kAIPathSuiteVersion		kAIPathSuiteVersion7
#define kAIPathVersion			kAIPathSuiteVersion


/** Maximum number of segments in one path */
#define kMaxPathSegments		32000
/** Obsolete with AI11. Maximum number of segments in one text path */
#define kMaxTextPathSegments	67


/** Selection states for path segments. */
enum AIPathSegementSelectionState {
	kSegmentNotSelected			= 0,
	kSegmentPointSelected		= 1,
	kSegmentInSelected			= 2,
	kSegmentOutSelected			= 3,
	kSegmentInAndOutSelected	= 4
};


/** @ingroup Errors
	See \c #AIPathSuite */
#define kTooManySegmentsErr			'SEGM'


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct {
	AIRealPoint p, in, out;
	AIBoolean corner;
} AIPathSegment;


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides functions that allow you to examine and manipulate
	\e paths, which are art objects of type \c #kPathArt.

	The shape of a path is defined by one or more path \e segments.
	Every segment of a path corresponds to an \e anchor \e point, which is
	the handle shown when the path is selected. The number of anchor points
	on a path, or \e segment \e count, includes the two at each end.
	A segment is defined by the \c #AIPathSegment structure. Segment
	index numbers begin at zero. A path can have a single anchor point.

	The \e in and \e out points of a segment define the tangent of the curve
	at a point \e p. The in point is not used for the initial and final segments
	of an open path. A segment can be a \e corner point or a \e smooth point.
	For a corner, the in and out points can be anywhere. To make a straight line,
	place the in and out points of each end on their p points.

	A path can be can be \e closed or \e open.
	If a path is open, it is defined only by its segments. If it is closed,
	Illustrator draws a segment between the first and last anchor points,
	which uses the out tangent of the last segment and the in tangent of the first.

	Some paths are also used as \e guides. In all other respects they are paths,
	with the same contents and attributes. Paint attributes are associated with
	a path through a \e path \e style. See the \c #AIPathStyleSuite.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathSuite and \c #kAIPathVersion.
*/
typedef struct {

	/** Gets the number of anchor points on a path, including the two at each
		end.
			@param path The path object.
			@param count [out] A buffer in which to return the number of segments.
		*/
	AIAPI AIErr (*GetPathSegmentCount) ( AIArtHandle path, short *count );

	/** Removes segments from or appends segments to the end of a path.
		If the count is increased, new segments	are initialized to default values,
		which are not guaranteed to always be the same.
			@param path The path object.
			@param count The new segment count.
			@return The error \c #kTooManySegmentsErr if the new count exceeds
				the maximum number of path segments,

			@note When \c #AIArtSuite::NewArt() creates a path, it initially allocates space
				for 32 segments. When creating many small paths, this can waste memory.
				Use this function to free the memory of unused path segments immediately.
	*/
	AIAPI AIErr (*SetPathSegmentCount) ( AIArtHandle path, short count );

	/** Retrieves a set of segments from a path.
			@param path The path object.
			@param segNumber The 0-based index of the first segment.
			@param count The number of segments to retrieve.
			@param segment [out] A buffer in which to return a pointer
				to the segment array. You must allocate an array of \c #AIPathSegment
				the size of \c count.
		*/
	AIAPI AIErr (*GetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	/** Adds or updates segments in a path. If segments are removed from a closed path,
		the path remains closed.
			@param path The path object.
			@param segNumber The 0-based index of the first segment.
			@param count The number of segments to add.
			@param segment A pointer to the new segment array. You must allocate and
				fill an array of \c #AIPathSegment the size of \c count.
			@return The error \c #kTooManySegmentsErr if the new segment count exceeds
  				the maximum number of path segments,
		*/
	AIAPI AIErr (*SetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	/** Inserts segments into a path.
			@param path The path object.
			@param segNumber The 0-based index of an existing segment in the path.
				The new segments are inserted after this one.
			@param count The number of segments to insert.
			@param segment A pointer to the new segment array. You must allocate and
				fill an array of \c #AIPathSegment the size of \c count.
			@return The error \c #kTooManySegmentsErr if the new segment count exceeds
  				the maximum number of path segments,
		*/
	AIAPI AIErr (*InsertPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	/** Deletes segments from a path. If you delete segments from a closed path,
		the path remains closed.
			@param path The path object.
			@param segNumber The 0-based index of the first segment.
			@param count The number of segments to delete.
		*/
	AIAPI AIErr (*DeletePathSegments) ( AIArtHandle path, short segNumber, short count );

	/** Reports whether a path is closed.
			@param path The path object.
			@param closed [out] A buffer in which to return true if the path is closed,
				false if it is open.
		*/
	AIAPI AIErr (*GetPathClosed) ( AIArtHandle path, AIBoolean *closed );

	/** Opens or closes a path. When you close a path, an additional segment is
		drawn between the last segment and the first segment. This is often the
		last step in creating a new path.
			@param path The path object.
			@param closed True to close the path, false to open it.

		*/
	AIAPI AIErr (*SetPathClosed) ( AIArtHandle path, AIBoolean closed );

	/** Reports whether a path is used as a guide.
			@param path The path object.
			@param isGuide [out] A buffer in which to return true if the path is a guide
		*/
	AIAPI AIErr (*GetPathGuide) ( AIArtHandle path, AIBoolean *isGuide );

	/** Sets whether a path is used as a guide.
			@param path The path object.
			@param isGuide True if the path is to be used as a guide, false if it is not.
		*/
	AIAPI AIErr (*SetPathGuide) ( AIArtHandle path, AIBoolean isGuide );

	/** Reports whether any part of a path segment is selected.
			@param path The path object.
			@param segNumber The 0-based index of the segment.
			@param selected [out] A buffer in which to return the selection state of the
				segment, an \c #AIPathSegementSelectionState value.
		*/
	AIAPI AIErr (*GetPathSegmentSelected)( AIArtHandle path, short segNumber, short *selected );

	/** Sets the selection state for a segment.
			@param path The path object.
			@param segNumber The 0-based index of the segment.
			@param selected The new selection state of the segment,
				an \c #AIPathSegementSelectionState value.

			@note Modifying the selection state of one segment can affect
				adjacent segments. For example, if the out direction of one segment
				is selected, the in direction of the following segment is also selected.
		*/
	AIAPI AIErr (*SetPathSegmentSelected)( AIArtHandle path, short segNumber, short selected );

	/** Reverses the order of segments in a path. The winding order is only
		significant if the path is a subpath of a compound path. It controls
		the insideness of the compound path.
			@param path The path object.
		*/
	AIAPI AIErr (*ReversePathSegments) ( AIArtHandle path );

	/** Calculates the area of a path. A path’s winding order is
		determined by the sign of area. If the area is negative,
		the path is wound counter-clockwise. Self-intersecting paths
		can contain sub-areas that cancel each other out. This makes
		it possible for the function to return zero for a path that
		does have area.
			@param path The path object.
			@param area [out] A buffer in which to return the area, in
				square points.
		*/
	AIAPI AIErr (*GetPathArea) ( AIArtHandle path, AIReal *area );

	// New for AI8.0:

	/** Calculates the length of the perimeter of a path measured in points.
			@param path The path object.
			@param length [out] A buffer in which to return the length, in points.
			@param flatness Not used.
		*/
	AIAPI AIErr (*GetPathLength) ( AIArtHandle path, AIReal *length, AIReal flatness );

	/** Calculates the bezier values of a path segment.
		\li For the last anchor point of an open path, wraps to the beginning.
		\li  For the last anchor point of a closed path, all four bezier points are
			equal--that is, the outgoing control point is ignored, so that the visible
			bounding box, length, and other function treat it correctly.

			@param path The path object.
			@param segNumber The 0-based index of the segment.
			@param bezier [out] A buffer in which to return the bezier values.
		*/
	AIAPI AIErr (*GetPathBezier) ( AIArtHandle path, short segNumber, AIRealBezier *bezier );

	/** Reports whether a path has length. This is more efficient than checking
		whether \c #GetPathLength() != 0.
			@param path The path object.
			@param hasLength [out] A buffer in which to return true if the path length
				is not zero.
		*/
	AIAPI AIErr (*PathHasLength) ( AIArtHandle path, AIBoolean *hasLength );

	/** Reports whether a path is a clipping path. The path can be a compound path.
		 To be a clipping object a path must have at least two segments.
		 To make a path into a clipping path use \c #AIArtSuite::SetArtUserAttr()
			@param path The path object.
			@param isClip [out] A buffer in which to return true if the path is a clipping path.
	 	*/
	AIAPI AIErr (*GetPathIsClip) ( AIArtHandle path, AIBoolean *isClip );

	// New for AI 11

	/** Reports whether all segments of a path are selected.
			@param path The path object.
			@param selected [out] A buffer in which to return true if the path is fully selected.
		*/
	AIAPI AIErr (*GetPathAllSegmentsSelected) ( AIArtHandle path, AIBoolean *selected );

	// New for AI 13

	/** Retrieves path object and segment number of the key anchor point (that is,
		the one to which other anchor points are aligned). The key anchor point
		is usually the last anchor point selected with the direct select tool.
			@param path [out] A buffer in which to return the path object.
			@param segmentNumber [out] A buffer in which to return the segment number.
		*/
	AIAPI AIErr (*GetKeySegment) (AIArtHandle* path, short* segmentNumber);

	/** Clears the key anchor point (the one to which other anchor points are aligned).
		This is usually the last anchor point selected with the direct select tool.
		*/
	AIAPI AIErr (*CancelKeySegment) (void);

	/** Reports whether a path is 9-slice splitter; that is, a guide that defines
		a line splitting the art board into 9 regions.
			@param path The path object.
			@return True if the path is 9-slice splitter, false if not, or if the
				path is not used as a guide.
			@see \c #GetPathGuide()
		*/
	AIAPI AIBoolean (*IsPath9SliceSplitter)(AIArtHandle path);




} AIPathSuite;


#include "AIHeaderEnd.h"


#endif
