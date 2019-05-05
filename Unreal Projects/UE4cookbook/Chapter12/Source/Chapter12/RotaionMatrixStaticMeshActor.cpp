// Fill out your copyright notice in the Description page of Project Settings.

#include "RotaionMatrixStaticMeshActor.h"

ARotaionMatrixStaticMeshActor::ARotaionMatrixStaticMeshActor()
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

/*
	바라보는 방향 벡터를 계산한 후
	X축(정면)을 바라보게 하고 Z축(상향) 벡터와 함께 회전 행렬을 구성한다.
*/
void ARotaionMatrixStaticMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector toTarget = target->GetActorLocation() - GetActorLocation();
	FMatrix	rotationMatrix = FRotationMatrix::MakeFromXZ(toTarget, GetActorUpVector());
	//FMatrix	rotationMatrix = FRotationMatrix::MakeFromX(toTarget);
	
	SetActorRotation(rotationMatrix.Rotator());	
}