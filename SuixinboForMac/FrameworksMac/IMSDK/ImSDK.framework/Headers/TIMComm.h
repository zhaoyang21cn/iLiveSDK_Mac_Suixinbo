//
//  TIMComm.h
//  ImSDK
//
//  Created by bodeng on 29/1/15.
//  Copyright (c) 2015 tencent. All rights reserved.
//

#ifndef ImSDK_TIMComm_h
#define ImSDK_TIMComm_h

#import <Foundation/Foundation.h>

#define ERR_IMSDK_KICKED_BY_OTHERS      6208


/**
 * 网络连接状态
 */
typedef NS_ENUM(NSInteger, TIMNetworkStatus) {
    /**
     * 已连接
     */
    TIM_NETWORK_STATUS_CONNECTED             = 1,
    /**
     * 链接断开
     */
    TIM_NETWORK_STATUS_DISCONNECTED          = 2,
};


/**
 * 日志级别
 */
typedef NS_ENUM(NSInteger, TIMLogLevel) {
    TIM_LOG_NONE                = 0,
    TIM_LOG_ERROR               = 1,
    TIM_LOG_WARN                = 2,
    TIM_LOG_INFO                = 3,
    TIM_LOG_DEBUG               = 4,
};

/////////////////////////////////////////////////////////
///  回调Block
/////////////////////////////////////////////////////////

/**
 *  获取消息回调
 *
 *  @param msgs 消息列表
 */
typedef void (^TIMGetMsgSucc)(NSArray * msgs);

/**
 *  一般操作成功回调
 */
typedef void (^TIMSucc)();

/**
 *  操作失败回调
 *
 *  @param code 错误码
 *  @param msg  错误描述，配合错误码使用，如果问题建议打印信息定位
 */
typedef void (^TIMFail)(int code, NSString * msg);

/**
 *  登陆成功回调
 */
typedef void (^TIMLoginSucc)();

/**
 *  获取资源
 *
 *  @param data 资源二进制
 */
typedef void (^TIMGetResourceSucc)(NSData * data);



/**
 *  群创建成功
 *
 *  @param groupId 群组Id
 */
typedef void (^TIMCreateGroupSucc)(NSString * groupId);

/**
 *  群成员列表回调
 *
 *  @param members 群成员列表
 */
typedef void (^TIMGroupMemberSucc)(NSArray * members);

/**
 *  群成员列表回调（分页使用）
 *
 *  @param members 群成员（TIMGroupMemberInfo*）列表
 */
typedef void (^TIMGroupMemberSuccV2)(uint64_t nextSeq, NSArray * members);

/**
 *  群列表回调
 *
 *  @param arr 群列表
 */
typedef void (^TIMGroupListSucc)(NSArray * arr);


/**
 *  日志回调
 *
 *  @param lvl      输出的日志级别
 *  @param msg 日志内容
 */
typedef void (^TIMLogFunc)(TIMLogLevel lvl, NSString * msg);


@class TIMImageElem;
/**
 *  上传图片成功回调
 *
 *  @param elem 上传图片成功后elem
 */
typedef void (^TIMUploadImageSucc)(TIMImageElem * elem);

/**
 *  获取用户自定义状态成功回调
 *
 *  @param statusList 用户自定义状态（TIMUserDefinedStatus*）列表
 */
typedef void (^TIMUserDefinedStatusSucc)(NSArray * statusList);

/////////////////////////////////////////////////////////
///  基本类型
/////////////////////////////////////////////////////////

/**
 *  登陆信息
 */

@interface TIMLoginParam : NSObject{
    NSString*       accountType;        // 用户的账号类型
    NSString*       identifier;         // 用户名
    NSString*       userSig;            // 鉴权Token
    NSString*       appidAt3rd;          // App用户使用OAuth授权体系分配的Appid

    int             sdkAppId;           // 用户标识接入SDK的应用ID
}

/**
 *  用户的账号类型
 */
@property(nonatomic,retain) NSString* accountType;

/**
 * 用户名
 */
@property(nonatomic,retain) NSString* identifier;

/**
 *  鉴权Token
 */
@property(nonatomic,retain) NSString* userSig;

/**
 *  App用户使用OAuth授权体系分配的Appid
 */
@property(nonatomic,retain) NSString* appidAt3rd;


/**
 *  用户标识接入SDK的应用ID
 */
@property(nonatomic,assign) int sdkAppId;

@end



/**
 * 会话类型：
 *      C2C     双人聊天
 *      GROUP   群聊
 */
typedef NS_ENUM(NSInteger, TIMConversationType) {
    /**
     *  C2C 类型
     */
    TIM_C2C              = 1,
    
    /**
     *  群聊 类型
     */
    TIM_GROUP            = 2,
    
    /**
     *  系统消息
     */
    TIM_SYSTEM           = 3,
};



/**
 *  消息状态
 */
typedef NS_ENUM(NSInteger, TIMMessageStatus){
    /**
     *  消息发送中
     */
    TIM_MSG_STATUS_SENDING              = 1,
    /**
     *  消息发送成功
     */
    TIM_MSG_STATUS_SEND_SUCC            = 2,
    /**
     *  消息发送失败
     */
    TIM_MSG_STATUS_SEND_FAIL            = 3,
    /**
     *  消息被删除
     */
    TIM_MSG_STATUS_HAS_DELETED          = 4,
    /**
     *  导入到本地的消息
     */
    TIM_MSG_STATUS_LOCAL_STORED         = 5,
};


