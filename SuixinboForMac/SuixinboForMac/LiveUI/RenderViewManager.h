//
//  RenderViewManager.h
//  LiveDemoForMac
//
//  Created by wilderliao on 2017/5/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 渲染视图管理器(获取渲染frame，记录上麦id等)
 */
@interface RenderViewManager : NSObject

+ (instancetype)shareInstance;

@property (assign) NSInteger count;

- (NSRect)getRenderViewRect;

- (ILiveRenderViewForMac *)addCameraRenderView:(NSString *)identifier;
- (void)removeCameraRenderView:(NSString *)identifier;
- (ILiveRenderViewForMac *)addScreenRenderView:(NSString *)identifier;
- (void)removeScreenRenderView:(NSString *)identifier;

//判断一个用户是否上麦
- (BOOL)isUpVideo:(NSString *)identifier;

- (void)releaseManager;
@end
