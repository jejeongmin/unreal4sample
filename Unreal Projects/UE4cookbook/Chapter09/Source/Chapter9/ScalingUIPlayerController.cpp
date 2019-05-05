// Fill out your copyright notice in the Description page of Project Settings.

#include "ScalingUIPlayerController.h"



/*
	언리얼은 화면 크기에 따라 사용자 인터페이스를 확장할 수 있는 UI Scaling 시스템이 기본으로 동작한다.
	장점이 더 많은 시스템이지만, 단점도 있다.
	아주 작은 해상도에서는 너무 작게 스케일링되어 텍스트를 읽기 어려울 수도 있다.
	아래의 방법을 활용하면 지정된 화면 해상도에 따라 화면의 모든 컨트롤을 스케일하는 전역 스케일 수정자를 제어할 수 있다.

	1. DefaultEngine.ini 를 연다.
	2. [/Script/Engine.UserInterfaceSettings] 절을 찾는다.
	3. UIScaleCurve 라는 키를 찾는다.
	4. 이 값에서 (Time=보통 세로 해상도,Value=좌측 해상도에서의 스케일링 값) 원하는 해상도의 스케일 값을 1 로 지정한다.

	or

	위의 설정은 언리얼 에디터 프로젝트 설정 > User Interface > DPI Scaling 에서 동일하게 조정할 수 있다.
*/
void AScalingUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TSharedRef<SVerticalBox> widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Test button")))
			]
		];

	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), widget, 1);
}
