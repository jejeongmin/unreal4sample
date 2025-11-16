// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraPawnData.generated.h"

class ULyraCameraMode;
class ULyraInputConfig;

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ULyraPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	ULyraPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** Pawn¿« Class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;

	/** Camera Mode */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Camera")
	TSubclassOf<ULyraCameraMode> DefaultCameraMode;

	/** input configuration used by player controlled pawns to create input mappings and bind input actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|InputConfig")
	TObjectPtr<ULyraInputConfig> InputConfig;
};
