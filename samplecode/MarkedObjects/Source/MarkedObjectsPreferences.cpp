//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/MarkedObjects/Source/MarkedObjectsPreferences.cpp $
//
//  $Revision: #9 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#include "MarkedObjectsPreferences.hpp"

static char* kStringPreference = "MarkedObjects";

static char* kMarkedObjects_DPDockCodeStr = "kMarkedObjects_DPDockCodeStr";
static char* kMarkedObjects_DPDockGroupStr = "kMarkedObjects_DPDockGroupStr";
static char* kMarkedObjects_DPLocationStr = "kMarkedObjects_DPLocationStr";
static char* kMarkedObjects_DPSizeStr = "kMarkedObjects_DPSizeStr";
static char* kMarkedObjects_DPVisibleStr = "kMarkedObjects_DPVisibleStr";

static char* kMarkedObjects_SubLocationXStr = "kMarkedObjects_SubLocationXStr";
static char* kMarkedObjects_SubLocationYStr = "kMarkedObjects_SubLocationYStr";
static char* kMarkedObjects_SubFontNameStr = "kMarkedObjects_SubFontNameStr";
static char* kMarkedObjects_SubFontSizeStr = "kMarkedObjects_SubFontSizeStr";

static char* kMarkedObjects_DefLocationXStr = "kMarkedObjects_DefLocationXStr";
static char* kMarkedObjects_DefLocationYStr = "kMarkedObjects_DefLocationYStr";
static char* kMarkedObjects_DefFontNameStr = "kMarkedObjects_DefFontNameStr";
static char* kMarkedObjects_DefFontSizeStr = "kMarkedObjects_DefFontSizeStr";
static char* kMarkedObjects_DefTextStr = "kMarkedObjects_DefTextStr";

static char* kMarkedObjects_PrecisionStr = "kMarkedObjects_PrecisionStr";
static char* kMarkedObjects_AutoSortStr = "kMarkedObjects_AutoSortStr";

const int kOK					= 1;
const int kCancelButton			= 2;
const int kSubFontSizeStr		= 3;
const int kSubFontSizeText		= 4;
const int kSubFontNameStr		= 5;
const int kSubFontNamePopup		= 6;
const int kSubLocXStr			= 7;
const int kSubLocXText			= 8;
const int kSubLocYStr			= 9;
const int kSubLocYText			= 10;
const int kDefFontSizeStr		= 11;
const int kDefFontSizeText		= 12;
const int kDefFontNameStr		= 13;
const int kDefFontNamePopup		= 14;
const int kDefLocXStr			= 15;
const int kDefLocXText			= 16;
const int kDefLocYStr			= 17;
const int kDefLocYText			= 18;
const int kDefTextStr			= 19;
const int kDefTextText			= 20;
const int kSubscriptBorderStr	= 21;
const int kSubscriptBorder		= 22;
const int kDefTextBorderStr		= 23;
const int kDefTextBorder 		= 24;
const int kPrecStr				= 25;
const int kPrecText				= 26;
const int kAutoSort				= 27;
const int kFontDumpButton		= 28;
const int kLastItem				= 28;

const int kID_PreferenceDialog 	= 16500;

int GetFullPathToDesktop(char * fullPath, int32 maxPathLength);

MarkedObjectsPreferences* gPreferences = NULL;

