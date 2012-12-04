#ifndef __AI110Layer__
#define __AI110Layer__

/*
 *        Name:	AI110Layer.h
 *   $Revision: 12 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Layers.
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

#include "AILayer.h"

#include "AIHeaderBegin.h"

/** @file AI110Layer.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAILayerSuiteVersion4		AIAPI_VERSION(4)		// Illustrator 6.0
#define kAILayerSuiteVersion5		AIAPI_VERSION(5)		// Illustrator 6.0.1
#define kAILayerSuiteVersion6		AIAPI_VERSION(6)		// Illustrator 7.0
#define kAILayerSuiteVersion7		AIAPI_VERSION(7)	// Illustrator 8.0
#define kAILayerSuiteVersion9		AIAPI_VERSION(9)		// Illustrator 9.0


#define kAI110LayerSuite			kAILayerSuite	
#define kAI110LayerSuiteVersion		kAILayerSuiteVersion9		// The current version

#define kAI110LayerVersion			kAI110LayerSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** 
	The artwork in an Illustrator document is contained within layers. The document
	has a stack of lists of layers. The topmost list of layers in the stack are the
	ones currently being edited. See the AILayerListSuite for more about this stack.
	Each layer contains a group of objects. These objects may include sublayers. All
	documents begin with at least one layer, and the user (or a plug-in) may add
	any number of new layers to it. The AIArtSuite::GetFirstArtOfLayer() API can be
	used to get the group of art objects belonging to a layer.

	In addition to its artwork, a layer has several associated properties, including
	its name, color, and flags indicating whether the layer is visible, editable,
	printable, and displays placed art as dimmed. A reference to an Illustrator
	layer is opaque so these values cannot be set directly. Instead, use the functions
	in the Layer Suite to get and set layer properties.

	The color of the layer is used to when drawing selection marks for selected art. By
	default it is blue. If the layer is visible, artwork within it will be rendered. If
	it is editable changes can be made to it, otherwise it is locked. If it is printable,
	artwork within it will be printed. The dimmed placed art flag determines how placed
	art is rendered.
	
	Several layer properties affect whether artwork on those layers should be editable.
	Normally objects on such layers cannot be selected so plugins that operate on the
	current selection need not worry about these properties. If you’re walking through
	the artwork, you should call GetLayerEditable()	on each layer before attempting to
	make any changes to the artwork.

	Some layers may also be designated as template layers. A template layer is a layer
	that contains template artwork being used to guide the construction of the document
	artwork. For example, it might contain an image that is being traced. Template
	layers are never printed or exported to final form file formats.

	There are four notifiers associated with the layers:

	- #kAICurrentLayerNotifier
	- #kAILayerDeletionNotifier
	- #kAILayerSetNotifier
	- #kAILayerOptionsNotifier
*/
typedef struct {

	/** Returns a count of the number of top level layers in the current document
		layer list.	If there is no current document the API does not return an
		error, instead it returns 0 for the count. */
	AIAPI AIErr (*CountLayers) ( long *count );
	/** Get the Nth top level layer of the current layer list. The index is 0 based.
		The 0th layer is the topmost layer in stacking order. Note that it is more
		efficient to iterate the layers using the GetFirstLayer(), GetNextLayer() APIs. */
	AIAPI AIErr (*GetNthLayer) ( long n, AILayerHandle *layer );
	/** Returns the current layer. This is the layer on which new artwork is created
		by default and is indicated in the layers palette by a black triangle to
		its right. */
	AIAPI AIErr	(*GetCurrentLayer) ( AILayerHandle *layer );
	/** Set the current layer. This is the layer on which new artwork is created
		by default and is indicated in the layers palette by a black triangle to
		its right. */
	AIAPI AIErr	(*SetCurrentLayer) ( AILayerHandle layer );

	/** Get the top layer of the current document layer list. */
	AIAPI AIErr	(*GetFirstLayer) ( AILayerHandle *first );
	/** Get the next layer below the given layer in stacking order. Returns NULL if
		there are no more layers. The layer returned is at the same level as the
		input layer. That is, sublayers are not visited. */
	AIAPI AIErr	(*GetNextLayer) ( AILayerHandle prev, AILayerHandle *next );
	
	/** This function adds a new layer to the document. New layers are inserted into
		the list of layers by specifying a position relative to another layer. The
		constants used to specify the relative position are the same as those used
		by the AIArtSuite::NewArt() call. See #AIArtOrder for the possible values.
		
		A layer inserted above another will have a lower index number. Inserting
		below will have a greater index number. kPlaceAbove and kPlaceBelow
		require a layer to be specified in the layer argument to serve as the relative
		marker.

		The kPlaceAboveAll and kPlaceBelowAll constants ignore the layer argument,
		so you can pass nil. kPlaceAboveAll creates a layer at index 0, kPlaceBelowAll
		creates a layer at index count.*/
	AIAPI AIErr	(*InsertLayer) ( AILayerHandle layer, short paintOrder, AILayerHandle *newLayer );
	/** Removes the specified layer from the document. All art in the layer is also
		deleted.

		Every document must have a least one layer, so calling DeleteLayer when
		CountLayers() is 1 will return an error.*/
	AIAPI AIErr	(*DeleteLayer) ( AILayerHandle layer );

	/** GetLayerTitle returns the name of the specified layer as a Pascal string. The
		maximum title size returned is 100 bytes. */
	AIAPI AIErr (*GetLayerTitle) ( AILayerHandle layer, unsigned char *title );
	/** Specify a new name (Pascal string) for a layer. */
	AIAPI AIErr (*SetLayerTitle) ( AILayerHandle layer, unsigned char *title );
	/** Returns the color used when outlining selected artwork. */
	AIAPI AIErr (*GetLayerColor) ( AILayerHandle layer, AIRGBColor *color );
	/** Sets the color used when outlining selected artwork. */
	AIAPI AIErr (*SetLayerColor) ( AILayerHandle layer, AIRGBColor color );
	/** GetLayerVisible returns an AIBoolean specifying whether the artwork in
		a layer is visible. If a parent layer is not visible then the artwork
		of a sublayer may be invisible even though this API returns true. */
	AIAPI AIErr (*GetLayerVisible) ( AILayerHandle layer, AIBoolean *visible );
	/** Sets whether the artwork in a layer is visible. If a parent layer is
		not visible then the visibility state of a sublayer has no immediate
		effect. */
	AIAPI AIErr (*SetLayerVisible) ( AILayerHandle layer, AIBoolean visible );
	/** GetLayerPreview returns whether the layer is rendered in preview mode
		(true) or outline mode (false). If a parent layer specifies outline
		mode then all sublayers are rendered with outline mode regardless of
		their individual setting. */
	AIAPI AIErr (*GetLayerPreview) ( AILayerHandle layer, AIBoolean *preview );
	/** SetLayerPreview sets the layer to be rendered in preview mode or outline
		mode. Pass true for preview mode or false for outline mode. If a parent
		layer specifies outline mode then all sublayers are rendered with outline
		mode regardless of their individual setting.*/
	AIAPI AIErr (*SetLayerPreview) ( AILayerHandle layer, AIBoolean preview );
	/** Returns whether the specified layer is editable. That is, whether artwork
		can be created or modified in it. If a parent layer is not editable
		then sublayers also may not be edited regardless of their individual
		setting. */
	AIAPI AIErr (*GetLayerEditable) ( AILayerHandle layer, AIBoolean *editable );
	/** Sets whether the specified layer is editable. That is, whether artwork
		can be created or modified in it. If a parent layer is not editable
		then sublayers also may not be edited regardless of their individual
		setting. */
	AIAPI AIErr (*SetLayerEditable) ( AILayerHandle layer, AIBoolean editable );
	/** When printing separations it is possible to choose whether to print all
		layers, visible layers or printable, visible layers. This API returns
		whether a layer is to be considered printable in this case. */
	AIAPI AIErr (*GetLayerPrinted) ( AILayerHandle layer, AIBoolean *printed );
	/** When printing separations it is possible to choose whether to print all
		layers, visible layers or printable, visible layers. This API sets
		whether a layer is to be considered printable in this case. */
	AIAPI AIErr (*SetLayerPrinted) ( AILayerHandle layer, AIBoolean printed );
	/** Returns whether images are "dimmed" when rendering. If a parent layer
		specifies dimming images on sublayers will be dimmed regardless of their
		individual setting.*/
	AIAPI AIErr (*GetLayerDimPlacedImages) ( AILayerHandle layer, AIBoolean *dimmed );
	/** Sets whether images are "dimmed" when rendering. If a parent layer
		specifies dimming images on sublayers will be dimmed regardless of their
		individual setting.*/
	AIAPI AIErr (*SetLayerDimPlacedImages) ( AILayerHandle layer, AIBoolean dimmed );

	// version 5, new for AI 6.0.1
	
	/** This function returns an AIBoolean specifying whether the layer’s selected
		flag is set (true) or not (false). This function is provided mainly for backward
		compatiblity with Illustrator 6.0. */
	AIAPI AIErr (*GetLayerSelected) ( AILayerHandle layer, AIBoolean *selected );
	/** This function sets the specified layer’s selected flag (true) or (false). This
		function is provided mainly for backward compatiblity with Illustrator 6.0. */
	AIAPI AIErr (*SetLayerSelected) ( AILayerHandle layer, AIBoolean selected );

	// version 6, new for AI 7.0
	
	/** Returns the layer which corresponds to the title passed in title. This is the
		same title which is set by SetLayerTitle or returned by GetLayerTitle.
		This is also the same title the user may have given the layer via the user
		interface. The layer returned may be a sublayer or a top level layer. */
	AIAPI AIErr (*GetLayerByTitle) ( AILayerHandle *layer, unsigned char *title );
	/** Returns true if the layer contains objects other than sublayers. */
	AIAPI AIErr (*LayerHasArt) ( AILayerHandle layer, AIBoolean *hasArt );
	/** This function returns an AIBoolean specifying whether the specified layer
		has any selected artwork (true) or not (false). */
	AIAPI AIErr (*LayerHasSelectedArt) ( AILayerHandle layer, AIBoolean *hasSel );
	/** Deselects all objects on the layer. */
	AIAPI AIErr (*DeselectArtOnLayer) ( AILayerHandle layer );
	/** Selects all objects on the layer that may be selected. */
	AIAPI AIErr (*SelectArtOnLayer) ( AILayerHandle layer );

	// version 7, new for AI 8.0

	/** Returns true if the layer is a template layer. If a layer is a template layer
		then all sublayers are considered to be template layers. */
	AIAPI AIErr (*GetLayerIsTemplate) ( AILayerHandle layer, AIBoolean *isTemplate );
	/** Sets whether the layer is a template layer. If a layer is a template layer
		then all sublayers are considered to be template layers. */
	AIAPI AIErr (*SetLayerIsTemplate) ( AILayerHandle layer, AIBoolean isTemplate );
	/** Get the previous layer above the given layer in stacking order. Returns NULL if
		there are no more layers. The layer returned is at the same level as the
		input layer. That is, sublayers are not visited. */
	AIAPI AIErr (*GetPrevLayer) ( AILayerHandle next, AILayerHandle *prev );
	/** Get the dimming factor used for drawing images when a layer is set to be
		dimmed. */
	AIAPI AIErr (*GetLayerDimmedPercent) ( AILayerHandle layer, long *percent );
	/** Set the dimming factor used for drawing images when a layer is set to be
		dimmed. */
	AIAPI AIErr (*SetLayerDimmedPercent) ( AILayerHandle layer, long percent );

	// version 8, new for AI 9.0

	/** Returns the first child sublayer of the layer or NULL if there are no sublayers. */
	AIAPI AIErr (*GetLayerFirstChild) ( const AILayerHandle layer, AILayerHandle *child );
	/** Returns the parent layer or NULL if there is no parent. */
	AIAPI AIErr (*GetLayerParent) ( const AILayerHandle layer, AILayerHandle *parent );
	/** Inserts a new layer relative to the specified art object. The position identified
		must be legal for creation of a layer. That is it must either be at the top level
		or such that the resulting parent is a layer. */
	AIAPI AIErr (*InsertLayerAtArt) ( const AIArtHandle art, AIPaintOrder paintOrder, AILayerHandle *newLayer );

	/** Specify using either layer or layer group. For nested layers only. */
	AIAPI AIErr (*ChangeLayerToGroup) ( const AILayerHandle layer, const AIArtHandle group );

	/** Return next layer in preorder traversal (node first then descendents) */
	AIAPI AIErr (*GetNextPreorderLayer) ( AILayerHandle prev, AILayerHandle *next );

	/** Return next layer in preorder traversal that is not a child of 'prev' */
	AIAPI AIErr (*GetNextNonChildPreorderLayer) ( AILayerHandle prev, AILayerHandle *next );

} AI110LayerSuite;


#include "AIHeaderEnd.h"

#endif
