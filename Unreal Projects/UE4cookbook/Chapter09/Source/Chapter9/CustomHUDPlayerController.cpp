// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomHUDPlayerController.h"

/*
	게임이 실행될 때 로드되는 클래스 중 하나에서 UI 를 인스턴스화해야 해서 이 레시피에서는
	UI 를 생성하는 곳으로 사용자 정의 Controller 의 BeginPlay 함수를 사용한다.
*/
void ACustomHUDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TSharedRef<SVerticalBox> widget = SNew(SVerticalBox) + SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Test Button")))
			]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), widget, 1);
}


