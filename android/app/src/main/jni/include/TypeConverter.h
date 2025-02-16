#pragma once

#include <map>
#include <string>
#include <jni.h>

class TypeConverter
{
public:
    static bool ConvertString(JNIEnv *Env, jstring JavaObject, std::string& CppObject);
    static bool ConvertMap(JNIEnv *Env, jobject JavaObject, std::map<std::string, std::string>& CppObject);
};