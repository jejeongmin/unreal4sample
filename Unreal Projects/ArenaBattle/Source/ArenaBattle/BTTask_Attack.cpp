// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "ABAIController.h"
#include "ABCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

/*
	chapter 12

	캐릭터의 델리게이트 설정이 완료되면 태스크에서 람다 함수를 해당 델리게이트에 등록하고 Tick 함수 로직에서 이를 파악해
	FinishLatentTask 함수를 호출함으로써 태스크를 종료하도록 구현한다.
*/
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == character)
		return EBTNodeResult::Failed;

	character->Attack();
	IsAttacking = true;
	character->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
