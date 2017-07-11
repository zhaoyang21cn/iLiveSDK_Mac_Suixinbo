//
//  RecordListCellView.m
//  SuixinboForMac
//
//  Created by wilderliao on 2017/6/27.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "RecordListCellView.h"

@implementation RecordListCellView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (void)awakeFromNib {
    
    [_hostHeadImageView setWantsLayer: YES];
    _hostHeadImageView.layer.borderWidth = 0.5;
    _hostHeadImageView.layer.cornerRadius = _hostHeadImageView.frame.size.width/2;
    _hostHeadImageView.layer.borderColor = [NSColor grayColor].CGColor;
    _hostHeadImageView.layer.masksToBounds = YES;
}

- (void)configWith:(RecordVideoItem *)item;
{
    if (!item)
    {
        return;
    }
    _item = item;
    
    //懒加载封面
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSString *path = [self downAndSaveToLocal];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (path)
            {
                NSImage *image = [[NSImage alloc] initWithContentsOfFile:path];
                [_recordCoverImageView setImage:image];
            }
        });
    });
    [_recordCoverImageView setImage:[NSImage imageNamed:@"defaul_publishcover"]];
    
    __weak typeof(self)ws = self;
    //设置用户头像
    [[TIMFriendshipManager sharedInstance] GetUsersProfile:@[item.uid] succ:^(NSArray *friends) {
        if (friends.count <= 0)
        {
            return ;
        }
        TIMUserProfile *profile = friends[0];
        if (profile.faceURL && profile.faceURL.length > 0)
        {
            NSURL *avatarUrl = [NSURL URLWithString:profile.faceURL];
            NSImage *image = [[NSImage alloc] initWithContentsOfURL:avatarUrl];
            if ([NSThread isMainThread])
            {
                [ws.hostHeadImageView setImage:image];
            }
            else
            {
                dispatch_sync(dispatch_get_main_queue(), ^{
                    [ws.hostHeadImageView setImage:image];
                });
            }
        }
    } fail:nil];
    [_hostHeadImageView setImage:[NSImage imageNamed:@"default_head"]];
    
    NSArray *array = [item.name componentsSeparatedByString:@"_"];
    if (array.count > 2)//录制文件名 //录制用户
    {
        NSString *fileName = array[2];
        [_recordTitleTF setStringValue:[NSString stringWithFormat:@"录制标题:%@",fileName]];
        
        NSString *identifier = array[1];
        [_hostNameTF setStringValue:identifier];
    }
    if (array.count > 3)//录制时间
    {
        NSString *recStartTime = array[array.count-2];//倒数第二个是开始时间
        NSArray *recStartTimeArray = [recStartTime componentsSeparatedByString:@"-"];
        NSMutableString *dateString = [NSMutableString string];
        NSMutableString *timeString = [NSMutableString string];
        if (recStartTimeArray.count >= 6)
        {
            for (int index = 0; index < 3; index++)
            {
                [dateString appendFormat:@"%@-",recStartTimeArray[index]];
            }
            for (int index = 3; index < 6; index++)
            {
                [timeString appendFormat:@"%@:",recStartTimeArray[index]];
            }
            NSString *resultDate = [dateString substringToIndex:dateString.length-1];
            NSString *resultTime = [timeString substringToIndex:timeString.length-1];
            NSString *showInfo = [NSString stringWithFormat:@"%@  %@",resultDate,resultTime];
            [_recordTimeTF setStringValue:showInfo];
        }
        
    }
}

- (NSString *)downAndSaveToLocal
{
    if (!_item)
    {
        return nil;
    }
    if (_item.playurl.count <= 0)
    {
        return nil;
    }
    NSString *urlStr = _item.playurl[0];
    if (!(urlStr && urlStr.length > 0))
    {
        return nil;
    }
    NSString *videoId = _item.videoId;
    //判断截图文件是否存在
    NSString *path = [self isExitsFile:videoId];
    if (path)
    {
        return path;
    }
    NSString *tempDir = NSTemporaryDirectory();
    path = [NSString stringWithFormat:@"%@%@", tempDir, videoId];
    //视频截图
    AVURLAsset *urlAsset = [[AVURLAsset alloc] initWithURL:[NSURL URLWithString:urlStr] options:nil];
    AVAssetImageGenerator *imageGenerator = [[AVAssetImageGenerator alloc] initWithAsset:urlAsset];
    imageGenerator.appliesPreferredTrackTransform = YES;   // 截图的时候调整到正确的方向
    CMTime time = CMTimeMakeWithSeconds(1.0, 30);          // 1.0为截取视频1.0秒处的图片，30为每秒30帧
    CGImageRef cgImage = [imageGenerator copyCGImageAtTime:time actualTime:nil error:nil];
    NSImage *image = [[NSImage alloc] initWithCGImage:cgImage size:_recordCoverImageView.bounds.size];
    CGImageRelease(cgImage);
    
    //保存
    NSData *snapshotData = [image TIFFRepresentation];
    NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:snapshotData];
    [imageRep setSize:[[_recordCoverImageView image] size]];
    
    NSDictionary *imageProps = nil;
    NSNumber *quality = [NSNumber numberWithFloat:.85];
    imageProps = [NSDictionary dictionaryWithObject:quality forKey:NSImageCompressionFactor];
    NSData * snapshotData1 = [imageRep representationUsingType:NSJPEGFileType properties:imageProps];
    if (![[NSFileManager defaultManager] createFileAtPath:path contents:snapshotData1 attributes:nil])
    {
        return nil;
    }
    return path;
}

- (NSString *)isExitsFile:(NSString *)videoId
{
    NSString *tempDir = NSTemporaryDirectory();
    NSString *snapshotPath = [NSString stringWithFormat:@"%@%@", tempDir, videoId];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:snapshotPath])
    {
        return snapshotPath;
    }
    return nil;
}
@end
