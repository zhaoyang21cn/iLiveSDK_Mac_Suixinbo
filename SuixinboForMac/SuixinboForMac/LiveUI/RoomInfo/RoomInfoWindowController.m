//
//  RoomInfoWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "RoomInfoWindowController.h"

@interface RoomInfoWindowController ()

@end

@implementation RoomInfoWindowController

- (void)awakeFromNib {
    _resolutionDic = [NSMutableDictionary dictionary];
}

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    [self onLogTimer];
    
    _logTimer = [NSTimer timerWithTimeInterval:1 target:self selector:@selector(onLogTimer) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:_logTimer forMode:NSDefaultRunLoopMode];
}

- (void)onLogTimer
{
    __weak typeof(self) ws = self;
    QAVContext *context = [[ILiveSDK getInstance] getAVContext];
    NSDictionary *dic = [context.room GetQualityParam];
    if (context.videoCtrl && context.audioCtrl && context.room)
    {
        ILiveQualityData *qualityData = [[ILiveRoomManager getInstance] getQualityData];
        NSMutableString *paramString = [NSMutableString string];
        //FPS
        [paramString appendString:[NSString stringWithFormat:@"FPS:%ld.\n",qualityData.interactiveSceneFPS/10]];
        //Send Recv
        [paramString appendString:[NSString stringWithFormat:@"Send: %ldkbps, Recv: %ldkbps.\n",qualityData.sendRate,(long)qualityData.recvRate]];
        //sendLossRate recvLossRate
        CGFloat sendLossRate = (CGFloat)qualityData.sendLossRate / (CGFloat)100;
        CGFloat recvLossRate = (CGFloat)qualityData.recvLossRate / (CGFloat)100;
        NSString *per = @"%";
        [paramString appendString:[NSString stringWithFormat:@"SendLossRate: %.2f%@,   RecvLossRate: %.2f%@.\n",sendLossRate,per,recvLossRate,per]];
        
        //appcpu syscpu
        CGFloat appCpuRate = (CGFloat)qualityData.appCPURate / (CGFloat)100;
        CGFloat sysCpuRate = (CGFloat)qualityData.sysCPURate / (CGFloat)100;
        [paramString appendString:[NSString stringWithFormat:@"AppCPURate:   %.2f%@,   SysCPURate:   %.2f%@.\n",appCpuRate,per,sysCpuRate,per]];
        
        //分别角色的分辨率
        NSArray *keys = [_resolutionDic allKeys];
        for (NSString *key in keys)
        {
            QAVFrameDesc *desc = _resolutionDic[key];
            [paramString appendString:[NSString stringWithFormat:@"%@---> %d * %d\n",key,desc.width,desc.height]];
        }
        //avsdk版本号
        NSString *avSDKVer = [NSString stringWithFormat:@"AVSDK版本号: %@\n",[QAVContext getVersion]];
        [paramString appendString:avSDKVer];
        //房间号
        int roomid = [[ILiveRoomManager getInstance] getRoomId];
        [paramString appendString:[NSString stringWithFormat:@"房间号:%d\n",roomid]];
        //角色
        NSString *roleStr = _isHost ? @"主播" : @"非主播";
        [paramString appendString:[NSString stringWithFormat:@"角色:%@\n",roleStr]];
        
        //采集信息
        NSString *videoParam = [context.videoCtrl getQualityTips];
        NSArray *array = [videoParam componentsSeparatedByString:@"\n"]; //从字符A中分隔成2个元素的数组
        if (array.count > 3)
        {
            NSString *resolution = [array objectAtIndex:2];
            [paramString appendString:[NSString stringWithFormat:@"%@\n",resolution]];
        }
        //麦克风
        NSString *isOpen = [[ILiveRoomManager getInstance] getCurMicState] ? @"ON" : @"OFF";
        [paramString appendString:[NSString stringWithFormat:@"麦克风: %@\n",isOpen]];
        //扬声器
        NSString *isOpenSpeaker = [[ILiveRoomManager getInstance] getCurSpeakerState] ? @"ON" : @"OFF";
        [paramString appendString:[NSString stringWithFormat:@"扬声器: %@\n",isOpenSpeaker]];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            ws.roomInfoTextView.string = paramString;
        });
    }
}

@end
