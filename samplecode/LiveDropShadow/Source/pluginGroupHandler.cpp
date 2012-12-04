//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/LiveDropShadow/Source/pluginGroupHandler.cpp $
//
//  $Revision: #3 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"

#include "common.h"
#include "plugingroupHandler.h"

extern AIErr goNotify( AIPluginGroupMessage *message ) {

	AIErr result = kNoErr;
	return result;	
}


extern AIErr goUpdate( AIPluginGroupMessage *message ) {


	#define DROP_SHADOW_OFFSET 5

	AIErr result = kNoErr;
	AIArtHandle plugin = message->art;
	AIArtHandle editArt = NULL;
	AIArtHandle resultArt = NULL;
	unsigned long count = 0;
//	ObjectData local;

	AIArtHandle child;
	AIArtHandle dropShadowGroup;
	AIArtHandle duplicate;

//	AILayerHandle layer;
//	AIRealRect bounds;



	// get the edit art
	result = sAIPluginGroup->GetPluginArtEditArt( plugin, &editArt );
	
	// get the result art
	result = sAIPluginGroup->GetPluginArtResultArt( plugin, &resultArt );

	result = sAIPluginGroup->GetPluginArtDataCount( plugin, &count );

	// destroy all art that exists below the result art
	result = sAIArt->GetArtFirstChild( resultArt, &child );
	
	while ( ( result == kNoErr ) && ( child != NULL ) ) {
	
		if ( result == kNoErr ) {
		
			result = sAIArt->DisposeArt( child );
		}
		
		if ( result == kNoErr ) {
			result = sAIArt->GetArtFirstChild( resultArt, &child );
		}
	}
	
	// build the drop shadow group
	if ( result == kNoErr ) {
	
		result = sAIArt->NewArt( kGroupArt, kPlaceInsideOnTop, resultArt, &dropShadowGroup );
	
	}

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtFirstChild( editArt, &child );
	
	}
	
	while ( ( result == kNoErr ) && ( child != NULL ) ) {
	
			result = sAIArt->DuplicateArt( child, kPlaceInsideOnTop, dropShadowGroup, &duplicate );
			result = sAIArt->GetArtSibling( child, &child );		
	}
	
	// make a copy of the original edit art above the drop shadow grou
	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtFirstChild( editArt, &child );
	
	}
	
	while ( ( result == kNoErr ) && ( child != NULL ) ) {
	
			result = sAIArt->DuplicateArt( child, kPlaceAbove, dropShadowGroup, &duplicate );
			result = sAIArt->GetArtSibling( child, &child );		
	}

	
	// set the drop shadow style
	result = setDropShadowStyle( dropShadowGroup );
	
	// transform the drop shadow
	result = transformDropShadow( dropShadowGroup, DROP_SHADOW_OFFSET, -DROP_SHADOW_OFFSET, 0, 1, 1 );
	

	return result;		
}


extern AIErr SetFilteredFill( AIBoolean *paint, AIFillStyle *fill ) {

	AIErr result = kNoErr;

	*paint = false;
	
	fill->color.kind = kGrayColor;
	fill->color.c.g.gray = kAIRealZero;
	
	fill->overprint = false;
	
	return result;
	
}


extern AIErr SetFilteredStroke( AIBoolean *paint, AIStrokeStyle *stroke ) {

	AIErr result = kNoErr;

	*paint = true;

	stroke->color.kind = kGrayColor;
	stroke->color.c.g.gray = kAIRealOne;
	
	stroke->overprint = false;
	
	stroke->width = kAIRealOne;
	stroke->dash.length = 0;
	stroke->cap = kAIButtCap;
	stroke->join = kAIMiterJoin;
	stroke->miterLimit = _ShortToAIReal(4);
	
	return result;
	
}


