//
//  AppDelegate.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "AppDelegate.h"
#import "LiveWindowController.h"

//禁用控制台日志_1
#import <QAVSDK/QAVAppChannel.h>

//禁用控制台日志_2
@interface AppDelegate ()<QAVLogger>

@end

@implementation AppDelegate

+ (instancetype)sharedInstance{
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    //0 正式环境， 1 测试环境
//    [[[ILiveSDK getInstance] getTIMManager] setEnv:1];
    
    //init sdk
    //禁用控制台日志_3
    [self disableLogPrint];
    [[ILiveSDK getInstance] initSdk:SuixinboSdkAppId accountType:SuixinboAccountType];
    
    
    _mainWC = [[MainWindowController alloc] initWithWindowNibName:@"MainWindowController"];
    [_mainWC.window makeKeyAndOrderFront:nil];
//    [_mainWC.window center];
//    [_mainWC.window orderFront:nil];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

//禁用控制台日志_4
- (void)disableLogPrint
{
    TIMManager *manager = [[ILiveSDK getInstance] getTIMManager];
    [manager initLogSettings:NO logPath:[manager getLogPath]];
    [[ILiveSDK getInstance] setConsoleLogPrint:NO];
    [QAVAppChannelMgr setExternalLogger:self];
}

#pragma mark - avsdk日志代理
//禁用控制台日志_5
- (BOOL)isLogPrint
{
    return NO;
}

//禁用控制台日志_6
- (NSString *)getLogPath
{
    return [[TIMManager sharedInstance] getLogPath];
}
@end
