// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "King.generated.h"

// �� ��ũ�δ� �����Ǵ� ��������Ʈ �ñ״�ó�� Ÿ�� �̸�, �ñ״�ó �Ķ������ Ÿ��, �ñ״�ó�� �Ķ���� �̸� �� ���� ���� ���ڸ� ����Ѵ�.
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

	// ���̳��� ��������Ʈ�� UPROPERTY ���𿡼� BlueprintCallable �� ǥ�õ� �� �ִ�.
	// BlueprintCallable �� ��������Ʈ�� ��ε�ĳ��Ʈ �Լ��� ȣ��� �� ȣ��� ��������Ʈ�� �𸮾� �������Ʈ �ý����� �������� �Ҵ��� �� ������ ��Ÿ����.
	UFUNCTION(BlueprintCallable, Category = King)
		void Die();

	UPROPERTY(BlueprintAssignable)
	FOnKingDeathSignature OnKingDeath;
	
};