MarkedObjectsPreferences::MarkedObjectsPreferences() : moDialog(NULL)
{
	subLoc.h = 6;
	subLoc.v = -6;
	subFontName = "ArialMT";
	subFontSize = 7;
	
	labelLoc.h = 20;
	labelLoc.v = -4;
	labelFontName = "ArialMT";
	labelFontSize = 10;
	labelDefaultText = "Default Text";

	precision = 0;
	autoSort = true;

	gPreferences = this;

	char tempChar[1024];

	// these *()^*&^ routines don't return a value if the preference is not there, very nice
	double value = subLoc.h;

	AIErr error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_SubLocationXStr, &value );
	if ( error == kNoErr ) subLoc.h = (ASReal)value;

	value = subLoc.v;
	error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_SubLocationYStr, &value );
	if ( error == kNoErr ) subLoc.v = (ASReal)value;

	memset(tempChar, 0, 1024);
	strcpy( tempChar, subFontName.c_str() );
	error = sAIPreference->GetStringPreference( kStringPreference, kMarkedObjects_SubFontNameStr, tempChar );
	if ( error == kNoErr ) subFontName.assign( tempChar, tempChar + strlen( tempChar ) );

	value = subFontSize;
	error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_SubFontSizeStr, &value );
	if ( error == kNoErr ) subFontSize = (AIReal)value;

	value = labelLoc.h;
	error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_DefLocationXStr, &value );
	if ( error == kNoErr ) labelLoc.h = (ASReal)value;

	value = labelLoc.v;
	error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_DefLocationYStr, &value );
	if ( error == kNoErr ) labelLoc.v = (ASReal)value;

	memset(tempChar, 0, 1024);
	strcpy( tempChar, labelFontName.c_str() );
	error = sAIPreference->GetStringPreference( kStringPreference, kMarkedObjects_DefFontNameStr, tempChar );
	if ( error == kNoErr ) labelFontName.assign( tempChar, tempChar + strlen( tempChar ) );

	value = labelFontSize;
	error = sAIPreference->GetRealPreference( kStringPreference, kMarkedObjects_DefFontSizeStr, &value );
	if ( error == kNoErr ) labelFontSize = (AIReal)value;

	memset(tempChar, 0, 1024);
	strcpy( tempChar, labelDefaultText.c_str() );
	error = sAIPreference->GetStringPreference( kStringPreference, kMarkedObjects_DefTextStr, tempChar );
	if ( error == kNoErr ) labelDefaultText.assign( tempChar, tempChar + strlen( tempChar ) );
	
	error = sAIPreference->GetIntegerPreference( kStringPreference, kMarkedObjects_PrecisionStr, &precision );

	error = sAIPreference->GetBooleanPreference( kStringPreference, kMarkedObjects_AutoSortStr, &autoSort );

}

MarkedObjectsPreferences::~MarkedObjectsPreferences()
{
	if ( moDialog != NULL && sAIPreference != NULL && sADMDialogGroup != NULL )
	{
		// for the dialog layout
		char *groupName;
		long positionCode;
		sADMDialogGroup->GetDialogGroupInfo( moDialog->GetDialog(), (const char **)&groupName, &positionCode );
		
		IADMPoint location, size;
		IADMRect boundsRect;
		moDialog->GetBoundsRect( boundsRect );
		
		location.h = boundsRect.left;
		location.v = boundsRect.top;
		size.h = boundsRect.Width();
		size.v = boundsRect.Height();

		sAIPreference->PutIntegerPreference( kStringPreference, kMarkedObjects_DPDockCodeStr, positionCode );
		sAIPreference->PutStringPreference( kStringPreference, kMarkedObjects_DPDockGroupStr, groupName );
		sAIPreference->PutPointPreference( kStringPreference, kMarkedObjects_DPLocationStr, &location );
		sAIPreference->PutPointPreference( kStringPreference, kMarkedObjects_DPSizeStr, &size );
		sAIPreference->PutBooleanPreference( kStringPreference, kMarkedObjects_DPVisibleStr, moDialog->IsVisible() );
		
		// for the marked object, font information, offsets, and size
		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_SubLocationXStr, subLoc.h );
		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_SubLocationYStr, subLoc.v );
		sAIPreference->PutStringPreference( kStringPreference, kMarkedObjects_SubFontNameStr, subFontName.c_str() );
		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_SubFontSizeStr, subFontSize );

		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_DefLocationXStr, labelLoc.h );
		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_DefLocationYStr, labelLoc.v );
		sAIPreference->PutStringPreference( kStringPreference, kMarkedObjects_DefFontNameStr, labelFontName.c_str() );
		sAIPreference->PutRealPreference( kStringPreference, kMarkedObjects_DefFontSizeStr, labelFontSize );
		sAIPreference->PutStringPreference( kStringPreference, kMarkedObjects_DefTextStr, labelDefaultText.c_str() );

		sAIPreference->PutIntegerPreference( kStringPreference, kMarkedObjects_PrecisionStr, precision );
		sAIPreference->PutBooleanPreference( kStringPreference, kMarkedObjects_AutoSortStr, autoSort );
	}
	
	gPreferences = NULL;
}

