//
//  LoginView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol LoginViewDelegate <NSObject>

- (void)loginComplete:(NSString *)module code:(int)code msg:(NSString *)msg;

@end

/**
  登录视图（登出事件在ClickSelfHeadImageView中响应）
 */
@interface LoginView : NSView

@property (strong) IBOutlet NSTextField *accountTF;//用户名输入框
@property (strong) IBOutlet NSSecureTextField *passwardTF;//密码输入框
@property (weak) id<LoginViewDelegate>   delegate;

- (void)show;
- (void)hide;
@end
