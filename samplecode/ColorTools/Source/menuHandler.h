/*
 *  menuHandler.h
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __menuHandler__
#define __menuHandler__

#include "AIMenu.h"

extern AIErr addMenu( SPInterfaceMessage *message );

extern AIErr goMenuItem( AIMenuMessage *message );
extern AIErr updateMenuItem( AIMenuMessage *message );


#endif
