//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Webter/Source/WebterDialog.cpp $
//
//  $Revision: #5 $
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

#include "IADMEntry.hpp"
#include "IADMItem.hpp"
#include "IADMList.hpp"
#include "IADMNotifier.hpp"

#include "WebterDialog.hpp"

#include "AIPreference.h"
#include "AIDictionary.h"
#include "ADMDialogGroup.h"
#include "ADMBasic.h"

#include "StringUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" ADMDialogGroupSuite *sADMDialogGroup;
extern "C" ADMBasicSuite *sADMBasic;

extern "C" AIPreferenceSuite *sAIPreference;
extern "C" AIDictionarySuite *sAIDictionary;
extern "C" AIDictionaryIteratorSuite *sAIDictionaryIterator;

static char* kStringPreference = "WebterDialog";
static char* kWebter_DPDockCodeStr = "kWebter_DPDockCodeStr";
static char* kWebter_DPDockGroupStr = "kWebter_DPDockGroupStr";
static char* kWebter_DPLocationStr = "kWebter_DPLocationStr";
static char* kWebter_DPSizeStr = "kWebter_DPSizeStr";
static char* kWebter_DPVisibleStr = "kWebter_DPVisibleStr";

// Most of this just calls the base class to do all the work
WebterDialog::WebterDialog( ) : BaseADMDialog()
{
	fDocumentDictionary = NULL;
	fArtDictionary = NULL;
}

ADMDialogRef WebterDialog::Create(SPPluginRef pluginRef, char *name, int dialogID, ADMDialogStyle style, int options ) 
{
	// Let the base class Create
	return ( BaseADMDialog::Create( pluginRef, name, dialogID, style, options ) );
}

ASErr WebterDialog::Init()
{
	// Let the base class initialize
	ASErr error = BaseADMDialog::Init();
	
	// init the location of the dialog box
	char groupName[64] = "SDK Dialogs";
	sAIPreference->GetStringPreference( kStringPreference, kWebter_DPDockGroupStr, groupName );

	long positionCode = 0x00001c00;
	sAIPreference->GetIntegerPreference( kStringPreference, kWebter_DPDockCodeStr, &positionCode );
	
	IADMRect boundsRect;
	GetBoundsRect( boundsRect );
	
	ADMRect dimensions;
	sADMBasic->GetPaletteLayoutBounds( &dimensions );
	ADMPoint location;
	location.h = dimensions.right - (boundsRect.right - boundsRect.left);
	location.v = dimensions.bottom - (boundsRect.bottom - boundsRect.top);
	
	sAIPreference->GetPointPreference( kStringPreference, kWebter_DPLocationStr, &location );
	
	ADMPoint size;
	size.h = 360;
	size.v = 170;
#ifdef WIN32
	size.v += 6;
	location.v -= 6;
	size.h += 4;
#endif

	error = 	sAIPreference->GetPointPreference( kStringPreference, kWebter_DPSizeStr, &size );
	IADMRect rect;
	rect.left = location.h;
	rect.right = location.h + size.h;
	rect.top = location.v;
	rect.bottom = location.v + size.v;

	// restore the size and location of the dialog
	SetBoundsRect( rect );
	// restore the position code of the dialog
	error = 	sADMDialogGroup->SetDialogGroupInfo( GetDialog(), groupName, positionCode );

	IADMItem item = GetItem( kDocumentType );
	IADMList list = item.GetList();
	list.SetMenuID( kTypeMenuResource );

	item = GetItem( kArtType );
	list = item.GetList();
	list.SetMenuID( kTypeMenuResource );

	return error;
}

IADMList WebterDialog::ClearPopUpList(int itemID)
{
	IADMItem childrenPopUp = GetItem( itemID );
	childrenPopUp.Enable(true);
	IADMList childrenList = childrenPopUp.GetList();
	int entries = childrenList.NumberOfEntries();
	for( int counter = entries; counter >= 0; counter--)
		childrenList.RemoveEntry(counter);
	return childrenList;
		
}

void WebterDialog::Notify(IADMNotifier notifier)
{
	if (notifier.IsNotifierType(kADMUserChangedNotifier))
	{
		IADMItem item(notifier.GetItem());
		if (item)
		{
			int itemID = item.GetID();
			switch (itemID)
			{
				case kDocumentAdd:
				case kArtAdd:
					AddEntryToDictionary(itemID);
					break;
				case kDocumentEntry:
				case kArtEntry:
					UpdateDefinitionAndType(itemID);
					break;
			}
		}
	}
	BaseADMDialog::Notify(notifier);
}

