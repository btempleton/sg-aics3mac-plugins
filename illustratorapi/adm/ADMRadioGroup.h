/*******************************************************************************
*
* ADMRadioGroup.h -- ADM Radio Group Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2003-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
* Started by David Hearst, 15 Jan 2003
*
********************************************************************************/

/** @file ADMRadioGroup.h ADM Radio Group Suite */

#ifndef __ADMRadioGroup__
#define __ADMRadioGroup__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// =============================================================================
//		* ADM Radio Group Suite
// =============================================================================

/// Basic suite name
#define kADMRadioGroupSuite ("ADM Radio Group Suite")

/// Basic suite version
#define kADMRadioGroupSuiteVersion1 1

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite provides functions for managing radio button groups.
	The buttons in a group are mutually exclusive. Selecting any button
	deselects all other buttons in the group.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMRadioGroupSuite and \c #kADMRadioGroupSuiteVersion1.
	*/
struct ADMRadioGroupSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// radio group creation/destruction

	/** Creates a radio-button group in a dialog.
		Use \c #Add() to initialize the group with radio-button items.
		Use \c #Destroy() to free the object when no longer needed.
			@param inDialog The dialog object.
			@param outRadioGroup [out] A buffer in which to return the new radio-group object.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*Create)(ADMDialogRef inDialog, ADMRadioGroupRef* outRadioGroup);

	/** Destroys a radio-group object that is no longer needed, and frees its
		resources, including contained radio button items.
			@param inDialog The dialog object.
			@param inRadioGroup The radio-group object.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*Destroy)(ADMDialogRef inDialog, ADMRadioGroupRef inRadioGroup);

	/** Adds a radio-button item to a radio group. All button items in the group
		must have the same \c #ADMRadioButtonStyle.
			@param inRadioGroup The radio-group object.
			@param inItem The dialog item, of type \c #kADMTextRadioButtonType
				or \c #kADMPictureRadioButtonType,
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*Add)(ADMRadioGroupRef inRadioGroup, ADMItemRef inItem);

	/** Removes a  radio-button item from a radio group.
			@param inRadioGroup The radio-group object.
			@param inItem The dialog item.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*Remove)(ADMRadioGroupRef inRadioGroup, ADMItemRef inItem);

	/** Retrieves the radio-button group to which a radio-button dialog item belongs.
			@param inItem The dialog item.
			@param outRadioGroup [out] A buffer in which to return the radio-group object.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*GetForItem)(ADMItemRef inItem, ADMRadioGroupRef* outRadioGroup);

};

#ifndef __cplusplus
typedef struct ADMRadioGroupSuite1 ADMRadioGroupSuite1;
#endif

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// The following is not necessary until we rev the suite for the first time...
//
//// -----------------------------------------------------------------------------
////	Old versions of suites
//
//#ifndef __ADMRadioGroupOld__
//#ifdef MAC_ENV
//#include "ADMRadioGroupOld.h"
//#else
//#include ".\Legacy\ADMRadioGroupOld.h"
//#endif
//#endif



// -----------------------------------------------------------------------------

#endif	// __ADMRadioGroup__
