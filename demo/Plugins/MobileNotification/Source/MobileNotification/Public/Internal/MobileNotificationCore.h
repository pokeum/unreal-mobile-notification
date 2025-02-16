#pragma once

#include "CoreMinimal.h"
#include "HAL/ThreadSafeBool.h"

class MOBILENOTIFICATION_API FMobileNotificationCore
{
public:

#pragma region iOS Only

	void RegisterForRemoteNotifications();
	
	FString GetDeviceToken();

#pragma endregion
	
	FString GetFirebaseToken();

	void DeleteFirebaseToken();

	void ActivateMobileNotificationListener();
	
	void HandleOnTokenRefresh(const FString& Token);
	
	void HandleOnMessageReceived(const TMap<FString, FString>& RemoteMessageData);

private:
	FThreadSafeBool IsMobileNotificationListenerActivated = false;

public:
	static FString UnhandledToken;
	static TMap<FString, FString> UnhandledRemoteMessageData;
};
