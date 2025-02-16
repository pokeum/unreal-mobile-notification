#pragma once

#include "Demo.h"
#include "Blueprint/UserWidget.h"
#include "MobileNotificationListenerInterface.h"
#include "MainWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class DEMO_API UMainWidget : public UUserWidget, public IMobileNotificationListenerInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	virtual void OnTokenRefresh(const FString& Token) override;
	virtual void OnMessageReceived(const FRemoteMessage& RemoteMessage) override;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* iOSPanel;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CopyDeviceTokenButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* GetDeviceTokenButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DeviceTokenTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RegisterForRemoteNotificationsButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CopyFirebaseTokenButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* GetFirebaseTokenButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DeleteFirebaseTokenButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FirebaseTokenTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CopyOnTokenRefreshButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetOnTokenRefreshButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* OnTokenRefreshTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CopyMessageButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetMessageButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MessageTextBlock;

	UFUNCTION()
	void OnClickCopyDeviceTokenButton();
	
	UFUNCTION()
	void OnClickGetDeviceTokenButton();

	UFUNCTION()
	void OnClickRegisterForRemoteNotificationsButton();
	
	UFUNCTION()
	void OnClickCopyFirebaseTokenButton();
	
	UFUNCTION()
	void OnClickGetFirebaseTokenButton();

	UFUNCTION()
	void OnClickDeleteFirebaseTokenButton();
	
	UFUNCTION()
	void OnClickCopyOnTokenRefreshButton();

	UFUNCTION()
	void OnClickResetOnTokenRefreshButton();

	UFUNCTION()
	void OnClickCopyMessageButton();
	
	UFUNCTION()
	void OnClickResetMessageButton();
	
private:
	void InitButton();

	void SetTextBlock(UTextBlock* TextBlock, const FString& Text);
	void ClearTextBlock(UTextBlock* TextBlock);
};
