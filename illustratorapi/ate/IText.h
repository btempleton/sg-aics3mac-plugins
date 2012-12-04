/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	IText.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#pragma once

#include "ATESuites.h"
#include "ATEException.h"
namespace ATE
{
class IApplicationPaint;
class ICompFont;
class ICompFontClass;
class ICompFontClassSet;
class ICompFontComponent;
class ICompFontSet;
class IGlyphRun;
class IGlyphRunsIterator;
class IMojiKumi;
class IMojiKumiSet;
class ITextFrame;
class ITextFramesIterator;
class ITextLine;
class ITextLinesIterator;
class ITextResources;
class IApplicationTextResources;
class IDocumentTextResources;
class IVersionInfo;
class IArrayApplicationPaintRef;
class IArrayReal;
class IArrayBool;
class IArrayInteger;
class IArrayLineCapType;
class IArrayFigureStyle;
class IArrayLineJoinType;
class IArrayWariChuJustification;
class IArrayStyleRunAlignment;
class IArrayAutoKernType;
class IArrayBaselineDirection;
class IArrayLanguage;
class IArrayFontCapsOption;
class IArrayFontBaselineOption;
class IArrayFontOpenTypePositionOption;
class IArrayUnderlinePosition;
class IArrayStrikethroughPosition;
class IArrayParagraphJustification;
class IArrayArrayReal;
class IArrayBurasagariType;
class IArrayPreferredKinsokuOrder;
class IArrayKinsokuRef;
class IArrayMojiKumiRef;
class IArrayMojiKumiSetRef;
class IArrayTabStopsRef;
class IArrayLeadingType;
class IArrayFontRef;
class IArrayGlyphID;
class IArrayRealPoint;
class IArrayRealMatrix;
class ICharFeatures;
class ICharInspector;
class ICharStyle;
class ICharStyles;
class ICharStylesIterator;
class IFind;
class IFont;
class IGlyph;
class IGlyphs;
class IGlyphsIterator;
class IKinsoku;
class IKinsokuSet;
class IParaFeatures;
class IParagraph;
class IParagraphsIterator;
class IParaInspector;
class IParaStyle;
class IParaStyles;
class IParaStylesIterator;
class ISpell;
class IStories;
class IStory;
class ITabStop;
class ITabStops;
class ITabStopsIterator;
class ITextRange;
class ITextRanges;
class ITextRangesIterator;
class ITextRunsIterator;
class IWordsIterator;
//////////////////////////////////////////////
//       --IApplicationPaint--
//////////////////////////////////////////////
class IApplicationPaint
{
private:
	ApplicationPaintRef	fApplicationPaint;
public:
	IApplicationPaint();
	IApplicationPaint(const IApplicationPaint& src);
	IApplicationPaint& operator=(const IApplicationPaint& rhs);
	bool operator==(const IApplicationPaint& rhs) const;
	bool operator!=(const IApplicationPaint& rhs) const;
	explicit IApplicationPaint(ApplicationPaintRef applicationpaint);
	virtual ~IApplicationPaint();
	ApplicationPaintRef GetRef() const;
	bool IsNull() const;


};

//////////////////////////////////////////////
//       --ICompFont--
//////////////////////////////////////////////
class ICompFont
{
private:
	CompFontRef	fCompFont;
public:
	ICompFont();
	ICompFont(const ICompFont& src);
	ICompFont& operator=(const ICompFont& rhs);
	bool operator==(const ICompFont& rhs) const;
	bool operator!=(const ICompFont& rhs) const;
	explicit ICompFont(CompFontRef compfont);
	virtual ~ICompFont();
	CompFontRef GetRef() const;
	bool IsNull() const;

	ICompFont( ITextResources pResources);
	// PROPERTIES
	// =======================================================================
	void GetNativeName( ASUnicode* name, ASInt32 maxLength) const;
	// The PostScript name will be automatically derived from the NativeName.
	void SetNativeName( const ASUnicode* name);
	void GetPostScriptName( ASUnicode* name, ASInt32 maxLength) const;
	void GetPostScriptName( char* name, ASInt32 maxLength) const;
	void SetFontDictionary( void* fontDictionary);
	void* GetFontDictionary( ) const;
	// METHODS
	// =======================================================================
	ICompFont Duplicate( ) const;
	// Has the resource been modified since it became editable?
	bool IsModified( ) const;
	bool IsEditable( ) const;
	bool IsCommitted( ) const;
	// Is the font in a valid state, either editable or committed?
	bool VerifyState( ) const;
	bool IsATCFileLoaded( ) const;
	ASInt32 GetComponentCount( ) const;
	ICompFontComponent GetComponent( ASInt32 index) const;
	ASInt32 Find( ICompFontComponent component) const;
	// Removes an existing component, returns true if successful
	bool RemoveComponent( ASInt32 index);
	// Appends a new component, returns its new index if successful,
	// -1 if unsuccessful
	ASInt32 AddComponent( ICompFontComponent component);
	// Replaces an existing component, retuns true if successful
	bool ReplaceComponent( ASInt32 index, ICompFontComponent component);

};

//////////////////////////////////////////////
//       --ICompFontClass--
//////////////////////////////////////////////
class ICompFontClass
{
private:
	CompFontClassRef	fCompFontClass;
public:
	ICompFontClass();
	ICompFontClass(const ICompFontClass& src);
	ICompFontClass& operator=(const ICompFontClass& rhs);
	bool operator==(const ICompFontClass& rhs) const;
	bool operator!=(const ICompFontClass& rhs) const;
	explicit ICompFontClass(CompFontClassRef compfontclass);
	virtual ~ICompFontClass();
	CompFontClassRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// =======================================================================
	void GetNativeName( ASUnicode* name, ASInt32 maxLength) const;
	void SetNativeName( const ASUnicode* name);
	// Returns number of integers written to buffer, including terminating 0.
	// It will not write more than maxLength number of integers, including
	// terminating 0.
	ASInt32 GetCodes( ASUnicode* codes, ASInt32 maxLength) const;
	// Return character code count which does not include terminating null.
	ASInt32 SetCodes( const ASUnicode* codes);
	// METHODS
	// =======================================================================
	ICompFontClass Duplicate( ) const;
	ASInt32 GetCharacterCount( ) const;
	CompositeFontClassType GetClassType( ) const;
	bool IsCodeInClass( ASUnicode code) const;
	// Predefined classes are never be editable.  Cutom override classes
	// are editable only if it is in an editable state.
	bool IsEditable( ) const;
	bool IsCustomOverride( ) const;
	// Has the resource been modified since it became editable?
	bool IsModified( ) const;
	// Is the font in a valid state, either editable or committed?
	bool VerifyState( ) const;

};

//////////////////////////////////////////////
//       --ICompFontClassSet--
//////////////////////////////////////////////
class ICompFontClassSet
{
private:
	CompFontClassSetRef	fCompFontClassSet;
public:
	ICompFontClassSet();
	ICompFontClassSet(const ICompFontClassSet& src);
	ICompFontClassSet& operator=(const ICompFontClassSet& rhs);
	bool operator==(const ICompFontClassSet& rhs) const;
	bool operator!=(const ICompFontClassSet& rhs) const;
	explicit ICompFontClassSet(CompFontClassSetRef compfontclassset);
	virtual ~ICompFontClassSet();
	CompFontClassSetRef GetRef() const;
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	ASInt32 GetSize( ) const;
	ICompFontClass GetFirst( ) const;
	ICompFontClass GetLast( ) const;
	// =======================================================================
	// METHODS
	// =======================================================================
	ICompFontClass Item( ASInt32 nIndex) const;
	// Returns a valid index if found, else return -1
	ASInt32 Find( ICompFontClass compFontClass) const;
	// Returns a valid index if found, else return -1
	ASInt32 FindPredefined( CompositeFontClassType predefinedType) const;
	// =======================================================================
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

};

//////////////////////////////////////////////
//       --ICompFontComponent--
//////////////////////////////////////////////
class ICompFontComponent
{
private:
	CompFontComponentRef	fCompFontComponent;
public:
	ICompFontComponent();
	ICompFontComponent(const ICompFontComponent& src);
	ICompFontComponent& operator=(const ICompFontComponent& rhs);
	bool operator==(const ICompFontComponent& rhs) const;
	bool operator!=(const ICompFontComponent& rhs) const;
	explicit ICompFontComponent(CompFontComponentRef compfontcomponent);
	virtual ~ICompFontComponent();
	CompFontComponentRef GetRef() const;
	bool IsNull() const;

	ICompFontComponent( ITextResources pResources);
	// PROPERTIES
	// =======================================================================
	ICompFontClass GetClass( ) const;
	void SetClass( ICompFontClass charClass);
	IFont GetFont( ) const;
	void SetFont( IFont font);
	ASReal GetSize( ) const;
	void SetSize( ASReal size);
	ASReal GetBaseline( ) const;
	void SetBaseline( ASReal baseline);
	ASReal GetHorizontalScale( ) const;
	void SetHorizontalScale( ASReal horizontalScale);
	ASReal GetVerticalScale( ) const;
	void SetVerticalScale( ASReal verticalScale);
	bool GetCenterGlyph( ) const;
	void SetCenterGlyph( bool centerglyph);
	// METHODS
	// =======================================================================
	bool IsModified( ) const;

};

//////////////////////////////////////////////
//       --ICompFontSet--
//////////////////////////////////////////////
class ICompFontSet
{
private:
	CompFontSetRef	fCompFontSet;
public:
	ICompFontSet();
	ICompFontSet(const ICompFontSet& src);
	ICompFontSet& operator=(const ICompFontSet& rhs);
	bool operator==(const ICompFontSet& rhs) const;
	bool operator!=(const ICompFontSet& rhs) const;
	explicit ICompFontSet(CompFontSetRef compfontset);
	virtual ~ICompFontSet();
	CompFontSetRef GetRef() const;
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	ASInt32 GetSize( ) const;
	ICompFont GetFirst( ) const;
	ICompFont GetLast( ) const;
	// =======================================================================
	// METHODS
	// =======================================================================
	ICompFont Item( ASInt32 nIndex) const;
	// Returns a valid index if found, else return -1
	ASInt32 Find( ICompFont font) const;
	// Removes an existing composite font, returns true if successful
	bool Remove( ASInt32 nIndex);
	// Appends a new composite font, returns its new index if successful,
	// -1 if unsuccessful
	ASInt32 Add( ICompFont font);
	// Replaces an existing composite font, returns true if successful
	bool Replace( ASInt32 nIndex, ICompFont newFont);
	// Updates composite font set to reflect what is currently in the
	// document font resource's font set.  This may invalidate any old
	// indices the client may be holding on to.
	void Update( ) const;
	// =======================================================================
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

};

//////////////////////////////////////////////
//       --IGlyphRun--
//////////////////////////////////////////////
class IGlyphRun
{
private:
	GlyphRunRef	fGlyphRun;
public:
	IGlyphRun();
	IGlyphRun(const IGlyphRun& src);
	IGlyphRun& operator=(const IGlyphRun& rhs);
	bool operator==(const IGlyphRun& rhs) const;
	bool operator!=(const IGlyphRun& rhs) const;
	explicit IGlyphRun(GlyphRunRef glyphrun);
	virtual ~IGlyphRun();
	GlyphRunRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// =======================================================================
	///This API will return ITextLine, parent of this IGlyphRun.
	ITextLine GetTextLine( ) const;
	/** return the size of glyphs in this run.
	This API will return the size of the glyphs in this run.  The size of the glyphs
	might be different from GetCharacterCount() due to factors like ligature, hyphenation  etc...
	If you want the count of glyphs, then use GetGlyphIDs().GetSize().
	*/
	ASInt32 GetSize( ) const;
	/** return the size of characters in this run.
	This API will return the size of characters in this run.  You can use this API before calling
	IGlyphRun::GetContents(xxx , ASInt32 maxLength) to know the size of maxLength needed.
	The size of the glyphs IGlyphRun::GetSize() might be different from the return of GetCharacterCount() due to factors like ligature, hyphenation  etc...
	*/
	ASInt32 GetCharacterCount( ) const;
	IArrayRealPoint GetOrigins( ) const;
	IArrayGlyphID GetGlyphIDs( ) const;
	/** Return transformation matrix of this run.
	The matrix returned spesify the full transformation of the given run.  You need to transform the origin by IGlyphRun::GetOrigins() and
	concat with ITextFrame::GetMatrix() in order to get the location of the glyphs.
	*/
	ASRealMatrix GetMatrix( ) const;
	/** return character feature of this run.
	Use this to get access to Font, FontSize, HorizontalScale
	VerticalScale, Tracking, BaselineShift, FillColor , StrokeColor ,fBlend
	Fill , Stroke , FillFirst , FillOverPrint , StrokeOverPrint ,
	LineCap , LineJoin , LineWidth , MiterLimit , LineDashOffset ,
	LineDashArray and that is it, the rest of CharFeatures members are not defined.
	*/
	ICharFeatures GetCharFeatures( ) const;
	///Glyph orientation in that run.
	GlyphOrientation GetGlyphOrientation( ) const;
	ASReal GetAscent( ) const;
	ASReal GetDescent( ) const;
	/// This is the tracking that is computed by the layout engine.  i.e the space between each character.
	ASReal GetTracking( ) const;
	/// width of the space glyph in that font
	ASReal GetSpaceGlyphWidth( ) const;
	/// distance of baseline in that font
	ASReal GetDistanceToBaseline( ) const;
	/// underline position in that font
	ASReal GetUnderlinePosition( ) const;
	/// underline thickness in that font
	ASReal GetUnderlineThickness( ) const;
	/// Maximum Cap height in that font
	ASReal GetMaxCapHeight( ) const;
	/// Minimum Cap height in that font
	ASReal GetMinCapHeight( ) const;
	/// Component font for the run if using a composite font, other wise the same font as in
	/// character feature.
	IFont GetFlattenedFont( ) const;
	/// Note: size of glyphrun may be different from size of characters.
	ASInt32 GetContents( ASUnicode* text, ASInt32 maxLength) const;
	ASInt32 GetContents( char* text, ASInt32 maxLength) const;

};

//////////////////////////////////////////////
//       --IGlyphRunsIterator--
//////////////////////////////////////////////
class IGlyphRunsIterator
{
private:
	GlyphRunsIteratorRef	fGlyphRunsIterator;
public:
	IGlyphRunsIterator();
	IGlyphRunsIterator(const IGlyphRunsIterator& src);
	IGlyphRunsIterator& operator=(const IGlyphRunsIterator& rhs);
	bool operator==(const IGlyphRunsIterator& rhs) const;
	bool operator!=(const IGlyphRunsIterator& rhs) const;
	explicit IGlyphRunsIterator(GlyphRunsIteratorRef glyphrunsiterator);
	virtual ~IGlyphRunsIterator();
	GlyphRunsIteratorRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// =====================================================================
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	void Next( );
	IGlyphRun Item( ) const;

};

//////////////////////////////////////////////
//       --IMojiKumi--
//////////////////////////////////////////////
class IMojiKumi
{
private:
	MojiKumiRef	fMojiKumi;
public:
	IMojiKumi();
	IMojiKumi(const IMojiKumi& src);
	IMojiKumi& operator=(const IMojiKumi& rhs);
	bool operator==(const IMojiKumi& rhs) const;
	bool operator!=(const IMojiKumi& rhs) const;
	explicit IMojiKumi(MojiKumiRef mojikumi);
	virtual ~IMojiKumi();
	MojiKumiRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// =======================================================================
	ASInt32 GetName( ASUnicode * name, ASInt32 maxLength) const;
	ASInt32 GetNameSize( ) const;
	void SetName( const ASUnicode * name);
	bool MatchesPredefinedResourceTag( ATE::MojikumiTablePredefinedTag tag) const;
	void GetEntry( ASInt32 index, ASReal * minExpansion, ASReal * maxExpansion, ASReal * desiredExpansion) const;
	void SetEntry( ASInt32 index, ASReal minExpansion, ASReal maxExpansion, ASReal desiredExpansion);
	// METHODS
	// =======================================================================
	bool IsEquivalent( IMojiKumi rhsMojiKumi) const;
	bool IsModified( ) const;
	bool IsPredefined( ) const;
	IMojiKumi Duplicate( ) const;

};

//////////////////////////////////////////////
//       --IMojiKumiSet--
//////////////////////////////////////////////
class IMojiKumiSet
{
private:
	MojiKumiSetRef	fMojiKumiSet;
public:
	IMojiKumiSet();
	IMojiKumiSet(const IMojiKumiSet& src);
	IMojiKumiSet& operator=(const IMojiKumiSet& rhs);
	bool operator==(const IMojiKumiSet& rhs) const;
	bool operator!=(const IMojiKumiSet& rhs) const;
	explicit IMojiKumiSet(MojiKumiSetRef mojikumiset);
	virtual ~IMojiKumiSet();
	MojiKumiSetRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// =======================================================================
	ASInt32 GetSize( );
	IMojiKumi GetFirst( );
	IMojiKumi GetLast( );
	// METHODS
	// =======================================================================
	IMojiKumi Item( ASInt32 nIndex) const;
	/// Returns a valid index if found, else return -1
	/// This will search for mojikumi with the same name and data
	ASInt32 Find( const IMojiKumi mojiKumi);
	/// Returns a valid index if found, else return -1
	/// Search by name only
	ASInt32 Find( const ASUnicode* name);
	/// Returns a valid index if found, else return -1
	/// If kUserDefinedMojikumiTableTag is requested for search, it will return the
	/// first user defined mojikumi it finds.
	ASInt32 Find( MojikumiTablePredefinedTag tag);
	/// Removes an existing mojikumi, returns true if successful
	bool Remove( ASInt32 nIndex);
	/// Appends a new mojikumi, returns its new index if successful,
	/// -1 if unsuccessful
	/// If the mojikumi being added already exists in the set, it will
	/// return its current index.
	ASInt32 Add( IMojiKumi mojiKumi);
	/// Replaces an existing mojikumi at the given index with the
	/// given moji kumi.  Returns true if successful
	bool Replace( ASInt32  nIndex, IMojiKumi mojiKumi);
	/// Creates an empty new mojikumi with the specified name
	/// and appends it to the new set.
	/// It will return its new index via the nIndex parameter.
	/// If the creation of mojiKumi was unsuccessful, it will
	/// return an null AutoMojiKumi and nIndex will be -1.
	IMojiKumi CreateNewMojiKumi( const ASUnicode* name, ASInt32* nIndex);

};

//////////////////////////////////////////////
//       --ITextFrame--
//////////////////////////////////////////////
class ITextFrame
{
private:
	TextFrameRef	fTextFrame;
public:
	ITextFrame();
	ITextFrame(const ITextFrame& src);
	ITextFrame& operator=(const ITextFrame& rhs);
	bool operator==(const ITextFrame& rhs) const;
	bool operator!=(const ITextFrame& rhs) const;
	explicit ITextFrame(TextFrameRef textframe);
	virtual ~ITextFrame();
	TextFrameRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// =====================================================================
	/// Get the parent story
	IStory GetStory( ) const;
	/** Get the text range of this frame,
	If this frame is the last frame in this story then:-
	1. If bIncludeOverflow is true, then the range returned is including the overflown text.
	2. If bIncludeOverflow is false, then the range returned will not include the overflown text.
	*/
	ITextRange GetTextRange( bool bIncludeOverflow = true) const;
	ITextLinesIterator GetTextLinesIterator( ) const;
	FrameType GetType( ) const;
	LineOrientation GetLineOrientation( ) const;
	/** Check if this frame is selected.  To set the selection, you have to use application specific
	API for that.  In Illustrator case, you can use AIArtSuite to set the selection.
	*/
	bool GetSelected( ) const;
	ASRealMatrix GetMatrix( ) const;
	ASInt32 GetRowCount( ) const;
	ASInt32 GetColumnCount( ) const;
	bool GetRowMajorOrder( ) const;
	ASReal GetRowGutter( ) const;
	ASReal GetColumnGutter( ) const;
	ASReal GetSpacing( ) const;
	bool GetOpticalAlignment( ) const;
	void SetRowCount( ASInt32 rowCount);
	void SetColumnCount( ASInt32 columnCount);
	void SetRowMajorOrder( bool isRowMajor);
	void SetRowGutter( ASReal gutter);
	void SetColumnGutter( ASReal gutter);
	void SetSpacing( ASReal spacing);
	void SetOpticalAlignment( bool isActive);
	void SetLineOrientation( LineOrientation lineOrientation);

};

//////////////////////////////////////////////
//       --ITextFramesIterator--
//////////////////////////////////////////////
class ITextFramesIterator
{
private:
	TextFramesIteratorRef	fTextFramesIterator;
public:
	ITextFramesIterator();
	ITextFramesIterator(const ITextFramesIterator& src);
	ITextFramesIterator& operator=(const ITextFramesIterator& rhs);
	bool operator==(const ITextFramesIterator& rhs) const;
	bool operator!=(const ITextFramesIterator& rhs) const;
	explicit ITextFramesIterator(TextFramesIteratorRef textframesiterator);
	virtual ~ITextFramesIterator();
	TextFramesIteratorRef GetRef() const;
	bool IsNull() const;

