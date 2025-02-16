#pragma once

#include <android/log.h>

#define LOG_TAG                 "UE-MobileNotification"
#define LOG_VERBOSE(...)        ((void)__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#define LOG_DEBUG(...)          ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOG_INFO(...)           ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOG_WARN(...)           ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOG_ERROR(...)          ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOG_FATAL(...)          ((void)__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__))