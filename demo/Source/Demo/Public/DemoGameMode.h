#pragma once

#include "Demo.h"
#include "GameFramework/GameModeBase.h"
#include "DemoGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FOnTokenRefreshDelegateSignature, const FString&)
DECLARE_DELEGATE_OneParam(FOnMessageReceivedDelegateSignature, const FRemoteMessage&)

UCLASS()
class DEMO_API ADemoGameMode : public AGameModeBase
{
private:
	GENERATED_BODY()

public:
	ADemoGameMode();
	
protected:
	virtual void BeginPlay() override;
	
	// Method will be called by Mobile Notification when token is refreshed
	UFUNCTION()
	void OnTokenRefresh(const FString& Token);

	// Method will be called by Mobile Notification when message is received
	UFUNCTION()
	void OnMessageReceived(const FRemoteMessage& RemoteMessage);

	// Register listeners through component
	UPROPERTY()
	UMobileNotificationListener* MobileNotificationListener;

public:
	FOnTokenRefreshDelegateSignature OnTokenRefreshDelegate;
	FOnMessageReceivedDelegateSignature OnMessageReceivedDelegate;
};
