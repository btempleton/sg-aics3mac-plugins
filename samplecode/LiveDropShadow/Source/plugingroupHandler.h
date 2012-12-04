//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/LiveDropShadow/Source/plugingroupHandler.h $
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

#ifndef __plugingroupHandler__
#define __plugingroupHandler__

#include "AIPluginGroup.h"

extern AIErr goNotify( AIPluginGroupMessage *message );
extern AIErr goUpdate( AIPluginGroupMessage *message );

extern AIErr StartLensObject( AIArtHandle *object, ObjectData *data );
extern AIErr FinishLensObject( AIArtHandle *object, ObjectData *data );
extern AIErr appendPluginGroup( AIArtHandle *object, ObjectData *data, AIArtHandle path );

extern AIErr ReleaseLensObject( AIArtHandle plugin );

extern AIErr FirstLensObject( AIArtHandle *object, ObjectData *data );
extern AIErr LastLensObject( AIArtHandle *object, ObjectData *data );
extern AIErr ModifyLensObject( AIArtHandle *object, ObjectData *data, AIArtHandle plugin );
extern AIErr EditLensObject( ObjectData *data );

extern AIErr SetFilteredFill( AIBoolean *paint, AIFillStyle *fill );
extern AIErr SetFilteredStroke( AIBoolean *paint, AIStrokeStyle *stroke );
extern AIErr SetFilteredStyle( AIArtHandle object );

extern AIErr SetBackingFill( AIBoolean *paint, AIFillStyle *fill );
extern AIErr SetBackingStroke( AIBoolean *paint, AIStrokeStyle *stroke );
extern AIErr SetBackingStyle( AIArtHandle object );

extern AIErr SetBoundingFill( AIBoolean *paint, AIFillStyle *fill );
extern AIErr SetBoundingStroke( AIBoolean *paint, AIStrokeStyle *stroke );
extern AIErr SetBoundingStyle( AIArtHandle object );

extern AIErr SetClippingStyle( AIArtHandle object );
extern AIErr DuplicateCoveredArt( AIArtHandle source, AIArtHandle destination, AIRealRect *bounds, AIArtHandle start, AIBoolean *found );

extern AIErr ReportError( AIErr result );

extern AIErr setDropShadowStyle( AIArtHandle object );
extern AIErr setDropShadowFill( AIFillStyle *fill );
extern AIErr setDropShadowStroke( AIStrokeStyle *stroke );
extern AIErr transformDropShadow(  AIArtHandle art, AIReal tx, AIReal ty, AIReal theta, AIReal sx, AIReal sy );

#endif
