#ifndef __AIDocumentView__
#define __AIDocumentView__

/*
 *     Name:	AIDocumentView.h
 *     Purpose:	Adobe Illustrator Document View Suite.
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


#include "AIHeaderBegin.h"

/** @file AIDocumentView.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDocumentViewSuite			"AI Document View Suite"
#define kAIDocumentViewSuiteVersion9	AIAPI_VERSION(9)

// latest version
#define kAIDocumentViewSuiteVersion		kAIDocumentViewSuiteVersion9
#define kAIDocumentViewVersion			kAIDocumentViewSuiteVersion

/** @ingroup Notifiers
	Sent when the document view changes. See \c #AIDocumentViewSuite. */
#define kAIDocumentViewChangedNotifier				"AI Document View Changed Notifier"
/** @ingroup Notifiers
 	See \c #AIDocumentViewSuite::GetDocumentViewInvalidRect()
	*/
#define kAIDocumentViewInvalidRectChangedNotifier	"AI Document View Invalid Rect Changed Notifier"
/** @ingroup Notifiers
	 Sent when the document view style changes. See \c #AIDocumentViewSuite. */
#define kAIDocumentViewStyleChangedNotifier			"AI Document View Style Changed Notifier"

/*******************************************************************************
 **
 **	Types
 **
 **/

/** The same as a Macintosh GWorldPtr. Applies only to version 2 of this suite. */
typedef void *AIDocumentPlatformViewBitmap;

/** An opaque reference for a document view.  */
typedef struct _t_AIDocumentViewOpaque *AIDocumentViewHandle;

/** Screen mode values, see \c #AIDocumentViewSuite::GetScreenMode(),
	\c #AIDocumentViewSuite::SetScreenMode() */
enum AIScreenMode {
	/** Null mode, used only when there is no visible document */
	kNoScreenMode,
	/** The normal display mode. Multiple windows are visible. */
	kMultiWindowMode,
	/** A single view takes up the whole screen but the menu is visible. */
	kFullScreenWithMenuMode,
	/** A single view takes up the whole screen, the menu is not visible. */
	kFullScreenNoMenuMode,
  	/** Only one window on screen, edges flush with top and side panes.
  		Valid only for suite version 9 and higher. */
  	kMaximizedWindowMode
} ;


/** The page tiling structure that describes how artwork is printed
	on one or more pages. See \c #AIDocumentViewSuite::GetPageTiling().
	Tiling operates on an \e art \e piece, which can be a set of art objects,
	the entire art board, or a crop box.  */
struct AIPageTiling {
	/** Horizontal and vertical number of page tiles on the art piece. A tile counts
		if and only if some of its imageable area intersects the art piece bounds. */
	AIPoint tilesPerArt;
	/** The total number of page tiles, <code>tilesPerArt.x * tilesPerArt.y</code> */
	ASInt16 tilesPerArtPiece;
	/** The bounds of the artboard, whose dimensions are configured when
		creating a new document or through document setup.
		Page tiles may extend beyond these bounds, but they must intersect it. */
	AIRealRect bounds;
	/** Size of paper, in points. */
	AIRealPoint paperSize;
	/** Top left of first piece of paper, in page coordinates.  */
	AIRealPoint paperOrigin;
	/** Size of imageable page area, in points */
	AIRealPoint imageSize;
	/** Top left of first imageable page area, in page coordinates. */
	AIRealPoint imageOrigin;
	/** Unused. Art size plus gap */
	AIRealPoint pieceDelta;
	/* When true, show outlines of page tiles. */
	ASBoolean showTiling;
} ;


/** Outline mode view style; see \c #AIDocumentViewSuite::GetDocumentViewStyle().
	 */
#define kVsArtwork			0x0001
/** Preview mode view style; see \c #AIDocumentViewSuite::GetDocumentViewStyle().
	 */
