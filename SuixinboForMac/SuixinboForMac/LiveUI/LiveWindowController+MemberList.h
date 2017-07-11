//
//  LiveWindowController+MemberList.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 成员列表的响应事件和逻辑在本扩展类中，主要是右键点击时的逻辑
 */
@interface LiveWindowController (MemberList)<NSTabViewDelegate,NSTableViewDataSource,NSMenuDelegate>

@end
