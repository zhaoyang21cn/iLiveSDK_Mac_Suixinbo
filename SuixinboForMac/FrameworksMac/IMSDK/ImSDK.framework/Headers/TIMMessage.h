//
//  TIMMessage.h
//  ImSDK
//
//  Created by bodeng on 28/1/15.
//  Copyright (c) 2015 tencent. All rights reserved.
//

#ifndef ImSDK_TIMMessage_h
#define ImSDK_TIMMessage_h


#import <Foundation/Foundation.h>

#import "TIMComm.h"
#import "TIMCallback.h"
#import "TIMCodingModel.h"

@class TIMUserProfile;
@class TIMGroupMemberInfo;

/**
 *  消息会话
 */
@class TIMConversation;

/**
 *  发送消息给多用户的失败信息
 */
@interface TIMSendToUsersErrInfo : NSObject
/**
 *  发送消息失败的目标用户id
 */
@property(nonatomic,retain) NSString *identifier;
/**
 *  错误码
 */
@property(nonatomic,assign) int code;
/**
 *  错误描述
 */
@property(nonatomic,retain) NSString *err;
@end

/**
 *  发送消息给多用户的失败回调信息
 */
@interface TIMSendToUsersDetailInfo : NSObject
/**
 *  发送消息成功的目标用户数
 */
@property(nonatomic,assign) uint32_t succCnt;
/**
 *  发送消息失败的目标用户数
 */
@property(nonatomic,assign) uint32_t failCnt;
/**
 *  失败信息（TIMSendToUsersErrInfo*）列表
 */
@property(nonatomic,retain) NSArray *errInofs;
@end

/**
 *  消息Elem基类
 */
@interface TIMElem : TIMCodingModel
@end

/**
 *  文本消息Elem
 */
@interface TIMTextElem : TIMElem
/**
 *  消息文本
 */
@property(nonatomic,retain) NSString * text;
@end


/**
 *  图片压缩选项
 */
typedef NS_ENUM(NSInteger, TIM_IMAGE_COMPRESS_TYPE){
    /**
     *  原图(不压缩）
     */
    TIM_IMAGE_COMPRESS_ORIGIN              = 0x00,
    /**
     *  高压缩率：图片较小，默认值
     */
    TIM_IMAGE_COMPRESS_HIGH                = 0x01,
    /**
     *  低压缩：高清图发送(图片较大)
     */
    TIM_IMAGE_COMPRESS_LOW                 = 0x02,
};

/**
 *  图片类型
 */
typedef NS_ENUM(NSInteger, TIM_IMAGE_TYPE){
    /**
     *  原图
     */
    TIM_IMAGE_TYPE_ORIGIN              = 0x01,
    /**
     *  缩略图
     */
    TIM_IMAGE_TYPE_THUMB               = 0x02,
    /**
     *  大图
     */
    TIM_IMAGE_TYPE_LARGE               = 0x04,
};

/**
 *  图片格式
 */
typedef NS_ENUM(NSInteger, TIM_IMAGE_FORMAT){
    /**
     *  JPG格式
     */
    TIM_IMAGE_FORMAT_JPG            = 0x1,
    /**
     *  GIF格式
     */
    TIM_IMAGE_FORMAT_GIF            = 0x2,
    /**
     *  PNG格式
     */
    TIM_IMAGE_FORMAT_PNG            = 0x3,
    /**
     *  BMP格式
     */
    TIM_IMAGE_FORMAT_BMP            = 0x4,
    /**
     *  未知格式
     */
    TIM_IMAGE_FORMAT_UNKNOWN        = 0xff,
};

@interface TIMImage : NSObject
/**
 *  图片ID，内部标识，可用于外部缓存key
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  图片类型
 */
@property(nonatomic,assign) TIM_IMAGE_TYPE type;
/**
 *  图片大小
 */
@property(nonatomic,assign) int size;
/**
 *  图片宽度
 */
@property(nonatomic,assign) int width;
/**
 *  图片高度
 */
@property(nonatomic,assign) int height;
/**
 *  下载URL
 */
@property(nonatomic, retain) NSString * url;

/**
 *  获取图片
 *
 *  @param path 图片保存路径
 *  @param succ 成功回调，返回图片数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getImage:(NSString*) path succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  获取图片
 *
 *  @param path 图片保存路径
 *  @param cb 图片获取回调
 */
- (void) getImage:(NSString*) path cb:(id<TIMCallback>)cb;

