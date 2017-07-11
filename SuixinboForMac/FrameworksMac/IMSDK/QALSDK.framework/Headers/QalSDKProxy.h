//
//  QalSDKProxy.h
//  QalSDK
//
//  Created by wtlogin on 15/8/7.
//  Copyright (c) 2015年 tencent. All rights reserved.
//
#ifndef QALSDK_PROXY_H
#define QALSDK_PROXY_H
#import <Foundation/Foundation.h>
#import "QalSDKCallbackProtocol.h"
//#import "MsfDelegate.h"
//#import <MsfSDK/MsfSDK.h>


#define SSOOPEN_REG @"sso_open_status.stat_reg"
#define SSOOPEN_HB  @"sso_open_status.stat_hello"

#define DEFAULT_LOG_SDK_PATH    @"/sdk.log"
#define DEFAULT_LOG_APP_PATH    @"/app.log"
#define log_internal 3600


@class QalStatusAdapter;
#ifdef QALSDK_FOR_TLS
@class TLSRefreshDelegate;

#endif
/**
 * 日志级别
 */
typedef NS_ENUM(NSInteger, LogLevel) {
    LOG_ERROR               = 1,
    LOG_WARN                = 2,
    LOG_INFO                = 3,
    LOG_DEBUG               = 4,
};

typedef enum _EQALBindFailReason
{
    EQALBindFail_Unknown = 0,   //未知错误
    EQALBindFail_NoSSOTicket,   //缺少sso票据
    EQALBindFail_NoNeedToUnbind,//已经unbind，不需要重复unbind
    EQALBindFail_TinyidNULL,//tiny为空
    EQALBindFail_GuidNULL,//guid为空
    EQALBindFail_UnpackRegPackFail,//解注册包失败
    EQALBindFail_RegTimeOut,//注册超时
    EQALBindFail_isBinding//正在注册中
    
    //>1000的错误码为状态svr返回
}EQALBindFailReason;

typedef enum _EQALPacketFailReason
{
    EQALPacketFail_Unknown = 0,
    EQALPacketFail_NoNetOnReq,
    EQALPacketFail_NoNetOnResp,
    EQALPacketFail_NoAuthOnReq,
    EQALPacketFail_SSOError,
    EQALPacketFail_TimeoutOnReq, //请求超时
    EQALPacketFail_TimeoutOnResp,//回包超时
    EQALPacketFail_NoResendOnReq,
    EQALPacketFail_NoResendOnResp,
    EQALPacketFail_FlowSaveFiltered,
    EQALPacketFail_OverLoadOnReq,
    EQALPacketFail_LogicError
}EQALPacketFailReason;


typedef enum _EQALNetworkType
{
    EQALNetworkType_Undefine = -1,
    EQALNetworkType_NotReachable = 0,
    EQALNetworkType_ReachableViaWiFi = 1,
    EQALNetworkType_ReachableViaWWAN = 2,
    EQALNetworkType_UNKNOWN = 100,
    EQALNetworkType_GPRS = 101,
    EQALNetworkType_EDGE = 102,
    EQALNetworkType_UMTS = 103,
    EQALNetworkType_CDMA = 104,
    EQALNetworkType_EVDO0 = 105,
    EQALNetworkType_EVDOA = 106,
    EQALNetworkType_1xRTT = 107,
    EQALNetworkType_HSDPA = 108,
    EQALNetworkType_HSUPA = 109,
    EQALNetworkType_HSPA = 110,
    EQALNetworkType_IDEN = 111,
    EQALNetworkType_EVDOB = 112,
    EQALNetworkType_LTE = 113,
    EQALNetworkType_EHRPD = 114,
    EQALNetworkType_HSPAP = 115,
    
    //Alert: 有ios自己的新类型时，从这里递减，并且改下EMSFNetWorkType_IOS_BEGIN的值
    EQALNetworkType_IOS_BEGIN = 98,
    //....
    EQALNetworkType_CDMA1x = 98,
    EQALNetworkType_WCDMA = 99,
    EQALNetworkType_IOS_END = 99,
}EQALNetworkType;




