//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/filterHandler.cpp $
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

#include "IllustratorSDK.h"

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
 **	External functions
 **
 **/

extern AIErr twirl_get_parms( AIFilterMessage *pb );
extern AIErr go_twirl( AIFilterMessage *pb );




/**-----------------------------------------------------------------------------
 **
 **	Functions
 **
 **/

AIErr addFilters( SPInterfaceMessage *message )
{
	AIErr error = kNoErr;
	unsigned char categoryStr[MAX_FILTER_NAME]; /* pascal string */
	unsigned char nameStr[MAX_FILTER_NAME];     /* pascal string */
	AIMenuItemHandle menuItem;
	PlatformAddFilterData filterData;
	short	nIndex;
	short	filterIndex = 0;

	for (nIndex = 1; nIndex < kMaxFilters * 2 ; nIndex += FILTER_STRING_INC, filterIndex++) {
 		sADMBasic->GetIndexString( message->d.self, kFilterStrings, nIndex, (char*)categoryStr, MAX_FILTER_NAME );

		if (!categoryStr[0]) // first null category means no more filters
			break;

		sADMBasic->GetIndexString( message->d.self, kFilterStrings, (nIndex+1), (char*)nameStr, MAX_FILTER_NAME );

		SUctopstr( (char*)categoryStr );
		SUctopstr( (char*)nameStr );
		filterData.category = categoryStr;
		filterData.title = nameStr;

		error = sFilter->AddFilter( message->d.self, "Twirl Filter", &filterData, 
					0, &g->filters[filterIndex] );
		if ( error ) 
			goto errorTag;

		error = sFilter->GetFilterMenuItem(g->filters[filterIndex], &menuItem);
		if ( error ) 
			goto errorTag;
		
		error = sMenu->UpdateMenuItemAutomatically(menuItem, kAutoEnableMenuItemAction, 0, 0,
			kIfPath, 0, 0, 0);
		if ( error ) 
			goto errorTag;
		}

	g->numFilters = filterIndex;

errorTag:

	return error;
}



AIErr filterGetParms( AIFilterMessage *message )
{
	AIErr error;

	if ( message->filter == g->filters[ 0 ] ) {

		error = twirl_get_parms( message );
		if (error) goto error;
	}
	
error:
	return error;
}



AIErr goFilter( AIFilterMessage *message )
{
	AIErr error = kNoErr;

	go_twirl( message );
	
	return error;
}