void WebterDialog::AddEntryToDictionary(int itemID)
{
	char entryString[256];
	AIEntryType entryType;
	IADMItem item = GetItem(itemID-3);
	item.GetText(entryString, 255);
	item = GetItem(itemID-1);
	IADMList list = item.GetList();
	IADMEntry entry = list.GetActiveEntry();
	entryType = entry.GetIndex();
	AIDictKey dictKey;

	AIDictionaryRef dictionaryRef = NULL;
	if (itemID == kDocumentAdd)
		dictionaryRef = fDocumentDictionary;
	else
		dictionaryRef = fArtDictionary;

	item = GetItem(itemID-2);

	char stringValue[256];
	int intValue;
	ASBoolean booleanValue;
	float floatValue;
	switch (entryType)
	{
		case IntegerType:
			item.GetText(stringValue, 255);
			intValue = atoi(stringValue);
			dictKey = sAIDictionary->Key(entryString);
			sAIDictionary->SetIntegerEntry(dictionaryRef, dictKey, intValue);
			break;
		case BooleanType:
			item.GetText(stringValue, 255);
			booleanValue = atoi(stringValue);
			dictKey = sAIDictionary->Key(entryString);
			sAIDictionary->SetBooleanEntry(dictionaryRef, dictKey, booleanValue);
			break;
		case RealType:
			item.GetText(stringValue, 255);
			floatValue = (float)atof(stringValue);
			dictKey = sAIDictionary->Key(entryString);
			sAIDictionary->SetRealEntry(dictionaryRef, dictKey, floatValue);
			break;
		case StringType:
			item.GetText(stringValue, 255);
			dictKey = sAIDictionary->Key(entryString);
			sAIDictionary->SetStringEntry(dictionaryRef, dictKey, stringValue);
			break;
		case UnknownType:
		case DictType:
		case ArrayType:
		case BinaryType:
		case PointType:
		case MatrixType:
		case PatternRefType:
		case BrushPatternRefType:
		case CustomColorRefType:
		case GradientRefType:
		case PluginObjectRefType:
		case FillStyleType:
		case StrokeStyleType:
		case UIDType:
		case UIDREFType:
		case XMLNodeType:
		case SVGFilterType:
		case ArtStyleType:
			sADMBasic->ErrorAlert("I don't support that type!");
			break;
	}
}

void WebterDialog::UpdateDefinitionAndType(int itemID)
{
	char textString[256] = "";
	AIEntryType entryType;
	IADMItem item = GetItem(itemID);
	item.GetText(textString, 255);
	AIDictionaryRef dictionaryRef;
	AIDictKey dictKey;

	if (itemID == kDocumentEntry)
		dictionaryRef = fDocumentDictionary;
	else
		dictionaryRef = fArtDictionary;

	dictKey = sAIDictionary->Key(textString);
	AIErr error = sAIDictionary->GetEntryType( dictionaryRef, dictKey, &entryType);
	if (error)
	{
		textString[0] = '-';
		dictKey = sAIDictionary->Key(textString);
		sAIDictionary->GetEntryType( dictionaryRef, dictKey, &entryType);
	}	
	item = GetItem(itemID+2);
	IADMList list = item.GetList();
	IADMEntry entry = list.GetEntry(entryType+1);
	entry.Select(true);
	switch (entryType)
	{
		case UnknownType:
			strcpy(textString, "UnknownType");
			break;
		case IntegerType:
			ASInt32 intValue;
			sAIDictionary->GetIntegerEntry( dictionaryRef, dictKey, &intValue);
			sprintf(textString, "%d", intValue);
			break;
		case BooleanType:
			ASBoolean booleanValue;
			sAIDictionary->GetBooleanEntry( dictionaryRef, dictKey, &booleanValue);
			strcpy(textString, booleanValue ? "True" : "False");
			break;
		case RealType:
			ASReal realValue;
			sAIDictionary->GetRealEntry( dictionaryRef, dictKey, &realValue);
			sprintf(textString, "%f", realValue);
			break;
		case StringType:
			const char *stringValue;
			sAIDictionary->GetStringEntry( dictionaryRef, dictKey, &stringValue);
			sprintf(textString, stringValue);
			break;
		case DictType:
			strcpy(textString, "DictType");
			break;
		case ArrayType:
			strcpy(textString, "ArrayType");
			break;
		case BinaryType:
			strcpy(textString, "BinaryType");
			break;
		case PointType:
			strcpy(textString, "PointType");
			break;
		case MatrixType:
			strcpy(textString, "MatrixType");
			break;
		case PatternRefType:
			strcpy(textString, "PatternRefType");
			break;
		case BrushPatternRefType:
			strcpy(textString, "BrushPatternRefType");
			break;
		case CustomColorRefType:
			strcpy(textString, "CustomColorRefType");
			break;
		case GradientRefType:
			strcpy(textString, "GradientRefType");
			break;
		case PluginObjectRefType:
			strcpy(textString, "PluginObjectRefType");
			break;
		case FillStyleType:
			strcpy(textString, "FillStyleType");
			break;
		case StrokeStyleType:
			strcpy(textString, "StrokeStyleType");
			break;
		case UIDType:
			strcpy(textString, "UIDType");
			break;
		case UIDREFType:
			strcpy(textString, "UIDREFType");
			break;
		case XMLNodeType:
			strcpy(textString, "XMLNodeType");
			break;
		case SVGFilterType:
			strcpy(textString, "SVGFilterType");
			break;
		case ArtStyleType:
			strcpy(textString, "ArtStyleType");
			break;
		default:
			strcpy(textString, "Error Default Type!");
	}
	item = GetItem(itemID+1);
	item.SetText(textString);
	item.Invalidate();
	item.Update();

}
void WebterDialog::Destroy()
{
	BaseADMDialog::Destroy();
}

