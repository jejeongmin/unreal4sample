// Fill out your copyright notice in the Description page of Project Settings.

#include "Chapter8.h"
#include "OnConstructionActor.h"





void AOnConstructionActor::OnConstruction(const FTransform& Transform)
{
	GetStaticMeshComponent()->SetVisibility(ShowStaticMesh);
}

/*
	PostEditrChangeProperty 를 사용한 것처럼 특정 property 를 명시적으로 필터링하진 않는다.
	그런 이유로 OnConstructioin 스크립트는 객체에서 변경되는 모든 property 에 대해 전체적으로 실행된다.
	방금 편집된 property 를 테스트할 수 있는 방법이 없으므로
	계산 집약적인 코드를 배치하는 것에 대해서는 신중해야 한다.
*/
AOnConstructionActor::AOnConstructionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	ShowStaticMesh = true;
}
