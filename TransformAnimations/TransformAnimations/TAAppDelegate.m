//
//  TAAppDelegate.m
//  TransformAnimations
//
//  Created by h7ing on Mar/5/2013.
//  Copyright (c) 2013 h7ing. All rights reserved.
//

#import "TAAppDelegate.h"
#import "TAMainViewController.h"

@implementation TAAppDelegate

@synthesize window = _window;

- (void)dealloc
{
    [_window release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    TAMainViewController *mainController = [[[TAMainViewController alloc] initWithStyle:UITableViewStylePlain] autorelease];
    UINavigationController *navController = [[[UINavigationController alloc] initWithRootViewController:mainController] autorelease];
    self.window.rootViewController = navController;
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
}

@end
