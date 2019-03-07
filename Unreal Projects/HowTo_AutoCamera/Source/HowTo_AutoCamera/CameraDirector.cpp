// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		// 로컬 플레이어의 컨트롤을 처리하는 액터를 찾습니다.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != Cameras[0].Camera) && (Cameras[0].Camera != nullptr))
				selectedCameraIndex = 0;
			else if ((OurPlayerController->GetViewTarget() != Cameras[1].Camera) && (Cameras[1].Camera != nullptr))
				selectedCameraIndex = 1;

			TimeToNextCameraChange += Cameras[selectedCameraIndex].TimeBetweenCameraChanges;

			if (Cameras[selectedCameraIndex].SmoothBlend)
				OurPlayerController->SetViewTargetWithBlend(Cameras[selectedCameraIndex].Camera, Cameras[selectedCameraIndex].SmoothBlendTime);
			else
				OurPlayerController->SetViewTarget(Cameras[selectedCameraIndex].Camera);
		}
	}
}

