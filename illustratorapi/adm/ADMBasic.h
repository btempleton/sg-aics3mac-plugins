/*******************************************************************************
*
* ADMBasic.h -- ADM Basic Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by Dave Lazarony, 09 Mar 1996
*
********************************************************************************/

/** @file ADMBasic.h ADM Basic Suite */

#ifndef __ADMBasic__
#define __ADMBasic__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"

// -----------------------------------------------------------------------------

/** The maximum number of characters that can be used in file type specifications.
		@see \c #ADMPlatformFileTypesSpecification3 */
#define kADMMaxFilterLength (256)

/** Return values for the question and yes-no dialog invocation functions,
	that indicate which button was used to dismiss the dialog.
		@see \c #ADMBasicSuite10::QuestionAlert(), \c #ADMBasicSuite10::YesNoAlert(), \c #ADMBasicSuite10::SetAlertButtonText()
		<br> \c #ADMBasicSuite10::QuestionAlertW(), \c #ADMBasicSuite10::YesNoAlertW(), \c #ADMBasicSuite10::SetAlertButtonTextW()*/
enum ADMAnswer
{
	/** The left button, whose default label is "No". */
	kADMNoAnswer = 0,
	/** The right button, whose default label is "Yes". */
	kADMYesAnswer,
	/** The middle button, whose default label is "Cancel". */
	kADMCancelAnswer,
	/** Internal */
	kADMDummyAnswer = 0xFFFFFFFF
};

#ifndef __cplusplus
typedef enum ADMAnswer ADMAnswer;
#endif

#ifndef __cplusplus
typedef enum ADMChoice ADMChoice;
#endif

/** The screen mode for the document window.
    @see \c #ADMBasicSuite10::SetWindowUIMode(),
    	\c #ADMBasicSuite10::GetWindowUIMode()
    */
enum ADMWindowUIMode
{
	/** The document window is a user-resizable window within the application window.
		This corresponds to "Standard Screen Mode" in the Tools palette. */
	kADMUIMode_Freeform,
	/** The document window fills the screen, with the application menu at the top
		but no title bar.
		This corresponds to "Full Screen Mode with Menu Bar" in the Tools palette.  */
	kADMUIMode_FullScreen,
	/** The document window fills the screen, with neither the application menu
		nor a title bar.
		This corresponds to "Full Screen Mode" in the Tools palette. */
	kADMUIMode_FullScreenNoMenu,
	/** The document window fills the screen, has no title bar, and cannot be resized
		vertically.
		This corresponds to "Maximized Screen Mode" in the Tools palette. */
	kADMUIMode_Maximized,

	kADMUIMode_Dummy = 0xFFFFFFFF
};

/** The overall display brightness for the background of dialog windows.
    @see \c #ADMBasicSuite10::SetUIBrightness(),
    	\c #ADMBasicSuite10::GetUIBrightness()
    */
enum ADMUIBrightness
{
	kADMUIBright_default,
	kADMUIBright_dark1,
	kADMUIBright_dark2,
	kADMUIBright_dark3,
	kADMUIBright_dark4,

	kADMUIBright_dummy = 0xFFFFFFFF
};

// -----------------------------------------------------------------------------

#ifdef MAC_ENV

	/** File type specification in Mac OS.	*/
	struct _t_ADMPlatformFileTypesSpecification
	{
		/** An array of file type codes, as defined in Mac OS. */
		ADMUInt32* types;
		/** The number of members of the \c types array. */
		ADMInt16 numTypes;
	};

	/**	 File type specification in Mac OS. 	*/
	typedef struct _t_ADMPlatformFileTypesSpecification ADMPlatformFileTypesSpecification;

	/**	File type specification in Mac OS. 	*/
	struct _t_ADMPlatformFileTypesSpecification3
	{
		/** An array of file type codes, as defined in Mac OS. */
		ADMUInt32* types;
		/** The number of members of the \c types array. */
		ADMInt16 numTypes;
		/** A character array containing a file-specification string. */
		char filter[kADMMaxFilterLength];
	};

	/**  File type specification */
	typedef struct _t_ADMPlatformFileTypesSpecification3 ADMPlatformFileTypesSpecification3;

