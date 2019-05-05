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
			// TAttribute ���� �˻��ϴµ� ���� �Լ��� ����� ���� �ؽ�Ʈ ����� ���� �����Ѵ�.
			// Get �� �̿��� Label TAttribute ���� �˻��ϴµ� ���� �Լ��� ����ϰ� FText �� ��ȯ�� ���� �ؽ�Ʈ ����� Text �Ӽ����� �����Ѵ�.
			SNew(STextBlock)
			.Text_Lambda([this] {return FText::FromString(Label.Get()); })
		]
	];
}
