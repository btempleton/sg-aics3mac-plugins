//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/Twirl.cpp $
//
//  $Revision: #7 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

//	Twirl anchor points around the path's center.

/**-----------------------------------------------------------------------------
 **
 **	Headers
 **			
 **/

#include "IllustratorSDK.h"

#include "common.h"
#include "PluginDlg.h"


/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/

 
#define kBadSelectionErr  	'!sel'




/**-----------------------------------------------------------------------------
 **
 **	Forward Functions
 **
 **/

// exports
AIErr twirl_get_parms( AIFilterMessage *pb );
AIErr twirl_get_parms( AILiveEffectEditParamMessage *pb );
AIErr go_twirl( AIFilterMessage *pb );
AIErr go_twirl( AILiveEffectGoMessage *pb );

// the guts of the thing
AIErr get_selection( AIArtHandle ***matches, long *numMatches,
		long *totalSegments, ASBoolean justLooking );
void release_selection( AIArtHandle **matches );

AIErr twirl_path( AIFilterMessage *pb, AIArtHandle art, long progress_current,
		long progress_total );
AIErr twirl_path( parms_t &pb, AIArtHandle art, long progress_current,
		long progress_total );

// dialog support
ASErr ASAPI PluginDlgInitProc(ADMDialogRef dialog);
void ASAPI DlgOKButtonCallBackProc(ADMItemRef item, ADMNotifierRef notifier);








/**-----------------------------------------------------------------------------
 **
 **	The filter Functions
 **
 **/

#define DEFAULT_ANGLE	_ShortToAIReal( 50 ) /* 50 */

AIErr twirl_get_parms( AIFilterMessage *pb )
{
	parms_t **parms;
	ASBoolean canceled = false;
	parms_t orig_parms;
	AIErr error;
	short dialog_id;
	AIArtHandle **matches;
	long count, total_segments=4;

//	AMPDialogRef	dlgPtr;
//	long			item;							   


	error = get_selection( &matches, &count, &total_segments, false );
	if ( error ) 
		goto errorTag;

	sAIMDMemory->MdMemoryDisposeHandle((AIMdMemoryHandle)matches);

	if ( total_segments < 10 ) dialog_id = kTwirlFewDLOG;
	else dialog_id = kTwirlDLOG;


	parms = (parms_t **) pb->parameters;
	if ( !parms ) {

		error = sAIMDMemory->MdMemoryNewHandle( sizeof(parms_t), (AIMdMemoryHandle *)&pb->parameters);
		if ( error )
			goto errorTag;

		if ( !pb->parameters ) {
			error = kOutOfMemoryErr;
			goto errorTag;
			}

		parms = (parms_t **) pb->parameters;

		(**parms).d_angle = DEFAULT_ANGLE;
		(**parms).bPositionSet = FALSE;
	}		
	
	orig_parms = **parms;
	canceled = kDlgOKButton != sADMDialog->Modal(pb->d.self, "Twirl Plug-in Dialog", dialog_id, kADMModalDialogStyle, PluginDlgInitProc, (ADMUserData)*parms, 0);
	
	if (canceled)		// then Cancel button was hit.
	{
		**parms = orig_parms;
	}
	


	return (canceled ? kCanceledErr : kNoErr);

errorTag:
	return (error);
}			 

