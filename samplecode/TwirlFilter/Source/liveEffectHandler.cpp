//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/liveEffectHandler.cpp $
//
//  $Revision: #4 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// Useful routines for plug-in liveEffects.

/**-----------------------------------------------------------------------------
 **
 **	Headers
 **
 **/

#include "IllustratorSDK.h"

#include "common.h"
#include "liveEffectHandler.h"
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
extern AIErr twirl_get_parms( AILiveEffectEditParamMessage *pb );
extern AIErr go_twirl( AIFilterMessage *pb );
extern AIErr go_twirl( AILiveEffectGoMessage *pb );




/**-----------------------------------------------------------------------------
 **
 **	Functions
 **
 **/

AIErr addLiveEffects( SPInterfaceMessage *message )
{
	AIErr error = kNoErr;
	char categoryStr[MAX_FILTER_NAME]; /* pascal string */
	char nameStr[MAX_FILTER_NAME];     /* pascal string */
	AILiveEffectData effectData;
	AddLiveEffectMenuData menuData;
	AIMenuItemHandle menuHandle = nil;
	short	nIndex;
	short	filterIndex = 0;

	for (nIndex = 1; nIndex < kMaxEffects * 2 ; nIndex += FILTER_STRING_INC, filterIndex++) {
 		sADMBasic->GetIndexString( message->d.self, kFilterStrings, nIndex, (char*)categoryStr, MAX_FILTER_NAME );

		if (!categoryStr[0]) // first null category means no more filters
			break;

		sADMBasic->GetIndexString( message->d.self, kFilterStrings, (nIndex+1), (char*)nameStr, MAX_FILTER_NAME );

		effectData.self = message->d.self;
		effectData.name = nameStr;				// Localized name of the effect
		effectData.title = nameStr;
		effectData.majorVersion = 1;
		effectData.minorVersion = 0;
		effectData.prefersAsInput = (kGroupInputArt | kPathInputArt | kCompoundPathInputArt);//kAnyInputArt;	// AIStyleFilterPreferedInputArtType
		effectData.styleFilterFlags = kPostEffectFilter;	// AIStyleFilterFlags

		error = sLiveEffect->AddLiveEffect( &effectData, &g->effects[filterIndex] );
		if ( error ) 
			goto errorTag;

		menuData.category = categoryStr;
		menuData.title = nameStr;
		menuData.options = 0;

		error = sLiveEffect->AddLiveEffectMenuItem( g->effects[filterIndex],
													nameStr,
													&menuData,
													&menuHandle,
													NULL );

		if ( error ) 
			goto errorTag;
		error = sMenu->UpdateMenuItemAutomatically(menuHandle, kAutoEnableMenuItemAction, 0, 0,
			kIfPath, 0, 0, 0);
		if ( error ) 
			goto errorTag;
		if ( error ) 
			goto errorTag;
		}

	g->numEffects = filterIndex;

errorTag:

	return error;
}



AIErr liveEffectGetParms( AILiveEffectEditParamMessage *message )
{
	AIErr error;

	if ( message->effect == g->effects[ 0 ] ) {

		error = twirl_get_parms( message );
		if (error) goto error;
	}
	
error:
	return error;
}



AIErr goLiveEffect( AILiveEffectGoMessage *message )
{
	AIErr error = kNoErr;

	go_twirl( message );
	
	return error;
}

AIErr liveEffectInterpolate( AILiveEffectInterpParamMessage *message )
{
	return kNoErr;
}

AIErr liveEffectGetInputType( AILiveEffectInputTypeMessage *message )
{
	return kNoErr;
}

