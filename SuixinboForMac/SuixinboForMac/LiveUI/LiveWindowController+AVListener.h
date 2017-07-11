//
//  LiveWindowController+AVListener.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 监听音视频事件(打开/关闭 摄像头， 打开关闭屏幕分享)，在本类中添加渲染视图
 */
@interface LiveWindowController (AVListener)<ILiveMemStatusListener>

@end
