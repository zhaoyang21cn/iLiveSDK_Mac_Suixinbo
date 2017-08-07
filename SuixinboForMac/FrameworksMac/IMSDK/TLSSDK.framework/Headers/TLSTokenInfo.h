//
//  TLSTokenInfo.h
//  TLSSDK
//
//  Created by okhowang on 15/11/16.
//
//
#ifndef TLSSDK_TLSTLSTokenInfo_h
#define TLSSDK_TLSTLSTokenInfo_h
#import <Foundation/Foundation.h>

@interface TLSTokenInfo : NSObject
@property (retain) NSString* openid;
@property (retain) NSString* accessToken;
@property (retain) NSString* refreshToken;
@property (retain) NSString* scope;
@property (retain) NSString* unionid;
@property (retain) NSDate* expireTime;
@end
#endif
