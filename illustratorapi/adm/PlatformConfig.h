/*******************************************************************************
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2002-2007 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
* Started by David Hearst, 05 Jun 2002
*
********************************************************************************/

#ifndef __PlatformConfig__
#define __PlatformConfig__

/*
 * Defines for Metrowerks
 */
#if defined (__MWERKS__)
	#if defined (__POWERPC__)
		#ifndef MAC_ENV
			#define MAC_ENV
		#endif
	#endif
	#if defined (__INTEL__)
		#ifndef WIN_ENV
			#define WIN_ENV
		#endif
	#endif
#endif

/*
 * Defines for GNU 
 */
#if  defined(__GNUC__)
	#if ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) )
		#ifndef MAC_ENV
			#define MAC_ENV
		#endif
	#endif
	#if defined (__INTEL__)
		#ifndef WIN_ENV
			#define WIN_ENV
		#endif
	#endif
#endif

/*
 * Defines for Visual C++ on Windows.
 */
#ifdef _MSC_VER
	#ifndef WIN_ENV
		#define WIN_ENV
	#endif
#endif

/*
 *	Make certain that one and only one of the platform constants is defined.
 */

#if !defined(WIN_ENV) && !defined(MAC_ENV)
	#error
#endif

#if defined(WIN_ENV) && defined(MAC_ENV)
	#error
#endif

#if defined(MAC_ENV)
	//Would like to be able to get rid of these two if possible are they used anywhere? dmaclach
	#define MACPPC_ENV
	#define MAC_MACHO_ENV
#endif

#endif
