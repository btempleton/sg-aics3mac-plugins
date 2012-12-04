//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/file utils.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// Getting a Full Pathname
// Utilities from the Apple Q&A Stack showing how to get the full
// pathname of a file.  Note that this is NOT the recommended way
// to specify a file to Toolbox routines.  These routines should be
// used for displaying full pathnames only.

#include "SPConfig.h"
#ifdef MAC_ENV

#include "Files.h"
#include "file utils.h"
#include "stringUtils.h"

// Assumes inclusion of <MacHeadersCarbon>
#define haveAUX() 0


void PathNameFromDirID(long dirID, short vRefNum, unsigned char *fullPathName)
{
	FSRefParam pb;
	DirInfo *block = (DirInfo *)&pb;
	Str255	directoryName;
	OSErr	err;

	fullPathName[0] = '\0';

	block->ioDrParID = dirID;
	block->ioNamePtr = directoryName;
	do {
			block->ioVRefNum = vRefNum;
			block->ioFDirIndex = -1;
			block->ioDrDirID = block->ioDrParID;
			err = PBGetCatalogInfoSync( &pb );
			if (haveAUX()) {
					if (directoryName[1] != '/')
							/* If this isn't root (i.e. "/"), append a slash ('/') */
							SUpstrcat(directoryName, (StringPtr)"\p/");
			}
			else
					SUpstrcat(directoryName, (StringPtr)"\p:");
			SUpstrinsert(fullPathName, directoryName);
	} while (block->ioDrDirID != 2);
}



#endif