//
//  MainView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/26.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "MainView.h"
#import "LiveListCellView.h"

@implementation MainView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)awakeFromNib {
    self.layer.backgroundColor = CGColorCreateGenericRGB(67.0/256.0, 67.0/256.0, 67.0/256.0, 0.2);
    [_liveListTableView setTarget:self];
    [_liveListTableView setDoubleAction:NSSelectorFromString(@"doubleClickRow:")]; //setDoubleAction双击选择事件
    __weak typeof(self) ws = self;
    _userHeadImageView.logoutBlock = ^(NSString *module,int code, NSString *msg){
        if (self.delegate && [self.delegate respondsToSelector:@selector(logoutComplete:code:msg:)]) {
            [ws.delegate logoutComplete:module code:code msg:msg];
        }
    };
    _userHeadImageView.logoutBeforeBlock = ^(){
        if (ws.liveWC && [[ILiveRoomManager getInstance] getRoomId]) {//登出时正在直播或正在观看
            [ws.liveWC onExitLive:nil];
        }
    };
}

- (void)show {
    self.window.title = @"Mac随心播_直播列表";
    NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
    _curLoginUserTF.stringValue = loginId;
    [self loadLiveList];
    self.hidden = NO;
}

- (void)hide {
    self.hidden = YES;
}

#pragma mark - create room
- (IBAction)onCreateRoom:(NSButton *)sender {
    //判断当前是否在房间中
    if ([self isInRoom])
    {
        [SuixinboAlert tipsWith:@"当前正在房间中，不能同时存在于两个房间中，请退出后再操作"];
        return;
    }
    _createRoomWC = [[CreateRoomWC alloc] initWithWindowNibName:@"CreateRoomWC"];
    _createRoomWC.delegate = self;
    
    [_createRoomWC.window orderFront:nil];
}

- (void)createRoom:(TCShowLiveListItem *)item config:(LiveRommConfig *)config {
    [_createRoomWC.window close];
    [_createRoomWC.window orderOut:nil];
    
    _liveWC = [[LiveWindowController alloc] initWithWindowNibName:@"LiveWindowController"];
    _liveWC.item = item;
    _liveWC.config = config;
    _liveWC.roomOptionType = RoomOptionType_CrateRoom;
    _liveWC.isHost = YES;
    [_liveWC.window orderFront:nil];
}

//挡墙是否正在房间中
- (BOOL)isInRoom
{
    if (_liveWC && [[ILiveRoomManager getInstance] getRoomId] > 0) {//在房间中
        return YES;
    }
    return NO;
}

#pragma mark - refresh live list
- (IBAction)onRefresh:(NSButton *)sender {
    if (!_recordListView || _recordListView.hidden) {
        [self loadLiveList];
    }
    else {
        [self loadRecordList];
    }
}

- (void)loadLiveList{
    __weak typeof(self) ws = self;
    //向业务后台请求直播间列表
    RoomListRequest *listReq = [[RoomListRequest alloc] initWithHandler:^(BaseRequest *request) {
        RoomListRequest *wreq = (RoomListRequest *)request;
        RoomListRspData *respData = (RoomListRspData *)wreq.response.data;
        if (ws.datas) {
            [ws.datas removeAllObjects];
        }
        else{
            ws.datas = [NSMutableArray array];
        }
        [ws.datas addObjectsFromArray:respData.rooms];
        [ws.liveListTableView reloadData];
    } failHandler:^(BaseRequest *request) {
        NSString *errinfo = [NSString stringWithFormat:@"errid=%ld,errmsg=%@",(long)request.response.errorCode,request.response.errorInfo];
        NSLog(@"regist fail.%@",errinfo);
        [SuixinboAlert tipsWith:errinfo showTo:ws.window];
    }];
    listReq.token = [AppDelegate sharedInstance].token;
    listReq.type = @"live";
    listReq.index = 0;
    listReq.size = 20;
    listReq.appid = SuixinboSdkAppId;
    [[WebServiceEngine sharedEngine] asyncRequest:listReq wait:YES];
}

- (void)loadRecordList {
    __weak typeof(self) ws = self;
    RecordListRequest *recListReq = [[RecordListRequest alloc] initWithHandler:^(BaseRequest *request) {
        RecordListResponese *recordRsp = (RecordListResponese *)request.response;
        [ws.recordListView.datas removeAllObjects];
        [ws.recordListView.datas addObjectsFromArray:recordRsp.videos];
        dispatch_async(dispatch_get_main_queue(), ^{
            [ws.recordListView.recordListTableView reloadData];
        });
        NSLog(@"--->%ld",(long)recordRsp.total);
        if (ws.recordListView.datas.count >= recordRsp.total)
        {
        }
    } failHandler:^(BaseRequest *request) {
        NSLog(@"fail");
    }];
    recListReq.token = [AppDelegate sharedInstance].token;
    recListReq.type = 0;
    recListReq.index = 1;
    recListReq.size =  _recordListView.numberTF.stringValue ? [_recordListView.numberTF.stringValue integerValue] : 15;
    recListReq.uid = _recordListView.acountTF.stringValue ? _recordListView.acountTF.stringValue : @"";
    [[WebServiceEngine sharedEngine] asyncRequest:recListReq wait:NO];
}

