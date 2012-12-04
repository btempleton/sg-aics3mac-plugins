//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/CodeSnippets/SnpFileHelper.cpp $
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

#include "SDKErrors.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnippetRunnerSuites.h"
#include "SnippetRunnerLog.h"
#include "SnippetRunnerParameter.h"
#include "SnpFileHelper.h"

/*
*/
ASErr SnpFileHelper::GetDirectoryDialog(const ai::UnicodeString &title, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		bool forceLocalFileView = false;
		result = sAIUser->GetDirectoryDialog(title, forceLocalFileView, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnpFileHelper::GetFileDialog(const ai::UnicodeString &title, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		AIPlatformFileDlgOpts* opts = NULL;
		bool forceLocalFileView = false;
		result = sAIUser->GetFileDialog(title, opts, forceLocalFileView, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnpFileHelper::PutFileDialog(const ai::UnicodeString &title, const ai::UnicodeString& defaultName, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		AIPlatformFileDlgOpts* opts = NULL;
		bool forceLocalFileView = false;
		result = sAIUser->PutFileDialog(title, opts, forceLocalFileView, defaultName, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnpFileHelper::GetIllustratorFileDialog(const ai::UnicodeString &title, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		AIPlatformFileDlgOpts options;
#ifdef WIN_ENV
		options.AddFilter(ai::UnicodeString("Adobe Illustrator (*.AI, *.AIT)"), ai::UnicodeString("*.ai;*.ait"));
#endif
#ifdef MAC_ENV
		AIPlatformFileDlgOpts::PopupFilter filters[2];
		//Adobe Illustrator Files
		filters[0].fDesc = ai::UnicodeString("Adobe Illustrator Documents");
		filters[0].fExtension = ai::UnicodeString("ai"); 
		filters[0].fCreatorType.creator = 'ART5';
		filters[0].fCreatorType.type = 'PDF ';
		//Adobe Illustrator Template Files
		filters[1].fDesc = ai::UnicodeString("Adobe Illustrator Templates");
		filters[1].fExtension = ai::UnicodeString("ait"); 
		filters[1].fCreatorType.creator = 'ART5';
		filters[1].fCreatorType.type = 'AITm';
		options.SetFilterArray(filters, 2);
#endif
		bool forceLocalFileView = false;
		result = sAIUser->GetFileDialog(title, &options, forceLocalFileView, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnpFileHelper::PutIllustratorFileDialog(const ai::UnicodeString &title, const ai::UnicodeString& defaultName, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		AIPlatformFileDlgOpts options;
#ifdef WIN_ENV
		options.AddFilter(ai::UnicodeString("Adobe Illustrator Document(*.AI)"), ai::UnicodeString("*.ai"));
		options.AddFilter(ai::UnicodeString("Adobe Illustrator Template(*.AIT)"), ai::UnicodeString("*.ait"));
#endif
#ifdef MAC_ENV
		AIPlatformFileDlgOpts::PopupFilter filters[2];
		//Adobe Illustrator
		filters[0].fDesc = ai::UnicodeString("Adobe Illustrator Document");
		filters[0].fExtension = ai::UnicodeString("ai"); 
        filters[0].fCreatorType.creator = 'ART5';
        filters[0].fCreatorType.type = 'PDF ';
		//Adobe Illustrator Template
		filters[1].fDesc = ai::UnicodeString("Adobe Illustrator Template");
		filters[1].fExtension = ai::UnicodeString("ait"); 
        filters[1].fCreatorType.creator = 'ART5';
        filters[1].fCreatorType.type = 'AITm';
		options.SetFilterArray(filters, 2);
		// 1556362 Macintosh only; Function AIUserSuite::PutFileDialog does not respect the 
		// PopupFilters passed in the opts parameter. 
		// Expected: Format popup on Save dialog. 
		// Actual: No format popup on Save dialog.
#endif
		bool forceLocalFileView = false;
		result = sAIUser->PutFileDialog(title, &options, forceLocalFileView, defaultName, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}


/*
*/
ASErr SnpFileHelper::GetTextFileDialog(const ai::UnicodeString &title, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		AIPlatformFileDlgOpts options;
#ifdef WIN_ENV
		options.AddFilter(ai::UnicodeString("Text documents (*.txt)"), ai::UnicodeString("*.txt"));
		options.AddFilter(ai::UnicodeString("All Files"), ai::UnicodeString("*.*"));
#endif
#ifdef MAC_ENV
		AIPlatformFileDlgOpts::PopupFilter filters[1];
		// Text files
		filters[0].fDesc = ai::UnicodeString("Text (txt)");
		filters[0].fExtension = ai::UnicodeString("txt"); 
		filters[0].fCreatorType.creator = 'ttxt';
		filters[0].fCreatorType.type = 'TEXT';
		options.SetFilterArray(filters, 1);
#endif
		bool forceLocalFileView = false;
		result = sAIUser->GetFileDialog(title, &options, forceLocalFileView, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

/*
*/
ASErr SnpFileHelper::PutTextFileDialog(const ai::UnicodeString &title, const ai::UnicodeString& defaultName, ai::FilePath& ioFilePath)
{
	ASErr result = kNoErr;
	try {
		SDK_ASSERT(sAIUser);
		AIPlatformFileDlgOpts options;
#ifdef WIN_ENV
		options.AddFilter(ai::UnicodeString("Text documents (*.txt)"), ai::UnicodeString("*.txt"));
		options.AddFilter(ai::UnicodeString("All Files"), ai::UnicodeString("*.*"));
#endif
#ifdef MAC_ENV
		AIPlatformFileDlgOpts::PopupFilter filters[1];
		// Text files
		filters[0].fDesc = ai::UnicodeString("Text (txt)");
		filters[0].fExtension = ai::UnicodeString("txt"); 
		filters[0].fCreatorType.creator = 'ttxt';
		filters[0].fCreatorType.type = 'TEXT';
		options.SetFilterArray(filters, 1);
#endif
		bool forceLocalFileView = false;
		result = sAIUser->PutFileDialog(title, &options, forceLocalFileView, defaultName, ioFilePath);
		aisdk::check_ai_error(result);
	}
	catch (ai::Error& ex) {
		result = ex;
	}
	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/* Makes the snippet SnpFileHelper available to the SnippetRunner framework.
 */
class _SnpRunnableFileHelper : public SnpRunnable
{
	public:
		/* Constructor registers the snippet with the framework.
		 */
		_SnpRunnableFileHelper () : SnpRunnable() {}

		/* Destructor.
		 */
		virtual ~_SnpRunnableFileHelper () {}

		/* Returns name of snippet.
		*/
		std::string GetName() const;

		/* Returns a description of what the snippet does.
		*/
		std::string	GetDescription() const;

		/** Returns the operations this snippet supports.
		*/
		Operations GetOperations() const;

		/** Returns name of the snippet's default operation.
		*/
		std::string GetDefaultOperationName() const;

		/** Returns the categories a snippet belongs to.
			@return default categories.
		*/
		std::vector<std::string> GetCategories() const;

		/* Returns true if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return true if snippet can run, false otherwise
		 */
		ASBoolean			CanRun(SnpRunnable::Context& runnableContext);

		/* Runs the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kNoErr on success, other ASErr otherwise.
		*/
		ASErr		Run(SnpRunnable::Context& runnableContext);

		/** Runs unit test.
		*/
		ASErr RunUnitTest(SnpRunnable::Context& runnableContext);
};

/*
*/
std::string _SnpRunnableFileHelper::GetName() const
{
	return "FileHelper";
}

/*
*/
std::string _SnpRunnableFileHelper::GetDescription() const 
{
	return "Helper class for choosing, opening and saving files";
}

/*
*/
SnpRunnable::Operations _SnpRunnableFileHelper::GetOperations() const
{
	SnpRunnable::Operations operations;
	operations.push_back(Operation("GetDirectoryDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("GetFileDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("PutFileDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("GetIllustratorFileDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("PutIllustratorFileDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("GetTextFileDialog", "", kSnpRunNotSupportedContext));
	operations.push_back(Operation("PutTextFileDialog", "", kSnpRunNotSupportedContext));
	return operations;
}

/*
*/
std::string _SnpRunnableFileHelper::GetDefaultOperationName() const 
{
	return "GetDirectoryDialog";
}

/*
*/
std::vector<std::string> _SnpRunnableFileHelper::GetCategories() const
{
	std::vector<std::string> categories = SnpRunnable::GetCategories();
	categories.push_back("Helper Snippets");
	return categories;
}

/* Checks if preconditions are met.
*/
ASBoolean _SnpRunnableFileHelper::CanRun(SnpRunnable::Context& runnableContext)
{
	return true;
}

/* Instantiates and calls your snippet class.
*/
ASErr _SnpRunnableFileHelper::Run(SnpRunnable::Context& runnableContext)
{
	ASErr result = kNoErr;
	try {
		ai::FilePath ioFilePath;
		SnpFileHelper instance;
		if ("GetDirectoryDialog"  == runnableContext.GetOperation().GetName()) {
			result = instance.GetDirectoryDialog(ai::UnicodeString("Choose folder"), ioFilePath);
		}
		else if ("GetFileDialog"  == runnableContext.GetOperation().GetName()) {
			result = instance.GetFileDialog(ai::UnicodeString("Choose file"), ioFilePath);
		}
		else if ("PutFileDialog"  == runnableContext.GetOperation().GetName()) {
			result = instance.PutFileDialog(ai::UnicodeString("Choose file"), ai::UnicodeString("Default"), ioFilePath);
		}
		else if ("GetIllustratorFileDialog" == runnableContext.GetOperation().GetName()) {
			result = instance.GetIllustratorFileDialog(ai::UnicodeString("Choose Illustrator file"), ioFilePath);
		}
		else if ("PutIllustratorFileDialog"  == runnableContext.GetOperation().GetName()) {
			result = instance.PutIllustratorFileDialog(ai::UnicodeString("Choose Illustrator file"), ai::UnicodeString("Default.ai"), ioFilePath);
		}
		else if ("GetTextFileDialog" == runnableContext.GetOperation().GetName()) {
			result = instance.GetTextFileDialog(ai::UnicodeString("Choose text file"), ioFilePath);
		}
		else if ("PutTextFileDialog" == runnableContext.GetOperation().GetName()) {
			result = instance.PutTextFileDialog(ai::UnicodeString("Choose text file"), ai::UnicodeString("Default.txt"), ioFilePath);
		}
		else {
			result = kBadParameterErr;
		}
		if (!result) {
			SnippetRunnerLog::Instance()->Write(ioFilePath.GetFullPath());
		}
	}
	catch (ai::Error& ex) {
		result = ex;
	}	
	return result;
}

/*
*/
ASErr _SnpRunnableFileHelper::RunUnitTest(SnpRunnable::Context& runnableContext)
{
	// SnpFileHelper is an interactive class that prompts the user to choose files and folder.
	SnippetRunnerLog::Instance()->Write("Interactive snippet - not suitable for automated testing - unit test code intentionally ommited");
	return kNoErr;
}

/*	Declares an instance to register the snippet hook with the framework.
*/
static _SnpRunnableFileHelper instance_SnpRunnableFileHelper;

// End SnpFileHelper.cpp

