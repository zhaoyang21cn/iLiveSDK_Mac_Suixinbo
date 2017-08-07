//
//  PushParamWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

typedef void(^StartPushBlock)(ILivePushOption *option);//开始推流
typedef void(^CancelPushBlock)();//取消

@interface PushParamWindowController : NSWindowController

@property (strong) IBOutlet NSTextField *channelNameTF;
@property (strong) IBOutlet NSTextField *channelDescTF;
@property (strong) IBOutlet NSComboBox *encodeTypeComBox;
@property (strong) IBOutlet NSComboBox *recordFileTypeComBox;
@property (strong) IBOutlet NSButton *audioRecordCheckBox;

@property (nonatomic, copy) StartPushBlock  startPush;
@property (nonatomic, copy) CancelPushBlock cancelPush;
@end
