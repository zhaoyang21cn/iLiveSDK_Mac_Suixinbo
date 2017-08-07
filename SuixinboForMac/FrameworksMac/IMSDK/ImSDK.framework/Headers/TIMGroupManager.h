//
//  TIMGroupManager.h
//  ImSDK
//
//  Created by bodeng on 17/3/15.
//  Copyright (c) 2015 tencent. All rights reserved.
//

#ifndef ImSDK_TIMGroupManager_h
#define ImSDK_TIMGroupManager_h

#import "TIMComm.h"

#import "TIMCodingModel.h"

@class TIMMessage;
@class TIMGroupAssistant;

/**
 * 加群选项
 */
typedef NS_ENUM(NSInteger, TIMGroupAddOpt) {
    /**
     *  禁止加群
     */
    TIM_GROUP_ADD_FORBID                    = 0,
    
    /**
     *  需要管理员审批
     */
    TIM_GROUP_ADD_AUTH                      = 1,
    
    /**
     *  任何人可以加入
     */
    TIM_GROUP_ADD_ANY                       = 2,
};

/**
 * 群成员角色
 */
typedef NS_ENUM(NSInteger, TIMGroupMemberRole) {
    /**
     *  未定义（没有获取该字段）
     */
    TIM_GROUP_MEMBER_UNDEFINED              = 0,
    
    /**
     *  群成员
     */
    TIM_GROUP_MEMBER_ROLE_MEMBER              = 200,
    
    /**
     *  群管理员
     */
    TIM_GROUP_MEMBER_ROLE_ADMIN               = 300,
    
    /**
     *  群主
     */
    TIM_GROUP_MEMBER_ROLE_SUPER               = 400,
};

/**
 *  群成员角色过滤方式
 */
typedef NS_ENUM(NSInteger, TIMGroupMemberFilter) {
    /**
     *  全部成员
     */
    TIM_GROUP_MEMBER_FILTER_ALL            = 0x00,
    /**
     *  群主
     */
    TIM_GROUP_MEMBER_FILTER_SUPER          = 0x01,
    /**
     *  管理员
     */
    TIM_GROUP_MEMBER_FILTER_ADMIN          = 0x02,
    /**
     *  普通成员
     */
    TIM_GROUP_MEMBER_FILTER_COMMON         = 0x04,
};

/**
 * 群成员获取资料标志
 */
typedef NS_ENUM(NSInteger, TIMGetGroupMemInfoFlag) {
    
    /**
     * 入群时间
     */
    TIM_GET_GROUP_MEM_INFO_FLAG_JOIN_TIME                    = 0x01,
    /**
     * 消息标志
     */
    TIM_GET_GROUP_MEM_INFO_FLAG_MSG_FLAG                     = 0x01 << 1,
    /**
     * 角色
     */
    TIM_GET_GROUP_MEM_INFO_FLAG_ROLE_INFO                    = 0x01 << 3,
    /**
     * 禁言时间
     */
    TIM_GET_GROUP_MEM_INFO_FLAG_SHUTUP_TIME                  = 0x01 << 4,
    /**
     * 群名片
     */
    TIM_GET_GROUP_MEM_INFO_FLAG_NAME_CARD                    = 0x01 << 5,
};

/**
 * 群基本获取资料标志
 */
