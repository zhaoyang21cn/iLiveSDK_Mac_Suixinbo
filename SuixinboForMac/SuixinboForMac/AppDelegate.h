//
//  AppDelegate.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MainWindowController.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>

+ (instancetype)sharedInstance;

@property (nonatomic, strong) NSString *token;
@property (nonatomic, strong) MainWindowController *mainWC;

@end

