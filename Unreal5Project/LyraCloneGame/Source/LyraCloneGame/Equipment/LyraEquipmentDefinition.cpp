// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LyraEquipmentDefinition.h"
#include "Equipment/LyraEquipmentInstance.h"
#include "LyraEquipmentDefinition.h"

ULyraEquipmentDefinition::ULyraEquipmentDefinition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 기본값으로, ULyraEquipmentInstance로 설정
	InstanceType = ULyraEquipmentInstance::StaticClass();
}
