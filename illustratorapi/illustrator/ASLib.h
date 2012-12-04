
#ifndef _ASLIB_H_
#define _ASLIB_H_

/*
 *        Name:	ASTypes.h
 *   $Revision: 7 $
 *      Author:
 *        Date:	10/8/96
 *     Purpose:	Adobe Standard Functions (from stdio, stlib, etc.).
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

/*
 * Includes
 */

#include <stdlib.h>

#include "ASTypes.h"

#include "AIHeaderBegin.h"

/*
 * Constants
 */

#define kASLibSuite				"AS Lib Suite"
#define kASLibSuiteVersion		1
#define kASLibVersion			kASLibSuiteVersion
/** @ingroup Suites
	This suite provides cover functions for standard C library
	string utilities. For additional details, see ANSI C documentation.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kASLibSuite and \c #kASLibVersion.
	*/
typedef struct
{
	// functions from stdio.h
	/** Writes a sequence of arguments to a character buffer, applying
		format instructions.
			@param buffer [in, out] A buffer in which to store the result string.
			@param format A string containing text and format tags, which are replaced
				with text in the succeeding arguments.
				For details of format instructions, see ANSI C documentation.
			@param argument(s) One or more strings of text containing substitution text.
			@return The number of characters written to the buffer, or a negative number on error.
		*/
	ASCAPI int    (*sprintf) (char *, const char *, ...);

	// functions from stdlib.h

	// functions from string.h

	/** Finds a character in a string.
			@param string The null-terminated string to search.
			@param c The character to find.
			@return A pointer to the first occurrence of the character in the string,
				or \c NULL if the character is not found.
		*/
	ASAPI char * (*strchr)  (const char *, int);
	/** Copies bytes from one buffer to another.
			@param dest The destination buffer.
			@param src The source buffer.
			@param num The number of bytes to copy.
			@return The destination buffer.
		*/
	ASAPI void * (*memcpy)  (void *, const void *, size_t);
	/** Compares two buffers, considering each byte as an \c unsigned \c char.
			@param b1 The first buffer.
			@param b2 The second buffer.
			@param num The number of bytes to compare.
			@return 0 if the buffers are the same,
				<br>negative if \c b1 is less than \c b2,
				<br>positive if \c b1 is greater than \c b2
		*/
	ASAPI int    (*memcmp)  (const void *, const void *, size_t);
	/** Fills a buffer with a character.
			@param buffer The buffer.
			@param char The character.
			@param num The number of bytes to copy.
			@return The buffer.
		*/
	ASAPI void * (*memset)  (void *, int, size_t);
	/** Moves bytes from one buffer to another. This copies correctly even if the buffers overlap.
			@param dest The destination buffer.
			@param src The source buffer.
			@param num The number of bytes to copy.
			@return The destination buffer.
		*/
	ASAPI void * (*memmove) (void *, const void *, size_t);
	/** Copies a string.
			@param s1 The destination string, which must be long enough
				to contain the source string.
			@param s2 The null-terminated source string.
			@return The destination string.
		*/
	ASAPI char * (*strcpy)  (char *, const char *);
	/** Appends one string to another.
			@param s1 The destination string, null-terminated with enough
				space to contain both strings.
			@param s2 The null-terminated string to append.
			@return The destination string.
		*/
	ASAPI char * (*strcat)  (char *, const char *);
	/** Compares two strings. Compares each character until one differs,
		or until the end of the string is reached.
			@param s1 The first null-terminated string.
			@param s2 The second null-terminated string.
			@return 0 if the strings are the same,
				<br>negative if \c s1 is less than \c s2,
				<br>positive if \c s1 is greater than \c s2
		*/
	ASAPI int    (*strcmp)  (const char *, const char *);
	/** Retrieves the number of characters in a string.
			@param str The null-terminated string.
			@return The number of characters before the null termination character.
		*/
	ASAPI size_t (*strlen)  (const char *);
	/** Appends a substring of one string to another.
 		The terminating null character in \c dst is overwritten by the
 		first character of \c src. The resulting string includes a
 		null-character at the end.
 		If the terminating null-character appears in \c src
		before \c num characters have been appended,
		the function appends the null character to \c dst and ends.
			@param dst The destination string, null-terminated with enough
				space to contain the original characters and the number
				of characters to append.
			@param src The null-terminated string containing characters to append.
			@param num The maximum number of characters to append.
			@return The destination string.
		*/
	ASAPI char * (*strncat) (char *, const char *, size_t);
	/** Compares some characters of two strings. Compares each character until one differs,
		or until the number of characters is reached.
			@param s1 The first null-terminated string.
			@param s2 The second null-terminated string.
			@param num The maximum number of characters to compare.
			@return 0 if the strings are the same,
				<br>negative if \c s1 is less than \c s2,
				<br>positive if \c s1 is greater than \c s2
		*/
	ASAPI int    (*strncmp) (const char *, const char *, size_t);
	/** Copies characters from one string to another.
		Copies the first \c num characters of \c src to \c dst.
		No null-character is implicitly appended to \c dst after copying,
		so \c dst may not be null-terminated if no null characters are copied from \c src.
 		If \c num is greater than the length of \c src, \c dst is padded with zeros until \c num.
			@param dst The destination string, with enough space to contain \c num characters.
			@param src The null-terminated string containing characters to copy.
			@param num The number of characters to copy.
			@return The destination string.
		*/
	ASAPI char * (*strncpy) (char *, const char *, size_t);
	/** Finds last occurrence of a character in a string.
		The null-terminating character is included as part
		of the string and can also be searched.
  			@param str The string.
			@param c The character.
			@return A pointer to the last occurrence of the character,
				or \c NULL if the character is not found.
 	  */
	ASAPI char * (*strrchr) (const char *, int);
	/** Finds a substring. The search does not include terminating null-characters.
			@param str1	The null-terminated string to search.
			@param str2	The null terminated string to look for.
			@return	A pointer to the first occurrence of \c str2 in \c str1,
				or \c NULL if it is not found.
		*/
	ASAPI char * (*strstr)  (const char *, const char *);

	// functions that "should" be in one of the above (:-)

	/** Substitutes characters in a string.	Finds the first location of the
		search string in the working string, and substitutes a replacement string.
			@param pszStr The null-terminated string in which to search and replace.
			@param iMaxLen The maximum size that the string can grow to
				(the size of the \c pszStr buffer).
			@param pszSearch The null-terminated string to replace.
			@param pszReplace The null-terminated string to substitute.
			@return	A pointer to the first replaced character in \c pszStr,
				or \c NULL if \c pszSearch is not found or if there is not enough
				room in \c pszStr to make the replacement.
		*/
	ASAPI char * (*strsubst)(char *pszStr, int iMaxLen, const char *pszSearch, const char *pszReplace);

} ASLibSuite;

#include "AIHeaderEnd.h"

#endif // _ASLIB_H_