typedef NS_ENUM(NSInteger, TIMGetGroupBaseInfoFlag) {
    /**
     *  不获取群组资料
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_NONE                           = 0x00,
    /**
     *  获取群组名
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_NAME                           = 0x01,
    /**
     *  获取创建时间
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_CREATE_TIME                    = 0x01 << 1,
    /**
     *  获取群主id
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_OWNER_UIN                      = 0x01 << 2,
    /**
     *  （不可用）
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_SEQ                            = 0x01 << 3,
    /**
     *  获取最近一次修改群信息时间
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_TIME                           = 0x01 << 4,
    /**
     *  （不可用）
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_NEXT_MSG_SEQ                   = 0x01 << 5,
    /**
     *  获取最近一次发消息时间
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_LAST_MSG_TIME                  = 0x01 << 6,
    /**
     *  （不可用）
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_APP_ID                         = 0x01 << 7,
    /**
     *  获取群成员数量
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_MEMBER_NUM                     = 0x01 << 8,
    /**
     *  获取最大群成员数量
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_MAX_MEMBER_NUM                 = 0x01 << 9,
    /**
     *  获取群公告
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_NOTIFICATION                   = 0x01 << 10,
    /**
     *  获取群简介
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_INTRODUCTION                   = 0x01 << 11,
    /**
     *  获取群头像
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_FACE_URL                       = 0x01 << 12,
    /**
     *  获取入群类型
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_ADD_OPTION                     = 0x01 << 13,
    /**
     *  获取群组类型
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_GROUP_TYPE                     = 0x01 << 14,
    /**
     *  获取最后一条群消息
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_LAST_MSG                       = 0x01 << 15,
    /**
     *  获取在线人数
     */
    TIM_GET_GROUP_BASE_INFO_FLAG_ONLINE_NUM                     = 0x01 << 16,
    /**
     *  获取群成员是否可见标志
     */
    TIM_GET_GROUP_BASE_INFO_VISIBLE                             = 0x01 << 17,
    /**
     *  获取群是否能被搜到标志
     */
    TIM_GET_GROUP_BASE_INFO_SEARCHABLE                          = 0x01 << 18
};

typedef NS_ENUM(NSInteger, TIMGroupMemberVisibleType) {
    /**
     *  未知
     */
    TIM_GROUP_MEMBER_VISIBLE_UNKNOWN          = 0x00,
    /**
     *  群组成员不可见
     */
    TIM_GROUP_MEMBER_VISIBLE_NO               = 0x01,
    /**
     *  群组成员可见
     */
    TIM_GROUP_MEMBER_VISIBLE_YES              = 0x02,
};

typedef NS_ENUM(NSInteger, TIMGroupSearchableType) {
    /**
     *  未知
     */
    TIM_GROUP_SEARCHABLE_UNKNOWN              = 0x00,
    /**
     *  群组不能被搜到
     */
    TIM_GROUP_SEARCHABLE_NO                   = 0x01,
    /**
     *  群组能被搜到
     */
    TIM_GROUP_SEARCHABLE_YES                  = 0x02,
};

/**
 *  群搜索回调
 *
 *  @param totalNum 搜索结果的总数
 *  @param groups  请求的群列表片段
 */
typedef void (^TIMGroupSearchSucc)(uint64_t totalNum, NSArray * groups);

/**
 *  群接受消息选项回调
 *
 *  @param opt 群接受消息选项
 */
typedef void (^TIMGroupReciveMessageOptSucc)(TIMGroupReceiveMessageOpt opt);


/**
 *  创建群组时的成员信息
 */
@interface TIMCreateGroupMemberInfo : TIMCodingModel

/**
 *  被操作成员
 */
@property(nonatomic,retain) NSString* member;

/**
 *  成员类型
 */
@property(nonatomic,assign) TIMGroupMemberRole role;

/**
 *  自定义字段集合,key是NSString*类型,value是NSData*类型
 */
@property(nonatomic,retain) NSDictionary* customInfo;

@end


/**
 *  群组内的本人信息
 */
@interface TIMGroupSelfInfo : NSObject

/**
 *  加入群组时间
 */
@property(nonatomic,assign) uint32_t joinTime;

/**
 *  群组中的角色
 */
@property(nonatomic,assign) TIMGroupMemberRole role;

/**
 *  群组消息接收选项
 */
@property(nonatomic,assign) TIMGroupReceiveMessageOpt recvOpt;

/**
 *  群组中的未读消息数
 */
