// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Widget.h"
#include "CustomButton.h"
#include "SlateDelegates.h"
#include "CustomButtonWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FGetString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);
/**
 * ����� SWidget ( CustomButton ) �� �����Ƿ� �����̳ʰ� WYSIWYG �����Ϳ��� ������ ����� �� �ֵ���
 * ������ UMG�ý��ۿ� ǥ���ϴ� UWidget ���� ��ü�� ������ �Ѵ�.
 */
UCLASS()
class CHAPTER9_API UCustomButtonWidget : public UWidget
{
	GENERATED_BODY()
	
protected:
	// UWidget ��ü�� ������ ���� SWidget ��ü ������ �־�� �Ѵ�. �׷��� Ŭ�������� ���������ͷ� ������ protected ����� ��ġ�Ѵ�.
	TSharedPtr<SCustomButton> MyButton;
	
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	UCustomButtonWidget();
	//multicast
	UPROPERTY(BlueprintAssignable)
	FButtonClicked ButtonClicked;

	FReply OnButtonClicked();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Label;

	//MUST be of the form varnameDelegate
	UPROPERTY()
	FGetString LabelDelegate;

	virtual void SynchronizeProperties() override;

};
