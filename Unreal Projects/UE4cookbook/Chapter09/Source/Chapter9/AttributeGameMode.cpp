// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeGameMode.h"




void AAttributeGameMode::BeginPlay()
{
	Super::BeginPlay();

	Widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Content()
		[
			// FText Ÿ���� Text �Ӽ��� ���𰡸� �����Ѵ�. �� �Ӽ��� TAttribute<FText> �� �Ҵ��� �� ������
			// UI �� �ֽ� ���·� �����Ϸ��� �� ������ TAttribute::Get() �Լ��� ȣ��ȴ�.
			SNew(STextBlock)
			.Text(TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateUObject(this, &AAttributeGameMode::GetButtonLabel)))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
}

/*
	TAttribute Ŭ������ �Ӽ��� ������ ���� ���� Ÿ���� ���ø����� ����� ������ ��ȯ�����μ� ���� Ÿ���� ���ø����� �ϴ� ��������Ʈ�� �ʿ��ϴ�.
	�����ڸ� TAttribute<FText> �� �����ٸ� �̰Ϳ� ����� ��������Ʈ�� FText �� ��ȯ�ؾ� �Ѵ�.
*/
FText AAttributeGameMode::GetButtonLabel() const
{
	FVector ActorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return FText::FromString(FString::Printf(TEXT("%f, %f, %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z));
}
