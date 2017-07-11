//
//  SuixinboAlert.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/7.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "SuixinboAlert.h"

@implementation SuixinboAlert
+ (void)tipsWith:(NSString *)msg{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"确定"];
        [alert setMessageText:msg];
        [alert setAlertStyle:NSAlertStyleInformational];
        NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
        [alert setAccessoryView:view];
        [alert.window setFrame:NSMakeRect(0, 0, 210, 60) display:YES animate:YES];
        [alert runModal];
    });
}
+ (void)tipsWith:(NSString *)msg showTo:(NSWindow *)window {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"确定"];
        [alert setMessageText:msg];
        [alert setAlertStyle:NSAlertStyleInformational];
        NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
        [alert setAccessoryView:view];
        //    [alert.window setFrame:NSMakeRect(0, 0, 210, 60) display:YES animate:YES];
        [alert beginSheetModalForWindow:window completionHandler:^(NSModalResponse returnCode) {
        }];

    });
}

+ (void)alertWith:(NSString *)title msg:(NSString *)msg funBtns:(NSArray *)btns showTo:(NSWindow *)window completeHanler:(void (^ __nullable)(NSModalResponse returnCode))handler {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSAlert *alert = [[NSAlert alloc] init];
        for (NSString *btnTitle in btns) {
            [alert addButtonWithTitle:btnTitle];
        }
        [alert setMessageText:msg];
        [alert setAlertStyle:NSAlertStyleInformational];
        NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0,0,210,1)];
        [alert setAccessoryView:view];
        [alert beginSheetModalForWindow:window completionHandler:^(NSModalResponse returnCode) {
            if (handler) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    handler(returnCode);
                });
            }
        }];
    });
}
@end
