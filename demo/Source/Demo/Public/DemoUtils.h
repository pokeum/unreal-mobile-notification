#pragma once

#include "Demo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoUtils.generated.h"

UCLASS()
class DEMO_API UDemoUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void ShowToast(const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void CopyToClipboard(const FString& Label, const FString& Text);
	
	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static FString MapToString(const TMap<FString, FString>& Map);

	static void PrintCurrentThread(const FString& Tag, const FString& Identifier);
};