extern AIErr SetFilteredStyle( AIArtHandle object ) {

	AIErr result = kNoErr;

	short type;
	AIPathStyle style;
	AIArtHandle child;

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( object, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
	case kMysteryPathArt:
	case kRasterArt:
	
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		if ( result == kNoErr ) {

			result = SetFilteredFill( &style.fillPaint, &style.fill );
		
		}
		
		if ( result == kNoErr ) {

			result = SetFilteredStroke( &style.strokePaint, &style.stroke );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
		
	case kGroupArt:
	case kCompoundPathArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtFirstChild( object, &child );
		
		}
		
		while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
			if ( result == kNoErr ) {
			
				result = SetFilteredStyle( child );
				
			}
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtSibling( child, &child );
			
			}
			
		}
		break;
		
	case kPlacedArt:
	
		break;
	
	case kPluginArt:

		break;

	default:
	
		break;
	
	}
	
	return result;
	
}


extern AIErr SetBackingFill( AIBoolean *paint, AIFillStyle *fill ) {

	AIErr result = kNoErr;

	*paint = true;
	
	fill->color.kind = kGrayColor;
	fill->color.c.g.gray = kAIRealZero;
	
	fill->overprint = false;
	
	return result;
	
}


extern AIErr SetBackingStroke( AIBoolean *paint, AIStrokeStyle *stroke ) {

	AIErr result = kNoErr;

	*paint = false;

	stroke->color.kind = kGrayColor;
	stroke->color.c.g.gray = kAIRealOne;
	
	stroke->overprint = false;
	
	stroke->width = kAIRealOne;
	stroke->dash.length = 0;
	stroke->cap = kAIButtCap;
	stroke->join = kAIMiterJoin;
	stroke->miterLimit = _ShortToAIReal(4);
	
	return result;
	
}


extern AIErr SetBackingStyle( AIArtHandle object ) {

	AIErr result = kNoErr;

	short type;
	AIPathStyle style;
	AIArtHandle child;

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( object, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
	case kMysteryPathArt:
	case kRasterArt:
	
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		if ( result == kNoErr ) {

			result = SetBackingFill( &style.fillPaint, &style.fill );
		
		}
		
		if ( result == kNoErr ) {

			result = SetBackingStroke( &style.strokePaint, &style.stroke );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
		
	case kGroupArt:
	case kCompoundPathArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtFirstChild( object, &child );
		
		}
		
		while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
			if ( result == kNoErr ) {
			
				result = SetBackingStyle( child );
				
			}
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtSibling( child, &child );
			
			}
			
		}
		break;
		
	case kPlacedArt:
	
		break;
	
	case kPluginArt:

		break;

	default:
	
		break;
	
	}
	
	return result;
	
}


extern AIErr SetBoundingFill( AIBoolean *paint, AIFillStyle *fill ) {

	AIErr result = kNoErr;

	*paint = false;
	
	fill->color.kind = kGrayColor;
	fill->color.c.g.gray = kAIRealZero;
	
	fill->overprint = false;
	
	return result;
	
}


extern AIErr SetBoundingStroke( AIBoolean *paint, AIStrokeStyle *stroke ) {

	AIErr result = kNoErr;

	*paint = true;

	stroke->color.kind = kGrayColor;
	stroke->color.c.g.gray = kAIRealOne;
	
	stroke->overprint = false;
	
	stroke->width = kAIRealZero;
	stroke->dash.length = 0;
	stroke->cap = kAIButtCap;
	stroke->join = kAIMiterJoin;
	stroke->miterLimit = _ShortToAIReal(4);
	
	return result;
	
}


extern AIErr SetBoundingStyle( AIArtHandle object ) {

	AIErr result = kNoErr;

	short type;
	AIPathStyle style;
	AIArtHandle child;

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( object, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
	case kMysteryPathArt:
	case kRasterArt:
	
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		if ( result == kNoErr ) {

			result = SetBoundingFill( &style.fillPaint, &style.fill );
		
		}
		
		if ( result == kNoErr ) {

			result = SetBoundingStroke( &style.strokePaint, &style.stroke );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
		
	case kGroupArt:
	case kCompoundPathArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtFirstChild( object, &child );
		
		}
		
		while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
			if ( result == kNoErr ) {
			
				result = SetBoundingStyle( child );
				
			}
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtSibling( child, &child );
			
			}
			
		}
		break;
		
	case kPlacedArt:
	
		break;
	
	case kPluginArt:

		break;

	default:
	
		break;
	
	}
	
	return result;
	
}