#define kVsPreview			0x0002
/** Pixel preview mode view style; see \c #AIDocumentViewSuite::GetDocumentViewStyle().
	 */
#define kVsRaster			0x0040
/** Unimplemented. Transparency attributes and masks are ignored.
	 */
#define kVsOpaque			0x0080
/** OPP preview mode view style; see \c #AIDocumentViewSuite::GetDocumentViewStyle().
	 */
#define kVsInk				0x0100

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	Use these functions to get and set properties of a document view,
	including the bounds, center, zoom, and screen mode.

	To operate on the current view, you can usually pass \c NULL for
	the \c view parameter. To get a view reference for the current
	view, pass 0 to \c #AIDocumentViewSuite::GetNthDocumentView().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDocumentViewSuite and \c #kAIDocumentViewVersion.
*/
struct AIDocumentViewSuite {

	/** Retrieves the bounds of a document view in artwork coordinates (that is,
		the portion of the artboard that is visible in the window).
			@param view The view reference, or \c NULL for the current view.
			@param bounds [out] A buffer in which to return the bounding box.
		*/
	AIAPI AIErr (*GetDocumentViewBounds) ( AIDocumentViewHandle view, AIRealRect *bounds );

	/** Retrieves the center of a document view in artwork coordinates (that is, the
		point of the artboard that maps to the center of the window).
			@param view The view reference, or \c NULL for the current view.
			@param center [out] A buffer in which to return the center point.
		*/
	AIAPI AIErr (*GetDocumentViewCenter) ( AIDocumentViewHandle view, AIRealPoint *center );

	/** Sets the point of the artboard that maps to the center of the window for a view.
			@param view The view reference, or \c NULL for the current view.
			@param center The new center point.
		*/
	AIAPI AIErr (*SetDocumentViewCenter) ( AIDocumentViewHandle view, const AIRealPoint *center );

	/** Retrieves the zoom factor for a view. This is the scale factor from artwork
		coordinates to window coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param zoom [out] A buffer in which to return the zoom factor, a percentage
				value where 1 is 100% (actual size), 0.5 is 50% and 2 is 200%.
		*/
	AIAPI AIErr (*GetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal *zoom );

	/** Sets the scale factor from artwork coordinates to window coordinates for a view.
		The scale factor is silently clamped to lie between the minimum and maximum values
		supported (currently between 1/32 and 64). After adjusting the zoom, the document view
		center remains unchanged.
				@param view The view reference, or \c NULL for the current view.
				@param zoom The new zoom factor, a percentage value where
					1 is 100% (actual size), 0.5 is 50% and 2 is 200%.
		*/
	AIAPI AIErr (*SetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal zoom );

	/** Converts a point from artwork coordinates to view (window) coordinates. The resulting
		view coordinate is rounded to the nearest pixel.
			@param view The view reference, or \c NULL for the current view.
			@param artworkPoint The point to convert, in artwork coordinates.
			@param viewPoint [out] A buffer in which to return the converted point, in window coordinates.
			@see \c #FixedArtworkPointToViewPoint() (does not round)
		*/
	AIAPI AIErr (*ArtworkPointToViewPoint) ( AIDocumentViewHandle view, const AIRealPoint *artworkPoint, AIPoint *viewPoint );

	/** Converts a point from view coordinates to artwork coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param viewPoint The point to convert, in window pixel coordinates.
			@param artworkPoint [out] A buffer in which to return the converted point, in artboard coordinates.
			@see \c #FixedViewPointToArtworkPoint() (takes floating-point coordinate values)
		 */
	AIAPI AIErr (*ViewPointToArtworkPoint) ( AIDocumentViewHandle view, const AIPoint *viewPoint, AIRealPoint *artworkPoint );

	/** Gets the number of open views for the current document. Use with
		\c #GetNthDocumentView() to iterate through views.
			@param count [out] A buffer in which to return the number of views.
		*/
	AIAPI AIErr (*CountDocumentViews)( long *count );

