//
//  TIMGroupAssistant.h
//  ImSDK
//
//  Created by tomzhu on 16/3/24.
//  Copyright © 2016年 tencent. All rights reserved.
//

#ifndef TIMGroupAssistant_h
#define TIMGroupAssistant_h


#import "TIMGroupManager.h"


@protocol TIMGroupAssistantListener <NSObject>
@optional
/**
 *  有新用户加入群时的通知回调
 *
 *  @param groupId     群ID
 *  @param membersInfo 加群用户的群资料（TIMGroupMemberInfo*）列表
 */
-(void) OnMemberJoin:(NSString*)groupId membersInfo:(NSArray*)membersInfo;

/**
 *  有群成员退群时的通知回调
 *
 *  @param groupId 群ID
 *  @param members 退群成员的identifier（NSString*）列表
 */
-(void) OnMemberQuit:(NSString*)groupId members:(NSArray*)members;

/**
 *  群成员信息更新的通知回调
 *
 *  @param groupId     群ID
 *  @param membersInfo 更新后的群成员资料（TIMGroupMemberInfo*）列表
 */
-(void) OnMemberUpdate:(NSString*)groupId membersInfo:(NSArray*)membersInfo;

/**
 *  加入群的通知回调
 *
 *  @param groupInfo 加入群的群组资料
 */
-(void) OnGroupAdd:(TIMGroupInfo*)groupInfo;

/**
 *  解散群的通知回调
 *
 *  @param groupId 解散群的群ID
 */
-(void) OnGroupDelete:(NSString*)groupId;

/**
 *  群资料更新的通知回调
 *
 *  @param groupInfo 更新后的群资料信息
 */
-(void) OnGroupUpdate:(TIMGroupInfo*)groupInfo;

@end

@interface TIMGroupSetting : NSObject
/**
 *  需要获取的群组信息标志（TIMGetGroupBaseInfoFlag）
 */
@property(nonatomic,assign) uint64_t groupFlags;

/**
 *  需要获取群组资料的自定义信息（NSString*）列表
 */
@property(nonatomic,retain) NSArray * groupCustom;

/**
 *  需要获取的群成员标志（TIMGetGroupMemInfoFlag）
 */
@property(nonatomic,assign) uint64_t memberFlags;

/**
 *  需要获取群成员资料的自定义信息（NSString*）列表
 */
@property(nonatomic,retain) NSArray * memberCustom;

@end

/**
 *  群组助手
 */
@interface TIMGroupAssistant : NSObject

/**
 *  获取群组助手实例
 *
 *  @return 群主助手实例
 */
+(TIMGroupAssistant*) sharedInstance;

/**
 *  获取用户所在群组信息
 *
 *  @param groups 群组id（NSString*）列表
 *
 *  @return 群组信息（TIMGroupInfo*)列表，assistant未同步时返回nil
 */
-(NSArray*) GetGroupInfo:(NSArray*)groups;

/**
 *  获取用户群组列表
 *
 *  @return 群组信息（TIMGroupInfo*）列表，assistant未同步时返回nil
 */
-(NSArray*) GetGroupList;

@end


#endif /* TIMGroupAssistant_h */
