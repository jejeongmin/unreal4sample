// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

/*
	Blueprintable �� �����ڰ� Blueprint Ŭ�������� ��ӹ��� �� �ִ� Ŭ������ ǥ���� �� ������ �ǹ��Ѵ�.
	
	���δ� �Ϻ� ��ɸ� �ʿ��� ���� �ֱ� ������ BlueprintType �� Blueprintable �� �ϳ��� ���յ� ������ ��� ����� �� �ִ�.
	���� ��� Ư�� Ŭ������ ������ ����� �� ������ ���ɻ��� ������ ���� �������Ʈ�� ������ �� ����.
	�� ��� �� �����ڰ� �ƴ� BlueprintType�� ����ϰ� �ȴ�.
	
	�ݸ鿡 �츮�� �������Ʈ �����͸� ����� �� ���� Ŭ������ ����� ������, ���� Ŭ���� ���ο��� ��ü �ν��Ͻ��� �����ϰ� ������ �ʴ�.
	Blueprintable �� ����ϴ� ���� ��õ������, �� ��쿡�� BlueprintType �� �����Ѵ�.
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
