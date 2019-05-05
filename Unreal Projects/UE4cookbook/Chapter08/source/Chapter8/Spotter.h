// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Spotter.generated.h"

/*
	�������� �������� �𸣰�����, c++ Ŭ������ ������� Blueprint �� ������ ����,
	parent ����� �Ǵ� c++ Ŭ������ �����ϸ� ��ӹ��� Blueprint Ŭ���������� �� ���� ������ �ݿ����� �ʴ´�.

	������ �ٽ� ��ӹ޾� blueprint Ŭ������ ����� �ݿ��� �ȴ�.
	��� �޾� blueprint class �� �����ϴ� ������ ���������� �纻�� ������ �Ǵ°ǰ�?
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
