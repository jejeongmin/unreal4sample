#pragma once

#include "LyraInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"
#include "LyraInventoryFragment_EquippableItem.generated.h"

/** forward declaration */
class ULyraEquipmentDefinition;

UCLASS()
class ULyraInventoryFragment_EquippableItem : public ULyraInventoryItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Lyra)
	TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition;
};