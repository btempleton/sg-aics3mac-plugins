//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TwirlFilter/Source/filterHandler.h $
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

#ifndef __filterHandler__
#define __filterHandler__

#include "AIFilter.h"
#include "necessitiesRes.h" //for kFilterStrings definition (GI 1/97)

#define kMaxFilters 10 // Just because it is.  It can be whatever a plug-in needs.

// This structure will be passed back to Illustrator, so you can store 
// information here that you will use next time the filter is called.  
// This is different from the global variables block of the plug-in. 
// Since a plug-in might have multiple filters, each one can have parameter
// block with different values, and the correct parameter block will be
// passed to the filter when it is called.  This is easier than storing all
// possible parameters in the globals block.  The structure is allocated using
// the MDMemory suite functions. 
typedef struct {

	// your user parameters go here
	AIReal d_angle;

	AIReal twirl;
	AIRealPoint center;
	AIReal diagonal;

	ADMPoint dialog_position;
	ASBoolean	bPositionSet;

} parms_t;



extern AIErr addFilters( SPInterfaceMessage *message );

extern AIErr filterGetParms( AIFilterMessage *message );
extern AIErr goFilter( AIFilterMessage *message );

#endif
