// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PickupsPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PICKUPS_API APickupsPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 Pickups;

	UPROPERTY(Replicated)
	int32 PlayerStateTick = 0;

public:

	void AddPickup() { Pickups++; }

	void IncreasePlayerStateTick() { ++PlayerStateTick; }

	int32	GetPlayerStateTick() { return PlayerStateTick; }
};
