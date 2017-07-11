//
//  MainWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "MainWindowController.h"

@interface MainWindowController ()

@end

@implementation MainWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    [self initUI];
    _loginView.delegate = self;
    _mainView.delegate = self;
}


- (void)windowWillClose:(NSNotification *)notification {
    NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
    if (loginId && loginId.length > 0) {
        [[ILiveLoginManager getInstance] iLiveLogout:^{
            [NSApp terminate:nil];
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            [NSApp terminate:nil];
        }];
    }
    else{
        [NSApp terminate:nil];
    }
}

- (void)initUI {
    //登录视图
    NSArray *loginViewObjects = [[NSArray alloc] init];
    if ([[NSBundle mainBundle] loadNibNamed:@"LoginView" owner:nil topLevelObjects:&loginViewObjects])
    {
        for (id item in loginViewObjects) {
            if ([item isKindOfClass:[LoginView class]]) {
                _loginView = item;
            }
        }
        [self.window.contentView addSubview:_loginView];
        [_loginView show];
    }
    //主界面视图
    NSArray *mainViewObjects = [[NSArray alloc] init];
    if ([[NSBundle mainBundle] loadNibNamed:@"MainView" owner:nil topLevelObjects:&mainViewObjects])
    {
        for (id item in mainViewObjects) {
            if ([item isKindOfClass:[MainView class]]) {
                _mainView = item;
            }
        }
        [self.window.contentView addSubview:_mainView];
        [_mainView hide];
    }
}

#pragma mark - loginView delegate
- (void)loginComplete:(NSString *)module code:(int)code msg:(NSString *)msg {
    if (code == 0) {
        [_loginView hide];
        [_mainView show];
        [[ILiveSDK getInstance] setUserStatusListener:self];
    }
}

#pragma mark - mainView delegate
- (void)logoutComplete:(NSString *)module code:(int)code msg:(NSString *)msg {
    if (code == 0) {
        [_loginView show];
        [_mainView hide];
        [[ILiveSDK getInstance] setUserStatusListener:nil];
    }
}

#pragma mark - UserStatusListener delegate
- (void)onForceOffline {
    int roomId = [[ILiveRoomManager getInstance] getRoomId];
    if (roomId > 0) {//在直播
        [_mainView.liveWC onExitLive:nil];
    }
    _mainView.hidden = YES;
    _loginView.hidden = NO;
    [SuixinboAlert tipsWith:@"你的账号在其它设备登录，请重新登录" showTo:self.window];
}
- (void)onReConnFailed:(int)code err:(NSString*)err {
}
- (void)onUserSigExpired {
}

@end

