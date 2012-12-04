/***********************************************************************/
/*                                                                     */
/* IADMNotifier.hpp                                                    */
/* Object wrapper for ADM Notifier suite                               */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2007 Adobe Systems Incorporated.                     */
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
/* Started by Dave Lazarony, 03/06/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMNotifier_hpp__
#define __IADMNotifier_hpp__

/*
 * Includes
 */
 
#ifndef __ADMNotifier__
#include "ADMNotifier.h"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMNotifierSuite2* sADMNotifier;

/*
 * Wrapper Class
 */

class IADMNotifier
{
private:
	ADMNotifierRef fNotifier;

public:	
	IADMNotifier() 												{ fNotifier = NULL; }
	IADMNotifier(ADMNotifierRef notifier) 						{ fNotifier = notifier; }
	
	operator ADMNotifierRef() 									{ return fNotifier; }
	
	ADMItemRef GetItem()										{ return sADMNotifier->GetItem(fNotifier); }	
	ADMDialogRef GetDialog()									{ return sADMNotifier->GetDialog(fNotifier); }

	ADMBoolean IsNotifierType(const char* notifierType)			{ return sADMNotifier->IsNotifierType(fNotifier, notifierType); }

	void GetNotifierType(char* notifierType, ADMUInt32 maxLength = 0)	{ sADMNotifier->GetNotifierType(fNotifier, notifierType, maxLength); }

};

#endif
