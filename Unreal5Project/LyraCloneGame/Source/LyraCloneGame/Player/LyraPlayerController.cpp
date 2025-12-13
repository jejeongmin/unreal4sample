// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyraPlayerController.h"
#include "Camera/LyraPlayerCameraManager.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Player/LyraPlayerState.h"

ALyraPlayerController::ALyraPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ALyraPlayerCameraManager::StaticClass();
}


void ALyraPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	// 우선 PostProcessInput()가 언제 호출되는지 확인해보자:
	// - UPlayerInput::ProcessInputStack()에서 호출된다

	if (ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	{
		LyraASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

ALyraPlayerState* ALyraPlayerController::GetLyraPlayerState() const
{
	// ECastCheckedType의 NullAllowed는 Null 반환을 의도할 경우 유용하다
	return CastChecked<ALyraPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

ULyraAbilitySystemComponent* ALyraPlayerController::GetLyraAbilitySystemComponent() const
{
	const ALyraPlayerState* LyraPS = GetLyraPlayerState();
	return (LyraPS ? LyraPS->GetLyraAbilitySystemComponent() : nullptr);
}
