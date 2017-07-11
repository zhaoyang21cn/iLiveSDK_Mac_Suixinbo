//
//  ClickSelfHeadImageView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

typedef void(^LogoutBeforeBlock)();//登出之前需要做的操作
typedef void(^LogoutBlock)(NSString *module,int code, NSString *msg);

/**
 点击登录用户的头像，事件响应(右上角)
 */
@interface ClickSelfHeadImageView : NSImageView

@property (nonatomic, copy) LogoutBlock logoutBlock;
@property (nonatomic, copy) LogoutBeforeBlock logoutBeforeBlock;
@end
