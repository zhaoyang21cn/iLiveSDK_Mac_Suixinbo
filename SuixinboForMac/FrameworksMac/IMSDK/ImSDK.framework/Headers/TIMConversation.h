//
//  TIMConversation.h
//  ImSDK
//
//  Created by bodeng on 28/1/15.
//  Copyright (c) 2015 tencent. All rights reserved.
//

#ifndef ImSDK_TIMConversation_h
#define ImSDK_TIMConversation_h

#import "TIMComm.h"
#import "TIMCallback.h"

@class TIMMessage;
@class TIMMessageDraft;

/**
 *  会话
 */
@interface TIMConversation : NSObject

/**
 *  发送消息
 *
 *  @param msg  消息体
 *  @param succ 发送成功时回调
 *  @param fail 发送失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) sendMessage: (TIMMessage*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  发送消息
 *
 *  @param msg 消息体
 *  @param cb  回调
 *
 *  @return 0 成功
 */
-(int) sendMessage: (TIMMessage*)msg cb:(id<TIMCallback>)cb;

/**
 *  保存消息到消息列表，这里只保存在本地
 *
 *  @param msg 消息体
 *  @param sender 发送方
 *  @param isReaded 是否已读，如果发送方是自己，默认已读
 *
 *  @return 0 成功
 */
-(int) saveMessage: (TIMMessage*)msg sender:(NSString*)sender isReaded:(BOOL)isReaded;

/**
 *  获取会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) getMessage: (int)count last:(TIMMessage*)last succ:(TIMGetMsgSucc)succ fail:(TIMFail)fail;

/**
 *  向前获取会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) getMessageForward: (int)count last:(TIMMessage*)last succ:(TIMGetMsgSucc)succ fail:(TIMFail)fail;

/**
 *  获取会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param cb    回调
 *
 *  @return 0 成功
 */
-(int) getMessage: (int)count last:(TIMMessage*)last cb:(id<TIMGetMessageCallback>)cb;

/**
 *  获取本地会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) getLocalMessage: (int)count last:(TIMMessage*)last succ:(TIMGetMsgSucc)succ fail:(TIMFail)fail;

/**
 *  获取本地会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param cb    回调
 *
 *  @return 0 成功
 */
-(int) getLocalMessage: (int)count last:(TIMMessage*)last cb:(id<TIMGetMessageCallback>)cb;

/**
 *  删除本地会话消息
 *
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) deleteLocalMessage:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  设置已读消息
 *
 *  @param readed 会话内最近一条已读的消息
 *
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 表示成功
 */
-(int) setReadMessage:(TIMMessage *)readed succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  设置已读消息
 *
 *  @param readed 会话内最近一条已读的消息
 *
 *  @return 0 表示成功
 */
-(int) setReadMessage: (TIMMessage*)readed;

/**
 *  设置会话中所有消息为已读状态
 *
 *  @return 0 表示成功
 */
-(int) setReadMessage;

/**
 *  获取该会话的未读计数
 *
 *  @return 返回未读计数
 */
-(int) getUnReadMessageNum;

/**
 *  获取会话人，单聊为对方账号，群聊为群组Id
 *
 *  @return 会话人
 */
-(NSString*) getReceiver;

/**
 *  获取会话类型
 *
 *  @return 会话类型
 */
-(TIMConversationType) getType;

/**
 *  获取改会话所属用户的id
 *
 *  @return 用户id
 */
-(NSString*) getSelfIdentifier;

/**
 *  从cache中获取最后几条消息
 *
 *  @param count 需要获取的消息数，最多为20
 *
 *  @return 消息（TIMMessage*）列表，第一条为最新消息
 */
-(NSArray*) getLastMsgs:(uint32_t)count;

/**
 *  发送红包消息（高优先级消息，普通消息不要使用此接口，否则可能影响红包消息）
 *
 *  @param msg  消息体
 *  @param succ 发送成功时回调
 *  @param fail 发送失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) sendRedPacketMessage: (TIMMessage*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  发送点赞消息（低优先级消息，极端情况可能会丢失消息确保系统稳定性）
 *
 *  @param msg  消息体
 *  @param succ 发送成功时回调
 *  @param fail 发送失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) sendLikeMessage: (TIMMessage*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  发送在线消息（服务器不保存消息）
 *
 *  @param msg  消息体
 *  @param succ 成功回调
 *  @param fail 失败回调
 *
 *  @return 0 成功
 */
-(int) sendOnlineMessage: (TIMMessage*)msg succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  将消息导入本地数据库
 *
 *  @param msgs 消息（TIMMessage*）列表
 *
 *  @return 0 成功
 */
-(int) importMessages: (NSArray*)msgs;

/**
 *  设置会话草稿
 *
 *  @param draft 草稿内容
 *
 *  @return 0 成功
 */
-(int) setDraft:(TIMMessageDraft*)draft;

/**
 *  获取会话草稿
 *
 *  @return 草稿内容，没有草稿返回nil
 */
-(TIMMessageDraft*) getDraft;

/**
 * 禁用本会话的存储，只对当前初始化有效，重启后需要重新设置
 * 需要 initSdk 之后调用
 */
-(void) disableStorage;

/**
 *  获取会话消息
 *
 *  @param locators 消息定位符（TIMMessageLocator）数组
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) findMessages:(NSArray*)locators succ:(TIMGetMsgSucc)succ fail:(TIMFail)fail;

@end


#endif