#else

	/** File type specification in Windows. */
	typedef struct
	{
		/** A character array containing a file-specification string. */
		char filter[kADMMaxFilterLength];
	}
	ADMPlatformFileTypesSpecification, ADMPlatformFileTypesSpecification3;

#endif


// =============================================================================
//		* ADM Basic Suite
// =============================================================================

/// Basic suite name
#define kADMBasicSuite ("ADM Basic Suite")

/// Basic suite version
#define kADMBasicSuiteVersion10 10

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides utility functions that allow you to work with platform string
	and cursor resources, tool tips, and context menus. Additional utilities
	include conversion functions, accessors for application-wide properties
	and preferences, and platform-independent access to utilities such as
	the beep, and predefined dialogs such as error and message alerts.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMBasicSuite and \c #kADMBasicSuiteVersion10.
	*/
struct ADMBasicSuite10
{

	// *** This suite is OPEN.
	// *** It will ship with Illustrator 13.

	/** Retrieves a platform-specific  string resource as a C string.
			\li	In Mac OS, reads strings from a ’STR#’ string list resource, and converts
				them from Pascal to C strings. The index is 1-based.
			\li In Windows, reads a string from a string resource, identified with an ID
				plus index.
			@param inPluginRef		This plug-in reference.
			@param inStringID		The string resource identifier in Windows. Ignored in Mac OS.
			@param inStringIndex	The 1-based position index of the string in the list.
								In Windows, added to the ID to identify the resource.
			@param outString		[out] A buffer in which to return the string.
			@param inMaxLen			The number of characters in the buffer.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLen);

	/** Retrieves a platform-specific  string resource as a Unicode string.
			\li	In Mac OS, reads strings from a ’STR#’ string list resource, and converts
				them from Pascal to Unicode strings. The index is 1-based.
			\li In Windows, reads a string from a string resource, identified with an ID
				plus index, and converts to Unicode.
			@param inPluginRef		This plug-in reference.
			@param inStringID		The string resource identifier in Windows. Ignored in Mac OS.
			@param inStringIndex	The 1-based position index of the string in the list.
								In Windows, added to the ID to identify the resource.
			@param outString		[out] A buffer in which to return the string.
			@param inMaxLen			The number of characters in the buffer.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetIndexStringW)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, ADMUnicode* outString, ADMInt32 inMaxLen);

	/** Causes a simple system beep. calling the platform’s standard beep function.
			@return Nothing.
		*/
	void ADMAPI (*Beep)();

	/** Displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a C string, with the platform-specific
		error icon at the left, and an OK button.
			@param inErrorString The text string.
			@return Nothing.
			@see \c #LightweightErrorAlert(), \c #MessageAlert(),  \c #QuestionAlert(),
				\c #SetAlertButtonText(), \c #YesNoAlert()
		*/
	void ADMAPI (*ErrorAlert)(const char* inErrorString);

	/** Displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a Unicode string, with the platform-specific
		error icon at the left, and an OK button.
			@param inErrorString The text string.
			@return Nothing.
			@see \c #MessageAlertW(), \c #LightweightErrorAlertW(), \c #QuestionAlertW(),
				\c #SetAlertButtonTextW(), \c #YesNoAlertW()
		*/
	void ADMAPI (*ErrorAlertW)(const ADMUnicode* inErrorString);

	/** Displays a predefined dialog with an informational message.
		The dialog displays text specified with a C string, with the
		platform-specific message icon at the left, and an OK button.
			@param inMessageString The text string.
			@return Nothing.
			@see \c #ErrorAlert(), \c #LightweightErrorAlert(), \c #QuestionAlert(),
				\c #SetAlertButtonText(), \c #YesNoAlert()
		*/
	void ADMAPI (*MessageAlert)(const char* inMessageString);

