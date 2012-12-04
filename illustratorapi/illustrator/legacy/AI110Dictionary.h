#ifndef __AI110Dict__
#define __AI110Dict__

/*
 *        Name:	AI110Dictionary.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0-11.0 Dictionary Object Suite.
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

#include "AIDictionary.h"


#include "AIHeaderBegin.h"

/** @file AI110Dictionary.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110DictionarySuite					kAIDictionarySuite
#define kAIDictionarySuiteVersion5				AIAPI_VERSION(5)
#define kAI110DictionarySuiteVersion			kAIDictionarySuiteVersion5
#define kAI110DictionaryVersion					kAI110DictionarySuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	A dictionary is a heterogeneous container whose elements are accessed by
	keys.

	The elements of a dictionary are called entries and their type is an
	AIEntryRef. Entries can be of various types. There are simple types such
	as booleans, integers, floats, and strings and complex types such as arrays,
	dictionaries and references to document objects including art objects,
	brushes and styles. This flexibility makes dictionaries a very flexible and
	poweful container. The AIEntry suite provides methods to construct and
	query entries of different types.

	Dictionaries can themselves be stored in other containers such as arrays
	or dictionaries. In particular they can be stored in the dictionaries
	attached to art objects and to the document. When a dictionary is stored in
	one of these places (directly or indirectly) it is read and written as
	a part of the document.
 */
typedef struct AI110DictionarySuite {

	/** create a brand new dictionary. initial reference count is 1. */
	AIAPI AIErr (*CreateDictionary) ( AIDictionaryRef* dictionary );


	/** Dictionaries are reference counted. Call Release once you are done with
		a dictionary to free its memory. */
	AIAPI ASInt32 (*AddRef) ( AIDictionaryRef dictionary );
	AIAPI ASInt32 (*Release) ( AIDictionaryRef dictionary );


	/** Make an exact duplicate of the source dictionary. a deep copy is performed. */
	AIAPI AIErr (*Clone) ( AIDictionaryRef src, AIDictionaryRef* dst );
	/** make a copy of the source dictionary replacing the current contents of the dictionary */
	AIAPI AIErr (*Copy) ( AIDictionaryRef dict, AIDictionaryRef src );


	/** Get the number of entires in the dictionary */
	AIAPI ASInt32 (*Size) ( AIDictionaryRef dict );
	/** Get an iterator for visiting the dictionary entries */
	AIAPI AIErr (*Begin) ( AIDictionaryRef dict, AIDictionaryIterator* iterator );

	/** Create a dictionary key, or find the key if it was already created */
	AIAPI AIDictKey (*Key) ( const char* keyString );
	/** Get the string value for a key */
	AIAPI const char* (*GetKeyString) ( AIDictKey key );

	/** Is there an entry with the given key in the dictionary? */
	AIAPI AIBoolean (*IsKnown) ( AIDictionaryRef dictionary, AIDictKey key );
	/** remove the entry with the given key from the dictionary */
	AIAPI AIErr (*DeleteEntry) ( AIDictionaryRef dictionary, AIDictKey key );
	/** get the type of the entry */
	AIAPI AIErr (*GetEntryType) ( AIDictionaryRef dictionary, AIDictKey key, AIEntryType* entryType );


	/** copy the entry at key1 of dictionary1 to key2 of dictionary2. the dictionaries
		need not be distinct. */
	AIAPI AIErr (*CopyEntry) ( AIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );
	/** move the entry at key1 of dictionary1 to key2 of dictionary2 removing it
		from dictionary1 and inserting it into dictionary2. the dictionaries need not
		be distinct. */
	AIAPI AIErr (*MoveEntry) ( AIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );
	/** swap the entry at key1 of dictionary1 with that at key2 of dictionary2. the
		dictionaries need not be distinct. */
	AIAPI AIErr (*SwapEntries) ( AIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );
	

	/** get an art entry */
	AIAPI AIErr (*GetArtEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArtHandle* art );
	/** create an entry which is a new art object of the specified type */
	AIAPI AIErr (*NewArtEntry) ( AIDictionaryRef dictionary, AIDictKey key, short type );


	/** move the art object from the art tree into the dictionary. */
	AIAPI AIErr (*MoveArtToEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArtHandle art );
	/** move the art object from the dictionary into the art tree. */
	AIAPI AIErr (*MoveEntryToArt) ( AIDictionaryRef dictionary, AIDictKey key, short paintOrder,
			AIArtHandle prep, AIArtHandle* art );
	

	/** copy the art object from the art tree into the dictionary. */
	AIAPI AIErr (*CopyArtToEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArtHandle art );
	/** copy the art object from the dictionary into the art tree. */
	AIAPI AIErr (*CopyEntryToArt) ( AIDictionaryRef dictionary, AIDictKey key, short paintOrder,
			AIArtHandle prep, AIArtHandle* art );
	

	/** set the entry of the dictionary to refer to the topmost group of the layer */
	AIAPI AIErr (*SetEntryToLayer) ( AIDictionaryRef dictionary, AIDictKey key, AILayerHandle layer );
	/** insert a new layer whose group is the dictionary entry which must be a group */
	AIAPI AIErr (*SetLayerToEntry) ( AIDictionaryRef dictionary, AIDictKey key, short paintOrder,
			AILayerHandle prep, AILayerHandle *layer );
			

	/** get the entry with the given key. returns a nil entry if it does not exist. */
	AIAPI AIEntryRef (*Get) ( AIDictionaryRef dictionary, AIDictKey key );
	/** set the entry with the given key. note that entries whose keys are prefixed with
		the character '-' are considered to be temporary entries which are not saved to file. */
	AIAPI AIErr (*Set) ( AIDictionaryRef dictionary, AIDictKey key, AIEntryRef entry );


	// the following are convenience APIs for getting and setting entries of the basic types

	AIAPI AIErr (*GetBooleanEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASBoolean* value );
	AIAPI AIErr (*SetBooleanEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASBoolean value );

	AIAPI AIErr (*GetIntegerEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASInt32* value );
	AIAPI AIErr (*SetIntegerEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASInt32 value );

	AIAPI AIErr (*GetRealEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASReal* value );
	AIAPI AIErr (*SetRealEntry) ( AIDictionaryRef dictionary, AIDictKey key, ASReal value );

	AIAPI AIErr (*GetStringEntry) ( AIDictionaryRef dictionary, AIDictKey key, const char** value );
	AIAPI AIErr (*SetStringEntry) ( AIDictionaryRef dictionary, AIDictKey key, const char* value );

	AIAPI AIErr (*GetBinaryEntry) ( AIDictionaryRef dictionary, AIDictKey key, void* value, ASInt32* size );
	AIAPI AIErr (*SetBinaryEntry) ( AIDictionaryRef dictionary, AIDictKey key, void* value, ASInt32 size );

	AIAPI AIErr (*GetDictEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIDictionaryRef* value );
	AIAPI AIErr (*SetDictEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIDictionaryRef value );

	AIAPI AIErr (*GetArrayEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArrayRef* value );
	AIAPI AIErr (*SetArrayEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArrayRef value );

	/** indicates that a change has been made to the dictionary that "touches" any associated art
		object. that is it affects a user visible property of the object. In particular this
		will cause any styles or plugin groups containing the object to which this dictionary
		is attached to execute. */
	AIAPI AIErr (*TouchArt) ( AIDictionaryRef dictionary );

} AI110DictionarySuite;



#include "AIHeaderEnd.h"


#endif
