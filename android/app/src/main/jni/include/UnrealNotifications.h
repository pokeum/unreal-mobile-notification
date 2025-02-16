#pragma once

#include <map>
#include <string>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     co_pokeum_unreal_notifications_OnMessageReceivedListener
 * Method:    onMessageReceived
 * Signature: (Ljava/util/Map;)V
 */
JNIEXPORT void JNICALL
Java_co_pokeum_unreal_notifications_OnMessageReceivedListener_onMessageReceived(JNIEnv *, jobject, jobject);

/*
 * Class:     co_pokeum_unreal_notifications_OnTokenRefreshListener
 * Method:    OnTokenRefresh
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_co_pokeum_unreal_notifications_OnTokenRefreshListener_OnTokenRefresh(JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif