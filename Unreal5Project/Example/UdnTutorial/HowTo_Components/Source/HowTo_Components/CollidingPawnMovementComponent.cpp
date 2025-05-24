// Fill out your copyright notice in the Description page of Project Settings.

#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// 모든 것이 아직 유효한지, 이동 가능한지 확인합니다.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// ACollidingPawn::Tick 에 설정한 무브먼트 벡터를 구(한 뒤 소거)합니다.
	// ConsumeInputVector() -> 대기중인 입력을 반환하고 다시 0으로 설정하는 함수
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	
	DesiredMovementThisFrame += FVector(0.f, 0.f, -0.5f);

	// 바로 위에서 중력 적용을 했기 때문에 사실상 IsNearlyZero 인 경우는 없다. 그래서 주석 처리했음
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// 무언가에 부딛혔으면, 돌아가 봅니다.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
};