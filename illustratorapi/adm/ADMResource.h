/*******************************************************************************
*
* ADMResource.h -- ADM Resource IDs
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
* Started by Dave Lazarony, 12 May 1996
*
********************************************************************************/

/** @file ADMResource.h ADM Resource IDs */

#ifndef __ADMResource__
#define __ADMResource__


// -----------------------------------------------------------------------------
//	ADM picture IDs

/** @ingroup AdmResources Picture identifier */
#define kADMAttentionPictureID					-1000
/** @ingroup AdmResources Picture identifier */
#define kADMErrorPictureID						-1001

/** @ingroup AdmResources Picture identifier */
#define kADMSliderPictureID						-16000
/** @ingroup AdmResources Picture identifier */
#define kADMSliderSelectedPictureID				-16001
/** @ingroup AdmResources Picture identifier */
#define kADMSliderDisabledPictureID				-16002
/** @ingroup AdmResources Picture identifier */
#define kADMXPSliderPictureID					-16003		// majones 10/25/2001 - XP Slider
/** @ingroup AdmResources Picture identifier */
#define kADMNewEntryPictureID					-16010
/** @ingroup AdmResources Picture identifier */
#define kADMNewEntryColorPictureID				-16011
/** @ingroup AdmResources Picture identifier */
#define kADMNewEntryDisabledPictureID			-16012
/** @ingroup AdmResources Picture identifier */
#define kADMDeleteEntryPictureID				-16020
/** @ingroup AdmResources Picture identifier */
#define kADMDeleteEntryColorPictureID			-16021
/** @ingroup AdmResources Picture identifier */
#define kADMDeleteEntryDisabledPictureID		-16022
/** @ingroup AdmResources Picture identifier */
#define kADMUpSpinArrowPictureID				-16040
/** @ingroup AdmResources Picture identifier */
#define kADMUpSpinArrowDisabledPictureID		-16042
/** @ingroup AdmResources Picture identifier */
#define kADMDownSpinArrowPictureID				-16050
/** @ingroup AdmResources Picture identifier */
#define kADMDownSpinArrowDisabledPictureID		-16052
/** @ingroup AdmResources Picture identifier */
#define kADMLeftSpinArrowPictureID				-16060
/** @ingroup AdmResources Picture identifier */
#define kADMLeftSpinArrowDisabledPictureID		-16062
/** @ingroup AdmResources Picture identifier */
#define kADMRightSpinArrowPictureID				-16070
/** @ingroup AdmResources Picture identifier */
#define kADMRightSpinArrowDisabledPictureID		-16072
/** @ingroup AdmResources Picture identifier */
#define kADMRightPopupArrowPictureID			-16080
/** @ingroup AdmResources Picture identifier */
#define kADMRightPopupArrowDisabledPictureID	-16082
/** @ingroup AdmResources Picture identifier */
#define kADMDownPopupArrowPictureID				-16090
/** @ingroup AdmResources Picture identifier */
#define kADMDownPopupArrowDisabledPictureID		-16092
/** @ingroup AdmResources Picture identifier */
#define kADMHierarchyListExpandPictureID		-16094
/** @ingroup AdmResources Picture identifier */
#define kADMHierarchyListCollapsePictureID		-16095
/** @ingroup AdmResources Picture identifier */
#define kADMXPHierarchyListExpandPictureID		-16098		// majones 10/29/2001 - XP Discolsure Triangles
/** @ingroup AdmResources Picture identifier */
#define kADMXPHierarchyListCollapsePictureID	-16099		// majones 10/29/2001 - XP Discolsure Triangles
// [cpaduan] 7/16/01 - Picture IDs for icons only needed for Mac OS X.
#if Platform_Carbon
/** @ingroup AdmResources Picture identifier */
#define kADMHierarchyListExpandMacOSXPictureID	-16096
/** @ingroup AdmResources Picture identifier */
#define kADMHierarchyListCollapseMacOSXPictureID -16097
/** @ingroup AdmResources Picture identifier */
#define kADMMacOSXResizePictureID				-16110
#endif
// majones 10/4/2001 - Windows XP PNG Icons
/** @ingroup AdmResources Picture identifier */
#define kADMNormalDialPictureID					-16030
/** @ingroup AdmResources Picture identifier */
#define kADMResizePictureID						-16100

