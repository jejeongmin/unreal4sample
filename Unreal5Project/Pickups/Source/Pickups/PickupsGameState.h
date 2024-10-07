// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PickupsGameState.generated.h"

/**
 * 
 */
UCLASS()
class PICKUPS_API APickupsGameState : public AGameState
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 PickupsRemaining;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 GameStateTick = 0;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	TArray<APlayerState*> GetPlayerStatesOrderedByScore() const;

public:

	void RemovePickup()	{ PickupsRemaining--; }

	bool HasPickups() const	{ return PickupsRemaining > 0; }

	void IncreaseGameStateTick() { ++GameStateTick;	}
	int32 GetGameStateTick() const { return GameStateTick; }
};
