//
//  TATemplateViewController.h
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TATemplateViewController : UIViewController
{
@protected
    NSMutableArray *_buttons;
    UIView *_debugView;
}

- (void)onStartButtonTouchUpInside:(id)sender;
- (void)onRevertButtonTouchUpInside:(id)sender;

@end
