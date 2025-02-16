#pragma once

//=============================================================================================================//
// Do not modify the following code!!!                                                                         //
//=============================================================================================================//
#include "MobileNotification.h"                                                                                //
#include "Internal/MobileNotificationModule.h"                                                                 //
#define MOBILE_NOTIFICATION_MODULE_POINTER  (FMobileNotificationModule::Get())                                 //
#define MOBILE_NOTIFICATION_CORE_POINTER    ((MOBILE_NOTIFICATION_MODULE_POINTER)->GetMobileNotification())    //
//=============================================================================================================//