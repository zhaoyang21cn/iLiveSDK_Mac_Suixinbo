//
//  ClickSelfHeadImageView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "ClickSelfHeadImageView.h"

@implementation ClickSelfHeadImageView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)mouseDown:(NSEvent *)theEvent{
    NSInteger clickCount = [theEvent clickCount];
    if (clickCount == 1) {
        [self onClick];
    }
}

- (void)onClick{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"退出登录"];
    [alert addButtonWithTitle:@"取消"];
    [alert setMessageText:@"确定退出登录吗"];
    [alert setAlertStyle:NSAlertStyleInformational];
    NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
    [alert setAccessoryView:view];
    
    [alert beginSheetModalForWindow:[self window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn) {
            [self logout];
        }
    }];
}

- (void)logout{
    if (self.logoutBeforeBlock) {
        self.logoutBeforeBlock();
    }
    __weak typeof(self) ws = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //通知业务服务器登出
        LogoutRequest *logoutReq = [[LogoutRequest alloc] initWithHandler:^(BaseRequest *request) {
            [[ILiveLoginManager getInstance] iLiveLogout:^{
                [ws deleteLoginParamFromLocal];
                if (ws.logoutBlock) {
                    ws.logoutBlock(nil,0,nil);
                }
            } failed:^(NSString *module, int errId, NSString *errMsg) {
                if (ws.logoutBlock) {
                    ws.logoutBlock(module,errId,errMsg);
                }
                NSString *errinfo = [NSString stringWithFormat:@"module=%@,errid=%ld,errmsg=%@",module,(long)request.response.errorCode,request.response.errorInfo];
                NSLog(@"regist fail.%@",errinfo);
                [SuixinboAlert tipsWith:errinfo showTo:[self window]];
            }];
        } failHandler:^(BaseRequest *request) {
            NSString *errinfo = [NSString stringWithFormat:@"errid=%ld,errmsg=%@",(long)request.response.errorCode,request.response.errorInfo];
            NSLog(@"regist fail.%@",errinfo);
            [SuixinboAlert tipsWith:errinfo showTo:[self window]];
        }];
        logoutReq.token = [AppDelegate sharedInstance].token;
        [[WebServiceEngine sharedEngine] asyncRequest:logoutReq];
    });
}

- (void)deleteLoginParamFromLocal{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults removeObjectForKey:kLoginParam];
}

@end
