// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/LyraGameplayAbility.h"

ULyraGameplayAbility::ULyraGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivationPolicy = ELyraAbilityActivationPolicy::OnInputTriggered;
}