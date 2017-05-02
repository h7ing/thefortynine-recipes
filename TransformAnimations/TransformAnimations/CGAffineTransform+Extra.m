//
//  CGAffineTransform+Extra.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "CGAffineTransform+Extra.h"

// Rot(Q, theta) = Trans(-wq) * Rot(theta) * Trans(wq)
CGAffineTransform TAAffineTransformMakeRotation(CGPoint center, CGFloat angle)
{
    CGAffineTransform translate = CGAffineTransformMakeTranslation(center.x, center.y);
    CGAffineTransform rotation = CGAffineTransformMakeRotation(angle);
    
    return CGAffineTransformConcat(CGAffineTransformConcat(CGAffineTransformInvert(translate), rotation), translate);
}

CGAffineTransform TAAffineTransformMakeMirrorInHorizontal()
{
    return CGAffineTransformMakeScale(1.0, -1.0);
}

CGAffineTransform TAAffineTransformMakeMirrorInVertical()
{
    return CGAffineTransformMakeScale(-1.0, 1.0);
}

CGAffineTransform TAAffineTransformMakeShearHorizontal(CGFloat angle)
{
    return CGAffineTransformMake(1.0, 0, tanf(angle), 1.0, 0, 0);
}

CGAffineTransform TAAffineTransformMakeShearVertical(CGFloat angle)
{
    return CGAffineTransformMake(1.0, tanf(angle), 0, 1.0, 0, 0);
}
