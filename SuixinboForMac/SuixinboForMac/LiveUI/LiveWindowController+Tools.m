//
//  LiveWindowController+Tools.m
//  LiveDemoForMac
//
//  Created by wilderliao on 2017/5/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+Tools.h"

@implementation LiveWindowController (Tools)

- (void)upCameraVideo:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail
{
    __weak typeof(self) ws = self;
    ILiveRoomManager *manager = [ILiveRoomManager getInstance];
    [manager changeRole:kSxbRole_InteractHD succ:^ {
        [ws addLog:@"上麦:改变角色成功"];
        [manager enableCamera:CameraPosFront enable:YES succ:^{
            [ws addLog:@"上麦:打开摄像头成功"];
            [manager enableMic:YES succ:^{
                [ws addLog:@"上麦:打开麦克风成功"];
                [ws addLog:@"上麦成功"];
                succ ? succ() : nil;
            } failed:^(NSString *module, int errId, NSString *errMsg) {
                [ws addLog:[NSString stringWithFormat:@"上麦:打开麦克风失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
                fail ? fail(module,errId,errMsg) : nil;
            }];
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            [ws addLog:[NSString stringWithFormat:@"上麦:打开摄像头失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
            fail ? fail(module,errId,errMsg) : nil;
        }];
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        [ws addLog:[NSString stringWithFormat:@"上麦:切换角色失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
        fail ? fail(module,errId,errMsg) : nil;
    }];
}

- (void)downCameraVideo:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail
{
    __weak typeof(self) ws = self;
    ILiveRoomManager *manager = [ILiveRoomManager getInstance];
    [manager changeRole:kSxbRole_GuestHD succ:^ {
        [ws addLog:@"下麦:改变角色成功"];
        cameraPos pos = [[ILiveRoomManager getInstance] getCurCameraPos];
        [manager enableCamera:pos enable:NO succ:^{
            [ws addLog:@"下麦:关闭摄像头成功"];
            succ ? succ() : nil;
            [manager enableMic:NO succ:^{
                [ws addLog:@"下麦:关闭麦克风成功"];
                [ws addLog:@"下麦成功"];
                succ ? succ() : nil;
            } failed:^(NSString *module, int errId, NSString *errMsg) {
                [ws addLog:[NSString stringWithFormat:@"下麦:关闭麦克风失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
                fail ? fail(module,errId,errMsg) : nil;
            }];
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            [ws addLog:[NSString stringWithFormat:@"下麦:关闭摄像头失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
            fail ? fail(module,errId,errMsg) : nil;
        }];
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        [ws addLog:[NSString stringWithFormat:@"下麦:切换角色失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
        fail ? fail(module,errId,errMsg) : nil;
    }];
}

- (void)sendCustomC2CMessage:(BOOL)isOnline recvId:(NSString *)recvId cmd:(ILVLiveIMCmd)cmd succ:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail
{
    //消息组装
    //如果将nsdata类型作为dictionary的value，序列化会崩溃
    NSString *dataStr = @"";//[[NSString alloc] initWithData:msg.data encoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *sendDic = [NSDictionary dictionaryWithObjectsAndKeys:@(cmd), kMsgCmdKey, dataStr, kMsgDataKey,nil];
    NSData *sendData = [NSJSONSerialization dataWithJSONObject:sendDic options:NSJSONWritingPrettyPrinted error:&error];
    if(error != nil){
        [self addLog:[NSString stringWithFormat:@"发送消息失败:code=%ld",error.code]];
        return;
    }
    
    TIMCustomElem *imCustomElem = [[TIMCustomElem alloc] init];
    [imCustomElem setData:sendData];
    TIMMessage *imMessage = [[TIMMessage alloc] init];
    [imMessage addElem:imCustomElem];
    __weak typeof(self) ws = self;
    if (isOnline) {
        [[ILiveRoomManager getInstance] sendOnlineC2CMessage:recvId message:imMessage succ:^{
//            [ws addLog:@"发送连麦邀请成功"];
            succ ? succ() : nil;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            fail ? fail(module,errId,errMsg) : nil;
            [ws addLog:[NSString stringWithFormat:@"发送连麦邀请失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
        }];
    }
    else{
        [[ILiveRoomManager getInstance] sendC2CMessage:recvId message:imMessage succ:^{
//            [ws addLog:@"发送连麦邀请成功"];
            succ ? succ() : nil;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            fail ? fail(module,errId,errMsg) : nil;
            [ws addLog:[NSString stringWithFormat:@"发送连麦邀请失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
        }];
    }
    
}

- (void)sendCustomGroupMessage:(BOOL)isOnline recvId:(NSString *)recvId cmd:(ILVLiveIMCmd)cmd succ:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail {
    //如果将nsdata类型作为dictionary的value，序列化会崩溃
    NSString *dataStr = recvId;//[[NSString alloc] initWithData:msg.data encoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *sendDic = [NSDictionary dictionaryWithObjectsAndKeys:@(cmd), kMsgCmdKey, dataStr, kMsgDataKey,nil];
    NSData *sendData = [NSJSONSerialization dataWithJSONObject:sendDic options:NSJSONWritingPrettyPrinted error:&error];
    if(error != nil){
                [self addLog:[NSString stringWithFormat:@"发送消息失败:code=%ld",error.code]];
        return;
    }
    
    TIMCustomElem *imCustomElem = [[TIMCustomElem alloc] init];
    [imCustomElem setData:sendData];
    TIMMessage *imMessage = [[TIMMessage alloc] init];
    [imMessage addElem:imCustomElem];
    
    if (isOnline) {
        [[ILiveRoomManager getInstance] sendOnlineGroupMessage:imMessage succ:^{
            succ ? succ() : nil;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            fail ? fail(module,errId,errMsg) : nil;
        }];
    }
    else {
        [[ILiveRoomManager getInstance] sendGroupMessage:imMessage succ:^{
            succ ? succ() : nil;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            fail ? fail(module,errId,errMsg) : nil;
        }];
    }
}
@end
