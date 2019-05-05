// Fill out your copyright notice in the Description page of Project Settings.

#include "ToggleHUDGameMode.h"




void AToggleHUDGameMode::BeginPlay()
{
	Super::BeginPlay();
	widget = SNew(SVerticalBox)
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
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), widget.ToSharedRef(), 1);

	// FTimerDelegate::CreateLambda 함수는 람다 함수를 타이머가 특정 간격으로 호출할 수 있는 델리게이트로 변환하도록 설계돼 있다.
	GetWorld()->GetTimerManager().SetTimer(HUDToggleTimer, FTimerDelegate::CreateLambda([this]
	{

		if (this->widget->GetVisibility().IsVisible())
		{
			this->widget->SetVisibility(EVisibility::Hidden);
		}
		else
		{
			this->widget->SetVisibility(EVisibility::Visible);
		}
	}), 5, true);
}

/*
	BeginPlay 중에 타이머를 설정하면 EndPlay 에서 타이머를 지우는 게 좋다.
	EndPlay 는 GameMode 가 종료되거나 파괴될 때마다 호출되므로 구현 중에 타이머를 안전하게 취소할 수 있다.
*/
void AToggleHUDGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(HUDToggleTimer);
}
