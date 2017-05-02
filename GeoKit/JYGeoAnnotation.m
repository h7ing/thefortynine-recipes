//
//  JYGeoAnnotation.m
//
//  Created by h7ing on Nov/29/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import "JYGeoAnnotation.h"

@implementation JYGeoAnnotation

@synthesize elementCount = elementCount_;
@synthesize coordinate = coordinate_;
@synthesize canBePoster;

- (void)dealloc
{
    [super dealloc];
}

- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate
{
    self = [super init];
    if (self)
    {
        coordinate_ = coordinate;
    }
    
    return self;
}

- (NSString *)title
{
    return [NSString stringWithFormat:@"%d", elementCount_];
}

@end
