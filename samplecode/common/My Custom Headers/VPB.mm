/*
 *  VPB.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "VPB.h"
#import "PlateItem.h"


Instance::VPB::VPB() : fActionParamValueRef(NULL)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIActionManager);
		result = sAIActionManager->AINewActionParamValue(&fActionParamValueRef);
		SDK_ASSERT(!result);
		SDK_ASSERT(fActionParamValueRef);
	}
	catch (ai::Error) {
	}
}

/*
*/
Instance::VPB::~VPB()
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIActionManager);
		result = sAIActionManager->AIDeleteActionParamValue(fActionParamValueRef);
		SDK_ASSERT(!result);
		fActionParamValueRef = NULL;
	}
	catch (ai::Error) {
	}
}


// kAISaveDocumentAsAction parameters
/*
*/
void Instance::VPB::SetSaveDocumentAsName(const ai::FilePath& name)
{
	SDK_ASSERT(sAIActionManager);
	ASErr result = sAIActionManager->AIActionSetStringUS(this->fActionParamValueRef, kAISaveDocumentAsNameKey, name.GetFullPath());
	aisdk::check_ai_error(result);
}

/*
*/
void Instance::VPB::SetSaveDocumentAsFormat(const char* format)  
{
	SDK_ASSERT(sAIActionManager);
	ASErr result = sAIActionManager->AIActionSetString(this->fActionParamValueRef, kAISaveDocumentAsFormatKey, format);
	aisdk::check_ai_error(result);
}

/*
*/
void Instance::VPB::SetSaveDocumentAsGetParams(ASBoolean getParams)
{
	SDK_ASSERT(sAIActionManager);
	ASErr result = sAIActionManager->AIActionSetBoolean(this->fActionParamValueRef, kAISaveDocumentAsGetParamsKey, getParams);
	aisdk::check_ai_error(result);
}



/*
*/
ASErr Instance::SaveDocumentAsPDF(Dialog* dlg, PlateItem* plateItem, const string& name)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIActionManager);
		
		Instance::VPB vpb;

		// Format parameter.
		vpb.SetSaveDocumentAsFormat(kAIPDFFileFormat);

		// Compatibility.
		ASErr result = sAIActionManager->AIActionSetInteger(vpb.fActionParamValueRef, kAIPDFCompatibilityKey, kAIPDFCompatibility14);
		aisdk::check_ai_error(result);
		
/*		// Crop To
		result = sAIActionManager->AIActionSetInteger(vpb.fActionParamValueRef, kAIPDFCropToKey, kAIPDFArtBox);
		aisdk::check_ai_error(result);
		
		// Page Count
		//result = sAIActionManager->AIActionSetInteger(vpb.fActionParamValueRef, kAIPDFPageCountKey, 1);
		//aisdk::check_ai_error(result);
		
		// Page Index
		ASInt32 index; sAICropArea->GetActive(&index);
		result = sAIActionManager->AIActionSetInteger(vpb.fActionParamValueRef, kAIPDFPageIndexKey, index);
		aisdk::check_ai_error(result);

*/		

		// Option Set
		result = sAIActionManager->AIActionSetInteger(vpb.fActionParamValueRef, kAIPDFOptionSetKey, kAIPDFOptionSetCustom);
		aisdk::check_ai_error(result);
		result = sAIActionManager->AIActionSetString(vpb.fActionParamValueRef, kAIPDFOptionSetNameKey, "BStat Preset");
		aisdk::check_ai_error(result);
		


/*
		// Round trip.
		result = sAIActionManager->AIActionSetBoolean(vpb.fActionParamValueRef, kAIPDFRoundTripKey, FALSE);
		aisdk::check_ai_error(result);
		
		// Generate thumbnails.
		result = sAIActionManager->AIActionSetBoolean(vpb.fActionParamValueRef, kAIPDFGenerateThumbnailsKey, FALSE);
		aisdk::check_ai_error(result);
		
		// View PDF file.
		result = sAIActionManager->AIActionSetBoolean(vpb.fActionParamValueRef, kAIPDFViewPDFFileKey, FALSE);
		aisdk::check_ai_error(result);

		// Fast web view.
		result = sAIActionManager->AIActionSetBoolean(vpb.fActionParamValueRef, kAIPDFFastWebViewKey, FALSE);
		aisdk::check_ai_error(result);
		
		// Password Protection
		result = sAIActionManager->AIActionSetBoolean(vpb.fActionParamValueRef, kAIPDFUserPasswordRequiredKey, FALSE);
		aisdk::check_ai_error(result);
*/		
		//Output directory
		NSString* outputFolder;
		if ([dlg outputToPlants]) {
			outputFolder = [plateItem createManufacturingPath];
		} else {
			outputFolder = [dlg outputPathString];
		}
		
		//Create path
		NSString* fullPathForNewPDF = [outputFolder stringByAppendingPathComponent:[[NSString stringWithCString:name.c_str() encoding:NSASCIIStringEncoding] stringByAppendingString: @".pdf"]];

		// Gather common parameters then save.
		
		//sADMBasic->MessageAlert(buffer);
		result = this->SaveDocumentAs((ai::UnicodeString)[fullPathForNewPDF cStringUsingEncoding:NSASCIIStringEncoding], vpb);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}	
	return result;
}

/*
*/
ASErr Instance::SaveDocumentAs(const ai::UnicodeString& name, Instance::VPB& vpb)
{
	ASErr result = kNoErr;
	try {
		// Name parameter.
		ai::FilePath path;
		path.Set(name, FALSE);
		//sADMBasic->MessageAlert(name.as_UTF8().c_str());
		//SnippetRunnerLog::Instance()->Write(path.GetFullPath());
		vpb.SetSaveDocumentAsName(path);

		// Enable dialogs parameter.
		ASBoolean getParams = FALSE /*SnippetRunnerParameter::Instance()->GetBoolean("Enable dialogs during save", false)*/;
		vpb.SetSaveDocumentAsGetParams(getParams);

		// Play the action.
		result = this->SaveDocumentAs(kDialogOff, vpb);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}	
	return result;

}

/*
*/
ASErr Instance::SaveDocumentAs(ActionDialogStatus dialogStatus, AIActionParamValueRef parameters)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIActionManager);
		result = sAIActionManager->PlayActionEvent(kAISaveDocumentAsAction, dialogStatus, parameters);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}	
	return result;

}
