/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------
 
	$File: ATETypes.h $

	Author: 

	$Author: micheleg $

	$DateTime: 2006/01/02 16:27:31 $

	$Revision: #2 $

	$Change: 379550 $
	
	Notes:	
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATETypes__
#define __ATETypes__

#ifdef __MWERKS__
	#if defined(__MC68K__) || defined(__POWERPC__)
		#pragma enumsalwaysint on
	#endif
#endif // __MWERKS__

typedef unsigned short ASUTF16;

#ifdef __cplusplus
namespace ATE
{
#endif

typedef int	ATEGlyphID;

typedef unsigned char ATEBool8;

/** @ingroup Errors Adobe Text Engine (ATE) error codes. */
enum ATEErr {
	kNoError = 0,
	kBadParameter,
	kOutOfMemory,
	kOutOfRange,
	kNullPointer,
	kInternalError,
	kMissingSpellingDictionary,
	kMissingHyphenationDictionary
};
#ifndef __cplusplus
typedef enum ATEErr ATEErr;
#endif

/** Adobe Text Engine (ATE) stream version constants */
enum StreamVersion
{
	kStreamVersion1 = 1, 
	kStreamVersion2, 
	kStreamVersion3,					kStreamLastNonPersistedVersion = kStreamVersion3, 
	kStreamVersion4,					kVerticalTextScaleChange = kStreamVersion4,


	// ^^^^^^^^^^^^ Add new versions above this comment ^^^^^^^^^^^^ 
	// This allows us to have the current version always equal the last.
	kDontUseLastPlusOne,
	kStreamCurrentVersion = kDontUseLastPlusOne - 1
};
#ifndef __cplusplus
typedef enum StreamVersion StreamVersion;
#endif

// ----------------------------------------------------------------------------------

enum FontLockingAllowance 
{
	kAllowFontLocking, 
	kDontAllowFontLocking,
	kUseFontLockDocumentSetting
};

#ifndef __cplusplus
typedef enum FontLockingAllowance FontLockingAllowance;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line cap type constants */			
enum LineCapType {
	kButtCap = 0,
	kRoundCap = 1,
	kSquareCap = 2,
	kNumLineCapTypes
};
#ifndef __cplusplus
typedef enum LineCapType LineCapType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) character type constants */		
enum ASCharType {
	/** Space character */
	kASSpaceChar = 0,
	/** Punctuation character */
	kPunctuationChar,
	/** Paragraph end character CR */
	kParagraphEndChar,
	/** This character is anything but space, punctuation or paragraph end */
	kNormalChar
};
#ifndef __cplusplus
typedef enum ASCharType ASCharType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line-join type constants */		
enum LineJoinType {
	/** A mitered join */
	kMiterJoin = 0,
	/** A round join */
	kRoundJoin = 1,
	/** A beveled join */
	kBevelJoin = 2,
	kNumLineJoinTypes
};
#ifndef __cplusplus
typedef enum LineJoinType LineJoinType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) paragraph justification type constants */		
enum ParagraphJustification
{
	kLeftJustify = 0,
	kRightJustify,
	kCenterJustify,

	kFullJustifyLastLineLeft,
	kFullJustifyLastLineRight,
	kFullJustifyLastLineCenter,

	kFullJustifyLastLineFull
};
#ifndef __cplusplus
typedef enum ParagraphJustification ParagraphJustification;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Wari Chu justification type constants */
enum WariChuJustification
{
	kWariChuLeftJustify = 0,
	kWariChuRightJustify,
	kWariChuCenterJustify,

	kWariChuFullJustifyLastLineLeft,
	kWariChuFullJustifyLastLineRight,
	kWariChuFullJustifyLastLineCenter,

	kWariChuFullJustifyLastLineFull,