// DRL 2004-08-17   PNGs for CS2 Tab Palette Look.
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontLeftNoGripPictureID			-16200
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontLeftCyclePictureID			-16201
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontLeftFillPictureID			-16202
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontCenterPictureID				-16203
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontCenterFillPictureID			-16204
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontRightPictureID				-16205
/** @ingroup AdmResources Picture identifier */
#define kADMTabFrontRightFillPictureID			-16206
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackLeftPictureID				-16207
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackLeftFillPictureID			-16208
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackCenterPictureID				-16209
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackCenterFillPictureID			-16210
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackRightPictureID				-16211
/** @ingroup AdmResources Picture identifier */
#define kADMTabBackRightFillPictureID			-16212
/** @ingroup AdmResources Picture identifier */
#define kADMFlyoutShapePictureID				-16213
/** @ingroup AdmResources Picture identifier */
#define kADMFlyoutShapeFillPictureID			-16214
/** @ingroup AdmResources Picture identifier */
#define kADMOptionFlyoutPictureID				-16215
/** @ingroup AdmResources Picture identifier */
#define kADMOptionFlyoutRolloverPictureID		-16216

// -----------------------------------------------------------------------------
//	ADM cursor IDs

/** @ingroup AdmResources
	Cursor identifier for a beam cursor. */
#define kADMIBeamCursorID						-1
/** @ingroup AdmResources
	Cursor identifier for a cross cursor. */
#define kADMCrossCursorID						-2
/** @ingroup AdmResources
	Cursor identifier for a wait cursor. */
#define kADMWaitCursorID						-3
/** @ingroup AdmResources
	Cursor identifier for an arrow cursor. */
#define kADMArrowCursorID						-4
/** @ingroup AdmResources
	Cursor identifier for a cancel cursor. */
#define kADMCancelCursorID						-5
/** @ingroup AdmResources
	Cursor identifier for a finger cursor. */
#define kADMFingerCursorID						-6
/** @ingroup AdmResources
	Cursor identifier for a fist cursor. */
#define kADMFistCursorID						-7
/** @ingroup AdmResources
	Cursor identifier for a plus-sign cursor. */
#define kADMFistPlusCursorID					-8
/** @ingroup AdmResources
	Cursor identifier for a cursor for platform-specific controls. */
#define kADMHostControlsCursorID				-9

/** @ingroup AdmResourcesCursor
	Cursor identifier for the smallest cursor. */
#define kADMSmallestCursorID					kADMHostControlsCursorID
/** @ingroup AdmResourcesCursor
	Cursor identifier for the largest cursor. */
#define kADMLargestCursorID						kADMIBeamCursorID


// -----------------------------------------------------------------------------
//	OR this flag with the dialog style of a Windows dialog resource and the
//	dialog's units are read as Pixel Units instead of Dialog Units.

/** @ingroup AdmResources
	Bit flag to OR with the dialog style of a Windows dialog resource
	in order to read units as Pixel Units instead of Dialog Units.*/
#define kADMPixelUnitsDialogStyle				0x0020


// -----------------------------------------------------------------------------
//	Popup Control Dialog IDs

/** @ingroup AdmResources Predefined pop-up slider. */
#define kADMPopupSliderDialogID					-2000		//1900 - 2000 reserved for ADM Sliders
/** @ingroup AdmResources  Predefined pop-up dial. */
#define kADMPopupDialDialogID					-2010       //2001 - 2010 reserved for ADM Dials


#endif	// __ADMResource__
