/*
 *  FindReplaceGraphics.h
 *  ColorTools
 *
 *  Created by Comp Mac 8a on 5/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __findreplace__
#define __findreplace__

/*******************************************************************************
 **
 **	PROTOTYPES
 **
 **/


struct COLORS {
	AIColor FromColor;
	AIColor ToColor;
};

// private functions
AIErr createFindReplaceDialog( AINotifierMessage *message );
ASErr ASAPI FindReplaceDlgInit(ADMDialogRef dlg);
static void ASAPI FindReplaceDlgDestroyProc(ADMDialogRef dlg);

static void ASAPI changeButtonUp( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI removeUnusedButtonUp( ADMItemRef item, ADMNotifierRef notifier);
static ASBoolean ASAPI fromListClicked(  ADMItemRef item, ADMTrackerRef tracker);
static ASBoolean ASAPI toListClicked(  ADMItemRef item, ADMTrackerRef tracker);
static void ASAPI listChanged( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI attributeListChanged( ADMItemRef item, ADMNotifierRef notifier);
static void ASAPI addRemoveListChanged( ADMItemRef item, ADMNotifierRef notifier);

void changeSwatchList( int list );
void changeChangeInList();
void fillArtSet ( AIArtSet &artSet , int ChangeIn );
bool setColorByName ( string name , AIColor &color );

void adjustColor(AIColor *color, void *userData, AIErr *result, AIBoolean *altered);



#define layerMinWidth  	206
#define layerMaxWidth	618

#ifdef MAC_ENV
#define layerMinHeight	74		// 3 * layerLineHeight + bottomBarHeight-2 (see Resize)
#else
#define layerMinHeight	76		// 3 * layerLineHeight + bottomBarHeight
#endif
#define layerLineHeight 20


#endif //__findreplace__
