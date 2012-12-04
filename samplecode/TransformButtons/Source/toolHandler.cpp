//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/toolHandler.cpp $
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

	AIErr error = kNoErr;
	AIAddToolData toolData;
	AIToolHandle theTool;

	toolData.title = "My Tool";
	toolData.tooltip = "My Tool";

	toolData.icon = sADMIcon->GetFromResource (  message->d.self, kMyToolIcon, kToolIcons );
	if ( ( sADMIcon->GetType( toolData.icon ) ) == kUnknown  )
		return kNoIconErr;

	// this tells you what kind of icon it returned
	// iconType = sADMIcon->GetType( toolData.icon );

	toolData.sameGroupAs = kNoTool;

	error = sTool->GetToolNumberFromName(kScrollTool, &toolData.sameToolsetAs);
	if (error) goto error;

	error = sTool->AddTool( message->d.self, "My tool", &toolData,
						kToolWantsToTrackCursorOption, &theTool );

error:
	return error;

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
	
	g->endPoint = message->cursor;

	if (error)
		goto error;
	
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





static void SetPlatformCursor(SPPluginRef pluginRef, int nCursorID)
{
	ASErr error = kNoErr;
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


