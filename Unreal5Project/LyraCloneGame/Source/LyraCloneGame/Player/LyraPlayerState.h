// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LyraPlayerState.generated.h"

class ULyraExperienceDefinition;
class ULyraPawnData;

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ALyraPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	 * AActor's interface
	 */
	virtual void PostInitializeComponents() final;

	/**
	 * member methods
	 */
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);

	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