extern AIErr SetClippingStyle( AIArtHandle object ) {

	AIErr result = kNoErr;

	short type;
	AIPathStyle style;
	AIArtHandle child;
	
	if ( object == NULL ) {
	
		return noErr;
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( object, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
	case kMysteryPathArt:
	case kRasterArt:
	
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		style.fillPaint = false;
		style.strokePaint = false;
		style.clip = true;
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
		
	case kGroupArt:
	case kCompoundPathArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtFirstChild( object, &child );
		
		}
		
		while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
			if ( result == kNoErr ) {
			
				result = SetClippingStyle( child );
			}
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtSibling( child, &child );
			
			}
			
		}
		break;
		
	case kPlacedArt:
	
		break;
	
	case kPluginArt:

		break;

	default:
	
		break;
	
	}
	
	return result;
	
}


extern AIErr DuplicateCoveredArt( AIArtHandle source, AIArtHandle destination, AIRealRect *bounds, AIArtHandle start, AIBoolean *found ) {

	AIErr result = kNoErr;

	short type;
	AIRealRect local;
				
	AIArtHandle child;
	AIArtHandle ahead;
	AIArtHandle clone;

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( source, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
	case kTextFrameArt:
	case kMysteryPathArt:
	case kPlacedArt:
	case kRasterArt:
	case kCompoundPathArt:
	
		if ( *found ) {
		
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtBounds( source, &local );
			
			}
			
			if ( sAIRealMath->AIRealRectOverlap( bounds, &local ) ) {
			
				if ( result == kNoErr ) {
			
					result = sAIArt->DuplicateArt( source, kPlaceInsideOnBottom, destination, &clone );
				
				}
			
			}
				
		}
		break;
		
	case kGroupArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtBounds( source, &local );
		
		}

		if ( sAIRealMath->AIRealRectOverlap( bounds, &local ) ) {
		
			AIBoolean clipped = false;
			
			if ( result == kNoErr ) {
			
				result = sAIGroup->GetGroupClipped( source, &clipped );
			
			}
			
			if ( clipped ) {

				if ( *found ) {
				
					if ( result == kNoErr ) {
				
						result = sAIArt->DuplicateArt( source, kPlaceInsideOnBottom, destination, &clone );
					
					}
				
				}
			
			} else {
				
				if ( result == kNoErr ) {
			
					result = sAIArt->NewArt( kGroupArt, kPlaceInsideOnBottom, destination, &clone );
				
				}
				
				if ( result == kNoErr ) {
				
					result = sAIArt->GetArtFirstChild( source, &child );
				
				}
				
				if ( result == kNoErr ) {
				
					result = sAIArt->GetArtSibling( child, &ahead );
					
				}

				while ( ( result == kNoErr ) && ( ahead != NULL ) ) {

					child = ahead;
				
					if ( result == kNoErr ) {

						result = sAIArt->GetArtSibling( child, &ahead );
					
					}
					
				}
				
				while ( ( result == kNoErr ) && ( child != NULL ) ) {
				
					if ( result == kNoErr ) {
					
						result = DuplicateCoveredArt( child, clone, bounds, start, found );
						
					}
				
					if ( result == kNoErr ) {
					
						result = sAIArt->GetArtPriorSibling( child, &child );
					
					}
				
				}
				
				if ( result == kNoErr ) {
				
					result = sAIArt->GetArtFirstChild( clone, &child );
				
				}
				
				if ( child == NULL ) {
				
					if ( result == kNoErr ) {
					
						result = sAIArt->DisposeArt( clone );
					
					}
				
				}
			
			}
			
		}
		break;
		
	case kPluginArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtBounds( source, &local );
		
		}

		if ( sAIRealMath->AIRealRectOverlap( bounds, &local ) ) {
		
			if ( result == kNoErr ) {
		
				result = sAIPluginGroup->GetPluginArtEditArt( source, &child );
			
			}
			
			if ( result == kNoErr ) {
			
				result = DuplicateCoveredArt( child, destination, bounds, start, found );
				
			}
		
		}
		break;
		
	default:
	
		break;
		
	}

	if ( source == start ) {
	
		*found = true;
	
	}
	
	return result;
	
}


