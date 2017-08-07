//
//  MemberCellView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "MemberCellView.h"

@implementation MemberCellView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)config:(MemberListItem *)item {
    _avatarImageView.image = [NSImage imageNamed:@"default_head"];
    _identifierTF.stringValue = item.identifier;
    if (item.role == 0)//guest
    {
        _userRoleTF.stringValue = @"观众";
    }
    if (item.role == 1)//host
    {
        _userRoleTF.stringValue = @"主播";
    }
    if (item.role == 2)//interact
    {
        _userRoleTF.stringValue = @"上麦观众";
    }    
}

@end
