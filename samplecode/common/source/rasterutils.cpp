//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/rasterutils.cpp $
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
#include "raster utils.h"

#define		kRowBytesMask			0x3fff



// Creates an offscreen GWorld and locks down its pixels
extern FXErr createOffscreen( GWorldPtr *offscreen, Rect *bounds, short depth )
{
    QDErr err;
    FXErr error = kNoErr;
	PixMapHandle offscreenPMHandle;
    
    // create offscreen graphics world
    err = NewGWorld(offscreen, depth, bounds, nil, nil, 0);

    if (!offscreen || (err != kNoErr))
   	error = kMyOffscreenErr;
   
    offscreenPMHandle = GetGWorldPixMap(*offscreen);
    if ( !LockPixels(offscreenPMHandle) ) {
    	error = kMyOffscreenErr;
        DisposeGWorld(*offscreen);
		}

	RectRgn( (*offscreen)->clipRgn, &(*offscreen)->portRect);
		
    return error;
}



// Unlock any locked pixels in a GWorld and dipose of it
extern void disposeOffscreen( GWorldPtr *offscreen )
{
	PixMapHandle offscreenPMHandle = GetGWorldPixMap(*offscreen);

    // unlock & release the pixel image
    UnlockPixels(offscreenPMHandle);
    DisposeGWorld(*offscreen);
    *offscreen = nil;
}




// Given a GWorld and a dpi, this creates the appropriate raster art object to receive
// it and fills in a copy request record to be using in transfering the pixels.  
extern FXErr newRasterArtForGWorld( GWorldPtr theWorld, Fixed dpi,
			 MakeGWorldTileRequest *request, AIArtHandle *newRaster ) {

	FXErr 			error = kNoErr;
	AIRasterRecord	rasterInformation;
	AIArtHandle		theRasterObject;		
	Rect 			nBounds;
	Rect			bounds;
	FixedPoint		inverseScale;
	FixedMatrix		rasterMatrix;
	Fixed 			scale;
	

	error = kNoErr;

	// Raster objects have a base resolution of 72dpi.  The resolution can be changed 
	// by increasing the image bounds by a scale and using the inverse scale as a 
	// scaling factor.  For instance, to do 144 dpi, uses bounds*2 with a scale of 50%.
	// bounds * scale and kFixedOne/scale
	scale = sMath->FixedDiv( dpi, _ShortToFixed( 72 ));

	// Make a uninitialized raster object
	error = sArt->NewArt( kRasterArt, kPlaceAboveAll, nil, &theRasterObject );
	if ( !error ) {

		// an init it...
		error = sRaster->GetRasterInfo( theRasterObject, &rasterInformation );
		if ( !error ) {

			// get the bounds to create the gworld and raster art
			bounds = ((GrafPtr)theWorld)->portRect;
			nBounds.top = 0;
			nBounds.left = 0;
			nBounds.bottom = _FixedTruncToShort( sMath->FixedMul( scale, _ShortToFixed(bounds.bottom) ) );// + 1;
			nBounds.right = _FixedTruncToShort( sMath->FixedMul( scale, _ShortToFixed(bounds.right) ) );// + 1;

			rasterInformation.colorSpace = kRGBColorSpace;
			error = GetColorSpaceDepth( rasterInformation.colorSpace, &rasterInformation.bitsPerPixel );
			
			rasterInformation.bounds = nBounds;
			rasterInformation.byteWidth = (rasterInformation.bounds.right * (rasterInformation.bitsPerPixel / 8));
			
			error = sRaster->SetRasterInfo( theRasterObject, &rasterInformation );
			if ( !error ) {
				// now set the scale of the the raster object
				inverseScale.h = sMath->FixedDiv( kFixedOne, scale );
				inverseScale.v = sMath->FixedDiv( kFixedOne, scale );
				
				sMath->FixedMatrixSetScale( &rasterMatrix, inverseScale.h, inverseScale.v );
				error = sRaster->SetRasterMatrix( theRasterObject, &rasterMatrix );					
				}

			// if successful, fill in parts of the copy request record
			if (!error) {
				request->fRasterBounds = rasterInformation.bounds;
				request->fSelectionBounds.top = kFixedZero;
				request->fSelectionBounds.left = kFixedZero;
				request->fSelectionBounds.bottom = _ShortToFixed( nBounds.bottom );
				request->fSelectionBounds.right = _ShortToFixed( nBounds.right );
	
				request->fScale = scale;
				request->fColorSpace = rasterInformation.colorSpace;
				request->fWorld = theWorld;
				}
			}
		if (error)
			sArt->DisposeArt( theRasterObject );
		}
	
	if (error)
		*newRaster = nil;
	else
		*newRaster = theRasterObject;

	return( error );	
}
	


	
// given a raster art object and copy request record, copy a gworld to the Illustrator object	
FXErr copyGWorldToRasterArt( MakeGWorldTileRequest	*request, AIArtHandle destRaster ) {
	FXErr error = kNoErr;
	short sliceWidth, sliceHeight;
	PixMapHandle offscreenPMHandle;
	CGrafPtr savedWorld;
	GDHandle savedDevice;

	GetGWorld( &savedWorld, &savedDevice );
	SetGWorld( request->fWorld, nil );

	offscreenPMHandle = GetGWorldPixMap( request->fWorld );
	LockPixels( offscreenPMHandle );
	request->fWorldTile.data = GetPixBaseAddr( offscreenPMHandle );

	// This is the height and width to be set at a given time
	sliceWidth = (request->fWorldSlice.right - request->fWorldSlice.left);
	sliceHeight = (request->fWorldSlice.bottom - request->fWorldSlice.top);

	// and is used to determine the slice (subset) of the whole which is to be copied
	request->fRasterSlice.top = request->fRasterBounds.top;
	request->fRasterSlice.bottom = request->fRasterBounds.top + sliceHeight;

	// if you were doing a using DrawArt() into a series of RasterArt tiles
	// you would do something like this to set the origin relative to which
	// the art is drawn, moving it with the slice horizontally and vertically across
	// the tile.  (Not used here since this basically a GWorld transfer.)
	// request->fDrawArt.origin.v = request->fSelectionBounds.top;
	
	while ( !error && (request->fRasterSlice.top < request->fRasterBounds.bottom) ) {

		request->fRasterSlice.left = request->fRasterBounds.left;
		request->fRasterSlice.right = request->fRasterSlice.left + sliceWidth;
		
		// see the DrawArt() comment above
		// request->fDrawArt.origin.h = request->fSelectionBounds.left;
		
		while ( !error && (request->fRasterSlice.left < request->fRasterBounds.right) ) {

			// copy the slices horizontally
			error = sRaster->SetRasterTile( destRaster, &request->fRasterSlice, &request->fWorldTile, &request->fWorldSlice );
			
			// and increment for the next slice
			if ( !error ) {
				// see the DrawArt() comment above
				// request->fDrawArt.origin.h += sliceWidth;
				request->fRasterSlice.left += sliceWidth;
				request->fRasterSlice.right += sliceWidth;
				}
			}

		if ( !error ) {
			// see the DrawArt() comment above
			// request->fDrawArt.origin.v += sliceHeight;
			request->fRasterSlice.top += sliceHeight;
			request->fRasterSlice.bottom += sliceHeight;
			}					
		}
		
	SetGWorld( savedWorld, savedDevice );

	return error;
}





