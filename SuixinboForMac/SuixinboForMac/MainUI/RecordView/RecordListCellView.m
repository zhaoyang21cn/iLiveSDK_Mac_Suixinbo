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
    _dateFormatter = [[NSDateFormatter alloc] init];
    [_dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
}

- (void)configWith:(RecordVideoItem *)item
{
    if (!item)
    {
        return;
    }
    _item = item;
    __weak typeof(self)ws = self;
    
    //封面
    [_recordCoverImageView setImage:[NSImage imageNamed:@"defaul_publishcover"]];
    if (_item.cover && item.cover.length > 0) {
        NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:_item.cover]];
        NSImage *image = [[NSImage alloc] initWithData:data];
        [_recordCoverImageView setImage:image];
    }
    
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
    
    //录制文件名
    [_recordTitleTF setStringValue:_item.name];
    //录制用户名
    [_hostNameTF setStringValue:_item.uid];
    //录制时间
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:[_item.createTime integerValue]];
    NSString *timeStr = [self.dateFormatter stringFromDate:date];
    [_recordTimeTF setStringValue:[NSString stringWithFormat:@"%@",timeStr]];
    //录制时长
    NSInteger duration = [_item.duration integerValue];
    NSInteger sec = duration % 60;
    NSInteger minu = (duration/60) % 60;
    NSInteger hour = duration/3600;
    if (hour>0)
    {
        NSString *showTime = [NSString stringWithFormat:@"%2ld小时%2ld分%2ld秒",hour,minu,sec];
        [_recordDuration setStringValue:showTime];
    }
    else
    {
        if (minu>0)
        {
            NSString *showTime = [NSString stringWithFormat:@"%2ld分%2ld秒",minu,sec];
            [_recordDuration setStringValue:showTime];
        }
        else
        {
            NSString *showTime = [NSString stringWithFormat:@"%2ld秒",sec];
            [_recordDuration setStringValue:showTime];
        }
    }
    
    //录制文件大小
    if (_item.fileSize) {
        NSString *size = [self convertFileSize:[_item.fileSize integerValue]];
        [_recordSize setStringValue:size];
    }
}

- (NSString *)convertFileSize:(long long)size
{
    long kb = 1024;
    long mb = kb * 1024;
    long gb = mb * 1024;
    
    if (size >= gb) {
        return [NSString stringWithFormat:@"%.1fGB", (float) size / gb];
    } else if (size >= mb) {
        float f = (float) size / mb;
        if (f > 100) {
            return [NSString stringWithFormat:@"%.0fMB", f];
        }else{
            return [NSString stringWithFormat:@"%.1fMB", f];
        }
    } else if (size >= kb) {
        float f = (float) size / kb;
        if (f > 100) {
            return [NSString stringWithFormat:@"%.0fKB", f];
        }else{
            return [NSString stringWithFormat:@"%.1fKB", f];
        }
    } else
        return [NSString stringWithFormat:@"%lldB", size];
}

/*
 //手动录制时，需要用到下面的代码解析
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
}*/
@end
