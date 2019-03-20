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

	UI ������ NativeConstruct �Լ��� AddToViewport �Լ��� �ܺο��� ȣ��� �� UI ������ �ʱ�ȭ�Ǹ鼭 ȣ��ȴٴ� Ư¡�� ������.
	�׷��� �÷��̾� ��Ʈ�ѷ��� ShowResultUI �Լ����� AddToViewport �Լ��� ȣ���ϱ� ���� �̸� UI ������ ���ӽ�����Ʈ�� ������ �о���� �� �ֵ��� ���ε��� �����Ѵ�.
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


