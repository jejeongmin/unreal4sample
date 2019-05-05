// Fill out your copyright notice in the Description page of Project Settings.
#include "TalkingMesh.h"
#include "ConstructorHelpers.h"




ATalkingMesh::ATalkingMesh()
    :Super()
{
	// FObjectFinder 클래스의 인스턴스를 만들었고, 템플릿의 파라메터로 로드하기 원하는 에셋의 타입을 남겼다.
	// FObjectFinder 는 에셋을 로드할 수 있도록 돕는 클래스 템플릿이다.
	// 생성할 때, 로드할 에셋의 경로가 포함된 문자열을 남긴다.
	// 문자열은 {ObjectType}'/Path/To/Asset.Asset'" 형식이다.
    auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (MeshAsset.Object != nullptr)
    {
        GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
        //GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
        GetStaticMeshComponent()->bGenerateOverlapEvents = true;
    }
    GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
    SetActorEnableCollision(true);
}

void ATalkingMesh::StartTalking_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Hello there. What is your name?"));
}

