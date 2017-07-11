//
//  PlayerWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AVKit/AVKit.h>
#import <AVFoundation/AVFoundation.h>

/**
 通过URL播放录制视频
 */
@interface PlayerWindowController : NSWindowController
@property (nonatomic, strong) RecordVideoItem *item;
@property (nonatomic, strong) AVPlayerView *playerView;
@end
