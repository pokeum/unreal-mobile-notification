#include "TypeConverter.h"

bool TypeConverter::ConvertString(JNIEnv *Env, jstring JavaObject, std::string& CppObject)
{
    if (JavaObject == nullptr) { return false; }

    const char* UTFString = Env->GetStringUTFChars(JavaObject, nullptr);
    if (UTFString == nullptr) { return false; }

    CppObject = std::string(UTFString);

    // Release heap memory
    Env->ReleaseStringUTFChars(JavaObject, UTFString);
    Env->DeleteLocalRef(JavaObject);

    return true;
}

bool TypeConverter::ConvertMap(JNIEnv *Env, jobject JavaObject, std::map<std::string, std::string>& CppObject)
{
    if (JavaObject == nullptr) { return false; }

    // Get Map class
    jclass MapClass = Env->FindClass("java/util/Map");
    if (MapClass == nullptr) { return false; }

    // Get "entrySet" method of Map class
    jmethodID EntrySetMethod = Env->GetMethodID(MapClass, "entrySet", "()Ljava/util/Set;");
    if (EntrySetMethod == nullptr) { return false; }

    // Get Set<Map.Entry<String, String>> of Java Object Map
    jobject EntrySet = Env->CallObjectMethod(JavaObject, EntrySetMethod);
    if (EntrySet == nullptr) { return false; }

    // Obtain an iterator over the Set
    jclass SetClass = Env->FindClass("java/util/Set");
    if (SetClass == nullptr) { return false; }
    jmethodID IteratorMethod = Env->GetMethodID(SetClass, "iterator", "()Ljava/util/Iterator;");
    if (IteratorMethod == nullptr) { return false; }
    jobject Iterator = Env->CallObjectMethod(EntrySet, IteratorMethod);
    if (Iterator == nullptr) { return false; }

    // Get the Iterator method IDs
    jclass IteratorClass = Env->FindClass("java/util/Iterator");
    if (IteratorClass == nullptr) { return false; }
    jmethodID HasNextMethod = Env->GetMethodID(IteratorClass, "hasNext", "()Z");
    if (HasNextMethod == nullptr) { return false; }
    jmethodID NextMethod = Env->GetMethodID(IteratorClass, "next", "()Ljava/lang/Object;");
    if (NextMethod == nullptr) { return false; }

    // Get the Entry class method IDs
    jclass Map$EntryClass = Env->FindClass("java/util/Map$Entry");
    if (Map$EntryClass == nullptr) { return false; }
    jmethodID GetKeyMethod = Env->GetMethodID(Map$EntryClass, "getKey", "()Ljava/lang/Object;");
    if (GetKeyMethod == nullptr) { return false; }
    jmethodID GetValueMethod = Env->GetMethodID(Map$EntryClass, "getValue", "()Ljava/lang/Object;");
    if (GetValueMethod == nullptr) { return false; }

    // Iterate over the entry Set
    while (Env->CallBooleanMethod(Iterator, HasNextMethod))
    {
        jobject Entry = Env->CallObjectMethod(Iterator, NextMethod);

        std::string Key, Value;
        if (!ConvertString(Env, (jstring) Env->CallObjectMethod(Entry, GetKeyMethod), Key)) { return false; }
        if (!ConvertString(Env, (jstring) Env->CallObjectMethod(Entry, GetValueMethod), Value)) { return false; }

        CppObject.insert({ Key, Value });

        // Release heap memory
        Env->DeleteLocalRef(Entry);
    }
    return true;
}