	ITextFramesIterator( const ITextRange& range);
	// METHODS
	// =====================================================================
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void Next( );
	void Previous( );
	ITextFrame Item( ) const;

};

//////////////////////////////////////////////
//       --ITextLine--
//////////////////////////////////////////////
class ITextLine
{
private:
	TextLineRef	fTextLine;
public:
	ITextLine();
	ITextLine(const ITextLine& src);
	ITextLine& operator=(const ITextLine& rhs);
	bool operator==(const ITextLine& rhs) const;
	bool operator!=(const ITextLine& rhs) const;
	explicit ITextLine(TextLineRef textline);
	virtual ~ITextLine();
	TextLineRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// =======================================================================
	IGlyphRunsIterator GetGlyphRunsIterator( ) const;
	ITextFrame GetTextFrame( ) const;
	ITextRange GetTextRange( ) const;

};

//////////////////////////////////////////////
//       --ITextLinesIterator--
//////////////////////////////////////////////
class ITextLinesIterator
{
private:
	TextLinesIteratorRef	fTextLinesIterator;
public:
	ITextLinesIterator();
	ITextLinesIterator(const ITextLinesIterator& src);
	ITextLinesIterator& operator=(const ITextLinesIterator& rhs);
	bool operator==(const ITextLinesIterator& rhs) const;
	bool operator!=(const ITextLinesIterator& rhs) const;
	explicit ITextLinesIterator(TextLinesIteratorRef textlinesiterator);
	virtual ~ITextLinesIterator();
	TextLinesIteratorRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// =======================================================================
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void Next( );
	void Previous( );
	ITextLine Item( ) const;

};

//////////////////////////////////////////////
//       --ITextResources--
//////////////////////////////////////////////
class ITextResources
{
private:
	TextResourcesRef	fTextResources;
public:
	ITextResources();
	ITextResources(const ITextResources& src);
	ITextResources& operator=(const ITextResources& rhs);
	bool operator==(const ITextResources& rhs) const;
	bool operator!=(const ITextResources& rhs) const;
	explicit ITextResources(TextResourcesRef textresources);
	virtual ~ITextResources();
	TextResourcesRef GetRef() const;
	bool IsNull() const;

	ITextResources GetTextResources( );

};

//////////////////////////////////////////////
//       --IApplicationTextResources--
//////////////////////////////////////////////
class IApplicationTextResources
{
private:
	ApplicationTextResourcesRef	fApplicationTextResources;
public:
	IApplicationTextResources();
	IApplicationTextResources(const IApplicationTextResources& src);
	IApplicationTextResources& operator=(const IApplicationTextResources& rhs);
	bool operator==(const IApplicationTextResources& rhs) const;
	bool operator!=(const IApplicationTextResources& rhs) const;
	explicit IApplicationTextResources(ApplicationTextResourcesRef applicationtextresources);
	virtual ~IApplicationTextResources();
	ApplicationTextResourcesRef GetRef() const;
	bool IsNull() const;

	// From parent class...
	ITextResources GetTextResources( );
	// PROPERTIES
	// =======================================================================
	IKinsokuSet GetKinsokuSet( ) const;
	IMojiKumiSet GetMojiKumiSet( ) const;
	ICompFontClassSet GetCompFontClassSet( ) const;
	ICompFontSet GetCompFontSet( ) const;

};

//////////////////////////////////////////////
//       --IDocumentTextResources--
//////////////////////////////////////////////
class IDocumentTextResources
{
private:
	DocumentTextResourcesRef	fDocumentTextResources;
public:
	IDocumentTextResources();
	IDocumentTextResources(const IDocumentTextResources& src);
	IDocumentTextResources& operator=(const IDocumentTextResources& rhs);
	bool operator==(const IDocumentTextResources& rhs) const;
	bool operator!=(const IDocumentTextResources& rhs) const;
	explicit IDocumentTextResources(DocumentTextResourcesRef documenttextresources);
	virtual ~IDocumentTextResources();
	DocumentTextResourcesRef GetRef() const;
	bool IsNull() const;

	// From parent class...
	IKinsokuSet GetKinsokuSet( ) const;
	IMojiKumiSet GetMojiKumiSet( ) const;
	ICompFontClassSet GetCompFontClassSet( ) const;
	ICompFontSet GetCompFontSet( ) const;
	ITextResources GetTextResources( );
	IFind GetFind( );
	ISpell GetSpell( const char* pSpellingDirectory);
	IGlyph GetGlyphAndAlternates( ) const;
	IGlyph GetAlternateGlyph( ) const;
	void InsertAlternateGlyph( const ASUnicode* theCharacters, const ATEGlyphID glyphID, const char* otFeatureArray, ASInt32 otFeatureCount, const long* otFeatureIndexArray, bool leaveSelected);
	IArrayInteger GetAlternatesAvailableThroughoutSelection( ) const;
	JapaneseAlternateFeature GetJapaneseAlternateFeatureInSelection( bool* isFeature) const;
	void SetJapaneseAlternateFeatureInSelection( JapaneseAlternateFeature feature);
	ICharStyles GetCharStylesInDocument( ) const;
	IParaStyles GetParaStylesInDocument( ) const;
	/// Returns a named style corresponding to pName.  If no matching
	/// style can be found or *pName == L'\0' then a null object is returned.
	ICharStyle GetCharStyle( const ASUnicode* pName) const;
	IParaStyle GetParaStyle( const ASUnicode* pName) const;
	ICharStyle GetNormalCharStyle( ) const;
	IParaStyle GetNormalParaStyle( ) const;
	void ResetNormalCharStyle( );
	void ResetNormalParaStyle( );
	/// Routines to add new named styles to the document.  If an existing
	/// style already corresponds to pName or *pName == L'\0' then the
	/// document is unchanged and a null object is returned.
	ICharStyle CreateCharStyle( const ASUnicode* pName);
	IParaStyle CreateParaStyle( const ASUnicode* pName);
	ICharStyle CreateCharStyleWithFeatures( const ASUnicode* pName, ICharFeatures pFeatures);
	IParaStyle CreateParaStyleWithFeatures( const ASUnicode* pName, IParaFeatures pFeatures);
	/// Removes a style from the document.  Exact details will be provided
	/// later.
	///
	/// If no matching style in the document corresponds to pName or
	/// *pName == L'\0' then the document is unchanged and false is returned.
	bool RemoveCharStyle( const ASUnicode* pName);
	bool RemoveParaStyle( const ASUnicode* pName);
	/// Imports named styles from pSrcResources into current resource.
	void ImportCharStyles( ITextResources pSrcResources);
	void ImportParaStyles( ITextResources pSrcResources);
	void SetUseSmartQuotes( bool smartQuotesAreOn);
	void SetSmartDoubleQuoteCharacters( ASUnicode openQuote, ASUnicode closeQuote, Language language);
	void SetSmartSingleQuoteCharacters( ASUnicode openQuote, ASUnicode closeQuote, Language language);
	bool UseSmartQuotes( );
	void GetSmartDoubleQuoteCharacters( ASUnicode* openQuote, ASUnicode* closeQuote, Language language);
	void GetSmartSingleQuoteCharacters( ASUnicode* openQuote, ASUnicode* closeQuote, Language language);
	/// The library stores an internal set of insertion attributes either from
	/// the last selection or from the last attribute change to text.  This set
	/// of insertion attributes comprises the local overrides (CharFeatures)
	/// and the named style (CharStyle)
	ICharFeatures GetInsertionCharFeatures( ) const;
	ICharStyle GetInsertionCharStyle( ) const;
	void SetInsertionFeaturesAndStyle( const ICharFeatures& pFeatures, const ASUnicode* pStyleName);
	/// Get superscript size
	ASReal GetSuperscriptSize( ) const;
	/// Set superscript size
	void SetSuperscriptSize( ASReal value);
	/// Get superscript position
	ASReal GetSuperscriptPosition( ) const;
	/// Set superscript position
	void SetSuperscriptPosition( ASReal value);
	/// Get subscript size
	ASReal GetSubscriptSize( ) const;
	/// Set subscript size
	void SetSubscriptSize( ASReal value);
	/// Get subscript position
	ASReal GetSubscriptPosition( ) const;
	/// Set subscript position
	void SetSubscriptPosition( ASReal value);
	/// Get SmallCap size
	ASReal GetSmallCapSize( ) const;
	/// Set SmallCap size
	void SetSmallCapSize( ASReal value);
	/// Get ShowHiddenCharacters
	bool GetShowHiddenCharacters( ) const;
	/// Set ShowHiddenCharacters
	void SetShowHiddenCharacters( bool value);
	/// Get Greeking Size
	ASInt32 GetGreekingSize( ) const;
	/// Set Greeking Size
	void SetGreekingSize( ASInt32 value);
	/// Get HighlightSubstituteFonts
	bool GetHighlightSubstituteFonts( ) const;
	/// Set HighlightSubstituteFonts
	void SetHighlightSubstituteFonts( bool value);
	/// Get HighlightAlternateGlyphs
	bool GetHighlightAlternateGlyphs( ) const;
	/// Set HighlightAlternateGlyphs
	void SetHighlightAlternateGlyphs( bool value);

};

//////////////////////////////////////////////
//       --IVersionInfo--
//////////////////////////////////////////////
class IVersionInfo
{
private:
	VersionInfoRef	fVersionInfo;
public:
	IVersionInfo();
	IVersionInfo(const IVersionInfo& src);
	IVersionInfo& operator=(const IVersionInfo& rhs);
	bool operator==(const IVersionInfo& rhs) const;
	bool operator!=(const IVersionInfo& rhs) const;
	explicit IVersionInfo(VersionInfoRef versioninfo);
	virtual ~IVersionInfo();
	VersionInfoRef GetRef() const;
	bool IsNull() const;

