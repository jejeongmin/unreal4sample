// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperSideScrollerGameMode.h"
#include "SuperSideScrollerCharacter.h"
#include "UObject/ConstructorHelpers.h"

/*
*	gamemode �� blueprint �� ��� �޾� �����ؼ� default pawn �� �����ϴ� �� �⺻������, �Ʒ� ó�� ���� native c++ ���� �����ؼ� DefaultPawnClass �� �Ҵ��� ���� �ִ�.
*/
ASuperSideScrollerGameMode::ASuperSideScrollerGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MainCharacter/Blueprints/BP_SuperSideScroller_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
