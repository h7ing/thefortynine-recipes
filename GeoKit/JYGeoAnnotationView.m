//
//  JYGeoAnnotationView.m
//
//  Created by h7ing on Nov/30/2012.
//  Copyright (c) 2012 h7ing. All rights reserved.
//

#import "JYGeoAnnotationView.h"

@implementation JYGeoAnnotationView

@synthesize loadingIndicatorVisible = loadingIndicatorVisible_;

- (void)dealloc
{
    [indicatorView_ release]; indicatorView_ = nil;
    [super dealloc];
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    indicatorView_.center = CGPointMake(CGRectGetMidX(self.bounds), CGRectGetMidY(self.bounds));
}

- (void)setLoadingIndicatorVisible:(BOOL)loadingIndicatorVisible
{
    loadingIndicatorVisible_ = loadingIndicatorVisible;
    
    if (loadingIndicatorVisible_)
    {
        if (!indicatorView_)
        {
            indicatorView_ = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
            indicatorView_.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0.4];
            indicatorView_.contentMode = UIViewContentModeCenter;
            [self addSubview:indicatorView_];
        }
        indicatorView_.hidden = NO;
        [indicatorView_ startAnimating];
        [self bringSubviewToFront:indicatorView_];
    }
    else
    {
        if (indicatorView_ && !indicatorView_.hidden)
        {
            [indicatorView_ stopAnimating];
            indicatorView_.hidden = YES;
        }
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
//    [[self.annotation title]
//     drawInRect:CGRectMake(self.bounds.size.width - 27, 0, 54, 54)
//     withFont:[UIFont systemFontOfSize:12.0]];
}
 */

@end