	/// Return major version.
	int GetMajorVersion( );
	/// Return minor version.
	int GetMinorVersion( );
	/// Return sub minor version.
	int GetSubMinorVersion( );
	/// maxLength is the size of versionString in ASUTF16 units.
	/// return is number of characters in versionString.
	/// Here is usage:-
	/// ASUTF16 versionString[256];
	/// GetVersionAsUTF16(versionString , 256);
	int GetVersionAsUTF16( ASUTF16* versionString, int maxLength);

};

//////////////////////////////////////////////
//       --IArrayApplicationPaintRef--
//////////////////////////////////////////////
class IArrayApplicationPaintRef
{
private:
	ArrayApplicationPaintRefRef	fArrayApplicationPaintRef;
public:
	IArrayApplicationPaintRef();
	IArrayApplicationPaintRef(const IArrayApplicationPaintRef& src);
	IArrayApplicationPaintRef& operator=(const IArrayApplicationPaintRef& rhs);
	bool operator==(const IArrayApplicationPaintRef& rhs) const;
	bool operator!=(const IArrayApplicationPaintRef& rhs) const;
	explicit IArrayApplicationPaintRef(ArrayApplicationPaintRefRef arrayapplicationpaintref);
	virtual ~IArrayApplicationPaintRef();
	ArrayApplicationPaintRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IApplicationPaint GetFirst( ) const;
	IApplicationPaint GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IApplicationPaint Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayReal--
//////////////////////////////////////////////
class IArrayReal
{
private:
	ArrayRealRef	fArrayReal;
public:
	IArrayReal();
	IArrayReal(const IArrayReal& src);
	IArrayReal& operator=(const IArrayReal& rhs);
	bool operator==(const IArrayReal& rhs) const;
	bool operator!=(const IArrayReal& rhs) const;
	explicit IArrayReal(ArrayRealRef arrayreal);
	virtual ~IArrayReal();
	ArrayRealRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ASReal GetFirst( ) const;
	ASReal GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ASReal Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBool--
//////////////////////////////////////////////
class IArrayBool
{
private:
	ArrayBoolRef	fArrayBool;
public:
	IArrayBool();
	IArrayBool(const IArrayBool& src);
	IArrayBool& operator=(const IArrayBool& rhs);
	bool operator==(const IArrayBool& rhs) const;
	bool operator!=(const IArrayBool& rhs) const;
	explicit IArrayBool(ArrayBoolRef arraybool);
	virtual ~IArrayBool();
	ArrayBoolRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	bool GetFirst( ) const;
	bool GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	bool Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayInteger--
//////////////////////////////////////////////
class IArrayInteger
{
private:
	ArrayIntegerRef	fArrayInteger;
public:
	IArrayInteger();
	IArrayInteger(const IArrayInteger& src);
	IArrayInteger& operator=(const IArrayInteger& rhs);
	bool operator==(const IArrayInteger& rhs) const;
	bool operator!=(const IArrayInteger& rhs) const;
	explicit IArrayInteger(ArrayIntegerRef arrayinteger);
	virtual ~IArrayInteger();
	ArrayIntegerRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ASInt32 GetFirst( ) const;
	ASInt32 GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ASInt32 Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLineCapType--
//////////////////////////////////////////////
class IArrayLineCapType
{
private:
	ArrayLineCapTypeRef	fArrayLineCapType;
public:
	IArrayLineCapType();
	IArrayLineCapType(const IArrayLineCapType& src);
	IArrayLineCapType& operator=(const IArrayLineCapType& rhs);
	bool operator==(const IArrayLineCapType& rhs) const;
	bool operator!=(const IArrayLineCapType& rhs) const;
	explicit IArrayLineCapType(ArrayLineCapTypeRef arraylinecaptype);
	virtual ~IArrayLineCapType();
	ArrayLineCapTypeRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	LineCapType GetFirst( ) const;
	LineCapType GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	LineCapType Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFigureStyle--
//////////////////////////////////////////////
class IArrayFigureStyle
{
private:
	ArrayFigureStyleRef	fArrayFigureStyle;
public:
	IArrayFigureStyle();
	IArrayFigureStyle(const IArrayFigureStyle& src);
	IArrayFigureStyle& operator=(const IArrayFigureStyle& rhs);
	bool operator==(const IArrayFigureStyle& rhs) const;
	bool operator!=(const IArrayFigureStyle& rhs) const;
	explicit IArrayFigureStyle(ArrayFigureStyleRef arrayfigurestyle);
	virtual ~IArrayFigureStyle();
	ArrayFigureStyleRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	FigureStyle GetFirst( ) const;
	FigureStyle GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	FigureStyle Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLineJoinType--
//////////////////////////////////////////////
class IArrayLineJoinType
{
private:
	ArrayLineJoinTypeRef	fArrayLineJoinType;
public:
	IArrayLineJoinType();
	IArrayLineJoinType(const IArrayLineJoinType& src);
	IArrayLineJoinType& operator=(const IArrayLineJoinType& rhs);
	bool operator==(const IArrayLineJoinType& rhs) const;
	bool operator!=(const IArrayLineJoinType& rhs) const;
	explicit IArrayLineJoinType(ArrayLineJoinTypeRef arraylinejointype);
	virtual ~IArrayLineJoinType();
	ArrayLineJoinTypeRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	LineJoinType GetFirst( ) const;
	LineJoinType GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	LineJoinType Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayWariChuJustification--
//////////////////////////////////////////////
class IArrayWariChuJustification
{
private:
	ArrayWariChuJustificationRef	fArrayWariChuJustification;
public:
	IArrayWariChuJustification();
	IArrayWariChuJustification(const IArrayWariChuJustification& src);
	IArrayWariChuJustification& operator=(const IArrayWariChuJustification& rhs);
	bool operator==(const IArrayWariChuJustification& rhs) const;
	bool operator!=(const IArrayWariChuJustification& rhs) const;
	explicit IArrayWariChuJustification(ArrayWariChuJustificationRef arraywarichujustification);
	virtual ~IArrayWariChuJustification();
	ArrayWariChuJustificationRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	WariChuJustification GetFirst( ) const;
	WariChuJustification GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	WariChuJustification Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayStyleRunAlignment--
//////////////////////////////////////////////
class IArrayStyleRunAlignment
{
private:
	ArrayStyleRunAlignmentRef	fArrayStyleRunAlignment;
public:
	IArrayStyleRunAlignment();
	IArrayStyleRunAlignment(const IArrayStyleRunAlignment& src);
	IArrayStyleRunAlignment& operator=(const IArrayStyleRunAlignment& rhs);
	bool operator==(const IArrayStyleRunAlignment& rhs) const;
	bool operator!=(const IArrayStyleRunAlignment& rhs) const;
	explicit IArrayStyleRunAlignment(ArrayStyleRunAlignmentRef arraystylerunalignment);
	virtual ~IArrayStyleRunAlignment();
	ArrayStyleRunAlignmentRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	StyleRunAlignment GetFirst( ) const;
	StyleRunAlignment GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	StyleRunAlignment Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayAutoKernType--
//////////////////////////////////////////////
class IArrayAutoKernType
{
private:
	ArrayAutoKernTypeRef	fArrayAutoKernType;
public:
	IArrayAutoKernType();
	IArrayAutoKernType(const IArrayAutoKernType& src);
	IArrayAutoKernType& operator=(const IArrayAutoKernType& rhs);
	bool operator==(const IArrayAutoKernType& rhs) const;
	bool operator!=(const IArrayAutoKernType& rhs) const;
	explicit IArrayAutoKernType(ArrayAutoKernTypeRef arrayautokerntype);
	virtual ~IArrayAutoKernType();
	ArrayAutoKernTypeRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	AutoKernType GetFirst( ) const;
	AutoKernType GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	AutoKernType Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBaselineDirection--
//////////////////////////////////////////////
class IArrayBaselineDirection
{
private:
	ArrayBaselineDirectionRef	fArrayBaselineDirection;
public:
	IArrayBaselineDirection();
	IArrayBaselineDirection(const IArrayBaselineDirection& src);
	IArrayBaselineDirection& operator=(const IArrayBaselineDirection& rhs);
	bool operator==(const IArrayBaselineDirection& rhs) const;
	bool operator!=(const IArrayBaselineDirection& rhs) const;
	explicit IArrayBaselineDirection(ArrayBaselineDirectionRef arraybaselinedirection);
	virtual ~IArrayBaselineDirection();
	ArrayBaselineDirectionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	BaselineDirection GetFirst( ) const;
	BaselineDirection GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	BaselineDirection Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLanguage--
//////////////////////////////////////////////
class IArrayLanguage
{
private:
	ArrayLanguageRef	fArrayLanguage;
public:
	IArrayLanguage();
	IArrayLanguage(const IArrayLanguage& src);
	IArrayLanguage& operator=(const IArrayLanguage& rhs);
	bool operator==(const IArrayLanguage& rhs) const;
	bool operator!=(const IArrayLanguage& rhs) const;
	explicit IArrayLanguage(ArrayLanguageRef arraylanguage);
	virtual ~IArrayLanguage();
	ArrayLanguageRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	Language GetFirst( ) const;
	Language GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	Language Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontCapsOption--
//////////////////////////////////////////////
class IArrayFontCapsOption
{
private:
	ArrayFontCapsOptionRef	fArrayFontCapsOption;
public:
	IArrayFontCapsOption();
	IArrayFontCapsOption(const IArrayFontCapsOption& src);
	IArrayFontCapsOption& operator=(const IArrayFontCapsOption& rhs);
	bool operator==(const IArrayFontCapsOption& rhs) const;
	bool operator!=(const IArrayFontCapsOption& rhs) const;
	explicit IArrayFontCapsOption(ArrayFontCapsOptionRef arrayfontcapsoption);
	virtual ~IArrayFontCapsOption();
	ArrayFontCapsOptionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	FontCapsOption GetFirst( ) const;
	FontCapsOption GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	FontCapsOption Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontBaselineOption--
//////////////////////////////////////////////
class IArrayFontBaselineOption
{
private:
	ArrayFontBaselineOptionRef	fArrayFontBaselineOption;
public:
	IArrayFontBaselineOption();
	IArrayFontBaselineOption(const IArrayFontBaselineOption& src);
	IArrayFontBaselineOption& operator=(const IArrayFontBaselineOption& rhs);
	bool operator==(const IArrayFontBaselineOption& rhs) const;
	bool operator!=(const IArrayFontBaselineOption& rhs) const;
	explicit IArrayFontBaselineOption(ArrayFontBaselineOptionRef arrayfontbaselineoption);
	virtual ~IArrayFontBaselineOption();
	ArrayFontBaselineOptionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	FontBaselineOption GetFirst( ) const;
	FontBaselineOption GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	FontBaselineOption Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontOpenTypePositionOption--
//////////////////////////////////////////////
class IArrayFontOpenTypePositionOption
{
private:
	ArrayFontOpenTypePositionOptionRef	fArrayFontOpenTypePositionOption;
public:
	IArrayFontOpenTypePositionOption();
	IArrayFontOpenTypePositionOption(const IArrayFontOpenTypePositionOption& src);
	IArrayFontOpenTypePositionOption& operator=(const IArrayFontOpenTypePositionOption& rhs);
	bool operator==(const IArrayFontOpenTypePositionOption& rhs) const;
	bool operator!=(const IArrayFontOpenTypePositionOption& rhs) const;
	explicit IArrayFontOpenTypePositionOption(ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption);
	virtual ~IArrayFontOpenTypePositionOption();
	ArrayFontOpenTypePositionOptionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	FontOpenTypePositionOption GetFirst( ) const;
	FontOpenTypePositionOption GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	FontOpenTypePositionOption Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayUnderlinePosition--
//////////////////////////////////////////////
class IArrayUnderlinePosition
{
private:
	ArrayUnderlinePositionRef	fArrayUnderlinePosition;
public:
	IArrayUnderlinePosition();
	IArrayUnderlinePosition(const IArrayUnderlinePosition& src);
	IArrayUnderlinePosition& operator=(const IArrayUnderlinePosition& rhs);
	bool operator==(const IArrayUnderlinePosition& rhs) const;
	bool operator!=(const IArrayUnderlinePosition& rhs) const;
	explicit IArrayUnderlinePosition(ArrayUnderlinePositionRef arrayunderlineposition);
	virtual ~IArrayUnderlinePosition();
	ArrayUnderlinePositionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	UnderlinePosition GetFirst( ) const;
	UnderlinePosition GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	UnderlinePosition Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayStrikethroughPosition--
//////////////////////////////////////////////
class IArrayStrikethroughPosition
{
private:
	ArrayStrikethroughPositionRef	fArrayStrikethroughPosition;
public:
	IArrayStrikethroughPosition();
	IArrayStrikethroughPosition(const IArrayStrikethroughPosition& src);
	IArrayStrikethroughPosition& operator=(const IArrayStrikethroughPosition& rhs);
	bool operator==(const IArrayStrikethroughPosition& rhs) const;
	bool operator!=(const IArrayStrikethroughPosition& rhs) const;
	explicit IArrayStrikethroughPosition(ArrayStrikethroughPositionRef arraystrikethroughposition);
	virtual ~IArrayStrikethroughPosition();
	ArrayStrikethroughPositionRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	StrikethroughPosition GetFirst( ) const;
	StrikethroughPosition GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	StrikethroughPosition Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayParagraphJustification--
//////////////////////////////////////////////
class IArrayParagraphJustification
{
private:
	ArrayParagraphJustificationRef	fArrayParagraphJustification;
public:
	IArrayParagraphJustification();
	IArrayParagraphJustification(const IArrayParagraphJustification& src);
	IArrayParagraphJustification& operator=(const IArrayParagraphJustification& rhs);
	bool operator==(const IArrayParagraphJustification& rhs) const;
	bool operator!=(const IArrayParagraphJustification& rhs) const;
	explicit IArrayParagraphJustification(ArrayParagraphJustificationRef arrayparagraphjustification);
	virtual ~IArrayParagraphJustification();
	ArrayParagraphJustificationRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ParagraphJustification GetFirst( ) const;
	ParagraphJustification GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ParagraphJustification Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayArrayReal--
//////////////////////////////////////////////
class IArrayArrayReal
{
private:
	ArrayArrayRealRef	fArrayArrayReal;
public:
	IArrayArrayReal();
	IArrayArrayReal(const IArrayArrayReal& src);
	IArrayArrayReal& operator=(const IArrayArrayReal& rhs);
	bool operator==(const IArrayArrayReal& rhs) const;
	bool operator!=(const IArrayArrayReal& rhs) const;
	explicit IArrayArrayReal(ArrayArrayRealRef arrayarrayreal);
	virtual ~IArrayArrayReal();
	ArrayArrayRealRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IArrayReal GetFirst( ) const;
	IArrayReal GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IArrayReal Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBurasagariType--
//////////////////////////////////////////////
class IArrayBurasagariType
{
private:
	ArrayBurasagariTypeRef	fArrayBurasagariType;
public:
	IArrayBurasagariType();
	IArrayBurasagariType(const IArrayBurasagariType& src);
	IArrayBurasagariType& operator=(const IArrayBurasagariType& rhs);
	bool operator==(const IArrayBurasagariType& rhs) const;
	bool operator!=(const IArrayBurasagariType& rhs) const;
	explicit IArrayBurasagariType(ArrayBurasagariTypeRef arrayburasagaritype);
	virtual ~IArrayBurasagariType();
	ArrayBurasagariTypeRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	BurasagariType GetFirst( ) const;
	BurasagariType GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	BurasagariType Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayPreferredKinsokuOrder--
//////////////////////////////////////////////
class IArrayPreferredKinsokuOrder
{
private:
	ArrayPreferredKinsokuOrderRef	fArrayPreferredKinsokuOrder;
public:
	IArrayPreferredKinsokuOrder();
	IArrayPreferredKinsokuOrder(const IArrayPreferredKinsokuOrder& src);
	IArrayPreferredKinsokuOrder& operator=(const IArrayPreferredKinsokuOrder& rhs);
	bool operator==(const IArrayPreferredKinsokuOrder& rhs) const;
	bool operator!=(const IArrayPreferredKinsokuOrder& rhs) const;
	explicit IArrayPreferredKinsokuOrder(ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder);
	virtual ~IArrayPreferredKinsokuOrder();
	ArrayPreferredKinsokuOrderRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	PreferredKinsokuOrder GetFirst( ) const;
	PreferredKinsokuOrder GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	PreferredKinsokuOrder Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayKinsokuRef--
//////////////////////////////////////////////
class IArrayKinsokuRef
{
private:
	ArrayKinsokuRefRef	fArrayKinsokuRef;
public:
	IArrayKinsokuRef();
	IArrayKinsokuRef(const IArrayKinsokuRef& src);
	IArrayKinsokuRef& operator=(const IArrayKinsokuRef& rhs);
	bool operator==(const IArrayKinsokuRef& rhs) const;
	bool operator!=(const IArrayKinsokuRef& rhs) const;
	explicit IArrayKinsokuRef(ArrayKinsokuRefRef arraykinsokuref);
	virtual ~IArrayKinsokuRef();
	ArrayKinsokuRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IKinsoku GetFirst( ) const;
	IKinsoku GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IKinsoku Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayMojiKumiRef--
//////////////////////////////////////////////
class IArrayMojiKumiRef
{
private:
	ArrayMojiKumiRefRef	fArrayMojiKumiRef;
public:
	IArrayMojiKumiRef();
	IArrayMojiKumiRef(const IArrayMojiKumiRef& src);
	IArrayMojiKumiRef& operator=(const IArrayMojiKumiRef& rhs);
	bool operator==(const IArrayMojiKumiRef& rhs) const;
	bool operator!=(const IArrayMojiKumiRef& rhs) const;
	explicit IArrayMojiKumiRef(ArrayMojiKumiRefRef arraymojikumiref);
	virtual ~IArrayMojiKumiRef();
	ArrayMojiKumiRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IMojiKumi GetFirst( ) const;
	IMojiKumi GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IMojiKumi Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayMojiKumiSetRef--
//////////////////////////////////////////////
class IArrayMojiKumiSetRef
{
private:
	ArrayMojiKumiSetRefRef	fArrayMojiKumiSetRef;
public:
	IArrayMojiKumiSetRef();
	IArrayMojiKumiSetRef(const IArrayMojiKumiSetRef& src);
	IArrayMojiKumiSetRef& operator=(const IArrayMojiKumiSetRef& rhs);
	bool operator==(const IArrayMojiKumiSetRef& rhs) const;
	bool operator!=(const IArrayMojiKumiSetRef& rhs) const;
	explicit IArrayMojiKumiSetRef(ArrayMojiKumiSetRefRef arraymojikumisetref);
	virtual ~IArrayMojiKumiSetRef();
	ArrayMojiKumiSetRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IMojiKumiSet GetFirst( ) const;
	IMojiKumiSet GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IMojiKumiSet Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayTabStopsRef--
//////////////////////////////////////////////
class IArrayTabStopsRef
{
private:
	ArrayTabStopsRefRef	fArrayTabStopsRef;
public:
	IArrayTabStopsRef();
	IArrayTabStopsRef(const IArrayTabStopsRef& src);
	IArrayTabStopsRef& operator=(const IArrayTabStopsRef& rhs);
	bool operator==(const IArrayTabStopsRef& rhs) const;
	bool operator!=(const IArrayTabStopsRef& rhs) const;
	explicit IArrayTabStopsRef(ArrayTabStopsRefRef arraytabstopsref);
	virtual ~IArrayTabStopsRef();
	ArrayTabStopsRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ITabStops GetFirst( ) const;
	ITabStops GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ITabStops Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLeadingType--
//////////////////////////////////////////////
class IArrayLeadingType
{
private:
	ArrayLeadingTypeRef	fArrayLeadingType;
public:
	IArrayLeadingType();
	IArrayLeadingType(const IArrayLeadingType& src);
	IArrayLeadingType& operator=(const IArrayLeadingType& rhs);
	bool operator==(const IArrayLeadingType& rhs) const;
	bool operator!=(const IArrayLeadingType& rhs) const;
	explicit IArrayLeadingType(ArrayLeadingTypeRef arrayleadingtype);
	virtual ~IArrayLeadingType();
	ArrayLeadingTypeRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	LeadingType GetFirst( ) const;
	LeadingType GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	LeadingType Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontRef--
//////////////////////////////////////////////
class IArrayFontRef
{
private:
	ArrayFontRefRef	fArrayFontRef;
public:
	IArrayFontRef();
	IArrayFontRef(const IArrayFontRef& src);
	IArrayFontRef& operator=(const IArrayFontRef& rhs);
	bool operator==(const IArrayFontRef& rhs) const;
	bool operator!=(const IArrayFontRef& rhs) const;
	explicit IArrayFontRef(ArrayFontRefRef arrayfontref);
	virtual ~IArrayFontRef();
	ArrayFontRefRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	IFont GetFirst( ) const;
	IFont GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	IFont Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayGlyphID--
//////////////////////////////////////////////
class IArrayGlyphID
{
private:
	ArrayGlyphIDRef	fArrayGlyphID;
public:
	IArrayGlyphID();
	IArrayGlyphID(const IArrayGlyphID& src);
	IArrayGlyphID& operator=(const IArrayGlyphID& rhs);
	bool operator==(const IArrayGlyphID& rhs) const;
	bool operator!=(const IArrayGlyphID& rhs) const;
	explicit IArrayGlyphID(ArrayGlyphIDRef arrayglyphid);
	virtual ~IArrayGlyphID();
	ArrayGlyphIDRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ATEGlyphID GetFirst( ) const;
	ATEGlyphID GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEGlyphID Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayRealPoint--
//////////////////////////////////////////////
class IArrayRealPoint
{
private:
	ArrayRealPointRef	fArrayRealPoint;
public:
	IArrayRealPoint();
	IArrayRealPoint(const IArrayRealPoint& src);
	IArrayRealPoint& operator=(const IArrayRealPoint& rhs);
	bool operator==(const IArrayRealPoint& rhs) const;
	bool operator!=(const IArrayRealPoint& rhs) const;
	explicit IArrayRealPoint(ArrayRealPointRef arrayrealpoint);
	virtual ~IArrayRealPoint();
	ArrayRealPointRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ASRealPoint GetFirst( ) const;
	ASRealPoint GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ASRealPoint Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --IArrayRealMatrix--
//////////////////////////////////////////////
class IArrayRealMatrix
{
private:
	ArrayRealMatrixRef	fArrayRealMatrix;
public:
	IArrayRealMatrix();
	IArrayRealMatrix(const IArrayRealMatrix& src);
	IArrayRealMatrix& operator=(const IArrayRealMatrix& rhs);
	bool operator==(const IArrayRealMatrix& rhs) const;
	bool operator!=(const IArrayRealMatrix& rhs) const;
	explicit IArrayRealMatrix(ArrayRealMatrixRef arrayrealmatrix);
	virtual ~IArrayRealMatrix();
	ArrayRealMatrixRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( ) const;
	ASRealMatrix GetFirst( ) const;
	ASRealMatrix GetLast( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	ASRealMatrix Item( ASInt32 index) const;

};

//////////////////////////////////////////////
//       --ICharFeatures--
//////////////////////////////////////////////
class ICharFeatures
{
private:
	CharFeaturesRef	fCharFeatures;
public:
	ICharFeatures();
	ICharFeatures(const ICharFeatures& src);
	ICharFeatures& operator=(const ICharFeatures& rhs);
	bool operator==(const ICharFeatures& rhs) const;
	bool operator!=(const ICharFeatures& rhs) const;
	explicit ICharFeatures(CharFeaturesRef charfeatures);
	virtual ~ICharFeatures();
	CharFeaturesRef GetRef() const;
	bool IsNull() const;