@property(nonatomic,assign) uint32_t unReadMessageNum;

@end


/**
 *  创建群参数
 */
@interface TIMCreateGroupInfo : TIMCodingModel

/**
 *  群组Id,nil则使用系统默认Id
 */
@property(nonatomic,retain) NSString* group;

/**
 *  群名
 */
@property(nonatomic,retain) NSString* groupName;

/**
 *  群类型：Private,Public,ChatRoom,AVChatRoom,BChatRoom
 */
@property(nonatomic,retain) NSString* groupType;

/**
 *  是否设置入群选项，Private类型群组请设置为false
 */
@property(nonatomic,assign) BOOL setAddOpt;

/**
 *  入群选项
 */
@property(nonatomic,assign) TIMGroupAddOpt addOpt;

/**
 *  最大成员数，填0则系统使用默认值
 */
@property(nonatomic,assign) uint32_t maxMemberNum;

/**
 *  群公告
 */
@property(nonatomic,retain) NSString* notification;

/**
 *  群简介
 */
@property(nonatomic,retain) NSString* introduction;

/**
 *  群头像
 */
@property(nonatomic,retain) NSString* faceURL;

/**
 *  自定义字段集合,key是NSString*类型,value是NSData*类型
 */
@property(nonatomic,retain) NSDictionary* customInfo;

/**
 *  创建成员（TIMCreateGroupMemberInfo*）列表
 */
@property(nonatomic,retain) NSArray* membersInfo;

@end


/**
 * 未决请求选项
 */
@interface TIMGroupPendencyOption : TIMCodingModel

/**
 *  拉取的起始时间 0：拉取最新的
 */
@property(nonatomic,assign) uint64_t timestamp;

/**
 *  每页的数量
 */
@property(nonatomic,assign) uint32_t numPerPage;
@end


/**
 *  未决请求元信息
 */
@interface TIMGroupPendencyMeta : TIMCodingModel

/**
 *  下一次拉取的起始时间戳
 */
@property(nonatomic,assign) uint64_t nextStartTime;

/**
 *  已读时间戳大小
 */
@property(nonatomic,assign) uint64_t readTimeSeq;

/**
 *  未决未读数
 */
@property(nonatomic,assign) uint32_t unReadCnt;

@end


typedef NS_ENUM(NSInteger, TIMGroupPendencyGetType) {
    /**
     *  申请入群
     */
    TIM_GROUP_PENDENCY_GET_TYPE_JOIN            = 0x0,
    /**
     *  邀请入群
     */
    TIM_GROUP_PENDENCY_GET_TYPE_INVITE          = 0x1,
};


typedef NS_ENUM(NSInteger, TIMGroupPendencyHandleStatus) {
    /**
     *  未处理
     */
    TIM_GROUP_PENDENCY_HANDLE_STATUS_UNHANDLED            = 0,
    /**
     *  被他人处理
     */
    TIM_GROUP_PENDENCY_HANDLE_STATUS_OTHER_HANDLED        = 1,
    /**
     *  被用户处理
     */
    TIM_GROUP_PENDENCY_HANDLE_STATUS_OPERATOR_HANDLED     = 2,
};


typedef NS_ENUM(NSInteger, TIMGroupPendencyHandleResult) {
    /**
     *  拒绝申请
     */
    TIM_GROUP_PENDENCY_HANDLE_RESULT_REFUSE       = 0,
    /**
     *  同意申请
     */
    TIM_GROUP_PENDENCY_HANDLE_RESULT_AGREE        = 1,
};


/**
 *  未决申请
 */
@interface TIMGroupPendencyItem : TIMCodingModel

/**
 *  相关群组id
 */
@property(nonatomic,retain) NSString* groupId;

/**
 *  请求者id，请求加群:请求者，邀请加群:邀请人
 */
@property(nonatomic,retain) NSString* fromUser;

/**
 *  判决者id，请求加群:0，邀请加群:被邀请人
 */
