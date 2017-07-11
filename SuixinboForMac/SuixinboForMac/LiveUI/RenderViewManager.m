//
//  RenderViewManager.m
//  LiveDemoForMac
//
//  Created by wilderliao on 2017/5/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "RenderViewManager.h"

@interface RenderViewManager ()

@property (strong) NSMutableArray *upVideoMembers;

@end
@implementation RenderViewManager

+ (instancetype)shareInstance
{
    static RenderViewManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[RenderViewManager alloc] init];
        instance.count = 0;
        instance.upVideoMembers = [NSMutableArray array];
    });
    return instance;
}

- (NSRect)getRenderViewRect
{
    CGFloat x = 25;
    CGFloat bigViewH = 480;
    if (_count == 0)
    {
        return NSMakeRect(x, 270, 640, bigViewH);
    }
    
    CGFloat margin = 10;
    NSInteger maxRow = 4;//最多显示4行
    CGFloat smallH = (bigViewH - margin * 5)/4;
    CGFloat smallW = smallH * 4/3;
    NSInteger col = (_count-1)/maxRow;//第几列(从右到左)
    CGFloat smallX = 640+x - (smallW + margin) * (col+1);
    CGFloat y = 750 - (margin + smallH) * (_count % maxRow);
    return NSMakeRect(smallX, y, smallW, smallH);
}

//打开相机事件
- (ILiveRenderViewForMac *)addCameraRenderView:(NSString *)identifier{
    [_upVideoMembers addObject:identifier];
    ILiveFrameDispatcher *frameDispatcher = [[ILiveRoomManager getInstance] getFrameDispatcher];
    NSRect renderRect = [self getRenderViewRect];
    ILiveRenderViewForMac *view = [frameDispatcher addRenderAt:renderRect forIdentifier:identifier srcType:QAVVIDEO_SRC_TYPE_CAMERA];
    _count++;
    return view;
}

//关闭相机事件
- (void)removeCameraRenderView:(NSString *)identifier{
    [_upVideoMembers removeObject:identifier];
    ILiveFrameDispatcher *frameDispatcher = [[ILiveRoomManager getInstance] getFrameDispatcher];
    ILiveRenderViewForMac *view = [frameDispatcher getRenderView:identifier srcType:QAVVIDEO_SRC_TYPE_CAMERA];
    [view removeFromSuperview];
    _count--;
}

//打开屏幕分享事件
- (ILiveRenderViewForMac *)addScreenRenderView:(NSString *)identifier{
    [_upVideoMembers addObject:identifier];
    NSRect renderRect = [self getRenderViewRect];
    ILiveFrameDispatcher *frameDispatcher = [[ILiveRoomManager getInstance] getFrameDispatcher];
    ILiveRenderViewForMac *view = [frameDispatcher addRenderAt:renderRect forIdentifier:identifier srcType:QAVVIDEO_SRC_TYPE_SCREEN];
    _count++;
    return view;
}

//关闭屏幕分享事件
- (void)removeScreenRenderView:(NSString *)identifier{
    [_upVideoMembers removeObject:identifier];
    ILiveFrameDispatcher *frameDispatcher = [[ILiveRoomManager getInstance] getFrameDispatcher];
    ILiveRenderViewForMac *view = [frameDispatcher getRenderView:identifier srcType:QAVVIDEO_SRC_TYPE_SCREEN];
    [view removeFromSuperview];
    _count--;
}

- (BOOL)isUpVideo:(NSString *)identifier {
    BOOL isUp = NO;
    for (NSString *temp in _upVideoMembers) {
        if ([temp isEqualToString:identifier]) {
            isUp = YES;
            break;
        }
    }
    return isUp;
}
- (void)releaseManager
{
    [_upVideoMembers removeAllObjects];
    _count = 0;
    ILiveFrameDispatcher *frameDispatcher = [[ILiveRoomManager getInstance] getFrameDispatcher];
    NSArray *renderViews = [frameDispatcher removeAllRenderViews];
    for (ILiveRenderViewForMac *view in renderViews)
    {
        [view removeFromSuperview];
    }
}
@end
