//
//  LiveWindowController+Beauty.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"

/**
 美颜需要设置监听QAVLocalVideoDelegate，按照本类的写法来，除了本扩展类中的内容，在主类中还有个TILFilter对象，一起完成美颜美白功能
 */
@interface LiveWindowController (Beauty)<QAVLocalVideoDelegate>

@end
