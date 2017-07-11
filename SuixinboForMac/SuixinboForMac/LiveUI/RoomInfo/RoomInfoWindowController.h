//
//  RoomInfoWindowController.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface RoomInfoWindowController : NSWindowController

@property (nonatomic, copy) NSTimer *logTimer;
@property (strong) IBOutlet NSTextView *roomInfoTextView;
@property (strong) NSMutableDictionary *resolutionDic;
@property (nonatomic, assign) BOOL isHost;

@end
