//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/TextFileFormat/Source/fileFormatHandler.cpp $
//
//  $Revision: #6 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include <string.h>
#include "common.h"
#include "fileFormatHandler.h"
#include "stringUtils.h"
#include "file utils.h"

#ifndef MAC_ENV
    #define BUFFERSIZE 560
#endif

AIErr WriteText( const char * pathName, bool selectedTextOnly  );
AIErr ReadText ( const char * pathName );
AIArtHandle CreateTextArt( AIReal width, AIReal height );

AIErr addFileFormat( SPInterfaceMessage *message ) 
{
	AIErr error;
	PlatformAddFileFormatData affd;
	std::auto_ptr<char> title( new char[1024] ); 

#ifdef MAC_ENV	
	strcpy( title.get(), "Selected Text as TEXT" );
#else
	strcpy( title.get(), BUFFERSIZE, "Selected Text as TEXT");
#endif
	SUctopstr( title.get() );
	affd.title = reinterpret_cast<unsigned char *>( title.get() );
	affd.titleOrder = 0;
	affd.extension = "txt";
	
	error = sAIFileFormat->AddFileFormat( message->d.self, "Selected text format",
				                          &affd, kFileFormatWrite,
										  &g->fileFormatSelected );

	if ( !error )
	{
#ifdef MAC_ENV	
		strcpy( title.get(), "All Text as TEXT" );
#else
		strcpy( title.get(), BUFFERSIZE, "All Text as TEXT");
#endif
		SUctopstr( title.get() );
		affd.title = reinterpret_cast<unsigned char *>( title.get() );

		error = sAIFileFormat->AddFileFormat( message->d.self, "All text format",
				                              &affd, kFileFormatWrite | kFileFormatRead,
										      &g->fileFormatAll );
	}

	return error;
}




AIErr goGetFormatParms( AIFileFormatMessage *message ) 
{
	// Does the plug-in need any info from user?  It should get it
	// here.  The information may be needed for writing or reading.

	return kNoErr;
}





AIErr goFileFormat( AIFileFormatMessage *message ) 
{
	AIErr error = kNoErr;
	char pathName[300];

	message->GetFilePath().GetFullPath().as_Roman( pathName, 300);
	
	if ( message->option & kFileFormatWrite ) 
	{
		// Get whatever art is supposed to be saved.  You might walk the tree writing out 
		// information on each object as you come to it, or as in this case
		// just get a bunch of art and work in batch mode.  It depends on what your doing.					

		error = WriteText( pathName, message->fileFormat == g->fileFormatSelected );
	}

	else if ( message->option & kFileFormatRead ) 
	{
		error = ReadText( pathName );
	} 
	
	return error;
}





AIErr goCheckFormat( AIFileFormatMessage *message ) 
{
	// this function is only needed for reading. The file is of a type we can read, but another
	// file format can also read it.  It is an opportunity to check if we can really handle it.
	// If we can we return 0, if not we return 1.  If more than one file format can read 
	// the selected file, the user will be prompted as to which format should actually
	// open the file.
	
	// I really don't need to do this because I told them I can't read these files.
	// It's sample code so I'll leave it in.
	if ( message->fileFormat == g->fileFormatSelected )
		return 1;
		
	return 0;
}


