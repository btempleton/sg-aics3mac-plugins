//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/admHandler.h $
//
//  $Revision: #4 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
#ifndef __fixblack__
#define __fixblack__

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/
 
// private functions
//AIErr createADMDialog( AINotifierMessage *message );
//ASErr ASAPI DlgInit(ADMDialogRef dlg);
//static void ASAPI DlgDestroyProc(ADMDialogRef dlg);

#include "common.h"

bool FixBlack();


void convertObjectsToGlobalBlack(AIColor *color, void *userData, AIErr *result, AIBoolean *altered);
void convertObjectsToGlobalCMYK(AIColor *color, void *userData, AIErr *result, AIBoolean *altered);
void convertZeroTintToWhite(AIColor *color, void *userData, AIErr *result, AIBoolean *altered);
void removeWhiteOverprint();

#endif //__fixblack__