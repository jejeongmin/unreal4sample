// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "ABGC_DeadSink.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGC_DeadSink : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
    virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    bool bIsSinking = false;
    float SinkSpeed = 50.0f;
    float SinkDuration = 2.0f;
    float ElapsedTime = 0.0f;
    FVector InitialLocation;

    TWeakObjectPtr<AActor> TargetActor;	
};