AIErr WriteText( const char * pathName, bool selectedTextOnly ) 
{
	AIErr error = 0;
	
#ifdef MAC_ENV
	FILE * fp = fopen( pathName, "w" );
#else
	FILE *fp;
	errno_t err;
	err = fopen(&fp, pathName, "w" );
#endif
	
	if ( fp != NULL )
	{

		ATE::ITextRanges iTextRanges;

		if ( selectedTextOnly )
		{
			TextRangesRef textSelectionRef;
			error = sAIDocument->GetTextSelection( &textSelectionRef );
			if ( !error )
			{
				iTextRanges = ATE::ITextRanges( textSelectionRef );
			}
		}
		else
		{
			AIArtHandle **artStore = NULL;
			long artCount = 0;
				
			AIMatchingArtSpec spec;
			spec.type = kTextFrameArt;
			spec.whichAttr = 0;
			spec.attr = 0;
			
			(void) sAIMatchingArt->GetMatchingArt( &spec, 1, &artStore, &artCount );

			for( long i = 0; i < artCount && !error; i++ )
			{
				AIArtHandle artHandle = (*artStore)[i];
				TextRangeRef textRange;
				error = sAITextFrame->GetATETextRange( artHandle, &textRange );
				if ( error ) continue;
				ATE::ITextRange iTextRange( textRange );
				iTextRanges.Add( iTextRange );
			}

			(void) sAIMdMemory->MdMemoryDisposeHandle( (void**) artStore );

		}

		if ( !error )
		{

			ASInt32 textRangeSize = iTextRanges.GetSize();

			for ( int i = 0; i < textRangeSize; i++ ) 
			{
				ATE::ITextRange iTextRange = iTextRanges.Item( i );
				ASInt32 strLength = iTextRange.GetSize();
				if ( strLength > 0 )
				{
					std::vector<char> vc(strLength);
					ASInt32 conLength = iTextRange.GetContents( &vc[0], strLength );
					if ( conLength == strLength )
					{
						std::string contents;
						contents.assign( vc.begin(), vc.begin() + strLength );
						fputs( contents.c_str(), fp );
					}
				}
			}
		}
	
		fclose( fp );
	
	}

	return error;
}

AIErr ReadText( const char * pathName )
{
	AIErr error = 0;

#ifdef MAC_ENV
	FILE * fp = fopen( pathName, "r" );
#else
	FILE *fp;
	errno_t err;
	err = fopen(&fp, pathName, "r" );
#endif

	if ( fp != NULL ) 
	{
		AIDocumentSetup docSetup;
		
		error = sAIDocument->GetDocumentSetup( &docSetup );
		
		if ( !error )
		{
			AIArtHandle textHandle = CreateTextArt( docSetup.width, docSetup.height );
			
			if ( textHandle != NULL )
			{
				TextRangeRef textRange;

				error = sAITextFrame->GetATETextRange( textHandle, &textRange );
		
				if ( !error )
				{
					ATE::ITextRange iTextRange( textRange );

					iTextRange.Remove();

					const unsigned int textSize = 1024 * 100;
					std::auto_ptr<char> text( new char[textSize] ); 
					size_t bytesRead = 0;

					do 
					{
						bytesRead = fread( text.get(), 1, textSize, fp );
						if ( ! ferror( fp ) && bytesRead )
						{
							iTextRange.InsertAfter( text.get() );
						}
					} while ( ! ferror( fp ) && ! feof( fp ) && bytesRead );
				}
			}
		}

		fclose( fp );
	
	}
						
	return error;
}		

AIArtHandle CreateTextArt( AIReal width, AIReal height )
{
	AIArtHandle artHandle = NULL;
	AIArtHandle textArtHandle = NULL;
	AIErr error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, NULL, &artHandle );
	if ( !error )
	{
		error = sAIPath->SetPathSegmentCount( artHandle, 4);
		if ( !error )
		{
			AIPathSegment segments[4];

			const int shrink = 10;
				
			AIReal left = 0 + shrink;
			AIReal top = 0 + shrink;
				
			AIReal right = width - shrink;
			AIReal bottom = height - shrink;
				
			segments[0].p.h = left; 	
			segments[0].p.v = top; 		
			segments[1].p.h = right; 	
			segments[1].p.v = top; 		
			segments[2].p.h = right; 	
			segments[2].p.v = bottom; 	
			segments[3].p.h = left; 	
			segments[3].p.v = bottom;
								
			segments[0].in = segments[0].p;
			segments[0].out = segments[0].p;
				
			segments[1].in = segments[1].p;
			segments[1].out = segments[1].p;
				
			segments[2].in = segments[2].p;
			segments[2].out = segments[2].p;
				
			segments[3].in = segments[3].p;
			segments[3].out = segments[3].p;
				
			error = sAIPath->SetPathSegments( artHandle, 0, 4, segments );
			if ( !error )
				error = sAIPath->SetPathClosed( artHandle, true );		
			if ( !error )
				error = sAITextFrame->NewInPathText(kPlaceAboveAll, NULL, 
													kHorizontalTextOrientation, 
													artHandle, NULL, false, 
				                                    &textArtHandle );
			else
				error = sAIArt->DisposeArt( artHandle );
		}
	}

	return textArtHandle;
}
// end fileFormatHandler.cpp