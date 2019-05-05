// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Spotter.generated.h"

/*
	버그인지 스펙인지 모르겠지만, c++ 클래스를 기반으로 Blueprint 를 생성한 이후,
	parent 기반이 되는 c++ 클래스를 수정하면 상속받은 Blueprint 클래스에서는 그 수정 내용이 반영되지 않는다.

	새로이 다시 상속받아 blueprint 클래스를 만들면 반영이 된다.
	상속 받아 blueprint class 를 생성하는 시점에 내부적으로 사본이 형성이 되는건가?
*/
UCLASS()
class CHAPTER8_API ASpotter : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpotter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnPlayerSpotted(APawn* Player);
	
};
