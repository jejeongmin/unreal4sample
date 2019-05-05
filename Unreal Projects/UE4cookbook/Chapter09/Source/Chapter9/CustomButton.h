// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SCompoundWidget.h"

/**
	�� ������ �Բ� ���� ������ �������� �ϱ� ������ SCompoundWidget �� ����Ŭ������ ���ο� ������ �����.
	SCompoundWidget �� ����ϸ� ���� ��ü�� ���� ���� ������ ĸ��ȭ�� �� �ִ�.
 */
class CHAPTER9_API SCustomButton : public SCompoundWidget
{
	// �Ʒ� ��ũ�θ� ���� FArguments ��� ���� ����ü�� �����Ѵ�.
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
