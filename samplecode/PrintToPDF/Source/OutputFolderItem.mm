//
//  OutputFolderItem.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "OutputFolderItem.h"
#import "Dialog.h"

extern Dialog* theDialog;

@implementation OutputFolderItem

//*************************************************
// -init
// initializes a OutputFolderItem object
//*************************************************
-(id)init
{
	if (self = [super init]) {
		parent = nil;
		children = [[NSMutableArray alloc] initWithCapacity:1];
		nodeName = @"";
		folderPath = @"";
		validPath = NO;
		isRoot = NO;
	}
	return self;
}

//*************************************************
// -initWithParent:Children:NodeName:FolderPath:ValidPath
// initializes a PlateItem object with specific info
//*************************************************
- (OutputFolderItem *) initWithParent: (OutputFolderItem *) theParent
							 Children: (NSMutableArray *) childrenArray
							 NodeName: (NSString *) theName
						   FolderPath: (NSString *) thePath
							   IsRoot: (BOOL) bIsRoot
{
	if (self = [super init]) {
		[self setParent:theParent];
		[self setChildren:childrenArray];
		[self setNodeName:theName];
		[self setFolderPath:thePath];
		[self setIsRoot:bIsRoot];
		
		if (bIsRoot && ![thePath length]) {
			[self setValidPath:YES];
		}
	}
	return self;
}

//*************************************************
// -createBlankItem
// Adds a specified PlateItem to the plate list
//*************************************************
+ (OutputFolderItem*)createBlankItem
{
	return [[[OutputFolderItem alloc] init] autorelease];
}
		 

//*************************************************
// -dealloc
// destructor
//*************************************************
-(void)dealloc
{
	[children release];
	[super dealloc];
}


//****************************************************************************************************
// ************************** Getters/Setters *************************************************
//****************************************************************************************************
- (OutputFolderItem*)parent
{
	return parent;
}

- (void)setParent:(OutputFolderItem*)newParent
{
	if (newParent == parent) {
		return;
	}
	
	[newParent retain];
	[parent release];
	parent = newParent;
}

- (NSMutableArray*)children
{
	return children;
}

- (void)setChildren:(NSMutableArray*)newChildren
{
	if (newChildren == children) {
		return;
	}
	
	[newChildren retain];
	[children release];
	children = newChildren;
}

- (NSString*)nodeName
{
	return nodeName;
}

- (void)setNodeName:(NSString*)theString
{
	if (theString == nodeName) {
		return;
	}
	
	[theString retain];
	[nodeName release];
	nodeName = theString;
}

- (NSString*)folderPath
{
	return folderPath;
}

- (void)setFolderPath:(NSString*)theString
{
	if (theString == folderPath) {
		return;
	}
	
	[theString retain];
	[folderPath release];
	folderPath = theString;
	
	//Check the path for validity, and set validPath
	NSFileManager* MyFileManager = [[NSFileManager alloc] init];
	if ([MyFileManager fileExistsAtPath:folderPath])
	{
		validPath = YES;
	} else { 
		if (![folderPath length]) {
			validPath = YES;
		} else {
			validPath = NO;
			//Set the parent too, so we see a trail to the bad one in our tree
			[parent setValidPath:NO];
		}
	}
	[MyFileManager release];
}

- (void)changeFolderPath
{
	// Create the File Open Dialog class.
	NSOpenPanel* openDlg = [NSOpenPanel openPanel];
	
	// Enable the selection of directories in the dialog.
	[openDlg setCanChooseDirectories:YES];
	
	//Disable multiple selection
	[openDlg setAllowsMultipleSelection:NO];
	
	// Display the dialog.  If the OK button was pressed,
	// process the files.
	if ( [openDlg runModalForDirectory:[theDialog outputPathString] file:nil] == NSOKButton )
	{
		[self setFolderPath:[openDlg filename]];
	}
}


- (BOOL) validPath
{
	return validPath;
}

- (void) setValidPath:(BOOL)boolean
{
	if (boolean == validPath) {
		return;
	}
	validPath = boolean;
	if (!validPath) {
		//Set the parent too, so we see a trail to the bad one in the tree
		[parent setValidPath:NO];
	}
}

- (BOOL) isRoot
{
	return isRoot;
}

- (void) setIsRoot:(BOOL)boolean
{
	if (boolean == isRoot) {
		return;
	}
	isRoot = boolean;
}


//*************************************************
// -addChild:
// Adds a child object to this node
//*************************************************
-(void)addChild: (OutputFolderItem *) newChild;
{
	if (children) {
		[children addObject:newChild];
	} else {
		children = [NSMutableArray arrayWithObject:newChild];
	}
	
}

#pragma mark NSCoding methods
//*************************************************
// -encodeWithCoder:coder
// Encodes our outputFolderItem
//*************************************************
- (void) encodeWithCoder:(NSCoder *)coder
{
	[coder encodeConditionalObject:parent forKey:@"parent"];
	[coder encodeObject:children forKey:@"children"];
	[coder encodeObject:nodeName forKey:@"nodeName"];
	[coder encodeObject:folderPath forKey:@"folderPath"];
	[coder encodeBool:isRoot forKey:@"isRoot"];
}

//*************************************************
// -initWithCoder:coder
// Un-encodes our outputFolderItem
//*************************************************
- (id) initWithCoder:(NSCoder *)coder
{
	if (self = [super init]) {
		[self setParent:[coder decodeObjectForKey:@"parent"]];
		[self setChildren:[coder decodeObjectForKey:@"children"]];
		[self setNodeName:[coder decodeObjectForKey:@"nodeName"]];
		[self setFolderPath:[coder decodeObjectForKey:@"folderPath"]];
		[self setIsRoot:[coder decodeBoolForKey:@"isRoot"]];
	}
	return self;	
}





OutputFolderItem *rootItem = nil;

#define IsALeafNode ((id)-1)


+ (OutputFolderItem *)rootItem {
	if (rootItem == nil) rootItem = [[OutputFolderItem alloc] init];
	return rootItem;       
}



- (OutputFolderItem *)childAtIndex:(int)n {
    return [[self children] objectAtIndex:n];
}

- (int)numberOfChildren {
    id tmp = [self children];
    return (tmp == IsALeafNode) ? (-1) : [tmp count];
}



@end
