#ifndef __AI110Entry__
#define __AI110Entry__

/*
 *        Name:	AI110Entry.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 11.0 Dictionary Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

/** @file AI110Entry.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110EntrySuite							"AI Entry Suite"
#define kAIEntrySuiteVersion2					AIAPI_VERSION(2)
#define kAI110EntrySuiteVersion					kAIEntrySuiteVersion2
#define kAI110EntryVersion							kAI110EntrySuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	The AIEntry suite contains methods for constructing and inspecting the
	entries stored within heterogeneous containers such as dictionaries and
	arrays.
	
	Some notes on use of entries:

	Entries, like the dictionaries and arrays that contain them, are reference
	counted. This means that when a client is given an entry the count on
	the entry is incremented before it is returned. It is then the clients
	responsibility to decrement the count else leaks will occur. For entries
	these rules could result in some rather unnatural and lengthy code. To
	avoid this the "ToSomeType" methods and the "Set" methods have side
	effects on the reference counts of the entries that are described below.

	The "ToSomeType" methods have the side effect of decrementing the reference
	count of the entry they are passed. Therefore to get the value of an entry
	in a container such as a dictionary it is possible to write:

 		ASBoolean value;
		result = sAIEntry->ToBoolean(sAIDictionary->Get(dict, "MyKey"), &value);

	The "Set" methods of the various container types also have the side effect
	of decrementing the entry's reference count. Hence a value may be set in a
	container such as a dictionary via code like:

		result = sAIDictionary->Set(dict, "MyKey", sAIEntry->FromReal(15));

	"GetType" does not consume its parameter so this can be used to determine the
	type of an entry and act accordingly.
*/

