//
//  IMSdkComm.h
//  ImSDK
//
//  Created by bodeng on 10/12/14.
//  Copyright (c) 2014 tencent. All rights reserved.
//

#ifndef ImSDK_IMSdkComm_h
#define ImSDK_IMSdkComm_h

@interface OMErrResp : NSObject
{
    NSString*   cmd;                // 返回的命令字
    int         seq;                // 请求包的seq
    NSString*   uin;                // uin
    int         errCode;          // 错误码
    NSString*   errTips;            // error tips
}

@property(nonatomic,retain) NSString* cmd;
@property(nonatomic,retain) NSString* uin;
@property(nonatomic,assign) int seq;
@property(nonatomic,assign) int errCode;
@property(nonatomic,retain) NSString* errTips;

@end


/// 业务相关回调

/**
 *  userid和tinyid 转换回包
 *  userList 存储IMUserId结构
 */
@interface OMUserIdResp : NSObject{
    NSArray*   userList;         // 用户的登录的open id
}


@property(nonatomic,retain) NSArray* userList;

@end

/**
 *  userid转换tinyid回调
 *
 *  @param resp 回包结构
 *
 *  @return 0 处理成功
 */
typedef int (^OMUserIdSucc)(OMUserIdResp *resp);

//请求回调
typedef int (^OMErr)(OMErrResp *resp);


/**
 *  音视频回调
 */
@interface OMCommandResp : NSObject{
    NSData*   rspbody;
}


@property(nonatomic,retain) NSData* rspbody;

@end

// relay 回调
typedef int (^OMCommandSucc)(OMCommandResp *resp);

// request 回调
typedef void (^OMRequestSucc)(NSData * data);
typedef void (^OMRequsetFail)(int code, NSString* msg);

/**
 *  UserId 结构，表示一个用户的账号信息
 */
@interface IMUserId : NSObject{
    NSString*       uidtype;            // uid 类型
    unsigned int    userappid;
    NSString*       userid;             // 用户id
    unsigned long long   tinyid;
    unsigned long long   uin;
}

@property(nonatomic,retain) NSString* uidtype;
@property(nonatomic,assign) unsigned int userappid;
@property(nonatomic,retain) NSString* userid;
@property(nonatomic,assign) unsigned long long tinyid;
@property(nonatomic,assign) unsigned long long uin;

@end

/**
 *  一般多人音视频操作成功回调
 */
typedef void (^OMMultiSucc)();

/**
 *  一般多人音视频操作失败回调
 *
 *  @param code     错误码
 *  @param err      错误描述
 */
typedef void (^OMMultiFail)(int code, NSString * err);

/**
 *  OMAVRoomInfo 结构，表示一个隐式频房间的信息
 */
@interface OMAVRoomInfo : NSObject {
    UInt32 relationId;
    UInt32 roomId;
}
@property(nonatomic,assign) UInt32 relationId;
@property(nonatomic,assign) UInt32 roomId;
@end

typedef NS_ENUM(NSInteger, AVEncodeType)
{
    AV_ENCODE_HLS = 0x01,
//    AV_ENCODE_FLV = 0x02,
    AV_ENCODE_RAW = 0x04,
    AV_ENCODE_RTMP = 0x05,
    AV_ENCODE_HLS_AND_RTMP = 0x06,
};

typedef NS_ENUM(NSInteger, AVRateType) {
    /**
     *  未知码率
     */
    AV_RATE_TYPE_UNKNOWN        = 0x00,
    /**
     *  原始码率
     */
    AV_RATE_TYPE_ORIGINAL       = 0x01,
    /**
     *  标清码率550K
     */
    AV_RATE_TYPE_550            = (0x01 << 1),
    /**
     *  高清码率900K
     */
    AV_RATE_TYPE_900            = (0x01 << 2),
};

/**
 *  AVLiveUrl 数组，表示一个编码类型的url信息
 */
@interface AVLiveUrl : NSObject {
    AVEncodeType type;
    NSString *playUrl;
    AVRateType rateType;
}
@property(nonatomic,assign) AVEncodeType type;
@property(nonatomic,strong) NSString *playUrl;
@property(nonatomic,assign) AVRateType rateType;
@end

typedef NS_ENUM(NSInteger, AVSDKType)
{
    AVSDK_TYPE_NORMAL = 0x01,           //普通开发SDK业务
    AVSDK_TYPE_IOTCamera = 0x02,        //普通物联网摄像头SDK业务
    AVSDK_TYPE_COASTCamera = 0x03,      //滨海摄像头SDK业务
};

/**
 *  旁路直播频道信息（只对直播控制台配置成频道模式有效）
 *  channelName        (必选)直播频道的名称
 *  channelDescribe    (可选)直播频道的描述
 *  playerPassword     (可选)为接收方播放器设置的密码
 */
