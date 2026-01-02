// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "LyraPlayerController.generated.h"

class ULyraAbilitySystemComponent;
class ALyraPlayerState;

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ALyraPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	ALyraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* PlayerController interface
	*/
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	/**
	 * member methods
	 */
	ALyraPlayerState* GetLyraPlayerState() const;
	ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;
};