extern AIErr StartLensObject( AIArtHandle *object, ObjectData *data ) {

	AIErr result = kNoErr;

	*object = NULL;
	
	return result;
	
}


extern AIErr FinishLensObject( AIArtHandle *object, ObjectData *data ) {

	AIErr result = kNoErr;
		
	*object = NULL;
	
	return result;
	
}


extern AIErr appendPluginGroup( AIArtHandle *object, ObjectData *data, AIArtHandle path ) {

	AIErr result = kNoErr;
	
	AIArtHandle editArt = NULL;

	if ( *object == NULL ) {
	
		if ( result == kNoErr ) {
		
			result = EditLensObject( data );
		
		}
		// create a new kPluginArt above the selected art	
		if ( result == kNoErr ) {
		
			result = sAIArt->NewArt( kPluginArt, kPlaceAbove, path, object );
		
		}
		
		if ( result == kNoErr ) {
			// register your pluginGroup
			result = sAIPluginGroup->UseAIPluginGroup( *object, g->dsPluginGroupHandle );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPluginGroup->SetPluginArtDataCount( *object, sizeof( ObjectData ) );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPluginGroup->SetPluginArtDataRange( *object, data, 0, sizeof( ObjectData ) );
		
		}
		
	}


	// unlock the path put it inside the edit art object
	if ( result == kNoErr ) {
	
		result = sAIArt->SetArtUserAttr( path, kArtLocked, kArtLocked );
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIArt->SetArtUserAttr( path, kArtLocked, 0 );
	
	}

	if ( result == kNoErr ) {
	
		result = sAIPluginGroup->GetPluginArtEditArt( *object, &editArt );
	
	}

	if ( result == kNoErr ) {
		// put path inside editArt
		result = sAIArt->ReorderArt( path, kPlaceInsideOnBottom, editArt );
	
	}
	
	
	return result;
	
}


extern AIErr ReleaseLensObject( AIArtHandle plugin ) {

	AIErr result = kNoErr;
	
	AIArtHandle editArt;
	AIArtHandle child;
	AIArtHandle clone;

	if ( result == kNoErr ) {
	
		result = sAIArt->SetArtUserAttr( plugin, kArtLocked, kArtLocked );
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIArt->SetArtUserAttr( plugin, kArtLocked, 0 );
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIPluginGroup->GetPluginArtEditArt( plugin, &editArt );
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtFirstChild( editArt, &child );
	
	}
	
	while ( ( result == kNoErr ) && ( child != NULL ) ) {
	
		if ( result == kNoErr ) {
	
			result = sAIArt->DuplicateArt( child, kPlaceAbove, plugin, &clone );
	
		}
		
		if ( result == kNoErr ) {
	
			result = sAIArt->GetArtSibling( child, &child );
	
		}
	
	}
	
	if ( result == kNoErr ) {
	
		result = sAIArt->DisposeArt( plugin );
	
	}
	
	return result;
	
}