	// CharFeatures is a complete Set of character attributes that
	// can be applied to text (except for kerning).  They can be used to
	// describe or Set the (1) local character attributes of text (a.k.a.
	// the local overrides or (2) attributes of a named character style.
	//
	// Often, a given CharFeatures instance will only partially define
	// each of its attributes.  The validity of an attribute is
	// determined by an associated boolean.  Calls to "Get" methods
	// return an "isAssigned" boolean that reflects the validity of
	// the returned argument.  Calls to "Set" methods always Set the
	// associated boolean to indicate validity.  Calls to "clear"
	// methods always invalidate that boolean/attribute pair.
	//
	// A character's attribute is determined by an inheritance model.
	// At the top is the "Normal" style which fully defines all
	// attributes.  These can be overriden by a named style or a local
	// override, where an attribute is valid.
	//
	// A given attribute value of a character is determined by starting
	// with the local override for that attribute if it is defined.  If
	// not, then the attribute comes from the corresponding named style
	// (if it exists and) if it is defined.  If all else fails, the
	// default value comes from the "Normal" character style.
	//
	// Default constructor creates a "blank" CharFeatures instance where
	// all attributes are undefined (invalid).
	ICharFeatures Clone( ) const;
	IFont GetFont( bool* isAssigned) const;
	ASReal GetFontSize( bool* isAssigned) const;
	ASReal GetHorizontalScale( bool* isAssigned) const;
	ASReal GetVerticalScale( bool* isAssigned) const;
	bool GetAutoLeading( bool* isAssigned) const;
	ASReal GetLeading( bool* isAssigned) const;
	ASInt32 GetTracking( bool* isAssigned) const;
	ASReal GetBaselineShift( bool* isAssigned) const;
	ASReal GetCharacterRotation( bool* isAssigned) const;
	/** Kern type information is only available for CharStyle instances.
	Use Story::GetKern( ) to obtain kern type information for a TextRange.
	*/
	AutoKernType GetAutoKernType( bool* isAssigned) const;
	FontCapsOption GetFontCapsOption( bool* isAssigned) const;
	FontBaselineOption GetFontBaselineOption( bool* isAssigned) const;
	FontOpenTypePositionOption GetFontOpenTypePositionOption( bool* isAssigned) const;
	StrikethroughPosition GetStrikethroughPosition( bool* isAssigned) const;
	UnderlinePosition GetUnderlinePosition( bool* isAssigned) const;
	ASReal GetUnderlineOffset( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	bool GetLigature( bool* isAssigned) const;
	bool GetDiscretionaryLigatures( bool* isAssigned) const;
	bool GetContextualLigatures( bool* isAssigned) const;
	bool GetAlternateLigatures( bool* isAssigned) const;
	bool GetOldStyle( bool* isAssigned) const;
	bool GetFractions( bool* isAssigned) const;
	bool GetOrdinals( bool* isAssigned) const;
	bool GetSwash( bool* isAssigned) const;
	bool GetTitling( bool* isAssigned) const;
	bool GetConnectionForms( bool* isAssigned) const;
	bool GetStylisticAlternates( bool* isAssigned) const;
	bool GetOrnaments( bool* isAssigned) const;
	FigureStyle GetFigureStyle( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	bool GetProportionalMetrics( bool* isAssigned) const;
	bool GetKana( bool* isAssigned) const;
	bool GetRuby( bool* isAssigned) const;
	bool GetItalics( bool* isAssigned) const;
	BaselineDirection GetBaselineDirection( bool* isAssigned) const;
	Language GetLanguage( bool* isAssigned) const;
	JapaneseAlternateFeature GetJapaneseAlternateFeature( bool* isAssigned) const;
	ASReal GetTsume( bool* isAssigned) const;
	StyleRunAlignment GetStyleRunAlignment( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	bool GetWariChuEnabled( bool* isAssigned) const;
	ASInt32 GetWariChuLineCount( bool* isAssigned) const;
	ASInt32 GetWariChuLineGap( bool* isAssigned) const;
	ASReal GetWariChuScale( bool* isAssigned) const;
	ASReal GetWariChuSize( bool* isAssigned) const;
	ASInt32 GetWariChuWidowAmount( bool* isAssigned) const;
	ASInt32 GetWariChuOrphanAmount( bool* isAssigned) const;
	WariChuJustification GetWariChuJustification( bool* isAssigned) const;
	ASInt32 GetTCYUpDownAdjustment( bool* isAssigned) const;
	ASInt32 GetTCYLeftRightAdjustment( bool* isAssigned) const;
	ASReal GetLeftAki( bool* isAssigned) const;
	ASReal GetRightAki( bool* isAssigned) const;
	bool GetNoBreak( bool* isAssigned) const;
	IApplicationPaint GetFillColor( bool* isAssigned) const;
	IApplicationPaint GetStrokeColor( bool* isAssigned) const;
	bool GetFill( bool* isAssigned) const;
	bool GetStroke( bool* isAssigned) const;
	bool GetFillFirst( bool* isAssigned) const;
	bool GetFillOverPrint( bool* isAssigned) const;
	bool GetStrokeOverPrint( bool* isAssigned) const;
	LineCapType GetLineCap( bool* isAssigned) const;
	LineJoinType GetLineJoin( bool* isAssigned) const;
	ASReal GetLineWidth( bool* isAssigned) const;
	ASReal GetMiterLimit( bool* isAssigned) const;
	ASReal GetLineDashOffset( bool* isAssigned) const;
	IArrayReal GetLineDashArray( bool* isAssigned) const;
	// SET PROPERTIES
	// ======================================================================
	void SetFont( IFont newVal);
	/** Set font size
	This function will throw kOutOfRange error if (newVal > 1296 || newVal < 0.1)
	*/
	void SetFontSize( ASReal newVal);
	/** Set Horizontal Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	void SetHorizontalScale( ASReal newVal);
	/** Set Vertical Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	void SetVerticalScale( ASReal newVal);
	void SetAutoLeading( bool newVal);
	void SetLeading( ASReal newVal);
	void SetTracking( ASInt32 newVal);
	void SetBaselineShift( ASReal newVal);
	void SetCharacterRotation( ASReal newVal);
	void SetAutoKernType( AutoKernType newVal);
	void SetFontCapsOption( FontCapsOption newVal);
	void SetFontBaselineOption( FontBaselineOption newVal);
	void SetFontOpenTypePositionOption( FontOpenTypePositionOption newVal);
	void SetStrikethroughPosition( StrikethroughPosition newVal);
	void SetUnderlinePosition( UnderlinePosition newVal);
	void SetUnderlineOffset( ASReal newVal);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	void SetLigature( bool newVal);
	void SetDiscretionaryLigatures( bool newVal);
	void SetContextualLigatures( bool newVal);
	void SetAlternateLigatures( bool newVal);
	void SetOldStyle( bool newVal);
	void SetFractions( bool newVal);
	void SetOrdinals( bool newVal);
	void SetSwash( bool newVal);
	void SetTitling( bool newVal);
	void SetConnectionForms( bool newVal);
	void SetStylisticAlternates( bool newVal);
	void SetOrnaments( bool newVal);
	void SetFigureStyle( FigureStyle newVal);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	void SetProportionalMetrics( bool newVal);
	void SetKana( bool newVal);
	void SetItalics( bool newVal);
	void SetRuby( bool newVal);
	void SetBaselineDirection( BaselineDirection newVal);
	void SetLanguage( Language newVal);
	void SetJapaneseAlternateFeature( JapaneseAlternateFeature newVal);
	void SetTsume( ASReal newVal);
	void SetStyleRunAlignment( StyleRunAlignment newVal);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	void SetWariChuEnabled( bool newVal);
	void SetWariChuLineCount( ASInt32 newVal);
	void SetWariChuLineGap( ASInt32 newVal);
	void SetWariChuScale( ASReal newVal);
	void SetWariChuSize( ASReal newVal);
	void SetWariChuWidowAmount( ASInt32 newVal);
	void SetWariChuOrphanAmount( ASInt32 newVal);
	void SetWariChuJustification( WariChuJustification newVal);
	void SetTCYUpDownAdjustment( ASInt32 newVal);
	void SetTCYLeftRightAdjustment( ASInt32 newVal);
	void SetLeftAki( ASReal newVal);
	void SetRightAki( ASReal newVal);
	void SetNoBreak( bool newVal);
	void SetFillColor( IApplicationPaint newVal);
	void SetStrokeColor( IApplicationPaint newVal);
	void SetFill( bool newVal);
	void SetStroke( bool newVal);
	void SetFillFirst( bool newVal);
	void SetFillOverPrint( bool newVal);
	void SetStrokeOverPrint( bool newVal);
	void SetLineCap( LineCapType newVal);
	void SetLineJoin( LineJoinType newVal);
	void SetLineWidth( ASReal newVal);
	void SetMiterLimit( ASReal newVal);
	void SetLineDashOffset( ASReal newVal);
	void SetLineDashArray( IArrayReal newVal);
	// CLEAR PROPERTIES
	// ======================================================================
	void ClearFont( );
	void ClearFontSize( );
	void ClearHorizontalScale( );
	void ClearVerticalScale( );
	void ClearAutoLeading( );
	void ClearLeading( );
	void ClearTracking( );
	void ClearBaselineShift( );
	void ClearCharacterRotation( );
	void ClearAutoKernType( );
	void ClearFontCapsOption( );
	void ClearFontBaselineOption( );
	void ClearFontOpenTypePositionOption( );
	void ClearStrikethroughPosition( );
	void ClearUnderlinePosition( );
	void ClearUnderlineOffset( );
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	void ClearLigature( );
	void ClearDiscretionaryLigatures( );
	void ClearContextualLigatures( );
	void ClearAlternateLigatures( );
	void ClearOldStyle( );
	void ClearFractions( );
	void ClearOrdinals( );
	void ClearSwash( );
	void ClearTitling( );
	void ClearConnectionForms( );
	void ClearStylisticAlternates( );
	void ClearOrnaments( );
	void ClearFigureStyle( );
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	void ClearProportionalMetrics( );
	void ClearKana( );
	void ClearItalics( );
	void ClearRuby( );
	void ClearBaselineDirection( );
	void ClearLanguage( );
	void ClearJapaneseAlternateFeature( );
	void ClearTsume( );
	void ClearStyleRunAlignment( );
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	void ClearWariChuEnabled( );
	void ClearWariChuLineCount( );
	void ClearWariChuLineGap( );
	void ClearWariChuSubLineAmount( );
	void ClearWariChuWidowAmount( );
	void ClearWariChuOrphanAmount( );
	void ClearWariChuJustification( );
	void ClearTCYUpDownAdjustment( );
	void ClearTCYLeftRightAdjustment( );
	void ClearLeftAki( );
	void ClearRightAki( );
	void ClearNoBreak( );
	void ClearFillColor( );
	void ClearStrokeColor( );
	void ClearFill( );
	void ClearStroke( );
	void ClearFillFirst( );
	void ClearFillOverPrint( );
	void ClearStrokeOverPrint( );
	void ClearLineCap( );
	void ClearLineJoin( );
	void ClearLineWidth( );
	void ClearMiterLimit( );
	void ClearLineDashOffset( );
	void ClearLineDashArray( );
	// ALGEBRA METHODS
	// Methods return true if changes were made.
	// ======================================================================
	// Intersection of 2 Features is the intersection of each attribute
	//  on the lhs with the corresponding attribute on the rhs.
	//  Attribute intersections are defined by the following truth table:
	//
	// ______________________________________________________________________
	//  this.attribute | rhs.attribute || Action/Result
	// ======================================================================
	//  assigned  | assigned  || [Case 1] If values are equal
	//      |    ||  ACTION: nothing
	//      |    ||  RESULT: value preserved
	//      |    || [Case 2] If values are not equal
	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
	//      |    ||      this.attribute.Clear();
	//      |    ||  RESULT: unassigned
	// ----------------------------------------------------------------------
	//  assigned  | unassigned || ACTION: this.attribute.Clear()
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | unassigned || ACTION: nothing (both are equal)
	//     |    || RESULT: unassigned
	// ______________________________________________________________________
	//
	bool IntersectFeatures( ICharFeatures rhs);
	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
	bool ReplaceOrAddFeatures( ICharFeatures rhs);
	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
	bool UnassignEachIfEqual( ICharFeatures rhs);
	// True if all are not assigned; false otherwise
	bool IsEachNotAssigned( ) const;
	// True if all are assigned; false otherwise
	bool IsEachAssigned( ) const;
	// ACCESSORS DESIGNED FOR CLIENT APPLICATION CORE
	// ======================================================================

};

//////////////////////////////////////////////
//       --ICharInspector--
//////////////////////////////////////////////
class ICharInspector
{
private:
	CharInspectorRef	fCharInspector;
public:
	ICharInspector();
	ICharInspector(const ICharInspector& src);
	ICharInspector& operator=(const ICharInspector& rhs);
	bool operator==(const ICharInspector& rhs) const;
	bool operator!=(const ICharInspector& rhs) const;
	explicit ICharInspector(CharInspectorRef charinspector);
	virtual ~ICharInspector();
	CharInspectorRef GetRef() const;
	bool IsNull() const;

	IArrayFontRef GetFont( ) const;
	IArrayReal GetFontSize( ) const;
	IArrayReal GetHorizontalScale( ) const;
	IArrayReal GetVerticalScale( ) const;
	IArrayBool GetSyntheticBold( ) const;
	IArrayBool GetSyntheticItalic( ) const;
	IArrayBool GetAutoLeading( ) const;
	IArrayReal GetLeading( ) const;
	IArrayInteger GetTracking( ) const;
	IArrayReal GetBaselineShift( ) const;
	IArrayReal GetCharacterRotation( ) const;
	IArrayFontCapsOption GetFontCapsOption( ) const;
	IArrayFontBaselineOption GetFontBaselineOption( ) const;
	IArrayFontOpenTypePositionOption GetFontOpenTypePositionOption( ) const;
	IArrayStrikethroughPosition GetStrikethroughPosition( ) const;
	IArrayUnderlinePosition GetUnderlinePosition( ) const;
	IArrayReal GetUnderlineOffset( ) const;
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	IArrayBool GetLigature( ) const;
	IArrayBool GetDiscretionaryLigatures( ) const;
	IArrayBool GetContextualLigatures( ) const;
	IArrayBool GetAlternateLigatures( ) const;
	IArrayBool GetOldStyle( ) const;
	IArrayBool GetFractions( ) const;
	IArrayBool GetOrdinals( ) const;
	IArrayBool GetSwash( ) const;
	IArrayBool GetTitling( ) const;
	IArrayBool GetConnectionForms( ) const;
	IArrayBool GetStylisticAlternates( ) const;
	IArrayBool GetOrnaments( ) const;
	IArrayFigureStyle GetFigureStyle( ) const;
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	IArrayBool GetProportionalMetrics( ) const;
	IArrayBool GetKana( ) const;
	IArrayBool GetItalics( ) const;
	IArrayBool GetRuby( ) const;
	IArrayBaselineDirection GetBaselineDirection( ) const;
	IArrayLanguage GetLanguage( ) const;
	IArrayReal GetTsume( ) const;
	IArrayStyleRunAlignment GetStyleRunAlignment( ) const;
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	IArrayInteger GetWariChuLineCount( ) const;
	IArrayInteger GetWariChuLineGap( ) const;
	IArrayReal GetWariChuScale( ) const;
	IArrayReal GetWariChuSize( ) const;
	IArrayInteger GetWariChuWidowAmount( ) const;
	IArrayInteger GetWariChuOrphanAmount( ) const;
	IArrayWariChuJustification GetWariChuJustification( ) const;
	IArrayBool GetWariChuEnabled( ) const;
	IArrayInteger GetTCYUpDownAdjustment( ) const;
	IArrayInteger GetTCYLeftRightAdjustment( ) const;
	IArrayReal GetLeftAki( ) const;
	IArrayReal GetRightAki( ) const;
	IArrayBool GetNoBreak( ) const;
	IArrayApplicationPaintRef GetFillColor( ) const;
	IArrayApplicationPaintRef GetStrokeColor( ) const;
	IArrayBool GetFill( ) const;
	IArrayBool GetStroke( ) const;
	IArrayBool GetFillFirst( ) const;
	IArrayBool GetFillOverPrint( ) const;
	IArrayBool GetStrokeOverPrint( ) const;
	IArrayLineCapType GetLineCap( ) const;
	IArrayLineJoinType GetLineJoin( ) const;
	IArrayReal GetLineWidth( ) const;
	IArrayReal GetMiterLimit( ) const;
	IArrayReal GetLineDashOffset( ) const;
	IArrayArrayReal GetLineDashArray( ) const;

};

//////////////////////////////////////////////
//       --ICharStyle--
//////////////////////////////////////////////
class ICharStyle
{
private:
	CharStyleRef	fCharStyle;
public:
	ICharStyle();
	ICharStyle(const ICharStyle& src);
	ICharStyle& operator=(const ICharStyle& rhs);
	bool operator==(const ICharStyle& rhs) const;
	bool operator!=(const ICharStyle& rhs) const;
	explicit ICharStyle(CharStyleRef charstyle);
	virtual ~ICharStyle();
	CharStyleRef GetRef() const;
	bool IsNull() const;

	/// Name of style is set in pName up to maxLength characters.
	/// Length of actual name is returned; 0 if error occurred.
	ASInt32 GetName( ASUnicode* pName, ASInt32 maxLength) const;
	/// Sets name of style to null-terminated pName.  If existing style of
	/// same name exists or *pName == L'\0' then false is returned.
	bool SetName( const ASUnicode* pName);
	/// Parent style returned.  For Normal style, a null object is returned.
	ICharStyle GetParent( ) const;
	/// Parent style set.  Returns false if attempting to set the parent
	/// of Normal style, true otherwise.
	bool SetParent( const ICharStyle pStyle);
	/// Returns whether style has parent.  Always false for normal style.
	bool HasParent( ) const;
	/// Returns features for style.
	ICharFeatures GetFeatures( ) const;
	/// The style's feature attributes are all assigned to those of pFeatures.
	/// For Normal style, this has same effect as ReplaceOrAddFeatures.
	void SetFeatures( ICharFeatures pFeatures);
	/// The style's feature attributes are replaced by any corresponding ones
	/// in pFeatures that contain valid values (i.e. the attribute is assigned).
	void ReplaceOrAddFeatures( ICharFeatures pFeatures);

};

//////////////////////////////////////////////
//       --ICharStyles--
//////////////////////////////////////////////
class ICharStyles
{
private:
	CharStylesRef	fCharStyles;
public:
	ICharStyles();
	ICharStyles(const ICharStyles& src);
	ICharStyles& operator=(const ICharStyles& rhs);
	bool operator==(const ICharStyles& rhs) const;
	bool operator!=(const ICharStyles& rhs) const;
	explicit ICharStyles(CharStylesRef charstyles);
	virtual ~ICharStyles();
	CharStylesRef GetRef() const;
	bool IsNull() const;

	bool IsEmpty( ) const;
	ASInt32 GetSize( ) const;
	void ShowAllStyles( ) const;
	void ShowOnlyUnreferencedStyles( ) const;
	void ShowOnlyStylesReferencedIn( ITextRange pRange) const;
	// Reorders position of style
	void MoveStyleTo( ICharStyle pStyle, ASInt32 position);

};

//////////////////////////////////////////////
//       --ICharStylesIterator--
//////////////////////////////////////////////
class ICharStylesIterator
{
private:
	CharStylesIteratorRef	fCharStylesIterator;
public:
	ICharStylesIterator();
	ICharStylesIterator(const ICharStylesIterator& src);
	ICharStylesIterator& operator=(const ICharStylesIterator& rhs);
	bool operator==(const ICharStylesIterator& rhs) const;
	bool operator!=(const ICharStylesIterator& rhs) const;
	explicit ICharStylesIterator(CharStylesIteratorRef charstylesiterator);
	virtual ~ICharStylesIterator();
	CharStylesIteratorRef GetRef() const;
	bool IsNull() const;

	ICharStylesIterator( ICharStyles pStyles, Direction direction = kForward);
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	void Previous( );
	ICharStyle Item( ) const;

};

//////////////////////////////////////////////
//       --IFind--
//////////////////////////////////////////////
class IFind
{
private:
	FindRef	fFind;
public:
	IFind();
	IFind(const IFind& src);
	IFind& operator=(const IFind& rhs);
	bool operator==(const IFind& rhs) const;
	bool operator!=(const IFind& rhs) const;
	explicit IFind(FindRef find);
	virtual ~IFind();
	FindRef GetRef() const;
	bool IsNull() const;

	// Options
	// ========================================================================
	Direction GetSearchDirection( ) const;
	bool GetIgnoreCase( ) const;
	bool GetWholeWord( ) const;
	bool GetWrap( ) const;
	bool GetFindWordsOutOfBounds( ) const;
	void SetSearchDirection( Direction newValue);
	void SetIgnoreCase( bool newValue);
	void SetWholeWord( bool newValue);
	void SetWrap( bool newValue);
	void SetFindWordsOutOfBounds( bool newValue);
	// Control scope of search to be entire document or Story.
	// By default, the entire document is searched.
	SearchScope GetSearchScope( ) const;
	void SetSearchScope( SearchScope searchScope);
	// If called, search is done only within specified TextRange
	void SetSearchRange( ITextRange pRange);
	void SetSearchChars( ASUnicode* pSearchChars);
	void GetSearchChars( ASUnicode* pSearchChars, ASInt32 length) const;
	void SetReplaceChars( ASUnicode* pSearchChars);
	void GetReplaceChars( ASUnicode* pSearchChars, ASInt32 length) const;
	// Temporary way to reset the engine for modeless operation
	void Reset( );
	// Methods
	// ========================================================================
	// Searches current user selection.
	// Returns false if the search failed
	bool FindMatch( ITextRange pTextRange);
	// Skips the current user selection.
	// Returns false if the search failed
	bool FindNextMatch( ITextRange pTextRange);
	bool ReplaceMatch( ITextRange pTextRange, bool findNext);
	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
	bool FindAndReplaceAllMatches( ASInt32* pReplaceCount);
	// Use these to implement ReplaceAll.
	// Start by saving off the settings with GetPreReplaceAllSettings( )
	// (also note what text object you're currently working with so you can restore that
	// via SetSearchRange( ) when you're finished.
	void GetPreReplaceAllSettings( ASInt32* pCurrentPoint, ASInt32* pStartPoint) const;
	// Implement a loop to go through all the text objects you want to replace all with.
	// Use FindMatch( ), FindNextMatch( ), and ReplaceMatch( ) to replace all.
	// Keep track of how many ReplaceMatch( ) calls were made for reporting back to the user
	// When finished, restore the correct text object and range using SetSearchRange( )
	// and restore the positions using RestorePreReplaceAllSettings( )
	void RestorePreReplaceAllSettings( const ASInt32 currentPoint, const ASInt32 startPoint);

};

//////////////////////////////////////////////
//       --IFont--
//////////////////////////////////////////////
class IFont
{
private:
	FontRef	fFont;
public:
	IFont();
	IFont(const IFont& src);
	IFont& operator=(const IFont& rhs);
	bool operator==(const IFont& rhs) const;
	bool operator!=(const IFont& rhs) const;
	explicit IFont(FontRef font);
	virtual ~IFont();
	FontRef GetRef() const;
	bool IsNull() const;

	// METHODS
	// ========================================================================
	bool IsCoolTypeTechnology( ) const;
	/// if this font has its roman glyphs sideway by default.
	bool IsVerticalRomanGlyphsOnSideByDefault( bool withItalics, StyleRunAlignment characterAlignment) const;
	void* GetCTFontDict( );

};

//////////////////////////////////////////////
//       --IGlyph--
//////////////////////////////////////////////
class IGlyph
{
private:
	GlyphRef	fGlyph;
public:
	IGlyph();
	IGlyph(const IGlyph& src);
	IGlyph& operator=(const IGlyph& rhs);
	bool operator==(const IGlyph& rhs) const;
	bool operator!=(const IGlyph& rhs) const;
	explicit IGlyph(GlyphRef glyph);
	virtual ~IGlyph();
	GlyphRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEGlyphID GetGlyphID( ) const;
	IGlyphs GetAlternateGlyphs( ) const;
	void GetOTFeatures( char** otFeatures, long* otFeatureCount, long** otFeatureIndex);
	// RealMatrix   GetTransformation();
	// ========================================================================
	// METHODS
	// ========================================================================
	// =============================================================================
	// PROTECTED AND PRIVATE
	// =============================================================================

};

//////////////////////////////////////////////
//       --IGlyphs--
//////////////////////////////////////////////
class IGlyphs
{
private:
	GlyphsRef	fGlyphs;
public:
	IGlyphs();
	IGlyphs(const IGlyphs& src);
	IGlyphs& operator=(const IGlyphs& rhs);
	bool operator==(const IGlyphs& rhs) const;
	bool operator!=(const IGlyphs& rhs) const;
	explicit IGlyphs(GlyphsRef glyphs);
	virtual ~IGlyphs();
	GlyphsRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// ========================================================================
	ASInt32 GetSize( );
	IGlyph GetFirst( );
	IGlyph GetLast( );
	// navigation objects.
	ITextRanges GetTextRanges( ) const;
	ITextRanges GetTextSelection( ) const;
	IParagraphsIterator GetParagraphsIterator( ) const;
	ITextRunsIterator GetTextRunsIterator( ) const;
	IWordsIterator GetWordsIterator( ) const;
	// METHODS
	// ========================================================================
	void Add( const IGlyph& glyph);
	IGlyph Item( ASInt32 nIndex) const;
	void RemoveAll( );
	void Remove( ASInt32 nIndex);
	// PROTECTED AND PRIVATE
	// ========================================================================

};

//////////////////////////////////////////////
//       --IGlyphsIterator--
//////////////////////////////////////////////
class IGlyphsIterator
{
private:
	GlyphsIteratorRef	fGlyphsIterator;
public:
	IGlyphsIterator();
	IGlyphsIterator(const IGlyphsIterator& src);
	IGlyphsIterator& operator=(const IGlyphsIterator& rhs);
	bool operator==(const IGlyphsIterator& rhs) const;
	bool operator!=(const IGlyphsIterator& rhs) const;
	explicit IGlyphsIterator(GlyphsIteratorRef glyphsiterator);
	virtual ~IGlyphsIterator();
	GlyphsIteratorRef GetRef() const;
	bool IsNull() const;

	IGlyphsIterator( IGlyphs glyphs, Direction direction = kForward);
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	IGlyph GetFirst( );
	IGlyph GetLast( );
	IGlyph GetNext( );
	IGlyph Item( ) const;
	void Next( );
	void Previous( );

};

//////////////////////////////////////////////
//       --IKinsoku--
//////////////////////////////////////////////
class IKinsoku
{
private:
	KinsokuRef	fKinsoku;
public:
	IKinsoku();
	IKinsoku(const IKinsoku& src);
	IKinsoku& operator=(const IKinsoku& rhs);
	bool operator==(const IKinsoku& rhs) const;
	bool operator!=(const IKinsoku& rhs) const;
	explicit IKinsoku(KinsokuRef kinsoku);
	virtual ~IKinsoku();
	KinsokuRef GetRef() const;
	bool IsNull() const;

	/// Constructs an empty Kinsoku
	// PROPERTIES
	// =======================================================================
	ASInt32 GetName( ASUnicode* name, ASInt32 maxLength) const;
	ASInt32 GetNameSize( ) const;
	void SetName( const ASUnicode* name);
	bool MatchesPredefinedResourceTag( ATE::KinsokuPredefinedTag tag) const;
	ASInt32 GetNoStartCharSet( ASUnicode* noStartCharSet, ASInt32 maxLength) const;
	ASInt32 GetNoStartCharSetSize( ) const;
	void SetNoStartCharSet( const ASUnicode* noStartCharSet);
	ASInt32 GetNoEndCharSet( ASUnicode* noEndCharSet, ASInt32 maxLength) const;
	ASInt32 GetNoEndCharSetSize( ) const;
	void SetNoEndCharSet( const ASUnicode* noEndCharSet);
	ASInt32 GetNoBreakCharSet( ASUnicode* noBreakCharSet, ASInt32 maxLength) const;
	ASInt32 GetNoBreakCharSetSize( ) const;
	void SetNoBreakCharSet( const ASUnicode* noBreakCharSet);
	ASInt32 GetHangingCharSet( ASUnicode* hangingCharSet, ASInt32 maxLength) const;
	ASInt32 GetHangingCharSetSize( ) const;
	void SetHangingCharSet( const ASUnicode* hangingCharSet);
	// METHODS
	// =======================================================================
	bool IsNoStartChar( ASUnicode character) const;
	bool IsNoEndChar( ASUnicode character) const;
	bool IsNoBreakChar( ASUnicode character) const;
	bool IsHangingChar( ASUnicode character) const;
	/// Does a shallow equivalency test
	/// Does a deep equivalency test
	bool IsEquivalent( IKinsoku rhsKinsoku) const;
	/// Has the resource been modified since it became editable?
	bool IsModified( ) const;
	/// Is it a predefined or user defined kinsoku?
	bool IsPredefined( ) const;
	IKinsoku Duplicate( ) const;

};

//////////////////////////////////////////////
//       --IKinsokuSet--
//////////////////////////////////////////////
class IKinsokuSet
{
private:
	KinsokuSetRef	fKinsokuSet;
public:
	IKinsokuSet();
	IKinsokuSet(const IKinsokuSet& src);
	IKinsokuSet& operator=(const IKinsokuSet& rhs);
	bool operator==(const IKinsokuSet& rhs) const;
	bool operator!=(const IKinsokuSet& rhs) const;
	explicit IKinsokuSet(KinsokuSetRef kinsokuset);
	virtual ~IKinsokuSet();
	KinsokuSetRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// =======================================================================
	ASInt32 GetSize( );
	IKinsoku GetFirst( );
	IKinsoku GetLast( );
	// METHODS
	// =======================================================================
	IKinsoku Item( ASInt32 nIndex) const;
	/// Returns a valid index if found, else return -1
	/// This will search for kinsoku with the same name and data
	ASInt32 Find( IKinsoku kinsoku);
	/// Returns a valid index if found, else return -1
	/// Search by name only
	ASInt32 Find( const ASUnicode* name);
	/// Returns a valid index if found, else return -1
	/// If kUserDefinedKinsokuTag is requested for search, it will return the
	/// first user defined kinsoku it finds.
	ASInt32 Find( KinsokuPredefinedTag tag);
	/// Removes an existing kinsoku, returns true if successful
	bool Remove( ASInt32 nIndex);
	/// Appends a new kinsoku, returns its new index if successful,
	/// -1 if unsuccessful
	/// If the kinsoku being added already exists in the set, it will
	/// return its current index.
	ASInt32 Add( IKinsoku kinsoku);
	/// Replaces an existing kinsoku at the given index with the
	/// given kinsoku.  Returns true if successful
	bool Replace( ASInt32 nIndex, IKinsoku kinsoku);

};

//////////////////////////////////////////////
//       --IParaFeatures--
//////////////////////////////////////////////
class IParaFeatures
{
private:
	ParaFeaturesRef	fParaFeatures;
public:
	IParaFeatures();
	IParaFeatures(const IParaFeatures& src);
	IParaFeatures& operator=(const IParaFeatures& rhs);
	bool operator==(const IParaFeatures& rhs) const;
	bool operator!=(const IParaFeatures& rhs) const;
	explicit IParaFeatures(ParaFeaturesRef parafeatures);
	virtual ~IParaFeatures();
	ParaFeaturesRef GetRef() const;
	bool IsNull() const;

	// ParaFeatures is a complete Set of paragraph attributes that
	// can be applied to text (except for kerning).  They can be used to
	// describe or Set the (1) local paragraph attributes of text (a.k.a.
	// the local overrides or (2) attributes of a named paragraph style.
	//
	// Often, a given ParaFeatures instance will only partially define
	// each of its attributes.  The validity of an attribute is
	// determined by an associated boolean.  Calls to "Get" methods
	// return an "isAssigned" boolean that reflects the validity of
	// the returned argument.  Calls to "Set" methods always Set the
	// associated boolean to indicate validity.  Calls to "Clear"
	// methods always invalidate that boolean/attribute pair.
	//
	// A paragraph's attribute is determined by an inheritance model.
	// At the top is the "Normal" style which fully defines all
	// attributes.  These can be overriden by a named style or a local
	// override, where an attribute is valid.
	//
	// A given attribute value of a paragraph is determined by starting
	// with the local override for that attribute if it is defined.  If
	// not, then the attribute comes from the corresponding named style
	// (if it exists and) if it is defined.  If all else fails, the
	// default value comes from the "Normal" paragraph style.
	//
	// Default constructor creates a "blank" ParaFeatures instance where
	// all attributes are undefined (invalid).
	IParaFeatures Clone( ) const;
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	ParagraphJustification GetJustification( bool* isAssigned) const;
	ASReal GetFirstLineIndent( bool* isAssigned) const;
	ASReal GetStartIndent( bool* isAssigned) const;
	ASReal GetEndIndent( bool* isAssigned) const;
	ASReal GetSpaceBefore( bool* isAssigned) const;
	ASReal GetSpaceAfter( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	bool GetAutoHyphenate( bool* isAssigned) const;
	ASInt32 GetHyphenatedWordSize( bool* isAssigned) const;
	ASInt32 GetPreHyphenSize( bool* isAssigned) const;
	ASInt32 GetPostHyphenSize( bool* isAssigned) const;
	ASInt32 GetConsecutiveHyphenLimit( bool* isAssigned) const;
	ASReal GetHyphenationZone( bool* isAssigned) const;
	bool GetHyphenateCapitalized( bool* isAssigned) const;
	ASReal GetHyphenationPreference( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	ASReal GetDesiredWordSpacing( bool* isAssigned) const;
	ASReal GetMaxWordSpacing( bool* isAssigned) const;
	ASReal GetMinWordSpacing( bool* isAssigned) const;
	ASReal GetDesiredLetterSpacing( bool* isAssigned) const;
	ASReal GetMaxLetterSpacing( bool* isAssigned) const;
	ASReal GetMinLetterSpacing( bool* isAssigned) const;
	ASReal GetDesiredGlyphScaling( bool* isAssigned) const;
	ASReal GetMaxGlyphScaling( bool* isAssigned) const;
	ASReal GetMinGlyphScaling( bool* isAssigned) const;
	ParagraphJustification GetSingleWordJustification( bool* isAssigned) const;
	ASReal GetAutoLeadingPercentage( bool* isAssigned) const;
	LeadingType GetLeadingType( bool* isAssigned) const;
	ITabStops GetTabStops( bool* isAssigned) const;
	ASReal GetDefaultTabWidth( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	bool GetHangingRoman( bool* isAssigned) const;
	ASInt32 GetAutoTCY( bool* isAssigned) const;
	bool GetBunriKinshi( bool* isAssigned) const;
	BurasagariType GetBurasagariType( bool* isAssigned) const;
	PreferredKinsokuOrder GetPreferredKinsokuOrder( bool* isAssigned) const;
	bool GetKurikaeshiMojiShori( bool* isAssigned) const;
	/// This will return a null object if Kinsoku is not used (ie None set)
	IKinsoku GetKinsoku( bool* isAssigned) const;
	/// This will return a null object if Mojikumi is not used (ie None set)
	IMojiKumi GetMojiKumi( bool* isAssigned) const;
	// Other
	bool GetEveryLineComposer( bool* isAssigned) const;
	ICharFeatures GetDefaultCharFeatures( bool* isAssigned) const;
	// SET PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	void SetJustification( ParagraphJustification newVal);
	void SetFirstLineIndent( ASReal newVal);
	void SetStartIndent( ASReal newVal);
	void SetEndIndent( ASReal newVal);
	void SetSpaceBefore( ASReal newVal);
	void SetSpaceAfter( ASReal newVal);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	void SetAutoHyphenate( bool newVal);
	void SetHyphenatedWordSize( ASInt32 newVal);
	void SetPreHyphenSize( ASInt32 newVal);
	void SetPostHyphenSize( ASInt32 newVal);
	void SetConsecutiveHyphenLimit( ASInt32 newVal);
	void SetHyphenationZone( ASReal newVal);
	void SetHyphenateCapitalized( bool newVal);
	void SetHyphenationPreference( ASReal newVal);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	void SetDesiredWordSpacing( ASReal newVal);
	void SetMaxWordSpacing( ASReal newVal);
	void SetMinWordSpacing( ASReal newVal);
	void SetDesiredLetterSpacing( ASReal newVal);
	void SetMaxLetterSpacing( ASReal newVal);
	void SetMinLetterSpacing( ASReal newVal);
	void SetDesiredGlyphScaling( ASReal newVal);
	void SetMaxGlyphScaling( ASReal newVal);
	void SetMinGlyphScaling( ASReal newVal);
	void SetSingleWordJustification( ParagraphJustification newVal);
	void SetAutoLeadingPercentage( ASReal newVal);
	void SetLeadingType( LeadingType newVal);
	void SetTabStops( ITabStops newVal);
	void SetDefaultTabWidth( ASReal newVal);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	void SetHangingRoman( bool newVal);
	void SetAutoTCY( ASInt32 newVal);
	void SetBunriKinshi( bool newVal);
	void SetBurasagariType( BurasagariType newVal);
	void SetPreferredKinsokuOrder( PreferredKinsokuOrder newVal);
	void SetKurikaeshiMojiShori( bool newVal);
	void SetKinsoku( IKinsoku newVal);
	void SetMojiKumi( IMojiKumi newVal);
	// Other
	void SetEveryLineComposer( bool newVal);
	void SetDefaultCharFeatures( ICharFeatures newVal);
	// CLEAR PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	void ClearJustification( );
	void ClearFirstLineIndent( );
	void ClearStartIndent( );
	void ClearEndIndent( );
	void ClearSpaceBefore( );
	void ClearSpaceAfter( );
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	void ClearAutoHyphenate( );
	void ClearHyphenatedWordSize( );
	void ClearPreHyphenSize( );
	void ClearPostHyphenSize( );
	void ClearConsecutiveHyphenLimit( );
	void ClearHyphenationZone( );
	void ClearHyphenateCapitalized( );
	void ClearHyphenationPreference( );
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	void ClearWordSpacing( );
	void ClearLetterSpacing( );
	void ClearGlyphScaling( );
	void ClearSingleWordJustification( );
	void ClearAutoLeadingPercentage( );
	void ClearLeadingType( );
	void ClearTabStops( );
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	void ClearHangingRoman( );
	void ClearAutoTCY( );
	void ClearBunriKinshi( );
	void ClearBurasagariType( );
	void ClearPreferredKinsokuOrder( );
	void ClearKurikaeshiMojiShori( );
	void ClearKinsoku( );
	void ClearMojiKumi( );
	// Other
	void ClearEveryLineComposer( );
	void ClearDefaultCharFeatures( );
	// ALGEBRA METHODS
	// Methods return true if changes were made.
	// ======================================================================
	// Intersection of 2 Features is the intersection of each attribute
	//  on the lhs with the corresponding attribute on the rhs.
	//  Attribute intersections are defined by the following truth table:
	//
	// ______________________________________________________________________
	//  this.attribute | rhs.attribute || Action/Result
	// ======================================================================
	//  assigned  | assigned  || [Case 1] If values are equal
	//      |    ||  ACTION: nothing
	//      |    ||  RESULT: value preserved
	//      |    || [Case 2] If values are not equal
	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
	//      |    ||      this.attribute.Clear();
	//      |    ||  RESULT: unassigned
	// ----------------------------------------------------------------------
	//  assigned  | unassigned || ACTION: this.attribute.Clear()
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | unassigned || ACTION: nothing (both are equal)
	//     |    || RESULT: unassigned
	// ______________________________________________________________________
	//
	bool IntersectFeatures( IParaFeatures rhs);
	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
	bool ReplaceOrAddFeatures( IParaFeatures rhs);
	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
	bool UnassignEachIfEqual( const IParaFeatures rhs);
	// True if all are not assigned; false otherwise
	bool IsEachNotAssigned( ) const;
	// True if all are assigned; false otherwise
	bool IsEachAssigned( ) const;
	// PRIVATE AND PROTECTED
	// ======================================================================

};

//////////////////////////////////////////////
//       --IParagraph--
//////////////////////////////////////////////
class IParagraph
{
private:
	ParagraphRef	fParagraph;
public:
	IParagraph();
	IParagraph(const IParagraph& src);
	IParagraph& operator=(const IParagraph& rhs);
	bool operator==(const IParagraph& rhs) const;
	bool operator!=(const IParagraph& rhs) const;
	explicit IParagraph(ParagraphRef paragraph);
	virtual ~IParagraph();
	ParagraphRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// ========================================================================
	ASInt32 GetLength( );
	// navigation objects.
	IStory GetStory( );
	ITextRange GetTextRange( );
	ITextRanges GetTextRanges( );
	ITextRanges GetTextSelection( );
	IWordsIterator GetWordsIterator( );
	// METHODS
	// ========================================================================
	IParagraph GetNext( );
	IParagraph GetPrev( );
	ASErr GetContents( ASUnicode* text, ASInt32 maxLength);
	ASErr GetContents( char* text, ASInt32 maxLength);

};

//////////////////////////////////////////////
//       --IParagraphsIterator--
//////////////////////////////////////////////
class IParagraphsIterator
{
private:
	ParagraphsIteratorRef	fParagraphsIterator;
public:
	IParagraphsIterator();
	IParagraphsIterator(const IParagraphsIterator& src);
	IParagraphsIterator& operator=(const IParagraphsIterator& rhs);
	bool operator==(const IParagraphsIterator& rhs) const;
	bool operator!=(const IParagraphsIterator& rhs) const;
	explicit IParagraphsIterator(ParagraphsIteratorRef paragraphsiterator);
	virtual ~IParagraphsIterator();
	ParagraphsIteratorRef GetRef() const;
	bool IsNull() const;

	IParagraphsIterator( ITextRanges ranges, Direction direction = kForward);
	bool IsDone( ) const;
	bool IsNotDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	IParagraph Item( );

};

//////////////////////////////////////////////
//       --IParaInspector--
//////////////////////////////////////////////
class IParaInspector
{
private:
	ParaInspectorRef	fParaInspector;
public:
	IParaInspector();
	IParaInspector(const IParaInspector& src);
	IParaInspector& operator=(const IParaInspector& rhs);
	bool operator==(const IParaInspector& rhs) const;
	bool operator!=(const IParaInspector& rhs) const;
	explicit IParaInspector(ParaInspectorRef parainspector);
	virtual ~IParaInspector();
	ParaInspectorRef GetRef() const;
	bool IsNull() const;

	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	IArrayParagraphJustification GetJustification( ) const;
	IArrayReal GetFirstLineIndent( ) const;
	IArrayReal GetStartIndent( ) const;
	IArrayReal GetEndIndent( ) const;
	IArrayReal GetSpaceBefore( ) const;
	IArrayReal GetSpaceAfter( ) const;
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	IArrayBool GetAutoHyphenate( ) const;
	IArrayInteger GetHyphenatedWordSize( ) const;
	IArrayInteger GetPreHyphenSize( ) const;
	IArrayInteger GetPostHyphenSize( ) const;
	IArrayInteger GetConsecutiveHyphenLimit( ) const;
	IArrayReal GetHyphenationZone( ) const;
	IArrayBool GetHyphenateCapitalized( ) const;
	IArrayReal GetHyphenationPreference( ) const;
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	IArrayReal GetDesiredWordSpacing( ) const;
	IArrayReal GetMaxWordSpacing( ) const;
	IArrayReal GetMinWordSpacing( ) const;
	IArrayReal GetDesiredLetterSpacing( ) const;
	IArrayReal GetMaxLetterSpacing( ) const;
	IArrayReal GetMinLetterSpacing( ) const;
	IArrayReal GetDesiredGlyphScaling( ) const;
	IArrayReal GetMaxGlyphScaling( ) const;
	IArrayReal GetMinGlyphScaling( ) const;
	IArrayParagraphJustification GetSingleWordJustification( ) const;
	IArrayReal GetAutoLeadingPercentage( ) const;
	IArrayLeadingType GetLeadingType( ) const;
	IArrayTabStopsRef GetTabStops( ) const;
	IArrayReal GetDefaultTabWidth( ) const;
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	IArrayBool GetHangingRoman( ) const;
	IArrayInteger GetAutoTCY( ) const;
	IArrayBool GetBunriKinshi( ) const;
	IArrayBurasagariType GetBurasagariType( ) const;
	IArrayPreferredKinsokuOrder GetPreferredKinsokuOrder( ) const;
	IArrayBool GetKurikaeshiMojiShori( ) const;
	IArrayKinsokuRef GetKinsoku( ) const;
	IArrayMojiKumiRef GetMojiKumi( ) const;
	// Other
	IArrayBool GetEveryLineComposer( ) const;

};

//////////////////////////////////////////////
//       --IParaStyle--
//////////////////////////////////////////////
class IParaStyle
{
private:
	ParaStyleRef	fParaStyle;
public:
	IParaStyle();
	IParaStyle(const IParaStyle& src);
	IParaStyle& operator=(const IParaStyle& rhs);
	bool operator==(const IParaStyle& rhs) const;
	bool operator!=(const IParaStyle& rhs) const;
	explicit IParaStyle(ParaStyleRef parastyle);
	virtual ~IParaStyle();
	ParaStyleRef GetRef() const;
	bool IsNull() const;

	/// Name of style is set in pName up to maxLength characters.
	/// Length of actual name is returned; 0 if error occurred.
	ASInt32 GetName( ASUnicode* pName, ASInt32 maxLength) const;
	/// Sets name of style to null-terminated pName.  If existing style of
	/// same name exists or *pName == L'\0' then false is returned.
	bool SetName( const ASUnicode* pName);
	/// Parent style returned.  For Normal style, a null object is returned.
	IParaStyle GetParent( ) const;
	/// Parent style set.  Returns false if attempting to set the parent
	/// of Normal style, true otherwise.
	bool SetParent( const IParaStyle pStyle);
	/// Returns whether style has parent.  Always false for normal style.
	bool HasParent( ) const;
	/// Returns features for style.
	IParaFeatures GetFeatures( ) const;
	/// The style's feature attributes are assigned to pFeatures.
	/// For Normal style, this has same effect as ReplaceOrAddFeatures.
	void SetFeatures( IParaFeatures pFeatures);
	/// The style's feature attributes are replaced by any corresponding ones
	/// in pFeatures that contain valid values (i.e. the attribute is assigned).
	void ReplaceOrAddFeatures( IParaFeatures pFeatures);

};

//////////////////////////////////////////////
//       --IParaStyles--
//////////////////////////////////////////////
class IParaStyles
{
private:
	ParaStylesRef	fParaStyles;
public:
	IParaStyles();
	IParaStyles(const IParaStyles& src);
	IParaStyles& operator=(const IParaStyles& rhs);
	bool operator==(const IParaStyles& rhs) const;
	bool operator!=(const IParaStyles& rhs) const;
	explicit IParaStyles(ParaStylesRef parastyles);
	virtual ~IParaStyles();
	ParaStylesRef GetRef() const;
	bool IsNull() const;

	bool IsEmpty( ) const;
	ASInt32 GetSize( ) const;
	void ShowAllStyles( ) const;
	void ShowOnlyUnreferencedStyles( ) const;
	void ShowOnlyStylesReferencedIn( ITextRange pRange) const;
	// Reorders position of style
	void MoveStyleTo( IParaStyle pStyle, ASInt32 position);

};

//////////////////////////////////////////////
//       --IParaStylesIterator--
//////////////////////////////////////////////
class IParaStylesIterator
{
private:
	ParaStylesIteratorRef	fParaStylesIterator;
public:
	IParaStylesIterator();
	IParaStylesIterator(const IParaStylesIterator& src);
	IParaStylesIterator& operator=(const IParaStylesIterator& rhs);
	bool operator==(const IParaStylesIterator& rhs) const;
	bool operator!=(const IParaStylesIterator& rhs) const;
	explicit IParaStylesIterator(ParaStylesIteratorRef parastylesiterator);
	virtual ~IParaStylesIterator();
	ParaStylesIteratorRef GetRef() const;
	bool IsNull() const;

	IParaStylesIterator( IParaStyles paraStyles, Direction direction = kForward);
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	void Previous( );
	IParaStyle Item( ) const;

};

//////////////////////////////////////////////
//       --ISpell--
//////////////////////////////////////////////
class ISpell
{
private:
	SpellRef	fSpell;
public:
	ISpell();
	ISpell(const ISpell& src);
	ISpell& operator=(const ISpell& rhs);
	bool operator==(const ISpell& rhs) const;
	bool operator!=(const ISpell& rhs) const;
	explicit ISpell(SpellRef spell);
	virtual ~ISpell();
	SpellRef GetRef() const;
	bool IsNull() const;

	// Options
	// ========================================================================
	void Initialize( const char* pSpellingDirectory);
	bool IsInitialized( );
	bool GetIgnoreWordsInAllUppercase( ) const;
	bool GetIgnoreWordsWithNumbers( ) const;
	bool GetIgnoreRomanNumerals( ) const;
	bool GetIgnoreRepeatedWords( ) const;
	bool GetIgnoreUncapitalizedStartOfSentence( ) const;
	void SetIgnoreWordsInAllUppercase( bool newValue);
	void SetIgnoreWordsWithNumbers( bool newValue);
	void SetIgnoreRomanNumerals( bool newValue);
	void SetIgnoreRepeatedWords( bool newValue);
	void SetIgnoreUncapitalizedStartOfSentence( bool newValue);
	// Control scope of search to be entire document or Story.
	// By default, the entire document is searched.
	SearchScope GetSearchScope( ) const;
	void SetSearchScope( SearchScope searchScope);
	// If called, search is done only within specified TextRange
	void SetSearchRange( const ITextRange& pRange, const bool resetEndOfSentence = true, const bool resetCurPos = true);
	// Temporary way to reset the engine for modeless operation
	void Reset( );
	// Use this if the user changes the text significantly enough that you need to reset,
	// but are fairly certain that the text hasn't been changed before the resumePoint.
	void ResumeFrom( const ASInt32 resumePoint);
	// Use this to resume from the current insertion point.
	void ResumeFromInsertionPoint( );
	// Methods
	// ========================================================================
	// Searches from start for unknown words and return the first one it finds.
	// Returns true if it found an unknown word, false if it searched to the end
	// and didn't find any unknown words.
	bool FindOneMisspelledWord( SpellCheckingResult* pResult, ITextRange pRange, Language* pLanguage = NULL);
	// Calling FindOneMisspelledWord( ) will fill up an internal list of suggested
	// corrections.  Use these calls to get the contents of that word list:
	//
	// This will return the size of the buffer required to hold the contents of the word list.
	ASInt32 GetWordListSize( );
	//
	// This will fill up pWordListBuffer with the contents of the list.
	// sizeOfBuffer is the size of pWordListBuffer (used to prevent overflow)
	// pNumberOfWords is the number of words in the buffer.  The words are all null-terminated.
	void GetWordListContents( ASUnicode*   pWordListBuffer, ASInt32    sizeOfBuffer, ASInt32*   pNumberOfWords);
	void Replace( ITextRange pRange, const ASUnicode* pCorrection);
	// Use this to add an entry to a pair dictionary, binding the selected word to rCorrection.
	void AddSelectedToReplaceAllDict( const ASUnicode* pCorrection);
	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
	bool DoReplaceAll( );
	// Use these to implement ReplaceAll.
	// Start by saving off the settings with GetPreReplaceAllSettings( )
	// (also note what text object you're currently working with so you can restore that
	// via SetSearchRange( ) when you're finished.
	void GetPreReplaceAllSettings( ASInt32* pCurrentPoint, bool* pFoundSentenceEnd) const;
	// Implement a loop to go through all the text objects you want to replace all with.
	// Use this to find all instances of the target word in the current text object.
	// Keep calling it until it returns false, making sure to set firstTimeInThisObject as needed.
	// It will return the text range to select and call ReplaceSelected( ) with.
	bool FindReplaceAllWord( ITextRange pRange, const bool firstTimeInThisObject);
	// When finished, restore the correct text object and range using SetSearchRange( )
	// and restore the positions using RestorePreReplaceAllSettings( )
	// Order is important here - do notcall RestorePreReplaceAllSettings( ) first,
	// as SetSearchRange( ) will reset the foundSentenceEnd flag.
	void RestorePreReplaceAllSettings( const ASInt32 currentPoint, const bool foundSentenceEnd);
	// The pair dictionary is not automatically cleared.  Call this when you want it cleared.
	void ClearPairDictionary( );
	// Use this for adding words as they're found.
	void AddSelectedToUserDict( );
	// User dictionary access and maintenance - used to manage the dictionary at any time.
	//
	// Calling GetUserDictionaryContents( ) will fill up the same internal list as FindAndSelectOneMisspelledWord( )
	// Use GetWordListSize( ) and GetWordListContents( ) just like with the suggestion list.
	void GetUserDictionaryContents( );
	// now makes sure that there are no spaces (multiple words)
	// Return value reflects success in adding legit word.
	bool AddToUserDictionary( const ASUnicode* pWord);
	void DeleteFromUserDictionary( const ASUnicode* pWord);
	bool WordExistsInUserDictionary( const ASUnicode* pWord);
	// The ignore list is used for storing "ignore all" words.
	void AddSelectedToIgnoreList( );
	// The ignore list is not automatically cleared.  Call this when you want it cleared.
	void ClearIgnoreList( );
	Language GetLanguageOfLastMissingDictionary( );

};

//////////////////////////////////////////////
//       --IStories--
//////////////////////////////////////////////
class IStories
{
private:
	StoriesRef	fStories;
public:
	IStories();
	IStories(const IStories& src);
	IStories& operator=(const IStories& rhs);
	bool operator==(const IStories& rhs) const;
	bool operator!=(const IStories& rhs) const;
	explicit IStories(StoriesRef stories);
	virtual ~IStories();
	StoriesRef GetRef() const;
	bool IsNull() const;

	ASInt32 GetSize( ) const;
	IStory GetFirst( );
	IStory GetLast( );
	/// Only one story might have the focus.  It is the one being edited by keyboard input.
	/// The current focused story might lose focus if multiselection happens outside the focused story, or
	/// a mouse click happens that makes the story lose focus ( like tool bar action ).
	bool HasFocus( ) const;
	/// Return the focused story, the one being edited.  If there is no text being edited, it will return
	/// a Null object, you can check the return using .IsNull() method.
	IStory GetFocus( ) const;
	/// changing focus will deselect everything in the document.
	void SetFocus( const IStory& story);
	void LoseFocus( );
	// navigation objects.
	ITextRanges GetTextRanges( ) const;
	ITextRanges GetTextSelection( ) const;
	IParagraphsIterator GetParagraphsIterator( ) const;
	IWordsIterator GetWordsIterator( ) const;
	ITextRunsIterator GetTextRunsIterator( ) const;
	IDocumentTextResources GetDocumentTextResources( ) const;
	// METHODS
	// ========================================================================
	IStory Item( ASInt32 nIndex) const;
	/* Suspend reflow calculation.  This will speed up ITextRange::InsertXXX() call or any call that
	causes a reflow to happen.*/
	void SuspendReflow( );
	/// Resume reflow calculation.  Make sure to match each SuspendReflow with ResumeReflow.
	void ResumeReflow( );
	// DOCUMENT METHODS
	// ========================================================================

};

//////////////////////////////////////////////
//       --IStory--
//////////////////////////////////////////////
class IStory
{
private:
	StoryRef	fStory;
public:
	IStory();
	IStory(const IStory& src);
	IStory& operator=(const IStory& rhs);
	bool operator==(const IStory& rhs) const;
	bool operator!=(const IStory& rhs) const;
	explicit IStory(StoryRef story);
	virtual ~IStory();
	StoryRef GetRef() const;
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	/// Get the index of this story from the stories array.
	ASInt32 GetIndex( ) const;
	/// Get how many characters in this story.
	ASInt32 GetSize( ) const;
	/// navigation objects.
	IStories GetStories( ) const;
	/// return the text range of this story (0, GetSize()).
	ITextRange GetTextRange( ) const;
	ITextRanges GetTextSelection( ) const;
	IParagraphsIterator GetParagraphsIterator( ) const;
	IWordsIterator GetWordsIterator( ) const;
	ITextRunsIterator GetTextRunsIterator( ) const;
	ITextFramesIterator GetTextFramesIterator( ) const;
	ITextFrame GetFrame( ASInt32 frameIndex) const;
	/// for auto or optical kerns
	void SetKernForSelection( const ITextRange& textRange, AutoKernType autoKernType);
	/// for manual kerns
	void SetKernAtChar( ASInt32 charIndex, ASInt32 value);
	void GetKern( const ITextRange& textRange, AutoKernType* pAutoKernType, ASInt32* value) const;
	AutoKernType GetModelKernAtChar( ASInt32 charIndex, ASInt32* pManualKernValue) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Get a text range from start to end.
	This function might change start and end if they are invalid.
	i.e, if either has negative values or exceeding Story.GetSize().
	*/
	ITextRange GetTextRange( ASInt32 start, ASInt32 end) const;
	IStory Duplicate( );
	/** Suspend reflow calculation.  This will speed up ITextRange::InsertXXX() call or any call that
	causes a reflow to happen.*/
	void SuspendReflow( );
	/** Resume reflow calculation.
	Make sure to match each SuspendReflow with ResumeReflow.  Or use IInhibitReflow instead of
	SuspendReflow() and ResumeReflow().
	*/
	void ResumeReflow( );

};

//////////////////////////////////////////////
//       --ITabStop--
//////////////////////////////////////////////
class ITabStop
{
private:
	TabStopRef	fTabStop;
public:
	ITabStop();
	ITabStop(const ITabStop& src);
	ITabStop& operator=(const ITabStop& rhs);
	bool operator==(const ITabStop& rhs) const;
	bool operator!=(const ITabStop& rhs) const;
	explicit ITabStop(TabStopRef tabstop);
	virtual ~ITabStop();
	TabStopRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// =======================================================================
	TabType GetTabType( ) const;
	void SetTabType( TabType tabType);
	ASReal GetPosition( ) const;
	void SetPosition( ASReal position);
	bool HasLeader( ) const;
	void GetLeader( ASUnicode* leader, ASInt32 maxLength) const;
	void SetLeader( ASUnicode* leader);
	ASUnicode GetDecimalCharacter( ) const;
	void SetDecimalCharacter( ASUnicode decimalChar);

};

//////////////////////////////////////////////
//       --ITabStops--
//////////////////////////////////////////////
class ITabStops
{
private:
	TabStopsRef	fTabStops;
public:
	ITabStops();
	ITabStops(const ITabStops& src);
	ITabStops& operator=(const ITabStops& rhs);
	bool operator==(const ITabStops& rhs) const;
	bool operator!=(const ITabStops& rhs) const;
	explicit ITabStops(TabStopsRef tabstops);
	virtual ~ITabStops();
	TabStopsRef GetRef() const;
	bool IsNull() const;

	// TabStops is a container class that stores an array of TabStop
	// instances.  Often, a client will receive a TabStops object when
	// asking about the tab stops of a selected paragraph.  In other
	// cases, they will wish to create their own Set of TabStops to
	// apply to a paragraph.
	//
	// Creates empty container
	// PROPERTIES
	// =======================================================================
	// Number of TabStop instances in container
	ASInt32 GetSize( ) const;
	// Returns first TabStop in container
	ITabStop GetFirst( ) const;
	// Returns last TabStop in container
	ITabStop GetLast( ) const;
	// METHODS
	// =======================================================================
	// Adds a TabStop or replaces an existing one in container.
	void ReplaceOrAdd( const ITabStop& pTabStop);
	// Requests TabStop by index.
	ITabStop Item( ASInt32 nIndex) const;
	// Removes TabStop by index.  No op if bad index passed in.
	void Remove( ASInt32 nIndex);
	// Empties container
	void RemoveAll( );
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

};

//////////////////////////////////////////////
//       --ITabStopsIterator--
//////////////////////////////////////////////
class ITabStopsIterator
{
private:
	TabStopsIteratorRef	fTabStopsIterator;
public:
	ITabStopsIterator();
	ITabStopsIterator(const ITabStopsIterator& src);
	ITabStopsIterator& operator=(const ITabStopsIterator& rhs);
	bool operator==(const ITabStopsIterator& rhs) const;
	bool operator!=(const ITabStopsIterator& rhs) const;
	explicit ITabStopsIterator(TabStopsIteratorRef tabstopsiterator);
	virtual ~ITabStopsIterator();
	TabStopsIteratorRef GetRef() const;
	bool IsNull() const;

	ITabStopsIterator( ITabStops tabStops, Direction direction = kForward);
	bool IsDone( ) const;
	bool IsNotDone( ) const;
	bool IsEmpty( );
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	ITabStop Item( ) const;

};

/**
	ITextRange is the basic and most important object you will use while manipulating ATE library.  
	ITextRange is basically an object that represent a range, start and an end, in a particular story.
	So, in order to change any attributes in a certain range in a particular story, you need access to ITextRange object.
	You can create ITextRange from almost anywhere in ATE objects, you can change it's start,end,story attributes 
	to point to different range in the same story or another story.  For example, if you have IStory, you can ask it
	to get the range of all the story or if you know a particular range you can set (start, end) values:-
	ITextRange myRange = myStory.GetTextRange(0,1);// this object now represent the first character in "myStory" object.
	If you are manipulating the contents of a text range, each time you do that, a reflow will happen and it might
	take some time for it to finish, so if you want to enhance performace, it is important to bracket you change between
	IStory::SuspendReflow and IStory::ResumeReflow APIs, or use the IInhibitReflow C++ class for it.  Functions that can cause reflow are:-
	InsertAfter, InsertBefore, Remove, SetLocalCharFeatures, ReplaceOrAddLocalCharFeatures, SetLocalParaFeatures
	ReplaceOrAddLocalParaFeatures.
*/
//////////////////////////////////////////////
//       --ITextRange--
//////////////////////////////////////////////
class ITextRange
{
private:
	TextRangeRef	fTextRange;
public:
	ITextRange();
	ITextRange(const ITextRange& src);
	ITextRange& operator=(const ITextRange& rhs);
	bool operator==(const ITextRange& rhs) const;
	bool operator!=(const ITextRange& rhs) const;
	explicit ITextRange(TextRangeRef textrange);
	virtual ~ITextRange();
	TextRangeRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// ========================================================================
	ASInt32 GetStart( ) const;
	void SetStart( ASInt32 start);
	ASInt32 GetEnd( ) const;
	void SetEnd( ASInt32 end);
	ASInt32 GetSize( ) const;
	// NAVIGATION OBJECTS
	// ========================================================================
	IStory GetStory( ) const;
	ITextRanges GetTextSelection( ) const;
	ITextFramesIterator GetTextFramesIterator( ) const;
	IParagraphsIterator GetParagraphsIterator( ) const;
	IWordsIterator GetWordsIterator( ) const;
	ITextRunsIterator GetTextRunsIterator( ) const;
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	ICharInspector GetCharInspector( ) const;
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	IParaInspector GetParaInspector( ) const;
	/// Returns list of named styles used in the TextRange
	ICharStyles GetNamedCharStyles( ) const;
	/// Returns list of named styles used in the TextRange
	IParaStyles GetNamedParaStyles( ) const;
	/// Set the named style referred to by pName in the TextRange.  Returns
	/// false if style not found.
	bool SetNamedCharStyle( const ASUnicode* pName );
	/// Set the named style referred to by pName in the TextRange.  Returns
	/// false if style not found.
	bool SetNamedParaStyle( const ASUnicode* pName);
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	void ClearNamedCharStyle( );
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	void ClearNamedParaStyle( );
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used in the TextRange.
	///
	/// Hence, GetUniqueCharFeatures returns CharFeatures
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	ICharFeatures GetUniqueCharFeatures( ) const;
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used in the TextRange.
	///
	/// Hence, GetUniqueParaFeatures returns ParaFeatures
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	IParaFeatures GetUniqueParaFeatures( ) const;
	/// If true, then local overrides are present.  If false, then none exist.
	bool HasLocalCharFeatures( );
	/// If true, then local overrides are present.  If false, then none exist.
	bool HasLocalParaFeatures( );
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout all the text runs
	/// in the TextRange.
	///
	/// Hence, GetUniqueLocalCharFeatures returns CharFeatures
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) across all text runs are valid.
	///
	/// An empty CharFeatures (every attribute is "invalid") indicates
	/// either the text range has no local overrides or that no common
	/// attribute values existed for the local overrides.
	ICharFeatures GetUniqueLocalCharFeatures( );
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout all the text runs
	/// in the TextRange.
	///
	/// Hence, GetUniqueLocalParaFeatures returns ParaFeatures
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) across all text runs are valid.
	///
	/// An empty ParaFeatures (every attribute is "invalid") indicates
	/// either the text range has no local overrides or that no common
	/// attribute values existed for the local overrides.
	IParaFeatures GetUniqueLocalParaFeatures( );
	/// Local overrides are specified via CharFeatures.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named CharStyle (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocalCharFeatures( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocalCharFeatures( ).
	void SetLocalCharFeatures( const ICharFeatures& pFeatures );
	void ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures );
	void ClearLocalCharFeatures( );
	/// Local overrides are specified via ParaFeatures.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named ParaStyle (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocalParaFeatures( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocalPara}Features( ).
	void SetLocalParaFeatures( const IParaFeatures& pFeatures);
	void ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures);
	void ClearLocalParaFeatures( );
	// METHODS
	// ========================================================================
	void SetStory( const IStory& story);
	void SetRange( ASInt32 start, ASInt32 end);
	/// start and end of this range will change depending on direction
	/// if direction = CollapseEnd, then end = start
	/// if direction = CollapseStart, then start = end
	void Collapse( CollapseDirection direction = CollapseEnd);
	/// Translate start and end by 'unit'.
	/// a Move(3), will make this range start+3, end+3, pending story limits.  i.e start and end will never be out of bounds.
	/// The return of this method will be equal to 'unit' unless it is out of bounds, in that case, return is zero.
	ASInt32 Move( ASInt32 unit);
	/// This method will make a copy of this range.
	ITextRange Clone( ) const;
	/// Insert 'text' before the start of the range.
	/// If length is -1, then parameter "text" should be null terminated, otherwise length should indicate strlen(text)
	void InsertBefore( const char* text, ASInt32 length = -1, IFont insertionFont = IFont());
	/// Insert 'text' after the end of the range.
	/// If length is -1, then parameter "text" should be null terminated, otherwise length should indicate strlen(text)
	void InsertAfter( const char* text, ASInt32 length = -1, IFont insertionFont = IFont());
	/// Insert 'text' before the start of the range.
	void InsertBefore( const ASUnicode* text, ASInt32 length = -1 );
	/// Insert 'text' after the end of the range.
	void InsertAfter( const ASUnicode* text, ASInt32 length = -1 );
	/// Insert 'anotherRange' before the start of the range.
	void InsertBefore( const ITextRange& anotherRange);
	/// Insert 'anotherRange' after the end of the range.
	void InsertAfter( const ITextRange& anotherRange);
	/** Gets the contents of this range as unicode.
	Return value is number of characters.
	*/
	ASInt32 GetContents( ASUnicode* text, ASInt32 maxLength) const;
	/** Gets the contents of this range as platform codes.  Internally things are
	stored in unicode, so a conversion will happen data might get lost.
	Return value is number of characters.
	*/
	ASInt32 GetContents( char* text, ASInt32 maxLength) const;
	bool GetSingleGlyphInRange( ATEGlyphID* pSingleGlyph) const;
	/// This method will select this range.
	/// if addToSelection is true, it will add this range to the current document selection.
	/// if addToSelection is false, it will clear the selection from the document and only select this range.
	void Select( bool addToSelection = false);
	/// This method will remove this range from the selection.
	/// Note, deselecting a range can cause defregmented selection, if this range is a sub range of the current selection.
	void DeSelect( );
	void ChangeCase( CaseChangeType caseChangeType);
	void FitHeadlines( );
	/// This method will delete all the characters in that range.
	void Remove( );
	/// This Range has to be of size equal to 1, any other size will throw error (kBadParameter)
	ASCharType GetCharacterType( ) const;

};

//////////////////////////////////////////////
//       --ITextRanges--
//////////////////////////////////////////////
class ITextRanges
{
private:
	TextRangesRef	fTextRanges;
public:
	ITextRanges();
	ITextRanges(const ITextRanges& src);
	ITextRanges& operator=(const ITextRanges& rhs);
	bool operator==(const ITextRanges& rhs) const;
	bool operator!=(const ITextRanges& rhs) const;
	explicit ITextRanges(TextRangesRef textranges);
	virtual ~ITextRanges();
	TextRangesRef GetRef() const;
	bool IsNull() const;

