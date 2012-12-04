//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/rasterutils.h $
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


#define kMyOffscreenErr '!Off'


typedef struct {

	GWorldPtr 				fWorld;			// pass this in to newRasterForGWorld
	// Scratch Fields
	Rect					fRasterBounds;  // filled out by newRasterForGWorld
	int16					fColorSpace;	// passed into CreateGWorldTile
	Fixed					fScale;
	FixedRect				fSelectionBounds;

	Slice					fRasterSlice;
	Slice					fWorldSlice;
 	Tile					fWorldTile ;
 		
} MakeGWorldTileRequest;
	


extern FXErr newRasterArtForGWorld( GWorldPtr theWorld, Fixed scale, 
			MakeGWorldTileRequest *request, AIArtHandle *newRaster );
extern FXErr CreateGWorldTile( MakeGWorldTileRequest *request );
extern FXErr GetColorSpaceDepth( int16 colorSpace, int16 *depthPointer );
extern FXErr createOffscreen( GWorldPtr *offscreen, Rect *bounds, short depth );
extern void disposeOffscreen( GWorldPtr *offscreen );
extern FXErr copyGWorldToRasterArt( MakeGWorldTileRequest *request, AIArtHandle destRaster );
