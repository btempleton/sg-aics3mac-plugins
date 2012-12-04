//
//  PlantComboBoxCell.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface PlantComboBoxCell : NSComboBoxCell {

}
- (NSArray *)objectValues;
- (NSString *)completedString:(NSString *)substring;
- (int)numberOfItems;


@end
