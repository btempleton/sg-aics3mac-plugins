#ifndef __AI80Mesh__
#define __AI80Mesh__

/*
 *        Name:	AI80Mesh.h
 *   $Revision: 26 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 8.0 Mesh Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AIMesh__
#include "AIMesh.h"
#endif

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIMeshSuiteVersion1					AIAPI_VERSION(1)


/*******************************************************************************
 **
 **	Suites
 **
 **/


typedef struct {

	AIAPI AIErr (*InitCartesian) (AIArtHandle mesh, long i, long j);
	AIAPI AIErr (*InitPolar) (AIArtHandle mesh, long i, long j);
	AIAPI AIErr (*GetKind) (AIArtHandle mesh, long *kind);
	AIAPI AIErr (*GetSize) (AIArtHandle mesh, long *i, long *j);

	AIAPI AIErr (*NewSelection) (AIArtHandle mesh, AIBoolean all, AIMeshSelection* selection);
	AIAPI AIErr (*GetSelection) (AIArtHandle mesh, AIMeshSelection* selection);
	
	AIAPI AIErr (*GetPatch) (AIArtHandle mesh, long i, long j, AIMeshPatchIterator* patch);
	AIAPI AIErr (*GetStartPatch) (AIArtHandle mesh, AIMeshPatchIterator* patch);

	AIAPI AIErr (*GetNode) (AIArtHandle mesh, long i, long j, AIMeshVertexIterator* vertex);
	AIAPI AIErr (*GetStartVertex) (AIArtHandle mesh, AIMeshVertexIterator* vertex);

	AIAPI AIErr (*GetStartSegment) (AIArtHandle mesh, AIMeshSegmentIterator* segment);

	AIAPI void (*GetColorSpace) (AIArtHandle mesh, AIColorTag* kind, AICustomColorHandle* custom);
	AIAPI AIBoolean (*InvertPoint) (AIArtHandle mesh, AIRealPoint* point, AIReal* u, AIReal* v);
	AIAPI void (*EvalPoint) (AIArtHandle mesh, AIReal u, AIReal v, AIRealPoint* point);
	AIAPI void (*EvalColor) (AIArtHandle mesh, AIReal u, AIReal v, AIColor* color);

	AIAPI AIErr (*Transform) (AIArtHandle mesh, AIRealMatrix* matrix);
	AIAPI AIErr (*MapPoints) (AIArtHandle mesh, AIMeshPointMap f, void* userData);
	AIAPI AIErr (*MapColors) (AIArtHandle mesh, AIMeshColorMap f, void* userData);
	AIAPI void (*QueryColors) (AIArtHandle mesh, AIMeshColorQuery f, void* userData);

	AIAPI AIErr (*InsertU) (AIArtHandle mesh, AIReal u, long* i);
	AIAPI AIErr (*InsertV) (AIArtHandle mesh, AIReal v, long* j);
	AIAPI AIErr (*DeleteGridLines) (AIArtHandle mesh, AIReal u, AIReal v);
	
	AIAPI void (*TrackBegin) (AIArtHandle mesh);
	AIAPI void (*TrackEnd) (AIArtHandle mesh);

} AI80MeshSuite;


#include "AIHeaderEnd.h"


#endif
