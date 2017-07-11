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
    self.imageView.image =  [NSImage imageNamed:@"default_head"];
    self.textField.stringValue = item.identifier;
}

@end
