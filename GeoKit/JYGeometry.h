//
//  JYGeometry.h
//
//  README
//  The map uses the Mercator projection.
//  http://en.wikipedia.org/wiki/Mercator_projection
//
//  The map size at zoom level l:
//      256 * pow(2, l);
//
//  So, the actual level is:
//    Start Level:
//      Level 1 : 256 * pow(2,  1) = 512;
//    Max Level(1pix on map, 1pix on mapView):
//      Level 20: 256 * pow(2, 20) = 268435456;
//
//  The map can be zoomed in up to level 17.
//  Reference:
//  http://troybrant.net/blog/2010/01/mkmapview-and-zoom-levels-a-visual-guide/
//  Addition: the map size at max level noted in the post is wrong, it's exactly
//  268435456.
//
//
//  Created by h7ing on Nov/13/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>

typedef uint64_t JYGeoHash;
typedef uint8_t JYGeoZoomLevel;
typedef uint32_t JYGeoIndex;

static const JYGeoZoomLevel kJYGeoZoomLevelMaxInTheory = 20; // 地图可缩放等级理论值
static const JYGeoZoomLevel kJYGeoZoomLevelMaxDeFacto = 17; // 地图可缩放等级实际值(GoogleMap为17,高德为18,17完全满足现有需求)

JYGeoZoomLevel JYGeoZoomLevelForMapView(MKMapView *mapView);

JYGeoIndex JYGeoRowForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel);
JYGeoIndex JYGeoColumnForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel);

JYGeoHash JYGeoHashForGrip(JYGeoIndex row, JYGeoIndex col, JYGeoZoomLevel zoomLevel);
JYGeoHash JYGeoHashForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel);
JYGeoHash JYGeoHashForCoordinate(CLLocationCoordinate2D coordinate, JYGeoZoomLevel zoomLevel);

NSNumber *JYGeoNumberFromHash(JYGeoHash hash);

MKMapPoint JYMidMapPointForTile(JYGeoHash hash);
