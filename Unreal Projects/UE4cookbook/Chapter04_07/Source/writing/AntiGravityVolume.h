// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AntiGravityVolume.generated.h"

UCLASS()
class WRITING_API AAntiGravityVolume : public AActor
{
        GENERATED_BODY()

    public:
        // Sets default values for this actor's properties
        AAntiGravityVolume();

        // Called when the game starts or when spawned
        virtual void BeginPlay() override;

        // Called every frame
        virtual void Tick( float DeltaSeconds ) override;

		// 클래스 선언에 추가된 UPROPERTY 매크로는 우리 액터의 하위 객체처럼 사용하는 컴포넌트들을 유지하고 있는 포인터이다.
		// 선언된 객체의 포인터가 레퍼런스되는 것으로 간주하고, 우리가 원치 않는 상황에서, 포인터가 댕글링되도록 GC되지 않는다는 것을 보장한다.
        UPROPERTY()
        class UBoxComponent* CollisionComponent;


    public:
        virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


        virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

};
