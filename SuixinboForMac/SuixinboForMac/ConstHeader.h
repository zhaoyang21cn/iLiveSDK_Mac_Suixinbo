//
//  ConstHeader.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/7.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#ifndef ConstHeader_h
#define ConstHeader_h

/******************** app **********************/
#define SuixinboSdkAppId       1400027849
#define SuixinboAccountType    11656

//#define SuixinboSdkAppId       1104062745
//#define SuixinboAccountType    107
//#define TestRoomNum            801234

/******************** role string **********************/
//#define kSxbRole_Host       @"LiveMaster"
#define kSxbRole_HostHD     @"HD"
#define kSxbRole_HostSD     @"SD"
#define kSxbRole_HostLD     @"LD"
//主播角色标题
#define kSxbRole_HostHDTitle @"高清(1280x720,25fps)"
#define kSxbRole_HostSDTitle @"标清(960x540,20fps)"
#define kSxbRole_HostLDTitle @"流畅(640x480,15fps)"

//连麦
//#define kSxbRole_Interact   @"LiveGuest"
#define kSxbRole_InteractHD @"HDGuest"
#define kSxbRole_InteractSD @"SDGuest"
#define kSxbRole_InteractLD @"LDGuest"
//连麦角色标题
#define kSxbRole_InteractHDTitle @"高清(1280x720,25fps)"
#define kSxbRole_InteractSDTitle @"标清(960x540,20fps)"
#define kSxbRole_InteractLDTitle @"流畅(640x480,15fps)"

//观众
#define kSxbRole_GuestHD    @"Guest"
#define kSxbRole_GuestLD    @"Guest2"
//观众标题
#define kSxbRole_GuestHDTitle      @"1、清晰"
#define kSxbRole_GuestLDTitle      @"2、流畅"

/******************** local param **********************/
#define kLoginParam         @"kLoginParam"
#define kLoginIdentifier    @"kLoginIdentifier"
#define kLoginPassward      @"kLoginPassward"
#define kEnvParam           @"kEnvParam"
#define kLogLevel           @"kLogLevel"
#define kBeautyScheme       @"kBeautyScheme"
#define kILiveBeauty        @"插件美颜"
#define kQAVSDKBeauty       @"内置美颜"

/******************** camera desc **********************/
#define kCameraDesc         @"Mac自带摄像头"
/******************** custom msg **********************/
#define kMsgCmdKey      @"userAction"
#define kMsgDataKey     @"actionParam"

#define kHeartInterval 5 //心跳间隔

typedef enum {
    /**
     * 无效消息
     */
    ILVLIVE_IMCMD_NONE                = 0x700,
    /**
     * 用户加入直播, Group消息
     */
    ILVLIVE_IMCMD_ENTER,
    /**
     * 用户退出直播, Group消息
     */
    ILVLIVE_IMCMD_LEAVE,
    /**
     * 邀请上麦，C2C消息
     */
    ILVLIVE_IMCMD_INVITE,
    /**
     * 取消邀请上麦，C2C消息
     */
    ILVLIVE_IMCMD_INVITE_CANCEL,
    /**
     * 关闭上麦，C2C消息
     */
    ILVLIVE_IMCMD_INVITE_CLOSE,
    /**
     * 同意上麦，C2C消息
     */
    ILVLIVE_IMCMD_INTERACT_AGREE,
    /**
     * 拒绝上麦，C2C消息
     */
    ILVLIVE_IMCMD_INTERACT_REJECT,
    /**
     * 请求跨房连麦，C2C消息
     */
    ILVLIVE_IMCMD_LINKROOM_REQ,
    /**
     * 同意跨房连麦，C2C消息
     */
    ILVLIVE_IMCMD_LINKROOM_ACCEPT,
    /**
     * 拒绝跨房连麦，C2C消息
     */
    ILVLIVE_IMCMD_LINKROOM_REFUSE,
    /**
     * 跨房连麦者达到上限，C2C消息
     */
    ILVLIVE_IMCMD_LINKROOM_LIMIT,
    /**
     * 真正连接成功
     */
    ILVLIVE_IMCMD_LINKROOM_SUCC,
    /**
     * 取消跨房连麦
     */
    ILVLIVE_IMCMD_UNLINKROOM,
    /**
     * 自定义消息段下限
     */
    ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT     = 0x800,
    /**
     * 自定义消息段上限
     */
    ILVLIVE_IMCMD_CUSTOM_UP_LIMIT      = 0x900,
}ILVLiveIMCmd;

