// Copyright Epic Games, Inc. All Rights Reserved.

#include "MP_CppGameMode.h"
#include "MP_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMP_CppGameMode::AMP_CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