@end


/**
 *  图片消息Elem
 */
@interface TIMImageElem : TIMElem

/**
 *  要发送的图片路径
 */
@property(nonatomic,retain) NSString * path;

/**
 *  所有类型图片，只读
 */
@property(nonatomic,retain) NSArray * imageList;

/**
 * 上传时任务Id，可用来查询上传进度
 */
@property(nonatomic,assign) uint32_t taskId;

/**
 *  图片压缩等级，详见 TIM_IMAGE_COMPRESS_TYPE（仅对jpg格式有效）
 */
@property(nonatomic,assign) TIM_IMAGE_COMPRESS_TYPE level;

/**
 *  图片格式，详见 TIM_IMAGE_FORMAT
 */
@property(nonatomic,assign) TIM_IMAGE_FORMAT format;


/**
 *  查询上传进度
 */
- (uint32_t) getUploadingProgress;


@property(nonatomic,retain) NSString * selfIdentifier;

@end

/**
 *  文件消息Elem
 */
@interface TIMFileElem : TIMElem
/**
 *  上传时任务Id，可用来查询上传进度
 */
@property(nonatomic,assign) uint32_t taskId;
/**
 *  上传时，文件的路径（设置path时，优先上传文件）
 */
@property(nonatomic,retain) NSString * path;
/**
 *  文件数据，发消息时设置，收到消息时不能读取，通过 getFileData 获取数据
 */
@property(nonatomic,retain) NSData * data;
/**
 *  文件内部ID
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  文件大小
 */
@property(nonatomic,assign) int fileSize;
/**
 *  文件显示名，发消息时设置
 */
@property(nonatomic,retain) NSString * filename;

/**
 *  获取文件数据到指定路径的文件中
 *
 *  @param path 文件保存路径
 *  @param succ 成功回调，返回数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getToFile:(NSString*)path succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  获取文件数据到指定路径的文件中
 *
 *  @param path 文件保存路径
 *  @param cb   语音获取回调
 */
- (void) getToFile:(NSString*)path cb:(id<TIMCallback>)cb;

/**
 *  获取文件
 *
 *  @param succ 成功回调，返回原始文件数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getFileData:(TIMGetResourceSucc)succ fail:(TIMFail)fail;

/**
 * 当前用户自己的identifier（内部使用）
 */
@property(nonatomic,retain) NSString * selfIdentifier;

/**
 *  查询上传进度
 */
- (uint32_t) getUploadingProgress;

@end

/**
 *  语音消息Elem
 */
@interface TIMSoundElem : TIMElem
/**
 *  上传时任务Id，可用来查询上传进度
 */
@property(nonatomic,assign) uint32_t taskId;
/**
 *  上传时，语音文件的路径（设置path时，优先上传语音文件），接收时使用getSoundToFile获得数据
 */
@property(nonatomic,retain) NSString * path;
/**
 *  发送时设置为语音数据，接收时使用getSoundToFile获得数据
 */
@property(nonatomic,retain) NSData * data;
/**
 *  语音消息内部ID
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  语音数据大小
 */
@property(nonatomic,assign) int dataSize;
/**
 *  语音长度（秒），发送消息时设置
 */
@property(nonatomic,assign) int second;

/**
 *  获取语音数据到指定路径的文件中
 *
 *  @param path 语音保存路径
 *  @param succ 成功回调，返回语音数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getSoundToFile:(NSString*)path succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  获取语音数据到指定路径的文件中
 *
 *  @param path 语音保存路径
 *  @param cb   语音获取回调
 */
- (void) getSoundToFile:(NSString*)path cb:(id<TIMCallback>)cb;

/**
 *  获取语音数据
 *
 *  @param succ 成功回调，返回语音数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getSound:(TIMGetResourceSucc)succ fail:(TIMFail)fail;

/**
 *  获取语音数据
 *
 *  @param cb 资源获取回调
 */
- (void) getSound:(id<TIMResourceCallback>)cb;

/**
 * 当前用户自己的identifier（内部使用）
 */
@property(nonatomic,retain) NSString * selfIdentifier;

/**
 *  查询上传进度
 */
- (uint32_t) getUploadingProgress;

@end


/**
 *  群Tips类型
 */
