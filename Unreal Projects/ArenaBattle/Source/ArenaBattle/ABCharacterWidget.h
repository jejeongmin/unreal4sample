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
		�츮�� ����ϴ� ĳ���� ������ ĳ���Ϳ� ���縦 ���� �ϱ� ������ �� �������� ����� �ʿ����.
		�׷��� UI �� ���Ͱ� ���� �ٸ� ���Ͷ�� �������͸� ����ϴ� ���� �ٶ������� �����ֱ� ���� ������ �Ϻη� ����ߴ�.
	*/
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
