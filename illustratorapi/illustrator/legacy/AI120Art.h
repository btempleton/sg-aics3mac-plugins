#ifndef __AI120Art__
#define __AI120Art__

/*
 *        Name:	AI120Art.h
 *     Purpose:	Adobe Illustrator 12.0 Artwork Object Suite.
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

#include "AIArt.h"

#include "AIHeaderBegin.h"

/** @file AI120Art.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI120ArtSuite			kAIArtSuite
#define kAIArtSuiteVersion11	AIAPI_VERSION(12)
#define kAI120ArtSuiteVersion	kAIArtSuiteVersion11


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Illustrator 12.0 Art suite */
typedef struct _AI120ArtSuite {

	AIAPI AIErr (*NewArt) ( short type, short paintOrder, AIArtHandle prep, AIArtHandle *newArt );
	AIAPI AIErr (*DisposeArt) ( AIArtHandle art );
	AIAPI AIErr (*ReorderArt) ( AIArtHandle thisArt, short paintOrder, AIArtHandle prep );
	AIAPI AIErr (*DuplicateArt) ( AIArtHandle thisArt, short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	AIAPI AIErr (*GetFirstArtOfLayer) ( AILayerHandle layer, AIArtHandle *art );
	AIAPI AIErr (*GetLayerOfArt) ( AIArtHandle art, AILayerHandle *layer );
	AIAPI AIErr (*GetArtType) ( AIArtHandle art, short *type );
	AIAPI AIErr (*GetArtUserAttr) ( AIArtHandle art, long whichAttr, long *attr );
	AIAPI AIErr (*SetArtUserAttr) ( AIArtHandle art, long whichAttr, long attr );
	AIAPI AIErr (*GetArtParent) ( AIArtHandle art, AIArtHandle *parent );
	AIAPI AIErr (*GetArtFirstChild) ( AIArtHandle art, AIArtHandle *child );
	AIAPI AIErr (*GetArtSibling) ( AIArtHandle art, AIArtHandle *sibling );
	AIAPI AIErr (*GetArtPriorSibling) ( AIArtHandle art, AIArtHandle *sibling );

	AIAPI AIErr (*GetArtBounds) ( AIArtHandle art, AIRealRect *bounds );
	AIAPI AIErr (*SetArtBounds) ( AIArtHandle art );

	AIAPI AIErr (*GetArtCenterPointVisible) ( AIArtHandle art, AIBoolean *visible );
	AIAPI AIErr (*SetArtCenterPointVisible) ( AIArtHandle art, AIBoolean visible );

	/* New with Illustrator 7.0 */
	AIAPI AIErr (*GetArtTransformBounds) ( AIArtHandle art, AIRealMatrix *transform, long flags, AIRealRect *bounds );
	AIAPI AIErr (*UpdateArtworkLink) ( AIArtHandle art, AIBoolean *updated );

	/* New in Illustrator 8.0 */

	AIAPI AIBoolean (*ValidArt) ( AIArtHandle art );
	AIAPI AIErr (*GetArtOrder) ( AIArtHandle art1, AIArtHandle art2, short *order );
	AIAPI AIErr (*SelectNamedArtOfLayer) ( AILayerHandle layer, char *name, AIBoolean matchWholeWord, AIBoolean caseSensitive );
	AIAPI AIErr (*GetArtRotatedBounds) ( AIArtHandle art, AIReal angle, long flags, AIRealRect *bounds );

	AIAPI AIBoolean (*ArtHasFill) ( AIArtHandle art );
	AIAPI AIBoolean (*ArtHasStroke) ( AIArtHandle art );
	AIAPI AIBoolean (*ArtsHaveEqualPaths) ( AIArtHandle art1, AIArtHandle art2 );
	AIAPI AIErr (*ArtCopyFillStyleIfEqualPaths) ( AIArtHandle dstArt, AIArtHandle srcArt );
	AIAPI AIErr (*ArtCopyStrokeStyleIfEqualPaths) ( AIArtHandle dstArt, AIArtHandle srcArt );

	/* New in Illustrator 9.0 */
	
	AIAPI AIErr (*GetInsertionPoint) ( AIArtHandle *art, short *paintorder, ASBoolean *editable );
	AIAPI AIErr (*SetInsertionPoint) ( AIArtHandle art );

	AIAPI AIErr (*GetKeyArt) ( AIArtHandle *art );	 
	AIAPI AIErr (*CancelKeyArt) (void);

	AIAPI AIErr (*GetDictionary) ( AIArtHandle art, struct _AIDictionary** dictionary );

	AIAPI AIErr (*SetArtName) (AIArtHandle art, const ai::UnicodeString& name);
	AIAPI AIErr (*GetArtName) (AIArtHandle art, ai::UnicodeString& name, ASBoolean *isDefaultName);

	AIAPI AIErr (*IsArtLayerGroup) (AIArtHandle art, ASBoolean *isLayerGroup);
	AIAPI AIErr (*ReleaseToLayers) (const AIArtHandle art, ASBoolean build);
	
	AIAPI AIErr (*ModifyTargetedArtSet) (AIArtHandle *list, long count, long action);

	AIAPI AIBoolean (*IsArtStyledArt) (AIArtHandle art);

	AIAPI AIBoolean (*IsArtClipping) (AIArtHandle art);


	/* New in Illustrator 10.0 */

	AIAPI AIErr (*TransferAttributes) (AIArtHandle srcart, AIArtHandle dstart, unsigned long which);

	/* New in Illustrator 11.0 */

	AIAPI AIErr (*GetArtLastChild) ( AIArtHandle art, AIArtHandle *child );

	AIAPI AIErr (*SetArtTextWrapProperty) ( AIArtHandle art, AIReal offset, AIBoolean invert );
	AIAPI AIErr (*GetArtTextWrapProperty) ( AIArtHandle art, AIReal *offset, AIBoolean *invert );
	
	AIAPI AIErr (*CreateCopyScope) (enum AICopyScopeKind kind, AICopyScopeHandle* scope);
	AIAPI AIErr (*DestroyCopyScope) (AICopyScopeHandle scope);

	/* New in Illustrator 12.0 */

	AIAPI AIErr (*InsertionPointBadForArtType) (short paintOrder, AIArtHandle prep, short artType);
	AIAPI AIErr (*PreinsertionFlightCheck) (AIArtHandle candidateArt, short paintOrder, AIArtHandle prep);

	AIAPI AIErr (*SetNote) (AIArtHandle art, const ai::UnicodeString& inNote);
	AIAPI AIErr (*GetNote) (AIArtHandle art, ai::UnicodeString& outNote);
	AIAPI AIBoolean (*HasNote) (AIArtHandle art);
	AIAPI void (*DeleteNote) (AIArtHandle art);

	AIAPI AIErr (*GetArtXMPSize)(AIArtHandle art, long* size);
	AIAPI AIErr (*GetArtXMP)(AIArtHandle art, char *xmp, long size);
	AIAPI AIErr (*SetArtXMP)(AIArtHandle art, const char *xmp);

 	AIAPI AIErr (*GetPreciseArtTransformBounds) ( AIArtHandle art, AIRealMatrix *transform, long flags, AIDoubleRect *bounds );

	AIAPI AIErr (*UncheckedDisposeArt) ( AIArtHandle art );

} AI120ArtSuite;

#include "AIHeaderEnd.h" // __cplusplus

#endif // __AI120Art__