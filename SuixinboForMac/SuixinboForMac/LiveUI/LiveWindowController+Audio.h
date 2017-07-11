//
//  LiveWindowController+Audio.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/4.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 音频相关处理
 改变麦克风音量
 1、setAudioDataEventDelegate
 2、创建房间成功之后 registerAudioDataCallback
 3、audioDataDispose 回调中设置音量大小
 */
@interface LiveWindowController (Audio)<QAVAudioDataDelegate>

@end
