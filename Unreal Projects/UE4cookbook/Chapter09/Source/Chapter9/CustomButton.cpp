// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomButton.h"

void SCustomButton::Construct(const FArguments& InArgs)
{
	Label = InArgs._Label;
	ButtonClicked = InArgs._ButtonClicked;
	ChildSlot.VAlign(VAlign_Center)
	.HAlign(HAlign_Center)
	[
		SNew(SButton)
		.OnClicked(ButtonClicked)
		.Content()
		[
			// TAttribute 값을 검색하는데 람다 함수를 사용해 내부 텍스트 블록의 값을 설정한다.
			// Get 을 이용해 Label TAttribute 값을 검색하는데 람다 함수를 사용하고 FText 로 변환한 다음 텍스트 블록의 Text 속성으로 저장한다.
			SNew(STextBlock)
			.Text_Lambda([this] {return FText::FromString(Label.Get()); })
		]
	];
}
