#pragma once

#include "AttackAvoider.generated.h"


/**  */
UINTERFACE()
class WRITING_API UAttackAvoider: public UInterface
{
        GENERATED_BODY()
};

/**
	�������̽��� �Լ��� �߰��� �� BlueprintImplementableEvent �� ����ϸ� �������Ʈ �ȿ��� �������̽��� ������ �� �ִ�.
*/
class WRITING_API IAttackAvoider
{
        GENERATED_BODY()

    public:
        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = AttackAvoider)
        void AttackIncoming(AActor* AttackActor);
};
