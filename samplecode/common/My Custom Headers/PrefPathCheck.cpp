/*
 *  PrefPathCheck.cpp
 *  AddColor
 *
 *  Created by Comp Mac 8a on 4/5/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PrefPathCheck.h"


bool IsPluginPathLocal() {

	ai::FilePath pluginPath;
	ai::UnicodeString searchString("/Users");

	sAIPreference->GetFilePathSpecificationPreference(NULL, "plugins", pluginPath);
	
	ai::UnicodeString path(pluginPath.GetFullPath());

	if ( path.caseFind(searchString) == ai::UnicodeString::npos ) {
		return FALSE;
	}
	
	return TRUE;

}