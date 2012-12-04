#ifndef __AI110Menu__
#define __AI110Menu__

/*
 *        Name:	AIMenu.h
 *   $Revision: 10 $
 *      Author:	 
 *        Date:	   
 *     Purpose: Adobe Illustrator 6.0 and 7.0 Menu Suite.	
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

#include "AIMenu.h"

#include "AIHeaderBegin.h"

/** @file AIMenu.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110MenuSuite					"AI Menu Suite"
#define kAIMenuSuiteVersion7			AIAPI_VERSION(7)		// In AI10
#define kAI110MenuSuiteVersion			kAIMenuSuiteVersion7

/*******************************************************************************
 **
 **	Types
 **
 **/

/** parameters used when creating a menu item. */
typedef struct {
	const char *groupName;
	unsigned char *itemText;
} AIPlatformAddMenuItemData;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The Menu Suite allows you to add menu items to the Illustrator menu structure.
	Menus can be used for a number of purposes: as stand alone interfaces
	to a plug-in feature, or to group a number of such features together. Other
	plug-in types may have an associated plug-in menu item. For instance, a
	window (or non-modal dialog box) will likely add a menu item to the Windows
	menu to hide and show the window.

	This section describes how to install and use plug-in menu items. It discusses
	the caller, selectors and messages that plug-in menus receive, as well as the
	functions provided to add menus, set options, and control menu appearance.
	Simple appearance changes can be set to happen automatically based on the
	artwork.

	Although this suite is completely cross-platform, it provides a set of functions
	that closely parallel the Macintosh toolbox functions for changing
	menu appearance.

	<b>Differences Between Filter and Menu Plug-ins</b>

	Menu plug-ins differ from Filter plug-ins in several ways. While Filters are
	always found under that menu heading, Menu plug-ins can appear in any of
	the Illustrator menus. Filters have a number of features provided automatically,
	including automatic repeat and setting the undo menu item text.
	Menu plug-ins must set the undo menu item text, but can also set command
	keys and control their appearance. Both plug-in types receive a go selector,
	but Filters also receive a selector to get parameters.

	<b>Plug-in Menu Selectors</b>

	The caller for menu plug-ins is #kCallerAIMenu. The selectors that may be
	received are listed below. The caller and selectors would be checked for in
	the plug-in's main function. The message data for each of these selectors
	is defined by the AIMenuMessage structure.

	- #kSelectorAIGoMenuItem
	- #kSelectorAIUpdateMenuItem

	Note: Should a plug-in with a menu become unloaded, it must first be
	reloaded before it can process the update selector. This potentially
	causes a performance lag perceivable to the user when the menu bar
	is clicked. Unless there is a pressing reason for a custom menu update,
	you should use the UpdateMenuItemAutomatically() function
	instead of requesting this selector.

	<b>Menu Groups</b>

	Menu items are installed using AIMenuSuite::AddMenu() function.	Menu items are
	added to menu groups. These are predefined locations within Illustrator's menu
	structure. Some examples of menu groups are: #kOpenMenuGroup, #kArrangeMoveMenuGroup
	and #kTypeSizeMenuGroup. The names are fairly descriptive of their menu location.
	A utilities group is located at the top to a menu group; for instance, the
	type size utilities	menu group is at the top of the type size hierarchical menu.
	The complete list of groups is found in the file AIMenuGroups.h.
	
	You can create new menu groups, to which your plug–in or other plug–ins
	can add menu items. Documentation of such menu groups is the responsibility
	of the developer of the plug-in adding the menu group.
	
	Note: Because the #kFilterUtilities menu is implemented using an
	internal plug-in, to use the menu group a plug-in must acquire the
	Filter Suite.

	<b>Menu Options</b>

	There are two sets of options for menus. The #AIMenuItemOption defines options
	that apply to menu items and the #AIMenuGroupOption defines options that apply
	to menu groups. The menu item options can be set at the time of the AddMenuItem()
	or with SetMenuItemOptions() after the menu item is installed. Similarly the
	options for menu groups can be set with AddMenuGroup() or SetMenuGroupOptions().

	<b>AIMenuHandles and PlatformMenus</b>

	When a plug-in menu is added to Adobe Illustrator, the plug-in is returned
	an AIMenuItemHandle reference. This is Illustrator's means of keeping track
	of menus. It is an opaque reference that cannot be used to directly make
	changes to the menu item itself.

	The UpdateMenuItemAutomatically() function tells Illustrator to automatically
	make changes to a menu item's appearance.

	If your plug-in needs to manipulate the menu item directly, the menu suite
	provides the GetPlatformMenuItem() function to obtain a platform specific
	reference to the menu in an AIPlatformMenuItem structure.

	<b>Menu Notifiers</b>
	
	The following notifiers relating to menu events are sent:

	- #kAIMenuChangedNotifier
	- #kAIMenuBeforePluginNotifier
	- #kAIMenuAfterPluginNotifier
	- #kAIMenuBeforeUnknownMenuNotifier
	- #kAIMenuAfterUnknownMenuNotifier

