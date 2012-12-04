#ifndef __AI80Undo__
#define __AI80Undo__

/*
 *        Name:	AIUndo.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Undo Suite.
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

#include "AIUndo.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI80UndoSuite			"AI Undo Suite"
#define kAIUndoSuiteVersion3	AIAPI_VERSION(3)
#define kAI80UndoVersion		kAIUndoSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*SetUndoText) ( const char *undoText, const char *redoText );
	AIAPI AIErr (*UndoChanges) ( void );

	AIAPI AIErr (*SetActionPaletteUndo) ( void );
	AIAPI AIErr (*PurgeAllUndos) ( void );

} AI80UndoSuite;


#include "AIHeaderEnd.h"


#endif
