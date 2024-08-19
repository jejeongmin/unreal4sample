// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	void ShowRestartWidget();
	void HideRestartWidget();

private:

	// 이 속성은 블루프린트 클래스에서 편집할 수 없지만, UPROPERTY로 지정해야 한다. 이렇게 하지 않으면 GC가 이 변수의 컨텐츠를 삭제해버린다.
	UPROPERTY()
	class URestartWidget* RestartWidget;
};
