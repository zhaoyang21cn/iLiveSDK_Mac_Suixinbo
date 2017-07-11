# iLiveSDK_Mac 集成文档
#### 1、导入腾讯相关的SDK，清单如下:

|SDK名|描述|是否必须|
|--|--|--|
|QAVSDK.framework|音视频能力基础包|必须|
|xplatform.framework|跨平台支持库|必须|
|IMCore.framework|即时通讯核心库|必须|
|ImSDK.framework|即时通讯Mac平台封装库|必须|
|QALSDK.framework|即时通讯网络模块依赖库|必须|
|TLSSDK.framework|登录模块依赖库|必须|
|ILiveSDK.framework|互动直播核心业务依赖库|必须|
|TILFilterSDK.framework|互动直播美颜依赖库|非必须|

#### 2、导入系统依赖库，清单如下:

|依赖库|
|--|
|QuartzCore.framework|
|CoreTelephony.framework|
|CoreWLAN.framework|
|Foundation.framework|
|SystemConfiguration.framework|
|libc++.tbd|
|libiconv.tbd|
|libresolv.9.tbd|
|libsqlite3.tbd|
|libstdc++.6.tbd|
|libz.tbd|

#### 3、工程配置
##### 3.1、最低支持MacOS 10.7

设置最低版本大于或等10.7,Build Settings -> macOS Deployment Target -> macOS 10.7,如下图所示：

![](http://mc.qcloudimg.com/static/img/592954bf985115b7089147800a3667c8/image.png)

##### 3.2、-ObjC 配置

Build Settings -> Other Linker Flags -> -ObjC,如下图所示：

![](http://mc.qcloudimg.com/static/img/2ce4909a75e4dd9c29e0fb9f9898eb48/image.png)

#### 4、验证

```
1、//AppDelegate.m中导入头文件 #import <ILiveSDK/ILiveSDK.h>
2、打印iLiveSDK版本号
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
NSLog(@"version = %@",[[ILiveSDK getInstance] getVersion]);
}
```
