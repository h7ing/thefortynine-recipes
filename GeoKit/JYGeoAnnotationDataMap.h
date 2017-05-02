//
//  JYGeoAnnotationDataMap.h
//
//  Created by h7ing on Nov/29/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "JYGeometry.h"
#import "JYGeoAnnotation.h"

@interface JYGeoAnnotationDataMap : NSObject
{
@private
    NSMutableDictionary *dataMap_;
}

// 传入参数必须为JYGeoAnnotation类型
- (id)initWithGeoAnnotations:(NSArray *)annotations;

// 建立地图标记的索引
// 注意: 同时会索引每个区域的海报标记, 优先采用canBePoster为YES的标记
// 某些区域内的海报标记的canBePoster如果为NO, 说明该区域内没有canBePoster的点
- (void)indexAndAddGeoAnnotations:(NSArray *)annotations;

- (NSArray *)geoAnnotationsForGeoHash:(JYGeoHash)geoHash;
- (JYGeoAnnotation *)posterAnnotationForGeoHash:(JYGeoHash)geoHash;

@end
