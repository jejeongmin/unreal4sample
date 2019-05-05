#pragma once

#include "Wearable.generated.h"


/**  */
UINTERFACE()
class WRITING_API UWearable: public UInterface
{
        GENERATED_BODY()
};

/**
	BlueprintNativeEvent 는 기본적으로 C++ 구현을 가지고 있고, 블루프린트로 재정의될 수 있는 UFUNCTION 을 의미한다.
	BlueprintNativeEvent 와 함께 가상 함수로 조합된다.

	구현 함수의 경우 interface 의 postfix 로 _Implementation() 를 붙여준다.
	즉 {interface name}__Implementation() 된다.

	적합한 함수가 호출되는 기능에서 기본 구현을 분리되기 위해 UHT 는 정의한 함수에서 이름을 취하고 끝에 _Implementation() 를 추가해
	새로운 함수를 정의한다.
*/
class WRITING_API IWearable
{
        GENERATED_BODY()

    public:
        UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
        int32 GetStrengthRequirement();
        UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
        bool CanEquip(APawn* Wearer);
        UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
        void OnEquip(APawn* Wearer);
};
