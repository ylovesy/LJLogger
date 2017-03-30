//
//  LJLogger.h
//  LJLogger
//
//  Created by yangyiyang on 2017-03-27.
//  Copyright © 2017 lianjia. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, LJLogMode)
{
    LJLogModeAsync,
    LJLogModeSync
};

typedef NS_ENUM(NSInteger, LJLogLevel)
{
    LJLogLevelAll = 0,
    LJLogLevelVerbose = 0,
    LJLogLevelDebug,    // Detailed information on the flow through the system.
    LJLogLevelInfo,     // Interesting runtime events (startup/shutdown), should be conservative and keep to a minimum.
    LJLogLevelWarn,     // Other runtime situations that are undesirable or unexpected, but not necessarily "wrong".
    LJLogLevelError,    // Other runtime errors or unexpected conditions.
    LJLogLevelFatal,    // Severe errors that cause premature termination.
    LJLogLevelNone,     // Special level used to disable all log messages.
};

@interface LJLogger : NSObject

//log
+ (BOOL)shouldLog:(LJLogLevel)level;

+ (void)logWithLevel:(LJLogLevel)logLevel moduleName:(const char*)moduleName fileName:(const char*)fileName lineNumber:(int)lineNumber funcName:(const char*)funcName message:(NSString *)message;
+ (void)logWithLevel:(LJLogLevel)logLevel moduleName:(const char*)moduleName fileName:(const char*)fileName lineNumber:(int)lineNumber funcName:(const char*)funcName format:(NSString *)format, ...;

//configuration
+ (void)openLogger:(LJLogMode)mode path:(NSString *)logPath namePrefix:(NSString *)prefix;
+ (void)closeLogger;

+ (void)setLoggerLevel:(LJLogLevel)level;
+ (void)setEnableConsoleLog:(BOOL)flag;

+ (void)flushLogger;

@end
