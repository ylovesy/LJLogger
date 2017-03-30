//
//  LJLogger.m
//  LJLogger
//
//  Created by yangyiyang on 2017-03-27.
//  Copyright © 2017 lianjia. All rights reserved.
//

#import "LJLogger.h"
#import <sys/xattr.h>

#import <Log/xlog/xlogger.h>
#import <Log/xlog/appender.h>

static NSUInteger g_processID = 0;

@implementation LJLogger

+ (void)logWithLevel:(LJLogLevel)logLevel moduleName:(const char*)moduleName fileName:(const char*)fileName lineNumber:(int)lineNumber funcName:(const char*)funcName message:(NSString *)message {
    
    XLoggerInfo info;
    info.level = (TLogLevel)logLevel;
    info.tag = moduleName;
    info.filename = fileName;
    info.func_name = funcName;
    info.line = lineNumber;
    gettimeofday(&info.timeval, NULL);
    info.tid = (uintptr_t)[NSThread currentThread];
    info.maintid = (uintptr_t)[NSThread mainThread];
    info.pid = g_processID;
    xlogger_Write(&info, message.UTF8String);
}

+ (void)logWithLevel:(LJLogLevel)logLevel moduleName:(const char*)moduleName fileName:(const char*)fileName lineNumber:(int)lineNumber funcName:(const char*)funcName format:(NSString *)format, ... {
    if ([self shouldLog:logLevel]) {
        va_list argList;
        va_start(argList, format);
        NSString* message = [[NSString alloc] initWithFormat:format arguments:argList];
        [self logWithLevel:logLevel moduleName:moduleName fileName:fileName lineNumber:lineNumber funcName:funcName message:message];
        va_end(argList);
    }
}

+ (BOOL)shouldLog:(LJLogLevel)level {
    
    if (level >= xlogger_Level()) {
        return YES;
    }
    
    return NO;
}

+ (void)openLogger:(LJLogMode)mode path:(NSString *)logPath namePrefix:(NSString *)prefix
{
    const char* attrName = "com.apple.MobileBackup";
    u_int8_t attrValue = 1;
    setxattr([logPath UTF8String], attrName, &attrValue, sizeof(attrValue), 0, 0);

    const char*prefixName = prefix ? [prefix UTF8String] : "Log";
    switch (mode) {
        case LJLogModeAsync:
            appender_open(kAppednerAsync, [logPath UTF8String], prefixName);
            break;
        case LJLogModeSync:
            appender_open(kAppednerSync, [logPath UTF8String], prefixName);
            break;
        default:
            appender_open(kAppednerAsync, [logPath UTF8String], prefixName);
            break;
    }
}

+ (void)closeLogger
{
    appender_close();
}

+ (void)setLoggerLevel:(LJLogLevel)level
{
    xlogger_SetLevel((TLogLevel)level);
}

+ (void)setEnableConsoleLog:(BOOL)flag
{
    appender_set_console_log(flag);
}

+ (void)flushLogger
{
    appender_flush();
}

@end