	/** Displays a predefined dialog with an informational message.
		The dialog displays text specified with a Unicode string, with the
		platform-specific message icon at the left, and an OK button.
			@param inMessageString The text string.
			@return Nothing.
			@see \c #ErrorAlertW(), \c #LightweightErrorAlertW(), \c #QuestionAlertW(),
				\c #SetAlertButtonTextW(), \c #YesNoAlertW()
		*/
	void ADMAPI (*MessageAlertW)(const ADMUnicode* inMessageString);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a C string, and
		buttons with default labels Yes, No, and Cancel. Use
		\c #SetAlertButtonText() to change the labels.
			@param inQuestionString The text string.
			@return The result, a constant value that indicates
				which button was clicked.
			@see \c #ErrorAlert(), \c #LightweightErrorAlert(), \c #MessageAlert(),
				 \c #YesNoAlert()
		*/
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a Unicode string, and
		buttons with default labels Yes, No, and Cancel. Use
		\c #SetAlertButtonTextW() to change the labels.
			@param inQuestionString The text string.
			@return The result, a constant value that indicates
				which button was clicked.
			@see \c #ErrorAlertW(), \c #LightweightErrorAlertW(), \c #MessageAlertW(),
				 \c #YesNoAlertW()
		*/
	ADMAnswer ADMAPI (*QuestionAlertW)(const ADMUnicode* inQuestionString);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a C string, and
		buttons with default labels Yes and No. Use
		\c #SetAlertButtonText() to change the labels.
			@param inQuestionString The text string.
			@return The result, a constant value that indicates
				which button was clicked.
			@see \c #ErrorAlert(), \c #LightweightErrorAlert(), \c #MessageAlert(),
				\c #QuestionAlert()
		*/
	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a Unicode string, and
		buttons with default labels Yes and No. Use
		\c #SetAlertButtonTextW() to change the labels.
			@param inQuestionString The text string.
			@return The result, a constant value that indicates
				which button was clicked.
			@see \c #ErrorAlertW(), \c #LightweightErrorAlertW(), \c #MessageAlertW(),
				 \c #YesNoAlertW()
		*/
	ADMAnswer ADMAPI (*YesNoAlertW)(const ADMUnicode* inQuestionString);

 	/** Retrieves the dimensions of the screen containing a specified point.
 		Supports multiple monitors.
			@param inPoint The point.
			@param outDimensions [out] A buffer in which to return the screen's bounding box.
			@return True if the point is on any screen, false otherwise.
		*/
	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

