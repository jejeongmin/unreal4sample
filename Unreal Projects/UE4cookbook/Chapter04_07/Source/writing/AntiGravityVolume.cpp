// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiGravityVolume.h"
#include "GravityObject.h"
#include "Engine.h"

// Sets default values
AAntiGravityVolume::AAntiGravityVolume()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

	// 사용자 정의 액터는 다른 액터에 붙이지 않고서는 위치를 가질 수 없다.
	// 루트 컴포넌트 없이 액터는 기본 트랜스폼을 가질 수 없기 때문에, 위치를 가질 수 없다.
	// 대부분의 액터들은 사용성을 위해 적어도 1개의 컴포넌트를 요구한다.
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
    CollisionComponent->SetBoxExtent(FVector(200, 200, 400));
    RootComponent = CollisionComponent;

}

// Called when the game starts or when spawned
void AAntiGravityVolume::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AAntiGravityVolume::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

void AAntiGravityVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
    IGravityObject* GravityObject = Cast<IGravityObject>(OtherActor);
    if (GravityObject != nullptr)
    {
        GravityObject->DisableGravity();
    }
}

void AAntiGravityVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
    IGravityObject* GravityObject = Cast<IGravityObject>(OtherActor);
    if (GravityObject != nullptr)
    {
        GravityObject->EnableGravity();
    }
}