extern AIErr FirstLensObject( AIArtHandle *object, ObjectData *data ) {

	AIErr result = kNoErr;

	long index, count;
	AIArtHandle **store = NULL;

	*object = NULL;
	
	if ( result == kNoErr ) {
	
		if ( sAIMatchingArt->GetSelectedArt( &store, &count ) ) {
		
			store = NULL;
			count = 0;
		
		}
	
	}

	if ( store != NULL ) {

		for ( index = 0; ( result == kNoErr ) && ( index < count ) && ( *object == NULL ); index++ ) {
		
			AIArtHandle art = (*store)[index];
			short artType = kUnknownArt;
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtType( art, &artType );
			
			}

			if ( artType == kPluginArt ) {
			
				AIPluginGroupHandle artEntry;
				
				if ( result == kNoErr ) {
				
					result = sAIPluginGroup->GetPluginArtPluginGroup(art, &artEntry);
				
				}
				
				if ( result == kNoErr ) {
				
					if ( artEntry != g->dsPluginGroupHandle ) {
					
						artType = kUnknownArt;
					
					}
				
				}
			
			}

			if ( artType == kPluginArt ) {

				unsigned long length;
				
				if ( result == kNoErr ) {
			  	
					result = sAIPluginGroup->GetPluginArtDataCount( art, &length );
				
				}
				
				if ( result == kNoErr ) {
				
					if ( length != sizeof( ObjectData ) ) {
					
						artType = kUnknownArt;
					
					}
				
				}
			
			}

			if ( artType == kPluginArt ) {

				if ( result == kNoErr ) {
				
					result = sAIPluginGroup->GetPluginArtDataRange( art, data, 0, sizeof( ObjectData ) );
				
				}
				
				if ( result == kNoErr ) {
				
					*object = art;
				
				}
			
			}
			
		}
		
	}

	if ( store != NULL ) {
	
		sAIMdMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle) store );
	
	}
	
	if ( result == kNoErr ) {
  	
  		if ( *object == NULL ) {
  		
  			result = kUnknownArtTypeErr;
  		
  		}
	
	}

	if ( result == kNoErr ) {
	
		result = EditLensObject( data );
	
	}

	return result;
	
}


extern AIErr LastLensObject( AIArtHandle *object, ObjectData *data ) {

	AIErr result = kNoErr;
	
	*object = NULL;
	
	return result;
	
}

extern AIErr ModifyLensObject( AIArtHandle *object, ObjectData *data, AIArtHandle plugin ) {

	AIErr result = kNoErr;
	
	if ( result == kNoErr ) {
  	
		result = sAIPluginGroup->SetPluginArtDataCount( plugin, sizeof( ObjectData ) );
	
	}

	if ( result == kNoErr ) {
	
		result = sAIPluginGroup->SetPluginArtDataRange( plugin, &data, 0, sizeof( ObjectData ) );
	
	}

	if(result == kNoErr)
	{
		sADMBasic->MessageAlert("The data stores size and range were set.");
	}
	else
	{
		sADMBasic->MessageAlert("An error occurred, the data stores size and range were not set.");
	}
	
	return result;
	
}


extern AIErr EditLensObject( ObjectData *data ) {

	AIErr result = kNoErr;
	
	return result;
	
}

/*
extern AIErr ReportError( AIErr result ) {

	short index = 0;
	
	switch ( result ) {
	
	case kNoErr:
		index = 0;
		break;
		
	default:
		index = kUnknownErrorString;
		break;
	
	}
	
	if ( index != 0 ) {
	
		char string255];
		
		error = sADMBasic->GetIndexString(message->d.self, kErrorStringResID, index, string, sizeof(string));
				ParamText( string, "\p", "\p", "\p" );

		InitCursor();
		Alert( kErrorAlertResID, NULL );
	
	}
	
	return result;
	
}
*/