 	/** Turns ADM tool tips on and off.
			@param inEnable	True to turn tool tips on, false to turn them off.
			@return Nothing.
			@see \c #ADMDialogSuite10::LoadToolTips(), \c #ShowToolTip(), \c #AreToolTipsSticky()
		*/
	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);

	/** Reports whether ADM tool tips are currently on or off.
			@return True if tool tips are on, false if they are off.
			@see \c #EnableToolTips(), \c #ShowToolTip(), \c #AreToolTipsSticky()
		*/
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();

	/** Converts a floating-point value to a C string.
			@param inValue The floating-point value.
			@param outText [out] A buffer in which to return the string value.
			@param inMaxLen	The number of characters in the buffer.
			@param inUnits Optional. A measurement unit type. The value is
				converted to these units before being converted to a string.
				If this is a unit of linear measure, the input value is assumed to be
				in document points. If this is \c #kADMTimeUnits, the input value
				is assumed to be in frames, and is converted to \c hours:minutes:seconds:frames.
			@param inPrecision The maximum number of decimal places in the result string.
			@param inAlwaysAppendUnits True to append measurement unit type to the numeric value.
			@return None.
			@see \c #StringToValue()
	*/
	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	/** Converts a floating-point value to a Unicode string.
			@param inValue The floating-point value.
			@param outText [out] A buffer in which to return the string value.
			@param inMaxLen	The number of characters in the buffer.
			@param inUnits Optional. A measurement unit type. The value is
				converted to these units before being converted to a string.
				If this is a unit of linear measure, the input value is assumed to be
				in document points. If this is \c #kADMTimeUnits, the input value
				is assumed to be in frames, and is converted to \c hours:minutes:seconds:frames.
			@param inPrecision The maximum number of decimal places in the result string.
			@param inAlwaysAppendUnits True to append measurement unit type to the numeric value.
			@return None.
			@see \c #StringToValueW()
	*/
	void ADMAPI (*ValueToStringW)(float inValue, ADMUnicode* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	/** Converts a C string to a floating-point value.
			@param inText The string value.
			@param outValue [out] A buffer in which to return the floating-point value.
			@param inUnits Optional. A measurement unit type. The value is
				converted to these units from the assumed unit type.
				If this is a unit of linear measure, the original value is assumed to be
				in document points. If this is \c #kADMTimeUnits, the original value
				is assumed to be in frames, and is converted to \c hours:minutes:seconds:frames.
			@return True if the conversion was successful, false otherwise.
			@see \c #ValueToString()
	*/
	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	/** Converts a Unicode string to a floating-point value.
			@param inText The string value.
			@param outValue [out] A buffer in which to return the floating-point value.
			@param inUnits Optional. A measurement unit typeThe value is
				converted to these units from the assumed unit type.
				If this is a unit of linear measure, the original value is assumed to be
				in document points. If this is \c #kADMTimeUnits, the original value
				is assumed to be in frames, and is converted to \c hours:minutes:seconds:frames.
			@return True if the conversion was successful, false otherwise.
			@see \c #ValueToStringW()
		*/
	ADMBoolean ADMAPI (*StringToValueW)(const ADMUnicode* inText, float* outValue, ADMUnits inUnits);

	/** Invokes the platform-specific Open File dialog, with a text
		message specified as a C string.
			@param inMessage Text displayed at the top of the dialog.
			@param inFilter	 Filter that determines what files are displayed.
							\li In Mac OS, list files, types, and/or extensions.
							\li In Windows, list files with	extensions.
			@param inStartingDir	Starting directory.
			@param inStartingFile	Starting file.
			@param outResult [out] A buffer in which to return the file selected by user.
			@return True if a file was found and returned, false otherwise.
  			@see \c #StandardPutFileDialog(), \c #StandardGetDirectoryDialog()
		*/
	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific Open File dialog, with a text
		message specified as a Unicode string.
			@param inMessage Text displayed at the top of the dialog.
			@param inFilter	 Filter that determines what files are displayed.
							\li In Mac OS, list files, types, and/or extensions.
							\li In Windows, list files with	extensions.
			@param inStartingDir	Starting directory.
			@param inStartingFile	Starting file.
			@param outResult [out] A buffer in which to return the file selected by user.
			@return True if a file was found and returned, false otherwise.
  			@see \c #StandardPutFileDialogW(), \c #StandardGetDirectoryDialogW()
		*/
	ADMBoolean ADMAPI (*StandardGetFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific Open Directory dialog, with a text
		message specified as a C string.
			@param inMessage Text displayed at the top of the dialog.
			@param inStartingDir	Starting directory.
			@param outResult [out] A buffer in which to return the directory selected by user.
			@return True if a directory was found and returned, false otherwise.
  			@see \c #StandardPutFileDialog(), \c #StandardGetFileDialog()
		*/
	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific Open Directory dialog, with a text
		message specified as a Unicode string.
			@param inMessage Text displayed at the top of the dialog.
			@param inStartingDir	Starting directory.
			@param outResult [out] A buffer in which to return the directory selected by user.
			@return True if a directory was found and returned, false otherwise.
  			@see \c #StandardPutFileDialog(), \c #StandardGetFileDialog()
		*/
	ADMBoolean ADMAPI (*StandardGetDirectoryDialogW)(const ADMUnicode* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific Save File dialog, with a text
		message specified as a C string.
			@param inMessage Text displayed at the top of the dialog.
			@param inFilter	 Filter that determines what files are displayed.
							\li In Mac OS, list files, types, and/or extensions.
							\li In Windows, list files with	extensions.
			@param inStartingDir	Starting directory.
			@param inStartingFile	Starting file.
			@param outResult [out] A buffer in which to return the file selected by user.
			@return True if a file was successfully saved, false otherwise.
  			@see \c #StandardGetFileDialog(), \c #StandardGetDirectoryDialog()
		*/
	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific Save File dialog, with a text
		message specified as a Unicode string.
			@param inMessage Text displayed at the top of the dialog.
			@param inFilter	 Filter that determines what files are displayed.
							\li In Mac OS, list files, types, and/or extensions.
							\li In Windows, list files with	extensions.
			@param inStartingDir	Starting directory.
			@param inStartingFile	Starting file.
			@param outResult [out] A buffer in which to return the file selected by user.
			@return True if a file was successfully saved, false otherwise.
  			@see \c #StandardGetFileDialogW(), \c #StandardGetDirectoryDialogW()
		*/
	ADMBoolean ADMAPI (*StandardPutFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/** Invokes the platform-specific color picker dialog.
			@param inWhere	The position of the dialog.	 (0, 0) centers the dialog on the screen.
			@param inColor	The initially selected color value.
			@param outColor	[out] A buffer in which to return the selected color.
			@return True if the user selected a color, false otherwise.
  			@see \c #ADMColorToRGBColor()
	*/
	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);

 	/**	Sets measurement unit preferences for the application. You can set up to
		10 preferences. See \c #ADMUnits.

		For example, you might set a preference for the default unit for most measurements
		as the value of \c #kADMAppUnits1, and \c #kADMAppUnits2 as the default units for
		typographic measurements. You could then easily switch the default unit between inches
		and centimeters, for instance, and the typographic unit between points and pixels.
			@param inAppUnits The preference unit constant, \c #kADMAppUnits1 to \c #kADMAppUnits10.
			@param inActualUnits The measurement unit constant to associate with the preference.
			@return Nothing.
			@see \c #GetAppUnits()
	*/
	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);

	/** Retrieves the measurement associated with a developer-defined unit preference.
			@param inAppUnits The preference unit constant, \c #kADMAppUnits1 to \c #kADMAppUnits10.
			@return The measurement unit constant.
			@see \c #SetAppUnits(), \c #ADMUnits.
		*/
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);

	/** Sets whether numbers entered without a units specifier are in points (1/72 inches).
	    Points are the default measurement unit for Illustrator.
			@param inPoints True to make points the default measurement unit, false to
				remove this default.
			@return Nothing.
 	 		@see \c #GetNumbersArePoints()
		*/
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);

	/** Reports whether numbers entered without a units specifier are in points (1/72 inches).
	    Points are the default measurement unit for Illustrator.
			@return True if points are the default measurement unit, false if not.
 	 		@see \c #SetNumbersArePoints()
		*/
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	/** Sets the default small and large increments for spinners, sliders, and scroll bar cursor
		movement.
			@param inUnits The measurement unit for the increment values.
			@param inSmallIncrement	The new small increment value.
			@param inLargeIncrement	The new large increment value.
			@return Nothing.
			@see \c #GetDefaultIncrements(), c #ADMItemSuite9::SetSmallIncrement(),
				\c #ADMItemSuite9::SetLargeIncrement()
	*/
	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	/**	Reports the default small and large increments for spinners, sliders, and scroll bar cursor
		movement.
			@param inUnits The measurement unit for the increment values.
			@param outSmallIncrement [out] A buffer in which to return the small increment value.
			@param outLargeIncrement [out] A buffer in which to return the large increment value.
			@return Nothing.
			@see \c #SetDefaultIncrements(), c #ADMItemSuite9::GetSmallIncrement(),
				\c #ADMItemSuite9::GetLargeIncrement().
		*/
	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);


	/**	Internal. Third-party plug-in developers should use \c #PluginAboutBox().	*/
	void ADMAPI (*AboutBox)(SPPluginRef inPlugin, const char* inText1, const char* inText2);

	/**	Internal. Third-party plug-in developers should use \c #PluginAboutBoxW(). */
	void ADMAPI (*AboutBoxW)(SPPluginRef inPlugin, const ADMUnicode* inText1, const ADMUnicode* inText2);

	/** Reports whether ADM tool tips are currently in the "sticky" state for a dialog.
		This is true if a tool tip is already visible, so that no delay is needed
		before displaying the next tip if the cursor moves over another item.
			@param inDialog	The dialog object.
			@return True if tool tips are sticky; false otherwise.
			@see \c #EnableToolTips(), \c #GetToolTipDelays()
		*/
	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);

	/** Retrieves the tool tips delay time and pop-up duration. You cannot modify these values.
 			@param outPopupDelay [out] A buffer in which to return the delay time, in seconds,
				after the mouse cursor enters the item, until a tool tip is displayed.
				Default is 5 seconds.
			@param outPopdownDelay [out] A buffer in which to return the delay time, in seconds,
				after the tool tip is displayed, until a tool tip is hidden. Default is 5 seconds.
			@return Nothing.
		*/
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	/** Sets the document-window screen mode. This is the equivalent of choosing a
		mode from the bottom of the Tools palette.
			@param inUIMode	The new mode.
			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*SetWindowUIMode)(ADMWindowUIMode inUIMode);

	/** Retrieves the current document-window screen mode.
			@return The mode value.
	*/
	ADMWindowUIMode ADMAPI (*GetWindowUIMode)();

	/** Sets the overall brightness preference for the background
		of dialogs.
			@param inBrightness The new UI brightness value.
			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*SetUIBrightness)(ADMUIBrightness inBrightness);

	/** Retrieves the overall dialog brightness preference.
			@return The UI brightness constant.
	*/
	ADMUIBrightness ADMAPI (*GetUIBrightness)(void);

	/** Sets the persistence preference for palette drawers (the subpanels that
		open when the user clicks on palettes in icon-mode panes).
			@param persistent True to make drawers stay open until dismissed, or
				until another drawer is opened. False to make drawers close
				when the user clicks outside the palette.
	*/
	void ADMAPI (*SetUsePersistentPaletteDrawers)(ADMBoolean persistent);

	/** Retrieves the current palette-drawer persistence setting.
			@return True if the drawers are set to persist, false otherwise.
			@see \c #SetUsePersistentPaletteDrawers()
	*/
	ADMBoolean ADMAPI (*GetUsePersistentPaletteDrawers)(void);

	/** Sets the preference for using animations in user-interface transitions.
			@param useAnimations True to use animation where appropriate.
	*/
	void ADMAPI (*SetUseUIAnimations)(ADMBoolean useAnimations);

	/** Retrieves the current user-interface animations preference.
			@return True if animation is used, false otherwise.
	*/
	ADMBoolean ADMAPI (*GetUseUIAnimations)(void);

	/** Retrieves the working dimensions of the primary screen, which do not include
		the system menus, task bars, and so on.
			@param outDimensions [out] A buffer in which to return the workspace bounding box.
			@return True if dimensions were successfully retrieved, false otherwise.
		*/
	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);

 	/** Retrieves the area available for document windows inside top and bottom docks,
 		if any, and optionally inside side docks.
 			@param inInclSideDocks	When true, return lateral dimensions inside side docks.
 			@param outDimensions [out] A buffer in which to return the bounding box of
 				the area available for document windows.
 			@return True if dimensions were successfully obtained; false otherwise.
 	*/
 	ADMBoolean ADMAPI (*GetDocumentAreaBounds)(ADMBoolean inInclSideDocks, ADMRect* outDimensions);


	/** Retrieves the internal dimensions of the application main window, which is the
		area available for use in placing dialogs.
			@param outDimensions [out] A buffer in which to return the bounding box.
			@return True if dimensions were successfully obtained, false otherwise.
		*/
	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);

 	/**	Sets the default cursor.
			@param inPluginRef This plug-in reference.
			@param inCursorID	The platform-specific cursor resource identifier.
				\li In Mac OS, a 'CURS' value.
				\li In Windows, a \c CURSOR value.
			@return Nothing.
		*/
	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);

 	/** Displays an informational message dialog that describes the plug-in,
		with text specified as C strings.
			@param inTitle	Text displayed in the title bar of the dialog.
			@param inText	Text displayed in the dialog. The box is sized vertically to
				contain the text.
			@return Nothing.
		*/
	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);

 	/** Displays an informational message dialog that describes the plug-in,
		with text specified as Unicode strings.
			@param inTitle	Text displayed in the title bar of the dialog.
			@param inText	Text displayed in the dialog. The box is sized vertically to
				contain the text.
			@return Nothing.
		*/
	void ADMAPI (*PluginAboutBoxW)(const ADMUnicode* inTitle, const ADMUnicode* inText);

	/** Sets the text labels for the buttons of a question dialog, using a C string.
 		Label text returns to the default after each invocation of the dialog.
 			@param inLeftChoice		Text for left button. Default is "No".
			@param inMiddleChoice	Text for middle button. Default is "Cancel".
			@param inRightChoice	Text for right button. Default is "Yes".
			@return Nothing.
			@see \c #QuestionAlert(), \c #YesNoAlert()
		*/
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);

	/** Sets the text labels for the buttons of a question dialog, using a Unicode string.
 		Label text returns to the default after each invocation of the dialog.
 			@param inLeftChoice		Text for left button. Default is "No".
			@param inMiddleChoice	Text for middle button. Default is "Cancel".
			@param inRightChoice	Text for right button. Default is "Yes".
			@return Nothing.
			@see \c #QuestionAlert(), \c #YesNoAlert()
		*/
	void ADMAPI (*SetAlertButtonTextW)(const ADMUnicode* inLeftChoice, const ADMUnicode* inMiddleChoice,
				const ADMUnicode* inRightChoice);

	/** Displays an item tool tip with text specified by a C string.
		The tip is shown for 5 seconds, unless you call \c #HideToolTip()
		before that.
		Does not affect the standard tool tip behavior.
			@param inWhere	The position at which to show the tool tip, in screen coordinates.
			@param inTip	The text string.
		*/
	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTip);

	/** Displays an item tool tip with text specified by a Unicode string.
		The tip is shown for 5 seconds, unless you call \c #HideToolTip()
		before that.
		Does not affect the standard tool tip behavior.
			@param inWhere	The position at which to show the tool tip, in screen coordinates.
			@param inTip	The text string.
			@see \c #EnableToolTips()
		*/
	void ADMAPI (*ShowToolTipW)(const ADMPoint* inWhere, const ADMUnicode* inTip);

	/** Hides a tool tip displayed by calling \c #ShowToolTip().
		Does not affect the standard tool tip behavior.
			@return Nothing.
		*/
	void ADMAPI (*HideToolTip)();


 	/** Creates a context menu, a list object that pop ups when the cursor is over a specific location.
		A combination of mouse states or modifier keys can be used to select an option.
		<br> This list does not have an associated dialog item. Initialize it using the
		\c #ADMListSuite4 and \c #ADMListEntrySuite4.
		<br> Destroy the menu object when you are done with it, using \c #DestroyMenu().
			@param outMenu [out] A buffer in which to return the new context menu list object.
			@return An error code, \c #kNoErr on success.
			@see \c #DestroyMenu(), \c #DisplayMenu()
		*/
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);

	/** Displays a context menu over a dialog at a specified point.
			@param inMenu The context menu list object.
			@param inDialog	The dialog object.
			@param inDialogPoint The position of the menu, in local dialog coordinates.

			@return An error code, \c #kNoErr on success.
			@see \c #DestroyMenu(), \c #CreateMenu()
		*/
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);

	/**	Frees resources associated with a context menu that is no longer needed.
			@param inMenu The context menu list object.
			@return An error code, \c #kNoErr on success.
			@see \c #CreateMenu(), c #DisplayMenu()
		*/
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);


 	/** Retrieves information about why the most recent attempt at dialog creation failed.
	 		@param outError [out] A buffer in which to return the error code. Error
				constants are defined in
				<br>\c ADMDialog.h
				<br>\c ADMTypes.h
				<br>\c ADMCustomResource.h
				<br>\c ADMDialogGroup.h
			@param outErrorData [out] A buffer in which to return data associated with
				the error.
			@return False.
			@see \c #ADMDialogSuite10::Create(), \c #ADMDialogSuite10::Modal(),
				\c #ADMDialogSuite10::CreateGroupInDialog()
		*/
	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outError, ADMInt32* outErrorData);

	/** Converts an ADM standard color to an RGB value.
			@param inADMColor The ADM color constant.
			@param outRGBColor [out] A buffer in which to return the RGB value.
			@return True if the conversion was successful, false otherwise.
			@see \c #ChooseColor()
		*/
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	/** Sets the application refresh rate.
			@param inFPS The new rate, in frames-per-second.
			@return Nothing.
			@see \c #GetAppFPS()
	*/
	void ADMAPI (*SetAppFPS)(float inFPS);

	/**	Reports the application refresh rate.
			@return The rate, in frames-per-second.
			@see \c #SetAppFPS()
		*/
	float ADMAPI (*GetAppFPS)();


	/** Beeps and displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a C string, with the platform-specific
		error icon at the left, and an OK button.

		This version is more efficient and uses fewer resources than \c #ErrorAlert().
		It uses a platform-supplied dialog, rather than creating an ADM dialog.
			@param inErrorString The text string.
			@return Nothing.
			@see \c #MessageAlert(), \c #QuestionAlert(),
				 \c #YesNoAlert(), \c #SetAlertButtonText()
		*/
	void ADMAPI (*LightweightErrorAlert)(const char* inErrorString);

	/** Beeps and displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a Unicode string, with the platform-specific
		error icon at the left, and an OK button.

		This version is more efficient and uses fewer resources than \c #ErrorAlertW().
		It uses a platform-supplied dialog, rather than creating an ADM dialog.
			@param inErrorString The text string.
			@return Nothing.
			@see \c #MessageAlertW(),  \c #QuestionAlertW(),
				 \c #YesNoAlertW(), \c #SetAlertButtonTextW()
		*/
	void ADMAPI (*LightweightErrorAlertW)(const ADMUnicode* inErrorString);

 	/**	Internal */
	ADMBoolean ADMAPI (*LookUpZString)(SPPluginRef inPluginRef,
				const char* inString, char* outString, ADMUInt32* ioBufferSize);

	/**	Internal */
	ADMBoolean ADMAPI (*LookUpZStringW)(SPPluginRef inPluginRef,
				const char* inString, ADMUnicode* outString, ADMUInt32* ioBufferSize);
};

#ifndef __cplusplus
/** @ingroup Suites
	This suite provides utility functions that allow you to work with platform string
	and cursor resources, tool tips, and context menus. Additional utilities
	include conversion functions, accessors for application-wide properties
	and preferences, and platform-independent access to utilities such as
	the beep, and predefined dialogs such as error and message alerts. */
typedef struct ADMBasicSuite10 ADMBasicSuite10;
#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMBasicOld__
#ifdef MAC_ENV
#include "ADMBasicOld.h"
#else
#include ".\Legacy\ADMBasicOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMBasic__
