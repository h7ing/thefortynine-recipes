//
//  TA3DRotationViewController.m
//  TransformAnimations
//
//  Created by h7ing on Mar/11/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TA3DRotationViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface TA3DRotationViewController ()

@end

@implementation TA3DRotationViewController

+ (NSString *)description
{
    return @"3DRotation";
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
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
    CATransform3D persp = CATransform3DIdentity;
    persp.m34 = -1.0 / 100.0;
    CATransform3D trans3d = CATransform3DMakeRotation((60.0/180.0)*M_PI, 0, 1, 0);
    trans3d = CATransform3DConcat(trans3d, persp);
    
    CABasicAnimation *transformAnimation = [CABasicAnimation animationWithKeyPath:@"transform"];
	transformAnimation.fromValue = [NSValue valueWithCATransform3D:CATransform3DIdentity];
	transformAnimation.toValue = [NSValue valueWithCATransform3D:trans3d];
	transformAnimation.duration = 1.5;
	transformAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    [_debugView.layer addAnimation:transformAnimation forKey:nil];
    
    _debugView.layer.transform = trans3d;
}

@end
