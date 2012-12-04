/*
 *  menuHandler.h
 *  BStatMU
 *
 *  Created by Comp Mac 8a on 8/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __menuHandler__
#define __menuHandler__

#include "AIMenu.h"

extern AIErr addMenu( SPInterfaceMessage *message );

extern AIErr goMenuItem( AIMenuMessage *message );
extern AIErr updateMenuItem( AIMenuMessage *message );


#endif
