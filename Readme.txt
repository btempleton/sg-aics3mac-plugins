Adobe Illustrator CS3 Software Development Kit
(Build 407, September 2007) 
ReadMe File

______________________________________________________________________

This file contains the latest information about the Adobe Illustrator 
SDK.  This information applies to Adobe Illustrator CS3 (13.0).

The SDK enables you to develop software modules that plug into and 
extend the functionality of Adobe Illustrator CS3.
______________________________________________________________________

This file has the following sections:
    1. Legal
    2. SDK Documentation Overview
    3. Development Environments
    4. Installing the SDK
    5. What's New
    6. Known Issues
    7. Developer Support and Adobe Partner Programs


***********************************************************
1. Legal
***********************************************************
You may use this SDK only in a manner consistent with the included
End User License Agreement:

	<SDK>/legalnotices/EULAs.pdf


***********************************************************
2. SDK Documentation Overview
***********************************************************

Adobe Illustrator CS3 Getting Started Guide:
	File: <SDK>/docs/guides/getting-started-guide.pdf
	Describes the basics of how to get started developing plug-ins
	for Illustrator CS3 and provides descriptions of the sample
	plug-ins provided with this SDK. Supersedes the 
	AboutSampleCode.txt document.

Adobe Illustrator CS3 Porting Guide:
	File: <SDK>/docs/guides/porting-guide.pdf
	Describes how to set up your development environment and port
	existing code to Illustrator CS3. Details changes in the public
	API and other aspects of the SDK since the prior release.

Adobe Illustrator CS3 Programmer's Guide:
	File: <SDK>/docs/guides/porting-guide.pdf
	Describes the fundamentals of writing plug-ins for Illustrator.

Adobe Dialog Manager Programmer's Guide:
	File: <SDK>/docs/guides/adm-guide.pdf
	Describes the concepts involved in programming the cross-platform 
	user-interface toolkit used in Illustrator. 

Using the Adobe Text Engine:
	File: <SDK>/docs/guides/using-adobe-text-engine.pdf
	Describes the components of the Illustrator Adobe Text Engine API,
	and provides recipes for creating, editing, deleting, styling and 
	iterating text items in a document, with references to sample code 
	and the Adobe Illustrator API Reference.

Adobe Illustrator API Reference:
	Reference documentation for the API can be found in the files below.

	File: <SDK>/docs/references/index.chm
	API reference in compiled HTML format. This searchable help file 
	contains reference documentation for the API. To view the contents 
	on Windows, double-click the index.chm file icon in Windows Explorer,
	to open the home page. To view the contents on a Macintosh, you need 
	a CMH viewer (for options, see "Adobe Illustrator CS3 Porting Guide").

	File: <SDK>/docs/references/sdkdocs.tar.gz
	API reference in archive HTML format. This archive contains reference 
	documentation for the API. After installing the SDK, double-click the 
	sdkdocs.tar.gz file to decompress the archive. View the HTML 
	documentation in your browser.

API Advisor:
	File: <SDK>/docs/references/apiadvisor-ai12-vs-ai13.html
	Reports class, struct, and file differences between the API included 
	with the Illustrator CS2 SDK and this SDK.


***********************************************************
3. Development Environments
***********************************************************
The following platforms are supported for the development of plug-ins 
for Illustrator CS3:

Macintosh:
	OS:  Mac OS 10.4
	IDE: Xcode 2.4.1

Windows:
	OS:  Microsoft Windows XP with service pack 2
	IDE: Microsoft Visual C++ 2005

For more details, see "Adobe Illustrator CS3 Porting Guide".


***********************************************************
4. Installing the SDK
***********************************************************
To install the SDK, download the pre-configured archive for your platform 
from the Adobe Illustrator Developers site:

	http://www.adobe.com/devnet/illustrator/

Start by expanding the archive, then follow the detailed instructions in 
"Adobe Illustrator CS3 Porting Guide" to set up your development platform.


***********************************************************
5. What's New
***********************************************************
- Macintosh development environment switches to Xcode:
	You must use Xcode 2.4.1 to develop plug-ins for Illustrator CS3 
	on the Macintosh. CodeWarrior is no longer supported.

- Windows development environment switches to Visual C++ 2005:
	You must use Visual C++ 2005 to develop plug-ins for Illustrator 
	CS3 on Windows.

- API Reference:
	Improved reference documentation for the API is provided.

- API Advisor:
	New reference documentation on API changes made between 
	Illustrator CS2 and Illustrator CS3 is provided.

- New APIs:
	Document Presets (see AINewDocumentPreset), 
	Crop Area (see AICropAreaSuite), 
	Isolation Mode (see AIIsolationModeSuite) and 
	Color Harmony (see AIColorHarmonySuite).

