//
//  TATemplateViewController.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TATemplateViewController.h"

@interface TATemplateViewController ()

@end

@implementation TATemplateViewController

- (void)dealloc
{
    [_buttons release];
    [_debugView release];
    [super dealloc];
}

- (UIButton *)createButtonAtPosition:(CGPoint)center withTitle:(NSString *)title target:(id)target selector:(SEL)selector
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button setTitle:title forState:UIControlStateNormal];
    [button sizeToFit];
    button.center = center;
    [button addTarget:target action:selector forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (void)loadButtons
{
    if (_buttons)
        return;
    
    _buttons = [[NSMutableArray alloc] init];
    
    UIButton *startButton = [self createButtonAtPosition:CGPointMake(100.0, self.view.bounds.size.height - 100.0) withTitle:@"start" target:self selector:@selector(onStartButtonTouchUpInside:)];
    [self.view addSubview:startButton];
    [_buttons addObject:startButton];
    
    UIButton *revertButton = [self createButtonAtPosition:CGPointMake(200.0, self.view.bounds.size.height - 100.0) withTitle:@"revert" target:self selector:@selector(onRevertButtonTouchUpInside:)];
    [self.view addSubview:revertButton];
    [_buttons addObject:revertButton];
}

- (void)loadDebugView
{
    if (_debugView)
        return;
    
    _debugView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100.0, 50.0)];
    _debugView.center = CGPointMake(CGRectGetMidX(self.view.bounds), 150.0);
    _debugView.backgroundColor = [UIColor greenColor];
    
    [self.view addSubview:_debugView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    [self loadButtons];
    [self loadDebugView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onStartButtonTouchUpInside:(id)sender
{
    
}

- (void)onRevertButtonTouchUpInside:(id)sender
{
    [UIView animateWithDuration:1.0 animations:^{
        _debugView.transform = CGAffineTransformIdentity;
    }];
}

@end
