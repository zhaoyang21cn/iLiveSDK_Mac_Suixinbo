//
//  AppDelegate.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "AppDelegate.h"
#import "LiveWindowController.h"

#import <QAVSDK/QAVAppChannel.h>

@interface AppDelegate ()<QAVLogger>

@end

@implementation AppDelegate

+ (instancetype)sharedInstance{
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    //0 正式环境， 1 测试环境(外部用户不要使用)
//    [[[ILiveSDK getInstance] getTIMManager] setEnv:1];
    
    //禁用控制台日志打印
//    [self disableLogPrint];
    
    //init sdk
    [[ILiveSDK getInstance] setChannelMode:E_ChannelIMSDK withHost:@""];
    
    [[ILiveSDK getInstance] initSdk:SuixinboSdkAppId accountType:SuixinboAccountType];
    
    _mainWC = [[MainWindowController alloc] initWithWindowNibName:@"MainWindowController"];
    [_mainWC.window makeKeyAndOrderFront:nil];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (void)disableLogPrint
{
    TIMManager *manager = [[ILiveSDK getInstance] getTIMManager];
    [manager initLogSettings:NO logPath:[manager getLogPath]];
    [[ILiveSDK getInstance] setConsoleLogPrint:NO];
    [QAVAppChannelMgr setExternalLogger:self];
}

#pragma mark - avsdk日志代理
- (BOOL)isLogPrint
{
    return NO;
}

- (NSString *)getLogPath
{
    return [[TIMManager sharedInstance] getLogPath];
}
@end