	/** Retrieves a document view for the current document by position index. Use with
		\c #CountDocumentViews() to iterate through views.
			@param n The index, in the range <code>[1..numViews]</code>, or 0 to get the current view.
			@param view [out] A buffer in which to return the view reference.
		*/
	AIAPI AIErr (*GetNthDocumentView)( long n, AIDocumentViewHandle *view );

	/** Converts a point from artwork coordinates to view (window) coordinates. Does \e not round
		the result.
			@param view The view reference, or \c NULL for the current view.
		 	@param artworkPoint The point to convert, in artwork coordinates.
		 	@param viewPoint [out] A buffer in which to return the converted point, in window coordinates.
			@see \c #ArtworkPointToViewPoint() (rounds result to nearest pixel)
		*/
	AIAPI AIErr (*FixedArtworkPointToViewPoint) ( AIDocumentViewHandle view, const AIRealPoint *artworkPoint, AIRealPoint *viewPoint );

	/** Converts a point from view coordinates to artwork coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param viewPoint The point to convert, in window floating-point coordinates.
			@param artworkPoint [out] A buffer in which to return the converted point, in artboard coordinates.
			@see \c #ViewPointToArtworkPoint() (takes pixel coordinate values)
		*/
	AIAPI AIErr (*FixedViewPointToArtworkPoint) ( AIDocumentViewHandle view, const AIRealPoint *viewPoint, AIRealPoint *artworkPoint );

	/** Sets the screen mode of a view. In the UI, the screen mode is
		selected with icons at the bottom of the Tool palette.
			 @param view The view reference, or \c NULL for the current view.
			 @param mode The new screen mode.
		*/
	AIAPI AIErr (*SetScreenMode) ( AIDocumentViewHandle view, AIScreenMode mode );

	/** Retrieves the screen mode of a view. In the UI, the screen mode is
		shown by icons at the bottom of the Tool palette.
			 @param view The view reference, or \c NULL for the current view.
			 @param mode [out] A buffer in which to return the screen mode.
		*/
	AIAPI AIErr (*GetScreenMode) ( AIDocumentViewHandle view, AIScreenMode *mode );

	/** Retrieves the page tiling information that describes how the artwork is printed
		onto one or more pages.
			 @param pageTiling [out] A buffer in which to return the tiling information.
		*/
	AIAPI AIErr (*GetPageTiling) ( AIPageTiling *pageTiling );

	/** Reports whether there is a visible template layer.
			 @param view The view reference, or \c NULL for the current view.
			 @param visible [out] A buffer in which to return true if the template layer is shown.
		*/
	AIAPI AIErr (*GetTemplateVisible) ( AIDocumentViewHandle view, AIBoolean *visible );

	/** Scrolls a document window.
			 @param view The view reference, or \c NULL for the current view.
			 @param delta The vector by which to scroll, a horizontal and vertical
			 	distance in points.
		*/
	AIAPI AIErr (*DocumentViewScrollDelta)( AIDocumentViewHandle view, AIRealPoint *delta);

	/** Retrieves a rectangle that encloses (at least) the portions of the viewed
		document that have been changed and so need to be redrawn. This rectangle is reset to
		be empty each time the \c #kAIDocumentViewInvalidRectChangedNotifier is sent.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect [out] A buffer in which to return the invalid area, in artwork coordinates.
		*/
	AIAPI AIErr (*GetDocumentViewInvalidRect)( AIDocumentViewHandle view, AIRealRect *invalidRect );

	/** Sets the invalid rectangle for a view. This is the area that encloses
		(at least) the portions of the viewed document that have been changed
		and so need to be redrawn in the given view.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect The new area, in artwork coordinates.
			@see \c #GetDocumentViewInvalidRect(), \c #SetDocumentViewInvalidDocumentRect()
		*/
	AIAPI AIErr (*SetDocumentViewInvalidRect)( AIDocumentViewHandle view, const AIRealRect *invalidRect );

