// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickEventGameMode.h"



/*
	OnClicked �� ��������Ʈ �Ӽ��̴�. �̴� ��ư�� Ŭ������ ��, �̸����� �� �� �ֵ���
	��ư�� Ư�� �̺�Ʈ���� �߻��� ������ OnClicked ��������Ʈ�� �����Ѵٴ� �ǹ̴�.
	��������Ʈ�� ����ϰų� ��ų� �����ϴ� �̺�Ʈ�� ���� �˸��� �������� �Ӽ��� ��������Ʈ �ν��Ͻ��� �Ҵ��ؾ� �Ѵ�.
	
	CreateUObject, CreateStatic, CreateLambda ���� ǥ�� ��������Ʈ �Լ��� ����� ��������Ʈ ����� ������ �� �ִ�.
	�̰͵� ��� ������ ���̰� UObject ��� �Լ�, ���� �Լ�, ���ٿ� ��Ÿ �Լ����� ���ε��� �� �ִ�.
*/
void AClickEventGameMode::BeginPlay()
{
	Super::BeginPlay();
	Widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateUObject(this, &AClickEventGameMode::ButtonClicked))
		.Content()
		[
			SAssignNew(ButtonLabel, STextBlock)
			.Text(FText::FromString(TEXT("Click me!")))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GEngine->GetFirstLocalPlayerController(GetWorld())->
		SetInputMode(FInputModeUIOnly().SetWidgetToFocus(Widget));
}

/*
	FReply::Handled() �� FReply �� �����ӿ�ũ�� �� �̺�Ʈ�� ó���Ǿ����� �˷��ش�.
	���� FReply::Unhandled()�� ����ߴٸ�, �� �̺�Ʈ�� ó������ ������ ���ϴ� ���̰�,
	�����ӿ�ũ�� ��� �̺�Ʈ�� �����ִ� �ٸ� ��ü�� ã�ƾ� �� ���̴�.
*/
FReply AClickEventGameMode::ButtonClicked()
{
	ButtonLabel->SetText(FString(TEXT("Clicked!")));

	return FReply::Handled();
}
