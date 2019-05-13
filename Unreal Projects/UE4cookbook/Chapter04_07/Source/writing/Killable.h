#pragma once

#include "Killable.generated.h"


/**
	블루프린트에서 테스트하기 위해 블루프린트를 통해 호출할 수 있는 인터페이스 함수를 만들어야 하고
	블루프린트에서 호출할 수 있도록 UFunction 지정자가 필요하다.
	그러나 UInterface 에서, 컴파일러는 기본으로 C++ 으로 구현할 것을 요구한다.
	이것은 BlueprintCallable 과 상충되고, 단순하게 함수가 블루프린트로 실행될 수 있고, 재정의할 수 없음을 나타낸다.
	CannotImplementInterfaceInBlueprint 으로 인터페이스를 마킹해서, 충돌하는 문제를 해결할 수 있다.
	CannotImplementInterfaceInBlueprint 보다는 UFunction 지정자로 BlueprintCallable 을 사용한다.
*/
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class WRITING_API UKillable: public UInterface
{
        GENERATED_BODY()
};

/**  */
class WRITING_API IKillable
{
        GENERATED_BODY()

    public:
        UFUNCTION(BlueprintCallable, Category=Killable)
        virtual bool IsDead();
        UFUNCTION(BlueprintCallable, Category=Killable)
        virtual void Die();

};
