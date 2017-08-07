//
//  ScreenShareWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ScreenShareWindowController : NSWindowController
@property (strong) IBOutlet NSTextField *shareRectX;
@property (strong) IBOutlet NSTextField *shareRectY;
@property (strong) IBOutlet NSTextField *shareRectW;
@property (strong) IBOutlet NSTextField *shareRectH;

@property (strong) IBOutlet NSButton *shareBtn;

@property (strong) IBOutlet NSTextField *logTF;
@end
