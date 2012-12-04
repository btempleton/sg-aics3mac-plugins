/*******************************************************************************
*
* ADMFlashPlayer.h -- ADM Flash Player Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*
********************************************************************************/

/** @file ADMFlashPlayer.h ADM Flash Player Suite */

#ifndef __ADMFlashPlayer__
#define __ADMFlashPlayer__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#include "ADMHeaderBegin.h"


// -----------------------------------------------------------------------------


// =============================================================================
//		* ADM Flash Player Suite
// =============================================================================

/** Flash Player suite name */
#define kADMFlashPlayerSuite "ADM Flash Player Suite"

/** Flash Player suite version */
#define kADMFlashPlayerSuiteVersion		1

// -----------------------------------------------------------------------------

/**  Signature of a host function that is called by an art object of type
	\c #kADMFlashPlayerType, when a movie invokes an application function via the
	\c ExternalInterface.call ActionScript function.

	The host function should parse the ActionScript command specified in \c inRequest,
	perform the action specified in the request, compose a response, and
	return the response as the function's result.

	If the host function returns \c NULL, "<undefined/>" is returned to
	the ActionScript code that invoked the callback.

		@see \c #ADMFlashPlayerSuite::UpdateCallHostFunctionProc()
		@param inRequest An XML element containing the ActionScript command
			to execute, with its arguments.

		@return	An XML element describing the result of the host function invocation.
			ADM assumes ownership of this string buffer and frees it with \c #SPBasicSuite::FreeBlock().
*/

typedef ADMUnicode* ADMAPI (*ADMFlashHostCallbackProc)(const ADMUnicode* inRequest);

/** The internal ADM Flash Player procedures table returned by
	\c #ADMFlashPlayerSuite::GetADMFlashPlayerProcs(). Used by ScriptUI, the
	JavaScript user-interface module. */
typedef struct _ADMFlashPlayerProcs
{
	void *admGetVersion;
	void *admLoadMovie;
	void *admPlay;
	void *admStopPlay;
	void *admCallMovieFunction;
	void *admChangeAppFunctionCallback;
	void *admIsFlashPlayerWidget;
} ADMFlashPlayerProcs;

// -----------------------------------------------------------------------------

/** @ingroup Suites
	This suite allows you to access and manipulate the Flash movie player
	which is embedded in the application. The Flash player is represented by
	an \c #ADMItemRef of type \c #kADMFlashPlayerType.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kADMFlashPlayerSuite and \c #kADMFlashPlayerSuiteVersion.
	*/

typedef struct ADMFlashPlayerSuite
{
	/** Loads a movie into the Flash player.

		This function is the equivalent of \c FPP_LoadMovie in the
	Flash External Player API.
			@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
			@param inURL The URL path to the movie to be played. A UTF-16 encoded string
				formed according to the rules defined for the
				path argument to \c FPP_LoadMovie.
			@param inPlayerPush True to load the movief from the specified path,
				false to load the movie after this call using \c #PushDataBuf().
 			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*LoadMovie)(ADMItemRef inItem,
							   const ADMUnicode* inURL,
							   ADMBoolean inPlayerPush);

	/** Calls an ActionScript function that is registered for a Flash player,
		using the \c ExternalInterface.addCallback method in the movie being played.

		This function is the equivalent of \c FPP_CallFunction2 in the
	Flash External Player API.
			@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
			@param inRequest An XML element that specifies the function to invoke
				and any arguments.
			@param outResponse A buffer in which to return the XML element response
				from the movie. May not be NULL.
				The caller assumes ownership of the returned string buffer, and must
				free it using \c #SPBasicSuite::FreeBlock().
 			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*CallMovieFunction)(ADMItemRef			inItem,
									   const ADMUnicode*	inRequest,
									   ADMUnicode**			outResponse);

	/** Sets up the function to be invoked when a movie invokes an
		application function for a Flash player, via the
		\c ExternalInterface.call ActionScript function.  By default, the
		Flash player does not call any function when the movie invokes
		an application function.

	The application function callback is the equivalent of
		\c FPA_CallFunction in the Flash External Player API.

		@see \c #ADMFlashHostCallbackProc
			@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
			@param inCallback The function to be called when the item's
				movie invokes an application function. Pass \c NULL to indicate
				that no function should be called when a movie invokes an
				application function.
			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI  (*UpdateCallHostFunctionProc)(ADMItemRef inItem,
												 ADMFlashHostCallbackProc inCallback);

	/** Streams a movie's bits into a Flash player. Use after passing false
		for the \c inPlayerPush argument to \c #LoadMovie().

		This function is the equivalent of \c FPP_PushDataBuf in the
	Flash External Player API.
			@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
			@param inBuffer A pointer to a memory buffer holding the movie
				bits to be pushed.
			@param inBufferSize The number of bytes from the buffer to be
				pushed to the player.
			@return An error code, \c #kNoErr on success.
		*/
	ADMErr ADMAPI (*PushDataBuf)(ADMItemRef		inItem,
								 const void*	inBuffer,
								 ADMUInt32		inBufferSize);

 	/** Stops playing the main timeline of the movie in a Flash player.

 		This function is the equivalent of \c FPP_StopPlay in the Flash
 		External Player API.
	 		@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
  			@return An error code, \c #kNoErr on success.
 		*/
 	ADMErr ADMAPI (*StopMovie)(ADMItemRef		inItem);

 	/** Resumes playing the main timeline of the movie in a Flash player.

 		This function is the equivalent of \c FPP_Play in the Flash
 		External Player API.
 			@param inItem The item object, of type \c #kADMFlashPlayerType, for
				the Flash player.
 			@param inRewind When true, the movie plays from the beginning. When
				false, it plays from the point at which it was stopped.
  			@return An error code, \c #kNoErr on success.
 		*/
 	ADMErr ADMAPI (*PlayMovie)(ADMItemRef		inItem,
 							   ADMBoolean		inRewind);

	/** Fills out the internal ADM Flash Player procedures table. The entries
	    are needed by ScriptUI (the JavaScript user-interface module)
	    to support the FlashPlayer element. The contents of the returned
	    function table are considered private to ADM.
 			@param outProcs [out] A buffer in which to return the internal
 				ADM Flash Player procedure table.
 			@return An error code, \c #kNoErr on success.
	*/
	ADMErr ADMAPI (*GetADMFlashPlayerProcs)(ADMFlashPlayerProcs *outProcs);
}
ADMFlashPlayerSuite;

// -----------------------------------------------------------------------------

#include "ADMHeaderEnd.h"

// -----------------------------------------------------------------------------

#endif	// __ADMFlashPlayer__
