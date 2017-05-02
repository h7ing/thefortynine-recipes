//
//  TAShearViewController.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TAShearViewController.h"
#import <CoreGraphics/CoreGraphics.h>
#import "CGAffineTransform+Extra.h"

@interface TAShearViewController ()

@end

@implementation TAShearViewController

+ (NSString *)description
{
    return @"Shear";
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onStartButtonTouchUpInside:(id)sender
{
    [UIView animateWithDuration:1.0 animations:^{
        CGFloat angle = 30.0 / 180.0 * M_PI;
        
        _debugView.transform = TAAffineTransformMakeShearHorizontal(angle);
        //_debugView.transform = TAAffineTransformMakeShearVertical(angle);
    }];
}

@end
