#ifndef __AI90Entry__
#define __AI90Entry__

/*
 *        Name:	AI90Dictionary.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Dictionary Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
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

#include "AIEntry.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90EntrySuite							"AI Entry Suite"
#define kAIEntrySuiteVersion1					AIAPI_VERSION(1)
#define kAI90EntrySuiteVersion					kAIEntrySuiteVersion1
#define kAI90EntryVersion						kAI90EntrySuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/*

Some notes on use of entries:

The ToSomeType methods have the side effect of decrementing the reference
count of the entry they are passed. Therefore to get the value of an entry
in a container such as a dictionary it is possible to write:

 	ASBoolean value;
	result = sAIEntry->ToBoolean(sAIDictionary->Get(dict, "MyKey"), &value);

The Set methods of the various container types also have the side effect
of decrementing the entry's reference count. Hence a value may be set in a
container such as a dictionary via code like:

	result = sAIDictionary->Set(dict, "MyKey", sAIEntry->FromReal(15));

GetType does not consume its parameter so this can be used to determine the
type of an entry and act accordingly.

*/

typedef struct {

	// reference count maintenance.
	AIAPI ASInt32 (*AddRef) ( AIEntryRef entry );
	AIAPI ASInt32 (*Release) ( AIEntryRef entry );


	// get the type of the entry
	AIAPI AIEntryType (*GetType) ( AIEntryRef entry );


	// the various entry types
	
	AIAPI AIErr (*ToBoolean) ( AIEntryRef entry, ASBoolean* value );
	AIAPI AIEntryRef (*FromBoolean) ( ASBoolean value );

	AIAPI AIErr (*ToInteger) ( AIEntryRef entry, ASInt32* value );
	AIAPI AIEntryRef (*FromInteger) ( ASInt32 value );

	AIAPI AIErr (*ToReal) ( AIEntryRef entry, ASReal* value );
	AIAPI AIEntryRef (*FromReal) ( ASReal value );

	AIAPI AIErr (*ToRealPoint) ( AIEntryRef entry, AIRealPoint* value );
	AIAPI AIEntryRef (*FromRealPoint) ( const AIRealPoint *value );

	AIAPI AIErr (*ToRealMatrix) ( AIEntryRef entry, AIRealMatrix* value );
	AIAPI AIEntryRef (*FromRealMatrix) ( const AIRealMatrix *value );

	AIAPI AIErr (*ToString) ( AIEntryRef entry, const char** value );
	AIAPI AIEntryRef (*FromString) ( const char* value );

	AIAPI AIErr (*ToDict) ( AIEntryRef entry, AIDictionaryRef* value );
	AIAPI AIEntryRef (*FromDict) ( AIDictionaryRef value );

	AIAPI AIErr (*ToArt) ( AIEntryRef entry, AIArtHandle* art );

	AIAPI AIErr (*ToArray) ( AIEntryRef entry, AIArrayRef* value );
	AIAPI AIEntryRef (*FromArray) ( AIArrayRef value );

	AIAPI AIErr (*ToBinary) ( AIEntryRef entry, void* value, ASInt32* size );
	AIAPI AIEntryRef (*FromBinary) ( void* value, ASInt32 size );

	AIAPI AIErr (*ToPattern) ( AIEntryRef entry, AIPatternHandle* value );
	AIAPI AIEntryRef (*FromPattern) ( AIPatternHandle value );

	AIAPI AIErr (*ToBrushPattern) ( AIEntryRef entry, AIPatternHandle* value );
	AIAPI AIEntryRef (*FromBrushPattern) ( AIPatternHandle value );

	AIAPI AIErr (*ToGradient) ( AIEntryRef entry, AIGradientHandle* value );
	AIAPI AIEntryRef (*FromGradient) ( AIGradientHandle value );

	AIAPI AIErr (*ToCustomColor) ( AIEntryRef entry, AICustomColorHandle* value );
	AIAPI AIEntryRef (*FromCustomColor) ( AICustomColorHandle value );

	AIAPI AIErr (*ToPluginObject) ( AIEntryRef entry, AIObjectHandle* value );
	AIAPI AIEntryRef (*FromPluginObject) ( AIObjectHandle value );

	AIAPI AIErr (*ToFillStyle) ( AIEntryRef entry, AIFillStyle *value );
	AIAPI AIEntryRef (*FromFillStyle) ( const AIFillStyle *value );

	AIAPI AIErr (*ToStrokeStyle) ( AIEntryRef entry, AIStrokeStyle *value );
	AIAPI AIEntryRef (*FromStrokeStyle) ( const AIStrokeStyle *value );


} AI90EntrySuite;



#include "AIHeaderEnd.h"


#endif