typedef NS_ENUM(NSInteger, TIM_GROUP_TIPS_TYPE){
    /**
     *  邀请加入群 (opUser & groupName & userList)
     */
    TIM_GROUP_TIPS_TYPE_INVITE              = 0x01,
    /**
     *  退出群 (opUser & groupName & userList)
     */
    TIM_GROUP_TIPS_TYPE_QUIT_GRP            = 0x02,
    /**
     *  踢出群 (opUser & groupName & userList)
     */
    TIM_GROUP_TIPS_TYPE_KICKED              = 0x03,
    /**
     *  设置管理员 (opUser & groupName & userList)
     */
    TIM_GROUP_TIPS_TYPE_SET_ADMIN           = 0x04,
    /**
     *  取消管理员 (opUser & groupName & userList)
     */
    TIM_GROUP_TIPS_TYPE_CANCEL_ADMIN        = 0x05,
    /**
     *  群资料变更 (opUser & groupName & introduction & notification & faceUrl & owner)
     */
    TIM_GROUP_TIPS_TYPE_INFO_CHANGE         = 0x06,
    /**
     *  群成员资料变更 (opUser & groupName & memberInfoList)
     */
    TIM_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE         = 0x07,
};

/**
 *  群tips，成员变更信息
 */
@interface TIMGroupTipsElemMemberInfo : NSObject

/**
 *  变更用户
 */
@property(nonatomic,retain) NSString * identifier;
/**
 *  禁言时间（秒，表示还剩多少秒可以发言）
 */
@property(nonatomic,assign) uint32_t shutupTime;

@end


/**
 *  群Tips类型
 */
typedef NS_ENUM(NSInteger, TIM_GROUP_INFO_CHANGE_TYPE){
    /**
     *  群名修改
     */
    TIM_GROUP_INFO_CHANGE_GROUP_NAME                    = 0x01,
    /**
     *  群简介修改
     */
    TIM_GROUP_INFO_CHANGE_GROUP_INTRODUCTION            = 0x02,
    /**
     *  群公告修改
     */
    TIM_GROUP_INFO_CHANGE_GROUP_NOTIFICATION            = 0x03,
    /**
     *  群头像修改
     */
    TIM_GROUP_INFO_CHANGE_GROUP_FACE                    = 0x04,
    /**
     *  群主变更
     */
    TIM_GROUP_INFO_CHANGE_GROUP_OWNER                   = 0x05,
};

/**
 *  群tips，群变更信息
 */
@interface TIMGroupTipsElemGroupInfo : NSObject

/**
 *  变更类型
 */
@property(nonatomic, assign) TIM_GROUP_INFO_CHANGE_TYPE type;

/**
 *  根据变更类型表示不同含义
 */
@property(nonatomic,retain) NSString * value;
@end

/**
 *  群Tips
 */
@interface TIMGroupTipsElem : TIMElem

/**
 *  群组Id
 */
@property(nonatomic,retain) NSString * group;

/**
 *  群Tips类型
 */
@property(nonatomic,assign) TIM_GROUP_TIPS_TYPE type;

/**
 *  操作人用户名
 */
@property(nonatomic,retain) NSString * opUser;

/**
 *  被操作人列表 NSString* 数组
 */
@property(nonatomic,retain) NSArray * userList;

/**
 *  在群名变更时表示变更后的群名，否则为 nil
 */
@property(nonatomic,retain) NSString * groupName;

/**
 *  群信息变更： TIM_GROUP_TIPS_TYPE_INFO_CHANGE 时有效，为 TIMGroupTipsElemGroupInfo 结构体列表
 */
@property(nonatomic,retain) NSArray * groupChangeList;

/**
 *  成员变更： TIM_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE 时有效，为 TIMGroupTipsElemMemberInfo 结构体列表
 */
@property(nonatomic,retain) NSArray * memberChangeList;

/**
 *  操作者用户资料
 */
@property(nonatomic,retain) TIMUserProfile * opUserInfo;
/**
 *  操作者群成员资料
 */
@property(nonatomic,retain) TIMGroupMemberInfo * opGroupMemberInfo;
/**
 *  变更成员资料
 */
@property(nonatomic,retain) NSDictionary * changedUserInfo;
/**
 *  变更成员群内资料
 */
@property(nonatomic,retain) NSDictionary * changedGroupMemberInfo;

/**
 *  当前群人数： TIM_GROUP_TIPS_TYPE_INVITE、TIM_GROUP_TIPS_TYPE_QUIT_GRP、
 *             TIM_GROUP_TIPS_TYPE_KICKED时有效
 */
@property(nonatomic,assign) uint32_t memberNum;


