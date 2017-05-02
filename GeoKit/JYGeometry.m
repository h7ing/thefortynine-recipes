//
//  JYGeometry.m
//
//  Created by h7ing on Nov/13/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#include <math.h>
#import "JYGeometry.h"

JYGeoZoomLevel JYGeoZoomLevelForMapView(MKMapView *mapView)
{
    JYGeoZoomLevel level = 1;
    
    if (mapView)
    {
        // (256 * pow(2, l)) / (256 * pow(2, 20)) = mapView.width / visibleMapWidth
        double zoomScale = mapView.visibleMapRect.size.width / mapView.bounds.size.width;
        double zoomExponent = log2(zoomScale);
        level = kJYGeoZoomLevelMaxInTheory - (int)zoomExponent;
    }
    
    return level;
}

JYGeoHash JYGeoHashForGrip(JYGeoIndex row, JYGeoIndex col, JYGeoZoomLevel zoomLevel)
{
    JYGeoHash zoomLevelHash = (JYGeoHash)zoomLevel << 40;
    JYGeoHash rowHash = (JYGeoHash)row << 20;
    JYGeoHash colHash = (JYGeoHash)col;
    
    return zoomLevelHash | rowHash | colHash;
}

JYGeoHash JYGeoHashForCoordinate(CLLocationCoordinate2D coordinate, JYGeoZoomLevel zoomLevel)
{
    return JYGeoHashForMapPoint(MKMapPointForCoordinate(coordinate), zoomLevel);
}

JYGeoHash JYGeoHashForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel)
{
    // col = pointX / tileWidth
    // tileWidth = worldMapWidth / numOfTiles, numOfTiles = 2^zoomLevel
    
    // ldexp(x,n) = x * (2 ^ n)
    JYGeoIndex row = ldexp(mapPoint.y / MKMapSizeWorld.height, zoomLevel);
    JYGeoIndex col = ldexp(mapPoint.x / MKMapSizeWorld.width, zoomLevel);
    
    return JYGeoHashForGrip(row, col, zoomLevel);
}

JYGeoIndex JYGeoRowForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel)
{
    return ldexp(mapPoint.y / MKMapSizeWorld.height, zoomLevel);
}

JYGeoIndex JYGeoColumnForMapPoint(MKMapPoint mapPoint, JYGeoZoomLevel zoomLevel)
{
    return ldexp(mapPoint.x / MKMapSizeWorld.width, zoomLevel);
}

NSNumber *JYGeoNumberFromHash(JYGeoHash hash)
{
    //return [NSString stringWithFormat:@"%u", hash];
    return [NSNumber numberWithUnsignedLongLong:hash];
}

MKMapPoint JYMidMapPointForTile(JYGeoHash hash)
{
    JYGeoIndex row = (hash >> 20) & 0xFFFFFFFF;
    JYGeoIndex col = hash & 0xFFFFFFFF;
    JYGeoZoomLevel zoomLevel = (hash >> 40) & 0xFF;
    
    // x = (col + 0.5) * worldMapSize / numOfTiles, numOfTiles = 2^zoomLevel
    double x = ldexp((col + 0.5) * MKMapSizeWorld.width, -zoomLevel);
    double y = ldexp((row + 0.5) * MKMapSizeWorld.height, -zoomLevel);
    
    return MKMapPointMake(x, y);
}
