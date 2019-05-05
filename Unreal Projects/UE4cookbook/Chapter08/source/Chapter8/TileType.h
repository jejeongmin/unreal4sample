// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TileType.generated.h"

/**
 * BlueprintType 로 class specifier 를 지정하면 블루프린트에서 새로운 타입으로 등록해 사용할 수 있다.
 */
UCLASS(BlueprintType)
class CHAPTER8_API UTileType : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 MovementCost;
	
	UPROPERTY()
	bool CanBeBuiltOn;

	UPROPERTY()
	FString TileName;


};
