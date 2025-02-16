#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MobileNotificationListener.generated.h"

USTRUCT(BlueprintType)
struct FRemoteMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> Data;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenRefreshDelegate, const FString&, Token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceivedDelegate, const FRemoteMessage&, RemoteMessage);

UCLASS( ClassGroup=("Mobile Notification"), meta=(BlueprintSpawnableComponent) )
class MOBILENOTIFICATION_API UMobileNotificationListener : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMobileNotificationListener(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Mobile Notification")
	FOnTokenRefreshDelegate OnTokenRefresh;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Mobile Notification")
	FOnMessageReceivedDelegate OnMessageReceived;
};
