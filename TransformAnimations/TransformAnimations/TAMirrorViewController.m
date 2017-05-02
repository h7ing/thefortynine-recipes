//
//  TAMirrorViewController.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TAMirrorViewController.h"
#import <CoreGraphics/CoreGraphics.h>
#import "CGAffineTransform+Extra.h"

@interface TAMirrorViewController ()

@end

@implementation TAMirrorViewController

+ (NSString *)description
{
    return @"Mirror";
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
        _debugView.transform = TAAffineTransformMakeMirrorInVertical();
    }];
}

@end