-Adobe Illustrator CS3 Getting Started Guide:
	New guide to help new developers get started developing plug-ins
	for Illustrator CS3.

-Adobe Illustrator CS3 Porting Guide:
	New guide that describes how to set up your development environment 
	and port existing code to Illustrator CS3.  Details changes in the API
	and other aspects of the SDK since the prior release.

-Using the Adobe Text Engine:
	New document which describes, and provides recipes for using, the 
	Illustrator ATE API.

-Xcode and Visual C++ Project Templates for Illustrator SDK Plug-in:
	Xcode and Visual C++ templates were created to ease the creation 
	of Illustrator plug-ins that are structured like an SDK sample. 
	To learn more about how to use the templates, see the  "Using 
	the plug-in project templates" section in "Adobe Illustrator 
	CS3 Getting Started Guide".

- API changes:
	See "Adobe Illustrator CS3 Porting Guide" and "API Advisor".

- SDK supports universal binary:
	The SDK supports universal binary for Macintosh plug-ins. Plug-ins
	built as universal binary can run on PowerPC or Intel-based
	Macintosh hardware.

- Sample code changes:
	The samples were ported to Xcode 2.4.1 and Visual C++ 2005.
	Substantial improvements were made, notably:

	- Tutorial: 
		Shows the fundamentals of Illustrator
		plug-in development. If you are getting started
		look at this sample together with the 
		"Adobe Illustrator CS3 Programmer's Guide".


	The following sample was added:

	- SnippetRunner:
		Provides user interface, parameter input and log output 
		capabilities for Illustrator code snippets,there are 
		several sample and helper code snippets provided.

		A code snippet is a source file in which you can quickly and
		easily prototype SDK API calls.

		

	The following samples were removed:

	- TextRoadMap: 
		The sample code from this plug-in was moved into 
		the SnpText code snippet in the SnippetRunner
		plug-in.

	- TextTest: 
		The sample code from this plug-in was moved into 
		the SnpText, SnpTextIterator, SnpTextStyler
		and SnpTextStyles code snippets in the SnippetRunner
		plug-in.

	- TutorialCallMe: 
		This sample showed how to call the action
		event added by the Tutorial sample. The 
		SnippetRunner plug-in has sample code that shows 
		how to call action events. This duplication was 
		eliminated.

	- PlayActions:
		The sample code from this plug-in was moved into the 
		SnpDocumentActionHelper code snippet in the 
		SnippetRunner plugin.


***********************************************************
6. Known Issues
***********************************************************

The following are known issues in this SDK. These issues will be 
addressed in forthcoming SDKs:

______________________________________________________________________
- On the Macintosh, if you use StuffIt Expander to decompress the 
  <SDK>/docs/references/sdkdocs.tar.gz file, older versions may 
  truncate filenames at 31 characters, thus breaking HTML links.

  The workaround for this is to decompress the archive following
  these steps:

	1. Open a Terminal shell window, and type the following:

	    cd <SDK>/docs/references
	    tar -xzf sdkdocs.tar.gz

	2. After you are done decompressing, open the index.html
	   file to see the documentation.

______________________________________________________________________
- On Vista, opening the <SDK>/docs/references/index.chm file causes 
  a security warning and once opened none of the pages can be viewed.

  The workaround for this is to open the document following these steps:

	1. Extract the SDK.

	2. Open <SDK>/docs/references/index.chm

	3. Uncheck the 'Always ask before opening this file' check box
	   in the security warning dialog.

	4. Select Open.

______________________________________________________________________
- On Intel based Macintosh hardware the Xcode debugger may fail to step over 
  certain Illustrator API calls in your plug-in (1510374). 
  
  There are situations where the frame pointer gets hijacked for other purposes 
  and the Xcode debugger gets confused. Symbol stripping the release build of 
  Illustrator contributes to this problem but is not the root cause.
  
  If you have problems stepping through your plug-in code in the Xcode 
  debugger first make sure you are using the supported version of Xcode.
  
  If you are stepping over an Illustrator API call and you see the message, 
  "Previous frame inner to this frame (corrupt stack?)", try one of the 
  following workarounds:

    1. Use the Xcode debugger’s Continue button to resume execution.

    2. Use the Xcode debugger Continue to Here command to run to a subsequent 
       line of code. The Continue to Here command is available by right clicking 
       the left of the code-editor pane in the Xcode debugger window.
    
    3. Step using gdb instead of the Step Over button. Use Xcode’s 
       Debug > Console Log menu to open the debugger console and type step at 
       the prompt.
       
    4. Debug on a PowerPC based Macintosh platform.

