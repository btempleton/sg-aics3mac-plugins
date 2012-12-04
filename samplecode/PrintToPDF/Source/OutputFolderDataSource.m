//
//  OutputFolderDataSource.m
//  PrintToPDF
//
//  Created by Comp Mac 8a on 6/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "OutputFolderDataSource.h"
#import "OutputFolderItem.h"


@implementation OutputFolderDataSource

// Data Source methods

- (int)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    return (item == nil) ? 1 : [item numberOfChildren];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    return (item == nil) ? YES : ([item numberOfChildren] != -1);
}

- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item {
    return (item == nil) ? [OutputFolderItem rootItem] : [(OutputFolderItem *)item childAtIndex:index];
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
	if (![[tableColumn identifier] compare:@"name"]) {
		return [item nodeName];
	} else if (![[tableColumn identifier] compare:@"path"]) {
		return [item folderPath];
	} else if (![[tableColumn identifier] compare:@"valid"]) {
		return @"p";
	}
}

// Delegate methods

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldEditTableColumn:(NSTableColumn *)tableColumn item:(id)item {
    return NO;
}




@end
