//
//  TIMCallbackExt.h
//  ImSDK
//
//  Created by bodeng on 30/12/15.
//  Copyright © 2015 tencent. All rights reserved.
//

#ifndef TIMCallbackExt_h
#define TIMCallbackExt_h

/////////////////////////////////////////////////////////
///  回调协议
/////////////////////////////////////////////////////////

#import "AVMultiInvitProtocols.h"

#import "TIMComm.h"

@class TIMMessage;
@class TIMGroupTipsElem;


/**
 *  消息回调
 */
@protocol TIMMessageListener <NSObject>
@optional
/**
 *  新消息回调通知
 *
 *  @param msgs 新消息列表，TIMMessage 类型数组
 */
- (void)onNewMessage:(NSArray*) msgs;
@end


@protocol TIMMessageReceiptListener <NSObject>
@optional
/**
 *  收到了已读回执
 *
 *  @param receipts 已读回执（TIMMessageReceipt*）列表
 */
- (void) onRecvMessageReceipts:(NSArray*)receipts;
@end


/**
 *  消息修改回调
 */
@protocol TIMMessageUpdateListener <NSObject>
@optional
/**
 *  消息修改通知
 *
 *  @param msgs 修改的消息列表，TIMMessage 类型数组
 */
- (void)onMessageUpdate:(NSArray*) msgs;
@end



/**
 *  图片上传进度回调
 */
@protocol TIMUploadProgressListener <NSObject>
@optional
/**
 *  上传进度回调
 *
 *  @param msg      正在上传的消息
 *  @param elemidx  正在上传的elem的索引
 *  @param taskid   任务id
 *  @param progress 上传进度
 */
- (void)onUploadProgressCallback:(TIMMessage *)msg elemidx:(uint32_t)elemidx taskid:(uint32_t)taskid progress:(uint32_t)progress;
@end


// 音视频邀请消息回调
@protocol TIMAVInvitationListener <NSObject>
@optional
/**
 *  收到音视频邀请消息
 *  @params req 相应的请求
 */
- (void)onReceiveInvitation:(id<AVMultiInvitationReqAble>)req;

@end


/**
 *  群组成员变更通知
 */
@protocol TIMGroupMemberListener <NSObject>
@optional
/**
 *  群成员数量变更通知回调
 *  @param group   群组Id
 *  @param tipType 提示类型
 *  @param members 变更的成员列表
 */
- (void)onMemberUpdate:(NSString*)group tipType:(TIMGroupTipsType)tipType members:(NSArray*)members;

/**
 *  群成员资料变更通知回调
 *  @param group       群组Id
 *  @param memberInfos 成员资料变更列表,TIMGroupTipsElemMemberInfo类型数组
 */
- (void)onMemberInfoUpdate:(NSString*)group  memberInfos:(NSArray*)memberInfos;
@end

/**
 *  群事件通知回调
 */
@protocol TIMGroupEventListener <NSObject>
@optional
/**
 *  群tips回调
 *
 *  @param elem  群tips消息
 */
- (void)onGroupTipsEvent:(TIMGroupTipsElem*)elem;
@end

/**
 *  用户自定义状态回调
 */
@protocol TIMUserDefinedStatusListener <NSObject>
@optional
/**
 *  用户自定义状态变更通知回调
 *
 *  @param status 用户当前状态
 */
- (void)onStatusChanged:(TIMUserDefinedStatus*)status;
@end

#endif /* TIMCallbackExt_h */
