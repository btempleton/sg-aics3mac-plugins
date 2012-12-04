/*
 *        Name:	AIFilePath.cpp
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "AIFilePath.h"

using ai::FilePath;
using ai::UnicodeString;

#ifdef _IAIFilePathSuite_INCLUDE_H_
    #include _IAIFilePathSuite_INCLUDE_H_
#else
	extern "C" AIFilePathSuite *sAIFilePath;
#endif

/* Throw result as an ai::Error */
static void check_result(AIErr result)
{
	if ( result != kNoErr )
	{
		throw ai::Error(result);
	}
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::ResetVolumeCache() AINOTHROW
{
	sAIFilePath->ResetVolumeCache();
}

////////////////////////////////////////////////////////////////////////////////
// Constructors/destructors
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath():
	impl(0)
{
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const FilePath &src):
	impl(0)
{
	AIErr result = sAIFilePath->Copy(src, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const ai::UnicodeString &in, bool expandName):
	impl(0)
{
	AIErr result = sAIFilePath->Set(in, expandName, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const SPPlatformFileSpecification &spec):
	impl(0)
{
	sAIFilePath->SetFromSPFileSpec(spec, *this);
}

#ifdef MAC_ENV
////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const CFStringRef string):
	impl(0)
{
	sAIFilePath->SetFromCFString(string, *this);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const FSRef &ref):
	impl(0)
{
	OSStatus result = sAIFilePath->SetFromFSRef(ref, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const FSSpec &spec):
	impl(0)
{
	OSStatus result = sAIFilePath->SetFromFSSpec(spec, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const CFURLRef url):
	impl(0)
{
	sAIFilePath->SetFromCFURL(url, *this);
}

#endif	// MAC_ENV

////////////////////////////////////////////////////////////////////////////////
FilePath::~FilePath()
{
	(void)sAIFilePath->DeleteFilePath(*this);
}

////////////////////////////////////////////////////////////////////////////////
FilePath &FilePath::operator=(const FilePath &in)
{
	AIErr result = sAIFilePath->Copy(in, *this);
	check_result(result);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Other members
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// The Copy function is not explicitly implemented here-- use the copy constructor

////////////////////////////////////////////////////////////////////////////////
bool FilePath::IsEmpty() const
{
	return sAIFilePath->IsEmpty(*this);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::MakeEmpty()
{
	sAIFilePath->MakeEmpty(*this);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::Equal(const FilePath &other, const bool resolveLinks) const
{
	return sAIFilePath->Equal(*this, other, resolveLinks);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator==(const FilePath &path) const
{
	return sAIFilePath->Equal(*this, path, false);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator!=(const FilePath &path) const
{
	return !sAIFilePath->Equal(*this, path, false);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator<(const FilePath &path) const
{
	return sAIFilePath->LessThan(*this, path);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::StartsWithDelimiter() const
{
	return sAIFilePath->StartsWithDelimiter(*this);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::EndsWithDelimiter() const
{
	return sAIFilePath->EndsWithDelimiter(*this);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::AddComponent(const ai::UnicodeString &addend)
{
	AIErr result = sAIFilePath->AddComponent(addend, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::RemoveComponent()
{
	sAIFilePath->RemoveComponent(*this);
}

	
////////////////////////////////////////////////////////////////////////////////
void FilePath::AddExtension(const ai::UnicodeString &ext)
{
	sAIFilePath->AddExtension(ext, *this);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::RemoveExtension()
{
	sAIFilePath->RemoveExtension(*this);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::Exists(
	const bool resolveLinks,
	ai::UnicodeString *longPath,
	bool *isFile) const
{
	AIBool8 isFileRet;
	bool ret = sAIFilePath->Exists(*this, resolveLinks, longPath, &isFileRet);
	if (isFile) *isFile = isFileRet;
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::Resolve()
{
	AIErr result = sAIFilePath->Resolve(*this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
// Set methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void FilePath::Set(const ai::UnicodeString &string, bool expandName)
{
	AIErr result = sAIFilePath->Set(string, expandName, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::SetFromSPFileSpec(const SPPlatformFileSpecification &spec)
{
	sAIFilePath->SetFromSPFileSpec(spec, *this);
}

#ifdef MAC_ENV
////////////////////////////////////////////////////////////////////////////////
void FilePath::SetFromCFString(const CFStringRef string)
{
	sAIFilePath->SetFromCFString(string, *this);
}

////////////////////////////////////////////////////////////////////////////////
OSStatus FilePath::SetFromFSRef(const FSRef &ref)
{
	OSStatus result = sAIFilePath->SetFromFSRef(ref, *this);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
OSStatus FilePath::SetFromFSSpec(const FSSpec &spec)
{
	OSStatus result = sAIFilePath->SetFromFSSpec(spec, *this);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::SetFromCFURL(const CFURLRef url)
{
	sAIFilePath->SetFromCFURL(url, *this);
}
#endif	// MAC_ENV

////////////////////////////////////////////////////////////////////////////////
// Get methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileName(const bool displayName) const
{
	ai::UnicodeString fileName;
	AIErr result = sAIFilePath->GetFileName(*this, displayName, fileName);
	
	check_result(result);
	return fileName;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileNameNoExt() const
{
	ai::UnicodeString fileName;
	AIErr result = sAIFilePath->GetFileNameNoExt(*this, fileName);
	
	check_result(result);
	return fileName;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileExtension() const
{
	ai::UnicodeString fileExt;
	AIErr result = sAIFilePath->GetFileExtension(*this, fileExt);
	
	check_result(result);
	return fileExt;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFullPath(const bool displayName) const
{
	ai::UnicodeString fullPath;
	AIErr result = sAIFilePath->GetFullPath(*this, displayName, fullPath);

	check_result(result);
	return fullPath;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetDirectory(const bool displayName) const
{
	ai::UnicodeString dir;
	AIErr result = sAIFilePath->GetDirectory(*this, displayName, dir);
	
	check_result(result);
	return dir;
}

////////////////////////////////////////////////////////////////////////////////
#ifdef MAC_ENV
void FilePath::GetVolumeAndParent(FSVolumeRefNum *vol, UInt32 *parent) const
{
	sAIFilePath->GetVolumeAndParent(*this, vol, parent);
}
#endif

////////////////////////////////////////////////////////////////////////////////
const char FilePath::GetDelimiter()
{
	return sAIFilePath->GetDelimiter();
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetShortPath() const
{
	ai::UnicodeString path;
	AIErr result = sAIFilePath->GetShortPath(*this, path);
	
	check_result(result);
	return path;
}

////////////////////////////////////////////////////////////////////////////////
AIErr FilePath::GetCreatorAndType(unsigned long *creator, unsigned long *type) const
{
	AIErr result = sAIFilePath->GetCreatorAndType(*this, creator, type);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetAsURL(const bool displayName) const
{
	ai::UnicodeString url;
	AIErr result = sAIFilePath->GetAsURL(*this, displayName, url);
	
	check_result(result);
	return url;
}

////////////////////////////////////////////////////////////////////////////////
FilePath FilePath::GetParent() const
{
	FilePath parent;
	AIErr result = sAIFilePath->GetParent(*this, parent);
	
	check_result(result);
	return parent;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::GetAsSPPlatformFileSpec(SPPlatformFileSpecification &spec) const
{
	AIErr result = sAIFilePath->GetAsSPPlatformFileSpec(*this, spec);
	check_result(result);
}

#ifdef MAC_ENV
////////////////////////////////////////////////////////////////////////////////
CFStringRef FilePath::GetAsCFString() const
{
	CFStringRef string = sAIFilePath->GetAsCFString(*this);
	return string;
}

////////////////////////////////////////////////////////////////////////////////
OSStatus FilePath::GetAsFSRef(FSRef &ref) const
{
	OSStatus result = sAIFilePath->GetAsFSRef(*this, ref);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
OSStatus FilePath::GetAsFSSpec(FSSpec &spec) const
{
	OSStatus result = sAIFilePath->GetAsFSSpec(*this, spec);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
CFURLRef FilePath::GetAsCFURL() const
{
	return sAIFilePath->GetAsCFURL(*this);
}
#endif	// MAC_ENV
