//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Shell/Source/menuHandler.h $
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

#ifndef __menuHandler__
#define __menuHandler__

#include "AIMenu.h"

extern AIErr addMenu( SPInterfaceMessage *message );

extern AIErr goMenuItem( AIMenuMessage *message );
extern AIErr updateMenuItem( AIMenuMessage *message );


#endif
