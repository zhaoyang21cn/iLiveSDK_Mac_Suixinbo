//
//  LiveListCellView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/**
 直播列表Cel
 */
@interface LiveListCellView : NSTableCellView

@property (strong) IBOutlet NSImageView *liveCoverImageView;
@property (strong) IBOutlet NSTextField *liveTitleTF;
@property (strong) IBOutlet NSTextField *liveRoomGuestCountTF;
@property (strong) IBOutlet NSTextField *liveRoomPraiseCountTF;
@property (strong) IBOutlet NSImageView *hostHeadImageView;
@property (strong) IBOutlet NSTextField *hostNameTF;

- (void)configWith:(TCShowLiveListItem *)item;
@end
