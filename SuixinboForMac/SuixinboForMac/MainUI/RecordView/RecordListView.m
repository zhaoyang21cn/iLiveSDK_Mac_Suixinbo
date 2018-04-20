//
//  RecordListView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "RecordListView.h"
#import "RecordListCellView.h"
#import "PlayerWindowController.h"

@implementation RecordListView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)config {
    _datas = [NSMutableArray array];
    _searchDatas = [NSMutableArray array];
    _pageItem = [[RequestPageParamItem alloc] init];
    _pageItem.pageIndex = 1;//录制列表页号是从1开始的
    _pageItem.pageSize = _numberTF.stringValue.length>0 ? [_numberTF.stringValue integerValue] : 15;
    
    [_recordListTableView setTarget:self];
    [_recordListTableView setDoubleAction:NSSelectorFromString(@"doubleClickRow:")]; //setDoubleAction双击选择事件
    
    _acountTF.stringValue = [[ILiveLoginManager getInstance] getLoginId];
    _acountTF.delegate = self;
    _numberTF.delegate = self;
    _isCanLoadMore = YES;
    [self reLoad:nil];
}

- (void)reLoad:(TCIVoidBlock)complete
{
    _pageItem.pageIndex = 1;
    _pageItem.pageSize = _numberTF.stringValue.length>0 ? [_numberTF.stringValue integerValue] : 15;
    if (_pageItem.pageSize > 100 || _pageItem.pageSize < 0)//后台限制在0-100之间
    {
        _pageItem.pageSize = 15;
    }
    [_datas removeAllObjects];
    
    __weak typeof(self) ws = self;
    __weak RequestPageParamItem *wpi = _pageItem;
    RecordListRequest *recListReq = [[RecordListRequest alloc] initWithHandler:^(BaseRequest *request) {
        RecordListResponese *recordRsp = (RecordListResponese *)request.response;
        [ws.datas addObjectsFromArray:recordRsp.videos];
        dispatch_async(dispatch_get_main_queue(), ^{
            [ws.recordListTableView reloadData];
        });
        wpi.pageIndex ++;
        if (ws.datas.count >= recordRsp.total)
        {
            _isCanLoadMore = NO;
        }
        if (complete)
        {
            complete();
        }
    } failHandler:^(BaseRequest *request) {
    }];

    recListReq.token = [AppDelegate sharedInstance].token;
    recListReq.type = 0;
    recListReq.index = _pageItem.pageIndex;
    recListReq.size = _pageItem.pageSize;
    recListReq.uid = _acountTF.stringValue ? _acountTF.stringValue : @"";
    [[WebServiceEngine sharedEngine] asyncRequest:recListReq wait:NO];
}

//回车搜索录制文件
- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector {
    NSString *str =  NSStringFromSelector(commandSelector);
    if ([str isEqualToString:@"insertNewline:"]) {
        [self reLoad:nil];
    }
    return NO;
}

- (IBAction)onSearch:(NSButton *)sender {
    [self reLoad:nil];
}

/*
 - (void)searchVideo:(NSString *)identifier {
    if (identifier.length <= 0) {
        _isShowSearchData = NO;
        [_searchDatas removeAllObjects];
        [_recordListTableView reloadData];
        return;
    }
    _isShowSearchData = YES;
    [_searchDatas removeAllObjects];
    //本地数据查询
    for (RecordVideoItem *item in _datas) {
        if ([item.uid isEqualToString:identifier]) {
            RecordVideoItem *temp = [item copy];
            [_searchDatas addObject:temp];
        }
    }
    //服务器数据查询
    if (_isCanLoadMore) {
        [self searchRemoteData:_pageItem.pageIndex targetId:identifier];
    }
}
- (void)searchRemoteData:(NSInteger)index targetId:(NSString *)identifier{
    __weak typeof(self) ws = self;
    RecordListRequest *recListReq = [[RecordListRequest alloc] initWithHandler:^(BaseRequest *request) {
        RecordListResponese *recordRsp = (RecordListResponese *)request.response;
        for (RecordVideoItem *item in recordRsp.videos) {
            if ([item.uid isEqualToString:identifier]) {
                RecordVideoItem *temp = [item copy];
                [_searchDatas addObject:temp];
            }
        }
        if (index * 100 >= recordRsp.total) {
            [ws.recordListTableView reloadData];
            return ;
        }
        else {
            [ws searchRemoteData:index+1 targetId:identifier];
        }
    } failHandler:^(BaseRequest *request) {
    }];
    recListReq.token = [AppDelegate sharedInstance].token;
    recListReq.type = 0;
    recListReq.index = index;
    recListReq.size = 100;
    [[WebServiceEngine sharedEngine] asyncRequest:recListReq wait:NO];
}
*/

#pragma mark - table view delegate
-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView{
    if (_isShowSearchData) {
        return _searchDatas.count;
    }
    else {
        return _datas.count;
    }
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
    return 100;
}

- (NSView *)tableView:(NSTableView*)tableView viewForTableColumn:(NSTableColumn*)tableColumn row:(NSInteger)row{
    RecordListCellView *cellView = [tableView makeViewWithIdentifier:@"RecordListCellViewID" owner:self];
    if (_isShowSearchData) {
        if (_searchDatas.count > row) {
            [cellView configWith:_searchDatas[row]];
        }
    }
    else {
        if (_datas.count > row) {
            [cellView configWith:_datas[row]];
        }
    }
    return cellView;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
    return nil;
}

- (BOOL)tabView:(NSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem {
    return YES;
}

//双击开始观看直播
- (void)doubleClickRow:(id)sender {
    NSInteger rowNumber = [_recordListTableView clickedRow];
    RecordVideoItem *item = nil;
    if (_isShowSearchData) {
        if (_searchDatas.count <= rowNumber) {
            return;
        }
        item = _searchDatas[rowNumber];
    }
    else {
        if (_datas.count <= rowNumber) {
            return;
        }
        item = _datas[rowNumber];
    }
    
    if (item && item.playurl.count > 0)
    {
        PlayerWindowController *playerWC = [[PlayerWindowController alloc] initWithWindowNibName:@"PlayerWindowController"];
        playerWC.item = item;
        [NSApp runModalForWindow:playerWC.window];
    }
    else
    {
        [SuixinboAlert tipsWith:@"无效的播放地址"];
    }
}

@end
