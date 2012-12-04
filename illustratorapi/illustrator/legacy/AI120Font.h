/*
 *        Name:	AI120Font.h
 *   $Revision: 1 $
 *      Author:	Adam Lane
 *        Date:	7/10/2002
 *     Purpose:	Adobe Illustrator Font Suite.
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

#ifndef __AI120Font__
#define __AI120Font__

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIFont.h"

#ifdef __cplusplus
using ATE::FontRef;
#endif

#include "AIHeaderBegin.h"

/** @file AI120Font.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI120FontSuite				kAIFontSuite
#define kAIFontSuiteVersion2		AIAPI_VERSION(2)
#define kAI120FontSuiteVersion		kAIFontSuiteVersion2
#define kAI120FontVersion			kAIFontSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** Illustrator maintains information about the set of fonts that are
	available for use in documents. This includes fonts from the operating
	system, those installed with Illustrator and substitute fonts for
	missing fonts in open documents. The set of fonts may change during
	application execution as a result of font activation, deletion and
	opening and closing documents.

	Fonts have names. There are several different types of names that
	can be queried via the APIs:

	- PostScript name. This is a unique, ASCII name for a font. It can
		be stored in files to identify a font. For multiple master
		instances it includes the specific design axis values.
	- Illustrator PostScript name. This is the PostScript name with
		a suffix identifying the encoding. It can also be stored in
		a file to identify a font.
	- User names. These are names intended for presentation to the
		user, They may be in ASCII or a localized encoding. There are a
		number of different names that can be presented to a user. For
		example a full name describing the font and the font family name.
*/
struct AI120FontSuite {
	/** Returns the total number of fonts. Note that "Times Roman Regular" and
		"Times Roman Italic" are counted as distinct fonts. */
	AIAPI AIErr (*CountFonts)( long *count );
	/** Returns the font at the specified index. Font indices can change as
		fonts are added and removed. */
	AIAPI AIErr (*IndexFontList)( long index, AIFontKey *fontKey );
	/** Returns the total number of font families. For this API italic, bold etc
		variants are counted as a single family. */
	AIAPI AIErr (*CountTypefaces)( long *count );
	/** Returns the family at the specified index. Family indices can change as
		fonts are added and removed. */
	AIAPI AIErr (*IndexTypefaceList)( long index, AITypefaceKey *typeFaceKey );
	/** Given a font family returns the number of font variants (e.g bold, italic)
		within that family. */
	AIAPI AIErr (*CountTypefaceStyles)( AITypefaceKey typeface, long *count );
	/** Returns the font variant within the family with the given index. */
	AIAPI AIErr (*IndexTypefaceStyleList)( AITypefaceKey typeface, long index, AIFontKey *fontKey );
	/** Given the key for a font (e.g "Times Roman Bold") returns the font
		family and index of the variant within the family. */
	AIAPI AIErr (*TypefaceAndStyleFromFontKey)(AIFontKey theKey, AITypefaceKey *typefaceResult, short *styleResult);

	/** Attempts to find the font matching the given parameters including a
		font name (e.g "Times-Roman"), the font technology, and the language for which
		the font was designed. If substituteFlag is true then a substitute font will be
		returned if not found. The font name can either be a PostScript font name
		or an Illustrator PostScript font name. In the latter case the encoding
		suffix is removed before searching. */
	AIAPI AIErr (*FindFont)( char *postscriptName, enum AIFontTechnology fontTechnology, AIFaceScript script,
			AIBoolean substituteFlag, AIFontKey *result);
	/** Returns the Illustrator font given a Macintosh identifier for a system font. */
	AIAPI AIErr (*FindMacFont)(short familyID, short styleCode, AIFontKey *result);
	/** Unimplemented. */
	AIAPI AIErr (*FindWinFont)(AILOGFONTA *logFont, AIFontKey *result);
	/** Returns the Macintosh system font for an Illustrator font. Returns an error
		on Windows. On the Mac if the font is not a system font it returns default
		values. */
	AIAPI AIErr (*GetMacFontFamilyAndStyle)(AIFontKey fontKey, short *familyResult, short *styleResult);
	/** Returns the system name for the font if it is a system font. On windows
		this is the lfFaceName member of the LOGFONT. */
	AIAPI AIErr (*GetSystemFontName)(AIFontKey fontKey, char *result, short maxName);
	/** This method works only on fauxed single-byte horizontal fonts. */
	AIAPI AIErr (*SetCharWidths)(AIFontKey fontKey, AIReal *charWidths);

