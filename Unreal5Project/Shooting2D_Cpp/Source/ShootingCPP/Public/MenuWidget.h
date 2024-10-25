// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UButton* button_Restart;

    // meta 정보의 BindWidget 의 경우 c++ 에서 만든 변수를 실제 위젯 블루프린트와 연동하는 역할을 한다.
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UButton* button_Quit;

private:
    UFUNCTION()
    void Restart();

    UFUNCTION()
    void Quit();

protected:
    virtual void NativeConstruct() override;

};