/**
 *  操作方平台信息
 *  取值： iOS Android Windows Mac Web RESTAPI Unknown
 */
@property(nonatomic,retain) NSString * platform;

@end

/**
 *  地理位置Elem
 */
@interface TIMLocationElem : TIMElem
/**
 *  地理位置描述信息，发送消息时设置
 */
@property(nonatomic,retain) NSString * desc;
/**
 *  纬度，发送消息时设置
 */
@property(nonatomic,assign) double latitude;
/**
 *  经度，发送消息时设置
 */
@property(nonatomic,assign) double longitude;
@end


/**
 *  自定义消息类型
 */
@interface TIMCustomElem : TIMElem

/**
 *  自定义消息二进制数据
 */
@property(nonatomic,retain) NSData * data;
/**
 *  自定义消息描述信息，做离线Push时文本展示（已废弃，请使用TIMMessage中offlinePushInfo进行配置）
 */
@property(nonatomic,retain) NSString * desc DEPRECATED_ATTRIBUTE;
/**
 *  离线Push时扩展字段信息（已废弃，请使用TIMMessage中offlinePushInfo进行配置）
 */
@property(nonatomic,retain) NSString * ext DEPRECATED_ATTRIBUTE;
/**
 *  离线Push时声音字段信息（已废弃，请使用TIMMessage中offlinePushInfo进行配置）
 */
@property(nonatomic,retain) NSString * sound DEPRECATED_ATTRIBUTE;
@end

/**
 *  表情消息类型
 */
@interface TIMFaceElem : TIMElem

/**
 *  表情索引，用户自定义
 */
@property(nonatomic, assign) int index;
/**
 *  额外数据，用户自定义
 */
@property(nonatomic,retain) NSData * data;
@end


/**
 *  群系统消息类型
 */
typedef NS_ENUM(NSInteger, TIM_GROUP_SYSTEM_TYPE){
    /**
     *  申请加群请求（只有管理员会收到）
     */
    TIM_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE              = 0x01,
    /**
     *  申请加群被同意（只有申请人能够收到）
     */
    TIM_GROUP_SYSTEM_ADD_GROUP_ACCEPT_TYPE               = 0x02,
    /**
     *  申请加群被拒绝（只有申请人能够收到）
     */
    TIM_GROUP_SYSTEM_ADD_GROUP_REFUSE_TYPE               = 0x03,
    /**
     *  被管理员踢出群（只有被踢的人能够收到）
     */
    TIM_GROUP_SYSTEM_KICK_OFF_FROM_GROUP_TYPE            = 0x04,
    /**
     *  群被解散（全员能够收到）
     */
    TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE                   = 0x05,
    /**
     *  创建群消息（创建者能够收到）
     */
    TIM_GROUP_SYSTEM_CREATE_GROUP_TYPE                   = 0x06,
    /**
     *  邀请入群通知(被邀请者能够收到)
     */
    TIM_GROUP_SYSTEM_INVITED_TO_GROUP_TYPE               = 0x07,
    /**
     *  主动退群（主动退群者能够收到）
     */
    TIM_GROUP_SYSTEM_QUIT_GROUP_TYPE                     = 0x08,
    /**
     *  设置管理员(被设置者接收)
     */
    TIM_GROUP_SYSTEM_GRANT_ADMIN_TYPE                    = 0x09,
    /**
     *  取消管理员(被取消者接收)
     */
    TIM_GROUP_SYSTEM_CANCEL_ADMIN_TYPE                   = 0x0a,
    /**
     *  群已被回收(全员接收)
     */
    TIM_GROUP_SYSTEM_REVOKE_GROUP_TYPE                   = 0x0b,
    /**
     *  邀请入群请求(被邀请者接收)
     */
    TIM_GROUP_SYSTEM_INVITE_TO_GROUP_REQUEST_TYPE        = 0x0c,
    /**
     *  邀请加群被同意(只有发出邀请者会接收到)
     */
    TIM_GROUP_SYSTEM_INVITE_TO_GROUP_ACCEPT_TYPE         = 0x0d,
    /**
     *  邀请加群被拒绝(只有发出邀请者会接收到)
     */
    TIM_GROUP_SYSTEM_INVITE_TO_GROUP_REFUSE_TYPE         = 0x0e,
    /**
     *  用户自定义通知(默认全员接收)
     */
    TIM_GROUP_SYSTEM_CUSTOM_INFO                         = 0xff,
};