AIErr twirl_get_parms( AILiveEffectEditParamMessage *pb )
{
	parms_t parms;
	ASBoolean canceled = false;
	parms_t orig_parms;
	AIErr error;
	short dialog_id;
	AIArtHandle **matches;
	long count, total_segments=4;
	AILiveEffectParameters liveEffectDictionary = pb->parameters;
	AIDictKey dictKey;

	error = get_selection( &matches, &count, &total_segments, false );
	if ( error ) goto errorTag;

	sAIMDMemory->MdMemoryDisposeHandle((AIMdMemoryHandle)matches);

	if ( total_segments < 10 ) 
		dialog_id = kTwirlFewDLOG;
	else 
		dialog_id = kTwirlDLOG;

	dictKey = sDictionary->Key("angle");
	if ( sDictionary->IsKnown( liveEffectDictionary, dictKey ) )
	{
		sDictionary->GetRealEntry( liveEffectDictionary, dictKey, &(parms.d_angle) );
		dictKey = sDictionary->Key("position");
		sDictionary->GetBooleanEntry( liveEffectDictionary, dictKey, &(parms.bPositionSet) );
	}
	else
	{
		parms.d_angle = DEFAULT_ANGLE;
		parms.bPositionSet = FALSE;
	}
	
	orig_parms = parms;
	canceled = kDlgOKButton != sADMDialog->Modal(pb->d.self, "Twirl Plug-in Dialog", dialog_id, kADMModalDialogStyle, PluginDlgInitProc, (ADMUserData)&parms, 0);
	
	if (canceled)		// then Cancel button was hit.
	{
		parms = orig_parms;
	}
	else
	{
		dictKey = sDictionary->Key("angle");
		sDictionary->SetRealEntry( liveEffectDictionary, dictKey, parms.d_angle );
		dictKey = sDictionary->Key("position");
		sDictionary->SetBooleanEntry( liveEffectDictionary, dictKey, parms.bPositionSet );
		sLiveEffect->UpdateParameters( pb->context );
	}

	return (canceled ? kCanceledErr : kNoErr);

errorTag:
	return (error);
}			 




ASErr ASAPI PluginDlgInitProc(ADMDialogRef dialog)
{
	#define MIN_VALUE	(kAIRealZero - _ShortToAIReal( 360 ))
	#define MAX_VALUE	_ShortToAIReal( 360 )
	
	ASErr error = kNoErr;
	parms_t *parms;
	AIReal defaultValue;
	ADMItemRef editItem;
	
	if (!error)
	{
		parms = (parms_t*)sADMDialog->GetUserData(dialog);
		defaultValue = parms->d_angle;
		editItem = sADMDialog->GetItem(dialog, kTwirlAngleDItem);
		
		// No need to add the buttons.
		
		// By default OK is assumed to be item 1 and Cancel is assumed to be item 2.
		
		sADMItem->SetUnits(editItem, kADMDegreeUnits);		// This should handle wrap around but does not currently.  DRL 4/15/96
		sADMItem->SetMinFloatValue(editItem, MIN_VALUE);
		sADMItem->SetMaxFloatValue(editItem, MAX_VALUE);
		sADMItem->SetFloatValue(editItem, defaultValue);
		
		sADMItem->Activate(editItem, true);					// It should do this automaticly, but for now. DRL 4/15/96
		sADMItem->SelectAll(editItem);
		
		sADMItem->SetNotifyProc(sADMDialog->GetItem(dialog, kDlgOKButton), DlgOKButtonCallBackProc);
	}
	
	return kNoErr;
}



void ASAPI DlgOKButtonCallBackProc(ADMItemRef item, ADMNotifierRef notifier)
{
	ADMDialogRef dialog = sADMItem->GetDialog(item);
	AIReal value;
	parms_t *parms = (parms_t*)sADMDialog->GetUserData(dialog);
	ADMRect boundsRect;
	
	// Call the default Notify so the dialog knows the OK button was hit.
	sADMItem->DefaultNotify(item, notifier);

	value = sADMItem->GetFloatValue(sADMDialog->GetItem(dialog, kTwirlAngleDItem));
	parms->d_angle = value;

	sADMDialog->GetBoundsRect(dialog, &boundsRect);
	
	parms->dialog_position.h = boundsRect.left;
	parms->dialog_position.v = boundsRect.top;
	
	parms->bPositionSet = TRUE;
	
}



AIErr get_selection( AIArtHandle ***matches, long *numMatches,
		long *totalSegments, ASBoolean justLooking )
{
	AIMatchingArtSpec spec[2];
	long i;
	AIErr error;

	*matches = nil;

	spec[0].type = kPathArt;
	spec[0].whichAttr = kArtSelected;
	spec[0].attr = kArtSelected;

	spec[1].type = kMysteryPathArt;
	spec[1].whichAttr = kArtSelected;
	spec[1].attr = kArtSelected;

	error = sAIMatch->GetMatchingArt( spec, 2, matches, numMatches );
	if ( error ) return error;

	if ( !*numMatches ) {
		error = kBadSelectionErr;
		goto errorTag;
	}

	*totalSegments = 0;
	for ( i = 0; i < *numMatches; ++i ) {
		short count;

		error = sAIPath->GetPathSegmentCount( (**matches)[i], &count );
		if ( error ) goto errorTag;
		*totalSegments += count;
		if ( justLooking ) break;
	}

	return kNoErr;

errorTag:
	if ( *matches )
		sAIMDMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle)*matches );

	return error;
}


