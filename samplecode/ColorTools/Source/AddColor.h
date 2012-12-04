/*
 *  AddColor.h
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __addcolor__
#define __addcolor__

#include <Carbon/Carbon.h>

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/

// private functions
AIErr createAddColorDialog( AINotifierMessage *message );
ASErr ASAPI AddColorDlgInit(ADMDialogRef dlg);
static void ASAPI AddColorDlgDestroyProc(ADMDialogRef dlg);
static void ASAPI addButtonUp( ADMItemRef item, ADMNotifierRef notifier);
static ASBoolean ASAPI editTextEnter( ADMItemRef item, ADMTrackerRef tracker);
ai::UnicodeString createNameFromInput();
ai::UnicodeString makeColorName(char* middle);
void stripSpaces(char *Str);


#define layerMinWidth  	206
#define layerMaxWidth	618

#ifdef MAC_ENV
#define layerMinHeight	74		// 3 * layerLineHeight + bottomBarHeight-2 (see Resize)
#else
#define layerMinHeight	76		// 3 * layerLineHeight + bottomBarHeight
#endif
#define layerLineHeight 20

#endif //__addcolor__