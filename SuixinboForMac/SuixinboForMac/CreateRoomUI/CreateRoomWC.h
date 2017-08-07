//
//  CreateRoomWC.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/19.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ClickCoverImageView.h"
#import "LiveWindowController.h"

@interface LiveRommConfig : NSObject

@property (nonatomic, assign) BOOL isAutoOpenMic;
@property (nonatomic, assign) BOOL isAutoOpenSpeaker;
@property (nonatomic, strong) NSString *cameraDesc;
@property (nonatomic, strong) NSString *roleDesc;

@end

@protocol CreateRoomDelegate <NSObject>

- (void)createRoom:(TCShowLiveListItem *)item config:(LiveRommConfig *)config;

@end
/**
 创建直播时，配置直播间参数
 */

@interface CreateRoomWC : NSWindowController

@property (strong) IBOutlet NSView *bgView;

@property (strong) IBOutlet NSTextField *liveTitleTF;
@property (strong) IBOutlet ClickCoverImageView *liveCoverImageView;
@property (strong) IBOutlet NSPopUpButton *cameraPpoUpBtn;
@property (strong) IBOutlet NSPopUpButton *micPopUpBtn;
@property (strong) IBOutlet NSPopUpButton *rolePopUpBtn;

@property (strong) id<CreateRoomDelegate> delegate;

@property (strong) LiveWindowController *liveWC;

- (IBAction)onCancel:(id)sender;

@end