typedef struct {

	/** reference count maintenance. increments the count of references to the entry. */
	AIAPI ASInt32 (*AddRef) ( AIEntryRef entry );
	/** reference count maintenance. decrements the count of references to the entry. */
	AIAPI ASInt32 (*Release) ( AIEntryRef entry );


	/** get the type of the entry */
	AIAPI AIEntryType (*GetType) ( AIEntryRef entry );


	// the various entry types

	/** Get the value of the entry assuming it is boolean. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToBoolean) ( AIEntryRef entry, ASBoolean* value );
	/** Construct an entry from a boolean value. */
	AIAPI AIEntryRef (*FromBoolean) ( ASBoolean value );

	/** Get the value of the entry assuming it is an integer. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToInteger) ( AIEntryRef entry, ASInt32* value );
	/** Construct an entry from an integer value. */
	AIAPI AIEntryRef (*FromInteger) ( ASInt32 value );

	/** Get the value of the entry assuming it is a real. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToReal) ( AIEntryRef entry, ASReal* value );
	/** Construct an entry from a real value. */
	AIAPI AIEntryRef (*FromReal) ( ASReal value );

	/** Get the value of the entry assuming it is a point. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToRealPoint) ( AIEntryRef entry, AIRealPoint* value );
	/** Construct an entry from a point value. */
	AIAPI AIEntryRef (*FromRealPoint) ( const AIRealPoint *value );

	/** Get the value of the entry assuming it is a matrix. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToRealMatrix) ( AIEntryRef entry, AIRealMatrix* value );
	/** Construct an entry from a matrix value. */
	AIAPI AIEntryRef (*FromRealMatrix) ( const AIRealMatrix *value );

	/** Get the value of the entry assuming it is a string. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToString) ( AIEntryRef entry, const char** value );
	/** Construct an entry from a string value. */
	AIAPI AIEntryRef (*FromString) ( const char* value );

	/** Get the value of the entry assuming it is a dictionary. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToDict) ( AIEntryRef entry, AIDictionaryRef* value );
	/** Construct an entry from a dictionary value. */
	AIAPI AIEntryRef (*FromDict) ( AIDictionaryRef value );

	/** Get the value of the entry assuming it is an art object. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToArt) ( AIEntryRef entry, AIArtHandle* art );

	/** Get the value of the entry assuming it is an array. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToArray) ( AIEntryRef entry, AIArrayRef* value );
	/** Construct an entry from an array value. */
	AIAPI AIEntryRef (*FromArray) ( AIArrayRef value );

	/** Get the value of the entry assuming it is binary data. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToBinary) ( AIEntryRef entry, void* value, ASInt32* size );
	/** Construct an entry from a binary value. */
	AIAPI AIEntryRef (*FromBinary) ( void* value, ASInt32 size );

	/** Get the value of the entry assuming it is a pattern. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToPattern) ( AIEntryRef entry, AIPatternHandle* value );
	/** Construct an entry from a pattern value. */
	AIAPI AIEntryRef (*FromPattern) ( AIPatternHandle value );

	/** Get the value of the entry assuming it is a brush pattern. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToBrushPattern) ( AIEntryRef entry, AIPatternHandle* value );
	/** Construct an entry from a brush pattern value. */
	AIAPI AIEntryRef (*FromBrushPattern) ( AIPatternHandle value );

	/** Get the value of the entry assuming it is a gradient. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToGradient) ( AIEntryRef entry, AIGradientHandle* value );
	/** Construct an entry from a gradient value. */
	AIAPI AIEntryRef (*FromGradient) ( AIGradientHandle value );

	/** Get the value of the entry assuming it is a custom color. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToCustomColor) ( AIEntryRef entry, AICustomColorHandle* value );
	/** Construct an entry from a custom color value. */
	AIAPI AIEntryRef (*FromCustomColor) ( AICustomColorHandle value );

	/** Get the value of the entry assuming it is a plugin global object. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToPluginObject) ( AIEntryRef entry, AIObjectHandle* value );
	/** Construct an entry from a plugin global object value. */
	AIAPI AIEntryRef (*FromPluginObject) ( AIObjectHandle value );

	/** Get the value of the entry assuming it is a fill style. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToFillStyle) ( AIEntryRef entry, AIFillStyle *value );
	/** Construct an entry from a fill style value. */
	AIAPI AIEntryRef (*FromFillStyle) ( const AIFillStyle *value );

	/** Get the value of the entry assuming it is a stroke style. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToStrokeStyle) ( AIEntryRef entry, AIStrokeStyle *value );
	/** Construct an entry from a stroke style value. */
	AIAPI AIEntryRef (*FromStrokeStyle) ( const AIStrokeStyle *value );


	/* New in Illustrator 10.0 */

	/** Get the value of the entry assuming it is an UID. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToUID) ( AIEntryRef entry, AIUIDRef* value );
	/** Construct an entry from an UID value. */
	AIAPI AIEntryRef (*FromUID) ( AIUIDRef value );

	/** Get the value of the entry assuming it is an UIDREF. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToUIDREF) ( AIEntryRef entry, AIUIDREFRef* value );
	/** Construct an entry from an UIDREF value. */
	AIAPI AIEntryRef (*FromUIDREF) ( AIUIDREFRef value );

	/** Get the value of the entry assuming it is an XML node. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToXMLNode) ( AIEntryRef entry, AIXMLNodeRef* value );
	/** Construct an entry from an XML node value. */
	AIAPI AIEntryRef (*FromXMLNode) ( AIXMLNodeRef value );

	/** Get the value of the entry assuming it is a SVG filter. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToSVGFilterHandle) ( AIEntryRef entry, AISVGFilterHandle* value );
	/** Construct an entry from a SVG filter value. */
	AIAPI AIEntryRef (*FromSVGFilterHandle) ( AISVGFilterHandle value );

	/** Get the value of the entry assuming it is a symbol pattern. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToSymbolPattern) ( AIEntryRef entry, AIPatternHandle* value );
	/** Construct an entry from a symbol pattern value. */
	AIAPI AIEntryRef (*FromSymbolPattern) ( AIPatternHandle value );

	// type conversion routines.
	// type conversion rules same as that of std::basic_[io]stream rules.

	/**  convert entry to boolean. valid for "1" or "0", or "true" or "false */
	AIAPI AIErr (*AsBoolean) ( AIEntryRef entry, ASBoolean* value );
	/** convert entry to an integer if possible. */
	AIAPI AIErr (*AsInteger) ( AIEntryRef entry, ASInt32* value );
	/** convert entry to a real if possible. */
	AIAPI AIErr (*AsReal) ( AIEntryRef entry, ASReal* value );
	/** convert entry to a string if possible. */
	AIAPI AIErr (*AsString) ( AIEntryRef entry, const char** value );
	/** convert entry to a UID reference it must be of the form: "id('foo')", where "foo" is the uid. */
	AIAPI AIErr (*AsUIDREF) ( AIEntryRef entry, AIUIDREFRef* value );

	/** Get the value of the entry assuming it is an art style. Returns an error
		if the value is not. Note that this automatically decrements
		the reference count. */
	AIAPI AIErr (*ToArtStyle) ( AIEntryRef entry, AIArtStyleHandle* value );
	/** Construct an entry from an art style value. */
	AIAPI AIEntryRef (*FromArtStyle) ( AIArtStyleHandle value );

} AI110EntrySuite;


#include "AIHeaderEnd.h"


#endif
