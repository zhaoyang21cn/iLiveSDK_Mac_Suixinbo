//
//  RecordListCellView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface RecordListCellView : NSTableCellView

@property (strong) IBOutlet NSImageView *recordCoverImageView;
@property (strong) IBOutlet NSTextField *recordTitleTF;
@property (strong) IBOutlet NSTextField *recordTimeTF;
@property (strong) IBOutlet NSTextField *recordDuration;
@property (strong) IBOutlet NSTextField *recordSize;
@property (strong) IBOutlet NSImageView *hostHeadImageView;
@property (strong) IBOutlet NSTextField *hostNameTF;

@property (nonatomic, strong) NSDateFormatter *dateFormatter;

@property (nonatomic, strong) RecordVideoItem *item;
- (void)configWith:(RecordVideoItem *)item;
@end
