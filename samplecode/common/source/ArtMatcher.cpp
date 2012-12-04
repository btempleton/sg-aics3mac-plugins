//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/ArtMatcher.cpp $
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

#include "ArtMatcher.hpp"
#include "AIMdMemory.h"
#include "SPBasic.h"

// these need to be declared by client
extern "C" AIMatchingArtSuite *sAIMatchingArt;
extern "C" SPBasicSuite *sSPBasic;

ArtMatcher::ArtMatcher(int iNumSpecs)
{
	if (iNumSpecs > 0)
	{
		m_pSpecs = new AIMatchingArtSpec[iNumSpecs];
	}
	else
	{
		m_pSpecs = NULL;
	}

	if (m_pSpecs == NULL)
	{
		m_iNumSpecs = 0;
	}
	else
	{
		m_iNumSpecs = iNumSpecs;
	}

	m_lNumMatches = 0;
	m_hMatches = NULL;
}

ArtMatcher::~ArtMatcher(void)
{
	delete [] m_pSpecs;

	if (m_hMatches != NULL && sSPBasic != NULL)
	{
		AIMdMemorySuite *sAIMdMemory = NULL;

		sSPBasic->AcquireSuite(kAIMdMemorySuite, kAIMdMemorySuiteVersion, (void **) &sAIMdMemory);

		if (sAIMdMemory != NULL)
		{
			sAIMdMemory->MdMemoryDisposeHandle((AIMdMemoryHandle) (m_hMatches));
			sSPBasic->ReleaseSuite(kAIMdMemorySuite, kAIMdMemorySuiteVersion);
		}
	}
}

ASErr
ArtMatcher::SetSpec(int iX, short shType, long lWhichAttr, long lAttr)
{
	ASErr result = kNoErr;

	if (0 <= iX && iX <= m_iNumSpecs)
	{
		AIMatchingArtSpec *pSpec = m_pSpecs + iX;

		pSpec->type = shType;
		pSpec->whichAttr = lWhichAttr;
		pSpec->attr = lAttr;
	}
	else
	{
		result = AM_InvalidIndex;
	}

	return result;
}

ASErr
ArtMatcher::GetMatchingArt(void)
{
	ASErr result = kNoErr;

	m_lNumMatches = 0;

	if (sAIMatchingArt == NULL)
	{
		result = AM_InvalidSuite;
		goto ex;
	}

	result =
	sAIMatchingArt->GetMatchingArt
	(
		m_pSpecs,
		(short) m_iNumSpecs,
		&m_hMatches,
		&m_lNumMatches
	);

ex:
	return result;
}

int
ArtMatcher::GetNumMatches(void)
{
	return m_lNumMatches;
}

AIArtHandle
ArtMatcher::GetMatchedArt(int iX)
{
	AIArtHandle matchedArt = NULL;

	if (0 <= iX && iX < m_lNumMatches)
	{
		matchedArt = (*m_hMatches)[iX];
	}

	return matchedArt;
}