	kWariChuAutoJustify
};
#ifndef __cplusplus
typedef enum WariChuJustification WariChuJustification;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Kinsoku order constants */
enum PreferredKinsokuOrder
{
	kPushIn = 0,
	kPushOutFirst,
	kPushOutOnly
};
#ifndef __cplusplus
typedef enum PreferredKinsokuOrder PreferredKinsokuOrder;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Burasagari type constants */
enum BurasagariType
{
	kBurasagariNone = 0,
	kBurasagariStandard,
	kBurasagariStrong
};
#ifndef __cplusplus
typedef enum BurasagariType BurasagariType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) leading type constants */
enum LeadingType
{
	kRomanLeadingType = 0,
	kJapaneseLeadingType = 1
};
#ifndef __cplusplus
typedef enum LeadingType LeadingType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) tab type constants */
enum TabType
{
	kLeftTabType = 0,
	kCenterTabType,
	kRightTabType,
	kDecimalTabType
};
#ifndef __cplusplus
typedef enum TabType TabType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) kerning type constants */
enum AutoKernType { kNoAutoKern, kMetricKern, kOpticalKern };
#ifndef __cplusplus
typedef enum AutoKernType AutoKernType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Japanese alternate feature type constants */
enum JapaneseAlternateFeature
{
	kDefaultForm,
	kTraditionalForm,
	kExpertForm,
	kJIS78Form,
	kJIS83Form,
	kHalfWidthForm,
	kThirdWidthForm,
	kQuarterWidthForm,
	kFullWidthForm,
	kProportionalWidthForm
};
#ifndef __cplusplus
typedef enum JapaneseAlternateFeature JapaneseAlternateFeature;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) baseline direction constants */
enum BaselineDirection
{
	kNeverUseMustBeKnown = 0,				// we don't allow "unknown" like we used to
	kBaselineWithStream = 1,	// rotate roman glyphs to vertical orientation in vertical
	kBaselineVerticalRotated = 2,					// default baseline -- roman glyphs on side in vertical
	kBaselineVerticalCrossStream = 3				// Tate-Chu-Yoko in vertical
};
#ifndef __cplusplus
typedef enum BaselineDirection BaselineDirection;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) underline position constants */
enum UnderlinePosition
{
	kUnderlineOff,
	kUnderlineOn_RightInVertical,
	kUnderlineOn_LeftInVertical
};

#ifndef __cplusplus
typedef enum UnderlinePosition UnderlinePosition;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) strike-through position constants */
enum StrikethroughPosition
{
	kStrikethroughOff,
	kStrikethroughOn_XHeight,
	kStrikethroughOn_EMBox
};

#ifndef __cplusplus
typedef enum StrikethroughPosition StrikethroughPosition;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) style-run alignment constants */
enum StyleRunAlignment
{
	kAlignStylesByBottom = 0,
	kAlignStylesByICFBottom = 1,
	
	kAlignStylesByRomanHorizontalCenterVertical = 2,
	
	kAlignStylesByCenterHorizontalRomanVertical = 3,
	
	kAlignStylesByICFTop = 4,
	kAlignStylesByTop = 5
};
#ifndef __cplusplus
typedef enum StyleRunAlignment StyleRunAlignment;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) character case change constants */
enum CaseChangeType
{
	kUppercase = 0,
	kLowercase,
	kTitleCase,
	kSentenceCase
};
#ifndef __cplusplus
typedef enum CaseChangeType CaseChangeType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) language constants */
enum Language
{
	kEnglishLanguage,
	kFinnishLanguage,
	kStandardFrenchLanguage,
	kCanadianFrenchLanguage,
	kGerman1996ReformLanguage, 			// [1996-2006] Previously kStandardGermanLanguage.  See below for latest German.
	kOldGermanLanguage,					// Pre 1996 Reform
	kOldSwissGermanLanguage, 			// Pre 2006 Reform.  Previously kSwissGermanLanguage.  See below for latest Swiss German.
	kItalianLanguage,
	kBokmalNorwegianLanguage,
	kNynorskNorwegianLanguage,
	kStandardPortugueseLanguage,
	kBrazillianPortugueseLanguage,
	kSpanishLanguage,
	kSwedishLanguage,
	kUKEnglishLanguage,
	kOldDutchLanguage,					// Pre 2006 Reform. Previously kDutchLanguage. See below for latest Dutch.
	kDanish,
	kCatalan,
	kRussian,
	kUkranian,
	kBulgarian,
	kSerbian,
	kCzech,
	kPolish,
	kRumanian,
	kGreek,
	kTurkish,
	kIcelandic,
	kHungarian,
	kChineseLanguage,
	kJapaneseLanguage,
	kCroatian,
	kHebrew,
	kSlovenian,
	kBelarussian,
	kAlbanian,
	kLithuanian,
	kLatvian,
	kSlovakian,
	kArabic,
	kEstonian,
	kFarsi,
	kGerman2006ReformLanguage,			// Latest German.  Should be the default as of 2006
	kDutch2005ReformLanguage,			// Latest Dutch.   Should be the default as of 2006
	kSwissGerman2006ReformLanguage,		// Latest Swiss German.   Should be the default as of 2006
	kCanadianEnglish,
	kNumberOfLanguages,
	kInvalidLanguage = 1000		// LILO need us to have an invalid language
};

