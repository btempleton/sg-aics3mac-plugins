/***********************************************************************/
/*                                                                     */
/* IADMIcon.hpp                                                        */
/* Object wrapper for ADM Icon Suite                                   */
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
/* Started by Paul Asente, 06/15/1996                                  */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMIcon_hpp__
#define __IADMIcon_hpp__

/*
 * Includes
 */
 
#ifndef __ADMIcon__
#include "ADMIcon.h"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMIconSuite* sADMIcon;

/*
 * Wrapper Class
 */

class IADMIcon
{
private:
	ADMIconRef fIcon;

public:	
	IADMIcon(ADMIconType type, int width, int height, void* data)
		{ fIcon = sADMIcon->Create(type, width, height, data); }

	IADMIcon(SPPluginRef pluginRef, int iconID, int iconIndex)
		{ fIcon = sADMIcon->GetFromResource(pluginRef, iconID, iconIndex); }

	~IADMIcon()						{ sADMIcon->Destroy(fIcon); }

	IADMIcon(ADMIconRef icon)		{ fIcon = icon; }

	operator ADMIconRef()			{ return fIcon; }

	ADMIconType GetType()			{ return sADMIcon->GetType(fIcon); }
	int GetWidth()					{ return sADMIcon->GetWidth(fIcon); }
	int GetHeight()					{ return sADMIcon->GetHeight(fIcon); }
	void* GetData()					{ return sADMIcon->GetData(fIcon); }
	ADMBoolean IsFromResource()		{ return sADMIcon->IsFromResource(fIcon); }
};

#endif