extern AIErr setDropShadowStyle( AIArtHandle object ) {

	AIErr result = kNoErr;

	short type;
	AIPathStyle style;
	AIArtHandle child;

	if ( result == kNoErr ) {
	
		result = sAIArt->GetArtType( object, &type );
	
	}
	
	switch ( type ) {
	
	case kPathArt:
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		if ( result == kNoErr ) {

			result = setDropShadowFill( &style.fill );
		
		}
		
		if ( result == kNoErr ) {

			result = setDropShadowStroke( &style.stroke );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
	case kMysteryPathArt:
	case kRasterArt:
	
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->GetPathStyle( object, &style );
		
		}

		if ( result == kNoErr ) {

			result = setDropShadowFill( &style.fill );
		
		}
		
		if ( result == kNoErr ) {

			result = setDropShadowStroke( &style.stroke );
		
		}
		
		if ( result == kNoErr ) {
		
			result = sAIPathStyle->SetPathStyle( object, &style );
		
		}
		break;
		
	case kCompoundPathArt:
	
		if ( result == kNoErr ) {
		
			result = sAIArt->GetArtFirstChild( object, &child );
		
		}
		
		while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
			if ( result == kNoErr ) {
			
				result = setDropShadowStyle( child );
				
			}
			
			if ( result == kNoErr ) {
			
				result = sAIArt->GetArtSibling( child, &child );
			
			}
			
		}
		break;
		
	case kPlacedArt:
	
		break;
	
	case kPluginArt:

		break;

	default:
	
		break;
	
	}
	
	return result;
	
}



extern AIErr setDropShadowFill( AIFillStyle *fill ) {

	AIErr result = kNoErr;	

	fill->color.kind = kGrayColor;
	fill->color.c.g.gray = kAIRealOne * 0.5;
	fill->overprint = false;
	return result;
	
}


extern AIErr setDropShadowStroke( AIStrokeStyle *stroke ) {

	AIErr result = kNoErr;

	stroke->color.kind = kGrayColor;
	stroke->color.c.g.gray = kAIRealOne * 0.5;
	stroke->overprint = false;	
	return result;
	
}

	
extern AIErr transformDropShadow(  AIArtHandle art, AIReal tx, AIReal ty, AIReal theta, AIReal sx, AIReal sy ) {
	AIErr result = kNoErr;
//	AIRealRect artBounds, artboardBounds;
	AIRealPoint artCenter;
	AIRealMatrix artMatrix;	
	AIReal lineScale;
	AIArtHandle child;
	long transformFlags = kTransformObjects | kScaleLines;
	short type;
	AIRealRect artBounds;
	
	lineScale = (sAIRealMath->AIRealSqrt(sx)) * (sAIRealMath->AIRealSqrt(sy));
	
	sAIArt->GetArtType( art, &type );
	
	switch ( type ) {
	
		case kGroupArt:
			result = sAIArt->GetArtFirstChild( art, &child );
		
			while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
				if ( result == kNoErr ) {
					result = transformDropShadow( child, tx, ty, theta, sx, sy );
				}
			
				if ( result == kNoErr ) {
					result = sAIArt->GetArtSibling( child, &child );
				}
			}
		break;
	
		case kCompoundPathArt:
			result = sAIArt->GetArtFirstChild( art, &child );
		
			while ( ( result == kNoErr ) && ( child != NULL ) ) {
		
				if ( result == kNoErr ) {
					result = transformDropShadow( child, tx, ty, theta, sx, sy );
				}
			
				if ( result == kNoErr ) {
					result = sAIArt->GetArtSibling( child, &child );
				}
			
			}
		break;

	
		default:
			//result = sAIDocument->GetDocumentMaxArtboardBounds( &artboardBounds );
			result = sAIArt->GetArtBounds( art, &artBounds );
			artCenter.h = artBounds.left + (artBounds.right-artBounds.left) / 2;
			artCenter.v = artBounds.bottom + (artBounds.top-artBounds.bottom) / 2;
		
			// move object to center
			sAIRealMath->AIRealMatrixSetTranslate( &artMatrix, -artCenter.h, -artCenter.v );
			// translate object
			sAIRealMath->AIRealMatrixConcatTranslate( &artMatrix, tx, ty );
			// rotate object
			sAIRealMath->AIRealMatrixConcatRotate( &artMatrix, theta );
			// scale object
			sAIRealMath->AIRealMatrixConcatScale( &artMatrix, sx, sy );
			// move the object back to the center
			sAIRealMath->AIRealMatrixConcatTranslate( &artMatrix, artCenter.h, artCenter.v );
		
			result = sAITransformArt->TransformArt( art, &artMatrix, lineScale, transformFlags );
		break;
	}
	return result;
}