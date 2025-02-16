#include "Internal/MobileNotificationModule.h"

#if PLATFORM_IOS
#include "Platforms/iOS/MNAppDelegate.h"
#endif

#define LOCTEXT_NAMESPACE "FMobileNotification"

void FMobileNotificationModule::StartupModule()
{
	MobileNotificationCorePointer = MakeShareable(new FMobileNotificationCore());

#if PLATFORM_IOS
	[MNAppDelegate load];
#endif
}

void FMobileNotificationModule::ShutdownModule()
{
#if PLATFORM_IOS
	[MNAppDelegate unregisterLifeCycleListener];
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMobileNotificationModule, MobileNotification)