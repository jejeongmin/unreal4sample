// Fill out your copyright notice in the Description page of Project Settings.

#include "QuaternionStaticMeshActor.h"

AQuaternionStaticMeshActor::AQuaternionStaticMeshActor()
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

void AQuaternionStaticMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// x ���� �������� ȸ��
	FQuat	quatX(FQuat(FVector(1, 0, 0), GetWorld()->TimeSeconds));

	/*
		���ʹϾ� ��ü�� �����̹Ƿ� ȸ���� �� �ִ�.
		���ʹϾ��� (x, y, z) ������ �����ϰ� ����ȭ�� ���� �ش� ���͸� ȸ���ϸ� �ȴ�.
		ȸ���Ϸ��� ������ ���� ���ο� ���� ���Ϳ��� ���ο� ���ʹϾ��� ������.
	*/
	FQuat	quatXY = FQuat(FVector(1, 0, 0), GetWorld()->TimeSeconds) * FQuat(FVector(0, 1, 0), GetWorld()->TimeSeconds);

	SetActorRotation(quatXY);
}