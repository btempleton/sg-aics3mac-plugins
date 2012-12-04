//
//  resultImageTransformer.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 2/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "resultImageTransformer.h"


@implementation resultImageTransformer

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
	NSString* _resultValue = (NSString *)value;
	if (value != nil) {
		if(![@"OK!" caseInsensitiveCompare:_resultValue]){
			NSImage* im = [[[NSImage alloc] initWithContentsOfFile:[[NSBundle bundleForClass:[self class]] pathForResource:@"check" ofType:@"png"]] autorelease];
			return im;
		} else if (![@"ERR" caseInsensitiveCompare:_resultValue]){
			NSImage* im = [[[NSImage alloc] initWithContentsOfFile:[[NSBundle bundleForClass:[self class]] pathForResource:@"error" ofType:@"png"]] autorelease];
			return im;
		} else {
			return nil;
		}
	} else {
		return nil;
	}
}



@end
