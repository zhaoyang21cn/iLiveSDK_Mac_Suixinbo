//
//  MainWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ClickSelfHeadImageView.h"
#import "LiveWindowController.h"
#import "CreateRoomWC.h"
#import "LoginView.h"
#import "MainView.h"

/**
 主界面控制器，控制各个视图的显示与隐藏，切换等（包括登录视图和主视图）
 */
@interface MainWindowController : NSWindowController<LoginViewDelegate,MainViewDelegate,TIMUserStatusListener>

@property (strong) LoginView *loginView;
@property (strong) MainView *mainView;

@end

