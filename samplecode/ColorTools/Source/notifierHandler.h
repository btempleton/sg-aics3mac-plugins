/*
 *  notifierHandler.h
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __notifierHandler__
#define __notifierHandler__

#include "AINotifier.h"
#include "AIRuntime.h"

extern AIErr addNotifiers( SPInterfaceMessage *message );

extern AIErr goNotifier( AINotifierMessage *message );

#endif
