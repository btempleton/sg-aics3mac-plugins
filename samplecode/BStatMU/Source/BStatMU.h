//========================================================================================
//  
//  $File: BStatMU.h $
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

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/


#ifndef BSTATMU_H
#define BSTATMU_H
#include "common.h"

#import "Node.h"
#import "Plate.h"

bool BStatMU();

//Checks
bool DocumentOriginInLowerLeft();
bool KeyObjectsFound();


//GLOBALS
#define BSTATMU_VERSION 1.2

extern AIColor registrationColor;
extern AIDictionaryRef dictMain;


#endif // BSTATMU_H