#include "MobileNotification.h"

#include "Internal/MobileNotificationModule.h"

void UMobileNotification::RegisterForRemoteNotifications()
{
	FMobileNotificationModule::Get()->GetMobileNotification()->RegisterForRemoteNotifications();
}

FString UMobileNotification::GetDeviceToken()
{
	return FMobileNotificationModule::Get()->GetMobileNotification()->GetDeviceToken();
}

FString UMobileNotification::GetFirebaseToken()
{
	return FMobileNotificationModule::Get()->GetMobileNotification()->GetFirebaseToken();
}

void UMobileNotification::DeleteFirebaseToken()
{
	FMobileNotificationModule::Get()->GetMobileNotification()->DeleteFirebaseToken();
}

void UMobileNotification::ActivateMobileNotificationListener()
{
	FMobileNotificationModule::Get()->GetMobileNotification()->ActivateMobileNotificationListener();
}