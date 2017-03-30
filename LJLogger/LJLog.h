//
//  LJLog.h
//  LJLogger
//
//  Created by yangyiyang on 2017-03-27.
//  Copyright © 2017 lianjia. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LJLogger.h"

#if LIANJIA_LOG == 1
#ifdef DDLogDebug
#undef DDLogDebug
#endif
#define DDLogDebug(format, ...) LJDebug(format, ##__VA_ARGS__)
#ifdef NSLog
#undef NSLog
#endif
#define NSLog(format, ...) LJInfo(format, ##__VA_ARGS__)
#ifdef DDLogInfo
#undef DDLogInfo
#endif
#define DDLogInfo(format, ...) LJInfo(format, ##__VA_ARGS__)
#ifdef DDLogWarn
#undef DDLogWarn
#endif
#define DDLogWarn(format, ...) LJWarn(format, ##__VA_ARGS__)
#ifdef DDLogError
#undef DDLogError
#endif
#define DDLogError(format, ...) LJError(format, ##__VA_ARGS__)
#ifdef DDLogVerbose
#undef DDLogVerbose
#endif
#define DDLogVerbose(format, ...) LJVerbose(format, ##__VA_ARGS__)
#endif

#define __FILENAME__ (strrchr(__FILE__,'/')+1)

#define LJDebug(format, ...)    LJDebugWithModule(NULL, format, ##__VA_ARGS__)
#define LJInfo(format, ...)     LJInfoWithModule(NULL, format, ##__VA_ARGS__)
#define LJWarn(format, ...)     LJWarnWithModule(NULL, format, ##__VA_ARGS__)
#define LJError(format, ...)    LJErrorWithModule(NULL, format, ##__VA_ARGS__)
#define LJVerbose(format, ...)    LJVerboseWithModule(NULL, format, ##__VA_ARGS__)

#define LJDebugWithModule(module, format, ...) \
LJDebugInternal(module, __FILENAME__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LJInfoWithModule(module, format, ...) \
LJInfoInternal(module, __FILENAME__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LJWarnWithModule(module, format, ...) \
LJWarnInternal(module, __FILENAME__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LJErrorWithModule(module, format, ...) \
LJErrorInternal(module, __FILENAME__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LJVerboseWithModule(module, format, ...) \
LJVerboseInternal(module, __FILENAME__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#define LJDebugInternal(module, file, line, func, format, ...) \
LJLogInternal(LJLogLevelDebug, module, file, line, func, @"Debug:", format, ##__VA_ARGS__)
#define LJInfoInternal(module, file, line, func, format, ...) \
LJLogInternal(LJLogLevelInfo, module, file, line, func, @"Info:", format, ##__VA_ARGS__)
#define LJWarnInternal(module, file, line, func, format, ...) \
LJLogInternal(LJLogLevelWarn, module, file, line, func, @"Warn:", format, ##__VA_ARGS__)
#define LJErrorInternal(module, file, line, func, format, ...) \
LJLogInternal(LJLogLevelError, module, file, line, func, @"Error:", format, ##__VA_ARGS__)
#define LJVerboseInternal(module, file, line, func, format, ...) \
LJLogInternal(LJLogLevelVerbose, module, file, line, func, @"Verbose:", format, ##__VA_ARGS__)

#define LJLogInternal(level, module, file, line, func, prefix, format, ...) \
do { \
    if ([LJLogger shouldLog:level]) { \
        NSString *aMessage = [NSString stringWithFormat:@"%@%@", prefix, [NSString stringWithFormat:format, ##__VA_ARGS__, nil]]; \
        [LJLogger logWithLevel:level moduleName:module fileName:file lineNumber:line funcName:func message:aMessage]; \
    } \
} while(0)