	// PROPERTIES
	// ======================================================================
	ASInt32 GetSize( ) const;
	ITextRange GetFirst( ) const;
	ITextRange GetLast( ) const;
	// navigation objects.
	ITextRanges GetTextSelection( ) const;
	IParagraphsIterator GetParagraphsIterator( ) const;
	IWordsIterator GetWordsIterator( ) const;
	ITextRunsIterator GetTextRunsIterator( ) const;
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	ICharInspector GetCharInspector( ) const;
	IParaInspector GetParaInspector( ) const;
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	void ClearNamedCharStyle( );
	void ClearNamedParaStyle( );
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used across each TextRange in the
	/// TextRanges object.
	///
	/// Hence, GetUnique{Char,Para}Features returns {Char,Para}Features
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	ICharFeatures GetUniqueCharFeatures( ) const;
	IParaFeatures GetUniqueParaFeatures( ) const;
	/// If true, then local overrides are present.  If false, then none exist.
	bool HasLocalCharFeatures( );
	bool HasLocalParaFeatures( );
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout each TextRange
	/// in the TextRanges object.
	///
	/// Hence, GetUniqueLocal{Char,Para}Features returns {Char,Para}Features
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) for all text runs are valid.
	///
	/// An empty {Char,Para}Features (every attribute is "invalid") indicates
	/// either no local overrides exist in any of the TextRange objects
	/// or that no common attribute values existed for the local overrides.
	ICharFeatures GetUniqueLocalCharFeatures( );
	IParaFeatures GetUniqueLocalParaFeatures( );
	/// Local overrides are specified via {Char,Para}Features.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named {Char,Para}Style (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocal{Char,Para}Features( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocal{Char,Para}Features( ).
	void SetLocalCharFeatures( const ICharFeatures& pFeatures );
	void ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures );
	void ClearLocalCharFeatures( );
	void SetLocalParaFeatures( const IParaFeatures& pFeatures);
	void ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures);
	void ClearLocalParaFeatures( );
	// METHODS
	// ======================================================================
	/// This method will select those ranges.
	/// if addToSelection is true, it will add those ranges to the current document selection.
	/// if addToSelection is false, it will clear the selection from the document and only select those ranges.
	void Select( bool addToSelection = false);
	/// This method will remove those ranges from the selection.
	/// Note, deselecting ranges can cause defregmented selection.
	void DeSelect( );
	ASInt32 GetContents( ASUnicode* text, ASInt32 maxLength) const;
	ASInt32 GetContents( char* text, ASInt32 maxLength) const;
	void ChangeCase( CaseChangeType caseChangeType);
	void Add( const ITextRange& textRange);
	ITextRange Item( ASInt32 nIndex) const;
	void RemoveAll( );
	void Remove( ASInt32 nIndex);

};

//////////////////////////////////////////////
//       --ITextRangesIterator--
//////////////////////////////////////////////
class ITextRangesIterator
{
private:
	TextRangesIteratorRef	fTextRangesIterator;
public:
	ITextRangesIterator();
	ITextRangesIterator(const ITextRangesIterator& src);
	ITextRangesIterator& operator=(const ITextRangesIterator& rhs);
	bool operator==(const ITextRangesIterator& rhs) const;
	bool operator!=(const ITextRangesIterator& rhs) const;
	explicit ITextRangesIterator(TextRangesIteratorRef textrangesiterator);
	virtual ~ITextRangesIterator();
	TextRangesIteratorRef GetRef() const;
	bool IsNull() const;