/**
 *  群系统消息
 */
@interface TIMGroupSystemElem : TIMElem

/**
 * 操作类型
 */
@property(nonatomic,assign) TIM_GROUP_SYSTEM_TYPE type;

/**
 * 群组Id
 */
@property(nonatomic,retain) NSString * group;

/**
 * 操作人
 */
@property(nonatomic,retain) NSString * user;

/**
 * 操作理由
 */
@property(nonatomic,retain) NSString * msg;


/**
 *  消息标识，客户端无需关心
 */
@property(nonatomic,assign) uint64_t msgKey;

/**
 *  消息标识，客户端无需关心
 */
@property(nonatomic,retain) NSData * authKey;

/**
 *  用户自定义透传消息体（type＝TIM_GROUP_SYSTEM_CUSTOM_INFO时有效）
 */
@property(nonatomic,retain) NSData * userData;

/**
 *  操作人资料
 */
@property(nonatomic,retain) TIMUserProfile * opUserInfo;

/**
 *  操作人群成员资料
 */
@property(nonatomic,retain) TIMGroupMemberInfo * opGroupMemberInfo;


/**
 *  同意申请，目前只对申请加群和被邀请入群消息生效
 *
 *  @param msg  同意理由，选填
 *  @param succ 成功回调
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) accept:(NSString*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  拒绝申请，目前只对申请加群和被邀请入群消息生效
 *
 *  @param msg  拒绝理由，选填
 *  @param succ 成功回调
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) refuse:(NSString*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 * 当前用户自己的identifier（内部使用）
 */
@property(nonatomic,retain) NSString * selfIdentifier;

/**
 *  操作方平台信息
 *  取值： iOS Android Windows Mac Web RESTAPI Unknown
 */
@property(nonatomic,retain) NSString * platform;

@end


typedef NS_ENUM(NSInteger, TIM_SNS_SYSTEM_TYPE){
    /**
     *  增加好友消息
     */
    TIM_SNS_SYSTEM_ADD_FRIEND                           = 0x01,
    /**
     *  删除好友消息
     */
    TIM_SNS_SYSTEM_DEL_FRIEND                           = 0x02,
    /**
     *  增加好友申请
     */
    TIM_SNS_SYSTEM_ADD_FRIEND_REQ                       = 0x03,
    /**
     *  删除未决申请
     */
    TIM_SNS_SYSTEM_DEL_FRIEND_REQ                       = 0x04,
    /**
     *  黑名单添加
     */
    TIM_SNS_SYSTEM_ADD_BLACKLIST                        = 0x05,
    /**
     *  黑名单删除
     */
    TIM_SNS_SYSTEM_DEL_BLACKLIST                        = 0x06,
    /**
     *  未决已读上报
     */
    TIM_SNS_SYSTEM_PENDENCY_REPORT                      = 0x07,
    /**
     *  关系链资料变更
     */
    TIM_SNS_SYSTEM_SNS_PROFILE_CHANGE                   = 0x08,
    /**
     *  推荐数据增加
     */
    TIM_SNS_SYSTEM_ADD_RECOMMEND                        = 0x09,
    /**
     *  推荐数据删除
     */
    TIM_SNS_SYSTEM_DEL_RECOMMEND                        = 0x0a,
    /**
     *  已决增加
     */
    TIM_SNS_SYSTEM_ADD_DECIDE                           = 0x0b,
    /**
     *  已决删除
     */
    TIM_SNS_SYSTEM_DEL_DECIDE                           = 0x0c,
    /**
     *  推荐已读上报
     */
    TIM_SNS_SYSTEM_RECOMMEND_REPORT                     = 0x0d,
    /**
     *  已决已读上报
     */
    TIM_SNS_SYSTEM_DECIDE_REPORT                        = 0x0e,


};


/**
 *  关系链变更详细信息
 */
@interface TIMSNSChangeInfo : NSObject

/**
 *  用户 identifier
 */
@property(nonatomic,retain) NSString * identifier;

/**
 *  用户昵称
 */
@property(nonatomic,retain) NSString * nickname;

/**
 *  申请添加时有效，添加理由
 */
@property(nonatomic,retain) NSString * wording;

/**
 *  申请时填写，添加来源
 */
@property(nonatomic,retain) NSString * source;


/**
 *  备注 type=TIM_SNS_SYSTEM_SNS_PROFILE_CHANGE 有效
 */
