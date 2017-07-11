//
//  LiveWindowController+Audio.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/4.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+Audio.h"

@implementation LiveWindowController (Audio)

- (QAVResult)audioDataComes:(QAVAudioFrame *)audioFrame type:(QAVAudioDataSourceType)type {
    return QAV_OK;
}

- (QAVResult)audioDataShouInput:(QAVAudioFrame *)audioFrame type:(QAVAudioDataSourceType)type {
    return QAV_OK;
}

- (QAVResult)audioDataDispose:(QAVAudioFrame *)audioFrame type:(QAVAudioDataSourceType)type {
    if (type == QAVAudioDataSource_VoiceDispose) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [[[ILiveSDK getInstance] getAVContext].audioCtrl SetAudioDataDBVolume:type volume:self.volume];
        });
    }
    return QAV_OK;
}
@end