#ifndef __cplusplus
typedef enum Language Language;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) synthetic font type constants */
enum SyntheticFontType
{
	kNoSynthetic = 0,
	kItalicSynthetic,
	kBoldSynthetic,
	kBoldItalicSynthetic
};
#ifndef __cplusplus
typedef enum SyntheticFontType SyntheticFontType;
#endif

/** Adobe Text Engine (ATE) figure style constants */
enum FigureStyle
{
	kDefaultFigureStyle = 0,
	kTabularLining,
	kProportionalOldStyle,
	kProportionalLining,
	kTabularOldStyle
};
#ifndef __cplusplus
typedef enum FigureStyle FigureStyle;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) font capitalization constants */
enum FontCapsOption
{
	kFontNormalCaps = 0,
	kFontSmallCaps,
	kFontAllCaps,
	kFontAllSmallCaps
};
#ifndef __cplusplus
typedef enum FontCapsOption FontCapsOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) baseline option constants */
enum FontBaselineOption
{
	kFontNormalBaseline = 0,
	kFontFauxedSuperScript,
	kFontFauxedSubScript
};

#ifndef __cplusplus
typedef enum FontBaselineOption FontBaselineOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) OpenType font position constants */
enum FontOpenTypePositionOption
{
	kFontOTNormalPosition,
	kFontOTSuperscriptPosition,
	kFontOTSubscriptPosition,
	kFontOTNumeratorPosition,
	kFontOTDenominatorPosition
};

#ifndef __cplusplus
typedef enum FontOpenTypePositionOption FontOpenTypePositionOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) memory management constants */
enum MakeEmptyMemoryHint
{
	kMakeEmptyAndFreeAllocations,
	kMakeEmptyAndPreserveAllocations
};

#ifndef __cplusplus
typedef enum MakeEmptyMemoryHint MakeEmptyMemoryHint;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) direction constants */
enum Direction { kForward = +1, kStationary = 0, kBackward = -1 };
#ifndef __cplusplus
typedef enum Direction Direction;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) flattening options */
enum FlattenWithParentStyles
{
	kDoNotFlattenWithParent = 0,
	kFlattenWithParent = 1
};
#ifndef __cplusplus
typedef enum FlattenWithParentStyles FlattenWithParentStyles;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) search options */
enum SearchScope
{
	kSearchEntireDocument = 0,
	kSearchStory = 1
};
#ifndef __cplusplus
typedef enum SearchScope SearchScope;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) collapse direction options */
enum CollapseDirection
{
	CollapseEnd,
	CollapseStart
};
#ifndef __cplusplus
typedef enum CollapseDirection CollapseDirection;
#endif


// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi constants */
enum
{
	kOpenParenthesis_MojiKumiCharacterClass = 1,
	kCloseParenthesis_MojiKumiCharacterClass = 2,
	kCantBeginLineCharacters_MojiKumiCharacterClass = 3,
	kBreakingPunctuation_MojiKumiCharacterClass = 4,
	kMiddlePunctuation_MojiKumiCharacterClass = 5,
	kPeriods_MojiKumiCharacterClass = 6,
	kComma_MojiKumiCharacterClass = 7,
	kIndivisibleCharacters_MojiKumiCharacterClass = 8,
	kPreAbbreviationSymbols_MojiKumiCharacterClass = 9,
	kPostAbbreviationSymbols_MojiKumiCharacterClass = 10,
	kJapaneseSpace_MojiKumiCharacterClass = 11,
	kHiragana_MojiKumiCharacterClass = 12,
	kDoubleByteNumber_MojiKumiCharacterClass = 13,
	kOtherJapaneseCharacters_MojiKumiCharacterClass = 14,
	kSingleByteNumber_MojiKumiCharacterClass = 15,
	kRomanNonSpaceCharacters_MojiKumiCharacterClass = 16,
	kTopOrEndOfLine_MojiKumiCharacterClass = 17,
	kTopOfParagraph_MojiKumiCharacterClass = 18
};

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) composite font class constants */
enum CompositeFontClassType
{
	kCompositeFontClassOverride = 0,

	// Following are predefined composite font class types
	kCompositeFontClassBase,					// Kanji class
	kCompositeFontClassKana,					// Full Width
	kCompositeFontClassPunctuation,
	kCompositeFontClassFWSymbolsAndAlphabetic,	// Full Width
	kCompositeFontClassHWSymbolsAndAlphabetic,	// Half Width
	kCompositeFontClassHWNumerals,				// Half Width
	kCompositeFontClassGaiji0,
	kCompositeFontClassGaiji1,
	kCompositeFontClassGaiji2,
	kCompositeFontClassGaiji3,
	kCompositeFontClassGaiji4,
	kCompositeFontClassGaiji5,
	kCompositeFontClassGaiji6,
	kCompositeFontClassGaiji7,
	kCompositeFontClassGaiji8,
	kCompositeFontClassGaiji9,
	kCompositeFontClassGaiji10,
	kCompositeFontClassGaiji11,

