/*******************************************************************************
*
* ADMDrawer.h -- ADM Drawer Suite
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
*
* Started by Dave Lazarony, 06 Mar 1996
*
********************************************************************************/

/** @file ADMDrawer.h ADM Drawer Suite */

#ifndef __ADMDrawer__
#define __ADMDrawer__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef _ADMAGMTYPES_H_
#include "ADMAGMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------

/** Pixel combination method constants */
typedef enum
{
	/** Replace old value with new value (overwrites existing pixels) */
	kADMNormalMode = 0,
	/** Perform exclusive OR of old and new value (inverts overwritten pixels) */
	kADMXORMode,
	/** Internal */
	kADMDummyMode = 0xFFFFFFFF
}
ADMDrawMode;


/** Font information. All measurements are in document points (1/72 inch).
	@see \c #ADMDrawerSuite6::GetFontInfo(), \c #ADMDrawerSuite6::GetThisFontInfo() */
typedef struct
{
	/** Character height */
	ADMInt32 height;
	/** Ascent (height above baseline) */
	ADMInt32 ascent;
	/** Descent (height below baseline) */
	ADMInt32 descent;
	/** Leading (space between characters) */
	ADMInt32 leading;
	/** Maximum character width */
	ADMInt32 maxWidth;
}
ADMFontInfo;


/** Recoloring style constants.
	@see \c #ADMDrawerSuite6::DrawRecoloredResPicture(),
		\c #ADMDrawerSuite6::DrawRecoloredResPictureCentered(),
		\c #ADMDrawerSuite6::DrawRecoloredIcon(),
		\c #ADMDrawerSuite6::DrawRecoloredIconCentered()
		*/
typedef enum
{
	/** Do not recolor icon */
	kADMNoRecolor,
	/** Recolor icon for active (selected) state */
	kADMActiveRecolor,
	/** Recolor icon for inactive (unselected) state */
	kADMInactiveRecolor,
	/** Recolor icon for disabled (grayed) state */
	kADMDisabledRecolor,
	/** Recolor icon for transparency; replaces white
		in the image with the background color. */
	kADMBackgroundRecolor,		// DRL 2004-08-26  For CS2 Tab Palette Look. Replaces the white in the image with the background color.
	/** Internal */
	kADMDummyRecolor = 0xFFFFFFFF
}
ADMRecolorStyle;

// majones: UNICODE 12/19/02 DrawText needs to be undefined as it it clashes with
//          a Microsoft API definition in Winuser.h when the UNICODE pre-processor
//          option is used.
#undef DrawText

// =============================================================================
//		* ADM Drawer Suite
// =============================================================================