	ITextRangesIterator( ITextRanges textRanges, Direction direction = kForward);
	ITextRangesIterator Clone( ) const;
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	ITextRange Item( ) const;

};

//////////////////////////////////////////////
//       --ITextRunsIterator--
//////////////////////////////////////////////
class ITextRunsIterator
{
private:
	TextRunsIteratorRef	fTextRunsIterator;
public:
	ITextRunsIterator();
	ITextRunsIterator(const ITextRunsIterator& src);
	ITextRunsIterator& operator=(const ITextRunsIterator& rhs);
	bool operator==(const ITextRunsIterator& rhs) const;
	bool operator!=(const ITextRunsIterator& rhs) const;
	explicit ITextRunsIterator(TextRunsIteratorRef textrunsiterator);
	virtual ~ITextRunsIterator();
	TextRunsIteratorRef GetRef() const;
	bool IsNull() const;

	/// A TextRun is a range of text whose character attributes are the same.
	/// Insertions and deletions into a story can invalidate the entire iterator.
	ITextRunsIterator( const ITextRanges& ranges, Direction direction = kForward);
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	/// The next run will be the one following (or preceding, depending on
	/// the iterator's direction) the run returned by Item( ).  Since Item( )
	/// is affected by attribute modifications to text, so is Next( ).
	void Next( );
	/// The range returned by Item( ) may differ from a preceding call if
	/// character attributes are modified in the story that the run is a
	/// part of.  For forward iteration, the new run will begin at or
	/// before the old run.  Similar for backwards iteration.
	ITextRange Item( ) const;

};

//////////////////////////////////////////////
//       --IWordsIterator--
//////////////////////////////////////////////
class IWordsIterator
{
private:
	WordsIteratorRef	fWordsIterator;
public:
	IWordsIterator();
	IWordsIterator(const IWordsIterator& src);
	IWordsIterator& operator=(const IWordsIterator& rhs);
	bool operator==(const IWordsIterator& rhs) const;
	bool operator!=(const IWordsIterator& rhs) const;
	explicit IWordsIterator(WordsIteratorRef wordsiterator);
	virtual ~IWordsIterator();
	WordsIteratorRef GetRef() const;
	bool IsNull() const;

