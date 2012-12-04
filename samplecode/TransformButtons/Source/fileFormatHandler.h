//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/fileFormatHandler.h $
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

#ifndef __fileFormatHandler__
#define __fileFormatHandler__

#include "AIFileFormat.h"

extern AIErr addFileFormat( SPInterfaceMessage *message );
extern AIErr goGetFormatParms( AIFileFormatMessage *message );
extern AIErr goFileFormat( AIFileFormatMessage *message );
extern AIErr goCheckFormat( AIFileFormatMessage *message );

#endif