void release_selection( AIArtHandle **matches )
{
	if ( matches ) 
		sAIMDMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle)matches );
}


AIErr go_twirl( AIFilterMessage *pb )
{
	parms_t **parms = (parms_t **) pb->parameters;
	AIArtHandle **matches = nil;
	long i, count, progress_current, progress_total;
	ASBoolean bounded;
	AIRealRect bounds;
	AIErr error = kNoErr;

	error = get_selection( &matches, &count, &progress_total, false );
	if ( error ) goto errorTag;

	(**parms).twirl = sAIMath->DegreeToRadian( (**parms).d_angle );


	bounded = false;
	for ( i = 0; i < count; ++i ) {
		AIRealRect one_bounds;

		error = sAIArt->GetArtBounds( (*matches)[i], &one_bounds ); // not (*matches[i]). njn
		if ( error ) goto errorTag;
		if ( !bounded ) {
			bounds = one_bounds;
			bounded = true;
		}
		else sAIMath->AIRealRectUnion( &bounds, &one_bounds, &bounds );
	}


	(**parms).center.h = sAIMath->AIRealDiv( bounds.right + bounds.left, _ShortToAIReal(2) );
	(**parms).center.v = sAIMath->AIRealDiv( bounds.bottom + bounds.top, _ShortToAIReal(2) );

	(**parms).diagonal = sAIMath->AIRealPointLength( (AIRealPoint *) &bounds, &(**parms).center );


	progress_current = 0;
	for ( i = 0; i < count; ++i ) {

		short progress_increment;
		AIArtHandle path = (*matches)[i];

		error = sAIPath->GetPathSegmentCount( path, &progress_increment );
		if ( error ) goto errorTag;

		error = twirl_path( pb, path, progress_current, progress_total );
		if ( error ) goto errorTag;

		progress_current += progress_increment;

		sAIUser->UpdateProgress( progress_current, progress_total );
		if ( sAIUser->Cancel() ) {
			error = kCanceledErr;
			goto errorTag;
		}

	}

	sAIMDMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle)matches );
	return kNoErr;

errorTag:
	if ( matches )
		sAIMDMemory->MdMemoryDisposeHandle((AIMdMemoryHandle) matches );

	return error;
}

AIErr go_twirl( AILiveEffectGoMessage *pb )
{
	AILiveEffectParameters liveEffectDictionary = pb->parameters;
	parms_t parms;
	short progress_increment;
	long progress_current;
	AIErr error = kNoErr;
	AIArtHandle path = pb->art;
	AIArtHandle anotherart = pb->art;
	short artType;
	AIDictKey dictKey;

	dictKey = sDictionary->Key("angle");
	if ( sDictionary->IsKnown( liveEffectDictionary, dictKey ) )
	{
		sDictionary->GetRealEntry( liveEffectDictionary, dictKey, &(parms.d_angle) );
		dictKey = sDictionary->Key("position");
		sDictionary->GetBooleanEntry( liveEffectDictionary, dictKey, &(parms.bPositionSet) );
	}
	else
	{
		return kNoErr;
	}

	parms.twirl = sAIMath->DegreeToRadian( parms.d_angle );

	AIRealRect one_bounds;

	error = sAIArt->GetArtBounds( pb->art, &one_bounds );
	if ( error ) goto errorTag;
	error = sAIArt->GetArtType( anotherart, &artType );
	if ( error ) goto errorTag;

	parms.center.h = sAIMath->AIRealDiv( one_bounds.right + one_bounds.left, _ShortToAIReal(2) );
	parms.center.v = sAIMath->AIRealDiv( one_bounds.bottom + one_bounds.top, _ShortToAIReal(2) );

	parms.diagonal = sAIMath->AIRealPointLength( (AIRealPoint *) &one_bounds, &(parms.center) );

	do {
		if ( artType == kGroupArt )
		 	error = sAIArt->GetArtFirstChild( anotherart, &anotherart );
		else
			error = sAIArt->GetArtSibling( anotherart, &anotherart );
		if ( error ) goto errorTag;
		if ( anotherart ) 
		{
			error = sAIArt->GetArtType( anotherart, &artType );
			if ( error ) goto errorTag;
			if ( artType == kPathArt )
			{
				error = sAIArt->GetArtBounds( anotherart, &one_bounds );
				if ( error ) goto errorTag;

				error = sAIPath->GetPathSegmentCount( anotherart, &progress_increment );
				if ( error ) goto errorTag;

				error = twirl_path( parms, anotherart, 1, 1 );
				if ( error ) goto errorTag;
			}
		}
	} while ( anotherart );

	path = anotherart ? anotherart : path;

	progress_current = 0;


	progress_current += progress_increment;

	if ( sAIUser->Cancel() ) 
	{
		error = kCanceledErr;
	}

errorTag:

	return error;
}