/******************** custom msg cmd **********************/
typedef enum {
    AVIMCMD_Text = -1,          // 普通的聊天消息
    
    AVIMCMD_None,               // 无事件：0
    
    // 以下事件为TCAdapter内部处理的通用事件
    AVIMCMD_EnterLive,          // 用户加入直播, Group消息 ： 1
    AVIMCMD_ExitLive,           // 用户退出直播, Group消息 ： 2
    AVIMCMD_Praise,             // 点赞消息, Demo中使用Group消息 ： 3
    AVIMCMD_Host_Leave,         // 主播或互动观众离开, Group消息 ： 4
    AVIMCMD_Host_Back,          // 主播或互动观众回来, Group消息 ： 5
    
    //    ShowCustomCmd_Begin = ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,
    //    ShowCustomCmd_Praise,
    //    ShowCustomCmd_JoinRoom,
    //    ShowCustomCmd_DownVideo,//主播发送下麦通知
    
    AVIMCMD_Multi = ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,              // 多人互动消息类型 ： 2048
    
    AVIMCMD_Multi_Host_Invite,          // 多人主播发送邀请消息, C2C消息 ： 2049
    AVIMCMD_Multi_CancelInteract,       // 已进入互动时，断开互动，Group消息，带断开者的imUsreid参数 ： 2050
    AVIMCMD_Multi_Interact_Join,        // 多人互动方收到AVIMCMD_Multi_Host_Invite多人邀请后，同意，C2C消息 ： 2051
    AVIMCMD_Multi_Interact_Refuse,      // 多人互动方收到AVIMCMD_Multi_Invite多人邀请后，拒绝，C2C消息 ： 2052
    
    // =======================
    // 暂未处理以下
    AVIMCMD_Multi_Host_EnableInteractMic,  // 主播打开互动者Mic，C2C消息 ： 2053
    AVIMCMD_Multi_Host_DisableInteractMic, // 主播关闭互动者Mic，C2C消息 ：2054
    AVIMCMD_Multi_Host_EnableInteractCamera, // 主播打开互动者Camera，C2C消息 ：2055
    AVIMCMD_Multi_Host_DisableInteractCamera, // 主播关闭互动者Camera，C2C消息 ： 2056
    // ==========================
    
    
    AVIMCMD_Multi_Host_CancelInvite,            // 取消互动, 主播向发送AVIMCMD_Multi_Host_Invite的人，再发送取消邀请， 已发送邀请消息, C2C消息 ： 2057
    AVIMCMD_Multi_Host_ControlCamera,           // 主动控制互动观众摄像头, 主播向互动观众发送,互动观众接收时, 根据本地摄像头状态，来控制摄像头开关（即控制对方视频是否上行视频）， C2C消息 ： 2058
    AVIMCMD_Multi_Host_ControlMic,              // 主动控制互动观众Mic, 主播向互动观众发送,互动观众接收时, 根据本地MIC状态,来控制摄像头开关（即控制对方视频是否上行音频），C2C消息 ： 2059
}ShowCustomCmd;

typedef enum {
    /**
     * C2C消息
     */
    ILVLIVE_IMTYPE_C2C         = 1,
    /**
     * Group消息
     */
    ILVLIVE_IMTYPE_GROUP,
}ILVLiveIMType;

typedef enum {
    RoomOptionType_CrateRoom = 0,
    RoomOptionType_JoinRoom,
}RoomOptionType;

#endif /* ConstHeader_h */
