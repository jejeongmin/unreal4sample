// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomMovementComponent.generated.h"


// ���� ������Ʈ�� ���� ���̿� �����Ǵ� �������� ����� �����ϴ� ���� ����̴�.
// ���� ������Ʈ�� ���������� ������ �̺�Ʈ�� �����ϰų� �ٸ� ������ ������Ʈ�� ����ϴ� ���� ������ �� �ִ�.
// �� ������ Test ���������� �ð������� Ȯ���ϱ� ���� Sphere �� �ϳ� �ٿ��״�.

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