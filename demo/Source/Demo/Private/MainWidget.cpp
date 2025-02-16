#include "MainWidget.h"

#include "DemoUtils.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Clear Text Blocks
	ClearTextBlock(DeviceTokenTextBlock);
	ClearTextBlock(FirebaseTokenTextBlock);
	ClearTextBlock(OnTokenRefreshTextBlock);
	ClearTextBlock(MessageTextBlock);

	// Platform Panel Settings
	iOSPanel->SetVisibility(ESlateVisibility::Collapsed);
#if PLATFORM_IOS
	iOSPanel->SetVisibility(ESlateVisibility::Visible);
#endif

	InitButton();
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWidget::OnTokenRefresh(const FString& Token)
{
	UDemoUtils::ShowToast(TEXT("Token Refreshed!"));

	// Unreal Slate can only be accessed from the GameThread or the SlateLoadingThread!
	if (IsInGameThread())
	{
		SetTextBlock(OnTokenRefreshTextBlock, Token);
	}
	else
	{
		// Ensure the code runs on the game thread
		AsyncTask(ENamedThreads::GameThread, [this, Token]()
		{
			SetTextBlock(OnTokenRefreshTextBlock, Token);
		});
	}
}

void UMainWidget::OnMessageReceived(const FRemoteMessage& RemoteMessage)
{
	UDemoUtils::ShowToast(TEXT("Message Received!"));

	// Unreal Slate can only be accessed from the GameThread or the SlateLoadingThread!
	if (IsInGameThread())
	{
		SetTextBlock(MessageTextBlock, UDemoUtils::MapToString(RemoteMessage.Data));
	}
	else
	{
		// Ensure the code runs on the game thread
		AsyncTask(ENamedThreads::GameThread, [this, RemoteMessage]()
		{
			SetTextBlock(MessageTextBlock, UDemoUtils::MapToString(RemoteMessage.Data));
		});
	}	
}

void UMainWidget::OnClickCopyDeviceTokenButton()
{
	UDemoUtils::ShowToast(TEXT("Copy to Clipboard"));
	UDemoUtils::CopyToClipboard(TEXT("Device Token"), DeviceTokenTextBlock->Text.ToString());
}

void UMainWidget::OnClickGetDeviceTokenButton()
{
	SetTextBlock(DeviceTokenTextBlock, UMobileNotification::GetDeviceToken());
}

void UMainWidget::OnClickRegisterForRemoteNotificationsButton()
{
	UMobileNotification::RegisterForRemoteNotifications();
}

void UMainWidget::OnClickCopyFirebaseTokenButton()
{
	UDemoUtils::ShowToast(TEXT("Copy to Clipboard"));
	UDemoUtils::CopyToClipboard(TEXT("Firebase Token"), FirebaseTokenTextBlock->Text.ToString());
}

void UMainWidget::OnClickGetFirebaseTokenButton()
{
	SetTextBlock(FirebaseTokenTextBlock, UMobileNotification::GetFirebaseToken());
}

void UMainWidget::OnClickDeleteFirebaseTokenButton()
{
	UMobileNotification::DeleteFirebaseToken();
	ClearTextBlock(FirebaseTokenTextBlock);
}
	
void UMainWidget::OnClickCopyOnTokenRefreshButton()
{
	UDemoUtils::ShowToast(TEXT("Copy to Clipboard"));
	UDemoUtils::CopyToClipboard(TEXT("Firebase Token"), OnTokenRefreshTextBlock->Text.ToString());
}

void UMainWidget::OnClickResetOnTokenRefreshButton()
{
	ClearTextBlock(OnTokenRefreshTextBlock);
}

void UMainWidget::OnClickCopyMessageButton()
{
	UDemoUtils::ShowToast(TEXT("Copy to Clipboard"));
	UDemoUtils::CopyToClipboard(TEXT("Remote Message"), MessageTextBlock->Text.ToString());
}
	
void UMainWidget::OnClickResetMessageButton()
{
	ClearTextBlock(MessageTextBlock);
}

void UMainWidget::InitButton()
{
	if (!CopyDeviceTokenButton->OnClicked.IsBound())
		CopyDeviceTokenButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickCopyDeviceTokenButton);
	
	if (!GetDeviceTokenButton->OnClicked.IsBound())
		GetDeviceTokenButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickGetDeviceTokenButton);
	
	if (!RegisterForRemoteNotificationsButton->OnClicked.IsBound())
		RegisterForRemoteNotificationsButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickRegisterForRemoteNotificationsButton);
	
	if (!CopyFirebaseTokenButton->OnClicked.IsBound())
		CopyFirebaseTokenButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickCopyFirebaseTokenButton);
	
	if (!GetFirebaseTokenButton->OnClicked.IsBound())
		GetFirebaseTokenButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickGetFirebaseTokenButton);
	
	if (!DeleteFirebaseTokenButton->OnClicked.IsBound())
		DeleteFirebaseTokenButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickDeleteFirebaseTokenButton);
		
	if (!CopyOnTokenRefreshButton->OnClicked.IsBound())
		CopyOnTokenRefreshButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickCopyOnTokenRefreshButton);
		
	if (!ResetOnTokenRefreshButton->OnClicked.IsBound())
		ResetOnTokenRefreshButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickResetOnTokenRefreshButton);
        		
	if (!CopyMessageButton->OnClicked.IsBound())
		CopyMessageButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickCopyMessageButton);
                		
	if (!ResetMessageButton->OnClicked.IsBound())
		ResetMessageButton->OnClicked.AddDynamic(this, &UMainWidget::OnClickResetMessageButton);
}

void UMainWidget::SetTextBlock(UTextBlock* TextBlock, const FString& Text)
{
	TextBlock->SetText(FText::FromString(Text));
}

void UMainWidget::ClearTextBlock(UTextBlock* TextBlock)
{
	SetTextBlock(TextBlock, TEXT(""));
}