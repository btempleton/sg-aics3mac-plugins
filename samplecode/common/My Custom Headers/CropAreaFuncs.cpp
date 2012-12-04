/*
 *  CropAreaFuncs.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 1/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CropAreaFuncs.h"
#include "DictFuncs.h"

AIRealRect offsetRect;
extern Node* startNode;

void ForceCropCoordUpdate() {
	bool flag = FALSE;
	ASInt32 cropCount = 0;
	sAICropArea->GetCount(&cropCount);
	
	if (cropCount) {
		
		AICropAreaPtr cropArea;
		AIRealRect* oldCropRectArray;
		oldCropRectArray = new AIRealRect[cropCount];
		AIRealRect* newCropRectArray;
		newCropRectArray = new AIRealRect[cropCount];
		
		//Store the original crop area rect
		for (int i = 0 ; i < cropCount ; i++ ) {
			sAICropArea->Get(i, &cropArea);
			oldCropRectArray[i] = cropArea->m_CropAreaRect;
		}
		
		//We need to select the crop tool to force the crop areas to update correctly
		AIToolHandle prevTool = NULL;
		AIToolHandle cropTool = NULL;
		AIToolType toolType = 0;
		sAITool->GetSelectedTool(&prevTool);
		sAITool->GetToolNumberFromName(kCropTool, &toolType);
		sAITool->GetToolHandleFromNumber(toolType, &cropTool);
		sAITool->SetSelectedTool(cropTool);
		sAITool->SetSelectedTool(prevTool);
		
		//Sometimes there is falsely reported 1 crop area. After we do that force update,
		//There are none, so we'll check the count again and if its zero now, break
		sAICropArea->GetCount(&cropCount); if ( cropCount == 0 ) {
			delete [] oldCropRectArray;
			delete [] newCropRectArray;
			return;
		}
		
		//Store the new crop area rect
		for (int i = 0 ; i < cropCount ; i++ ) {
			sAICropArea->Get(i, &cropArea);
			newCropRectArray[i] = cropArea->m_CropAreaRect;
			
			//Check if new and old are the same and set the flag so we know theres some we have to fix
			if ( !sAIRealMath->AIRealRectEqual(&oldCropRectArray[i], &newCropRectArray[i]) ) { flag = TRUE; }
		}
		
		if (flag) {
			for (int i = 0 ; i < cropCount ; i++ ) {
				//Crop areas same after update, we need to adjust by the offset
				if ( sAIRealMath->AIRealRectEqual(&oldCropRectArray[i], &newCropRectArray[i]) ) {
					//Adjust the crop rect
					sAIRealMath->AIRealRectSet(&newCropRectArray[i],
											   (newCropRectArray[i].left - offsetRect.left),
											   (newCropRectArray[i].top - offsetRect.top),
											   (newCropRectArray[i].right - offsetRect.right),
											   (newCropRectArray[i].bottom - offsetRect.bottom) );
					cropArea->m_CropAreaRect = newCropRectArray[i];
					sAICropArea->Update(i, cropArea);
				}
				//Crop areas different after update (Should always be the first one,
				//As Illustrator updates the first one automatically.
				else {
					//Store the difference
					sAIRealMath->AIRealRectSet(&offsetRect,
											   (oldCropRectArray[i].left - newCropRectArray[i].left),
											   (oldCropRectArray[i].top - newCropRectArray[i].top),
											   (oldCropRectArray[i].right - newCropRectArray[i].right),
											   (oldCropRectArray[i].bottom - newCropRectArray[i].bottom) );
				}
			}
		}
		//Clean up
		delete [] oldCropRectArray;
		delete [] newCropRectArray;
	}
}


AIRealPoint FindDistanceFromArtBoard(Node* node) {
	
	AIRealPoint offset = {0,0};
	AIRealRect nodeBounds, startBounds;
	AIArtHandle nodeRegBox = NULL;
	AIArtHandle startRegBox = NULL;
	
	nodeRegBox = GetArtHandleFromUIDRef(node->p->RegBoxUIDRef());
	startRegBox = GetArtHandleFromUIDRef(startNode->p->RegBoxUIDRef());
	
	if (!nodeRegBox || !startRegBox) {
		return offset;
	}
	
	sAIArt->GetArtBounds(nodeRegBox, &nodeBounds);
	sAIArt->GetArtBounds(startRegBox, &startBounds);
	
	AIRealPoint a = {startBounds.left, startBounds.top};
	AIRealPoint b = {nodeBounds.left, nodeBounds.top};
	
	sAIRealMath->AIRealPointSubtract(&a, &b, &offset);

	return offset;
}