extern uint64_t g_tinyid;
extern uint32_t g_isready;









@interface QalSDKProxy : NSObject
{
    int env;
    int _sdkAppid;
    int _accType;
    id<QalConnListenerProtocol> _conncb;
    id<QalLogListenerProtocol> _logcb;
    id<QalUserStatusListenerProtocol> _statuscb;
    int shortConn;
}

+(void)setMsfFilePath:(NSString*) filePath;

/*
 获取QalSDK的实例
 */
+ (QalSDKProxy *)sharedInstance;

/*
 设置正式/测试环境
 @param value 0：正式环境，1：测试环境
 */
-(void)setEnv:(int) value;

/*
 初始化QalSDK
 @param sdkAppid sdkappid
 */

-(id)initQal:(int) sdkAppid;


/*
 初始化QalSDK
 @param appid msf appid
 @param sdkAppid sdkappid
 @pram accTye account type
 */

-(id)initWithAppid:(int) appid andSDKAppid:(int) sdkAppid andAccType:(int)accType;




/*
 增加push命令字回调
 @param cmd sso命令字
 @param cb push回调
*/

//-(void)addInitListener:(id<QalInitCallbackProtocol>) cb;

-(void)addPushListener:(NSString*) cmd andQalPushListener:(id<QalPushListenerProtocol>) cb;

/*
 设置连接通知回调
 @param cb 连接通知回调
*/

-(void)setConnectionListener:(id<QalConnListenerProtocol>) cb;


/*
 设置日志回调
 @param cb 日志回调
 */
-(void)setLogListener:(id<QalLogListenerProtocol>) cb;
/*
 设置用户状态通知回调
 @param cb 用户状态通知回调
 */
-(void)setUserStatusListener:(id<QalUserStatusListenerProtocol>) cb;

/*
 发送消息
 @param cmd sso命令字
 @param reqbody 请求包（总包长+业务包体，总包长=业务包体长度+包头长度4字节）
 @param timout 回包超时时间（单位:秒）
 @param cb 收包回调

-(int)sendMsg:(NSString*) cmd andReqbody:(NSData*) reqbody andTimeout:(int) timeout andQalReqCallback:(id<QalReqCallbackProtocol>) cb;
*/

/*
 发送消息
 @param identifier identifier
 @param cmd sso命令字
 @param reqbody 请求包（总包长+业务包体，总包长=业务包体长度+包头长度4字节）
 @param timout 回包超时时间（单位:秒）
 @param cb 收包回调
 */
-(int)sendMsgWithID:(NSString*)identifier AndCmd:(NSString*) cmd andReqbody:(NSData*) reqbody andTimeout:(int) timeout andQalReqCallback:(id<QalReqCallbackProtocol>) cb;


/*
 绑定账户
 @param user 用户名
 @param cb 绑定回调
 */
-(void)bindID:(NSString*) user andQalBindCallback:(id<QalBindCallbackProtocol>) cb;

/*解绑账户
 @param user 用户名
 @param cb 解绑回调
 */
-(void)unbindID:(NSString*) user andQalReqCallback:(id<QalBindCallbackProtocol>) cb;



- (BOOL)isConnected;

/*
 打印log
 @param level 日志级别
 @param tag 日志tag
 @param msg 日志内容
 */
 
-(void)log:(int)level andTag:(NSString*)tag andMsg:(NSString*)msg;

/*
 打印log
 @param level 日志级别
 @param tag 日志tag
 @param msg 日志内容
 */

-(void)applog:(int)level andTag:(NSString*)tag andMsg:(NSString*)msg;




/*
 获取当前的qalid
 */
-(NSString*)getIdentifier;



-(void)closeLocalLog;



-(NSString*)getSDKVer;


-(void)clearCb:(int)seq;

-(NSString*)getMsfAppid;

- (void)setOpenAppid:(NSString *)aOpenAppid;

-(int)getNetType;



@end
#endif
