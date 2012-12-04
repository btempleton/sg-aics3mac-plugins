/*
 *  CropAreaFuncs.h
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 1/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CROPAREAFUNCS_H
#define CROPAREAFUNCS_H
#include "common.h"
#include "Node.h"


//Selects and deselects the crop area tool to force crop area coords to update
void ForceCropCoordUpdate();

//Stores the crop area offset if the origin moves
//This must be initialized like: sAIRealMath->AIRealRectSet(&offsetRect, 0, 0, 0, 0);
//Before you use it
extern AIRealRect offsetRect;

//Finds the distance of the passed node from the artboard
//Returns (0,0) if it could not find Registration boxes
AIRealPoint FindDistanceFromArtBoard(Node* node);


#endif  //CROPAREAFUNCS_H