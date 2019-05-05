// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "QuaternionStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER12_API AQuaternionStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AQuaternionStaticMeshActor();

	virtual void Tick(float DeltaSeconds) override;
};
