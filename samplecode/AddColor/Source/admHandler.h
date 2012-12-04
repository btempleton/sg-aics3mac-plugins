//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/ADMNonModalDialog/Source/admHandler.h $
//
//  $Revision: #4 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/

// private functions
AIErr createADMDialog( AINotifierMessage *message );
ASErr ASAPI DlgInit(ADMDialogRef dlg);
static void ASAPI DlgDestroyProc(ADMDialogRef dlg);
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