*/
typedef struct {

	/** Use this to install a plug-in menu item.
	
		- self is a reference to the plug-in adding the menu item.
		- name is a C string identifying the plug-in menu being added to Illustrator and
			other plug-ins.
		- data contains the menu group to which the plug-in menu will be added and a Pascal
			string to be used for the menu. Note: to create a menu separator, pass a dash "-"
			character as the itemText.
		- options flags are used control the menu item's behavior see #AIMenuItemOption.
		- menuItem identifies the installed plug-in menu. If you are installing multiple menu
			items, this reference must be stored in the plug-in's globals record, as your
			plug-in will need it to determine which menu command is to be processed.
	*/
	AIAPI AIErr (*AddMenuItem) ( SPPluginRef self, const char *name,
				AIPlatformAddMenuItemData *data, AIMenuItemOption options,
				AIMenuItemHandle *menuItem );

	/** Returns name, a pointer to the name of the menuItem. This is the name value
		originally passed to the AddMenuItem call. It should not be modified. */
	AIAPI AIErr (*GetMenuItemName) ( AIMenuItemHandle menuItem, const char** name );
	/** Use this to get the current options of a menu item. See #AIMenuItemOption for the
		options. */
	AIAPI AIErr (*GetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption *options );
	/** Use this to set the current options of a menu item. See #AIMenuItemOption for the
		options. */
	AIAPI AIErr (*SetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption options );
	/** Returns the plugin that installed the menu item. */
	AIAPI AIErr (*GetMenuItemPlugin) ( AIMenuItemHandle menuItem,
				SPPluginRef *plugin );

	/** Get the number of installed menu items. */
	AIAPI AIErr (*CountMenuItems) ( long *count );
	/** Get the nth installed menu item. */
	AIAPI AIErr (*GetNthMenuItem) ( long n, AIMenuItemHandle *menuItem );

	/** Use this to get the platform menu item reference associated with menuItem. */
	AIAPI AIErr (*GetPlatformMenuItem) ( AIMenuItemHandle menuItem,
				AIPlatformMenuItem *platformMenuItem );

	/** Use this function to tell Illustrator to update a menu item automatically
		according to the criteria passed to the function. Each criteria is evaluated
		and the results combined to produce a value. This value then determines the
		behaviour of the action. The actions are defined by #AIAutoMenuUpdateAction,
		the object based criteria are defined by #AIAutoMenuUpdateObjectCriteria and
		the document properties based criteria are defined by #AIAutoMenuUpdatePropertyCriteria.

		- The menuItem is the item to be updated.
		- The action variable contains a flag that indicates how the menu is to be
			modified.

		The "positive" criteria are true if any of the properties they specify are
		present. The results of these are then or'ed together to produce a positive
		result. This result is then true if any of the criteria are true.

		- ifObjectIsInArtwork is true if any of the object types identified are
			present in the document.
		- ifObjectIsSelected is true if any of the object types identified are
			present in the current selection.
		- ifIsTrue is true if any of the document properties identified are true.

		The "negative" criteria are true if none of the properties they specify are
		present. The results of these are then and'ed together to produce a negative
		result. This result is then true if none of the criteria are true.

		- ifObjectIsNotInArtwork is true if none of the object types identified
			are present in the document.
		- ifObjectIsNotSelected is true if none of the object types identified are
			present in the current selection.
		- ifIsNotTrueis true if none of the document properties identified are
			true.

		Finally the combined result used to perform the update action is true if
		both the positive and negative results are true. That is, if any of the
		desired properties are present and none of the undesired properties are
		present.
	*/
	AIAPI AIErr (*UpdateMenuItemAutomatically) ( AIMenuItemHandle menuItem,
				long action,
				long ifObjectIsInArtwork, long ifObjectIsNotInArtwork,
				long ifObjectIsSelected, long ifObjectIsNotSelected,
				long ifIsTrue, long ifIsNotTrue );
	/** Use this function to get the artwork and document state information that
		the Illustrator application uses to do it's menu updating. This is quicker than
		scanning the artwork tree or getting specific art, as Illustrator has already
		computed the information for its own use.

		You can use this as a preliminary check to update a menu. The inArtwork
		argument returns flags about the art objects in the current document. The
		isSelected argument returns flags about the selected art objects. The
		isTrue argument returns information about the document state. See
		#AIAutoMenuUpdateObjectCriteria for values for inArtwork and isSelected.
		See #AIAutoMenuUpdatePropertyCriteria for values for isTrue.
		
		This call can only be used when the #kSelectorAIUpdateMenuItem selector
		is received. The information will be invalid at any other time. The
		#kMenuItemWantsUpdateOption option must be set for the plug-in to receive this
		selector.
	*/
	AIAPI AIErr (*GetUpdateFlags)( long *inArtwork, long *isSelected, long *isTrue );

	/*-------------------------------------------------------------------------------------------*/
	
	/** Enable menu item */
	AIAPI AIErr (*EnableItem) ( AIMenuItemHandle menuItem);
	/** Disable menu item */
	AIAPI AIErr (*DisableItem) ( AIMenuItemHandle menuItem);

	/** This call gets the text itemCString of a menu item. itemCString is the
		same text that was specified in the AIPlatformAddMenuItemData struct
		when using AddMenuItem. The maximum length of itemCString is 256
		characters.

		You can use this after using SetItemText. Note: the text returned by
		GetItemText is different than what is returned by GetMenuItemName. Text
		returned by this function must be localized. */
	AIAPI AIErr (*GetItemText) ( AIMenuItemHandle menuItem, char* itemCString );
	/** Set the text of a menu item. This is the localized string displayed in
		the menu and has a maximum length of 255 characters (exluding null
		terminator). */
	AIAPI AIErr (*SetItemText) ( AIMenuItemHandle menuItem, const char* itemCString );

	/** Check or uncheck the menu item. */
	AIAPI AIErr (*CheckItem) ( AIMenuItemHandle menuItem, AIBoolean bCheckIt );

	/** This call places an icon to the left of the specified menu item. The icon is
		read from platform resources and are specified by the iconSelector ID.

		Under Mac OS, the call uses an icon in a 'SICN' resource. The resource ID is
		computed by adding iconSelector to 256.

		On Windows, the function uses BitMap resources for icons. On Windows:
		MAKEINTRESOURCE(iconSelector + 256) is the bitmap resource ID for the
		menuItem.
		
		Due to the way Illustrator handles menus internally, a plug-in menu item
		cannot have both an icon and a command key. */
	AIAPI AIErr (*SetItemIcon) ( AIMenuItemHandle menuItem, short iconSelector );

	/** Get the menu group to which the menu item belongs. */
	AIAPI AIErr (*GetItemMenuGroup) ( AIMenuItemHandle menuItem, AIMenuGroup *group );
	/** Creates a new menu group, which you can use to add your plug-in menu.
		
		- name is the new menu group name.
		- options indicate the behavior of the menu group see #AIMenuGroupOption.
		- The new menu group will appear beneath the existing menu group specified by
			nearGroup which may be any available menu group including those created
			by other plugins.
		- A reference to the new group is returned in the group argument.

		A plug-in installing several menu items with a unique function may wish to
		add a menu group. The new menu group can be documented and used by
		other plug-ins installing menu items with similar functions. The menu group
		name can be passed to the AddMenuItem() function just as any of the built in
		menu group names can.
	*/
	AIAPI AIErr (*AddMenuGroup) ( const char *name, AIMenuGroupOption options, const char *nearGroup,
				AIMenuGroup *group );
	/** Illustrator menus use a Menu Group to handle hierarchical menus. Use this
		function to create a hierarchical "submenu" name. It is possible to have
		nested submenus.

		- The options argument indicate the behavior of the menu group see
			#AIMenuGroupOption.
		- The new menu group will appear as a hierarchical menu at the menu
			item indicated by menuItem.
		- An AIMenuGroup reference for the new group is returned in the
			variable group.
		
		To create a hierarchical menu, a plug-in first creates a normal menu item.
		It then calls AddMenuGroupAsSubMenu with the AIMenuItemHandle of this
		menu item and a group name.
	*/
	AIAPI AIErr (*AddMenuGroupAsSubMenu) ( const char *name, AIMenuGroupOption options, AIMenuItemHandle menuItem, AIMenuGroup *group);
	/** Returns a pointer to the name of the group. This is the name value originally
		passed to the AddMenuGroup call. It should not be modified. */
	AIAPI AIErr (*GetMenuGroupName) ( AIMenuGroup group, const char **name );
	/** Get option flags of a menu group. */
	AIAPI AIErr (*GetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption *options );
	/** Set option flags of a menu group. */
	AIAPI AIErr (*SetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption options );
	/** On the Mac, this call will return a MenuInfo struct for the AIPlatformMenuHandle. On
		Windows, it will return a WinMenu struct for the AIPlatformMenuHandle. It also
		returns the first and last menu indices of the hierarchical menu.*/
	AIAPI AIErr (*GetMenuGroupRange) ( AIMenuGroup group, AIPlatformMenuHandle *theMenu,
				short *firstItem, short *numItems );
	/** Return the number of installed menu groups. */
	AIAPI AIErr (*CountMenuGroups) ( long *count );
	/** Get the nth installed menu group. */
	AIAPI AIErr (*GetNthMenuGroup) ( long n, AIMenuGroup *group );

	/** Returns the command key and modifiers assigned to a menu item. See #AIMenuItemModifier
		for modifiers. Note: Submenus created by plug-ins do not support modified command keys. */
	AIAPI AIErr (*GetItemCmd) ( AIMenuItemHandle menuItem, short *cmdChar, short *modifiers );
	/** Sets the command key and modifiers assigned to a menu item.  See #AIMenuItemModifier
		for modifiers. Note: Submenus created by plug-ins do not support modified command keys. */
	AIAPI AIErr (*SetItemCmd) ( AIMenuItemHandle menuItem, char cmdChar, short modifiers );

	/** This call returns the function key fkey and modifiers modifiers associated
		with the specified menu item. See #AIMenuItemModifier for modifiers. */
	AIAPI AIErr (*GetItemFunctionKey) ( AIMenuItemHandle menuItem, short *fkey, short *modifiers );
	/** This call associates the function key fkey and modifiers modifiers to the specified
		menu item. This function supports fkeys 1-15 and is 1-based. See #AIMenuItemModifier
		for modifiers. */
	AIAPI AIErr (*SetItemFunctionKey) ( AIMenuItemHandle menuItem, short fkey, short modifiers );
	
	/** Obsolete */
	AIAPI AIErr (*GetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID *helpID );
	/** Obsolete */
	AIAPI AIErr (*SetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID helpID );
	
	/** True if the menu item is enabled */
	AIAPI AIErr (*IsItemEnabled) ( AIMenuItemHandle menuItem, ASBoolean *bEnabled);
	/** True if the menu item is checked */
	AIAPI AIErr (*IsItemChecked) ( AIMenuItemHandle menuItem, AIBoolean *bCheckIt );
	
	AIAPI AIErr (*RemoveMenuItem) ( AIMenuItemHandle menuItem );

} AIMenuSuite7;


#include "AIHeaderEnd.h"

#endif