/**
 *  消息优先级标识
 */
typedef NS_ENUM(NSInteger, TIMMessagePriority) {
    /**
     *  高优先级，一般为红包或者礼物消息
     */
    TIM_MSG_PRIORITY_HIGH               = 1,
    /**
     *  普通优先级，普通消息
     */
    TIM_MSG_PRIORITY_NORMAL             = 2,
    /**
     *  低优先级，一般为点赞消息
     */
    TIM_MSG_PRIORITY_LOW                = 3,
    /**
     *  最低优先级，一般为后台下发的成员进退群通知
     */
    TIM_MSG_PRIORITY_LOWEST             = 4,
};

/**
 *  SetToken 参数
 */
@interface TIMTokenParam : NSObject
/**
 *  获取的客户端Token信息
 */
@property(nonatomic,retain) NSData* token;
/**
 *  业务ID，传递证书时分配
 */
@property(nonatomic,assign) uint32_t busiId;

@end


/**
 *  切后台参数
 */
@interface TIMBackgroundParam : NSObject {
    int c2cUnread;
    int groupUnread;
}

/**
 *  C2C 未读计数
 */
@property(nonatomic,assign) int c2cUnread;

/**
 *  群 未读计数
 */
@property(nonatomic,assign) int groupUnread;

@end

/**
 *  群组提示类型
 */
typedef NS_ENUM(NSInteger, TIMGroupTipsType){
    /**
     *  成员加入
     */
    TIM_GROUP_TIPS_JOIN              = 1,
    /**
     *  成员离开
     */
    TIM_GROUP_TIPS_QUIT              = 2,
    /**
     *  成员被踢
     */
    TIM_GROUP_TIPS_KICK              = 3,
    /**
     *  成员设置管理员
     */
    TIM_GROUP_TIPS_SET_ADMIN         = 4,
    /**
     *  成员取消管理员
     */
    TIM_GROUP_TIPS_CANCEL_ADMIN      = 5,
};

/**
 * 群消息接受选项
 */
typedef NS_ENUM(NSInteger, TIMGroupReceiveMessageOpt) {
    /**
     *  接收消息
     */
    TIM_GROUP_RECEIVE_MESSAGE                       = 0,
    /**
     *  不接收消息，服务器不进行转发
     */
    TIM_GROUP_NOT_RECEIVE_MESSAGE                   = 1,
    /**
     *  接受消息，不进行iOS APNs 推送
     */
    TIM_GROUP_RECEIVE_NOT_NOTIFY_MESSAGE            = 2,
};

@class TIMConversation;
/**
 *  已读回执
 */
@interface TIMMessageReceipt : NSObject
/**
 *  已读回执对应的会话（目前只支持C2C会话）
 */
@property(nonatomic,retain) TIMConversation * conversation;
/**
 *  收到已读回执时，这个时间戳之前的消息都已读
 */
@property(nonatomic,assign) time_t timestamp;
@end


/**
 *  事件上报信息
 */
@interface TIMEventReportItem : NSObject
/**
 *  事件id
 */
@property(nonatomic,assign) uint32_t event;
/**
 *  错误码
 */
@property(nonatomic,assign) uint32_t code;
/**
 *  错误描述
 */
@property(nonatomic,retain) NSString * desc;
/**
 *  事件延迟（单位ms）
 */
@property(nonatomic,assign) uint32_t delay;

@end

typedef NS_ENUM(NSInteger, TIMLoginStatus) {
    /**
     *  已登陆
     */
    TIM_STATUS_LOGINED             = 1,
    
    /**
     *  登陆中
     */
    TIM_STATUS_LOGINING            = 2,
    
    /**
     *  无登陆
     */
    TIM_STATUS_LOGOUT              = 3,
};


typedef NS_ENUM(NSInteger, TIMUserDefinedStatusClientType) {
    /**
     *  PC客户端
     */
    TIM_USER_DEFINED_STATUS_CLIENT_TYPE_PC      = 1,
    /**
     *  iOS客户端
     */
    TIM_USER_DEFINED_STATUS_CLIENT_TYPE_IOS     = 110,
    /**
     *  ANDROID客户端
     */
    TIM_USER_DEFINED_STATUS_CLIENT_TYPE_ANDROID = 109,
};

@interface TIMUserDefinedStatusUint : NSObject
/**
 *  客户端类型
 */
@property(nonatomic,assign) TIMUserDefinedStatusClientType clientType;
/**
 *  自定义状态
 */
@property(nonatomic,retain) NSString * status;
@end


@interface TIMUserDefinedStatus : NSObject
/**
 *  用户id
 */
@property(nonatomic,retain) NSString * identifier;
/**
 *  用户自定义状态（TIMUserDefinedStatusUint*）列表
 */
@property(nonatomic,retain) NSArray * uints;

@end

@interface TIMMessageLocator : NSObject
/**
 *  所属会话的id
 */
@property(nonatomic,retain) NSString * sessId;
/**
 *  所属会话的类型
 */
@property(nonatomic,assign) TIMConversationType sessType;
/**
 *  消息序列号
 */
@property(nonatomic,assign) uint64_t seq;
/**
 *  消息随机码
 */
@property(nonatomic,assign) uint64_t rand;
/**
 *  消息时间戳
 */
@property(nonatomic,assign) time_t time;
/**
 *  是否本人消息
 */
@property(nonatomic,assign) BOOL isSelf;

@end

#endif
