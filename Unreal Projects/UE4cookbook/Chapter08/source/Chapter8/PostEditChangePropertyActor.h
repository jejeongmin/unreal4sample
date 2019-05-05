// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PostEditChangePropertyActor.generated.h"

UCLASS()
class CHAPTER8_API APostEditChangePropertyActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostEditChangePropertyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		bool ShowStaticMesh;

	/*
		디자이너가 레벨에 배치된 액터의 property 를 변경하면 레벨을 시뮬레이션하거나 재생할 때 가 아닌
		즉시 시각적으로 변경된 결과를 표시하는 것이 중요하다.

		세부 정보 패널을 사용해 변경사항을 적용하면 편집 중인 property 에 응답할 수 있는 클래스의 인스턴스를
		제공하는 PostEditChangeProperty 라는 특수 이벤트가 발생한다.
	*/
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


	

};
