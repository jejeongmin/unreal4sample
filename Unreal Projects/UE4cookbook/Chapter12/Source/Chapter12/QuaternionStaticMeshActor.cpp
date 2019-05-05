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

	// x 축을 기준으로 회전
	FQuat	quatX(FQuat(FVector(1, 0, 0), GetWorld()->TimeSeconds));

	/*
		쿼터니언 자체가 벡터이므로 회전할 수 있다.
		쿼터니언의 (x, y, z) 성분을 추출하고 정규화한 다음 해당 벡터를 회전하면 된다.
		회전하려는 각도를 가진 새로운 단위 벡터에서 새로운 쿼터니언을 만들자.
	*/
	FQuat	quatXY = FQuat(FVector(1, 0, 0), GetWorld()->TimeSeconds) * FQuat(FVector(0, 1, 0), GetWorld()->TimeSeconds);

	SetActorRotation(quatXY);
}