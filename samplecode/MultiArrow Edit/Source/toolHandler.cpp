//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MultiArrowTool/Source/toolHandler.cpp $
//
//  $Revision: #7 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#include "common.h"
#include "toolHandler.h"

//#if Macintosh
//	#include <stdlib.h>
//#endif

extern AIErr addTool( SPInterfaceMessage *message ) {

	AIErr error = kNoErr;
	AIAddToolData toolData;
	//AIToolHandle theTool;
	short i;
	char bufftitle[256], bufftip[256], firstToolName[256];	
	
		for ( i = 0 ; i < 4 ; i++ ) {
	
		sADMBasic->GetIndexString( message->d.self, kToolStrings, ( i * 2 + 1), 
							   bufftitle, sizeof( bufftitle ) );
							  
		sADMBasic->GetIndexString( message->d.self, kToolStrings, ( i * 2 + 2), 
							   bufftip, sizeof( bufftip ) );
		toolData.title = bufftitle;
		toolData.tooltip = bufftip;					   
	
		toolData.icon = sADMIcon->GetFromResource (  message->d.self, kToolIcons, (i + 1) );
		if ( ( sADMIcon->GetType( toolData.icon ) ) == kUnknown  )
			return kNoIconErr;

		// this tells you what kind of icon it returned
		// iconType = sADMIcon->GetType( toolData.icon );

		if ( i == 0 ) {
            strcpy( firstToolName, toolData.title);

			// new group on tool palette
			toolData.sameGroupAs = kNoTool;
			// new toolset in new group
			toolData.sameToolsetAs = kNoTool;
			
		}
		else {
			error = sTool->GetToolNumberFromName( firstToolName, &toolData.sameGroupAs);
			error = sTool->GetToolNumberFromName( firstToolName, &toolData.sameToolsetAs);
		}
	
		//error = sTool->GetToolNumberFromName(kScrollTool, &toolData.sameToolsetAs);
		//if (error) goto error;

		error = sTool->AddTool( message->d.self, toolData.title, &toolData,
						kToolWantsToTrackCursorOption, &g->tool[i] );
		if (error)
			goto errorTag;
	}

errorTag:
	return error;


}



extern AIErr toolOptions( AIToolMessage *message ) {

	AIErr error = kNoErr;
	// put up our options dialog here

	return error;

}



