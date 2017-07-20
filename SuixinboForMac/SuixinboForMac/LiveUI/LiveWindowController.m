//
//  LiveWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/19.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveWindowController.h"
#import "LiveWindowController+AVListener.h"
#import "LiveWindowController+Audio.h"
#import "LiveWindowController+ImListener.h"
#import "LiveWindowController+MemberList.h"
#import "LiveWindowController+Tools.h"
#import "LiveWindowController+Beauty.h"
#import "RenderViewManager.h"
#import "CreateRoomWC.h"

@interface LiveWindowController ()

@end

@implementation LiveWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
//     Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    self.window.title = [NSString stringWithFormat:@"%@ 的直播", _item.uid];
    
    [self initLive];
    [self enterRoom];
    [self startLiveTimer];
    //进入房间，上报成员id
    [self reportMemberId:_item.info.roomnum operate:0];
    _members = [NSMutableArray array];
    _messageCount = 0;
    
    _memberTableView.delegate = self;
    _memberTableView.dataSource = self;
    
    _messageTF.delegate = self;
    
    //成员列表，右键菜单
    NSMenu *menu = [[NSMenu alloc] init];
    menu.delegate = self;
    
    _memberTableView.menu = menu;
    
    _tilFilter = [[TILFilter alloc] init];
}

- (void)initLive{
    [[[ILiveSDK getInstance] getTIMManager] addMessageListener:self];
    [[[ILiveSDK getInstance] getAVContext].audioCtrl setAudioDataEventDelegate:self];
//    [[[ILiveSDK getInstance] getAVContext].audioCtrl registerAudioDataCallback:QAVAudioDataSource_VoiceDispose];
//    [[[ILiveSDK getInstance] getAVContext].audioCtrl registerAudioDataCallback:QAVAudioDataSource_Play];
    //uninit todo
}

- (void)enterRoom {
    switch (_roomOptionType) {
        case RoomOptionType_CrateRoom:
        {
            [self createRoom];
            [self reportRoomInfo];
        }
            break;
        case RoomOptionType_JoinRoom:
        {
            [self joinRoom];
        }
            break;
        default:
            break;
    }
}

- (void)createRoom {
    //如果使用美颜sdk，需要设置本地画面代理，详情参考LiveWindowController+Beauty.m中的实现
    [[ILiveRoomManager getInstance] setLocalVideoDelegate:self];
    
    //开发者可以详细了解下option的各个参数配置，这很重要
    ILiveRoomOption *option = [ILiveRoomOption defaultHostLiveOption];
    option.controlRole = _item.info.roleName;       //这里填写开发者自己的账号系统下的角色名
    option.avOption.autoMic = _config.isAutoOpenMic;
    option.roomDisconnectListener = self;           //房间失去连接的回调通知
    option.memberStatusListener = self;             //房间内用户的事件回调
    __weak typeof(self) ws = self;
    [[ILiveRoomManager getInstance] createRoom:(int)_item.info.roomnum option:option succ:^{
        NSLog(@"succ");
        if (option.avOption.autoCamera) {
            [ws.openCameraBtn setTitle:@"关闭摄像头"];
        }
        [ws initUI];
        
        [[[ILiveSDK getInstance] getAVContext].audioCtrl registerAudioDataCallback:QAVAudioDataSource_VoiceDispose];
        [[[ILiveSDK getInstance] getAVContext].audioCtrl registerAudioDataCallback:QAVAudioDataSource_NetStream];
        
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        [ws onExitLive:nil];
        NSLog(@"createRoom fail,module=%@,code=%d,msg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"create room fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}

- (void)initUI {
    if (_isHost) {
        [self setHostUI];
    }
    else {
        [self setGuestUI];
    }
    _roomInfoWC = [[RoomInfoWindowController alloc] initWithWindowNibName:@"RoomInfoWindowController"];
    _roomInfoWC.isHost = _isHost;
    [_roomInfoWC.window orderFront:nil];
}

- (void)setHostUI {
    [_cameraComboBox addItemWithObjectValue:_config.cameraDesc];
    [_cameraComboBox selectItemAtIndex:0];
    
    if ([[ILiveRoomManager getInstance] getCurCameraState]) {
        [_openCameraBtn setTitle:@"关闭摄像头"];
    }
    else {
        [_openCameraBtn setTitle:@"打开摄像头"];
    }
    _openCameraBtn.enabled = YES;
    
    if ([[ILiveRoomManager getInstance] getCurMicState]) {
        [_openMicBtn setTitle:@"关闭麦克风"];
    }
    else {
        [_openMicBtn setTitle:@"打开麦克风"];
    }
    _openMicBtn.enabled = YES;
    
    if ([[ILiveRoomManager getInstance] getCurSpeakerState]) {
        [_openSpeakerBtn setTitle:@"关闭扬声器"];
    }
    else {
        [_openSpeakerBtn setTitle:@"打开扬声器"];
    }
    
    [_micSlider setContinuous:YES];
    _micSlider.intValue = [[ILiveSDK getInstance] getAVContext].audioCtrl.volume;
    _volume = [[ILiveSDK getInstance] getAVContext].audioCtrl.volume;
    
    [_beautySlider setContinuous:YES];
    [_whiteSlider setContinuous:YES];
    
    [_pushTypeComboBox addItemWithObjectValue:@"AV_ENCODE_HLS"];
    [_pushTypeComboBox addItemWithObjectValue:@"AV_ENCODE_RTMP"];
    [_pushTypeComboBox selectItemAtIndex:0];
    
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_HostHDTitle];
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_HostSDTitle];
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_HostLDTitle];
    
    if ([_config.roleDesc isEqualToString:kSxbRole_HostHDTitle]) {
        [_roleSwitchPopUpBtn selectItemAtIndex:0];
    }
    else if ([_config.roleDesc isEqualToString:kSxbRole_HostSDTitle]) {
        [_roleSwitchPopUpBtn selectItemAtIndex:1];
    }
    else {
        [_roleSwitchPopUpBtn selectItemAtIndex:2];
    }
}

