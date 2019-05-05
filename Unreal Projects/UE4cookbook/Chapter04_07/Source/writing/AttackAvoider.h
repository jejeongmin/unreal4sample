#pragma once

#include "AttackAvoider.generated.h"


/**  */
UINTERFACE()
class WRITING_API UAttackAvoider: public UInterface
{
        GENERATED_BODY()
};

/**
	인터페이스로 함수를 추가할 때 BlueprintImplementableEvent 를 사용하면 블루프린트 안에서 인터페이스를 구현할 수 있다.
*/
class WRITING_API IAttackAvoider
{
        GENERATED_BODY()

    public:
        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = AttackAvoider)
        void AttackIncoming(AActor* AttackActor);
};
