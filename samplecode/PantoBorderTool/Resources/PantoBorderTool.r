//========================================================================================
//  
//  $File: //ai/ai14/devtech/sdk/public/samplecode/ADMNonModalDialog/Resources/ADMNonModalDialog.r $
//
//  $Revision: #3 $
//
//  Copyright 1987-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#define PIPL_PLUGIN_NAME "PantoBorderTool"
#include "Plugin.r"

#include "Types.r"

read 'PNGI' (16051, "PantoBorderTool", purgeable)  "pbtool.png";
read 'PNGI' (16052, "PantoBorderToolRollover", purgeable)  "pbtoolRollover.png";

// Tool names and tool tip text.
resource 'STR#' (16100, "Tool Strings") {
	{
        "Panto/Border Tool";
	}
};

/** Head Arrow Tool cursor.
*/
resource 'CURS' (16001) {
        $"00 00 00 00"
		$"18 00 3C 00"
		$"1E 00 0F 00"
		$"07 80 03 C8"
        $"01 E8 00 FC"
		$"00 7C 00 7C"
		$"01 FE 00 3E"
		$"00 06 00 00",
        $"00 00 00 00"
		$"18 00 3C 00"
		$"1E 00 0F 00"
		$"07 80 03 C8"
        $"01 E8 00 FC"
		$"00 7C 00 7C"
		$"01 FE 00 3E"
		$"00 06 00 00",
        {14, 14}
};