- (void)setUpVideoUI {
    [_cameraComboBox addItemWithObjectValue:_config.cameraDesc];
    [_cameraComboBox selectItemAtIndex:0];
    
    if ([[ILiveRoomManager getInstance] getCurCameraState]) {
        [_openCameraBtn setTitle:@"关闭摄像头"];
    }
    else {
        [_openCameraBtn setTitle:@"打开摄像头"];
    }
    _openCameraBtn.enabled = YES;
    
    if ([[ILiveRoomManager getInstance] getCurMicState]) {
        [_openMicBtn setTitle:@"关闭麦克风"];
    }
    else {
        [_openMicBtn setTitle:@"打开麦克风"];
    }
    _openMicBtn.enabled = YES;
    
    if ([[ILiveRoomManager getInstance] getCurSpeakerState]) {
        [_openSpeakerBtn setTitle:@"关闭扬声器"];
    }
    else {
        [_openSpeakerBtn setTitle:@"打开扬声器"];
    }
    
    [_pushTypeComboBox addItemWithObjectValue:@"AV_ENCODE_HLS"];
    [_pushTypeComboBox addItemWithObjectValue:@"AV_ENCODE_RTMP"];
    [_pushTypeComboBox selectItemAtIndex:0];
    
    [_roleSwitchPopUpBtn removeAllItems];
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_InteractHDTitle];
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_InteractSDTitle];
    [_roleSwitchPopUpBtn addItemWithTitle:kSxbRole_InteractLDTitle];
    [_roleSwitchPopUpBtn selectItemAtIndex:0];
    _roleSwitchBtn.enabled = YES;
    
    _startPushBtn.enabled = YES;
    _startRecordBtn.enabled = YES;
    
    _whiteSlider.enabled = YES;
    _beautySlider.enabled = YES;
}

- (void)setGuestUI {
    _openCameraBtn.enabled = NO;
    _openMicBtn.enabled = NO;
    
    if ([[ILiveRoomManager getInstance] getCurSpeakerState]) {
        [_openSpeakerBtn setTitle:@"关闭扬声器"];
    }
    else {
        [_openSpeakerBtn setTitle:@"打开扬声器"];
    }
    
    _roleSwitchBtn.enabled = NO;
    _startPushBtn.enabled = NO;
    _startRecordBtn.enabled = NO;
    
    _whiteSlider.enabled = NO;
    _beautySlider.enabled = NO;
}

- (IBAction)onMicSlider:(NSSlider *)sender {
    _volume = sender.intValue;
}

