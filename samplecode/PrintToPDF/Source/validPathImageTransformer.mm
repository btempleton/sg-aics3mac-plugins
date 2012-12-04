//
//  validPathImageTransformer.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "validPathImageTransformer.h"


@implementation validPathImageTransformer

+ (Class)transformedValueClass
{
	return [NSImage class];
}

+ (BOOL)allowsReverseTransformation
{
	return NO;
}

- (NSImage*)transformedValue:(id)value
{
	BOOL _resultValue = [value boolValue];
	if (value != nil) {
		//If we have a bad path, output the error graphic
		if(!_resultValue) {
			NSImage* im = [[[NSImage alloc] initWithContentsOfFile:[[NSBundle bundleForClass:[self class]] pathForResource:@"smerror" ofType:@"png"]] autorelease];
			return im;
		} else {
			return nil;
		}
	} else {
		return nil;
	}
}

@end
