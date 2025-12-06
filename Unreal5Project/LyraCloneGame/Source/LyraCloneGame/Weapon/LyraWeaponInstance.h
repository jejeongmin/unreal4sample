// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cosmetics/LyraCosmeticAnimationTypes.h"
#include "Equipment/LyraEquipmentInstance.h"
#include "LyraWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ULyraWeaponInstance : public ULyraEquipmentInstance
{
	GENERATED_BODY()
	
public:
	ULyraWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Weapon에 Equip/Unequip에 대한 Animation Set 정보를 들고 있다 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLyraAnimLayerSelectionSet EquippedAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLyraAnimLayerSelectionSet UnequippedAnimSet;
};
