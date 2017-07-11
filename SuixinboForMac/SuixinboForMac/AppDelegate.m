//
//  AppDelegate.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "AppDelegate.h"
#import "LiveWindowController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

+ (instancetype)sharedInstance{
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    //init sdk
    [[ILiveSDK getInstance] initSdk:SuixinboSdkAppId accountType:SuixinboAccountType];
    
    NSString *ver = [QAVContext getVersion];
    NSLog(@"ver = %@",ver);
    
    
    _mainWC = [[MainWindowController alloc] initWithWindowNibName:@"MainWindowController"];
    [_mainWC.window makeKeyAndOrderFront:nil];
//    [_mainWC.window center];
//    [_mainWC.window orderFront:nil];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
