## MacOS_iLiveSDK_ChangeList
###### V1.9.6.14326(2019-03-11)
* 更新QAVSDK版本
###### V1.9.6.14326(2019-01-04)
* ilivesdk视频质量数据增加时延参数rtt

###### V1.9.6.14321(2019-01-03)
* 1、 ilivesdk封装音视频测试接口
* 2、 进房option增加enableMuteBag参数，YES时会发送静音包，默认关闭
###### V1.9.6.14296(2018-12-24)
* 1、修复本地日志上报配置文件损坏导致无法初始化问题
* 2、初始化接口增加回调
* 3、 更新QAVSDK，支持音频优先传输
* 4、 支持[自定义Spear配置功能](https://github.com/zhaoyang21cn/iLiveSDK_Android_LiveDemo/blob/master/doc/ILiveSDK/def_role.md)
* 5、 修复canclelistView接口无效的问题
* 6、 修复超时断开连接退房时，设置option的isReserved属性无效问题
* 7、 修复相机权限关闭时，调用打开相机回调不正确问题

###### V1.9.4.14133(2018-10-30)
* 1、ilivesdk版本更新支持imsdk V2/V3版本切换(备注：升级ilivesdk版本时，需要同时更新imsdk为最新版)
* 2、云上环境支持手动推流
###### V1.9.4.14037(2018-9-6)
* 1、修改角色不存在时进房失败
* 2、更新QAVSDK1.9.9.1018
* 3、修复进IM群组失败的问题
* 4、修复xcode10下编译失败问题（需要先在工程中删除libstdc++.6库）
###### V1.9.4.14015(2018-8-30)
* 1、修改默认群组类型为Public
* 2、修改sdk初始化接口- (int)initSdk:(int)appId;去掉accountType字段
###### V1.9.3.13966(2018-8-23)
* 1、更新AVSDK到1.9.9.1012
* 2、添加测速类ILiveSpeedTest，可通过startSpeedTest接口进行测试

###### V1.9.2.13903(2018-8-02)
* 1、房间和摄像头接口去时序化
* 2、ILiveSDK添加[统一事件回调](https://github.com/zhaoyang21cn/iLiveSDK_Android_LiveDemo/blob/master/doc/ILiveSDK/EventListener.md)
* 3、添加成员进出房间(群组)事件通知以及群组解散事件通知

###### V1.9.1.13841(2018-7-18)
* 修复推流和录制视频画面方向错误的问题

###### V1.9.0.13800(2018-7-11)
* 1、修改SDK内部默认通道为云上环境(**老用户需要在 初始化SDK之前 将通道设置为IMSDK通道，否则无法与旧版本互通**)
    `[[ILiveSDK getInstance] setChannelMode:E_ChannelIMSDK withHost:@""];`
* 2、ILiveSDK增加通道设置接口setChannelMode
* 3、修复日志上报模块，设置为NSNumber时crash问题
* 4、将authBuff字段更名为privateMapKey

###### V1.8.4.13565(2018-6-11)
* 1、修复日志上报引起的ILiveCabstructThread crash问题

###### V1.8.4.13487(2018-4-20)
* 1、更新AVSDK，提供控制台日志打印开关（ILiveSDK版本不变）

###### V1.8.4.13487(2018-4-16)
* 1、修复日志上报字段appname值错误问题
* 2、ILiveSDK中默认初始化日志上报SDK

###### V1.8.4.13473(2018-4-12)
* 1、更新avsdk1.9.8
* 2、分离日志上报模块，单独成立ILiveLogReport.Framework
* 4、调整ILiveSDK内部日志上报机制

###### 1.8.3.13017(2018-1-29)
* 1、修复打开/关闭摄像头失败时无回调问题
* 2、增加一个登录接口，支持本地配置spear配置(在网络不稳定拉去spear配置容易失败的场景下可以用到)

###### 1.8.1.12629(2017-12-18)
* 1、更新AVSDK1.9.6版本最新版版，修复内部bug
* 2、ILiveSDK增加禁用数据上报接口(用于屏蔽数据上报crash问题)

###### V1.7.2.12519(2017-12-06)
* 1、优化Mac随心播UI
* 2、更新AVSDK1.9.6，提升稳定性

###### V1.7.1.12078(2017-10-30)
* 1、主要是iOS端的变更，mac端无变更

###### V1.7.0.11812(2017-9-25)
* 1、增加极速模式

###### V1.6.1.11681(2017-9-7)
* 1、修复 被踢下线，再次登录时出现1003错误的问题
* 2、房间失去连接时，释放内部资源
* 3、增加内部关键日志打印

###### V1.6.0.11371(2017-8-7)
* 1、MacOS 平台增加屏幕分享能力

###### V1.5.1(2017-7-11)
* 1、MacOS 平台第一个版本
* 2、对齐iOS平台绝大部分功能
* 3、暂时不支持屏幕分享功能
* 4、暂时仅支持Mac自带摄像头
