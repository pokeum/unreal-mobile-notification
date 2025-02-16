#pragma once

#include "Demo.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MobileNotificationListenerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMobileNotificationListenerInterface : public UInterface
{
	GENERATED_BODY()
};

class DEMO_API IMobileNotificationListenerInterface
{
	GENERATED_BODY()

public:
	virtual void OnTokenRefresh(const FString& Token);
	
	virtual void OnMessageReceived(const FRemoteMessage& RemoteMessage);
};
