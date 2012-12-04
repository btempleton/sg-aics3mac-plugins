#ifndef __AI120User__
#define __AI120User__

/*
 *        Name: AI120User.h
 *   $Revision: 15 $
 *      Author:
 *        Date:
 *     Purpose: Adobe Illustrator User Utilities Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIUser.h"

#include "AIHeaderBegin.h"

/** @file AI120User.h */

/*******************************************************************************
 **
 ** Types
 **
 **/
struct AI120PlatformFileDlgOpts
{
#ifdef WIN_ENV

	/** Adds a file-type filter with default pattern (*.*)
		(Note that this function does not return an error code.)
			@param desc		Description of file type.
		*/
	void AddFilter(const ai::UnicodeString &desc);

	/** Adds a file-type filter with an \c ASUnicode pattern.
		(Note that this function does not return an error code.)
			@param desc		Description of file type.
			@param pattern	One or more Windows wildcard patterns to filter
				for the file type, separated with semicolons (;).
				For example, <code>Addfilter("JPEG Files", "*.jpg;*.jpeg");</code>
		*/
	void AddFilter(const ai::UnicodeString &desc, const ASUnicode *pattern);

	/** Adds a file-type filter with a \c UnicodeString pattern.
		(Note that this function does not return an error code.)
			@param desc		Description of file type.
			@param pattern	One or more Windows wildcard patterns to filter
				for the file type, separated with semicolons (;).
				For example, <code>Addfilter("JPEG Files", "*.jpg;*.jpeg");</code>
	*/
	void AddFilter(const ai::UnicodeString &desc, const ai::UnicodeString &pattern);

	/** Retrieves a single string containing type descriptions and patterns suitable for
		Windows dialog functions.
		(Note that this function returns a string value, not an error code.)
		 	@return A string containing a series of null-delimited descriptions
		 		and patterns, terminated by a double-null. For example:
				"first description\0first pattern\0...last description\0last pattern\0\0"
		 */
	const ai::UnicodeString &GetFilter() const;

	private:
	ai::UnicodeString filterStr;
#endif
};

/*******************************************************************************
 **
 **	Constants
 **
 **/

// v.12.0
#define kAI120UserSuite				kAIUserSuite
#define kAIUserSuiteVersion7		AIAPI_VERSION(7)
#define kAI120UserSuiteVersion		kAIUserSuiteVersion7
#define kAI120UserVersion			kAI120UserSuiteVersion


/** @ingroup Suites
	This suite provides utility functions for working with Illustrator,
	including unit conversion utilities and a progress bar.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI120UserSuite and \c #kAI120UserVersion.
	*/
struct AI120UserSuite {

	/** Reports whether a user has canceled the current operation.
		(Note that this function returns a boolean value, not an error code.)
			@return	True if the user has canceled an operation
				by pressing Command-dot or clicking Cancel or Stop in the
				progress bar.
			@see \c #AICustomProgressSuite
		*/
	AIAPI AIBoolean (*Cancel) ( void );

	/** Updates the progress bar.
		(Note that this function does not return an error code.)
			@param current A number between 0 and \c max that represents
				how far the operation has progressed.
			@param max The maximum value, representing 100% progress.
			@see \c #AICustomProgressSuite
		*/
	AIAPI void (*UpdateProgress) ( long current, long max );

	/**	Sets the text message displayed in the progress bar. If not provided,
		the text line is blank.
		(Note that this function does not return an error code.)
			@param text The text message.
			@see \c #AICustomProgressSuite
		*/
	AIAPI void (*SetProgressText) ( const ai::UnicodeString& text );

	/** Explicitly close the progress bar if one is currently shown.
		(Note that this function does not return an error code.)
			@see \c #AICustomProgressSuite
		*/
	AIAPI void (*CloseProgress) ( void );

