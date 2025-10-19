// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LyraGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ALyraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALyraGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;


	void HandleMatchAssignmentIfNotExpectingOne();
};
