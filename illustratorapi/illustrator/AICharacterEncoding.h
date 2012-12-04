#ifndef __AICharacterEncoding__
#define __AICharacterEncoding__

/*
 *        Name:	AICharacterEncoding.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Character Encoding Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2003-2007 Adobe Systems Incorporated.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AICharacterEncoding.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAICharacterEncodingSuite					"AI Character Encoding Suite"
#define kAICharacterEncodingSuiteVersion3			AIAPI_VERSION(3)
#define kAICharacterEncodingSuiteVersion			kAICharacterEncodingSuiteVersion3
#define kAICharacterEncodingVersion					kAICharacterEncodingSuiteVersion


/** Constant values for the various character encodings supported by this suite.
	The character sets for the specific language encodings (Roman, Japanese, and so on)
	are	platform specific. The character sets for the specific East Asian encodings
	(GB, JISX0213, and so on) are standard.
	See \c #AICharacterEncodingSuite::ConvertBuffer().*/
typedef enum {

	/** The character set currently supported by the system. */
	kAIPlatformCharacterEncoding = 0,
	/** UTF8 encoding */
	kAIUTF8CharacterEncoding,
	/** UTF16 encoding (formerly \c kAIUCS2CharacterEncoding) */
	kAIUTF16CharacterEncoding,
	// The encodings below are new in Illustrator 11.0
	/** Roman */
	kAIRomanCharacterEncoding = 0x10,
	/** Japanese, encoded using Shift-JIS  */
	kAIJapaneseCharacterEncoding,
 	/** Traditional Chinese */
	kAITraditionalChineseCharacterEncoding,
	/** Simplified Chinese */
	kAISimplifiedChineseCharacterEncoding,
	/** Korean */
	kAIKoreanCharacterEncoding,
	/** Arabic */
	kAIArabicCharacterEncoding,
	/** Hebrew */
	kAIHebrewCharacterEncoding,
	/** Greek */
	kAIGreekCharacterEncoding,
	/** Cyrillic */
	kAICyrillicCharacterEncoding,
	/** Central European Roman (also known as Eastern European Roman) */
	kAICentralEuroRomanCharacterEncoding,
	/** Turkish */
	kAITurkishCharacterEncoding,
	/** Baltic */
	kAIBalticCharacterEncoding,

	// Platform-independent encodings - East Asian character standards
	/** Japanese, JISX0213:2000 + JISX0208:1997, using Shift-JIS */
	kAIJapaneseX0213CharacterEncoding = 0x00000100,
	 /** Chinese, GB 18030-2000 */
	kAIChineseGB18030CharacterEncoding,
	 /** Chinese, HKSCS */
	kAIChineseHKSCSCharacterEncoding,

	kAIDummyCharacterEncoding = 0xFFFFFFFF

} AICharacterEncoding;


/** Constant values for ways to encode characters in the JIS character set.
	 See \c #AICharacterEncodingSuite::ConvertJapaneseChar(). */
typedef enum {
	/**  Shift-JIS */
	kAISJISEncoding,
	/** JISX0208:1997 */
	kAIJISEncoding,
	/** Kuten */
	kAIKutenEncoding,

	kAIDummyJapaneseEncoding = 0xFFFFFFFF

} AIJapaneseEncoding;

/* Error codes */

/** @ingroup Errors
	Returned from \c #AICharacterEncodingSuite::ConvertBuffer()
	when the conversion requires more bytes than specified in
	\c dstBytes. */
#define kDstBufferTooShortErr 'Shrt'

/** Returned from \c #AICharacterEncodingSuite::ConvertBuffer()
	when \c srcBuffer contains bytes that are invalid in the
	given \c srcEncoding. */
#define kSrcHasInvalidBytesErr 'InvB'

/** Returned from \c #AICharacterEncodingSuite::ConvertBuffer()
	when \c srcBuffer contains bytes that cannot be mapped to
	the destination encodings. */
#define kSrcCantMapBytesErr         '!Map'

/** Returned from \c #AICharacterEncodingSuite::ConvertBuffer()
	when \c srcBuffer contains bytes that cannot be mapped exactly. */
#define kSrcCantMapBytesExactlyErr  '~Map'

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The character encoding suite provides facilities for translating between different
	encodings of textual data. See also \c ai::EncodedString, which provides a C++ class
	for translating between platform encoding, UTF8, and UTF16.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICharacterEncodingSuite and \c #kAICharacterEncodingVersion.
*/

typedef struct AICharacterEncodingSuite {

	/** Converts text from one encoding to another.

		Unicode 3 values are always used as the intermediate representation
		during the translation between the source and the destination encodings.
		Byte order of UTF16 Unicode values are dictated by the current platform
		(big-endian in Mac OS, little-endian in Windows).

		If some characters do not map exactly, a loose or fallback mapping is used.
		If some characters cannot be mapped, the source characters are dropped from
		the destination buffer.
			@param srcBuffer The buffer containing the text.
			@param srcBytes The number of bytes in \c srcBuffer.
			@param srcEncoding The encoding used by the text in \c srcBuffer.
			@param dstBuffer [out] A buffer in which to return the converted text.
			@param dstBytes The number of bytes in \c dstBuffer.
			@param dstEncoding The encoding to which to convert the text.
			@param dstLength [out] A buffer in which to return the number of bytes
				written to \c dstBuffer.
			@param errIfCantMap When true, return error codes when characters do not
      			map exactly.
		*/
	AIAPI AIErr (*ConvertBuffer) (
			const void* srcBuffer, long srcBytes, AICharacterEncoding srcEncoding,
			void* dstBuffer, long dstBytes, AICharacterEncoding dstEncoding,
			long* dstLength, AIBoolean errIfCantMap);

	/* New in Illustrator 11.0 */

	/** Converts a Japanese character  from one Japanese encoding to another.
			@param srcEncoding The encoding currently used for \c ch.
			@param dstEncoding The encoding to which to convert the character.
			@param ch [in, out] A pointer to the Japanese character, represented as an unsigned short.
			@return The error \c #kBadParameterErr if \c ch is not within a valid range for \c srcEncoding.
			<br> The error \c #kBadParameterErr if \c ch is a single-byte Shift-JIS character
			(used to represent ASCII and half-width katakana characters). Such characters cannot be
			converted to JIS X 0208 or Kuten.
		 */
	AIAPI AIErr (*ConvertJapaneseChar) (
			AIJapaneseEncoding srcEncoding, AIJapaneseEncoding dstEncoding, unsigned short* ch );

	// The following two functions provide limited cross-platform support for classifying
	// Unicode characters.

	/** Reports whether a given Unicode (UTF16) character is categorized as a punctuation
		character. Only supports characters in the BMP (Basic Multilingual Plane).
		(Note that this function returns a boolean value, not an error code)
			@param inChar The character.
			@return True if the character is punctuation.
		*/
	AIAPI AIBool8 (*IsPunct)(ASUnicode inChar);

	/** Reports whether a given Unicode (UTF16) character is categorized as a spacing
		character. Only supports characters in the BMP (Basic Multilingual Plane).
		(Note that this function returns a boolean value, not an error code)
			@param inChar The character.
			@return True if the character is spacing.
		*/
	AIAPI AIBool8 (*IsSpace)(ASUnicode inChar);

} AICharacterEncodingSuite;


#include "AIHeaderEnd.h"


#endif
