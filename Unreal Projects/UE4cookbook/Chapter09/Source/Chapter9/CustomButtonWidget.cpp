// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomButtonWidget.h"


TSharedRef<SWidget> UCustomButtonWidget::RebuildWidget()
{
	MyButton = SNew(SCustomButton)
		.ButtonClicked(BIND_UOBJECT_DELEGATE(FOnClicked, OnButtonClicked));
	return MyButton.ToSharedRef();
}

UCustomButtonWidget::UCustomButtonWidget()
	:Label(TEXT("Default Value"))
{

}

FReply UCustomButtonWidget::OnButtonClicked()
{
	ButtonClicked.Broadcast();
	return FReply::Handled();
}

/*
	이 함수는 UWiwget 클래스에서 연결된 속성을 연결된 SWidget 에 적용한다.
*/
void UCustomButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	TAttribute<FString> LabelBinding = OPTIONAL_BINDING(FString, Label);
	MyButton->Label = LabelBinding;
	
	
}
