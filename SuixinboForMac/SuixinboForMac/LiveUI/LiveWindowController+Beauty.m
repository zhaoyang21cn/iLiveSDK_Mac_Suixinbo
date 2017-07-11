//
//  LiveWindowController+Beauty.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+Beauty.h"

@implementation LiveWindowController (Beauty)

- (void)OnLocalVideoPreview:(QAVVideoFrame *)frameData {
    //仅仅是为了打log
    NSString *key = frameData.identifier;
    if (key.length == 0)
    {
        key = [[ILiveLoginManager getInstance] getLoginId];
    }
    QAVFrameDesc *desc = [[QAVFrameDesc alloc] init];
    desc.width = frameData.frameDesc.width;
    desc.height = frameData.frameDesc.height;
    if (desc && key) {
        [self.roomInfoWC.resolutionDic setObject:desc forKey:key];
    }
}

- (void)OnLocalVideoPreProcess:(QAVVideoFrame *)frameData
{
    TILDataType type = TILDataType_NV12;
    switch (frameData.frameDesc.color_format)
    {
        case AVCOLOR_FORMAT_I420:
            type = TILDataType_I420;
            break;
        case AVCOLOR_FORMAT_NV12:
            type = TILDataType_NV12;
            break;
        default:
            break;
    }
    [self.tilFilter processData:frameData.data inType:type outType:type size:frameData.dataSize width:frameData.frameDesc.width height:frameData.frameDesc.height];
}

- (void)OnLocalVideoRawSampleBuf:(CMSampleBufferRef)buf result:(CMSampleBufferRef *)ret {
}

@end
