// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SCompoundWidget.h"

/**
	두 위젯을 함께 복합 구조로 모으려고 하기 때문에 SCompoundWidget 의 서브클래스로 새로운 위젯을 만든다.
	SCompoundWidget 을 사용하면 위젯 자체로 위젯 계층 구조를 캡슐화할 수 있다.
 */
class CHAPTER9_API SCustomButton : public SCompoundWidget
{
	// 아래 매크로를 통해 FArguments 라는 내부 구조체를 선언한다.
	SLATE_BEGIN_ARGS(SCustomButton)
		: _Label(TEXT("Default Value"))
		, _ButtonClicked()
	{}
		SLATE_ATTRIBUTE(FString, Label)SCompoundWidget
		SLATE_EVENT(FOnClicked, ButtonClicked)
	SLATE_END_ARGS()
		
public:
	void Construct(const FArguments& InArgs);
	TAttribute<FString> Label;
	FOnClicked ButtonClicked;
};
