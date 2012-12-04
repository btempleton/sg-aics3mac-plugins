//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsPreferences.hpp $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __MarkedObjectsPreferences_hpp__
#define __MarkedObjectsPreferences_hpp__

#include "MarkedObjectsPlugin.hpp"

class MarkedObjectsDialog;

class MarkedObjectsPreferencesDialog : public BaseADMDialog
{
private:
	ASRealPoint					subLoc;
	string						subFontName;
	AIReal						subFontSize;
	
	ASRealPoint					labelLoc;
	string						labelFontName;
	AIReal						labelFontSize;
	string						labelDefaultText;
	long						precision;
	AIBoolean					autoSort;
	
public:
	MarkedObjectsPreferencesDialog();
	virtual ~MarkedObjectsPreferencesDialog();
	
	int Modal(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style = kADMModalDialogStyle, int options = 0);

	ASErr Init();
	void Notify( IADMNotifier notifier );
	void Destroy();

	ASRealPoint	GetSubStringLocation( void ) { return subLoc; }
	const string GetSubStringFontName( void )	{ return subFontName; }
	AIReal GetSubStringFontSize( void )	{ return subFontSize; }

	ASRealPoint	GetLabelStringLocation( void ) { return labelLoc; }
	const string GetLabelStringFontName( void ) { return labelFontName; }
	AIReal GetLabelStringFontSize( void ) { return labelFontSize; }
	const string GetLabelStringDefaultText( void ) { return labelDefaultText; }
	
	void SetSubStringLocation( ASRealPoint inPoint ) { subLoc = inPoint; }
	void SetSubStringFontName( const string fontName ) { subFontName = fontName; }
	void SetSubStringFontSize( AIReal fontSize ) { subFontSize = fontSize; }

	void SetLabelStringLocation( ASRealPoint inPoint ) { labelLoc = inPoint; }
	void SetLabelStringFontName( const string fontName ) { labelFontName = fontName; }
	void SetLabelStringFontSize( AIReal fontSize ) { labelFontSize = fontSize; }
	void SetLabelStringDefaultText( const string newText ) { labelDefaultText = newText; }

	void SetPrecision( long p ) { precision = p; }
	long GetPrecision( void ) { return precision; }

	void SetAutoSort( AIBoolean as ) { autoSort = as; }
	AIBoolean GetAutoSort( void ) { return autoSort; }

};

class MarkedObjectsPreferences
{
private:
	MarkedObjectsDialog* 		moDialog;
	
	ASRealPoint					subLoc;
	string						subFontName;
	AIReal						subFontSize;
	
	ASRealPoint					labelLoc;
	string						labelFontName;
	AIReal						labelFontSize;
	string						labelDefaultText;
	long						precision;
	AIBoolean					autoSort;
		
public:
	MarkedObjectsPreferences();
	~MarkedObjectsPreferences();
	
	void SetDialogPreferences( MarkedObjectsDialog* dp );
	
	int DoModalPrefs( void );
	
	ASRealPoint	GetSubStringLocation( void ) { return subLoc; }
	const string GetSubStringFontName( void )	{ return subFontName; }
	AIReal GetSubStringFontSize( void )	{ return subFontSize; }

	ASRealPoint	GetLabelStringLocation( void ) { return labelLoc; }
	const string GetLabelStringFontName( void ) { return labelFontName; }
	AIReal GetLabelStringFontSize( void ) { return labelFontSize; }
	const string GetLabelStringDefaultText( void ) { return labelDefaultText; }
	
	void SetSubStringLocation( ASRealPoint inPoint ) { subLoc = inPoint; }
	void SetSubStringFontName( const string fontName ) { subFontName = fontName; }
	void SetSubStringFontSize( AIReal fontSize ) { subFontSize = fontSize; }

	void SetLabelStringLocation( ASRealPoint inPoint ) { labelLoc = inPoint; }
	void SetLabelStringFontName( const string fontName ) { labelFontName = fontName; }
	void SetLabelStringFontSize( AIReal fontSize ) { labelFontSize = fontSize; }
	void SetLabelStringDefaultText( const string newText ) { labelDefaultText = newText; }	

	void SetPrecision( long p ) { precision = p; }
	long GetPrecision( void ) { return precision; }

	void SetAutoSort( AIBoolean as ) { autoSort = as; }
	AIBoolean GetAutoSort( void ) { return autoSort; }
};

extern MarkedObjectsPreferences* gPreferences;

#endif
// end MarkedObjectsPreferences.hpp