extern FXErr CreateGWorldTile( MakeGWorldTileRequest	*request )

{

	// Locals
	FXErr 					error;
	PixMapHandle			pixelMapHandle;
		
	error = kNoErr;
		
	switch ( request->fColorSpace ) {
	
		case kGrayColorSpace:
			request->fWorldSlice.front = 0;
			request->fWorldSlice.back = 1;
			request->fRasterSlice.front = 0;
			request->fRasterSlice.back = 1;
			request->fWorldTile.colBytes = 1;
			request->fWorldTile.channelInterleave[0] = 0;	// Identical Mapping
		break;
		
		case kRGBColorSpace:
			request->fWorldSlice.front = 1;
			request->fWorldSlice.back = 4;
			request->fRasterSlice.front = 0;
			request->fRasterSlice.back = 3;
			request->fWorldTile.colBytes = 4;				// GWorlds don't do 24 bit, 16 or 32 only
			request->fWorldTile.channelInterleave[0] = 0;	// Alpha channel is ignored by setting wordSlice.front to 1
			request->fWorldTile.channelInterleave[1] = 0;	// Map 32-bit red position to 24-bit red position
			request->fWorldTile.channelInterleave[2] = 1;	// Map 32-bit green position to 24-bit green position
			request->fWorldTile.channelInterleave[3] = 2;	// Map 32-bit blue position to 24-bit blue position
		break;											
		
		case kCMYKColorSpace:
			request->fWorldSlice.front = 0;
			request->fWorldSlice.back = 4;
			request->fRasterSlice.front = 0;
			request->fRasterSlice.back = 4;
			request->fWorldTile.colBytes = 4;
			request->fWorldTile.channelInterleave[0] = 0;	// Identical Mapping
			request->fWorldTile.channelInterleave[1] = 1;
			request->fWorldTile.channelInterleave[2] = 2;
			request->fWorldTile.channelInterleave[3] = 3;
		break;
	
	}
	
	request->fWorldSlice.top = request->fRasterBounds.top;
	request->fWorldSlice.left = request->fRasterBounds.left;
	request->fWorldSlice.bottom = request->fRasterBounds.bottom;
	request->fWorldSlice.right = request->fRasterBounds.right;
	
	request->fWorldTile.data = nil;
	request->fWorldTile.bounds = request->fWorldSlice;
	request->fWorldTile.bounds.front = 0;
	request->fWorldTile.bounds.back = request->fWorldTile.colBytes;
	pixelMapHandle = GetGWorldPixMap( request->fWorld );
	request->fWorldTile.rowBytes = ((*pixelMapHandle)->rowBytes & kRowBytesMask);
	request->fWorldTile.planeBytes = 0;		
	
	return( error );	
}





extern FXErr GetColorSpaceDepth(

	int16		colorSpace,
	int16		*depthPointer )
	
{

	// Locals
	
		FXErr					error;
		
	error = kNoErr;
	
	switch ( colorSpace ) {
	
		case kGrayColorSpace:
			*depthPointer = 8;
		break;
		
		case kRGBColorSpace:
			*depthPointer = 24;
		break;
		
		case kCMYKColorSpace:
			*depthPointer = 32;
		break;
		
		default:
			*depthPointer = 0;
			error = kRasterTypeNotSupportedErr;
		break;
	
	}
	
	return( error );

}
