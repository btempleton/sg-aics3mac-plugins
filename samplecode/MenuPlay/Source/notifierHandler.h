//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MenuPlay/Source/notifierHandler.h $
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

#ifndef __notifierHandler__
#define __notifierHandler__

#include "AINotifier.h"


extern AIErr addNotifiers( SPInterfaceMessage *message );

extern AIErr goNotifier( AINotifierMessage *message );

#endif
