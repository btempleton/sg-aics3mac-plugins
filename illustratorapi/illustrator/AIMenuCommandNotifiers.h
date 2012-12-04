/*
 *        Name:	AIMenuCommandNotifiers.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/** @file AIMenuCommandNotifiers.h */

/** @ingroup Notifiers
	Sent before a plug-in menu item is executed. See \c #AIMenuSuite */
#define kAIMenuBeforePluginNotifier				"AI Command Notifier: Before Plugin"
/** @ingroup Notifiers
	Sent after a plug-in menu item is executed. See \c #AIMenuSuite  */
#define kAIMenuAfterPluginNotifier				"AI Command Notifier: After Plugin"

/** @ingroup Notifiers
	Sent before an Illustrator menu item is executed, if that item
	is not identified in the \c #MenuCommands list. See \c #AIMenuSuite  */
#define kAIMenuBeforeUnknownMenuNotifier		"AI Command Notifier: Before Unknown"
/** @ingroup Notifiers
	Sent after an Illustrator menu item is executed, if that item
	is not identified in the \c #MenuCommands list. See \c #AIMenuSuite  */
#define kAIMenuAfterUnknownMenuNotifier			"AI Command Notifier: After Unknown"


/**	Menu identifiers for pre- and post- notification
	See source code and \c #AIMenuSuite. */
char *MenuCommands[] = {
"About Illustrator",	// 0
"Redo",
"Desk Accessory",  // obsolete
"New",
"Open",
"Close",
"Save",
"Save As",
"Page Setup",

"Print",
"Quit",
"Undo",
"Cut",
"Copy",
"Paste",
"Clear",
"Select All",
"Paste in Front",
"Paste in Back",

"Show/Hide Clipboard",  // obsolete
"Preferences",
"Transform Again",
"Group",
"Ungroup",
"Join",
"Average",
"Unlink Text",
"Lock",
"Unlock All",

"Preview Mode",
"Show/Hide Template",
"Artwork Mode",
"Preview Selection",   // obsolete
"Reduce To Fit",
"New View",
"Show/Hide Rulers",
#ifdef AI6MENUCOMMANDS
"Show/Hide Toolbox",  // obsolete
#endif
"Show/Hide Color Palette",  // obsolete
"Show/Hide Unpainted Objects",  // obsolete

"Select Window",
"Send To Front",
"Send To Back",
"Text Font",
"Text Size",
#ifdef AI6MENUCOMMANDS
"Pattern",  // obsolete
"Custom Color",   // obsolete
#endif
"Link Text",
"Hide",
"Unhide All",

"Make Guides",
"Release Guides",
"Move Objects",
"Place EPSF",  // obsolete
"Make Compound Path",
"Release Compound Path",
"Text Alignment",
"Line Spacing",
"Tracking/Kerning",
"Word Spacing",

"Type Outlines",
"Actual Size",
"Discretionary Hyphen",
"Text Size",
"Tracking/Kerning",
"Make Crop Marks",
"Release Crop Marks",
"Make Text Wrap",
"Release Text Wrap",
"Set Graph Style",
"Edit Graph Data",

"Set Bar Design",
"Define Graph Design",
"Set Icon Design",
#ifdef MAC_ENV
"Publish",   // obsolete
"Subscribe",   // obsolete
"Publish Options",   // obsolete
#endif
"Show Hide Borders",   // obsolete
"Art Setup",
"Show/Hide Page Tiling",
#ifdef AI6MENUCOMMANDS
"Show/Hide Gradient Palette",  // obsolete
#endif
"Fit Headline",
"New Multiple Master Instance",
"Cut Picture",
"Copy Picture",
#ifdef AI6MENUCOMMANDS
"Show/Hide Layers Palette",
#endif
"Replace EPSF",  // obsolete
"Show Character Palette",
"Show Paragraph Palette",
"Make Mask",
"Release Mask",

"Show/Hide Infomation Palette",
"Set Note",
"Zoom In",
"Zoom Out",
"Brush Preferences",   // obsolete
"Eyedropper Preferences",   // obsolete
"Color Matching Preferences",
"Hyphenation Preferences",
"Plugins Folder Preferences",
"Deselect All",

"Custom View",  // obsolete
"New View Snap",
"Edit View Snap",
"Show/Hide Edges",
"Switch Units",
"Show/Hide Paint Palette",   // obsolete
#ifdef AI6MENUCOMMANDS
"Show/Hide Gradient Palette",   // obsolete
#endif
"Show/Hide Character Palette",   // obsolete
"Show/Hide Paragraph Palette",   // obsolete
"Show/Hide Guides",

"Lock/Unlock Guides",
"Revert To Saved",
"Show/Hide Tabs Palette",
"Separation Setup",

/* new in AI7.0 */
"Save A Copy As",
"Export",
"Send Forward",
"Send Backward",
"Website - Tips",
"Website - Support",
"Website - ImageClub",

"Show/Hide Grid",
"Enable/Disable Grid Snap",
"Grid Preferences",

"Transform - Rotate",
"Transform - Scale",
"Transform - Reflect",
"Transform - Shear",

#ifdef WIN_ENV
"Arrange Windows - Cascade",
"Arrange Windows - Horizontal",
"Arrange Windows - Vertical",
"Arrange Icons",
"Send Mail",  // obsolete
"Selecte File 1",
"Selecte File 2",
"Selecte File 3",
"Selecte File 4",
#endif

"Text Orientation",

#ifdef MAC_ENV
"Glyph Substitution Options",
#endif

"Add Anchor Point",
"Delete Anchor Point",

"Help",
"Help - Search",   // obsolete
"Help - Keyboard",   // obsolete
"Help - How To"   // obsolete

};