	// Accessing various attributes of a font...except the name...that's different
	
	AIAPI AIErr (*GetFontInfo)( AIFontKey font, struct AIFontStyle *result);
	AIAPI AIErr (*GetFontMetrics)( AIFontKey font, struct AIFontMetrics *result);
	/** Get the dimensions of the glyph for a 1 point font. */
	AIAPI AIErr (*GetGlyphDimensions)( AIFontKey font, AIGlyphID glyphID, enum AIMetricOrientation orientation,
			AIReal *hResult, AIReal *vResult);
	/** Get the dimensions of the UTF8 encoded character for a 1 point font. */
	AIAPI AIErr (*GetCharDimensions)( AIFontKey font, char *charPtr, enum AIMetricOrientation orientation,
			AIReal *hResult, AIReal *vResult);
	/** Returns what will be used as the default font for the given writing script. */
	AIAPI AIErr (*GetDefaultFont)( AIFaceScript script, AIFontKey *result);

	// Various ways to get the name of a font

	/** Returns the (non-Illustrator) PostScript name for a font. Illustrator appends encoding
		information to the PostScript name. This name does not include the appended data.
		The name is always encoded in ASCII. */
	AIAPI AIErr (*GetFullFontName)( AIFontKey font, char *fontName, short maxName );
	/** Get the (Illustrator) PostScript font name. This can be used to uniquely identify a font
		e.g in a file. The name is always encoded in ASCII. */
	AIAPI AIErr (*GetPostScriptFontName)( AIFontKey fontKey, char* postScriptFontName, short maxName );
	/** Returns the user name for the style of the font (e.g "Bold Italic") suitable for
		presentation to a user. The name is always encoded in ASCII. */
	AIAPI AIErr (*GetFontStyleName)( AIFontKey font, char *styleName, short maxName );
	/** Returns the user name for the family of the font (e.g "Times Roman").
		The name is either encoded in ASCII or the encoding of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetFontFamilyUIName)( AIFontKey font, char *familyName, short maxName );
	/** Returns the user name for the style of the font (e.g "Bold Italic").
		The name is either encoded in ASCII or the encoding of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetFontStyleUIName)( AIFontKey font, char *styleName, short maxName );
	/** Returns the user name for the family of the font (e.g "Times Roman").
		The name is always encoded in ASCII. */
	AIAPI AIErr (*GetTypefaceName)( AITypefaceKey typeface, char *name, short maxName );
	/** Returns the full user name for the font (e.g "Times Roman Bold Italic").
		The name is always encoded in ASCII. */
	AIAPI AIErr (*GetUserFontName)( AIFontKey font, char *userfontName, short maxName );
	/** Returns the full user name for the font (e.g "Times Roman Bold Italic").
		The name is either encoded in ASCII or the encoding of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetUserFontUIName)( AIFontKey font, char *userfontName, short maxName );

	/** The ATE interfaces represent a font as an ATE::Font whereas Illustrator's
		APIs use an AIFontKey. This API converts between the Illustrator and ATE
		representations. */
	AIAPI AIErr (*FontFromFontKey)(AIFontKey font, FontRef *result);
	/** The ATE interfaces represent a font as an ATE::Font whereas Illustrator's
		APIs use an AIFontKey. This API converts between the Illustrator and ATE
		representations. */
	AIAPI AIErr (*FontKeyFromFont)(FontRef font, AIFontKey *result);

	// The following methods deal with accessing alternate glyph information

