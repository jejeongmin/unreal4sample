// Fill out your copyright notice in the Description page of Project Settings.


#include "GC/ABGC_DeadSink.h"

bool AABGC_DeadSink::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    Super::OnActive_Implementation(MyTarget, Parameters);
    bIsSinking = true;
    ElapsedTime = 0.0f;
    InitialLocation = MyTarget->GetActorLocation();
    SetActorTickEnabled(true);

	TargetActor = MyTarget; // TargetActor�� �����մϴ�.

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
            
            // TargetActor(ĳ����) Destroy
            //TargetActor->Destroy();

            // �� GameplayCue Actor�� Destroy
            Destroy();
        }
    }
}