#pragma mark - record list
- (IBAction)onRecordList:(NSButton *)sender {
    if ([sender.title isEqualToString:@"观看回放"]) {
        [sender setTitle:@"返回"];
        if (!_recordListView) {
            NSArray *recordListObjects = [[NSArray alloc] init];;
            if ([[NSBundle mainBundle] loadNibNamed:@"RecordListView" owner:nil topLevelObjects:&recordListObjects]) {
                for (id item in recordListObjects) {
                    if ([item isKindOfClass:[RecordListView class]]) {
                        _recordListView = item;
                    }
                }
                [_recordListView config];
                [self addSubview:_recordListView];
            }
        }
        _liveListTableView.hidden = YES;
        _recordListView.hidden = NO;
        self.window.title = @"Mac随心播_录制列表";
    }
    else {
        [sender setTitle:@"观看回放"];
        _liveListTableView.hidden = NO;
        _recordListView.hidden = YES;
        self.window.title = @"Mac随心播_直播列表";
    }
}

#pragma mark - log report
- (IBAction)onLogReport:(NSButton *)sender {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"上报"];
    [alert addButtonWithTitle:@"取消"];
    [alert setMessageText:@"输入消息内容"];
    [alert setAlertStyle:NSAlertStyleInformational];
    
    NSView *logView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 210, 56)];
    NSTextField *offset = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 210, 24)];
    offset.placeholderString = @"0-当天，1-昨天，2-前天，以此类推";
    offset.stringValue = @"0";
    [logView addSubview:offset];
    NSTextField *desc = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 28, 210, 24)];
    desc.placeholderString = @"日志描述";
    desc.stringValue = @"Mac_随心播_LOG主动上报";
    [logView addSubview:desc];
    
    [alert setAccessoryView:logView];
    [alert.window setFrame:NSMakeRect(0, 0, 210, 60) display:YES animate:YES];
    if ([alert runModal] == NSAlertFirstButtonReturn)
    {
        [[ILiveSDK getInstance] uploadLog:desc.stringValue logDayOffset:[offset intValue] uploadResult:^(int retCode, NSString *retMsg, NSString *logKey) {
            NSLog(@"--->");
            if (retCode == 0) {
                [SuixinboAlert alertWith:@"日志上报成功" msg:logKey funBtns:@[@"复制Key",@"取消"] showTo:self.window completeHanler:^(NSModalResponse returnCode) {
                    if (returnCode == NSAlertFirstButtonReturn) {
                        NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
                        [pasteboard clearContents];
                        [pasteboard setString:logKey forType:NSPasteboardTypeString];
                    }
                }];
            }
            else {
                [SuixinboAlert tipsWith:[NSString stringWithFormat:@"日志上报失败:code=%d,Msg=%@",retCode,retMsg]];
            }
        }];
    }
}

#pragma mark - sdk version
- (IBAction)onVersion:(NSButton *)sender {
    NSString *iliveSDKVer = [NSString stringWithFormat:@"iLiveSDK: %@\n",[[ILiveSDK getInstance] getVersion]];
    NSString *imSDKVer = [NSString stringWithFormat:@"ImSDK: %@\n",[[TIMManager sharedInstance] GetVersion]];
    NSString *avSDKVer = [NSString stringWithFormat:@"QAVSDK: %@",[QAVContext getVersion]];
    NSString *version = [NSString stringWithFormat:@"%@%@%@",iliveSDKVer,imSDKVer,avSDKVer];
    [SuixinboAlert tipsWith:version];
}


#pragma mark - table view delegate
-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView{
    return _datas.count;
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
    return 100;
}

- (NSView *)tableView:(NSTableView*)tableView viewForTableColumn:(NSTableColumn*)tableColumn row:(NSInteger)row{
    LiveListCellView *cellView = [tableView makeViewWithIdentifier:@"LiveListCellViewID" owner:self];
    [cellView configWith:_datas[row]];
    return cellView;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
    return nil;
}

- (BOOL)tabView:(NSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    NSLog(@"");
    return YES;
}

//双击开始观看直播
- (void)doubleClickRow:(id)sender {
    //判断当前是否在房间中
    if ([self isInRoom])
    {
        [SuixinboAlert tipsWith:@"当前正在房间中，不能同时存在于两个房间中，请退出后再操作"];
        return;
    }
    _liveWC = [[LiveWindowController alloc] initWithWindowNibName:@"LiveWindowController"];
    NSInteger rowNumber = [_liveListTableView clickedRow];
    TCShowLiveListItem *item = _datas[rowNumber];
    _liveWC.item = item;
    LiveRommConfig *config = [[LiveRommConfig alloc] init];
    config.isAutoOpenMic = NO;
    config.cameraDesc = kCameraDesc;
    config.isAutoOpenSpeaker = YES;
    _liveWC.config = config;
    
    _liveWC.roomOptionType = RoomOptionType_JoinRoom;
    _liveWC.isHost = NO;
    [_liveWC.window orderFront:nil];
}
@end
