#include "DemoGameMode.h"

ADemoGameMode::ADemoGameMode()
{
	MobileNotificationListener = CreateDefaultSubobject<UMobileNotificationListener>(TEXT("MobileNotificationListener"));
}

void ADemoGameMode::BeginPlay()
{
	// Register listeners
	MobileNotificationListener->OnTokenRefresh.AddDynamic(this, &ADemoGameMode::OnTokenRefresh);
	MobileNotificationListener->OnMessageReceived.AddDynamic(this, &ADemoGameMode::OnMessageReceived);
  
	// Activate listeners
	UMobileNotification::ActivateMobileNotificationListener();
}

// Called by Mobile Notification when token is refreshed
void ADemoGameMode::OnTokenRefresh(const FString& Token)
{
	OnTokenRefreshDelegate.ExecuteIfBound(Token);
}

// Called by Mobile Notification when message is received
void ADemoGameMode::OnMessageReceived(const FRemoteMessage& RemoteMessage)
{
	OnMessageReceivedDelegate.ExecuteIfBound(RemoteMessage);
}