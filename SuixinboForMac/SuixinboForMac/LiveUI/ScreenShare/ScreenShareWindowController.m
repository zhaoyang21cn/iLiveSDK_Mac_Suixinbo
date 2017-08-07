//
//  ScreenShareWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "ScreenShareWindowController.h"

@interface ScreenShareWindowController ()

@end

@implementation ScreenShareWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    _logTF.stringValue = @"";
}

- (IBAction)onStopScreenShare:(NSButton *)sender {
    __weak typeof(self) ws = self;
    [[ILiveRoomManager getInstance] enableScreenShare:NO succ:^{
        [ws.window close];
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        NSString *log = [NSString stringWithFormat:@"enable screen fail.module=%@,code=%d,msg=%@",module,errId,errMsg];
        ws.logTF.stringValue = log;
    }];
}
- (IBAction)onStartScreenShare:(NSButton *)sender {
    CGFloat x = _shareRectX.floatValue;
    CGFloat y = _shareRectY.floatValue;
    CGFloat w = _shareRectW.floatValue;
    CGFloat h = _shareRectH.floatValue;
    NSRect rect = NSMakeRect(x, y, w, h);
    
    __weak typeof(self) ws = self;
    if ([[ILiveRoomManager getInstance] getCurScreenState])//如果正在屏幕分享，仅设置区域就可以了
    {
        [[ILiveRoomManager getInstance] setScreenShareRect:rect];
        [ws.window close];
    }
    else
    {
        [[ILiveRoomManager getInstance] enableScreenShare:YES succ:^{
            [[ILiveRoomManager getInstance] setScreenShareRect:rect];
            [ws.window close];
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            NSString *log = [NSString stringWithFormat:@"enable screen fail.module=%@,code=%d,msg=%@",module,errId,errMsg];
            ws.logTF.stringValue = log;
        }];
    }
}

- (IBAction)onFullScreenFrame:(NSButton *)sender {
    NSRect rect = [NSScreen mainScreen].frame;
    _shareRectX.floatValue = rect.origin.x;
    _shareRectY.floatValue = rect.origin.y;
    _shareRectW.floatValue = rect.size.width;
    _shareRectH.floatValue = rect.size.height;
}

@end
