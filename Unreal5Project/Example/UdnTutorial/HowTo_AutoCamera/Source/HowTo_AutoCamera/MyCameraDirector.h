// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCameraDirector.generated.h"

USTRUCT()
struct FTest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		AActor* Camera;

	UPROPERTY(EditAnywhere)
		float TimeBetweenCameraChanges = 2.f;

	UPROPERTY(EditAnywhere)
		float SmoothBlendTime = 0.75f;

	UPROPERTY(EditAnywhere)
		bool  SmoothBlend = true;
};

UCLASS()
class HOWTO_AUTOCAMERA_API AMyCameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	FTest Cameras[2];

	UPROPERTY(EditAnywhere)
	int selectedCameraIndex = 0;

	float TimeToNextCameraChange;
};