AIErr twirl_path( AIFilterMessage *pb, AIArtHandle path, long progress_current,
		long progress_total )
{
	parms_t **parms = (parms_t **) pb->parameters;
	short count, i;
	AIRealPoint center;
	AIReal diagonal, twirl;
	AIErr error;

	center = (**parms).center;
	diagonal = (**parms).diagonal;
	twirl = (**parms).twirl;

	error = sAIPath->GetPathSegmentCount( path, &count );
	if ( error ) goto errorTag;

	for ( i = 0; i < count; ++i ) {

		AIPathSegment segment;
		AIRealMatrix transform;
		AIReal angle;
		AIReal length;

		error = sAIPath->GetPathSegments( path, i, 1, &segment );
		if ( error ) goto errorTag;

		length = sAIMath->AIRealPointLength( &center, &segment.p );
		if ( length < 0 ) length = -length;
		angle = sAIMath->AIRealMul( twirl, sAIMath->AIRealDiv( length, diagonal ) );

		sAIMath->AIRealMatrixSetTranslate( &transform, -center.h, -center.v );
		sAIMath->AIRealMatrixConcatRotate( &transform, angle );
		sAIMath->AIRealMatrixConcatRotate( &transform, -twirl );
		sAIMath->AIRealMatrixConcatTranslate( &transform, center.h, center.v );
	
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.p,   &segment.p );
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.in,  &segment.in );
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.out, &segment.out );
	
		error = sAIPath->SetPathSegments( path, i, 1, &segment );
		if ( error ) goto errorTag;

		sAIUser->UpdateProgress( progress_current + i, progress_total );

	}

	return kNoErr;

errorTag:
	return error;
}

AIErr twirl_path( parms_t &pb, AIArtHandle path, long progress_current,
		long progress_total )
{
	short count, i;
	AIRealPoint center;
	AIReal diagonal, twirl;
	AIErr error;

	center = pb.center;
	diagonal = pb.diagonal;
	twirl = pb.twirl;

	error = sAIPath->GetPathSegmentCount( path, &count );
	if ( error ) goto errorTag;

	for ( i = 0; i < count; ++i ) {

		AIPathSegment segment;
		AIRealMatrix transform;
		AIReal angle;
		AIReal length;

		error = sAIPath->GetPathSegments( path, i, 1, &segment );
		if ( error ) goto errorTag;

		length = sAIMath->AIRealPointLength( &center, &segment.p );
		if ( length < 0 ) length = -length;
		angle = sAIMath->AIRealMul( twirl, sAIMath->AIRealDiv( length, diagonal ) );

		sAIMath->AIRealMatrixSetTranslate( &transform, -center.h, -center.v );
		sAIMath->AIRealMatrixConcatRotate( &transform, angle );
		sAIMath->AIRealMatrixConcatRotate( &transform, -twirl );
		sAIMath->AIRealMatrixConcatTranslate( &transform, center.h, center.v );
	
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.p,   &segment.p );
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.in,  &segment.in );
		sAIMath->AIRealMatrixXformPoint( &transform, &segment.out, &segment.out );
	
		error = sAIPath->SetPathSegments( path, i, 1, &segment );
		if ( error ) goto errorTag;

		sAIUser->UpdateProgress( progress_current + i, progress_total );

	}

	return kNoErr;

errorTag:
	return error;
}




