//
//  LiveWindowController+ImListener.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/8.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+ImListener.h"
#import "LiveWindowController+Tools.h"

@implementation LiveWindowController (ImListener)
- (void)onNewMessage:(NSArray *)msgs
{
    if (msgs.count <= 0){
        return;
    }
    TIMMessage *msg = msgs[0];
    if (msg.elemCount <= 0) {
        return;
    }
    TIMElem *elem = [msg getElem:0];
    
    BOOL isCustom = [NSStringFromClass(elem.class) isEqualToString:NSStringFromClass([TIMCustomElem class])];
    //[elem isKindOfClass:[TIMCustomElem class]];//奇怪的问题，在这里用isKondOfClass总是返回NO
    if (isCustom) {//自定义消息
        TIMCustomElem *customElem = (TIMCustomElem *)elem;
        
        NSError *error = nil;
        NSDictionary *dataDic = [NSJSONSerialization JSONObjectWithData:customElem.data options:NSJSONReadingAllowFragments error:&error];
        if(error != nil){
            //            [self addLog:@"recvMsg: 解析消息失败 pos_1"];
            return;
        }
        if([dataDic allKeys].count != 2 || ![dataDic objectForKey:kMsgCmdKey] || ![dataDic objectForKey:kMsgDataKey]){
            //            [self addLog:@"recvMsg: 解析消息失败 pos_2"];
            return;
        }
        ShowCustomCmd cmd = (ShowCustomCmd)[[dataDic objectForKey:kMsgCmdKey] integerValue];
        switch (cmd){
            case AVIMCMD_Multi_Host_Invite:
                [self onRecvInviteMsg:msg.sender];
                break;
            case AVIMCMD_Multi_Interact_Refuse:
            {
                NSString *log = [NSString stringWithFormat:@"%@拒绝了你的连麦邀请",msg.sender];
                [self addLog:log];
            }
                break;
            case AVIMCMD_Multi_Host_CancelInvite:
            {
                break;
            }
            case AVIMCMD_Multi_CancelInteract:
            {
                NSString *recvId = (NSString *)[dataDic objectForKey:kMsgDataKey];
                NSString *selfId = [[ILiveLoginManager getInstance] getLoginId];
                if ([recvId isEqualToString:selfId]) {
//                    [self downCameraVideo:nil fail:nil];
                    __weak typeof(self) ws = self;
                    [self downCameraVideo:^{
                        [ws setGuestUI];
                    } fail:^(NSString *module, int errId, NSString *errMsg) {
                        [ws setGuestUI];
                    }];
                }
            }
                break;
            case AVIMCMD_ExitLive:
                [self hostLeaveRoom];
                break;
//            case ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT:
//                [self onRecvLimitMsg:dataDic];
//                break;
            case AVIMCMD_EnterLive:
            {
                NSString *log = [NSString stringWithFormat:@"%@加入房间",msg.sender];
                [self addLog:log];
            }
                break;
            default:
                break;
        }
    }
    else if ([elem isKindOfClass:[TIMTextElem class]]) {
        TIMTextElem *textElem = (TIMTextElem *)elem;
        NSString *showTextInfo = [NSString stringWithFormat:@"%@: %@",msg.sender, textElem.text];
        self.messageCount++;
        [self insertMessageToUI:showTextInfo];
    }
}

- (void)onRecvInviteMsg:(NSString *)sender
{
    [self addLog:[NSString stringWithFormat:@"recvMsg:收到%@的连麦邀请",sender]];
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"上麦"];
    [alert addButtonWithTitle:@"拒绝"];
    [alert setMessageText:[NSString stringWithFormat:@"收到来自%@的连麦邀请",sender]];
    [alert setAlertStyle:NSAlertStyleInformational];
    NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
    [alert setAccessoryView:view];
    NSModalResponse response = [alert runModal];
    if (response == NSAlertFirstButtonReturn) {
        __weak typeof(self) ws = self;
        [self upCameraVideo:^{
            [ws setUpVideoUI];
        } fail:nil];
    }
    else if (response == NSAlertSecondButtonReturn) {//拒绝
        [self rejectToVideo:sender];
    }
}

//拒绝上麦
- (void)rejectToVideo:(id)sender
{
    [self sendCustomC2CMessage:NO recvId:sender cmd:(ILVLiveIMCmd)AVIMCMD_Multi_Interact_Refuse succ:^{

    } fail:^(NSString *module, int errId, NSString *errMsg) {

    }];
}

- (void)onRecvLimitMsg:(NSDictionary *)dataDic
{
    NSObject *obData = [dataDic objectForKey:kMsgDataKey];
    if([obData isKindOfClass:[NSString class]]){//本例中只有nsstring
        //        [self addLog:[NSString stringWithFormat:@"recvMsg:cmd=%d,text=%@",ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,(NSString *)obData]];
    }
}

- (void)hostLeaveRoom
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"退出"];
    [alert setMessageText:@"主播已经离开房间"];
    [alert setAlertStyle:NSAlertStyleInformational];
    NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
    [alert setAccessoryView:view];
    [alert.window setFrame:NSMakeRect(0, 0, 210, 60) display:YES animate:YES];
    if ([alert runModal] == NSAlertFirstButtonReturn)
    {
        [self onExitLive:nil];
    }
}
@end
