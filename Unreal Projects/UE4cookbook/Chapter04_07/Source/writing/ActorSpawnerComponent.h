// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorSpawnerComponent.generated.h"


/*
	씬 컴포넌트는 상대 위치, 회전, 스케일의 트랜스폼을 가진 액터 컴포넌트의 하위 클래스다.
	액터 컴포넌트처럼 씬 컴포넌트는 자체적으로 렌더링되지 못하지만, 액터에서 고정된 오프셋에 객체를 
	스폰시킨다든지 하는 다양한 이유로 트랜스폼이 사용될 수 있다.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WRITING_API UActorSpawnerComponent : public USceneComponent
{
        GENERATED_BODY()

    public:
        // Sets default values for this component's properties
        UActorSpawnerComponent();

		// UFunction 은 디버깅이 활성화된 플레이 세션 동안 개발자나 플레이어가 콘솔 커맨드를 실행할 수 있다는 의미로 exec 로 표시될 수 있다.
        UFUNCTION()
        void Spawn();

        UPROPERTY(EditAnywhere)
        TSubclassOf<AActor> ActorToSpawn;

    protected:
        // Called when the game starts
        virtual void BeginPlay() override;

    public:
        // Called every frame
        virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
