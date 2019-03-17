// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
	chapter 11

	AI ��Ʈ�ѷ����� PathFollowingComponent �� �پ� �־ �ڽ��� �����ϴ� ���� ��ã�⸦ ���� ���������� �����ϴ��� ���������� �����Ѵ�.
 */
UCLASS()
class ARENABATTLE_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	AABAIController();
	virtual void Possess(APawn* InPaw) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;

/*
	chapter 12.
	
	�����̺�� Ʈ�� ���� �ʰ� ���� ABCharacter �� �����̱� ���� ����� �ӽ� ����
	RepeatInterval ���� �������� ĳ���͸� �̵���Ų��.

public:
	virtual void UnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
*/
};
