#pragma once

//======================================================//
// Mobile Notification Header Files                     //
//======================================================//
#include "Internal/MobileNotificationListener.h"        //
//======================================================//

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MobileNotification.generated.h"

UCLASS()
class MOBILENOTIFICATION_API UMobileNotification : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Mobile Notification|iOS Only")
	static void RegisterForRemoteNotifications();
	
	UFUNCTION(BlueprintCallable, Category = "Mobile Notification|iOS Only")
	static UPARAM(DisplayName = "Token") FString GetDeviceToken();
	
	UFUNCTION(BlueprintCallable, Category = "Mobile Notification")
	static UPARAM(DisplayName = "Token") FString GetFirebaseToken();

	UFUNCTION(BlueprintCallable, Category = "Mobile Notification")
	static void DeleteFirebaseToken();

	UFUNCTION(BlueprintCallable, Category = "Mobile Notification")
	static void ActivateMobileNotificationListener();
};