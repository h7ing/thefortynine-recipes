//
//  TARotationViewController.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TARotationViewController.h"
#import <CoreGraphics/CoreGraphics.h>
#import "CGAffineTransform+Extra.h"

@interface TARotationViewController ()

@end

@implementation TARotationViewController

+ (NSString *)description
{
    return @"Rotation";
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onStartButtonTouchUpInside:(id)sender
{
    [UIView animateWithDuration:1.0 animations:^{
        _debugView.transform = TAAffineTransformMakeRotation(CGPointMake(25, 25), M_PI_2);
    }];
}

@end
