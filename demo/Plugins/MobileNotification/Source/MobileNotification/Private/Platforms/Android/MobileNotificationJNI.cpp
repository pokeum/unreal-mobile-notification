#if PLATFORM_ANDROID

#include "Platforms/MobileNotificationDefinitions.h"
#include "TypeConverter.h"

extern "C" {

	/*
	 * Class:     co_pokeum_unreal_notifications_OnMessageReceivedListener
	 * Method:    onMessageReceived
	 * Signature: (Ljava/util/Map;)V
	 */
	JNIEXPORT void JNICALL Java_co_pokeum_unreal_notifications_OnMessageReceivedListener_onMessageReceived
	(JNIEnv *Env, jobject This, jobject JavaObject)
	{
		TMap<FString, FString> Data;
		if (TypeConverter::ConvertMap(Env, JavaObject, Data))
		{
			// Check if module is loaded
			if (MOBILE_NOTIFICATION_MODULE_POINTER)
			{
				MOBILE_NOTIFICATION_CORE_POINTER->HandleOnMessageReceived(Data);
			}
			else
			{	// If module is not loaded
				FMobileNotificationCore::UnhandledRemoteMessageData = Data;
			}
		}
	}

	/*
	 * Class:     co_pokeum_unreal_notifications_OnTokenRefreshListener
	 * Method:    OnTokenRefresh
	 * Signature: (Ljava/lang/String;)V
	 */
	JNIEXPORT void JNICALL Java_co_pokeum_unreal_notifications_OnTokenRefreshListener_OnTokenRefresh
	(JNIEnv *Env, jobject This, jstring JavaObject)
	{
		FString Token;
		if (TypeConverter::ConvertString(Env, JavaObject, Token))
		{
			// Check if module is loaded
			if (MOBILE_NOTIFICATION_MODULE_POINTER)
			{
				MOBILE_NOTIFICATION_CORE_POINTER->HandleOnTokenRefresh(Token);
			}
			else
			{	// If module is not loaded
				FMobileNotificationCore::UnhandledToken = Token;
			}	
		}
	}
}
#endif