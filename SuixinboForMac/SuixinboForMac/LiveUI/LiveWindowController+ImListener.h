//
//  LiveWindowController+ImListener.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 添加IM消息监听（app中的各种指令，都是由自定义消息完成，比如邀请上麦AVIMCMD_Multi_Host_Invite等，如果用户需要自定义指令，也可以用自定义消息实现）
 文本消息也是在本类中监听
 */
@interface LiveWindowController (ImListener)<TIMMessageListener>

@end
