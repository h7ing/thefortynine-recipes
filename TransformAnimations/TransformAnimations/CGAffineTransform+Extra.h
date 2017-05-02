//
//  CGAffineTransform+Extra.h
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#include <math.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

// Return a transform which rotates around the given point(center) through the angle(radian)
extern CGAffineTransform TAAffineTransformMakeRotation(CGPoint center, CGFloat angle);

// Return a mirror transform
extern CGAffineTransform TAAffineTransformMakeMirrorInHorizontal();

extern CGAffineTransform TAAffineTransformMakeMirrorInVertical();


// A simple description about shear trasformation:
// http://www.cs.colorado.edu/~mcbryan/5229.03/mail/55.htm

// Return a shear transfrom in x axis, angle(radian)
extern CGAffineTransform TAAffineTransformMakeShearHorizontal(CGFloat angle);

// Return a shear transfrom in y axis, angle(radian)
extern CGAffineTransform TAAffineTransformMakeShearVertical(CGFloat angle);
