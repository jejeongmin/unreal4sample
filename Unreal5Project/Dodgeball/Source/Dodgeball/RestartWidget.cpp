// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"

/*
*	BeginPlay �Լ��� ����ϰ� �� ���� ȣ��ǹǷ�, ���� �۾��� �ϱ⿡ �����ϴ�.
*/
void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr)
	{
		// AddDynamic �Լ��� ȣ���� ���� UFUNCTION ��ũ�η� ǥ�õ� �Լ��� �����͸� �Ķ���ͷ� �����ؾ� �Ѵ�.
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
	}
}

void URestartWidget::OnRestartClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}

	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}