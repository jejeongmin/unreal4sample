// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Wearable.h"
#include "Boots.generated.h"

UCLASS()
class WRITING_API ABoots : public AActor, public IWearable
{
        GENERATED_BODY()

    public:
        // Sets default values for this actor's properties
        ABoots();

        // Called when the game starts or when spawned
        virtual void BeginPlay() override;

        // Called every frame
        virtual void Tick( float DeltaSeconds ) override;

		/*
			Boots 클래스는 IWearable 을 구현하지만, 기본 기능을 재정의하지는 않는다.
			그러나 _Implementation 함수들은 가상함수로 정의되기 때문에 명시적으로
			인터페이스를 구현할 필요가 있고 기본 구현으로 직접적으로 호출해줘야 한다.

			대조적으로 Gloves 는 IWearable 을 구현하지만 블루프린트 안에서 OnEquip 의 구현을 재정의한다.
		*/
        virtual void OnEquip_Implementation(APawn* Wearer) override
        {
            IWearable::OnEquip_Implementation(Wearer);
        }
        virtual bool CanEquip_Implementation(APawn* Wearer) override
        {
            return IWearable::CanEquip_Implementation(Wearer);
        }
        virtual int32 GetStrengthRequirement_Implementation() override
        {
            return IWearable::GetStrengthRequirement_Implementation();
        }

};
