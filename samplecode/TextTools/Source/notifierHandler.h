/*
 *  notifierHandler.h
 *  TextTools
 *
 *  Created by Comp Mac 8a on 10/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __notifierHandler__
#define __notifierHandler__

#include "AINotifier.h"
#include "AIRuntime.h"

extern AIErr addNotifiers( SPInterfaceMessage *message );

extern AIErr goNotifier( AINotifierMessage *message );

#endif