WebterDialog::~WebterDialog()
{
	const char *groupName;
	long positionCode;
	sADMDialogGroup->GetDialogGroupInfo( GetDialog(), &groupName, &positionCode );
	
	IADMPoint location, size;
	IADMRect boundsRect;
	GetBoundsRect( boundsRect );
	
	location.h = boundsRect.left;
	location.v = boundsRect.top;
	size.h = boundsRect.Width();
	size.v = boundsRect.Height();

	sAIPreference->PutIntegerPreference( kStringPreference, kWebter_DPDockCodeStr, positionCode );
	sAIPreference->PutStringPreference( kStringPreference, kWebter_DPDockGroupStr, groupName );
	sAIPreference->PutPointPreference( kStringPreference, kWebter_DPLocationStr, &location );
	sAIPreference->PutPointPreference( kStringPreference, kWebter_DPSizeStr, &size );
	sAIPreference->PutBooleanPreference( kStringPreference, kWebter_DPVisibleStr, IsVisible() );

	sAIDictionary->Release( fDocumentDictionary );
	sAIDictionary->Release( fArtDictionary );
}

void WebterDialog::SetDocumentDictionary(AIDictionaryRef docDictionary, const char * /* docName */ )
{
	sAIDictionary->Release(fDocumentDictionary);
	fDocumentDictionary = docDictionary;
	IADMList list = ClearPopUpList(kDocumentEntry);
	AIDictKey dictKey;

	if (fDocumentDictionary)
	{
		const char* keyString;
		AIDictionaryIterator dictionaryIter = NULL;
		sAIDictionary->Begin(fDocumentDictionary, &dictionaryIter);
		int a = 0;
		while ( !sAIDictionaryIterator->AtEnd(dictionaryIter) )
		{
			dictKey = sAIDictionaryIterator->GetKey( dictionaryIter );
			keyString = sAIDictionary->GetKeyString(dictKey);
			char betterKeyString[256];
			strcpy(betterKeyString, keyString);
			if (betterKeyString[0] == '-')
				betterKeyString[0] = ' ';
			IADMEntry entry(list.InsertEntry( a ));
			entry.SetText(betterKeyString);
			entry.SetID( a );
			sAIDictionaryIterator->Next(dictionaryIter);
			if (a == 0)
				entry.Select(true);
			a++;
		}
		sAIDictionaryIterator->Release( dictionaryIter );		
	}

//	IADMItem item = GetItem(kDocumentName);
//	item.SetText(docName);
}

void WebterDialog::SetArtDictionary(AIDictionaryRef artDictionary, const char *artName)
{
	sAIDictionary->Release(fArtDictionary);
	fArtDictionary = artDictionary;
	IADMList list = ClearPopUpList(kArtEntry);
	AIDictKey dictKey;

	if (fArtDictionary)
	{
		const char* keyString;
		AIDictionaryIterator dictionaryIter = NULL;
		sAIDictionary->Begin(fArtDictionary, &dictionaryIter);
		int a = 0;
		while ( !sAIDictionaryIterator->AtEnd(dictionaryIter) )
		{
			dictKey = sAIDictionaryIterator->GetKey( dictionaryIter );
			keyString = sAIDictionary->GetKeyString(dictKey);
			char betterKeyString[256];
			strcpy(betterKeyString, keyString);
			if (betterKeyString[0] == '-')
				betterKeyString[0] = ' ';
			IADMEntry entry(list.InsertEntry( a ));
			entry.SetText(betterKeyString);
			entry.SetID( a );
			sAIDictionaryIterator->Next(dictionaryIter);
			if (a == 0)
				entry.Select(true);
			a++;
		}
		sAIDictionaryIterator->Release( dictionaryIter );		
	}
	
	IADMItem item = GetItem(kArtName);
	item.SetText(artName);
}