void MarkedObjectsPreferences::SetDialogPreferences( MarkedObjectsDialog* dp )
{
	if ( dp == NULL ) return;
	
	moDialog = dp;
	
	// init the location of the dialog box
	char groupName[64] = "SDK Dialogs";
	sAIPreference->GetStringPreference( kStringPreference, kMarkedObjects_DPDockGroupStr, groupName );

	long positionCode = 0x00001c00;
	sAIPreference->GetIntegerPreference( kStringPreference, kMarkedObjects_DPDockCodeStr, &positionCode );
	
	IADMRect boundsRect;
	moDialog->GetBoundsRect( boundsRect );
	
	ADMRect dimensions;
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	ADMPoint location;
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);
	
	sAIPreference->GetPointPreference( kStringPreference, kMarkedObjects_DPLocationStr, &location );
	
	ADMPoint size;
	size.v = boundsRect.bottom - boundsRect.top;
	size.h = boundsRect.right - boundsRect.left;
	
	moDialog->SetMinHeight(size.v);
	moDialog->SetMinWidth(size.h);

#ifdef WIN32
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif

	sAIPreference->GetPointPreference( kStringPreference, kMarkedObjects_DPSizeStr, &size );

	IADMRect rect;
	rect.left = location.h;
	rect.right = location.h + size.h;
	rect.top = location.v;
	rect.bottom = location.v + size.v;

	// restore the size and location of the moDialog
	moDialog->SetBoundsRect( rect );

	// restore the position code of the moDialog
	sADMDialogGroup->SetDialogGroupInfo( moDialog->GetDialog(), groupName, positionCode );

}

int MarkedObjectsPreferences::DoModalPrefs( void )
{
	MarkedObjectsPreferencesDialog prefDialog;
	
	prefDialog.SetSubStringLocation( GetSubStringLocation() );
	prefDialog.SetSubStringFontName( GetSubStringFontName() );
	prefDialog.SetSubStringFontSize( GetSubStringFontSize() );

	prefDialog.SetLabelStringLocation( GetLabelStringLocation() );
	prefDialog.SetLabelStringFontName( GetLabelStringFontName() );
	prefDialog.SetLabelStringFontSize( GetLabelStringFontSize() );
	prefDialog.SetLabelStringDefaultText( GetLabelStringDefaultText() );

	prefDialog.SetPrecision( GetPrecision() );
	prefDialog.SetAutoSort( GetAutoSort() );

	int returnValue = prefDialog.Modal( gPlugin->GetPluginRef(), "Tommy", kID_PreferenceDialog);

	if ( returnValue == kOK )
	{
		SetSubStringLocation( prefDialog.GetSubStringLocation() );
		SetSubStringFontName( prefDialog.GetSubStringFontName() );
		SetSubStringFontSize( prefDialog.GetSubStringFontSize() );

		SetLabelStringLocation( prefDialog.GetLabelStringLocation() );
		SetLabelStringFontName( prefDialog.GetLabelStringFontName() );
		SetLabelStringFontSize( prefDialog.GetLabelStringFontSize() );
		SetLabelStringDefaultText( prefDialog.GetLabelStringDefaultText() );

		SetPrecision( prefDialog.GetPrecision() );
		SetAutoSort( prefDialog.GetAutoSort() );
	}

	return returnValue;
}

MarkedObjectsPreferencesDialog::MarkedObjectsPreferencesDialog()
{
	subLoc.h = 6;
	subLoc.v = -6;
	subFontName = "ArialMT";
	subFontSize = 7;
	
	labelLoc.h = 20;
	labelLoc.v = -4;
	labelFontName = "ArialMT";
	labelFontSize = 10;
	labelDefaultText = "Default Text";

	precision = 0;
	autoSort = true;
}

MarkedObjectsPreferencesDialog::~MarkedObjectsPreferencesDialog()
{
}
	
int MarkedObjectsPreferencesDialog::Modal( SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style, int options )
{
	return BaseADMDialog::Modal( pluginRef, name, dialogID, style, options );
}

