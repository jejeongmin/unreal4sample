// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
	chapter 11

	AI 컨트롤러에는 PathFollowingComponent 가 붙어 있어서 자신이 조종하는 폰이 길찾기를 통해 목적지까지 도달하는지 지속적으로 관리한다.
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

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;

/*
	chapter 12.
	
	비헤이비어 트리 쓰지 않고 직접 ABCharacter 를 움직이기 위해 사용한 임시 로직
	RepeatInterval 마다 랜덤으로 캐릭터를 이동시킨다.

public:
	virtual void UnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
*/
};
