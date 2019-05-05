// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatorStaticMeshActor.h"

ARotatorStaticMeshActor::ARotatorStaticMeshActor()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void ARotatorStaticMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	int	rotateSpeed = 10;

	FRotator	rotator(0, GetWorld()->TimeSeconds * rotateSpeed, 0);

	SetActorRotation(rotator);
}