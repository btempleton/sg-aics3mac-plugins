/***********************************************************************/
/*                                                                     */
/* ADMHeaderBegin.h                                                    */
/* A standard place to put the junk that occurs at the beginning       */
/* of all of our headers. This is all reset with ADMHeaderEnd.h        */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 2005-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Dave MacLachlan, 07/10/2005                              */
/*                                                                     */
/***********************************************************************/

#if defined(__ADMHeaderBegin_H__)
#error __ADMHeaderBegin_H__ included multiple times in a single file
#endif

#define __ADMHeaderBegin_H__ 1

#ifndef __PlatformConfig__
#include "PlatformConfig.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAC_ENV
	//power_gcc on MWERKS is basically equivalent to power on GCC
	#if defined (__MWERKS__)
		#pragma options align=power_gcc
		#pragma enumsalwaysint on
	#elif defined (__GNUC__)
		//GCC doesn't allow non int enums without using an attribute decl directly on
		//the enum, so no need to set it
		#pragma options align=power
	#endif
#endif

#ifdef WIN_ENV
	#pragma pack(push, 4)
#endif
