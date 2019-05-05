// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "RotatorStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER12_API ARotatorStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ARotatorStaticMeshActor();

	virtual void Tick(float DeltaSeconds) override;	
};
