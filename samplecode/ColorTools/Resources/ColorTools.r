#define PIPL_PLUGIN_NAME "ColorTools"
#include "Plugin.r"

#include "ADMNonModalDialogID.h"

#include "Types.r"

/** Add Color Dialog resource
 */
resource 'DLOG' (kADMAddColorDialogID, kADMAddColorDialogName, purgeable) {
	{100, 200, 132, 410},  // top, left, bottom, right
	1991, // floatZoomGrowProc defined in MacWindows.h
	visible, // drawn on screen immediately
	goAway, // has close button
	0x0, // application options
	kADMAddColorDialogID, // resource ID
	kADMAddColorDialogName, // dialog title
	0x0 // dialog positioning noAutoCenter
};

resource 'DITL' (kADMAddColorDialogID, kADMAddColorDialogName, purgeable) { { } };


/** Find/Replace Dialog resource
 */
resource 'DLOG' (kADMFindReplaceDialogID, kADMFindReplaceDialogName, purgeable) {
	{100, 200, 265, 410},  // top, left, bottom, right
	1991, // floatZoomGrowProc defined in MacWindows.h
	visible, // drawn on screen immediately
	goAway, // has close button
	0x0, // application options
	kADMFindReplaceDialogID, // resource ID
	kADMFindReplaceDialogName, // dialog title
	0x0 // dialog positioning noAutoCenter
};

resource 'DITL' (kADMFindReplaceDialogID, kADMFindReplaceDialogName, purgeable) { { } };