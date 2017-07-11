//
//  ClickCoverImageView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/7.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "ClickCoverImageView.h"

@implementation ClickCoverImageView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)mouseDown:(NSEvent *)theEvent{
    NSInteger clickCount = [theEvent clickCount];
    if (clickCount == 1) {
        [self onClick];
    }
}

- (void)onClick{
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    [panel setPrompt: @"选择"];
    [panel setAllowedFileTypes:@[@"png",@"jpg"]];
    __weak typeof(self) ws = self;
    [panel beginSheetModalForWindow:[self window] completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            NSString *pathString = [panel.URLs.firstObject path];
            NSImage *cover = [[NSImage alloc] initWithContentsOfFile:pathString];
            [ws setImage:cover];
        }
    }];
}

@end
