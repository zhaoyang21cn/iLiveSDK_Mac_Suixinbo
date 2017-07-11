//
//  CreateRoomWC.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/19.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "CreateRoomWC.h"

@implementation LiveRommConfig

@end

@interface CreateRoomWC ()

@end

@implementation CreateRoomWC
- (void)awakeFromNib{
    
    [self.contentViewController.view setWantsLayer:YES];
    self.contentViewController.view.layer.backgroundColor = CGColorCreateGenericRGB(51.0/256.0, 51.0/256.0, 51.0/256.0, 1);
    self.contentViewController.view.layer.backgroundColor = CGColorCreateGenericRGB(51.0/256.0, 51.0/256.0, 51.0/256.0, 1);
    _bgView.layer.backgroundColor = CGColorCreateGenericRGB(241.0/256.0,241.0/256.0, 241.0/256.0, 1);
    [_cameraPpoUpBtn addItemWithTitle:kCameraDesc];
    [_micPopUpBtn addItemWithTitle:@"开"];
    [_micPopUpBtn addItemWithTitle:@"关"];
    [_rolePopUpBtn addItemWithTitle:kSxbRole_HostHDTitle];
    [_rolePopUpBtn addItemWithTitle:kSxbRole_HostSDTitle];
    [_rolePopUpBtn addItemWithTitle:kSxbRole_HostLDTitle];
}
- (void)windowDidLoad {
    [super windowDidLoad];
}

- (IBAction)onCameraPopUp:(NSPopUpButton *)sender {
    
}
- (IBAction)onMicPopUp:(NSPopUpButton *)sender {
    
}

- (void)publishLive {
    __block CreateRoomResponceData *roomData = nil;
    __block NSString *imageUrl = nil;
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
        //请求房间id
        CreateRoomRequest *createRoomReq = [[CreateRoomRequest alloc] initWithHandler:^(BaseRequest *request) {
            roomData = (CreateRoomResponceData *)request.response.data;
            dispatch_semaphore_signal(semaphore);
            
        } failHandler:^(BaseRequest *request) {
            dispatch_semaphore_signal(semaphore);
        }];
        createRoomReq.token = [AppDelegate sharedInstance].token;
        createRoomReq.type = @"live";
        [[WebServiceEngine sharedEngine] asyncRequest:createRoomReq];
        
        //        //上传封面
        //        [[UploadImageHelper shareInstance] upload:_liveCoverImageView.image completion:^(NSString *imageSaveUrl) {
        //            imageUrl = imageSaveUrl;
        //            dispatch_semaphore_signal(semaphore);
        //
        //        } failed:^(NSString *failTip) {
        //            dispatch_semaphore_signal(semaphore);
        //        }];
        dispatch_time_t timeoutTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(10.0 * NSEC_PER_SEC));
        //        dispatch_semaphore_wait(semaphore, timeoutTime);
        dispatch_semaphore_wait(semaphore, timeoutTime);
        
        //设置参数
        TCShowLiveListItem *item = [[TCShowLiveListItem alloc] init];
        item.uid = [[ILiveLoginManager getInstance] getLoginId];
        item.info = [[ShowRoomInfo alloc] init];
        item.info.title = _liveTitleTF.stringValue.length > 0 ? _liveTitleTF.stringValue : self.liveTitleTF.placeholderString;
        item.info.type = @"live";
        item.info.roomnum = (int)roomData.roomnum;
        item.info.groupid = roomData.groupid;
        item.info.cover = imageUrl;
        item.info.appid = SuixinboSdkAppId;
        NSInteger roleIndex = _rolePopUpBtn.indexOfSelectedItem;
        item.info.roleName = [self getRoleName:roleIndex];
        
        LiveRommConfig *config = [[LiveRommConfig alloc] init];
        NSInteger tag = [_micPopUpBtn indexOfSelectedItem];
        if (tag == 0) {
            config.isAutoOpenMic = YES;
        }
        else if (tag == 1) {
            config.isAutoOpenMic = NO;
        }
        config.cameraDesc = [_cameraPpoUpBtn itemTitleAtIndex:[_cameraPpoUpBtn indexOfSelectedItem]];
        config.roleDesc = [self getRoleDesc:item.info.roleName];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (self.delegate && [self.delegate respondsToSelector:@selector(createRoom:config:)]) {
                [self.delegate createRoom:item config:config];
            }
        });
    });
}

- (IBAction)onCreateRoom:(id)sender {
    [self publishLive];
}

- (NSString *)getRoleName:(NSInteger)index{
    if (index == 0) {
        return kSxbRole_HostHD;
    }
    else if (index == 1){
        return kSxbRole_HostSD;
    }
    else {
        return kSxbRole_HostLD;
    }
}

- (NSString *)getRoleDesc:(NSString *)roleName {
    if ([roleName isEqualToString:kSxbRole_HostHD]) {
        return kSxbRole_HostHDTitle;
    }
    else if ([roleName isEqualToString:kSxbRole_HostSD]){
        return kSxbRole_HostSDTitle;
    }
    else {
        return kSxbRole_HostLDTitle;
    }
}
- (IBAction)onCancel:(id)sender {
    [[NSApplication sharedApplication] stopModal];
    [self.window close];
}

@end
