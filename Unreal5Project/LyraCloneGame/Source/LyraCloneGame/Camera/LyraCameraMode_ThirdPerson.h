// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/LyraCameraMode.h"
#include "LyraCameraMode_ThirdPerson.generated.h"

class UCurveVector;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class LYRACLONEGAME_API ULyraCameraMode_ThirdPerson : public ULyraCameraMode
{
	GENERATED_BODY()
	
public:
	ULyraCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* ULyraCameraMode's interface
	*/
	virtual void UpdateView(float DeltaTime) override;

	/**
	 * member variables
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	TObjectPtr<const UCurveVector> TargetOffsetCurve;
};
