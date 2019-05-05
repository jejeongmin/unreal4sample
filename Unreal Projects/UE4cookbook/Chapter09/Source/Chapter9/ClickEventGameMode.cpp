// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickEventGameMode.h"



/*
	OnClicked 는 델리게이트 속성이다. 이는 버튼이 클릭됐을 때, 이름에서 알 수 있듯이
	버튼이 특정 이벤트마다 발생할 때마다 OnClicked 델리게이트를 전송한다는 의미다.
	델리게이트를 등록하거나 듣거나 참조하는 이벤트에 대한 알림을 받으려면 속성에 델리게이트 인스턴스를 할당해야 한다.
	
	CreateUObject, CreateStatic, CreateLambda 같은 표준 델리게이트 함수를 사용해 델리게이트 등록을 수행할 수 있다.
	이것들 모두 동작할 것이고 UObject 멤버 함수, 정적 함수, 람다와 기타 함수들을 바인드할 수 있다.
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
	FReply::Handled() 는 FReply 가 프레임워크에 이 이벤트가 처리되었음을 알려준다.
	만약 FReply::Unhandled()를 사용했다면, 이 이벤트가 처리되지 못했을 말하는 것이고,
	프레임워크는 대신 이벤트에 관심있는 다른 객체를 찾아야 할 것이다.
*/
FReply AClickEventGameMode::ButtonClicked()
{
	ButtonLabel->SetText(FString(TEXT("Clicked!")));

	return FReply::Handled();
}
