// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MP_PlayerController.generated.h"

class UMP_PickupCountWidget;
/**
 * 
 */
UCLASS()
class MP_CPP_API AMP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMP_PickupCountWidget> PickupCountWidgetClass;

	UPROPERTY()
	TObjectPtr<UMP_PickupCountWidget> PickupCountWidget;

	UFUNCTION()
	void OnPickupCountChanged(int32 Count);
};
