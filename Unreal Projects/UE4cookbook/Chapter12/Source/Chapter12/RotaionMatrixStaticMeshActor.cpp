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
	�ٶ󺸴� ���� ���͸� ����� ��
	X��(����)�� �ٶ󺸰� �ϰ� Z��(����) ���Ϳ� �Բ� ȸ�� ����� �����Ѵ�.
*/
void ARotaionMatrixStaticMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector toTarget = target->GetActorLocation() - GetActorLocation();
	FMatrix	rotationMatrix = FRotationMatrix::MakeFromXZ(toTarget, GetActorUpVector());
	//FMatrix	rotationMatrix = FRotationMatrix::MakeFromX(toTarget);
	
	SetActorRotation(rotationMatrix.Rotator());	
}