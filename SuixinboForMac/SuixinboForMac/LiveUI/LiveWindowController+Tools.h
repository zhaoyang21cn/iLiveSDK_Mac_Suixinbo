//
//  LiveWindowController+Tools.h
//  LiveDemoForMac
//
//  Created by wilderliao on 2017/5/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 本扩张封装一些工具接口，将来有可能会封装到sdk中
 */
@interface LiveWindowController (Tools)

- (void)upCameraVideo:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail;
- (void)downCameraVideo:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail;

- (void)sendCustomC2CMessage:(BOOL)isOnline recvId:(NSString *)recvId cmd:(ILVLiveIMCmd)cmd succ:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail;
//recvid表示群里面 哪个用户需要响应这条消息
- (void)sendCustomGroupMessage:(BOOL)isOnline recvId:(NSString *)recvId cmd:(ILVLiveIMCmd)cmd succ:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail;
@end
