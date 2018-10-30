# iLiveSDK_Mac
iLiveSDK 提供了账号登录，音视频互动，文本互动等基础功能，顺利的话一天之内即可集成音视频能力。

## <a name="#sdk_download">SDK下载</a>

|SDK|版本号|摘要|下载地址|
|--|--|--|--|
|<a name="#avsdk_download">QAVSDK</a>|1.9.9.1031.40220|音视频SDK|[下载](http://dldir1.qq.com/hudongzhibo/ILiveSDK/AVSDK_1.9.9.1031.40220.zip)
|IMSDK|2.7.2.14130.14125|即时通讯SDK|[下载](http://dldir1.qq.com/hudongzhibo/ILiveSDK/IMSDK_MAC_2.7.2.14130.14125.zip)
|ILiveSDK|1.9.4.14133|互动直播核心业务SDK|[下载](http://dldir1.qq.com/hudongzhibo/ILiveSDK/ILiveSDKMac_1.9.4.14133.zip)

## 随心播

### 1、安装包体验

下载的工程中 SuiXinBoForMac_x.x.x.dmg 是可以直接运行的安装包

### 2、源码运行

** 下载SDK **

由于github有上传文件大小限制，请切记，下载工程之后，需要单独下载SDK。

下载SDK很简单： 
SDK目录: **iLiveSDK_Mac_Suixinbo/SuixinboForMac/FrameworksMac** 

1、打开终端，输入: cd FrameworksMac目录， 进入随心播FrameworksMac目录 

2、运行脚本下载SDK, 终端输入:sh LoadSDK.sh 

脚本会自动下载SDK，并解压到当前目录，这会消耗几分钟时间，下载好之后在看工程目录中，打开随心播工程可以看到，FrameworksMac下的所有SDK已经变成黑色状态，也就是可用状态了(如果有SDK下载失败的情况，重新运行脚本再下载一次)。

此时可以直接运行了

![](http://mc.qcloudimg.com/static/img/20c7e51f679f2ee525cc382f6c294e7f/image.png)

## SDK最近更新说明
###### V1.9.4.14133(2018-10-30)
* 1、ilivesdk版本更新支持imsdk V2/V3版本切换(备注：升级ilivesdk版本时，需要同时更新imsdk为最新版)
* 2、云上环境支持手动推流


[更多版本更新信息](https://github.com/zhaoyang21cn/iLiveSDK_Mac_Suixinbo/blob/master/doc/iLiveSDK_ChangeList.md)

## iLiveSDK导入

[Mac版iLiveSDK导入参考在这里](https://github.com/zhaoyang21cn/iLiveSDK_Mac_Suixinbo/blob/master/doc/iLiveSDK_Integrated.md)

## API文档
[API文档](https://zhaoyang21cn.github.io/iLiveSDK_Help/ios_help/)

## 错误码
[错误码表](https://github.com/zhaoyang21cn/ILiveSDK_Android_Demos/blob/master/doc/ILiveSDK/error.md)

## 已知问题

## 关键路径LOG
[关键路径LOG 请遇到问题先自行对比](https://github.com/zhaoyang21cn/suixinbo_doc/blob/master/doc2/log.md)

## 联系我们
技术支持QQ群：594923937 207177891

技术需求反馈：https://github.com/zhaoyang21cn/ILiveSDK_iOS_Demos/issues 

关注公众号"腾讯云视频"，给公众号发关键字"技术支持"，会有专人联系。

![](https://main.qcloudimg.com/raw/769293c3dbc0df8fbfb7d6a7cc904692.jpg)
