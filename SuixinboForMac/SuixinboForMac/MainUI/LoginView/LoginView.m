//
//  LoginView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LoginView.h"

@implementation LoginView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)awakeFromNib {
    self.layer.backgroundColor = CGColorCreateGenericRGB(67.0/256.0, 67.0/256.0, 67.0/256.0, 0.2);
}

- (void)show {
    [self autoFillLoginParam];
    self.window.title = @"Mac随心播_登录";
    self.hidden = NO;
}

- (void)hide {
    self.hidden = YES;
}


- (BOOL)isInputInvalid {
    
    if (_accountTF.stringValue.length <= 0 || _passwardTF.stringValue.length <= 0) {
        return YES;
    }
    if ([self invalidAccount:_accountTF.stringValue] || [self invalidPwd:_passwardTF.stringValue])
    {
        return YES;
    }
    return NO;
}

//用户名为4～24个字符，不能为纯数字
- (BOOL)invalidAccount:(NSString *)account
{
    if (account.length < 4 || account.length > 24)
    {
        return YES;
    }
    
    NSString *inputString = [account stringByTrimmingCharactersInSet:[NSCharacterSet decimalDigitCharacterSet]];
    if (inputString.length <= 0) {//是纯数字
        return YES;
    }
    else{
        return NO;
    }
}

//密码长度为8～16个字符
- (BOOL)invalidPwd:(NSString *)pwd
{
    if (pwd.length < 8 || pwd.length > 16)
    {
        return YES;
    }
    return NO;
}

- (IBAction)onLogin:(id)sender {
    
    if ([self isInputInvalid]) {
        [SuixinboAlert tipsWith:@"输入的账号或密码不合法" showTo:self.window];
        return;
    }
    ((NSButton *)sender).enabled = NO;
    NSString *identifier = _accountTF.stringValue;
    NSString *passward = _passwardTF.stringValue;
    __weak typeof(self) ws = self;
    //请求sig
    LoginRequest *sigReq = [[LoginRequest alloc] initWithHandler:^(BaseRequest *request) {
        LoginResponceData *responseData = (LoginResponceData *)request.response.data;
        [AppDelegate sharedInstance].token = responseData.token;
        [[ILiveLoginManager getInstance] iLiveLogin:identifier sig:responseData.userSig succ:^{
            ((NSButton *)sender).enabled = YES;
            NSLog(@"tillivesdkshow login succ");
            [ws saveLoginParamToLocal:identifier passward:passward];
            if ([ws.delegate respondsToSelector:@selector(loginComplete:code:msg:)]) {
                [ws.delegate loginComplete:nil code:0 msg:nil];
            }
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            ((NSButton *)sender).enabled = YES;
            if ([ws.delegate respondsToSelector:@selector(loginComplete:code:msg:)]) {
                [ws.delegate loginComplete:module code:errId msg:errMsg];
            }
            if (errId == 8050){//离线被踢,再次登录
                [ws onLogin:nil];
            }
            else{
                NSString *errInfo = [NSString stringWithFormat:@"module=%@,errid=%d,errmsg=%@",module,errId,errMsg];
                NSLog(@"login fail.%@",errInfo);
                [SuixinboAlert tipsWith:errInfo showTo:self.window];
            }
        }];
    } failHandler:^(BaseRequest *request) {
        ((NSButton *)sender).enabled = YES;
        NSString *errInfo = [NSString stringWithFormat:@"errid=%ld,errmsg=%@",(long)request.response.errorCode, request.response.errorInfo];
        NSLog(@"login fail.%@",errInfo);
        [SuixinboAlert tipsWith:errInfo showTo:self.window];
    }];
    sigReq.identifier = identifier;
    sigReq.pwd = passward;
    [[WebServiceEngine sharedEngine] asyncRequest:sigReq];
}

- (IBAction)onRegist:(id)sender {
    if ([self isInputInvalid]) {
        [SuixinboAlert tipsWith:@"账号或密码不合法" showTo:self.window];
        return;
    }
    ((NSButton *)sender).enabled = NO;
    //向业务后台注册
    RegistRequest *registReq = [[RegistRequest alloc] initWithHandler:^(BaseRequest *request) {
        ((NSButton *)sender).enabled = YES;
        [SuixinboAlert tipsWith:@"注册成功" showTo:self.window];
    } failHandler:^(BaseRequest *request) {
        ((NSButton *)sender).enabled = YES;
        NSString *errinfo = [NSString stringWithFormat:@"errid=%ld,errmsg=%@",(long)request.response.errorCode,request.response.errorInfo];
        NSLog(@"regist fail.%@",errinfo);
        [SuixinboAlert tipsWith:errinfo showTo:self.window];
    }];
    registReq.identifier = _accountTF.stringValue;
    registReq.pwd = _passwardTF.stringValue;
    [[WebServiceEngine sharedEngine] asyncRequest:registReq];
}

- (void)autoFillLoginParam
{
    NSDictionary *dic = [self getLocalLoginParam];
    if (dic)
    {
        NSString *identifier = [dic objectForKey:kLoginIdentifier];
        NSString *passward = [dic objectForKey:kLoginPassward];
        if (identifier.length > 0 && passward.length > 0)
        {
            _accountTF.stringValue = identifier;
            _passwardTF.stringValue = passward;
        }
    }
}

- (void)saveLoginParamToLocal:(NSString *)identifier passward:(NSString *)pwd{
    NSMutableDictionary *loginParam = [NSMutableDictionary dictionary];
    [loginParam setObject:identifier forKey:kLoginIdentifier];
    [loginParam setObject:pwd forKey:kLoginPassward];
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:loginParam forKey:kLoginParam];
}

- (NSDictionary *)getLocalLoginParam{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *dic = [userDefaults objectForKey:kLoginParam];
    return dic;
}

@end
