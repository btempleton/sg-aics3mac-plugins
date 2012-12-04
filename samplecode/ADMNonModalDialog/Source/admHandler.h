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

#define kADMNonModalDialogID	16000

#define kpopupItem	5
#define kpopupMenuID 800

#define kbeepItem 3
#define kbeepBeepItem 4

#define kspinEditPopupItem 6
#define kspinEditPopuMenuID 900

#define kradioButton1Item 7
#define kradioButton2Item 8
#define kradioButton3Item 9

#define kcheckBox1Item 10
#define kcheckBox2Item 11

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/

// private functions
AIErr createADMDialog( AINotifierMessage *message );
ASErr ASAPI DlgInit(ADMDialogRef dlg);
static void ASAPI DlgDestroyProc(ADMDialogRef dlg);
static void ASAPI dialogPopupMenuProc( ADMItemRef item, ADMNotifierRef notifier);
static ASBoolean ASAPI dialogPopupMenuTrackProc(ADMItemRef item, ADMTrackerRef tracker);
static void ASAPI PopupProc( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI beepButtonUp( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI beepBeepButtonUp( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI spinEditPopupProc( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI radioButtonProc( ADMItemRef item, ADMNotifierRef notifier);

static void ASAPI checkBox1Proc( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI checkBox2Proc( ADMItemRef item, ADMNotifierRef notifier);
static int GetPopupSelection( ADMItemRef item );

#define layerMinWidth  	206
#define layerMaxWidth	618

#ifdef MAC_ENV
#define layerMinHeight	74		// 3 * layerLineHeight + bottomBarHeight-2 (see Resize)
#else
#define layerMinHeight	76		// 3 * layerLineHeight + bottomBarHeight
#endif
#define layerLineHeight 20



