//
//  LiveWindowController+AVListener.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+AVListener.h"
#import "RenderViewManager.h"

@implementation LiveWindowController (AVListener)

#pragma mark - ILiveMemStatusListener
- (BOOL)onEndpointsUpdateInfo:(QAVUpdateEvent)event updateList:(NSArray *)endpoints{
    if (endpoints.count <= 0) {
        return NO;
    }
    switch (event) {
        case QAV_EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO:
            [self upCameraVideo:endpoints];
            break;
        case QAV_EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO:
            [self downCameraVideo:endpoints];
            break;
        case QAV_EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO:
            [self upScreenVideo:endpoints];
            break;
        case QAV_EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO:
            [self downScreenVideo:endpoints];
            break;
            
        default:
            break;
    }
    return YES;
}

//打开相机事件
- (void)upCameraVideo:(NSArray *)endpoints{
    for (QAVEndpoint *endpoint in endpoints) {
        NSString *identifier = endpoint.identifier;
        ILiveRenderViewForMac *view = [[RenderViewManager shareInstance] addCameraRenderView:identifier];
        if (view.frame.size.width >= 640) {//大画面，置于底层
            [self.window.contentView addSubview:view positioned:NSWindowBelow relativeTo:nil];
        }
        else {
            [self.window.contentView addSubview:view];
        }
    }
}

//关闭相机事件
- (void)downCameraVideo:(NSArray *)endpoints{
    for (QAVEndpoint *endpoint in endpoints) {
        NSString *identifier = endpoint.identifier;
        [[RenderViewManager shareInstance] removeCameraRenderView:identifier];
    }
}

//打开屏幕分享事件
- (void)upScreenVideo:(NSArray *)endpoints{
    for (QAVEndpoint *endpoint in endpoints) {
        NSString *identifier = endpoint.identifier;
        ILiveRenderViewForMac *view = [[RenderViewManager shareInstance] addScreenRenderView:identifier];
        [self.window.contentView addSubview:view];
    }
}

//关闭屏幕分享事件
- (void)downScreenVideo:(NSArray *)endpoints{
    for (QAVEndpoint *endpoint in endpoints) {
        NSString *identifier = endpoint.identifier;
        [[RenderViewManager shareInstance] removeScreenRenderView:identifier];
    }
}


@end
