//
//  TIMManager.h
//  ImSDK
//
//  Created by bodeng on 28/1/15.
//  Copyright (c) 2015 tencent. All rights reserved.
//

#ifndef ImSDK_TIMManager_h
#define ImSDK_TIMManager_h

#import "TIMComm.h"
#import "TIMCallback.h"
#import "AVMultiInvitProtocols.h"

/////////////////////////////////////////////////////////
///  Tencent 开放 SDK API
/////////////////////////////////////////////////////////

/**
 *  通讯管理
 */
@interface TIMManager : NSObject


/**
 *  获取管理器实例
 *
 *  @return 管理器实例
 */
+(TIMManager*)sharedInstance;


/**
 *  （已经废弃）初始化SDK,第三方托管账号不能使用该接口初始化
 *
 *  @return 0 成功
 */
-(int) initSdk  DEPRECATED_ATTRIBUTE;

/**
 *  初始化SDK
 *
 * @param sdkAppId    用户标识接入SDK的应用ID
 *
 *  @return 0 成功
 */
-(int) initSdk:(int)sdkAppId;

/**
 *  初始化SDK
 *
 *  @param sdkAppId    用户标识接入SDK的应用ID
 *  @param accountType 用户的账号类型
 *
 *  @return 0 成功
 */
-(int) initSdk:(int)sdkAppId accountType:(NSString *)accountType;

/**
 *  禁用Crash上报，由用户自己上报，如果需要，必须在initSdk之前调用
 */
-(void) disableCrashReport;

/**
 *  禁用IM功能
 */
-(void) disableIM;

/**
 *  登陆
 *
 *  @param param 登陆参数
 *  @param succ  成功回调
 *  @param fail  失败回调
 *
 *  @return 0 请求成功
 */
-(int) login: (TIMLoginParam *)param succ:(TIMLoginSucc)succ fail:(TIMFail)fail;

/**
 *  登陆托管账号（第三方账号不能使用该接口）
 *
 *  @param identifier   用户表示id
 *  @param userSig      用户userSig
 *  @param succ  成功回调
 *  @param fail  失败回调
 *
 *  @return 0 请求成功
 */
-(int) login:(NSString*)identifier userSig:(NSString*)userSig succ:(TIMLoginSucc)succ fail:(TIMFail)fail;

/**
 *  初始化存储，仅查看历史消息时使用，如果要收发消息等操作，如login成功，不需要调用此函数
 *
 *  @param param 登陆参数（userSig 不用填写）
 *  @param succ  成功回调，收到回调时，可以获取会话列表和消息
 *  @param fail  失败回调
 *
 *  @return 0 请求成功
 */
-(int) initStorage: (TIMLoginParam *)param succ:(TIMLoginSucc)succ fail:(TIMFail)fail;

/**
 *  获取当前登陆的用户
 *
 *  @return 如果登陆返回用户的identifier，如果未登录返回nil
 */
-(NSString*) getLoginUser;

/**
 *  获取当前登录状态
 *
 *  @return 登录状态
 */
-(TIMLoginStatus) getLoginStatus;

/**
 *  登陆
 *
 *  @param param 登陆参数
 *  @param cb    回调
 *
 *  @return 0 登陆请求发送成功，等待回调
 */
-(int) login: (TIMLoginParam *)param cb:(id<TIMCallback>)cb;

/**
 *  登出
 *
 *  @param succ 成功回调，登出成功
 *  @param fail 失败回调，返回错误吗和错误信息
 *
 *  @return 0 发送登出包成功，等待回调
 */
-(int) logout:(TIMLoginSucc)succ fail:(TIMFail)fail;

/**
 *  登出
 *
 *  @deprecated 使用logout:fail 替代.
 *
 *  @return 0 成功
 */
-(int) logout DEPRECATED_ATTRIBUTE;


/**
 *  设置连接通知回调
 *
 *  @param listener 回调
 *
 *  @return 0 成功
 */
-(int) setConnListener: (id<TIMConnListener>)listener;

/**
 * 获取网络状态
 */
-(TIMNetworkStatus) networkStatus;

/**
 *  设置用户状态通知回调
 *
 *  @param listener 回调
 *
 *  @return 0 成功
 */
-(int) setUserStatusListener: (id<TIMUserStatusListener>)listener;

/**
 *  设置Token
 *
 *  @param token token信息
 *
 *  @return 0 成功
 */
-(int) setToken: (TIMTokenParam *)token;

/**
 *  设置Token，登录成功后调用
 *
 *  @param token token信息
 *  @param succ   成功回调
 *  @param fail   失败回调
 *
 *  @return 0 成功
 */
