#ifndef __AI80Color__
#define __AI80Color__

/*
 *        Name:	AI80Color.h
 *   $Revision: 17 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Color Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

typedef enum {
	kGrayColor = 0,				/* Gray */
	kFourColor,					/* Solid ink, expressed in four process colors */
	kPattern,					/* color with a pattern from the art's pattern list */
	kCustomColor,				/* Solid ink, expressed as a custom ink color */
	kGradient,					/* Gradient */
	kThreeColor,				/* RGB colors */
	kNoneColor					/* None color, NOTE: when painted with kNoneColor, still need to
									set AIPathStyle.fillPaint or strokePaint to false */
} AIColorTag;

typedef enum {
	kCustomFourColor = 0,		/* Solid ink, expressed in four process colors */
	kCustomThreeColor			/* RGB colors */
 } AICustomColorTag;

enum {
	kLinearGradient = 0,
	kRadialGradient
};

typedef short AICustomColorFlags;

#define	kCustomSpotColor			0x0001
#define kCustomRegistrationColor	0x0002

/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct {
	AIReal gray;
} AIGrayColorStyle;

typedef struct {
	AIBoolean gray;
} AIGrayColorStyleMap;


typedef struct {
	AIReal cyan, magenta, yellow, black;
} AIFourColorStyle;

typedef struct {
	AIBoolean cyan, magenta, yellow, black;
} AIFourColorStyleMap;


typedef struct {
	AIReal red, green, blue;
} AIThreeColorStyle;

typedef struct {
	AIBoolean red, green, blue;
} AIThreeColorStyleMap;


typedef union {
	AIFourColorStyle	f;
	AIThreeColorStyle	rgb;
	AIGrayColorStyle	gray;
} AICustomColorUnion;

typedef struct {
	AICustomColorTag	kind;
	AICustomColorUnion	c;
	AICustomColorFlags	flag;
	unsigned char		name[32];
} AICustomColor;
typedef void *AICustomColorHandle;

typedef struct {
	AICustomColorHandle color;
	AIReal tint;
} AICustomColorStyle;

typedef struct {
	AIBoolean color;
	AIBoolean tint;
} AICustomColorStyleMap;


typedef struct {
	AIBoolean not_implemented;
} AIPattern;
typedef void *AIPatternHandle;

typedef struct {
	AIPatternHandle pattern;	 	/* reference to the AIPattern */
	AIReal shiftDist;	/* distance to translate the [unscaled] prototype before filling */
	AIReal shiftAngle;	/* angle to translate the [unscaled] prototype before filling */
	AIRealPoint scale;	/* fraction to scale the prototype before filling */
	AIReal rotate;		/* angle to rotate the prototype before filling */
	AIBoolean reflect;	/* whether or not the prototype is reflected before filling */
	AIReal reflectAngle;	/* axis around which to reflect */
	AIReal shearAngle;	/* angle to slant the shear by */
	AIReal shearAxis;	/* axis to shear with respect to */
	AIRealMatrix transform; /* additional transformation arising from manipulating the path */
} AIPatternStyle;

typedef struct {
	AIBoolean pattern;
	AIBoolean shiftDist;
	AIBoolean shiftAngle;
	AIBoolean scale;
	AIBoolean rotate;
	AIBoolean reflect;
	AIBoolean reflectAngle;
	AIBoolean shearAngle;
	AIBoolean shearAxis;
	AIBoolean transform;
} AIPatternStyleMap;


typedef void *AIGradientHandle;  // opaque reference to gradient color

typedef struct {
	AIGradientHandle gradient; 			/* reference to the AIGradient */
	AIRealPoint gradientOrigin;			/* gradient vector origin */
	AIReal gradientAngle;				/* gradient vector angle */
	AIReal gradientLength;				/* gradient vector length */
	AIRealMatrix matrix;					/* transformation applied by xform tools */
	AIReal hiliteAngle;					/* gradient hilite vector angle */
	AIReal hiliteLength;					/* length of hiliteVector measured as a fraction
										of the length of the gradient vector (gradientLength) */
} AIGradientStyle;

typedef struct {
	AIBoolean gradient;
	AIBoolean gradientOrigin;
	AIBoolean gradientAngle;
	AIBoolean gradientLength;
	AIBoolean matrix;
	AIBoolean hiliteAngle;
	AIBoolean hiliteLength;
} AIGradientStyleMap;


typedef union { 
	AIGrayColorStyle g;
	AIFourColorStyle f;
	AIThreeColorStyle rgb;
	AICustomColorStyle c;
	AIPatternStyle p;
	AIGradientStyle b;
} AIColorUnion;

typedef union { 
	AIGrayColorStyleMap g;
	AIFourColorStyleMap f;
	AIThreeColorStyleMap rgb;
	AICustomColorStyleMap c;
	AIPatternStyleMap p;
	AIGradientStyleMap b;
} AIColorUnionMap;

typedef struct {
	AIColorTag kind;			/* Used to determine the color variant */
	AIColorUnion c;
} AIColor;

typedef struct {
	AIBoolean kind;
	AIColorUnionMap c;
} AIColorMap;


typedef struct {
	AIReal midPoint; 				/* midpoint skew value in percent */
	AIReal rampPoint;				/* location of color in the blend in percent */
	AIColor color;
} AIGradientStop;


#include "AIHeaderEnd.h"

#endif
