#ifndef __AI90LayerList__
#define __AI90LayerList__

/*
 *        Name:	AI90LayerList.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Layer List Suite.
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

#include "AILayerList.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI90LayerListSuite				kAILayerListSuite
#define kAILayerListSuiteVersion1		AIAPI_VERSION(1)
#define kAI90LayerListSuiteVersion		kAILayerListSuiteVersion1
#define kAI90LayerListVersion			kAI90LayerListSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	/* Push a new layer list. The push layer list message is sent to the
		plugin to setup the list. See descriptions of messages above.
		The mode defines how the layer will be displayed.  */
	AIAPI AIErr (*Push) (SPPluginRef self, char* tag, void* data,
			AILayerListMode mode, AILayerList* list);

	/* Pop the current layer list. The plugin which pushed the layer list
		is called with the pop message. See descriptions of messages
		above. */
	AIAPI AIErr (*Pop) (void);

	/* Gets both the layer list and the layer on which the art object resides.
		Either output parameter may be NULL. */
	AIAPI AIErr (*GetLayerOfArt) (AIArtHandle art, AILayerList* list, AILayerHandle* layer);

	/* Methods for enumerating the layer lists. */
	AIAPI AIErr (*Count) (long* count);
	AIAPI AIErr (*GetFirst) (AILayerList* list);
	AIAPI AIErr (*GetLast) (AILayerList* list);
	AIAPI AIErr (*GetNext) (AILayerList list, AILayerList* next);

	/* Methods for enumerating the layers of a layer list. */
	AIAPI AIErr (*CountLayers) (AILayerList list, long* count);
	AIAPI AIErr (*GetFirstLayer) (AILayerList list, AILayerHandle* layer);
	AIAPI AIErr (*GetLastLayer) (AILayerList list, AILayerHandle* layer);
	AIAPI AIErr (*GetNextLayer) (AILayerList list, AILayerHandle layer, AILayerHandle* next);
	AIAPI AIErr (*GetPrevLayer) (AILayerList list, AILayerHandle layer, AILayerHandle* prev);

	/* Methods for querying and modifying how a layer list is rendered. */
	AIAPI AIErr (*SetDisplayMode) (AILayerList list, AILayerListMode mode);
	AIAPI AILayerListMode (*GetDisplayMode) (AILayerList list);

	/* Get the tag specified when the layer list was pushed. */
	AIAPI const char* (*GetTag) (AILayerList list);

} AI90LayerListSuite;


#include "AIHeaderEnd.h"


#endif