______________________________________________________________________
- In the API Reference, there are some incorrect/misleading descriptions:

	1.IFind::ReplaceMatch, description for the return value should be 
	  "If findNext parameter is true, returns true if there is another 
	  occurance found, returns false if no other occurance found. If 
	  findNext parameter is false, always returns false." (1589371)

	2.AISwatchGroupSuite::RemoveSwatchGroup/RemoveNthSwatchGroup, when
	  deleting spot colors, if it is the last reference to a particular
	  spot color used in the document the spot color is moved to the
	  general swatch group, even if deleteSwatches is true, its equivalent 
	  process color is not created like the documentation says. Only 
	  AISwatchGroupSuite::RemoveSwatch with deleteCustomColor set to true 
	  will delete the last reference to a used spot color. (1569455)

	3.AISwatchLibrariesSuite::SelectNthDocumentSwatchIfVisible is not fully 
	  implemented and should not be used. (1560539)

	4.AITracingSuite::SetSourceArtChanged, description says this member 
	  reports whether the source art has changed, but actually sets whether 
	  the source art has changed using the AIBoolean parameter. (1549617)

	5.AIUserSuite::IUAIRealString/IUStringToAIReal, description says these
	  functions convert to/from C strings which is incorrect as they convert
	  to/from Pascal strings. (1537963)

______________________________________________________________________
- AIActionManagerSuite::PlayActionEvent does not update document context within 
  current plug-in call: (1348729)

  When creating a new document through the plug-in API that new document should
  be the context under which future operations run. 

  Using AIDocumentSuite::New functions correctly, however using 
  AIActionManagerSuite::PlayActionEvent with kAINewDocumentAction does not. This 
  problem also occurs with other actions such as, kAIOpenDocumentAction and 
  kAICloseDocumentAction.

  Possible workarounds for this issue are:

  	1. Use provided suite functions and not the action if possible, for 
	   instance, use the AIDocumentSuite and AIDocumentList suite to perform 
	   new, open and close operations on a document.

	2. Use a timer and callback function to return control to Illustrator 
	   after performing an action using the AIActionManagerSuite.


***********************************************************
7. Developer Support and Adobe Partner Programs
***********************************************************
If you require developer support for the Illustrator CS3 SDK, you may 
purchase single or multi-pack developer support cases. Information on
purchasing developer support cases can be found at:

	http://partners.adobe.com/public/developer/support/index.html

If you are a partner who extends, markets, or sells Adobe products or
technology, you may want to consider membership in the Adobe Solution
Partner Program. The program provides developer support, timely product
information, as well as opportunities to participate in various marketing
activities. To learn more about the program, point your browser to:

	http://partners.adobe.com/public/asn/solutionpartner/detail.html 

or contact one of the following locations.

In the U.S., Canada, and Mexico: 
	Adobe Solution Partner Program
	Adobe Systems Incorporated 
	PO Box 2205
	Beaverton, OR 97005 
	Tel: 1-800-685-3510 (toll free in the US and Canada only) or
	     206-675-6145 
	Fax: 206-675-6872
	E-mail: solutionpartner@adobe.com 

In Europe, Middle East, and Africa: 
	Adobe Solution Partner Program
	Adobe Systems Incorporated
	Postbus 20623
	1001 NP Amsterdam
	The Netherlands
	Tel: +31 20 582 0850
	Fax: +31 20 582 0851
	E-mail: eurosolutionpartner@adobe.com 

In Japan: 
	Adobe Solution Partner Program
	Adobe Systems Co., Ltd. 
	Shinjuku Oak Tower 16F 6-8-1 Nishishinjuku, Shinjuku-ku, 
	  Tokyo 163-6016
	Japan
	Tel: 03-5740-2620 
	Fax: 03-5740-2621 
	E-mail: japanpartner@adobe.com
	http://partners.adobe.com/

In Asia Pacific and Latin America:
	Adobe Solution Partner Program
	Adobe Systems Incorporated
	45th Floor, One San Miguel Avenue Building
	San Miguel Avenue corner Shaw Boulevard, Ortigas Center
	Pasig City, Metro Manila 1600
	Philippines
	Tel: +(63) 2-702-2189
	Fax: +(63) 2-636-8534
	E-mail: apacsolutionpartner@adobe.com

As always, any plug-ins you create with this SDK can be sold or distributed 
royalty free.

_____________________________________________________________________________
Adobe and Illustrator are either registered trademarks or trademarks of Adobe 
Systems Incorporated in the United States and/or other countries. Windows is 
either a registered trademark or trademark of Microsoft Corporation in the 
United States and/or other countries. Macintosh is a trademark of Apple 
Computer, Inc., registered in the United States and other countries. All 
other brand and product names are trademarks or registered trademarks of 
their respective holders.
_____________________________________________________________________________

Copyright 2007 Adobe Systems Incorporated. All rights reserved.