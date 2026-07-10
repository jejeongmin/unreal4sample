// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyKartsGameMode.h"
#include "CrazyKartsPlayerController.h"

ACrazyKartsGameMode::ACrazyKartsGameMode()
{
	PlayerControllerClass = ACrazyKartsPlayerController::StaticClass();
}
