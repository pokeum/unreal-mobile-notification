#include "Internal/MobileNotificationCore.h"
#include "Internal/MobileNotificationListener.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#elif PLATFORM_IOS
#include "Platforms/iOS/MNPlugin.h"
#endif

FString FMobileNotificationCore::UnhandledToken;
TMap<FString, FString> FMobileNotificationCore::UnhandledRemoteMessageData;

#pragma region iOS Only

void FMobileNotificationCore::RegisterForRemoteNotifications()
{
#if PLATFORM_IOS
	[MNPlugin registerForRemoteNotifications];
#endif
}

FString FMobileNotificationCore::GetDeviceToken()
{
#if PLATFORM_IOS
	return FString([MNPlugin getDeviceToken]);
#endif
	return TEXT("");
}

#pragma endregion

FString FMobileNotificationCore::GetFirebaseToken()
{
	FString FirebaseToken = TEXT("");	// Empty String
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Jmethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getFirebaseToken", "()Ljava/lang/String;", false);
		jstring JstringFirebaseToken = (jstring) FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Jmethod);
		
		if (JstringFirebaseToken != nullptr)
		{
			FirebaseToken = FJavaHelper::FStringFromParam(Env, JstringFirebaseToken);
		}
	}
#elif PLATFORM_IOS
	FirebaseToken = FString([MNPlugin getFirebaseToken]);
#endif
	return FirebaseToken;
}

void FMobileNotificationCore::DeleteFirebaseToken()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Jmethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "deleteFirebaseToken", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Jmethod);
	}
#elif PLATFORM_IOS
	[MNPlugin deleteFirebaseToken];
#endif
}

void FMobileNotificationCore::ActivateMobileNotificationListener()
{
	if (!IsMobileNotificationListenerActivated.AtomicSet(true))
	{
		if (!UnhandledToken.IsEmpty())
		{
			HandleOnTokenRefresh(UnhandledToken);
		}
		if (UnhandledRemoteMessageData.Num() != 0)
		{
			HandleOnMessageReceived(UnhandledRemoteMessageData);
		}
	}
}

void FMobileNotificationCore::HandleOnTokenRefresh(const FString& Token)
{
	if (IsMobileNotificationListenerActivated)
	{
		for (TObjectIterator<UMobileNotificationListener> Itr; Itr; ++Itr)
     	{
     		Itr->OnTokenRefresh.Broadcast(Token);
     	}
		UnhandledToken = TEXT("");	// Reset
	}
	else
	{
		UnhandledToken = Token;
	}
}

void FMobileNotificationCore::HandleOnMessageReceived(const TMap<FString, FString>& RemoteMessageData)
{
	if (IsMobileNotificationListenerActivated)
	{
		for (TObjectIterator<UMobileNotificationListener> Itr; Itr; ++Itr)
		{
			Itr->OnMessageReceived.Broadcast(FRemoteMessage {RemoteMessageData});
		}
		UnhandledRemoteMessageData.Empty();	// Reset
	}
	else
	{
		UnhandledRemoteMessageData = RemoteMessageData;
	}
}