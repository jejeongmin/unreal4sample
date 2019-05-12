// Fill out your copyright notice in the Description page of Project Settings.

#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ��� ���� ���� ��ȿ����, �̵� �������� Ȯ���մϴ�.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// ACollidingPawn::Tick �� ������ �����Ʈ ���͸� ��(�� �� �Ұ�)�մϴ�.
	// ConsumeInputVector() -> ������� �Է��� ��ȯ�ϰ� �ٽ� 0���� �����ϴ� �Լ�
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	
	DesiredMovementThisFrame += FVector(0.f, 0.f, -0.5f);

	// �ٷ� ������ �߷� ������ �߱� ������ ��ǻ� IsNearlyZero �� ���� ����. �׷��� �ּ� ó������
	//if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// ���𰡿� �ε�������, ���ư� ���ϴ�.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
};