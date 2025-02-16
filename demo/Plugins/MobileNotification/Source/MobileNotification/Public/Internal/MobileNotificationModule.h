#pragma once

#include "MobileNotificationCore.h"
#include "Modules/ModuleManager.h"

typedef TSharedPtr<FMobileNotificationCore, ESPMode::ThreadSafe> FMobileNotificationCorePointer;

class FMobileNotificationModule : public IModuleInterface
{
public:
	static inline FMobileNotificationModule* Get()
	{
		return FModuleManager::LoadModulePtr<FMobileNotificationModule>("MobileNotification");
	}
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	inline FMobileNotificationCorePointer GetMobileNotification() const
	{
		return MobileNotificationCorePointer;
	}

protected:
	FMobileNotificationCorePointer MobileNotificationCorePointer;
};