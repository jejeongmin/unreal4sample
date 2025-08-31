// Fill out your copyright notice in the Description page of Project Settings.


#include "GC/ABGC_ComboMove.h"

bool AABGC_ComboMove::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters)
{
    Super::OnExecute_Implementation(Target, Parameters);

    TargetActor = Target; // TargetActor�� �����մϴ�.

	StartComboMove();

    return true;
}

void AABGC_ComboMove::StartComboMove()
{
	bIsComboMoving = true;
	ComboMoveElapsed = 0.f;

	if(TargetActor.IsValid())
	{
		ComboMoveStart = GetActorLocation();
		ComboMoveEnd = ComboMoveStart + GetActorForwardVector() * ComboMoveDistance;
	}	
}

void AABGC_ComboMove::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (bIsComboMoving)
	{
		ComboMoveElapsed += DeltaSeconds;
		float Alpha = FMath::Clamp(ComboMoveElapsed / ComboMoveDuration, 0.f, 1.f);

		// EaseOut: �ʹ� ������ �Ĺ� ������ (���� ����)
		float EaseAlpha = FMath::InterpEaseOut(0.f, 1.f, Alpha, 2.5f);

		FVector NewLocation = FMath::Lerp(ComboMoveStart, ComboMoveEnd, EaseAlpha);
		
		if (TargetActor.IsValid())
		{
			TargetActor->SetActorLocation(NewLocation, true); // Sweep�� true��!
		}			

		if (Alpha >= 1.f)
		{
			bIsComboMoving = false;
			Destroy();
		}
	}
}