//
//  SuixinboAlert.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/7.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SuixinboAlert : NSObject

+ (void)tipsWith:(NSString *)msg;

+ (void)tipsWith:(NSString *)msg showTo:(NSWindow *)window;

+ (void)alertWith:(NSString *)title msg:(NSString *)msg funBtns:(NSArray *)btns showTo:(NSWindow *)window completeHanler:(void (^ __nullable)(NSModalResponse returnCode))handler;
@end