@property(nonatomic,retain) NSString * remark;

@end

/**
 *  关系链变更消息
 */
@interface TIMSNSSystemElem : TIMElem

/**
 * 操作类型
 */
@property(nonatomic,assign) TIM_SNS_SYSTEM_TYPE type;

/**
 * 被操作用户列表：TIMSNSChangeInfo 列表
 */
@property(nonatomic,retain) NSArray * users;

/**
 * 未决已读上报时间戳 type=TIM_SNS_SYSTEM_PENDENCY_REPORT 有效
 */
@property(nonatomic,assign) uint64_t pendencyReportTimestamp;

/**
 * 推荐已读上报时间戳 type=TIM_SNS_SYSTEM_RECOMMEND_REPORT 有效
 */
@property(nonatomic,assign) uint64_t recommendReportTimestamp;

/**
 * 已决已读上报时间戳 type=TIM_SNS_SYSTEM_DECIDE_REPORT 有效
 */
@property(nonatomic,assign) uint64_t decideReportTimestamp;

@end

/**
 *  资料变更
 */
typedef NS_ENUM(NSInteger, TIM_PROFILE_SYSTEM_TYPE){
    /**
     好友资料变更
     */
    TIM_PROFILE_SYSTEM_FRIEND_PROFILE_CHANGE        = 0x01,
};


/**
 *  资料变更系统消息
 */
@interface TIMProfileSystemElem : TIMElem

/**
 *  变更类型
 */
@property(nonatomic,assign) TIM_PROFILE_SYSTEM_TYPE type;

/**
 *  资料变更的用户
 */
@property(nonatomic,retain) NSString * fromUser;

/**
 *  资料变更的昵称（如果昵称没有变更，该值为nil）
 */
@property(nonatomic,retain) NSString * nickName;

@end


@interface TIMVideo : NSObject
/**
 *  视频ID，不用设置
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  视频文件类型，发送消息时设置
 */
@property(nonatomic,retain) NSString * type;
/**
 *  视频大小，不用设置
 */
@property(nonatomic,assign) int size;
/**
 *  视频时长，发送消息时设置
 */
@property(nonatomic,assign) int duration;

@property(nonatomic,retain) NSString * selfIdentifier;

/**
 *  获取视频
 *
 *  @param path 视频保存路径
 *  @param succ 成功回调
 *  @param fail 失败回调，返回错误码和错误描述
 */
-(void) getVideo:(NSString*)path succ:(TIMSucc)succ fail:(TIMFail)fail;

@end


@interface TIMSnapshot : NSObject
/**
 *  图片ID，不用设置
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  截图文件类型，发送消息时设置
 */
@property(nonatomic,retain) NSString * type;
/**
 *  图片大小，不用设置
 */
@property(nonatomic,assign) int size;
/**
 *  图片宽度，发送消息时设置
 */
@property(nonatomic,assign) int width;
/**
 *  图片高度，发送消息时设置
 */
@property(nonatomic,assign) int height;

/**
 *  获取图片
 *
 *  @param path 图片保存路径
 *  @param succ 成功回调，返回图片数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getImage:(NSString*) path succ:(TIMSucc)succ fail:(TIMFail)fail;

@property(nonatomic,retain) NSString * selfIdentifier;

@end

/**
 *  微视频消息
 */
@interface TIMVideoElem : TIMElem

/**
 *  上传时任务Id，可用来查询上传进度
 */
@property(nonatomic,assign) uint32_t taskId;

/**
 *  视频文件路径，发送消息时设置
 */
@property(nonatomic,retain) NSString * videoPath;

/**
 *  视频信息，发送消息时设置
 */
@property(nonatomic,retain) TIMVideo * video;

/**
 *  截图文件路径，发送消息时设置
 */
@property(nonatomic,retain) NSString * snapshotPath;

/**
 *  视频截图，发送消息时设置
 */
@property(nonatomic,retain) TIMSnapshot * snapshot;

/**
 *  查询上传进度
 */
- (uint32_t) getUploadingProgress;


@property(nonatomic,retain) NSString * selfIdentifier;

@end


typedef NS_ENUM(NSInteger, TIMOfflinePushFlag) {
    /**
     *  按照默认规则进行推送
     */
    TIM_OFFLINE_PUSH_DEFAULT    = 0,
    /**
     *  不进行推送
     */
    TIM_OFFLINE_PUSH_NO_PUSH    = 1,
};

