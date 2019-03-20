// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UABCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	/*
		우리가 사용하는 캐릭터 위젯은 캐릭터와 생사를 같이 하기 때문에 약 포인터의 사용은 필요없다.
		그러나 UI 와 액터가 서로 다른 액터라면 약포인터를 사용하는 것이 바람직함을 보여주기 위한 예제로 일부러 사용했다.
	*/
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
