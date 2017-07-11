//
//  BackgroundView.h
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface BackgroundView : NSView

+ (BackgroundView *)initWithRGB:(CGFloat)r g:(CGFloat)g b:(CGFloat)b frame:(NSRect)frame;
+ (BackgroundView *)initWithRGB:(CGFloat)r g:(CGFloat)g b:(CGFloat)b a:(CGFloat)a frame:(NSRect)frame;
+ (BackgroundView *)initWithRGB:(NSImage *)image frame:(NSRect)frame;
@end
