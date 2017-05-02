//
//  JYGeoAnnotationDataMap.m
//
//  Created by h7ing on Nov/29/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import "JYGeoAnnotationDataMap.h"

static NSString *const kJYGeoAnnotationListKey = @"geo_annotation_list";
static NSString *const kJYGeoAnnotationPosterKey = @"geo_annotation_poster";

@implementation JYGeoAnnotationDataMap

- (void)dealloc
{
    [dataMap_ release]; dataMap_ = nil;
    [super dealloc];
}

- (id)initWithGeoAnnotations:(NSArray *)annotations
{
    self = [super init];
    if (self)
    {
        [self indexAndAddGeoAnnotations:annotations];
    }
    return self;
}

// 地理位置索引结构:
// {
//     JYGeoHashKey(NSNumber withUnsignedLongLong) :
//     {
//         AnnotationListKey(NSString) : AnnotationList(NSMutableArray)
//         PosterKey(NSString)         : PosterAnnotation(JYGeoAnnotation)
//     }
// }
- (void)indexAndAddGeoAnnotations:(NSArray *)annotations
{
    if (!dataMap_)
        dataMap_ = [[NSMutableDictionary alloc] init];
    
    if (!annotations || ![annotations count])
        return;
    
    MKMapPoint point = {0};
    JYGeoIndex row = 0;
    JYGeoIndex col = 0;
    
    NSLog(@"BEGIN generate data map");
    for (JYGeoAnnotation *value in annotations)
    {
        point = MKMapPointForCoordinate(value.coordinate);
        row = JYGeoRowForMapPoint(point, kJYGeoZoomLevelMaxDeFacto + 1);
        col = JYGeoColumnForMapPoint(point, kJYGeoZoomLevelMaxDeFacto + 1);
        
        for (int i = kJYGeoZoomLevelMaxDeFacto; i >= 1; i--)
        {
            if (row)
                row = row >> 1;
            if (col)
                col = col >> 1;
            
            JYGeoHash hash = JYGeoHashForGrip(row, col, i);
            NSNumber *geoKey = JYGeoNumberFromHash(hash);
            
            // 一个分块里的数据
            NSMutableDictionary *tileDataMap = [dataMap_ objectForKey:geoKey];
            if (!tileDataMap)
            {
                tileDataMap = [[NSMutableDictionary alloc] initWithCapacity:2];
                [dataMap_ setObject:tileDataMap forKey:geoKey];
                [tileDataMap release];
            }
            
            NSMutableArray *annotations = [tileDataMap objectForKey:kJYGeoAnnotationListKey];//[dataMap_ objectForKey:geoKey];
            if (!annotations)
            {
                annotations = [[NSMutableArray alloc] init];
                //[dataMap_ setObject:annotations forKey:geoKey];
                [tileDataMap setObject:annotations forKey:kJYGeoAnnotationListKey];
                [annotations release];
            }
            [annotations addObject:value];
            
            // set poster
            JYGeoAnnotation *poster = [tileDataMap objectForKey:kJYGeoAnnotationPosterKey];
            if (!poster || (!poster.canBePoster && value.canBePoster))
            {
                [tileDataMap setObject:value forKey:kJYGeoAnnotationPosterKey];
            }
        }
    }
    
    NSLog(@"END generate");
    NSLog(@"data map count:%d", [dataMap_ count]);
}

- (NSArray *)geoAnnotationsForGeoHash:(JYGeoHash)geoHash
{
    //return [dataMap_ objectForKey:JYGeoNumberFromHash(geoHash)];
    NSDictionary *tileDataMap = [dataMap_ objectForKey:JYGeoNumberFromHash(geoHash)];
    return [tileDataMap objectForKey:kJYGeoAnnotationListKey];
}

- (JYGeoAnnotation *)posterAnnotationForGeoHash:(JYGeoHash)geoHash
{
//    NSArray *annotations = [self geoAnnotationsForGeoHash:geoHash];
//    if (annotations && [annotations count])
//        return [annotations objectAtIndex:0];
//    
//    return nil;
    NSDictionary *tileDataMap = [dataMap_ objectForKey:JYGeoNumberFromHash(geoHash)];
    JYGeoAnnotation *poster = [tileDataMap objectForKey:kJYGeoAnnotationPosterKey];
    
    return poster;
}

@end
