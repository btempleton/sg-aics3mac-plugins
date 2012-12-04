//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TransformButtons/Source/fileFormatHandler.cpp $
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


#include "common.h"
#include "fileFormatHandler.h"
#include "stringUtils.h"


AIErr addFileFormat( SPInterfaceMessage *message ) {
	AIErr error;
	PlatformAddFileFormatData affd;
	AIFileFormatHandle fileFormat;
	char fftitleStr[] = "Selection As Raster PICT";

	affd.type = 'PICT';
	affd.title = ctopstr( fftitleStr );
	affd.titleOrder = 0;

	error = sFileFormat->AddFileFormat( message->d.self, "raster pict format",
				&affd, kFileFormatWrite | kFileFormatRead, &fileFormat );

	if (error)
		goto error;
	
error:
	return error;
}




AIErr goGetFormatParms( AIFileFormatMessage *message ) {
	AIErr error = kNoErr;
	
	// Does the plug-in need any info from user?  It should get it
	// here.  The information may be needed for writing or reading.

	if (error)
		goto error;

error:
	return error;
}





AIErr goFileFormat( AIFileFormatMessage *message ) {
	AIErr error = kNoErr;
	
	if ( message->option == kFileFormatWrite ) {
		// Get whatever art is supposed to be saved.  You might walk the tree writing out 
		// information on each object as you come to it just get a bunch of art and work 
		// in batch mode.  It depends on what your doing.					
	
		}
	else if ( message->option == kFileFormatRead ) {
		} 

	if (error)
		goto error;

error:
	return error;
}





AIErr goCheckFormat( AIFileFormatMessage *message ) {
	// This function is only needed for reading. The file is of a type we can read, but another
	// file format can also read it.  It is an opportunity to check if we can really handle it.
	// If we can we return 0, if not we return 1.  If more than one file format can read 
	// the selected file, the user will be prompted as to which format should actually
	// open the file.
	AIErr result = true;	// assume we can't read this file

	// if (thisIsAFileWeCanRead)
	//		result = false;	// now we now this is our file.  otherwise we won't read it

	return result;
}
