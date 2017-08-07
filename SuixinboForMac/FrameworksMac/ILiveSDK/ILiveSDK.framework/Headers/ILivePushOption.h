//
//  ILivePushOption.h
//  ILiveSDK
//
//  Created by AlexiChen on 2016/10/24.
//  Copyright © 2016年 AlexiChen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ImSDK/IMSdkComm.h>

@class ILiveChannelInfo;

typedef NS_ENUM(NSInteger, ILiveRecordFileType) {
    ILive_RECORD_FILE_TYPE_NONE        = 0x0,
    ILive_RECORD_FILE_TYPE_HLS         = 0x1,
    ILive_RECORD_FILE_TYPE_FLV         = 0x2,
    ILive_RECORD_FILE_TYPE_HLS_FLV     = 0x3,
    ILive_RECORD_FILE_TYPE_MP4         = 0x4,
    ILive_RECORD_FILE_TYPE_HLS_MP4     = 0x5,
    ILive_RECORD_FILE_TYPE_FLV_MP4     = 0x6,
    ILive_RECORD_FILE_TYPE_HLS_FLV_MP4 = 0x7,
    ILive_RECORD_MP3                   = 0x10,//录制mp3
};

typedef NS_ENUM(NSInteger, ILiveEncodeType)
{
    ILive_ENCODE_HLS = 0x01,
    //    AV_ENCODE_FLV = 0x02,
    ILive_ENCODE_RAW = 0x04,
    ILive_ENCODE_RTMP = 0x05,
    ILive_ENCODE_HLS_AND_RTMP = 0x06,
};

@interface ILivePushOption : NSObject

/** 旁路直播频道信息 */
@property (nonatomic, strong) ILiveChannelInfo *channelInfo;

/** 是否纯音频推流，YES：纯音频推流，NO：音视频推流 默认NO */
@property (nonatomic, assign) BOOL isAudioPush;

/** 编码格式 */
@property(nonatomic, assign) ILiveEncodeType   encodeType;

/** 录制文件类型（ILive_RECORD_FILE_TYPE_NONE则不开启录制） */
@property(nonatomic,assign) ILiveRecordFileType recrodFileType;

@end



@interface ILiveChannelInfo : NSObject

/** (必选)直播频道的名称 */
@property(nonatomic, copy)   NSString  *channelName;

/** (可选)直播频道的描述 */
@property(nonatomic, copy)   NSString  *channelDesc;

@end
