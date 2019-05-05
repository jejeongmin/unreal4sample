// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "King.generated.h"

// 이 매크로는 생성되는 델리게이트 시그니처의 타입 이름, 시그니처 파라미터의 타입, 시그니처의 파라미터 이름 등 여러 가지 인자를 취급한다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKingDeathSignature, AKing*, DeadKing);

UCLASS()
class CHAPTER8_API AKing : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKing();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// 다이내믹 델리게이트는 UPROPERTY 선언에서 BlueprintCallable 로 표시될 수 있다.
	// BlueprintCallable 은 델리게이트의 브로드캐스트 함수가 호출될 때 호출될 델리게이트에 언리얼 블루프린트 시스템을 동적으로 할당할 수 있음을 나타낸다.
	UFUNCTION(BlueprintCallable, Category = King)
		void Die();

	UPROPERTY(BlueprintAssignable)
	FOnKingDeathSignature OnKingDeath;
	
};
