// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPlayerController::Possess(APawn *aPawn)
{
	ABLOG_S(Warning);
	Super::Possess(aPawn);
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*
		chapter 5

		플레이어 컨트롤러는 게임에서의 입력과 출력되는 화면을 책임진다.
		블레이어 컨트롤러에게 UI 를 배제하고 게임에게만 입력을 전달하도록 아래와 같이 명령을 내릴 수 있다.
		에디터에서 매번 뷰포트를 클릭하지 않아도 되기 때문에 테스트할 때 편리하다.
		에디터 모드일 때 한해서 아래와 같이 동작하게 코딩해두면 좋을 것 같다.
	*/
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
		chapter 5

		폰을 조종하기 위한 입력 로직은 폰 클래스에 구현하는 것이 일반적이다.
		하지만 언리얼 엔진의 입력 시스템은 중간에 플레이어 컨트롤러를 거쳐서 폰에 전달된다.
		만일 플레이어 컨트롤러에 특정 입력을 처리하는 코드를 구현하면
		해당 입력은 플레이어 컨트롤러에서 필터링되어 폰에 더 이상 전달되지 않는다.
	*/
	//InputComponent->BindAxis(TEXT("LeftRight"), this, &AABPlayerController::LeftRight);
	
}

void AABPlayerController::LeftRight(float NewAxisValue)
{
	// do nothing!!!
}