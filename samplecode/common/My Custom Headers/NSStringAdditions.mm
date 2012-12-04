//
//  NSStringAdditions.mm
//  PrintToPDF
//
//  Created by Comp Mac 8a on 5/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NSStringAdditions.h"
#include "string.h"


@implementation NSString (AIUnicodeString)

+ (NSString*) withAIUnicodeString:(ai::UnicodeString)layerName
{	
	return [[[NSString alloc] initWithUTF8String:layerName.as_UTF8().c_str()] autorelease];
}

@end