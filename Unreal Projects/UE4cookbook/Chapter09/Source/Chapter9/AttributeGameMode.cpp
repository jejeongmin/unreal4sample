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
			// FText 타입의 Text 속성에 무언가를 배정한다. 이 속성에 TAttribute<FText> 를 할당할 수 있으며
			// UI 가 최신 상태로 유지하려고 할 때마다 TAttribute::Get() 함수가 호출된다.
			SNew(STextBlock)
			.Text(TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateUObject(this, &AAttributeGameMode::GetButtonLabel)))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
}

/*
	TAttribute 클래스는 속성이 연관된 실제 변수 타입을 템플릿으로 만들기 때문에 반환값으로서 변수 타입을 템플릿으로 하는 델리게이트가 필요하다.
	말하자면 TAttribute<FText> 를 가진다면 이것에 연결된 델리게이트는 FText 를 반환해야 한다.
*/
FText AAttributeGameMode::GetButtonLabel() const
{
	FVector ActorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return FText::FromString(FString::Printf(TEXT("%f, %f, %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z));
}
