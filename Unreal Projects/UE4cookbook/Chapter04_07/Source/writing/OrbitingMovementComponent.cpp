// Fill out your copyright notice in the Description page of Project Settings.

#include "OrbitingMovementComponent.h"


// Sets default values for this component's properties
UOrbitingMovementComponent::UOrbitingMovementComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    //bWantsBeginPlay = true;   4.14에서 DEPRECATED됨. 이제는 무조건 BeginPlay호출됨
    PrimaryComponentTick.bCanEverTick = true;
    RotationSpeed = 5;
    OrbitDistance = 100;
    CurrentValue = 0;
    RotateToFaceOutwards = true;
}


// Called when the game starts
void UOrbitingMovementComponent::BeginPlay()
{
    Super::BeginPlay();
}


// Called every frame
void UOrbitingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 공식에서 각도보다는 라디안으로 표시되는 각도를 요구한다.
	// 라디안은 파이로 각도가 설명된다.
	// 처음에 DegreesToRadians 함수를 사용해 currentValue 를 각도에서 라디안으로 바꾼다.
    float CurrentValueInRadians = FMath::DegreesToRadians<float>(CurrentValue);

    SetRelativeLocation(
        FVector(OrbitDistance * FMath::Cos(CurrentValueInRadians),
            OrbitDistance * FMath::Sin(CurrentValueInRadians),
            RelativeLocation.Z));
    if (RotateToFaceOutwards)
    {
        FVector LookDir = (RelativeLocation).GetSafeNormal();
        FRotator LookAtRot = LookDir.Rotation();
        SetRelativeRotation(LookAtRot);
    }
    CurrentValue = FMath::Fmod(CurrentValue + (RotationSpeed* DeltaTime), 360);
    //...
}

