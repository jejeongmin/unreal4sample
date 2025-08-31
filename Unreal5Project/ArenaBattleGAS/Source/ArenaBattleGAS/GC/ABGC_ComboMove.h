// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "ABGC_ComboMove.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGC_ComboMove : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
public:
	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void StartComboMove();

protected:
	bool bIsComboMoving = false;
	float ComboMoveDistance = 50.f; // �� �̵� �Ÿ�
	float ComboMoveElapsed = 0.f;
	float ComboMoveDuration = 0.2f; // �̵��� �ɸ� �ð�(���� ���������� �ð�, �ʿ�� ����)
	FVector ComboMoveStart;
	FVector ComboMoveEnd;

    TWeakObjectPtr<AActor> TargetActor;
};
