//
//  BackgroundView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "BackgroundView.h"

@interface BackgroundView ()

@property (nonatomic, strong) NSImage *bgImage;

@property (assign) CGFloat r;
@property (assign) CGFloat g;
@property (assign) CGFloat b;
@property (assign) CGFloat a;

@property (assign) BOOL colorBg;

@end

@implementation BackgroundView

+ (BackgroundView *)initWithRGB:(CGFloat)r g:(CGFloat)g b:(CGFloat)b frame:(NSRect)frame{
    return [BackgroundView initWithRGB:r g:g b:b a:1 frame:frame];
}

+ (BackgroundView *)initWithRGB:(CGFloat)r g:(CGFloat)g b:(CGFloat)b a:(CGFloat)a frame:(NSRect)frame
{
    BackgroundView *bgView = [[BackgroundView alloc] init];
    bgView.r = r;
    bgView.g = g;
    bgView.b = b;
    bgView.a = a;
    bgView.colorBg = YES;
    [bgView setFrame:frame];
    return bgView;
}

+ (BackgroundView *)initWithRGB:(NSImage *)image frame:(NSRect)frame{
    BackgroundView *bgView = [[BackgroundView alloc] init];
    bgView.bgImage = image;
    bgView.colorBg = NO;
    [bgView setFrame:frame];
    return bgView;
}

- (void)drawRect:(NSRect)dirtyRect{
    [super drawRect:dirtyRect];
    if (_colorBg) {
        self.layer.backgroundColor = CGColorCreateGenericRGB(_r, _g, _b, _a);
    }
    else{
        self.layer.contents = (id)_bgImage;
    }
}
@end