ASErr MarkedObjectsPreferencesDialog::Init()
{
	ASErr error = kNoErr;
	
	IADMItem item;
	ASRealPoint location;
	
	long i;
	// make all the items use the palette font and no units
	for (i = 1; i <= kLastItem; i++)
	{
		item = GetItem( i );
		
		if ( i == kSubFontSizeText || i == kSubLocXText || i == kSubLocYText ||
			 i == kDefFontSizeText || i == kDefLocXText || i == kDefLocYText ||
			 i == kPrecText)
			 item.SetUnits( kADMNoUnits );
		
		item.SetFont( kADMPaletteFont );
		
		switch ( i )
		{
			case kSubFontSizeText:
				item.SetFloatValue( GetSubStringFontSize() );
				break;

			case kSubFontNamePopup:
				item.SetText( GetSubStringFontName().c_str() );
				break;
				
			case kSubLocXText:
				location = GetSubStringLocation();
				item.SetFloatValue( location.h );
				break;
	
			case kSubLocYText:
				location = GetSubStringLocation();
				item.SetFloatValue( location.v );
				break;
	
			case kDefFontSizeText:
				item.SetFloatValue( GetLabelStringFontSize() );
				break;
				
			case kDefFontNamePopup:
				item.SetText( GetLabelStringFontName().c_str() );
				break;
				
			case kDefLocXText:
				location = GetLabelStringLocation();
				item.SetFloatValue( location.h );
				break;
				
			case kDefLocYText:
				location = GetLabelStringLocation();
				item.SetFloatValue( location.v );
				break;
				
			case kDefTextText:
				item.SetText( GetLabelStringDefaultText().c_str() );
				break;

			case kPrecText:
				item.SetIntValue( GetPrecision() );
				break;

			case kAutoSort:
				item.SetBooleanValue( GetAutoSort() );
				break;
				
			default:
				break;
		}
	}
#if 0 // shut off the pop up menu
	item = GetItem( kSubFontNamePopup );
	IADMList subList = item.GetList();
	item = GetItem( kDefFontNamePopup );
	IADMList labelList = item.GetList();

#if 0
	long count = 0;
	if ( !error )
		error = sAIFont->CountFonts( &count );
	
	string lastFontName;
	
	int entries = 1;

	for ( i = 0; i < count && !error && entries < 40; i++ )
	{
		AIFontKey fontKey;
		const int tempLength = 1024;
		char temp[tempLength];
		memset(temp, 0, tempLength);
		error = sAIFont->IndexFontList( i, &fontKey );
		if ( !error )
			error = sAIFont->GetPostScriptFontName( fontKey, temp, tempLength );
		string fontName;
		fontName.assign( temp, temp + strlen( temp ) );
		if (fontName.compare( lastFontName ) != 0 && fontName.find( "-" ) == basic_string<char>::npos )
		{
			lastFontName = fontName;
			IADMEntry entry( subList.InsertEntry( entries ) );
			entry.SetText( fontName.c_str() );
			if ( fontName.compare( GetSubStringFontName() ) == 0 )
				entry.Select();
			entry = labelList.InsertEntry( entries );
			entry.SetText( fontName.c_str() );
			if ( fontName.compare( GetLabelStringFontName() ) == 0 )
				entry.Select();
			entries++;
		}
	}
#else
	int c = subList.NumberOfEntries();
	while (c--)
		subList.RemoveEntry(c);

	c = labelList.NumberOfEntries();
	while (c--)
		labelList.RemoveEntry(c);

	IADMEntry entry( subList.InsertEntry( 0 ));
	entry.SetText( GetSubStringFontName().c_str() );
	entry.Select();
	entry = labelList.InsertEntry( 0 );
	entry.SetText( GetLabelStringFontName().c_str() );
	entry.Select();
#endif
#endif

	// if the alt key is down show this button
	item = GetItem(kFontDumpButton);

	bool altDown = false;
	
	#if WIN32
		short ks = GetAsyncKeyState( VK_MENU );
		altDown = ( 0x8000 & ks ? true : false );
	#elif Macintosh
		static const unsigned short kOptionCode = 0x3A;
		KeyMap theKeys;
		GetKeys( theKeys );
		unsigned char *km = (unsigned char *)theKeys;
		altDown = (((km[kOptionCode>>3] >> (kOptionCode & 7)) & 1) ? true : false);
	#endif

	if ( altDown )
	{
		item.Show();
		item.Enable();
	}
	else
	{
		item.Hide();
		item.Disable();
	}

	// do this last thing
	error = BaseADMDialog::Init();
	
	return error;
}

