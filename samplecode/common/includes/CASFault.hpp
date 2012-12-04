//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/CASFault.hpp $
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

#ifndef _CASFAULT_HPP_
#define _CASFAULT_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

#pragma PRAGMA_ALIGN_BEGIN
#pragma PRAGMA_IMPORT_BEGIN

////////////////////////////////////////////////////////////////////////
//
// A very simple exception class which allows Illustrator error codes to be
// returned as exceptions.
//
// Example of use:
//
// ASErr
// Foo(void)
// {
//     ASErr result = kNoErr;
//     ...
//     try
//     {
//         ...
//         throw CASFault(kBadParameterErr);
//         ...
//     }
//     catch (CASFault &f) // catch by (C++) reference
//     {
//         // assigns the ASErr field
//         result = f;
//     }
//
//     return result;
// }
//
////////////////////////////////////////////////////////////////////////

class CASFault {
public:
	CASFault (ASErr id)
		{fId = id;}

	operator ASErr()
		{return fId;}

protected:
	ASErr fId;
};

#pragma PRAGMA_IMPORT_END
#pragma PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif // _CASFAULT_HPP_