	/** Retrieves the display mode for a view.
			@param view	The view reference, or \c NULL for the current view.
			@param style [out] A buffer in which to return the style, a logical OR of these bit flags:<br>
				\c #kVsArtwork, \c #kVsPreview, \c #kVsRaster, \c #kVsOpaque, \c #kVsInk
		*/
	AIAPI AIErr (*GetDocumentViewStyle)( AIDocumentViewHandle view,  short *style );

	/** Sets the invalid rectangle for all views of a viewed document. This is the area
		that encloses (at least) the portions of the viewed document that have been
		changed and so need to be redrawn in all views of that document.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect The new area, in artwork coordinates.
			@see \c #SetDocumentViewInvalidRect()
		*/
	AIAPI AIErr (*SetDocumentViewInvalidDocumentRect)( AIDocumentViewHandle view, const AIRealRect *invalidRect );

	/** Reports whether page tiling is shown for the current view. Each view has its own setting.
			@param show [out] A buffer in which to return true if page tiling is shown.
		*/
	AIAPI AIErr (*GetShowPageTiling) ( ASBoolean *show );

	/** Sets the page tiling mode for the current view. Each view has its own setting.
			@param show True to turn page tiling on, false to turn it off.
		*/
	AIAPI AIErr (*SetShowPageTiling) ( ASBoolean show );

	/** Retrieves grid options for a view.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the grid is visible.
			@param snap [out] A buffer in which to return true if the snap-to-grid is on.
		*/
	AIAPI AIErr (*GetGridOptions) ( AIDocumentViewHandle view, ASBoolean* show, ASBoolean* snap );

	/**  Sets grid options for a view
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the grid visible, false to hide it.
			@param snap True to turn snap-to-grid on, false to turn it off.
		*/
	AIAPI AIErr (*SetGridOptions) ( AIDocumentViewHandle view, ASBoolean show, ASBoolean snap );

	/** Reports whether the transparency grid is shown in a view.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the transparency grid is visible.
		*/
	AIAPI AIErr (*GetShowTransparencyGrid) ( AIDocumentViewHandle view, ASBoolean* show );

	/** Sets whether the transparency grid is shown in the view.
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the transparency grid visible, false to hide it.
		*/
	AIAPI AIErr (*SetShowTransparencyGrid) ( AIDocumentViewHandle view, ASBoolean show );

	/** Retrieves the document displayed in a view.
			@param view The view reference, or \c NULL for the current view.
			@param document [out] A buffer in which to return the document reference.
		*/
	AIAPI AIErr (*GetDocumentViewDocument) ( AIDocumentViewHandle view, AIDocumentHandle *document );

	/** Forces all document views to not be obscured by the Control palette.
		*/
	AIAPI AIErr (*ForceDocumentViewsOnScreen) ( void );

	/** Retrieves the visibility state of the guides.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the guides are visible.
		*/
	AIAPI AIErr (*GetShowGuides) ( AIDocumentViewHandle view, ASBoolean* show );

	/** Sets the visibility state of the guides.
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the guides visible, false to hide them.
		*/
	AIAPI AIErr (*SetShowGuides) ( AIDocumentViewHandle view, ASBoolean show );

 	/** Retrieves the visibility state of the edges of the selection.
 			@param view The view reference, or \c NULL for the current view.
 			@param show True to make the edges visible, false to hide them.
 		*/
 	AIAPI AIErr (*GetShowEdges) ( AIDocumentViewHandle view, ASBoolean* show );

 	/** Sets the visibility state of the edges of the selection.
 			@param view The view reference, or \c NULL for the current view.
 			@param show True to make the edges visible, false to hide them.
 		*/
 	AIAPI AIErr (*SetShowEdges) ( AIDocumentViewHandle view, ASBoolean show );

} ;


#include "AIHeaderEnd.h"


#endif