typedef NS_ENUM(NSInteger, TIMAndroidOfflinePushNotifyMode) {
    /**
     *  通知栏消息
     */
    TIM_ANDROID_OFFLINE_PUSH_NOTIFY_MODE_NOTIFICATION = 0x00,
    /**
     *  不弹窗，由应用自行处理
     */
    TIM_ANDROID_OFFLINE_PUSH_NOTIFY_MODE_CUSTOM = 0x01,
};

@interface TIMAndroidOfflinePushConfig : NSObject
/**
 *  离线推送时展示标签
 */
@property(nonatomic,retain) NSString * title;
/**
 *  Android离线Push时声音字段信息
 */
@property(nonatomic,retain) NSString * sound;
/**
 *  离线推送时通知形式
 */
@property(nonatomic,assign) TIMAndroidOfflinePushNotifyMode notifyMode;

@end

/**
 填入sound字段表示接收时不会播放声音
 */
extern NSString * const kIOSOfflinePushNoSound;

@interface TIMIOSOfflinePushConfig : NSObject
/**
 *  离线Push时声音字段信息
 */
@property(nonatomic,retain) NSString * sound;
/**
 *  忽略badge计数
 */
@property(nonatomic,assign) BOOL ignoreBadge;
@end

@interface TIMOfflinePushInfo : NSObject
/**
 *  自定义消息描述信息，做离线Push时文本展示
 */
@property(nonatomic,retain) NSString * desc;
/**
 *  离线Push时扩展字段信息
 */
@property(nonatomic,retain) NSString * ext;
/**
 *  推送规则标志
 */
@property(nonatomic,assign) TIMOfflinePushFlag pushFlag;
/**
 *  iOS离线推送配置
 */
@property(nonatomic,retain) TIMIOSOfflinePushConfig * iosConfig;
/**
 *  Android离线推送配置
 */
@property(nonatomic,retain) TIMAndroidOfflinePushConfig * androidConfig;
@end


/**
 *  消息
 */
@interface TIMMessage : NSObject {
}

/**
 *  增加Elem
 *
 *  @param elem elem结构
 *
 *  @return 0       表示成功
 *          1       禁止添加Elem（文件或语音多于两个Elem）
 *          2       未知Elem
 */
-(int) addElem:(TIMElem*)elem;

/**
 *  获取对应索引的Elem
 *
 *  @param index 对应索引
 *
 *  @return 返回对应Elem
 */
-(TIMElem*) getElem:(int)index;

/**
 *  获取Elem数量
 *
 *  @return elem数量
 */
-(int) elemCount;

/**
 *  设置离线推送配置信息
 *
 *  @param info 配置信息
 *
 *  @return 0 成功
 */
-(int) setOfflinePushInfo:(TIMOfflinePushInfo*)info;

/**
 *  获得本消息离线推送配置信息
 *
 *  @return 配置信息，没设置返回nil
 */
-(TIMOfflinePushInfo*) getOfflinePushInfo;

/**
 *  设置业务命令字
 *
 *  @param buzCmds 业务命令字列表
 *                 @"im_open_busi_cmd.msg_robot" 表示发送给IM机器人
 *                 @"im_open_busi_cmd.msg_nodb" 表示不存离线
 *                 @"im_open_busi_cmd.msg_noramble" 表示不存漫游
 *                 @"im_open_busi_cmd.msg_nopush" 表示不实时下发给用户
 *
 *  @return 0 成功
 */
-(int) setBusinessCmd:(NSArray*)buzCmds;

/**
 *  获取会话
 *
 *  @return 该消息所对应会话
 */
-(TIMConversation*) getConversation;

/**
 *  是否已读
 *
 *  @return TRUE 已读  FALSE 未读
 */
-(BOOL) isReaded;

/**
 *  对方是否已读（仅C2C消息有效）
 *
 *  @return TRUE 已读  FALSE 未读
 */
-(BOOL) isPeerReaded;

/**
 *  消息状态
 *
 *  @return TIMMessageStatus 消息状态
 */
-(TIMMessageStatus) status;

/**
 *  是否发送方
 *
 *  @return TRUE 表示是发送消息    FALSE 表示是接收消息
 */
-(BOOL) isSelf;

/**
 *  获取发送方
 *
 *  @return 发送方标识
 */
-(NSString *) sender;

/**
 *  删除消息：注意这里仅修改状态
 *
 *  @return TRUE 成功
 */
-(BOOL) remove;

