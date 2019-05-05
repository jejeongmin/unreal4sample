// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "RotaionMatrixStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER12_API ARotaionMatrixStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ARotaionMatrixStaticMeshActor();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		AStaticMeshActor*	target;
};
