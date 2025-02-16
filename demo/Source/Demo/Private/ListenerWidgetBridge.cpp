#include "ListenerWidgetBridge.h"

#include "DemoGameMode.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AListenerWidgetBridge::AListenerWidgetBridge() : ListenerWidget(nullptr)
{
 	// Set this actor to call Tick() every frame.
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AListenerWidgetBridge::BeginPlay()
{
	Super::BeginPlay();
}

// Called whenever this actor is being removed from a level
void AListenerWidgetBridge::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ADemoGameMode* DemoGameMode = GetDemoGameMode();
	if (DemoGameMode != nullptr && ListenerWidget != nullptr)
	{
		DemoGameMode->OnTokenRefreshDelegate.Unbind();
		DemoGameMode->OnMessageReceivedDelegate.Unbind();
	}
}

AListenerWidgetBridge* AListenerWidgetBridge::SetWidget(UUserWidget* Widget)
{
	if (Widget->GetClass()->ImplementsInterface(UMobileNotificationListenerInterface::StaticClass()))
	{
		ListenerWidget = Cast<IMobileNotificationListenerInterface>(Widget);
	}
	return this;
}

void AListenerWidgetBridge::SetBridge()
{
	ADemoGameMode* DemoGameMode = GetDemoGameMode();
	if (DemoGameMode != nullptr && ListenerWidget != nullptr)
	{
		DemoGameMode->OnTokenRefreshDelegate.BindUObject(this, &AListenerWidgetBridge::OnTokenRefresh);
		DemoGameMode->OnMessageReceivedDelegate.BindUObject(this, &AListenerWidgetBridge::OnMessageReceived);
	}
}

void AListenerWidgetBridge::OnTokenRefresh(const FString& Token)
{
	if (ListenerWidget != nullptr)
	{
		ListenerWidget->OnTokenRefresh(Token);
	}
}

void AListenerWidgetBridge::OnMessageReceived(const FRemoteMessage& RemoteMessage)
{
	if (ListenerWidget != nullptr)
	{
		ListenerWidget->OnMessageReceived(RemoteMessage);
	}
}

ADemoGameMode* AListenerWidgetBridge::GetDemoGameMode() const
{
	UWorld* TheWorld = GetWorld();
	if (TheWorld == nullptr)
	{
		return nullptr;
	}
	
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	ADemoGameMode* DemoGameMode = Cast<ADemoGameMode>(GameMode);
	return DemoGameMode;
}