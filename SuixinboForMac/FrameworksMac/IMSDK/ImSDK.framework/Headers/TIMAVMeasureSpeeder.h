//
//  TIMAVMeasureSpeeder.h
//
//  Created by AlexiChen on 15/7/29.
//  Copyright (c) 2015年 bodeng. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#import "IMSdkComm.h"

@class TIMAVMeasureSpeeder;

@class TIMAVMeasureProgressItem;


@protocol TIMAVMeasureSpeederDelegate <NSObject>


@optional

// 请求测速失败
- (void)onAVMeasureSpeedRequestFailed:(TIMAVMeasureSpeeder *)avts;

// 请求测速成功
- (void)onAVMeasureSpeedRequestSucc:(TIMAVMeasureSpeeder *)avts;

// UDP未成功创建
- (void)onAVMeasureSpeedPingFailed:(TIMAVMeasureSpeeder *)avts;

// 开始拼包
- (void)onAVMeasureSpeedStarted:(TIMAVMeasureSpeeder *)avts;

//测速进度
- (void)onAVMeasureSpeedProgress:(TIMAVMeasureProgressItem *)item;

// 发包结束
// isByUser YES, 用户手动取消 NO : 收完所有包或内部超时自动返回
- (void)onAVMeasureSpeedPingCompleted:(TIMAVMeasureSpeeder *)avts byUser:(BOOL)isByUser;

@end



@interface TIMAVMeasureSpeeder : NSObject

@property (nonatomic, weak) id<TIMAVMeasureSpeederDelegate> delegate;

// 超时时间
// 默认是60s，该时间内没完成，自动回调onAVSpeedTestThreadCompleted:NO
@property (nonatomic, assign) NSUInteger timeout;

// 请求测速
- (void)requestMeasureSpeedWith:(short)bussType authType:(short)authType;

// 取消本次测速，并且自动提交
- (void)cancelMeasureSpeed;

//获取测试结果，每台接口机的测试结果 TIMAVMeasureSpeederItem 数组
- (NSMutableArray *)getMeasureResult;

//上报测速结果
- (void)reportMeasureResult:(OMRequestSucc)succ fail:(OMRequsetFail)fail;

@end


@interface TIMAVMeasureSpeederItem : NSObject

//接口机PORT
@property (nonatomic, assign) unsigned short interfacePort;

//接口机IP
@property (nonatomic, assign) unsigned int interfaceIP;

//归属地
@property (nonatomic, strong) NSString   *idc;

//运营商
@property (nonatomic, assign) NSString   *isp;

//发包数
@property (nonatomic, assign) unsigned int sendPkgNum;

//收包数
@property (nonatomic, assign) unsigned int recvPkgNum;

//平均时延
@property (nonatomic, assign) NSUInteger averageDelay;

@end

@interface TIMAVMeasureProgressItem : NSObject

//已收到
@property (nonatomic, assign) unsigned int recvPkgNum;

//应发包总数
@property (nonatomic, assign) unsigned int totalPkgNum;

@end