-(int) setToken:(TIMTokenParam *)token succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  设置APNS配置
 *
 *  @param config APNS配置
 *  @param succ   成功回调
 *  @param fail   失败回调
 *
 *  @return 0 成功
 */
-(int) setAPNS:(TIMAPNSConfig*)config succ:(TIMSucc)succ fail:(TIMFail)fail;

/**
 *  获取APNS配置
 *
 *  @param succ 成功回调，返回配置信息
 *  @param fail 失败回调
 *
 *  @return 0 成功
 */
-(int) getAPNSConfig:(TIMAPNSConfigSucc)succ fail:(TIMFail)fail;

/**
 *  app 切后台时调用
 *
 *  @param param 上报参数
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 表示成功
 */
-(int) doBackground: (TIMBackgroundParam*)param succ:(TIMSucc)succ fail:(TIMFail)fail;


/**
 *  切前台
 *
 *  @return 0 表示成功
 */
-(int) doForeground;


/**
 *  设置环境（在InitSdk之前调用，注意：除非是IM工作人员指定要求设置，否则不需要调用此接口）
 *
 *  @param env  0 正式环境（默认）
 *              1 测试环境
 */
-(void)setEnv:(int)env;

/**
 *  获取环境类型
 *
 *  @return env 0 正式环境（默认）
 *              1 测试环境
 *              2 beta 环境
 */
-(int)getEnv;


/**
 *  设置日志函数
 *
 *  @param cb 日志函数，SDK打印日志会通过此函数返给调用方
 */
-(void) setLogFunc:(TIMLogFunc)cb;

/**
 *  设置日志监听
 *
 *  @param cb 日志监听，SDK打印日志会通过此接口返给调用方
 */
-(void) setLogListener:(id<TIMLogListener>)cb;

/**
 *  设置日志回调的log等级
 *
 *  @param level 日志级别
 */
-(void) setLogListenerLevel:(TIMLogLevel)level;

/**
 *  获取日志回调的log等级
 *
 *  @return 日志级别
 */
-(TIMLogLevel) getLogListenerLevel;

/**
 *  获取版本号
 *
 *  @return 返回版本号，字符串表示，例如v1.1.1
 */
-(NSString*) GetVersion;

/**
 *  获取联网SDK的版本号
 *
 *  @return 返回版本号
 */
-(NSString*) GetQALVersion;

/**
 *  打印日志，通过ImSDK提供的日志功能打印日志
 *
 *  @param level 日志级别
 *  @param tag   模块tag
 *  @param msg   要输出的日志内容
 */
-(void) log:(TIMLogLevel)level tag:(NSString*)tag msg:(NSString*)msg;

/**
 * 设置日志级别，在initSDK之前调用
 *
 *  @param level 日志级别
 */
-(void) setLogLevel:(TIMLogLevel)level;

/**
 *  获取日志级别
 *
 *  @return 返回日志级别
 */
-(TIMLogLevel) getLogLevel;

/**
 *  app 切后台时调用
 *
 *  @deprecated 使用 doBackground 替代.
 *
 *  @param param 上报参数
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 表示成功
 */
-(int) doBackgroud: (TIMBackgroundParam*)param succ:(TIMSucc)succ fail:(TIMFail)fail DEPRECATED_ATTRIBUTE;

/**
 *  初始化日志设置，必须在initSdk之前调用，在initSdk之后设置无效
 *
 *  @param isEnableLogPrint 是否开启日志打印
 *  @param logPath  日志文件路径
 */
-(void) initLogSettings: (BOOL)isEnableLogPrint logPath:(NSString*) logPath;

/**
 * 获取日志文件路径
 */
-(NSString *) getLogPath;

/**
 * 是否开启sdk日志打印
 */
-(BOOL) getIsLogPrintEnabled;

/**
 *  设置会话刷新监听
 *
 *  @param listener 刷新监听（当有未读计数变更、会话变更时调用）
 *
 *  @return 0 设置成功
 */
-(int) setRefreshListener: (id<TIMRefreshListener>)listener;


/**
 *  创建新的管理器类型（多用户登陆时使用，否则可直接调用sharedInstance）
 *
 *  @return 管理器实例
 */
+(TIMManager*) newManager;

/**
 *  获取管理器类型（多用户登陆时使用，否则可直接调用sharedInstance）
 *
 *  @param identifier 用户identifier
 *
 *  @return 对应管理器类型，如果没有创建过，返回nil
 */
+(TIMManager*) getManager:(NSString*) identifier;

/**
 *  销毁管理器（多用户登陆时使用，否则可直接调用sharedInstance）
 *
 *  @param manager 需要销毁的管理器
 */
+(void) deleteManager:(TIMManager *) manager;

@end



#endif
