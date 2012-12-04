//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/artset utils.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "common.h"
#include "artset utils.h"

#ifdef __INCLUDERASTER__
#include "raster utils.h"
#endif


extern AIErr getSelectionSet( AIArtSet *matches, long whichMatches, long *numMatches, AIBoolean justLooking ) {

	AIErr error = kNoErr;
	short 	i;
	long 	changeCount = 0;
	AIArtSpec spec[6];

	for ( i = 0; i < 6; i++ ) {
		spec[i].whichAttr = kArtSelected;
		spec[i].attr = kArtSelected;
		}

	i = 0;
	// Get the current selection, bail if none
	if ( whichMatches & kWantsPathArt ) {
		spec[i].type = kPathArt;
		i++;
		}
	if ( whichMatches & kWantsTextArt ) {
		spec[i].type = kTextArt;
		i++;
		}
	if ( whichMatches & kWantsPlacedArt ) {
		spec[i].type = kPlacedArt;
		i++;
		}
	if ( whichMatches & kWantsRasterArt ) {
		spec[i].type = kRasterArt;
		i++;
		}
	if ( whichMatches & kWantsGroupArt ) {
		spec[i].type = kGroupArt;
		i++;
		}
	if ( whichMatches & kWantsCompoundArt ) {
		spec[i].type = kCompoundPathArt;
		i++;
		}

	error = sAIArtSet->NewArtSet( matches );
	if ( error )
		goto error;
	error = sAIArtSet->MatchingArtSet( spec, i, *matches );
	if ( error )
		goto error;
	error = sAIArtSet->CountArtSet( *matches, numMatches );
	if ( error )
		goto error;
		
	if ( justLooking ) {
		sAIArtSet->DisposeArtSet( matches );
		}
		
error:
	return error;
}



extern AIErr getArtSetBounds( AIArtSet matches, AIRealRect *totalBrushBounds ) {

	AIErr error = kNoErr;
	long 	count, i;
	AIArtHandle art;
	AIBoolean bounded = false;
	
	error = sAIArtSet->CountArtSet( matches, &count );
	if ( error )
		goto error;

	// get total art bounds
	for (i = 0; i<count; i++ ) {
		AIRealRect one_bounds;
		
		error = sAIArtSet->IndexArtSet( matches, i, &art );
		if ( error )
			goto error;
		
		error = sAIArt->GetArtBounds( art, &one_bounds );
		if ( error )
			goto error;
	
		if ( !bounded ) {
			*totalBrushBounds = one_bounds;
			bounded = true;
			}
		else 
			sAIMath->AIRealRectUnion( totalBrushBounds, &one_bounds, totalBrushBounds );
	}
	
error:
	return error;
}




#ifdef __INCLUDERASTER__

extern AIErr rasterizeArtSet( AIArtSet theArt, GWorldPtr *rasterizedArt, 
			 AIReal scale, Rect *boundsRect ) {					
	AIErr error = kNoErr;
	long i, count;
	AIDrawArtData data;
	AIRealRect bounds;
	AIArtHandle art;
	CGrafPtr savedWorld;
	GDHandle savedDevice;
	short depth = 32;

	// get the bounds to create the gworld and raster art
	getArtSetBounds( theArt, &bounds );
	boundsRect->top = 0;
	boundsRect->left = 0;
	boundsRect->bottom = _AIRealTruncToShort( sAIMath->AIRealMul( scale, bounds.top - bounds.bottom) );
	boundsRect->right = _AIRealTruncToShort( sAIMath->AIRealMul( scale, bounds.right - bounds.left) );

	// set up an offscreen GWorld for the rasterized art
	error = createOffscreen( rasterizedArt, boundsRect, depth );
	if ( error )
		goto error;

	GetGWorld( &savedWorld, &savedDevice );
	SetGWorld( *rasterizedArt, NULL );
	EraseRect( &(*rasterizedArt)->portRect );

	// set up the DrawArt data
	data.version = kAIDrawArtVersion;		// pass the suite version
	data.flags = kAIDrawArtPreviewMask;		// OR the options you want together

//	flag									meaning if set, else meaning if not set
//	------------------------------------    ------------------------------------------------------------
// 	kAIDrawArtPreviewMask					show in preview if set, else in line art mode
// 	kAIDrawArtPreviewImagesMask				set to rasterize images, else images are drawn as a Box
//	kAIDrawArtPreviewDimmedImagesMask		set to show grayed images, else images are drawn as a Box
// 	kAIDrawArtPreviewImageOrDimImageMask	above pre|'d together	
//	kAIDrawArtPreviewPatternsMask			rasterize pattern artwork, else pattern fills are drawn as black
//	kAIDrawArtSelectObjectsMask				use selectionColor to indicate selected art, else no selection shown
//	kAIDrawArtShowGuidesMask				rasterize guides as dotted lines, else ignore them


	data.type = kAIDrawArtGWorldOutput;			// the type of port to recieve the raster image
	data.greekThreshold = _ShortToAIReal( 10 );	// point size below which text is greeked

// we don't care about the selection color since its turned off
	data.selectionColor.mustBeZero = 0;
	data.selectionColor.red = 0;
	data.selectionColor.green = 0;
	data.selectionColor.blue = 0;
/* otherwise, set kAIDrawArtSelectObjectsMask and use something like:			
	data.selectionColor.mustBeZero = 0;
	data.selectionColor.red = 0x4f00;
	data.selectionColor.green = 0x8000;
	data.selectionColor.blue = 0xff00;
*/

	// set a value here to scale the image for reduction or enlargment
	sAIMath->AIRealMatrixSetScale( &data.matrix, scale, scale );
	
	// the art is drawn in the output port relative to the point
	// for instance, to place a white border around the image you might offset 
	// the bounds by 5 points.  If using DrawArt() on multiple art object, use the
	// top,left of the total bounds as shown here.
	data.origin.v = bounds.top;
	data.origin.h = bounds.left;
	
	// where the rasterized image is supposed to be placed.  Must correspond to data.type
	data.output.gWorld.worldPointer = *rasterizedArt;


	// the above done, we only have to specify the art object to be rasterized.  This is
	// handled within this loop.  We iterate through the art (the art set in this case)
	// and call DrawArt on each object.  Notice that artwork order is important when using
	// DrawArt repeatedly.  The loop does the backmost object first and works to the frontmost.
	// If the art were all in one group, we could just call DrawArt once for the whole group.
	error = sAIArtSet->CountArtSet( theArt, &count );
	if ( error )
		goto release;

	for ( i = count-1; i >= 0; i-- ) {
		error = sAIArtSet->IndexArtSet( theArt, i, &art );
		if ( error )
			goto release;

		data.art = art;
		error = sDrawArt->DrawArt( &data );
		if ( error )
			goto release;
		}
				
release:		
	SetGWorld( savedWorld, savedDevice );
	if ( error )
		disposeOffscreen( rasterizedArt );

error:
	return error;
}


extern void releaseRasterizedArtSet( GWorldPtr *offscreen ) {
	disposeOffscreen( offscreen );
}


		
#endif