//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/artset utils.h $
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

#include "AITypes.h"

//#define __INCLUDERASTER__

#define kWantsPathArt	(1L<<0)
#define kWantsTextArt	(1L<<1)
#define kWantsPlacedArt	(1L<<2)
#define kWantsRasterArt	(1L<<3)
#define kWantsGroupArt	(1L<<4)
#define kWantsCompoundArt (1L<<5)


extern AIErr getSelectionSet( AIArtSet *matches, long whichMatches, long *numMatches, AIBoolean justLooking );
extern AIErr getArtSetBounds( AIArtSet matches, AIRealRect *totalBrushBounds );


#ifdef __INCLUDERASTER__
extern AIErr rasterizeArtSet( AIArtSet theArt, GWorldPtr *rasterizedArt, 
			AIReal scale, Rect *boundsRect );
extern void releaseRasterizedArtSet( GWorldPtr *offscreen );
#endif