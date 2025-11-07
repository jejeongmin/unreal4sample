// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/LyraCameraComponent.h"
#include "Camera/LyraCameraMode.h"

ULyraCameraComponent::ULyraCameraComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), CameraModeStack(nullptr)
{
}

void ULyraCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (!CameraModeStack)
	{
		// 초기화 (BeginPlay와 같은)가 딱히 필요없는 객체로 NewObject로 할당
		CameraModeStack = NewObject<ULyraCameraModeStack>(this);
	}
}

void ULyraCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CameraModeStack);

	UpdateCameraModes();
}

void ULyraCameraComponent::UpdateCameraModes()
{
	check(CameraModeStack);

	// DetermineCameraModeDelegate는 CameraMode Class를 반환한다:
	// - 해당 delegate는 HeroComponent의 멤버 함수로 바인딩되어 있다
	if (DetermineCameraModeDelegate.IsBound())
	{
		if (const TSubclassOf<ULyraCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
			// CameraModeStack->PushCameraMode(CameraMode);
		}
	}
}