	/** Returns a AIGlyphSet, which is an object used to access information about alternate
		glyphs within an OpenType font.  "theFont" must be an OpenType font.  If "otFeature" is zero,
		then the result will contain information about all glyphs.  If "otFeature" is non-zero,
		then the result will contain only glyphs that pertain to that feature.  Be sure to
		call ReleaseGlyphSet for any AIGlyphSet obtained. */
	AIAPI AIErr (*GetGlyphSet)(AIFontKey theFont, long otFeature, AIGlyphSet *result);
	/** Disposes an AIGlyphSet that you obtained earlier via GetGlyphSet. */
	AIAPI AIErr (*ReleaseGlyphSet)(AIGlyphSet theSet);
	/** Returns the number of glyphs within a AIGlyphSet. */
	AIAPI AIErr (*CountGlyphs)(AIGlyphSet theSet, int *glyphCountResult);
	/** Returns information about a specific glyph.  glyphIndex is the index number of the glyph
		you want information about.  It can range from 0 to (1 - CountGlyphs()) */
	AIAPI AIErr (*GetGlyphInfo)(AIGlyphSet theSet, int glyphIndex, AIGlyphInfo *glyphInfoResult);
	/** Returns the ordinal position within the glyph list of a given glyph ID. */
	AIAPI AIErr (*GlyphIDToIndex)(AIGlyphSet theSet, AIGlyphID glyphID, int *glyphIndexResult);
	/** Returns all OpenType features supported by a particular font.  featureList will be an
		array of OpenType features of length "featureCount".  Caller must provide featureList array.
		Pass in NULL for featureList to obtain the size of the array required. */
	AIAPI AIErr (*GetOTFeatures)(AIFontKey theFont, long *featureList, long *featureCount);
	/** If "existFlag" is TRUE, this function returns true or false depending upon whether or not there
		are any glyphs that belong to that feature.  Fonts can define an OpenType feature, yet assign no
		glyphs to that feature.  This is a way to efficiently assure that at least one glyph is present.
		If "existFlag" is FALSE, a "glyphSet" is returned that contains the glyphs.  GetGlyphSet with a
		specific otFeature parameter is another way to get such a glyph set.  Either way, the resultant
		AIGlyphSet must be disposed of with ReleaseGlyphSet. */
	AIAPI long  (*GetGlyphsForFeatureAccessInfo)(long theFeature, AIFontKey fontKey, AIBoolean existFlag,
			AIGlyphSet *glyphSet);
	/** Given an AIGlyphSet, this returns the AIFontInst font instance of the pertinant font. */
	AIAPI AIErr (*GetFontInstance)(AIGlyphSet glyphSetOpaque, AIFontInst **result);
	/** Returns the ID of a glyph */
	AIAPI AIErr (*GetGlyphID)(AIGlyphInfo glyphInfo, AIGlyphID *result);
	/** Given a glyph, returns it's set of alternate glyphs. */
	AIAPI AIErr (*GetAlternateGlyphs)(AIGlyphInfo glyphInfo, AIGlyphSet *result);
	/** Given a glyph, returns the OpenType features that pertain to it. */
	AIAPI AIErr (*GetGlyphOTFeatures)(AIGlyphInfo glyphInfo, char **otFeatures, long *otFeatureCount,
			long **otFeatureIndex);
	/** Given a font, glyph ID and desired OpenType feature, returns the unicode and OpenType feature that
		expresses the glyph.  Each glyph may have multiple unicode/OpenType feature expressions, so the result
		of this call may depend upon the "desiredOTFeature" parameter. Clients are responsible for any memory
		allocated and returned in otFeatures and otFeatureIndex. Clients should release the memory using
		SPBasic::FreeBlock(). */
	AIAPI AIErr (*GetGlyphUnicodeValue)(AIGlyphID mGlyphID, AIFontKey fontKey, char *desiredOTFeature,
			ASUnicode *theChar, int *resultLength, char **otFeatures, long *otFeatureCount, long **otFeatureIndex);
	/** Given a glyph, returns the AIFontKey that pertains to it. */
	AIAPI AIErr (*GetGlyphFontKey)(AIGlyphInfo theGlyphInfo, AIFontKey *result);
	/** Given a glyph, returns the number of alternate glyphs that it has. */
	AIAPI AIErr (*GetGlyphAlternateCount)(AIGlyphInfo theGlyphInfo, int *result);
	/** Given a glyph set, returns the glyph ID of the "undefined glyph".  Each font has one undefined glyph. */
	AIAPI AIErr (*GetUndefinedGlyphID)(AIGlyphSet theSet, AIGlyphID *undefinedGlyphIDResult);
	/** Not every AIGlyphSet contains the "undefined glyph".  This is a quick way to see. */
	AIAPI AIBoolean (*HasUndefinedGlyph)(AIGlyphSet theSet);

