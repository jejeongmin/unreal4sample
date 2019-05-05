// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

/*
	Blueprintable 은 개발자가 Blueprint 클래스에서 상속받을 수 있는 클래스로 표시할 수 있음을 의미한다.
	
	때로는 일부 기능만 필요할 수도 있기 때문에 BlueprintType 과 Blueprintable 을 하나의 결합된 지정자 대신 사용할 수 있다.
	예를 들어 특정 클래스는 변수로 사용할 수 있지만 성능상의 이유로 인해 블루프린트에 생성할 수 없다.
	이 경우 두 지정자가 아닌 BlueprintType을 사용하게 된다.
	
	반면에 우리는 블루프린트 에디터를 사용해 새 하위 클래스를 만들고 싶지만, 액터 클래스 내부에서 객체 인스턴스를 전달하고 싶지는 않다.
	Blueprintable 을 사용하는 것을 추천하지만, 이 경우에는 BlueprintType 을 생략한다.
*/
UCLASS(Blueprintable)
class CHAPTER8_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY()
		FString WeaponName;
	UPROPERTY()
		int32 MaximumHealth;
};
