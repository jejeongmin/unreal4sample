// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperSideScrollerGameMode.h"
#include "SuperSideScrollerCharacter.h"
#include "UObject/ConstructorHelpers.h"

/*
*	gamemode 를 blueprint 로 상속 받아 정의해서 default pawn 을 지정하는 게 기본이지만, 아래 처럼 직접 native c++ 에서 지정해서 DefaultPawnClass 에 할당할 수도 있다.
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
