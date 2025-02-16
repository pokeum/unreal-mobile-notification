#pragma once

#include "Demo.h"
#include "GameFramework/Actor.h"
#include "MobileNotificationListenerInterface.h"
#include "ListenerWidgetBridge.generated.h"

UCLASS()
class DEMO_API AListenerWidgetBridge : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AListenerWidgetBridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called whenever this actor is being removed from a level
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Demo|Listener Widget Bridge")
	UPARAM(DisplayName = "Return Target") AListenerWidgetBridge* SetWidget(UPARAM(DisplayName = "Listener Widget") UUserWidget* Widget);
	
	UFUNCTION(BlueprintCallable, Category = "Demo|Listener Widget Bridge")
	void SetBridge();

private:
	IMobileNotificationListenerInterface* ListenerWidget;

	UFUNCTION()
	void OnTokenRefresh(const FString& Token);
	
	UFUNCTION()
	void OnMessageReceived(const FRemoteMessage& RemoteMessage);

	class ADemoGameMode* GetDemoGameMode() const;
};
