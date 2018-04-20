//
//  LiveWindowController+MemberList.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController+MemberList.h"
#import "LiveWindowController+Tools.h"
#import "MemberCellView.h"
#import "RenderViewManager.h"

@implementation LiveWindowController (MemberList)

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView{
    if (tableView == self.memberTableView) {
        return self.members.count;
    }
    else {
        return 0;
    }
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
    return 25;
}

- (NSView *)tableView:(NSTableView*)tableView viewForTableColumn:(NSTableColumn*)tableColumn row:(NSInteger)row{
    MemberCellView *cellView = [tableView makeViewWithIdentifier:@"MemberCellViewID" owner:self];
    if (self.members.count > row) {
        MemberListItem *item = [self.members objectAtIndex:row];
        [cellView config:item];
    }
    return cellView;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
    return nil;
}

- (BOOL)tabView:(NSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem {

    return YES;
}

- (void)menuNeedsUpdate:(NSMenu*)menu {
    NSInteger row = [self.memberTableView clickedRow];
    if (self.members.count <= row) {
        return;
    }
    MemberListItem *memberItem = [self.members objectAtIndex:row];
    if (self.isHost) {
        NSMenuItem *item = nil;
        if ([menu itemArray].count <= 0) {
            item = [[NSMenuItem alloc] init];
            item.action = @selector(onMemberRightMenuItem:);
            [menu addItem:item];
        }
        else {
            item = [menu itemAtIndex:0];
        }
        //如果主播点击的是自己，则不做响应
        NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
        if ([memberItem.identifier isEqualToString:loginId]) {
            [menu removeAllItems];
            return;
        }
        if ([[RenderViewManager shareInstance] isUpVideo:memberItem.identifier]) {
            item.title = @"下麦";
        }
        else {
            item.title = @"上麦";
        }
        
        item.tag = row;
    }
    else {//观众只有点击自己，且自己正在上麦，才有右键操作
        NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
        if ([memberItem.identifier isEqualToString:loginId]) {
            if ([[RenderViewManager shareInstance] isUpVideo:loginId]) {
                NSMenuItem *item = nil;
                if ([menu itemArray].count <= 0) {
                    item = [[NSMenuItem alloc] init];
                    item.action = @selector(onMemberRightMenuItem:);
                    [menu addItem:item];
                }
                else {
                    item = [menu itemAtIndex:0];
                }
                item.title = @"下麦";
                item.tag = row;
            }
            else {
                [menu removeAllItems];
            }
            return;
        }
        if ([menu itemArray].count > 0) {
            [menu removeAllItems];
        }
    }
}

- (void)onMemberRightMenuItem:(NSMenuItem *)item {
    __weak typeof(self) ws = self;
    if (self.members.count > item.tag) {
        MemberListItem *memberItem = [self.members objectAtIndex:item.tag];

        if (self.isHost)
        {
            NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
            if ([memberItem.identifier isEqualToString:loginId]) {
                return;
            }
            
            if (![[RenderViewManager shareInstance] isUpVideo:memberItem.identifier]) {
                [self sendCustomC2CMessage:YES recvId:memberItem.identifier cmd:(ILVLiveIMCmd)AVIMCMD_Multi_Host_Invite succ:^{
                    [ws addLog:@"发送连麦邀请成功"];
                } fail:^(NSString *module, int errId, NSString *errMsg) {
                    [ws addLog:[NSString stringWithFormat:@"发送连麦邀请失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
                }];
            }
            else {
                [self sendCustomGroupMessage:NO recvId:memberItem.identifier cmd:(ILVLiveIMCmd)AVIMCMD_Multi_CancelInteract succ:^{
                    [ws addLog:@"发送下麦消息成功"];
                } fail:^(NSString *module, int errId, NSString *errMsg) {
                    [ws addLog:[NSString stringWithFormat:@"发送下麦失败,M=%@,code=%d,Msg=%@",module,errId,errMsg]];
                }];
            }
        }
        else {//如果是观众，必定是下麦操作(其它情况不会有右键操作，已经在menuNeedsUpdate做判断了)
            [self downCameraVideo:^{
                [ws setGuestUI];
            } fail:^(NSString *module, int errId, NSString *errMsg) {
            }];
        }
    }
}
@end
