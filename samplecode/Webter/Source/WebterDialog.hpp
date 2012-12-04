//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/Webter/Source/WebterDialog.hpp $
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

#ifndef __WebterDialog_hpp__
#define __WebterDialog_hpp__

#include "BaseADMDialog.hpp"
#include "IADMList.hpp"
#include "AIDictionary.h"

static const int kDocumentName			= 4;
static const int kDocumentEntry			= 5;
static const int kDocumentDefinition	= 6;
static const int kDocumentType			= 7;
static const int kDocumentAdd			= 8;
static const int kArtName				= 9;
static const int kArtEntry				= 10;
static const int kArtDefinition			= 11;
static const int kArtType				= 12;
static const int kArtAdd				= 13;
static const int kTypeMenuResource		= 800;

class WebterDialog : public BaseADMDialog
{
private:
	AIDictionaryRef fDocumentDictionary;
	AIDictionaryRef fArtDictionary;
public:
	WebterDialog();
	ADMDialogRef Create(SPPluginRef pluginRef, char *name, int dialogID, ADMDialogStyle style, int options );
	virtual ~WebterDialog();
	
	void SetDocumentDictionary(AIDictionaryRef docDictionary, const char *docName);
	void SetArtDictionary(AIDictionaryRef artDictionary, const char *artName);
	
protected:

	ASErr Init();
	void Notify( IADMNotifier notifier );
	void Destroy();
	
	IADMList ClearPopUpList(int itemID);
	void UpdateDefinitionAndType(int itemID);
	void AddEntryToDictionary(int itemID);

};

#endif