extern ASErr toolTrackCursor( AIToolMessage *message ) {

	AIErr error = kNoErr;
	short cursorIndex = 1;
	
	if ( message->tool == g->tool[1] )
		cursorIndex = 2;
	else if ( message->tool == g->tool[2] )
		cursorIndex = 3;
	else if ( message->tool == g->tool[3] )
		cursorIndex = 4;
	

	SetPlatformCursor(message->d.self, ( kCursorID + cursorIndex) );

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
	AIReal pathAngle, arrowAngle;
	AIRealPoint arrowPt1, arrowPt2;
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
		short angle = (short)(abs((int)(sAIRealMath->RadianToDegree(sAIRealMath->AIRealPointAngle(&g->startingPoint, &g->endPoint)))));

		if (angle < 45 || angle > 135)
		{
			g->endPoint.v = g->startingPoint.v;
		}
		else
		{
			g->endPoint.h = g->startingPoint.h;
		}
	}

	
	if ( message->tool == g->tool[0] ) {
		//	HEAD ARROW
		// head arrow has 5 points	
		error = sAIPath->SetPathSegmentCount( path, 5 );		

		// beginning (and end) point. This is butt end of arrow
		segments[0].p.h = g->startingPoint.h;
		segments[0].p.v = g->startingPoint.v;
		segments[0].in = segments[0].out = segments[0].p;
		segments[0].corner = true;

		// arrow head point
		segments[1].p.h = g->endPoint.h;
		segments[1].p.v = g->endPoint.v;
		segments[1].in = segments[1].out = segments[1].p;
		segments[1].corner = true;

		// angle created by line segment
		pathAngle = sAIRealMath->AIRealPointAngle( &g->endPoint, &g->startingPoint );
		arrowAngle = sAIRealMath->DegreeToRadian( _ShortToAIReal(20) );

		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle + arrowAngle, &arrowPt1 );
		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle - arrowAngle, &arrowPt2 );

		segments[2].p.h = g->endPoint.h + arrowPt1.h;
		segments[2].p.v = g->endPoint.v + arrowPt1.v;
		segments[2].in = segments[2].out = segments[2].p;
		segments[2].corner = true;

		segments[3].p.h = g->endPoint.h + arrowPt2.h;
		segments[3].p.v = g->endPoint.v + arrowPt2.v;
		segments[3].in = segments[3].out = segments[3].p;
		segments[3].corner = true;		

		segments[4].p.h = g->endPoint.h;
		segments[4].p.v = g->endPoint.v;
		segments[4].in = segments[4].out = segments[4].p;
		segments[4].corner = true;		

		error = sAIPath->SetPathSegments( path, 0, 5, segments );
		if ( error )
			goto error;
			
		}

	else if ( message->tool == g->tool[1] ) {
		
		//	TAIL ARROW
		// tail arrow has 5 points	
		error = sAIPath->SetPathSegmentCount( path, 5 );		

		// beginning point. This is point of arrow
		segments[0].p.h = g->startingPoint.h;
		segments[0].p.v = g->startingPoint.v;
		segments[0].in = segments[0].out = segments[0].p;
		segments[0].corner = true;

		// angle created by line segment
		pathAngle = sAIRealMath->AIRealPointAngle( &g->endPoint, &g->startingPoint );
		arrowAngle = sAIRealMath->DegreeToRadian( _ShortToAIReal(20) );
		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle + arrowAngle, &arrowPt1 );
		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle - arrowAngle, &arrowPt2 );

		// arrow point 1
		segments[1].p.h = g->startingPoint.h - arrowPt1.h;
		segments[1].p.v = g->startingPoint.v - arrowPt1.v;
		segments[1].in = segments[1].out = segments[1].p;
		segments[1].corner = true;

		// arrow point 2
		segments[2].p.h = g->startingPoint.h - arrowPt2.h;
		segments[2].p.v = g->startingPoint.v - arrowPt2.v;
		segments[2].in = segments[2].out = segments[2].p;
		segments[2].corner = true;
		
		// beginning point. This is point of arrow
		segments[3].p.h = g->startingPoint.h;
		segments[3].p.v = g->startingPoint.v;
		segments[3].in = segments[3].out = segments[3].p;
		segments[3].corner = true;

		// end point. This is the butt end of arrow
		segments[4].p.h = g->endPoint.h;
		segments[4].p.v = g->endPoint.v;
		segments[4].in = segments[4].out = segments[4].p;
		segments[4].corner = true;

		error = sAIPath->SetPathSegments( path, 0, 5, segments );
		if ( error )
			goto error;
		}
		
		else if ( message->tool == g->tool[2] ) {
		//	BOTH ENDS ARROW
		// tail arrow has 8 points	
		error = sAIPath->SetPathSegmentCount( path, 8 );		

		// beginning point. This is point of arrow
		segments[0].p.h = g->startingPoint.h;
		segments[0].p.v = g->startingPoint.v;
		segments[0].in = segments[0].out = segments[0].p;
		segments[0].corner = true;

		// angle created by line segment
		pathAngle = sAIRealMath->AIRealPointAngle( &g->endPoint, &g->startingPoint );
		arrowAngle = sAIRealMath->DegreeToRadian( _ShortToAIReal(20) );
		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle + arrowAngle, &arrowPt1 );
		sAIRealMath->AIRealPointLengthAngle( _ShortToAIReal(10), pathAngle - arrowAngle, &arrowPt2 );

		// arrow point 1
		segments[1].p.h = g->startingPoint.h - arrowPt1.h;
		segments[1].p.v = g->startingPoint.v - arrowPt1.v;
		segments[1].in = segments[1].out = segments[1].p;
		segments[1].corner = true;

		// arrow point 2
		segments[2].p.h = g->startingPoint.h - arrowPt2.h;
		segments[2].p.v = g->startingPoint.v - arrowPt2.v;
		segments[2].in = segments[2].out = segments[2].p;
		segments[2].corner = true;
		
		// beginning point. This is point of arrow
		segments[3].p.h = g->startingPoint.h;
		segments[3].p.v = g->startingPoint.v;
		segments[3].in = segments[3].out = segments[3].p;
		segments[3].corner = true;

		// end point. This is the butt end of arrow
		segments[4].p.h = g->endPoint.h;
		segments[4].p.v = g->endPoint.v;
		segments[4].in = segments[4].out = segments[4].p;
		segments[4].corner = true;

		// arrow point 3
		segments[5].p.h = g->endPoint.h + arrowPt1.h;
		segments[5].p.v = g->endPoint.v + arrowPt1.v;
		segments[5].in = segments[5].out = segments[5].p;
		segments[5].corner = true;
		
		// arrow point 4
		segments[6].p.h = g->endPoint.h + arrowPt2.h;
		segments[6].p.v = g->endPoint.v + arrowPt2.v;
		segments[6].in = segments[6].out = segments[6].p;
		segments[6].corner = true;		
		
		// end point. This is the butt end of arrow
		segments[7].p.h = g->endPoint.h;
		segments[7].p.v = g->endPoint.v;
		segments[7].in = segments[7].out = segments[7].p;
		segments[7].corner = true;
		
		error = sAIPath->SetPathSegments( path, 0, 8, segments );
		if ( error )
			goto error;
		}
		
	else if ( message->tool == g->tool[3] ) {
		//	STRAIGHT LINE
		error = sAIPath->SetPathSegmentCount( path, 2 );		

		// beginning point.
		segments[0].p.h = g->startingPoint.h;
		segments[0].p.v = g->startingPoint.v;
		segments[0].in = segments[0].out = segments[0].p;
		segments[0].corner = true;

		// end point
		segments[1].p.h = g->endPoint.h;
		segments[1].p.v = g->endPoint.v;
		segments[1].in = segments[1].out = segments[1].p;
		segments[1].corner = true;
		
		error = sAIPath->SetPathSegments( path, 0, 2, segments );
		if ( error )
			goto error;

	}

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





extern void SetPlatformCursor(SPPluginRef pluginRef, int nCursorID)
{

#if Macintosh
	CursHandle cursor; 

	cursor = GetCursor( nCursorID );
	if ( cursor )
		SetCursor( *cursor );
#else
	ASErr error = kNoErr;
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


