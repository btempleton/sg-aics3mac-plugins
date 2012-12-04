/*
 *        Name:	IAIUnicodeString.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Utility templates and convenience functions for use with
 *				the ai::UnicodeString wrapper class.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


#ifndef _IAIUNICODESTRINGUTILS_H_
#define _IAIUNICODESTRINGUTILS_H_

#include "IAIUnicodeString.h"


/** @file IAIUnicodeStringUtils.h */

namespace ai {

/** Retrieves the text of an ADM object as a Unicode string.
		@param s Pointer to the ADM suite (for example, \c ADMItemSuite).
		@param obj ADM object reference (for example, an \c ADMItemRef).
		@param out [out] A buffer in which to return the text as a Unicode string.
		@return Nothing.
		@see \c #ADMItemSuite9::GetTextW(), \c #ADMDialogSuite10::GetTextW()
	*/
template<typename ADMSuitePtr, typename ADMObjRef> void GetADMTextUS (ADMSuitePtr s, const ADMObjRef& obj, ai::UnicodeString& out)
{
	ADMInt32 utfCount = s->GetTextLengthW(obj) + 1;
	ai::AutoBuffer<ADMUnicode> buffer(utfCount);

	s->GetTextW(obj, buffer, utfCount);

	out = ai::UnicodeString(buffer.GetBuffer());
}

/** Retrieves the text of an ADM object as a Unicode string.
	Returns an error code rather than throwing an exception.
		@param s Pointer to the ADM suite (for example, \c ADMItemSuite).
		@param obj ADM object reference (for example, an \c ADMItemRef).
		@param out [out] A buffer in which to return the text as a Unicode string.
		@return An error code, \c #kNoErr on success.
		@see \c #ADMItemSuite9::GetTextW(), \c #ADMDialogSuite10::GetTextW()
	*/
template<typename ADMSuitePtr, typename ADMObjRef> AIErr GetADMTextUS (ADMSuitePtr s, const ADMObjRef& obj, ai::UnicodeString& out,
											  const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		GetADMTextUS(s, obj, out);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
	return result;
}

/** Sets the text of an ADM object using a Unicode string.
		@param s Pointer to the ADM suite (for example, \c ADMItemSuite).
		@param obj ADM object reference (for example, an \c ADMItemRef).
		@param in The new text as a Unicode string.
		@return Nothing.
		@see \c #ADMItemSuite9::SetTextW(), \c #ADMDialogSuite10::SetTextW()
	*/
template<typename ADMSuitePtr, typename ADMObjRef> void SetADMTextUS (ADMSuitePtr s, const ADMObjRef& obj, const ai::UnicodeString& in)
{
	s->SetTextW(obj, in.as_ASUnicode().c_str());
}

/** Sets the text of an ADM object using a Unicode string.
	Returns an error code rather than throwing an exception.
		@param s Pointer to the ADM suite (for example, \c ADMItemSuite).
		@param obj ADM object reference (for example, an \c ADMItemRef).
		@param in The new text as a Unicode string.
		@return An error code, \c #kNoErr on success.
		@see \c #ADMItemSuite9::SetTextW(), \c #ADMDialogSuite10::SetTextW()
	*/
template<typename ADMSuitePtr, typename ADMObjRef> AIErr SetADMTextUS (ADMSuitePtr s, const ADMObjRef& obj,
											const ai::UnicodeString& in, const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		SetADMTextUS(s, obj, in);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
	return result;
}

/** Retrieves a resource string as an ai:UnicodeString object, using
	\c #ADMBasicSuite10:: GetIndexStringW().
		@param s  A suite reference for \c #ADMBasicSuite10.
		@param inPluginRef This plug-in object.
		@param inStringID The resource identifier for string set containing the desired string.
		@param inStringIndex The 0-based position index of the desired string in the set.
		@param out [out] A buffer in which to return the Unicode string object.
		@param inMaxLen The maximum expected length of the resource string in UTF16 code units.
		@return Nothing.
	*/
template<typename ADMSuitePtr> void GetADMIndexString (ADMSuitePtr s, SPPluginRef inPluginRef, ADMInt32 inStringID,
													   ADMInt32 inStringIndex, ai::UnicodeString& out, ADMInt32 inMaxLen)
{
	ai::AutoBuffer<ADMUnicode> buffer(inMaxLen);

	s->GetIndexStringW(inPluginRef, inStringID, inStringIndex, buffer, inMaxLen);

	out = ai::UnicodeString(buffer.GetBuffer());
}

/** Retrieves a resource string as an ai:UnicodeString object, using
	\c #ADMBasicSuite10:: GetIndexStringW().
		@param s  A suite reference for \c #ADMBasicSuite10.
		@param inPluginRef This plug-in object.
		@param inStringID The resource identifier for the desired string.
		@param inStringIndex The 0-based position index of the desired string.
		@param out [out] A buffer in which to return the Unicode string object.
		@param inMaxLen The maximum expected length of the resource string in UTF16 code units.
		@return An error code, \c #kNoErr on success.

	*/
template<typename ADMSuitePtr> AIErr GetADMIndexString (ADMSuitePtr s, SPPluginRef inPluginRef, ADMInt32 inStringID,
													   ADMInt32 inStringIndex, ai::UnicodeString& out, ADMInt32 inMaxLen, const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		GetADMIndexString(s, inPluginRef, inStringID, inStringIndex, out, inMaxLen);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
	return result;
}

/** Internal */
template<typename ADMSuitePtr> void ADMLookUpZString (ADMSuitePtr s, SPPluginRef inPluginRef,
				const char* inString, ai::UnicodeString& out)
{
	const ADMUInt32 kInitBufferLen = 256;
	ai::AutoBuffer<ADMUnicode> buffer(kInitBufferLen);
	ADMUInt32 bufferLen = kInitBufferLen;

	s->LookUpZStringW(inPluginRef, inString, buffer, &bufferLen);
	if ( bufferLen > kInitBufferLen )
	{
		buffer.Resize(bufferLen);
		s->LookUpZStringW(inPluginRef, inString, buffer, &bufferLen);
	}

	out = ai::UnicodeString(buffer.GetBuffer());
}

/** Internal */
template<typename ADMSuitePtr> AIErr ADMLookUpZString (ADMSuitePtr s, SPPluginRef inPluginRef,
				const char* inString, ai::UnicodeString& out, const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		ADMLookUpZString(s, inPluginRef, inString, out);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
	return result;
}


/** Internal */
template<typename IADMObj> void SetIADMTextUS (IADMObj& o, const ai::UnicodeString& in)
{
	o.SetTextW(in.as_ASUnicode().c_str());
}

/** Internal */
template<typename IADMObj> void SetIADMTextUS (IADMObj& o, const ai::UnicodeString& in, const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		SetIADMTextUS(o, in);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
}

/** Internal */
template<typename IADMObj> void GetIADMTextUS (IADMObj& o, ai::UnicodeString& out)
{
	ADMInt32 utfCount = o.GetTextLengthW() + 1;
	ai::AutoBuffer<ADMUnicode> buffer(utfCount);

	o.GetTextW(buffer, utfCount);

	out = ai::UnicodeString(buffer.GetBuffer());
}

/** Internal */
template<typename IADMObj> void GetIADMTextUS (IADMObj& o, ai::UnicodeString& out, const std::nothrow_t&) AINOTHROW
{
	AIErr result = kNoErr;
	try
	{
		GetIADMTextUS(o, out);
	}
	catch(ai::Error& e)
	{
		result = e;
	}
}

} // namespace ai

#endif // _IAIUNICODESTRINGUTILS_H_
