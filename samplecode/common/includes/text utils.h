//========================================================================================
//  
//  $File: //ai/ai13/devtech/sdk/public/samplecode/common/includes/text utils.h $
//
//  $Revision: #2 $
//
//  Copyright 1987-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

extern AIErr WriteText( FILE *fp, AIArtHandle theText );
extern AIErr ReadText( FILE *fp, AIStreamHandle stream  );

extern AIErr closeAndPositionText( AIArtHandle label, AIStreamHandle stream );
extern AIErr openDefaultText( AIArtHandle *label, AIStreamHandle *stream );