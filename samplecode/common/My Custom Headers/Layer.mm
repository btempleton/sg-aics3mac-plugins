//
//  Layer.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Layer.h"
#import "CException.h"

#include "common.h"

@implementation Layer


- (id) init
{
	if (self = [super init]) {
		[self setProperties:[NSMutableDictionary dictionaryWithObjectsAndKeys:@"editable",NO, @"visible", NO, @"preview", NO]];
	}
	return self;
}

- (id) initWithLayerNamed:(NSString*)layerName
{
	if (self = [super init]) {
		//Get the properties for the layer named layerName
		ai::UnicodeString usLayerName = ai::UnicodeString((CFStringRef)layerName);
		AILayerHandle layer = NULL; sAILayer->GetLayerByTitle(&layer, usLayerName);
		AIBoolean re; sAILayer->GetLayerEditable(layer, &re);
		AIBoolean rv; sAILayer->GetLayerVisible(layer, &rv);
		AIBoolean rp; sAILayer->GetLayerPreview(layer, &rp);
		
		[self setProperties:[NSMutableDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:(int)re], @"editable", 
																			  [NSNumber numberWithBool:(int)rv], @"visible",
																			  [NSNumber numberWithBool:(int)rp], @"preview", nil]];
	}
	return self;
}


- (void) dealloc
{
	[properties release];
	[super dealloc];
}



//****************************************************************************************************
// ************************** Getters/Setters *************************************************
//****************************************************************************************************
- (NSMutableDictionary*)properties
{
	return properties;
}

- (void)setProperties:(NSMutableDictionary*)theDictionary
{
	if (theDictionary == properties) {
		return;
	}
	
	[theDictionary retain];
	[properties release];
	properties = theDictionary;
}

- (BOOL) editable
{
	return [[properties valueForKey:@"editable"] boolValue];
}
- (void) setEditable: (BOOL)boolean
{
	[properties setValue:[NSNumber numberWithBool:boolean] forKey:@"editable"];
}

- (BOOL) visible
{
	return [[properties valueForKey:@"visible"] boolValue];
}
- (void) setVisible: (BOOL)boolean
{
	[properties setValue:[NSNumber numberWithBool:boolean] forKey:@"visible"];
}

- (BOOL) preview
{
	return [[properties valueForKey:@"preview"] boolValue];
}
- (void) setPreview: (BOOL)boolean
{
	[properties setValue:[NSNumber numberWithBool:boolean] forKey:@"preview"];
}



//****************************************************************************************************
// ************************** Convenience Methods *************************************************
//****************************************************************************************************
+ (Layer*) layerWithLayerNamed:(NSString*)layerName
{
	return [[[Layer alloc] initWithLayerNamed:layerName] autorelease];
}

@end
