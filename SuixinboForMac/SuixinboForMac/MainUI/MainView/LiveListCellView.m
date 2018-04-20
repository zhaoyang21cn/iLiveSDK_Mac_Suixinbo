//
//  LiveListCellView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "LiveListCellView.h"

@implementation LiveListCellView

- (void)awakeFromNib{
    
    [_hostHeadImageView setWantsLayer: YES];
    _hostHeadImageView.layer.borderWidth = 0.5;
    _hostHeadImageView.layer.cornerRadius = _hostHeadImageView.frame.size.width/2;
    _hostHeadImageView.layer.borderColor = [NSColor grayColor].CGColor;
    _hostHeadImageView.layer.masksToBounds = YES;
}

- (void)configWith:(TCShowLiveListItem *)item{
    //设置默认封面
    _liveCoverImageView.image = [NSImage imageNamed:@"defaul_publishcover"];
    _hostHeadImageView.image = [NSImage imageNamed:@"default_head"];
    //设置封面
    if (item.info.cover && item.info.cover.length > 0)
    {
        NSURL *imageUrl = [NSURL URLWithString:item.info.cover];
        NSImage *image = [[NSImage alloc] initWithContentsOfURL:imageUrl];
        _liveCoverImageView.image = image;
    }
    //设置标题
    _liveTitleTF.stringValue = [NSString stringWithFormat:@"直播标题:%@",item.info.title];
    //设置观众人数
    _liveRoomGuestCountTF.stringValue = [NSString stringWithFormat:@"观众:%d",item.info.memsize];
    //设置点赞数
    _liveRoomPraiseCountTF.stringValue = [NSString stringWithFormat:@"点赞:%d",item.info.thumbup];
    //设置主播头像 //todo
    //设置主播名
    _hostNameTF.stringValue = item.uid;
}
@end
