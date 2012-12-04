#ifndef __AICursorSnap__
#define __AICursorSnap__

/*
 *        Name:	AICursorSnap.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Cursor Snapping Suite.
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
#ifndef __AIDocumentView__
#include "AIDocumentView.h"
#endif
#ifndef __AITool__
#include "AITool.h"
#endif

#include "AIHeaderBegin.h"

/** @file AICursorSnap.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAICursorSnapSuite				"AI Cursor Snap Suite"
#define kAICursorSnapSuiteVersion13		AIAPI_VERSION(2)
#define kAICursorSnapSuiteVersion		kAICursorSnapSuiteVersion13
#define kAICursorSnapVersion			kAICursorSnapSuiteVersion


/**
	Kinds of custom constraints
 */
enum {
	/** Single point */
	kPointConstraint = 1,
	/** A line whose angle is relative to the page coordinates */
	kLinearConstraintAbs,
	/**	A line whose angle is relative to the constraint angle	*/
	kLinearConstraintRel
};


/**  Flags for custom constraints: snap to constraint when shift key is down */
#define kShiftConstraint			(1<<0L)


/** Boundary editors for the transformation tools. */
enum {
	kTranslateBoundaryEditor = 1
};


/*******************************************************************************
 **
 ** Types
 **
 **/

/**
	Structure describing a custom constraint.
 */
typedef struct {
	/** Type of constraint, one of:
		\li \c kPointConstraint: A single point.
		\li \c kLinearConstraintAbs: A line whose angle is relative to
			the page coordinates.
		\li \c kLinearConstraintRel: A line whose angle is relative
			to the constraint \c angle.
	*/
	long				kind;
	/** Flags for the constraint. The only flag is \c #kShiftConstraint,
	 which means snap to the constraint when the shift key is down.*/
	long				flags;
	/** Origin point for the constraint. */
	AIRealPoint			point;
	/** When \c kind is \c kLinearConstraintRel, the angle of the line. */
	AIFloat				angle;
	/** Label for the constraint presented to the user. */
	char*				label;
} AICursorConstraint;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Tools that use the Smart Guides snapping facility use these
	functions in the cursor-tracking code.The suite provides functions
	for snapping the cursor to various things, called \e constraints.
	Constraints include art objects, page boundaries
	and the automatically generated guide lines. You can also define your own
	constraints, using \c #SetCustom(), although most tools do not do so.

	@note Turning on the grid turns smart guides off, so you never use
	this facility to snap to the grid.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICursorSnapSuite and \c #kAICursorSnapVersion.

	Snap the cursor using the \c #Track() function, which
	takes a current cursor location and returns the snapped location.
	A control string contains a series of Smart Guide commands
	that control how the snap is performed; that is, what kind of
	object is snapped to, and what kind of location to look for in
	each kind of object.

	You can find out what object is under the snapped location:
@code
AIHitRef hit;
long option = <<whatever options>>
result = sAIHitTest->HitTest(NULL, &p, option, &hit);
if (result)
	throw ai::Error(result);
@endcode

	These are the control strings used by the various tools built
	into Illustrator, as saved in the preferences file.
	The first entry in each line is the key used in preferences. The second
	is the control string for when the mouse is up and the third is the control
	string for when the mouse is down.

	- "Blend", "A v", "A v"
	- "Select", "A v o f", "ATFGP v i o f"
	- "RangeSelect", "", ""
	- "Zoom", "", ""
	- "Page", "ATFGP v i o", "ATFGP v i o"
	- "Ruler", "ATFGP v i o", "ATFGP v i o"
	- "Guide", "ATFGP v i o", "ATFGP v i o"
	- "Scissor", "ATFGP v i o", "ATFGP v i o"
	- "SquareCircle", "ATFGP v i o", "ATFGP v i o"
	- "Pen", "ATFGP v i o", "ATFGP v i o"
	- "Translate", "ATFGP v i o", "ATFGPB v i o"
	- "Scale", "ATFGP v i o", "ATFGPB v i o"
	- "Rotate", "ATFGP v i o", "ATFGP v i o"
	- "Reflect", "ATFGP v i o", "ATFGP v i o"
	- "Shear", "ATFGP v i o", "ATFGP v i o"
	- "Eyebucket", "A v o f", "A v o f"
*/

