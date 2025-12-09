// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LyraWeaponInstance.h"
#include "LyraWeaponInstance.h"

ULyraWeaponInstance::ULyraWeaponInstance(const FObjectInitializer& ObjectInitializer)
{
}

TSubclassOf<UAnimInstance> ULyraWeaponInstance::PickBestAnimLayer(bool bEquipped,
	const FGameplayTagContainer& CosmeticTags) const
{
	const FLyraAnimLayerSelectionSet& SetToQuery = (bEquipped ? EquippedAnimSet : UnequippedAnimSet);
	return SetToQuery.SelectBestLayer(CosmeticTags);
}