#include "UnrealNotifications.h"

#include "Logger.h"
#include "TypeConverter.h"

JNIEXPORT void JNICALL Java_co_pokeum_unreal_notifications_OnMessageReceivedListener_onMessageReceived
(JNIEnv *Env, jobject This, jobject JavaObject)
{
    std::map<std::string, std::string> Data;
    if (TypeConverter::ConvertMap(Env, JavaObject, Data))
    {
        LOG_DEBUG("==================== OnMessageReceived ==================");
        LOG_DEBUG("{");
        for (const auto& entry: Data) {
            LOG_DEBUG("\t\"%s\": \"%s\",", entry.first.c_str(), entry.second.c_str());
        }
        LOG_DEBUG("}");
    }
}

JNIEXPORT void JNICALL Java_co_pokeum_unreal_notifications_OnTokenRefreshListener_OnTokenRefresh
(JNIEnv *Env, jobject This, jstring JavaObject)
{
    std::string Token;
    if (TypeConverter::ConvertString(Env, JavaObject, Token))
    {
        LOG_DEBUG("==================== OnTokenRefresh ==================");
        LOG_DEBUG("%s", Token.c_str());
    }
}