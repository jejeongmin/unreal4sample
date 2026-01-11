// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraWeaponUserInterface.h"
#include <Equipment/LyraEquipmentManagerComponent.h>
#include "Weapon/LyraWeaponInstance.h"

ULyraWeaponUserInterface::ULyraWeaponUserInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ULyraWeaponUserInterface::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Pawn을 가져오고
	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		// EquipmentManagerComponent를 활용하여, WeaponInstance를 가져오자
		if (ULyraEquipmentManagerComponent* EquipmentManager = Pawn->FindComponentByClass<ULyraEquipmentManagerComponent>())
		{
			if (ULyraWeaponInstance* NewInstance = EquipmentManager->GetFirstInstanceOfType<ULyraWeaponInstance>())
			{
				if (NewInstance != CurrentInstance && NewInstance->GetInstigator() != nullptr)
				{
					// 새로 업데이트해주고, OnWeaponChanged 호출 진행
					ULyraWeaponInstance* OldWeapon = CurrentInstance;
					CurrentInstance = NewInstance;
					OnWeaponChanged(OldWeapon, CurrentInstance);
				}
			}
		}
	}
}