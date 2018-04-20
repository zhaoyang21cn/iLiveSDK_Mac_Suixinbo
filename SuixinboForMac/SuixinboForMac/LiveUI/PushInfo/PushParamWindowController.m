//
//  PushParamWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/7/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "PushParamWindowController.h"

@interface PushParamWindowController ()

@end

@implementation PushParamWindowController

- (void)awakeFromNib {
    NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
    
    NSString *channelName = [NSString stringWithFormat:@"Mac_随心播推流_%@",loginId];
    _channelNameTF.stringValue = channelName;
    
    NSString *channelDesc = [NSString stringWithFormat:@"Mac_随心播推流描述文本"];
    _channelDescTF.stringValue = channelDesc;
    
    [_encodeTypeComBox addItemWithObjectValue:@"HLS编码"];
    [_encodeTypeComBox addItemWithObjectValue:@"RTMP编码"];
    [_encodeTypeComBox selectItemAtIndex:0];//默认选中0
    
    [_recordFileTypeComBox addItemWithObjectValue:@"不自动录制"];
    [_recordFileTypeComBox addItemWithObjectValue:@"HLS"];
    [_recordFileTypeComBox addItemWithObjectValue:@"FLV"];
    [_recordFileTypeComBox addItemWithObjectValue:@"HSL & FLV"];
    [_recordFileTypeComBox addItemWithObjectValue:@"MP4"];
    [_recordFileTypeComBox addItemWithObjectValue:@"HLS & MP4"];
    [_recordFileTypeComBox addItemWithObjectValue:@"FLV & MP4"];
    [_recordFileTypeComBox addItemWithObjectValue:@"HLS & FLV & MP4"];
    [_recordFileTypeComBox addItemWithObjectValue:@"MP3(纯音频文件)"];
    [_recordFileTypeComBox selectItemAtIndex:4];//默认选中mp4
}

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}
- (IBAction)onCancel:(NSButton *)sender {
    if (self.cancelPush) {
        [self cancelPush];
    }
    [self.window close];
}

- (IBAction)onConfirm:(NSButton *)sender {
    
    if (self.startPush) {
        ILiveChannelInfo *info = [[ILiveChannelInfo alloc] init];
        info.channelName = _channelNameTF.stringValue;
        info.channelDesc = _channelNameTF.stringValue;

        ILivePushOption *option = [[ILivePushOption alloc] init];
        option.channelInfo = info;
        option.encodeType = [self getEncodeType:_encodeTypeComBox.indexOfSelectedItem];
        option.recrodFileType = [self getRecordFileType:_recordFileTypeComBox.indexOfSelectedItem];
        option.isAudioPush = _audioRecordCheckBox.state;
        self.startPush(option);
    }
    [self.window close];
}

- (IBAction)onAudioCheckBox:(NSButton *)sender {
}

- (ILiveEncodeType)getEncodeType:(NSInteger)index {
    if (index == 0) {
        return ILive_ENCODE_HLS;
    }
    else {
        return ILive_ENCODE_RTMP;
    }
}

- (ILiveRecordFileType)getRecordFileType:(NSInteger)index {
    switch (index) {
        case 0:
            return ILive_RECORD_FILE_TYPE_NONE;
        case 1:
            return ILive_RECORD_FILE_TYPE_HLS;
        case 2:
            return ILive_RECORD_FILE_TYPE_FLV;
        case 3:
            return ILive_RECORD_FILE_TYPE_HLS_FLV;
        case 4:
            return ILive_RECORD_FILE_TYPE_MP4;
        case 5:
            return ILive_RECORD_FILE_TYPE_HLS_MP4;
        case 6:
            return ILive_RECORD_FILE_TYPE_FLV_MP4;
        case 7:
            return ILive_RECORD_FILE_TYPE_HLS_FLV_MP4;
        case 8:
            return ILive_RECORD_MP3;
        default:
            break;
    }
    return ILive_RECORD_FILE_TYPE_NONE;
}

@end
