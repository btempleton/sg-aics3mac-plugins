/*
 *  DictFuncs.h
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DICTFUNCS_H
#define DICTFUNCS_H

#include "Node.h"
#include "string.h"

AIDictKey GenerateKey(string identifier, int CAIndex = -1);
AIDictKey GenerateKey(ai::UnicodeString identifier, int CAIndex = -1);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index
//Returns the existing key, or a new key reference if none was found

ai::UnicodeString GenerateUIDString(string identifier, int CAIndex = -1);
ai::UnicodeString GenerateUIDString(ai::UnicodeString identifier, int CAIndex);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index
//Returns a string in the format "identifier_CAIndex"

ASBoolean CheckArtHandleFromUIDRef(AIUIDRef artToCheck);
//artToCheck -- The UIDRef to validate
//Returns TRUE if the uid points to an art handle in the document, FALSE if its NULL or invalid

AIArtHandle GetArtHandleFromUIDRef(AIUIDRef uidRef);
//uidRef -- the UID Reference to find the art object associated with
//Returns the handle to the art object with the associated id, or a NULL handle if it couldn't be found

AIArtHandle GetArtHandleFromIdentifier(ai::UnicodeString identifier, int CAIndex = -1);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index

AIBoolean AddArtUIDToDictionary(AIArtHandle currArt, ai::UnicodeString identifier, int CAIndex = -1);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index

AIBoolean CheckDictionaryForArtObjectWithIdentifier(ai::UnicodeString identifier, int CAIndex = -1);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index

AIBoolean RemoveIdentifierFromDictionary(ai::UnicodeString identifier, int CAIndex = -1);
//identifier -- the word part of the key... usually the variable name we're storing
//CAIndex -- the crop area index

#endif //DICTFUNCS_H