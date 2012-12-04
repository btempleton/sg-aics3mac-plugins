//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/toolHandler.cpp $
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

#include "common.h"
#include "toolHandler.h"


extern AIErr addTool( SPInterfaceMessage *message ) {
	/*
	 AIErr error = kNoErr;
	 AIAddToolData toolData;
	 AIToolHandle theTool;
	 ADMIconRef rolloverIcon = sADMIcon2->GetFromResource (  message->d.self , "PantoBorderToolRolloverIcon" , 2, kToolIcons );
	 
	 toolData.title = "Panto/Border Tool";
	 toolData.tooltip = "Panto/Border Tool";
	 
	 toolData.icon = sADMIcon2->GetFromResource (  message->d.self , "PantoBorderToolIcon" , 1, kToolIcons );
	 if ( ( sADMIcon2->GetType( toolData.icon ) ) == kUnknown  )
	 return kNoIconErr;
	 
	 // this tells you what kind of icon it returned
	 // iconType = sADMIcon->GetType( toolData.icon );
	 
	 toolData.sameGroupAs = kNoTool;
	 toolData.sameToolsetAs = kNoTool;
	 
	 error = sAITool->AddTool( message->d.self, "PantoBorderTool", &toolData,
	 kToolWantsToTrackCursorOption, &theTool );
	 sAITool->SetToolRolloverIcon( theTool, rolloverIcon);
	 
	 error:
	 return error;
	 */
}



extern AIErr toolOptions( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	// put up our options dialog here
	
	return error;
	
}



extern ASErr toolTrackCursor( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	SetPlatformCursor(message->d.self, kCursorID);
	
	
	return error;
	
}


extern AIErr toolMouseDown( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	// we want our initial mouse down to base the drag on later	
	g->startingPoint = message->cursor;
	
	if (error)
		goto error;
	
error:
	return error;
}


extern AIErr toolMouseDrag( AIToolMessage *message ) {
	AIErr error = kNoErr;
	AIArtHandle path;
	AIPathSegment segments[8];
	AIPathStyle pathStyle;
	AIPathStyleMap pathStyleMap;
	
	// all suites already acquired. See shell.c
	
	error = sAIUndo->UndoChanges( );
	
	g->endPoint = message->cursor;
	
	// create new art. we will fill it with points below
	error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, NULL, &path );
	if ( error )
		goto error;
	
	if (sADMTracker->GetModifiers(NULL) & kADMShiftKeyDownModifier)
	{
		short angle = (short)(sAIRealMath->RadianToDegree(sAIRealMath->AIRealPointAngle(&g->startingPoint, &g->endPoint)));
		
		if ((angle <= 90 && angle >= 0) || (angle <= -90 && angle >= -180))
		{
			g->endPoint.v = g->startingPoint.v + (g->endPoint.h - g->startingPoint.h);
			g->endPoint.h = g->startingPoint.h + (g->endPoint.v - g->startingPoint.v);
		}
		else
		{
			g->endPoint.v = g->startingPoint.v - (g->endPoint.h - g->startingPoint.h);
			g->endPoint.h = g->startingPoint.h - (g->endPoint.v - g->startingPoint.v);
		}
	}
	
	
	//	RECTANGLE
	// RECTANGLE has 4 points	
	error = sAIPath->SetPathSegmentCount( path, 4 );		
	
	// beginning (and end) point. This is the first corner.
	segments[0].p.h = g->startingPoint.h;
	segments[0].p.v = g->startingPoint.v;
	segments[0].in = segments[0].out = segments[0].p;
	segments[0].corner = true;
	
	// next corner
	segments[1].p.h = g->startingPoint.h;
	segments[1].p.v = g->endPoint.v;
	segments[1].in = segments[1].out = segments[1].p;
	segments[1].corner = true;
	
	segments[2].p.h = g->endPoint.h;
	segments[2].p.v = g->endPoint.v;
	segments[2].in = segments[2].out = segments[2].p;
	segments[2].corner = true;
	
	segments[3].p.h = g->endPoint.h;
	segments[3].p.v = g->startingPoint.v;
	segments[3].in = segments[3].out = segments[3].p;
	segments[3].corner = true;		
	
	error = sAIPath->SetPathSegments( path, 0, 4, segments );
	if ( error )
		goto error;
	
	
	
	error = sAIPath->SetPathClosed( path, true );
	if ( error )
		goto error;
	
	// fill and stroke with black; 1 point line
	error = sAIPathStyle->GetCurrentPathStyle( &pathStyle, &pathStyleMap );
	pathStyle.fillPaint = true;
	pathStyle.fill.color.kind = kGrayColor;
	pathStyle.fill.color.c.g.gray = kAIRealOne;
	
	pathStyle.strokePaint = true;
	pathStyle.stroke.color.kind = kGrayColor;
	pathStyle.stroke.color.c.g.gray = kAIRealOne;
	pathStyle.stroke.width = kAIRealOne;
	error = sAIPathStyle->SetPathStyle( path, &pathStyle );
	
error:
	return error;
	
}


extern AIErr toolMouseUp( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	return error;
	
}

extern AIErr toolSelect( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	return error;
	
}


extern AIErr toolDeselect( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	return error;
	
}


extern AIErr toolValidate( AIToolMessage *message ) {
	
	AIErr error = kNoErr;
	
	return error;
	
}





/*static*/ void SetPlatformCursor(SPPluginRef pluginRef, int nCursorID)
{
	//	ASErr error = kNoErr;
#if Macintosh
	CursHandle cursor; 
	
	cursor = GetCursor( nCursorID );
	if ( cursor )
		SetCursor( *cursor );
#else
	HCURSOR cursor;
	SPAccessRef access;
	SPPlatformAccessInfo spAccessInfo;
	
	error = sSPAccess->GetPluginAccess(pluginRef, &access);
	if( kNoErr == error)
		error = sSPAccess->GetAccessInfo(access, &spAccessInfo);
	if( kNoErr == error)
	{
		cursor = LoadCursor((HINSTANCE)spAccessInfo.defaultAccess, MAKEINTRESOURCE(nCursorID));
		if ( cursor )
			SetCursor(cursor);
	}
#endif
	
	return;
}


