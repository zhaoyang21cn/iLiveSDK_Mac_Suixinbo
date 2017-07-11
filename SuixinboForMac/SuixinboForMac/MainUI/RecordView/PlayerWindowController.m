//
//  PlayerWindowController.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "PlayerWindowController.h"


@interface PlayerWindowController ()

@end

@implementation PlayerWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    _playerView = [[AVPlayerView alloc] initWithFrame:self.window.contentView.bounds];

    //url
    NSString *urlStr = _item.playurl[0];
    NSURL *url = [NSURL URLWithString:urlStr];
    _playerView.player = [AVPlayer playerWithURL:url];
    [self.window.contentView addSubview:_playerView];
    
    //file identifier
    NSArray *array = [_item.name componentsSeparatedByString:@"_"];
    if (array.count > 2)//录制文件名 //录制用户
    {
        NSString *identifier = array[1];
        NSString *fileName = array[2];
        self.window.title = [NSString stringWithFormat:@"id:%@  标题:%@",identifier,fileName];
    }
}

- (BOOL)windowShouldClose:(id)sender {
    [_playerView removeFromSuperview];
    [NSApp stopModalWithCode:0];
    return TRUE;
}
@end
