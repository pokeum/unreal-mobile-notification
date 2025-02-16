#include "DemoUtils.h"

#include "HAL/ThreadManager.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#elif PLATFORM_IOS
#import "Platforms/iOS/SGToast.h"
#endif

void UDemoUtils::ShowToast(const FString& Msg)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "showToast", "(Ljava/lang/String;)V", false);
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringMsg);
	}
#elif PLATFORM_IOS
	[[SGToast singleton] message:Msg.GetNSString() duration:(float)1.0];
#endif
}

void UDemoUtils::CopyToClipboard(const FString& Label, const FString& Text)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "copyToClipboard", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		jstring JStringLabel = Env->NewStringUTF(TCHAR_TO_UTF8(*Label));
		jstring JStringText = Env->NewStringUTF(TCHAR_TO_UTF8(*Text)); 
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringLabel, JStringText);
	}
#elif PLATFORM_IOS
	UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
	pasteboard.string = Text.GetNSString();
#endif
}

FString UDemoUtils::MapToString(const TMap<FString, FString>& Map)
{
	// Build the string representation of the map (e.g. {key1=value1, key2=value2})
	bool isFirst = true;
	FString MapString = "{\n";
	for (const auto& Pair : Map)
	{
		if (!isFirst)
		{
			MapString += TEXT(",\n");
		}
		else
		{
			isFirst = false;
		}
		MapString += FString::Printf(TEXT("\t\"%s\": \"%s\""), *Pair.Key, *Pair.Value);
	}
	MapString += "\n}";
	return MapString;
}

void UDemoUtils::PrintCurrentThread(const FString& Tag, const FString& Identifier)
{
	uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
	FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);

	auto Message = FString::Printf(TEXT("[%s] Thread ID: %d"), *Identifier, ThreadId);
	if (!ThreadName.IsEmpty())
	{
		Message += FString::Printf(TEXT(" | Thread Name: %s"), *ThreadName);
	}
	UE_LOG(LogTemp, Display, TEXT("[%s] %s"), *Tag, *Message);
}