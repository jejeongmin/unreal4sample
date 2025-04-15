// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_UMGGameModeBase.h"

void AHowTo_UMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

// 이 코드는 제공된 위젯 인스턴스를 만들어 화면에 넣습니다.
// 언리얼 엔진은 한 번에 다수의 위젯 표시 및 상호작용 처리가 가능하기는 하지만, 
// 한 번에 하나만 활성화되도록 제거를 하기도 합니다.위젯 을 직접 소멸시킬 필요는 절대 없는데, 
// 뷰포트에서의 제거 및 레퍼런싱하는 모든 변수 소거(또는 변경) 작업은 언리얼 엔진 의 가비지 컬렉션 시스템에서 해 주기 때문입니다.
void AHowTo_UMGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}