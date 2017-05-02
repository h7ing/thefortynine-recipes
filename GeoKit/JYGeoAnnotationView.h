//
//  JYGeoAnnotationView.h
//
//  Created by h7ing on Nov/30/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import <MapKit/MapKit.h>

@interface JYGeoAnnotationView : MKAnnotationView
{
@protected
    UIActivityIndicatorView *indicatorView_;
}

@property (nonatomic, assign) BOOL loadingIndicatorVisible;

@end