@interface LVBChannelInfo : NSObject {
    NSString *channelName;
    NSString *channelDescribe;
//    NSString *playerPassword;
}
@property(nonatomic,strong) NSString *channelName;
@property(nonatomic,strong) NSString *channelDescribe;
//@property(nonatomic,strong) NSString *playerPassword;
@end

/**
 *  创建旁路直播频道的结果信息
 *  channelID   创建频道的ID
 *  urls        AVLiveUrl列表
 *  recordTaskId    录制任务id
 */
@interface AVStreamerResp : NSObject {
    UInt64 channelID;
    NSArray *urls;
    uint32_t recordTaskId;
}
@property(nonatomic,assign) UInt64 channelID;
@property(nonatomic,strong) NSArray *urls;
@property(nonatomic,assign) uint32_t recordTaskId;
@end

/**
 *  推流请求成功回调
 *
 *  @param rsp 开始推流请求的返回结果
 */
typedef void (^OMMultiVideoStreamerStartSucc)(AVStreamerResp * rsp);

typedef NS_ENUM(NSInteger, AVRecordFileType) {
    AV_RECORD_FILE_TYPE_NONE        = 0x0,
    AV_RECORD_FILE_TYPE_HLS         = 0x1,
    AV_RECORD_FILE_TYPE_FLV         = 0x2,
    AV_RECORD_FILE_TYPE_HLS_FLV     = 0x3,
    AV_RECORD_FILE_TYPE_MP4         = 0x4,
    AV_RECORD_FILE_TYPE_HLS_MP4     = 0x5,
    AV_RECORD_FILE_TYPE_FLV_MP4     = 0x6,
    AV_RECORD_FILE_TYPE_HLS_FLV_MP4 = 0x7,
};

/**
 *  推流请求参数结构
 *  encodeType  编码格式
 *  avSdkType  SDK业务类型
 *  channelInfo  频道信息
 *  enableRecord  是否同时开启录制
 *  enableWatermark  是否开启水印，默认不带水印
 *  watermarkId  水印id：0默认水印，其他水印id需要通过控制台去获取
 *  rateFlags    支持的码率AVRateType（支持多码率观看，默认原始码率）
 */
@interface AVStreamInfo : NSObject {
    AVEncodeType encodeType;
//    AVSDKType avSdkType;
    LVBChannelInfo *channelInfo;
//    BOOL enableRecord;
//    BOOL enableWatermark;
//    uint32_t watermarkId;
//    AVRateType rateFlags;
    AVRecordFileType recrodFileType;
}
@property(nonatomic,assign) AVEncodeType encodeType;
//@property(nonatomic,assign) AVSDKType avSdkType;
@property(nonatomic,strong) LVBChannelInfo *channelInfo;
//@property(nonatomic,assign) BOOL enableRecord;
//@property(nonatomic,assign) BOOL enableWatermark;
//@property(nonatomic,assign) uint32_t watermarkId;
//@property(nonatomic,assign) AVRateType rateFlags;
@property(nonatomic,assign) AVRecordFileType recrodFileType;
@end

typedef NS_ENUM(NSInteger, AVRecordType) {
    /**
     *  录制视频
     */
    AV_RECORD_TYPE_VIDEO    = 0,
    /**
     *  录制纯音频
     */
    AV_RECORD_TYPE_AUDIO    = 1,
};

/**
 *  录制请求参数结构
 *  fileName  录制生成的文件名,如果包含空格则需要
 *            使用rawurlencode,长度在40个字符以内
 *  tags  视频标签的NSString*列表
 *  classId  视频分类ID
 *  avSdkType   SDK对应的业务类型
 *  isTransCode  是否转码
 *  isScreenShot  是否截图
 *  isWaterMark  是否打水印
 */
@interface AVRecordInfo : NSObject {
    NSString *fileName;
    NSArray *tags;
    UInt32 classId;
    AVSDKType avSdkType;
    BOOL isTransCode;
    BOOL isScreenShot;
    BOOL isWaterMark;
    AVRecordType recordType;
}
@property(nonatomic,strong) NSString *fileName;
@property(nonatomic,strong) NSArray *tags;
@property(nonatomic,assign) UInt32 classId;
@property(nonatomic,assign) AVSDKType avSdkType;
@property(nonatomic,assign) BOOL isTransCode;
@property(nonatomic,assign) BOOL isScreenShot;
@property(nonatomic,assign) BOOL isWaterMark;
@property(nonatomic,assign) AVRecordType recordType;
@end

/**
 *  停止录制请求成功回调
 *
 *  @param fileIds 文件ID NSString列表
 */
typedef void (^OMMultiVideoRecorderStopSucc)(NSArray * fileIds);

#endif
