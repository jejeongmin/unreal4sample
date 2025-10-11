// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraCloneGame.h"
#include "LyraLog.h"
#include "Modules/ModuleManager.h"

class FLyraCloneGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
		FDefaultGameModuleImpl::StartupModule();

		UE_LOG(LogTemp, Warning, TEXT("LyraCloneGame module has started!"));
		UE_LOG(LyraLog, Warning, TEXT("LyraCloneGame module has started!"));
	}
	virtual void ShutdownModule() override
	{
		// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
		// we call this function before unloading the module.
		FDefaultGameModuleImpl::ShutdownModule();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FLyraCloneGameModule, LyraCloneGame, "LyraCloneGame" );
