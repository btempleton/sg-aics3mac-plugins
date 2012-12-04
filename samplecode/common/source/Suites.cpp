//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/source/Suites.cpp $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#include "Suites.hpp"

#include "SPAccess.h"
#include "SPBlocks.h"
#include "SPInterf.h"
#include "SPRuntme.h" 
#include "SPSuites.h" 
#include "AINotifier.h"
#include "AIContext.h"
#include "ADMBasic.h"

#include <string.h>
#include <stdio.h>

extern "C" {
	SPAccessSuite *sSPAccess;
	SPPluginsSuite *sSPPlugins;
	AINotifierSuite *sAINotifier;
	AIAppContextSuite *sAIAppContext;
	ADMBasicSuite *sADMBasic;
}

extern "C" SPBasicSuite *sSPBasic;

// These are the suites we always acquire because we need them
ImportSuite gBasicSuites[] =
{
	kSPAccessSuite, kSPAccessSuiteVersion, &sSPAccess,
	kSPPluginsSuite, kSPPluginsSuiteVersion, &sSPPlugins,
	kAINotifierSuite, kAINotifierSuiteVersion, &sAINotifier,
	kAIAppContextSuite, kAIAppContextVersion, &sAIAppContext,
	kADMBasicSuite, kADMBasicSuiteVersion, &sADMBasic,
};


extern ImportSuite gImportSuites[];

int Suites::fAcquiredCount = 0;

Suites::Suites()
{
	fError = AcquireSuites();
}

Suites::~Suites()
{
	ReleaseSuites();
}

ASErr Suites::AcquireSuites()
{
	ASErr error = kNoErr;
	long i;

	if (fAcquiredCount == 0)
	{
		for (i = 0; i < sizeof(gBasicSuites)/sizeof(gBasicSuites[0]); ++i)
		{
			error = AcquireSuite(gBasicSuites+i);
			if (error)
				goto error;	
		}
		for (i = 0; gImportSuites[i].name != nil; ++i)
		{
			error = AcquireSuite(gImportSuites+i);
			if (error)
				goto error;	
		}
	}
	fAcquiredCount++;
	
error:
	return error;
}

ASErr Suites::AcquireSuite(ImportSuite *suite)
{
	ASErr error = kNoErr;
	char message[256];

	if (suite->suite != nil) 
	{
		error = sSPBasic->AcquireSuite(suite->name, 
									suite->version, 
									(const void **)suite->suite);
		if ( error && sADMBasic != NULL )
		{
			sprintf(message, "Error: %d, suite: %s, version: %d!", error, suite->name, suite->version );
			sADMBasic->MessageAlert( message );

		}
	}
	return error;
}

ASErr Suites::ReleaseSuites() 
{
	ASErr error = kNoErr;
	long i;
	
	fAcquiredCount--;
	
	if (fAcquiredCount == 0)
	{
		for (i = 0; i < sizeof(gBasicSuites)/sizeof(gBasicSuites[0]); ++i)
		{
			error = ReleaseSuite(gBasicSuites+i);
			if ( error )
				goto error;
		}
		for (i = 0; gImportSuites[i].name != nil; ++i)
		{
			error = ReleaseSuite(gImportSuites+i);
			if (error)
				goto error;	
		}
	}
	
error:
	return error;
}

ASErr Suites::ReleaseSuite(ImportSuite *suite)
{
	ASErr error = kNoErr;

	if (suite->suite != nil) {
		void **s = (void **) suite->suite;
		if (*s != nil) {
			error = sSPBasic->ReleaseSuite(suite->name, suite->version);
			*s = nil;
		}
	}
	return error;
}

