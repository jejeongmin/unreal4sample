// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABUIPlayerController.generated.h"

/**
 *	chapter 15

	상속받은 블루프린트에서 앞으로 띄울 UI 의 클래스 값을 에디터에서 설정할 수 있도록 위젯 클래스 속성을 추가하고 EditDefaultOnly 키워드를 지정한다.
 */
UCLASS()
class ARENABATTLE_API AABUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
	class UUserWidget* UIWidgetInstance;
};
