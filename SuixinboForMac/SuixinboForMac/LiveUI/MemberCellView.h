//
//  MemberCellView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MemberCellView : NSTableCellView

@property (strong) IBOutlet NSImageView *avatarImageView;
@property (strong) IBOutlet NSTextField *identifierTF;
@property (strong) IBOutlet NSTextField *userRoleTF;

- (void)config:(MemberListItem *)item;
@end