/** Drawer suite name */
#define kADMDrawerSuite "ADM Drawer Suite"
/** Drawer suite version */
#define kADMDrawerSuiteVersion6 6

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite allows you to modify or replace the way dialog, items,
	and lists are drawn on the screen.

	You can modify or replace the default drawing method of a dialog or dialog
	item by providing your own handler, in the form of a drawing callback
	procedure, \c #ADMItemDrawProc, associated with the dialog or item. See
	\c #ADMDialogSuite10::SetDrawProc() and \c #ADMItemSuite9::SetDrawProc().

	The drawing of list entries (\c #ADMEntryRef or \c #ADMListEntryRef) is handled
	by the drawing callback (\c #ADMEntryDrawProc) of the containing list
	(\c #ADMListRef or	\c #ADMHierarchyListRef). See \c #ADMListSuite4::SetDrawProc()
	and \c #ADMHierarchyListSuite5::SetDrawProc().

	The drawer object, \c #ADMDrawerRef, provides access to the
	platform-independent imaging functions in this suite, which include basic
	imaging, such as \c #DrawLine(), and text handling.	The suite makes
	use of the streamlined ADM color and font style constants, and provides functions
	that simplify the implementation of many standard dialog elements, such as
	\c #DrawIcon() and \c #DrawUpArrow().

	All drawing is done in coordinates local to the object being drawn, whose
	origin is, by default, the top-left corner of the bounding rectangle.
	The drawer has an update region, and draws only within that region.
	You can further specify a clipping path for a drawer; pixels that lie
	outside the clip region are not drawn.

	To invoke the default drawing method of a dialog, item, or list, call
	that object's default drawing handler from within your handler; for example,
	\c #ADMItemSuite9::DefaultDraw().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMDrawerSuite and \c #kADMDrawerSuiteVersion6.
	*/
typedef struct ADMDrawerSuite6
{

	// port accessor

	/** Retrieves a platform-specific port reference for a drawer,
		which you can use to draw directly to the window with platform-specific
		code.
			@param inDrawer The drawing object.
			@return The port reference.
		*/
	ADMPortRef ADMAPI (*GetPortRef)(ADMDrawerRef inDrawer);

	// clear entire area of drawer

	/** Fills the area of the object being drawn with the background color.
			@param inDrawer The drawing object.
			@return Nothing.
		*/
	void ADMAPI (*Clear)(ADMDrawerRef inDrawer);

	// bounds accessor

	/** Retrieves the size of the object being drawn.
			@param inDrawer The drawing object.
			@param outBoundsRect [out] A buffer in which to return the
				object's bounding box relative to its own origin,
				in which  \c left and \c top  are both 0, and \c bottom and
				\c right provide the height and width in pixels.
			@return Nothing.
		*/
	void ADMAPI (*GetBoundsRect)(ADMDrawerRef inDrawer, ADMRect* outBoundsRect);

	// clipping

	/**	Retrieves the clipping region for a drawer.	Pixels that lie outside this
		region are not drawn. The clip rectangle defaults to the bounds rectangle.
			@param inDrawer The drawing object.
			@param outClipRect [out] A buffer in which to return the
				clipping region's rectangle, or, if the clipping region
				has been set with \c #SetClipPolygon(), the bounding box
				of the clip polygon.
			@return Nothing.
			@see \c #SetClipRect(), \c #SetClipPolygon()
		*/
	void ADMAPI (*GetClipRect)(ADMDrawerRef inDrawer, ADMRect* outClipRect);

	/**	Sets the clipping region for a drawer to a rectangle. Pixels that lie outside this
		region are not drawn. The clip rectangle defaults to the bounds rectangle.
			@param inDrawer The drawing object.
			@param inClipRect The clipping region's rectangle. Coordinates
				are in pixels, relative to the origin (top left) of the
				object being drawn.
			@return Nothing.
			@see \c #IntersectClipRect(), \c #UnionClipRect(), \c #SubtractClipRect(),
				\c #SetClipPolygon()
		*/
	void ADMAPI (*SetClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	/**	Modifies the clipping region for a drawer, limiting it to the intersection
		of the current clipping region with a specified rectangle.
			@param inDrawer The drawing object.
			@param inClipRect The rectangle to intersect with the current
				clipping region. Coordinates are in pixels, relative to the
				origin (top left) of the object being drawn.
			@return Nothing.
			@see \c #SetClipRect(), \c #UnionClipRect(), \c #SubtractClipRect(),
				\c #SetClipPolygon()
		*/
	void ADMAPI (*IntersectClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	/**	Modifies the clipping region for a drawer, expanding it to the union
		of the current clipping region with a specified rectangle.
			@param inDrawer The drawing object.
			@param inClipRect The rectangle to form a union with the current
				clipping region. Coordinates are in pixels, relative to the
				origin (top left) of the object being drawn.
			@return Nothing.
			@see \c #SetClipRect(), \c #IntersectClipRect(),  \c #SubtractClipRect(),
				\c #SetClipPolygon()
		*/
	void ADMAPI (*UnionClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	/**	Modifies the clipping region for a drawer, removing a specified rectangle
		from the current clipping region.
			@param inDrawer The drawing object.
			@param inClipRect The rectangle to remove from the current
				clipping region. Coordinates are in pixels, relative to the
				origin (top left) of the object being drawn.
			@return Nothing.
			@see \c #SetClipRect(), \c #IntersectClipRect(),  \c #UnionClipRect(),
				\c #SetClipPolygon()
		*/
	void ADMAPI (*SubtractClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	/**	Sets the clipping region for a drawer to a polygon. Pixels that lie outside this
		region are not drawn.
			@param inDrawer The drawing object.
			@param inPoints An array of points that define the polygon. Coordinates
				are in pixels, relative to the origin (top left) of the
				object being drawn.
			@param inNumPoints The number of points in the array.
			@return Nothing.
			@see \c #IntersectClipPolygon(), \c #UnionClipPolygon(), \c #SubtractClipPolygon(),
				\c #SetClipRect()
		*/
	void ADMAPI (*SetClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	/**	Modifies the clipping region for a drawer, limiting it to the intersection
		of the current clipping region with a specified polygon.
				@param inDrawer The drawing object.
				@param inPoints An array of points that define the polygon. Coordinates
					are in pixels, relative to the origin (top left) of the
					object being drawn.
				@param inNumPoints The number of points in the array.
				@return Nothing.
				@see \c #SetClipPolygon(), \c #UnionClipPolygon(), \c #SubtractClipPolygon(),
					\c #SetClipRect()
		*/
	void ADMAPI (*IntersectClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	/**	Modifies the clipping region for a drawer, expanding it to the union
		of the current clipping region with a specified polygon.
			@param inDrawer The drawing object.
			@param inPoints An array of points that define the polygon. Coordinates
				are in pixels, relative to the origin (top left) of the
				object being drawn.
			@param inNumPoints The number of points in the array.
			@return Nothing.
			@see \c #SetClipPolygon(), \c #IntersectClipPolygon(), \c #SubtractClipPolygon(),
				\c #SetClipRect()
		*/
	void ADMAPI (*UnionClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	/**	Modifies the clipping region for a drawer, removing a specified polygon
		from the current clipping region.
			@param inDrawer The drawing object.
			@param inPoints An array of points that define the polygon. Coordinates
				are in pixels, relative to the origin (top left) of the
				object being drawn.
			@param inNumPoints The number of points in the array.
			@return Nothing.
			@see \c #SetClipPolygon(), \c #IntersectClipPolygon(), \c #UnionClipPolygon(),
				\c #SetClipRect()
		*/
	void ADMAPI (*SubtractClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	// port origin

	/**	Retrieves the origin (top left corner) of the drawing region.
		Normally (0,0), but can be changed with \c #SetOrigin().
			@param inDrawer The drawing object.
			@param outOrigin [out] A buffer in which to return the origin point.
				Coordinates are in pixels, relative to the origin (top left) of the
				object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*GetOrigin)(ADMDrawerRef inDrawer, ADMPoint* outOrigin);

	/**	Sets the origin (top left corner) of the drawing region.
			@param inDrawer The drawing object.
			@param inOrigin The new origin point. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*SetOrigin)(ADMDrawerRef inDrawer, const ADMPoint* inOrigin);

	// drawing state accessors

	/**	Retrieves the RGB color currently used for drawing.
			@param inDrawer The drawing object.
			@param outColor [out] A buffer in which to return the color value.
			@return Nothing.
		*/
	void ADMAPI (*GetRGBColor)(ADMDrawerRef inDrawer, ADMRGBColor* outColor);

	/**	Sets the RGB color to use for drawing. To make your custom dialog elements
		consistent with application dialogs, use ADM colors instead.
			@param inDrawer The drawing object.
			@param inColor The color value.
			@return Nothing.
			@see \c #SetADMColor()
		*/
	void ADMAPI (*SetRGBColor)(ADMDrawerRef inDrawer, const ADMRGBColor* inColor);

	/**	Retrieves the ADM color currently used for drawing.	These constants
		identify colors by their usage, and help to make your custom dialog elements
		consistent with application dialogs.
			@param inDrawer The drawing object.
			@param outColor [out] A buffer in which to return the color constant.
			@return Nothing.
		*/
	ADMColor ADMAPI (*GetADMColor)(ADMDrawerRef inDrawer);

	/**	Sets the ADM color currently used for drawing.	These constants
		identify colors by their usage, and help to make your custom dialog elements
		consistent with application dialogs.
			@param inDrawer The drawing object.
			@param inColor The color constant.
			@return Nothing.
		*/
	void ADMAPI (*SetADMColor)(ADMDrawerRef inDrawer, ADMColor inColor);

	/**	Retrieves the pixel combination method used when overwriting
		existing pixels.
			@param inDrawer The drawing object.
			@return The drawing mode constant.
		*/
	ADMDrawMode ADMAPI (*GetDrawMode)(ADMDrawerRef inDrawer);

	/**	Sets the pixel combination method to use when overwriting
		existing pixels.
			@param inDrawer The drawing object.
			@param inDrawMode The drawing mode constant.
			@return Nothing.
		*/
	void ADMAPI (*SetDrawMode)(ADMDrawerRef inDrawer, ADMDrawMode inDrawMode);

	/**	Retrieves the font style used when drawing text.
			@param inDrawer The drawing object.
			@return The font-style constant.
		*/
	ADMFont ADMAPI (*GetFont)(ADMDrawerRef inDrawer);

	/**	Sets the font style to use when drawing text. These constants
		identify fonts by their usage, and help to make your custom dialog
		elements consistent with application dialogs.
			@param inDrawer The drawing object.
			@param inFont The font-style constant.
			@return Nothing.
		*/
	void ADMAPI (*SetFont)(ADMDrawerRef inDrawer, ADMFont inFont);

	/** Reports whether the drawer uses the palette background color
		or default background color.
			@param inDrawer The drawing object.
			@return True if the drawer uses the palette background color,
				false if it uses the default (\c #kADMBackgroundColor).
		*/
	ADMBoolean ADMAPI (*GetUsePaletteBGColor)(ADMDrawerRef inDrawer);

	/** Sets whether the drawer uses the palette background color
		or default background color.
			@param inDrawer The drawing object.
			@param inUsePaletteBGColor True to use the palette background color,
				false to use the default (\c #kADMBackgroundColor).
			@return Nothing.
		*/
	void ADMAPI (*SetUsePaletteBGColor)(ADMDrawerRef inDrawer, ADMBoolean inUsePaletteBGColor);

	// simple shape drawers

	/**	Draws a line 1 point in width in the current color, between
		specified points. Coordinates are in pixels,
		relative to the origin (top left) of the object being drawn.
			@param inDrawer The drawing object.
			@param inStartPoint The starting point of the line.
			@param 	inEndPoint The ending point of the line.
			@return Nothing.
		*/
	void ADMAPI (*DrawLine)(ADMDrawerRef inDrawer, const ADMPoint* inStartPoint,
				const ADMPoint* inEndPoint);

	/**	Draws a polygon, using a line 1 point in width in the current color,
		between specified points. Coordinates are in pixels,
		relative to the origin (top left) of the object being drawn.
			@param inDrawer The drawing object.
			@param inPoints An array of points that specify the polygon.
			@param 	inNumPoints The number of points in the array.
			@return Nothing.
		*/
	void ADMAPI (*DrawPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	/**	Draws a polygon filled with the current color, a specified by
		a line 1 point in width between specified points. Coordinates are in pixels,
		relative to the origin (top left) of the object being drawn.
			@param inDrawer The drawing object.
			@param inPoints An array of points that specify the polygon.
			@param 	inNumPoints The number of points in the array.
			@return Nothing.
		*/
	void ADMAPI (*FillPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	/**	Draws a rectangle, using a  line 1 point in width in the current color.
		Coordinates are in pixels, relative to the origin (top left) of the
		object being drawn.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*DrawRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a rectangle filled with the current color.
		Coordinates are in pixels, relative to the origin (top left) of the
		object being drawn.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*FillRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a rectangle filled with the background color.
		Coordinates are in pixels, relative to the origin (top left) of the
		object being drawn.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*ClearRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a rectangle filled with the background color, with top and left
		edges in a darker gray than the bottom and right edges, to create a sunken
		appearance. Coordinates are in pixels, relative to the origin (top left) of the
		object being drawn.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*DrawSunkenRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a rectangle filled with the background color, with top and left
		edges in a lighter gray than the bottom and right edges, to create a raised
		appearance. Coordinates are in pixels, relative to the origin (top left) of the
		object being drawn.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*DrawRaisedRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Inverts all pixels within a rectangular region. Black and white are
		reversed; other colors are replaced by their RGB inverses.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*InvertRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a line 1-point in width in the current color outlining
		an oval bounded by a specified rectangle. The interior of the oval
		is not filled.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*DrawOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a line 1-point in width in the current color outlining
		an oval bounded by a specified rectangle, and fills it with the
		current color.
			@param inDrawer The drawing object.
			@param inRect The bounding rectangle.
			@return Nothing.
		*/
	void ADMAPI (*FillOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// AGM access

	/** Retrieves an Adobe Graphics Manager (AGM) port reference for a drawing object,
		which you can use to draw directly to the window with AGM imaging functions.
			@param inDrawer The drawing object.
			@return The port reference.
			@see \c ADMAGMTypes.h
		*/
	ADMAGMPortPtr ADMAPI (*GetAGMPort)(ADMDrawerRef inDrawer);

	/** @deprecated Do not use.*/
	void ADMAPI (*DrawAGMImage)(ADMDrawerRef inDrawer,
				const struct _t_ADMAGMImageRecord* inImage,
				const ADMFixedMatrix* inMatrix, ADMInt32 inFlags);

	// resource drawing

	/**	Draws a predefined picture defined by an application resource.
			@param inDrawer The drawing object.
			@param inPluginRef The plug-in object that owns the resource.
				Obtain this from the object being drawn, with, for example,
				\c #ADMItemSuite9::GetPluginRef().
			@param inRsrcID The resource identifier.
				\li In Mac OS, the resource type, which is 'PICT'
				\li In Windows, the bitmap resource.
			@param inTopLeftPoint The anchor point for the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint);

	/**	Draws a predefined picture defined by an application resource, placing
		it so that it is centered in a specified rectangle.
			@param inDrawer The drawing object.
			@param inPluginRef The plug-in object that owns the resource.
				Obtain this from the object being drawn, with, for example,
				\c #ADMItemSuite9::GetPluginRef().
			@param inRsrcID The resource identifier.
				\li In Mac OS, the resource type, which is 'PICT'
				\li In Windows, the bitmap resource.
			@param inRect The rectangle in which to center the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawResPictureCentered)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMRect* inRect);

	/**	Draws a predefined picture defined by an application resource, and recolors
		it to indicate a specific state (such as disabled).
			@param inDrawer The drawing object.
			@param inPluginRef The plug-in object that owns the resource.
				Obtain this from the object being drawn, with, for example,
				\c #ADMItemSuite9::GetPluginRef().
			@param inRsrcID The resource identifier.
				\li In Mac OS, the resource type, which is 'PICT'
				\li In Windows, the bitmap resource.
			@param inTopLeftPoint The anchor point for the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@param inStyle The style constant that indicates the state.
			@return Nothing.
		*/
	void ADMAPI (*DrawRecoloredResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	/**	Draws a predefined picture defined by an application resource, placing
		it so that it is centered in a specified rectangle, and recoloring
		it to indicate a specific state (such as disabled).
			@param inDrawer The drawing object.
			@param inPluginRef The plug-in object that owns the resource.
				Obtain this from the object being drawn, with, for example,
				\c #ADMItemSuite9::GetPluginRef().
			@param inRsrcID The resource identifier.
				\li In Mac OS, the resource type, which is 'PICT'
				\li In Windows, the bitmap resource.
			@param inRect The rectangle in which to center the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@param inStyle The style constant that indicates the state.
			@return Nothing.
		*/
	void ADMAPI (*DrawRecoloredResPictureCentered)(ADMDrawerRef inDrawer,
				SPPluginRef inPluginRef, ADMInt32 inRsrcID, const ADMRect* inRect,
				ADMRecolorStyle inStyle);

	// icon drawing

	/**	Draws a predefined icon defined by a plug-in resource. Obtain the plug-in
		from the object being drawn, with, for example, \c #ADMItemSuite9::GetPluginRef(),
		then obtain the icon with \c #ADMIconSuite2::GetFromResource().
			@param inDrawer The drawing object.
			@param inIcon The icon object.
			@param inTopLeftPoint The anchor point for the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMPoint* inTopLeftPoint);

	/**	Draws a predefined icon defined by a plug-in resource, placing
		it so that it is centered in a specified rectangle. Obtain the plug-in
		from the object being drawn, with, for example, \c #ADMItemSuite9::GetPluginRef(),
		then obtain the icon with \c #ADMIconSuite2::GetFromResource().
			@param inDrawer The drawing object.
			@param inIcon The icon object.
			@param inRect The rectangle in which to center the icon.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMRect* inRect);

	/**	Draws a predefined icon defined by a plug-in resource, and recolors
		it to indicate a specific state (such as disabled). Obtain the plug-in
		from the object being drawn, with, for example, \c #ADMItemSuite9::GetPluginRef(),
		then obtain the icon with \c #ADMIconSuite2::GetFromResource().
			@param inDrawer The drawing object.
			@param inIcon The icon object.
			@param inTopLeftPoint The anchor point for the picture.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@param inStyle The style constant that indicates the state.
			@return Nothing.
		*/
	void ADMAPI (*DrawRecoloredIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	/**	Draws a predefined icon defined by a plug-in resource, placing
		it so that it is centered in a specified rectangle, and recolors
		it to indicate a specific state (such as disabled). Obtain the plug-in
		from the object being drawn, with, for example, \c #ADMItemSuite9::GetPluginRef(),
		then obtain the icon with \c #ADMIconSuite2::GetFromResource().
			@param inDrawer The drawing object.
			@param inIcon The icon object.
			@param inRect The rectangle in which to center the icon.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@param inStyle The style constant that indicates the state.
			@return Nothing.
		*/
	void ADMAPI (*DrawRecoloredIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMRect* inRect, ADMRecolorStyle inStyle);

	/**	Retrieves the size of a predefined picture defined by an application resource.
		Use to decide whether scaling is needed, for example, or how to place the image.
			@param inDrawer The drawing object.
			@param inPluginRef The plug-in object that owns the resource.
				Obtain this from the object being drawn, with, for example,
				\c #ADMItemSuite9::GetPluginRef().
			@param inRsrcID The resource identifier.
				\li In Mac OS, the resource type, which is 'PICT'
				\li In Windows, the bitmap resource.
			@param outBoundsRect [out] A buffer in which to return the
				image's bounding box relative to its own origin,
				in which  \c left and \c top  are both 0, and \c bottom and
				\c right provide the height and width in pixels.
			@return Nothing.
		*/
	void ADMAPI (*GetResPictureBounds)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, ADMRect* outBoundsRect);

	// text drawing

	/** Retrieves the width of text specified as a C string,
		when drawn in the font style of a drawer.
			@param inDrawer The drawing object.
			@param inText The text string.
			@return The width in pixels.
		*/
	ADMInt32 ADMAPI (*GetTextWidth)(ADMDrawerRef inDrawer, const char* inText);

	/** Retrieves the width of text specified as a Unicode string,
		when drawn in the font style of a drawer.
			@param inDrawer The drawing object.
			@param inText The text string.
			@return The width in pixels.
		*/
	ADMInt32 ADMAPI (*GetTextWidthW)(ADMDrawerRef inDrawer, const ADMUnicode* inText);

	/**	Retrieves information such as font metrics from the current font for
		a drawer. Use this, for example, to choose where to place text.
			@param inDrawer The drawing object.
			@param outFontInfo [out] A buffer in which to return the font information.
			@return Nothing.
			@see \c #GetThisFontInfo()
		*/
	void ADMAPI (*GetFontInfo)(ADMDrawerRef inDrawer, ADMFontInfo* outFontInfo);

	/**	Draws text specified by a C string at a specified position,
		using the current font style.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inPoint The point at which to start drawing.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawText)(ADMDrawerRef inDrawer, const char* inText, const ADMPoint* inPoint);

	/**	Draws text specified by a Unicode string at a specified position,
		using the current font style.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inPoint The point at which to start drawing.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMPoint* inPoint);

	/**	Draws text specified by a C string using the current font style,
		placing it so that it is left justified within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidth()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextLeft)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);

	/**	Draws text specified by a Unicode string using the current font style,
		placing it so that it is left justified within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidthW()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextLeftW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);

	/**	Draws text specified by a C string using the current font style,
		placing it so that it is centered within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidth()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextCentered)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);

	/**	Draws text specified by a Unicode string using the current font style,
		placing it so that it is centered within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidthW()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextCenteredW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);

	/**	Draws text specified by a C string using the current font style,
		placing it so that it is right justified within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidth()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextRight)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);

	/**	Draws text specified by a Unicode string using the current font style,
		placing it so that it is right justified within a specified rectangle.
		Text is clipped to fit the region if necessary.	Use \c #GetTextWidthW()
		and \c #GetFontInfo() to determine the size needed.
			@param inDrawer The drawing object.
			@param inText The text string.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextRightW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);

	// standard arrows

	/**	Draws an up-pointing triangular arrow button to fill the area
		of a specified rectangle. This is the arrow used in spin-edit items.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawUpArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a down-pointing triangular arrow button to fill the area
		of a specified rectangle. This is the arrow used in spin-edit items.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawDownArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a left-pointing triangular arrow button to fill the area
		of a specified rectangle. This is the arrow used in spin-edit items.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawLeftArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	/**	Draws a right-pointing triangular arrow button to fill the area
		of a specified rectangle. This is the arrow used in spin-edit items.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*DrawRightArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// drawer creation/destruction

	/**	Creates a drawing object. ADM does this automatically before calling
		a drawing procedure, and passes the object to the procedure.
	    If you create a drawing object, you must free it when it is no
		longer needed, using \c #Destroy().
			@param inPortRef The window drawing port for the object to be drawn.
				Obtain the window (with, for example, \c #ADMDialogSuite10::GetWindowRef())
				then use it to object the port with \c #GetADMWindowPort().
			@param inBoundsRect Optional. The bounding box of the update region. All drawing
				is within this region, which can be further restricted with a clipping path.
				Default is the bounding box of the object being drawn.
				Coordinates are in pixels, relative to the origin (top left) of the
				object being drawn.
			@param inFont The font style to use for drawing text, a font-style constant.
			@return The new drawing object.
		*/
	ADMDrawerRef ADMAPI (*Create)(ADMPortRef inPortRef, const ADMRect* inBoundsRect, ADMFont inFont);

	/**	Frees memory and resources associated with a drawing object that you
		have created using \c #Create(). Drawers created automatically by ADM do
		not need to be explicitly destroyed.
			@param inDrawer The drawing object.
			@return Nothing.
		*/
	void ADMAPI (*Destroy)(ADMDrawerRef inDrawer);

	// image drawing

	/**	Draws an ADM image at a specified position.
			@param inDrawer The drawing object.
			@param inImage The image object.
			@param inTopLeftPoint The anchor point for the image.
				Coordinates are in pixels, relative to the origin (top left)
				of the object being drawn.
			@return Nothing.
			@see \c #ADMImageSuite2::Create(), \c #ADMImageSuite2::CreateBitmap(),
				\c #ADMImageSuite2::CreateOffscreen(),
		*/
	void ADMAPI (*DrawADMImage)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMPoint* inTopLeftPoint);

	/**	Draws an ADM image, centered within a specified rectangle.
			@param inDrawer The drawing object.
			@param inImage The image object.
			@param inRect The rectangle. Coordinates are in pixels, relative to the
				origin (top left) of the object being drawn.
			@return Nothing.
			@see \c #ADMImageSuite2::Create(), \c #ADMImageSuite2::CreateBitmap(),
				\c #ADMImageSuite2::CreateOffscreen(),
		*/
	void ADMAPI (*DrawADMImageCentered)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMRect* inRect);

	// platform port accessors

	/** Creates an ADM drawing port for a window. Free this object
		when you no longer need it, using \c #ReleaseADMWindowPort().
			@param inWindowRef The window reference, as obtained from
				object being drawn, with, for example, \c #ADMDialogSuite10::GetWindowRef().
			@return The ADM port reference.
			@see \c #Create()
		*/
	ADMPortRef ADMAPI (*GetADMWindowPort)(ADMWindowRef inWindowRef);

	/** Frees memory and resources use for an ADM drawing port, created with
		\c #GetADMWindowPort().
			@param inWindowRef The window reference.
			@param inPort The ADM port reference.
			@return Nothing.
		*/
	void ADMAPI (*ReleaseADMWindowPort)(ADMWindowRef inWindowRef, ADMPortRef inPort);

	// font information

	/**	Retrieves information about the font used for a specific
		font style. Font-style constants identify fonts by their usage,
		and help to make your custom dialog elements consistent with application dialogs.
			@param inFont The font constant.
			@param outFontInfo [out] A buffer in which to return the font information.
			@return Nothing.
			@see \c #GetFontInfo()
		*/
	void ADMAPI (*GetThisFontInfo)(ADMFont inFont, ADMFontInfo* outFontInfo);

	// text drawing

	/**	Draws text specified by a C string using the current font style,
		flowing it to fit within a specified rectangle.
		Text is clipped to fit the region if necessary.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextInABox)(ADMDrawerRef inDrawer, const ADMRect* inRect,
				const char* inText);
	/**	Draws text specified by a Unicode string using the current font style,
		flowing it to fit within a specified rectangle.
		Text is clipped to fit the region if necessary.
			@param inDrawer The drawing object.
			@param inRect The rectangle. Coordinates are in pixels,
				relative to the origin (top left) of the object being drawn.
			@param inText The text string.
			@return Nothing.
		*/
	void ADMAPI (*DrawTextInABoxW)(ADMDrawerRef inDrawer, const ADMRect* inRect,
				const ADMUnicode* inText);

	// update area accessor

	/**	Retrieves the update region of a drawer, as specified on creation.
		The default update region is the same as the bounding box of the
		object being drawn.
			@param inDrawer The drawing object.
			@param outRect [out] A buffer in which to return the bounding box.
				Coordinates are in pixels, relative to the
				origin (top left) of the object being drawn.
			@return Nothing.
		*/
	void ADMAPI (*GetUpdateRect)(ADMDrawerRef inDrawer, ADMRect* outRect);

	// text measurement

	/** Retrieves the height of a rectangle of a specified width that
		is needed to fit text specified as a C string,
		when drawn in the font style of a drawer.
			@param inDrawer The drawing object.
			@param inWidth The width of the rectangle, in pixels
			@param inText The text string.
			@return The height in pixels.
		*/
	ADMInt16 ADMAPI (*GetTextRectHeight)(ADMDrawerRef inDrawer, ADMInt16 inWidth,
				const char* inText);
	/** Retrieves the height of a rectangle of a specified width that
		is needed to fit text specified as a Unicode string,
		when drawn in the font style of a drawer.
			@param inDrawer The drawing object.
			@param inWidth The width of the rectangle, in pixels
			@param inText The text string.
			@return The height in pixels.
		*/
	ADMInt16 ADMAPI (*GetTextRectHeightW)(ADMDrawerRef inDrawer, ADMInt16 inWidth,
				const ADMUnicode* inText);

}
ADMDrawerSuite6;

typedef ADMDrawerSuite6 ADMDrawerSuite;
#define kADMDrawerSuiteVersion kADMDrawerSuiteVersion6

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMDrawerOld__
#ifdef MAC_ENV
#include "ADMDrawerOld.h"
#else
#include ".\Legacy\ADMDrawerOld.h"
#endif
#endif


// -----------------------------------------------------------------------------

#endif	// __ADMDrawer__
