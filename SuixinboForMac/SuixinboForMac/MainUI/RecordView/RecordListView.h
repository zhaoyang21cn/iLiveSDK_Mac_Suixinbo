//
//  RecordListView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/**
 录制列表视图，从随心播后台拉取录制列表进行展示，双击播放
 提供了按照录制者identifier过滤查找的功能
 */
@interface RecordListView : NSView<NSTextFieldDelegate>

@property (nonatomic, strong) NSMutableArray *datas;
@property (nonatomic, strong) NSMutableArray *searchDatas;
@property (nonatomic, strong) RequestPageParamItem *pageItem;
@property (nonatomic, assign) BOOL isCanLoadMore;

@property (nonatomic, assign) BOOL isShowSearchData;//显示查找数据还是全部数据

@property (strong) IBOutlet NSTextField *searchTF;
@property (strong) IBOutlet NSTableView *recordListTableView;//录制列表

- (void)config;
@end
