#ifndef __AI120Annotator__
#define __AI120Annotator__

/*
 *        Name:	AI120Annotator.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Annotator Suite.
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

#define kAIAnnotatorSuiteVersion3	AIAPI_VERSION(3)
/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AIAnnotator.h"
#endif

/*******************************************************************************
 **
 **	Suite Record
 **
 **/


/**
	The annotator suite allows plugins to draw annotations into the document window
	that are not a part of the artwork. These annotations are drawn on top after all
	artwork has been drawn. For example, selection handles are annotations.

	In order to be given an opportunity to draw annotations a plugin must first call
	\c #AddAnnotator() to register itself as an annotator. Typically this is done at
	plugin startup but it may be done at any time. An annotator may be active or
	inactive. Only active annotators receive requests to draw.

	A plugin annotator can receive two messages via its main entry point. These
	messages have caller \c #kCallerAIAnnotation. The messages are:
	\li \c kSelectorAIDrawAnnotation  A request for the annotator to draw its
		annotations. In this case the message structure is an \c ::AIAnnotatorMessage
		that supplies information about the document view to be drawn.
	\li \c kSelectorAIInvalAnnotation A request to invalidate the bounds of any
		annotations in the current document view. In response the plugin should
		call \c #InvalAnnotationRect() for each annotation.

	In addition to responding to the previous two messages a plugin annotator
	will typically call \c #InvalAnnotationRect() whenever its set of annotations
	changes. This indicates the parts of the document view that need to be
	redrawn as a consequence of the changes.
 */

typedef struct {
	/** Adds a new annotator to your plug-in. Typically called during startup.

		@param self The startup plug-in.
		@param name The annotator’s display name.
		@param notifier [out] A buffer in which to return a unique identifier for the new annotator.
		*/

	AIAPI AIErr (*AddAnnotator) ( SPPluginRef self, char *name, AIAnnotatorHandle *notifier );

	/** Retrieves the display name of this annotator.

			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param name [out] A buffer in which to return the display name.
		*/
	AIAPI AIErr (*GetAnnotatorName) ( AIAnnotatorHandle notifier, char **name );

	/** Reports whether an annotator is currently active.

			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param active [out] A buffer in which to return the result, true if the annotator is active.
		*/
	AIAPI AIErr (*GetAnnotatorActive) ( AIAnnotatorHandle notifier, AIBoolean *active );

	/**  Activates or deactivates an annotator.

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param active  True to activate the annotator, false to deactivate it.
		*/
	AIAPI AIErr (*SetAnnotatorActive) ( AIAnnotatorHandle notifier, AIBoolean active );

	/** Retrieves the plug-in that defines this annotator.

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetAnnotatorPlugin) ( AIAnnotatorHandle notifier, SPPluginRef *plugin );

	/** Gets the number of currently registered annotators.
	Use with \c #GetNthAnnotator() to iterate through all annotators.

		@param [out] A buffer in which to return the number of annotators.
		*/
	AIAPI AIErr (*CountAnnotators) ( long *count );
	/** Retrieves a registered annotator by position index.
	 Use with \c #CountAnnotators() to iterate through all registered annotators.

		@param n The index, in the range \c [1..numAnnotators].
		@param notifier [out] A buffer in which to return the annotator reference.
		*/
	AIAPI AIErr (*GetNthAnnotator) ( long n, AIAnnotatorHandle *notifier );

	/** Invalidates a rectangular area of the document so that drawing can be performed.
	After using this function to determine the area in which to draw,
	you can call \c ADMDrawer to perform platform-independent drawing.
	For example:
	@code
	portBounds.left = _AIRealRoundToShort(updateRect.left) - 1;
	portBounds.top = _AIRealRoundToShort(updateRect.top) + 1;
	portBounds.right = _AIRealRoundToShort(updateRect.right) + 1;
	portBounds.bottom = _AIRealRoundToShort(updateRect.bottom) - 1;

	sAIAnnotator->InvalAnnotationRect(fDocumentView, &portBounds);
	@endcode

		@param view The document view. See \c apiAIDocumentView.h
		@param annotationBounds A pointer to rectangle structure that specifies the area boundaries.
		*/
	AIAPI AIErr (*InvalAnnotationRect)( AIDocumentViewHandle view, AIRect *annotationBounds );

	/** Adds an annotator to a different plug-in (for instance, one that does on-screen drawing).
	This is the alternate plug-in; you can retrieve the handle to it using \c #GetAnnotatorAlternatePlugin().

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param plugin The handle for the alternate plug-in.
		*/
	AIAPI AIErr (*SetAnnotatorAlternatePlugin) ( AIAnnotatorHandle notifier, SPPluginRef plugin );

	/** Retrieves the alternate plugin for the annotator, to which it was added with \c #SetAnnotatorAlternatePlugin().

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param plugin [out] A buffer in which to return the alternate plug-in reference.
		*/
	AIAPI AIErr (*GetAnnotatorAlternatePlugin) ( AIAnnotatorHandle notifier, SPPluginRef *plugin );

} AI120AnnotatorSuite;


#endif