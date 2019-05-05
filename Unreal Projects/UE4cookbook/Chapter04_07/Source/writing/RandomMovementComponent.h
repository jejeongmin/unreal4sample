// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomMovementComponent.generated.h"


// 액터 컴포넌트는 액터 사이에 공유되는 공통적인 기능을 구현하는 쉬운 방법이다.
// 액터 컴포넌트는 랜더링되지 않지만 이벤트를 구독하거나 다른 액터의 컴포넌트와 통신하는 일을 수행할 수 있다.
// 이 예제의 Test 레벨에서는 시각적으로 확인하기 위해 Sphere 를 하나 붙여뒀다.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WRITING_API URandomMovementComponent : public UActorComponent
{
        GENERATED_BODY()

    public:
        // Sets default values for this component's properties
        URandomMovementComponent();

        UPROPERTY()
        float MovementRadius;

    protected:
        // Called when the game starts
        virtual void BeginPlay() override;

    public:
        // Called every frame
        virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
