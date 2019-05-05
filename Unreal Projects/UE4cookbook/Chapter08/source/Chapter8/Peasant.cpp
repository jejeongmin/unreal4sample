// Fill out your copyright notice in the Description page of Project Settings.

#include "Chapter8.h"

#include "Peasant.h"




APeasant::APeasant()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	IsRunAway = false;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

// 농민들이 도망가는 것을 텔레포트가 아니라 부드럽게 표시할 수 있다.
void APeasant::Flee(AKing* DeadKing)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Waily Waily!"));
	FVector FleeVector = GetActorLocation() - DeadKing->GetActorLocation();
	FleeVector.Normalize();
	FleeVector *= 500;
	TargetLocation = GetActorLocation() + FleeVector;
	IsRunAway = true;
}

/*
	IsRunAway 추가하지 않고 PrimaryActorTick 의 tick 관련 get/setter 로 해결해보려고 했는데 안되네.
	bStartWithTickEnabled 와 bCanEverTick 는 초기화 설정값으로 한번만 적용되고 이후 변경된 것에 대해서는 동작 안하는 듯.
*/
void APeasant::Tick(float DeltaSeconds)
{
	if (IsRunAway)
	{
		FVector CurrentLocation = GetActorLocation();

		SetActorLocation(FMath::Lerp(CurrentLocation, TargetLocation, 0.05));

		if (CurrentLocation.Equals(TargetLocation, 1.0f))
		{
			IsRunAway = false;
			//PrimaryActorTick.bCanEverTick = false;		// 이걸로 tick 을 끄려고 했는데 안꺼지고
			PrimaryActorTick.SetTickFunctionEnable(false);	// 이렇게 해야 꺼지네
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("stop run away!!"));
		}
	}
}
