//
//  QalSDKCallbackProtocol.h
//  QalSDK
//
//  Created by wtlogin on 15/8/7.
//  Copyright (c) 2015年 tencent. All rights reserved.
//
#ifndef QALSDK_CALLBACKPROTOCOL_H
#define QALSDK_CALLBACKPROTOCOL_H
#import <Foundation/Foundation.h>



@protocol QalInitCallbackProtocol <NSObject>

-(void)initFinished;

@end


@protocol QalPushListenerProtocol <NSObject>

@required
/*
 收到push包的回调
 @param busibuf 业务包
 @param cmd 命令字
 */
-(void)onPushSucc:(NSData*)busibuf andCmd:(NSString*)cmd andId:(NSString*)identifier;

/*
 push包错误的回调
 @param failreason 失败原因，具体参见QalSDKProxy.h里的_EQALPacketFailReason
 */

-(void)onPushFail:(int)failReason;

@end

@protocol QalConnListenerProtocol <NSObject>

@required
/*
 连接成功的回调
 @param ip 连接成功的svr ip
 @param port 连接成功的svr port
 */

-(void)onConnSucc:(NSString*)ip andPort:(NSString*)port;

/*
 连接断开的回调
 */
-(void)onDisconnected;

/*
 连接中的回调
 */
-(void)onConnecting;

/*
 wifi需要验证
 */
-(void)onNeedAuth;

@end

@protocol QalLogListenerProtocol <NSObject>

/*
 打印log回调
 @param level 日志级别
 @param tag 日志tag
 @param msg 日志内容
 */

@required
-(void)log:(int)level andTag:(NSString*)tag andMsg:(NSString*)msg;

@end

@protocol QalUserStatusListenerProtocol <NSObject>

@required
/*
 状态注册成功回调
 */
-(void)onRegSucc:(NSString*)identy;
/*
 状态注册失败回调
 */
-(void)onRegFail:(int) errCode andErrMsg:(NSString*)errMsg andIdentifier:(NSString*)identy;
/*
 踢下线通知回调
 */
-(void)onForceOffLine:(NSString*)identy;

/*
 票据错误通知
 */
-(void)onTicketError:(NSString*)identy andErrorcode:(NSString*)code;

@end

@protocol QalReqCallbackProtocol <NSObject>

@required
/*
 收到回包的回调
 @param busibuf 业务包
 */
-(void)onReqSucc:(NSData*)busibuf;
/*
 回包错误的回调
 @param failreason 失败原因，具体参见QalSDKProxy.h里的_EQALPacketFailReason
 */
-(void)onReqFail:(int)failReason;

@optional
-(void)onInnerReqSucc:(NSString*)tinyID andBusibuf:(NSData*)busibuf;
-(void)onInnerReqFail:(NSString*)tinyID andReason:(int)failReason;


@end

@protocol QalBindCallbackProtocol <NSObject>

@required
/*
 收到回包的回调
 @param busibuf 业务包
 */
-(void)onSucc;
/*
 回包错误的回调
 @param failreason 失败原因，具体参见QalSDKProxy.h里的_EQALBindFailReason
 */
-(void)onFail:(int)failReason;


@end

#endif