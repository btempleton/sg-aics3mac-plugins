//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/filterHandler.cpp $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

//	Useful routines for plug-in filters.

/**-----------------------------------------------------------------------------
 **
 **	Headers
 **
 **/

#include "common.h"
#include "filterHandler.h"
#include "stringUtils.h"

/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/

#define MAX_FILTER_NAME 65
#define FILTER_STRING_INC 2

/**-----------------------------------------------------------------------------
 **
 **	Variables
 **
 **/


AIErr addFilters( SPInterfaceMessage *message )
{
	AIErr error = kNoErr;
	unsigned char categoryStr[MAX_FILTER_NAME]; /* pascal string */
	unsigned char nameStr[MAX_FILTER_NAME];     /* pascal string */

	PlatformAddFilterData filterData;
	// AIMenuItemHandle menuItem; // include this when appropriate
	short	nIndex;
	short	filterIndex = 0;

	for (nIndex = 1; nIndex < kMaxFilters * 2 ; nIndex += FILTER_STRING_INC, filterIndex++) {
 		sADMBasic->GetIndexString( message->d.self, kFilterStrings, nIndex, (char*)categoryStr, MAX_FILTER_NAME );

		if (!categoryStr[0]) // first null category means no more filters
			break;

		sADMBasic->GetIndexString( message->d.self, kFilterStrings, (nIndex+1), (char*)nameStr, MAX_FILTER_NAME );

		ctopstr( (char*)categoryStr );
		ctopstr( (char*)nameStr );
		filterData.category = categoryStr;
		filterData.title = nameStr;

		error = sFilter->AddFilter( message->d.self, "Twirl Filter", &filterData, 
					0, &g->filters[filterIndex] );
		if ( error ) 
			goto errorTag;

/*		// include this when appropriate
		error = sFilter->GetFilterMenuItem(g->filters[filterIndex], &menuItem);
		if ( error ) 
			goto errorTag;
		
		error = sMenu->UpdateMenuItemAutomatically(menuItem, kAutoEnableMenuItemAction, 0, 0,
			kIfPath, 0, 0, 0);
		if ( error ) 
			goto errorTag;
*/
		}

	g->numFilters = filterIndex;
errorTag:

	return error;
}





AIErr filterGetParms( AIFilterMessage *message )
{
	parms_t **parms;
//	parms_t orig_parms;
	AIBoolean canceled = false;
	AIErr error;

	if ( message->filter == g->filters[ 0 ] ) {

		parms = (parms_t **) message->parameters;
		if ( !parms ) {

			sMDMemory->MdMemoryNewHandle ( sizeof(parms_t), ( AIMdMemoryHandle *)&message->parameters );
			if ( !message->parameters ) {
				error = memFullErr;
				goto error;
				}
	
			parms = (parms_t **) message->parameters;
			(**parms).userValue = 10;
		}
	}
	
// else if ( g->filters[kSomeOtherFilter] == message->filter ) { ... } else...

error:
	return (canceled ? kCanceledErr : kNoErr);
}



AIErr goFilter( AIFilterMessage *message )
{
	parms_t **parms = (parms_t **) message->parameters;
	AIErr error = noErr;


	if (error)
		goto error;

error:
	return error;
}