	/**	Converts a number of document points to a Unicode string, using
		the period as a decimal separator.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param precision The number of digits to the right of the decimal,
				in the range [0..4].
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
	AIAPI void (*AIRealToString) ( AIReal value, short precision, ai::UnicodeString& string );

	/**	Converts a Unicode string containing a number to an \c #AIReal value,
		using the period as a decimal separator.
		(Note that this function does not return an error code.)
			@param string The string to convert.
			@param value  [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
		*/
	AIAPI void (*StringToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/**	Converts a number of document points to a C string, using the localized
		international utilities (IU) decimal separator.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param precision The number of digits to the right of the decimal,
				in the range [0..4].
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
	AIAPI void (*IUAIRealToString) ( AIReal value, short precision, unsigned char *string );

	/**	Converts a C string containing a number to an \c #AIReal value,
		using the localized international utilities (IU) decimal separator.
		(Note that this function does not return an error code.)
			@param string The string to convert.
			@param value  [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
		*/
	AIAPI void (*IUStringToAIReal) ( unsigned char *string, AIReal *value );

	/**	Converts a number of document points to a formatted Unicode string containing
		a number and ruler units, using the localized international utilities (IU)
		decimal separator, and the user preferences for precision.
		Uses the currently set ruler units, which can be inches, points, or centimeters.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
	AIAPI AIErr (*IUAIRealToStringUnits) ( AIReal value, ai::UnicodeString& string );

	/** Converts a formatted Unicode string containing a number expressed in ruler units
		to an \c #AIReal value in points. The current ruler units for the artwork
		are used as the original units to scale the result, and the user's
		preferences for precision are applied.
		(Note that this function does not return an error code.)
			@param string The string to convert, which uses the localized international utilities (IU)
				decimal separator. It can contain a unit specifier, one of "in", "pt", or "cm".
				If no unit specifier is included, uses the current ruler units.
			@param value [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
	  	*/
	AIAPI void (*IUStringUnitsToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/** Retrieves a string representing the current ruler units.
			@param format The format for the result, one of:
				<br> \c #kShortUnits
				<br> \c #kLongSingularUnits
				<br> \c #kLongPluralUnits
				<br> If, for instance, the current unit is inches, the returned string
				would be "in", "inch", or "inches".
			@param string [out] A buffer in which to return the units string, at least 20 characters.
		*/
	AIAPI AIErr (*GetUnitsString) ( short format, ai::UnicodeString& string );

	/**	Converts an Illustrator units constant value to an \c #ADMUnits constant value.
		For example, the equivalent of \c #kPointsUnits is \c #kADMPointUnits.
			@param aiUnits The value to convert.
			@param admUnits [out] A buffer in which to return the converted value.
		*/
	AIAPI AIErr (*AIUnitsToADMUnits) ( short aiUnits, ADMUnits *admUnits);

	/**	Converts an \c #ADMUnits constant value to an Illustrator units constant value.
		For example, the equivalent of \c #kADMPointUnits is \c #kPointsUnits.
			@param admUnits The value to convert.
			@param aiUnits [out] A buffer in which to return the converted value.
		*/
	AIAPI AIErr (*ADMUnitsToAIUnits) ( ADMUnits admUnits, short *aiUnits);

	/**	Retrieves the base name of a global object, stripping off any additional
		token that was added to make the name unique (by a function such as
				\c #AICustomColorSuite::NewCustomColorName(), for example).
			@param name [in, out] A string in which to pass a unique name and
				return the base name. The string is modified in place.
		*/
	AIAPI AIErr (*GetGlobalObjectDisplayName)( ai::UnicodeString& name );

	/** Opens the appropriate application to edit a placed or raster object.
		This is equivalent to an option-double-click on the object with the selection tool.
			@param art The placed or raster art object.
			@return \c #kApplicationNotFoundErr error if the application is not found.
				<br> \c #kObjectNotLinkedErr error if the object is not a placed or raster object.
		*/
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	/** Makes Illustrator idle. <<what does it mean for it to be idle?>> */
	AIAPI AIErr (*AppIdle) ( void );

	/**	<<what does this do, and when should it be used?>>
			@param menu
			@param fileSpec
		*/
	AIAPI AIErr (*BuildDirectoryMenu) ( AIPlatformMenuHandle menu, const ai::FilePath &fileSpec);

	/**	<<what does this do, and when should it be used?>>
			@param fileSpec
			@param index
		*/
	AIAPI AIErr (*GetIndexedDirectorySpec) ( ai::FilePath &fileSpec, int index);

	/**	<<what does this do, and when should it be used?>>
			@param fileSpec
		*/
	AIAPI AIErr (*RevealTheFile) ( const ai::FilePath &fileSpec);

	/** Disables (dims) the cancel or stop button in the progress bar.
		(Note that this function does not return an error code.)
			@see \c #AICustomProgressSuite
		*/
	AIAPI void (*DisableProgressCancel) ( void );

	/**	Converts a file specification to a path string.
			@param fileSpec	 The file specification.
			@param path	[out] A buffer in which to return the path string.
		*/
	AIAPI AIErr (*SPPlatformFileSpecification2Path) ( const SPPlatformFileSpecification *fileSpec, char *path );

	/**	Converts a path string to a file specification.
			@param path	The path string.
			@param fileSpec	[out] A buffer in which to return the file specification.
		*/
	AIAPI AIErr (*Path2SPPlatformFileSpecification) ( const char *path, SPPlatformFileSpecification *fileSpec );

	/** Reports whether it is safe to allocate memory. Call when a timer
		or other  asynchronous event triggers an action that allocates memory.
		Not needed when handling notifications or user events; the plug-in does not receive
		these when it is not ok to allocate memory.
		(Note that this function returns a boolean value, not an error code.)
			@param True if it is safe to allocate memory. False if it is not safe; in this case,
				reschedule the action and try again later.
		*/
	AIAPI AIBoolean (*OKToAllocateMemory) ( void );

	// New for AI 11
	/** Retrieves the current date and time.
			@param ioValue [out] A buffer in which to return the current date-time value.
		*/
	AIAPI AIErr (*GetDateAndTime)(AIUserDateTime *ioValue);

	/* Formats a date into a Unicode string.
			@param ioValue The date to format, or \c NULL to format the current date-time value.
			@param formatFlag The format to use, one of:
				<br> \c #kAIShortDateFormat
				<br> \c #kAILongDateFormat
				<br> \c #kAIAbbrevDateFormat
			@param dateStringUS [out] A buffer in which to return the formatted date string.
		*/
	AIAPI AIErr (*GetDateString)(const AIUserDateTime *ioValue, const int formatFlag, ai::UnicodeString& dateStringUS);

	/* Formats a time into a Unicode string.
			@param ioValue The time to format, or \c NULL to format the current date-time value.
			@param formatFlag The format to use, one of:
				<br> \c #kAIShortTimeFormat
				<br> \c #kAILongTimeFormat
			@param dateStringUS [out] A buffer in which to return the formatted time string.
		*/
	AIAPI AIErr (*GetTimeString)(const AIUserDateTime *ioValue, const int formatFlag, ai::UnicodeString& dateStringUS);

	/** Retrieves the year value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetYear)(const AIUserDateTime *ioValue, int *year);

	/** Retrieves the month value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetMonth)(const AIUserDateTime *ioValue, int *month);

	/** Retrieves the day value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetDay)(const AIUserDateTime *ioValue, int *day);

	/** Retrieves the hour value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetHour)(const AIUserDateTime *ioValue, int *hour);

	/** Retrieves the minute value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetMinute)(const AIUserDateTime *ioValue, int *minute);

	/** Retrieves the second value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetSecond)(const AIUserDateTime *ioValue, int *second);

	/** Retrieves the day-of-week value from a date-time.
			@param ioValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetDayOfWeek)(const AIUserDateTime *ioValue, int *dayOfWeek);

	/**	Launches an application, and optionally opens the current document in it.
			@param spFileSpec The file specification for the application's executable.
			@param openDoc True to open the current document in the new application.
		*/
	AIAPI AIErr (*LaunchApp)(const ai::FilePath &spFileSpec, ASBoolean openDoc);

	/** Generates an appropriate name for a a named object, such as
		a layer, swatch, or style, according to the naming rules for that
		collection.
			@param set The naming rules.
			@param name [out] A buffer in which to return the generated name.
				Must be at least \c #AIAutoNameGenerator::maximumLength + 1
				\c #ASUnicode elements in size.
		*/
	AIAPI AIErr (*NextName) (AIAutoNameGenerator* set, ASUnicode* name);

	/** Generates an appropriate name for a copy of a named object, such as
		a layer, swatch, or style, according to the naming rules for that
		collection.
			@param set The naming rules.
			@param name [out] A buffer in which to return the generated name.
				Must be at least \c #AIAutoNameGenerator::maximumLength + 1
				\c #ASUnicode elements in size.
 		*/
    AIAPI AIErr (*CopyOfName) (AIAutoNameGenerator* set, const ASUnicode* original, ASUnicode* copy);

	/** Tests for equality of names within a collection of named objects.
		Use in the \c #AIAutoNameGenerator::HasName() callback function
		to test whether an automatically generated name matches a name
		already in the collection.
			@param name1 The first name.
			@param name2 The second name.
			@param same [out] A buffer in which to return true if the names
				are the same.
		*/
	AIAPI AIErr (*SameName) (const ASUnicode* name1, const ASUnicode* name2, AIBoolean* same);

	/** Not implemented. (Installs a custom progress reporting mechanism.)
			@return \c #kNotImplementedErr.
	  */
	AIAPI AIErr (*PushCustomProgress) (AICustomProgressSuite *suite);

	/**  Not implemented. (Removes the most recently installed custom progress reporting mechanism.)
			@return \c #kNotImplementedErr.
	  */
	AIAPI AIErr (*PopCustomProgress) ();

	/** Opens a platform-specific dialog for saving a file.
     		@param title Dialog title.
			@param AI120PlatformFileDlgOpts File types to save. Can be \c NULL.
			@param forceLocalFileView True to inhibit Version Cue view.
			@param defaultName Default file name to appear in dialog. Can be \c NULL.
			@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
				return the full path of the file chosen by the user.
		*/
	AIAPI AIErr (*PutFileDialog)(const ai::UnicodeString &title, const AI120PlatformFileDlgOpts*, AIBool8 forceLocalFileView, const ai::UnicodeString &defaultName, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for opening a file.
     		@param title Dialog title.
			@param AI120PlatformFileDlgOpts File types to open. Can be \c NULL.
			@param forceLocalFileView True to inhibit Version Cue view.
			@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
				return the full path of the file chosen by the user.
	  */
	AIAPI AIErr (*GetFileDialog)(const ai::UnicodeString &title, const AI120PlatformFileDlgOpts*, AIBool8 forceLocalFileView, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for choosing a folder.
     		@param title Dialog title.
			@param forceLocalFileView True to inhibit Version Cue view.
			@param ioFilePath [in, out] A buffer in which to pass the folder to browse or \c NULL, and
				return the full path of the folder chosen by the user.
	  */
	AIAPI AIErr (*GetDirectoryDialog)(const ai::UnicodeString &title, AIBool8 forceLocalFileView, ai::FilePath &ioFilePath);

	/** Displays an alert dialog with a warning icon and OK and Cancel buttons.
			@param msg The message to display.
			@param defaultOk True to make the OK button the default, false to make Cancel the default.
			@param dontShowKey A preference key to use with the "Do not show again" checkbox,
				in which to store the user's choice and save it in the application preferences file.
				When \c NULL, the dialog does not include the checkbox.
		*/
	AIAPI AIBoolean (*OKCancelAlert) (const ai::UnicodeString& msg, AIBoolean defaultOk, const char* dontShowKey);
};

/*
	Inline members
*/
#ifdef WIN_ENV
	inline void AI120PlatformFileDlgOpts::AddFilter(const ai::UnicodeString &desc)
	{
		const ASUnicode allFiles[] = {'*', '.', '*', 0};
		AddFilter(desc, ai::UnicodeString(allFiles));
	}

	inline void AI120PlatformFileDlgOpts::AddFilter(const ai::UnicodeString &desc, const ai::UnicodeString &pattern)
	{
		if (!desc.empty() && !pattern.empty())
		{
			const ai::UnicodeString::size_type len = filterStr.length();
			if (len)
				filterStr.erase(len-1);	// erase one null of the previous double null terminators
			filterStr.append(desc);
			filterStr.append(1, 0);
			filterStr.append(pattern);
			filterStr.append(2, 0);
		}
	}

	inline void AI120PlatformFileDlgOpts::AddFilter(const ai::UnicodeString &desc, const ASUnicode *pattern)
	{
		AddFilter(desc, ai::UnicodeString(pattern));
	}

	inline const ai::UnicodeString &AI120PlatformFileDlgOpts::GetFilter() const
	{
		return filterStr;
	}
#endif

#include "AIHeaderEnd.h"

#endif // AI120User

