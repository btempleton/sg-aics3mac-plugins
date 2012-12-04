//
//  NSStringAdditions.h
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface NSString (AIUnicodeString)
+ (NSString*) withAIUnicodeString:(ai::UnicodeString)layerName;
@end