// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OwnershipTestActor.generated.h"

UCLASS()
class PICKUPS_API AOwnershipTestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOwnershipTestActor();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ownership Test Actor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ownership Test Actor")
	float OwnershipRadius = 400.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
