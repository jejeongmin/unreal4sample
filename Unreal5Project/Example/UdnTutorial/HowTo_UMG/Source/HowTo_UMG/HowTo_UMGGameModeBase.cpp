// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_UMGGameModeBase.h"

void AHowTo_UMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

// �� �ڵ�� ������ ���� �ν��Ͻ��� ����� ȭ�鿡 �ֽ��ϴ�.
// �𸮾� ������ �� ���� �ټ��� ���� ǥ�� �� ��ȣ�ۿ� ó���� �����ϱ�� ������, 
// �� ���� �ϳ��� Ȱ��ȭ�ǵ��� ���Ÿ� �ϱ⵵ �մϴ�.���� �� ���� �Ҹ��ų �ʿ�� ���� ���µ�, 
// ����Ʈ������ ���� �� ���۷����ϴ� ��� ���� �Ұ�(�Ǵ� ����) �۾��� �𸮾� ���� �� ������ �÷��� �ý��ۿ��� �� �ֱ� �����Դϴ�.
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