/**
 *  从本地数据库删除消息：注意群组消息通过getMessage接口会从svr同步到本地
 *
 *  @return TRUE 成功
 */
-(BOOL) delFromStorage;

/**
 *  消息Id
 */
-(NSString *) msgId;

/**
 *  消息有断层，OnNewMessage回调收到消息，如果有断层，需要重新GetMessage补全（有C2C漫游的情况下使用）
 *
 *  @return TRUE 有断层
 *          FALSE  无断层
 */
-(BOOL) hasGap;

/**
 *  当前消息的时间戳
 *
 *  @return 时间戳
 */
-(NSDate*) timestamp;


/**
 *  获取发送者资料（发送者为自己时可能为空）
 *
 *  @return 发送者资料，nil 表示没有获取资料，目前只有字段：identifier、nickname、faceURL、customInfo
 */
-(TIMUserProfile *) GetSenderProfile;

/**
 *  获取发送者群内资料（发送者为自己时可能为空）
 *
 *  @return 发送者群内资料，nil 表示没有获取资料或者不是群消息，目前只有字段：member、nameCard、role、customInfo
 */
-(TIMGroupMemberInfo *) GetSenderGroupMemberProfile;

/**
 *  设置自定义整数，默认为0
 *
 *  @param param 设置参数
 *
 *  @return TRUE 设置成功
 */
- (BOOL) setCustomInt:(int32_t) param;

/**
 *  设置自定义数据，默认为""
 *
 *  @param data 设置参数
 *
 *  @return TRUE 设置成功
 */
- (BOOL) setCustomData:(NSData*) data;

/**
 *  获取CustomInt
 *
 *  @return CustomInt
 */
- (int32_t) customInt;

/**
 *  获取CustomData
 *
 *  @return CustomData
 */
- (NSData*) customData;

/**
 *  获取消息uniqueId
 *
 *  @return uniqueId
 */
- (uint64_t) uniqueId;

/**
 *  获取消息定位符
 *
 *  @return locator
 */
- (TIMMessageLocator*) locator;

/**
 *  设置消息的优先级
 *
 *  @param priority 优先级
 *
 *  @return TRUE 设置成功
 */
- (BOOL) setPriority:(TIMMessagePriority)priority;

/**
 *  获取消息的优先级
 *
 *  @return 优先级
 */
- (TIMMessagePriority) getPriority;

/**
 *  获取消息所属会话的接收消息选项（仅对群组消息有效）
 *
 *  @return 接收消息选项
 */
- (TIMGroupReceiveMessageOpt) getRecvOpt;

/**
 *  设置消息时间戳，导入到本地时有效
 *
 *  @param time 时间戳
 *
 *  @return 0 成功
 */
- (int) setTime:(time_t)time;

/**
 *  设置消息发送方
 *
 *  @param sender 发送方Id
 *
 *  @return 0 成功
 */
- (int) setSender:(NSString*)sender;

/**
 *  将消息导入到本地
 *
 *  @return 0 成功
 */
- (int) convertToImportedMsg;


/**
 *  拷贝消息中的属性（ELem、priority、online、offlinePushInfo）
 *
 *  @param srcMsg 源消息
 *
 *  @return 0 成功
 */
- (int) copyFrom:(TIMMessage*)srcMsg;

@end

@interface TIMMessageDraft : NSObject

/**
 *  设置自定义数据
 *
 *  @param userData 自定义数据
 *
 *  @return 0 成功
 */
-(int) setUserData:(NSData*)userData;

/**
 *  获取自定义数据
 *
 *  @return 自定义数据
 */
-(NSData*) getUserData;

/**
 *  增加Elem
 *
 *  @param elem elem结构
 *
 *  @return 0       表示成功
 *          1       禁止添加Elem（文件或语音多于两个Elem）
 *          2       未知Elem
 */
-(int) addElem:(TIMElem*)elem;

/**
 *  获取对应索引的Elem
 *
 *  @param index 对应索引
 *
 *  @return 返回对应Elem
 */
-(TIMElem*) getElem:(int)index;

/**
 *  获取Elem数量
 *
 *  @return elem数量
 */
-(int) elemCount;

/**
 *  草稿生成对应的消息
 *
 *  @return 消息
 */
-(TIMMessage*) transformToMessage;

/**
 *  当前消息的时间戳
 *
 *  @return 时间戳
 */
-(NSDate*) timestamp;

@end

#endif
