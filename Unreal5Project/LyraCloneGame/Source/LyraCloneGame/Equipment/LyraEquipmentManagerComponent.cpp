// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LyraEquipmentManagerComponent.h"

ULyraEquipmentInstance* FLyraEquipmentList::AddEntry(TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition)
{
	return nullptr;
}

void FLyraEquipmentList::RemoveEntry(ULyraEquipmentInstance* Instance)
{
}

ULyraEquipmentManagerComponent::ULyraEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), EquipmentList(this)
{
}
