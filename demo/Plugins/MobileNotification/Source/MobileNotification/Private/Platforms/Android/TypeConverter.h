#pragma once

#include "CoreMinimal.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

class TypeConverter
{
public:
	static bool ConvertString(JNIEnv *Env, jstring JavaObject, FString& CppObject);
	static bool ConvertMap(JNIEnv *Env, jobject JavaObject, TMap<FString, FString>& CppObject);
};
#endif