@property(nonatomic,retain) NSString* toUser;

/**
 *  未决添加时间
 */
@property(nonatomic,assign) uint64_t addTime;

/**
 *  未决请求类型
 */
@property(nonatomic,assign) TIMGroupPendencyGetType getType;

/**
 *  已决标志
 */
@property(nonatomic,assign) TIMGroupPendencyHandleStatus handleStatus;

/**
 *  已决结果
 */
@property(nonatomic,assign) TIMGroupPendencyHandleResult handleResult;

/**
 *  申请或邀请附加信息
 */
@property(nonatomic,retain) NSString* requestMsg;

/**
 *  审批信息：同意或拒绝信息
 */
@property(nonatomic,retain) NSString* handledMsg;


/**
 *  同意申请
 *
 *  @param msg      同意理由，选填
 *  @param succ     成功回调
 *  @param fail     失败回调，返回错误码和错误描述
 */
-(void) accept:(NSString*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  拒绝申请
 *
 *  @param msg      拒绝理由，选填
 *  @param succ     成功回调
 *  @param fail     失败回调，返回错误码和错误描述
 */
-(void) refuse:(NSString*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;


/**
 *  用户自己的id
 */
@property(nonatomic,retain) NSString* selfIdentifier;

@end


/**
 *  获取群组未决请求列表成功
 *
 *  @param meta       未决请求元信息
 *  @param pendencies 未决请求列表（TIMGroupPendencyItem）数组
 */
typedef void (^TIMGetGroupPendencyListSucc)(TIMGroupPendencyMeta * meta, NSArray * pendencies);


/**
 *  成员操作返回值
 */
@interface TIMGroupMemberInfo : TIMCodingModel

/**
 *  被操作成员
 */
@property(nonatomic,retain) NSString* member;

/**
 *  群名片
 */
@property(nonatomic,retain) NSString* nameCard;

/**
 *  加入群组时间
 */
@property(nonatomic,assign) time_t joinTime;

/**
 *  成员类型
 */
@property(nonatomic,assign) TIMGroupMemberRole role;

/**
 *  禁言结束时间（时间戳）
 */
@property(nonatomic,assign) uint32_t silentUntil;

/**
 *  自定义字段集合,key是NSString*类型,value是NSData*类型
 */
@property(nonatomic,retain) NSDictionary* customInfo;

@end

/**
 *  本人群组内成员信息回调
 *
 *  @param selfInfo 本人成员信息
 */
typedef void (^TIMGroupSelfSucc)(TIMGroupMemberInfo * selfInfo);


@interface TIMGroupManager : NSObject

/**
 *  获取群管理器实例
 *
 *  @return 管理器实例
 */
+(TIMGroupManager*)sharedInstance;

/**
 *  创建私有群
 *
 *  @param members   群成员，NSString* 数组
 *  @param groupName 群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) CreatePrivateGroup:(NSArray*)members groupName:(NSString*)groupName succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;

/**
 *  创建公开群
 *
 *  @param members   群成员，NSString* 数组
 *  @param groupName 群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) CreatePublicGroup:(NSArray*)members groupName:(NSString*)groupName succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;

/**
 *  创建聊天室
 *
 *  @param members   群成员，NSString* 数组
 *  @param groupName 群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) CreateChatRoomGroup:(NSArray*)members groupName:(NSString*)groupName succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;


/**
 *  创建音视频聊天室（可支持超大群，详情可参考wiki文档）
 *
 *  @param groupName 群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) CreateAVChatRoomGroup:(NSString*)groupName succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;

/**
 *  创建群组
 *
 *  @param type       群类型,Private,Public,ChatRoom,AVChatRoom
 *  @param members    待加入群组的成员列表
 *  @param groupName  群组名称
 *  @param groupId    自定义群组id
 *  @param succ       成功回调
 *  @param fail       失败回调
 *
 *  @return 0 成功
 */
-(int) CreateGroup:(NSString*)type members:(NSArray*)members groupName:(NSString*)groupName groupId:(NSString*)groupId succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;

/**
 *  创建群组
 *
 *  @param groupInfo 群组信息
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) CreateGroup:(TIMCreateGroupInfo*)groupInfo succ:(TIMCreateGroupSucc)succ fail:(TIMFail)fail;

/**
 *  解散群组
 *
 *  @param group 群组Id
 *  @param succ  成功回调
 *  @param fail  失败回调
 *
 *  @return 0 成功
 */
-(int) DeleteGroup:(NSString*)group succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  邀请好友入群
 *
 *  @param group   群组Id
 *  @param members 要加入的成员列表（NSString* 类型数组）
 *  @param succ    成功回调
 *  @param fail    失败回调
 *
 *  @return 0 成功
 */
-(int) InviteGroupMember:(NSString*)group members:(NSArray*)members succ:(TIMGroupMemberSucc)succ fail:(TIMFail)fail;

/**
 *  删除群成员
 *
 *  @param group   群组Id
 *  @param members 要删除的成员列表
 *  @param succ    成功回调
 *  @param fail    失败回调
 *
 *  @return 0 成功
 */
-(int) DeleteGroupMember:(NSString*)group members:(NSArray*)members succ:(TIMGroupMemberSucc)succ fail:(TIMFail)fail;

/**
 *  删除群成员
 *
 *  @param group   群组Id
 *  @param reason  删除原因
 *  @param members 要删除的成员列表
 *  @param succ    成功回调
 *  @param fail    失败回调
 *
 *  @return 0 成功
 */
-(int) DeleteGroupMemberWithReason:(NSString*)group reason:(NSString*)reason members:(NSArray*)members succ:(TIMGroupMemberSucc)succ fail:(TIMFail)fail;

/**
 *  申请加群
 *
 *  @param group 申请加入的群组Id
 *  @param msg   申请消息
 *  @param succ  成功回调（申请成功等待审批）
 *  @param fail  失败回调
 *
 *  @return 0 成功
 */
-(int) JoinGroup:(NSString*)group msg:(NSString*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  主动退出群组
 *
 *  @param group 群组Id
 *  @param succ  成功回调
 *  @param fail  失败回调
 *
 *  @return 0 成功
 */
-(int) QuitGroup:(NSString*)group succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  获取群列表
 *
 *  @param succ 成功回调，NSArray列表为 TIMGroupInfo，结构体只包含 group\groupName\groupType\faceUrl\selfInfo 信息
 *  @param fail 失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupList:(TIMGroupListSucc)succ fail:(TIMFail)fail;

/**
 *  获取群信息
 *
 *  @param succ 成功回调，不包含 selfInfo信息
 *  @param fail 失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupInfo:(NSArray*)groups succ:(TIMGroupListSucc)succ fail:(TIMFail)fail;

/**
 *  获取本人在群组内的成员信息
 *
 *  @param group 群组Id
 *  @param succ  成功回调，返回信息
 *  @param fail  失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupSelfInfo:(NSString*)group succ:(TIMGroupSelfSucc)succ fail:(TIMFail)fail;

/**
 *  获取接受消息选项
 *
 *  @param group            群组Id
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) GetReciveMessageOpt:(NSString*)group succ:(TIMGroupReciveMessageOptSucc)succ fail:(TIMFail)fail;

/**
 *  修改群名
 *
 *  @param group     群组Id
 *  @param groupName 新群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupName:(NSString*)group groupName:(NSString*)groupName succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群简介
 *
 *  @param group            群组Id
 *  @param introduction     群简介（最长120字节）
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupIntroduction:(NSString*)group introduction:(NSString*)introduction succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群公告
 *
 *  @param group            群组Id
 *  @param notification     群公告（最长150字节）
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupNotification:(NSString*)group notification:(NSString*)notification succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群头像
 *
 *  @param group            群组Id
 *  @param url              群头像地址（最长100字节）
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupFaceUrl:(NSString*)group url:(NSString*)url succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改加群选项
 *
 *  @param group            群组Id
 *  @param opt              加群选项，详见 TIMGroupAddOpt
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupAddOpt:(NSString*)group opt:(TIMGroupAddOpt)opt succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群自定义字段集合
 *
 *  @param group      群组Id
 *  @param customInfo 自定义字段集合,key是NSString*类型,value是NSData*类型
 *  @param succ       成功回调
 *  @param fail       失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupCustomInfo:(NSString*)group customInfo:(NSDictionary*)customInfo succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  转让群给新群主
 *
 *  @param group      群组Id
 *  @param identifier 新的群主Id
 *  @param succ       成功回调
 *  @param fail       失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupOwner:(NSString*)group user:(NSString*)identifier succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改接受消息选项
 *
 *  @param group            群组Id
 *  @param opt              接受消息选项，详见 TIMGroupReceiveMessageOpt
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyReciveMessageOpt:(NSString*)group opt:(TIMGroupReceiveMessageOpt)opt succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群成员角色
 *
 *  @param group            群组Id
 *  @param identifier       被修改角色的用户identifier
 *  @param role             角色（注意：不能修改为群主），详见 TIMGroupMemberRole
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupMemberInfoSetRole:(NSString*)group user:(NSString*)identifier role:(TIMGroupMemberRole)role succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  禁言用户（只有管理员或群主能够调用）
 *
 *  @param group            群组Id
 *  @param identifier       被禁言的用户identifier
 *  @param stime            禁言时间
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupMemberInfoSetSilence:(NSString*)group user:(NSString*)identifier stime:(uint32_t)stime succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群名片（只有本人、管理员或群主能够调用）
 *
 *  @param group            群组Id
 *  @param identifier       被操作用户identifier
 *  @param nameCard         群名片
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupMemberInfoSetNameCard:(NSString*)group user:(NSString*)identifier nameCard:(NSString*)nameCard succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群成员自定义字段集合
 *
 *  @param group      群组Id
 *  @param identifier 被操作用户identifier
 *  @param customInfo 自定义字段集合,key是NSString*类型,value是NSData*类型
 *  @param succ       成功回调
 *  @param fail       失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupMemberInfoSetCustomInfo:(NSString*)group user:(NSString*)identifier customInfo:(NSDictionary*)customInfo succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群组是否可被搜索属性
 *
 *  @param group      群组Id
 *  @param searchable 是否能被搜索
 *  @param succ       成功回调
 *  @param fail       失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupSearchable:(NSString*)group searchable:(BOOL)searchable succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  修改群组成员是否可见属性
 *
 *  @param group   群组Id
 *  @param visible 是否可见
 *  @param succ    成功回调
 *  @param fail    失败回调
 *
 *  @return 0 成功
 */
-(int) ModifyGroupMemberVisible:(NSString*)group visible:(BOOL)visible succ:(TIMSucc)succ fail:(TIMFail)fail;


/**
 *  获取群成员列表
 *
 *  @param group 群组Id
 *  @param succ  成功回调(TIMGroupMemberInfo列表)
 *  @param fail  失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupMembers:(NSString*)group succ:(TIMGroupMemberSucc)succ fail:(TIMFail)fail;

/**
 *  获取群组指定成员的信息
 *
 *  @param group   群组Id
 *  @param members 成员Id（NSString*）列表
 *  @param succ    成功回调(TIMGroupMemberInfo列表)
 *  @param fail    失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupMembersInfo:(NSString*)group members:(NSArray*)members succ:(TIMGroupMemberSucc)succ fail:(TIMFail)fail;

/**
 *  获取群公开信息
 *  @param groups 群组Id
 *  @param succ 成功回调
 *  @param fail 失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupPublicInfo:(NSArray*)groups succ:(TIMGroupListSucc)succ fail:(TIMFail)fail;

/**
 *  获取群成员列表（支持按字段拉取，分页）
 *
 *  @param group    群组Id
 *  @param flags    拉取资料标志
 *  @param custom   要获取的自定义key列表，暂不支持，传nil
 *  @param nextSeq  分页拉取标志，第一次拉取填0，回调成功如果不为零，需要分页，传入再次拉取，直至为0
 *  @param succ     成功回调
 *  @param fail     失败回调
 *
 *  @return 0 成功
 */
-(int) GetGroupMembersV2:(NSString*)group flags:(TIMGetGroupMemInfoFlag)flags custom:(NSArray*)custom nextSeq:(uint64_t)nextSeq succ:(TIMGroupMemberSuccV2)succ fail:(TIMFail)fail;

/**
 *  获取指定类型的成员列表（支持按字段拉取，分页）
 *
 *  @param group      群组Id：（NSString*) 列表
 *  @param filter     群成员角色过滤方式
 *  @param flags      拉取资料标志
 *  @param custom     要获取的自定义key（NSString*）列表
 *  @param nextSeq    分页拉取标志，第一次拉取填0，回调成功如果不为零，需要分页，传入再次拉取，直至为0
 *  @param succ       成功回调
 *  @param fail       失败回调
 */
-(int) GetGroupMembers:(NSString*)group ByFilter:(TIMGroupMemberFilter)filter flags:(TIMGetGroupMemInfoFlag)flags custom:(NSArray*)custom nextSeq:(uint64_t)nextSeq succ:(TIMGroupMemberSuccV2)succ fail:(TIMFail)fail;

/**
 *  获取群公开资料（可指定字段拉取）
 *
 *  @param groups   群组Id：（NSString*) 列表
 *  @param flags    拉取资料标志
 *  @param custom   要获取的自定义key（NSString*）列表
 *  @param succ     成功回调
 *  @param fail     失败回调
 */
-(int) GetGroupPublicInfoV2:(NSArray*)groups flags:(TIMGetGroupBaseInfoFlag)flags custom:(NSArray*)custom succ:(TIMGroupListSucc)succ fail:(TIMFail)fail;

/**
 *  通过名称信息获取群资料（可指定字段拉取）
 *
 *  @param groupName      群组名称
 *  @param flags          拉取资料标志
 *  @param custom         要获取的自定义key（NSString*）列表
 *  @param pageIndex      分页号
 *  @param pageSize       每页群组数目
 *  @param succ           成功回调
 *  @param fail           失败回调
 */
-(int) SearchGroup:(NSString*)groupName flags:(TIMGetGroupBaseInfoFlag)flags custom:(NSArray*)custom pageIndex:(uint32_t)pageIndex pageSize:(uint32_t)pageSize succ:(TIMGroupSearchSucc)succ fail:(TIMFail)fail;

/**
 *  获取群组未决列表
 *
 *  @param option 未决参数配置
 *  @param succ   成功回调，返回未决列表
 *  @param fail   失败回调
 *
 *  @return 0 成功
 */
-(int) GetPendencyFromServer:(TIMGroupPendencyOption*)option succ:(TIMGetGroupPendencyListSucc)succ fail:(TIMFail)fail;

/**
 *  群未决已读上报
 *
 *  @param timestamp 上报已读时间戳
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int) PendencyReport:(uint64_t)timestamp succ:(TIMSucc)succ fail:(TIMFail)fail;

@end

/**
 *  群资料信息
 */
@interface TIMGroupInfo : TIMCodingModel {
    NSString*       group;          // 群组Id
    NSString*       groupName;      // 群名
    NSString*       groupType;      // 群组类型
    NSString*       owner;          // 创建人
    uint32_t        createTime;     // 群创建时间
    uint32_t        lastInfoTime;   // 最近一次修改资料时间
    uint32_t        lastMsgTime;    // 最近一次发消息时间
    uint32_t        maxMemberNum;   // 最大成员数
    uint32_t        memberNum;      // 群成员数量
    TIMGroupAddOpt  addOpt;         // 申请入群类型
    
    NSString*       notification;      // 群公告
    NSString*       introduction;      // 群简介
    
    NSString*       faceURL;            // 群头像
    
    TIMMessage *     lastMsg;           // 最后一条消息
    
    uint32_t        onlineMemberNum;
    TIMGroupSearchableType isSearchable;   // 是否可被搜到
    TIMGroupMemberVisibleType isMemberVisible;    // 成员是否可见
    
    TIMGroupSelfInfo * selfInfo;        // 本人信息
    
    NSDictionary *   customInfo;        // 自定义字段集合
}

/**
 *  群组Id
 */
@property(nonatomic,retain) NSString* group;
/**
 *  群名
 */
@property(nonatomic,retain) NSString* groupName;
/**
 *  群创建人/管理员
 */
@property(nonatomic,retain) NSString * owner;
/**
 *  群类型：Private,Public,ChatRoom
 */
@property(nonatomic,retain) NSString* groupType;
/**
 *  群创建时间
 */
@property(nonatomic,assign) uint32_t createTime;
/**
 *  最近一次群资料修改时间
 */
@property(nonatomic,assign) uint32_t lastInfoTime;
/**
 *  最近一次发消息时间
 */
@property(nonatomic,assign) uint32_t lastMsgTime;
/**
 *  最大成员数
 */
@property(nonatomic,assign) uint32_t maxMemberNum;
/**
 *  群成员数量
 */
@property(nonatomic,assign) uint32_t memberNum;

/**
 *  入群类型
 */
@property(nonatomic,assign) TIMGroupAddOpt addOpt;

/**
 *  群公告
 */
@property(nonatomic,retain) NSString* notification;

/**
 *  群简介
 */
@property(nonatomic,retain) NSString* introduction;

/**
 *  群头像
 */
@property(nonatomic,retain) NSString* faceURL;

/**
 *  最后一条消息
 */
@property(nonatomic,retain) TIMMessage* lastMsg;

/**
 *  在线成员数量
 */
@property(nonatomic,assign) uint32_t onlineMemberNum;

/**
 *  群组是否被搜索类型
 */
@property(nonatomic,assign) TIMGroupSearchableType isSearchable;

/**
 *  群组成员可见类型
 */
@property(nonatomic,assign) TIMGroupMemberVisibleType isMemberVisible;

/**
 *  群组中的本人信息
 */
@property(nonatomic,retain) TIMGroupSelfInfo* selfInfo;

/**
 *  自定义字段集合,key是NSString*类型,value是NSData*类型
 */
@property(nonatomic,retain) NSDictionary* customInfo;

@end


/**
 *  群组操作结果
 */
typedef NS_ENUM(NSInteger, TIMGroupMemberStatus) {
    /**
     *  操作失败
     */
    TIM_GROUP_MEMBER_STATUS_FAIL              = 0,
    
    /**
     *  操作成功
     */
    TIM_GROUP_MEMBER_STATUS_SUCC              = 1,
    
    /**
     *  无效操作，加群时已经是群成员，移除群组时不在群内
     */
    TIM_GROUP_MEMBER_STATUS_INVALID           = 2,
    
    /**
     *  等待处理，邀请入群时等待对方处理
     */
    TIM_GROUP_MEMBER_STATUS_PENDING           = 3,
};

/**
 *  成员操作返回值
 */
@interface TIMGroupMemberResult : NSObject

/**
 *  被操作成员
 */
@property(nonatomic,retain) NSString* member;
/**
 *  返回状态
 */
@property(nonatomic,assign) TIMGroupMemberStatus status;

@end

#endif
