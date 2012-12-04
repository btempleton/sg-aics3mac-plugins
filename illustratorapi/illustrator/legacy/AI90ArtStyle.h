/*
 *        Name:	AI90ArtStyle.h
 *     Purpose:	Adobe Illustrator 9.0 Art Style Suite.
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
#ifndef __AI90ArtStyle__
#define __AI90ArtStyle__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIArtStyle.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90ArtStyleSuite				kAIArtStyleSuite
#define kAIArtStyleSuiteVersion2		AIAPI_VERSION(2)
#define kAI90ArtStyleSuiteVersion		kAIArtStyleSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Suite for retrieving and editing styles on art objects */
typedef struct {

	AIAPI AIErr (*GetStyledArt) ( AIArtHandle art, AIArtHandle* styledArt );

	// ------- Retrieving art styles -------
	AIAPI AIErr (*GetArtStyle) ( AIArtHandle art, AIArtStyleHandle* artStyle );
	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* artStyle, AIBoolean* mixedState );
	AIAPI AIErr (*GetArtStyleByName) ( AIArtStyleHandle* artStyle, const char* name,
									   AIBoolean searchAllStyles );
	AIAPI AIErr (*CountNamedArtStyles) ( long* count );
	AIAPI AIErr (*GetNthNamedArtStyle) ( long n, AIArtStyleHandle* artStyle );  // 0-based


	// ------- Setting art styles -------
	AIAPI AIErr (*SetArtStyle) ( AIArtHandle art, AIArtStyleHandle artStyle );
	AIAPI AIErr (*SetCurrentArtStyle) ( AIArtStyleHandle artStyle );

	
	// ------- Art styles attributes -------
	AIAPI AIErr (*GetArtStyleName) ( AIArtStyleHandle artStyle, char* name, long maxChars,
									 AIBoolean* isAnonymous );
	// Style names are limited to 63 characters.
	AIAPI AIErr (*SetArtStyleName) ( AIArtStyleHandle artStyle, const char* name );
	AIAPI AIErr (*GetPaintAttributes) ( AIArtStyleHandle artStyle, AIPathStyle* aiPathStyle,
										AIArtStylePaintData* paintData );
	

	
	// ------- Allocating and modifying styles -------
	AIAPI AIErr (*NewStyle) ( AIPathStyle* aiPathStyle, AIArtStylePaintData* paintData,
							  AIDictionaryRef blendDict, AIArtStyleHandle* newStyle );
	// Style names are limited to 63 characters. When adding a style, names are limited
	// to 61 characters if uniquify is set to true.
	AIAPI AIErr (*AddNamedStyle) ( AIArtStyleHandle artStyle, const char* name, AIBoolean uniquify,
								   AIArtStyleHandle* namedStyle );
	AIAPI AIErr (*RemoveNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );
	AIAPI AIErr (*CreateAnonymousStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );
	AIAPI AIErr (*RedefineNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle dstStyle );
	AIAPI AIErr (*MoveNamedStyle) (AIArtStyleHandle namedStyle, int index);
	
	
	// ------- Retrieving art styles from other documents -------
	AIAPI AIErr (*GetArtStyleByNameFromDocument) ( AIArtStyleHandle* artStyle, const char* name,
												   AIDocumentHandle document );
	AIAPI AIErr (*CountNamedArtStylesFromDocument) ( long* count, AIDocumentHandle document );
	AIAPI AIErr (*GetNthNamedArtStyleFromDocument) ( long n, AIArtStyleHandle* artStyle,
													 AIDocumentHandle document );
	
	// ------- Testing equivalence between styles -------
	AIAPI AIErr (*Equiv) ( AIArtStyleHandle artStyle1, AIArtStyleHandle artStyle2,
							  AIBoolean* result );

	// ------- Sorting the named styles in the current document by their name -------
	AIAPI AIErr (*SortNamedStyles) ( void );
	
	
	// ------- Retrieving the default style of the document -------
	AIAPI AIErr (*GetDefaultArtStyle) (AIArtStyleHandle* artStyle);
	
	
	// ------- Validating an art style --------
	AIAPI AIBoolean (*ValidateArtStyle) ( AIArtStyleHandle artStyle );
	
	// ------- Flattening (expanding) the style of an art object --------
	// This replaces the given art object with the art that would have been returned
	// in a call to GetStyledArt. It takes care of doing such things as transferring
	// opacity masks, URLs, tags, etc. from the input art to the flattened art.
	// Clients should be wary that the art handle passed in might be invalidated
	// after this call returns. Clients should not depend on the value of 'art' after
	// this call returns.
	AIAPI AIErr (*FlattenStyle) ( AIArtHandle art );
	
	// ------- Getting the style type, for efficiency reasons -------
	AIAPI AIErr (*GetArtStyleType) ( AIArtStyleHandle artStyle, short* type );
	
	// ------- Can the art style execute (or is it missing a plugin?) -------
	AIAPI AIBoolean (*CanExecute) ( AIArtStyleHandle artStyle );
	
	// ------- Retrieve/set/reset the scale factor for the given object's style -------
	// There is an option "Scale Strokes & Effects" inside the app. Scaling operations
	// now have the ability to scale the stroke weight and effects attached to the art.
	// However, if the art style is a named style, we do not want to break the link to
	// the named style just because the object was scaled. To get around this, we added
	// a scale factor that is stored on a per object basis. So, even if the style attached
	// to an object has a stroke with a weight of 2 pt, if the object's scale factor is 2.5, 
	// then the visual stroke weight is 5 pt.
	// Here is a small subtle point: Calling GetPaintAttributes from this suite will return
	// the _unscaled_ stroke weight. In addition, going through the AIArtStyleParser suite, you
	// will get the _unscaled_ parameters of all the strokes and effects. However, the old 
	// AIPathStyle suite calls will always return the _scaled_ stroke weights attached to 
	// the objects.
	// The call ResetArtStyleScaleFactor will attach a new style to the given object with
	// all the strokes and effects scaled appropriately according to the object's original scale
	// factor. The object's scale factor is then reverted back to 1.0 after the new style is 
	// attached.
	AIAPI AIReal (*GetArtStyleScaleFactor) ( AIArtHandle art );
	AIAPI AIErr (*SetArtStyleScaleFactor) ( AIArtHandle art, AIReal scaleFactor );
	AIAPI AIErr (*ResetArtStyleScaleFactor) ( AIArtHandle art );

	// ------- Transform the artStyle of an object (flags are from AITransformArt.h)  -------
	// If the kTransformObjects flag is on, the assumption is made that the art object itself
	// has also been transformed by the same matrix, and that any transformation of the points,
	// descendant art, etc. has already been performed. (This allows gradient vectors and
	// other style attributes that are dependent upon object bounds to be adjusted immediately
	// rather than deferred until artwork synchronization.)  
	AIAPI AIErr (*TransformObjectArtStyle) ( AIArtHandle art, AIRealMatrix *matrix, AIReal lineScale, long flags );
	
	// ------- Retrieve the name of the default style -------
	AIAPI AIErr (*GetDefaultArtStyleName) ( char* name, long maxChars );
	
	// ------- Examine the artStyle for specified contents, and return which ones were found -------
	AIAPI AIArtStyleHasAttrs (*ExamineStyle) ( AIArtStyleHandle artStyle, AIArtStyleHasAttrs checkFor );

	// ------- Get the art style that will be used for new art. Based on preferences. -------
	AIAPI AIErr (*GetToolArtStyle) ( AIArtStyleHandle* artStyle );

} AI90ArtStyleSuite;


#include "AIHeaderEnd.h"


#endif
