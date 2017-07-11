//
//  MainView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ClickSelfHeadImageView.h"
#import "LiveWindowController.h"
#import "CreateRoomWC.h"
#import "RecordListView.h"

@protocol MainViewDelegate <NSObject>

- (void)logoutComplete:(NSString *)module code:(int)code msg:(NSString *)msg;

@end

/**
 主视图 （包括直播列表视图，录制列表视图）
 */
@interface MainView : NSView<CreateRoomDelegate>

@property (strong) IBOutlet NSView *headBgView; //顶部背景视图
@property (strong) IBOutlet ClickSelfHeadImageView *userHeadImageView;//展示当前登录用户头像
@property (strong) IBOutlet NSTextField *curLoginUserTF;//展示当前登录用户名

@property (strong) IBOutlet NSTableView *liveListTableView;//直播列表
@property (strong) RecordListView *recordListView;

@property (strong) NSMutableArray *datas;

@property (strong) LiveWindowController *liveWC;
@property (strong) CreateRoomWC *createRoomWC;

@property (weak) id<MainViewDelegate>   delegate;

- (void)show;
- (void)hide;

- (BOOL)isInRoom;
@end