- (void)reportRoomInfo
{
    ReportRoomRequest *reportReq = [[ReportRoomRequest alloc] initWithHandler:^(BaseRequest *request) {
        NSLog(@"-----> 上传成功");
        
    } failHandler:^(BaseRequest *request) {
        // 上传失败
        NSLog(@"-----> 上传失败");
        
        dispatch_async(dispatch_get_main_queue(), ^{
            NSString *errinfo = [NSString stringWithFormat:@"code=%ld,msg=%@",(long)request.response.errorCode,request.response.errorInfo];
            [SuixinboAlert tipsWith:errinfo showTo:self.window];
        });
    }];
    
    reportReq.token = [AppDelegate sharedInstance].token;
    
    reportReq.room = [[ShowRoomInfo alloc] init];
    reportReq.room.title = _item.info.title;
    reportReq.room.type = @"live";
    reportReq.room.roomnum = _item.info.roomnum;
    reportReq.room.groupid = _item.info.groupid;
    reportReq.room.cover = _item.info.cover.length > 0 ? _item.info.cover : @"";
    reportReq.room.appid = SuixinboSdkAppId;
    [[WebServiceEngine sharedEngine] asyncRequest:reportReq wait:NO];
}

- (void)joinRoom {
    //参数意义见创建房间
    //用户成功加入房间后，如果打开摄像头，则会收到onEndpointsUpdateInfo回调，在onEndpointsUpdateInfo回调中，添加上渲染视图即可
    __weak typeof(self) ws = self;
    ILiveRoomOption *option = [ILiveRoomOption defaultGuestLiveOption];
    option.controlRole = _item.info.roleName;
    option.memberStatusListener = self;
    [[ILiveRoomManager getInstance] joinRoom:(int)_item.info.roomnum option:option succ:^{
        NSLog(@"succ");
        [ws initUI];
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        [ws onExitLive:nil];
        NSLog(@"joinRoom fail,module=%@,code=%d,msg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"join room fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}

- (void)test
{
    ILiveRoomOption *option = [ILiveRoomOption defaultHostLiveOption];
    option.controlRole = @"LiveMaster";
    option.memberStatusListener = self;
    [[ILiveRoomManager getInstance] createRoom:100100 option:option succ:^{
        NSLog(@"succ");
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        NSLog(@"fail");
    }];
}

- (IBAction)onCamera:(NSButton *)sender {
//    [self test];
    static BOOL isEnableIng = NO;//控制快速点击
    if (!isEnableIng) {
        isEnableIng = YES;
        BOOL isEnable = NO;
        if ([sender.title isEqualToString:@"打开摄像头"]) {
            isEnable = YES;
        }
        else {
            isEnable = NO;
        }
        [[ILiveRoomManager getInstance] enableCamera:CameraPosFront enable:isEnable succ:^{
            if (isEnable) {
                [sender setTitle:@"关闭摄像头"];
            }
            else {
                [sender setTitle:@"打开摄像头"];
            }
            isEnableIng = NO;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            isEnableIng = NO;
            NSLog(@"camera option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
            NSString *failInfo = [NSString stringWithFormat:@"camera option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
            [SuixinboAlert tipsWith:failInfo];
        }];
    }
}

- (IBAction)onOpenMic:(NSButton *)sender {
    static BOOL isEnableIng = NO;//控制快速点击
    if (!isEnableIng) {
        isEnableIng = YES;
        BOOL isEnable = NO;
        if ([sender.title isEqualToString:@"打开麦克风"]) {
            isEnable = YES;
        }
        else {
            isEnable = NO;
        }
        [[ILiveRoomManager getInstance] enableMic:isEnable succ:^{
            if (isEnable) {
                [sender setTitle:@"关闭麦克风"];
            }
            else {
                [sender setTitle:@"打开麦克风"];
            }
            isEnableIng = NO;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            isEnableIng = NO;
            NSLog(@"mic option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
            NSString *failInfo = [NSString stringWithFormat:@"mic option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
            [SuixinboAlert tipsWith:failInfo];
        }];
    }
}
- (IBAction)onOpenSpeaker:(NSButton *)sender {
    static BOOL isEnableIng = NO;//控制快速点击
    if (!isEnableIng) {
        isEnableIng = YES;
        BOOL isEnable = NO;
        if ([sender.title isEqualToString:@"打开扬声器"]) {
            isEnable = YES;
        }
        else {
            isEnable = NO;
        }
        [[ILiveRoomManager getInstance] enableSpeaker:isEnable succ:^{
            if (isEnable) {
                [sender setTitle:@"关闭扬声器"];
            }
            else {
                [sender setTitle:@"打开扬声器"];
            }
            isEnableIng = NO;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            isEnableIng = NO;
            NSLog(@"speaker option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
            NSString *failInfo = [NSString stringWithFormat:@"speaker option fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
            [SuixinboAlert tipsWith:failInfo];
        }];
    }
}
- (IBAction)onSwitchRole:(NSButton *)sender {
    static BOOL isEnableIng = NO;//控制快速点击
    if (!isEnableIng) {
        isEnableIng = YES;
        __weak typeof(self) ws = self;
        NSInteger selectIndex = [_roleSwitchPopUpBtn indexOfSelectedItem];
        NSString *roleNmae = [self getRoleNameFromIndex:selectIndex];
        [[ILiveRoomManager getInstance] changeRole:roleNmae succ:^{
            NSString *logInfo = [NSString stringWithFormat:@"切换到分辨率 %@ 成功", ws.roleSwitchPopUpBtn.selectedItem.title];
            [ws addLog:logInfo];
            isEnableIng = NO;
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            isEnableIng = NO;
            NSLog(@"change role fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
            NSString *failInfo = [NSString stringWithFormat:@"change role fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
            [SuixinboAlert tipsWith:failInfo];
        }];
    }
}
- (IBAction)onPush:(NSButton *)sender {
    __weak typeof(self) ws = self;
    static BOOL isEnableIng = NO;//控制快速点击
    if (!isEnableIng) {
        isEnableIng = YES;
        if ([sender.title isEqualToString:@"开始推流"]) {
            [self startPushStream:^{
                [sender setTitle:@"停止推流"];
                isEnableIng = NO;
            } fail:^(NSString *module, int errId, NSString *errMsg) {
                isEnableIng = NO;
                [ws addLog:[NSString stringWithFormat:@"开始推流失败M=%@,code=%d,Msg=%@",module,errId,errMsg]];
            }];
        }
        else {
            [self stopPushStream:^{
                [sender setTitle:@"开始推流"];
                isEnableIng = NO;
            } fail:^(NSString *module, int errId, NSString *errMsg) {
                isEnableIng = NO;
                [ws addLog:[NSString stringWithFormat:@"停止推流失败M=%@,code=%d,Msg=%@",module,errId,errMsg]];
            }];
        }
    }
}

- (void)startPushStream:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail{
    ILiveChannelInfo *info = [[ILiveChannelInfo alloc] init];
    info.channelName = [NSString stringWithFormat:@"Mac_随心播推流_%@",[[ILiveLoginManager getInstance] getLoginId]];
    info.channelDesc = [NSString stringWithFormat:@"Mac_随心播推流描述测试文本"];
    
    ILivePushOption *option = [[ILivePushOption alloc] init];
    option.channelInfo = info;
    option.encodeType = [self getEncodeType:_pushTypeComboBox.indexOfSelectedItem];
    option.recrodFileType = AV_RECORD_FILE_TYPE_MP4;
    
    __weak typeof(self) ws = self;
    [[ILiveRoomManager getInstance] startPushStream:option succ:^(id selfPtr) {
        AVStreamerResp *resp = (AVStreamerResp *)selfPtr;
        ws.channelId = resp.channelID;
        AVLiveUrl *url = nil;
        if (resp && resp.urls && resp.urls.count > 0)
        {
            url = resp.urls[0];
        }
        NSString *msg = url ? url.playUrl : @"url为nil";
        [SuixinboAlert alertWith:@"推流成功" msg:msg funBtns:@[@"复制URL", @"取消"] showTo:self.window completeHanler:^(NSModalResponse returnCode) {
            if (returnCode == NSAlertFirstButtonReturn) {
                NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
                [pasteboard clearContents];
                [pasteboard setString:url.playUrl forType:NSPasteboardTypeString];
            }
        }];
        succ ? succ() : nil;
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        if (fail) {
            fail(module,errId,errMsg);
        }
        NSLog(@"start push fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"start push fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}

- (void)stopPushStream:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail{
    __weak typeof(self) ws = self;
    [[ILiveRoomManager getInstance] stopPushStreams:@[@(ws.channelId)] succ:^{
        ws.channelId = 0;//重置channelid
        succ ? succ() : nil;
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        if (fail) {
            fail(module,errId,errMsg);
        }
        NSLog(@"stop push fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"stop push fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}

- (IBAction)onRecord:(NSButton *)sender {
    static BOOL isEnableIng = NO;
    if (!isEnableIng) {
        isEnableIng = YES;
        if ([sender.title isEqualToString:@"开始录制"]) {
            [self startRecord:^{
                [sender setTitle:@"停止录制"];
                isEnableIng = NO;
            } fail:^(NSString *module, int errId, NSString *errMsg) {
                isEnableIng = NO;
            }];
        }
        else {
            [self stopRecord:^{
                [sender setTitle:@"开始录制"];
                isEnableIng = NO;
            } fail:^(NSString *module, int errId, NSString *errMsg) {
                isEnableIng = NO;
            }];
        }
    }
}

- (void)startRecord:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail{
    NSString *recName = _recordFileNameTF.stringValue.length ? _recordFileNameTF.stringValue : @"默认录制文件名";
    [self recordReport:recName type:AV_RECORD_TYPE_VIDEO];
    
    ILiveRecordOption *option = [[ILiveRecordOption alloc] init];
    NSString *identifier = [[ILiveLoginManager getInstance] getLoginId];
    option.fileName = [NSString stringWithFormat:@"sxb_%@_%@",identifier,recName];
    option.recordType = AV_RECORD_TYPE_VIDEO;
    [[ILiveRoomManager getInstance] startRecordVideo:option succ:^{
        succ ? succ() : nil;
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        if (fail) {
            fail(module,errId,errMsg);
        }
        NSLog(@"start record fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"start record fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}
- (void)stopRecord:(TCIVoidBlock)succ fail:(TCIErrorBlock)fail{
    [[ILiveRoomManager getInstance] stopRecordVideo:^(id selfPtr) {
        succ ? succ() : nil;
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        if (fail) {
            fail(module,errId,errMsg);
        }
        NSLog(@"stop record fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
        NSString *failInfo = [NSString stringWithFormat:@"stop record fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
        [SuixinboAlert tipsWith:failInfo];
    }];
}

//回车键发送消息
- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector {
    NSString *str =  NSStringFromSelector(commandSelector);
    if ([str isEqualToString:@"insertNewline:"]) {
        [self onSendMessage:nil];
    }
    return NO;
}

- (IBAction)onSendMessage:(NSButton *)sender {
    if (_messageTF.stringValue.length > 0) {
        
        TIMTextElem *elem = [[TIMTextElem alloc] init];
        elem.text = _messageTF.stringValue;
        
        TIMMessage *msg = [[TIMMessage alloc] init];
        [msg addElem:elem];
        
        __weak typeof(self) ws = self;
        [[ILiveRoomManager getInstance] sendOnlineGroupMessage:msg succ:^{
            [ws insertMessageToUI:[NSString stringWithFormat:@"我: %@",elem.text]];
            ws.messageTF.stringValue = @"";
        } failed:^(NSString *module, int errId, NSString *errMsg) {
            NSLog(@"send message fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg);
            NSString *failInfo = [NSString stringWithFormat:@"stop record fail.M=%@,errId=%d,errMsg=%@",module,errId,errMsg];
            [ws insertMessageToUI:[NSString stringWithFormat:@"我: 消息发送失败.%@",failInfo]];
        }];
    }
}

- (void)insertMessageToUI:(NSString *)message
{
    NSString *oldMessage = [NSString stringWithFormat:@"%@",self.messageTextView.string];
    if (self.messageCount > 300) {//超出300条消息，则清空
        oldMessage = @"";
    }
    [self.messageTextView setString:[NSString stringWithFormat:@"%@\n%@",oldMessage,message]];
    [self.messageTextView scrollToEndOfDocument:self.messageTextView];
}

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
        __weak typeof(self) ws = self;
        [[ILiveSDK getInstance] uploadLog:desc.stringValue logDayOffset:[offset intValue] uploadResult:^(int retCode, NSString *retMsg, NSString *logKey) {
            NSLog(@"--->");
            if (retCode == 0) {
                [ws addLog:[NSString stringWithFormat:@"日志上报成功:Key=%@",logKey]];
            }
            else {
                [ws addLog:[NSString stringWithFormat:@"日志上报失败:code=%d,Msg=%@",retCode,retMsg]];
            }
        }];
    }
}

- (IBAction)onBeautySlider:(NSSlider *)sender {
    _beautyValueTF.stringValue = [NSString stringWithFormat:@"%d",sender.intValue];
    int value = sender.intValue;
    [_tilFilter setBeautyLevel:value];
}
- (IBAction)onWhiteSlider:(NSSlider *)sender {
    _whiteValueTF.stringValue = [NSString stringWithFormat:@"%d",sender.intValue];
    [_tilFilter setWhitenessLevel:sender.intValue];
}

- (void)addLog:(NSString *)logStr
{
    NSString *oldLog = [NSString stringWithFormat:@"%@",_logTextView.string];
    [_logTextView setString:[NSString stringWithFormat:@"%@\n%@",oldLog,logStr]];
    [_logTextView scrollToEndOfDocument:_logTextView];
}

- (void)recordReport:(NSString *)name type:(AVRecordType)type
{
    RecordReportRequest *req = [[RecordReportRequest alloc] initWithHandler:^(BaseRequest *request) {
        NSLog(@"rec report succ");
        
    } failHandler:^(BaseRequest *request) {
        NSLog(@"rec report fail %ld,%@", (long)request.response.errorCode,request.response.errorInfo);
    }];
    req.token = [AppDelegate sharedInstance].token;
    req.roomnum = _item.info.roomnum;
    req.uid = [[ILiveLoginManager getInstance] getLoginId];
    req.name = name;
    req.type = (NSInteger)type;
    req.cover = _item.info.cover;
    [[WebServiceEngine sharedEngine] asyncRequest:req];
}

- (IBAction)onExitLive:(NSButton *)sender {
    __weak typeof(self) ws = self;
    if (_isHost)//主播退群时，发送退群消息
    {
        [self sendCustomGroupMessage:YES recvId:@"" cmd:(ILVLiveIMCmd)AVIMCMD_ExitLive succ:^{
            [ws realExit];
        } fail:^(NSString *module, int errId, NSString *errMsg) {
            [ws realExit];
        }];
    }
    else {
        [ws realExit];
    }
}

- (void)realExit {
    //停止心跳
    [self stopLiveTimer];
    
    __weak typeof(self) ws = self;
    
    if (_isHost)
    {
        //通知业务服务器，退房
        ExitRoomRequest *exitReq = [[ExitRoomRequest alloc] initWithHandler:^(BaseRequest *request) {
            NSLog(@"上报退出房间成功");
        } failHandler:^(BaseRequest *request) {
            NSLog(@"上报退出房间失败");
        }];
        
        exitReq.token = [AppDelegate sharedInstance].token;
        exitReq.roomnum = _item.info.roomnum;
        exitReq.type = @"live";
        
        [[WebServiceEngine sharedEngine] asyncRequest:exitReq wait:NO];
    }
    else
    {
        [self reportMemberId:_item.info.roomnum operate:1];
    }
    
    [[ILiveRoomManager getInstance] quitRoom:^{
        int roomId = [[ILiveRoomManager getInstance] getRoomId];
        NSLog(@"%d",roomId);
        [ws.item cleanLocalData];
        [ws.window close];
    } failed:^(NSString *module, int errId, NSString *errMsg) {
        [ws.window close];
    }];
    
    [[RenderViewManager shareInstance] releaseManager];
    
    [_roomInfoWC.logTimer invalidate];
    _roomInfoWC.logTimer = nil;
    [_roomInfoWC.window orderOut:nil];
    
    [[[ILiveSDK getInstance] getAVContext].audioCtrl unregisterAudioDataCallbackAll];
    [[[ILiveSDK getInstance] getAVContext].audioCtrl setAudioDataEventDelegate:nil];
    [[[ILiveSDK getInstance] getTIMManager] removeMessageListener:self];
}

- (NSString *)getRoleNameFromIndex:(NSInteger)index {
    if (_isHost) {
        if (index == 0) {
            return kSxbRole_HostHD;
        }
        else if (index == 1) {
            return kSxbRole_HostSD;
        }
        else {
            return kSxbRole_HostLD;
        }
    }
    else {
        if (index == 0) {
            return kSxbRole_InteractHD;
        }
        else if (index == 1) {
            return kSxbRole_InteractSD;
        }
        else {
            return kSxbRole_InteractLD;
        }
    }
    return nil;
}

- (AVEncodeType)getEncodeType:(NSInteger)index {
    if (index == 0) {
        return AV_ENCODE_HLS;
    }
    else {
        return AV_ENCODE_RTMP;
    }
}

- (void)reportMemberId:(NSInteger)roomnum operate:(NSInteger)operate {
    __weak typeof(self) ws = self;
    ReportMemIdRequest *req = [[ReportMemIdRequest alloc] initWithHandler:^(BaseRequest *request) {
        NSLog(@"report memeber id succ");
        [ws onRefreshMemberList];
        
    } failHandler:^(BaseRequest *request) {
        NSLog(@"report memeber id fail");
    }];
    req.token = [AppDelegate sharedInstance].token;
    req.userId = [[ILiveLoginManager getInstance] getLoginId];
    req.roomnum = roomnum;
    req.role = _isHost ? 1 : 0;
    req.operate = operate;
    
    [[WebServiceEngine sharedEngine] asyncRequest:req wait:NO];
}

//停止发送心跳
- (void)stopLiveTimer
{
    if(_heartTimer)
    {
        [_heartTimer invalidate];
        _heartTimer = nil;
    }
}

//开始发送心跳
- (void)startLiveTimer
{
    [self stopLiveTimer];
    _heartTimer = [NSTimer scheduledTimerWithTimeInterval:kHeartInterval target:self selector:@selector(onPostHeartBeat:) userInfo:nil repeats:YES];
}

//发送心跳
- (void)onPostHeartBeat:(NSTimer *)timer
{
    HostHeartBeatRequest *heartReq = [[HostHeartBeatRequest alloc] initWithHandler:^(BaseRequest *request) {
        
        NSLog(@"---->heart beat succ");
    } failHandler:^(BaseRequest *request) {
        NSLog(@"---->heart beat fail");
    }];
    heartReq.token = [AppDelegate sharedInstance].token;
    heartReq.roomnum = _item.info.roomnum;
    heartReq.thumbup = _item.info.thumbup;
    //判断自己是什么角色
    if (_isHost)
    {
        heartReq.role = 1;
    }
    else
    {
        BOOL isOpenCamear = [[ILiveRoomManager getInstance] getCurCameraState];
        
        if (isOpenCamear)//连麦用户
        {
            heartReq.role = 2;
        }
        else//普通观众
        {
            heartReq.role = 0;
        }
    }
    [[WebServiceEngine sharedEngine] asyncRequest:heartReq wait:NO];
    
    //每次心跳刷新一下成员列表，在随心播中，只显示了成员数
    [self onRefreshMemberList];
}

- (void)onRefreshMemberList
{
    __weak typeof(self) ws = self;
    
    RoomMemListRequest *listReq = [[RoomMemListRequest alloc] initWithHandler:^(BaseRequest *request) {
        RoomMemListRspData *listRspData = (RoomMemListRspData *)request.response.data;
        [ws.members removeAllObjects];
        NSString *loginId = [[ILiveLoginManager getInstance] getLoginId];
        NSInteger index = 0;
        for (MemberListItem *item in listRspData.idlist) {//把自己移动到第一个
            if ([item.identifier isEqualToString:loginId]) {
                [listRspData.idlist exchangeObjectAtIndex:index withObjectAtIndex:0];
                break;
            }
            index++;
        }
        [ws.members addObjectsFromArray:listRspData.idlist];
        [ws.memberTableView reloadData];
    } failHandler:^(BaseRequest *request) {
        NSLog(@"get group member fail ,code=%ld,msg=%@",(long)request.response.errorCode, request.response.errorInfo);
    }];
    listReq.token = [AppDelegate sharedInstance].token;
    listReq.roomnum = _item.info.roomnum;
    listReq.index = 0;
    listReq.size = 20;
    
    [[WebServiceEngine sharedEngine] asyncRequest:listReq wait:NO];
}

- (void)OnVideoPreview:(QAVVideoFrame *)frameData {
    //仅仅是为了打log
    NSString *key = frameData.identifier;
    QAVFrameDesc *desc = [[QAVFrameDesc alloc] init];
    desc.width = frameData.frameDesc.width;
    desc.height = frameData.frameDesc.height;
    [self.roomInfoWC.resolutionDic setObject:desc forKey:key];
}

- (BOOL)onRoomDisconnect:(int)reason {
    __weak typeof(self) ws = self;
    [SuixinboAlert alertWith:nil msg:@"房间失去连接" funBtns:@[@"确定"] showTo:self.window completeHanler:^(NSModalResponse returnCode) {
        [ws onExitLive:nil];
    }];
    return YES;
}
@end
