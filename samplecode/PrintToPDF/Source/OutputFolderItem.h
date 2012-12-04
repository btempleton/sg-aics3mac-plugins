//
//  OutputFolderItem.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface OutputFolderItem : NSObject <NSCoding> {
	OutputFolderItem *parent;
	NSMutableArray *children;
	
	NSString *nodeName;
	NSString *folderPath;
	BOOL validPath;
	BOOL isRoot;
}


+ (OutputFolderItem *)rootItem;
- (int)numberOfChildren;			// Returns -1 for leaf nodes
- (OutputFolderItem *)childAtIndex:(int)n;	// Invalid to call on leaf nodes



//**************************************************************
//*********** Getters and Setters ******************************
//**************************************************************
- (OutputFolderItem *) parent;
- (void) setParent: (OutputFolderItem *) newParent;

- (NSMutableArray*) children;
- (void) setChildren: (NSMutableArray *) newChildren;
- (void) addChild: (OutputFolderItem *) newChild;

- (NSString*) nodeName;
- (void) setNodeName: (NSString *) theString;

- (NSString*) folderPath;
- (void) setFolderPath: (NSString *) theString;
- (void) changeFolderPath;

- (BOOL) validPath;
- (void) setValidPath:(BOOL) boolean;

- (BOOL) isRoot;
- (void) setIsRoot:(BOOL) boolean;

//**************************************************************
//*********** Convenience init and set *************************
//**************************************************************
- (OutputFolderItem *) initWithParent: (OutputFolderItem *) theParent
							 Children: (NSMutableArray *) childrenSet
							 NodeName: (NSString *) theName
						   FolderPath: (NSString *) thePath
							   IsRoot: (BOOL) bIsRoot;


+ (OutputFolderItem *) createBlankItem;


//**************************************************************
//*********** NSCoding methods         *************************
//**************************************************************
- (void) encodeWithCoder:(NSCoder *)coder;
- (id) initWithCoder:(NSCoder *)coder;

@end
