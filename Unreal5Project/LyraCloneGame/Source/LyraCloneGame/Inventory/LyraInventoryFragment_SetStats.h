// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LyraInventoryItemDefinition.h"
#include "LyraInventoryFragment_SetStats.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ULyraInventoryFragment_SetStats : public ULyraInventoryItemFragment
{
	GENERATED_BODY()
public:
	virtual void OnInstanceCreated(ULyraInventoryItemInstance* Instance) const override;

	/** InitialItemStats gives constructor's parameters for LyraGameplayTagStackContainer */
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TMap<FGameplayTag, int32> InitialItemStats;
};
