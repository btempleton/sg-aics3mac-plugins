
#ifndef __AI120UnicodeString__
#define __AI120UnicodeString__

/*
 *        Name:	AI120UnicodeString.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Unicode String Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
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

#include "AIUnicodeString.h"

#include "AICharacterEncoding.h"
#include "AITypes.h"

#include "AIHeaderBegin.h"

/** @file AI120UnicodeString.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120UnicodeStringSuite			kAIUnicodeStringSuite
#define kAIUnicodeStringSuiteVersion5		AIAPI_VERSION(5)
#define kAI120UnicodeStringVersion			kAIUnicodeStringSuiteVersion5

/*******************************************************************************
 **
 ** Types
 **
 **/

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	Support suite for the ai::UnicodeString class in plug-ins.
*/
typedef struct {

	/* String Creation & Destruction */

	/** Initialize str with the contents of string using at most srcByteLen 
	   bytes of string. encoding must specify the encoding of the data in string.
	   @param str string to be initialized.
	   @param string the data to be used for the initalization.
	   @param srcByteLen the length of the data buffer string in bytes.
	   @param encoding the encoding of the data in string.
	   @return AIErr
    */
	AIAPI AIErr (*Initialize) (ai::UnicodeString& str, const char* string, 
		long srcByteLen, AICharacterEncoding encoding);

	/** Initialize str with the contents of utfs.  utfs must be a valid UTF-16
		encoded string.
		@param str string to be initialized.
		@param utfs pointer to an array UTF-16 code units to initialize 
		str.
		@param srcUTF16Count the number of UTF-16 code units to be taken from utfs.  If npos is 
		passed it is assumed that utfs is 0 terminated.
		@return AIErr
	*/
	AIAPI AIErr (*InitializeUTF16) (ai::UnicodeString& str, const ASUnicode* utfs, ai::UnicodeString::size_type srcUTF16Count);

	/** Initialize str with count ch UTF32 code point "characters".
		@param str string to be initialized.
		@param count number of characters to initialize this string with.
		@param ch the UTF code point to use to initialize the string.
		@return AIErr
	*/
	AIAPI AIErr (*InitializeUTF32Char) (ai::UnicodeString& str, ai::UnicodeString::size_type count, 
		ai::UnicodeString::UTF32TextChar ch);

	/** Contents of str are deleted.  Any pointers to utf_16 buffers derived 
	   from str will be invalid. str is reset to an unitialized state.
	   @param str string to be destroyed.
    */
	AIAPI AIErr (*Destroy) (ai::UnicodeString& str);

	/* Basic operations (a la std::basic_string) */

	/** Append the Unicode string str2 to the Unicode string str.
		@param str string to be appended to.
		@param str2 string to be appened. */
	AIAPI AIErr (*Append) (ai::UnicodeString& str, const ai::UnicodeString& str2);

	/** Append the sub-string of str2 defined by startOffset and count to str.  
		At most count characters will be appended. 
		@param str string to be appened to.
		@param str2 string to be appened.
		@param startOffset the character offset for the 1st character in str2 
		that will appened. 
		@param count the maximum number of characters from str2 that will be 
		appened. */
	AIAPI AIErr (*AppendSubString) (ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Assign the string str2 to this string.
		@param str the string to be assiged to.
		@param str2 the string to be assigned from.
	*/
	AIAPI AIErr (*Assign) (ai::UnicodeString& str, 
		const ai::UnicodeString& str2);

	/** Copy str2 into str.  If str2 is empty or unitialized, str will be truncated.
	    @param str string to be copied into.
	    @param str2 the string to be copied.
    */
	AIAPI AIErr (*Copy) (ai::UnicodeString& str, const ai::UnicodeString& str2);

	/** Get the UTF-32 code point at position.
		@param str is the string to query.
		@param offset is the position to query.
		@param ch is the returned character at position.
		@result an error is returned if position is not a valid offset into 
		the string.
	*/
	AIAPI AIErr (*GetChar) (const ai::UnicodeString& str, 
		ai::UnicodeString::size_type position, 
		ai::UnicodeString::UTF32TextChar& ch);

	/** Clear the contents of str. This is synonymous with erase(0, npos). 
	    Uninitialized strings remain unchanged.
		@param str is the string to be cleared.
	*/
	AIAPI void (*Clear) (ai::UnicodeString& str);

	/** Code point based comparison of strings.  If str and str2 are equal 0 
	    is returned. If str is less than str2 a negative value is returned.
		If str is greater than str2 a positive value is returned.
		Uninitialized strings are equal to other uninitialized strings and 
		empty strings.
		Uninitialized and empty strings are always less than initialized, 
		non-empty strings.
		@param str is the left hand side string.
		@param str2 is the right hand side string.
	*/ 
	AIAPI int (*Compare) (const ai::UnicodeString& str, 
		ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num, 
		const ai::UnicodeString& str2, 
		ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count);

	/** Code point based caseless comparison of strings.  Strings are case folded
		in a locale independent manner prior to comparison.  If str and str2 are equal 0 
	    is returned. If str is less than str2 a negative value is returned.
		If str is greater than str2 a positive value is returned.
		Uninitialized strings are equal to other uninitialized strings and 
		empty strings.
		Uninitialized and empty strings are always less than initialized, 
		non-empty strings.
		@param str is the left hand side string.
		@param str2 is the right hand side string.
	*/ 
	AIAPI int (*CaseCompare) (const ai::UnicodeString& str, 
		ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num, 
		const ai::UnicodeString& str2, 
		ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count);

	/** Normalized code point based comparison of strings.  If str and str2 are equal compareResult 
		is set to 0. If str is less than str2 it is set to a negative value.
		If str is greater than str2 it is set to a positive value.
		Uninitialized strings are equal to other uninitialized strings and 
		empty strings.
		Uninitialized and empty strings are always less than initialized, 
		non-empty strings.
		@param str is the left hand side string.
		@param str2 is the right hand side string.
	*/ 
	AIAPI AIErr (*CanonicalCompare) (const ai::UnicodeString& str, const ai::UnicodeString& str2, int& compareResult);

	/** Normalized caseless code point based comparison of strings.  If str and str2 are equal compareResult 
		is set to 0. If str is less than str2 it is set to a negative value.
		If str is greater than str2 it is set to a positive value.
		Uninitialized strings are equal to other uninitialized strings and 
		empty strings.
		Uninitialized and empty strings are always less than initialized, 
		non-empty strings.
		@param str is the left hand side string.
		@param str2 is the right hand side string.
	*/ 
	AIAPI AIErr (*CanonicalCaseCompare) (const ai::UnicodeString& str, const ai::UnicodeString& str2, int& compareResult);


	///** Normalize the passed string.
	//    @param str the string to be normalized.
	//*/
	//AIAPI AIErr (*Normalize) (ai::UnicodeString& str);

	/** Return the count of the number of UTF-32 (code points) in the string.
		Unitialized strings are of length 0.
		@param string to query.
	*/
	AIAPI ai::UnicodeString::size_type (*Length) (const ai::UnicodeString& str);
	/** Return a bool indicating if the string is empty.  Uninitialized strings 
	    are empty.
		@param str is the string to query. */
	AIAPI AIBool8 (*Empty) (const ai::UnicodeString& str);
	/** Erase at most n full code points from the string starting at offset 
	    the offset position.
		@param str the string to modifiy.
		@param startOffset is the index of the first character to erase.
		@param count is the number of code points to erase.
		@return out of range error is returned if startOffset is not a valid 
		offset into the string.
	*/
	AIAPI AIErr (*Erase) (ai::UnicodeString& str, 
		ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Search the string for the 1st occurance of the UTF32 character (code point) 
	    ch starting the search at startOffset.  
		@param str is the string to search.
		@param ch is the character to search for.
		@param startOffset is the position in str to begin the search.
		@return the character index of the found char. Returns npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindChar) (const ai::UnicodeString& str, 
		ai::UnicodeString::UTF32TextChar ch, 
		ai::UnicodeString::size_type startOffset);

	/** Search the string for the 1st occurance of the entire string str2 starting 
		the search in str at startOffset.  
		@param str the string to search.
		@param str2 the string to search for.
		@param startOffset the position in str to begin the search.
		@return the character index of the start of the found string. Returns npos 
		if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindString) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset);

	/** Search the string for the 1st occurance of a substring of string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search for.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindSubString) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);
	
	AIAPI ai::UnicodeString::size_type (*CaseFindSubString) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** 
		Search the string for the last occurance of the UTF32 character (code point) 
	    ch starting the search at startOffset.  
		@param str is the string to search.
		@param ch is the character to search for.
		@param startOffset is the position in str to begin the search.
		@return the character index of the found char. Returns npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*RFindChar) (const ai::UnicodeString& str, 
		ai::UnicodeString::UTF32TextChar ch, 
		ai::UnicodeString::size_type startOffset);

	/** 
		Search the string for the last occurance of the entire string str2 starting 
		the search in str at startOffset.  
		@param str the string to search.
		@param str2 the string to search for.
		@param startOffset the position in str to begin the search.
		@return the character index of the start of the found string. Returns npos 
		if the string is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*RFindString) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset);

	/** 
		Search the string for the last occurance of a substring of string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search for.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the string is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*RFindSubString) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Search the string for the 1st occurance of a character from string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search from.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindFirstOf) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Search the string for the 1st occurance of a character does not appear in string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search from.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindFirstNotOf) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Search the string for the last character in str that appears in string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search from.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindLastOf) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Search the string for the last character that does not appear in  string str2 
	    starting the search in str at startOffset and comparing no more than 
		count characters from str2.
		@param str the string to search.
		@param str2 the string to search from.
		@param startOffset the position in str to begin the search.
		@param count the number of characters from str2 to compare against.
		@return the character index of the start of the found string. Returns 
		npos if the character is not found.
	*/
	AIAPI ai::UnicodeString::size_type (*FindLastNotOf) (const ai::UnicodeString& str, 
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset, 
		ai::UnicodeString::size_type count);

	/** Attempts to resize the string to hold count characters.  If the string is longer than 
		count it is truncated to count.  If the string is shorter than count it is extended 
		to hold count characters padding the end of the string with ch.
		Note: use of resize will not guarantee that 
		@param str the string to resize.
		@param count the desired length of the string.
		@param ch the character to use to pad the string.
	*/
	AIAPI AIErr (*Resize) (ai::UnicodeString& str, ai::UnicodeString::size_type count, ai::UnicodeString::UTF32TextChar ch);

	/** Create a substring of str starting at offset and containing no more than 
	    count characters. If subString is unitialized, it will be initialzed 
		iff str is initialized and has a length > 0.
		@param subString the string to receive the substring.
		@param str the string to obtain the substring from.
		@param offset the start character position in str.
		@param count the maximum number of characters to place in the new substring.
	*/
	AIAPI AIErr (*SubStr) (ai::UnicodeString& subString, 
		const ai::UnicodeString& str, 
		ai::UnicodeString::size_type offset, ai::UnicodeString::size_type count);

	/** swap the contents of str2 with the contents of str */
	AIAPI AIErr (*SwapStr) (ai::UnicodeString& str, ai::UnicodeString& str2);

	/* non-std::string based functionality */

	//AIAPI int CaseCompare(const ai::UnicodeString& str,
	//	ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num, 
	//	const ai::UnicodeString& str2, 
	//	ai::UnicodeString::size_type startOffset, 
	//	ai::UnicodeString::size_type count);
	//AIAPI void FoldCase(ai::UnicodeString& str);
	/** Check if the string contains surrogate pairs.
		@param str string to check.
		@return true if it contains at least one surrogate pair. 
	*/
	AIAPI AIBool8 (*HasSurrogates) (const ai::UnicodeString& str);

	/** Returns a read-only pointer to a buffer containing UTF-16 
		encoded buffer in platform byte order.  Returned size_type is the 
		size of the buffer in UTF-16 code units.  The returned buffer pointer may be 
		0 if this string is empty or uninitialized. 
		@param str string to get the buffer for.
		@param buffer the pointer to the buffer.
		@return size_type the length of buffer in UTF-16 code units.
		The returned buffer might not be 0 terminated. 
	*/
	AIAPI ai::UnicodeString::size_type (*UTF_16) (const ai::UnicodeString& str, 
		const ai::UnicodeString::UTF16Char*& buffer);

	/** Obtain the contents of the passed string in the encoding specified.
		@param str the string whose contents are to be retrieved.
		@param encoding the desired encoding of the contents.
		@param buffer a buffer object to which the contents will be written; it ]
		does not need to be initialized prior to the call.
		@param bufferByteCount is the number of bytes in the buffer that contain the 
		requested data.  Note: the buffer may be larger than the returned bufferByteCount.
	*/
	AIAPI AIErr (*GetAs) (const ai::UnicodeString& str, AICharacterEncoding encoding,
		ai::AutoBuffer<char>& buffer, ai::UnicodeString::size_type& bufferByteCount);

	// THIS SHOULD BE MOVED UP LATER
	/** Initialize str froma a ZString key's referred string.
		@param str string to be initialized.
		@param zStringKey key to the ZString to use as the initializer.
		@return AIErr
	*/
	AIAPI AIErr (*InitializeZString) (ai::UnicodeString& str, ZRef zStringKey);

} AI120UnicodeStringSuite;


#include "AIHeaderEnd.h"



#endif // __AI120UnicodeString__
