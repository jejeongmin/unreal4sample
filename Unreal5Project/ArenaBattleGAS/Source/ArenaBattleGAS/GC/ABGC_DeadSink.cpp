// Fill out your copyright notice in the Description page of Project Settings.


#include "GC/ABGC_DeadSink.h"

bool AABGC_DeadSink::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters)
{
    Super::OnExecute_Implementation(Target, Parameters);
    bIsSinking = true;
    ElapsedTime = 0.0f;
    InitialLocation = Target->GetActorLocation();
    SetActorTickEnabled(true);

    TargetActor = Target; // TargetActor를 설정합니다.

    return true;
}

void AABGC_DeadSink::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsSinking && TargetActor.IsValid())
    {
        ElapsedTime += DeltaSeconds;
        FVector NewLocation = InitialLocation;
        NewLocation.Z -= SinkSpeed * ElapsedTime;
        TargetActor->SetActorLocation(NewLocation);

        if (ElapsedTime >= SinkDuration)
        {
            bIsSinking = false;
            SetActorTickEnabled(false);
            
            // TargetActor(캐릭터) Destroy
            //TargetActor->Destroy();

            // 이 GameplayCue Actor도 Destroy
            Destroy();
        }
    }
}