//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/ArtMatcher.hpp $
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

#ifndef _ARTMATCHER_HPP_
#define _ARTMATCHER_HPP_

#include "AIArt.h"
#include "AIMatchingArt.h"

#ifdef __cplusplus
extern "C"
{
#endif

#pragma PRAGMA_ALIGN_BEGIN
#pragma PRAGMA_IMPORT_BEGIN

class ArtMatcher
{
public:
	ArtMatcher(int iNumSpecs);
	virtual ~ArtMatcher(void);
	//
	ASErr SetSpec(int iX, short shType, long lWhichAttr, long lAttr);
	//
	ASErr GetMatchingArt(void);
	int GetNumMatches(void);
	AIArtHandle GetMatchedArt(int iX);
	//
	enum eArtMatcherErrors
	{
		AM_OK = kNoErr,
		AM_InvalidIndex,
		AM_InvalidSuite,
		AM_NumErrs
	};
	//
private:
	int m_iNumSpecs;
	AIMatchingArtSpec *m_pSpecs;
	//
	ASInt32 m_lNumMatches;
	AIArtHandle **m_hMatches;
};

#pragma PRAGMA_IMPORT_END
#pragma PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif // _ARTMATCHER_HPP_

