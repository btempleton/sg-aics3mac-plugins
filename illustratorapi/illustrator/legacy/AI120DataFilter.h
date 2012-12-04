#ifndef __AI120DataFilter__
#define __AI120DataFilter__

/*
 *        Name:	AI120DataFilter.h
 *   $Revision: 7 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator Data Filter Suite.
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

#include "AIDataFilter.h"

#include "AIHeaderBegin.h"

/** @file AI120DataFilter.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI120DataFilterSuite			"AI Data Filter Suite"
#define kAIDataFilterSuiteVersion5		AIAPI_VERSION(5)
#define kAI120DataFilterVersion			kAIDataFilterSuiteVersion5

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** A data filter is an object that bytes of data can be read from or written to.
	The filter usually does something interesting with those bytes. For example,
	it might write them to a disk file, send them over a network or it could
	perform JPEG encoding and decoding.
	
	The power of a data filter is multiplied by the fact that they can be linked
	together. Therefore a file filter could be linked to an ASCII encoding
	filter which is in turn linked to a binary compression filter. The result
	is a composite filter that compresses and ASCII encodes data before writing
	it to file.

	The following code shows how to set up a data filter that performs buffered
	writes to a file. Note that LinkDataFilter must be called even for the
	first filter as it initializes the filter.
@code
	AIErr result = kNoErr;
	AIDataFilter* dstfilter = NULL;
	AIDataFilter* filter;
	if (!result)
		result = sAIDataFilter->NewFileDataFilter(file, "write", 'ART5', 'TEXT', &filter);
	if (!result)
	{
		result = sAIDataFilter->LinkDataFilter(dstfilter, filter);
		dstfilter = filter;
	}
	if (!result)
		result = sAIDataFilter->NewBufferDataFilter(32*1024, &filter);
	if (!result)
	{
		result = sAIDataFilter->LinkDataFilter(dstfilter, filter);
		dstfilter = filter;
	}
@endcode

	When done with the filter the following code can be used to close it.
@code
	AIErr result = kNoErr;
	while (dstfilter)
	{
		AIErr tmpresult = sAIDataFilter->UnlinkDataFilter(dstfilter, &dstfilter);
		if (!result)
			result = tmpresult;
	}
@endcode
*/
struct AI120DataFilterSuite {

	/** Initializes the filter next and links it to the filter prev. Next
		will read its data from or write it to prev. */
	AIAPI AIErr (*LinkDataFilter) ( AIDataFilter *prev, AIDataFilter *next );
	/** Terminate the filter next and return in prev the filter it was linked
		to (i.e the one it reads from or write to). Terminating a filter
		that is writing causes it to flush any writes. */
	AIAPI AIErr (*UnlinkDataFilter) ( AIDataFilter *next, AIDataFilter **prev );
	/** Read count bytes of data from filter into store. When the stream is
		exhausted a count of 0 will be returned. */
	AIAPI AIErr (*ReadDataFilter) ( AIDataFilter *filter, char *store, long *count );
	/** Write count bytes of data from store to the filter. */
	AIAPI AIErr (*WriteDataFilter) ( AIDataFilter *filter, char *store, long *count );
	/** Seek to a position that was returned by MarkDataFilter(). Not all data
		filters support random access. */
	AIAPI AIErr (*SeekDataFilter) ( AIDataFilter *filter, long *count );
	/** Return a value that indicates the current position. */
	AIAPI AIErr (*MarkDataFilter) ( AIDataFilter *filter, long *count );

	/** Create a new data filter that reads or writes a file. The mode may be
		"read", "write" or "append". The creator and type are used to assign a
		creator and type to files on the Macintosh. */
	AIAPI AIErr (*NewFileDataFilter) ( const ai::FilePath &spec, const char *mode, long creator, long type, AIDataFilter **filter );

	/** Creates a buffer data filter. When reading the filter reads its data from the
		next filter in the chain in chunks of "size" bytes. When writing the it
		buffers up chunks of size bytes before sending them to the next filter. */
	AIAPI AIErr (*NewBufferDataFilter) ( long size, AIDataFilter **filter );

	/** Creates an ASCIIHEX encode/decode data filter. statestr indicates
		whether the filter is encoding or decoding according to whether
		it is "write" or "read". */
	AIAPI AIErr (*NewHexdecDataFilter) ( char *state, long shift, AIDataFilter **filter );

	/** Creates a new block data filter. The block data filter reads and writes to
		the block of memory at address of the specified size. */
	AIAPI AIErr (*NewBlockDataFilter) ( void *address, long size, AIDataFilter **filter );

	/** Creates a random access data filter that reads and writes to Illustrator's
		VM. this can be used to create a temporary file that is paged to and from
		memory as needed. if initialsize is given then the initial VM stream is
		created with that size causing the end of the stream to be set to that size. */
	AIAPI AIErr (*NewVMDataFilter) ( long initialsize, AIDataFilter **filter );

	/** Creates an ASCII85 encode/decode data filter. statestr indicates
		whether the filter is encoding or decoding according to whether
		it is "write" or "read". */
	AIAPI AIErr (*NewA85DataFilter) ( char *statestr, char* prefix, AIDataFilter **filter );

	/** Creates a ZLib compression/decompression data filter. statestr indicates
		whether the filter is compressing or decompressing according to whether
		it is "write" or "read". */
	AIAPI AIErr (*NewZDataFilter) ( char *statestr, AIDataFilter **filter );


	/* New in Illustrator 10.0 */

	/** Create a data filter for a stream with the specified methods. note
		that the data filter must be a data source or a data sink. */
	AIAPI AIErr (*NewPluginStream) ( AIPluginStream* stream, AIDataFilter **filter );

};


#include "AIHeaderEnd.h"


#endif
