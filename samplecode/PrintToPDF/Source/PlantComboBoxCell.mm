//
//  PlantComboBoxCell.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlantComboBoxCell.h"
#import "Dialog.h"
extern Dialog* theDialog;

@implementation PlantComboBoxCell

- (NSArray *)objectValues
{
	return [NSArray arrayWithObjects:@"Townsend", @"Salt Lake City", @"Midland", nil];
}


- (NSString *)completedString:(NSString *)substring
{
	return @"CompletedString";
}

- (int)numberOfItems
{
	//[self addItemsWithObjectValues:[NSArray arrayWithObjects:@"Townsend", @"Salt Lake City", @"Midland", nil]];
	//return 3;
}


- (void)comboBoxWillPopUp:(NSNotification *)notification
{
	return;
}
@end
