// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameplayResultWidget.h"
#include "Components/TextBlock.h"
#include "ABGameState.h"

void UABGameplayResultWidget::BindGameState(AABGameState * GameState)
{
	ABCHECK(nullptr != GameState);
	CurrentGameState = GameState;
}

/*
	chapter 15

	UI 위젯의 NativeConstruct 함수는 AddToViewport 함수가 외부에서 호출될 때 UI 위젯이 초기화되면서 호출된다는 특징을 가진다.
	그래서 플레이어 컨트롤러의 ShowResultUI 함수에서 AddToViewport 함수를 호출하기 전에 미리 UI 위젯이 게임스테이트의 정보를 읽어들일 수 있도록 바인딩을 설정한다.
*/
void UABGameplayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABCHECK(CurrentGameState.IsValid());

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	ABCHECK(nullptr != Result);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	ABCHECK(nullptr != TotalScore);
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
}


