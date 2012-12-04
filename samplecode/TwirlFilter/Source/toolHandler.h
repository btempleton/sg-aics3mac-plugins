//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/toolHandler.h $
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

#ifndef __toolHandler__
#define __toolHandler__

#include "common.h"

extern AIErr addTool( SPInterfaceMessage *message );

extern AIErr toolOptions( AIToolMessage *message );
extern AIErr toolTrackCursor( AIToolMessage *message );
extern AIErr toolMouseDown( AIToolMessage *message );
extern AIErr toolMouseDrag( AIToolMessage *message );
extern AIErr toolMouseUp( AIToolMessage *message );
extern AIErr toolSelect( AIToolMessage *message );
extern AIErr toolDeselect( AIToolMessage *message );
extern AIErr toolValidate( AIToolMessage *message );

extern void SetPlatformCursor(SPPluginRef pluginRef, int nCursorID);


#define kMyToolIcon				1
#define kToolIcons					16050
#define kNoIconErr				'!ico'

#define kCursorID				16000


#endif
