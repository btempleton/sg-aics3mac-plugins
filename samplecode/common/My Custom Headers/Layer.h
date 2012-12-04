//
//  Layer.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface Layer : NSObject {
	//properties dictionary consists of three keys, each with a BOOL value: editable, visible, preview
	NSMutableDictionary* properties;
}


- (id)init;
- (id)initWithLayerNamed:(NSString*)layerName;
- (void) dealloc;

//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (NSMutableDictionary*) properties;
- (void) setProperties: (NSMutableDictionary *) theDictionary;

- (BOOL) editable;
- (void) setEditable: (BOOL)boolean;
- (BOOL) visible;
- (void) setVisible: (BOOL)boolean;
- (BOOL) preview;
- (void) setPreview: (BOOL)boolean;



//**************************************************************
//*********** Convenience Methods ******************************
//**************************************************************
+ (Layer*) layerWithLayerNamed:(NSString*)layerName;



@end