void MarkedObjectsPreferencesDialog::Notify( IADMNotifier notifier )
{
	if (notifier.IsNotifierType(kADMUserChangedNotifier))
	{
		IADMItem item ( notifier.GetItem() );	
		if ( item.GetID() == kFontDumpButton )
		{
			char logfilename[256];
			char * filename = "IllustratorFontList.log";
			int error = GetFullPathToDesktop( logfilename, 256 );
			if (!error)
			{
				strcat( logfilename, filename );

				ofstream fileOut(logfilename , ios_base::app|ios_base::out);

				fileOut << "Name, PostScript Name, Family, Font\n";

 				long count = 0;
				error = sAIFont->CountFonts( &count );
	
				for ( int i = 0; i < count && !error; i++ )
				{
					AIFontKey fontKey;
					const int tempLength = 1024; 
					char temp[tempLength];
					memset(temp, 0, tempLength);
					error = sAIFont->IndexFontList( i, &fontKey );
					if ( !error )
						error = sAIFont->GetFullFontName( fontKey, temp, tempLength );
					if ( !error )
						fileOut << temp << ", ";
					memset(temp, 0, tempLength);
					if ( !error )
						error = sAIFont->GetPostScriptFontName( fontKey, temp, tempLength );
					if ( !error )
						fileOut << temp << ", ";
					memset(temp, 0, tempLength);
					if ( !error )
						error = sAIFont->GetFontFamilyUIName( fontKey, temp, tempLength );
					if ( !error )
						fileOut << temp << ", ";
					memset(temp, 0, tempLength);
					if ( !error )
						error = sAIFont->GetFontStyleName( fontKey, temp, tempLength );
					if ( !error )
						fileOut << temp << "\n";
				}
			}
		}
	}
	
	BaseADMDialog::Notify(notifier);
}

void MarkedObjectsPreferencesDialog::Destroy()
{
	IADMItem item;
	int textLength;
	ASRealPoint location;
	
	item = GetItem( kSubFontSizeText );
	SetSubStringFontSize( item.GetFloatValue() );
	
	item = GetItem( kSubFontNamePopup );
	textLength = item.GetTextLength() + 1;
	string fontName(textLength, ' ');
	item.GetText(const_cast<char*>(fontName.c_str()), textLength ); //sa+
	SetSubStringFontName( fontName );
	
	item = GetItem( kSubLocXText );
	location.h = item.GetFloatValue();
	
	item = GetItem( kSubLocYText );
	location.v = item.GetFloatValue();

	SetSubStringLocation( location );

	item = GetItem( kDefFontSizeText );
	SetLabelStringFontSize( item.GetFloatValue() );
	
	item = GetItem( kDefFontNamePopup );
	textLength = item.GetTextLength() + 1;
	string defFontName(textLength, ' ');
	item.GetText( const_cast<char*>(defFontName.c_str()), textLength );
	SetLabelStringFontName( defFontName );
	
	item = GetItem( kDefLocXText );
	location.h = item.GetFloatValue();
	
	item = GetItem( kDefLocYText );
	location.v = item.GetFloatValue();

	SetLabelStringLocation( location );

	item = GetItem( kDefTextText );
	textLength = item.GetTextLength() + 1;
	string defText(textLength, ' ');
	item.GetText( const_cast<char*>(defText.c_str()), textLength );
	SetLabelStringDefaultText( defText );

	item = GetItem( kPrecText );
	precision = item.GetIntValue();

	item = GetItem( kAutoSort );
	autoSort = item.GetBooleanValue();
}

int GetFullPathToDesktop(char * fullPath, int32 maxPathLength)
{
	int error = 0;
	if (fullPath == NULL) return kSPBadParameterError;
	
	#if Macintosh
		strcpy(fullPath, "");

		FSRef fsRef;

		error = FSFindFolder(kOnSystemDisk, 
			 				 kDesktopFolderType, 
							 kDontCreateFolder, 
							 &fsRef);
		if (error) return error;

		error = FSRefMakePath(&fsRef, (unsigned char*)fullPath, maxPathLength);
		if (error) return error;
		
		strcat(fullPath, "/");

	#else
	    unsigned int sizeFullPath = strlen(fullPath);
		strcpy(fullPath, sizeFullPath, "C:\\");
	#endif
	
	return error;
}
// end MarkedObjectsPreferences.cpp