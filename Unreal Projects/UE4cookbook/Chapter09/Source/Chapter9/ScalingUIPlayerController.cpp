// Fill out your copyright notice in the Description page of Project Settings.

#include "ScalingUIPlayerController.h"



/*
	�𸮾��� ȭ�� ũ�⿡ ���� ����� �������̽��� Ȯ���� �� �ִ� UI Scaling �ý����� �⺻���� �����Ѵ�.
	������ �� ���� �ý���������, ������ �ִ�.
	���� ���� �ػ󵵿����� �ʹ� �۰� �����ϸ��Ǿ� �ؽ�Ʈ�� �б� ����� ���� �ִ�.
	�Ʒ��� ����� Ȱ���ϸ� ������ ȭ�� �ػ󵵿� ���� ȭ���� ��� ��Ʈ���� �������ϴ� ���� ������ �����ڸ� ������ �� �ִ�.

	1. DefaultEngine.ini �� ����.
	2. [/Script/Engine.UserInterfaceSettings] ���� ã�´�.
	3. UIScaleCurve ��� Ű�� ã�´�.
	4. �� ������ (Time=���� ���� �ػ�,Value=���� �ػ󵵿����� �����ϸ� ��) ���ϴ� �ػ��� ������ ���� 1 �� �����Ѵ�.

	or

	���� ������ �𸮾� ������ ������Ʈ ���� > User Interface > DPI Scaling ���� �����ϰ� ������ �� �ִ�.
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
