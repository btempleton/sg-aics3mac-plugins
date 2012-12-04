//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/IllustratorSDK.h $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __IllustratorSDK__
#define __IllustratorSDK__

#include "SPConfig.h"

// std library 
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>

// several methods are now deprecated on windows xp but not mactel or ppc, the following define statements determine which method
// name to use on which platform

#ifdef MAC_ENV
	#include <Carbon.h>
#endif

#ifdef WIN_ENV
 	#include "windows.h"
	#include <time.h>
	//The following defines were added to keep the methods cross platform after they were deprecated on Windows.
    #define strcpy strcpy_s
    #define sprintf sprintf_s
    #define strncpy strncpy_s
    #define strcat strcat_s
    #define _strdate _strdate_s
    #define fopen fopen_s
    #define _strtime _strtime_s
#endif

using namespace std;


// sweet pea headers
#include "SPTypes.h"
#include "SPBlocks.h"

// adm headers
#include "ADMBasic.h"
#include "ADMDialog.h"
#include "ADMItem.h"
#include "ADMIcon.h"
#include "ADMDialogGroup.h"

// adm C++ wrapper classes
#include "IADMDialog.hpp"
#include "IADMEntry.hpp"
#include "IADMHierarchyList.hpp"
#include "IADMEntry.hpp"
#include "IADMIcon.hpp"
#include "IADMItem.hpp"
#include "IADMList.hpp"
#include "IADMListEntry.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"

#include "BaseADMDialog.hpp"


// illustrator headers
#include "AITypes.h"                        

#include "AIArt.h"
#include "AIArtSet.h"
#include "AIDictionary.h"
#include "AIDocument.h"
#include "AIHardSoft.h"
#include "AILayer.h"
#include "AILegacyTextConversion.h"
#include "AIMatchingArt.h"
#include "AIMdMemory.h"
#include "AIMenu.h"
#include "AIMenuGroups.h"
#include "AINotifier.h"
#include "AIPath.h"
#include "AIPathStyle.h"
#include "AIPlugin.h"
#include "AIPreference.h"
#include "AITextFrame.h"
#include "AITimer.h"
#include "AITool.h"
#include "AIRuntime.h"
#include "AIUndo.h"
#include "AIUser.h"

// Legacy headers
#include "AI110Art.h"
#include "AI110Document.h"
#include "AI110Font.h"
#include "AI110Layer.h"
#include "AI110Menu.h"
#include "AI110Path.h"
#include "AI110User.h"

// ATE text API
#include "IText.h"

// SDK common headers
#include "Suites.hpp"
#include "stringUtils.h"
#include "Plugin.hpp"

#endif //  __IllustratorSDK__
