/*
 *  DictFuncs.cpp
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "common.h"
#include "DictFuncs.h"

AIDictKey GenerateKey(string identifier, int CAIndex) {
	
	char* cstr;
	cstr = new char [identifier.size()+1];
	strcpy (cstr, identifier.c_str());
	
	AIDictKey currKey = NULL;
	
	char UIDString[identifier.size()+4];
	sprintf(UIDString,"%s_%i", cstr, CAIndex );
	
	currKey = sAIDictionary->Key(UIDString);
	
	delete[] cstr;
	
	return currKey;
}

AIDictKey GenerateKey(ai::UnicodeString identifier, int CAIndex) {
	
	char* cstr;
	cstr = new char [identifier.size()+1];
	strcpy ( cstr, identifier.as_Platform().c_str() );
	
	AIDictKey currKey = NULL;
	
	char UIDString[identifier.size()+4];
	sprintf(UIDString,"%s_%i", cstr, CAIndex );
	
	currKey = sAIDictionary->Key(UIDString);
	
	delete[] cstr;
	
	return currKey;
}

ai::UnicodeString GenerateUIDString(string identifier, int CAIndex) {
	char* cstr;
	cstr = new char [identifier.size()+1];
	strcpy ( cstr, identifier.c_str() );
	
	char UIDString[identifier.size()+4];
	sprintf(UIDString,"%s_%i", cstr, CAIndex );
	
	delete[] cstr;
	
	return ai::UnicodeString(UIDString);
}


ai::UnicodeString GenerateUIDString(ai::UnicodeString identifier, int CAIndex) {
	char* cstr;
	cstr = new char [identifier.size()+1];
	strcpy ( cstr, identifier.as_Platform().c_str() );
	
	char UIDString[identifier.size()+4];
	sprintf(UIDString,"%s_%i", cstr, CAIndex );
	
	delete[] cstr;
	
	return ai::UnicodeString(UIDString);
}


ASBoolean CheckArtHandleFromUIDRef(AIUIDRef uidToCheck) {
	//The handle was NULL, so we don't need to look for this one
	if (!uidToCheck) {
		return FALSE;
	}
	
	AIArtHandle currArtObject = NULL;
	AIUIDREFRef uidREFRef = NULL;
	sAIUID->NewUIDREF(uidToCheck, &uidREFRef);
	
	sAIUIDUtils->GetReferencedArt(uidREFRef, &currArtObject);
	sAIUIDREF->Release(uidREFRef);
	
	if (currArtObject) {
		return sAIArt->ValidArt(currArtObject, TRUE);
	} else { 
		return FALSE;
	}	
}

AIArtHandle GetArtHandleFromUIDRef(AIUIDRef uidRef) {
	if (!uidRef) {
		return NULL;
	}
	
	AIArtHandle currArtObject = NULL;
	AIUIDREFRef uidREFRef = NULL;
	sAIUID->NewUIDREF(uidRef, &uidREFRef);
	
	sAIUIDUtils->GetReferencedArt(uidREFRef, &currArtObject);
	sAIUIDREF->Release(uidREFRef);
	
	if (currArtObject) {
		if (sAIArt->ValidArt(currArtObject, TRUE) ) {
			return currArtObject;
		} else {
			return NULL;
		}
	} else { 
		return NULL;
	}	
	
}


AIArtHandle GetArtHandleFromIdentifier(ai::UnicodeString identifier, int CAIndex)
{
	AIArtHandle foundArtHandle = NULL;
	
	AIDictionaryRef currDict = NULL;
	sAIDocument->GetDictionary(&currDict);
	
	if (currDict) {
		AIDictKey keyForIdentifier = GenerateKey(identifier, CAIndex);
		AIEntryRef entryForIdentifier = NULL;
		entryForIdentifier = sAIDictionary->Get(currDict, keyForIdentifier);
		if (entryForIdentifier) {
			AIUIDREFRef uidRefForIdentifier = NULL;
			sAIEntry->ToUIDREF(entryForIdentifier, &uidRefForIdentifier);
			if (uidRefForIdentifier) {
				AIUIDRef uidForIdentifier = NULL;
				sAIUIDREF->GetUID(uidRefForIdentifier, &uidForIdentifier);
				if (uidForIdentifier) {
					foundArtHandle = GetArtHandleFromUIDRef(uidForIdentifier);
					
					sAIUID->Release(uidForIdentifier);
				}				
				sAIUIDREF->Release(uidRefForIdentifier);
			}
			sAIEntry->Release(entryForIdentifier);
		}
		sAIDictionary->Release(currDict);
	}
	
	return foundArtHandle;
}


AIBoolean AddArtUIDToDictionary(AIArtHandle currArt, ai::UnicodeString identifier, int CAIndex) {
	AIDictionaryRef currDict = NULL;
	sAIDocument->GetDictionary(&currDict);
	
	if (currDict) {
		AIUIDRef uid = NULL;
		sAIUIDUtils->GetArtUID(currArt, TRUE /*To create one if there is none*/, &uid);
		if (uid) {
			AIUIDREFRef uidREFRef = NULL;
			sAIUID->NewUIDREF(uid, &uidREFRef);
			if (uidREFRef) {
				AIEntryRef newEntry = NULL;
				newEntry = sAIEntry->FromUIDREF(uidREFRef);
				if (newEntry) {
					
					sAIDictionary->Set(currDict, GenerateKey(identifier, CAIndex), newEntry);
					
					sAIEntry->Release(newEntry);	
				}// else break;
				sAIUIDREF->Release(uidREFRef);
			} //else break;
			sAIUID->Release(uid);
		} //else break;
		sAIDictionary->Release(currDict);
	} //else return FALSE;
	
	return TRUE;
}


AIBoolean CheckDictionaryForArtObjectWithIdentifier(ai::UnicodeString identifier, int CAIndex)
{
	AIBoolean foundRef = FALSE;
	
	AIDictionaryRef currDict = NULL;
	sAIDocument->GetDictionary(&currDict);
	
	if (currDict) {
		AIDictKey keyForIdentifier = GenerateKey(identifier, CAIndex);
		AIEntryRef entryForIdentifier = NULL;
		entryForIdentifier = sAIDictionary->Get(currDict, keyForIdentifier);
		if (entryForIdentifier) {
			AIUIDREFRef uidRefForIdentifier = NULL;
			sAIEntry->ToUIDREF(entryForIdentifier, &uidRefForIdentifier);
			if (uidRefForIdentifier) {
				AIUIDRef uidForIdentifier = NULL;
				sAIUIDREF->GetUID(uidRefForIdentifier, &uidForIdentifier);
				if (uidForIdentifier) {
					foundRef = CheckArtHandleFromUIDRef(uidForIdentifier);
					
					sAIUID->Release(uidForIdentifier);
				}				
				sAIUIDREF->Release(uidRefForIdentifier);
			}
			sAIEntry->Release(entryForIdentifier);
		}
		sAIDictionary->Release(currDict);
	}
	
	if (foundRef) return TRUE;
	else return FALSE;
	
}

AIBoolean RemoveIdentifierFromDictionary(ai::UnicodeString identifier, int CAIndex)
{
	AIErr error = kNoErr;
	
	AIDictionaryRef currDict = NULL;
	sAIDocument->GetDictionary(&currDict);
	
	if (currDict) {
		AIDictKey keyForIdentifier = GenerateKey(identifier, CAIndex);
		
		error = sAIDictionary->DeleteEntry(currDict, keyForIdentifier);
		
		sAIDictionary->Release(currDict);
	}
	
	if (error == kNoErr) return TRUE;
	else return FALSE;
	
}