//
//  JYGeoAnnotation.h
//
//  Created by h7ing on Nov/29/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface JYGeoAnnotation : NSObject<MKAnnotation>

@property (nonatomic, assign) int elementCount;
@property (nonatomic, assign) BOOL canBePoster;

- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate;

@end