typedef struct {

	/** Reports whether Smart Guides should be used to snap the
		cursor in a given view. (Note that this function returns
		a boolean value, not an error code.)
			@param view The document view.
			@return True if Smart Guides should be used.
	 */
	AIAPI AIBoolean		(*UseSmartGuides)		(AIDocumentViewHandle view);

	/** Resets the Smart Guides snapping engine. This clears all custom constraints
		and all automatically generated constraint lines.
	 */
	AIAPI AIErr			(*Reset)				(void);

	/** Clears all custom constraints without clearing automatically
		generated constraint lines.
	 */
	AIAPI AIErr			(*ClearCustom)			(void);

	/** Replaces the current set of custom constraints with the specified set.
			@param count The number of constraints being defined.
			@param constraints An array of custom constraints. The function makes a
				copy, so the caller can free this memory after making the call.
	 */
	AIAPI AIErr			(*SetCustom)			(long count, const AICursorConstraint* constraints);

	/** Snaps the cursor to a specified constraint, using a specified technique, using
		the "Snap To Point" application preference.
			@param view The document view in which to snap the cursor.
			@param srcpoint The actual cursor location in view coordinates.
				Typically passed in the \c #AIToolMessage member \c cursor.
			@param event The state of modifier keys.
			@param control How snapping is performed, a string containing
				a sequence of uppercase and lowercase characters, and spaces.
				Each character in the string is a command to the snapping engine.
				They are processed sequentially from left to right.
				\li An uppercase character enables a constraint:
					- A: Enable snapping to art objects (if the "Snap To Point" application
						 preference is set). Uses the Snapping tolerance preference
						 (rather than the Selection tolerance).
					- T: Enable snapping to custom constraints defined by the current tool.
					- F: Enable snapping to automatically generated guidelines.
					- P: Enable snapping to the page boundaries.
				\li A lower case character is an instruction to look for the best snap location.
					of a particular type among the currently enabled constraints.
						- i: Look for intersections of two or more constraints.
						- o: Try to snap onto a constraint line
						- v: Try to snap to a point (vertex).
						- f: Look for filled objects.
				\li A space character is an instruction to return the best snap location found
					so far. If no snap location has been found, the search continues.

			@param dstpoint [out] A buffer in which to return the snapped cursor position.
	*/
	AIAPI AIErr			(*Track)				(AIDocumentViewHandle view, AIRealPoint srcpoint,
												const AIEvent* event, const char* control,
												AIRealPoint* dstpoint);

	/**	Snaps the cursor to a specified constraint, using a specified technique. Does not
		consider the "Snap To Point" application preference, and uses the Selection
		tolerance to identify hits on art objects. This function is used for direct
		selection of anchor points.
			@param view The document view in which to snap the cursor.
			@param srcpoint The actual cursor location in view coordinates.
				Typically passed in the \c #AIToolMessage member \c cursor.
			@param event The state of modifier keys.
			@param control How snapping is performed, a string containing
				a sequence of uppercase and lowercase characters, and spaces.
				Each character in the string is a command to the snapping engine.
				They are processed sequentially from left to right.
				\li An uppercase character enables a constraint:
					- A: Enable snapping to art objects (without regard to the
						"Snap To Point" application preference). Uses the Selection
						tolerance preference (rather than the Snapping tolerance).
					- T: Enable snapping to custom constraints defined by the current tool.
					- F: Enable snapping to automatically generated guidelines.
					- P: Enable snapping to the page boundaries.
				\li A lower case character is an instruction to look for the best snap location
					of a particular type among the currently enabled constraints.
						- i: Look for intersections of two or more constraints.
						- o: Try to snap onto a constraint line.
						- v: Try to snap to a point (vertex).
						- f: Look for filled objects.
				\li A space character is an instruction to return the best snap location found
					so far. If no snap location has been found, the search continues.

			@param dstpoint [out] A buffer in which to return the snapped cursor position.
			@param magnifyAnchorPoint [in] True to magnify an anchor point whose hotspot is under the
				mouse cursor, as the direct selection tool does.
	*/
	AIAPI AIErr			(*HitTrack)				(AIDocumentViewHandle view, AIRealPoint srcpoint,
												const AIEvent* event, const char* control,
												AIRealPoint* dstpoint, AIBoolean magnifyAnchorPoint);
} AICursorSnapSuite;


#include "AIHeaderEnd.h"


#endif