	kEndOfCompositeFontClassType
};
#ifndef __cplusplus
typedef enum CompositeFontClassType CompositeFontClassType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi code-class constants */
enum MojiKumiCodeClass
{
	kOpen = 1,
	kClose,
	kNoBegin,
	kEndPunctuation,
	kMiddlePunctuation,
	kPeriodPunctuation,
	kCommaPunctuation,
	kNotSeparatePunctuation,
	kSymbolsPrecedingNumbers,
	kSymbolsFollowingNumbers,
	kIdeographic,
	kHiragana,
	kDoubleByteNumbers,
	kOtherJapaneseCharacters,
	kSingleByteNumbers,
	kRomanNonSpace,
	kLineEdgeClass,
	kParagraphStartClass,

	kEndOfCodeClasses
};
#ifndef __cplusplus
typedef enum MojiKumiCodeClass MojiKumiCodeClass;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) class metric restrictions for a composite font component. */
enum ClassMetricRestriction
{
	// class metric restrictions for a composite font component.
	kClassMetricRestrictionNone = 0,
	kClassMetricRestrictionSize = 1 << 0,
	kClassMetricRestrictionBaseline =  1 << 1,
	kClassMetricRestrictionHorizontalScale =  1 << 2,
	kClassMetricRestrictionVerticalScale =  1 << 3,
	kClassMetricRestrictionCenterGlyph = 1 << 4
};
#ifndef __cplusplus
typedef enum ClassMetricRestriction ClassMetricRestriction;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line orientation options */
enum LineOrientation
{
	kHorizontalLines = 0,
	/** Not supported by Illustrator */
	kVerticalLeftToRight = 1,	
	kVerticalRightToLeft = 2
};
#ifndef __cplusplus
typedef enum LineOrientation LineOrientation;
#endif


// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) glyph orientation constants */
enum GlyphOrientation
{
	/** Horizontal left to right. */
	kHorizontalGlyphs,				
	/** Standard vertical, straight from the font as vertical glyphs.	 */
	kVerticalGlyphs,			
	/** Horizontal glyphs rotated 90 degrees to be on side in vertical.	 */
	kHorizontalGlyphsRotated,
	/** Not used; we are no longer setting this constant but it may exist in files. */
	kVerticalUprightRomanGlyphs
};
#ifndef __cplusplus
typedef enum GlyphOrientation GlyphOrientation;
#endif

/** Adobe Text Engine (ATE) frame type constants */
enum FrameType
{
	kPointTextFrame = 0,
	kInPathTextFrame = 1,
	kOnPathTextFrame = 2
};
#ifndef __cplusplus
typedef enum FrameType FrameType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) spell-checking result constants */
enum SpellCheckingResult
{
	kNoProblems = 0,
	kUnknownWord = 1,	
	kRepeatedWords = 2,
	kUncappedStartOfSentence = 3,
	kUncappedUnknownStartOfSentence = 4
};
#ifndef __cplusplus
typedef enum SpellCheckingResult SpellCheckingResult;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Kinsoku predefined tag constants */
enum KinsokuPredefinedTag
{
	kUserDefinedKinsokuTag = 0,
	kPredefinedHardKinsokuTag = 1,
	kPredefinedSoftKinsokuTag = 2
};
#ifndef __cplusplus
typedef enum KinsokuPredefinedTag KinsokuPredefinedTag;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi predefined tag constants */
enum MojikumiTablePredefinedTag
{
	kUserDefinedMojikumiTableTag = 0,
	kPredefinedYakumonoHankakuMojikumiTableTag = 1,
	kPredefinedYakumonoZenkakuMojikumiTableTag = 2,
	kPredefinedGyomatsuYakumonoHankakuMojikumiTableTag = 3,
	kPredefinedGyomatsuYakumonoZenkakuMojikumiTableTag = 4
};
#ifndef __cplusplus
typedef enum MojikumiTablePredefinedTag MojikumiTablePredefinedTag;
#endif

// ----------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#ifdef __MWERKS__
	#if defined(__MC68K__) || defined(__POWERPC__)
		#pragma enumsalwaysint reset
	#endif
#endif // __MWERKS__

#endif //__ATETypes__
