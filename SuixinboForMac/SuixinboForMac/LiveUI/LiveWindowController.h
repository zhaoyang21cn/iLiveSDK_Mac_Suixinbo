//
//  LiveWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/19.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <TILFilterSDK/TILFilter.h>
#import "RoomInfoWindowController.h"
#import "PushParamWindowController.h"
#import "ScreenShareWindowController.h"

@class LiveRommConfig;
/**
 直播控制器（本类内容比较多，分成多个模块，每个模块对应相应的扩展类，要查看哪个模块，可以直接去看对应的扩展类）
 */
@interface LiveWindowController : NSWindowController<NSTextFieldDelegate,QAVRemoteVideoDelegate,ILiveRoomDisconnectListener,ILiveFirstFrameListener>

//右侧方向UI
@property (strong) IBOutlet NSTableView *memberTableView;//成员列表
@property (strong) IBOutlet NSTextView *messageTextView; //消息列表
@property (strong) IBOutlet NSTextField *messageTF;      //消息输入框
@property (strong) IBOutlet NSButton *messageSendBtn;    //消息发送按钮(回车键也可以发送)

@property (strong) NSMutableArray *members;//成员列表
@property (assign) NSInteger messageCount;//接收到的消息数

//底部UI
@property (strong) IBOutlet NSButton *openCameraBtn;     //相机
@property (strong) IBOutlet NSComboBox *cameraComboBox;

@property (strong) IBOutlet NSSlider *micSlider;         //麦克风
@property (strong) IBOutlet NSButton *openMicBtn;

@property (strong) IBOutlet NSButton *openSpeakerBtn;    //扬声器

@property (strong) IBOutlet NSSlider *beautySlider;      //美颜
@property (strong) IBOutlet NSTextField *beautyValueTF;
@property (strong) IBOutlet NSSlider *whiteSlider;       //美白
@property (strong) IBOutlet NSTextField *whiteValueTF;

@property (strong) IBOutlet NSButton *startPushBtn;//推流
@property (strong) PushParamWindowController *pushParamWC;

@property (strong) IBOutlet NSButton *startRecordBtn;//录制

@property (strong) IBOutlet NSButton *screenShareBtn;//屏幕分享
@property (strong) ScreenShareWindowController *screenShareWC;


@property (strong) IBOutlet NSPopUpButton *roleSwitchPopUpBtn;
@property (strong) IBOutlet NSButton *roleSwitchBtn;      //切换角色（切换分辨率）

//Log
@property (strong) IBOutlet NSTextView *logTextView;

@property (strong) RoomInfoWindowController *roomInfoWC;//显示房间信息窗口


@property (assign) BOOL isHost;//自己是不是主播
@property (assign) RoomOptionType roomOptionType;//create or join
@property (strong) TCShowLiveListItem *item;//房间信息
@property (strong) LiveRommConfig *config;//进房间前的一些配置项

@property (assign) int volume;      //麦克风音量

@property (nonatomic, strong) TILFilter *tilFilter;//美颜对象

@property (assign) UInt64 channelId;//频道id，推流和停止推流的过程中，需要记录

@property (nonatomic, strong) NSTimer *heartTimer;//直播心跳计时器，房间保活

- (IBAction)onExitLive:(NSButton *)sender;//退出直播（外部也有调用，所以放到头文件中）

- (void)insertMessageToUI:(NSString *)message;//插入一条消息到UI
- (void)addLog:(NSString *)logStr;//添加一条Log

- (void)setHostUI;//主播UI
- (void)setUpVideoUI;//上麦者UI
- (void)setGuestUI;//观众UI
@end