	/** Imports composite fonts from a specified AI or ATC file into the current document. */
	AIAPI AIErr (*ImportCompositeFonts)(const ai::FilePath &source);
	
	/** Translate a character value to a single glyphID.  ConvertCharacterToGlyphID will extract
		(at most) one glyph from the given string. As many bytes as are needed to form one glyph 
		will be used, starting with the first byte pointed to by 'ch'. The encoding of the string
		is derived from the font key. Returns #kGlyphNotDefinedErr if a glyph is not defined for 
		this character, and glyphID is initialized with the "notdef" glyph. */
	AIAPI AIErr (*ConvertCharacterToGlyphID) ( AIFontKey fontKey, const char* ch, long srcLen, 
											   enum AIMetricOrientation orientation, AIGlyphID* glyphID );

	/** Translate a character value to a single glyphID.  ConvertCharacterToGlyphID will extract
		(at most) one glyph from the given string. As many bytes as are needed to form one glyph 
		will be used, starting with the first byte pointed to by 'ch'. The encoding of the string
		is UTF16, and srcLen is number of ASUnicode's (not bytes). Returns #kGlyphNotDefinedErr if
		a glyph is not defined for this character, and glyphID is initialized with the "notdef"
		glyph. */
	AIAPI AIErr (*ConvertUnicodeToGlyphID) ( AIFontKey fontKey, const ASUnicode* ch, long srcLen, 
											 enum AIMetricOrientation orientation, AIGlyphID* glyphID );

	/** Returns the full user name for the font (e.g "Times Roman Bold Italic") in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetUserFontUINameUnicode)( AIFontKey fontKey, ASUnicode* userfontName, long maxName );
	/** Returns the user name for the family of the font (e.g "Times Roman") in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetFontFamilyUINameUnicode)( AIFontKey fontKey, ASUnicode* familyName, long maxName );
	/** Returns the user name for the style of the font (e.g "Bold Italic") in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names. */
	AIAPI AIErr (*GetFontStyleUINameUnicode)( AIFontKey fontKey, ASUnicode* styleName, long maxName );

	// New for Illustrator 12.0

	/** Retreive the Ideographic Character Face (IFC) bounds.

		This method fills out the client-supplied 'icfBox' array with the left, top,
		right, and bottom edges (in horizontal writing mode) of the Ideographic Character
		Face (ICF) box of a 1-unit-em font. This value will be defined for every font
		(including non-CJK fonts).

		The x coordinates increase rightward, the y downward. The values are relative to
		the font coordinate system's origin.

		The ICF-box is the maximum bounding box of the ideographic portion of a CJK font,
		usually centered within the em-box. Note that this value is defined also for
		non-CJK fonts.

		See the 'icfb' and 'icft' Baseline tags in the OpenType tag registry for more
		information.
		@param fontKey font to get info for.
		@param icfBox the returned icfBox.
		@return error code. */
	AIAPI AIErr (*GetICFBox) ( AIFontKey fontKey, AIRealRect& icfBox );

};

#include "AIHeaderEnd.h"

#endif // __AI120Font__