	IWordsIterator( const ITextRanges& ranges, Direction direction = kForward);
	bool IsNotDone( ) const;
	bool IsDone( ) const;
	bool IsEmpty( ) const;
	void MoveToFirst( );
	void MoveToLast( );
	void Next( );
	// The next word corresponds to performing a control/command + arrow key
	// action from the UI.  Hence, each TextRange returned includes trailing
	// characters.  This also implies that (among other things) "..." is considered
	// a word.
	ITextRange Item( ) const;
	// NOTE: Trailing information is always for the current word
	// returned by Item( ).  It always gives you the counts for
	// characters that come after (i.e. trailing) the word
	// (regardless of the direction of iteration)
	//
	// The total number of trailing characters is given by GetTrailingCount( )
	ASInt32 GetTrailingSpaceCount( ) const;
	ASInt32 GetTrailingCount( ) const;
	ASInt32 GetTrailingTerminatingPunctuationCount( ) const;

};


class IInhibitReflow
{
public:
   IInhibitReflow()
   {
   }
   IInhibitReflow(const IStory& story)
   :fStory(story)
   {
       fStory.SuspendReflow();
   }
   IInhibitReflow(const IInhibitReflow& reflow)
   :fStory(reflow.fStory)
   {
       fStory.SuspendReflow();
   }
   virtual ~IInhibitReflow()
   {
       if(!fStory.IsNull())
           fStory.ResumeReflow();
   }
   IInhibitReflow& operator=(const IInhibitReflow& rhs)
   {
       this->~IInhibitReflow( );
       fStory = rhs.fStory;
       if(!fStory.IsNull())
          fStory.SuspendReflow();
       return *this;
   }
protected:
   IStory    fStory;
};
}// namespace ATE

