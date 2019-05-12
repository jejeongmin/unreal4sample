// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingCamera.h"

// Sets default values
AFloatingCamera::AFloatingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * speed;       //Scale our height by a factor of speed

	float DeltaHorizontal = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Y += DeltaHorizontal * speed;       //Scale our width by a factor of speed

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);

}
