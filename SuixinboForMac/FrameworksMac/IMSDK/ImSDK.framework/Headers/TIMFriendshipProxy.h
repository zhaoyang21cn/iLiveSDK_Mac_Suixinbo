//
//  TIMFriendshipProxy.h
//  ImSDK
//
//  Created by tomzhu on 16/3/3.
//  Copyright © 2016年 tencent. All rights reserved.
//

#ifndef TIMFriendshipProxy_h
#define TIMFriendshipProxy_h

#import "TIMFriendshipManager.h"
#import "TIMComm.h"

#import "TIMCodingModel.h"

/**
 * 好友代理状态
 */
typedef NS_ENUM(NSInteger, TIM_FRIENDSHIP_PROXY_STATUS) {
    /**
     *  未初始化
     */
    TIM_FRIENDSHIP_STATUS_NONE      = 0x0,
    /**
     *  正在和服务器同步数据
     */
    TIM_FRIENDSHIP_STATUS_SYNCING   = 0x1,
    /**
     *  已经完成数据同步
     */
    TIM_FRIENDSHIP_STATUS_SYNCED    = 0x2,
    /**
     *  数据同步失败
     */
    TIM_FRIENDSHIP_STATUS_FAILED    = 0x3,
};

/**
 *  好友代理事件回调
 */
@protocol TIMFriendshipProxyListener <NSObject>
@optional
/**
 *  收到代理状态变更通知
 *
 *  @param status 当前状态
 */
-(void) OnProxyStatusChange:(TIM_FRIENDSHIP_PROXY_STATUS)status;

/**
 *  添加好友通知
 *
 *  @param users 好友列表（TIMUserProfile*）
 */
-(void) OnAddFriends:(NSArray*)users;

/**
 *  删除好友通知
 *
 *  @param identifiers 用户id列表（NSString*）
 */
-(void) OnDelFriends:(NSArray*)identifiers;

/**
 *  好友资料更新通知
 *
 *  @param profiles 资料列表（TIMUserProfile*）
 */
-(void) OnFriendProfileUpdate:(NSArray*)profiles;

/**
 *  好友申请通知
 *
 *  @param reqs 好友申请者id列表（TIMSNSChangeInfo*）
 */
-(void) OnAddFriendReqs:(NSArray*)reqs;

@end

/**
 *  好友分组信息扩展
 */
@interface TIMFriendGroupWithProfiles : TIMFriendGroup
/**
 *  好友资料（TIMUserProfile*）列表
 */
@property(nonatomic,retain) NSArray* profiles;
@end

/**
 *  好友分组列表
 *
 *  @param arr 好友分组（TIMFriendGroupWithProfiles*)列表
 */
typedef void (^TIMFriendGroupWithProfilesSucc)(NSArray * arr);

@interface TIMFriendshipSetting : NSObject

/**
 *  需要获取的好友信息标志（TIMProfileFlag）
 */
@property(nonatomic,assign) uint64_t friendFlags;

/**
 *  需要获取的好友自定义信息（NSString*）列表
 */
@property(nonatomic,retain) NSArray * friendCustom;

/**
 *  需要获取的用户自定义信息（NSString*）列表
 */
@property(nonatomic,retain) NSArray * userCustom;

@end


/**
 *  好友代理
 */
@interface TIMFriendshipProxy : NSObject

/**
 *  获取好友代理实例
 *
 *  @return 好友代理实例
 */
+(TIMFriendshipProxy*) sharedInstance;

/**
 *  获取好友列表
 *
 *  @return 好友资料（TIMUserProfile*）列表，proxy未同步时返回nil
 */
-(NSArray*) GetFriendList;

/**
 *  获取指定好友资料
 *
 *  @param users 好友id（NSString*）列表
 *
 *  @return 好友资料（TIMUserProfile*）列表，proxy未同步时返回nil
 */
-(NSArray*) GetFriendsProfile:(NSArray*)users;

/**
 *  获取好友分组列表
 *
 *  @return 好友分组（TIMFriendGroupWithProfiles*）列表，proxy未同步时返回nil
 */
-(NSArray*) GetFriendGroupList;

/**
 *  获取指定好友分组
 *
 *  @param groups 好友分组名称（NSString*）列表
 *
 *  @return 好友分组（TIMFriendGroupWithProfiles*）列表，proxy未同步时返回nil
 */
-(NSArray*) GetFriendGroup:(NSArray*)groups;

/**
 *  获取好友代理的状态
 *
 *  @return 好友代理的状态
 */
-(TIMFriendStatus) GetStaus;

@end


#endif /* TIMFriendshipProxy_h */
