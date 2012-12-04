#ifndef __AIMenuMac__
#define __AIMenuMac__

/*
 *        Name:	AIMenuMac.h
 *   $Revision: 4 $
 *      Author:	 
 *        Date:	   
 *     Purpose: Adobe Illustrator 6.0 Mac Menu Suite.	
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

#ifndef __AITypes__
	#include "AITypes.h"
#endif

#ifndef __AIPlugin__
	#include "AIPlugin.h"
#endif

#ifndef __AIMenu__
	#include "AIMenu.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIMacMenuSuite		"AI Mac Menu Suite"
#define kAIMacMenuSuiteVersion	AIAPI_VERSION(3)
#define kAIMacMenuVersion	kAIMacMenuSuiteVersion

#define kSelectorAIMacUpdateMenuItem	kSelectorAIUpdateMenuItem


// These are the options available to a menu item.
#define kMacMenuItemWantsUpdateOption	kMenuItemWantsUpdateOption
#define kMacMenuItemAlwaysEnabled		kMenuItemAlwaysEnabled

// These are the options available to a mac menu group.
#define kMacMenuGroupSortedAlphabeticallyOption	kMenuGroupSortedAlphabeticallyOption


#define kMacAutoEnableMenuItemAction	kAutoEnableMenuItemAction
#define kMacAutoCheckMenuItemAction		kAutoCheckMenuItemAction

#define kMacIfGroup						kIfGroup					
#define kMacIfPath						kIfPath						
#define kMacIfPostscript				kIfPostscript				
#define kMacIfPlaced					kIfPlaced					
#define kMacIfText						kIfText						
#define kMacIfTextPath					kIfTextPath					
#define kMacIfTextFlow					kIfTextFlow					
#define kMacIfTextRun					kIfTextRun					
#define kMacIfGuide						kIfGuide					
#define kMacIfGraphData					kIfGraphData				
#define kMacIfMask						kIfMask						
#define kMacIfEndMask					kIfEndMask					
#define kMacIfNormalGroup				kIfNormalGroup				
#define kMacIfCompoundGroup				kIfCompoundGroup			
#define kMacIfWrapAroundGroup			kIfWrapAroundGroup			
#define kMacIfClipGroup					kIfClipGroup				
#define kMacIfPointText					kIfPointText				
#define kMacIfInPathText				kIfInPathText				
#define kMacIfOnPathText				kIfOnPathText				
#define kMacIfThreadedText				kIfThreadedText				
#define kMacIfRaster					kIfRaster					

#define kMacIfCurrentLayerIsEditable	kIfCurrentLayerIsEditable
#define kMacIfOpenTextEdit				kIfOpenTextEdit				
#define kMacIfAnyPrintingChars			kIfAnyPrintingChars			
#define kMacIfAnyHiddenObjects			kIfAnyHiddenObjects			
#define kMacIfAnyLockedObjects			kIfAnyLockedObjects			
#define kMacIfAnyClipPaths				kIfAnyClipPaths				
#define kMacIfOpenDocument				kIfOpenDocument				
#define kMacIfCMYKDocument				kIfCMYKDocument				
#define kMacIfRGBDocument				kIfRGBDocument				

// These are the modifiers available to a menu item with a command key.
#define kMacItemCmdShiftModifier		kMenuItemCmdShiftModifier
#define kMacItemCmdOptionModifier		kMenuItemCmdOptionModifier
#define kMacItemCmdControlModifier		kMenuItemCmdControlModifier


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef MenuRef AIPlatformMacMenuHandle;
typedef struct _t_MacMenuGroupOpaque *MacMenuGroup;

/*******************************************************************************
 **
 **	Suite
 **
 **/

// These routines replace the corresponding Macintosh Toolbox routines and must
// be used instead. Functions beginning with 'MacX' are Illustrator extensions
// to the Macintosh Toolbox.

typedef struct {

	AIAPI void (*MacEnableItem) ( AIPlatformMacMenuHandle theMenu, short whichItem );
	AIAPI void (*MacDisableItem) ( AIPlatformMacMenuHandle theMenu, short whichItem );
	AIAPI void (*MacGetItem) ( AIPlatformMacMenuHandle theMenu, short whichItem, unsigned char itemString[256] );
	AIAPI void (*MacSetItem) ( AIPlatformMacMenuHandle theMenu, short whichItem, unsigned char itemString[256] );
	AIAPI void (*MacCheckItem) ( AIPlatformMacMenuHandle theMenu, short whichItem, AIBoolean checkIt );
	AIAPI void (*MacGetItemMark) ( AIPlatformMacMenuHandle theMenu, short whichItem, short *markChar );
	AIAPI void (*MacSetItemMark) ( AIPlatformMacMenuHandle theMenu, short whichItem, char markChar );
	AIAPI void (*MacGetItemIcon) ( AIPlatformMacMenuHandle theMenu, short whichItem, short *icon );
	AIAPI void (*MacSetItemIcon) ( AIPlatformMacMenuHandle theMenu, short whichItem, short iconSelector );
	AIAPI void (*MacGetItemStyle) ( AIPlatformMacMenuHandle theMenu, short whichItem, unsigned char *chStyle );
	AIAPI void (*MacSetItemStyle) ( AIPlatformMacMenuHandle theMenu, short whichItem, unsigned char chStyle );
	AIAPI void (*MacXGetItemCmd) ( AIPlatformMacMenuHandle theMenu, short whichItem, short *cmdChar,
				short *modifiers );
	AIAPI void (*MacXSetItemCmd) ( AIPlatformMacMenuHandle theMenu, short whichItem, char cmdChar,
				short modifiers );
	
	AIAPI void (*MacXGetItemMenuGroup) ( AIPlatformMacMenuHandle theMenu, short whichItem,
				MacMenuGroup *group );
	AIAPI void (*MacXAddMenuGroup) ( const char *name, long options, const char *nearGroup,
				MacMenuGroup *group );
	AIAPI void (*MacXAddMenuGroupAsSubMenu) ( const char *name, long options, AIPlatformMacMenuHandle theMenu,
				short whichItem, MacMenuGroup *group );
	AIAPI void (*MacXGetMenuGroupName) ( MacMenuGroup group, const char **name );
	AIAPI void (*MacXGetMenuGroupOptions) ( MacMenuGroup group, long *options );
	AIAPI void (*MacXSetMenuGroupOptions) ( MacMenuGroup group, long options );
	AIAPI void (*MacXGetMenuGroupRange) ( MacMenuGroup group, AIPlatformMacMenuHandle *theMenu,
				short *firstItem, short *numItems );
	AIAPI void (*MacXCountMenuGroups) ( long *count );
	AIAPI void (*MacXGetNthMenuGroup) ( long n, MacMenuGroup *group );

} AIMacMenuSuite;


#include "AIHeaderEnd.h"

#endif
