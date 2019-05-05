// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Widget.h"
#include "CustomButton.h"
#include "SlateDelegates.h"
#include "CustomButtonWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FGetString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);
/**
 * 선언된 SWidget ( CustomButton ) 이 있으므로 디자이너가 WYSIWYG 에디터에서 위젯을 사용할 수 있도록
 * 위젯을 UMG시스템에 표시하는 UWidget 래퍼 객체를 만들어야 한다.
 */
UCLASS()
class CHAPTER9_API UCustomButtonWidget : public UWidget
{
	GENERATED_BODY()
	
protected:
	// UWidget 객체는 소유한 실제 SWidget 객체 참조가 있어야 한다. 그래서 클래스에서 공유포인터로 저장해 protected 멤버에 위치한다.
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
